import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.|[0]
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    if not result:
        # $.|[1]
        result = isinstance(value, int) and not isinstance(value, bool) and value >= 1
        if not result:
            # $.|[2]
            result = isinstance(value, str)
    return result

# object properties must and may maps

