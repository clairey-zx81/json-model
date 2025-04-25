# generated from model: ./or_0.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = not isinstance(value, (list, dict)) and value in set()
    if not result:
        result = isinstance(value, int) and not isinstance(value, bool)
        if result:
            # '$'.'|'.0
            result = isinstance(value, int) and not isinstance(value, bool) and value == 200
            if not result:
                # '$'.'|'.1
                result = isinstance(value, int) and not isinstance(value, bool) and value == 300
                if not result:
                    # '$'.'|'.2
                    result = isinstance(value, int) and not isinstance(value, bool) and value == 400
                    if not result:
                        # '$'.'|'.3
                        result = isinstance(value, int) and not isinstance(value, bool) and value == 500
    return result

