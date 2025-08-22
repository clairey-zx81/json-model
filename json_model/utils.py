#
# Common model utilities
#
import sys
import re
import json
from importlib.metadata import version as pkg_version
from importlib.resources import files as data_files
import logging
from .mtypes import ModelType, ModelPath, ModelError, ModelObject
from .mtypes import Jsonable, JsonObject, ValueType, Symbols

__version__ = pkg_version("json_model_compiler")

log = logging.getLogger("json-model")
# log.setLevel(logging.DEBUG)

MODEL_PREDEFS = {
    "$ANY", "$NONE", "$NULL", "$BOOL", "$BOOLEAN",
    "$INT", "$INTEGER", "$I32", "$I64", "$U32", "$U64",
    "$FLOAT", "$F32", "$F64", "$NUMBER",
    "$STRING", "$DATE", "$TIME", "$DATETIME",
    "$URL", "$REGEX", "$EXREG", "$UUID",
    "$URI", "$EMAIL", "$JSON",
    # TODO $URI-REF, $DOMAIN…
}

ANY_STR_RE = r"(?s).*"
WEAK_DATE_RE = r"\d{4}-(0?[1-9]|1[012])-(0?[1-9]|[12]\d|3[01])"
WEAK_TIME_RE = r"([01]?[0-9]|2[0-4]):[0-5]?[0-9]:[0-5]?[0-9](\.\d+)?"
TZ_RE = r"(Z|[-+]\d+)?"
UUID_RE = r"(?i)[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}"
CONST_RE = r"^=(null|true|false|-?\d+(\.\d+)?([eE]-?\d+)?)$"
JSKW_RE = r"^([#~$%@|&+^/*=]|[<>!]=?)$"
URL_RE = r"((https?|file)://.*|\..*)"
EMAIL_RE = r"[-_a-zA-Z0-9.]+@[-_a-zA-Z0-9.]+"

# (approximate) regular expressions for some predefs
PREDEF_RE = {
    "$STRING": ANY_STR_RE,
    "$DATE": WEAK_DATE_RE,
    "$TIME": WEAK_TIME_RE,
    "$DATETIME": WEAK_DATE_RE + "[ T]" + WEAK_TIME_RE + TZ_RE,
    "$UUID": UUID_RE,
    "$REGEX": ANY_STR_RE,
    "$EXREG": ANY_STR_RE,
    "$URL": URL_RE,
    "$URI": URL_RE,
    "$EMAIL": EMAIL_RE,
}

def tname(m) -> str:
    return type(m).__name__ if m is not None else "null"

def is_regex(s: ValueType, p: str = "") -> bool:
    if isinstance(s, str):
        try:
            re.compile(s)
            return True
        except Exception as e:
            # probably only "simple" re should be accepted, see JSON Schema approach
            # \c ControlLetter (ECMA 262 v13 - 22.2.1 p. 552)
            # \p{UnicodePropertyValueExpression} (same p. 553)
            good_anyway = re.search(r"\\[Pp]\{", s) or re.search(r"\\c[a-zA-Z]", s)
            if not good_anyway:
                log.warning(f"invalid /{s}/ at {p}: {e}")
            return good_anyway is not None
    else:
        return False

def is_cst(s: Jsonable) -> bool:
    return s is None or isinstance(s, str) and s != "" and s[0] not in ("$", "/")

def cst(s: str|None) -> None|bool|int|float|str:  # JsonScalar
    if s is None:
        return None
    elif s[0] == "_":
        return s[1:]
    elif s[0] == "=":
        if s == "=null":
            return None
        elif s == "=true":
            return True
        elif s == "=false":
            return False
        elif "." in s or "e" in s or "E" in s:
            return float(s[1:])
        else:
            return int(s[1:])
    else:
        return s

def distinct_values(val: Jsonable) -> bool:
    # stupid implementation because True == 1
    if isinstance(val, (list, tuple, str)):
        seen = []
        for i in val:
            if any(map(lambda v: type(v) is type(i) and v == i, seen)):
                return False
            seen.append(i)
    return True

def one(lb) -> bool:
    """Tell if only one from an iterable is True."""
    seen = False
    for b in lb:
        if b:
            if seen:
                return False  # second
            seen = True   # first
    return seen

def model_eq(m1: ModelType, m2: ModelType) -> bool:
    """Recursively compare two models…"""
    # TODO resolve @ and $
    t1, t2 = type(m1), type(m2)
    if t1 is not t2:
        return False
    elif t1 is type(None):
        return True
    elif t1 in (bool, int, float, str):
        return m1 == m2
    elif t1 is list:
        assert isinstance(m1, list) and isinstance(m2, list)  # type hint
        if len(m1) != len(m2):
            return False
        else:  # same size, recurse
            return all(model_eq(i1, i2) for i1, i2 in zip(m1, m2))
    elif t1 is dict:  # compare contents but # $ %
        # check m1 ⊂  m2
        assert isinstance(m1, dict) and isinstance(m2, dict)  # type hint helper
        for p in m1.keys():
            if p not in ("#", "%", "$"):
                if p not in m2:
                    return False
                if not model_eq(m1[p], m2[p]):
                    return False
        # check m2 ⊂  m1
        for p in m2.keys():
            if p not in ("#", "%", "$") and p not in m1:
                return False
        # m1 == m2
        return True
    else:
        raise ModelError(f"unexpected model element type ({t1.__name__})")

# TODO maybe we should accept some simple type inclusions
def same_model(m1: ModelType, m2: ModelType) -> bool:
    """Compare models…"""
    # beware that True == 1 and False == 0
    # return type(m1) == type(m2) and m1 == m2
    return model_eq(m1, m2)

def model_in_models(m: ModelType, lm: list[ModelType]) -> bool:
    for i in lm:
        if model_eq(i, m):
            return True
    return False

def split_object(model: JsonObject, path: ModelPath) -> \
        tuple[JsonObject, JsonObject, JsonObject, JsonObject, JsonObject]:
    """Split properties in must/may/refs/regs/other cases."""

    if not isinstance(model, dict):
        raise ModelError(f"unexpected + model: {model} {path}")

    if "@" in model or "|" in model or "^" in model or "+" in model or "&" in model:
        raise ModelError(f"unexpected + model: {model} {path}")

    # FIXME should it be lists to keep the initial order?
    must, may, refs, regs, others = {}, {}, {}, {}, {"": model[""]} if "" in model else {}

    # put each property in the expected set
    for key, val in model.items():

        if not isinstance(key, str):
            raise ModelError(f"object proprety name must be a str: {tname(key)} {path + [key]}")

        # some (late) sanity check
        if key in ("$", "%", "#", ""):
            if key == "%" and not isinstance(val, dict):
                raise ModelError(f"{key} value must be an object: {tname(key)} {path + [key]}")
            if key == "#" and not isinstance(val, (str, dict)):
                raise ModelError(
                    f"{key} value must be string or object: {tname(key)} {path + [key]}"
                )
            if key == "$" and not isinstance(val, str):
                raise ModelError(f"{key} value must be string: {tname(key)} {path + [key]}")
            # ignore anyway
            continue

        c, name = key[0], key[1:]

        if c in ("_", "!", "?") and (name in must or name in may):
            raise ModelError(f"multiply defined property: {name} {path + [key]}")

        if c == "_" or c == "!":
            must[name] = val
        elif c == "?":
            may[name] = val
        elif c == "$":
            refs[name] = val
        elif c == "/":
            if key.endswith("/"):
                regex = name[:-1]
            else:
                regex, options = name.rsplit("/", 1)
                regex = f"(?{options}){regex}"
            regs[regex] = val
        else:
            if key in must or key in may:
                raise ModelError(f"multiply defined property: {name} {path + [key]}")
            must[key] = val

    return must, may, refs, regs, others

def _bang(s):
    return s if re.match(r"[A-Za-z0-9]", s) else f"!{s}"

def unsplit_object(must: JsonObject, may: JsonObject, refs: JsonObject,
                   regs: JsonObject, others: JsonObject) -> JsonObject:
    """Regenerate an object from separated properties."""
    return {
        **{_bang(k): v for k, v in must.items()},
        **{f"?{k}": v for k, v in may.items()},
        **{f"${k}": v for k, v in refs.items()},
        # FIXME /i support?
        **{f"/{k}/": v for k, v in regs.items()},
        **others
    }

def is_constructed(model: ModelType):
    """Tell whether model is constructed, i.e. uses some combinator or indirection.

    NOTE references are assumed to be resolved beforehand.
    """
    return isinstance(model, dict) and \
        ("|" in model or "&" in model or "^" in model or "+" in model or "@" in model)

def constant_value(m: ModelType, mpath: ModelPath) -> tuple[bool, ValueType]:
    if m is None:
        return True, None
    elif isinstance(m, str):
        char = m[0] if m else ""
        if char == "=":
            val = m[1:]
            if val == "null":
                return True, None
            elif val == "true":
                return True, True
            elif val == "false":
                return True, False
            elif re.search(r"^-?[0-9]+$", val):
                return True, int(val)
            else:  # float?
                try:
                    return True, float(val)
                except Exception:
                    raise ModelError(f"unexpected float value {val} [{mpath}]")
        elif char == "_":
            return True, m[1:]
        elif char == "/":
            return False, None
        elif char == "$":
            return False, None
        elif len(m) > 0:
            return True, m
        else:
            return False, None
    else:
        return False, None

def all_model_type(models: list[ModelType], mpath: ModelPath) -> tuple[bool, type|None]:
    first, current_type = True, None
    for i, m in enumerate(models):
        is_known, has_type = model_type(m, mpath + [i])
        if is_known:
            if first:
                current_type = has_type
                first = False
            elif current_type != has_type:
                return False, None
        else:
            return False, None
    if first:
        # empty list
        return False, None
    else:
        return True, current_type

def model_type(model: ModelType, mpath: ModelPath) -> tuple[bool, type|None]:
    """Tell the type of the model, if known."""
    match model:
        case None:
            return True, None
        case bool():
            return True, bool
        case int():
            return True, int
        case float():
            return True, float
        case str():
            if model in ("", "$STRING"):
                return True, str
            elif model[0] in ("_", "/"):
                return True, str
            elif model == "$BOOL":
                return True, bool
            elif model == "$NULL":
                return True, None
            elif model in ("$INTEGER", "$I32", "$U32", "$I64", "$U64"):
                return True, int
            elif model in ("$FLOAT", "$F32", "$F64"):
                return True, float
            elif model[0] == "$":
                # how to access definitions?
                return False, None
            elif model[0] == "=":
                # handle constants
                a_cst, val = constant_value(model, mpath)
                if a_cst:
                    return True, type(val)
                else:
                    return False, None
            else:
                return True, str
        case list():
            return True, list
        case dict():
            if "@" in model:
                return model_type(model["@"], mpath + ["@"])
            elif "|" in model:
                models = model["|"]
                assert isinstance(models, list)
                return all_model_type(models, mpath + ["|"])
            elif "&" in model:
                models = model["&"]
                assert isinstance(models, list)
                return all_model_type(models, mpath + ["&"])
            elif "^" in model:
                models = model["^"]
                assert isinstance(models, list)
                return all_model_type(models, mpath + ["^"])
            elif "+" in model:
                return True, dict
            else:  # simple object!
                return True, dict
        case _:
            raise ModelError(f"unexpected model: {model} ({tname(model)})")

def resolve_model(m: ModelType, defs: Symbols) -> ModelType:
    """Follow definitions and @ to find the underlying type, if possible."""
    changed, resolved = True, set()
    while changed:
        # FIXME possible infinite recursion?
        changed = False
        if isinstance(m, str) and m != "" and m[0] == "$":
            name = m[1:]
            if name not in resolved and name in defs:
                m, changed = defs[name]._model, True  # pyright: ignore
            resolved.add(name)
        if isinstance(m, dict) and "@" in m:
            m, changed = m["@"], True
    return m

def openfiles(args: list[str] = []):
    if not args:  # empty list is same as stdin
        args = ["-"]
    for fn in args:
        if fn == "-":
            yield fn, sys.stdin
        else:
            with open(fn) as fh:
                yield fn, fh

def _dedup_models(models: list[ModelType]) -> list[ModelType]:
    dedups = []
    for m in models:
        if not model_in_models(m, dedups):
            dedups.append(m)
    return dedups

# FIXME consistency with _structurally_distinct_models…
def _distinct_models(m1: ModelType, m2: ModelType, defs: Symbols, mpath: ModelPath) -> bool:
    """Whether m1 and m2 are provably distinct, i.e. do not have values in common."""
    m1, m2 = resolve_model(m1, defs), resolve_model(m2, defs)
    # log.warning(f"m1={m1} m2={m2}")
    # type
    if isinstance(m1, str) and m1 and m1[0] == "$":  # unresolved reference
        return m1 == "$NONE"  # special case for none which interact with nothing
    if isinstance(m2, str) and m2 and m2[0] == "$":  # unresolved reference
        return m2 == "$NONE"
    if is_constructed(m1) or is_constructed(m2):
        return False
    if type(m1) is not type(m2):
        # log.warning("distinct!")
        return True
    # else same type… try value
    c1, v1 = constant_value(m1, mpath)
    c2, v2 = constant_value(m2, mpath)
    # log.warning(f"{c1} {v1} / {c2} {v2}")
    if c1 and c2 and (type(v1) is not type(v2) or v1 != v2):
        return True
    return False


class _Object:
    """Internal representation of an object model."""

    def __init__(self, model: ModelType, gdefs: Symbols, mpath: ModelPath):
        assert isinstance(model, dict)
        must, may, defs, regs, oth = split_object(model, mpath)
        self._must = must
        self._may = may
        self._defs = defs
        self._regs = regs
        self._oth = oth
        self._global_defs = gdefs
        self._mpath = mpath

    def __contains__(self, o):
        """Whether o may be included in self (safe).

        That is all mandatory properties of o may be accepted by self.
        We could do a better job by checking model target incompatibility.
        """
        if not isinstance(o, _Object):
            raise ModelError("Only objects can be compared")
        if self._defs:
            # FIXME improve?
            log.debug("$-reference keys are not handled")
            return True
        # we look for mandatory one property in o which allows to discriminate
        for p, m in o._must.items():
            if p in self._must:
                if _distinct_models(m, self._must[p], self._global_defs, self._mpath):
                    return False
                # o.p does not discriminate with self
                continue
            elif p in self._may:
                if _distinct_models(m, self._may[p], self._global_defs, self._mpath):
                    return False
                continue
            for reg, model in self._regs.items():
                if re.search(reg, p):
                    # TODO catch more $NONE cases?
                    if model == "$NONE":
                        return False
                    # else try model resolution… this may depend on the execution order?
                    resolved = resolve_model(model, self._global_defs)
                    if resolved == "$NONE":
                        return False
                    if _distinct_models(m, model, self._global_defs, self._mpath):
                        return False
                    # else o.p does not discrimate
                    continue
            if "" in self._oth:
                if _distinct_models(m, self._oth[""], self._global_defs, self._mpath):
                    return False
                # self is open so would accept p
                continue
            # else: p is not must nor may nor re nor others!
            return False
        # we did not found any sure discrimination on this way
        return True


def merge_objects(models: list[ModelObject], path: ModelPath) -> JsonObject|str:
    """Merge a list of simple object models."""

    assert isinstance(models, list) and len(models) > 0

    m0 = models[0]
    must, may, refs, regs, others = split_object(m0, path + [0])

    for i, m in enumerate(models[1:]):

        lpath = path + [i + 1]
        mu, ma, rf, rg, ot = split_object(m, lpath)

        # combine all properties
        # merge MUST
        for prop, mod in mu.items():
            lppath = path + [prop]
            if prop in must:
                mumod = must[prop]
                if mumod != "$ANY" and mod != "$ANY" and not same_model(mod, mumod):
                    raise ModelError(f"incompatible must property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else keep best
                if mod != "$ANY" and mumod == "$ANY":
                    must[prop] = mod
            elif prop in may:
                mamod = may[prop]
                if mamod != "$ANY" and mod != "$ANY" and not same_model(mod, mamod):
                    raise ModelError(f"incompatible must property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                must[prop] = mod if mod != "$ANY" else mamod
                del may[prop]
            else:  # new mandatory property
                must[prop] = mod

        # merge MAY
        for prop, mod in ma.items():
            lppath = path + [prop]
            if prop in must:
                mumod = must[prop]
                if mod != "$ANY" and "mumod" != "$ANY" and not same_model(mod, must[prop]):  # ???
                    raise ModelError(f"incompatible may property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else keep best
                if mod != "$ANY" and mumod == "$ANY":
                    must[prop] = mod
            elif prop in may:
                mamod = may[prop]
                if mod != "$ANY" and mamod != "$ANY" and not same_model(mod, mamod):
                    raise ModelError(f"incompatible may property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else keep best
                if mod != "$ANY" and mamod == "$ANY":
                    may[prop] = mod
            else:  # new optional property
                may[prop] = mod

        # merge MAYBE
        def mergeMaybe(dst, src, cat: str, path: ModelPath):
            for prop, mod in src.items():
                lppath = path + [prop]
                if prop in dst:
                    dstmod = dst[prop]
                    if mod != "$ANY" and dstmod != "$ANY" and not same_model(mod, dstmod):
                        raise ModelError(f"incompatible {cat} property {prop} while merging:"
                                         f"{m0} / {m} {lppath}")
                    # else keep best
                    if mod != "$ANY" and dstmod == "$ANY":
                        dst[prop] = mod
                else:  # new property
                    dst[prop] = mod

        mergeMaybe(refs, rf, "refs", path)
        mergeMaybe(regs, rg, "regs", path)

        # merge OTHERS
        if "" in ot:
            mod = ot[""]
            if "" in others:
                omod = others[""]
                if mod != "$ANY" and omod != "$ANY" and not same_model(mod, omod):
                    raise ModelError("incompatible catchall while merging: "
                                     f"{m0} / {m} [{lpath}.'']")
                # else keep best
                if mod != "$ANY" and omod == "$ANY":
                    others[""] = mod
            else:  # new catchall
                others = ot

    return unsplit_object(must, may, refs, regs, others)


def _structurally_distinct_models(lm: list[ModelType], defs: Symbols, mpath: ModelPath) -> bool:
    """Whether all models are structurally distinct.

    This ensures that values in these are distinct.
    """
    log.debug(f"distinct on {lm}")
    # TODO add other constant values?
    types, objects, strings = set(), [], set()
    for m in lm:
        m = resolve_model(m, defs)
        mt = type(m)
        # special str preprocessing
        if isinstance(m, str):
            if m.startswith("$"):  # unresolved reference
                log.debug("- unresolved $-reference")
                return False
            elif m.startswith("="):
                c, v = constant_value(m, mpath)
                assert c
                m, mt = v, type(v)
            # else: empty or re or str constant

        if mt in (type(None), bool, int, float, list):
            if mt in types:
                log.debug(f"- multiple type {mt.__name__}")
                return False
            types.add(mt)
        elif isinstance(m, str):
            if m == "" or m[0] == "/":  # generic string
                if str in types or strings:
                    log.debug("- multiple strings")
                    return False
                types.add(str)
            else:  # constant string
                if str in types:
                    log.debug("- constant strings")
                    return False
                if m[0] == "_":
                    m = m[1:]
                # ???
                if m in strings:
                    log.warning(f"repeated constant: {m} {mpath}")
                    log.debug("- repeated constant strings")
                    return False
                strings.add(m)
        elif isinstance(m, dict):
            if "+" in m:  # may try later, after merging
                return False
            assert "@" not in m  # should have been resolved!
            # assert "+" not in m  # should have been merged!
            if is_constructed(m):
                log.debug(f"- constructed model: {m}")
                return False
            # else dict is a model for an object
            obj = _Object(m, defs, mpath)
            # distinguishable objects?
            # - each object has a mandatory prop which cannot exists in others objects
            #   possibly with one exception
            if not objects:  # first encounted object
                objects.append(obj)
            else:
                for o in objects:
                    if o in obj and obj in o:
                        log.debug("- conflicting objects")
                        return False
                objects.append(obj)
        else:
            raise ModelError(f"unexpected model type ({mt.__name__}) {mpath}")
    return True

def json_loads(j: str, *, allow_duplicates: bool = False) -> Jsonable:
    """Load JSON, possibly rejecting duplicated keys."""
    if allow_duplicates:
        dict_nodups = None  # type: ignore
    else:
        def dict_nodups(pairs):
            d = {}
            for (k, v) in pairs:
                if k in d:
                    raise ValueError(f"duplicated key {k} found while building JSON object")
                d[k] = v
            return d
    return json.loads(j, object_pairs_hook=dict_nodups)

def is_obj_model(model: ModelType, keywords: set[str]) -> bool:
    """Whether object model is restricted to these keywords and possibly comments."""
    if not isinstance(model, dict):
        return False
    for prop in model:
        if not prop.startswith("#") and prop not in keywords:
            return False
    return True

def load_data_file(fn: str) -> str:
    return data_files("json_model.data").joinpath(fn).read_text()
