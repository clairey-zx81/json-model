# generated from model: ./opt_06.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, int) and not isinstance(value, bool)
    if result:
        # '$'.'&'.0
        result = value >= 0
        if result:
            # '$'.'&'.1
            result = value >= 1
            if result:
                # '$'.'&'.2
                result = True
    return result

