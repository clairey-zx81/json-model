import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_obj_3_must: dict[str, CheckFun]
jmsc_obj_4_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.%.A.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.A.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_1_must_b" ($.%.A.|[1].b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.A.|[1].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result

# define "jmsc_obj_2_must_c" ($.%.B.|[0].c)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.B.|[0].c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_3_must_a" ($.%.B.|[1].a)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.B.|[1].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_4_must_b" ($.%.B.|[2].b)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.%.B.|[2].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result


# object $.%.A.|[0]
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

# object $.%.A.|[1]
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

# define "A" ($.%.A)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.A
    result = isinstance(value, dict)
    if result:
        # $.%.A.|[0]
        result = jmsc_obj_0(value, path)
        if not result:
            # $.%.A.|[1]
            result = jmsc_obj_1(value, path)
    return result

# object $.%.B.|[0]
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

# object $.%.B.|[1]
def jmsc_obj_3(value: Any, path: str) -> bool:
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
    return must_count == 1

# object $.%.B.|[2]
def jmsc_obj_4(value: Any, path: str) -> bool:
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
    return must_count == 1

# define "B" ($.%.B)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.%.B
    result = isinstance(value, dict)
    if result:
        # $.%.B.|[0]
        result = jmsc_obj_2(value, path)
        if not result:
            # $.%.B.|[1]
            result = jmsc_obj_3(value, path)
            if not result:
                # $.%.B.|[2]
                result = jmsc_obj_4(value, path)
    return result

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.@
    result = jmsc_f_3(value, path)
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_1,
}
jmsc_obj_1_must = {
    "b": jmsc_f_2,
}
jmsc_obj_2_must = {
    "c": jmsc_f_4,
}
jmsc_obj_3_must = {
    "a": jmsc_f_5,
}
jmsc_obj_4_must = {
    "b": jmsc_f_6,
}
