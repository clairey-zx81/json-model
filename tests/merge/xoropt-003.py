import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/[a-z]/"
jmsc_re_0 = re.compile("[a-z]").search



# define "A" ($.%.A)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.A
    # $.%.A.|[0]
    result = isinstance(value, bool)
    if not result:
        # $.%.A.|[1]
        result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
        if not result:
            # $.%.A.|[2]
            result = isinstance(value, float) and value >= 1.0
            if not result:
                # $.%.A.|[3]
                # "/[a-z]/"
                result = isinstance(value, str) and jmsc_re_0(value) is not None
    return result

# define "" ($)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $
    # $.@
    result = jmsc_f_0(value, path)
    return result

# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_1(value, "$")
