# generated from model: ./null.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# define "$" ($)
def json_model_0(value: Jsonable, path: str) -> bool:
    # $
    result = value is None
    return result

# entry function check_model
def check_model(value: Jsonable, path: str = "$") -> bool:
    return json_model_0(value, path)

