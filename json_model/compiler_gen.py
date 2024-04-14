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

from .utils import ModelType, ValueType, ModelError
from .utils import openfiles, split_object
from .preproc import _constant_value, model_preprocessor

logging.basicConfig()
log = logging.getLogger("gen")
# log.setLevel(logging.DEBUG)

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

    def __str__(self):
        return "\n".join(("    " * n + l) for n, l in self._code)

class SourceCode():

    def __init__(self, model: ModelType, prefix: str = ""):
        self._prefix = prefix
        self._model = model
        # keep track of generated identifiers
        self._nvars: dict[str, int] = {}
        self._names: dict[str, str] = {}
        self._regs: dict[str, str] = {}
        # generated stuff
        self._defs: list[str] = []
        self._help: list[Code] = []
        self._maps: dict[str, dict[str, str]] = {}
        self._subs: list[Code] = []
        # generate code
        self.define("import re")
        self.define("")
        self._compileRoot(model)

    def _map(self, mp: dict[str, str]) -> str:
        return "\n".join(f"    {self._esc(p)}: {v}," for p, v in mp.items())

    def __str__(self):
        """Generate check package."""
        return ("\n".join(self._defs) +
                "\n" +
                "\n".join(str(code) for code in self._help) + "\n" +
                "\n" +
                "# object properties must and may maps\n" +
                "\n".join(f"{name} = {{\n{self._map(mp)}\n}}" for name, mp in self._maps.items()) +
                "\n" +
                "\n".join(str(code) for code in self._subs) + "\n")

    def _ident(self, prefix: str, local: bool = False) -> str:
        if prefix not in self._nvars:
            self._nvars[prefix] = 0
        ident = f"{'' if local else self._prefix}{prefix}{self._nvars[prefix]}"
        self._nvars[prefix] += 1
        return ident

    def _regex(self, regex: str) -> str:
        if regex not in self._regs:
            if regex[-1] == "/":
                pattern = regex[1:-1]
                fun = self._ident("re_")
                self._regs[regex] = fun
                self.define(f"# regex {self._esc(regex)}")
                self.define(f"{fun} = re.compile({self._esc(pattern)}).search")
            else:
                # TODO /…/i
                raise NotImplementedError("model = {regex}")
        return self._regs[regex]

    def _regExpr(self, regex: str, val: str):
        return f"{self._regex(regex)}({val}) is not None"

    def _esc(self, string: str):
        # return '"' + string.translate({"\"": "\\\"", "\\": "\\\\"}) + '"'
        return json.dumps(string)

    def subs(self, code: Code):
        self._subs.append(code)

    def help(self, code: Code):
        self._help.append(code)

    def define(self, line: str):
        """Append a definition."""
        self._defs.append(line)

    def _dollarExpr(self, name: str, val: str, vpath: str):
        if name in _PREDEFS:
            return _PREDEFS[name](val)
        else:
            fun = self._getName(name)
            return f"{fun}({val}, {vpath})"

    def _compileModel(self, code: Code, model: ModelType, mpath: str,
                      res: str, val: str, vpath: str, indent: int,
                      skip_dollar: bool = False):
        log.debug(f"model={model} res={res} val={val} vpath={vpath} indent={indent} mpath={mpath}")
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
            elif len(model) == 1:
                idx = self._ident("idx_", True)
                item = self._ident("item_", True)
                code.add(indent, f"{res} = {expr}")
                code.add(indent, f"if {res}:")
                # TODO enumerate
                code.add(indent+1, f"for {idx}, {item} in enumerate({val}):")
                self._compileModel(code, model[0], f"{mpath}[0]", res, item, f"f\"{{{vpath}}}[{{{idx}}}]\"", indent+2)
                code.add(indent+2, f"if not {res}: break")
            else:
                raise NotImplementedError("tuple check")
        elif isinstance(model, dict):
            assert "+" not in model, "merge must have been preprocessed"
            if "@" in model:
                self._compileModel(code, model["@"], f"{mpath}.@", res, val, vpath, indent)
                # TODO constraints, needs the ultimate type…
                raise NotImplementedError("@ check")
            elif "|" in model:
                # TODO list of (string) constants optimization
                # TODO discriminant optimization
                lpath = mpath + ".|"
                models = model["|"]
                if all(map(lambda m: _constant_value(m, lpath)[0], models)):
                    # list of constants
                    constants = set(map(lambda m: _constant_value(m, lpath)[1], models))
                    code.add(indent, f"{res} = {val} in {constants}")
                    return
                if not models:
                    code.add(indent, f"{res} = False")
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if not {res}:")
                    self._compileModel(code, m, f"{lpath}[{i}]", res, val, vpath, indent + i)
            elif "&" in model:
                lpath = mpath + ".&"
                models = model["&"]
                if not models:
                    code.add(indent, f"{res} = True")
                for i, m in enumerate(models):
                    if i:
                        code.add(indent + i - 1, f"if {res}:")
                    self._compileModel(code, m, f"{lpath}[{i}]", res, val, vpath, indent + i)
            elif "^" in model:
                raise NotImplementedError("^ check")
            else:
                # TODO check for non-root %
                # TODO optimize empty model?
                # TODO generate separate functions for objects?
                if "$" in model and not skip_dollar:
                    name = model["$"]
                    self.subs(self._compileName(name, model, mpath, skip_dollar=True))
                    fun = self._getName(name)
                    code.add(indent, f"{res} = {fun}({val}, path)")
                    return
                # separate properties
                must, may, defs, regs, oth = split_object(model, mpath)
                prop_model: dict[str, str] = {}
                # compile property helpers
                if must:
                    prop_must = self._ident("pmu_")
                    prop_must_map: dict[str, str] = {}
                    self._maps[prop_must] = prop_must_map
                    for p, m in must.items():
                        pid = f"{prop_must}_{p}"  # tmp unique identifier
                        self.help(self._compileName(pid, m, f"{mpath}.{p}"))
                        prop_must_map[p] = self._getName(pid)
                if may:
                    prop_may = self._ident("pma_")
                    prop_may_map: dict[str, str] = {}
                    self._maps[prop_may] = prop_may_map
                    for p, m in may.items():
                        pid = f"{prop_may}_{p}"
                        self.help(self._compileName(pid, m, f"{mpath}.{p}"))
                        prop_may_map[p] = self._getName(pid)
                # WIP    
                code.add(indent, f"{res} = isinstance({val}, dict)")
                code.add(indent, f"if {res}:")
                # variables
                prop = self._ident("p_", True)
                value = self._ident("v_", True)
                must_c = self._ident("mc_", True)
                if must:
                    code.add(indent+1, f"{must_c} = 0")
                code.add(indent+1, f"for {prop}, {value} in {val}.items():")
                code.add(indent+2, f"{res} = isinstance({prop}, str)")
                code.add(indent+2, f"if not {res}: break")
                cond = "if"
                if must:
                    code.add(indent+2, f"{cond} {prop} in {prop_must}:  # must")
                    code.add(indent+3, f"{must_c} += 1")
                    code.add(indent+3, f"{res} = {prop_must}[{prop}]({value}, f\"{{path}}.{{{prop}}}\")")
                    code.add(indent+3, f"if not {res}: break")
                    # code.add(indent+3, f"continue")
                    cond = "elif"
                if may:
                    code.add(indent+2, f"{cond} {prop} in {prop_may}:  # may")
                    code.add(indent+3, f"{res} = {prop_may}[{prop}]({value}, f\"{{path}}.{{{prop}}}\")")
                    code.add(indent+3, f"if not {res}: break")
                    # code.add(indent+3, f"continue")
                    cond = "elif"
                # $* is inlined expr
                for d, v in defs.items():
                    code.add(indent+2, f"{cond} {self._dollarExpr(d, prop, 'path')}:  # ${d}")
                    self._compileModel(code, v, f"{mpath}.{d}", res, value, vpath, indent+3)
                    code.add(indent+3, f"if not {res}: break")
                    # code.add(indent+3, f"continue")
                    cond = "elif"
                # // is inlined
                for r, v in regs.items():
                    regex = f"/{r}/"
                    code.add(indent+2, f"{cond} {self._regex(regex)}({prop}) is not None:  # {regex}")
                    self._compileModel(code, v, f"{mpath}.{regex}", res, value, vpath, indent+3)
                    code.add(indent+3, f"if not {res}: break")
                    # code.add(indent+3, f"continue")
                    cond = "elif"
                # catchall is inlined
                if oth:
                    omodel = oth[""]
                    if cond == "if":  # direct
                        code._compileModel(code, omodel, f"{mpath}.", res, value, vpath, indent+2)
                        code.add(indent+2, f"if not {res}: break")
                        # code.add(indent+2, f"continue")
                    else:
                        code.add(indent+2, "else:  # catch all")
                        self._compileModel(code, omodel, f"{mpath}.", res, value, vpath, indent+3)
                        code.add(indent+3, f"if not {res}: break")
                        # code.add(indent+3, f"continue")
                else:
                    if cond == "if":
                        # we are expecting an empty object
                        code.add(indent+2, f"{res} = False")
                        code.add(indent+2, f"break")
                    else:
                        code.add(indent+2, "else:  # no catch all")
                        code.add(indent+3, f"{res} = False")
                        code.add(indent+3, f"break")
                # check that all must were seen
                if must:
                    code.add(indent+1, f"{res} = {res} and {must_c} == {len(must)}")
        else:
            raise ModelError(f"unexpected model type: {type(model).__name__}")

    def _getName(self, name: str) -> str:
        if name not in self._names:
            self._names[name] = self._ident("f_")
        log.debug(f"{name} -> {self._names[name]}")
        return self._names[name]

    def _compileName(self, name: str, model: ModelType, mpath: str, skip_dollar: bool=False) -> Code:
        fun = self._getName(name)
        code = Code()
        code.nl()
        code.add(0, f"# define {self._esc(name)}")
        code.add(0, f"def {fun}(value, path: str) -> bool:")
        self._compileModel(code, model, mpath, "result", "value", "path", 1, skip_dollar)
        code.add(1, "return result")
        return code

    def _compileRoot(self, model: ModelType):
        # compile definitions
        if "%" in model:
            for name, mod in model["%"].items():
                self.subs(self._compileName(name, mod, f"$.%.{name}"))
        # compile root
        self.subs(self._compileName("", model, "$"))
        
def static_compile(model: ModelType, name: str = "model_check") -> SourceCode:
    """Generate the check source code for a model."""
    rw_model = model_preprocessor(model, {}, "$")
    sc = SourceCode(rw_model, "jmsc_")
    fun = sc._names[""]
    code = Code()
    code.nl()
    code.add(0, f"# model {name}")
    code.add(0, f"def {name}(value):")
    code.add(1, f"return {fun}(value, \"$\")")
    sc.subs(code)
    return sc

def static_compile_fun(model: ModelType):
    """Generate a check function for a model."""
    code = str(static_compile(model))
    env = {}
    exec(code, env)
    assert "model_check" in env
    return env["model_check"]
