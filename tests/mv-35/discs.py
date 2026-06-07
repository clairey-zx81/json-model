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

_jm_map_0: dict[str, str]
check_model_map: PropMap

def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "n"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return pval is None

def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "b"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "i"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, int) and not isinstance(pval, bool)

def _jm_obj_3(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "u"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0

def _jm_obj_4(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "f"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, float)

def _jm_obj_5(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "s"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, str)

def _jm_obj_6(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "a"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, list)

def _jm_obj_7(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    if len(val) != 2:
        return False
    pval: Jsonable
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, str) and pval == "o"
    if not res:
        return False
    if not ((pval := val.get("v", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, dict)


def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool = isinstance(val, dict)
    if res:
        tag_0: Jsonable
        if (tag_0 := val.get("d", UNDEFINED)) != UNDEFINED:
            fun_0: CheckFun = _jm_map_0.get(tag_0, UNDEFINED) if not isinstance(tag_0, (list, dict)) else UNDEFINED
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
        _jm_map_0 = {
            "n": _jm_obj_0,
            "b": _jm_obj_1,
            "i": _jm_obj_2,
            "u": _jm_obj_3,
            "f": _jm_obj_4,
            "s": _jm_obj_5,
            "a": _jm_obj_6,
            "o": _jm_obj_7,
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
