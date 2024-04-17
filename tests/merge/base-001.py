import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_f_0_must: dict[str, CheckFun]

# define "jmsc_f_0_must_a" ($.a)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.a
    result = isinstance(value, str)
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
        else:  # no catch all
            return False
    return must_count == 1


# object properties must and may maps
jmsc_f_0_must = {
    "a": jmsc_f_1,
}

def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
