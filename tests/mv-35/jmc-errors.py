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

check_model_map: PropMap

def json_model_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool = isinstance(val, list)
    if res:
        for arr_0_idx, arr_0_item in enumerate(val):
            res = isinstance(arr_0_item, int) and not isinstance(arr_0_item, bool) and arr_0_item >= 0
            if not res:
                break
    if res:
        res = is_unique_array(val, path, rep)
    return res

def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    res: bool
    for prop, pval in val.items():
        if prop == "schema":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "dynpy":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "js":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "sql":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "pl":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "java":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "c":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "py":
            res = json_model_2(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "ts":
            res = isinstance(pval, bool)
            if not res:
                return False
            continue
        elif prop == "auto.diverse":
            res = isinstance(pval, bool)
            if not res:
                return False
            continue
        if prop.startswith("#"):
            res = isinstance(pval, str)
            if not res:
                return False
        else:
            return False
    return True


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
            "ErrorIndex": json_model_2,
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
