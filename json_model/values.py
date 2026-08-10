#
# Generate values from model
#
from .mtypes import ModelType, Jsonable

class UnsupportedValue(Exception):
    """No value could be generated for this model."""
    pass

def _simplest_scalar(model: ModelType) -> Jsonable:
    """Simplest value for a scalar type inference model."""
    match model:
        case None:
            return None
        case bool():
            if model is not True:
                raise UnsupportedValue(f"not a boolean scalar model: {model}")
            return False
        case int():
            if model not in (0, 1, -1):
                raise UnsupportedValue(f"not an integer scalar model: {model}")
            return 1 if model == 1 else 0
        case float():
            if model not in (0.0, 1.0, -1.0):
                raise UnsupportedValue(f"not a float scalar model: {model}")
            return 1.0 if model == 1.0 else 0.0
        case _:
            raise UnsupportedValue(f"not a scalar model: {model}")

def _simplest_string(model: str) -> Jsonable:
    """Simplest value for a string model."""
    if model == "":
        return ""
    raise UnsupportedValue(f"unsupported string model: {model}")

def simplest(model: ModelType) -> Jsonable:
    """Generate the simplest value matching a model."""
    match model:
        case None | bool() | int() | float():
            return _simplest_scalar(model)
        case str():
            return _simplest_string(model)
        case list():
            raise UnsupportedValue(f"unsupported array model: {model}")
        case dict():
            raise UnsupportedValue(f"unsupported object model: {model}")
        case _:
            raise UnsupportedValue(f"unexpected model: {model}")
