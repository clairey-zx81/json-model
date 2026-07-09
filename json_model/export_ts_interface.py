#
# Generate typescript interface from model definitions
#

from .model import JsonModel
from .language import Block
from .mtypes import ModelType
from .predefs import INT_MODEL_PREDEFS, FLOAT_MODEL_PREDEFS, BOOL_MODEL_PREDEFS

def _unwrap(model: ModelType) -> ModelType:
    while isinstance(model, dict) and "@" in model:
        model = model["@"]
    return model

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

def field_type(name: str, model: ModelType) -> tuple[str, Block]:
    """Return (typescript type, hoisted interface blocks) for one field value."""
    model = _unwrap(model)
    if isinstance(model, dict):
        # object → hoist its own interface, reference it by name
        return name, m2ts(name, model) + [""]
    if isinstance(model, list):
        # strings starting with "#" are comments and are ignored
        cells = [c for c in model if not (isinstance(c, str) and c.startswith("#"))]
        if len(cells) == 1:
            # [X] → homogeneous array of any length
            t, extra = field_type(name, cells[0])
            return f"{t}[]", extra
        # [X, Y, ...] → tuple of fixed positional types (each cell named X_i)
        parts: list[str] = []
        hoisted: Block = []
        for i, cell in enumerate(cells):
            t, extra = field_type(f"{name}_{i}", cell)
            parts.append(t)
            hoisted += extra
        return "[" + ", ".join(parts) + "]", hoisted
    return m2type(model) or "any", []

def m2ts(name: str, model: ModelType) -> Block:
    model = _unwrap(model)
    code: Block = []
    if isinstance(model, dict):
        hoisted: Block = []
        code += [f"interface {name} {{"]
        for key, jm in model.items():
            optional = key.startswith("?")
            field = key[1:] if optional else key
            ftype, extra = field_type(f"{name}_{field}", jm)
            hoisted += extra
            code += [f"\t{field}{'?' if optional else ''}: {ftype}"]
        code += ["}"]
        code = hoisted + code
    else:
        mtype = m2type(model) or "any"
        code.append(f"type {name} = {mtype}")

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
