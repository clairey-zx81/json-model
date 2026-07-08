#
# Generate typescript interface from model definitions
#

from .model import JsonModel
from .language import Block
from .mtypes import ModelType, JsonScalar, JsonArray, JsonObject, Number

def m2type(model: ModelType) -> str | None:
    if model is None:
        return "Null"
    if isinstance(model, bool):
        return "boolean"
    if isinstance(model, Number):
        return "number"
    if isinstance(model, str):
        return "string"
    return None

def m2ts(name: str, model: ModelType) -> Block:
    while isinstance(model, dict) and "@" in model:
        model = model["@"]
    

def model2tsinterface(model: JsonModel, root: str|None = "RootModel") -> Block:
    code: Block = [
        "console.log('Interface')"
    ]
    #for name, jm in model._defs.items():
    #    code += [""] + m2py(name, jm._model)
    #if root is not None:
    #    code += [""] + m2py(root, model._model)
    return code