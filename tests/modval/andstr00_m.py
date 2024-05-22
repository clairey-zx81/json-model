import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/[a-z]/"
jmsc_re_0 = re.compile("[a-z]").search
# regex "/[0-9]/"
jmsc_re_1 = re.compile("[0-9]").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.&[0]
    # "/[a-z]/"
    result = isinstance(value, str) and jmsc_re_0(value) is not None
    if result:
        # $.&[1]
        # "/[0-9]/"
        result = jmsc_re_1(value) is not None
    return result

# object properties must and may maps

