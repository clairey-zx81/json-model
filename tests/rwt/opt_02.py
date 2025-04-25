# generated from model: ./opt_02.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    # '$'.'|'.0
    result = isinstance(value, int) and not isinstance(value, bool) and value >= 0
    if not result:
        # '$'.'|'.1
        result = isinstance(value, float) and value >= 0.0
        if not result:
            # '$'.'|'.2
            result = isinstance(value, bool)
    return result

