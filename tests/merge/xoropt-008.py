import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, bool)
    return result

# define "jmsc_obj_1_must_a" ($.|[1].a)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.|[1].a
    result = isinstance(value, str)
    return result

# define "jmsc_obj_2_must_a" ($.|[2].a)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.|[2].a
    result = isinstance(value, list)
    if result:
        for idx_0, item_0 in enumerate(value):
            # $.|[2].a[0]
            result = isinstance(item_0, int) and not isinstance(item_0, bool) and item_0 >= 0
            if not result: break
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
    # $.|[0]
    result = jmsc_obj_0(value, path)
    if not result:
        # $.|[1]
        result = jmsc_obj_1(value, path)
        if not result:
            # $.|[2]
            result = jmsc_obj_2(value, path)
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

def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
