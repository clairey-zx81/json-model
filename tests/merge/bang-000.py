import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_f_0_must: dict[str, CheckFun]
jmsc_f_0_may: dict[str, CheckFun]

# define "jmsc_f_0_must_!" ($.!)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.!
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_0_must__" ($._)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $._
    result = isinstance(value, bool)
    return result

# define "jmsc_f_0_must_a" ($.a)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.a
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    return result

# define "jmsc_f_0_must_?" ($.?)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.?
    result = isinstance(value, float) and value >= 0.0
    return result

# define "jmsc_f_0_must_/" ($./)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $./
    result = isinstance(value, int) and not isinstance(value, bool) and value == 17
    return result

# define "jmsc_f_0_may_b" ($.b)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.b
    result = value is None
    return result


# object $
def jmsc_f_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_0_must:  # must
            must_count += 1
            if not jmsc_f_0_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_f_0_may:  # may
            if not jmsc_f_0_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 5


# object properties must and may maps
jmsc_f_0_must = {
    "!": jmsc_f_1,
    "_": jmsc_f_2,
    "a": jmsc_f_3,
    "?": jmsc_f_4,
    "/": jmsc_f_5,
}
jmsc_f_0_may = {
    "b": jmsc_f_6,
}

def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
