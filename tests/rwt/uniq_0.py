# generated from model: ./uniq_0.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    # '$'.'@'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_0_idx, array_0_item in enumerate(value):
            # '$'.'@'.0
            result = isinstance(array_0_item, int) and not isinstance(array_0_item, bool) and array_0_item >= 1
            if not result: break
    result &= len(set(value)) == len(value)
    return result

