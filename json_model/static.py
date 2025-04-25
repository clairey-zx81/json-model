# primitive python source code generation for a model
#
# TODO
# - language agnostic?
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

from typing import Any, Callable
import re
import json
import logging
import argparse

from .types import ModelType, ModelError, ModelPath, UnknownModel, JsonModel
from .utils import openfiles, split_object, model_in_models, all_model_type, constant_value, log, tname, json_path
from .preproc import model_preprocessor
from .defines import Validator

type Line = tuple[int, str]

# inlined predefs
_PREDEFS = {
    "ANY": lambda _v: "True",
    "NONE": lambda _v: "False",
    "NULL": lambda v: f"{v} is None",
    "BOOL": lambda v: f"isinstance({v}, bool)",
    "INTEGER": lambda v: f"isinstance({v}, int) and not isinstance({v}, bool)",
    "FLOAT": lambda v: f"isinstance({v}, float)",
    "NUMBER": lambda v: f"isinstance({v}, (float, int)) and not isinstance({v}, bool)",
    "STRING": lambda v: f"isinstance({v}, str)",
    "REGEX": lambda v: f"isinstance({v}, str)",  # TODO should be a valid regex
    # TODO more
}

# variable names in generated code?!
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
        return "\n".join(("    " * n + lc) for n, lc in self._code) + "\n"


class SourceCode(Validator):

    def __init__(self, model: JsonModel, prefix: str = ""):

        # No actual compiler
        super().__init__()

        # global prefix
        self._model = model
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
        self.define("from typing import Callable")
        self.define(f"import {_RE} as re")
        self.define("")
        self.define("type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]")
        self.define("type CheckFun = Callable[[Jsonable, str], bool]")
        self.define("type PropMap = dict[str, CheckFun]")
        self.define("type TagMap = dict[None|bool|float|int|str, CheckFun]")
        self.define("")

    # add contents
    def subs(self, code: Code):
        self._subs.append(code)

    def help(self, code: Code):
        self._help.append(code)

    def define(self, line: str):
        """Append a definition."""
        self._defines.append(line)

    # show generated code
    def _map(self, mp: dict[str, str]) -> str:
        return "\n".join(f"    {self._esc(p)}: {v}," for p, v in mp.items())

    def __str__(self):
        """Generate check package."""

        res = ""
        defs = "\n".join(self._defines)
        helps = "\n".join(map(str, self._help))
        subs = "\n".join(map(str, self._subs))
        maps = "\n".join(f"{name} = {{\n{self._map(mp)}\n}}" for name, mp in self._maps.items())

        if defs:
            res += defs
        if helps and re.search(r"\S", helps):
            res += ("\n" if res else "") + helps
        if subs and re.search(r"\S", subs):
            res += ("\n" if res else "") + subs
        if maps and re.search(r"\S", maps):
            res += ("\n" if res else "") + "# object properties maps\n" + maps + "\n"

        return res

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

    def _compileConstraint(self, code: Code, indent: int, model: ModelType, mpath: ModelPath,
                           res: str, val: str, vpath: str):
        assert isinstance(model, dict) and "@" in model
        self._compileModel(code, indent, model["@"], mpath + ["@"], res, val, vpath)
        tmodel = self._ultimate_type(self._model, model["@"])
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
            # FIXME partial implementation
            if model["!"]:
                code.add(indent, f"{res} &= len(set({val})) == len({val})")
            # else defaut is nothing to check
            # raise NotImplementedError("! is not yet implemented")
        if checks:
            code.add(indent, f"{res} &= {' and '.join(checks)}")

    def _disjunction(self, code: Code, indent: int, model: ModelType, mpath: ModelPath,
                     res: str, val: str, vpath: str) -> bool:
        """Generate optimized disjunction check.

        model: `{"|": [ o1, o2, ... ] }`
        """

        dis = self._disjunct_analyse(self._model, model, mpath)
        if dis is None:
            return False
        tag_name, tag_type, models, all_const_props = dis

        # Compile all object models in the list if needed
        assert isinstance(model, dict)

        init = model["|"]
        assert len(models) == len(init)
        for i, m in enumerate(models):
            p = mpath + [i]
            mi = init[i]  # initial model
            if isinstance(mi, str) and mi and mi[0] == "$":
                # it is a reference, it must be compiled for its name, no need to recompile it!
                fun = self._getName(mi[1:])
                if p not in self._paths:
                    # several path will lead to the same function
                    self._paths[p] = fun
                # else nothing to do?
            elif tuple(p) not in self._paths:
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
        code.add(indent, f"            {res} = False")

        return True

    def _compileObject(self, code: Code, indent: int, model: ModelType, mpath: ModelPath,
                       oname: str, res: str, val: str, vpath: str):
        # separate properties
        assert isinstance(model, dict)
        must, may, defs, regs, oth = split_object(model, mpath)
        # TODO optimize must only case?
        code.add(indent, f"if not isinstance({val}, dict):")
        code.add(indent + 1, "return False")
        prop_must = f"{oname}_must"
        if must:
            prop_must_map: dict[str, str] = {}
            self.define(f"{prop_must}: PropMap")
            self._maps[prop_must] = prop_must_map
            for p, m in must.items():
                pid = f"{prop_must}_{p}"  # tmp unique identifier
                self.help(self._compileName(pid, m, mpath + [p]))
                prop_must_map[p] = self._getName(pid)
        prop_may = f"{oname}_may"
        if may:
            prop_may_map: dict[str, str] = {}
            self.define(f"{prop_may}: PropMap")
            self._maps[prop_may] = prop_may_map
            for p, m in may.items():
                pid = f"{prop_may}_{p}"
                self.help(self._compileName(pid, m, mpath + [p]))
                prop_may_map[p] = self._getName(pid)
        # variables
        # prop = self._ident("p_", True)
        # value = self._ident("v_", True)
        # must_c = self._ident("mc_", True)
        prop, value, must_c = "prop", "model", "must_count"
        if must:
            code.add(indent, f"{must_c} = 0")
        code.add(indent, f"for {prop}, {value} in {val}.items():")
        code.add(indent, f"    assert isinstance({prop}, str)")
        cond = "if"
        if must:
            code.add(indent, f"    {cond} {prop} in {prop_must}:  # must")
            code.add(indent, f"        {must_c} += 1")
            code.add(indent, f"        if not {prop_must}[{prop}]({value}, "
                     f"f\"{{path}}.{{{prop}}}\"):")
            code.add(indent, r"            return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        if may:
            code.add(indent, f"    {cond} {prop} in {prop_may}:  # may")
            code.add(indent, f"        if not {prop_may}[{prop}]({value}, "
                     f"f\"{{path}}.{{{prop}}}\"):")
            code.add(indent, r"            return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # $* is inlined expr
        for d, v in defs.items():
            code.add(indent, f"    {cond} {self._dollarExpr(d, prop, 'path')}:  # ${d}")
            self._compileModel(code, indent + 2, v, mpath + [d], res, value, vpath)
            code.add(indent, f"        if not {res}: return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # // is inlined
        for r, v in regs.items():
            regex = f"/{r}/"
            code.add(indent, f"    {cond} {self._regex(regex)}({prop}) is not None:  # {regex}")
            self._compileModel(code, indent + 2, v, mpath + [regex], res, value, vpath)
            code.add(indent, f"        if not {res}: return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        # catchall is inlined
        if oth:
            omodel = oth[""]
            if cond == "if":  # direct
                self._compileModel(code, indent + 1, omodel, mpath + [""], res, value, vpath)
                code.add(indent, f"    if not {res}: return False")
            else:
                code.add(indent, r"    else:  # catch all")
                self._compileModel(code, indent + 2, omodel, mpath + [""], res, value, vpath)
                code.add(indent, f"        if not {res}: return False")
                # code.add(indent+3, f"continue")
        else:
            if cond == "if":
                # we are expecting an empty object
                code.add(indent, "    # no catch all")
                code.add(indent, "    return False")
            else:
                code.add(indent, "    else:  # no catch all")
                code.add(indent, "        return False")
        # check that all must were seen
        if must:
            code.add(indent, f"return {must_c} == {len(must)}")
        else:
            code.add(indent, "return True")

    def _compileModel(self, code: Code, indent: int, model: ModelType, mpath: ModelPath,
                      res: str, val: str, vpath: str, known: set[str]|None = None,
                      skip_dollar: bool = False):
        # known = expression already verified
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath} indent={indent}")
        assert isinstance(mpath, list)
        code.add(indent, f"# {json_path(mpath)}")
        match model:
            case None:
                code.add(indent, f"{res} = {val} is None")
            case bool():
                code.add(indent, f"{res} = isinstance({val}, bool)")
            case int():
                expr = f"isinstance({val}, int) and not isinstance({val}, bool)"
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
            case float():
                expr = f"isinstance({val}, float)"
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
                    if expr:
                        expr += f" and {val} >= 0.0"
                    else:
                        expr = f"{val} >= 0.0"
                elif model == 1.0:
                    if expr:
                        expr += f" and {val} > 0.0"
                    else:
                        expr = f"{val} > 0.0"
                else:
                    raise ModelError(f"unexpected float value {model} at {mpath}")
                if expr:
                    code.add(indent, res + " = " + expr)
            case str():
                expr = f"isinstance({val}, str)"
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
                    (a_cst, value) = constant_value(model, mpath)
                    if a_cst:
                        if value is None:
                            code.add(indent, f"{res} = {val} is None")
                        elif isinstance(value, bool):
                            code.add(indent, f"{res} = isinstance({val}, bool) and {val} == {value}")
                        elif isinstance(value, int):
                            code.add(indent,
                                     f"{res} = isinstance({val}, int) and "
                                     f"not isinstance({val}, bool) and {val} == {value}")
                        elif isinstance(value, float):
                            code.add(indent, f"{res} = isinstance({val}, float) and {val} == {value}")
                        elif isinstance(value, str):
                            code.add(indent, f"{res} = isinstance({val}, str) and {val} == {value}")
                        else:
                            raise ModelError(f"unexpected constant type: {tname(value)}")
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
            case list():
                expr = f"isinstance({val}, list)"
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
                    code.add(indent + 1, f"assert isinstance({val}, list)  # pyright helper")
                    code.add(indent + 1, f"for {idx}, {item} in enumerate({val}):")
                    self._compileModel(code, indent + 2, model[0],
                                       mpath + [0], res, item, f"f\"{{{vpath}}}[{{{idx}}}]\"")
                    code.add(indent + 2, f"if not {res}: break")
                else:
                    if expr:
                        code.add(indent, f"{res} = {expr} and len({val}) == {len(model)}")
                    else:
                        code.add(indent, f"{res} = len({val}) == {len(model)}")
                    for i, m in enumerate(model):
                        code.add(indent + i, f"if {res}:")
                        # FIXME vpath
                        self._compileModel(code, indent + i + 1, model[i],
                                           mpath + [i], res, f"{val}[{i}]", f"{vpath}[{i}]")
            case dict():
                assert "+" not in model, "merge must have been preprocessed"
                # if "$" in model and not skip_dollar:
                #     name = model["$"]
                #     self.subs(self._compileName(name, model, mpath, skip_dollar=True))
                #     fun = self._getName(name)
                #     code.add(indent, f"{res} = {fun}({val}, path)")
                #     return
                if "@" in model:
                    self._compileConstraint(code, indent, model, mpath, res, val, vpath)
                elif "|" in model:
                    lpath = mpath + ["|"]
                    models = model["|"]
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
                        code.add(indent, f"{res} = not isinstance({val}, (list, dict)) and {val} in {constants}")
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
                        self._compileModel(code, indent + i, m,
                                           lpath + [i], res, val, vpath, or_known)
                elif "&" in model:
                    and_known = set(known or [])
                    lpath = mpath + ["&"]
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
                        self._compileModel(code, indent + i, m,
                                           lpath + [i], res, val, vpath, and_known)
                elif "^" in model:
                    lpath = mpath + ["^"]
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
                            self._compileModel(code, indent + i, m,
                                               lpath + [idx], "isin", val, vpath)
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
                        self._compileModel(code, indent + depth, mod,
                                           lpath + [idx], res, val, vpath)
                    else:  # several models are inlined
                        if len(models) == 2 and "$ANY" in models:
                            # get other model
                            m = models[1] if models[0] == "$ANY" else models[0]
                            is_m = self._ident("is_m_", True)
                            self._compileModel(code, indent + depth, m,
                                               lpath + ["?"], is_m, val, vpath)
                            code.add(indent + depth, f"{res} = not {is_m}")
                        else:
                            count = self._ident("xc_", True)
                            test = self._ident("xr_", True)
                            code.add(indent + depth, f"{count} = 0")
                            for i, m in enumerate(models):
                                idx = models_i[i]
                                code.add(indent + depth, f"if {count} <= 1:")
                                self._compileModel(code, indent + depth + 1, m,
                                                   lpath + [idx], test, val, vpath)
                                code.add(indent + depth + 1, f"if {test}: {count} += 1")
                            code.add(indent + depth, f"{res} = {count} == 1")
                else:
                    # TODO check for non-root %
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
                        ocode.add(0, f"def {objid}(value: Jsonable, path: str{path_init}) -> bool:")
                        self._compileObject(ocode, 1, model, mpath, objid, _RESULT, _VALUE, _PATH)
                        self.subs(ocode)
                        self._generated.add(hpath)
                    del hpath
                    code.add(indent, f"{res} = {objid}({val}, {vpath})")
            case _:
                raise ModelError(f"unexpected model type: {tname(model)}")

    def _getName(self, name: str) -> str:
        if name not in self._names:
            self._names[name] = self._ident("f_")
        log.debug(f"{name} -> {self._names[name]}")
        return self._names[name]

    def _compileName(self, name: str, model: ModelType, mpath: ModelPath,
                     skip_dollar: bool = False) -> Code:
        log.debug(f"name: mpath={mpath} name={name}")
        code = Code()
        # keep definitions
        self._defs.set(name, model)
        fun2 = None
        hpath = tuple(mpath)
        if hpath in self._paths:
            fun = self._paths[hpath]
            if name in self._names:
                fun2 = self._names[name]
            else:
                self._names[name] = fun
        else:
            fun = self._getName(name)
            self._paths[hpath] = fun
        # generate code
        path_init = " = \"$\"" if mpath == ["$"] else ""
        code.nl()
        code.add(0, f"# define {self._esc(name)} ({json_path(mpath)})")
        code.add(0, f"def {fun}(value: Jsonable, path: str{path_init}) -> bool:")
        self._compileModel(code, 1, model, mpath, _RESULT, _VALUE, _PATH, None, skip_dollar)
        code.add(1, f"return {_RESULT}")
        if fun2 and fun2 != fun:
            code.nl()
            code.add(0, "# named root")
            code.add(0, f"{fun2} = {fun}")
        # NOTE yuk! the function may have been generated as a side effect of the previous call.
        # if so, this version is simply discarded
        if hpath not in self._generated:
            # on a named root, two names for the same path
            self._generated.add(hpath)
        else:
            code.clear()
        return code


_DEFAULT_NAME = "check_model"

DefFun = Callable[[str, str], Any]
InitFun = Callable[[DefFun], None]

def static_compile(
        model: JsonModel,
        name: str = _DEFAULT_NAME,
        prefix: str = "jmsc_",
        re: str = "re",
    ) -> SourceCode:
    """Generate the check source code for a model."""
    global _RE
    _RE = re
    sc = SourceCode(model, prefix)
    sc._names[name] = name
    if model._defs:
        for fn, jm in model._defs.items():
            sc.subs(sc._compileName(fn, jm._model, ["$", "$", fn]))
    sc.subs(sc._compileName(name, model._model, ["$"]))
    return sc
