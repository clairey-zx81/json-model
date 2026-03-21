from .mtypes import ModelType, ModelPath, ModelError, ModelObject
from .mtypes import Jsonable, JsonObject, ValueType
from .model import JsonModel
from .utils import log, is_obj_model
from . import utils 

def normalizeModel(model: ModelType) -> ModelType:
    """Use canonical forms in some cases to simplify comparisons."""
    if model is None or isinstance(model, (bool, int, float)):
        return model
    elif isinstance(model, str):
        if model == "":
            return model
        elif model == "$STRING":
            # NOTE could also absorb some regex, but masking issue
            return ""
        elif model in ("$INT", "$INTEGER", "$I32", "$I64"):
            return -1
        elif model in ("$U32", "$U64"):
            return 0
        elif model in utils.FLOAT_MODEL_PREDEFS:
            return -1.0
        elif model in utils.BOOL_MODEL_PREDEFS:
            return True
        elif model in ("$NULL", "=null"):
            return None
        elif model[0] not in "$/=_":  # string constants
            return "_" + model
        else:
            return model
    elif isinstance(model, list):  # remove comments
        model = list(filter(lambda m: not is_comment(m), model))
        if model == [ "$NONE" ]:
            return []
        return model
    elif isinstance(model, dict):  # remove comments
        model = {p: v for p, v in model.items() if not is_comment(p)}
        return model
    else:
        raise ModelError(f"unexpected model type: {utils.tname(model)}")

def is_comment(model: ModelType) -> bool:
    """Tell whether model is a comment."""
    return isinstance(model, str) and model.startswith("#")

def is_prop(p: str) -> bool:
    """Is this a property spec inside a dict?"""
    return p == "" or p not in ("#", "~", "$", "%") and not p[0] == "#"

def is_bool(model: ModelType) -> bool:
    """Is it a boolean."""
    return (isinstance(model, bool) or
            isinstance(model, str) and model in ("=true", "=false"))

def structure(model: ModelType) -> str|None:
    """Return the structure."""
    if isinstance(model, dict):
        return (
            "&" if "&" in model else
            "|" if "|" in model else
            "^" if "^" in model else
            "+" if "+" in model else
            "@" if "@" in model else
            None
        )
    return None

# TODO memoize?
def is_submodel(jm: JsonModel, m1: ModelType, m2: ModelType) -> bool:
    """Tell whether m1 is a submodel of m2."""

    # log.debug(f"submodel: m1={m1} m2={m2}")

    # quick shortcut
    if m1 == m2 or m1 == "$NONE" or m2 == "$ANY":
        return True
    if m2 == "$NONE":
        return False

    # follow definitions
    if isinstance(m1, str) and m1.startswith("$") and m1 not in utils.MODEL_PREDEFS:
        m1 = jm.resolveRef(m1, [])._model
    if isinstance(m2, str) and m2.startswith("$") and m2 not in utils.MODEL_PREDEFS:
        m2 = jm.resolveRef(m2, [])._model
    # and normalize
    m1, m2 = normalizeModel(m1), normalizeModel(m2)

    # shortcut again
    if m1 == m2 or m1 == "$NONE" or m2 == "$ANY":
        return True
    if m2 == "$NONE":
        return False

    # per target type, simple cases first
    if m2 is None:
        return utils.is_null(m1)

    if isinstance(m2, bool):
        # NOTE equal constants have been dealt with the shortcut
        assert m2 == True
        return is_bool(m1)

    struc1 = structure(m1)
    if struc1 and struc1 in "&|^":
        # TODO check ^?
        return all(is_submodel(jm, m, m2) for m in m1[struc1] if not is_comment(m))
    if struc1 and struc1 == "@":
        # it is safe to ignore constraints
        return is_submodel(jm, m1["@"], m2)
    # struc1 may be "+", typed1 and t1 is dict

    typed1, t1 = utils.model_type(m1, [])
    const1, v1 = utils.constant_value(m1, [])

    if not typed1:
        return False

    if isinstance(m2, (int, float)):
        assert m2 in (-1, 0, 1, -1.0, 0.0, 1.0)
        typed2, t2 = utils.model_type(m2, [])
        assert typed2
        if isinstance(m1, (int, float)):
            assert m1 in (-1, 0, 1, -1.0, 0.0, 1.0)
            return m1 >= m2 if t1 is t2 else False
        elif const1:
            if t2 is int:
                if jm._loose_int and isinstance(v1, float) and v1 == int(v1):
                    v1 = int(v1)
                if m2 == -1:
                    return isinstance(v1, int)
                elif m2 == 0:
                    return isinstance(v1, int) and v1 >= 0
                else:
                    assert m2 == 1
                    return isinstance(v1, int) and v1 >= 1
            else:
                assert t2 is float
                if jm._loose_float and isinstance(v1, int):
                    v1 = float(v1)
                if m2 == -1.0:
                    return isinstance(v1, float)
                elif m2 == 0.0:
                    return isinstance(v1, float) and v1 >= 0.0
                else:
                    assert m2 == 1.0
                    return isinstance(v1, float) and v1 > 0.0
        # else no value to conclude
        # TODO handle constraints?
        return False

    if isinstance(m2, list):
        # NOTE inlined model comments have been removed
        if m2 == []:  # empty list
            return m1 == []
        if m2 == [ "$ANY" ]:  # list of anything
            return typed1 and t1 is list
        elif len(m2) == 1:  # list of something
            if typed1 and t1 is list:
                return all(is_submodel(jm, m, m2[0]) for m in m1)
            return False
        elif typed1 and t1 is list and len(m1) == len(m2):  # tuple
            return all(is_submodel(jm, i1, i2) for i1, i2 in zip(m1, m2))
        else:
            return False

    if isinstance(m2, dict):
        # structures
        struc2 = structure(m2)
        if struc2 and struc2 == "&":
            return all(is_submodel(jm, m1, m) for m in m2[struc2] if not is_comment(m))
        if struc2 and struc2 == "|":
            return any(is_submodel(jm, m1, m) for m in m2[struc2] if not is_comment(m))
        if struc2 and struc2 in "@+^":  # TODO improve in some cases?
            return False
        # m2 is an object
        if m2 == {"": "$ANY"}:
            return typed1 and t1 is dict
        if is_obj_model(m2, {"", "$", "%", "~"}):
            if "" in m2:  # {"": something}
                mv2 = m2[""]
                if typed1 and t1 is dict:
                    return all(is_submodel(jm, mv, mv2) for p, mv in m1.items() if is_prop(p))
            else:  # empty object
                return is_obj_model(m1, {"$", "%", "~"})
        # TODO improve
        return False

    if isinstance(m2, str): 
        if m2 == "":
            return typed1 and t1 is str
        if m2[0] == "_":
            return m1 == m2
        if m2[0] == "/":
            if typed1 and t1 is str and const1:
                assert isinstance(v1, str)
                try:
                    # FIXME extensions?
                    regex, opts = m2[1:].rsplit("/", 1)
                    if "i" in opts:
                        regex = "(?i)" + regex
                    return re.search(regex, v1) != None
                except Exception:
                    pass
            return False
        # predefs
        if m2[0] == "$":
            return False
        # other values
        assert m2[0] == "=", f"m2 is a scalar constant: {m2}"
        typed2, t2 = utils.model_type(m2, [])
        if typed2 and t1 is not t2:
            return False
        const2, v2 = utils.constant_value(m2, [])
        if const1 and const2:
            return v1 == v2
        return False
            
    raise ModelError(f"unexpected model type: {utils.tname(m2)}")
