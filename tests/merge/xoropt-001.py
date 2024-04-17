import re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]




# define "N" ($.%.N)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.%.N
    result = value is None
    return result

# define "B" ($.%.B)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.%.B
    result = isinstance(value, bool)
    return result

# define "I" ($.%.I)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.%.I
    result = isinstance(value, int) and not isinstance(value, bool)
    return result

# define "F" ($.%.F)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.%.F
    result = isinstance(value, float)
    return result

# define "S" ($.%.S)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.%.S
    result = isinstance(value, str)
    return result

# define "A" ($.%.A)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.%.A
    result = isinstance(value, list)
    if result:
        for idx_0, item_0 in enumerate(value):
            # $.%.A[0]
            result = jmsc_f_6(item_0, path)
            if not result: break
    return result

# object $.%.O
def jmsc_f_7(value: Any, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # $.%.O.
        result = jmsc_f_6(model, path)
        if not result: return False
    return True


# define "Any" ($)
def jmsc_f_8(value: Any, path: str) -> bool:
    # $
    # $.|[0]
    result = jmsc_f_0(value, path)
    if not result:
        # $.|[1]
        result = jmsc_f_1(value, path)
        if not result:
            # $.|[2]
            result = jmsc_f_2(value, path)
            if not result:
                # $.|[3]
                result = jmsc_f_3(value, path)
                if not result:
                    # $.|[4]
                    result = jmsc_f_4(value, path)
                    if not result:
                        # $.|[5]
                        result = jmsc_f_5(value, path)
                        if not result:
                            # $.|[6]
                            result = jmsc_f_7(value, path)
    return result

# named root
jmsc_f_6 = jmsc_f_8


# object properties must and may maps


def check_model(value) -> bool:
    return jmsc_f_8(value, "$")
