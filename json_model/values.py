#
# Generate values from model
#
import re
import re._parser as _parser

from .mtypes import ModelType, ModelArray, Jsonable

_NUMBER_RE = re.compile(r"^=-?\d+(\.\d+)?([Ee][-+]?\d+)?$")
_CONSTANTS = {"=null": None, "=true": True, "=false": False}
_CATEGORIES = {
    _parser.CATEGORY_DIGIT: "0",
    _parser.CATEGORY_WORD: "a",
    _parser.CATEGORY_SPACE: " ",
}
_ANY_CHAR = "a"
_PREDEFS = {
    "$ANY": None, "$NULL": None,
    "$BOOL": False, "$BOOLEAN": False,
    "$INT": 0, "$INTEGER": 0, "$I32": 0, "$I64": 0, "$U32": 0, "$U64": 0,
    "$FLOAT": 0.0, "$F32": 0.0, "$F64": 0.0, "$NUMBER": 0,
    "$STRING": "", "$REGEX": "", "$EXREG": "", "$JSONPT": "",
    "$DATE": "1970-01-01", "$TIME": "00:00:00", "$TIMETZ": "00:00:00+00:00",
    "$DATETIME": "1970-01-01T00:00:00", "$DURATION": "PT0S",
    "$UUID": "00000000-0000-0000-0000-000000000000", "$CARD": "4111111111111111",
    "$IP4": "0.0.0.0", "$IP6": "::", "$HOST": "a", "$ETH": "00:00:00:00:00:00",
    "$URL": "http://a/", "$URI": "http://a/", "$URL_REL": "/", "$EMAIL": "a@b",
    "$JSON": "null", "$SEMVER": "0.0.0",
}

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

def _simplest_constant(model: str) -> Jsonable:
    """Simplest value for a scalar constant model."""
    if model in _CONSTANTS:
        return _CONSTANTS[model]
    if _NUMBER_RE.match(model) is None:
        raise UnsupportedValue(f"invalid scalar constant model: {model}")
    number = model[1:]
    return float(number) if any(c in number for c in ".eE") else int(number)

def _regex_char(item) -> str:
    """Simplest character for a regex character class item."""
    op, av = item
    if op is _parser.LITERAL:
        return chr(av)
    if op is _parser.RANGE:
        return chr(av[0])
    if op is _parser.CATEGORY and av in _CATEGORIES:
        return _CATEGORIES[av]
    raise UnsupportedValue(f"unsupported regex character class item: {op}")

def _regex_walk(pattern) -> str:
    """Simplest string matching a parsed regex."""
    value = ""
    for op, av in pattern:
        if op is _parser.LITERAL:
            value += chr(av)
        elif op is _parser.AT:
            pass
        elif op is _parser.ANY:
            value += _ANY_CHAR
        elif op is _parser.IN:
            value += _regex_char(av[0])
        elif op is _parser.MAX_REPEAT or op is _parser.MIN_REPEAT:
            repeat, _, body = av
            value += _regex_walk(body) * repeat
        elif op is _parser.BRANCH:
            value += _regex_walk(av[1][0])
        elif op is _parser.SUBPATTERN:
            value += _regex_walk(av[3])
        else:
            raise UnsupportedValue(f"unsupported regex construct: {op}")
    return value

def _simplest_regex(model: str) -> str:
    """Simplest value for a regex model."""
    if "/" not in model[1:]:
        raise UnsupportedValue(f"invalid regex model: {model}")
    pattern, opts = model[1:].rsplit("/", 1)
    if "X" in opts:
        raise UnsupportedValue(f"unsupported extended regex model: {model}")
    source = f"(?{opts}){pattern}" if opts else pattern
    try:
        parsed, compiled = _parser.parse(source), re.compile(source)
    except re.error as e:
        raise UnsupportedValue(f"invalid regex model {model}: {e}")
    value = _regex_walk(parsed)
    if compiled.search(value) is None:
        raise UnsupportedValue(f"no value generated for regex model: {model}")
    return value

def _simplest_predef(model: str) -> Jsonable:
    """Simplest value for a predefined model."""
    if model in _PREDEFS:
        return _PREDEFS[model]
    if model == "$NONE":
        raise UnsupportedValue("no value exists for model: $NONE")
    raise UnsupportedValue(f"unsupported predef or reference model: {model}")

def _simplest_array(model: ModelArray) -> Jsonable:
    """Simplest value for an array or tuple model."""
    items = [i for i in model if not (isinstance(i, str) and i.startswith("#"))]
    if len(items) <= 1:
        return []
    return [simplest(i) for i in items]

def _simplest_string(model: str) -> Jsonable:
    """Simplest value for a string model."""
    if model == "":
        return ""
    if model.startswith("_"):
        return model[1:]
    if model.startswith("="):
        return _simplest_constant(model)
    if model.startswith("/"):
        return _simplest_regex(model)
    if model.startswith("$"):
        return _simplest_predef(model)
    return model

def simplest(model: ModelType) -> Jsonable:
    """Generate the simplest value matching a model."""
    match model:
        case None | bool() | int() | float():
            return _simplest_scalar(model)
        case str():
            return _simplest_string(model)
        case list():
            return _simplest_array(model)
        case dict():
            raise UnsupportedValue(f"unsupported object model: {model}")
        case _:
            raise UnsupportedValue(f"unexpected model: {model}")
