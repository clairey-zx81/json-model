#! /bin/env python
#
# Generated by JSON Model Compiler version 2.0b1
# see https://github.com/clairey-zx81/json-model
#
from typing import Callable
import re2 as re
from json_model.runtime import *
__version__ = "2"

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

_jm_map_0: ConstMap = ConstMap()
check_model_map: PropMap

# object .'|'.0
def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'|'.0]", path))
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_0: Path = (path + [ prop ]) if path is not None else None
        if prop == "tag":
            # handle must tag property
            must_count += 1
            # .'|'.0.tag
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval == 18
            if not res:
                rep is None or rep.append(("unexpected =18 [.'|'.0.tag]", lpath_0 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.0.tag]", lpath_0 if path is not None else None))
                return False
        elif prop == "a":
            # handle must a property
            must_count += 1
            # .'|'.0.a
            res = isinstance(pval, str)
            if not res:
                rep is None or rep.append(("unexpected string [.'|'.0.a]", lpath_0 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.0.a]", lpath_0 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.'|'.0]", lpath_0 if path is not None else None))
            return False
    if must_count != 2:
        if rep is not None:
            if not "a" in val:
                rep is None or rep.append(("missing mandatory prop <a> [.'|'.0]", path))
            if not "tag" in val:
                rep is None or rep.append(("missing mandatory prop <tag> [.'|'.0]", path))
        return False
    return True

# object .'|'.1
def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'|'.1]", path))
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_1: Path = (path + [ prop ]) if path is not None else None
        if prop == "tag":
            # handle must tag property
            must_count += 1
            # .'|'.1.tag
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval == 42
            if not res:
                rep is None or rep.append(("unexpected =42 [.'|'.1.tag]", lpath_1 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.1.tag]", lpath_1 if path is not None else None))
                return False
        elif prop == "b":
            # handle must b property
            must_count += 1
            # .'|'.1.b
            res = isinstance(pval, str)
            if not res:
                rep is None or rep.append(("unexpected string [.'|'.1.b]", lpath_1 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.1.b]", lpath_1 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.'|'.1]", lpath_1 if path is not None else None))
            return False
    if must_count != 2:
        if rep is not None:
            if not "b" in val:
                rep is None or rep.append(("missing mandatory prop <b> [.'|'.1]", path))
            if not "tag" in val:
                rep is None or rep.append(("missing mandatory prop <tag> [.'|'.1]", path))
        return False
    return True

# object .'|'.2
def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'|'.2]", path))
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_2: Path = (path + [ prop ]) if path is not None else None
        if prop == "tag":
            # handle must tag property
            must_count += 1
            # .'|'.2.tag
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval == 1024
            if not res:
                rep is None or rep.append(("unexpected =1024 [.'|'.2.tag]", lpath_2 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.2.tag]", lpath_2 if path is not None else None))
                return False
        elif prop == "c":
            # handle must c property
            must_count += 1
            # .'|'.2.c
            res = isinstance(pval, str)
            if not res:
                rep is None or rep.append(("unexpected string [.'|'.2.c]", lpath_2 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'|'.2.c]", lpath_2 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.'|'.2]", lpath_2 if path is not None else None))
            return False
    if must_count != 2:
        if rep is not None:
            if not "c" in val:
                rep is None or rep.append(("missing mandatory prop <c> [.'|'.2]", path))
            if not "tag" in val:
                rep is None or rep.append(("missing mandatory prop <tag> [.'|'.2]", path))
        return False
    return True


# check $ (.)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # disjunction on an integer
    # .
    res = isinstance(val, dict)
    if res:
        tag_0: Jsonable = val.get("tag", UNDEFINED)
        if tag_0 != UNDEFINED:
            fun_0: CheckFun = _jm_map_0.get(tag_0, UNDEFINED)
            if fun_0 != UNDEFINED:
                res = fun_0(val, path, rep)
            else:
                res = False
                rep is None or rep.append(("tag <tag> value not found [.'|']", path))
        else:
            res = False
            rep is None or rep.append(("tag prop <tag> is missing [.'|']", path))
    else:
        rep is None or rep.append(("value is not an object [.'|']", path))
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_map_0
        _jm_map_0[18] = _jm_obj_0
        _jm_map_0[42] = _jm_obj_1
        _jm_map_0[1024] = _jm_obj_2
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
