# generated from model: ./scope_1.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# regex "/[a-z]/"
jm_re_0 = re.compile("[a-z]").search
# regex "/[0-9]/"
jm_re_1 = re.compile("[0-9]").search

# define "$R" ($.R)
def json_model_1(value: Jsonable, path: str) -> bool:
    # $.R
    result = json_model_3(value, path)
    return result


# define "$S" ($.S)
def json_model_2(value: Jsonable, path: str) -> bool:
    # $.S
    # "/[a-z]/"
    result = isinstance(value, str) and jm_re_0(value) is not None
    return result


# define "$./scope_0" ($.'$./scope_0')
def json_model_3(value: Jsonable, path: str) -> bool:
    # $.'$./scope_0'
    result = isinstance(value, list) and len(value) == 2
    if result:
        # $.'$./scope_0'.0
        result = json_model_4(value[0], path)
        if result:
            # $.'$./scope_0'.1
            result = json_model_4(value[1], path)
    return result


# define "$#R#S" ($.'$#R#S')
def json_model_4(value: Jsonable, path: str) -> bool:
    # $.'$#R#S'
    # "/[0-9]/"
    result = isinstance(value, str) and jm_re_1(value) is not None
    return result


# define "check_model" ($)
def check_model(value: Jsonable, path: str = "$") -> bool:
    # $
    # $.'|'.0
    result = json_model_2(value, path)
    if not result:
        # $.'|'.1
        result = json_model_4(value, path)
    return result

