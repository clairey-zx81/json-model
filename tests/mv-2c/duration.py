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
jm_is_duration_reco: object
jm_is_duration: RegexFun

def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    return isinstance(val, str) and jm_is_duration(val, None, None)



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
        global jm_is_duration_reco, jm_is_duration
        jm_is_duration_reco = re.compile("^P(([0-9]+D|[0-9]+M([0-9]+D)?|[0-9]+Y([0-9]+M([0-9]+D)?)?)(T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S))?|T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S)|[0-9]+W)$")
        jm_is_duration = lambda s, p, r: jm_is_duration_reco.search(s) is not None

# differed module cleanup
def check_model_free():
    global initialized
    if initialized:
        initialized = False
        global jm_is_duration_reco, jm_is_duration
        jm_is_duration_reco = None
        jm_is_duration = None

if __name__ == "__main__":
    check_model_init()
    main(check_model_fun, check_model_map, __version__)
    check_model_free()
