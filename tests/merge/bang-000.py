import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

check_model_must: dict[str, CheckFun]
check_model_may: dict[str, CheckFun]

# define "check_model_must_!" ($.!)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.!
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "check_model_must__" ($._)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $._
    result = isinstance(value, bool)
    return result

# define "check_model_must_a" ($.a)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "check_model_must_?" ($.?)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.?
    result = isinstance(value, float) and value >= 0.0
    return result

# define "check_model_must_/" ($./)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $./
    result = isinstance(value, int) and not isinstance(value, bool) and value == 17
    return result

# define "check_model_may_b" ($.b)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.b
    result = value is None
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
        elif prop in check_model_may:  # may
            if not check_model_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 5


# object properties must and may maps
check_model_must = {
    "!": jmsc_f_0,
    "_": jmsc_f_1,
    "a": jmsc_f_2,
    "?": jmsc_f_3,
    "/": jmsc_f_4,
}
check_model_may = {
    "b": jmsc_f_5,
}
