# generated from model: ./l10n.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

check_model_must: PropMap
jmsc_f_0_must: PropMap
# regex "/^\\./"
jmsc_re_0 = re.compile("^\\.").search
# regex "/^([#~$%@|&+^/*=!]|[<>!]=)$/"
jmsc_re_1 = re.compile("^([#~$%@|&+^/*=!]|[<>!]=)$").search
check_model_may: PropMap

# define "jmsc_f_0_must_Model" ('$'.'$'.Model)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Model
    result = isinstance(value, str) and value == "$https://json-model.org/models/json-model-v2"
    return result




# define "check_model_must_~" ('$'.'~')
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'~'
    result = isinstance(value, str) and value == "https://json-model.org/models/l10n"
    return result




# define "check_model_must_@" ('$'.'@')
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    # '$'.'@'
    result = isinstance(value, str) and value == "$Model"
    return result


# define "check_model_may_#" ('$'.'#')
def jmsc_f_5(value: Jsonable, path: str) -> bool:
    # '$'.'#'
    result = isinstance(value, str)
    return result


# object '$'.'$'
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_0_must:  # must
            must_count += 1
            if not jmsc_f_0_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'%'
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_0(prop) is not None:  # /^\./
            # '$'.'%'.'/^\./'
            # "/^([#~$%@|&+^/*=!]|[<>!]=)$/"
            result = isinstance(model, str) and jmsc_re_1(model) is not None
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'
def check_model(value: Jsonable, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in check_model_must:  # must
            must_count += 1
            if not check_model_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in check_model_may:  # may
            if not check_model_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 4



# object properties maps
check_model_must = {
    "$": jmsc_f_0,
    "~": jmsc_f_2,
    "%": jmsc_f_3,
    "@": jmsc_f_4,
}
jmsc_f_0_must = {
    "Model": jmsc_f_1,
}
check_model_may = {
    "#": jmsc_f_5,
}

