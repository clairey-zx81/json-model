# generate python source code for a model
#
# TODO
# - check name override
# - optimize out redundant checks!

import sys
import re
import json
import logging

from .utils import ModelType, ValueType, ModelError, openfiles
from .preproc import _constant_value, model_preprocessor

logging.basicConfig()
log = logging.getLogger("gen")
# log.setLevel(logging.DEBUG)

Line = tuple[int, str]
Code = list[Line]

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
        self._code: Code = []
        # generate code
        self.define("import re")
        self.define("")
        self._compileRoot(model)

    def __str__(self):
        """Generate check package."""
        return ("\n".join(self._defs) +
                "\n" +
                "\n".join(("    " * line[0] + line[1]) for line in self._code))

    def _ident(self, prefix: str) -> str:
        if prefix not in self._nvars:
            self._nvars[prefix] = 0
        ident = f"{self._prefix}{prefix}{self._nvars[prefix]}"
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
                raise NotImplementedError("model = {regex}")
        return self._regs[regex]

    def _esc(self, string: str):
        # return '"' + string.translate({"\"": "\\\"", "\\": "\\\\"}) + '"'
        return json.dumps(string)

    def line(self, indent: int, line: str):
        """Append an indentend code line."""
        self._code.append((indent, line))

    def nl(self):
        """Append a newline to code."""
        self.line(0, "")

    def define(self, line: str):
        """Append a definition."""
        self._defs.append(line)

    def _compileModel(self, model: ModelType, res: str, val: str, indent: int, mpath: str, skip_dollar: bool = False):
        log.debug(f"model={model} res={res} val={val} indent={indent} mpath={mpath}")
        self.line(indent, f"# {mpath}")
        if model is None:
            self.line(indent, f"{res} = {val} is None")
        elif isinstance(model, bool):
            self.line(indent, f"{res} = isinstance({val}, bool)")
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
            self.line(indent, res + " = " + expr)
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
            self.line(indent, res + " = " + expr)
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
            self.line(indent, res + " = " + expr)
        elif isinstance(model, str):
            expr = f"isinstance({val}, str)"
            if model == "":
                self.line(indent, f"{res} = {expr}")
            elif model[0] == "_":
                self.line(indent, f"{res} = {expr} and {val} == {self._esc(model[1:])}")
            elif model[0] == "=":
                (is_cst, value) = _constant_value(model, mpath)
                if is_cst:
                    if value is None:
                        self.line(indent, f"{res} = {val} is None")
                    elif isinstance(value, bool):
                        self.line(indent, f"{res} = isinstance({val}, bool) and {val} == {value}")
                    elif isinstance(value, int):
                        self.line(indent, f"{res} = isinstance({val}, int) and not isinstance({val}, bool) and {val} == {value}")
                    elif isinstance(value, float):
                        self.line(indent, f"{res} = isinstance({val}, float) and {val} == {value}")
                    elif isinstance(value, str):
                        self.line(indent, f"{res} = isinstance({val}, str) and {val} == {value}")
                    else:
                        raise ModelError(f"unexpected constant type: {type(value).__name__}")
                else:
                    raise ModelError(f"unexpected constant: {model}")
            elif model[0] == "$":
                name = model[1:]
                if name in _PREDEFS:
                    self.line(indent, f"{res} = " + _PREDEFS[name](val))
                else:
                    fun = self._getName(name)
                    self.line(indent, f"# call {self._esc(model)}")
                    self.line(indent, f"{res} = {fun}({val}, path)")
            elif model[0] == "/":
                fun = self._regex(model)
                self.line(indent, f"# {self._esc(model)}")
                self.line(indent, f"{res} = {expr} and {fun}({val})")
            else:  # simple string
                self.line(indent, f"{res} = {expr} and {val} == {self._esc(model)}")
        elif isinstance(model, list):
            expr = f"isinstance({val}, list)"
            if len(model) == 0:
                expr += f" and len({val}) == 0"
            elif len(model) == 1:
                item = self._ident("i")
                self.line(indent, res + " = " + expr)
                self.line(indent, f"if {res}:")
                # TODO enumerate
                self.line(indent+1, f"for {item} in {val}:")
                self._compileModel(model[0], res, item, indent+2, mpath + "[0]")
                self.line(indent+2, f"if not {res}: break")
            else:
                raise NotImplementedError("tuple check")
        elif isinstance(model, dict):
            if "@" in model:
                self._compileModel(model["@"], res, val, indent, mpath + ".@")
                # TODO constraints
                raise NotImplementedError("@ check")
            elif "|" in model:
                # TODO discriminant optimization
                lpath = mpath + ".|"
                models = model["|"]
                if not models:
                    self.line(indent, f"{res} = False")
                for i, m in enumerate(models):
                    if i:
                        self.line(indent + i - 1, f"if not {res}:")
                    self._compileModel(m, res, val, indent + i, lpath + f"[{i}]")
            elif "&" in model:
                lpath = mpath + ".&"
                models = model["&"]
                if not models:
                    self.line(indent, f"{res} = True")
                for i, m in enumerate(models):
                    if i:
                        self.line(indent + i - 1, f"if {res}:")
                    self._compileModel(m, res, val, indent + i, lpath + f"[{i}]")
            elif "^" in model:
                raise NotImplementedError("^ check")
            else:
                # check for non-root %
                if "$" in model and not skip_dollar:
                    name = model["$"]
                    self._compileName(name, model, mpath, skip_dollar=True)
                    fun = self._getName(name)
                    self.line(indent, f"{res} = {fun}({val}, path)")
                    return
                # TODO separate properties
                raise NotImplementedError("obj check")
        else:
            raise ModelError(f"unexpected model type: {type(model).__name__}")

    def _getName(self, name: str) -> str:
        if name not in self._names:
            self._names[name] = self._ident("f_")
        return self._names[name]

    def _compileName(self, name: str, model: ModelType, mpath: str, skip_dollar: bool=False):
        fun = self._getName(name)
        self.nl()
        self.line(0, f"# define {self._esc(name)}")
        self.line(0, f"def {fun}(value: ValueType, path: str) -> bool:")
        self._compileModel(model, "result", "value", 1, mpath, skip_dollar)
        self.line(1, "return result")

    def _compileRoot(self, model: ModelType):
        # compile definitions
        if "%" in model:
            for name, mod in model["%"].items():
                self._compileName(name, mod, f"$.%.{name}")
        # compile root
        self._compileName("", model, "$")
        
def static_compile(model: ModelType, name: str = "model_check") -> SourceCode:
    rw_model = model_preprocessor(model, {}, "$")
    sc = SourceCode(rw_model, "jmsc_")
    fun = sc._names[""]
    sc.nl()
    sc.line(0, f"# model {name}")
    sc.line(0, f"def {name}(value):")
    sc.line(1, f"return {fun}(value, \"$\")")
    return sc
