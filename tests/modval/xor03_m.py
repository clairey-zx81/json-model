import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "" ($)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $
    xc_0 = 0
    if xc_0 <= 1:
        # $.^[0]
        xr_0 = True
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[1]
        xr_0 = isinstance(value, int) and not isinstance(value, bool) and value >= 0
        if xr_0: xc_0 += 1
    result = xc_0 == 1
    return result

# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_0(value, "$")
