# experimental static (ecstatic?) compiler

import re
import json

from .mtypes import ModelType, ModelArray, ModelObject, ModelError, ModelPath, Symbols
from .mtypes import Jsonable, Number, JsonScalar
from .utils import split_object, model_in_models, all_model_type, constant_value, is_a_simple_object
from .utils import log, tname, MODEL_PREDEFS, partition
from .runtime.support import _path as json_path
from .analyze import ultimate_type, disjunct_analyse, distinct_prop_objects
from .model import JsonModel
from .language import Language, Code, Block, BoolExpr, PathExpr, PropMap, JsonExpr, StrExpr, Var
from .irep import IRep, optimizeIR, evaluate

# probability of named optional props in an object
MAY_P = 0.5

# expected number of props
DEF_E, REG_E, OTH_E = 0.5, 0.5, 1.0

# likely hint generation depending on threshold
# > => likely, ~ 0.0 => None, < => unlikely
def is_likely(count, threshold) -> bool|None:
    return None if abs(count - threshold) < 0.1 else count > threshold


class CodeGenerator:
    """JSON Models Compilation.

    - globs: global map of symbols.
    - language: target language abstraction.
    - execute: true for executable, false for module.
    - fname: entry function name.
    - prefix: use this prefix for file-level identifiers.
    - map_threshold: whether to inline property name checks (up to threshold) or use a map.
    - map_share: whether to share property maps
    - may_must_open_threshold: max number of optional props to mmop scheme, default 5
    - must_only_threshold: max number of mandatory props for must-only scheme, default 5
    - partition_threshold: max number of strings without search partitioning, 0 for no partitioning
    - or_must_prop: threshold to try or-list shortcut based on mandatory properties
    - sort_must: whether to sort must properties, default True
    - sort_may: whether to sort may properties, default True
    - report: whether to report rejection reasons.
    - path: whether to keep track of value path while checking.
    - debug: verbose debug mode.
    """

    def __init__(self, globs: Symbols, language: Language, fname: str = "check_model", *,
                 prefix: str = "", map_threshold: int = 3, map_share: bool = False,
                 may_must_open_threshold: int = 5, must_only_threshold: int = 5,
                 sort_must: bool = True, sort_may: bool = True, partition_threshold: int = 0,
                 or_must_prop: int = 0,
                 execute: bool = True, report: bool = True, path: bool = True,
                 package: str|None = None, debug: bool = False):

        super().__init__()

        self._globs = globs
        self._lang = language
        self._prefix = prefix
        self._map_threshold = map_threshold
        self._may_must_open_threshold = may_must_open_threshold
        self._must_only_threshold = must_only_threshold
        self._sort_must = sort_must
        self._sort_may = sort_may
        self._partition_threshold = partition_threshold
        self._map_share = map_share
        self._or_must_prop = or_must_prop
        self._report = report
        self._path = path
        self._package = package
        self._debug = debug

        self._code = Code(language, fname, executable=execute, package=package)

        # identifiers and functions
        # ident-prefix -> next number to use to ensure unique identifiers
        # FIXME global namespace! $-definitions -> function
        self._names: dict[str, str] = {}
        # /re.../ -> regex function name
        self._regs: dict[str, str] = {}
        # model path -> function name
        self._paths: dict[str|tuple[int|str, ...], str] = {}
        # already generated object paths
        self._generated: set[str|tuple[int|str, ...]] = set()
        # compiled json models ids
        self._compiled: set[int] = set()
        self._to_compile: dict[int, tuple[JsonModel, str]] = {}
        # already generated property maps: serialized to function name
        self._generated_maps: dict[str, str] = {}
        self.reset()

    def reset(self):
        """Reset internal attributes for reuse."""
        self._names.clear()
        self._regs.clear()
        self._paths.clear()
        self._generated.clear()
        self._compiled.clear()
        self._to_compile.clear()
        self._generated_maps.clear()

    def _exreg(self, jm: JsonModel, name: str, rname: str, remap: dict[str, str],
               regex: str, opts: str, path: str) -> Block:
        """Generate post regex code for extended regular expression."""
        gen = self._lang
        code = (
            gen.match_str_var(rname, "extract", "val", declare=True) +
            gen.match_var("match", gen.match_re(rname, "val", regex, opts), declare=True) +
            gen.if_stmt(gen.match_ko("match"), gen.ret(gen.false()))
        )
        checks = []
        # sname is the name of the substring
        first = True
        for sname, ref in remap.items():
            checks += gen.match_val("match", rname, sname, "extract", declare=first)
            checks += gen.if_stmt(
                gen.not_op(self._dollarExpr(jm, ref, "extract", path, is_raw=True)),
                gen.ret(gen.false()))
            first = False
        checks += gen.ret(gen.true())
        code += checks

        # generate the string check function
        self._code.strfun(name,  code)

        return []

    def _regex(self, jm: JsonModel, regex: str, path: str) -> str:
        """Compile a regular expression, with memoization, return function name."""
        gen = self._lang

        if regex not in self._regs:

            remap: dict[str, str] = {}
            nparen: int = 0
            pattern, ropts = regex[1:].rsplit("/", 1)
            assert ropts == "" or ropts.isalpha(), f"invalid options: {ropts}"

            # extract and check actual pattern
            try:
                # model eXtension
                # re: aiLmsux (Ascii/Unicode, Ignore case, Locale, Multi/Single-line, verbose)
                # js: dgimsuvy
                if "X" in ropts:
                    ropts = ropts.replace("X", "")

                    # match name to reference
                    def subref(match):
                        # log.debug(f"subref match={match}")
                        nonlocal nparen
                        nparen += 1
                        name = f"s{nparen}"
                        matched = match.group(0)
                        if len(matched) > 1:
                            matched = matched[1:-1]
                            if ":" in matched:
                                dollar, pattern = matched.split(":", 2)
                            else:
                                dollar, pattern = matched, ".*"
                            remap[name] = dollar
                            return gen.regroup(name, pattern)
                        else:  # no substitution
                            return matched

                    # FIXME this is possibly wrong
                    # we want both to count grouping parenthesis and ($FOO) pattern extensions
                    pattern = re.sub(r"\((\$\w+(:[^)]*)?\))?", subref, pattern)

                # statically check re validity by trying to compile it
                if self._lang._relib == "re2":
                    import re2 as rex
                else:
                    import re as rex

                # FIXME pcre2 and re syntax can differ
                rex.compile(pattern)

            except Exception as e:
                log.warning(f"possibly invalid regex: {regex} ({e})")

            # possibly generate extension function
            if remap:
                fun = gen.ident(self._prefix + "xre")
                self._code.regex(fun + "_re", pattern, ropts)
                self._exreg(jm, fun, fun + "_re", remap, pattern, ropts, path)
            else:
                fun = gen.ident(self._prefix + "re")
                self._code.regex(fun, pattern, ropts)

            # memoize
            self._regs[regex] = fun

        return self._regs[regex]

    def _regExpr(self, jm: JsonModel, regex: str,
                 val: JsonExpr|StrExpr, path: PathExpr, is_str: bool = False) -> BoolExpr:
        """Generate an inlined regex check expression on a value."""
        gen = self._lang
        sval: StrExpr = val if is_str else gen.value(val, str)  # type: ignore

        # optimized versions
        if re.match(r"^/\^?.\*\$?/[mis]?$", regex):
            return gen.true()
        elif re.match(r"^/(\?s)\.\+?/$", regex) or re.match(r"^/\.\+?/s$", regex):
            return gen.num_cmp(gen.str_len(sval), ">", gen.const(0))
        elif re.match(r"^/\^[^[({|.+*?\\^$]+/$", regex):  # starts with
            return gen.str_start(sval, regex[2:-1])
        elif re.match(r"^/[^[({|.+*?\\^$]+\$/$", regex):  # ends with
            return gen.str_end(sval, regex[1:-2])
        elif re.match(r"^/\^[^[({|.+*?\\^$]+\$/$", regex):  # streq
            return gen.str_cmp(sval, "=", gen.esc(regex[2:-2]))
        else:
            fun = self._regex(jm, regex, path)
            return gen.str_check_call(fun, sval, path)

    def _esc(self, val: Jsonable) -> str:
        """Escape value as necessary."""
        return json.dumps(val) if isinstance(val, str) else str(val)

    def _dollarExpr(self, jm: JsonModel, ref: str, val: str, vpath: str, *, is_raw: bool = False):
        """Generate a call to check for a $REF."""
        assert ref and ref[0] == "$"
        if ref in MODEL_PREDEFS:  # inline predefs
            return self._lang.predef(val, ref, vpath, is_raw)
        else:
            fun = self._getNameRef(jm, ref, [])
            return self._lang.check_call(fun, val, vpath, is_ptr=False, is_raw=is_raw)

    def _compileConstraint(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                           res: Var, val: JsonExpr, vpath: PathExpr):
        """Build constraint checking.

        This is kind of a pain because operators X overloading X types,
        plus the fact that the compiler may or may not know the value type statically.

        Comparison values may build a non satisfiable constraint, eg v >= 3 and v < 1.
        Type incompatibilities may also lead to rejections.
        """

        # TODO make it a function?
        assert isinstance(model, dict) and "@" in model
        smpath = json_path(mpath)
        gen = self._lang

        tmodel = ultimate_type(jm, model["@"])  # type: ignore
        assert tmodel in (bool, int, float, str, list, dict, type(None), None)

        # get which props are set
        cmp_props = set(filter(lambda k: k in {"<", ">", "=", "!=", ">=", "<="}, model.keys()))
        has_unique = "!" in model
        if has_unique and not isinstance(model["!"], bool):  # should not get there
            raise ModelError("unique constraint value must be a boolean")

        # simplify non empty string check based on length
        if (tmodel is str and len(cmp_props) == 1 and
            ((">=" in cmp_props and isinstance(model[">="], (int, float)) and 0 < model[">="] <= 1) or
             (">" in cmp_props and isinstance(model[">"], (int, float)) and 0 <= model[">"] < 1))):
            del model[">" if ">" in cmp_props else ">="]
            model["!="] = ""
            cmp_props = {"!="}

        # TODO ensure that not bool
        has_int = any(isinstance(model[k], int) for k in cmp_props)
        has_flt = any(isinstance(model[k], float) for k in cmp_props)
        has_str = any(isinstance(model[k], str) for k in cmp_props)

        # TODO allow any constant for comparisons?

        # static type eliminations, no need to check anything!
        # this is probably an unintended model error…
        elim: Block = []

        # per constraints
        if has_str and has_flt:
            elim += gen.lcom("cannot mix float and string constraints")

        # per model type
        if tmodel in (bool, type(None)) and (cmp_props or has_unique):
            elim += gen.lcom("no constraint allowed on bool or null")
            # else type check will be enough, standard case below
        elif tmodel in (dict, list) and (has_flt or has_str):
            elim += gen.lcom("no str/flt constraints on object or array")
        elif tmodel is str and has_flt:
            elim += gen.lcom("no float constraints on strings")
        elif tmodel in (int, float) and has_str:
            elim += gen.lcom("no string constraints on numbers")

        # per unique
        if has_unique and tmodel is not list:
            elim += gen.lcom(f"no unique constraint on {tname(tmodel)}")

        # TODO value-based elimination

        # TODO add to "optimize.py"
        if elim:
            log.warning(f"unfeasible model [{smpath}]")
            return elim + gen.bool_var(res, gen.false())  # type: ignore

        # initial model check
        code: Block = self._compileModel(jm, model["@"], mpath + ["@"], res, val, vpath,
                                         constrained=len(cmp_props) > 0)

        # shortcut if nothing to check
        if not cmp_props and not has_unique:
            return code

        checks: list[BoolExpr] = []
        cvars: Block = []
        if tmodel is None:
            # generic implementations if several model types, using runtime functions
            if has_unique:
                checks.append(gen.is_a(val, list))
                checks.append(gen.check_unique(val, vpath))
            for op in sorted(cmp_props):
                checks.append(gen.check_constraint(op, model[op], val, vpath))  # type: ignore
        else:
            # optimized known-type-specific code
            # NOTE we know that constraints make sense for the target type
            fval, sval, ival = None, None, None

            if has_unique:
                assert tmodel is list
                # TODO add const-based versions if more is known?
                checks.append(gen.check_unique(val, vpath))
            if has_int:
                if tmodel in (int, str, list, dict):
                    # skip float
                    ival = gen.ident("ival")
                    cvars += gen.int_var(ival, gen.any_int_val(val, tmodel), declare=True)
                else:
                    assert tmodel is float
                    fval = gen.ident("fval")
                    cvars += gen.flt_var(fval,
                        gen.value(val,
                            Number if jm._loose_float else float), declare=True)  # type: ignore
            if has_flt:
                if tmodel is float and not has_int:
                    fval = gen.ident("fval")
                    cvars += gen.flt_var(fval, gen.value(val,
                                         Number if jm._loose_float else float),  # type: ignore
                                         declare=True)
                elif tmodel is int:
                    fval = gen.ident("fval")
                    cvars += gen.flt_var(fval, gen.value(val, Number), declare=True)  # type: ignore
                # else cannot happen
            if has_str:
                assert tmodel is str  # redundant sanity check
                sval = gen.ident("sval")
                cvars += gen.str_var(sval, gen.value(val, str), declare=True)
            for op in sorted(cmp_props):  # FIXME looseness?
                vop = model[op]
                if isinstance(vop, int):
                    if tmodel is float:
                        checks.append(gen.num_cmp(fval, op, gen.const(vop)))  # type: ignore
                    else:
                        checks.append(gen.num_cmp(ival, op, gen.const(vop)))  # type: ignore
                elif isinstance(vop, str):
                    checks.append(gen.str_cmp(sval, op, gen.const(vop)))  # type: ignore
                elif isinstance(vop, float):
                    checks.append(gen.num_cmp(fval, op, gen.const(vop)))  # type: ignore

        assert checks
        if self._debug:
            log.debug(f"checks={checks}")

        code += gen.if_stmt(res,
            cvars + gen.bool_var(res, gen.and_op(*checks)) +
            self._gen_report(res, f"constraints failed [{smpath}]", vpath),
            likely=True
        )

        return code

    def _disjunction(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                     res: str, val: str, vpath: str, known: set[str]|None) -> Block|None:
        """Generate optimized disjunction check, return None if failed."""

        assert isinstance(model, dict) and "|" in model and isinstance(model["|"], list)

        dis = disjunct_analyse(jm, model, mpath, True)  # type: ignore
        log.debug(f"disjunct at {mpath}: dis={dis}")
        if dis is None:
            return None

        # disjunct: [(tag name, tag type, [0])], 0 -> p -> csts, 0 -> model
        disjuncts, all_const_props, others = dis
        smpath = json_path(mpath)
        gen = self._lang

        assert disjuncts, "non empty disjunction"

        # Compile all object models in the list if needed
        models = model["|"]
        assert isinstance(models, list)  # pyright hint

        mod_code: dict[int, Block] = {}

        for i, mi in enumerate(models):
            p = mpath + [i]
            tp = tuple(p)
            if isinstance(mi, str) and mi and mi[0] == "$":
                # it is a reference, it must be compiled for its name, no need to recompile it!
                fun = self._getNameRef(jm, mi, p)
                if tp not in self._paths:
                    # several path will lead to the same function
                    self._paths[tp] = fun
                mod_code[i] = gen.bool_var(res, gen.check_call(fun, val, vpath))
            elif tp not in self._paths:
                mod_code[i] = self._compileModel(jm, mi, p, res, val, vpath)

        # overall code
        code = []

        isobj = gen.is_a(val, dict)
        isovar = gen.ident("iso")
        isobj_needed = not known or isobj not in known

        code += gen.bool_var(isovar, isobj if isobj_needed else True, declare=True)

        # generate disjunction code
        alt_code: list[Block] = []
        for tag_name, tag_type, lalts in disjuncts:
            tag_code: Block = []
            cmap = gen.ident(self._prefix + "map")

            # mapping from tag values to check functions
            TAG_CHECKS: dict[JsonScalar, str] = {}
            for i in lalts:
                consts = all_const_props[i]
                tags = consts[tag_name]
                for t in sorted(tags):
                    TAG_CHECKS[t] = self._paths[tuple(mpath + [i])]
            self._code.cmap(cmap, TAG_CHECKS)

            tag = gen.ident("tag")
            itag = gen.json_var(tag, gen.obj_prop_val(val, tag_name, False), declare=True)

            fun = gen.ident("fun")
            ifun = gen.fun_var(fun, gen.get_cmap(cmap, tag, tag_type), True)
            icall = gen.bool_var(res, gen.check_call(fun, val, vpath, is_ptr=True))
            tagt = gen.if_stmt(
                gen.has_prop(val, tag_name),
                itag +
                ifun +
                gen.if_stmt(gen.is_def(fun),
                    icall,
                    gen.bool_var(res, gen.false()) +
                    gen.report(f"tag <{tag_name}> value not found [{smpath}]", vpath),
                    likely=True  # there is a tag
                ),
                gen.bool_var(res, gen.false()) +
                gen.report(f"tag prop <{tag_name}> is missing [{smpath}]", vpath),
                likely=True  # the tag value is valid
            )

            # reset res object test
            tag_code += gen.bool_var(res, gen.get_value(isovar, bool))

            # FIXME has_prop gets the tag value in C, so this means 2 get. alternate strategy?
            if isobj_needed:
                tag_code += gen.if_stmt(res,
                    tagt,
                    gen.report(f"value is not an object [{smpath}]", vpath),
                    likely=True
                )
            else:
                tag_code += tagt

            alt_code.append(tag_code)

        # build cascading alternative tests
        or_code: Block = None

        for i in reversed(others):
            if or_code is None:
                or_code = mod_code[i]
            else:
                or_code = mod_code[i] + gen.if_stmt(gen.not_op(res), or_code)

        for c in reversed(alt_code):
            if or_code is None:
                or_code = c
            else:
                or_code = c + gen.if_stmt(gen.not_op(res), or_code)

        return code + or_code

    def _gen_report(self, res: str, msg: str, path: str, cleanup: bool = False) -> Block:
        """Maybe generate a report."""
        if self._report:
            gen = self._lang
            if cleanup:
                return gen.if_stmt(res, gen.clean_report(), gen.report(msg, path), likely=True)
            else:
                return gen.if_stmt(gen.not_op(res), gen.report(msg, path), likely=False)
        else:
            return []

    def _gen_reporting(self, report: Block) -> Block:
        """Detailed reporting."""
        gen = self._lang
        return gen.if_stmt(gen.is_reporting(), report, likely=True) if self._report else []

    def _gen_fail(self, msg: str, path: PathExpr) -> Block:
        """Generate a report and return false."""
        gen = self._lang
        return gen.report(msg, path) + gen.ret(gen.false())

    def _gen_short_expr(self, expr: BoolExpr) -> Block:
        """Return immediately if expression is false."""
        gen = self._lang
        return gen.if_stmt(gen.not_op(expr), gen.ret(gen.false()), likely=False)

    def _gen_parts(self, var: str, codes: dict[int, Block]) -> Block:
        """Return dichotomic conditional blocks over partition conditions.
        The function assumes that len(codes) is a power of 2.
        """
        assert len(codes) >= 2
        gen = self._lang
        if len(codes) == 2:
            first, second = min(codes.keys()), max(codes.keys())
            return gen.if_stmt(gen.num_cmp(var, "<=", first, True), codes[first], codes[second])
        else:
            limit = list(sorted(codes.keys()))[len(codes) // 2 - 1]
            return gen.if_stmt(
                        gen.num_cmp(var, "<=", limit, True),
                        self._gen_parts(var, { v: c for v, c in codes.items() if v <= limit }),
                        self._gen_parts(var, { v: c for v, c in codes.items() if v > limit })
            )

    def _propmap_name(self, model: ModelObject, default: str) -> str:
        """Memoize property map names for reuse.

        However, generated model path are wrong.
        """
        assert isinstance(model, dict)
        if not self._map_share:
            return default
        # TODO ignore comments?!
        smodel = json.dumps(model, sort_keys=True)
        if smodel in self._generated_maps:
            return self._generated_maps[smodel]
        else:
            self._generated_maps[smodel] = default
            return default

    def _propmap_gen(self, jm: JsonModel, model: ModelObject, name: str, mpath: ModelPath):
        """Generate property map for sub-model."""
        assert isinstance(model, dict)

        prop_map: dict[str, str] = {}

        for p in sorted(model.keys()):
            m = model[p]
            if jm._isRef(m):
                # direct reference
                prop_map[p] = self._getNameRef(jm, m, mpath)
            else:
                pid = f"{name}_{p}"  # unique identifier for value function
                self._compileName(jm, pid, m, mpath + [p], True)
                prop_map[p] = self._getName(jm, pid)

        self._code.pmap(name, prop_map)

    # TODO known?
    def _closeMuObject(self, jm: JsonModel, must: dict[str, ModelType],
                        mpath: ModelPath, oname: str,
                        res: Var, val: JsonExpr, vpath: PathExpr) -> Block:
        """Optimize `{"x": ..., "": "y": ...}`."""

        assert isinstance(must, dict)
        gen = self._lang
        smpath = json_path(mpath)

        code = (
            gen.lcom("check close must only props") +
            # filter non object
            gen.if_stmt(gen.not_op(gen.is_a(val, dict)),
                        self._gen_fail(f"not an object [{smpath}]", vpath),
                        likely=False) +
            # filter ahead on the number of properties
            # NOTE necessary to detect unexpected misc property as the object is not scanned
            gen.if_stmt(gen.num_cmp(gen.obj_len(val), "!=", gen.const(len(must))),
                        self._gen_fail(f"bad property count [{smpath}]", vpath),
                        likely=False)
        )

        # value checks needs two variables
        if any(m != "$ANY" for m in must.values()):
            code += (
                gen.path_var("lpath", declare=True) +
                gen.json_var("pval", declare=True) +
                gen.bool_var(res, declare=True)
            )

        # may or may not be used
        lpath_ref: PathExpr = gen.path_lvar("lpath", vpath)

        # whether to combine property test and value extraction
        combined = gen.assign_obj_prop()

        # must properties
        for prop, pmodel in must.items():
            prop_fail: Block = self._gen_fail(f"missing mandatory prop <{prop}> [{smpath}]", vpath)
            if combined and pmodel != "$ANY":
                code += gen.if_stmt(
                    gen.not_op(gen.obj_has_prop_val("pval", val, prop, False)),
                    prop_fail,
                    likely=False
                )
            else:
                code += gen.if_stmt(gen.not_op(gen.has_prop(val, prop)), prop_fail, likely=False)
            if pmodel != "$ANY":
                code += gen.path_var("lpath", gen.path_val(vpath, prop, True, False))
                if not combined:
                    code += gen.json_var("pval", gen.obj_prop_val(val, prop, False))
                code += (
                    self._compileModel(jm, pmodel, mpath + [prop], res, "pval", lpath_ref) +
                    gen.if_stmt(
                        gen.not_op(res),
                        self._gen_fail(f"unexpected value for mandatory prop <{prop}> [{smpath}]",
                                       lpath_ref),
                        likely=False
                    )
                )

        return code + gen.ret(gen.true())

    # TODO known?
    # TODO fix vpath
    def _openMuMaObject(self, jm: JsonModel, must: dict[str, ModelType], may: dict[str, ModelType],
                        mpath: ModelPath, oname: str,
                        res: Var, val: JsonExpr, vpath: PathExpr) -> Block:
        """Optimize `{"x": ..., "": "?y": ..., "": "$ANY"}`."""

        assert isinstance(must, dict)
        gen = self._lang
        smpath = json_path(mpath)

        code = (
            gen.lcom("check open must/may only props") +
            gen.if_stmt(gen.not_op(gen.is_a(val, dict)),
                        self._gen_fail(f"not an object [{smpath}]", vpath),
                        likely=False)
        )

        # value checks?
        if any(m != "$ANY" for m in must.values()) or any(m != "$ANY" for m in may.values()):
            code += (
                gen.path_var("lpath", declare=True) +
                gen.json_var("pval", declare=True) +
                gen.bool_var(res, declare=True)
            )

        # may or may not be used
        lpath_ref: PathExpr = gen.path_lvar("lpath", vpath)

        # whether to combine test and assignment
        combined = gen.assign_obj_prop()

        for prop, pmodel in must.items():
            prop_fail: Block = self._gen_fail(f"missing mandatory prop <{prop}> [{smpath}]", vpath)
            if combined and pmodel != "$ANY":
                code += gen.if_stmt(
                    gen.not_op(gen.obj_has_prop_val("pval", val, prop, False)),
                    prop_fail,
                    likely=False
                )
            else:
                code += gen.if_stmt(gen.not_op(gen.has_prop(val, prop)), prop_fail, likely=False)
            if pmodel != "$ANY":
                code += gen.path_var("lpath", gen.path_val(vpath, prop, True, False))
                if not combined:
                    code += gen.json_var("pval", gen.obj_prop_val(val, prop, False))
                code += (
                    self._compileModel(jm, pmodel, mpath + [prop], res, "pval", lpath_ref) +
                    gen.if_stmt(
                        gen.not_op(res),
                        self._gen_fail(f"unexpected value for mandatory prop <{prop}> [{smpath}]",
                                       lpath_ref),
                        likely=False
                    )
                )

        expected_nprops = MAY_P * len(may)

        for prop, pmodel in may.items():

            if pmodel != "$ANY":
                likely = is_likely(MAY_P, 0.5 * expected_nprops)
                expected_nprops -= MAY_P
                check_value: Block = gen.path_var("lpath", gen.path_val(vpath, prop, True, False))
                has_prop: str
                if combined:
                    has_prop = gen.obj_has_prop_val("pval", val, prop)
                else:
                    has_prop = gen.has_prop(val, prop)
                    check_value += gen.json_var("pval", gen.obj_prop_val(val, prop, False))
                check_value += (
                    self._compileModel(jm, pmodel, mpath + [prop], res, "pval", lpath_ref) +
                    gen.if_stmt(
                        gen.not_op(res),
                        self._gen_fail(f"unexpected value for optional prop <{prop}> [{smpath}]",
                                       lpath_ref),
                        likely=False)
                )
                code += gen.if_stmt(has_prop, check_value, likely=likely)
            else:
                # covered by catchall, nothing to check!
                code += gen.lcom(f"ignored {smpath}.{prop}")

        return code + gen.ret(gen.true())

    def _compileObject(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                       oname: str, res: str, val: JsonExpr, vpath: PathExpr) -> Block:
        """Generate the body of a function which checks an actual object."""

        assert isinstance(model, dict)
        gen = self._lang

        # separate properties
        must, may, defs, regs, oth = split_object(model, mpath)
        smpath = json_path(mpath)

        # generated code helpers
        code: Block = []
        body_code: Block = []
        multi_if: list[tuple[BoolExpr, bool|None, Block]] = []
        prop, pval, must_c, pfun = "prop", "pval", "must_count", "pfun"

        # should be an object
        code += gen.if_stmt(gen.not_op(gen.is_a(val, dict)),
                            self._gen_fail(f"not an object [{smpath}]", vpath),
                            likely=False)

        # NOTE there may be different tradeoffs depending on the target languages,
        # libraries and the complexity of underlying operations.
        # This suggests that a cost/choice model could be used to decide based
        # on benchmarks.

        # shorcut for empty/any object
        if not must and not may and not defs and not regs:
            if not oth:  # empty object
                code += \
                    gen.if_stmt(
                        gen.num_cmp(gen.obj_len(val), "=", gen.const(0)),
                        gen.ret(gen.true()),
                        self._gen_fail(f"expecting empty object [{smpath}]", vpath),
                        likely=True
                    )
                return code
            elif oth == { "": "$ANY" }:  # any object (empty must/may/defs/regs)
                code += gen.lcom("accept any object") + gen.ret(gen.true())
                return code
            # only check values, fine code will be generated below

        # shortcut for open object with simple props only
        # TODO accept any other prop?
        if not defs and not regs and (must or may) and oth == {"": "$ANY"}:
            # if there are many may values, this may be too costly…
            ## if (len(may) / (len(must) + len(may)) < self._may_must_open_ratio or
            if (len(must) + len(may)) <= self._may_must_open_threshold:
                return self._openMuMaObject(jm, must, may, mpath, oname, res, val, vpath)

        # shortcut for must-only close object
        # NOTE we assume that this strategy is always beneficial, but it may depend on the target
        if must and not may and not defs and not regs and not oth and \
                len(must) <= self._must_only_threshold:
            return self._closeMuObject(jm, must, mpath, oname, res, val, vpath)

        # used for evaluating likely-ness
        expected_nprops = (
            len(must) +
            MAY_P * len(may) + DEF_E * len(defs) + REG_E * len(regs) +
            (OTH_E if oth else 0.0)
        )

        # path + [ prop ]
        lpath = gen.ident("lpath")
        lpath_ref: PathExpr = gen.path_lvar(lpath, vpath)

        # else we have some work to do!
        if defs or regs or oth and oth[""] != "$ANY" or \
                1 <= len(must) <= self._map_threshold or \
                1 <= len(may) <= self._map_threshold:
            code += gen.bool_var(res, declare=True)

        if len(may) > self._map_threshold or len(must) > self._map_threshold:
            # we need a function pointer for simple properties
            code += gen.fun_var(pfun, declare=True)

        hash_var = None

        # build multi-if structure to put in prop/val loop
        if must:

            # must prop counter to check at the end if all were seen
            code += gen.int_var(must_c, gen.const(0), True)

            if len(must) <= self._map_threshold:  # unroll property checks

                props = set(must.keys())
                if self._partition_threshold:
                    partitioning = partition(props, self._partition_threshold, gen._byte_order)
                else:
                    partitioning = None

                if partitioning is not None:
                    hash_size, partitions = partitioning
                    partitioned = True
                    # partition -> multi_if stuff
                    part_mif = { part: [] for part in partitions.keys() }
                    # property -> partition
                    prop_part = {}
                    for part, props in partitions.items():
                        for p in props:
                            prop_part[p] = part
                else:
                    # no partition
                    hash_size, partitions = 0, None
                    partitioned = False
                    partitions = { 255: props }
                    part_mif = { 255: [] }
                    prop_part = { p: 255 for p in props }

                log.debug(f"partitions = {partitions}")

                for part, props in partitions.items():

                    # subset of properties for this partition
                    must_pm = [ (p, m) for p, m in must.items() if prop_part[p] == part ]
                    if self._sort_must:
                        must_pm = sorted(must_pm, key=lambda pm: (len(pm[0]), pm[0]))

                    for p, m in must_pm:

                        likely = is_likely(1, 0.5 * expected_nprops)
                        expected_nprops -= 1

                        # TODO likely hint under partitioning?
                        if partitioned:
                            likely = None

                        mu_expr = gen.str_cmp(prop, "=", gen.esc(p))
                        mu_code = (
                            gen.lcom(f"handle must {p} property") +
                            gen.inc_var(must_c) +
                            self._compileModel(jm, m, mpath + [p], res, pval, lpath_ref) +
                            gen.if_stmt(gen.not_op(res),
                                self._gen_fail(
                                    f"invalid mandatory prop value [{json_path(mpath + [p])}]",
                                    lpath_ref),
                                likely=False) +
                            gen.cont()
                        )

                        part_mif[part] += [(mu_expr, likely, mu_code)]

                if partitioned:
                    part_code = { p: gen.mif_stmt(mi) for p, mi in part_mif.items() }
                    hash_var = gen.ident("hash")
                    body_code += (
                        gen.hash_var(hash_var, gen.str_hash(prop, hash_size), declare=True) +
                        self._gen_parts(hash_var, part_code)
                    )
                else:
                    # accumulate in global multi_if
                    body_code += gen.mif_stmt(part_mif[255])

            else:  # generic code with a map above threshold

                likely = is_likely(len(must), 0.5 * expected_nprops)
                expected_nprops -= len(must)

                candidate = f"{oname}_mup"
                prop_must = self._propmap_name(must, candidate)

                # no reuse, generate new map
                if prop_must == candidate:
                    self._propmap_gen(jm, must, prop_must, mpath)

                mu_prop_code = (
                    gen.inc_var(must_c) +
                    gen.if_stmt(gen.not_op(gen.check_call(pfun, pval, lpath_ref, is_ptr=True)),
                        self._gen_fail(f"invalid mandatory prop value [{smpath}]", lpath_ref),
                        likely=False) +
                    gen.cont()
                )

                # use map
                if gen.assign_expr():
                    mu_expr = gen.assign_prop_fun(pfun, prop, prop_must)
                    mu_code = (
                        gen.lcom(f"handle {len(must)} mandatory props") +
                        gen.if_stmt(gen.is_def(pfun), mu_prop_code, likely=likely)
                    )
                else:
                    mu_expr = gen.has_prop_fun(prop, prop_must)
                    mu_code = (
                        gen.lcom(f"handle {len(must)} mandatory props") +
                        gen.fun_var(pfun, gen.get_prop_fun(prop, prop_must)) +
                        mu_prop_code
                    )

                body_code += gen.mif_stmt([(mu_expr, likely, mu_code)])

        if may:

            if len(may) <= self._map_threshold:  # simple few-property code

                props = set(may.keys())
                if self._partition_threshold:
                    partitioning = partition(props, self._partition_threshold, gen._byte_order)
                else:
                    partitioning = None

                if partitioning is not None:
                    hash_size, partitions = partitioning
                    partitioned = True
                    # partition -> multi_if stuff
                    part_mif = { part: [] for part in partitions.keys() }
                    # property -> partition
                    prop_part = {}
                    for part, props in partitions.items():
                        for p in props:
                            prop_part[p] = part
                else:
                    # no partition
                    hash_size, partitions = 0, None
                    partitioned = False
                    partitions = { 255: props }
                    part_mif = { 255: [] }
                    prop_part = { p: 255 for p in props }

                log.debug(f"partitions = {partitions}")

                for part, props in partitions.items():

                    # subset of properties for this partition
                    may_pm = [ (p, m) for p, m in may.items() if prop_part[p] == part ]
                    if self._sort_may:
                        may_pm = sorted(may_pm, key=lambda pm: (len(pm[0]), pm[0]))

                    for p, m in may_pm:

                        likely = is_likely(MAY_P, 0.5 * expected_nprops)
                        expected_nprops -= MAY_P

                        if partitioned:
                            likely = None

                        ma_expr = gen.str_cmp(prop, "=", gen.esc(p))
                        ma_code = (
                            gen.lcom(f"handle may {p} property") +
                            self._compileModel(jm, m, mpath + [p], res, pval, lpath_ref) +
                            gen.if_stmt(gen.not_op(res),
                                self._gen_fail(
                                    f"invalid optional prop value [{json_path(mpath + [p])}]",
                                    lpath_ref),
                                likely=False)
                        )

                        # shortcut on expecting only one may prop and no other checks needed
                        if len(must) == 0 and len(may) == 1 and len(regs) == 0 and len(defs) == 0:
                            if oth == {"": "$ANY"}:
                                ma_code += gen.ret(gen.const(True))
                            else:
                                ma_code += gen.cont()
                        else:
                            ma_code += gen.cont()

                        part_mif[part] += [(ma_expr, likely, ma_code)]

                if partitioned:
                    part_code = { p: gen.mif_stmt(mi) for p, mi in part_mif.items() }
                    declare = hash_var is None
                    if declare:
                        hash_var = gen.ident("hash")
                    body_code += (
                        gen.hash_var(hash_var, gen.str_hash(prop, hash_size), declare=declare) +
                        self._gen_parts(hash_var, part_code)
                    )
                else:
                    # accumulate in global multi_if
                    # multi_if += part_mif[255]
                    body_code += gen.mif_stmt(part_mif[255])

            else:  # generic code

                likely = is_likely(MAY_P * len(may), 0.5 * expected_nprops)
                expected_nprops -= MAY_P * len(may)

                candidate = f"{oname}_map"
                prop_may = self._propmap_name(may, candidate)

                if prop_may == candidate:
                    self._propmap_gen(jm, may, prop_may, mpath)

                if gen.assign_expr():
                    ma_expr = gen.assign_prop_fun(pfun, prop, prop_may)
                    ma_code = (
                        gen.lcom(f"handle {len(may)} may props") +
                        gen.if_stmt(
                            gen.and_op(gen.is_def(pfun),
                                gen.not_op(gen.check_call(pfun, pval, lpath_ref, is_ptr=True))),
                            self._gen_fail(f"invalid optional prop value [{smpath}]", lpath_ref),
                            likely=False) +
                        gen.cont()
                    )
                else:
                    ma_expr = gen.has_prop_fun(prop, prop_may)
                    ma_code = (
                        gen.lcom(f"handle {len(may)} may props") +
                        gen.fun_var(pfun, gen.get_prop_fun(prop, prop_may)) +
                        gen.if_stmt(
                            gen.not_op(gen.check_call(pfun, pval, lpath_ref, is_ptr=True)),
                            self._gen_fail(f"invalid optional prop value [{smpath}]", lpath_ref),
                            likely=False) +
                        gen.cont()
                    )

                # multi_if += [(ma_expr, likely, ma_code)]
                body_code += gen.mif_stmt([(ma_expr, likely, ma_code)])

        # $* is inlined expr (FIXME inlining does not work with vpath)
        for d, m in defs.items():

            likely = is_likely(DEF_E, 0.5 * expected_nprops)
            expected_nprops -= DEF_E

            ref = "$" + d
            dl_expr = self._dollarExpr(jm, ref, prop, lpath_ref, is_raw=True)  # FIXME lpath &lpath?
            dl_code = gen.lcom(f"handle {len(defs)} key props") + \
                self._compileModel(jm, m, mpath + [ref], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(dl_expr, likely, dl_code)]

        # // is inlined
        for r, v in regs.items():

            likely = is_likely(REG_E, 0.5 * expected_nprops)
            expected_nprops -= REG_E

            # FIXME options?!
            regex = f"/{r}/"
            rg_expr = self._regExpr(jm, regex, prop, vpath, True)  # FIXME lpath &lpath?
            rg_code = gen.lcom(f"handle {len(regs)} re props") + \
                self._compileModel(jm, v, mpath + [regex], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(rg_expr, likely, rg_code)]

        # catchall is inlined?
        ot_code: Block
        if oth:
            omodel = oth[""]
            smpath = json_path(mpath + [""])
            if omodel != "$ANY":
                ot_code = gen.lcom("handle other props") + \
                    self._compileModel(jm, omodel, mpath + [""], res, pval, lpath_ref) + \
                    self._gen_short_expr(res)
            else:  # optimized "": "$ANY" case
                ot_code = gen.lcom("accept any other props") + gen.nope()
        else:  # no catch all
            smpath = json_path(mpath)
            ot_code = self._gen_fail(f"unexpected prop [{smpath}]", lpath_ref)

        code += gen.obj_loop(val, prop, pval,
            gen.path_var(lpath, gen.path_val(vpath, prop, True, True), True) +
            body_code +
            gen.mif_stmt(multi_if, ot_code))

        # check that all must were seen, with some effort to report the missing ones
        if must:
            missing = []
            for prop in sorted(must.keys()):
                missing += \
                    gen.if_stmt(gen.not_op(gen.has_prop(val, prop)),
                                gen.report(f"missing mandatory prop <{prop}> [{smpath}]", vpath),
                                likely=None
                    )
            code += \
                gen.if_stmt(gen.num_cmp(must_c, "!=", gen.const(len(must))),
                            self._gen_reporting(missing) +
                            gen.ret(gen.false()),
                            likely=False
                )

        # early returns so no need to look at res
        code += gen.ret(gen.true())

        return code

    def _compileOr(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                   res: str, val: str, vpath: str, known: set[BoolExpr]|None = None) -> Block:
        """Compile a general or-list of models."""

        code = []
        gen = self._lang
        smpath = json_path(mpath)

        # direct empty list
        if not models:
            # NOTE in practice this case is optimized out so should not come here
            if self._report:
                code += [ gen.report(f"empty or [{smpath}]", vpath) ]
            code += gen.bool_var(res, gen.false())
            return code
        elif len(models) == 1:
            # NOTE idem, should not come here
            return self._compileModel(jm, models[0], mpath + [0], res, val, vpath, known)

        # partial/full list of constants optimization
        # TODO constant_values
        l_const = list(map(lambda m: constant_value(m, mpath), models))
        need_if = False

        if len(list(filter(lambda t: t[0], l_const))) >= 2:

            # NOTE we use lists to avoid to squash 1, 1.0 and True…
            constants, n_models = [], []
            for i in range(len(models)):
                # NOTE python equality is a pain, True == 1 == 1.0, False == 0 == 0.0
                # NOTE python typing is a pain, isinstance(True, int) == True
                # thus we only keep strings…
                # TODO also consider int? at least if loose_int/float is false?
                if l_const[i][0] and isinstance(l_const[i][1], self._lang.set_caps):
                    cst = l_const[i][1]
                    constants.append(cst)
                else:
                    n_models.append(models[i])

            if constants:
                sname = gen.ident(self._prefix + "cst")
                self._code.cset(sname, constants)
                code += gen.bool_var(res,
                                     gen.and_op(gen.is_scalar(val),
                                                gen.in_cset(sname, val, constants)))
                code += self._gen_report(res, f"value not in enum [{smpath}]", vpath)
                if not n_models:
                    return code
                models = n_models
                if not models:
                    # all constants were tested, we are done
                    return code
                need_if = True

        # discriminant optimization for list of objects, None if fails
        tmp: ModelType = {"|": models}
        if dcode := self._disjunction(jm, tmp, mpath, res, val, vpath, known):
            if need_if:
                return code + gen.if_stmt(gen.not_op(res), dcode)
            else:
                return code + dcode

        # homogeneous typed list shortcut
        same, expected = all_model_type(models, mpath)
        or_known: set[BoolExpr] = set()
        or_code = []
        if same:
            # all models have the same ultimate type, type check shortcut
            type_test = gen.is_a(val, expected)
            or_known.add(type_test)
            or_code += gen.bool_var(res, type_test)
            or_code += self._gen_report(res, f"unexpected type [{smpath}]", vpath)

        # TODO reorder models? by type?
        # CSE should remove some repetitions, but not all?

        # mandatory property discrimination, which may be full or partial
        # TODO same is too restrictive
        mandatory_props: list[tuple[str, bool]|None] = (
            distinct_prop_objects(jm, models)
                if same and expected is dict and self._or_must_prop and len(models) >= self._or_must_prop else
            [ None ] * len(models)
        )

        # TODO on partial, merge common property tests if any?
        if False:  # self._reorder_models:
            commons: dict[str, list[int]]  = {}
            for i, prop, full in enumerate(mandatory_props):
                if not full:
                    if prop in commons:
                        commons[prop].append(i)
                    else:
                        commons[prop] = [i]
            # TODO

        # build code sequence in reverse order
        icode = []
        for i, m in reversed(list(enumerate(models))):
            # add a test if needed before the next check
            if icode and not (mandatory_props[i] and mandatory_props[i][1]):
                icode = gen.if_stmt(gen.not_op(res), icode)
            # current model code
            m_code = self._compileModel(jm, m, mpath + [i], res, val, vpath, or_known)
            # use the mandatory property test to reduce object checks
            if mandatory_props[i]:
                pname, full = mandatory_props[i]
                cond = gen.has_prop(val, pname)
                if full:
                    # full discriminant, only one test is required
                    icode = gen.if_stmt(cond, m_code, icode if icode else gen.bool_var(res, gen.false()), likely=len(icode)==0)
                else:
                    # partial, we still have to test others
                    m_code = gen.if_stmt(cond, m_code, gen.bool_var(res, gen.false()))
                    icode = m_code + icode
            else:
                # like partial, but without test
                icode = m_code + icode

        icode += self._gen_report(res, f"no model matched [{smpath}]", vpath, True)

        if or_code:
            or_code += gen.if_stmt(res, icode)
        else:
            or_code += icode

        if need_if:
            code += gen.if_stmt(gen.not_op(res), or_code)
        else:
            code += or_code

        return code

    def _compileXor(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                    res: str, val: str, vpath: str, known: set[BoolExpr]|None = None) -> Block:
        """Compile a xor-list of models."""

        assert isinstance(models, list)  # pyright hint
        gen = self._lang
        smpath = json_path(mpath)
        code = []

        # NOTE optimized out under -O
        if len(models) == 0:
            code += (
                gen.lcom("early empty xor list") +
                gen.bool_var(res, gen.false())
            )
            return code

        # NOTE optimized out under -O
        if len(models) == 1:
            return gen.lcom("early singleton xor list") + \
                self._compileModel(jm, models[0], mpath + [0], res, val, vpath, known)

        # optimize out repeated models
        if len(models) >= 2:
            seen, dups, kept = [], [], []
            seen_i, dups_i, kept_i = [], [], []
            for i, m in enumerate(models):
                if model_in_models(m, seen):
                    if not model_in_models(m, dups):
                        dups.append(m)
                        dups_i.append(i)
                else:
                    seen.append(m)
                    seen_i.append(i)
            for i, m in zip(seen_i, seen):
                if not model_in_models(m, dups):
                    kept.append(m)
                    kept_i.append(i)

            # direct false if in dups
            if dups:
                isin = gen.ident("is")
                code += (
                    gen.lcom("remove duplicate xor list") +
                    gen.bool_var(isin, declare=True) +
                    gen.bool_var(res, gen.true())
                )

                # generate flat if, no big deal?
                for i, m in enumerate(dups):
                    idx = dups_i[i]
                    icode = self._compileModel(jm, m, mpath + [idx], isin, val, vpath) + \
                        gen.bool_var(res, gen.not_op(isin))
                    if i == 0:
                        code += icode
                    else:
                        code += gen.if_stmt(res, icode)

            # update remaining models and their index
            models = kept
            models_i = kept_i
        else:
            dups = None
            models_i = list(range(len(models)))

        # standard case
        # TODO reporting
        xcode = []
        if not models:
            xcode += gen.lcom("empty xor list") + gen.bool_var(res, gen.false())
        elif len(models) == 1:
            mod, idx = models[0], models_i[0]
            xcode += gen.lcom("singleton xor list") + \
                self._compileModel(jm, mod, mpath + [idx], res, val, vpath)
        else:  # several models are inlined
            if len(models) == 2 and "$ANY" in models:
                xcode += gen.lcom("not-case xor list")
                # get other model
                if models[0] == "$ANY":
                    m = models[1]
                    idx = models_i[1]
                else:
                    m = models[0]
                    idx = models_i[0]
                is_m = self._lang.ident("is")
                xcode += (
                    gen.bool_var(is_m, declare=True) +
                    self._compileModel(jm, m, mpath + [idx], is_m, val, vpath) +
                    gen.bool_var(res, gen.not_op(is_m))
                )
            else:
                # TODO collect which model matched for reporting?
                count = self._lang.ident("xc")
                test = self._lang.ident("xr")
                xcode += (
                    gen.lcom("generic xor list") +
                    gen.int_var(count, gen.const(0), declare=True) +
                    gen.bool_var(test, declare=True)
                )

                # flat if…
                for i, m in enumerate(models):
                    idx = models_i[i]
                    icode = self._compileModel(jm, m, mpath + [idx], test, val, vpath) + \
                        gen.if_stmt(test, gen.inc_var(count))
                    if i < 2:
                        xcode += icode
                    else:  # maybe skip
                        xcode += gen.if_stmt(gen.num_cmp(count, "<=", gen.const(1)), icode)

                # verify that only one matched
                xcode += gen.bool_var(res, gen.num_cmp(count, "=", gen.const(1)))

        if dups:
            code += gen.if_stmt(res, xcode)
        else:
            code += xcode

        code += self._gen_report(res, f"not one model match [{smpath}]", vpath, True)

        return code

    def _compileAnd(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                    res: Var, val: JsonExpr, vpath: PathExpr,
                    known: set[BoolExpr]|None = None) -> Block:
        """Compile an and-list of models."""

        assert isinstance(models, list)  # pyright hint

        gen = self._lang
        and_known: set[BoolExpr] = set(known or [])
        smpath = json_path(mpath)
        code = []

        if not models:  # empty & list
            return gen.bool_var(res, gen.true())

        # homogeneous typed list
        same, expected = all_model_type(models, mpath)
        if same:
            # all models have the same ultimate type, use a type shortcut
            type_test = gen.is_a(val, expected)
            code += gen.bool_var(res, type_test)
            and_known.add(type_test)
        else:
            code += gen.bool_var(res, gen.true())

        # build in reverse order the if structure
        acode: Block = []
        for i, m in reversed(list(enumerate(models))):
            acode = gen.if_stmt(res,
                self._compileModel(jm, m, mpath + [i], res, val, vpath, and_known) +
                acode
            )
        code += acode

        code += self._gen_report(res, f"not all model match [{smpath}]", vpath, True)

        return code

    def _compileModel(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                      res: str, val: str, vpath: str, known: set[BoolExpr]|None = None,
                      constrained: bool = False, name: str|None = None) -> Block:
        # TODO break each level into a separate function and let the compiler inline
        # known = expression already verified
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath}")
        assert isinstance(mpath, list)
        smpath = json_path(mpath)
        gen = self._lang
        known = known or set()

        code = gen.lcom(f"{json_path(mpath)}")
        match model:
            case None:
                code += gen.bool_var(res, gen.is_a(val, None)) + \
                    self._gen_report(res, f"not null [{smpath}]", vpath)

            case bool():
                code += gen.bool_var(res, gen.is_a(val, bool)) + \
                    self._gen_report(res, f"not a bool [{smpath}]", vpath)

            case int():
                expr: BoolExpr|None = gen.is_a(val, int, jm._loose_int)
                if known is not None:
                    if expr in known:
                        expr = None
                if model == -1:
                    if known is not None:
                        if expr is not None:
                            known.add(expr)
                    if not expr:
                        expr = gen.true()
                elif model == 0:
                    compare = gen.num_cmp(
                        gen.value(val, Number if jm._loose_int else int),  # type: ignore
                                  ">=", gen.const(0))
                    expr = gen.and_op(expr, compare) if expr else compare
                elif model == 1:
                    compare = gen.num_cmp(
                        gen.value(val, Number if jm._loose_int else int),  # type: ignore
                                  ">=", gen.const(1))
                    expr = gen.and_op(expr, compare) if expr else compare
                else:
                    raise ModelError(f"unexpected int value {model} at {smpath}")
                if expr:
                    looseness = "loose" if jm._loose_int else "strict"
                    code += gen.bool_var(res, expr) + \
                        self._gen_report(res,
                            f"not a {model} {looseness} int [{smpath}]", vpath)

            case float():
                expr: BoolExpr|None = gen.is_a(val, float, jm._loose_float)
                if known is not None:
                    if expr in known:
                        expr = None
                if model == -1.0:
                    if known is not None:
                        if expr is not None:
                            known.add(expr)
                    if not expr:
                        expr = gen.true()
                elif model == 0.0:
                    compare = gen.num_cmp(
                        gen.value(val, Number if jm._loose_float else float),  # type: ignore
                                  ">=", gen.const(0.0))
                    expr = gen.and_op(expr, compare) if expr else compare
                elif model == 1.0:
                    compare = gen.num_cmp(
                        gen.value(val, Number if jm._loose_float else float),  # type: ignore
                                  ">", gen.const(0.0))
                    expr = gen.and_op(expr, compare) if expr else compare
                else:
                    raise ModelError(f"unexpected float value {model} at {mpath}")
                if expr:
                    looseness = "loose" if jm._loose_float else "strict"
                    code += gen.bool_var(res, expr) + \
                        self._gen_report(res, f"not a {model} {looseness} float [{smpath}]", vpath)

            case str():
                expr: BoolExpr|None = gen.is_a(val, str)
                if known is not None:
                    # Skip special cases
                    if model == "" or model[0] not in ["$", "="]:
                        # log.info(f"expr={expr} known={known}")
                        if expr in known:
                            expr = None
                if model == "":
                    if known is not None:
                        if expr is not None:
                            known.add(expr)
                    code += gen.bool_var(res, expr if expr else gen.true())
                elif model[0] == "_":
                    compare = gen.str_cmp(gen.value(val, str), "=",  # type: ignore
                                          gen.const(model[1:]))  # type: ignore
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += gen.bool_var(res, expr)
                elif model[0] == "=":
                    # TODO FIXME known
                    # NOTE expr is ignore here
                    (a_cst, value) = constant_value(model, mpath)
                    if not a_cst:
                        raise ModelError(f"unexpected constant: {model}")
                    if value is None:
                        code += gen.bool_var(res, gen.is_a(val, None))
                    elif isinstance(value, bool):
                        ttest = gen.is_a(val, bool)
                        expr = gen.num_cmp(gen.value(val, bool), "=", gen.const(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += gen.bool_var(res, expr)
                    elif isinstance(value, int):
                        ttest = gen.is_a(val, int, jm._loose_int)
                        # FIXME cast depends on type?
                        expr = gen.num_cmp(gen.value(val, int), "=", gen.const(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += gen.bool_var(res, expr)
                    elif isinstance(value, float):
                        ttest = gen.is_a(val, float, jm._loose_float)
                        expr = gen.num_cmp(
                            gen.value(val, Number if jm._loose_float else float),  # type: ignore
                                      "=", gen.const(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += gen.bool_var(res, expr)
                    # elif isinstance(value, str):
                    #     compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    #     expr = gen.and_op(expr, compare) if expr else compare
                    #     code += gen.bool_var(res, expr)
                    else:
                        raise ModelError(f"unexpected constant type: {tname(value)}")
                elif model[0] == "$":
                    call = self._dollarExpr(jm, model, val, vpath)
                    code += gen.bool_var(res, call)
                elif model[0] == "/":
                    code += gen.lcom(f"{self._esc(model)}")
                    call = self._regExpr(jm, model, val, vpath)
                    code += gen.bool_var(res, gen.and_op(expr, call) if expr else call)
                else:  # simple string
                    compare = gen.str_cmp(gen.value(val, str), "=",  # type: ignore
                                          gen.const(model))  # type: ignore
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += gen.bool_var(res, expr)
                if self._report:
                    smodel = model if model else "string"
                    code += self._gen_report(res, f"unexpected {smodel} [{smpath}]", vpath)

            case list():
                expr: BoolExpr|None = gen.is_a(val, list)
                smpath = json_path(mpath)

                if known is not None:
                    if expr in known:
                        expr = None
                    if expr is not None:
                        known.add(expr)

                if len(model) == 0:  # []
                    length = gen.num_cmp(gen.arr_len(val), "=", gen.const(0))
                    expr = gen.and_op(expr, length) if expr else length
                    code += gen.bool_var(res, expr)
                    # SHORT RES?

                elif len(model) == 1:  # homogeneous vector

                    if model[0] == "$ANY":
                        loop = gen.lcom("accept any array") + gen.nope()
                    else:
                        arrayid = gen.ident("arr")
                        idx, item, lpath = f"{arrayid}_idx", f"{arrayid}_item", f"{arrayid}_lpath"

                        loop = gen.arr_loop(val, idx, item,
                                gen.path_var(lpath, gen.path_val(vpath, idx, False, True), True) +
                                self._compileModel(jm, model[0], mpath + [0],
                                                   res, item,
                                                   gen.path_lvar(lpath, vpath)) +  # type: ignore
                                gen.if_stmt(gen.not_op(res), gen.brk(), likely=False))

                    code += (
                        gen.bool_var(res, expr if expr else gen.true()) +
                        gen.if_stmt(res, loop, likely=True) if expr else loop
                    )

                else:
                    # non empty list of models, aka tuple
                    lpath = gen.ident("lpath")
                    lpath_ref: PathExpr = gen.path_lvar(lpath, vpath)  # type: ignore
                    if not constrained:
                        length = gen.num_cmp(gen.arr_len(val), "=", gen.const(len(model)))
                        expr = gen.and_op(expr, length) if expr else length
                        code += gen.bool_var(res, expr)
                        # else inside a @ with constraints, so we do not check the len
                        # body = gen.path_var(lpath, declare=True)
                        body = []
                        for i, m in reversed(list(enumerate(model))):
                            body = gen.if_stmt(
                                res,
                                gen.path_var(lpath, gen.path_val(vpath, i, False, False), declare=i==0) +
                                # FIXME generated variable reference…
                                self._compileModel(
                                    jm, model[i], mpath + [i],
                                    res, gen.arr_item_val(val, i), lpath_ref) +
                                body,
                                likely=True)
                        code += body
                    else:
                        # assume varlen tuple: [ A, B, C* ]
                        arlen = gen.ident("len")
                        code += gen.path_var(lpath, None, declare=True)
                        body = []

                        # last model for repeats
                        lmodel, start = model[-1], len(model)-1

                        if lmodel != "$ANY":
                            idx = gen.ident("idx")
                            body += gen.int_loop(idx, start, arlen,
                                gen.path_var(lpath, gen.path_val(vpath, idx, False, True)) +
                                self._compileModel(jm, lmodel, mpath + [start], res,
                                                   gen.arr_item_val(val, idx), lpath_ref) +
                                gen.if_stmt(gen.not_op(res), gen.brk(), likely=False)
                            )

                        for i, m in reversed(list(enumerate(model[:-1]))):
                            ith_check = \
                                gen.if_stmt(gen.num_cmp(arlen, ">", i),
                                    gen.path_var(lpath, gen.path_val(vpath, i, False, False)) +
                                    self._compileModel(jm, m, mpath + [i], res,
                                                       gen.arr_item_val(val, i), lpath_ref))
                            if body:
                                body = ith_check + gen.if_stmt(res, body, likely=True)
                            else:
                                body = ith_check

                        # compute len before checking array items
                        body = gen.int_var(arlen, gen.arr_len(val), declare=True) + body

                        if lmodel == "$ANY":
                            body += gen.lcom("no array tail value checks needed")

                        code += (
                            gen.bool_var(res, expr if expr else gen.true()) +
                            gen.if_stmt(res, body, likely=True) if expr else body
                        )

                code += self._gen_report(res, f"not array or unexpected array [{smpath}]", vpath)

            case dict():
                assert isinstance(model, dict)  # pyright hint
                assert "+" not in model, "merge must have been preprocessed"
                if "@" in model:  # TODO known?
                    code += self._compileConstraint(jm, model, mpath, res, val, vpath)
                elif "|" in model:
                    models = model["|"]
                    assert isinstance(models, list)  # pyright hint
                    code += self._compileOr(jm, models, mpath + ["|"], res, val, vpath, known)
                elif "&" in model:
                    models = model["&"]
                    assert isinstance(models, list)  # pyright hint
                    code += self._compileAnd(jm, models, mpath + ["&"], res, val, vpath, known)
                elif "^" in model:
                    models = model["^"]
                    assert isinstance(models, list)  # pyright hint
                    code += self._compileXor(jm, models, mpath + ["^"], res, val, vpath, known)
                else:
                    if name:
                        objid = name
                        code += self._compileObject(jm, model, mpath, name, res, val, vpath)
                    else:
                        # new function to check the object
                        objid = gen.ident(self._prefix + "obj")
                        self._code.sub(
                            objid,
                            self._compileObject(jm, model, mpath, objid, "res", "val", "path"),
                            comment=f"object {json_path(mpath)}",
                            inline=True
                        )

                        # call object check and possibly report
                        code += gen.bool_var(res, gen.check_call(objid, val, vpath))
                        code += self._gen_report(res, f"unexpected element [{smpath}]", vpath)

                    # record object function for path
                    self._paths[tuple(mpath)] = objid

                if "#" in model:
                    code = gen.lcom(model["#"]) + code  # type: ignore

            case _:
                raise ModelError(f"unexpected model type: {tname(model)}")

        return code

    def _getName(self, jm: JsonModel, name: str) -> str:
        """Ensure global unique names for internal functions."""
        # FIXME global name space! prefix with jm._id ?
        if name not in self._names:
            self._names[name] = self._lang.ident(self._prefix + "f")
        log.debug(f"{name} -> {self._names[name]}")
        return self._names[name]

    def _getNameRef(self, jm: JsonModel, ref: str, path: ModelPath) -> str:
        assert jm._isRef(ref), f"must be a reference: {ref}"

        # FIXME shortcut hack
        if ref == "$#" and ref in self._names:
            return self._names[ref]

        try:
            gref = jm._defs.gget(ref)
        except KeyError:
            if self._debug:
                log.debug(f"_getNameRef[{jm._id},{jm._defs._id}]({ref}) at {path}")
                log.debug(f" with gmap={jm._defs._gmap}")
            # FIXME maybe we already have a global reference?
            gref = ref

        log.debug(f"name ref: gref={gref} globs={self._globs} names={self._names}")
        if gref not in self._names:
            jm = self._globs[gref]  # type: ignore
            if jm._id not in self._compiled:
                self._to_compile[jm._id] = (jm, gref)
            self._names[gref] = f"json_model_{jm._id}"

        # log.debug(f"name ref: ref={ref} gref={gref} at {path}: {self._names[gref]}")
        return self._names[gref]

    def _compileName(self, jm: JsonModel,
                     name: str, model: ModelType, mpath: ModelPath, local: bool = False):
        """Compile a model under a given name in a given scope."""
        log.debug(f"compile name={name} jm={jm._id} mpath={mpath} names={self._names}")

        # TODO simplify, clarify, remove
        # memoize the associated function name that can be retrieved if there is a recursion
        fun2 = None
        hpath = tuple(mpath)
        if hpath in self._paths:
            fun = self._paths[hpath]
            if name in self._names:
                fun2 = self._names[name]
            else:
                self._names[name] = fun
        else:
            fun = self._getName(jm, name)
            self._paths[hpath] = fun

        # on a simple object, do not generate a useless intermediate function by imposing the name
        if is_a_simple_object(model):
            body = self._compileModel(jm, model, mpath, "res", "val", "path", set(), name=fun)
        else:
            body = self._lang.bool_var("res", declare=True) + \
                self._compileModel(jm, model, mpath, "res", "val", "path", set(), name=fun) + \
                self._lang.ret("res")

        self._code.sub(fun, body, comment=f"check {name} ({json_path(mpath)})")

        if fun2 and fun2 != fun:
            raise NotImplementedError("2 functions for one?!")
            # code.add(0, "# named root")
            # code.add(0, f"{fun2} = {fun}")

        # FIXME!
        # NOTE yuk! the function may have been generated as a side effect of the previous call.
        # if so, this version is simply discarded
        if hpath not in self._generated:
            # on a named root, two names for the same path
            self._generated.add(hpath)
        else:
            log.warning("should not get there?!")

    def computeShortcuts(self, head: JsonModel) -> dict[str, str]:
        """Function shortcuts to skip calls in the global namespace."""
        assert head._is_head, "compute shortcuts on head model"

        shortcuts: dict[str, str] = {}

        for ref, jm0 in head._globs.items():
            mid, fun0, fun, jm = jm0._id, f"json_model_{jm0._id}", None, jm0

            if ref == "$#" or fun0 in shortcuts:
                continue

            tref = (ref,) if ref != "$" else tuple()
            fun = self._paths[tref] if tref in self._paths else fun0

            while jm._isRef(jm._model):
                jm = jm.resolveRef(jm._model, [])
                if jm._id == jm0._id:  # oops direct reference
                    raise Exception("infinite reference loop")
                fun = f"json_model_{jm._id}" if jm else fun0

            if fun in shortcuts:
                fun = shortcuts[fun]

            if fun != fun0:
                shortcuts[fun0] = fun

        # transitive closure, because of above shortcuts
        changed: False = True
        while changed:
            changed = False
            for k, v in shortcuts.items():
                if v in shortcuts:
                    shortcuts[k] = shortcuts[v]
                    changed = True

        # log.debug(f"shortcuts: {shortcuts}")
        return shortcuts

    def compileOneJsonModel(self, jm: JsonModel, name: str, path: ModelPath, local: bool = False):
        if jm._id not in self._compiled:
            self._compiled.add(jm._id)
            if name not in self._names:
                self._names[name] = "json_model_" + str(jm._id)
            self._compileName(jm, name, jm._model, path, local)

    def compileJsonModelHead(self, model: JsonModel):
        # $# special handing
        head_model_fun = f"json_model_{model._head._id}"
        self._names["$#"] = head_model_fun
        self._names[""] = head_model_fun

        entries: PropMap = {
            "": head_model_fun,
        }

        # compile direct definitions
        for n, jm in model._defs.items():
            dn = f"${n}"
            # special handling of the resolution gives another model
            # eg "foo": "$bla"
            if dn in self._globs and self._globs[dn]._id != jm._id:  # type: ignore
                # skip compilation and point to other function
                entries[n] = f"json_model_{self._globs[dn]._id}"  # type: ignore
            else:
                # actual compilation of a new function
                entries[n] = f"json_model_{jm._id}"
                self.compileOneJsonModel(jm, dn, ["$" + n], False)
            log.debug(f"after {n} ({jm._id}): {self._names}")

        # compile root
        self.compileOneJsonModel(model, "$", [], False)

        # TODO possibly add entries for referenced models? under an option?

        # compile other encountered references
        while todo := set(self._to_compile.keys()) - self._compiled:
            jm, gref = self._to_compile[min(todo)]
            self.compileOneJsonModel(jm, gref, [gref], True)

        # for skip call optimization
        self._code._shortcuts = self.computeShortcuts(model)

        # use shortcuts directly on entries
        for name, fun in entries.items():
            if fun in self._code._shortcuts:
                entries[name] = self._code._shortcuts[fun]

        # generate mapping, beware of name consistency
        self._code.pmap(f"{self._code._entry}_map", entries, True)

        return self._code


def xstatic_compile(
        model: JsonModel,
        fname: str = "check_model",
        *,
        lang: str = "py",
        prefix: str = "_jm_",
        relib: str|None = None,
        map_threshold: int|None = None,
        map_share: bool = False,
        may_must_open_threshold: int|None = None,
        must_only_threshold: int|None = None,
        sort_must: bool = True,
        sort_may: bool = True,
        partition_threshold: int|None = None,
        or_must_prop: int|None = None,
        strcmp_cset_partition_threshold: int = 32,  # or 64
        execute: bool = True,
        debug: bool = False,
        report: bool = True,
        short_version: bool = False,
        package: str|None = None,
        inline: bool = True,
        predef: bool = True,
        ir_optimize: bool = True,
        strcmp: bool = True,
        max_strcmp_cset: int = 64,
        byte_order: str = "le",
    ) -> Code:
    """Generate the check source code for a model.

    - model: JSON Model root to compile.
    - fname: target function name.
    - lang: name of target language.
    - prefix: prefix for generated functions.
    - map_threshold: inline property checks under this threshold.
    - map_share: share generated property maps.
    - may_must_open_threshold: mmop scheme if below threshold opt props
    - must_only_threshold: must-only scheme if below threshold mandatory props
    - sort_must: whether to sort must properties
    - sort_may: whether to sort may properties
    - partition_threshold: property test partition if over this threshold, 0 for no partitioning
    - or_must_prop: length threshold for or-list shortcut based on mandatory properties
    - strcmp_cset_partition_threshold: string set partitioning target chunk size, 0 for no partitioning
    - report: whether to generate code to report rejection reasons.
    - debug: debugging mode generates more traces.
    - short_version: in generated code.
    - package: namespace to use (Perl module, Pg schema name, Java package).
    - inline: enable function inlining (for C).
    - predef: enable string content predef checks.
    - ir_optimize: enable IR optimizations.
    - strcmp: whether to optimize some string comparisons
    - max_strcmp_cset: max size for direct str constant set
    - byte_order: le, be or dpd
    """
    # set default threshold for must-only scheme
    MUST_ONLY_THRESHOLD: dict[str, int] = {
        "c": 0,        # never good enough vs unroll
        "js": 256,     # no cutoff?
        "py": 256,     # no cutoff?
        "pl": 128,     # ?
        "java": 256,   # GSON
        "sql": 0,      # FIXME not tested
        "plpgsql": 0,  # FIXME not tested
    }
    if must_only_threshold is None:
        must_only_threshold = MUST_ONLY_THRESHOLD.get(lang, 8)

    # set default threshold for may-must-open scheme
    MAY_MUST_OPEN_THRESHOLD: dict[str, int] = {
        "c": 0,        # never good enough vs unroll, but faster than map
        # FIXME this is only beneficial the number of value props is significant on mays?
        # there is no cutoff in that case, but otherwise it reduces performance
        # TODO decision process should also involve may/must ratio or take into account
        # likelyhood of may props…
        # 256, 256, 256, 128 -> 16, 16, 16, 8 for now
        "js": 16,     # no cutoff? better than unroll and map *if* significant may numbers
        "py": 16,     # much better than unroll, slightly better than map
        "pl": 16,     # idem py
        "java": 8,   # better than map < 256
        "sql": 0,      # FIXME not tested
        "plpgsql": 0,  # FIXME not tested
    }
    if may_must_open_threshold is None:
       may_must_open_threshold = MAY_MUST_OPEN_THRESHOLD.get(lang, 16)

    # set default map threshold depending on target language
    MAP_THRESHOLD: dict[str, int] = {
        "c": 256,      # NOTE the actual cutoff is _very_ far, probably over 1000/1300
        # FIXME unclear… 40 -> 20 for now
        "js": 20,
        "py": 10,
        "pl": 8,
        "java": 12,
        "sql": 8,      # FIXME not tested
        "plpgsql": 8,  # FIXME not tested
    }
    if map_threshold is None:
        map_threshold = MAP_THRESHOLD.get(lang, 12)

    # partition threshold to generate a dichotomy on unrolled tests
    PARTITION_THRESHOLD: dict[str, int] = {
        "c": 6,
        # TODO other languages once tested
    }
    if partition_threshold is None:
        partition_threshold = PARTITION_THRESHOLD.get(lang, 0)
    if partition_threshold and lang not in PARTITION_THRESHOLD:
        log.warning(f"partitioning not implemented for {lang}, ignoring")
        partition_threshold = 0

    # length threshold about whether to shortcut or-list based on mandatory properties
    OR_MUST_PROP: dict[str, bool] = {
        "c": 4,
        "js": 2,
        "py": 2,
        "java": 2,
        "pl": 3,
        # UNTESTED
        "sql": 0,
        "plpgsql": 0,
    }
    if or_must_prop is None:
        or_must_prop = OR_MUST_PROP.get(lang, 0)

    log.info(f"lang={lang} mt={map_threshold} mmo={may_must_open_threshold} "
             f"mo={must_only_threshold} pt={partition_threshold} omp={or_must_prop}")

    # target language
    if lang == "py":
        from .python import Python
        language = Python(debug=debug, with_report=report, with_path=report,
                          with_predef=predef, relib=relib or "re2")
    elif lang == "c":
        from .clang import CLangJansson
        language = CLangJansson(debug=debug, with_report=report, with_path=report,
                                with_predef=predef, relib=relib or "re2",
                                inline=inline, strcmp_opt=strcmp, byte_order=byte_order,
                                max_strcmp_cset=max_strcmp_cset,
                                partition_threshold=strcmp_cset_partition_threshold
        )
    elif lang == "js":
        from .javascript import JavaScript
        language = JavaScript(debug=debug, with_report=report, with_path=report,
                              with_predef=predef, relib=relib or "re")
    elif lang in ("plpgsql", "sql"):
        from .plpgsql import PLpgSQL
        language = PLpgSQL(debug=debug, with_report=report, with_path=report, with_predef=predef,
                           relib=relib or "re", with_package=package is not None)
        package = package or "public"
    elif lang == "pl":
        from .perl import Perl
        language = Perl(debug=debug, with_report=report, with_path=report, with_predef=predef,
                        relib=relib or "re2", with_package=package is not None)
        package = package or "Model"
    elif lang == "java":
        from .java import Java
        language = Java(debug=debug, with_report=report, with_path=report, with_predef=predef,
                        relib=relib or "re", with_package=package is not None)
    elif lang == "json":
        language = None
    else:
        raise NotImplementedError(f"no support yet for language: {lang}")

    # intermediate representation if needed
    if ir_optimize or language is None:
        target = IRep(debug=debug, lang=language)
        if language:
            language._short_version = short_version
            target.set_caps = language.set_caps
    else:  # not needed
        target = language

    # cold override
    target._short_version = short_version

    # source code generator
    gen = CodeGenerator(
        model._globs, target, fname, prefix=prefix,  # type: ignore
        map_share=map_share,
        map_threshold=map_threshold,
        may_must_open_threshold=may_must_open_threshold,
        must_only_threshold=must_only_threshold,
        partition_threshold=partition_threshold,
        or_must_prop=or_must_prop,
        sort_must=sort_must, sort_may=sort_may,
        execute=execute, debug=debug, report=report, package=package
    )

    # generate IR or final code
    code: Code = gen.compileJsonModelHead(model)

    # optimize IR
    if ir_optimize:
        optimizeIR(code._subs, if_optim=True, shortcuts=code._shortcuts, reporting=report)
        optimizeIR(code._defs, if_optim=False, shortcuts=code._shortcuts, reporting=report)
        optimizeIR(code._inis, if_optim=False, shortcuts=code._shortcuts, reporting=report)
        optimizeIR(code._dels, if_optim=False, shortcuts=code._shortcuts, reporting=report)
        if language:
            code = evaluate(code, language)

    return code
