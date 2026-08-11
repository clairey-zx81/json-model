#
# Generate values from model
#
import re
import re._parser as _parser

from .mtypes import ModelType, ModelArray, ModelObject, Jsonable, ModelError
from .model import JsonModel
from .resolver import Resolver
from .predefs import MODEL_PREDEFS

_NUMBER_RE = re.compile(r"^=-?\d+(\.\d+)?([Ee][-+]?\d+)?$")
_CONSTANTS = {"=null": None, "=true": True, "=false": False}
_CATEGORIES = {
    _parser.CATEGORY_DIGIT: "0",
    _parser.CATEGORY_WORD: "a",
    _parser.CATEGORY_SPACE: " ",
}
_ANY_CHAR = "a"
_OPERATORS = {"@", "|", "&", "^", "+", "!", "=", "!=", "<", "<=", ">", ">="}
_ROOT_KEYS = {"$", "%", "~"}
_COMPARISONS = {"=", "!=", "<", "<=", ">", ">="}
_CONSTRAINTS = _COMPARISONS | {"!"}
_UINT_PREDEFS = {"$U32", "$U64"}
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

def _simplest_predef(model: str, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a predefined model or a reference."""
    if model in _PREDEFS:
        return _PREDEFS[model]
    if model == "$NONE":
        raise UnsupportedValue("no value exists for model: $NONE")
    if model in MODEL_PREDEFS:
        raise UnsupportedValue(f"unsupported predefined model: {model}")
    try:
        ja = jm.resolveRef(model, [])
    except (ModelError, AssertionError) as e:
        raise UnsupportedValue(f"cannot resolve {model}: {e}")
    if ja._url in seen:
        raise UnsupportedValue(f"no finite value for recursive model: {model}")
    return simplest(ja._model, ja, seen | {ja._url})

def _simplest_array(model: ModelArray, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for an array or tuple model."""
    items = [i for i in model if not (isinstance(i, str) and i.startswith("#"))]
    if len(items) <= 1:
        return []
    return [simplest(i, jm, seen) for i in items]

def _numeric_low(model: ModelType) -> int|float|None:
    """Smallest value allowed by a numeric model, None if unbounded below."""
    if isinstance(model, bool):
        return None
    if isinstance(model, (int, float)):
        return None if model in (-1, -1.0) else model
    if isinstance(model, str) and model in _UINT_PREDEFS:
        return 0
    return None

def _bounds(ops: ModelObject, step: int|float,
            low: int|float|None) -> tuple[int|float|None, int|float|None]:
    """Lower and upper bounds implied by comparison constraints."""
    lo, hi = low, None
    if "=" in ops:
        lo = hi = ops["="]
    if ">=" in ops:
        lo = ops[">="] if lo is None else max(lo, ops[">="])
    if ">" in ops:
        bound = ops[">"] + step
        lo = bound if lo is None else max(lo, bound)
    if "<=" in ops:
        hi = ops["<="] if hi is None else min(hi, ops["<="])
    if "<" in ops:
        bound = ops["<"] - step
        hi = bound if hi is None else min(hi, bound)
    return lo, hi

def _pick(lo: int|float|None, hi: int|float|None, ops: ModelObject,
          step: int|float, zero: int|float) -> int|float:
    """Simplest number within bounds, avoiding an excluded value."""
    value = zero
    if lo is not None and value < lo:
        value = lo
    if hi is not None and value > hi:
        value = hi
    if lo is not None and value < lo:
        raise UnsupportedValue(f"empty constraint range: {ops}")
    if "!=" in ops and value == ops["!="]:
        value += step
        if hi is not None and value > hi:
            value -= 2 * step
        if (lo is not None and value < lo) or (hi is not None and value > hi):
            raise UnsupportedValue(f"empty constraint range: {ops}")
    return value

def _simplest_constrained(props: ModelObject, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a constraint model."""
    target = props["@"]
    ops = {p: c for p, c in props.items() if p != "@"}
    if any(isinstance(c, str) for p, c in ops.items() if p in _COMPARISONS):
        raise UnsupportedValue(f"unsupported string comparison constraint: {ops}")
    unique = ops.get("!") is True
    base = simplest(target, jm, seen)
    if base is None or isinstance(base, bool) or isinstance(base, dict):
        raise UnsupportedValue(f"unsupported constrained model: {target}")
    if isinstance(base, (int, float)):
        if unique:
            raise UnsupportedValue(f"unique constraint on a number: {target}")
        is_float = isinstance(base, float)
        step: int|float = 1.0 if is_float else 1
        lo, hi = _bounds(ops, step, _numeric_low(target))
        value = _pick(lo, hi, ops, step, 0.0 if is_float else 0)
        return float(value) if is_float else int(value)
    lo, hi = _bounds(ops, 1, 0)
    if (lo is None or len(base) >= lo) and (hi is None or len(base) <= hi):
        return base
    length = int(_pick(lo, hi, ops, 1, 0))
    if isinstance(base, str):
        if target != "":
            raise UnsupportedValue(f"cannot resize string model: {target}")
        return _ANY_CHAR * length
    items = [i for i in target if not (isinstance(i, str) and i.startswith("#"))]
    if len(items) != 1:
        raise UnsupportedValue(f"cannot resize array model: {target}")
    if unique and length > 1:
        raise UnsupportedValue(f"unique constraint needs {length} distinct values: {target}")
    return [simplest(items[0], jm, seen)] * length

def _simplest_union(alts: ModelArray, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for the first alternative which yields one."""
    for alt in alts:
        if isinstance(alt, str) and alt.startswith("#"):
            continue
        try:
            return simplest(alt, jm, seen)
        except UnsupportedValue:
            pass
    raise UnsupportedValue(f"no alternative yields a value: {alts}")

def _simplest_object(model: ModelObject, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a simple object model or a bare target model."""
    props = {p: m for p, m in model.items() if not p.startswith("#")}
    if set(props) == {"|"}:
        return _simplest_union(props["|"], jm, seen)
    if "@" in props:
        others = set(props) - {"@"}
        if not others:
            return simplest(props["@"], jm, seen)
        if others <= _CONSTRAINTS:
            return _simplest_constrained(props, jm, seen)
    value: dict[str, Jsonable] = {}
    for prop, submodel in props.items():
        if prop in _OPERATORS:
            raise UnsupportedValue(f"unsupported object operator: {prop}")
        if prop in _ROOT_KEYS:
            raise UnsupportedValue(f"unsupported definitions or imports: {prop}")
        if prop == "" or prop.startswith(("?", "/", "$")):
            continue
        name = prop[1:] if prop.startswith(("!", "_")) else prop
        value[name] = simplest(submodel, jm, seen)
    return value

def _simplest_string(model: str, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
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
        return _simplest_predef(model, jm, seen)
    return model

def simplest(model: ModelType, jm: JsonModel|None = None,
             seen: frozenset[str] = frozenset()) -> Jsonable:
    """Generate the simplest value matching a model."""
    if jm is None:
        try:
            jm = JsonModel(model, Resolver())
        except (ModelError, AssertionError) as e:
            raise UnsupportedValue(f"invalid model: {e}")
        model = jm._model
    match model:
        case None | bool() | int() | float():
            return _simplest_scalar(model)
        case str():
            return _simplest_string(model, jm, seen)
        case list():
            return _simplest_array(model, jm, seen)
        case dict():
            return _simplest_object(model, jm, seen)
        case _:
            raise UnsupportedValue(f"unexpected model: {model}")
