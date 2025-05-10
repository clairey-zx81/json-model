# experimental static (ecstatic?) compiler

from typing import Callable
import re
import json

from .mtypes import ModelType, ModelError, ModelPath, UnknownModel, Symbols, Jsonable
from .utils import split_object, model_in_models, all_model_type, constant_value
from .utils import log, tname, json_path
from .defines import Validator
from .model import JsonModel
from .language import Language, Code, Block, BoolExpr

_PREDEFS = {
    "$ANY", "$NONE", "$NULL", "$BOOL",
    "$INT", "$INTEGER", "$I32", "$I64", "$U32", "$U64",
    "$FLOAT", "$F32", "$F64", "$NUMBER",
    "$STRING", "$DATE", "$URL", "$REGEX",
}


class SourceCode(Validator):
    """Source code for compiling JSON Models.

    - globs: global map of symbols.
    - prefix: use this prefix for function name generation.
    - report: whether to report rejection reasons.
    - path: whether to keep track of value path while checking.
    - debug: verbose debug mode.
    """

    def __init__(self, globs: Symbols, language: Language, *,
                 prefix: str = "",
                 report: bool = True, path: bool = True, debug: bool = False):

        super().__init__()

        self._globs = globs
        self._lang = language
        self._prefix = prefix
        self._report = report
        self._path = path
        self._debug = debug

        self._code = Code(language)

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
        self.reset()

    def reset(self):
        self._code.clear()
        self._names.clear()
        self._regs.clear()
        self._compiled.clear()
        self._to_compile.clear()

    # add contents
    def subs(self, code: Block):
        self._code.subs(code)

    def help(self, code: Block):
        self._code.header(code)

    def define(self, line: str):
        """Append a definition."""
        self._code.defs([line])

    # code generation

    def _ident(self, prefix: str, local: bool = False) -> str:
        """Generate a new identifier using a prefix and a counter."""
        if prefix not in self._nvars:
            self._nvars[prefix] = 0
        ident = f"{'' if local else self._prefix}{prefix}{self._nvars[prefix]}"
        self._nvars[prefix] += 1
        return ident

    def _regex(self, regex: str) -> str:
        """Compile a regular expression, with memoization, return function name."""

        if regex not in self._regs:

            # extract and check actual pattern
            try:
                pattern, ropts = regex[1:].rsplit("/", 1)
                assert ropts == "" or ropts.isalpha(), f"invalid options: {ropts}"
                pattern = f"(?{ropts}){pattern}" if ropts else pattern
                # statically check re validity
                if self._lang._relib == "re2":
                    import re2 as rex
                else:
                    import re as rex
                rex.compile(pattern)
            except Exception as e:
                raise ModelError(f"invalid regex: {regex} ({e})")

            # ok, generate code for pattern
            gen = self._lang
            fun = gen.new_ident(self._prefix + "re")
            self._code.defs(gen.decl_re(fun, pattern))
            self._code.subs(gen.gen_re(fun, pattern))
            self._code.init(gen.init_re(fun, pattern))

            # memoize
            self._regs[regex] = fun

        return self._regs[regex]

    def _regExpr(self, regex: str, val: str, path: str) -> BoolExpr:
        """Generate an inlined regex check expression on a value."""
        gen = self._lang

        # optimized versions
        if re.match(r"^/\^?.\*\$?/[mis]?$", regex):
            return gen.bool_cst(True)
        elif re.match(r"^/(\?s)\.\+?/$", regex) or re.match(r"^/\.\+?/s$", regex):
            return gen.num_gt(gen.str_len(gen.str_val(val)), gen.int_cst(0))
        else:
            fun = self._regex(regex)
            # TODO inline the internal function if possible?
            return gen.str_check_call(fun, gen.str_val(val))
        # TODO f" or _rep(f\"does not match {self._fesc(regex)} at {{{path}}}\", rep)"

    def _esc(self, val: Jsonable) -> str:
        """Escape value as necessary."""
        # return '"' + string.translate({"\"": "\\\"", "\\": "\\\\"}) + '"'
        return json.dumps(val) if isinstance(val, str) else str(val)

    def _fesc(self, val: str) -> str:
        """Escape string for an f-string."""
        # FIXME return val.translate({"{": "{{", "\\": "\\\\", "\"": "\\\""})
        return "FESC"

    def _dollarExpr(self, jm: JsonModel, ref: str, val: str, vpath: str):
        assert ref and ref[0] == "$"
        if ref in _PREDEFS:  # inline predefs
            # TODO improve
            return self._lang.predef(val, ref)
            # return (self._PREDEFS[ref](val, vpath) +
            #         (f" or _rep(f\"invalid {ref} at {{{vpath}}}\", rep)" if self._report else ""))
        else:
            fun = self._getNameRef(jm, ref, [])
            return self._lang.check_call(fun, val)  # FIXME vpath?

    def _compileConstraint(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                           res: str, val: str, vpath: str):
        assert isinstance(model, dict) and "@" in model
        smpath = json_path(mpath)
        self._compileModel(jm, model["@"], mpath + ["@"], res, val, vpath)
        tmodel = self._ultimate_type(jm, model["@"])  # pyright: ignore
        # NOTE UnknownModel should raise an error on any constraint
        # FIXME see _untype00.model.json for multiple types
        assert tmodel in (int, float, str, list, dict, UnknownModel, None), f"simple {tmodel}"
        checks = []
        what = f"len({val})" if tmodel in (list, dict) else val
        twhat = int if tmodel in (list, dict, None) else tmodel
        for constraint in ("=", "!=", "<", "<=", ">", ">="):
            if constraint in model:
                op = "==" if constraint == "=" else constraint
                cst = model[constraint]
                if not isinstance(cst, (twhat, int)):
                    raise ModelError(f"invalid constant: {cst} ({twhat.__name__}) {mpath}")
                if isinstance(cst, int) and tmodel is str:
                    checks.append(f"len({val}) {op} {cst}")
                elif isinstance(cst, int) and tmodel == UnknownModel:
                    checks.append(f"(len({val}) {op} {cst} if isinstance({val}, (str, list, dict))"
                                  " else "
                                  f"{val} {op} {self._esc(cst) if isinstance(cst, str) else cst})")
                elif isinstance(cst, str):
                    checks.append(f"{what} {op} {self._esc(cst)}")
                else:  # same type or list or dict
                    checks.append(f"{what} {op} {cst}")
        if "!" in model:
            if not isinstance(model["!"], bool):
                raise ModelError(f"! constraint expects a boolean {mpath}")
            if model["!"]:
                log.warning("FIXME: ! generated code is not reliable")
                code.add(indent, f"{res} &= len(set({val})) == len({val})")
            # else defaut is nothing to check
        if checks:
            code.add(indent, f"{res} &= {' and '.join(checks)}")
        if self._report:
            code.add(indent, f"if not {res}:")
            code.add(indent + 1, _rep(f"invalid type or constraints at {{{vpath}}} [{smpath}]"))

    def _disjunction(self, code: Code, indent: int,
                     jm: JsonModel, model: ModelType, mpath: ModelPath,
                     res: str, val: str, vpath: str) -> bool:
        """Generate optimized disjunction check.

        model: `{"|": [ o1, o2, ... ] }`
        """

        dis = self._disjunct_analyse(jm, model, mpath)  # pyright: ignore
        if dis is None:
            return False
        tag_name, tag_type, models, all_const_props = dis
        smpath = json_path(mpath)

        # Compile all object models in the list if needed
        assert isinstance(model, dict)

        init = model["|"]
        assert isinstance(init, list)  # pyright hint
        assert len(models) == len(init)
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
                c = Code()
                self._compileModel(jm, m, p, "res", "val", "path")
                # log.debug(f"{self._paths}")

        # {disid}_tm = { tag-value: check_function_for_this_tag_value }
        # if v is dict:
        #     if v[tag] in object_tag:
        #         res = object_tag[v[tag]](v)
        disid = self._ident("map_")
        tag = self._ident("tag_", True)

        # mapping from tag values to check functions
        TAG_CHECKS = {}
        for i in range(len(models)):
            consts = all_const_props[i]
            TAG_CHECKS[consts[tag_name]] = self._paths[tuple(mpath + [i])]

        self.define(f"{disid}: TagMap")
        self._maps[disid] = TAG_CHECKS
        esctag = self._esc(tag_name)

        # val is Object, tag is in val, tag_value is valid
        code.add(indent, f"{res} = isinstance({val}, dict)")
        code.add(indent, f"if {res}:")
        code.add(indent, f"    {res} = {esctag} in {val}")
        code.add(indent, f"    if {res}:")
        code.add(indent, f"        {tag} = {val}[{esctag}]")
        code.add(indent, f"        if {tag} in {disid}:")
        code.add(indent, f"            {res} = {disid}[{tag}]({val}, {vpath})")
        code.add(indent, r"        else:")
        if self._report:
            code.add(indent + 3,
                     _rep(f"tag {tag_name} value not found at {{{vpath}}} [{smpath}.'|']"))
        code.add(indent, f"            {res} = False")
        if self._report:
            code.add(indent, r"    else:")
            code.add(indent + 2, _rep(f"missing tag prop {tag_name} at {{{vpath}}} [{smpath}.'|']"))
            code.add(indent, r"else:  # not a dict")
            code.add(indent + 1, _rep(f"not an object at {{{vpath}}} [{smpath}.'|']"))

        return True

    def _gen_fail(self, msg: str) -> Block:
        """Generate a report and return false."""
        gen = self._lang
        return self._gen_report(msg) + [ gen.ret(gen.bool_cst(False)) ]

    def _gen_short_res(self, res: str) -> Block:
        """Generate a shortcut return if result is false."""
        gen = self._lang
        return gen.if_stmt(gen.not_op(res), [ gen.ret(gen.bool_cst(False)) ])

    def _compileObject(self, code: Code, indent: int,
                       jm: JsonModel, model: ModelType, mpath: ModelPath,
                       oname: str, res: str, val: str, vpath: str) -> Block:
        """Generate the body of a function which checks an actual object."""

        assert isinstance(model, dict)
        gen = self._lang

        # separate properties
        must, may, defs, regs, oth = split_object(model, mpath)
        smpath = json_path(mpath)

        # generated code helpers
        code: Block = []
        multi_if: list[tuple[BoolExpr, Block]] = []
        prop, pval, must_c = "prop", "pval", "must_count"

        # should be an object
        code += [
            gen.if_stmt(gen.not_op(gen.is_obj(val)),
                        self._gen_fail(f"not an object at {{{vpath}}} [{smpath}]"))
        ]

        # shorcut for empty object
        if not must and not may and not defs and not regs and not oth:
            code += \
                gen.if_stmt(gen.num_eq(gen.obj_len(val), gen.int_cst(0)),
                            [ gen.ret(bool_cst(True)) ],
                            self._gen_fail(f"expecting empty object at {{{vpath}}} [{smpath}]"))
            return code

        code += [ gen.decl_fun_var("fun") ]

        # build multi-if structure to put in prop/val loop
        if must:
            prop_must = f"{oname}_must"
            self._code.decl_map(prop_must)

            # must prop counter to check at the end if all were seen
            code += [ gen.decl_int_var_val(musc_c, gen.int_cst(0)) ]

            prop_must_map: dict[str, str] = {}
            for p in sorted(must.keys()):
                m = must[p]
                pid = f"{prop_must}_{p}"  # tmp unique identifier
                self._compileName(jm, pid, m, mpath + [p], True)
                prop_must_map[p] = self._getName(jm, pid)

            self._code.init_map(prop_must, prop_must_map)
            # self._maps[prop_must] = prop_must_map

            mu_expr = gen.prop_fun("fun", prop, prop_must_map)
            mu_code = gen.if_stmt(
                gen.is_def("fun"), [
                    gen.inc_var(must_c)
                ] + gen.if_stmt(gen.not_op(gen.check_call("fun", pval)),
                        self._gen_fail(f"invalid must property {{{prop}}} value at {{{vpath}}} [{smpath}]"))
            )
            multi_if += (mu_expr, mu_code)

        if may:
            prop_may = f"{oname}_may"
            self._code.decl_map(prop_may)

            prop_may_map: dict[str, str] = {}
            for p in sorted(may.keys()):
                m = may[p]
                pid = f"{prop_may}_{p}"
                self._compileName(jm, pid, m, mpath + [p])
                prop_may_map[p] = self._getName(jm, pid)

            self._code.init_map(prop_may, prop_may_map)
            # self._maps[prop_may] = prop_may_map

            ma_expr = gen.prop_fun("fun", prop, prop_must_map)
            ma_code = gen.if_stmt(
                gen.and_op(gen.is_def("fun"), gen.not_op(gen.check_call("fun", pval))),
                self._gen_fail(f"invalid may property {{{prop}}} value at {{{vpath}}} [{smpath}]")
            )
            multi_if += (ma_expr, ma_code)

        # $* is inlined expr (FIXME inlining does not work with vpath)
        for d, m in defs.keys():
            ref = "$" + d
            dl_expr = self._dollarExpr(jm, ref, prop, vpath)
            dl_code = self._compileModel(jm, m, mpath + [ref], res, pval, "lpath") + \
                self._gen_short_res(res)
            multi_if += (dl_expr, dl_code)

        # // is inlined
        for r, v in regs.items():
            # FIXME options?!
            regex = f"/{r}/"
            rg_expr = self._regExpr(regex, prop, "lpath")
            rg_code = self._compileModel(jm, v, mpath + [regex], res, pval, "lpath") + \
                self._gen_short_res(res)
            multi_if += (rg_expr, rg_code)

        # catchall is inlined?
        ot_code: Block
        if oth:
            omodel = oth[""]
            smpath = json_path(mpath + [""])
            if omodel != "$ANY":
                ot_code = self._compileModel(jm, omodel, mpath + [""], res, pval, "lpath") + \
                    self._gen_fail(f"unexpected other value at {{lpath}} [{smpath}]")
            else:  # optimized "": "$ANY" case
                ot_code = []
        else:  # no catch all
            smpath = json_path(mpath)
            ot_code = self._gen_fail(f"no other prop expected at {{{vpath}}} [{smpath}]")

        code += gen.obj_loop(val, prop, pval,
            [ gen.lcom(f"TODO lpath = {vpath} + '.' + {prop}") ] +
            gen.mif_stmt(multi_if, ot_code))

        # check that all must were seen, although we do not know which ones
        if must:
            code += gen.if_stmt(gen.num_ne(must_c, gen.int_cst(len(must))),
                self._gen_fail(f"missing must prop at {{{vpath}}} [{smpath}]"))

        # early returns so no need to look at res
        code += gen.ret(gen.bool_cst(True))

    def _gen_report(self, res: str, msg: str) -> Block:
        if self._report:
            gen = self._lang
            return gen.if_stmt(gen.not_op(res), gen.report(msg))
        else:
            return []

    def _compileModel(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                      res: str, val: str, vpath: str, known: set[str]|None = None) -> Block:
        # known = expression already verified
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath}")
        assert isinstance(mpath, list)
        smpath = json_path(mpath)
        gen = self._lang
        code = [ gen.lcom(f"{json_path(mpath)}") ]
        match model:
            case None:
                code += [ gen.bool_var_val(res, gen.is_null(val)) ] + \
                    self._gen_report(res, f"not null at {{{vpath}}} [{smpath}]")
            case bool():
                code += [ gen.bool_var_val(res, gen.is_bool(val)) ] + \
                    self._gen_report(res, f"not a bool at {{{vpath}}}[{smpath}]")
            case int():
                expr = gen.is_int(val, jm._loose_int)
                if known is not None:
                    if expr in known:
                        expr = None
                if model == -1:
                    if known is not None:
                        if expr is not None:
                            known.add(expr)
                    if not expr:
                        expr = "True"
                elif model == 0:
                    compare = gen.num_ge(gen.int_val(val), gen.int_cst(0))
                    expr = gen.and_op(expr, compare) if expr else compare
                elif model == 1:
                    compare = gen.num_ge(gen.int_val(val), gen.int_cst(1))
                    expr = gen.and_op(expr, compare) if expr else compare
                else:
                    raise ModelError(f"unexpected int value {model} at {smpath}")
                if expr:
                    code += [ gen.bool_var_val(res, expr) ] + \
                        self._gen_report(res, f"not a {model} int at {{{vpath}}} [{smpath}]")
            case float():
                expr = gen.is_flt(val, jm._loose_float)
                if known is not None:
                    if expr in known:
                        expr = None
                if model == -1.0:
                    if known is not None:
                        if expr is not None:
                            known.add(expr)
                    if not expr:
                        expr = "True"
                elif model == 0.0:
                    compare = gen.num_ge(gen.flt_val(val), gen.flt_cst(0.0))
                    expr = gen.and_op(expr, compare) if expr else compare
                elif model == 1.0:
                    compare = gen.num_gt(gen.flt_val(val), gen.flt_cst(0.0))
                    expr = gen.and_op(expr, compare) if expr else compare
                else:
                    raise ModelError(f"unexpected float value {model} at {mpath}")
                if expr:
                    code += [ gen.bool_var_val(res, expr) ] + \
                        self._gen_report(res, f"not a {model} float at {{{vpath}}} [{smpath}]")
            case str():
                expr = gen.is_str(val)
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
                    code += [ gen.bool_var_val(res, expr if expr else gen.bool_cst(True)) ]
                elif model[0] == "_":
                    compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += [ gen.bool_var_val(res, expr) ]
                elif model[0] == "=":
                    # TODO FIXME known
                    # NOTE expr is ignore here
                    (a_cst, value) = constant_value(model, mpath)
                    if not a_cst:
                        raise ModelError(f"unexpected constant: {model}")
                    if value is None:
                        code += [ gen.bool_var_val(res, gen.is_null(val)) ]
                    elif isinstance(value, bool):
                        code += [
                            gen.bool_var_val(res,
                                gen.and_op(gen.is_bool(val),
                                           gen.num_eq(gen.bool_val(val), gen.bool_cst(value))))
                        ]
                    elif isinstance(value, int):
                        code += [
                            gen.bool_var_val(res,
                                gen.and_op(gen.is_int(val, jm._loose_int),
                                           # FIXME cast depends on type?
                                           gen.num_eq(gen.int_val(val), gen.int_cst(value))))
                        ]
                    elif isinstance(value, float):
                        code += [
                            gen.bool_var_val(res,
                                gen.and_op(gen.is_flt(val, jm._loose_float),
                                           # FIXME cast depends on type?
                                           gen.num_eq(gen.flt_val(val), gen.flt_cst(value))))
                        ]
                    # elif isinstance(value, str):
                    #     compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    #     expr = gen.and_op(expr, compare) if expr else compare
                    #     code += [ gen.bool_var_val(res, expr) ]
                    else:
                        raise ModelError(f"unexpected constant type: {tname(value)}")
                elif model[0] == "$":
                    call = self._dollarExpr(jm, model, val, "path")
                    code += [ gen.bool_var_val(res, call) ]
                elif model[0] == "/":
                    code += [ gen.lcom(f"{self._esc(model)}") ]
                    call = self._regExpr(model, val, vpath)
                    code += [ gen.bool_var_val(res, gen.and_op(expr, call) if expr else call) ]
                else:  # simple string
                    compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += [ gen.bool_var_val(res, expr) ]
                if self._report:
                    smodel = model if model else "string"
                    if model and model[0] == "/":  # FIXME workaround
                        smodel = "REGEX"
                    code += self._gen_report(res, f"unexpected {smodel} at {{{vpath}}} [{smpath}]")
            case list():
                expr = f"isinstance({val}, list)"
                smpath = json_path(mpath)
                if known is not None:
                    if expr in known:
                        expr = None
                    if expr is not None:
                        known.add(expr)
                if len(model) == 0:
                    if expr:
                        expr += f" and len({val}) == 0"
                    else:
                        expr = f"len({val}) == 0"
                    code.add(indent, f"{res} = {expr}")
                elif len(model) == 1:
                    arrayid = self._ident("array_", True)
                    idx, item = f"{arrayid}_idx", f"{arrayid}_item"
                    if expr:
                        code.add(indent, f"{res} = {expr}")
                        code.add(indent, f"if {res}:")
                    else:
                        code.add(indent, "if True:")
                    # code.add(indent + 1, f"assert isinstance({val}, list)  # pyright helper")
                    code.add(indent + 1, f"for {idx}, {item} in enumerate({val}):")
                    code.add(indent + 1, f"    lpath = {vpath} + '.' + str({idx})")
                    # i+1
                    self._compileModel(jm, model[0], mpath + [0],
                                       res, item, "lpath")
                    # shortcut
                    code.add(indent + 2, f"if not {res}:")
                    # if self._report:
                    #     code.add(indent + 3,
                    #              _rep(f"unexpected array value at {{lpath}} [{smpath}]"))
                    code.add(indent + 2, r"    break")
                else:
                    if expr:
                        code.add(indent, f"{res} = {expr} and len({val}) == {len(model)}")
                    else:
                        code.add(indent, f"{res} = len({val}) == {len(model)}")
                    for i, m in enumerate(model):
                        code.add(indent + i, f"if {res}:")
                        # i+1
                        self._compileModel(jm, model[i], mpath + [i],
                                           res, f"{val}[{i}]", f"{vpath} + '.{i}'")
                    if self._report:
                        code.add(indent, r"else:")
                        code.add(indent + 1,
                                 _rep(f"not array or bad array length at {{{vpath}}} [{smpath}]"))
                if self._report:
                    code.add(indent, f"if not {res}:")
                    code.add(indent + 1,
                             _rep(f"not array or unexpected array at {{{vpath}}} [{smpath}]"))
            case dict():
                # TODO report
                assert isinstance(model, dict)  # pyright hint
                assert "+" not in model, "merge must have been preprocessed"
                if "@" in model:
                    self._compileConstraint(code, indent, jm, model, mpath, res, val, vpath)
                elif "|" in model:
                    lpath = mpath + ["|"]
                    slpath = json_path(lpath)
                    models = model["|"]
                    assert isinstance(models, list)  # pyright hint
                    # partial list of constants optimization
                    l_const = list(map(lambda m: constant_value(m, lpath), models))
                    if len(list(filter(lambda t: t[0], l_const))) >= 2:
                        constants, n_models = set(), []
                        for i in range(len(models)):
                            # NOTE python equality is a pain, True == 1 == 1.0, False == 0 == 0.0
                            # NOTE python typing is a pain, isinstance(True, int) == True
                            # thus we only keep strings…
                            if l_const[i][0] and isinstance(l_const[i][1], str):
                                constants.add(l_const[i][1])
                            else:
                                n_models.append(models[i])
                        if constants:
                            # ensure a deterministic output
                            sconst = "{" + str(sorted(constants))[1:-1] + "}"
                            code.add(indent,
                                     f"{res} = not isinstance({val}, (list, dict)) and "
                                     f"{val} in {sconst}")
                            if self._report:
                                code.add(indent, f"if not {res}:")
                                code.add(indent + 1,
                                         _rep(f"value not in enum at {{{vpath}}} [{slpath}]"))
                            if not n_models:
                                return
                            code.add(indent, f"if not {res}:")
                            indent += 1
                            models = n_models
                    # empty list
                    if not models:
                        if self._report:
                            code.add(indent, _rep(f"empty or at {{{vpath}}} [{slpath}]"))
                        code.add(indent, f"{res} = False")
                        return
                    # discriminant optimization
                    if self._disjunction(code, indent, jm, model, lpath, res, val, vpath):
                        return
                    # homogeneous typed list
                    same, expected = all_model_type(models, lpath)
                    or_known = set()
                    if same:
                        # all models have the same ultimate type
                        if expected is int:
                            type_test = f"isinstance({val}, int) and not isinstance({val}, bool)"
                        else:
                            type_test = f"isinstance({val}, {expected.__name__})"  # type: ignore
                        code.add(indent, f"{res} = {type_test}")
                        code.add(indent, f"if {res}:")
                        indent += 1
                        or_known.add(type_test)
                    for i, m in enumerate(models):
                        if i:
                            code.add(indent + i - 1, f"if not {res}:")
                        # i
                        self._compileModel(jm, m, lpath + [i], res, val, vpath, or_known)
                    if self._report:
                        code.add(indent, f"if not {res}:")
                        code.add(indent + 1, _rep(f"not any model match at {{{vpath}}} [{slpath}]"))
                elif "&" in model:
                    and_known = set(known or [])
                    lpath = mpath + ["&"]
                    slpath = json_path(lpath)
                    models = model["&"]
                    assert isinstance(models, list)  # pyright hint
                    if not models:
                        code.add(indent, f"{res} = True")
                        return
                    # homogeneous typed list
                    same, expected = all_model_type(models, lpath)
                    if same:
                        # all models have the same ultimate type
                        if expected is int:
                            type_test = f"isinstance({val}, int) and not isinstance({val}, bool)"
                        else:
                            type_test = f"isinstance({val}, {expected.__name__})"  # type: ignore
                        code.add(indent, f"{res} = {type_test}")
                        code.add(indent, f"if {res}:")
                        indent += 1
                        and_known.add(type_test)
                    for i, m in enumerate(models):
                        if i:
                            code.add(indent + i - 1, f"if {res}:")
                        # i
                        self._compileModel(jm, m, lpath + [i], res, val, vpath, and_known)
                    if self._report:
                        code.add(indent, f"if not {res}:")
                        code.add(indent + 1, _rep(f"not all model match at {{{vpath}}} [{slpath}]"))
                elif "^" in model:
                    lpath = mpath + ["^"]
                    slpath = json_path(lpath)
                    models = model["^"]
                    assert isinstance(models, list)  # pyright hint

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

                        # false if in dups
                        for i, m in enumerate(dups):
                            idx = dups_i[i]
                            # i
                            self._compileModel(jm, m, lpath + [idx], "isin", val, vpath)
                            code.add(indent + i, f"{res} = not isin")
                            code.add(indent + i, f"if {res}:")

                        # update remaining models and identation
                        models = kept
                        models_i = kept_i
                        depth = len(dups)
                    else:
                        models_i = list(range(len(models)))
                        depth = 0

                    # standard case
                    if not models:
                        code.add(indent + depth, f"{res} = False")
                    elif len(models) == 1:
                        mod, idx = models[0], models_i[0]
                        # depth
                        self._compileModel(jm, mod, lpath + [idx], res, val, vpath)
                    else:  # several models are inlined
                        if len(models) == 2 and "$ANY" in models:
                            # get other model
                            m = models[1] if models[0] == "$ANY" else models[0]
                            is_m = self._ident("is_m_", True)
                            # depth
                            self._compileModel(jm, m, lpath + ["?"], is_m, val, vpath)
                            code.add(indent + depth, f"{res} = not {is_m}")
                        else:
                            count = self._ident("xc_", True)
                            test = self._ident("xr_", True)
                            code.add(indent + depth, f"{count} = 0")
                            for i, m in enumerate(models):
                                idx = models_i[i]
                                code.add(indent + depth, f"if {count} <= 1:")
                                # depth + 1
                                self._compileModel(jm, m, lpath + [idx], test, val, vpath)
                                code.add(indent + depth + 1, f"if {test}: {count} += 1")
                            code.add(indent + depth, f"{res} = {count} == 1")
                    if self._report:
                        code.add(indent, f"if not {res}:")
                        code.add(indent + 1, _rep(f"not one model match at {{{vpath}}} [{slpath}]"))
                else:
                    # TODO optimize empty model?
                    # generate separate functions for objects?
                    hpath = tuple(mpath)
                    if hpath not in self._paths:
                        objid = self._ident("obj_")
                        self._paths[hpath] = objid
                    else:
                        objid = self._paths[hpath]
                    if hpath not in self._generated:
                        ocode = Code()
                        ocode.nl()
                        ocode.add(0, f"# object {json_path(mpath)}")
                        path_init = " = \"$\"" if mpath == ["$"] else ""
                        ocode.add(0, f"def {objid}(value: Jsonable, path: str{path_init}, "
                                  f"rep: Report = None) -> bool:")
                        self._compileObject(ocode, 1, jm, model, mpath, objid, _RES, _VAL, _PATH)
                        self.subs(ocode)
                        self._generated.add(hpath)
                    del hpath
                    code.add(indent, f"{res} = {objid}({val}, {vpath}, rep)")
                    if self._report:
                        code.add(indent, f"if not {res}:")
                        code.add(indent + 1,
                                 _rep(f"not an expected object at {{{vpath}}} [{smpath}]"))
            case _:
                raise ModelError(f"unexpected model type: {tname(model)}")
        return code

    def _getName(self, jm: JsonModel, name: str) -> str:
        """Ensure global unique names for internal functions."""
        # FIXME global name space! prefix with jm._id ?
        if name not in self._names:
            self._names[name] = self._ident("f_")
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
        # log.debug(f"name ref: gref={gref} globs={self._globs} names={self._names}")
        if gref not in self._names:
            jm = self._globs[gref]  # pyright: ignore
            if jm._id not in self._compiled:
                self._to_compile[jm._id] = (jm, gref)
            self._names[gref] = f"json_model_{jm._id}"
        # log.debug(f"name ref: ref={ref} gref={gref} at {path}: {self._names[gref]}")
        return self._names[gref]

    def _compileName(self, jm: JsonModel,
                     name: str, model: ModelType, mpath: ModelPath, local: bool = False):
        """Compile a model under a given name in a given scope."""
        log.debug(f"name: mpath={mpath} name={name} jm={jm._id}")

        # TODO simplify, clarify
        # memoize the associated function name that can be retrieved if there is a recursion
        xname = name if not name or name[0] != "$" else name[1:]
        self._defs.set(xname, model)
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

        body = self._compileModel(jm, model, mpath, "res", "val", "path", None)
        body = [ self._lang.decl_bool_var("res") ] + body + [ self._lang.ret("res") ]

        self._code.sub(fun, body, comment=f"check {name} ({json_path(mpath)})", local=local)

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
            raise Exception("should not get there?!")

    def compileOneJsonModel(self, jm: JsonModel, name: str, path: ModelPath, local: bool = False):
        if jm._id not in self._compiled:
            self._compiled.add(jm._id)
            if name not in self._names:
                self._names[name] = "json_model_" + str(jm._id)
            self._compileName(jm, name, jm._model, path, local)

    def compileJsonModelHead(self, name: str, model: JsonModel):
        # $# special handing
        self._names["$#"] = f"json_model_{model._head._id}"

        # compile definitions
        for n, jm in model._defs.items():
            self.compileOneJsonModel(jm, "$" + n, ["$" + n], False)
        # compile root
        self.compileOneJsonModel(model, "$", [], False)

        # compile other encountered references
        while todo := set(self._to_compile.keys()) - self._compiled:
            jm, gref = self._to_compile[min(todo)]
            self.compileOneJsonModel(jm, gref, [gref], True)

        # create entry_point
        self._code.sub(name, [
            self._lang.ret(self._lang.check_call(f"json_model_{model._id}", "val"))
        ], comment=f"entry function {name}"),

        return self._code


def xstatic_compile(
        model: JsonModel,
        name: str = "check_model",
        *,
        lang: str = "py",
        prefix: str = "_jm_",
        debug: bool = False,
        report: bool = True,
    ) -> SourceCode:
    """Generate the check source code for a model.

    - `model`: JSON Model root to compile.
    - `name`: target function name.
    - `lang`: name of target language.
    - `prefix`: prefix for generated functions
    - `report`: whether to generate code to report rejection reasons
    - `debug`: debugging mode generates more traces
    """
    # options
    if isinstance(model._model, dict) and "#" in model._model:
        comment = model._model["#"]
        assert isinstance(comment, str)
        loose_int = (True if "JSON_MODEL_LOOSE_INT" in comment else
                     False if "JSON_MODEL_STRICT_INT" in comment else
                     False)
        loose_float = (True if "JSON_MODEL_LOOSE_FLOAT" in comment else
                       False if "JSON_MODEL_STRICT_FLOAT" in comment else
                       False)
    # target language
    if lang == "py":
        from .python import Python
        language = Python(debug=debug)
    elif lang == "c":
        from .clang import CLangJansson
        language = CLangJansson(debug=debug)
    else:
        raise NotImplementedError(f"no support yet for language: {lang}")

    # cource code generator
    sc = SourceCode(model._globs, language, prefix=prefix, debug=debug, report=report)

    # generate
    code = sc.compileJsonModelHead(name, model)

    # debug and log.debug(f"code = {code}")
    return code
