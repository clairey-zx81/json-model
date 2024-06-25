import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.^[?]
    is_m_0 = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    result = not is_m_0
    return result

# object properties must and may maps

