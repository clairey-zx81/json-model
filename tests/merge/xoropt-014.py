import re as re
from typing import Any, Callable

CheckFun = Callable[[Any, str], bool]

check_model_must: dict[str, CheckFun]
jmsc_obj_0_must: dict[str, CheckFun]
jmsc_obj_1_must: dict[str, CheckFun]
jmsc_obj_2_must: dict[str, CheckFun]
jmsc_obj_3_must: dict[str, CheckFun]
jmsc_map_0: dict[Any, CheckFun]

# define "jmsc_obj_0_must_t" ($.movie.|[0].t)
def jmsc_f_1(value: Any, path: str) -> bool:
    # $.movie.|[0].t
    result = isinstance(value, str) and value == "fr"
    return result

# define "jmsc_obj_0_must_titre" ($.movie.|[0].titre)
def jmsc_f_2(value: Any, path: str) -> bool:
    # $.movie.|[0].titre
    result = isinstance(value, str)
    return result

# define "jmsc_obj_1_must_t" ($.movie.|[1].t)
def jmsc_f_3(value: Any, path: str) -> bool:
    # $.movie.|[1].t
    result = isinstance(value, str) and value == "en"
    return result

# define "jmsc_obj_1_must_title" ($.movie.|[1].title)
def jmsc_f_4(value: Any, path: str) -> bool:
    # $.movie.|[1].title
    result = isinstance(value, str)
    return result

# define "jmsc_obj_2_must_t" ($.movie.|[2].t)
def jmsc_f_5(value: Any, path: str) -> bool:
    # $.movie.|[2].t
    result = isinstance(value, str) and value == "de"
    return result

# define "jmsc_obj_2_must_Title" ($.movie.|[2].Title)
def jmsc_f_6(value: Any, path: str) -> bool:
    # $.movie.|[2].Title
    result = isinstance(value, str)
    return result

# define "jmsc_obj_3_must_t" ($.movie.|[3].t)
def jmsc_f_7(value: Any, path: str) -> bool:
    # $.movie.|[3].t
    result = isinstance(value, str) and value == "ru"
    return result

# define "jmsc_obj_3_must_suti" ($.movie.|[3].suti)
def jmsc_f_8(value: Any, path: str) -> bool:
    # $.movie.|[3].suti
    result = isinstance(value, str)
    return result

# define "check_model_must_movie" ($.movie)
def jmsc_f_0(value: Any, path: str) -> bool:
    # $.movie
    result = isinstance(value, dict)
    if result:
        result = "t" in value
        if result:
            tag_0 = value["t"]
            if tag_0 in jmsc_map_0:
                result = jmsc_map_0[tag_0](value, path)
            else:
                result = False
    return result


# object $.movie.|[0]
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
        else:  # no catch all
            return False
    return must_count == 2

# object $.movie.|[1]
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
        else:  # no catch all
            return False
    return must_count == 2

# object $.movie.|[2]
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
        else:  # no catch all
            return False
    return must_count == 2

# object $.movie.|[3]
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
        else:  # no catch all
            return False
    return must_count == 2

# object $
def check_model(value: Any, path: str = "$") -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in check_model_must:  # must
            must_count += 1
            if not check_model_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object properties must and may maps
check_model_must = {
    "movie": jmsc_f_0,
}
jmsc_obj_0_must = {
    "t": jmsc_f_1,
    "titre": jmsc_f_2,
}
jmsc_obj_1_must = {
    "t": jmsc_f_3,
    "title": jmsc_f_4,
}
jmsc_obj_2_must = {
    "t": jmsc_f_5,
    "Title": jmsc_f_6,
}
jmsc_obj_3_must = {
    "t": jmsc_f_7,
    "suti": jmsc_f_8,
}
jmsc_map_0 = {
    "fr": jmsc_obj_0,
    "en": jmsc_obj_1,
    "de": jmsc_obj_2,
    "ru": jmsc_obj_3,
}
