#
# Generate typescript interface from model definitions
#

from .model import JsonModel
from .language import Block
from .mtypes import ModelType
from .predefs import INT_MODEL_PREDEFS, FLOAT_MODEL_PREDEFS, BOOL_MODEL_PREDEFS

def m2type(model: ModelType) -> str | None:
    global def_keys

    if model is None:
        return "null"
    if isinstance(model, bool):
        return "boolean"
    if isinstance(model, (int, float)):
        return "number"
    if isinstance(model, str):
        if len(model) > 0 and model[0] == "$":
            if model in BOOL_MODEL_PREDEFS:
                return "boolean"
            if model in INT_MODEL_PREDEFS | FLOAT_MODEL_PREDEFS:
                return "number"
            if model[1:] in def_keys:
                return model[1:]
        return "string"
    return None

def m2ts(name: str, model: ModelType) -> Block:
    while isinstance(model, dict) and "@" in model:
        model = model["@"]
    code: Block = []
    if isinstance(model, dict):
        hoisted: Block = []
        code += [f"interface {name} {{"]
        for key, jm in model.items():
            optional = key.startswith("?")
            field = key[1:] if optional else key

            child = jm
            while isinstance(child, dict) and "@" in child:
                child = child["@"]
            if isinstance(child, dict):
                nested = f"{name}_{field}"
                hoisted += m2ts(nested, child) + [""]
                ftype = nested
            else:
                ftype = m2type(child)
            code += [f"\t{field}{'?' if optional else ''}: {ftype}"]
        code += ["}"]
        code = hoisted + code
    elif isinstance(model, list):
        pass
    else:
        mtype = m2type(model)
        code.append(f"{name}: {mtype}")

    return code

def model2tsinterface(model: JsonModel, root: str|None = "RootModel") -> Block:
    code: Block = []
    global def_keys
    def_keys = model._defs.keys()
    for name, jm in model._defs.items():
        code = m2ts(name, jm._model) + code

    if root is not None:
        code = code + [""] + m2ts(root, model._model)

    return code
