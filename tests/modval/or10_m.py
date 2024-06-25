import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_obj_1_must: dict[str, CheckFun]

# define "jmsc_obj_1_must_name" ($.|[1].name)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.|[1].name
    result = isinstance(value, str)
    return result


# object $.|[0]
def jmsc_obj_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # no catch all
        return False
    return True

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
jmsc_obj_1_must = {
    "name": jmsc_f_0,
}
