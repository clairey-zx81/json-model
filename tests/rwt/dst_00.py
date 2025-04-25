# generated from model: ./dst_00.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

jmsc_obj_0_must: PropMap
jmsc_obj_1_must: PropMap

# define "jmsc_obj_0_must_a" ('$'.'|'.0.a)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_0_must_b" ('$'.'|'.0.b)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_1_must_a" ('$'.'|'.1.a)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_1_must_c" ('$'.'|'.1.c)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.c
    result = isinstance(value, str)
    return result


# object '$'.'|'.0
def jmsc_obj_0(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_0_must:  # must
            must_count += 1
            if not jmsc_obj_0_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2


# object '$'.'|'.1
def jmsc_obj_1(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_1_must:  # must
            must_count += 1
            if not jmsc_obj_1_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, dict)
    if result:
        # '$'.'|'.0
        result = jmsc_obj_0(value, path)
        if not result:
            # '$'.'|'.1
            result = jmsc_obj_1(value, path)
    return result

# object properties maps
jmsc_obj_0_must = {
    "a": jmsc_f_0,
    "b": jmsc_f_1,
}
jmsc_obj_1_must = {
    "a": jmsc_f_2,
    "c": jmsc_f_3,
}

