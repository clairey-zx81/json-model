# experimental static (ecstatic?) compiler

from typing import Callable
import re
import json

from .mtypes import ModelType, ModelArray, ModelError, ModelPath, UnknownModel, Symbols, Jsonable
from .utils import split_object, model_in_models, all_model_type, constant_value
from .utils import log, tname, json_path
from .defines import Validator
from .model import JsonModel
from .language import Language, Code, Block, BoolExpr

_PREDEFS = {
    "$ANY", "$NONE", "$NULL", "$BOOL",
    "$INT", "$INTEGER", "$I32", "$I64", "$U32", "$U64",
    "$FLOAT", "$F32", "$F64", "$NUMBER",
    "$STRING", "$DATE", "$URL", "$REGEX", "$UUID",
}


class SourceCode(Validator):
    """Source code for compiling JSON Models.

    - globs: global map of symbols.
    - language: target language abstraction.
    - fname: entry function name.
    - prefix: use this prefix for file-level identifiers.
    - report: whether to report rejection reasons.
    - path: whether to keep track of value path while checking.
    - debug: verbose debug mode.
    """

    def __init__(self, globs: Symbols, language: Language, fname: str = "check_model", *,
                 prefix: str = "",
                 report: bool = True, path: bool = True, debug: bool = False):

        super().__init__()

        self._globs = globs
        self._lang = language
        self._prefix = prefix
        self._report = report
        self._path = path
        self._debug = debug

        self._code = Code(language, fname)

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
        # self._code.clear()
        self._names.clear()
        self._regs.clear()
        self._compiled.clear()
        self._to_compile.clear()

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
            fun = gen.ident(self._prefix + "re")
            self._code.regex(fun, pattern)

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
            return self._lang.predef(val, ref, vpath)
            # return (self._PREDEFS[ref](val, vpath) +
            #         (f" or _rep(f\"invalid {ref} at {{{vpath}}}\", rep)" if self._report else ""))
        else:
            fun = self._getNameRef(jm, ref, [])
            return self._lang.check_call(fun, val, vpath)

    def _compileConstraint(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                           res: str, val: str, vpath: str):

        # TODO make it a function?
        assert isinstance(model, dict) and "@" in model
        smpath = json_path(mpath)
        gen = self._lang

        # initial model check
        code: Block = self._compileModel(jm, model["@"], mpath + ["@"], res, val, vpath)

        # add constraints
        tmodel = self._ultimate_type(jm, model["@"])  # pyright: ignore

        # NOTE UnknownModel should raise an error on any constraint
        # FIXME see _untype00.model.json for multiple types

        assert tmodel in (int, float, str, list, dict, UnknownModel, None), f"simple {tmodel}"

        checks = []
        if tmodel == list:
            what = gen.arr_len(val)
        elif tmodel == dict:
            what = gen.obj_len(val)
        else:
            what = val

        # FIXME why None ?!
        twhat = int if tmodel in (list, dict, None) else tmodel

        # FIXME we must decide the type to do comparisons… or generate dynamic code.
        # TODO precise spec!

        for constraint in ("=", "!=", "<", "<=", ">", ">="):
            if constraint in model:
                op = "==" if constraint == "=" else constraint
                cst = model[constraint]
                if not isinstance(cst, (twhat, int)):
                    raise ModelError(f"invalid constant: {cst} ({twhat.__name__}) {mpath}")
                # TODO
                raise NotImplementedError("constraint not implemented")
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
                raise NotImplementedError("constraint not implemented")
                # TODO must be a list!
                log.warning("FIXME: ! generated code is not reliable")
                code.add(indent, f"{res} &= len(set({val})) == len({val})")
            # else defaut is nothing to check

        if checks:
            code += gen.iand_op(res, gen.and_op(checks))

        code += self._gen_report(res, f"invalid type or constraints [{smpath}]", vpath)

    def _disjunction(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                     res: str, val: str, vpath: str) -> Block|None:
        """Generate optimized disjunction check, return None if failed."""

        assert "|" in model and isinstance(model["|"], list)
        dis = self._disjunct_analyse(jm, model, mpath)  # pyright: ignore
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

        code += [ gen.bool_var(res, gen.is_obj(val)) ]

        # FIXME None tag value?!
        tag = self._lang.ident("tag")
        itag = gen.json_var(tag, gen.obj_prop_val(val, self._esc(tag_name)), True)

        fun = self._lang.ident("fun")
        ifun = gen.fun_var(fun, gen.get_cmap(cmap, tag, tag_type), True)
        icall = gen.bool_var(res, gen.check_call(fun, val, vpath))

        code += (
            gen.if_stmt(res,
                [ itag ] +
                gen.if_stmt(gen.is_def(tag),
                    [ ifun ] +
                    gen.if_stmt(gen.is_def(fun),
                        [ icall ],
                        [ gen.bool_var(res, gen.bool_cst(False)) ] +
                        gen.report(f"tag {tag_name} value not found [{smpath}]", vpath)),
                    [ gen.bool_var(res, gen.bool_cst(False)) ] +
                    gen.report(f"tag prop {tag_name} is missing [{smpath}]", vpath)),
                gen.report(f"value is not an object [{smpath}]", vpath))
        )

        return code

    def _gen_report(self, res: str, msg: str, path: str) -> Block:
        """Maybe enerate a report."""
        if self._report:
            gen = self._lang
            return gen.if_stmt(gen.not_op(res), gen.report(msg, path))
        else:
            return []

    def _gen_fail(self, msg: str, path: str) -> Block:
        """Generate a report and return false."""
        gen = self._lang
        return gen.report(msg, path) + [ gen.ret(gen.bool_cst(False)) ]

    def _gen_short_expr(self, expr: BoolExpr) -> Block:
        """Return immediately if expression is false."""
        gen = self._lang
        return gen.if_stmt(gen.not_op(expr), [ gen.ret(gen.bool_cst(False)) ])

    def _compileObject(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
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
        prop, pval, must_c, pfun = "prop", "pval", "must_count", "pfun"

        # should be an object
        code += gen.if_stmt(gen.not_op(gen.is_obj(val)),
                            self._gen_fail(f"not an object [{smpath}]", vpath))

        # shorcut for empty/any object
        if not must and not may and not defs and not regs:
            if not oth:  # empty object
                code += \
                    gen.if_stmt(gen.num_eq(gen.obj_len(val), gen.int_cst(0)),
                                [ gen.ret(bool_cst(True)) ],
                                self._gen_fail(f"expecting empty object [{smpath}]", vpath))
                return code
            elif oth == { "": "$ANY" }:  # any object (empty must/may/defs/regs)
                code += [ gen.lcom("accept any object"), gen.ret(gen.bool_cst(True)) ]
                return code
            # else cannot optimize early

        # path + [ prop ]
        lpath = gen.ident("lpath")
        lpath_ref = gen.path_lvar(lpath, vpath)

        # else we have some work to do!
        if defs or regs or oth:
            code += [ gen.bool_var(res, declare=True) ]
        if may or must:
            # we need a function pointer for simple properties
            code += [ gen.fun_var(pfun, declare=True) ]

        # build multi-if structure to put in prop/val loop
        if must:
            prop_must = f"{oname}_must"

            # must prop counter to check at the end if all were seen
            code += [ gen.int_var(must_c, gen.int_cst(0), True) ]

            prop_must_map: dict[str, str] = {}
            for p in sorted(must.keys()):
                m = must[p]
                pid = f"{prop_must}_{p}"  # tmp unique identifier
                self._compileName(jm, pid, m, mpath + [p], True)
                prop_must_map[p] = self._getName(jm, pid)

            self._code.pmap(prop_must, prop_must_map)

            mu_expr = gen.prop_fun(pfun, prop, prop_must)
            mu_code = (
                [ gen.lcom(f"handle {len(must)} must props") ] +
                gen.if_stmt(gen.is_def(pfun),
                    [ gen.inc_var(must_c) ] +
                    gen.if_stmt(gen.not_op(gen.check_call(pfun, pval, lpath_ref)),
                        self._gen_fail(f"invalid must property value [{smpath}]", lpath_ref)))
            )
            multi_if += [(mu_expr, mu_code)]

        if may:
            prop_may = f"{oname}_may"

            prop_may_map: dict[str, str] = {}
            for p in sorted(may.keys()):
                m = may[p]
                pid = f"{prop_may}_{p}"
                self._compileName(jm, pid, m, mpath + [p])
                prop_may_map[p] = self._getName(jm, pid)

            self._code.pmap(prop_may, prop_may_map)

            ma_expr = gen.prop_fun(pfun, prop, prop_may)
            ma_code = (
                [ gen.lcom("handle {len(may)} may props") ] +
                gen.if_stmt(gen.and_op(gen.is_def(pfun),
                                       gen.not_op(gen.check_call(pfun, pval, lpath_ref))),
                    self._gen_fail(f"invalid may property value [{smpath}]", lpath_ref))
            )
            multi_if += [(ma_expr, ma_code)]

        # $* is inlined expr (FIXME inlining does not work with vpath)
        for d, m in defs.keys():
            ref = "$" + d
            dl_expr = self._dollarExpr(jm, ref, prop, lpath_ref)  # FIXME lpath &lpath?
            dl_code = [ gen.lcom("handle {len(defs)} key props") ] + \
                self._compileModel(jm, m, mpath + [ref], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(dl_expr, dl_code)]

        # // is inlined
        for r, v in regs.items():
            # FIXME options?!
            regex = f"/{r}/"
            rg_expr = self._regExpr(regex, prop, vpath)  # FIXME lpath &lpath?
            rg_code = [ gen.lcom("handle {len(regs)} re props") ] + \
                self._compileModel(jm, v, mpath + [regex], res, pval, lpath_ref) + \
                self._gen_short_expr(res)
            multi_if += [(rg_expr, rg_code)]

        # catchall is inlined?
        ot_code: Block
        if oth:
            omodel = oth[""]
            smpath = json_path(mpath + [""])
            if omodel != "$ANY":
                ot_code = [ gen.lcom("handle other props") ] + \
                    self._compileModel(jm, omodel, mpath + [""], res, pval, lpath_ref) + \
                    self._gen_short_expr(res)
            else:  # optimized "": "$ANY" case
                ot_code = [ gen.lcom("accept any other props") ]
        else:  # no catch all
            smpath = json_path(mpath)
            ot_code = self._gen_fail(f"no other prop expected [{smpath}]", lpath_ref)

        code += gen.obj_loop(val, prop, pval,
            [ gen.path_var(lpath, gen.path_val(vpath, prop, True), True) ] +
            gen.mif_stmt(multi_if, ot_code))

        # check that all must were seen, although we do not know which ones
        if must:
            code += gen.if_stmt(gen.num_ne(must_c, gen.int_cst(len(must))),
                self._gen_fail(f"missing must prop [{smpath}]", vpath))

        # early returns so no need to look at res
        code += [ gen.ret(gen.bool_cst(True)) ]

        return code

    def _compileOr(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                   res: str, val: str, vpath: str, known: set[str]|None = None) -> Block:
        """Compile a or-list of models."""

        code = []
        gen = self._lang
        smpath = json_path(mpath)

        # direct empty list
        # NOTE in practice this case is optimized out so should not come here
        if not models:
            if self._report:
                code += [ gen.report(f"empty or [{smpath}]", vpath) ]
            code += [ gen.bool_val(res, gen.bool_cst(False)) ]
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
                code += [
                    gen.bool_var(res,
                                 gen.and_op(gen.is_scalar(val),
                                            gen.in_cset(sname, val, constants)))
                ]
                code += self._gen_report(res, f"value not in enum [{smpath}]", vpath)
                if not n_models:
                    return code
                models = n_models
                if not models:
                    # all constants were tested, we are done
                    return
                need_if = True

        # discriminant optimization for list of objects, None if fails
        tmp = {"|": models}
        if dcode := self._disjunction(jm, tmp, mpath, res, val, vpath):
            if need_if:
                return code + gen.if_stmt(gen.not_op(res), dcode)
            else:
                return code + dcode
            return

        # homogeneous typed list shortcut
        same, expected = all_model_type(models, mpath)
        or_known = set()
        or_code = []
        if same:
            # all models have the same ultimate type, type check shortcut
            type_test = gen.is_this_type(val, expected)
            or_known.add(type_test)
            or_code += [ gen.bool_var(res, type_test) ]
            or_code += self._gen_report(res, f"unexpected type at [{smpath}]", vpath)

        icode = []
        for i, m in reversed(list(enumerate(models))):
            body = self._compileModel(jm, m, mpath + [i], res, val, vpath, or_known) + icode
            if i > 0:
                icode = gen.if_stmt(gen.not_op(res), body)
            else:
                icode =  body

        icode += self._gen_report(res, f"no model matched [{smpath}]", vpath)

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
                    res: str, val: str, vpath: str, known: set[str]|None = None) -> Block:
        """Compile a xor-list of models."""

        assert isinstance(models, list)  # pyright hint
        gen = self._lang
        smpath = json_path(mpath)
        code = []

        raise NotImplementedError("TODO xor")

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
            self._compileModel(jm, mod, mpath + [idx], res, val, vpath)
        else:  # several models are inlined
            if len(models) == 2 and "$ANY" in models:
                # get other model
                m = models[1] if models[0] == "$ANY" else models[0]
                is_m = self._lang.ident("is_m_", True)
                # depth
                self._compileModel(jm, m, mpath + ["?"], is_m, val, vpath)
                code.add(indent + depth, f"{res} = not {is_m}")
            else:
                count = self._lang.ident("xc_")
                test = self._lang.ident("xr_")
                code.add(indent + depth, f"{count} = 0")
                for i, m in enumerate(models):
                    idx = models_i[i]
                    code.add(indent + depth, f"if {count} <= 1:")
                    # depth + 1
                    self._compileModel(jm, m, mpath + [idx], test, val, vpath)
                    code.add(indent + depth + 1, f"if {test}: {count} += 1")
                code.add(indent + depth, f"{res} = {count} == 1")

        code += self._gen_report(res, f"not one model match [{smpath}]", vpath)

        return code

    def _compileAnd(self, jm: JsonModel, models: ModelArray, mpath: ModelPath,
                    res: str, val: str, vpath: str, known: set[str]|None = None) -> Block:
        """Compile an and-list of models."""

        assert isinstance(models, list)  # pyright hint

        gen = self._lang
        and_known = set(known or [])
        smpath = json_path(mpath)
        code = []

        if not models:  # empty & list
            code += [ gen.bool_val(res, gen.bool_cst(True)) ]
            return

        # homogeneous typed list
        same, expected = all_model_type(models, mpath)
        if same:
            # all models have the same ultimate type, use a type shortcut
            type_test = gen.is_this_type(val, expected)
            code += [ gen.bool_var(res, type_test) ]
            and_known.add(type_test)
        else:
            code += [ gen.bool_var(res, gen.bool_cst(True)) ]

        # build in reverse order the if structure
        acode: Block = []
        for i, m in reversed(list(enumerate(models))):
            acode = gen.if_stmt(res,
                self._compileModel(jm, m, mpath + [i], res, val, vpath, and_known) +
                acode
            )
        code += acode
        code += self._gen_report(res, f"not all model match [{smpath}]", vpath)

        return code

    def _compileModel(self, jm: JsonModel, model: ModelType, mpath: ModelPath,
                      res: str, val: str, vpath: str, known: set[str]|None = None) -> Block:
        # TODO break each level into a separate function and let the compiler inline
        # known = expression already verified
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath}")
        assert isinstance(mpath, list)
        smpath = json_path(mpath)
        gen = self._lang
        known = known or set()

        code = [ gen.lcom(f"{json_path(mpath)}") ]
        match model:
            case None:
                code += [ gen.bool_var(res, gen.is_null(val)) ] + \
                    self._gen_report(res, f"not null [{smpath}]", vpath)
            case bool():
                code += [ gen.bool_var(res, gen.is_bool(val)) ] + \
                    self._gen_report(res, f"not a bool [{smpath}]", vpath)
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
                        expr = gen.bool_cst(True)
                elif model == 0:
                    compare = gen.num_ge(gen.int_val(val), gen.int_cst(0))
                    expr = gen.and_op(expr, compare) if expr else compare
                elif model == 1:
                    compare = gen.num_ge(gen.int_val(val), gen.int_cst(1))
                    expr = gen.and_op(expr, compare) if expr else compare
                else:
                    raise ModelError(f"unexpected int value {model} at {smpath}")
                if expr:
                    code += [ gen.bool_var(res, expr) ] + \
                        self._gen_report(res, f"not a {model} int [{smpath}]", vpath)
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
                    code += [ gen.bool_var(res, expr) ] + \
                        self._gen_report(res, f"not a {model} float [{smpath}]", vpath)
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
                    code += [ gen.bool_var(res, expr if expr else gen.bool_cst(True)) ]
                elif model[0] == "_":
                    compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += [ gen.bool_var(res, expr) ]
                elif model[0] == "=":
                    # TODO FIXME known
                    # NOTE expr is ignore here
                    (a_cst, value) = constant_value(model, mpath)
                    if not a_cst:
                        raise ModelError(f"unexpected constant: {model}")
                    if value is None:
                        code += [ gen.bool_var(res, gen.is_null(val)) ]
                    elif isinstance(value, bool):
                        ttest = gen.is_bool(val)
                        expr = gen.num_eq(gen.bool_val(val), gen.bool_cst(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += [ gen.bool_var(res, expr) ]
                    elif isinstance(value, int):
                        ttest = gen.is_int(val, jm._loose_int)
                        # FIXME cast depends on type?
                        expr = gen.num_eq(gen.int_val(val), gen.int_cst(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += [ gen.bool_var(res, expr) ]
                    elif isinstance(value, float):
                        ttest = gen.is_flt(val, jm._loose_float)
                        # FIXME cast depends on type? add loose parameter?
                        expr = gen.num_eq(gen.flt_val(val), gen.flt_cst(value))
                        if ttest not in known:
                            expr = gen.and_op(ttest, expr)
                        code += [ gen.bool_var(res, expr) ]
                    # elif isinstance(value, str):
                    #     compare = gen.str_eq(gen.str_val(val), gen.str_cst(model[1:]))
                    #     expr = gen.and_op(expr, compare) if expr else compare
                    #     code += [ gen.bool_var(res, expr) ]
                    else:
                        raise ModelError(f"unexpected constant type: {tname(value)}")
                elif model[0] == "$":
                    call = self._dollarExpr(jm, model, val, "path")
                    code += [ gen.bool_var(res, call) ]
                elif model[0] == "/":
                    code += [ gen.lcom(f"{self._esc(model)}") ]
                    call = self._regExpr(model, val, vpath)
                    code += [ gen.bool_var(res, gen.and_op(expr, call) if expr else call) ]
                else:  # simple string
                    compare = gen.str_eq(gen.str_val(val), gen.str_cst(model))
                    expr = gen.and_op(expr, compare) if expr else compare
                    code += [ gen.bool_var(res, expr) ]
                if self._report:
                    smodel = model if model else "string"
                    if model and model[0] == "/":  # FIXME workaround
                        smodel = "REGEX"
                    code += self._gen_report(res, f"unexpected {smodel} [{smpath}]", vpath)
            case list():
                expr = gen.is_arr(val)
                smpath = json_path(mpath)
                if known is not None:
                    if expr in known:
                        expr = None
                    if expr is not None:
                        known.add(expr)
                if len(model) == 0:
                    length = gen.num_eq(gen.arr_len(val), gen.int_cst(0))
                    expr = gen.and_op(expr, length) if expr else length
                    code += [ gen.bool_var(res, expr) ]
                    # SHORT RES?
                elif len(model) == 1:
                    if model[0] == "$ANY":
                        loop = [ gen.lcom("accept any array"), gen.nope() ]
                    else:
                        arrayid = gen.ident("arr")
                        idx, item, lpath = f"{arrayid}_idx", f"{arrayid}_item", f"{arrayid}_lpath"

                        loop = gen.arr_loop(val, idx, item, [
                            gen.path_var(lpath, gen.path_val(vpath, idx, False), True)
                        ] + self._compileModel(jm, model[0], mpath + [0],
                                               res, item, gen.path_lvar(lpath, vpath)) + \
                            gen.if_stmt(gen.not_op(res), [ gen.brk() ])
                        )

                    code += [ gen.bool_var(res, expr if expr else gen.bool_cst(True)) ] + \
                        gen.if_stmt(res, loop)
                else:
                    length = gen.num_eq(gen.arr_len(val), gen.int_cst(len(model)))
                    expr = gen.and_op(expr, length) if expr else length
                    code += [ gen.bool_var(res, expr) ]
                    lpath = gen.ident("lpath")
                    lpath_ref = gen.path_lvar(lpath, vpath)
                    # body = [ gen.path_var(lpath, declare=True) ]
                    body = []
                    for i, m in reversed(list(enumerate(model))):
                        body = gen.if_stmt(
                            res,
                            [ gen.path_var(lpath, gen.path_val(vpath, i, False), declare=True) ] +
                            # FIXME generated variable reference…
                            self._compileModel(
                                jm, model[i], mpath + [i],
                                res, gen.arr_item_val(val, i), lpath_ref) +
                            body)
                    code += body
                code += self._gen_report(res, f"not array or unexpected array [{smpath}]", vpath)
            case dict():
                assert isinstance(model, dict)  # pyright hint
                assert "+" not in model, "merge must have been preprocessed"
                if "@" in model:
                    code += self._compileConstraint(jm, model, mpath, res, val, vpath, known)
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
                        [ gen.lcom(f"object {json_path(mpath)}") ] +
                        gen.sub_fun(objid,
                            self._compileObject(jm, model, mpath, objid, "res", "val", "path"))
                    )
                    self._code.subs(ocode)

                    # call object check and possibly report
                    code += [ gen.bool_var(res, gen.check_call(objid, "val", vpath)) ]
                    code += self._gen_report(res, f"not an expected object at [{smpath}]", vpath)

                    # record object function for path
                    self._paths[tuple(mpath)] = objid
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

        body = self._compileModel(jm, model, mpath, "res", "val", "path", set())
        body = [ self._lang.bool_var("res", declare=True) ] + body + [ self._lang.ret("res") ]

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
            entries[n] = f"json_model_{jm._id}"
            self.compileOneJsonModel(jm, "$" + n, ["$" + n], False)

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
        debug: bool = False,
        report: bool = True,
    ) -> SourceCode:
    """Generate the check source code for a model.

    - model: JSON Model root to compile.
    - fname: target function name.
    - lang: name of target language.
    - prefix: prefix for generated functions
    - report: whether to generate code to report rejection reasons
    - debug: debugging mode generates more traces
    """
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
    sc = SourceCode(model._globs, language, fname, prefix=prefix, debug=debug, report=report)

    # generate
    code = sc.compileJsonModelHead(model)

    # debug and log.debug(f"code = {code}")
    return code
