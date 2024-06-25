import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    result = value in {'Calvin', 'Hobbes', 'Susie'}
    return result

# object properties must and may maps

