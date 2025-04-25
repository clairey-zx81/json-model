# generated from model: ./scp_00.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]


# define "a" ('$'.'$'.a)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'$'.a
    result = isinstance(value, str) and value == "a"
    return result


# define "A" ('$'.'$'.A)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'$'.A
    result = isinstance(value, str)
    return result


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    result = isinstance(value, str)
    return result

