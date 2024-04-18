import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_f_0_must: dict[str, CheckFun]
jmsc_f_3_must: dict[str, CheckFun]
jmsc_map_0: dict[Any, CheckFun]

# define "jmsc_f_0_must_t" ($.%.A.t)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.A.t
    result = isinstance(value, bool) and value == True
    return result

# define "jmsc_f_0_must_a" ($.%.A.a)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.A.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_3_must_t" ($.%.B.t)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.B.t
    result = isinstance(value, bool) and value == False
    return result

# define "jmsc_f_3_must_b" ($.%.B.b)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.B.b
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
    return must_count == 2


# define "" ($)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $
    result = isinstance(value, dict)
    if result:
        result = "t" in value
        if result:
            tag_0 = value["t"]
            if tag_0 in jmsc_map_0:
                result = jmsc_map_0[tag_0](value, path)
            else:
                result = False
    return result

# object properties must and may maps
jmsc_f_0_must = {
    "t": jmsc_f_1,
    "a": jmsc_f_2,
}
jmsc_f_3_must = {
    "t": jmsc_f_4,
    "b": jmsc_f_5,
}
jmsc_map_0 = {
    True: jmsc_f_0,
    False: jmsc_f_3,
}

def check_model(value) -> bool:
    return jmsc_f_6(value, "$")
