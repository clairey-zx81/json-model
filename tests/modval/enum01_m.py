import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "p1" ($.%.p1)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.p1
    result = value in {'Susie', 'Calvin', 'Moe', 'Hobbes'}
    return result

# define "p2" ($.%.p2)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.p2
    result = value in {'Castafiore', 'Tintin', 'Milou', 'Haddock'}
    return result

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = value in {'Calvin', 'Milou', 'Haddock', 'Hobbes', 'Castafiore', 'Susie', 'Tintin', 'Moe'}
    return result

# object properties must and may maps

