#
# Generate values from model
#
import copy
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
_CONSTANTS = {"=null": None, "=true": True, "=false": False}
_CATEGORIES = {
    _parser.CATEGORY_DIGIT: "0",
    _parser.CATEGORY_WORD: "a",
    _parser.CATEGORY_SPACE: " ",
}
_ANY_CHAR = "a"
_OPERATORS = {"@", "|", "&", "^", "!", "=", "!=", "<", "<=", ">", ">="}
_ROOT_KEYS = {"$", "%", "~"}
_COMPARISONS = {"=", "!=", "<", "<=", ">", ">="}
_CONSTRAINTS = _COMPARISONS | {"!"}
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
_TYPE_VIOLATIONS = [None, True, 0, "", [], {}]
_EXTRA_NAMES = ["zzz", "extra", "_x9"]
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

class UnsupportedValue(Exception):
    """No value could be generated for this model."""
    pass

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
        raise UnsupportedValue("no value exists for model: $NONE")
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
            raise UnsupportedValue(f"{index}: {e}")
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

def _names(prop: str, count: int, taken: set[str], jm: JsonModel) -> list[str]:
    """Distinct property names matching a catch-all or pattern property model."""
    try:
        seed = _ANY_CHAR if prop == "" else _simplest_regex(prop)
    except UnsupportedValue:
        return []
    names = []
    for i in range(count + len(taken) + 1):
        name = seed + _ANY_CHAR * i
        if name not in taken and _verify(name, prop, jm) is True:
            names.append(name)
            if len(names) >= count:
                break
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
            for name in _names(prop, length - len(value), set(value), jm):
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
    if (lo is None or len(base) >= lo) and (hi is None or len(base) <= hi):
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
        key = json.dumps([jm._url, {"$": defs, "@": model}], sort_keys=True)
    except (TypeError, ValueError):
        return None
    if key not in _CHECKERS:
        from .script import model_checker_from_json
        try:
            _CHECKERS[key] = model_checker_from_json(json.loads(key)[1],
                                                     resolver=jm._resolver)
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
                raise UnsupportedValue(f"{prop}: {e}")
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

def _property_name(prop: str, taken: set[str]) -> str:
    """Property name matching a pattern property, avoiding named properties."""
    name = _simplest_regex(prop)
    if name not in taken:
        return name
    pattern, opts = prop[1:].rsplit("/", 1)
    regex = re.compile(f"(?{opts}){pattern}" if opts else pattern)
    for suffix in ("0", "00", "000"):
        if name + suffix not in taken and regex.search(name + suffix):
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
                raise UnsupportedValue(f"invalid model {node._url}:{node._id}")
        if optimize:
            for node in nodes:
                optim.optimize(node)
        for node in reversed(nodes):
            merge(node)
        if optimize:
            for node in nodes:
                optim.optimize(node)
    except (ModelError, AssertionError, KeyError) as e:
        raise UnsupportedValue(f"invalid model: {e}")
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
    for mpath, vpath, frames, props in sites:
        node = props["@"]
        if (not set(props) - {"@"} and isinstance(node, dict)
                and not set(node) & (_OPERATORS | _ROOT_KEYS)):
            yield mpath, vpath, frames, node

def _pointer(path: list) -> str:
    """JSON pointer for a path of object keys and array indexes."""
    return "".join("/" + str(s).replace("~", "~0").replace("/", "~1") for s in path)

def _replaced(doc: Jsonable, path: list, value: Jsonable) -> Jsonable:
    """Copy of a document with one position set to a value."""
    result = copy.deepcopy(doc)
    node = result
    for step in path[:-1]:
        node = node[step]
    node[path[-1]] = value
    return result

def _without(model: ModelType, path: list) -> ModelType:
    """Copy of a model with one position removed."""
    result = copy.deepcopy(model)
    node = result
    for step in path[:-1]:
        node = node[step]
    del node[path[-1]]
    return result

def _sites(model: ModelType, mpath: list, vpath: list, frames: list,
           jm: JsonModel, seen: frozenset[str]):
    """Violation sites, as model path, value path, branch frames and properties."""
    if isinstance(model, str):
        name = model[1:]
        if model.startswith("$") and name in jm._defs._syms and name not in seen:
            yield from _sites(jm._defs._syms[name]._model, ["$", name], vpath,
                              frames, jm, seen | {name})
        elif model != "$ANY" and (not model.startswith("$") or name in PREDEFS):
            yield mpath, vpath, frames, {"@": model}
    elif isinstance(model, list):
        yield mpath, vpath, frames, {"@": model}
        items = [(i, m) for i, m in enumerate(model)
                 if not (isinstance(m, str) and m.startswith("#"))]
        if len(items) > 1:
            for n, (i, item) in enumerate(items):
                yield from _sites(item, mpath + [i], vpath + [n], frames, jm, seen)
    elif isinstance(model, dict):
        props = {p: m for p, m in model.items() if not p.startswith("#")}
        others = set(props) - {"@"}
        if "@" in props and others <= _CONSTRAINTS:
            if others:
                yield mpath, vpath, frames, props
            yield from _sites(props["@"], mpath + ["@"], vpath, frames, jm, seen)
        elif set(props) in ({"|"}, {"^"}, {"&"}):
            op = next(iter(props))
            yield mpath, vpath, frames, {"@": model}
            for index, alt in enumerate(props[op]):
                if isinstance(alt, str) and alt.startswith("#"):
                    continue
                yield from _sites(alt, mpath + [op, index], vpath,
                                  frames + [(vpath, alt)], jm, seen)
        elif not set(props) & (_OPERATORS | _ROOT_KEYS):
            yield mpath, vpath, frames, {"@": model}
            named = {p[1:] if p.startswith(("!", "?", "_")) else p
                     for p in props if p and not p.startswith(("/", "$"))}
            for prop, sub in props.items():
                if prop == "" or prop.startswith("$"):
                    continue
                elif prop.startswith("/"):
                    try:
                        name = _property_name(prop, named)
                    except UnsupportedValue:
                        continue
                    inner = frames + [(vpath + [name], sub)]
                else:
                    name = prop[1:] if prop.startswith(("!", "?", "_")) else prop
                    inner = (frames + [(vpath + [name], sub)] if prop.startswith("?")
                             else frames)
                yield from _sites(sub, mpath + [prop], vpath + [name], inner, jm, seen)
    else:
        yield mpath, vpath, frames, {"@": model}

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

def violations(model: ModelType, jm: JsonModel|None = None,
               seen: frozenset[str] = frozenset(), resolver: Resolver|None = None,
               url: str = "", extend: bool = False) -> dict[str, Jsonable]:
    """Generate a value breaking one constraint, type or property of a model."""
    vjm, vmodel = jm, model
    if jm is None:
        jm, model = _compile(model, False, resolver, url, extend)
        vjm, vmodel = _compile(vmodel, True, resolver, url, extend)
    sites = list(_sites(model, [], [], [], jm, frozenset()))
    if not sites:
        raise UnsupportedValue(f"no constraint in model: {model}")
    defs = _defs(jm)
    values: dict[str, Jsonable] = {}
    reasons: list[str] = []
    doc = None
    if any(f[0][0] if f else v for _, v, f, _ in sites):
        try:
            doc = simplest(model, jm, seen)
        except UnsupportedValue as e:
            reasons.append(f"no document to alter: {e}")
    for mpath, vpath, frames, props in sites:
        ops = set(props) - {"@"}
        if not ops or all(_pointer(mpath + [op]) in values for op in ops):
            continue
        try:
            subs = _violations_constrained(props, jm, seen)
        except UnsupportedValue as e:
            reasons.append(str(e))
            continue
        for op, sub in subs.items():
            key = _pointer(mpath + [op])
            if key in values:
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
                if mpath and mpath[0] == "$":
                    rest, rdefs = model, _without(defs, mpath[1:] + [op])
                else:
                    rest, rdefs = _without(model, mpath + [op]), defs
            except (UnsupportedValue, KeyError, IndexError, TypeError):
                continue
            if _verify(value, vmodel, vjm) is False and _verify(value, rest, jm, rdefs) is True:
                values[key] = value
    taken = {json.dumps(v, sort_keys=True) for v in values.values()}
    for mpath, vpath, frames, props in sites:
        key = _pointer(mpath)
        if set(props) - {"@"} or key in values:
            continue
        for candidate in _TYPE_VIOLATIONS:
            if _verify(candidate, props["@"], jm, defs) is not False:
                continue
            try:
                value = _document(copy.deepcopy(candidate), vpath, frames, doc, jm, seen)
            except (UnsupportedValue, KeyError, IndexError, TypeError):
                break
            if json.dumps(value, sort_keys=True) in taken:
                break
            elif _verify(value, vmodel, vjm) is False:
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
                break
    for mpath, vpath, frames, node in _object_sites(sites):
        try:
            built = simplest(node, jm, seen)
        except UnsupportedValue:
            continue
        if not isinstance(built, dict):
            continue
        for prop, name in _mandatory(node):
            key = f"{_pointer(mpath + [prop])} missing"
            if key in values or name not in built:
                continue
            sub = {p: v for p, v in built.items() if p != name}
            if _verify(sub, _optional(node, prop, name), jm, defs) is not True:
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
            except (UnsupportedValue, KeyError, IndexError, TypeError):
                break
            if json.dumps(value, sort_keys=True) in taken:
                continue
            elif _verify(value, vmodel, vjm) is False:
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
    for mpath, vpath, frames, node in _object_sites(sites):
        if not _closed(node, jm):
            continue
        try:
            built = simplest(node, jm, seen)
        except UnsupportedValue:
            continue
        if not isinstance(built, dict):
            continue
        for name in _EXTRA_NAMES:
            key = f"{_pointer(mpath + [name])} extra"
            if name in built or key in values:
                continue
            sub = {**built, name: None}
            if (_verify(sub, node, jm, defs) is not False
                    or _verify(sub, _opened(node), jm, defs) is not True):
                continue
            try:
                value = _document(sub, vpath, frames, doc, jm, seen)
            except (UnsupportedValue, KeyError, IndexError, TypeError):
                break
            if json.dumps(value, sort_keys=True) in taken:
                break
            elif _verify(value, vmodel, vjm) is False:
                values[key] = value
                taken.add(json.dumps(value, sort_keys=True))
                break
    if not values:
        raise UnsupportedValue(f"no constraint could be violated: {'; '.join(reasons)}")
    else:
        return values

def vectors(model: ModelType, resolver: Resolver|None = None, url: str = "",
            extend: bool = False) -> list:
    """Test vectors for a model, a valid value then one value per violation."""
    tests: list = []
    reasons: list[str] = []
    try:
        tests.append([True, simplest(model, resolver=resolver, url=url, extend=extend)])
    except UnsupportedValue as e:
        reasons.append(str(e))
    try:
        for key, value in violations(model, resolver=resolver, url=url,
                                     extend=extend).items():
            tests.append(key or "root")
            tests.append([False, value])
    except UnsupportedValue as e:
        reasons.append(str(e))
    if not tests:
        raise UnsupportedValue(f"no test vector: {'; '.join(reasons)}")
    return tests
