# common model utilities
import sys
import enum
import json
import re
import copy
from typing import Any, Callable  # why not callable?

import logging
log = logging.getLogger("json-model")
# log.setLevel(logging.DEBUG)

class UnknownModel:
    pass

Object = dict[str, Any]
ValueType = None|bool|int|float|str|list[Any]|tuple[Any]|Object
ModelType = ValueType|UnknownModel

# grrr… should be callable?
CheckFun = Callable[[Any, str], bool]
KeyCheckFun = Callable[[str, Any, str], bool|None]
Compiler = Callable[[ModelType, str], CheckFun|None]

class ModelError(BaseException):
    pass

#
# UTILITY FUNCTIONS
#

def is_regex(s: str) -> bool:
    if isinstance(s, str):
        try:
            re.compile(s)
            return True
        except Exception as e:
            # \c ControlLetter (ECMA 262 v13 - 22.2.1 p. 552)
            # \p{UnicodePropertyValueExpression} (same p. 553)
            good_anyway = re.search(r"\\[Pp]\{", s) or re.search(r"\\c[a-zA-Z]", s)
            if not good_anyway:
                log.warning(f"invalid /{s}/: {e}")
            return good_anyway
    else:
        return False

def distinct_values(val):
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

def one(l) -> bool:
    """Tell if only one from an iterable is True."""
    seen = False
    for b in l:
        if b:
            if seen:
                return False  # second
            seen = True   # first
    return seen

def model_eq(m1: ModelType, m2: ModelType) -> bool:
    """Recursively compare two models…"""
    # TODO resolve @ and $
    t1, t2 = type(m1), type(m2)
    if t1 != t2:
        return False
    elif t1 == type(None):
        return True
    elif t1 in (bool, int, float, str):
        return m1 == m2
    elif t1 == list:
        if len(m1) != len(m2):
            return False
        else:  # same size, recurse
            return all(model_eq(i1, i2) for i1, i2 in zip(m1, m2))
    elif t1 == dict:  # compare contents but # $ %
        # check m1 ⊂  m2
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

def model_in_models(m: ModelType, l: list[ModelType]) -> bool:
    for i in l:
         if model_eq(i, m):
            return True
    return False

def split_object(model: dict[str, Any], path: str) -> tuple[Object, Object, Object, Object, Object]:
    """Split properties in must/may/refs/regs/other cases."""

    if not isinstance(model, dict):
        raise ModelError(f"unexpected + model: {model} [{path}]")

    if "@" in model or "|" in model or "^" in model or "+" in model or "&" in model:
        raise ModelError(f"unexpected + model: {model} [{path}]")

    # FIXME should it be lists to keep the initial order?
    must, may, refs, regs, others = {}, {}, {}, {}, {"": model[""]} if "" in model else {}

    # put each property in the expected set
    for key, val in model.items():

        if not isinstance(key, str):
            raise ModelError(f"object proprety name must be a str: {type(key)} [{path}.{key}]")

        # some (late) sanity check
        if key in ("$", "%", "#", ""):
            if key == "%" and not isinstance(val, dict):
                raise ModelError(f"{key} value must be an object: {type(key)} [{path}.{key}]")
            if key == "#" and not isinstance(val, (str, dict)):
                raise ModelError(f"{key} value must be string or object: {type(key)} [{path}.{key}]")
            if key == "$" and not isinstance(val, str):
                raise ModelError(f"{key} value must be string: {type(key)} [{path}.{key}]")
            # ignore anyway
            continue

        c, name = key[0], key[1:]

        if c in ("_", "!", "?") and (name in must or name in may):
            raise ModelError(f"multiply defined property: {name} [{path}.{key}]")

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
                raise ModelError(f"multiply defined property: {name} [{path}.{key}]")
            must[key] = val

    return must, may, refs, regs, others

def unsplit_object(must: Object, may: Object, refs: Object, regs: Object, others: Object) -> Object:
    """Regenerate an object from separated properties."""
    return {
        **{f"!{k}": v for k, v in must.items()},
        **{f"?{k}": v for k, v in may.items()},
        **{f"${k}": v for k, v in refs.items()},
        # FIXME /i support?
        **{f"/{k}/": v for k, v in regs.items()},
        **others
    }

def is_constructed(model):
    """Tell whether model is constructed, i.e. uses some combinator or indirection.

    NOTE references are assumed to be resovled beforehand.
    """
    return isinstance(model, dict) and \
        ("|" in model or "&" in model or "^" in model or "+" in model or "@" in model)

def resolve_model(m: ModelType, defs: dict[str, Any]) -> ModelType:
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
