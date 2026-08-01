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
check_model_map: PropMap


def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        return False
    res: bool
    must_count: int = 0
    for prop, pval in val.items():
        if prop == "name":
            must_count += 1
            res = isinstance(pval, str) and _jm_re_0(pval, None, None)
            if not res:
                return False
            continue
        elif prop == "birth":
            must_count += 1
            res = is_valid_date(pval, None, rep)
            if not res:
                return False
            continue
        if prop == "friends":
            res = isinstance(pval, list)
            if res:
                for arr_0_idx, arr_0_item in enumerate(pval):
                    res = isinstance(arr_0_item, str) and _jm_re_0(arr_0_item, None, None)
                    if not res:
                        break
            if not res:
                return False
            continue
        return False
    return must_count == 2


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_re_0_reco, _jm_re_0
        _jm_re_0_reco = re.compile("(?s)^\\w+$")
        _jm_re_0 = lambda s, p, r: _jm_re_0_reco.search(s) is not None
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

if __name__ == "__main__":
    check_model_init()
    main(check_model_fun, check_model_map, __version__)
    check_model_free()
