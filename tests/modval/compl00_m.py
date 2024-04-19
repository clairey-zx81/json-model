import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

# regex "/^[a-z]+$/i"
jmsc_re_0 = re.compile("^[a-z]+$", re.IGNORECASE).search



# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.^[?]
    # "/^[a-z]+$/i"
    is_m_0 = isinstance(value, str) and jmsc_re_0(value) is not None
    result = not is_m_0
    return result

# object properties must and may maps

