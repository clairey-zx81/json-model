import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "" ($)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $
    # $.&[0]
    result = isinstance(value, int) and not isinstance(value, bool)
    if result:
        # $.&[1]
        result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
        if result:
            # $.&[2]
            result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
    return result

# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
