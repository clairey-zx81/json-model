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

_jm_re_0_reco: object
_jm_re_0: RegexFun
_jm_re_1_reco: object
_jm_re_1: RegexFun
check_model_map: PropMap



def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool = isinstance(val, list)
    if res:
        for arr_1_idx, arr_1_item in enumerate(val):
            res = isinstance(arr_1_item, str) and _jm_re_1(arr_1_item, None, None)
            if not res:
                break
        if res:
            for arr_0_idx, arr_0_item in enumerate(val):
                res = isinstance(arr_0_item, str) and _jm_re_0(arr_0_item, None, None)
                if not res:
                    break
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_re_0_reco, _jm_re_0
        _jm_re_0_reco = re.compile("y")
        _jm_re_0 = lambda s, p, r: _jm_re_0_reco.search(s) is not None
        global _jm_re_1_reco, _jm_re_1
        _jm_re_1_reco = re.compile("x")
        _jm_re_1 = lambda s, p, r: _jm_re_1_reco.search(s) is not None
        global check_model_map
        check_model_map = {
            "": json_model_1,
        }

# differed module cleanup
def check_model_free():
    global initialized
    if initialized:
        initialized = False
        global _jm_re_0_reco, _jm_re_0
        _jm_re_0_reco = None
        _jm_re_0 = None
        global _jm_re_1_reco, _jm_re_1
        _jm_re_1_reco = None
        _jm_re_1 = None

if __name__ == "__main__":
    check_model_init()
    main(check_model_fun, check_model_map, __version__)
    check_model_free()
