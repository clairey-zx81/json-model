# generated from model: ./obj_02.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "li0" ('$'.'$'.li0)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'$'.li0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_0_idx, array_0_item in enumerate(value):
            # '$'.'$'.li0.0
            result = isinstance(array_0_item, int) and not isinstance(array_0_item, bool) and array_0_item >= 0
            if not result: break
    return result


# define "ls0" ('$'.'$'.ls0)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'$'.ls0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_1_idx, array_1_item in enumerate(value):
            # '$'.'$'.ls0.0
            result = jmsc_f_2(array_1_item, path)
            if not result: break
    return result


# define "lb0" ('$'.'$'.lb0)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'$'.lb0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_2_idx, array_2_item in enumerate(value):
            # '$'.'$'.lb0.0
            result = isinstance(array_2_item, bool)
            if not result: break
    return result


# define "lf0" ('$'.'$'.lf0)
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    # '$'.'$'.lf0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_3_idx, array_3_item in enumerate(value):
            # '$'.'$'.lf0.0
            result = isinstance(array_3_item, float) and array_3_item >= 0.0
            if not result: break
    return result


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_4_idx, array_4_item in enumerate(value):
            # '$'.0
            result = isinstance(array_4_item, float) and array_4_item >= 0.0
            if not result: break
    return result

