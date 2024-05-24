import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/[0-9]/"
jmsc_re_0 = re.compile("[0-9]").search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = value in {'Calvin', 'Susie'}
    if not result:
        # $.|[0]
        # "/[0-9]/"
        result = isinstance(value, str) and jmsc_re_0(value) is not None
    return result

# object properties must and may maps

