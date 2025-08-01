#! /bin/env python
#
# Generated by JSON Model Compiler version 2.0b1
# see https://github.com/clairey-zx81/json-model
#
from typing import Callable
import re2 as re
from json_model.runtime import *
__version__ = "2"

def check_model_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return check_model_map[name]

# entry point for generated checkers
def check_model(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity agains JSON Model name."""
    if name not in check_model_map:
        raise Exception(f"unexpected model name: {name}")
    checker = check_model_map[name]
    return checker(val, [], rep)

_jm_map_0: dict[str, str]
check_model_map: PropMap

# check $position (.'$position')
def json_model_2(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$position'
    # .'$position'.'@'
    res = isinstance(val, list)
    if res:
        for arr_0_idx, arr_0_item in enumerate(val):
            arr_0_lpath: Path = (path + [ arr_0_idx ]) if path is not None else None
            # .'$position'.'@'.0
            res = isinstance(arr_0_item, (int, float)) and not isinstance(arr_0_item, bool)
            if not res:
                rep is None or rep.append(("not a -1.0 loose float [.'$position'.'@'.0]", arr_0_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$position'.'@']", path))
    if res:
        ival_0: int = len(val)
        res = ival_0 <= 3 and ival_0 >= 2
        if not res:
            rep is None or rep.append(("constraints failed [.'$position']", path))
    return res

# check $coord_array (.'$coord_array')
def json_model_3(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$coord_array'
    # .'$coord_array'.'@'
    res = isinstance(val, list)
    if res:
        for arr_1_idx, arr_1_item in enumerate(val):
            arr_1_lpath: Path = (path + [ arr_1_idx ]) if path is not None else None
            # .'$coord_array'.'@'.0
            res = json_model_2(arr_1_item, arr_1_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $position [.'$coord_array'.'@'.0]", arr_1_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$coord_array'.'@']", path))
    if res:
        ival_1: int = len(val)
        res = ival_1 >= 2
        if not res:
            rep is None or rep.append(("constraints failed [.'$coord_array']", path))
    return res

# check $linear_ring (.'$linear_ring')
def json_model_4(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$linear_ring'
    # .'$linear_ring'.'@'
    res = isinstance(val, list)
    if res:
        for arr_2_idx, arr_2_item in enumerate(val):
            arr_2_lpath: Path = (path + [ arr_2_idx ]) if path is not None else None
            # .'$linear_ring'.'@'.0
            res = json_model_2(arr_2_item, arr_2_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $position [.'$linear_ring'.'@'.0]", arr_2_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$linear_ring'.'@']", path))
    if res:
        ival_2: int = len(val)
        res = ival_2 >= 4
        if not res:
            rep is None or rep.append(("constraints failed [.'$linear_ring']", path))
    return res

# object .'$Point'
def _jm_obj_0(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$Point']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$Point']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$Point'.type
    res = isinstance(pval, str) and pval == "Point"
    if not res:
        rep is None or rep.append(("unexpected Point [.'$Point'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$Point']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$Point']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$Point'.coordinates
    res = json_model_2(pval, path, rep)
    if not res:
        rep is None or rep.append(("unexpected $position [.'$Point'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$Point']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$Point'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_3_idx, arr_3_item in enumerate(pval):
                arr_3_lpath: Path = (path + [ arr_3_idx ]) if path is not None else None
                # .'$Point'.bbox.0
                res = isinstance(arr_3_item, (int, float)) and not isinstance(arr_3_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$Point'.bbox.0]", arr_3_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$Point'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$Point']", path))
            return False
    return True

# check $Point (.'$Point')
def json_model_5(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$Point'
    res = _jm_obj_0(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$Point']", path))
    return res

# object .'$MultiPoint'
def _jm_obj_1(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$MultiPoint']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$MultiPoint']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$MultiPoint'.type
    res = isinstance(pval, str) and pval == "MultiPoint"
    if not res:
        rep is None or rep.append(("unexpected MultiPoint [.'$MultiPoint'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$MultiPoint']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$MultiPoint']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$MultiPoint'.coordinates
    res = isinstance(pval, list)
    if res:
        for arr_4_idx, arr_4_item in enumerate(pval):
            arr_4_lpath: Path = (path + [ arr_4_idx ]) if path is not None else None
            # .'$MultiPoint'.coordinates.0
            res = json_model_2(arr_4_item, arr_4_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $position [.'$MultiPoint'.coordinates.0]", arr_4_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$MultiPoint'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$MultiPoint']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$MultiPoint'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_5_idx, arr_5_item in enumerate(pval):
                arr_5_lpath: Path = (path + [ arr_5_idx ]) if path is not None else None
                # .'$MultiPoint'.bbox.0
                res = isinstance(arr_5_item, (int, float)) and not isinstance(arr_5_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$MultiPoint'.bbox.0]", arr_5_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$MultiPoint'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$MultiPoint']", path))
            return False
    return True

# check $MultiPoint (.'$MultiPoint')
def json_model_6(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$MultiPoint'
    res = _jm_obj_1(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$MultiPoint']", path))
    return res

# object .'$LineString'
def _jm_obj_2(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$LineString']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$LineString']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$LineString'.type
    res = isinstance(pval, str) and pval == "LineString"
    if not res:
        rep is None or rep.append(("unexpected LineString [.'$LineString'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$LineString']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$LineString']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$LineString'.coordinates
    res = json_model_3(pval, path, rep)
    if not res:
        rep is None or rep.append(("unexpected $coord_array [.'$LineString'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$LineString']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$LineString'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_6_idx, arr_6_item in enumerate(pval):
                arr_6_lpath: Path = (path + [ arr_6_idx ]) if path is not None else None
                # .'$LineString'.bbox.0
                res = isinstance(arr_6_item, (int, float)) and not isinstance(arr_6_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$LineString'.bbox.0]", arr_6_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$LineString'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$LineString']", path))
            return False
    return True

# check $LineString (.'$LineString')
def json_model_7(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$LineString'
    res = _jm_obj_2(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$LineString']", path))
    return res

# object .'$MultiLineString'
def _jm_obj_3(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$MultiLineString']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$MultiLineString']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$MultiLineString'.type
    res = isinstance(pval, str) and pval == "MultiLineString"
    if not res:
        rep is None or rep.append(("unexpected MultiLineString [.'$MultiLineString'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$MultiLineString']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$MultiLineString']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$MultiLineString'.coordinates
    res = isinstance(pval, list)
    if res:
        for arr_7_idx, arr_7_item in enumerate(pval):
            arr_7_lpath: Path = (path + [ arr_7_idx ]) if path is not None else None
            # .'$MultiLineString'.coordinates.0
            res = json_model_3(arr_7_item, arr_7_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $coord_array [.'$MultiLineString'.coordinates.0]", arr_7_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$MultiLineString'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$MultiLineString']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$MultiLineString'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_8_idx, arr_8_item in enumerate(pval):
                arr_8_lpath: Path = (path + [ arr_8_idx ]) if path is not None else None
                # .'$MultiLineString'.bbox.0
                res = isinstance(arr_8_item, (int, float)) and not isinstance(arr_8_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$MultiLineString'.bbox.0]", arr_8_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$MultiLineString'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$MultiLineString']", path))
            return False
    return True

# check $MultiLineString (.'$MultiLineString')
def json_model_8(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$MultiLineString'
    res = _jm_obj_3(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$MultiLineString']", path))
    return res

# object .'$Polygon'
def _jm_obj_4(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$Polygon']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$Polygon']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$Polygon'.type
    res = isinstance(pval, str) and pval == "Polygon"
    if not res:
        rep is None or rep.append(("unexpected Polygon [.'$Polygon'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$Polygon']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$Polygon']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$Polygon'.coordinates
    res = isinstance(pval, list)
    if res:
        for arr_9_idx, arr_9_item in enumerate(pval):
            arr_9_lpath: Path = (path + [ arr_9_idx ]) if path is not None else None
            # .'$Polygon'.coordinates.0
            res = json_model_4(arr_9_item, arr_9_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $linear_ring [.'$Polygon'.coordinates.0]", arr_9_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$Polygon'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$Polygon']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$Polygon'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_10_idx, arr_10_item in enumerate(pval):
                arr_10_lpath: Path = (path + [ arr_10_idx ]) if path is not None else None
                # .'$Polygon'.bbox.0
                res = isinstance(arr_10_item, (int, float)) and not isinstance(arr_10_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$Polygon'.bbox.0]", arr_10_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$Polygon'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$Polygon']", path))
            return False
    return True

# check $Polygon (.'$Polygon')
def json_model_9(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$Polygon'
    res = _jm_obj_4(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$Polygon']", path))
    return res

# object .'$MultiPolygon'
def _jm_obj_5(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$MultiPolygon']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$MultiPolygon']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$MultiPolygon'.type
    res = isinstance(pval, str) and pval == "MultiPolygon"
    if not res:
        rep is None or rep.append(("unexpected MultiPolygon [.'$MultiPolygon'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$MultiPolygon']", path))
        return False
    if not ("coordinates" in val):
        rep is None or rep.append(("missing mandatory prop <coordinates> [.'$MultiPolygon']", path))
        return False
    pval = val.get("coordinates", UNDEFINED)
    # .'$MultiPolygon'.coordinates
    res = isinstance(pval, list)
    if res:
        for arr_11_idx, arr_11_item in enumerate(pval):
            arr_11_lpath: Path = (path + [ arr_11_idx ]) if path is not None else None
            # .'$MultiPolygon'.coordinates.0
            res = isinstance(arr_11_item, list)
            if res:
                for arr_12_idx, arr_12_item in enumerate(arr_11_item):
                    arr_12_lpath: Path = ((arr_11_lpath if path is not None else None) + [ arr_12_idx ]) if (arr_11_lpath if path is not None else None) is not None else None
                    # .'$MultiPolygon'.coordinates.0.0
                    res = json_model_4(arr_12_item, arr_12_lpath if (arr_11_lpath if path is not None else None) is not None else None, rep)
                    if not res:
                        rep is None or rep.append(("unexpected $linear_ring [.'$MultiPolygon'.coordinates.0.0]", arr_12_lpath if (arr_11_lpath if path is not None else None) is not None else None))
                    if not res:
                        break
            if not res:
                rep is None or rep.append(("not array or unexpected array [.'$MultiPolygon'.coordinates.0]", arr_11_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$MultiPolygon'.coordinates]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <coordinates> [.'$MultiPolygon']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$MultiPolygon'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_13_idx, arr_13_item in enumerate(pval):
                arr_13_lpath: Path = (path + [ arr_13_idx ]) if path is not None else None
                # .'$MultiPolygon'.bbox.0
                res = isinstance(arr_13_item, (int, float)) and not isinstance(arr_13_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$MultiPolygon'.bbox.0]", arr_13_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$MultiPolygon'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$MultiPolygon']", path))
            return False
    return True

# check $MultiPolygon (.'$MultiPolygon')
def json_model_10(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$MultiPolygon'
    res = _jm_obj_5(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$MultiPolygon']", path))
    return res


# check $geometry (.'$geometry')
def json_model_11(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$geometry'
    res = isinstance(val, dict)
    if res:
        tag_0: Jsonable = val.get("type", UNDEFINED)
        if tag_0 != UNDEFINED:
            fun_0: CheckFun = _jm_map_0.get(tag_0, UNDEFINED)
            if fun_0 != UNDEFINED:
                res = fun_0(val, path, rep)
            else:
                res = False
                rep is None or rep.append(("tag <type> value not found [.'$geometry'.'|']", path))
        else:
            res = False
            rep is None or rep.append(("tag prop <type> is missing [.'$geometry'.'|']", path))
    else:
        rep is None or rep.append(("value is not an object [.'$geometry'.'|']", path))
    return res

# object .'$GeometryCollection'
def _jm_obj_6(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$GeometryCollection']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$GeometryCollection']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$GeometryCollection'.type
    res = isinstance(pval, str) and pval == "GeometryCollection"
    if not res:
        rep is None or rep.append(("unexpected GeometryCollection [.'$GeometryCollection'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$GeometryCollection']", path))
        return False
    if not "geometries" in val:
        rep is None or rep.append(("missing mandatory prop <geometries> [.'$GeometryCollection']", path))
        return False
    pval = val.get("geometries", UNDEFINED)
    # .'$GeometryCollection'.geometries
    res = isinstance(pval, list)
    if res:
        for arr_14_idx, arr_14_item in enumerate(pval):
            arr_14_lpath: Path = (path + [ arr_14_idx ]) if path is not None else None
            # .'$GeometryCollection'.geometries.0
            res = json_model_11(arr_14_item, arr_14_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $geometry [.'$GeometryCollection'.geometries.0]", arr_14_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$GeometryCollection'.geometries]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <geometries> [.'$GeometryCollection']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$GeometryCollection'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_15_idx, arr_15_item in enumerate(pval):
                arr_15_lpath: Path = (path + [ arr_15_idx ]) if path is not None else None
                # .'$GeometryCollection'.bbox.0
                res = isinstance(arr_15_item, (int, float)) and not isinstance(arr_15_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$GeometryCollection'.bbox.0]", arr_15_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$GeometryCollection'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$GeometryCollection']", path))
            return False
    return True

# check $GeometryCollection (.'$GeometryCollection')
def json_model_12(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$GeometryCollection'
    res = _jm_obj_6(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$GeometryCollection']", path))
    return res

# object .'$Feature'.properties.'|'.1
def _jm_obj_8(val: Jsonable, path: Path, rep: Report) -> bool:
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$Feature'.properties.'|'.1]", path))
        return False
    # accept any object
    return True

# object .'$Feature'
def _jm_obj_7(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$Feature']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$Feature']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$Feature'.type
    res = isinstance(pval, str) and pval == "Feature"
    if not res:
        rep is None or rep.append(("unexpected Feature [.'$Feature'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$Feature']", path))
        return False
    if not "geometry" in val:
        rep is None or rep.append(("missing mandatory prop <geometry> [.'$Feature']", path))
        return False
    pval = val.get("geometry", UNDEFINED)
    # .'$Feature'.geometry
    # .'$Feature'.geometry.'|'.0
    res = pval is None
    if not res:
        rep is None or rep.append(("not null [.'$Feature'.geometry.'|'.0]", path))
    if not res:
        # .'$Feature'.geometry.'|'.1
        res = json_model_11(pval, path, rep)
        if not res:
            rep is None or rep.append(("unexpected $geometry [.'$Feature'.geometry.'|'.1]", path))
        if not res:
            # .'$Feature'.geometry.'|'.2
            res = json_model_12(pval, path, rep)
            if not res:
                rep is None or rep.append(("unexpected $GeometryCollection [.'$Feature'.geometry.'|'.2]", path))
    if res:
        rep is None or rep.clear()
    else:
        rep is None or rep.append(("no model matched [.'$Feature'.geometry.'|']", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <geometry> [.'$Feature']", path))
        return False
    if not "properties" in val:
        rep is None or rep.append(("missing mandatory prop <properties> [.'$Feature']", path))
        return False
    pval = val.get("properties", UNDEFINED)
    # .'$Feature'.properties
    # .'$Feature'.properties.'|'.0
    res = pval is None
    if not res:
        rep is None or rep.append(("not null [.'$Feature'.properties.'|'.0]", path))
    if not res:
        # .'$Feature'.properties.'|'.1
        res = _jm_obj_8(pval, path, rep)
        if not res:
            rep is None or rep.append(("unexpected element [.'$Feature'.properties.'|'.1]", path))
    if res:
        rep is None or rep.clear()
    else:
        rep is None or rep.append(("no model matched [.'$Feature'.properties.'|']", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <properties> [.'$Feature']", path))
        return False
    if "id" in val:
        pval = val.get("id", UNDEFINED)
        # .'$Feature'.id
        # .'$Feature'.id.'|'.0
        res = isinstance(pval, str)
        if not res:
            rep is None or rep.append(("unexpected string [.'$Feature'.id.'|'.0]", path))
        if not res:
            # .'$Feature'.id.'|'.1
            res = isinstance(pval, (int, float)) and not isinstance(pval, bool)
            if not res:
                rep is None or rep.append(("not a -1.0 loose float [.'$Feature'.id.'|'.1]", path))
        if res:
            rep is None or rep.clear()
        else:
            rep is None or rep.append(("no model matched [.'$Feature'.id.'|']", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <id> [.'$Feature']", path))
            return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$Feature'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_16_idx, arr_16_item in enumerate(pval):
                arr_16_lpath: Path = (path + [ arr_16_idx ]) if path is not None else None
                # .'$Feature'.bbox.0
                res = isinstance(arr_16_item, (int, float)) and not isinstance(arr_16_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$Feature'.bbox.0]", arr_16_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$Feature'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$Feature']", path))
            return False
    return True

# check $Feature (.'$Feature')
def json_model_13(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$Feature'
    res = _jm_obj_7(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$Feature']", path))
    return res

# object .'$FeatureCollection'
def _jm_obj_9(val: Jsonable, path: Path, rep: Report) -> bool:
    # check must only props
    if not isinstance(val, dict):
        rep is None or rep.append(("not an object [.'$FeatureCollection']", path))
        return False
    pval: Jsonable
    res: bool
    if not "type" in val:
        rep is None or rep.append(("missing mandatory prop <type> [.'$FeatureCollection']", path))
        return False
    pval = val.get("type", UNDEFINED)
    # .'$FeatureCollection'.type
    res = isinstance(pval, str) and pval == "FeatureCollection"
    if not res:
        rep is None or rep.append(("unexpected FeatureCollection [.'$FeatureCollection'.type]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <type> [.'$FeatureCollection']", path))
        return False
    if not "features" in val:
        rep is None or rep.append(("missing mandatory prop <features> [.'$FeatureCollection']", path))
        return False
    pval = val.get("features", UNDEFINED)
    # .'$FeatureCollection'.features
    res = isinstance(pval, list)
    if res:
        for arr_17_idx, arr_17_item in enumerate(pval):
            arr_17_lpath: Path = (path + [ arr_17_idx ]) if path is not None else None
            # .'$FeatureCollection'.features.0
            res = json_model_13(arr_17_item, arr_17_lpath if path is not None else None, rep)
            if not res:
                rep is None or rep.append(("unexpected $Feature [.'$FeatureCollection'.features.0]", arr_17_lpath if path is not None else None))
            if not res:
                break
    if not res:
        rep is None or rep.append(("not array or unexpected array [.'$FeatureCollection'.features]", path))
    if not res:
        rep is None or rep.append(("unexpected value for mandatory prop <features> [.'$FeatureCollection']", path))
        return False
    if "bbox" in val:
        pval = val.get("bbox", UNDEFINED)
        # .'$FeatureCollection'.bbox
        res = isinstance(pval, list)
        if res:
            for arr_18_idx, arr_18_item in enumerate(pval):
                arr_18_lpath: Path = (path + [ arr_18_idx ]) if path is not None else None
                # .'$FeatureCollection'.bbox.0
                res = isinstance(arr_18_item, (int, float)) and not isinstance(arr_18_item, bool)
                if not res:
                    rep is None or rep.append(("not a -1.0 loose float [.'$FeatureCollection'.bbox.0]", arr_18_lpath if path is not None else None))
                if not res:
                    break
        if not res:
            rep is None or rep.append(("not array or unexpected array [.'$FeatureCollection'.bbox]", path))
        if not res:
            rep is None or rep.append(("unexpected value for optional prop <bbox> [.'$FeatureCollection']", path))
            return False
    return True

# check $FeatureCollection (.'$FeatureCollection')
def json_model_14(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # .'$FeatureCollection'
    res = _jm_obj_9(val, path, rep)
    if not res:
        rep is None or rep.append(("unexpected element [.'$FeatureCollection']", path))
    return res

# check $ (.)
def json_model_1(val: Jsonable, path: Path, rep: Report) -> bool:
    res: bool
    # Easy Geo JSON Model JSON_MODEL_LOOSE_FLOAT
    # .
    # generic xor list
    xc_0: int = 0
    xr_0: bool
    # .'^'.0
    xr_0 = json_model_11(val, path, rep)
    if not xr_0:
        rep is None or rep.append(("unexpected $geometry [.'^'.0]", path))
    if xr_0:
        xc_0 += 1
    # .'^'.1
    xr_0 = json_model_12(val, path, rep)
    if not xr_0:
        rep is None or rep.append(("unexpected $GeometryCollection [.'^'.1]", path))
    if xr_0:
        xc_0 += 1
    if xc_0 <= 1:
        # .'^'.2
        xr_0 = json_model_13(val, path, rep)
        if not xr_0:
            rep is None or rep.append(("unexpected $Feature [.'^'.2]", path))
        if xr_0:
            xc_0 += 1
    if xc_0 <= 1:
        # .'^'.3
        xr_0 = json_model_14(val, path, rep)
        if not xr_0:
            rep is None or rep.append(("unexpected $FeatureCollection [.'^'.3]", path))
        if xr_0:
            xc_0 += 1
    res = xc_0 == 1
    if res:
        rep is None or rep.clear()
    else:
        rep is None or rep.append(("not one model match [.'^']", path))
    return res


# initialization guard
initialized: bool = False

# differed module initializations
def check_model_init():
    global initialized
    if not initialized:
        initialized = True
        global _jm_map_0
        _jm_map_0 = {
            "Point": json_model_5,
            "MultiPoint": json_model_6,
            "LineString": json_model_7,
            "MultiLineString": json_model_8,
            "Polygon": json_model_9,
            "MultiPolygon": json_model_10,
        }
        global check_model_map
        check_model_map = {
            "": json_model_1,
            "position": json_model_2,
            "coord_array": json_model_3,
            "linear_ring": json_model_4,
            "Point": json_model_5,
            "MultiPoint": json_model_6,
            "LineString": json_model_7,
            "MultiLineString": json_model_8,
            "Polygon": json_model_9,
            "MultiPolygon": json_model_10,
            "geometry": json_model_11,
            "GeometryCollection": json_model_12,
            "Feature": json_model_13,
            "FeatureCollection": json_model_14,
        }

# differed module cleanup
def check_model_free():
    global initialized
    if initialized:
        initialized = False

if __name__ == "__main__":
    check_model_init()
    main(check_model_fun, check_model_map, __version__)
    check_model_free()
