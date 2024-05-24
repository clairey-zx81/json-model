import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/[0-9]/"
jmsc_re_0 = re.compile("[0-9]").search
# regex "/[a-z]/"
jmsc_re_1 = re.compile("[a-z]").search
# regex "/[A-Z]/"
jmsc_re_2 = re.compile("[A-Z]").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = isinstance(value, str)
    if result:
        # $.|[0]
        # "/[0-9]/"
        result = jmsc_re_0(value) is not None
        if not result:
            # $.|[1]
            # "/[a-z]/"
            result = jmsc_re_1(value) is not None
            if not result:
                # $.|[2]
                # "/[A-Z]/"
                result = jmsc_re_2(value) is not None
    return result

# object properties must and may maps

