import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = value in {'Hobbes', 'Susie', 'Calvin'}
    return result

# object properties must and may maps

