import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# object $.|[1]
def jmsc_obj_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # $.|[1].
        result = check_model(model, path)
        if not result: return False
    return True

# define "myself" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.|[0]
    result = isinstance(value, bool)
    if not result:
        # $.|[1]
        result = jmsc_obj_0(value, path)
    return result


# object properties must and may maps

