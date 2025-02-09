# generate python source code for a model
#
# TODO
# - cache already compiled models!
# - optimize out redundant checks! (WIP)
# - check name override
# - generate error messages
#
# FIXME
# - Python is fuzzy about int/bool distinction, eg
#   - isinstance(True, int) is True
#   - True == 1 is True
#   as a consequence, some generated code may not provide the hoped answer

import json
import logging
import argparse
from typing import Any, Callable

from .utils import ModelType, ModelError, UnknownModel
from .utils import openfiles, split_object, model_in_models, all_model_type, constant_value
from .preproc import model_preprocessor
from .defines import Validator

log = logging.getLogger("sc")

Line = tuple[int, str]

# inlined predefs
_PREDEFS = {
    "ANY": lambda _v: "True",
    "NONE": lambda _v: "False",
    "NULL": lambda v: f"{v} is None",
    "BOOL": lambda v: f"isinstance({v}, bool)",
    "INTEGER": lambda v: f"isinstance({v}, int) and not isinstance({v}, bool)",
    "FLOAT": lambda v: f"isinstance({v}, float)",
    "STRING": lambda v: f"isinstance({v}, str)",
    "REGEX": lambda v: f"isinstance({v}, str)",  # TODO should be a valid regex
    # TODO more
}

# variable names in generated code
_RESULT = "result"
_VALUE = "value"
_PATH = "path"
_RE = "re2"

class Code():

    def __init__(self):
        self._code: list[Line] = []

    def add(self, indent: int, line: str):
        self._code.append((indent, line))

    def nl(self):
        self.add(0, "")

    def clear(self):
        self._code.clear()

    def __str__(self):
        return "\n".join(("    " * n + lc) for n, lc in self._code)


class SourceCode(Validator):

    def __init__(self, prefix: str = ""):

        # No actual compiler
        super().__init__()

        # global prefix
        self._prefix = prefix

        # identifiers and functions
        # ident-prefix -> next number to use to ensure unique identifiers
        self._nvars: dict[str, int] = {}
        # $-definitions -> function
        self._names: dict[str, str] = {}
        # /re.../ -> regex function
        self._regs: dict[str, str] = {}
        # model path -> function name
        self._paths: dict[str, str] = {}
        # already generated object paths
        self._generated: set[str] = set()
        #
        # generated stuff
        #
        self._defines: list[str] = []
        self._help: list[Code] = []
        self._maps: dict[str, dict[str, str]] = {}
        self._subs: list[Code] = []
        # initialization
        self.reset()

    def reset(self):
        # self._defs.clear()
        self._nvars.clear()
        self._names.clear()
        self._regs.clear()
        self._defines.clear()
        self._help.clear()
        self._maps.clear()
        self._subs.clear()
        self.define(f"import {_RE} as re")
        self.define("from typing import Any, Callable")
        self.define("")
        self.define("CheckFun = Callable[[Any, str], bool]")
        self.define("")

    # add contents
    def subs(self, code: Code):
        self._subs.append(code)

    def help(self, code: Code):
        self._help.append(code)

    def define(self, line: str):
        """Append a definition."""
        self._defines.append(line)

    def compile(self, name: str, model: ModelType):
        """Compile a model into name."""
        self._compileRoot(name, model)

    # show generated code
    def _map(self, mp: dict[str, str]) -> str:
        return "\n".join(f"    {self._esc(p)}: {v}," for p, v in mp.items())

    def __str__(self):
        """Generate check package."""
        return ("\n".join(self._defines) +
                "\n" +
                "\n".join(str(code) for code in self._help) + "\n" +
                "\n" +
                "\n".join(str(code) for code in self._subs) + "\n" +
                "\n" +
                "# object properties must and may maps\n" +
                "\n".join(f"{name} = {{\n{self._map(mp)}\n}}" for name, mp in self._maps.items()))

    # code generation
    def _ident(self, prefix: str, local: bool = False) -> str:
        if prefix not in self._nvars:
            self._nvars[prefix] = 0
        ident = f"{'' if local else self._prefix}{prefix}{self._nvars[prefix]}"
        self._nvars[prefix] += 1
        return ident

    def _regex(self, regex: str) -> str:
        if regex not in self._regs:
            self.define(f"# regex {self._esc(regex)}")
            if regex[-1] == "/":
                pattern = regex[1:-1]
                fun = self._ident("re_")
                self._regs[regex] = fun
                self.define(f"{fun} = re.compile({self._esc(pattern)}).search")
            elif regex.endswith("/i"):
                pattern = regex[1:-2]
                fun = self._ident("re_")
                self._regs[regex] = fun
                if _RE == "re2":
                    pattern = "(?i)" + pattern
                    self.define(f"{fun} = re.compile({self._esc(pattern)}).search")
                else:
                    self.define(f"{fun} = re.compile({self._esc(pattern)}, re.IGNORECASE).search")
            else:
                raise NotImplementedError("model = {regex}")
        return self._regs[regex]

    def _regExpr(self, regex: str, val: str):
        return f"{self._regex(regex)}({val}) is not None"

    def _esc(self, val: Any):
        # return '"' + string.translate({"\"": "\\\"", "\\": "\\\\"}) + '"'
        return json.dumps(val) if isinstance(val, str) else str(val)

    def _dollarExpr(self, name: str, val: str, vpath: str):
        if name in _PREDEFS:
            return _PREDEFS[name](val)
        else:
            fun = self._getName(name)
            return f"{fun}({val}, {vpath})"

    def _compileConstraint(self, code: Code, indent: int, model: ModelType, mpath: str,
                           res: str, val: str, vpath: str):
        assert isinstance(model, dict) and "@" in model
        self._compileModel(code, indent, model["@"], f"{mpath}.@", res, val, vpath)
        tmodel = self._ultimate_type(model["@"])
        # NOTE UnknownModel should raise an error on any constraint
        # FIXME None?
        assert tmodel in (int, float, str, list, dict, UnknownModel), f"simple {tmodel}"
        checks = []
        what = f"len({val})" if tmodel in (list, dict) else val
        twhat = int if tmodel in (list, dict) else tmodel
        for constraint in ("=", "!=", "<", "<=", ">", ">="):
            if constraint in model:
                op = "==" if constraint == "=" else constraint
                cst = model[constraint]
                if not isinstance(cst, (twhat, int)):
                    raise ModelError(f"invalid constant: {cst} ({twhat.__name__}) [{mpath}]")
                if isinstance(cst, int) and tmodel is str:
                    checks.append(f"len({val}) {op} {cst}")
                elif isinstance(cst, int) and tmodel == UnknownModel:
                    checks.append(f"(len({val}) {op} {cst} if isinstance({val}, (str, list, dict)) else " +
                                  f"{val} {op} {self._esc(cst) if isinstance(cst, str) else cst})")
                elif isinstance(cst, str):
                    checks.append(f"{what} {op} {self._esc(cst)}")
                else:  # same type or list or dict
                    checks.append(f"{what} {op} {cst}")
        if "!" in model:
            if not isinstance(model["!"], bool):
                raise ModelError(f"! constraint expects a boolean [{mpath}]")
            # FIXME partial implementation
            code.add(indent, f"{res} = {res} and len(set({val})) == len({val})")
            # raise NotImplementedError("! is not yet implemented")
        if checks:
            code.add(indent, f"{res} = {res} and {' and '.join(checks)}")

    def _disjunction(self, code: Code, indent: int, model: ModelType, mpath: str,
                     res: str, val: str, vpath: str) -> bool:
        """Generate optimized disjunction check.

        model: `{"|": [ o1, o2, ... ] }`
        """

        dis = self._disjunct_analyse(model, mpath)
        if dis is None:
            return False
        tag_name, tag_type, models, all_const_props = dis

        # Compile all object models in the list if needed
        init = model["|"]
        assert len(models) == len(init)
        for i, m in enumerate(models):
            p = f"{mpath}[{i}]"
            mi = init[i]  # initial model
            if isinstance(mi, str) and mi and mi[0] == "$":
                # it is a reference, it must be compiled for its name, no need to recompile it!
                fun = self._getName(mi[1:])
                if p not in self._paths:
                    # several path will lead to the same function
                    self._paths[p] = fun
                # else nothing to do?
            elif p not in self._paths:
                # else compile the direct object as a side effect…
                c = Code()
                self._compileModel(c, 0, m, p, _RESULT, _VALUE, _PATH)
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
            TAG_CHECKS[consts[tag_name]] = self._paths[f"{mpath}[{i}]"]

        self.define(f"{disid}: dict[Any, CheckFun]")
        self._maps[disid] = TAG_CHECKS
        esctag = self._esc(tag_name)

        # val is Object, tag is in val, tag_value is valid 
        code.add(indent, f"{res} = isinstance({val}, dict)")
        code.add(indent, f"if {res}:")
        code.add(indent+1, f"{res} = {esctag} in {val}")
        code.add(indent+1, f"if {res}:")
        code.add(indent+2, f"{tag} = {val}[{esctag}]")
        code.add(indent+2, f"if {tag} in {disid}:")
        code.add(indent+3, f"{res} = {disid}[{tag}]({val}, {vpath})")
        code.add(indent+2, "else:")
        code.add(indent+3, f"{res} = False")

        return True

    def _compileObject(self, code: Code, indent: int, model: ModelType, mpath: str,
                       oname: str, res: str, val: str, vpath: str):
        # separate properties
        must, may, defs, regs, oth = split_object(model, mpath)
        # TODO optimize must only case?
        code.add(indent, f"if not isinstance({val}, dict):")
        code.add(indent+1, "return False")
        if must:
            prop_must = f"{oname}_must"
            prop_must_map: dict[str, str] = {}
            self.define(f"{prop_must}: dict[str, CheckFun]")
            self._maps[prop_must] = prop_must_map
            for p, m in must.items():
                pid = f"{prop_must}_{p}"  # tmp unique identifier
                self.help(self._compileName(pid, m, f"{mpath}.{p}"))
                prop_must_map[p] = self._getName(pid)
        if may:
            prop_may = f"{oname}_may"
            prop_may_map: dict[str, str] = {}
            self.define(f"{prop_may}: dict[str, CheckFun]")
            self._maps[prop_may] = prop_may_map
            for p, m in may.items():
                pid = f"{prop_may}_{p}"
                self.help(self._compileName(pid, m, f"{mpath}.{p}"))
                prop_may_map[p] = self._getName(pid)
        # variables
        # prop = self._ident("p_", True)
        # value = self._ident("v_", True)
        # must_c = self._ident("mc_", True)
        prop, value, must_c = "prop", "model", "must_count"
        if must:
            code.add(indent, f"{must_c} = 0")
        code.add(indent, f"for {prop}, {value} in {val}.items():")
        code.add(indent+1, f"assert isinstance({prop}, str)")
        cond = "if"
        if must:
            code.add(indent+1, f"{cond} {prop} in {prop_must}:  # must")
            code.add(indent+2, f"{must_c} += 1")
            code.add(indent+2, f"if not {prop_must}[{prop}]({value}, f\"{{path}}.{{{prop}}}\"):")
            code.add(indent+3, "return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        if may:
            code.add(indent+1, f"{cond} {prop} in {prop_may}:  # may")
            code.add(indent+2, f"if not {prop_may}[{prop}]({value}, f\"{{path}}.{{{prop}}}\"):")
            code.add(indent+3, "return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # $* is inlined expr
        for d, v in defs.items():
            code.add(indent+1, f"{cond} {self._dollarExpr(d, prop, 'path')}:  # ${d}")
            self._compileModel(code, indent+2, v, f"{mpath}.{d}", res, value, vpath)
            code.add(indent+2, f"if not {res}: return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # // is inlined
        for r, v in regs.items():
            regex = f"/{r}/"
            code.add(indent+1, f"{cond} {self._regex(regex)}({prop}) is not None:  # {regex}")
            self._compileModel(code, indent+2, v, f"{mpath}.{regex}", res, value, vpath)
            code.add(indent+2, f"if not {res}: return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # catchall is inlined
        if oth:
            omodel = oth[""]
            if cond == "if":  # direct
                self._compileModel(code, indent+1, omodel, f"{mpath}.", res, value, vpath)
                code.add(indent+1, f"if not {res}: return False")
            else:
                code.add(indent+1, "else:  # catch all")
                self._compileModel(code, indent+2, omodel, f"{mpath}.", res, value, vpath)
                code.add(indent+2, f"if not {res}: return False")
                # code.add(indent+3, f"continue")
        else:
            if cond == "if":
                # we are expecting an empty object
                code.add(indent+1, "# no catch all")
                code.add(indent+1, "return False")
            else:
                code.add(indent+1, "else:  # no catch all")
                code.add(indent+2, "return False")
        # check that all must were seen
        if must:
            code.add(indent, f"return {must_c} == {len(must)}")
        else:
            code.add(indent, "return True")

    def _compileModel(self, code: Code, indent: int, model: ModelType, mpath: str,
                      res: str, val: str, vpath: str, known: set[str]|None = None, skip_dollar: bool = False):
        # known = expression already verified
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath} indent={indent}")
        code.add(indent, f"# {mpath}")
        if model is None:
            code.add(indent, f"{res} = {val} is None")
        elif isinstance(model, bool):
            code.add(indent, f"{res} = isinstance({val}, bool)")
        elif isinstance(model, int):
            expr = f"isinstance({val}, int) and not isinstance({val}, bool)"
            if known is not None:
                if expr in known:
                    expr = None
            if model == -1:
                if known is not None: 
                    known.add(expr)
                if not expr:
                    expr = "True"
            elif model == 0:
                if expr:
                    expr += f" and {val} >= 0"
                else:
                    expr = f"{val} >= 0"
            elif model == 1:
                if expr:
                    expr += f" and {val} >= 1"
                else:
                    expr = f"{val} >= 1"
            else:
                raise ModelError(f"unexpected int value {model} at {mpath}")
            if expr:
                code.add(indent, res + " = " + expr)
        elif isinstance(model, float):
            expr = f"isinstance({val}, float)"
            if known is not None:
                if expr in known:
                    expr = None
            if model == -1.0:
                if known is not None: 
                    known.add(expr)
                if not expr:
                    expr = "True"
            elif model == 0.0:
                if expr:
                    expr += f" and {val} >= 0.0"
                else:
                    expr = f"{val} >= 0.0"
            elif model == 1.0:
                if expr:
                    expr += f" and {val} >= 1.0"
                else:
                    expr = f"{val} >= 1.0"
            else:
                raise ModelError(f"unexpected float value {model} at {mpath}")
            if expr:
                code.add(indent, res + " = " + expr)
        elif isinstance(model, str):
            expr = f"isinstance({val}, str)"
            if known is not None:
                # Skip special cases
                if model == "" or model[0] not in ["$", "="]:
                    # log.info(f"expr={expr} known={known}")
                    if expr in known:
                        expr = None
            if model == "":
                if known is not None: 
                    known.add(expr)
                if expr:
                    code.add(indent, f"{res} = {expr}")
                else:
                    code.add(indent, f"{res} = True")
            elif model[0] == "_":
                if expr:
                    code.add(indent, f"{res} = {expr} and {val} == {self._esc(model[1:])}")
                else:
                    code.add(indent, f"{res} = {val} == {self._esc(model[1:])}")
            elif model[0] == "=":
                # TODO FIXME known
                (is_cst, value) = constant_value(model, mpath)
                if is_cst:
                    if value is None:
                        code.add(indent, f"{res} = {val} is None")
                    elif isinstance(value, bool):
                        code.add(indent, f"{res} = isinstance({val}, bool) and {val} == {value}")
                    elif isinstance(value, int):
                        code.add(indent, f"{res} = isinstance({val}, int) and not isinstance({val}, bool) and {val} == {value}")
                    elif isinstance(value, float):
                        code.add(indent, f"{res} = isinstance({val}, float) and {val} == {value}")
                    elif isinstance(value, str):
                        code.add(indent, f"{res} = isinstance({val}, str) and {val} == {value}")
                    else:
                        raise ModelError(f"unexpected constant type: {type(value).__name__}")
                else:
                    raise ModelError(f"unexpected constant: {model}")
            elif model[0] == "$":
                # TODO FIXME known
                code.add(indent, f"{res} = " + self._dollarExpr(model[1:], val, "path"))
            elif model[0] == "/":
                code.add(indent, f"# {self._esc(model)}")
                if expr:
                    code.add(indent, f"{res} = {expr} and {self._regExpr(model, val)}")
                else:
                    code.add(indent, f"{res} = {self._regExpr(model, val)}")
            else:  # simple string
                if expr:
                    code.add(indent, f"{res} = {expr} and {val} == {self._esc(model)}")
                else:
                    code.add(indent, f"{res} = {val} == {self._esc(model)}")
        elif isinstance(model, list):
            expr = f"isinstance({val}, list)"
            if known is not None:
                if expr in known:
                    expr = None
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
                code.add(indent+1, f"assert isinstance({val}, list)  # pyright helper")
                code.add(indent+1, f"for {idx}, {item} in enumerate({val}):")
                self._compileModel(code, indent+2, model[0], f"{mpath}[0]", res, item, f"f\"{{{vpath}}}[{{{idx}}}]\"")
                code.add(indent+2, f"if not {res}: break")
            else:
                if expr:
                    code.add(indent, f"{res} = {expr}")
                else:
                    code.add(indent, f"{res} = True")
                for i, m in enumerate(model):
                    code.add(indent+i, f"if {res}:")
                    # FIXME vpath
                    self._compileModel(code, indent+i+1, model[i], f"{mpath}[{i}]", res, f"{val}[{i}]", f"{vpath}[{i}]")
        elif isinstance(model, dict):
            assert "+" not in model, "merge must have been preprocessed"
            if "$" in model and not skip_dollar:
                name = model["$"]
                self.subs(self._compileName(name, model, mpath, skip_dollar=True))
                fun = self._getName(name)
                code.add(indent, f"{res} = {fun}({val}, path)")
                return
            if "@" in model:
                self._compileConstraint(code, indent, model, mpath, res, val, vpath)
            elif "|" in model:
                lpath = mpath + ".|"
                models = model["|"]
                # partial list of constants optimization
                l_const = list(map(lambda m: constant_value(m, lpath), models))
                if len(list(filter(lambda t: t[0], l_const))) >= 2:
                    constants, n_models = set(), []
                    for i in range(len(models)):
                        if l_const[i][0]:
                            constants.add(l_const[i][1])
                        else:
                            n_models.append(models[i])
                    code.add(indent, f"{res} = {val} in {constants}")
                    if not n_models:
                        return
                    code.add(indent, f"if not {res}:")
                    indent += 1
                    models = n_models
                # empty list
                if not models:
                    code.add(indent, f"{res} = False")
                    return
                # discriminant optimization
                if self._disjunction(code, indent, model, lpath, res, val, vpath):
                    return
                # homogeneous typed list
                same_type, expected_type = all_model_type(models, lpath)
                or_known = set()
                if same_type:
                    # all models have the same ultimate type
                    if expected_type is int:
                        type_test = f"isinstance({val}, int) and not isinstance({val}, bool)"
                    else:
                        type_test = f"isinstance({val}, {expected_type.__name__})"
                    code.add(indent, f"{res} = {type_test}")
                    code.add(indent, f"if {res}:")
                    indent += 1
                    or_known.add(type_test) 
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if not {res}:")
                    self._compileModel(code, indent+i, m, f"{lpath}[{i}]", res, val, vpath, or_known)
            elif "&" in model:
                and_known = set(known or [])
                lpath = mpath + ".&"
                models = model["&"]
                if not models:
                    code.add(indent, f"{res} = True")
                    return
                # homogeneous typed list
                same_type, expected_type = all_model_type(models, lpath)
                if same_type:
                    # all models have the same ultimate type
                    if expected_type is int:
                        type_test = f"isinstance({val}, int) and not isinstance({val}, bool)"
                    else:
                        type_test = f"isinstance({val}, {expected_type.__name__})"
                    code.add(indent, f"{res} = {type_test}")
                    code.add(indent, f"if {res}:")
                    indent += 1
                    and_known.add(type_test)
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if {res}:")
                    self._compileModel(code, indent+i, m, f"{lpath}[{i}]", res, val, vpath, and_known)
            elif "^" in model:
                lpath = mpath + ".^"
                models = model["^"]

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
                        self._compileModel(code, indent+i, m, f"{lpath}[{idx}]", "isin", val, vpath)
                        code.add(indent+i, f"{res} = not isin")                   
                        code.add(indent+i, f"if {res}:")

                    # update remaining models and identation
                    models = kept
                    models_i = kept_i
                    depth = len(dups)
                else:
                    models_i = list(range(len(models)))
                    depth = 0

                # standard case
                if not models:
                    code.add(indent+depth, f"{res} = False")
                elif len(models) == 1:
                    mod, idx = models[0], models_i[0]
                    self._compileModel(code, indent+depth, mod, f"{lpath}[{idx}]", res, val, vpath)
                else:  # several models are inlined
                    if len(models) == 2 and "$ANY" in models:
                        # get other model
                        m = models[1] if models[0] == "$ANY" else models[0]
                        is_m = self._ident("is_m_", True)
                        self._compileModel(code, indent+depth, m, f"{lpath}[?]", is_m, val, vpath)
                        code.add(indent+depth, f"{res} = not {is_m}")
                    else:
                        count = self._ident("xc_", True)
                        test = self._ident("xr_", True)
                        code.add(indent+depth, f"{count} = 0")
                        for i, m in enumerate(models):
                            idx = models_i[i]
                            code.add(indent+depth, f"if {count} <= 1:")
                            self._compileModel(code, indent+depth+1, m, f"{lpath}[{idx}]", test, val, vpath)
                            code.add(indent+depth+1, f"if {test}: {count} += 1")
                        code.add(indent+depth, f"{res} = {count} == 1")
            else:
                # TODO check for non-root %
                # TODO optimize empty model?
                # generate separate functions for objects?
                if mpath not in self._paths:
                    objid = self._ident("obj_")
                    self._paths[mpath] = objid
                else:
                    objid = self._paths[mpath]
                if mpath not in self._generated:
                    ocode = Code()
                    ocode.nl()
                    ocode.add(0, f"# object {mpath}")
                    path_init = " = \"$\"" if mpath == "$" else ""
                    ocode.add(0, f"def {objid}(value: Any, path: str{path_init}) -> bool:")
                    self._compileObject(ocode, 1, model, mpath, objid, _RESULT, _VALUE, _PATH)
                    self.subs(ocode)
                    self._generated.add(mpath)
                code.add(indent, f"{res} = {objid}({val}, {vpath})")
        else:
            raise ModelError(f"unexpected model type: {type(model).__name__}")

    def _getName(self, name: str) -> str:
        if name not in self._names:
            self._names[name] = self._ident("f_")
        log.debug(f"{name} -> {self._names[name]}")
        return self._names[name]

    def _compileName(self, name: str, model: ModelType, mpath: str, skip_dollar: bool=False) -> Code:
        log.debug(f"name: mpath={mpath} name={name}")
        code = Code()
        # keep definitions
        self._defs.set(name, model)
        fun2 = None
        if mpath in self._paths:
            fun = self._paths[mpath]
            if name in self._names:
                fun2 = self._names[name]
            else:
                self._names[name] = fun
        else:
            fun = self._getName(name)
            self._paths[mpath] = fun
        # generate code
        path_init = " = \"$\"" if mpath == "$" else ""
        code.nl()
        code.add(0, f"# define {self._esc(name)} ({mpath})")
        code.add(0, f"def {fun}(value: Any, path: str{path_init}) -> bool:")
        self._compileModel(code, 1, model, mpath, _RESULT, _VALUE, _PATH, None, skip_dollar)
        code.add(1, f"return {_RESULT}")
        if fun2 and fun2 != fun:
            code.nl()
            code.add(0, "# named root")
            code.add(0, f"{fun2} = {fun}")
        # NOTE yuk! the function may have been generated as a side effect of the previous call.
        # if so, this version is simply discarded
        if mpath not in self._generated:
            # on a named root, two names for the same path
            self._generated.add(mpath)
        else:
            code.clear()
        return code

    def _compileRoot(self, rname: str, model: ModelType):
        # compile definitions
        if isinstance(model, dict) and "%" in model:
            for name, mod in model["%"].items():
                self.subs(self._compileName(name, mod, f"$.%.{name}"))
        # compile root
        self.subs(self._compileName(rname, model, "$"))

_DEFAULT_NAME = "check_model"

DefFun = Callable[[str, str], None]
InitFun = Callable[[DefFun], None]

def static_compile(model: ModelType,
                   name: str = _DEFAULT_NAME,
                   prefix: str = "jmsc_",
                   init: InitFun|None = None,
                   re: str = "re") -> SourceCode:
    """Generate the check source code for a model."""
    global _RE
    _RE = re
    sc = SourceCode(prefix)
    rw_model = model_preprocessor(model, {}, "$")
    sc._names[name] = name
    if init:
        init(lambda n, m: sc._compileName(n, m, f"${n}"))
    sc.compile(name, rw_model)
    return sc

def static_compile_fun(model: ModelType, init: InitFun|None = None):
    """Generate a check function for a model."""
    code = str(static_compile(model, init=init))
    env = {}
    exec(code, env)
    assert _DEFAULT_NAME in env
    return env[_DEFAULT_NAME]

#
# Static JSON Model Compiler
#

def static_compiler():
    """Compile model file arguments."""

    logging.basicConfig()

    # handle script options and arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--debug", action="store_true")
    ap.add_argument("-p", "--prefix", type=str, default="jmsc_")
    ap.add_argument("-r", "--result", type=str, default="result")
    ap.add_argument("-v", "--value", type=str, default="value")
    ap.add_argument("--re", action="store_true")
    ap.add_argument("models", nargs="*")
    args = ap.parse_args()

    if args.debug:
        log.setLevel(logging.DEBUG)

    global _RESULT, _VALUE, _RE

    _RESULT = args.result
    _VALUE = args.value
    if args.re:
        _RE = "re"

    for fn, fh in openfiles(args.models):
        try:
            log.debug(f"model: {fn}")
            model = json.load(fh)
            print(static_compile(model, prefix=args.prefix, re=_RE))
        except Exception as e:
            log.error(f"{fn}: {e}")
            log.error(e, exc_info=True)

def static_compiler_check():
    """Compile one model and check values."""

    logging.basicConfig()

    # handle script options and arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--debug", action="store_true")
    ap.add_argument("model", type=str)
    ap.add_argument("jsons", nargs="*")
    args = ap.parse_args()

    if args.debug:
        log.setLevel(logging.DEBUG)

    log.debug(f"model: {args.model}")
    with open(args.model) as f:
        model = json.load(f)

    checker = static_compile_fun(model)

    for fn, fh in openfiles(args.jsons):
        try:
            value = json.load(fh)
            okay = checker(value)
            print(f"{fn}: {okay}")
        except Exception as e:
            log.error(f"{fn}: {e}")
            log.error(e, exc_info=True)
