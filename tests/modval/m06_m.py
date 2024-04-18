import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "" ($)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $
    result = True
    return result

# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
