import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
# regex "/^[ab]$/"
jmsc_re_0 = re.compile("^[ab]$").search

# define "jmsc_obj_0_must_a" ($.|[0].a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.|[0].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_obj_1_must_b" ($.|[1].b)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.|[1].b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# define "None" ($.%.None)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.None
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
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_0(prop) is not None:  # /^[ab]$/
            # $.|[2]./^[ab]$/
            result = jmsc_f_0(model, path)
            if not result: return False
        else:  # catch all
            # $.|[2].
            result = isinstance(model, int) and not isinstance(model, bool) and model >= 0
            if not result: return False
    return True

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
            if not result:
                # $.|[2]
                result = jmsc_obj_2(value, path)
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_1,
}
jmsc_obj_1_must = {
    "b": jmsc_f_2,
}
