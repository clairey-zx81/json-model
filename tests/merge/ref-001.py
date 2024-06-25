import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_f_0_must: dict[str, CheckFun]
jmsc_f_3_must: dict[str, CheckFun]

# define "jmsc_f_0_must_a" ($.%.A.a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.A.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_0_must_b" ($.%.A.b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.A.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_3_must_a" ($.%.B.a)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.B.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_3_must_b" ($.%.B.b)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.B.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_3_must_c" ($.%.B.c)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.%.B.c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# object $.%.A
def jmsc_f_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_0_must:  # must
            must_count += 1
            if not jmsc_f_0_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2


# object $.%.B
def jmsc_f_3(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_3_must:  # must
            must_count += 1
            if not jmsc_f_3_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 3


# object $
def check_model(value: Any, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # no catch all
        return False
    return True


# object properties must and may maps
jmsc_f_0_must = {
    "a": jmsc_f_1,
    "b": jmsc_f_2,
}
jmsc_f_3_must = {
    "a": jmsc_f_4,
    "b": jmsc_f_5,
    "c": jmsc_f_6,
}
