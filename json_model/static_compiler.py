# generate python source code for a model
#
# TODO
# - check name override
# - optimize out redundant checks!
# - generate error messages
# - cache compiled models

import sys
import re
import json
import logging
import argparse
from typing import Any

from .utils import ModelType, ValueType, ModelError, UnknownModel
from .utils import openfiles, split_object
from .preproc import _constant_value, model_preprocessor
from .defines import Validator

# FIXME
logging.basicConfig()
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


class Code():

    def __init__(self):
        self._code: list[Line] = []

    def add(self, indent: int, line: str):
        self._code.append((indent, line))

    # def append(self, code: Code):
    #    self._code += code._code

    def nl(self):
        self.add(0, "")

    def clear(self):
        self._code.clear()

    def __str__(self):
        return "\n".join(("    " * n + l) for n, l in self._code)


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
        self._main: Code = Code()
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
        self.define("import re")
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
                "\n".join(f"{name} = {{\n{self._map(mp)}\n}}" for name, mp in self._maps.items()) +
                "\n" +
                str(self._main))

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
                if isinstance(cst, int) and tmodel == str:
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
        for i, m in enumerate(models):
            p = f"{mpath}[{i}]"
            if p not in self._paths:
                c = Code()
                self._compileModel(c, 0, m, p, "result", "value", "path")
                log.debug(f"{self._paths}")
                # NOTE object function generated as a side effect

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
        code.add(indent+2, f"else:")
        code.add(indent+3, f"{res} = False")

        return True

    def _compileObject(self, code: Code, indent: int, model: ModelType, mpath: str,
                       oname: str, res: str, val: str, vpath: str):
        # separate properties
        must, may, defs, regs, oth = split_object(model, mpath)
        # TODO optimize must only case?
        code.add(indent, f"if not isinstance({val}, dict):")
        code.add(indent+1, f"return False")
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
            code.add(indent+3, f"return False")
            # code.add(indent+3, f"continue")
            cond = "elif"
        if may:
            code.add(indent+1, f"{cond} {prop} in {prop_may}:  # may")
            code.add(indent+2, f"if not {prop_may}[{prop}]({value}, f\"{{path}}.{{{prop}}}\"):")
            code.add(indent+3, f"return False")
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
                code.add(indent+1, f"# no catch all")
                code.add(indent+1, f"return False")
            else:
                code.add(indent+1, "else:  # no catch all")
                code.add(indent+2, f"return False")
        # check that all must were seen
        if must:
            code.add(indent, f"return {must_c} == {len(must)}")
        else:
            code.add(indent, f"return True")

    def _compileModel(self, code: Code, indent: int, model: ModelType, mpath: str,
                      res: str, val: str, vpath: str, skip_dollar: bool = False):
        log.debug(f"mpath={mpath} model={model} res={res} val={val} vpath={vpath} indent={indent}")
        code.add(indent, f"# {mpath}")
        if model is None:
            code.add(indent, f"{res} = {val} is None")
        elif isinstance(model, bool):
            code.add(indent, f"{res} = isinstance({val}, bool)")
        elif isinstance(model, int):
            expr = f"isinstance({val}, int) and not isinstance({val}, bool)"
            if model == -1:
                pass
            elif model == 0:
                expr += f" and {val} >= 0"
            elif model == 1:
                expr += f" and {val} >= 1"
            else:
                raise ModelError(f"unexpected int value {model} at {mpath}")
            code.add(indent, res + " = " + expr)
        elif isinstance(model, int):
            expr = "isinstance({val}, int) and not isinstance({val}, bool)"
            if model == -1:
                pass
            elif model == 0:
                expr += f" and {val} >= 0"
            elif model == 1:
                expr += f" and {val} >= 1"
            else:
                raise ModelError(f"unexpected int value {model} at {mpath}")
            code.add(indent, res + " = " + expr)
        elif isinstance(model, float):
            expr = f"isinstance({val}, float)"
            if model == -1.0:
                pass
            elif model == 0.0:
                expr += f" and {val} >= 0.0"
            elif model == 1.0:
                expr += f" and {val} >= 1.0"
            else:
                raise ModelError(f"unexpected float value {model} at {mpath}")
            code.add(indent, res + " = " + expr)
        elif isinstance(model, str):
            expr = f"isinstance({val}, str)"
            if model == "":
                code.add(indent, f"{res} = {expr}")
            elif model[0] == "_":
                code.add(indent, f"{res} = {expr} and {val} == {self._esc(model[1:])}")
            elif model[0] == "=":
                (is_cst, value) = _constant_value(model, mpath)
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
                code.add(indent, f"{res} = " + self._dollarExpr(model[1:], val, "path"))
            elif model[0] == "/":
                code.add(indent, f"# {self._esc(model)}")
                code.add(indent, f"{res} = {expr} and {self._regExpr(model, val)}")
            else:  # simple string
                code.add(indent, f"{res} = {expr} and {val} == {self._esc(model)}")
        elif isinstance(model, list):
            expr = f"isinstance({val}, list)"
            if len(model) == 0:
                expr += f" and len({val}) == 0"
                code.add(indent, f"{res} = {expr}")
            elif len(model) == 1:
                idx = self._ident("idx_", True)
                item = self._ident("item_", True)
                code.add(indent, f"{res} = {expr}")
                code.add(indent, f"if {res}:")
                # TODO enumerate
                code.add(indent+1, f"for {idx}, {item} in enumerate({val}):")
                self._compileModel(code, indent+2, model[0], f"{mpath}[0]", res, item, f"f\"{{{vpath}}}[{{{idx}}}]\"")
                code.add(indent+2, f"if not {res}: break")
            else:
                code.add(indent, f"{res} = {expr}")
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
                # list of (string) constants optimization
                if all(map(lambda m: _constant_value(m, lpath)[0], models)):
                    # list of constants
                    constants = set(map(lambda m: _constant_value(m, lpath)[1], models))
                    code.add(indent, f"{res} = {val} in {constants}")
                    return
                # discriminant optimization
                if self._disjunction(code, indent, model, lpath, res, val, vpath):
                    return
                if not models:
                    code.add(indent, f"{res} = False")
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if not {res}:")
                    self._compileModel(code, indent+i, m, f"{lpath}[{i}]", res, val, vpath)
            elif "&" in model:
                lpath = mpath + ".&"
                models = model["&"]
                if not models:
                    code.add(indent, f"{res} = True")
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if {res}:")
                    self._compileModel(code, indent+i, m, f"{lpath}[{i}]", res, val, vpath)
            elif "^" in model:
                # TODO optimize out repeated models
                lpath = mpath + ".^"
                models = model["^"]
                if not models:
                    code.add(indent, f"{res} = False")
                elif len(models) == 1:
                    self._compileModel(code, ident, models[0], f"{lpath}[0]", res, val, vpath)
                else:  # several models are inlined
                    count = self._ident("xc_", True)
                    test = self._ident("xr_", True)
                    code.add(indent, f"{count} = 0")
                    for i, m in enumerate(models):
                        code.add(indent, f"if {count} <= 1:")
                        self._compileModel(code, indent+1, m, f"{lpath}[{i}]", test, val, vpath)
                        code.add(indent+1, f"if {test}: {count} += 1")
                    code.add(indent, f"{res} = {count} == 1")
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
                    ocode.add(0, f"def {objid}(value: Any, path: str) -> bool:")
                    self._compileObject(ocode, 1, model, mpath, objid, "result", "value", "path")
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
        code.nl()
        code.add(0, f"# define {self._esc(name)} ({mpath})")
        code.add(0, f"def {fun}(value: Any, path: str) -> bool:")
        self._compileModel(code, 1, model, mpath, "result", "value", "path", skip_dollar)
        code.add(1, "return result")
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

def static_compile(model: ModelType, name: str = _DEFAULT_NAME) -> SourceCode:
    """Generate the check source code for a model."""
    sc = SourceCode("jmsc_")
    rw_model = model_preprocessor(model, {}, "$")
    sc.compile("", rw_model)
    fun = sc._getName("")
    sc._main.nl()
    sc._main.add(0, f"def {name}(value) -> bool:")
    sc._main.add(1, f"return {fun}(value, \"$\")")
    return sc

def static_compile_fun(model: ModelType):
    """Generate a check function for a model."""
    code = str(static_compile(model))
    env = {}
    exec(code, env)
    assert _DEFAULT_NAME in env
    return env[_DEFAULT_NAME]

#
# Static JSON Model Compiler
#

def static_compiler():
    """Compile model file arguments."""

    # handle script options and arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--debug", action="store_true")
    ap.add_argument("models", nargs="*")
    args = ap.parse_args()

    if args.debug:
        log.setLevel(logging.DEBUG)

    for fn, fh in openfiles(args.models):
        try:
            log.debug(f"model: {fn}")
            model = json.load(fh)
            print(static_compile(model))
        except Exception as e:
            log.error(f"{fn}: {e}")
            log.error(e, exc_info=True)

def static_compiler_check():
    """Compile one model and check values."""

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
