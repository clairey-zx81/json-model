import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_obj_3_must: dict[str, CheckFun]
jmsc_obj_4_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.|[0].a
    result = jmsc_f_0(value, path)
    return result

# define "jmsc_obj_1_must_a" ($.|[1].a)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.|[1].a
    result = jmsc_f_1(value, path)
    return result

# define "jmsc_obj_2_must_a" ($.|[2].a)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.|[2].a
    result = isinstance(value, float) and value == 1.0
    return result

# define "jmsc_obj_3_must_a" ($.|[3].a)
def jmsc_f_7(value: Any, path: str) -> bool:
    # $.|[3].a
    result = isinstance(value, bool) and value == True
    return result

# define "jmsc_obj_4_must_a" ($.|[4].a)
def jmsc_f_8(value: Any, path: str) -> bool:
    # $.|[4].a
    result = jmsc_f_2(value, path)
    return result


# define "n" ($.%.n)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.n
    result = value is None
    return result

# define "x" ($.%.x)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.x
    result = isinstance(value, float) and value == 10.0
    return result

# define "f" ($.%.f)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.f
    result = isinstance(value, bool) and value == False
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

# object $.|[3]
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

# object $.|[4]
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

# define "" ($)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $
    # $.|[0]
    result = jmsc_obj_0(value, path)
    if not result:
        # $.|[1]
        result = jmsc_obj_1(value, path)
        if not result:
            # $.|[2]
            result = jmsc_obj_2(value, path)
            if not result:
                # $.|[3]
                result = jmsc_obj_3(value, path)
                if not result:
                    # $.|[4]
                    result = jmsc_obj_4(value, path)
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_4,
}
jmsc_obj_1_must = {
    "a": jmsc_f_5,
}
jmsc_obj_2_must = {
    "a": jmsc_f_6,
}
jmsc_obj_3_must = {
    "a": jmsc_f_7,
}
jmsc_obj_4_must = {
    "a": jmsc_f_8,
}

def check_model(value) -> bool:
    return jmsc_f_3(value, "$")
