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

check_model_map: PropMap

# object .'$A'
def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$A']", path))
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_0: Path = (path + [ prop ]) if path is not None else None
        if prop == "a":
            # handle must a property
            must_count += 1
            # .'$A'.a
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$A'.a]", lpath_0 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'$A'.a]", lpath_0 if path is not None else None))
                return False
        elif prop == "b":
            # handle must b property
            must_count += 1
            # .'$A'.b
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$A'.b]", lpath_0 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'$A'.b]", lpath_0 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.'$A']", lpath_0 if path is not None else None))
            return False
    if must_count != 2:
        if rep is not None:
            if not "a" in val:
                rep is None or rep.append(("missing mandatory prop <a> [.'$A']", path))
            if not "b" in val:
                rep is None or rep.append(("missing mandatory prop <b> [.'$A']", path))
        return False
    return True

# check $A (.'$A')
def json_model_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$A'
    res = _jm_obj_0(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$A']", path))
    return res

# object .'$B'
def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$B']", path))
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_1: Path = (path + [ prop ]) if path is not None else None
        if prop == "a":
            # handle must a property
            must_count += 1
            # .'$B'.a
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$B'.a]", lpath_1 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'$B'.a]", lpath_1 if path is not None else None))
                return False
        elif prop == "b":
            # handle must b property
            must_count += 1
            # .'$B'.b
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$B'.b]", lpath_1 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'$B'.b]", lpath_1 if path is not None else None))
                return False
        elif prop == "c":
            # handle must c property
            must_count += 1
            # .'$B'.c
            res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$B'.c]", lpath_1 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid mandatory prop value [.'$B'.c]", lpath_1 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.'$B']", lpath_1 if path is not None else None))
            return False
    if must_count != 3:
        if rep is not None:
            if not "a" in val:
                rep is None or rep.append(("missing mandatory prop <a> [.'$B']", path))
            if not "b" in val:
                rep is None or rep.append(("missing mandatory prop <b> [.'$B']", path))
            if not "c" in val:
                rep is None or rep.append(("missing mandatory prop <c> [.'$B']", path))
        return False
    return True

# check $B (.'$B')
def json_model_3(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$B'
    res = _jm_obj_1(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$B']", path))
    return res

# object .
def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.]", path))
        return False
    if len(val) == 0:
        return True
    else:
        rep is None or rep.append(("expecting empty object [.]", path))
        return False

# check $ (.)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .
    res = _jm_obj_2(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.]", path))
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global check_model_map
        check_model_map = {
            "": json_model_1,
            "A": json_model_2,
            "B": json_model_3,
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
