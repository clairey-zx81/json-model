import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_0_may: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_1_may: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_0_may_b" ($.|[0].b)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.|[0].b
    result = False
    return result

# define "jmsc_obj_1_must_b" ($.|[1].b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.|[1].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_1_may_a" ($.|[1].a)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.|[1].a
    result = False
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
        elif prop in jmsc_obj_0_may:  # may
            if not jmsc_obj_0_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # catch all
            # $.|[0].
            result = isinstance(model, int) and not isinstance(model, bool) and model >= 0
            if not result: return False
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
        elif prop in jmsc_obj_1_may:  # may
            if not jmsc_obj_1_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # catch all
            # $.|[1].
            result = isinstance(model, int) and not isinstance(model, bool) and model >= 0
            if not result: return False
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
    "a": jmsc_f_0,
}
jmsc_obj_0_may = {
    "b": jmsc_f_1,
}
jmsc_obj_1_must = {
    "b": jmsc_f_2,
}
jmsc_obj_1_may = {
    "a": jmsc_f_3,
}
