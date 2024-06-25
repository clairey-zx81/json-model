import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = isinstance(value, int) and not isinstance(value, bool)
    if result:
        # $.|[0]
        result = value >= 0
        if not result:
            # $.|[1]
            result = True
            if not result:
                # $.|[2]
                result = value >= 1
    return result

# object properties must and may maps

