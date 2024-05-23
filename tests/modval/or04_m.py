import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/[0-9]/"
jmsc_re_0 = re.compile("[0-9]").search
# regex "/[a-z]/"
jmsc_re_1 = re.compile("[a-z]").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.|[0]
    result = isinstance(value, str) and value == "Susie"
    if not result:
        # $.|[1]
        result = isinstance(value, str) and value == "Calvin"
        if not result:
            # $.|[2]
            # "/[0-9]/"
            result = isinstance(value, str) and jmsc_re_0(value) is not None
            if not result:
                # $.|[3]
                # "/[a-z]/"
                result = isinstance(value, str) and jmsc_re_1(value) is not None
    return result

# object properties must and may maps

