# generated from model: ./en_00.model.json
from typing import Callable
import re as re

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type CheckFun = Callable[[Jsonable, str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# regex "/^((file|https?)://.+|\\./.*|\\.\\./.*)$/"
jmsc_re_0 = re.compile("^((file|https?)://.+|\\./.*|\\.\\./.*)$").search
jmsc_f_4_may: PropMap
jmsc_f_8_must: PropMap
jmsc_f_8_may: PropMap
# regex "/^(<=|>=|<|>|\u2265|\u2264)$/"
jmsc_re_1 = re.compile("^(<=|>=|<|>|\u2265|\u2264)$").search
# regex "/^(=|!=|\u2260)$/"
jmsc_re_2 = re.compile("^(=|!=|\u2260)$").search
jmsc_f_11_must: PropMap
jmsc_f_13_must: PropMap
jmsc_f_15_must: PropMap
jmsc_f_17_must: PropMap
# regex "/^[@|&^+/*]$/"
jmsc_re_3 = re.compile("^[@|&^+/*]$").search
jmsc_obj_1_must: PropMap
jmsc_obj_1_may: PropMap
jmsc_obj_2_must: PropMap
jmsc_obj_2_may: PropMap
jmsc_obj_3_must: PropMap
jmsc_obj_3_may: PropMap
jmsc_obj_4_must: PropMap
jmsc_obj_4_may: PropMap
jmsc_obj_5_must: PropMap
jmsc_obj_5_may: PropMap
jmsc_obj_6_may: PropMap
jmsc_obj_7_must: PropMap
jmsc_obj_7_may: PropMap
jmsc_obj_9_must: PropMap
jmsc_obj_9_may: PropMap
# regex "/.+/"
jmsc_re_4 = re.compile(".+").search
# regex "/^\\..*$/"
jmsc_re_5 = re.compile("^\\..*$").search
# regex "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
jmsc_re_6 = re.compile("^([|&^+/*@~<>=!$%]|<=|>=|!=)$").search
# regex "/^\\$.*$/"
jmsc_re_7 = re.compile("^\\$.*$").search
jmsc_obj_11_must: PropMap
jmsc_obj_11_may: PropMap
jmsc_f_47_may: PropMap
jmsc_f_50_may: PropMap
jmsc_obj_12_must: PropMap
jmsc_obj_12_may: PropMap
jmsc_f_56_may: PropMap
jmsc_f_59_may: PropMap
jmsc_obj_13_must: PropMap
jmsc_obj_13_may: PropMap
jmsc_f_64_may: PropMap
jmsc_f_67_may: PropMap
jmsc_obj_14_must: PropMap
jmsc_obj_14_may: PropMap
jmsc_f_72_may: PropMap
jmsc_f_75_may: PropMap
jmsc_obj_15_must: PropMap
jmsc_obj_15_may: PropMap
jmsc_f_80_may: PropMap
jmsc_f_83_may: PropMap
jmsc_obj_16_may: PropMap
jmsc_f_87_may: PropMap
jmsc_f_90_may: PropMap

# define "jmsc_f_4_may_#" ('$'.'$'.Comment.'#')
def jmsc_f_5(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Comment.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_8_must_@" ('$'.'$'.Constraint.'@')
def jmsc_f_9(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Constraint.'@'
    result = jmsc_f_7(value, path)
    return result


# define "jmsc_f_8_may_!" ('$'.'$'.Constraint.'!')
def jmsc_f_10(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Constraint.'!'
    result = isinstance(value, bool)
    return result


# define "jmsc_f_11_must_|" ('$'.'$'.Or.'|')
def jmsc_f_12(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Or.'|'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_2_idx, array_2_item in enumerate(value):
            # '$'.'$'.Or.'|'.0
            result = jmsc_f_7(array_2_item, path)
            if not result: break
    return result


# define "jmsc_f_13_must_&" ('$'.'$'.And.'&')
def jmsc_f_14(value: Jsonable, path: str) -> bool:
    # '$'.'$'.And.'&'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_3_idx, array_3_item in enumerate(value):
            # '$'.'$'.And.'&'.0
            result = jmsc_f_7(array_3_item, path)
            if not result: break
    return result


# define "jmsc_f_15_must_^" ('$'.'$'.Xor.'^')
def jmsc_f_16(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Xor.'^'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_4_idx, array_4_item in enumerate(value):
            # '$'.'$'.Xor.'^'.0
            result = jmsc_f_7(array_4_item, path)
            if not result: break
    return result


# define "jmsc_f_17_must_+" ('$'.'$'.Add.'+')
def jmsc_f_18(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Add.'+'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_5_idx, array_5_item in enumerate(value):
            # '$'.'$'.Add.'+'.0
            result = jmsc_f_7(array_5_item, path)
            if not result: break
    return result


# define "jmsc_obj_1_must_@" ('$'.'$'.Elem.'|'.0.'@')
def jmsc_f_21(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.0.'@'
    result = jmsc_f_7(value, path)
    return result


# define "jmsc_obj_1_may_#" ('$'.'$'.Elem.'|'.0.'#')
def jmsc_f_22(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.0.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_1_may_!" ('$'.'$'.Elem.'|'.0.'!')
def jmsc_f_23(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.0.'!'
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_2_must_|" ('$'.'$'.Elem.'|'.1.'|')
def jmsc_f_24(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.1.'|'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_6_idx, array_6_item in enumerate(value):
            # '$'.'$'.Elem.'|'.1.'|'.0
            result = jmsc_f_7(array_6_item, path)
            if not result: break
    return result


# define "jmsc_obj_2_may_#" ('$'.'$'.Elem.'|'.1.'#')
def jmsc_f_25(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.1.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_3_must_&" ('$'.'$'.Elem.'|'.2.'&')
def jmsc_f_26(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.2.'&'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_7_idx, array_7_item in enumerate(value):
            # '$'.'$'.Elem.'|'.2.'&'.0
            result = jmsc_f_7(array_7_item, path)
            if not result: break
    return result


# define "jmsc_obj_3_may_#" ('$'.'$'.Elem.'|'.2.'#')
def jmsc_f_27(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.2.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_4_must_^" ('$'.'$'.Elem.'|'.3.'^')
def jmsc_f_28(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.3.'^'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_8_idx, array_8_item in enumerate(value):
            # '$'.'$'.Elem.'|'.3.'^'.0
            result = jmsc_f_7(array_8_item, path)
            if not result: break
    return result


# define "jmsc_obj_4_may_#" ('$'.'$'.Elem.'|'.3.'#')
def jmsc_f_29(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.3.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_5_must_+" ('$'.'$'.Elem.'|'.4.'+')
def jmsc_f_30(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.4.'+'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_9_idx, array_9_item in enumerate(value):
            # '$'.'$'.Elem.'|'.4.'+'.0
            result = jmsc_f_7(array_9_item, path)
            if not result: break
    return result


# define "jmsc_obj_5_may_#" ('$'.'$'.Elem.'|'.4.'#')
def jmsc_f_31(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.4.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_6_may_#" ('$'.'$'.Elem.'|'.5.'#')
def jmsc_f_32(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem.'|'.5.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_7_must_/" ('$'.'$'.Trafo.'|'.1.'/')
def jmsc_f_34(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.1.'/'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_10_idx, array_10_item in enumerate(value):
            # '$'.'$'.Trafo.'|'.1.'/'.0
            result = jmsc_f_2(array_10_item, path)
            if not result: break
    return result


# define "jmsc_obj_7_may_#" ('$'.'$'.Trafo.'|'.1.'#')
def jmsc_f_35(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.1.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_7_may_*" ('$'.'$'.Trafo.'|'.1.'*')
def jmsc_f_36(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.1.'*'
    # '$'.'$'.Trafo.'|'.1.'*'.'|'.0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_11_idx, array_11_item in enumerate(value):
            # '$'.'$'.Trafo.'|'.1.'*'.'|'.0.0
            result = jmsc_f_2(array_11_item, path)
            if not result: break
    if not result:
        # '$'.'$'.Trafo.'|'.1.'*'.'|'.1
        result = jmsc_obj_8(value, path)
    return result


# define "jmsc_obj_9_must_*" ('$'.'$'.Trafo.'|'.2.'*')
def jmsc_f_37(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.2.'*'
    # '$'.'$'.Trafo.'|'.2.'*'.'|'.0
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_12_idx, array_12_item in enumerate(value):
            # '$'.'$'.Trafo.'|'.2.'*'.'|'.0.0
            result = jmsc_f_2(array_12_item, path)
            if not result: break
    if not result:
        # '$'.'$'.Trafo.'|'.2.'*'.'|'.1
        result = jmsc_obj_10(value, path)
    return result


# define "jmsc_obj_9_may_#" ('$'.'$'.Trafo.'|'.2.'#')
def jmsc_f_38(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.2.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_9_may_/" ('$'.'$'.Trafo.'|'.2.'/')
def jmsc_f_39(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo.'|'.2.'/'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_13_idx, array_13_item in enumerate(value):
            # '$'.'$'.Trafo.'|'.2.'/'.0
            result = jmsc_f_2(array_13_item, path)
            if not result: break
    return result


# define "jmsc_obj_11_must_@" ('$'.'$'.Root.'|'.0.'@')
def jmsc_f_45(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'@'
    result = jmsc_f_7(value, path)
    return result


# define "jmsc_obj_11_may_~" ('$'.'$'.Root.'|'.0.'~')
def jmsc_f_46(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_47_may_#" ('$'.'$'.Root.'|'.0.'$'.'#')
def jmsc_f_48(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_47_may_" ('$'.'$'.Root.'|'.0.'$'.'')
def jmsc_f_49(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_50_may_#" ('$'.'$'.Root.'|'.0.'%'.'#')
def jmsc_f_51(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_11_may_#" ('$'.'$'.Root.'|'.0.'#')
def jmsc_f_52(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_11_may_!" ('$'.'$'.Root.'|'.0.'!')
def jmsc_f_53(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.0.'!'
    result = isinstance(value, bool)
    return result


# define "jmsc_obj_12_must_|" ('$'.'$'.Root.'|'.1.'|')
def jmsc_f_54(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'|'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_14_idx, array_14_item in enumerate(value):
            # '$'.'$'.Root.'|'.1.'|'.0
            result = jmsc_f_7(array_14_item, path)
            if not result: break
    return result


# define "jmsc_obj_12_may_~" ('$'.'$'.Root.'|'.1.'~')
def jmsc_f_55(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_56_may_#" ('$'.'$'.Root.'|'.1.'$'.'#')
def jmsc_f_57(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_56_may_" ('$'.'$'.Root.'|'.1.'$'.'')
def jmsc_f_58(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_59_may_#" ('$'.'$'.Root.'|'.1.'%'.'#')
def jmsc_f_60(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_12_may_#" ('$'.'$'.Root.'|'.1.'#')
def jmsc_f_61(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.1.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_13_must_&" ('$'.'$'.Root.'|'.2.'&')
def jmsc_f_62(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'&'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_15_idx, array_15_item in enumerate(value):
            # '$'.'$'.Root.'|'.2.'&'.0
            result = jmsc_f_7(array_15_item, path)
            if not result: break
    return result


# define "jmsc_obj_13_may_~" ('$'.'$'.Root.'|'.2.'~')
def jmsc_f_63(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_64_may_#" ('$'.'$'.Root.'|'.2.'$'.'#')
def jmsc_f_65(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_64_may_" ('$'.'$'.Root.'|'.2.'$'.'')
def jmsc_f_66(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_67_may_#" ('$'.'$'.Root.'|'.2.'%'.'#')
def jmsc_f_68(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_13_may_#" ('$'.'$'.Root.'|'.2.'#')
def jmsc_f_69(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.2.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_14_must_^" ('$'.'$'.Root.'|'.3.'^')
def jmsc_f_70(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'^'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_16_idx, array_16_item in enumerate(value):
            # '$'.'$'.Root.'|'.3.'^'.0
            result = jmsc_f_7(array_16_item, path)
            if not result: break
    return result


# define "jmsc_obj_14_may_~" ('$'.'$'.Root.'|'.3.'~')
def jmsc_f_71(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_72_may_#" ('$'.'$'.Root.'|'.3.'$'.'#')
def jmsc_f_73(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_72_may_" ('$'.'$'.Root.'|'.3.'$'.'')
def jmsc_f_74(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_75_may_#" ('$'.'$'.Root.'|'.3.'%'.'#')
def jmsc_f_76(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_14_may_#" ('$'.'$'.Root.'|'.3.'#')
def jmsc_f_77(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.3.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_15_must_+" ('$'.'$'.Root.'|'.4.'+')
def jmsc_f_78(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'+'
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_17_idx, array_17_item in enumerate(value):
            # '$'.'$'.Root.'|'.4.'+'.0
            result = jmsc_f_7(array_17_item, path)
            if not result: break
    return result


# define "jmsc_obj_15_may_~" ('$'.'$'.Root.'|'.4.'~')
def jmsc_f_79(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_80_may_#" ('$'.'$'.Root.'|'.4.'$'.'#')
def jmsc_f_81(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_80_may_" ('$'.'$'.Root.'|'.4.'$'.'')
def jmsc_f_82(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_83_may_#" ('$'.'$'.Root.'|'.4.'%'.'#')
def jmsc_f_84(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_15_may_#" ('$'.'$'.Root.'|'.4.'#')
def jmsc_f_85(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.4.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_obj_16_may_~" ('$'.'$'.Root.'|'.5.'~')
def jmsc_f_86(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.5.'~'
    result = jmsc_f_0(value, path)
    return result


# define "jmsc_f_87_may_#" ('$'.'$'.Root.'|'.5.'$'.'#')
def jmsc_f_88(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.5.'$'.'#'
    result = isinstance(value, str)
    return result


# define "jmsc_f_87_may_" ('$'.'$'.Root.'|'.5.'$'.'')
def jmsc_f_89(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.5.'$'.''
    result = jmsc_f_0(value, path)
    return result




# define "jmsc_f_90_may_#" ('$'.'$'.Root.'|'.5.'%'.'#')
def jmsc_f_91(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.5.'%'.'#'
    result = isinstance(value, str)
    return result




# define "jmsc_obj_16_may_#" ('$'.'$'.Root.'|'.5.'#')
def jmsc_f_92(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root.'|'.5.'#'
    result = isinstance(value, str)
    return result


# define "Url" ('$'.'$'.Url)
def jmsc_f_0(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Url
    # "/^((file|https?)://.+|\\./.*|\\.\\./.*)$/"
    result = isinstance(value, str) and jmsc_re_0(value) is not None
    return result


# define "Val" ('$'.'$'.Val)
def jmsc_f_1(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Val
    # '$'.'$'.Val.'|'.0
    result = value is None
    if not result:
        # '$'.'$'.Val.'|'.1
        result = isinstance(value, bool)
        if not result:
            # '$'.'$'.Val.'|'.2
            result = isinstance(value, int) and not isinstance(value, bool)
            if not result:
                # '$'.'$'.Val.'|'.3
                result = isinstance(value, float)
                if not result:
                    # '$'.'$'.Val.'|'.4
                    result = isinstance(value, str)
    return result


# object '$'.'$'.Any.'|'.2
def jmsc_obj_0(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # '$'.'$'.Any.'|'.2.''
        result = jmsc_f_2(model, path)
        if not result: return False
    return True


# define "Any" ('$'.'$'.Any)
def jmsc_f_2(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Any
    # '$'.'$'.Any.'|'.0
    result = jmsc_f_1(value, path)
    if not result:
        # '$'.'$'.Any.'|'.1
        result = isinstance(value, list)
        if result:
            assert isinstance(value, list)  # pyright helper
            for array_0_idx, array_0_item in enumerate(value):
                # '$'.'$'.Any.'|'.1.0
                result = jmsc_f_2(array_0_item, path)
                if not result: break
        if not result:
            # '$'.'$'.Any.'|'.2
            result = jmsc_obj_0(value, path)
    return result


# define "None" ('$'.'$'.None)
def jmsc_f_3(value: Jsonable, path: str) -> bool:
    # '$'.'$'.None
    result = False
    return result


# object '$'.'$'.Comment
def jmsc_f_4(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_4_may:  # may
            if not jmsc_f_4_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return True




# define "Array" ('$'.'$'.Array)
def jmsc_f_6(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Array
    result = isinstance(value, list)
    if result:
        assert isinstance(value, list)  # pyright helper
        for array_1_idx, array_1_item in enumerate(value):
            # '$'.'$'.Array.0
            result = jmsc_f_7(array_1_item, path)
            if not result: break
    return result


# object '$'.'$'.Constraint
def jmsc_f_8(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_8_must:  # must
            must_count += 1
            if not jmsc_f_8_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_f_8_may:  # may
            if not jmsc_f_8_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_1(prop) is not None:  # /^(<=|>=|<|>|≥|≤)$/
            # '$'.'$'.Constraint.'/^(<=|>=|<|>|≥|≤)$/'
            # '$'.'$'.Constraint.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            result = isinstance(model, int) and not isinstance(model, bool)
            if not result:
                # '$'.'$'.Constraint.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                result = isinstance(model, float)
                if not result:
                    # '$'.'$'.Constraint.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    result = isinstance(model, str)
            if not result: return False
        elif jmsc_re_2(prop) is not None:  # /^(=|!=|≠)$/
            # '$'.'$'.Constraint.'/^(=|!=|≠)$/'
            result = jmsc_f_1(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return must_count == 1




# object '$'.'$'.Or
def jmsc_f_11(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_11_must:  # must
            must_count += 1
            if not jmsc_f_11_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1




# object '$'.'$'.And
def jmsc_f_13(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_13_must:  # must
            must_count += 1
            if not jmsc_f_13_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1




# object '$'.'$'.Xor
def jmsc_f_15(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_15_must:  # must
            must_count += 1
            if not jmsc_f_15_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1




# object '$'.'$'.Add
def jmsc_f_17(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_17_must:  # must
            must_count += 1
            if not jmsc_f_17_must[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1




# object '$'.'$'.Obj
def jmsc_f_19(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_3(prop) is not None:  # /^[@|&^+/*]$/
            # '$'.'$'.Obj.'/^[@|&^+/*]$/'
            result = False
            if not result: return False
        else:  # catch all
            # '$'.'$'.Obj.''
            result = jmsc_f_7(model, path)
            if not result: return False
    return True




# object '$'.'$'.Elem.'|'.0
def jmsc_obj_1(value: Jsonable, path: str) -> bool:
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
        elif jmsc_re_1(prop) is not None:  # /^(<=|>=|<|>|≥|≤)$/
            # '$'.'$'.Elem.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            # '$'.'$'.Elem.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            result = isinstance(model, int) and not isinstance(model, bool)
            if not result:
                # '$'.'$'.Elem.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                result = isinstance(model, float)
                if not result:
                    # '$'.'$'.Elem.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    result = isinstance(model, str)
            if not result: return False
        elif jmsc_re_2(prop) is not None:  # /^(=|!=|≠)$/
            # '$'.'$'.Elem.'|'.0.'/^(=|!=|≠)$/'
            result = jmsc_f_1(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Elem.'|'.1
def jmsc_obj_2(value: Jsonable, path: str) -> bool:
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


# object '$'.'$'.Elem.'|'.2
def jmsc_obj_3(value: Jsonable, path: str) -> bool:
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


# object '$'.'$'.Elem.'|'.3
def jmsc_obj_4(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_4_must:  # must
            must_count += 1
            if not jmsc_obj_4_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_4_may:  # may
            if not jmsc_obj_4_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Elem.'|'.4
def jmsc_obj_5(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_5_must:  # must
            must_count += 1
            if not jmsc_obj_5_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_5_may:  # may
            if not jmsc_obj_5_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Elem.'|'.5
def jmsc_obj_6(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_6_may:  # may
            if not jmsc_obj_6_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_3(prop) is not None:  # /^[@|&^+/*]$/
            # '$'.'$'.Elem.'|'.5.'/^[@|&^+/*]$/'
            result = False
            if not result: return False
        else:  # catch all
            # '$'.'$'.Elem.'|'.5.''
            result = jmsc_f_7(model, path)
            if not result: return False
    return True


# define "Elem" ('$'.'$'.Elem)
def jmsc_f_20(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Elem
    result = isinstance(value, dict)
    if result:
        # '$'.'$'.Elem.'|'.0
        result = jmsc_obj_1(value, path)
        if not result:
            # '$'.'$'.Elem.'|'.1
            result = jmsc_obj_2(value, path)
            if not result:
                # '$'.'$'.Elem.'|'.2
                result = jmsc_obj_3(value, path)
                if not result:
                    # '$'.'$'.Elem.'|'.3
                    result = jmsc_obj_4(value, path)
                    if not result:
                        # '$'.'$'.Elem.'|'.4
                        result = jmsc_obj_5(value, path)
                        if not result:
                            # '$'.'$'.Elem.'|'.5
                            result = jmsc_obj_6(value, path)
    return result


# object '$'.'$'.Trafo.'|'.1.'*'.'|'.1
def jmsc_obj_8(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # '$'.'$'.Trafo.'|'.1.'*'.'|'.1.''
        result = jmsc_f_7(model, path)
        if not result: return False
    return True


# object '$'.'$'.Trafo.'|'.1
def jmsc_obj_7(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_7_must:  # must
            must_count += 1
            if not jmsc_obj_7_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_7_may:  # may
            if not jmsc_obj_7_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Trafo.'|'.2.'*'.'|'.1
def jmsc_obj_10(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        # '$'.'$'.Trafo.'|'.2.'*'.'|'.1.''
        result = jmsc_f_7(model, path)
        if not result: return False
    return True


# object '$'.'$'.Trafo.'|'.2
def jmsc_obj_9(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_9_must:  # must
            must_count += 1
            if not jmsc_obj_9_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_9_may:  # may
            if not jmsc_obj_9_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# define "Trafo" ('$'.'$'.Trafo)
def jmsc_f_33(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Trafo
    # '$'.'$'.Trafo.'|'.0
    result = jmsc_f_7(value, path)
    if not result:
        # '$'.'$'.Trafo.'|'.1
        result = jmsc_obj_7(value, path)
        if not result:
            # '$'.'$'.Trafo.'|'.2
            result = jmsc_obj_9(value, path)
    return result


# define "Scalar" ('$'.'$'.Scalar)
def jmsc_f_40(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Scalar
    result = not isinstance(value, (list, dict)) and value in set()
    if not result:
        # '$'.'$'.Scalar.'|'.0
        result = value is None
        if not result:
            # '$'.'$'.Scalar.'|'.1
            result = isinstance(value, bool) and value == True
            if not result:
                # '$'.'$'.Scalar.'|'.2
                result = isinstance(value, int) and not isinstance(value, bool) and value == 0
                if not result:
                    # '$'.'$'.Scalar.'|'.3
                    result = isinstance(value, int) and not isinstance(value, bool) and value == 1
                    if not result:
                        # '$'.'$'.Scalar.'|'.4
                        result = isinstance(value, int) and not isinstance(value, bool) and value == -1
                        if not result:
                            # '$'.'$'.Scalar.'|'.5
                            result = isinstance(value, float) and value == 0.0
                            if not result:
                                # '$'.'$'.Scalar.'|'.6
                                result = isinstance(value, float) and value == 1.0
                                if not result:
                                    # '$'.'$'.Scalar.'|'.7
                                    result = isinstance(value, float) and value == -1.0
                                    if not result:
                                        # '$'.'$'.Scalar.'|'.8
                                        result = isinstance(value, str)
    return result


# define "Model" ('$'.'$'.Model)
def jmsc_f_7(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Model
    # '$'.'$'.Model.'|'.0
    result = jmsc_f_40(value, path)
    if not result:
        # '$'.'$'.Model.'|'.1
        result = jmsc_f_6(value, path)
        if not result:
            # '$'.'$'.Model.'|'.2
            result = jmsc_f_20(value, path)
    return result


# object '$'.'$'.Defs
def jmsc_f_41(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Defs.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True




# object '$'.'$'.Rename
def jmsc_f_42(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Rename.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        else:  # no catch all
            return False
    return True




# object '$'.'$'.Rewrite
def jmsc_f_43(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Rewrite.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True




# object '$'.'$'.Root.'|'.0.'$'
def jmsc_f_47(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_47_may:  # may
            if not jmsc_f_47_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.0.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.0.'%'
def jmsc_f_50(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_50_may:  # may
            if not jmsc_f_50_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.0.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.0.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.0
def jmsc_obj_11(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_11_must:  # must
            must_count += 1
            if not jmsc_obj_11_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_11_may:  # may
            if not jmsc_obj_11_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_1(prop) is not None:  # /^(<=|>=|<|>|≥|≤)$/
            # '$'.'$'.Root.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            # '$'.'$'.Root.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            result = isinstance(model, int) and not isinstance(model, bool)
            if not result:
                # '$'.'$'.Root.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                result = isinstance(model, float)
                if not result:
                    # '$'.'$'.Root.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    result = isinstance(model, str)
            if not result: return False
        elif jmsc_re_2(prop) is not None:  # /^(=|!=|≠)$/
            # '$'.'$'.Root.'|'.0.'/^(=|!=|≠)$/'
            result = jmsc_f_1(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Root.'|'.1.'$'
def jmsc_f_56(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_56_may:  # may
            if not jmsc_f_56_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.1.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.1.'%'
def jmsc_f_59(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_59_may:  # may
            if not jmsc_f_59_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.1.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.1.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.1
def jmsc_obj_12(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_12_must:  # must
            must_count += 1
            if not jmsc_obj_12_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_12_may:  # may
            if not jmsc_obj_12_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Root.'|'.2.'$'
def jmsc_f_64(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_64_may:  # may
            if not jmsc_f_64_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.2.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.2.'%'
def jmsc_f_67(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_67_may:  # may
            if not jmsc_f_67_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.2.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.2.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.2
def jmsc_obj_13(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_13_must:  # must
            must_count += 1
            if not jmsc_obj_13_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_13_may:  # may
            if not jmsc_obj_13_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Root.'|'.3.'$'
def jmsc_f_72(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_72_may:  # may
            if not jmsc_f_72_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.3.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.3.'%'
def jmsc_f_75(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_75_may:  # may
            if not jmsc_f_75_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.3.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.3.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.3
def jmsc_obj_14(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_14_must:  # must
            must_count += 1
            if not jmsc_obj_14_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_14_may:  # may
            if not jmsc_obj_14_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Root.'|'.4.'$'
def jmsc_f_80(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_80_may:  # may
            if not jmsc_f_80_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.4.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.4.'%'
def jmsc_f_83(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_83_may:  # may
            if not jmsc_f_83_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.4.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.4.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.4
def jmsc_obj_15(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    must_count = 0
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_15_must:  # must
            must_count += 1
            if not jmsc_obj_15_must[prop](model, f"{path}.{prop}"):
                return False
        elif prop in jmsc_obj_15_may:  # may
            if not jmsc_obj_15_may[prop](model, f"{path}.{prop}"):
                return False
        else:  # no catch all
            return False
    return must_count == 1


# object '$'.'$'.Root.'|'.5.'$'
def jmsc_f_87(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_87_may:  # may
            if not jmsc_f_87_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_4(prop) is not None:  # /.+/
            # '$'.'$'.Root.'|'.5.'$'.'/.+/'
            result = jmsc_f_7(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.5.'%'
def jmsc_f_90(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_f_90_may:  # may
            if not jmsc_f_90_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_5(prop) is not None:  # /^\..*$/
            # '$'.'$'.Root.'|'.5.'%'.'/^\..*$/'
            # "/^([|&^+/*@~<>=!$%]|<=|>=|!=)$/"
            result = isinstance(model, str) and jmsc_re_6(model) is not None
            if not result: return False
        elif jmsc_re_7(prop) is not None:  # /^\$.*$/
            # '$'.'$'.Root.'|'.5.'%'.'/^\$.*$/'
            result = jmsc_f_33(model, path)
            if not result: return False
        else:  # no catch all
            return False
    return True


# object '$'.'$'.Root.'|'.5
def jmsc_obj_16(value: Jsonable, path: str) -> bool:
    if not isinstance(value, dict):
        return False
    for prop, model in value.items():
        assert isinstance(prop, str)
        if prop in jmsc_obj_16_may:  # may
            if not jmsc_obj_16_may[prop](model, f"{path}.{prop}"):
                return False
        elif jmsc_re_3(prop) is not None:  # /^[@|&^+/*]$/
            # '$'.'$'.Root.'|'.5.'/^[@|&^+/*]$/'
            result = False
            if not result: return False
        else:  # catch all
            # '$'.'$'.Root.'|'.5.''
            result = jmsc_f_7(model, path)
            if not result: return False
    return True


# define "Root" ('$'.'$'.Root)
def jmsc_f_44(value: Jsonable, path: str) -> bool:
    # '$'.'$'.Root
    result = isinstance(value, dict)
    if result:
        # '$'.'$'.Root.'|'.0
        result = jmsc_obj_11(value, path)
        if not result:
            # '$'.'$'.Root.'|'.1
            result = jmsc_obj_12(value, path)
            if not result:
                # '$'.'$'.Root.'|'.2
                result = jmsc_obj_13(value, path)
                if not result:
                    # '$'.'$'.Root.'|'.3
                    result = jmsc_obj_14(value, path)
                    if not result:
                        # '$'.'$'.Root.'|'.4
                        result = jmsc_obj_15(value, path)
                        if not result:
                            # '$'.'$'.Root.'|'.5
                            result = jmsc_obj_16(value, path)
    return result


# define "RootModel" ('$'.'$'.RootModel)
def jmsc_f_93(value: Jsonable, path: str) -> bool:
    # '$'.'$'.RootModel
    # '$'.'$'.RootModel.'|'.0
    result = jmsc_f_40(value, path)
    if not result:
        # '$'.'$'.RootModel.'|'.1
        result = jmsc_f_6(value, path)
        if not result:
            # '$'.'$'.RootModel.'|'.2
            result = jmsc_f_44(value, path)
    return result


# define "check_model" ('$')
def check_model(value: Jsonable, path: str = "$") -> bool:
    # '$'
    # '$'.'|'.0
    result = jmsc_f_40(value, path)
    if not result:
        # '$'.'|'.1
        result = jmsc_f_6(value, path)
        if not result:
            # '$'.'|'.2
            result = jmsc_f_44(value, path)
    return result

# object properties maps
jmsc_f_4_may = {
    "#": jmsc_f_5,
}
jmsc_f_8_must = {
    "@": jmsc_f_9,
}
jmsc_f_8_may = {
    "!": jmsc_f_10,
}
jmsc_f_11_must = {
    "|": jmsc_f_12,
}
jmsc_f_13_must = {
    "&": jmsc_f_14,
}
jmsc_f_15_must = {
    "^": jmsc_f_16,
}
jmsc_f_17_must = {
    "+": jmsc_f_18,
}
jmsc_obj_1_must = {
    "@": jmsc_f_21,
}
jmsc_obj_1_may = {
    "#": jmsc_f_22,
    "!": jmsc_f_23,
}
jmsc_obj_2_must = {
    "|": jmsc_f_24,
}
jmsc_obj_2_may = {
    "#": jmsc_f_25,
}
jmsc_obj_3_must = {
    "&": jmsc_f_26,
}
jmsc_obj_3_may = {
    "#": jmsc_f_27,
}
jmsc_obj_4_must = {
    "^": jmsc_f_28,
}
jmsc_obj_4_may = {
    "#": jmsc_f_29,
}
jmsc_obj_5_must = {
    "+": jmsc_f_30,
}
jmsc_obj_5_may = {
    "#": jmsc_f_31,
}
jmsc_obj_6_may = {
    "#": jmsc_f_32,
}
jmsc_obj_7_must = {
    "/": jmsc_f_34,
}
jmsc_obj_7_may = {
    "#": jmsc_f_35,
    "*": jmsc_f_36,
}
jmsc_obj_9_must = {
    "*": jmsc_f_37,
}
jmsc_obj_9_may = {
    "#": jmsc_f_38,
    "/": jmsc_f_39,
}
jmsc_obj_11_must = {
    "@": jmsc_f_45,
}
jmsc_obj_11_may = {
    "~": jmsc_f_46,
    "$": jmsc_f_47,
    "%": jmsc_f_50,
    "#": jmsc_f_52,
    "!": jmsc_f_53,
}
jmsc_f_47_may = {
    "#": jmsc_f_48,
    "": jmsc_f_49,
}
jmsc_f_50_may = {
    "#": jmsc_f_51,
}
jmsc_obj_12_must = {
    "|": jmsc_f_54,
}
jmsc_obj_12_may = {
    "~": jmsc_f_55,
    "$": jmsc_f_56,
    "%": jmsc_f_59,
    "#": jmsc_f_61,
}
jmsc_f_56_may = {
    "#": jmsc_f_57,
    "": jmsc_f_58,
}
jmsc_f_59_may = {
    "#": jmsc_f_60,
}
jmsc_obj_13_must = {
    "&": jmsc_f_62,
}
jmsc_obj_13_may = {
    "~": jmsc_f_63,
    "$": jmsc_f_64,
    "%": jmsc_f_67,
    "#": jmsc_f_69,
}
jmsc_f_64_may = {
    "#": jmsc_f_65,
    "": jmsc_f_66,
}
jmsc_f_67_may = {
    "#": jmsc_f_68,
}
jmsc_obj_14_must = {
    "^": jmsc_f_70,
}
jmsc_obj_14_may = {
    "~": jmsc_f_71,
    "$": jmsc_f_72,
    "%": jmsc_f_75,
    "#": jmsc_f_77,
}
jmsc_f_72_may = {
    "#": jmsc_f_73,
    "": jmsc_f_74,
}
jmsc_f_75_may = {
    "#": jmsc_f_76,
}
jmsc_obj_15_must = {
    "+": jmsc_f_78,
}
jmsc_obj_15_may = {
    "~": jmsc_f_79,
    "$": jmsc_f_80,
    "%": jmsc_f_83,
    "#": jmsc_f_85,
}
jmsc_f_80_may = {
    "#": jmsc_f_81,
    "": jmsc_f_82,
}
jmsc_f_83_may = {
    "#": jmsc_f_84,
}
jmsc_obj_16_may = {
    "~": jmsc_f_86,
    "$": jmsc_f_87,
    "%": jmsc_f_90,
    "#": jmsc_f_92,
}
jmsc_f_87_may = {
    "#": jmsc_f_88,
    "": jmsc_f_89,
}
jmsc_f_90_may = {
    "#": jmsc_f_91,
}

