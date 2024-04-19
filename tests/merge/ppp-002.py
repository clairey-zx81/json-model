import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

check_model_must: dict[str, CheckFun]

# define "check_model_must_a" ($.a)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "check_model_must_b" ($.b)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.b
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result

# define "check_model_must_c" ($.c)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.c
    result = isinstance(value, int) and not isinstance(value, bool)
    return result


# object $
def check_model(value: Any, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in check_model_must:  # must
            must_count += 1
            if not check_model_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 3


# object properties must and may maps
check_model_must = {
    "a": jmsc_f_0,
    "b": jmsc_f_1,
    "c": jmsc_f_2,
}
