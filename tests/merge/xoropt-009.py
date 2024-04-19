import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/a/"
jmsc_re_0 = re.compile("a").search
jmsc_obj_1_may: dict[str, CheckFun]

# define "jmsc_obj_1_may_a" ($.^[1].a)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.^[1].a
    result = value is None
    return result


# object $.^[0]
def jmsc_obj_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_0(prop) is not None:  # /a/
            # $.^[0]./a/
            result = isinstance(model, str)
            if not result: return False
        else:  # no catch all
            return False
    return True

# object $.^[1]
def jmsc_obj_1(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_1_may:  # may
            if not jmsc_obj_1_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return True

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
jmsc_obj_1_may = {
    "a": jmsc_f_0,
}
