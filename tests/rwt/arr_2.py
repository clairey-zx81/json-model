# generated from model: ./arr_2.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, list) and len(value) == 2
    if result:
        # '$'.0
        result = isinstance(value[0], bool)
        if result:
            # '$'.1
            result = isinstance(value[1], int) and not isinstance(value[1], bool) and value[1] >= 0
    return result

