import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_obj_3_must: dict[str, CheckFun]
jmsc_obj_4_must: dict[str, CheckFun]
jmsc_obj_5_must: dict[str, CheckFun]
jmsc_obj_6_must: dict[str, CheckFun]
jmsc_obj_7_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.%.A.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.A.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_1_must_b" ($.%.A.|[1].b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.A.|[1].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_2_must_a" ($.%.B.|[0].a)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.B.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_3_must_c" ($.%.B.|[1].c)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.B.|[1].c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_4_must_a" ($.|[0].a)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_5_must_a" ($.|[1].a)
def jmsc_f_7(value: Any, path: str) -> bool:
    # $.|[1].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_5_must_c" ($.|[1].c)
def jmsc_f_8(value: Any, path: str) -> bool:
    # $.|[1].c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_6_must_b" ($.|[2].b)
def jmsc_f_9(value: Any, path: str) -> bool:
    # $.|[2].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_6_must_a" ($.|[2].a)
def jmsc_f_10(value: Any, path: str) -> bool:
    # $.|[2].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_7_must_b" ($.|[3].b)
def jmsc_f_11(value: Any, path: str) -> bool:
    # $.|[3].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_7_must_c" ($.|[3].c)
def jmsc_f_12(value: Any, path: str) -> bool:
    # $.|[3].c
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
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
    return result

# object $.|[0]
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

# object $.|[1]
def jmsc_obj_5(value: Any, path: str) -> bool:
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
    return must_count == 2

# object $.|[2]
def jmsc_obj_6(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_6_must:  # must
            must_count += 1
            if not jmsc_obj_6_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2

# object $.|[3]
def jmsc_obj_7(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_7_must:  # must
            must_count += 1
            if not jmsc_obj_7_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 2

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = isinstance(value, dict)
    if result:
        # $.|[0]
        result = jmsc_obj_4(value, path)
        if not result:
            # $.|[1]
            result = jmsc_obj_5(value, path)
            if not result:
                # $.|[2]
                result = jmsc_obj_6(value, path)
                if not result:
                    # $.|[3]
                    result = jmsc_obj_7(value, path)
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_1,
}
jmsc_obj_1_must = {
    "b": jmsc_f_2,
}
jmsc_obj_2_must = {
    "a": jmsc_f_4,
}
jmsc_obj_3_must = {
    "c": jmsc_f_5,
}
jmsc_obj_4_must = {
    "a": jmsc_f_6,
}
jmsc_obj_5_must = {
    "a": jmsc_f_7,
    "c": jmsc_f_8,
}
jmsc_obj_6_must = {
    "b": jmsc_f_9,
    "a": jmsc_f_10,
}
jmsc_obj_7_must = {
    "b": jmsc_f_11,
    "c": jmsc_f_12,
}
