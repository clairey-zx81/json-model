# generated from model: ./or_1.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = not isinstance(value, (list, dict)) and value in {'Calvin', 'Susie'}
    if not result:
        # '$'.'|'.0
        result = value is None
        if not result:
            # '$'.'|'.1
            result = value is None
            if not result:
                # '$'.'|'.2
                result = isinstance(value, bool) and value == False
                if not result:
                    # '$'.'|'.3
                    result = isinstance(value, int) and not isinstance(value, bool) and value == 42
                    if not result:
                        # '$'.'|'.4
                        result = isinstance(value, float) and value == 3.14159
                        if not result:
                            # '$'.'|'.5
                            result = isinstance(value, float) and value == 1e+101
    return result

