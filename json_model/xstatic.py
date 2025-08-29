# experimental static (ecstatic?) compiler

import re
import json

from .mtypes import ModelType, ModelArray, ModelObject, ModelError, ModelPath, Symbols
from .mtypes import Jsonable, Number, JsonScalar
from .utils import split_object, model_in_models, all_model_type, constant_value
from .utils import log, tname, MODEL_PREDEFS
from .runtime.support import _path as json_path
from .analyze import ultimate_type, disjunct_analyse
from .model import JsonModel
from .language import Language, Code, Block, BoolExpr, PathExpr, PropMap, JsonExpr, StrExpr, Var


class CodeGenerator:
    """JSON Models Compilation.

    - globs: global map of symbols.
    - language: target language abstraction.
    - execute: true for executable, false for module.
    - fname: entry function name.
    - prefix: use this prefix for file-level identifiers.
    - map_threshold: whether to inline property name checks (up to threshold) or use a map.
    - report: whether to report rejection reasons.
    - path: whether to keep track of value path while checking.
    - debug: verbose debug mode.
    """

    def __init__(self, globs: Symbols, language: Language, fname: str = "check_model", *,
                 prefix: str = "", map_threshold: int = 3, map_share: bool = False,
                 execute: bool = True, report: bool = True, path: bool = True,
                 package: str|None = None, debug: bool = False):

        super().__init__()

        self._globs = globs
        self._lang = language
        self._prefix = prefix
        self._map_threshold = map_threshold
        self._map_share = map_share
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
        # self._code.clear()
        self._names.clear()
        self._regs.clear()
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
            # TODO inline the internal function if possible?
            return gen.str_check_call(fun, sval, path)
        # TODO f" or _rep(f\"does not match {self._fesc(regex)} at {{{path}}}\", rep)"

    def _esc(self, val: Jsonable) -> str:
        """Escape value as necessary."""
        # return '"' + string.translate({"\"": "\\\"", "\\": "\\\\"}) + '"'
        return json.dumps(val) if isinstance(val, str) else str(val)

    def _fesc(self, val: str) -> str:
        """Escape string for an f-string."""
        # FIXME return val.translate({"{": "{{", "\\": "\\\\", "\"": "\\\""})
        return "FESC"

    def _dollarExpr(self, jm: JsonModel, ref: str, val: str, vpath: str, *, is_raw: bool = False):
        """Generate a call to check for a $REF."""
        # FIXME C val is may be a char*, not a json_t*.
        assert ref and ref[0] == "$"
        if ref in MODEL_PREDEFS:  # inline predefs
            # TODO improve
            return self._lang.predef(val, ref, vpath, is_raw)
            # return (self.MODEL_PREDEFS[ref](val, vpath) +
            #         (f" or _rep(f\"invalid {ref} at {{{vpath}}}\", rep)" if self._report else ""))
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
            self._gen_report(res, f"constraints failed [{smpath}]", vpath))

        return code

    def _disjunction(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                     res: str, val: str, vpath: str) -> Block|None:
        """Generate optimized disjunction check, return None if failed."""

        assert isinstance(model, dict) and "|" in model and isinstance(model["|"], list)
        dis = disjunct_analyse(jm, model, mpath)  # type: ignore
        log.debug(f"disjunct at {mpath}: dis={dis}")
        if dis is None:
            return None

        tag_name, tag_type, models, all_const_props = dis
        smpath = json_path(mpath)
        gen = self._lang

        log.debug(f"disjunct: tag_name={tag_name} consts={all_const_props}")

        # Compile all object models in the list if needed
        assert isinstance(model, dict)

        init = model["|"]
        assert isinstance(init, list)  # pyright hint
        assert len(models) == len(init)

        code = []

        for i, m in enumerate(models):
            p = mpath + [i]
            tp = tuple(p)
            mi = init[i]  # initial model
            if isinstance(mi, str) and mi and mi[0] == "$":
                # it is a reference, it must be compiled for its name, no need to recompile it!
                fun = self._getNameRef(jm, mi, p)
                if tp not in self._paths:
                    # several path will lead to the same function
                    self._paths[tp] = fun
                # else nothing to do?
            elif tp not in self._paths:
                # else compile the direct object as a side effect…
                # BUT we need to recover the generated function name!
                self._compileModel(jm, m, p, res, val, vpath)
                # log.debug(f"{self._paths}")

        cmap = self._lang.ident(self._prefix + "map")

        # mapping from tag values to check functions
        TAG_CHECKS: dict[JsonScalar, str] = {}
        for i in range(len(models)):
            consts = all_const_props[i]
            TAG_CHECKS[consts[tag_name]] = self._paths[tuple(mpath + [i])]

        self._code.cmap(cmap, TAG_CHECKS)

        code += gen.bool_var(res, gen.is_a(val, dict))

        tag = self._lang.ident("tag")
        itag = gen.json_var(tag, gen.obj_prop_val(val, tag_name, False), declare=True)

        fun = self._lang.ident("fun")
        ifun = gen.fun_var(fun, gen.get_cmap(cmap, tag, tag_type), True)
        icall = gen.bool_var(res, gen.check_call(fun, val, vpath, is_ptr=True))

        # FIXME has_prop gets the tag value in C, so this means 2 get. alternate strategy?
        code += (
            gen.if_stmt(res,
                gen.if_stmt(gen.has_prop(val, tag_name),
                    itag +
                    ifun +
                    gen.if_stmt(gen.is_def(fun),
                        icall,
                        gen.bool_var(res, gen.false()) +
                        gen.report(f"tag <{tag_name}> value not found [{smpath}]", vpath)),
                    gen.bool_var(res, gen.false()) +
                    gen.report(f"tag prop <{tag_name}> is missing [{smpath}]", vpath)),
                gen.report(f"value is not an object [{smpath}]", vpath))
        )

        return code

    def _gen_report(self, res: str, msg: str, path: str, cleanup: bool = False) -> Block:
        """Maybe generate a report."""
        if self._report:
            gen = self._lang
            if cleanup:
                return gen.if_stmt(res, gen.clean_report(), gen.report(msg, path))
            else:
                return gen.if_stmt(gen.not_op(res), gen.report(msg, path))
        else:
            return []

    def _gen_reporting(self, report: Block) -> Block:
        """Detailed reporting."""
        gen = self._lang
        return gen.if_stmt(gen.is_reporting(), report) if self._report else []

    def _gen_fail(self, msg: str, path: PathExpr) -> Block:
        """Generate a report and return false."""
        gen = self._lang
        return gen.report(msg, path) + gen.ret(gen.false())

    def _gen_short_expr(self, expr: BoolExpr) -> Block:
        """Return immediately if expression is false."""
        gen = self._lang
        return gen.if_stmt(gen.not_op(expr), gen.ret(gen.false()))

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
            pid = f"{name}_{p}"  # unique identifier for value function
            self._compileName(jm, pid, m, mpath + [p], True)
            prop_map[p] = self._getName(jm, pid)
        self._code.pmap(name, prop_map)

    def _openMuMaObject(self, jm: JsonModel, must: dict[str, ModelType], may: dict[str, ModelType],
                        mpath: ModelPath, oname: str,
                        res: Var, val: JsonExpr, vpath: PathExpr) -> Block:
        """Optimize `{"x": ..., "": "?y": ..., "": "$ANY"}`."""

        assert isinstance(must, dict)
        gen = self._lang
        smpath = json_path(mpath)

        code = (
            gen.lcom("check must only props") +
            gen.if_stmt(gen.not_op(gen.is_a(val, dict)),
                        self._gen_fail(f"not an object [{smpath}]", vpath))
        )

        # value checks?
        if any(m != "$ANY" for m in must.values()) or any(m != "$ANY" for m in may.values()):
            code += (
                gen.json_var("pval", declare=True) +
                gen.bool_var(res, declare=True)
            )

        for prop, pmodel in must.items():
            code += gen.if_stmt(
                        gen.not_op(gen.has_prop(val, prop)),
                        self._gen_fail(f"missing mandatory prop <{prop}> [{smpath}]", vpath))
            if pmodel != "$ANY":
                code += (
                    gen.json_var("pval", gen.obj_prop_val(val, prop, False)) +
                    self._compileModel(jm, pmodel, mpath + [prop], res, "pval", vpath) +
                    gen.if_stmt(
                        gen.not_op(res),
                        self._gen_fail(f"unexpected value for mandatory prop <{prop}> [{smpath}]",
                                       vpath))
                )

        for prop, pmodel in may.items():
            if pmodel != "$ANY":
                code += gen.if_stmt(gen.has_prop(val, prop),
                    gen.json_var("pval", gen.obj_prop_val(val, prop, False)) +
                    self._compileModel(jm, pmodel, mpath + [prop], res, "pval", vpath) +
                    gen.if_stmt(
                        gen.not_op(res),
                        self._gen_fail(f"unexpected value for optional prop <{prop}> [{smpath}]",
                                       vpath))
                )
            # else covered by catchall

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
        multi_if: list[tuple[BoolExpr, Block]] = []
        prop, pval, must_c, pfun = "prop", "pval", "must_count", "pfun"

        # should be an object
        code += gen.if_stmt(gen.not_op(gen.is_a(val, dict)),
                            self._gen_fail(f"not an object [{smpath}]", vpath))

        # shorcut for empty/any object
        if not must and not may and not defs and not regs:
            if not oth:  # empty object
                code += \
                    gen.if_stmt(gen.num_cmp(gen.obj_len(val), "=", gen.const(0)),
                                gen.ret(gen.true()),
                                self._gen_fail(f"expecting empty object [{smpath}]", vpath))
                return code
            elif oth == { "": "$ANY" }:  # any object (empty must/may/defs/regs)
                code += gen.lcom("accept any object") + gen.ret(gen.true())
                return code
            # only check values, fine code will be generated below

        # shortcut for open object with simple props only
        if not defs and not regs and (must or may) and oth == {"": "$ANY"}:
            return self._openMuMaObject(jm, must, may, mpath, oname, res, val, vpath)

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

        # build multi-if structure to put in prop/val loop
        if must:

            # must prop counter to check at the end if all were seen
            code += gen.int_var(must_c, gen.const(0), True)

            if len(must) <= self._map_threshold:  # direct property checks

                for p, m in must.items():
                    mu_expr = gen.str_cmp(prop, "=", gen.esc(p))
                    mu_code = (
                        gen.lcom(f"handle must {p} property") +
                        gen.inc_var(must_c) +
                        self._compileModel(jm, m, mpath + [p], res, pval, lpath_ref) +
                        gen.if_stmt(gen.not_op(res),
                            self._gen_fail(
                                f"invalid mandatory prop value [{json_path(mpath + [p])}]",
                                lpath_ref)
                        )
                    )
                    multi_if += [(mu_expr, mu_code)]

            else:  # generic code above threshold

                candidate = f"{oname}_mup"
                prop_must = self._propmap_name(must, candidate)

                # no reuse, generate new map
                if prop_must == candidate:
                    self._propmap_gen(jm, must, prop_must, mpath)

                mu_prop_code = (
                    gen.inc_var(must_c) +
                    gen.if_stmt(gen.not_op(gen.check_call(pfun, pval, lpath_ref, is_ptr=True)),
                        self._gen_fail(f"invalid mandatory prop value [{smpath}]", lpath_ref))
                )

                # use map
                if gen.assign_expr():
                    mu_expr = gen.assign_prop_fun(pfun, prop, prop_must)
                    mu_code = (
                        gen.lcom(f"handle {len(must)} mandatory props") +
                        gen.if_stmt(gen.is_def(pfun), mu_prop_code)
                    )
                else:
                    mu_expr = gen.has_prop_fun(prop, prop_must)
                    mu_code = (
                        gen.lcom(f"handle {len(must)} mandatory props") +
                        gen.fun_var(pfun, gen.get_prop_fun(prop, prop_must)) +
                        mu_prop_code
                    )

                multi_if += [(mu_expr, mu_code)]

        if may:

            if len(may) <= self._map_threshold:  # simple few-property code

                for p, m in may.items():
                    ma_expr = gen.str_cmp(prop, "=", gen.esc(p))
                    ma_code = (
                        gen.lcom(f"handle may {p} property") +
                        self._compileModel(jm, m, mpath + [p], res, pval, lpath_ref) +
                        gen.if_stmt(gen.not_op(res),
                            self._gen_fail(
                                f"invalid optional prop value [{json_path(mpath + [p])}]",
                                lpath_ref)
                        )
                    )
                    multi_if += [(ma_expr, ma_code)]

            else:  # generic code

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
                            self._gen_fail(f"invalid optional prop value [{smpath}]", lpath_ref))
                    )
                else:
                    ma_expr = gen.has_prop_fun(prop, prop_may)
                    ma_code = (
                        gen.lcom(f"handle {len(may)} may props") +
                        gen.fun_var(pfun, gen.get_prop_fun(prop, prop_may)) +
                        gen.if_stmt(
                            gen.not_op(gen.check_call(pfun, pval, lpath_ref, is_ptr=True)),
                            self._gen_fail(f"invalid optional prop value [{smpath}]", lpath_ref))
                    )

                multi_if += [(ma_expr, ma_code)]

        # $* is inlined expr (FIXME inlining does not work with vpath)
        for d, m in defs.items():
            ref = "$" + d
            dl_expr = self._dollarExpr(jm, ref, prop, lpath_ref, is_raw=True)  # FIXME lpath &lpath?
            dl_code = gen.lcom(f"handle {len(defs)} key props") + \
                self._compileModel(jm, m, mpath + [ref], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(dl_expr, dl_code)]

        # // is inlined
        for r, v in regs.items():
            # FIXME options?!
            regex = f"/{r}/"
            rg_expr = self._regExpr(jm, regex, prop, vpath, True)  # FIXME lpath &lpath?
            rg_code = gen.lcom(f"handle {len(regs)} re props") + \
                self._compileModel(jm, v, mpath + [regex], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(rg_expr, rg_code)]

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
            gen.path_var(lpath, gen.path_val(vpath, prop, True), True) +
            gen.mif_stmt(multi_if, ot_code))

        # check that all must were seen, with some effort to report the missing ones
        if must:
            missing = []
            for prop in sorted(must.keys()):
                missing += \
                    gen.if_stmt(gen.not_op(gen.has_prop(val, prop)),
                                gen.report(f"missing mandatory prop <{prop}> [{smpath}]", vpath))
            code += \
                gen.if_stmt(gen.num_cmp(must_c, "!=", gen.const(len(must))),
                            self._gen_reporting(missing) +
                            gen.ret(gen.false()))

        # early returns so no need to look at res
        code += gen.ret(gen.true())

        return code

    def _compileOr(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                   res: str, val: str, vpath: str, known: set[BoolExpr]|None = None) -> Block:
        """Compile a or-list of models."""

        code = []
        gen = self._lang
        smpath = json_path(mpath)

        # direct empty list
        # NOTE in practice this case is optimized out so should not come here
        if not models:
            if self._report:
                code += [ gen.report(f"empty or [{smpath}]", vpath) ]
            code += gen.bool_var(res, gen.false())
            return code

        # partial/full list of constants optimization
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
        if dcode := self._disjunction(jm, tmp, mpath, res, val, vpath):
            if need_if:
                return code + gen.if_stmt(gen.not_op(res), dcode)
            else:
                return code + dcode
            return

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

        icode = []
        for i, m in reversed(list(enumerate(models))):
            body = self._compileModel(jm, m, mpath + [i], res, val, vpath, or_known) + icode
            if i > 0:
                icode = gen.if_stmt(gen.not_op(res), body)
            else:
                icode =  body

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
                      constrained: bool = False) -> Block:
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
                                gen.path_var(lpath, gen.path_val(vpath, idx, False), True) +
                                self._compileModel(jm, model[0], mpath + [0],
                                                   res, item,
                                                   gen.path_lvar(lpath, vpath)) +  # type: ignore
                                gen.if_stmt(gen.not_op(res), gen.brk()))

                    code += (
                        gen.bool_var(res, expr if expr else gen.true()) +
                        gen.if_stmt(res, loop) if expr else loop
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
                                gen.path_var(lpath, gen.path_val(vpath, i, False), declare=i==0) +
                                # FIXME generated variable reference…
                                self._compileModel(
                                    jm, model[i], mpath + [i],
                                    res, gen.arr_item_val(val, i), lpath_ref) +
                                body)
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
                                gen.path_var(lpath, gen.path_val(vpath, idx, False)) +
                                self._compileModel(jm, lmodel, mpath + [start], res,
                                                   gen.arr_item_val(val, idx), lpath_ref) +
                                gen.if_stmt(gen.not_op(res), gen.brk())
                            )

                        for i, m in reversed(list(enumerate(model[:-1]))):
                            ith_check = \
                                gen.if_stmt(gen.num_cmp(arlen, ">", i),
                                    gen.path_var(lpath, gen.path_val(vpath, i, False)) +
                                    self._compileModel(jm, m, mpath + [i], res,
                                                       gen.arr_item_val(val, i), lpath_ref))
                            if body:
                                body = ith_check + gen.if_stmt(res, body)
                            else:
                                body = ith_check

                        # compute len before checking array items
                        body = gen.int_var(arlen, gen.arr_len(val), declare=True) + body

                        if lmodel == "$ANY":
                            body += gen.lcom("no array tail value checks needed")

                        code += (
                            gen.bool_var(res, expr if expr else gen.true()) +
                            gen.if_stmt(res, body) if expr else body
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
                    # new function to check the object
                    objid = gen.ident(self._prefix + "obj")
                    ocode: Block = (
                        gen.lcom(f"object {json_path(mpath)}") +
                        gen.sub_fun(objid,
                            self._compileObject(jm, model, mpath, objid, "res", "val", "path"),
                            inline=True)
                    )
                    self._code.subs(ocode)

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

        body = self._lang.bool_var("res", declare=True) + \
            self._compileModel(jm, model, mpath, "res", "val", "path", set()) + \
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

        # generate mapping, name must be consistent with data/clang_*.c
        self._code.pmap(f"{self._code._entry}_map", entries, True)

        return self._code


def xstatic_compile(
        model: JsonModel,
        fname: str = "check_model",
        *,
        lang: str = "py",
        prefix: str = "_jm_",
        relib: str|None = None,
        map_threshold: int = 3,
        execute: bool = True,
        map_share: bool = False,
        debug: bool = False,
        report: bool = True,
        short_version: bool = False,
        package: str|None = None,
        inline: bool = True,
    ) -> Code:
    """Generate the check source code for a model.

    - model: JSON Model root to compile.
    - fname: target function name.
    - lang: name of target language.
    - prefix: prefix for generated functions.
    - map_threshold: inline property checks under this threshold.
    - map_share: share generated property maps.
    - report: whether to generate code to report rejection reasons.
    - debug: debugging mode generates more traces.
    - short_version: in generated code.
    - package: namespace to use (Perl module, Pg schema name, Java package).
    - inline: enable function inlining (for C)
    """
    # target language
    if lang == "py":
        from .python import Python
        language = Python(debug=debug, with_report=report, with_path=report,
                          relib=relib or "re2")
    elif lang == "c":
        from .clang import CLangJansson
        language = CLangJansson(debug=debug, with_report=report, with_path=report,
                                relib=relib or "re2", inline=inline)
    elif lang == "js":
        from .javascript import JavaScript
        language = JavaScript(debug=debug, with_report=report, with_path=report,
                              relib=relib or "re")
    elif lang in ("plpgsql", "sql"):
        from .plpgsql import PLpgSQL
        language = PLpgSQL(debug=debug, with_report=report, with_path=report,
                           relib=relib or "re", with_package=package is not None)
        package = package or "public"
    elif lang == "pl":
        from .perl import Perl
        language = Perl(debug=debug, with_report=report, with_path=report, relib=relib or "re2",
                        with_package=package is not None)
        package = package or "Model"
    elif lang == "java":
        # package?
        from .java import Java
        language = Java(debug=debug, with_report=report, with_path=report, relib=relib or "re",
                        with_package=package is not None)
    else:
        raise NotImplementedError(f"no support yet for language: {lang}")

    # cold override
    language._short_version = short_version

    # cource code generator
    gen = CodeGenerator(model._globs, language, fname, prefix=prefix,  # type: ignore
                        execute=execute, map_threshold=map_threshold, map_share=map_share,
                        debug=debug, report=report, package=package)

    # generate
    code = gen.compileJsonModelHead(model)

    # debug and log.debug(f"code = {code}")
    return code
