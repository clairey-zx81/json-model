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

# check $li0 (.'$li0')
def json_model_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$li0'
    res = isinstance(val, list)
    if res:
        for arr_0_idx, arr_0_item in enumerate(val):
            arr_0_lpath: Path = (path + [ arr_0_idx ]) if path is not None else None
            # .'$li0'.0
            res = isinstance(arr_0_item, int) and not isinstance(arr_0_item, bool) and arr_0_item >= 0
            if not res:
                rep is None or rep.append(("not a 0 strict int [.'$li0'.0]", arr_0_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$li0']", path))
    return res

# check $ls0 (.'$ls0')
def json_model_3(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$ls0'
    res = isinstance(val, list)
    if res:
        for arr_1_idx, arr_1_item in enumerate(val):
            arr_1_lpath: Path = (path + [ arr_1_idx ]) if path is not None else None
            # .'$ls0'.0
            res = is_valid_url(arr_1_item, arr_1_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $URL [.'$ls0'.0]", arr_1_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$ls0']", path))
    return res

# check $lb0 (.'$lb0')
def json_model_4(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$lb0'
    res = isinstance(val, list)
    if res:
        for arr_2_idx, arr_2_item in enumerate(val):
            arr_2_lpath: Path = (path + [ arr_2_idx ]) if path is not None else None
            # .'$lb0'.0
            res = isinstance(arr_2_item, bool)
            if not res:
                rep is None or rep.append(("unexpected $BOOL [.'$lb0'.0]", arr_2_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$lb0']", path))
    return res

# check $lf0 (.'$lf0')
def json_model_5(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$lf0'
    res = isinstance(val, list)
    if res:
        for arr_3_idx, arr_3_item in enumerate(val):
            arr_3_lpath: Path = (path + [ arr_3_idx ]) if path is not None else None
            # .'$lf0'.0
            res = isinstance(arr_3_item, float) and arr_3_item >= 0.0
            if not res:
                rep is None or rep.append(("not a 0.0 strict float [.'$lf0'.0]", arr_3_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$lf0']", path))
    return res

# check $ (.)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .
    # .'|'.0
    res = json_model_2(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected $li0 [.'|'.0]", path))
    if not res:
        # .'|'.1
        res = json_model_3(val, path, rep)
        if not res:
            rep is None or rep.append(("unexpected $ls0 [.'|'.1]", path))
        if not res:
            # .'|'.2
            res = json_model_4(val, path, rep)
            if not res:
                rep is None or rep.append(("unexpected $lb0 [.'|'.2]", path))
            if not res:
                # .'|'.3
                res = json_model_5(val, path, rep)
                if not res:
                    rep is None or rep.append(("unexpected $lf0 [.'|'.3]", path))
    if res:
        rep is None or rep.clear()
    else:
        rep is None or rep.append(("no model matched [.'|']", path))
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
            "li0": json_model_2,
            "ls0": json_model_3,
            "lb0": json_model_4,
            "lf0": json_model_5,
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
