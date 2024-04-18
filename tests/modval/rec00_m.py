import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# object $.%.obj
def jmsc_f_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # $.%.obj.
        result = jmsc_f_1(model, path)
        if not result: return False
    return True


# define "rec" ($)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $
    # $.|[0]
    result = isinstance(value, bool)
    if not result:
        # $.|[1]
        result = jmsc_f_0(value, path)
    return result

# named root
jmsc_f_1 = jmsc_f_2


# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_2(value, "$")
