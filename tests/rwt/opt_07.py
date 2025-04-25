# generated from model: ./opt_07.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

jmsc_obj_0_must: PropMap
jmsc_obj_1_must: PropMap
jmsc_obj_2_must: PropMap
jmsc_map_0: TagMap

# define "jmsc_obj_0_must_d" ('$'.'|'.0.d)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.d
    result = isinstance(value, int) and not isinstance(value, bool) and value == 1
    return result


# define "jmsc_obj_0_must_val" ('$'.'|'.0.val)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.val
    result = isinstance(value, int) and not isinstance(value, bool)
    return result


# define "jmsc_obj_1_must_d" ('$'.'|'.1.d)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.d
    result = isinstance(value, int) and not isinstance(value, bool) and value == 2
    return result


# define "jmsc_obj_1_must_val" ('$'.'|'.1.val)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.val
    result = isinstance(value, str)
    return result


# define "jmsc_obj_2_must_d" ('$'.'|'.2.d)
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    # '$'.'|'.2.d
    result = isinstance(value, int) and not isinstance(value, bool) and value == 3
    return result


# define "jmsc_obj_2_must_val" ('$'.'|'.2.val)
def jmsc_f_5(value: Jsonable, path: str) -> bool:
    # '$'.'|'.2.val
    result = isinstance(value, bool)
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


# object '$'.'|'.2
def jmsc_obj_2(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_2_must:  # must
            must_count += 1
            if not jmsc_obj_2_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, dict)
    if result:
        result = "d" in value
        if result:
            tag_0 = value["d"]
            if tag_0 in jmsc_map_0:
                result = jmsc_map_0[tag_0](value, path)
            else:
                result = False
    return result

# object properties maps
jmsc_obj_0_must = {
    "d": jmsc_f_0,
    "val": jmsc_f_1,
}
jmsc_obj_1_must = {
    "d": jmsc_f_2,
    "val": jmsc_f_3,
}
jmsc_obj_2_must = {
    "d": jmsc_f_4,
    "val": jmsc_f_5,
}
jmsc_map_0 = {
    1: jmsc_obj_0,
    2: jmsc_obj_1,
    3: jmsc_obj_2,
}

