import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

jmsc_f_1_must: dict[str, CheckFun]
jmsc_f_3_must: dict[str, CheckFun]
jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_0_may: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_1_may: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_obj_2_may: dict[str, CheckFun]
jmsc_obj_3_must: dict[str, CheckFun]
jmsc_obj_3_may: dict[str, CheckFun]

# define "jmsc_f_1_must_X" ($.%.X.X)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.X.X
    result = isinstance(value, str)
    return result

# define "jmsc_f_3_must_Y" ($.%.Y.Y)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.Y.Y
    result = isinstance(value, str)
    return result

# define "jmsc_obj_0_must_X" ($.%.E.|[0].X)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.%.E.|[0].X
    result = isinstance(value, str)
    return result

# define "jmsc_obj_0_may_Z" ($.%.E.|[0].Z)
def jmsc_f_7(value: Any, path: str) -> bool:
    # $.%.E.|[0].Z
    result = isinstance(value, str)
    return result

# define "jmsc_obj_1_must_Y" ($.%.E.|[1].Y)
def jmsc_f_8(value: Any, path: str) -> bool:
    # $.%.E.|[1].Y
    result = isinstance(value, str)
    return result

# define "jmsc_obj_1_may_Z" ($.%.E.|[1].Z)
def jmsc_f_9(value: Any, path: str) -> bool:
    # $.%.E.|[1].Z
    result = isinstance(value, str)
    return result

# define "jmsc_obj_2_must_X" ($.%.M.|[2].X)
def jmsc_f_11(value: Any, path: str) -> bool:
    # $.%.M.|[2].X
    result = isinstance(value, str)
    return result

# define "jmsc_obj_2_may_Z" ($.%.M.|[2].Z)
def jmsc_f_12(value: Any, path: str) -> bool:
    # $.%.M.|[2].Z
    result = isinstance(value, str)
    return result

# define "jmsc_obj_3_must_Y" ($.%.M.|[3].Y)
def jmsc_f_13(value: Any, path: str) -> bool:
    # $.%.M.|[3].Y
    result = isinstance(value, str)
    return result

# define "jmsc_obj_3_may_Z" ($.%.M.|[3].Z)
def jmsc_f_14(value: Any, path: str) -> bool:
    # $.%.M.|[3].Z
    result = isinstance(value, str)
    return result


# define "V" ($.%.V)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.V
    # $.%.V.|[0]
    result = isinstance(value, int) and not isinstance(value, bool)
    if not result:
        # $.%.V.|[1]
        result = isinstance(value, str)
    return result

# object $.%.X
def jmsc_f_1(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_1_must:  # must
            must_count += 1
            if not jmsc_f_1_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object $.%.Y
def jmsc_f_3(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_3_must:  # must
            must_count += 1
            if not jmsc_f_3_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object $.%.E.|[0]
def jmsc_obj_0(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_0_must:  # must
            must_count += 1
            if not jmsc_obj_0_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_0_may:  # may
            if not jmsc_obj_0_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1

# object $.%.E.|[1]
def jmsc_obj_1(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_1_must:  # must
            must_count += 1
            if not jmsc_obj_1_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_1_may:  # may
            if not jmsc_obj_1_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1

# define "E" ($.%.E)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.E
    result = isinstance(value, dict)
    if result:
        # $.%.E.|[0]
        result = jmsc_obj_0(value, path)
        if not result:
            # $.%.E.|[1]
            result = jmsc_obj_1(value, path)
    return result

# object $.%.M.|[2]
def jmsc_obj_2(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_2_must:  # must
            must_count += 1
            if not jmsc_obj_2_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_2_may:  # may
            if not jmsc_obj_2_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1

# object $.%.M.|[3]
def jmsc_obj_3(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_3_must:  # must
            must_count += 1
            if not jmsc_obj_3_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_3_may:  # may
            if not jmsc_obj_3_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1

# define "M" ($.%.M)
def jmsc_f_10(value: Any, path: str) -> bool:
    # $.%.M
    # $.%.M.|[0]
    result = isinstance(value, int) and not isinstance(value, bool)
    if not result:
        # $.%.M.|[1]
        result = isinstance(value, str)
        if not result:
            # $.%.M.|[2]
            result = jmsc_obj_2(value, path)
            if not result:
                # $.%.M.|[3]
                result = jmsc_obj_3(value, path)
    return result

# define "check_model" ($)
def check_model(value: Any, path: str = "$") -> bool:
    # $
    # $.@
    result = jmsc_f_10(value, path)
    return result

# object properties must and may maps
jmsc_f_1_must = {
    "X": jmsc_f_2,
}
jmsc_f_3_must = {
    "Y": jmsc_f_4,
}
jmsc_obj_0_must = {
    "X": jmsc_f_6,
}
jmsc_obj_0_may = {
    "Z": jmsc_f_7,
}
jmsc_obj_1_must = {
    "Y": jmsc_f_8,
}
jmsc_obj_1_may = {
    "Z": jmsc_f_9,
}
jmsc_obj_2_must = {
    "X": jmsc_f_11,
}
jmsc_obj_2_may = {
    "Z": jmsc_f_12,
}
jmsc_obj_3_must = {
    "Y": jmsc_f_13,
}
jmsc_obj_3_may = {
    "Z": jmsc_f_14,
}
