import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/^[a-z]+$/"
jmsc_re_0 = re.compile("^[a-z]+$").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = isinstance(value, str)
    if result:
        # $.|[0]
        result = value == "Susie"
        if not result:
            # $.|[1]
            # "/^[a-z]+$/"
            result = jmsc_re_0(value) is not None
    return result

# object properties must and may maps

