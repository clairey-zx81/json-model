# generated from model: ./mrg_00.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

check_model_must: PropMap

# define "check_model_must_a" ('$'.a)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "check_model_must_b" ('$'.b)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "check_model_must_c" ('$'.c)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.c
    result = isinstance(value, bool)
    return result


# define "check_model_must_d" ('$'.d)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.d
    result = isinstance(value, int) and not isinstance(value, bool)
    return result


# object '$'
def check_model(value: Jsonable, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in check_model_must:  # must
            must_count += 1
            if not check_model_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 4



# object properties maps
check_model_must = {
    "a": jmsc_f_0,
    "b": jmsc_f_1,
    "c": jmsc_f_2,
    "d": jmsc_f_3,
}

