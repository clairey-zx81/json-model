#
# Generate values from model
#
import copy
import datetime
import ipaddress
import json
import math
import re
import re._parser as _parser

from .mtypes import ModelType, ModelArray, ModelObject, Jsonable, ModelError
from .model import JsonModel
from .resolver import Resolver
from .objops import merge
from . import analyze, optim
from .predefs import MODEL_PREDEFS, PREDEFS
from .runtime.types import EntryCheckFun

_NUMBER_RE = re.compile(r"^=-?\d+(\.\d+)?([Ee][-+]?\d+)?$")
_JQ_NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
_MODEL_NAME_RE = re.compile(r"^[^\s\[\]'\"]+$")
_CONSTANTS = {"=null": None, "=true": True, "=false": False}
_CATEGORIES = {
    _parser.CATEGORY_DIGIT: "0",
    _parser.CATEGORY_WORD: "a",
    _parser.CATEGORY_SPACE: " ",
}
_ANY_CHAR = "a"
_NAME_CHARS = "abcdefghijklmnopqrstuvwxyz"
_ANY_NAME_PREDEFS = {"$ANY", "$STRING"}
_TYPE_PREDEFS = {
    "$NULL": {type(None)}, "$NONE": set(),
    "$BOOL": {bool}, "$BOOLEAN": {bool},
    "$INT": {int}, "$INTEGER": {int}, "$I32": {int}, "$I64": {int},
    "$U32": {int}, "$U64": {int},
    "$FLOAT": {float}, "$F32": {float}, "$F64": {float},
    "$NUMBER": {int, float},
}
_NO_NAME_PREDEFS = {
    "$NULL", "$NONE", "$BOOL", "$BOOLEAN", "$INT", "$INTEGER", "$I32", "$I64",
    "$U32", "$U64", "$FLOAT", "$F32", "$F64", "$NUMBER",
}
_DATE_RE = re.compile(r"\d{4}-\d{2}-\d{2}")
_UUID_RE = re.compile(r"[0-9a-fA-F]{8}(-[0-9a-fA-F]{4}){3}-[0-9a-fA-F]{12}")
_ETH_RE = re.compile(r"(?:[0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}")
_SEMVER_RE = re.compile(r"\d+\.\d+\.\d+(?:-[0-9A-Za-z.-]+)?(?:\+[0-9A-Za-z.-]+)?")
_CARD_RE = re.compile(r"\d{12,19}")
_DURATION_RE = re.compile(r"P(?!$)(\d+Y)?(\d+M)?(\d+D)?(T(?!$)(\d+H)?(\d+M)?(\d+(\.\d+)?S)?)?")
_JSONPT_RE = re.compile(r"(/([^/~]|~[01])*)*")
_OPERATORS = {"@", "|", "&", "^", "!", "=", "!=", "<", "<=", ">", ">="}
_QUOTED_OPS = _OPERATORS - {"@"}
_ROOT_KEYS = {"$", "%", "~"}
_COMPARISONS = {"=", "!=", "<", "<=", ">", ">="}
_CONSTRAINTS = _COMPARISONS | {"!"}
_BREAKING = {
    "=": lambda m, b: m != b, "!=": lambda m, b: m == b,
    "<": lambda m, b: m >= b, "<=": lambda m, b: m > b,
    ">": lambda m, b: m <= b, ">=": lambda m, b: m < b,
}
_INT_VIOLATIONS = {
    ">=": lambda n: math.ceil(n) - 1, ">": lambda n: math.floor(n),
    "<=": lambda n: math.floor(n) + 1, "<": lambda n: math.ceil(n),
    "=": lambda n: math.floor(n) + 1, "!=": lambda n: n,
}
_FLOAT_VIOLATIONS = {
    ">=": lambda n: n - 1.0, ">": lambda n: float(n),
    "<=": lambda n: n + 1.0, "<": lambda n: float(n),
    "=": lambda n: n + 1.0, "!=": lambda n: float(n),
}
_INT_BOUNDS = {
    ">=": lambda n: math.ceil(n), ">": lambda n: math.floor(n) + 1,
    "<=": lambda n: math.floor(n), "<": lambda n: math.ceil(n) - 1,
    "=": lambda n: math.floor(n), "!=": lambda n: math.floor(n) + 1,
}
_INT_MIRRORS = {"!=": lambda n: math.floor(n) - 1}
_FLOAT_BOUNDS = {
    ">=": lambda n: float(n), "<=": lambda n: float(n), "=": lambda n: float(n),
}
_TYPE_VIOLATIONS = [None, True, 0, "", [], {}]
_ROOT_TYPES = [None, True, False, -42, 3.14, "", "abc", [], [1], {}]
_EXTRA_NAMES = ["no-such-prop", "no-such-property", "no-such-property1"]
_UINT_PREDEFS = {"$U32", "$U64"}
_PREDEFS = {
    "$ANY": {}, "$NULL": None,
    "$BOOL": False, "$BOOLEAN": False,
    "$INT": 0, "$INTEGER": 0, "$I32": 0, "$I64": 0, "$U32": 0, "$U64": 0,
    "$FLOAT": 0.0, "$F32": 0.0, "$F64": 0.0, "$NUMBER": 0,
    "$STRING": "", "$REGEX": "", "$EXREG": "", "$JSONPT": "",
    "$DATE": "1970-01-01", "$TIME": "00:00:00", "$TIMETZ": "00:00:00+00:00",
    "$DATETIME": "1970-01-01T00:00:00", "$DURATION": "PT0S",
    "$UUID": "00000000-0000-0000-0000-000000000000", "$CARD": "4111111111111111",
    "$IP4": "0.0.0.0", "$IP6": "::", "$HOST": "json-model.org",
    "$ETH": "00:00:00:00:00:00",
    "$URL": "https://json-model.org/", "$URI": "https://json-model.org/",
    "$URL_REL": "/", "$EMAIL": "susie@json-model.org",
    "$JSON": "null", "$SEMVER": "0.0.0",
}

_PREDEF_VIOLATIONS = {
    "$U32": -1, "$U64": -1,
    "$REGEX": "[", "$EXREG": "[", "$JSONPT": "a",
    "$DATE": "1970-13-45", "$TIME": "25:00:00", "$TIMETZ": "00:00:00",
    "$DATETIME": "1970-01-01T25:00:00", "$DURATION": "P",
    "$UUID": "00000000-0000-0000-0000-00000000000", "$CARD": "411111111111111",
    "$IP4": "256.0.0.1", "$IP6": "xyz::", "$HOST": "json model.org",
    "$ETH": "00:00:00:00:00",
    "$URL": "https://json model.org/", "$URI": "https://json model.org/",
    "$URL_REL": "http://[bad", "$EMAIL": "susie@@json-model.org",
    "$JSON": "{", "$SEMVER": "0.0",
}

class UnsupportedValue(Exception):
    """No value could be generated for this model."""
    pass

class Vacuous(UnsupportedValue):
    """The model is inherently empty or holds no constraint."""
    pass

def _brief(model: ModelType, size: int = 60) -> str:
    """Short readable rendering of a model, for failure messages."""
    text = repr(model)
    return text if len(text) <= size else text[:size] + "..."

def _joined(reasons: list[str], limit: int = 8) -> str:
    """Distinct failure reasons, capped for readability."""
    kept = list(dict.fromkeys(reasons))
    text = "; ".join(kept[:limit])
    return text if len(kept) <= limit else f"{text}; and {len(kept) - limit} more"

def _simplest_scalar(model: ModelType) -> Jsonable:
    """Simplest value for a scalar type inference model."""
    match model:
        case None:
            return None
        case bool():
            return False
        case int():
            return 1 if model == 1 else 0
        case float():
            return 1.0 if model == 1.0 else 0.0
        case _:
            raise UnsupportedValue(f"not a scalar model: {model}")

def _simplest_constant(model: str) -> Jsonable:
    """Simplest value for a scalar constant model."""
    if model in _CONSTANTS:
        return _CONSTANTS[model]
    elif _NUMBER_RE.match(model) is None:
        raise UnsupportedValue(f"invalid scalar constant model: {model}")
    else:
        number = model[1:]
        return float(number) if any(c in number for c in ".eE") else int(number)

def _regex_char(item) -> str:
    """Simplest character for a regex character class item."""
    op, av = item
    if op is _parser.LITERAL:
        return chr(av)
    elif op is _parser.RANGE:
        return chr(av[0])
    elif op is _parser.CATEGORY and av in _CATEGORIES:
        return _CATEGORIES[av]
    else:
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
    else:
        return value

def _simplest_predef(model: str, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a predefined model or a reference."""
    if model in _PREDEFS:
        value = _PREDEFS[model]
        return copy.copy(value) if isinstance(value, (dict, list)) else value
    elif model == "$NONE":
        raise Vacuous("no value exists for model: $NONE")
    elif model in MODEL_PREDEFS:
        raise UnsupportedValue(f"unsupported predefined model: {model}")
    else:
        try:
            ja = jm.resolveRef(model, [])
        except (ModelError, AssertionError) as e:
            raise UnsupportedValue(f"cannot resolve {model}: {e}")
        if ja._url in seen:
            raise UnsupportedValue(f"no finite value for recursive model: {model}")
        else:
            return simplest(ja._model, ja, seen | {ja._url})

def _simplest_array(model: ModelArray, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for an array or tuple model."""
    items = [(i, m) for i, m in enumerate(model)
             if not (isinstance(m, str) and m.startswith("#"))]
    if len(items) <= 1:
        return []
    values: list[Jsonable] = []
    for index, item in items:
        try:
            values.append(simplest(item, jm, seen))
        except UnsupportedValue as e:
            raise type(e)(f"{index}: {e}")
    return values

def _numeric_low(model: ModelType) -> int|float|None:
    """Smallest value allowed by a numeric model, None if unbounded below."""
    if isinstance(model, bool):
        return None
    elif isinstance(model, (int, float)):
        return None if model in (-1, -1.0) else model
    elif isinstance(model, str) and model in _UINT_PREDEFS:
        return 0
    else:
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

def _variants(model: ModelType, jm: JsonModel, seen: frozenset[str],
              count: int) -> list[Jsonable]:
    """Distinct values matching a model, simplest first, at most count of them."""
    values: list[Jsonable]
    if model is None:
        values = [None]
    elif isinstance(model, bool):
        values = [False, True]
    elif isinstance(model, (int, float)):
        one: int|float = 1.0 if isinstance(model, float) else 1
        if model in (1, 1.0):
            values = [one * i for i in range(1, count + 1)]
        elif model in (0, 0.0):
            values = [one * i for i in range(count)]
        else:
            values = [one * 0]
            step = one
            while len(values) < count:
                values.append(step)
                values.append(-step)
                step += one
    elif model == "":
        values = [_ANY_CHAR * i for i in range(count)]
    elif isinstance(model, str) and not model.startswith(("/", "$")):
        values = [_simplest_string(model, jm, seen)]
    elif model == "$ANY":
        values = [{}, None, False, True, 0, "", []]
    elif isinstance(model, str) and model[1:] in PREDEFS:
        values = _variants(PREDEFS[model[1:]], jm, seen, count)
    elif isinstance(model, str) and model.startswith("$"):
        try:
            ja = jm.resolveRef(model, [])
        except (ModelError, AssertionError):
            values = []
        else:
            values = ([] if ja._url in seen
                      else _variants(ja._model, ja, seen | {ja._url}, count))
    elif isinstance(model, dict) and set(model) == {"|"}:
        values, keys = [], set()
        for alt in model["|"]:
            if isinstance(alt, str) and alt.startswith("#"):
                continue
            for value in _variants(alt, jm, seen, count):
                key = json.dumps(value, sort_keys=True)
                if key not in keys:
                    keys.add(key)
                    values.append(value)
    else:
        values = []
    return values[:count]

def _sized(target: ModelType, base: Jsonable, length: int, unique: bool,
           jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Value of a given length for a resizable string or array model."""
    if isinstance(base, str):
        if target != "":
            raise UnsupportedValue(f"cannot resize string model: {target}")
        else:
            return _ANY_CHAR * length
    items = [i for i in target if not (isinstance(i, str) and i.startswith("#"))]
    if not items:
        raise UnsupportedValue(f"cannot resize array model: {target}")
    models = [items[min(i, len(items) - 1)] for i in range(length)]
    if not unique or length <= 1:
        return [simplest(m, jm, seen) for m in models]
    values: list[Jsonable] = []
    keys: set[str] = set()
    for model in models:
        for value in _variants(model, jm, seen, length):
            key = json.dumps(value, sort_keys=True)
            if key not in keys:
                keys.add(key)
                values.append(value)
                break
        else:
            raise UnsupportedValue(f"unique constraint needs {length} distinct values: {target}")
    return values

def _typed(jm: JsonModel, model: ModelType, seen: frozenset[str],
           approx: dict[str, set[type]|None], found: dict[str, set[type]|None]) -> set[type]|None:
    """JSON types a model accepts, None when they cannot be enumerated.

    A reference met again stands for its current approximation, and what each
    reference yields is recorded, so that iterating reaches the least fixpoint.
    """
    if isinstance(model, str):
        if model in _TYPE_PREDEFS:
            return set(_TYPE_PREDEFS[model])
        elif model == "$ANY":
            return None
        elif model.startswith("$"):
            name = model[1:]
            if model in seen:
                return approx.get(model, set())
            elif name in jm._defs._syms:
                node = jm._defs._syms[name]
            elif name in PREDEFS:
                return {str}
            else:
                try:
                    node = jm.resolveRef(model, [])
                except (ModelError, AssertionError):
                    return None
            found[model] = _typed(node, node._model, seen | {model}, approx, found)
            return found[model]
        elif model.startswith("="):
            return ({type(None)} if model == "=null" else
                    {bool} if model in ("=true", "=false") else
                    {float} if any(c in model for c in ".eE") else {int})
        else:
            return {str}
    elif isinstance(model, list):
        return {list}
    elif isinstance(model, dict):
        props = {p: m for p, m in model.items() if not p.startswith("#")}
        if "@" in props:
            return _typed(jm, props["@"], seen, approx, found)
        elif "|" in props or "^" in props:
            op = "|" if "|" in props else "^"
            kept: set[type] = set()
            for alt in props[op]:
                if isinstance(alt, str) and alt.startswith("#"):
                    continue
                kinds = _typed(jm, alt, seen, approx, found)
                if kinds is None:
                    return None
                kept |= kinds
            return kept
        elif "&" in props:
            shared: set[type]|None = None
            for alt in props["&"]:
                if isinstance(alt, str) and alt.startswith("#"):
                    continue
                kinds = _typed(jm, alt, seen, approx, found)
                if kinds is not None:
                    shared = kinds if shared is None else shared & kinds
            return shared
        elif set(props) & _ROOT_KEYS:
            return None
        else:
            return {dict}
    else:
        return {type(model)} if not isinstance(model, bool) else {bool}

def _ultimate(jm: JsonModel, model: ModelType) -> set[type]|None:
    """JSON types a model accepts, widened for a loose float model."""
    try:
        approx: dict[str, set[type]|None] = {}
        while True:
            found = dict(approx)
            kinds = _typed(jm, model, frozenset(), approx, found)
            if found == approx:
                break
            approx = found
    except Exception:
        return None
    if kinds is not None and float in kinds and jm._loose_float:
        kinds = kinds | {int}
    if kinds is not None and int in kinds and jm._loose_int:
        kinds = kinds | {float}
    return kinds

def _rejected(target: str, value: Jsonable) -> bool:
    """Whether a predefined model certainly rejects a value.

    Reuses the format checkers written for property names, which decide a string
    against a predef without building a checker.
    """
    return (isinstance(value, str) and target in _PREDEF_NAMES
            and not _PREDEF_NAMES[target](value))

def _mistyped(value: Jsonable, kinds: set[type]|None) -> bool:
    """Whether a value certainly cannot match a model accepting these types."""
    return kinds is not None and type(value) not in kinds

def _unmatched(model: str, value: Jsonable) -> bool:
    """Whether a constant or regular expression string model certainly rejects a value.

    Decided without the compiler, like the property name checks, so that a
    disagreement shows up as a test failure.
    """
    if model.startswith("$") or model == "":
        return False
    elif model.startswith("="):
        try:
            constant = _simplest_constant(model)
        except UnsupportedValue:
            return False
        if constant is None or isinstance(constant, bool):
            return value is not constant
        elif isinstance(value, bool) or not isinstance(value, (int, float)):
            return True
        else:
            return value != constant
    elif model.startswith("/"):
        if "/" not in model[1:]:
            return False
        pattern, opts = model[1:].rsplit("/", 1)
        if "X" in opts or not isinstance(value, str):
            return False
        try:
            return re.compile(f"(?{opts}){pattern}" if opts else pattern).search(value) is None
        except re.error:
            return False
    elif model.startswith("_"):
        return value != model[1:]
    elif model[:1].isalpha():
        return value != model
    else:
        return False

def _outside(model: ModelType, value: Jsonable) -> bool:
    """Whether the sign a scalar or unsigned model implies rejects a number."""
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        return False
    elif isinstance(model, str):
        return model in _UINT_PREDEFS and value < 0
    elif isinstance(model, bool) or not isinstance(model, (int, float)):
        return False
    elif model == 0:
        return value < 0
    elif model == 1:
        return value <= 0 if isinstance(model, float) else value < 1
    else:
        return False

def _misfits(jm: JsonModel, items: ModelArray, value: list, fixed: bool) -> bool:
    """Whether the item models of an array or tuple certainly reject a list value."""
    if not items:
        return fixed and bool(value)
    elif fixed and len(items) != 1 and len(items) != len(value):
        return True
    else:
        return any(_denies(jm, items[min(index, len(items) - 1)], item)
                   for index, item in enumerate(value))

def _refuses(jm: JsonModel, model: ModelType, value: Jsonable, fixed: bool = True) -> bool:
    """Whether a model certainly rejects a value, by type, format or structure.

    The arity of a tuple is not fixed when a constraint opens it up.
    """
    if _mistyped(value, _ultimate(jm, model)):
        return True
    elif isinstance(model, str):
        return _rejected(model, value) or _unmatched(model, value) or _outside(model, value)
    elif isinstance(model, list) and isinstance(value, list):
        items = [m for m in model if not (isinstance(m, str) and m.startswith("#"))]
        return _misfits(jm, items, value, fixed)
    elif isinstance(model, dict) and isinstance(value, dict):
        node = {p: m for p, m in model.items() if not p.startswith("#")}
        if set(node) & (_OPERATORS | _ROOT_KEYS):
            return False
        elif any(name not in value for _, name in _mandatory(node)):
            return True
        for name, sub in value.items():
            if _unclaimed(node, name, jm):
                return True
            target = _claiming(node, name, jm)
            if target is not None and _denies(jm, target, sub):
                return True
        return False
    else:
        return _outside(model, value)

def _denies(jm: JsonModel, model: ModelType, value: Jsonable) -> bool:
    """Whether a model certainly rejects a whole value, following its references."""
    return _rejects(jm, model, [], value)

def _rejects(jm: JsonModel, model: ModelType, path: list, value: Jsonable,
             seen: frozenset[str] = frozenset(), fixed: bool = True) -> bool:
    """Whether a model certainly rejects a value at one of its positions."""
    if isinstance(model, str) and model.startswith("$"):
        node = None
        if model in seen:
            return False
        elif model[1:] in jm._defs._syms:
            node = jm._defs._syms[model[1:]]
        elif model[1:] not in PREDEFS:
            try:
                node = jm.resolveRef(model, [])
            except (ModelError, AssertionError):
                node = None
        if node is not None:
            return _rejects(node, node._model, path, value, seen | {model})
    props = ({p: m for p, m in model.items() if not p.startswith("#")}
             if isinstance(model, dict) else {})
    if "@" in props and set(props) - {"@"} <= _CONSTRAINTS:
        if not path and any(_breaks(op, props[op], value)
                            for op in props if op != "@"):
            return True
        return _rejects(jm, props["@"], path, value, seen,
                        not set(props) & _COMPARISONS)
    elif set(props) in ({"|"}, {"^"}, {"&"}):
        op = next(iter(props))
        alts = [a for a in props[op] if not (isinstance(a, str) and a.startswith("#"))]
        enough = any if op == "&" else all
        return bool(alts) and enough(_rejects(jm, alt, path, value, seen) for alt in alts)
    elif not path:
        return _refuses(jm, model, value, fixed)
    elif isinstance(model, list):
        items = [m for m in model if not (isinstance(m, str) and m.startswith("#"))]
        step = path[0]
        if isinstance(step, bool) or not isinstance(step, int) or not items:
            return False
        elif len(items) == 1:
            return _rejects(jm, items[0], path[1:], value, seen)
        elif 0 <= step < len(items):
            return _rejects(jm, items[step], path[1:], value, seen)
        elif step < len(items):
            return False
        else:
            return True if fixed else _rejects(jm, items[-1], path[1:], value, seen)
    elif props and not set(props) & (_OPERATORS | _ROOT_KEYS) and isinstance(path[0], str):
        target = _claiming(props, path[0], jm)
        return target is not None and _rejects(jm, target, path[1:], value, seen)
    else:
        return False

def _anything(jm: JsonModel, model: ModelType,
              seen: frozenset[str] = frozenset()) -> bool:
    """Whether a model certainly accepts every value."""
    if isinstance(model, str) and model.startswith("$"):
        name = model[1:]
        if name not in jm._defs._syms:
            return model == "$ANY"
        elif model in seen:
            return False
        node = jm._defs._syms[name]
        return _anything(node, node._model, seen | {model})
    props = ({p: m for p, m in model.items() if not p.startswith("#")}
             if isinstance(model, dict) else {})
    if "@" in props and not set(props) - {"@"}:
        return _anything(jm, props["@"], seen)
    elif set(props) == {"|"}:
        return any(_anything(jm, alt, seen) for alt in props["|"]
                   if not (isinstance(alt, str) and alt.startswith("#")))
    else:
        return False

def _justified(utype: type|None) -> list[Jsonable]:
    """Type violations the oracle can justify first, so a marked value is a last resort."""
    return sorted(_TYPE_VIOLATIONS, key=lambda candidate: not _mistyped(candidate, utype))

def _measured(value: Jsonable) -> int|float|None:
    """What a constraint compares: a number itself, otherwise a length."""
    if isinstance(value, bool):
        return None
    elif isinstance(value, (int, float)):
        return value
    elif isinstance(value, (str, list, dict)):
        return len(value)
    else:
        return None

def _breaks(op: str, bound: Jsonable, value: Jsonable) -> bool:
    """Whether a value certainly violates one constraint of an object model."""
    if op in _COMPARISONS:
        if isinstance(bound, str):
            return not isinstance(value, str) or _BREAKING[op](value, bound)
        measure = _measured(value)
        if measure is None or isinstance(bound, bool) or not isinstance(bound, (int, float)):
            return False
        return _BREAKING[op](measure, bound)
    elif op == "!" and bound is True and isinstance(value, list):
        dumped = [json.dumps(item, sort_keys=True) for item in value]
        return len(set(dumped)) < len(dumped)
    else:
        return False

def _parses(parser, name: str) -> bool:
    """Whether a reference parser accepts a name."""
    try:
        parser(name)
        return True
    except Exception:
        return False

def _iso_time(name: str, zoned: bool|None = None) -> bool:
    """Whether a name is an ISO time, allowing the 23:59:60 leap second."""
    probe = "23:59:59" + name[8:] if name.startswith("23:59:60") else name
    try:
        parsed = datetime.time.fromisoformat(probe)
    except ValueError:
        return False
    return zoned is None or (parsed.tzinfo is not None) is zoned

def _luhn(name: str) -> bool:
    """Whether a name is a card number passing the Luhn checksum."""
    if _CARD_RE.fullmatch(name) is None:
        return False
    total, double = 0, False
    for char in reversed(name):
        digit = int(char)
        total += digit * 2 - 9 if double and digit > 4 else digit * 2 if double else digit
        double = not double
    return total % 10 == 0

_PREDEF_NAMES = {
    "$DATE": lambda n: _DATE_RE.fullmatch(n) is not None
                       and _parses(datetime.date.fromisoformat, n),
    "$TIME": _iso_time,
    "$TIMETZ": lambda n: _iso_time(n, True),
    "$DATETIME": lambda n: _parses(datetime.datetime.fromisoformat, n),
    "$UUID": lambda n: _UUID_RE.fullmatch(n) is not None,
    "$IP4": lambda n: _parses(ipaddress.IPv4Address, n),
    "$IP6": lambda n: "%" not in n and _parses(ipaddress.IPv6Address, n),
    "$JSON": lambda n: _parses(json.loads, n),
    "$ETH": lambda n: _ETH_RE.fullmatch(n) is not None,
    "$SEMVER": lambda n: _SEMVER_RE.fullmatch(n) is not None,
    "$CARD": _luhn,
    "$DURATION": lambda n: _DURATION_RE.fullmatch(n) is not None,
    "$JSONPT": lambda n: _JSONPT_RE.fullmatch(n) is not None,
    "$REGEX": lambda n: _parses(re.compile, n),
    "$EXREG": lambda n: _parses(re.compile, re.sub(r"\(\$\w+", "(P<x>", n)),
}

def _referred(prop: str, jm: JsonModel) -> tuple[ModelType, JsonModel]:
    """Model a property key reference stands for, stopping at a predefined name."""
    seen: set[str] = set()
    target: ModelType = prop
    while (isinstance(target, str) and target.startswith("$")
           and target[1:] not in PREDEFS and target not in seen):
        seen.add(target)
        try:
            node = jm.resolveRef(target, [])
        except (ModelError, AssertionError):
            return prop, jm
        target, jm = node._model, node
    return target, jm

def _matches(name: str, prop: str, jm: JsonModel|None = None) -> bool|None:
    """Whether a name matches an object model property key, None if undecided.

    Independent of the compiler, so that a disagreement shows up as a test failure.
    With a model scope, a key referring to a string definition is resolved.
    """
    if prop == "" or prop in _ANY_NAME_PREDEFS:
        return True
    elif prop.startswith("#") or prop in _NO_NAME_PREDEFS:
        return False
    elif prop in _PREDEF_NAMES:
        return _PREDEF_NAMES[prop](name)
    elif prop.startswith("/"):
        if "/" not in prop[1:]:
            return None
        pattern, opts = prop[1:].rsplit("/", 1)
        if "X" in opts:
            return None
        source = f"(?{opts}){pattern}" if opts else pattern
        try:
            return re.compile(source).search(name) is not None
        except re.error:
            return None
    elif prop.startswith("$"):
        if jm is None or prop[1:] in PREDEFS:
            return None
        target, scope = _referred(prop, jm)
        if not isinstance(target, str) or target == prop:
            return None
        return _matches(name, target, scope)
    else:
        return name == (prop[1:] if prop.startswith(("!", "?", "_")) else prop)

def _unclaimed(node: ModelObject, name: str, jm: JsonModel|None = None) -> bool:
    """Whether no key of an object model can hold this property name."""
    return all(_matches(name, prop, jm) is False
               for prop in node if not prop.startswith("#"))

def _claiming(node: ModelObject, name: str, jm: JsonModel|None = None) -> ModelType|None:
    """Model a property name falls under, None when no key claims it or one is undecided.

    Concurrent catch-all keys are left to the compiler, which picks between them
    with a priority of its own.
    """
    if len([prop for prop in node if prop in optim.ANY_PROP]) > 1:
        return None
    for prop in _outranking(node, "") + ([""] if "" in node else []):
        verdict = _matches(name, prop, jm)
        if verdict is None:
            return None
        elif verdict:
            return node[prop]
    return None

def _outranking(node: ModelObject, prop: str) -> list[str]:
    """Property keys the model applies before a catch-all or pattern key.

    A named property wins over a predefined one, which wins over any pattern,
    and patterns apply in declaration order, so a generated name matching one of
    these belongs to that key instead.
    """
    keys = [p for p in node if not p.startswith("#")]
    literals = [p for p in keys if p != "" and not p.startswith(("/", "$"))]
    predefs = [p for p in keys if p.startswith("$")]
    patterns = [p for p in keys if p.startswith("/")]
    if prop == "":
        return literals + predefs + patterns
    elif prop in patterns:
        return literals + predefs + patterns[:patterns.index(prop)]
    else:
        return []

def _names(prop: str, count: int, taken: set[str],
           outranking: list[str] = []) -> list[str]:
    """Distinct property names matching a catch-all or pattern property model.

    A catch-all accepts any name, so fall back on further starting letters when
    an earlier key claims every name built from the first one.
    """
    try:
        seeds = list(_NAME_CHARS) if prop == "" else [_simplest_regex(prop)]
    except UnsupportedValue:
        return []
    names: list[str] = []
    for seed in seeds:
        for i in range(count + len(taken) + 1):
            name = seed + _ANY_CHAR * i
            if (name not in names and name not in taken
                    and _matches(name, prop) is True
                    and not any(_matches(name, other) is True for other in outranking)):
                names.append(name)
                if len(names) >= count:
                    return names
    return names

def _grown(target: ModelType, base: ModelObject, length: int,
           jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Object of a given size, extended with optional or free properties."""
    if not isinstance(target, dict) or set(target) & (_OPERATORS | _ROOT_KEYS):
        raise UnsupportedValue(f"cannot resize object model: {target}")
    elif len(base) > length:
        raise UnsupportedValue(f"cannot shrink object model: {target}")
    props = {p: m for p, m in target.items() if not p.startswith("#")}
    value = dict(base)
    for prop, submodel in props.items():
        if len(value) >= length:
            break
        elif prop.startswith("?") and prop[1:] not in value:
            value[prop[1:]] = simplest(submodel, jm, seen)
    for prop, submodel in props.items():
        if len(value) >= length:
            break
        elif prop == "" or prop.startswith("/"):
            for name in _names(prop, length - len(value), set(value),
                               _outranking(target, prop)):
                value[name] = simplest(submodel, jm, seen)
    if len(value) != length:
        raise UnsupportedValue(f"cannot reach {length} properties: {target}")
    else:
        return value

def _resolved(target: ModelType, jm: JsonModel,
              seen: frozenset[str]) -> tuple[ModelType, JsonModel, frozenset[str]]:
    """Model behind a predefined name or a reference, with its own scope."""
    names: set[str] = set()
    while isinstance(target, str) and target.startswith("$") and target not in names:
        names.add(target)
        if target[1:] in PREDEFS:
            target = PREDEFS[target[1:]]
        else:
            try:
                ja = jm.resolveRef(target, [])
            except (ModelError, AssertionError):
                break
            if ja._url in seen:
                break
            target, jm, seen = ja._model, ja, seen | {ja._url}
    return target, jm, seen

def _simplest_constrained(props: ModelObject, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a constraint model."""
    target = props["@"]
    ops = {p: c for p, c in props.items() if p != "@"}
    if any(isinstance(c, str) for p, c in ops.items() if p in _COMPARISONS):
        raise UnsupportedValue(f"unsupported string comparison constraint: {ops}")
    if any(isinstance(c, bool) or not isinstance(c, (int, float))
           for p, c in ops.items() if p in _COMPARISONS):
        raise UnsupportedValue(f"unsupported comparison constraint: {ops}")
    unique = ops.get("!") is True
    base = simplest(target, jm, seen)
    if base is None or isinstance(base, bool):
        raise UnsupportedValue(f"unsupported constrained model: {target}")
    elif unique and not isinstance(base, list):
        raise UnsupportedValue(f"unique constraint on a non-array: {target}")
    elif isinstance(base, (int, float)):
        is_float = isinstance(base, float)
        step: int|float = 1.0 if is_float else 1
        lo, hi = _bounds(ops, step, _numeric_low(target))
        value = _pick(lo, hi, ops, step, 0.0 if is_float else 0)
        return float(value) if is_float else int(value)
    lo, hi = _bounds(ops, 1, 0)
    if ((lo is None or len(base) >= lo) and (hi is None or len(base) <= hi)
            and not ("!=" in ops and len(base) == ops["!="])):
        return base
    length = int(_pick(lo, hi, ops, 1, 0))
    target, jm, seen = _resolved(target, jm, seen)
    if isinstance(base, dict):
        return _grown(target, base, length, jm, seen)
    value = _sized(target, base, length, unique, jm, seen)
    if unique and length > 1 and _verify(value, props, jm) is not True:
        raise UnsupportedValue(f"unique constraint is not satisfiable: {target}")
    else:
        return value

def _simplest_union(alts: ModelArray, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for the first alternative which yields one."""
    for alt in alts:
        if isinstance(alt, str) and alt.startswith("#"):
            continue
        else:
            try:
                return simplest(alt, jm, seen)
            except UnsupportedValue:
                pass
    raise UnsupportedValue(f"no alternative yields a value: {alts}")

_CHECKERS: dict[str, EntryCheckFun|None] = {}

def _defs(jm: JsonModel) -> ModelObject:
    """Definitions of a model, by name."""
    base = jm._url.split("#")[0]
    return {name: ("$" + node._url if node._url.split("#")[0] != base else node._model)
            for name, node in jm._defs._syms.items()}

def _needed(model: ModelType, defs: ModelObject) -> set[str]:
    """Definition names a model may reference."""
    keep: set[str] = set()
    pending = [model]
    while pending:
        text = json.dumps(pending.pop())
        for name in defs:
            if name not in keep and "$" + name in text:
                keep.add(name)
                pending.append(defs[name])
    return keep

def _verify(value: Jsonable, model: ModelType, jm: JsonModel,
            defs: ModelObject|None = None) -> bool|None:
    """Whether a value matches a model, None when no checker can be built."""
    try:
        if defs is None:
            defs = _defs(jm)
        defs = {name: defs[name] for name in _needed(model, defs)}
        key = json.dumps([jm._url, {"$": defs, "@": model},
                          jm._loose_int, jm._loose_float], sort_keys=True)
    except (TypeError, ValueError):
        return None
    if key not in _CHECKERS:
        from .script import model_checker_from_json
        try:
            _CHECKERS[key] = model_checker_from_json(
                json.loads(key)[1], resolver=jm._resolver,
                loose_int=jm._loose_int, loose_float=jm._loose_float)
        except Exception:
            _CHECKERS[key] = None
    check = _CHECKERS[key]
    if check is None:
        return None
    try:
        return check(value, "", None)
    except RecursionError:
        _CHECKERS[key] = None
        return None

def _simplest_operator(op: str, alts: ModelArray, jm: JsonModel,
                       seen: frozenset[str]) -> Jsonable:
    """Simplest value satisfying an operator, checked against the whole model."""
    models = [a for a in alts if not (isinstance(a, str) and a.startswith("#"))]
    for alt in models:
        try:
            value = simplest(alt, jm, seen)
        except UnsupportedValue:
            continue
        if _verify(value, {op: models}, jm) is True:
            return value
    raise UnsupportedValue(f"no alternative satisfies {op}: {alts}")

def _simplest_object(model: ModelObject, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a simple object model or a bare target model."""
    props = {p: m for p, m in model.items() if not p.startswith("#")}
    if set(props) == {"|"}:
        return _simplest_union(props["|"], jm, seen)
    elif set(props) == {"^"}:
        return _simplest_operator("^", props["^"], jm, seen)
    elif set(props) == {"&"}:
        return _simplest_operator("&", props["&"], jm, seen)
    elif "@" in props:
        others = set(props) - {"@"}
        if not others:
            return simplest(props["@"], jm, seen)
        elif others <= _CONSTRAINTS:
            return _simplest_constrained(props, jm, seen)
    value: dict[str, Jsonable] = {}
    for prop, submodel in props.items():
        if prop in _OPERATORS:
            raise UnsupportedValue(f"unsupported object operator: {prop}")
        elif prop in _ROOT_KEYS:
            raise UnsupportedValue(f"unsupported definitions or imports: {prop}")
        elif prop == "" or prop.startswith(("?", "/", "$")):
            continue
        else:
            name = prop[1:] if prop.startswith(("!", "_")) else prop
            try:
                value[name] = simplest(submodel, jm, seen)
            except UnsupportedValue as e:
                raise type(e)(f"{prop}: {e}")
    return value

def _simplest_string(model: str, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Simplest value for a string model."""
    if model == "":
        return ""
    elif model.startswith("_"):
        return model[1:]
    elif model.startswith("="):
        return _simplest_constant(model)
    elif model.startswith("/"):
        return _simplest_regex(model)
    elif model.startswith("$"):
        return _simplest_predef(model, jm, seen)
    else:
        return model

def _property_name(prop: str, taken: set[str], outranking: list[str] = []) -> str:
    """Property name matching a pattern property, free of any other key of the object."""
    def usable(name: str) -> bool:
        return (name not in taken
                and not any(_matches(name, other) is True for other in outranking))
    name = _simplest_regex(prop)
    if usable(name):
        return name
    for suffix in ("0", "00", "000"):
        if usable(name + suffix) and _matches(name + suffix, prop) is True:
            return name + suffix
    raise UnsupportedValue(f"no free property name for {prop}")

def _compile(model: ModelType, optimize: bool = True, resolver: Resolver|None = None,
             url: str = "", extend: bool = False) -> tuple[JsonModel, ModelType]:
    """Check and preprocess a model given as plain JSON """
    try:
        jm = JsonModel(model, resolver or Resolver(), url=url)
        nodes = sorted(jm._models.values(), key=lambda m: m._id)
        for node in nodes:
            if not analyze.valid(node, extend=extend):
                raise UnsupportedValue(f"unsupported model {node._url}:{node._id}")
        if optimize:
            for node in nodes:
                optim.optimize(node)
        for node in reversed(nodes):
            merge(node)
        if optimize:
            for node in nodes:
                optim.optimize(node)
    except (ModelError, AssertionError, KeyError) as e:
        msg = str(e)
        if msg:
            raise UnsupportedValue(f"unsupported model: {msg}")
        else:
            raise UnsupportedValue("unsupported model")
    return jm, jm._model

def simplest(model: ModelType, jm: JsonModel|None = None,
             seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
             url: str = "", extend: bool = False) -> Jsonable:
    """Generate the simplest value matching a model."""
    if jm is None:
        jm, model = _compile(model, True, resolver, url, extend)
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

def _violation_value(op: str, bound: Jsonable, props: ModelObject, base: Jsonable,
                     jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Candidate value just past a constraint, on its violating side."""
    target, ops = props["@"], {p: c for p, c in props.items() if p != "@"}
    if op == "!":
        if bound is not True:
            raise UnsupportedValue(f"unsupported unique constraint: {bound}")
        lo, hi = _bounds(ops, 1, 0)
        lo = 2 if lo is None else max(lo, 2)
        return _sized(target, base, int(_pick(lo, hi, ops, 1, 0)), False, jm, seen)
    is_float = isinstance(base, float)
    table = _FLOAT_VIOLATIONS if is_float else _INT_VIOLATIONS
    if op not in table:
        raise UnsupportedValue(f"unsupported constraint: {op}")
    elif isinstance(base, dict):
        raise UnsupportedValue(f"cannot resize object model: {target}")
    candidate = table[op](bound)
    if not isinstance(candidate, float if is_float else int):
        raise UnsupportedValue(f"no value of the target type violates {op} {bound}")
    elif isinstance(base, (int, float)):
        return candidate
    elif candidate < 0:
        raise UnsupportedValue(f"no length violates {op} {bound}")
    else:
        return _sized(target, base, candidate, ops.get("!") is True, jm, seen)

def _candidates(op: str, bound: Jsonable, props: ModelObject, base: Jsonable,
                jm: JsonModel, seen: frozenset[str]):
    """Values which may break a constraint, best first."""
    try:
        yield _violation_value(op, bound, props, base, jm, seen)
    except UnsupportedValue:
        pass
    yield base

def _violations_constrained(props: ModelObject, jm: JsonModel,
                            seen: frozenset[str]) -> dict[str, Jsonable]:
    """One value per size constraint, each breaking only that constraint."""
    target = props["@"]
    ops = {p: c for p, c in props.items() if p != "@"}
    if any(isinstance(c, str) for p, c in ops.items() if p in _COMPARISONS):
        raise UnsupportedValue(f"unsupported string comparison constraint: {ops}")
    base = simplest(target, jm, seen)
    if isinstance(base, bool) or not isinstance(base, (int, float, str, list, dict)):
        raise UnsupportedValue(f"unsupported constrained model: {target}")
    elif ops.get("!") is True and not isinstance(base, list):
        raise UnsupportedValue(f"unique constraint on a non-array: {target}")
    values: dict[str, Jsonable] = {}
    for op, bound in ops.items():
        rest = {p: m for p, m in props.items() if p != op}
        for value in _candidates(op, bound, props, base, jm, seen):
            if _verify(value, props, jm) is False and _verify(value, rest, jm) is True:
                values[op] = value
                break
    if not values:
        raise UnsupportedValue(f"no constraint could be violated: {props}")
    else:
        return values

def _bound_value(table: dict, op: str, bound: Jsonable, props: ModelObject,
                 base: Jsonable, jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Candidate value on the last step a constraint still accepts."""
    target, ops = props["@"], {p: c for p, c in props.items() if p != "@"}
    is_float = isinstance(base, float)
    if op not in table:
        raise UnsupportedValue(f"no exact bound for constraint: {op}")
    candidate = table[op](bound)
    if not isinstance(candidate, float if is_float else int):
        raise UnsupportedValue(f"no value of the target type reaches {op} {bound}")
    elif isinstance(base, (int, float)):
        return candidate
    elif candidate < 0:
        raise UnsupportedValue(f"no length reaches {op} {bound}")
    node, njm, nseen = _resolved(target, jm, seen)
    if isinstance(base, dict):
        return _grown(node, base, candidate, njm, nseen)
    else:
        return _sized(node, base, candidate, ops.get("!") is True, njm, nseen)

def _bound_candidates(op: str, bound: Jsonable, props: ModelObject, base: Jsonable,
                      jm: JsonModel, seen: frozenset[str]):
    """Values which may sit on a constraint bound, best first."""
    tables = [_FLOAT_BOUNDS if isinstance(base, float) else _INT_BOUNDS]
    if op == "!=" and not isinstance(base, float):
        tables.append(_INT_MIRRORS)
    for table in tables:
        try:
            yield _bound_value(table, op, bound, props, base, jm, seen)
        except UnsupportedValue:
            pass

def _bounds_constrained(props: ModelObject, jm: JsonModel,
                        seen: frozenset[str]) -> dict[str, Jsonable]:
    """One value per constraint, each on the last step it still accepts."""
    target = props["@"]
    ops = {p: c for p, c in props.items() if p != "@"}
    if any(isinstance(c, bool) or not isinstance(c, (int, float))
           for p, c in ops.items() if p in _COMPARISONS):
        raise UnsupportedValue(f"unsupported comparison constraint: {ops}")
    base = simplest(target, jm, seen)
    if isinstance(base, bool) or not isinstance(base, (int, float, str, list, dict)):
        raise UnsupportedValue(f"unsupported constrained model: {target}")
    elif ops.get("!") is True and not isinstance(base, list):
        raise UnsupportedValue(f"unique constraint on a non-array: {target}")
    values: dict[str, Jsonable] = {}
    for op, bound in ops.items():
        for value in _bound_candidates(op, bound, props, base, jm, seen):
            if _verify(value, props, jm) is True:
                values[op] = value
                break
    if not values:
        raise UnsupportedValue(
            f"no bound reached for {', '.join(ops)} in model: {_brief(target)}")
    else:
        return values

def _mandatory(node: ModelObject) -> list[tuple[str, str]]:
    """Model key and value name of each mandatory property of an object model."""
    props = []
    for prop in node:
        if prop == "" or prop.startswith(("#", "?", "/", "$")):
            continue
        props.append((prop, prop[1:] if prop.startswith(("!", "_")) else prop))
    return props

def _optional(node: ModelObject, prop: str, name: str) -> ModelObject:
    """Copy of an object model with one mandatory property made optional."""
    return {("?" + name if p == prop else p): m for p, m in node.items()}

def _optional_props(node: ModelObject, jm: JsonModel,
                    seen: frozenset[str]) -> list[tuple[str, str, ModelType]]:
    """Model key, value name and model of each optional property."""
    named = {p[1:] if p.startswith(("!", "?", "_")) else p
             for p in node if p and not p.startswith(("/", "$", "#"))}
    props: list[tuple[str, str, ModelType]] = []
    for prop, sub in node.items():
        if prop.startswith("#"):
            continue
        elif prop.startswith("?"):
            props.append((prop, prop[1:], sub))
        elif prop == "" or prop.startswith("/"):
            props.extend((prop, name, sub)
                         for name in _names(prop, 1, named, _outranking(node, prop)))
        elif prop.startswith("$"):
            try:
                name = simplest(prop, jm, seen)
            except UnsupportedValue:
                continue
            if isinstance(name, str) and name not in named:
                props.append((prop, name, sub))
    return props

def _opened(node: ModelObject) -> ModelObject:
    """Copy of an object model which also accepts any other property."""
    return {**node, "": "$ANY"}

def _closed(node: ModelObject, jm: JsonModel) -> bool:
    """Whether an object model rejects properties it does not describe."""
    if "" not in node:
        return True
    try:
        simplest(node[""], jm)
        return False
    except UnsupportedValue:
        return True

def _object_sites(sites: list):
    """Sites which target a plain object model."""
    for mpath, vpath, frames, props, disjunction in sites:
        node = props["@"]
        if (not set(props) - {"@"} and isinstance(node, dict)
                and not set(node) & (_OPERATORS | _ROOT_KEYS)):
            yield mpath, vpath, frames, node, disjunction

def _alternatives(sites: list):
    """Sites which target a union model."""
    for mpath, vpath, frames, props, disjunction in sites:
        node = props["@"]
        if set(props) - {"@"} or not isinstance(node, dict):
            continue
        keys = {p for p in node if not p.startswith("#")}
        if keys in ({"|"}, {"^"}):
            yield mpath, vpath, frames, node, next(iter(keys))

def _jqpath(path: list) -> str:
    """jq path expression for a path of object keys and array indexes."""
    if not path:
        return "."
    steps = []
    for step in path:
        if isinstance(step, int) and not isinstance(step, bool):
            steps.append(f"[{step}]")
        elif _JQ_NAME_RE.match(str(step)):
            steps.append(f".{step}")
        else:
            steps.append(f"[{json.dumps(str(step))}]")
    return "." + "".join(steps) if steps[0][0] == "[" else "".join(steps)

def _mpath(path: list) -> str:
    """Readable model path, written in JSON Model syntax."""
    steps: list[str] = []
    index = 0
    while index < len(path):
        step = path[index]
        follow = path[index + 1] if index + 1 < len(path) else None
        index += 1
        if isinstance(step, int) and not isinstance(step, bool):
            steps.append(f"[{step}]")
            continue
        name = str(step)
        if name == "$" and isinstance(follow, str):
            steps.append(f".${follow}")
            index += 1
        elif name in _QUOTED_OPS or not _MODEL_NAME_RE.match(name):
            steps.append(f".'{name}'")
        else:
            steps.append(f".{name}")
    text = "".join(steps)
    return "." + text if not text or text[0] == "[" else text

def _replaced(doc: Jsonable, path: list, value: Jsonable) -> Jsonable:
    """Copy of a document with one position set to a value."""
    result = copy.deepcopy(doc)
    node = result
    try:
        for step in path[:-1]:
            node = node[step]
        node[path[-1]] = value
    except (KeyError, IndexError, TypeError) as e:
        raise UnsupportedValue(f"cannot set {_jqpath(path)} in document: {e}")
    return result

def _without(model: ModelType, path: list) -> ModelType:
    """Copy of a model with one position removed."""
    result = copy.deepcopy(model)
    node = result
    try:
        for step in path[:-1]:
            if not isinstance(node, (dict, list)):
                break
            node = node[step]
        if not isinstance(node, (dict, list)):
            raise UnsupportedValue(
                f"cannot remove {_mpath(path)} from an imported definition")
        del node[path[-1]]
    except (KeyError, IndexError, TypeError) as e:
        raise UnsupportedValue(f"cannot remove {_mpath(path)} from model: {e}")
    return result

def _sites(model: ModelType, mpath: list, vpath: list, frames: list,
           jm: JsonModel, seen: frozenset[str], notes: list[str]|None = None,
           disjunction: tuple[list, ModelObject]|None = None):
    """Violation sites, as model path, value path, branch frames, properties and disjunction.

    A site under an alternative of a union or a xor carries the outermost one, as the
    value path where it applies and its node: breaking the model there only invalidates
    the document when every alternative of that operator rejects the value.
    """
    if isinstance(model, str):
        name = model[1:]
        if model.startswith("$") and name in jm._defs._syms and name not in seen:
            yield from _sites(jm._defs._syms[name]._model, ["$", name], vpath,
                              frames, jm, seen | {name}, notes, disjunction)
        elif model != "$ANY" and (not model.startswith("$") or name in PREDEFS):
            yield mpath, vpath, frames, {"@": model}, disjunction
        elif model == "$ANY" and notes is not None:
            notes.append(f"{_mpath(mpath)} invalid: $ANY accepts every value")
    elif isinstance(model, list):
        yield mpath, vpath, frames, {"@": model}, disjunction
        items = [(i, m) for i, m in enumerate(model)
                 if not (isinstance(m, str) and m.startswith("#"))]
        if len(items) > 1:
            for n, (i, item) in enumerate(items):
                yield from _sites(item, mpath + [i], vpath + [n], frames, jm, seen,
                                  notes, disjunction)
        elif items:
            i, item = items[0]
            yield from _sites(item, mpath + [i], vpath + [0],
                              frames + [(vpath, {"@": model, ">=": 1})], jm, seen,
                              notes, disjunction)
    elif isinstance(model, dict):
        props = {p: m for p, m in model.items() if not p.startswith("#")}
        others = set(props) - {"@"}
        if "@" in props and others <= _CONSTRAINTS:
            if others:
                yield mpath, vpath, frames, props, disjunction
            yield from _sites(props["@"], mpath + ["@"], vpath, frames, jm, seen,
                              notes, disjunction)
        elif set(props) in ({"|"}, {"^"}, {"&"}):
            op = next(iter(props))
            yield mpath, vpath, frames, {"@": model}, disjunction
            inner = (disjunction if disjunction is not None or op == "&"
                     else (vpath, props))
            for index, alt in enumerate(props[op]):
                if isinstance(alt, str) and alt.startswith("#"):
                    continue
                yield from _sites(alt, mpath + [op, index], vpath,
                                  frames + [(vpath, alt)], jm, seen, notes, inner)
        elif not set(props) & (_OPERATORS | _ROOT_KEYS):
            yield mpath, vpath, frames, {"@": model}, disjunction
            named = {p[1:] if p.startswith(("!", "?", "_")) else p
                     for p in props if p and not p.startswith(("/", "$"))}
            for prop, sub in props.items():
                if prop == "" or prop.startswith("$"):
                    continue
                elif prop.startswith("/"):
                    try:
                        name = _property_name(prop, named, _outranking(props, prop))
                    except UnsupportedValue:
                        continue
                    inner = frames + [(vpath + [name], sub)]
                else:
                    name = prop[1:] if prop.startswith(("!", "?", "_")) else prop
                    inner = (frames + [(vpath + [name], sub)] if prop.startswith("?")
                             else frames)
                yield from _sites(sub, mpath + [prop], vpath + [name], inner, jm, seen,
                                  notes, disjunction)
    else:
        yield mpath, vpath, frames, {"@": model}, disjunction

def _document(sub: Jsonable, vpath: list, frames: list, doc: Jsonable,
              jm: JsonModel, seen: frozenset[str]) -> Jsonable:
    """Whole document holding a violating value at one position."""
    value, path = sub, vpath
    for vp, branch in reversed(frames):
        if path != vp:
            value = _replaced(simplest(branch, jm, seen), path[len(vp):], value)
        path = vp
    if not path:
        return value
    elif doc is None:
        raise UnsupportedValue("no document to alter")
    else:
        return _replaced(doc, path, value)

def _at(doc: Jsonable, path: list) -> Jsonable:
    """Value held at a path in a document, None when there is none."""
    node = doc
    for step in path:
        if isinstance(node, dict) and step in node:
            node = node[step]
        elif isinstance(node, list) and isinstance(step, int) and 0 <= step < len(node):
            node = node[step]
        else:
            return None
    return node

def _validated(sub: Jsonable, vpath: list, frames: list, doc: Jsonable,
               model: ModelType, jm: JsonModel, seen: frozenset[str],
               taken: set[str], key: str = "",
               unverified: set[str]|None = None) -> list[Jsonable]:
    """Valid whole document holding a value at one position, empty if there is none."""
    here = _at(doc, vpath)
    candidates = [sub]
    if isinstance(sub, dict) and isinstance(here, dict) and {**here, **sub} != sub:
        candidates.append({**here, **sub})
    fallback: list[Jsonable] = []
    for candidate in candidates:
        value = _document(candidate, vpath, frames, doc, jm, seen)
        wholes = [value]
        if isinstance(value, dict) and isinstance(doc, dict) and {**doc, **value} != value:
            wholes.append({**doc, **value})
        for whole in wholes:
            if json.dumps(whole, sort_keys=True) in taken:
                return [whole]
            elif unverified is None and _verify(whole, model, jm) is True:
                return [whole]
            elif not fallback:
                fallback = [whole]
    if unverified is not None and fallback:
        unverified.add(key)
        return fallback
    return []

def violations(model: ModelType, jm: JsonModel|None = None,
               seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
               url: str = "", extend: bool = False,
               unverified: set[str]|None = None) -> dict[str, Jsonable]:
    """Generate a value breaking one constraint, type or property of a model."""
    return _violations(model, jm, seen, resolver, url, extend, unverified)[0]

def _beyond(jm: JsonModel, disjunction: tuple[list, ModelObject]|None,
            value: Jsonable) -> bool:
    """Whether every alternative of an enclosing union refuses the whole document.

    Breaking a model under a union only invalidates the document when no other
    alternative accepts it, which the value at the broken position cannot show.
    """
    return (disjunction is not None
            and _denies(jm, disjunction[1], _at(value, disjunction[0])))

def _violations(model: ModelType, jm: JsonModel|None = None,
                seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
                url: str = "", extend: bool = False,
                unverified: set[str]|None = None,
                valid: frozenset[str] = frozenset()) -> tuple[dict[str, Jsonable], list[str]]:
    """Generate a value breaking each constraint, and why some sites were skipped.

    Values already generated as valid, as JSON dumps, are known to match the model.
    """
    vjm, vmodel = jm, model
    skipped: list[str] = []
    if jm is None:
        jm, model = _compile(model, False, resolver, url, extend)
        vjm, vmodel = _compile(vmodel, True, resolver, url, extend)
    sites = list(_sites(model, [], [], [], jm, frozenset(), skipped))
    defs = _defs(jm)
    if not sites:
        if all(_verify(v, model, jm, defs) is True for v in _TYPE_VIOLATIONS):
            raise Vacuous(f"every value matches the model: {_brief(model)}")
        raise UnsupportedValue(f"cannot enter model: {_brief(model)}")
    values: dict[str, Jsonable] = {}
    reasons: list[str] = []
    doc = None

    def skip(note: str):
        """Record a case which cannot exist for this model."""
        reasons.append(note)
        if note not in skipped:
            skipped.append(note)

    def repeats(key: str, value: Jsonable) -> bool:
        """Whether a violation repeats a value already generated as valid."""
        if unverified is None or json.dumps(value, sort_keys=True) not in valid:
            return False
        skip(f"{key}: valid for the model")
        return True

    if any(f[0][0] if f else v for _, v, f, _, _ in sites):
        try:
            doc = simplest(model, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"no document to alter: {e}")
    for mpath, vpath, frames, props, disjunction in sites:
        ops = set(props) - {"@"}
        if not ops or all(_mpath(mpath + [op]) in values for op in ops):
            continue
        try:
            subs = _violations_constrained(props, jm, seen)
        except UnsupportedValue as e:
            reasons.append(str(e))
            continue
        for op, sub in subs.items():
            key = _mpath(mpath + [op])
            if key in values:
                continue
            proven = (_breaks(op, props[op], sub) if disjunction is None else
                      _rejects(jm, disjunction[1], vpath[len(disjunction[0]):], sub))
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
                proven = proven or _beyond(jm, disjunction, value)
                if mpath and mpath[0] == "$":
                    rest, rdefs = model, _without(defs, mpath[1:] + [op])
                else:
                    rest, rdefs = _without(model, mpath + [op]), defs
            except UnsupportedValue as e:

                reasons.append(str(e))

                continue
            if not proven and repeats(key, value):
                continue
            elif proven:
                values[key] = value
            elif unverified is not None:
                skip(f"{key}: no oracle proves the violation")
            elif _verify(value, vmodel, vjm) is False and _verify(value, rest, jm, rdefs) is True:
                values[key] = value
            else:
                skip(f"{key}: no value isolates it")
    taken = {json.dumps(v, sort_keys=True) for v in values.values()}
    for mpath, vpath, frames, props, disjunction in sites:
        key = f"{_mpath(mpath)} invalid"
        if not mpath or set(props) - {"@"} or key in values:
            continue
        target = _ultimate(jm, props["@"])
        for candidate in (_justified(target) if unverified is not None
                          else _TYPE_VIOLATIONS):
            if not _mistyped(candidate, target) and (
                    unverified is None
                    and _verify(candidate, props["@"], jm, defs) is not False):
                continue
            proven = _mistyped(candidate, target) and (
                disjunction is None
                or _rejects(jm, disjunction[1],
                            vpath[len(disjunction[0]):], candidate))
            try:
                value = _document(copy.deepcopy(candidate), vpath, frames, doc, jm, seen)
                proven = proven or _beyond(jm, disjunction, value)
            except UnsupportedValue as e:

                reasons.append(str(e))

                break
            if json.dumps(value, sort_keys=True) in taken:
                break
            elif not proven and repeats(key, value):
                break
            elif proven or (unverified is None and _verify(value, vmodel, vjm) is False):
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
                break
        else:
            skip(f"{key}: no type breaks the model here")
    for mpath, vpath, frames, props, disjunction in sites:
        key = f"{_mpath(mpath)} bad"
        if set(props) - {"@"} or key in values:
            continue
        target = props["@"]
        if not isinstance(target, str) or target not in _PREDEF_VIOLATIONS:
            continue
        proven = disjunction is None and _denies(jm, target, _PREDEF_VIOLATIONS[target])
        try:
            value = _document(copy.deepcopy(_PREDEF_VIOLATIONS[target]),
                              vpath, frames, doc, jm, seen)
            proven = proven or _beyond(jm, disjunction, value)
        except UnsupportedValue as e:

            reasons.append(str(e))

            continue
        if json.dumps(value, sort_keys=True) in taken:
            continue
        elif not proven and repeats(key, value):
            continue
        elif proven or (unverified is None and _verify(value, vmodel, vjm) is False):
            values[key] = value
            taken.add(json.dumps(value, sort_keys=True))
        elif unverified is not None:
            skip(f"{key}: no oracle proves the violation")
        else:
            skip(f"{key}: the {target} violation is still valid")
    for mpath, vpath, frames, node, disjunction in _object_sites(sites):
        try:
            built = simplest(node, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"{_mpath(mpath)}: no object to shrink: {e}")
            continue
        if not isinstance(built, dict):
            continue
        for prop, name in _mandatory(node):
            key = f"{_mpath(mpath + [prop])} missing"
            if key in values or name not in built:
                continue
            sub = {p: v for p, v in built.items() if p != name}
            proven = (disjunction is None or
                      _rejects(jm, disjunction[1], vpath[len(disjunction[0]):], sub))
            verdict = True if unverified is not None else \
                _verify(sub, _optional(node, prop, name), jm, defs)
            if verdict is not True:
                if verdict is False:
                    skip(f"{key}: dropping {name} does not match the model")
                else:
                    reasons.append(f"{key}: cannot check dropping {name}")
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
                proven = proven or _beyond(jm, disjunction, value)
            except UnsupportedValue as e:

                reasons.append(str(e))

                break
            if json.dumps(value, sort_keys=True) in taken:
                continue
            elif not proven and repeats(key, value):
                continue
            elif proven or (unverified is None and _verify(value, vmodel, vjm) is False):
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
            elif unverified is not None:
                skip(f"{key}: no oracle proves the violation")
            else:
                skip(f"{key}: dropping {name} is still valid")
    for mpath, vpath, frames, node, disjunction in _object_sites(sites):
        if not _closed(node, jm):
            skip(f"{_mpath(mpath)} extra: object is open")
            continue
        try:
            built = simplest(node, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"{_mpath(mpath)}: no object to extend: {e}")
            continue
        if not isinstance(built, dict):
            continue
        for name in _EXTRA_NAMES:
            key = f"{_mpath(mpath + [name])} extra"
            if name in built or key in values:
                continue
            sub = {**built, name: None}
            claiming = _claiming(node, name, jm)
            proven = (_unclaimed(node, name, jm) if disjunction is None else
                      _rejects(jm, disjunction[1], vpath[len(disjunction[0]):], sub))
            proven = proven or (claiming is not None and _denies(jm, claiming, None))
            if unverified is None and (_verify(sub, node, jm, defs) is not False
                                       or _verify(sub, _opened(node), jm, defs) is not True):
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
                proven = proven or _beyond(jm, disjunction, value)
            except UnsupportedValue as e:

                reasons.append(str(e))

                break
            if json.dumps(value, sort_keys=True) in taken:
                break
            elif not proven and repeats(key, value):
                break
            elif proven or (unverified is None and _verify(value, vmodel, vjm) is False):
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
                break
        else:
            skip(f"{_mpath(mpath)} extra: every extra property is valid")
    always = _anything(vjm, vmodel)
    for candidate in _ROOT_TYPES:
        dumped = json.dumps(candidate, sort_keys=True)
        shown = f"'{candidate}'" if isinstance(candidate, str) else dumped
        if dumped in taken:
            continue
        if _rejects(vjm, vmodel, [], candidate):
            verdict = False
        elif always or dumped in valid:
            verdict = True
        elif unverified is not None:
            continue
        else:
            verdict = _verify(candidate, vmodel, vjm)
        if verdict is not False:
            if verdict is True:
                skip(f".{shown} root: valid for the model")
            continue
        values[f".{shown} root invalid"] = copy.deepcopy(candidate)
        taken.add(dumped)
    if not values:
        if not reasons:
            reasons.append("no violation site could be used")
        raise UnsupportedValue(f"no constraint could be violated: {_joined(reasons)}")
    else:
        return values, skipped

def bounds(model: ModelType, jm: JsonModel|None = None,
           seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
           url: str = "", extend: bool = False,
           unverified: set[str]|None = None) -> dict[str, Jsonable]:
    """Generate a value on the bound of each constraint of a model."""
    return _all_bounds(model, jm, seen, resolver, url, extend, unverified)[0]

def _all_bounds(model: ModelType, jm: JsonModel|None = None,
                seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
                url: str = "", extend: bool = False,
                unverified: set[str]|None = None) -> tuple[dict[str, Jsonable], list[str]]:
    """Generate a value on each constraint bound, and why some bounds were skipped."""
    vjm, vmodel = jm, model
    if jm is None:
        jm, model = _compile(model, False, resolver, url, extend)
        vjm, vmodel = _compile(vmodel, True, resolver, url, extend)
    sites = list(_sites(model, [], [], [], jm, frozenset()))
    if not sites and not all(_verify(v, model, jm) is True for v in _TYPE_VIOLATIONS):
        raise UnsupportedValue(f"cannot enter model: {_brief(model)}")
    values: dict[str, Jsonable] = {}
    reasons: list[str] = []
    skipped: list[str] = []
    doc = None
    if any(f[0][0] if f else v for _, v, f, _, _ in sites):
        try:
            doc = simplest(model, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"no document to alter: {e}")
    for mpath, vpath, frames, props, disjunction in sites:
        ops = set(props) - {"@"}
        if not ops or all(_mpath(mpath + [op]) in values for op in ops):
            continue
        try:
            subs = _bounds_constrained(props, jm, seen)
        except UnsupportedValue as e:
            reasons.append(str(e))
            continue
        for op, sub in subs.items():
            key = _mpath(mpath + [op])
            if key in values:
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
            except UnsupportedValue as e:

                reasons.append(str(e))

                continue
            if unverified is not None:
                values[key] = value
                unverified.add(key)
            elif _verify(value, vmodel, vjm) is True:
                values[key] = value
            else:
                skipped.append(f"{key} bound: the value does not verify here")
    if not values:
        if not reasons and not skipped:
            raise Vacuous("no constraint bound: no constraint in model")
        raise UnsupportedValue(f"no constraint bound: {_joined(reasons + skipped)}")
    else:
        return values, skipped

def optionals(model: ModelType, jm: JsonModel|None = None,
              seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
              url: str = "", extend: bool = False,
              unverified: set[str]|None = None) -> tuple[dict[str, Jsonable], list[str]]:
    """Generate a valid value per optional property, and why the others were skipped."""
    if jm is None:
        jm, model = _compile(model, True, resolver, url, extend)
    sites = list(_sites(model, [], [], [], jm, frozenset()))
    values: dict[str, Jsonable] = {}
    reasons: list[str] = []
    doc = None
    try:
        doc = simplest(model, jm, seen)
    except Vacuous:
        raise
    except UnsupportedValue as e:
        reasons.append(f"optional values: no document to alter: {e}")
    taken = set() if doc is None else {json.dumps(doc, sort_keys=True)}
    for mpath, vpath, frames, node, disjunction in _object_sites(sites):
        props = _optional_props(node, jm, seen)
        if not props:
            continue
        try:
            built = simplest(node, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"{_mpath(mpath)} optional: no object to extend: {e}")
            continue
        if not isinstance(built, dict):
            continue
        for prop, name, submodel in props:
            key = f"{_mpath(mpath + [prop])} present"
            if key in values or name in built:
                continue
            try:
                sub = {**built, name: simplest(submodel, jm, seen)}
                found = _validated(sub, vpath, frames, doc, model, jm, seen, taken,
                                   key, unverified)
            except Vacuous:
                continue
            except UnsupportedValue as e:
                reasons.append(f"{key}: {e}")
                continue
            if not found:
                reasons.append(f"{key}: adding {name} is not valid")
                continue
            value = found[0]
            dumped = json.dumps(value, sort_keys=True)
            if dumped in taken:
                continue
            values[key] = value
            taken.add(dumped)
    if not values and not reasons:
        raise Vacuous(f"no optional property in model: {_brief(model)}")
    return values, reasons

def branches(model: ModelType, jm: JsonModel|None = None,
             seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
             url: str = "", extend: bool = False,
             unverified: set[str]|None = None) -> tuple[dict[str, Jsonable], list[str]]:
    """Generate a valid value per union alternative, and why the others were skipped."""
    if jm is None:
        jm, model = _compile(model, True, resolver, url, extend)
    sites = list(_sites(model, [], [], [], jm, frozenset()))
    values: dict[str, Jsonable] = {}
    reasons: list[str] = []
    doc = None
    try:
        doc = simplest(model, jm, seen)
    except Vacuous:
        raise
    except UnsupportedValue as e:
        reasons.append(f"branch values: no document to alter: {e}")
    taken = set() if doc is None else {json.dumps(doc, sort_keys=True)}
    for mpath, vpath, frames, node, op in _alternatives(sites):
        for index, alt in enumerate(node[op]):
            if isinstance(alt, str) and alt.startswith("#"):
                continue
            key = f"{_mpath(mpath + [op, index])} branch"
            if key in values:
                continue
            try:
                sub = simplest(alt, jm, seen)
                found = _validated(sub, vpath, frames, doc, model, jm, seen, taken,
                                   key, unverified)
            except Vacuous:
                continue
            except UnsupportedValue as e:
                reasons.append(f"{key}: {e}")
                continue
            if not found:
                reasons.append(f"{key}: the alternative is not valid here")
                continue
            value = found[0]
            dumped = json.dumps(value, sort_keys=True)
            if dumped in taken:
                continue
            values[key] = value
            taken.add(dumped)
    if not values and not reasons:
        raise Vacuous(f"no union alternative in model: {_brief(model)}")
    return values, reasons

_EXPLANATIONS = (" root invalid", " root", " bound", " present", " branch",
                 " invalid", " missing", " extra", " bad")

def _label(key: str, marks: set[str], suffix: str = "") -> str:
    """Comment introducing a test vector, marked when the compiler was not asked."""
    return f"# {key}{suffix} AGREES" if key in marks else f"# {key}{suffix}"

def _note(reason: str, warn: str) -> tuple[str, list]:
    """Path and comment about a test vector which could not be generated."""
    head, sep, detail = reason.partition(": ")
    return _path(head), [f"# {head} {warn}{sep}{detail}"]

def _path(key: str) -> str:
    """Model path a comment is about, without the explanation which follows it."""
    for word in _EXPLANATIONS:
        if key.endswith(word):
            return key[:-len(word)]
    return key

def _ordered(entries: list[tuple[int, str, list]]) -> list:
    """Test vectors valid before invalid, sorted by model path inside each group."""
    def rank(entry: tuple[int, str, list]) -> tuple:
        group, path, _ = entry
        return group, tuple((1, int(s), "") if s.isdigit() else (0, 0, s)
                            for s in re.split(r"(\d+)", path))
    return [item for *_, entry in sorted(entries, key=rank) for item in entry]

_AGREES = " AGREES"

def _recheck(entries: list[tuple[int, str, list]], model: ModelType,
             resolver: Resolver|None, url: str, extend: bool) -> None:
    """Ask the validator about marked vectors, keeping the values and rewriting the marks.

    A silent validator guards the mark as UNCHECKED rather than confirming it.
    """
    marked = [entry for *_, entry in entries
              if len(entry) == 2 and isinstance(entry[0], str)
              and entry[0].endswith(_AGREES)]
    if not marked:
        return
    def remark(entry: list, verdict: str) -> None:
        entry[0] = entry[0][:-len(_AGREES)] + " " + verdict
    try:
        jm, _ = _compile(model, True, resolver, url, extend)
        defs = _defs(jm)
    except UnsupportedValue:
        for entry in marked:
            remark(entry, "UNCHECKED")
        return
    for entry in marked:
        expect, value = entry[1]
        result = _verify(value, model, jm, defs)
        if result is None:
            remark(entry, "UNCHECKED")
        elif result != expect:
            remark(entry, "DISAGREES")

def vectors(model: ModelType, resolver: Resolver|None = None, url: str = "",
            extend: bool = False, unverified: bool = False) -> list:
    """Test vectors for a model, sorted by model path, valid values before violations.

    With unverified, skip the compiler: a valid value no oracle proves is kept and
    marked, so a disagreement is visible, while a violation no oracle proves is
    dropped rather than claimed, since the model may still accept it elsewhere.
    A last pass then submits each marked value to the validator: the mark stays
    AGREES when the validator agrees with the generator and becomes DISAGREES
    when it contradicts it. A validator which answers nothing leaves UNCHECKED,
    never a confirmation.
    """
    entries: list[tuple[int, str, list]] = []
    reasons: list[str] = []
    taken: set[str] = set()
    try:
        valid = simplest(model, resolver=resolver, url=url, extend=extend)
        entries.append((0, ".", ["# . simplest", [True, valid]]))
        taken.add(json.dumps(valid, sort_keys=True))
    except Vacuous as e:
        reasons.append(str(e))
    except UnsupportedValue as e:
        reasons.append(str(e))
        entries.append((0, ".", ["# invalid model FAILED"]))
    try:
        marks: set[str] = set()
        found, skipped = _all_bounds(model, resolver=resolver, url=url, extend=extend,
                                     unverified=marks if unverified else None)
        for key, value in found.items():
            dumped = json.dumps(value, sort_keys=True)
            if dumped in taken:
                continue
            taken.add(dumped)
            entries.append((0, _path(key), [_label(key, marks, " bound"), [True, value]]))
        for reason in skipped:
            entries.append((0, *_note(reason, "FAILED")))
    except Vacuous as e:
        reasons.append(str(e))
    except UnsupportedValue as e:
        reasons.append(str(e))
        entries.append((0, ".", _note(f"bound values: {e}", "FAILED")[1]))
    for step, generate in (("optional", optionals), ("branch", branches)):
        try:
            step_marks: set[str] = set()
            found, skipped = generate(model, resolver=resolver, url=url, extend=extend,
                                      unverified=step_marks if unverified else None)
            for key, value in found.items():
                dumped = json.dumps(value, sort_keys=True)
                if dumped in taken:
                    continue
                taken.add(dumped)
                entries.append((0, _path(key), [_label(key, step_marks), [True, value]]))
            for reason in skipped:
                entries.append((0, *_note(reason, "FAILED")))
        except Vacuous as e:
            reasons.append(str(e))
        except UnsupportedValue as e:
            reasons.append(str(e))
            entries.append((0, ".", _note(f"{step} values: {e}", "FAILED")[1]))
    try:
        broken_marks: set[str] = set()
        broken, skipped = _violations(model, resolver=resolver, url=url, extend=extend,
                                      unverified=broken_marks if unverified else None,
                                      valid=frozenset(taken))
        for key, value in broken.items():
            entries.append((1, _path(key), [_label(key, broken_marks), [False, value]]))
        for reason in skipped:
            entries.append((1, *_note(reason, "SKIPPED")))
    except Vacuous as e:
        reasons.append(str(e))
    except UnsupportedValue as e:
        reasons.append(str(e))
        entries.append((1, ".", ["# invalid model FAILED"]))
    if not any(len(entry) > 1 for *_, entry in entries):
        raise UnsupportedValue(f"no test vector: {_joined(reasons)}")
    if unverified:
        _recheck(entries, model, resolver, url, extend)
    return _ordered(entries)
