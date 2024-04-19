import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/^[A-Z][a-z]+$/"
jmsc_re_0 = re.compile("^[A-Z][a-z]+$").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.|[0]
    result = isinstance(value, float) and value >= 0.0
    if not result:
        # $.|[1]
        # "/^[A-Z][a-z]+$/"
        result = isinstance(value, str) and jmsc_re_0(value) is not None
    return result

# object properties must and may maps

