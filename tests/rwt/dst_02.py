# generated from model: ./dst_02.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

jmsc_obj_0_must: PropMap
jmsc_obj_1_must: PropMap
jmsc_obj_2_must: PropMap
jmsc_obj_3_must: PropMap
jmsc_obj_4_must: PropMap
jmsc_obj_5_must: PropMap

# define "jmsc_obj_0_must_b" ('$'.'|'.0.b)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_0_must_a" ('$'.'|'.0.a)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_0_must_d" ('$'.'|'.0.d)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'|'.0.d
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_1_must_b" ('$'.'|'.1.b)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_1_must_a" ('$'.'|'.1.a)
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_1_must_e" ('$'.'|'.1.e)
def jmsc_f_5(value: Jsonable, path: str) -> bool:
    # '$'.'|'.1.e
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_2_must_b" ('$'.'|'.2.b)
def jmsc_f_6(value: Jsonable, path: str) -> bool:
    # '$'.'|'.2.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_2_must_a" ('$'.'|'.2.a)
def jmsc_f_7(value: Jsonable, path: str) -> bool:
    # '$'.'|'.2.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_2_must_f" ('$'.'|'.2.f)
def jmsc_f_8(value: Jsonable, path: str) -> bool:
    # '$'.'|'.2.f
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_3_must_c" ('$'.'|'.3.c)
def jmsc_f_9(value: Jsonable, path: str) -> bool:
    # '$'.'|'.3.c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_3_must_a" ('$'.'|'.3.a)
def jmsc_f_10(value: Jsonable, path: str) -> bool:
    # '$'.'|'.3.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_3_must_d" ('$'.'|'.3.d)
def jmsc_f_11(value: Jsonable, path: str) -> bool:
    # '$'.'|'.3.d
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_4_must_c" ('$'.'|'.4.c)
def jmsc_f_12(value: Jsonable, path: str) -> bool:
    # '$'.'|'.4.c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_4_must_a" ('$'.'|'.4.a)
def jmsc_f_13(value: Jsonable, path: str) -> bool:
    # '$'.'|'.4.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_4_must_e" ('$'.'|'.4.e)
def jmsc_f_14(value: Jsonable, path: str) -> bool:
    # '$'.'|'.4.e
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_5_must_c" ('$'.'|'.5.c)
def jmsc_f_15(value: Jsonable, path: str) -> bool:
    # '$'.'|'.5.c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "jmsc_obj_5_must_a" ('$'.'|'.5.a)
def jmsc_f_16(value: Jsonable, path: str) -> bool:
    # '$'.'|'.5.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# define "jmsc_obj_5_must_f" ('$'.'|'.5.f)
def jmsc_f_17(value: Jsonable, path: str) -> bool:
    # '$'.'|'.5.f
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
    return must_count == 3


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
    return must_count == 3


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
    return must_count == 3


# object '$'.'|'.3
def jmsc_obj_3(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_3_must:  # must
            must_count += 1
            if not jmsc_obj_3_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 3


# object '$'.'|'.4
def jmsc_obj_4(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_4_must:  # must
            must_count += 1
            if not jmsc_obj_4_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 3


# object '$'.'|'.5
def jmsc_obj_5(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_5_must:  # must
            must_count += 1
            if not jmsc_obj_5_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 3


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
            if not result:
                # '$'.'|'.2
                result = jmsc_obj_2(value, path)
                if not result:
                    # '$'.'|'.3
                    result = jmsc_obj_3(value, path)
                    if not result:
                        # '$'.'|'.4
                        result = jmsc_obj_4(value, path)
                        if not result:
                            # '$'.'|'.5
                            result = jmsc_obj_5(value, path)
    return result

# object properties maps
jmsc_obj_0_must = {
    "b": jmsc_f_0,
    "a": jmsc_f_1,
    "d": jmsc_f_2,
}
jmsc_obj_1_must = {
    "b": jmsc_f_3,
    "a": jmsc_f_4,
    "e": jmsc_f_5,
}
jmsc_obj_2_must = {
    "b": jmsc_f_6,
    "a": jmsc_f_7,
    "f": jmsc_f_8,
}
jmsc_obj_3_must = {
    "c": jmsc_f_9,
    "a": jmsc_f_10,
    "d": jmsc_f_11,
}
jmsc_obj_4_must = {
    "c": jmsc_f_12,
    "a": jmsc_f_13,
    "e": jmsc_f_14,
}
jmsc_obj_5_must = {
    "c": jmsc_f_15,
    "a": jmsc_f_16,
    "f": jmsc_f_17,
}

