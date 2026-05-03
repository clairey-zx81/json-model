#! /bin/env python
import math
from typing import Callable
import re as re
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

check_model_map: PropMap

def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("c", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("f", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("c", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("e", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("c", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_3(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("b", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("f", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_4(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("b", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("e", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def _jm_obj_5(val: Jsonable, path: Path, rep: Report) -> bool:
    if len(val) != 3:
        return False
    pval: Jsonable
    if not ((pval := val.get("b", UNDEFINED)) != UNDEFINED):
        return False
    res: bool = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 0
    if not res:
        return False
    if not ((pval := val.get("a", UNDEFINED)) != UNDEFINED):
        return False
    res = isinstance(pval, int) and not isinstance(pval, bool) and pval >= 1
    if not res:
        return False
    if not ((pval := val.get("d", UNDEFINED)) != UNDEFINED):
        return False
    return isinstance(pval, bool)

def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    return isinstance(val, dict) and ("d" in val and _jm_obj_5(val, None, None) or "e" in val and _jm_obj_4(val, None, None) or "f" in val and _jm_obj_3(val, None, None) or "d" in val and _jm_obj_2(val, None, None) or "e" in val and _jm_obj_1(val, None, None) or "f" in val and _jm_obj_0(val, None, None))


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
