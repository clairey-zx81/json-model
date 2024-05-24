import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_1_may: dict[str, CheckFun]

# define "jmsc_obj_0_must_b" ($.|[0].b)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.|[0].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, str)
    return result

# define "jmsc_obj_1_must_b" ($.|[1].b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.|[1].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
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
    return must_count == 2

# object $.|[1].a
def jmsc_f_3(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # no catch all
        return False
    return True

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
        elif prop in jmsc_obj_1_may:  # may
            if not jmsc_obj_1_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = isinstance(value, dict)
    if result:
        # $.|[0]
        result = jmsc_obj_0(value, path)
        if not result:
            # $.|[1]
            result = jmsc_obj_1(value, path)
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "b": jmsc_f_0,
    "a": jmsc_f_1,
}
jmsc_obj_1_must = {
    "b": jmsc_f_2,
}
jmsc_obj_1_may = {
    "a": jmsc_f_3,
}
