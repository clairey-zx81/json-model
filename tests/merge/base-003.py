import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# object $
def check_model(value: Any, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # no catch all
        return False
    return True


# object properties must and may maps

