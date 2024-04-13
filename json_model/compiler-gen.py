# generate python source code for a model

import sys
import re
import json
import logging

from utils import ModelType, ValueType, ModelError, openfiles

logging.basicConfig()
log = logging.getLogger("gen")
log.setLevel(logging.DEBUG)

Line = tuple[int, str]
Code = list[Line]

# TODO encode name if needed
_is_simple_name = re.compile(r"^[_a-zA-Z][_a-zA-Z0-9]*$").search

_PREDEFS = {
    "ANY": lambda _v: "True",
    "NONE": lambda _v: "False",
    "STRING": lambda v: f"isinstance({v}, str)",
}

class SourceCode():

    def __init__(self, model: ModelType):
        self._nvars: dict[str, int] = {}
        self._names: set[str] = set()
        self._model: ModelType = model
        self._code: Code = []
        self._compileRoot(model)

    def __str__(self):
        return "\n".join(("    " * line[0] + line[1]) for line in self._code)

    def var(self, prefix: str):
        if prefix not in self._nvars:
            self._nvars[prefix] = 0
        v = f"{prefix}{self._nvars[prefix]}"
        self._nvars[prefix] += 1
        return v

    def esc(self, string: str):
        return string.translate({"\"": "\\\"", "\\": "\\\\"})

    def line(self, indent: int, line: str):
        self._code.append((indent, line))

    def _compileModel(self, model: ModelType, res: str, val: str, indent: int, mpath: str):
        log.debug(f"model={model} res={res} val={val} indent={indent} mpath={mpath}")
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
                self.line(indent, f"{res} = " + expr)
            elif model[0] == "_":
                self.line(indent, f"{res} = " + expr + f" and {val} == {esc(model[1:])}")
            elif model[0] == "$":
                name = model[1:]
                if name in _PREDEFS:
                    self.line(indent, f"{res} = " + _PREDEFS[name](val))
                else:
                    self.line(indent, f"{res} = check_{name}({val}, path)")
            elif model[0] == "/":
                raise NotImplementedError("/ handling")
            else:  # simple string
                self.line(indent, f"{res} = " + expr + f" and {val} == \"{esc(model)}\"")
        elif isinstance(model, list):
            expr = f"isinstance({val}, list)"
            if len(model) == 0:
                expr += f" and len({val}) == 0"
            elif len(model) == 1:
                item = self.var("i")
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
                self._compile(m["@"], res, val, indent, mpath + ".@")
                # TODO constraints
                raise NotImplementedError("@ check")
            if "|" in model:
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
                # TODO separate properties
                raise NotImplementedError("obj check")
        else:
            raise ModelError(f"unexpected model type: {type(model).__name__}")

    def _compileName(self, name: str, model: ModelType, mpath: str):
        assert _is_simple_name(name)
        self.line(0, f"def check_{name}(value: ValueType, path: str) -> bool:")
        self._compileModel(model, "result", "value", 1, mpath)
        self.line(1, "return result")
        self.line(0, "")

    def _compileRoot(self, model: ModelType):
        if "%" in model:
            for name, mod in model.items():
                self._compileName(name, f"$.%.{name}")
        self._compileName("main", model, "$")
        
def compile(model: ModelType) -> SourceCode:
    return SourceCode(model)

for fn, fh in openfiles(sys.argv[1:]):
    try:
        model = json.load(fh)
        print(compile(model))
    except Exception as e:
        log.error(f"{fn}: {e}")        
