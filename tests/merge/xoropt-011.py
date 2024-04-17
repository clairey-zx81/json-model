import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_map_0: dict[Any, CheckFun]

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value == 10
    return result

# define "jmsc_obj_1_must_a" ($.|[1].a)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.|[1].a
    result = isinstance(value, int) and not isinstance(value, bool) and value == 1
    return result

# define "jmsc_obj_2_must_a" ($.|[2].a)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.|[2].a
    result = isinstance(value, int) and not isinstance(value, bool) and value == 0
    return result


# object $.|[0]
def jmsc_obj_0(value: Any, path: str) -> bool:
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
    return must_count == 1

# object $.|[1]
def jmsc_obj_1(value: Any, path: str) -> bool:
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
    return must_count == 1

# object $.|[2]
def jmsc_obj_2(value: Any, path: str) -> bool:
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
    return must_count == 1

# define "" ($)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $
    result = isinstance(value, dict)
    if result:
        result = "a" in value
        if result:
            tag_0 = value["a"]
            if tag_0 in jmsc_map_0:
                result = jmsc_map_0[tag_0](value, path)
            else:
                result = False
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_1,
}
jmsc_obj_1_must = {
    "a": jmsc_f_2,
}
jmsc_obj_2_must = {
    "a": jmsc_f_3,
}
jmsc_map_0 = {
    10: jmsc_obj_0,
    1: jmsc_obj_1,
    0: jmsc_obj_2,
}

def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
