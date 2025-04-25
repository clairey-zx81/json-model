# generated from model: ./opt_00.model.json
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
        # '$'.'|'.0
        result = isinstance(value, int) and not isinstance(value, bool) and value == 1
        if not result:
            # '$'.'|'.1
            xc_0 = 0
            if xc_0 <= 1:
                # '$'.'|'.1.'^'.0
                xr_0 = isinstance(value, int) and not isinstance(value, bool) and value == 2
                if xr_0: xc_0 += 1
            if xc_0 <= 1:
                # '$'.'|'.1.'^'.1
                xr_0 = isinstance(value, int) and not isinstance(value, bool) and value == 3
                if xr_0: xc_0 += 1
            result = xc_0 == 1
    return result

