import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# object $
def check_model(value: Any, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # $.
        result = isinstance(model, int) and not isinstance(model, bool) and model >= 0
        if not result: return False
    return True


# object properties must and may maps

