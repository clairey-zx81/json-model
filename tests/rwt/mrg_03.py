# generated from model: ./mrg_03.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

check_model_must: PropMap

# define "check_model_must_a" ($.a)
def jm_f_0(value: Jsonable, path: str) -> bool:
    # $.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "check_model_must_b" ($.b)
def jm_f_1(value: Jsonable, path: str) -> bool:
    # $.b
    result = isinstance(value, str)
    return result


# define "check_model_must_c" ($.c)
def jm_f_2(value: Jsonable, path: str) -> bool:
    # $.c
    result = isinstance(value, float) and value > 0.0
    return result


# object $
def check_model(value: Jsonable, path: str) -> bool:
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
    return must_count == 3



# object properties maps
check_model_must = {
    "a": jm_f_0,
    "b": jm_f_1,
    "c": jm_f_2,
}

