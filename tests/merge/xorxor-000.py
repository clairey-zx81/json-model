import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "X" ($.%.X)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.X
    # $.%.X.|[0]
    result = value is None
    if not result:
        # $.%.X.|[1]
        result = isinstance(value, bool)
        if not result:
            # $.%.X.|[2]
            result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
            if not result:
                # $.%.X.|[3]
                result = isinstance(value, float) and value >= 1.0
    return result

# define "" ($)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $
    # $.|[0]
    result = value is None
    if not result:
        # $.|[1]
        result = isinstance(value, bool)
        if not result:
            # $.|[2]
            result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
            if not result:
                # $.|[3]
                result = isinstance(value, float) and value >= 1.0
                if not result:
                    # $.|[4]
                    result = isinstance(value, list)
                    if result:
                        for idx_0, item_0 in enumerate(value):
                            # $.|[4][0]
                            result = jmsc_f_0(item_0, path)
                            if not result: break
    return result

# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_1(value, "$")
