# generated from model: ./re_1.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# regex "/^S/i"
jmsc_re_0 = re.compile("^S", re.IGNORECASE).search

# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    # "/^S/i"
    result = isinstance(value, str) and jmsc_re_0(value) is not None
    return result

