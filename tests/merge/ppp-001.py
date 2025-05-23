#! /bin/env python
#
# Model: ppp-001.model.json
#
# Generated by jmc (JSON Model Compiler) (https://github.com/clairey-zx81/json-model)
#

from typing import Callable
import re as re
import datetime
import urllib.parse

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type Path = list[str]
type Report = list[str]|None
type CheckFun = Callable[[Jsonable, str, Report], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# extract type name
def _tname(value: Jsonable) -> str:
    return type(value).__name__

# maybe add message to report
def _rep(msg: str, rep: Report) -> bool:
    rep is None or rep.append(msg)
    return False

json_model_1_must: PropMap

# define "json_model_1_must_a" ($.a)
def _jm_f_0(value: Jsonable, path: str, rep: Report = None) -> bool:
    # $.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result



# object $
def json_model_1(value: Jsonable, path: str, rep: Report = None) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, val in value.items():
        assert isinstance(prop, str)
        lpath = path + "." + prop
        if prop in json_model_1_must:  # must
            must_count += 1
            if not json_model_1_must[prop](val, lpath, rep):
                return False
        else:  # no catch all
            return False
    result = must_count == 1
    return result



# entry function check_model
def check_model(value: Jsonable, path: str = "$", rep: Report = None) -> bool:
    return json_model_1(value, path, rep)


# object properties maps
json_model_1_must = {
    "a": _jm_f_0,
}


# possibly run as a script: $0 values...
if __name__ == "__main__":
    import json
    import sys
    for fn in sys.argv[1:]:
        try:
            with open(fn) as f:
                value = json.load(f)
            reasons = []
            if check_model(value, "", reasons):
                print(f"{fn}: PASS")
            else:
                print(f"{fn}: FAIL {reasons}")
        except Exception as e:
            print(f"{fn}: ERROR ({e})")

