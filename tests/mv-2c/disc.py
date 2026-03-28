#! /bin/env python
import math
from typing import Callable
import re2 as re
from json_model.runtime import *
__version__ = "2"

def check_model_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return check_model_map[name]

# entry point for generated checkers
def check_model(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity against JSON Model name."""
    if name not in check_model_map:
        raise Exception(f"unexpected model name: {name}")
    checker = check_model_map[name]
    return checker(val, [], rep)

_jm_map_0: ConstMap = ConstMap()
check_model_map: PropMap

def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval == 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, str)

def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval == 1
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0

def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval == 2
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    return pval is None

def _jm_obj_3(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval == 3
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)


def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool = isinstance(val, dict)
    if res:
        tag_0: Jsonable
        if (tag_0 := val.get("d", UNDEFINED)) != UNDEFINED:
            fun_0: CheckFun = _jm_map_0.get(tag_0, UNDEFINED)
            res = fun_0 != UNDEFINED and fun_0(val, None, None)
        else:
            res = False
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_map_0
        _jm_map_0[0] = _jm_obj_0
        _jm_map_0[1] = _jm_obj_1
        _jm_map_0[2] = _jm_obj_2
        _jm_map_0[3] = _jm_obj_3
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
