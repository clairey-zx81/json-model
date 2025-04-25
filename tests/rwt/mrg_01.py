# generated from model: ./mrg_01.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

jmsc_f_1_must: PropMap
jmsc_f_4_must: PropMap
check_model_must: PropMap

# define "jmsc_f_1_must_a" ('$'.'$'.X.a)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'$'.X.a
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "jmsc_f_1_must_b" ('$'.'$'.X.b)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'$'.X.b
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "jmsc_f_4_must_c" ('$'.'$'.Y.c)
def jmsc_f_5(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Y.c
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "jmsc_f_4_must_d" ('$'.'$'.Y.d)
def jmsc_f_6(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Y.d
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "check_model_must_c" ('$'.c)
def jmsc_f_7(value: Jsonable, path: str) -> bool:
    # '$'.c
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "check_model_must_d" ('$'.d)
def jmsc_f_8(value: Jsonable, path: str) -> bool:
    # '$'.d
    result = isinstance(value, str) and value == "cst_01"
    return result


# define "T" ('$'.'$'.T)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'$'.T
    result = isinstance(value, str) and value == "cst_01"
    return result


# object '$'.'$'.X
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_1_must:  # must
            must_count += 1
            if not jmsc_f_1_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2




# object '$'.'$'.Y
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_4_must:  # must
            must_count += 1
            if not jmsc_f_4_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2




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
    return must_count == 2



# object properties maps
jmsc_f_1_must = {
    "a": jmsc_f_2,
    "b": jmsc_f_3,
}
jmsc_f_4_must = {
    "c": jmsc_f_5,
    "d": jmsc_f_6,
}
check_model_must = {
    "c": jmsc_f_7,
    "d": jmsc_f_8,
}

