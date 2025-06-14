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

_jm_obj_0_mup: PropMap
check_model_map: PropMap

# check _jm_obj_0_mup_! (.'!')
def _jm_f_0(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'!'
    res = isinstance(val, int) and not isinstance(val, bool) and val >= 0
    if not res:
        rep is None or rep.append(("not a 0 strict int [.'!']", path))
    return res

# check _jm_obj_0_mup_/ (.'/')
def _jm_f_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'/'
    res = isinstance(val, int) and not isinstance(val, bool) and val == 17
    if not res:
        rep is None or rep.append(("unexpected =17 [.'/']", path))
    return res

# check _jm_obj_0_mup_? (.'?')
def _jm_f_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'?'
    res = isinstance(val, float) and val >= 0.0
    if not res:
        rep is None or rep.append(("not a 0.0 strict float [.'?']", path))
    return res

# check _jm_obj_0_mup__ (._)
def _jm_f_3(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # ._
    res = isinstance(val, bool)
    if not res:
        rep is None or rep.append(("not a bool [._]", path))
    return res

# check _jm_obj_0_mup_a (.a)
def _jm_f_4(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .a
    res = isinstance(val, int) and not isinstance(val, bool) and val >= 0
    if not res:
        rep is None or rep.append(("not a 0 strict int [.a]", path))
    return res


# object .
def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.]", path))
        return False
    res: bool
    pfun: CheckFun
    must_count: int = 0
    for prop, pval in val.items():
        assert isinstance(prop, str)
        lpath_0: Path = (path + [ prop ]) if path is not None else None
        if pfun := _jm_obj_0_mup.get(prop):
            # handle 5 mandatory props
            if pfun != UNDEFINED:
                must_count += 1
                if not pfun(pval, lpath_0 if path is not None else None, rep):
                    rep is None or rep.append(("invalid mandatory prop value [.]", lpath_0 if path is not None else None))
                    return False
        elif prop == "b":
            # handle may b property
            # .b
            res = pval is None
            if not res:
                rep is None or rep.append(("not null [.b]", lpath_0 if path is not None else None))
            if not res:
                rep is None or rep.append(("invalid optional prop value [.b]", lpath_0 if path is not None else None))
                return False
        else:
            rep is None or rep.append(("unexpected prop [.]", lpath_0 if path is not None else None))
            return False
    if must_count != 5:
        if rep is not None:
            if not "!" in val:
                rep is None or rep.append(("missing mandatory prop <!> [.]", path))
            if not "/" in val:
                rep is None or rep.append(("missing mandatory prop </> [.]", path))
            if not "?" in val:
                rep is None or rep.append(("missing mandatory prop <?> [.]", path))
            if not "_" in val:
                rep is None or rep.append(("missing mandatory prop <_> [.]", path))
            if not "a" in val:
                rep is None or rep.append(("missing mandatory prop <a> [.]", path))
        return False
    return True

# check $ (.)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .
    res = _jm_obj_0(val, path, rep)
    if not res:
        rep is None or rep.append(("not an expected object [.]", path))
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_obj_0_mup
        _jm_obj_0_mup = {
            "!": _jm_f_0,
            "/": _jm_f_1,
            "?": _jm_f_2,
            "_": _jm_f_3,
            "a": _jm_f_4,
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
