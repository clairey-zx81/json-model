#
# Common model utilities
#
import sys
import re
import logging
from .types import ModelType, ModelPath, ModelDefs, ModelError, Jsonable, JsonObject, ValueType

log = logging.getLogger("json-model")
# log.setLevel(logging.DEBUG)

def tname(m) -> str:
    return type(m).__name__ if m is not None else "null"

def is_regex(s: str, p: str = "") -> bool:
    if isinstance(s, str):
        try:
            re.compile(s)
            return True
        except Exception as e:
            # \c ControlLetter (ECMA 262 v13 - 22.2.1 p. 552)
            # \p{UnicodePropertyValueExpression} (same p. 553)
            good_anyway = re.search(r"\\[Pp]\{", s) or re.search(r"\\c[a-zA-Z]", s)
            if not good_anyway:
                log.warning(f"invalid /{s}/ at {p}: {e}")
            return good_anyway is not None
    else:
        return False

def is_cst(s) -> bool:
    return s is None or isinstance(s, str) and s and s[0] not in ("$", "/")

def cst(s: str|None):  # JsonScalar
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
    try:
        if isinstance(val, (list, tuple, str)):
            return len(val) == len(set(val))
        else:
            return False
    except TypeError as e:
        # log.warning(f"ignoring error: {e}", exc_info=True)
        log.warning(f"ignoring error: {e}")
        # try slow iterative version which relies on ==
        seen = []
        for i in val:
            if i in seen:
                return False
            else:
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


def split_object(model: JsonObject, path: ModelPath) -> tuple[JsonObject, JsonObject, JsonObject, JsonObject, JsonObject]:
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
            # FIXME /i support on keys
            assert key.endswith("/"), f"bad key: {key}"
            regs[name[:-1]] = val
        else:
            if key in must or key in may:
                raise ModelError(f"multiply defined property: {name} {path + [key]}")
            must[key] = val

    return must, may, refs, regs, others


def _bang(s):
    return s if re.match(r"[A-Za-z0-9]", s) else f"!{s}"


def unsplit_object(must: JsonObject, may: JsonObject, refs: JsonObject, regs: JsonObject, others: JsonObject) -> JsonObject:
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


def all_model_type(models: list[ModelType], mpath: ModelPath) -> tuple[bool, ModelType]:
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


def model_type(model: ModelType, mpath: ModelPath) -> tuple[bool, ModelType]:
    """Tell the type of the model, if known."""
    if model is None:
        return True, None
    elif isinstance(model, bool):
        return True, bool
    elif isinstance(model, int):
        return True, int
    elif isinstance(model, float):
        return True, float
    elif isinstance(model, str):
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
    elif isinstance(model, list):
        return True, list
    elif isinstance(model, dict):
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
    else:
        raise ModelError(f"unexpected model: {model} ({type(model).__name__})")


def resolve_model(m: ModelType, defs: ModelDefs) -> ModelType:
    """Follow definitions and @ to find the underlying type, if possible."""
    changed, resolved = True, set()
    while changed:
        # FIXME possible infinite recursion?
        changed = False
        if isinstance(m, str) and m and m[0] == "$":
            name = m[1:]
            if name not in resolved and name in defs:
                m, changed = defs[name], True
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
