import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]
# regex "/.../"
jmsc_re_0 = re.compile("...").search
jmsc_obj_1_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.^[0].a)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.^[0].a
    result = isinstance(value, str)
    return result

# define "jmsc_obj_1_must_b" ($.^[1].b)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.^[1].b
    result = isinstance(value, str)
    return result


# object $.^[0]
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
        else:  # catch all
            # $.^[0].
            # "/.../"
            result = isinstance(model, str) and jmsc_re_0(model) is not None
            if not result: return False
    return must_count == 1

# object $.^[1]
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
        else:  # catch all
            # $.^[1].
            # "/.../"
            result = isinstance(model, str) and jmsc_re_0(model) is not None
            if not result: return False
    return must_count == 1

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    xc_0 = 0
    if xc_0 <= 1:
        # $.^[0]
        xr_0 = jmsc_obj_0(value, path)
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[1]
        xr_0 = jmsc_obj_1(value, path)
        if xr_0: xc_0 += 1
    result = xc_0 == 1
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_0,
}
jmsc_obj_1_must = {
    "b": jmsc_f_1,
}
