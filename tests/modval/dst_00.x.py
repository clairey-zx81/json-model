#! /bin/env python
#
# Generated by JSON Model Compiler version 2.0a0
# see https://github.com/clairey-zx81/json-model
#
from typing import Callable
import re2 as re
from json_model.runtime import *
__version__ = "2.0a0"

def check_model_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return check_model_map[name]

# entry point for generated checkers
def check_model(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity agains JSON Model name."""
    if name not in check_model_map:
        raise Exception(f"unexpected model name: {name}")
    checker = check_model_map[name]
    return checker(val, [], rep)

_jm_obj_0_must: PropMap
_jm_obj_1_must: PropMap
check_model_map: PropMap

# check _jm_obj_0_must_a ($.'|'.1.a)
def _jm_f_0(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # $.'|'.1.a
    res = isinstance(val, int) and not isinstance(val, bool) and val >= 0
    if not res:
        rep is None or rep.append(("not a 0 strict int [$.'|'.1.a]", path))
    return res

# check _jm_obj_0_must_c ($.'|'.1.c)
def _jm_f_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # $.'|'.1.c
    res = isinstance(val, str)
    if not res:
        rep is None or rep.append(("unexpected string [$.'|'.1.c]", path))
    return res


# object $.'|'.1
def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [$.'|'.1]", path))
        return False
    pfun: CheckFun
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_0: Path = (path + [ prop ]) if path is not None else None
        if pfun := _jm_obj_0_must.get(prop):
            # handle 2 must props
            if pfun != UNDEFINED:
                must_count += 1
                if not pfun(pval, lpath_0 if path is not None else None, rep):
                    rep is None or rep.append(("invalid must property value [$.'|'.1]", lpath_0 if path is not None else None))
                    return False
        else:
            rep is None or rep.append(("no other prop expected [$.'|'.1]", lpath_0 if path is not None else None))
            return False
    if must_count != 2:
        rep is None or rep.append(("missing must prop [$.'|'.1]", path))
        return False
    return True

# check _jm_obj_1_must_a ($.'|'.0.a)
def _jm_f_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # $.'|'.0.a
    res = isinstance(val, int) and not isinstance(val, bool) and val >= 0
    if not res:
        rep is None or rep.append(("not a 0 strict int [$.'|'.0.a]", path))
    return res

# check _jm_obj_1_must_b ($.'|'.0.b)
def _jm_f_3(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # $.'|'.0.b
    res = isinstance(val, int) and not isinstance(val, bool) and val >= 1
    if not res:
        rep is None or rep.append(("not a 1 strict int [$.'|'.0.b]", path))
    return res


# object $.'|'.0
def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [$.'|'.0]", path))
        return False
    pfun: CheckFun
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_1: Path = (path + [ prop ]) if path is not None else None
        if pfun := _jm_obj_1_must.get(prop):
            # handle 2 must props
            if pfun != UNDEFINED:
                must_count += 1
                if not pfun(pval, lpath_1 if path is not None else None, rep):
                    rep is None or rep.append(("invalid must property value [$.'|'.0]", lpath_1 if path is not None else None))
                    return False
        else:
            rep is None or rep.append(("no other prop expected [$.'|'.0]", lpath_1 if path is not None else None))
            return False
    if must_count != 2:
        rep is None or rep.append(("missing must prop [$.'|'.0]", path))
        return False
    return True

# check $ ($)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # $
    res = isinstance(val, dict)
    if not res:
        rep is None or rep.append(("unexpected type at [$.'|']", path))
    if res:
        # $.'|'.0
        res = _jm_obj_1(val, path, rep)
        if not res:
            rep is None or rep.append(("not an expected object at [$.'|'.0]", path))
        if not res:
            # $.'|'.1
            res = _jm_obj_0(val, path, rep)
            if not res:
                rep is None or rep.append(("not an expected object at [$.'|'.1]", path))
        if not res:
            rep is None or rep.append(("no model matched [$.'|']", path))
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_obj_0_must
        _jm_obj_0_must = {
            "a": _jm_f_0,
            "c": _jm_f_1,
        }
        global _jm_obj_1_must
        _jm_obj_1_must = {
            "a": _jm_f_2,
            "b": _jm_f_3,
        }
        global check_model_map
        check_model_map = {
            "": json_model_1,
        }

# differed module cleanup
def check_model_free():
    global initialized
    if initialized:
        initialized = False


if __name__ == "__main__":
    check_model_init()
    main(check_model_fun, check_model_map, __version__)
    check_model_free()
