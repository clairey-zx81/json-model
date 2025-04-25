# generated from model: ./obj_01.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "foo" ('$'.'$'.foo)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'$'.foo
    result = jmsc_f_1(value, path)
    return result


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = jmsc_f_1(value, path)
    return result

