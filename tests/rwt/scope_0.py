# generated from model: ./scope_0.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# regex "/[0-9]/"
jm_re_0 = re.compile("[0-9]").search

# define "$S" ($.S)
def json_model_1(value: Jsonable, path: str) -> bool:
    # $.S
    # "/[0-9]/"
    result = isinstance(value, str) and jm_re_0(value) is not None
    return result


# define "check_model" ($)
def check_model(value: Jsonable, path: str = "$") -> bool:
    # $
    result = isinstance(value, list) and len(value) == 2
    if result:
        # $.0
        result = json_model_1(value[0], path)
        if result:
            # $.1
            result = json_model_1(value[1], path)
    return result

