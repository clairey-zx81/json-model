import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "p1" ($.%.p1)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.p1
    result = value in {'Moe', 'Calvin', 'Susie', 'Hobbes'}
    return result

# define "p2" ($.%.p2)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.p2
    result = value in {'Tintin', 'Castafiore', 'Milou', 'Haddock'}
    return result

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    xc_0 = 0
    if xc_0 <= 1:
        # $.^[0]
        xr_0 = isinstance(value, str) and value == "Susie"
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[1]
        xr_0 = isinstance(value, str) and value == "Calvin"
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[2]
        xr_0 = isinstance(value, str) and value == "Hobbes"
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[3]
        xr_0 = isinstance(value, str) and value == "Moe"
        if xr_0: xc_0 += 1
    if xc_0 <= 1:
        # $.^[4]
        xr_0 = jmsc_f_1(value, path)
        if xr_0: xc_0 += 1
    result = xc_0 == 1
    return result

# object properties must and may maps

