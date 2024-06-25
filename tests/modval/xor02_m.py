import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_0_must: dict[str, CheckFun]

# define "jmsc_obj_0_must_a" ($.^[1].a)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.^[1].a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result


# object $.^[1]
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

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.^[1]
    isin = jmsc_obj_0(value, path)
    result = not isin
    if result:
        result = False
    return result

# object properties must and may maps
jmsc_obj_0_must = {
    "a": jmsc_f_0,
}
