#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[2];
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[1];
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[2];
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_may_tab[1];
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[2];
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_may_tab[1];
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_must_tab[2];
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_may_tab[1];
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_must_tab[2];
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_may_tab[1];
static bool json_model_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_must_tab[2];
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_may_tab[1];
static bool json_model_10(const json_t* val, Path* path, Report* rep);
static constmap_t _jm_map_0_tab[6];
static bool json_model_11(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_6_must_tab[2];
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_6_may_tab[1];
static bool json_model_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_7_must_tab[3];
static bool _jm_f_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_25(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_7_may_tab[2];
static bool json_model_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_27(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_9_must_tab[2];
static bool _jm_f_28(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_9_may_tab[1];
static bool json_model_14(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[14];
const size_t check_model_map_size = 14;

// check $position ($.'$position')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$position'
    // $.'$position'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$position'.'@'.0
            res = json_is_number(arr_0_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$position'.'@'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$position'.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = ival_0 <= 3 && ival_0 >= 2;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$position']", path);
    }
    return res;
}

// check $coord_array ($.'$coord_array')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$coord_array'
    // $.'$coord_array'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // $.'$coord_array'.'@'.0
            res = json_model_2(arr_1_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $position [$.'$coord_array'.'@'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$coord_array'.'@']", path);
    }
    if (res)
    {
        int64_t ival_1 = json_array_size(val);
        res = ival_1 >= 2;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$coord_array']", path);
    }
    return res;
}

// check $linear_ring ($.'$linear_ring')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$linear_ring'
    // $.'$linear_ring'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
            // $.'$linear_ring'.'@'.0
            res = json_model_2(arr_2_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $position [$.'$linear_ring'.'@'.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$linear_ring'.'@']", path);
    }
    if (res)
    {
        int64_t ival_2 = json_array_size(val);
        res = ival_2 >= 4;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$linear_ring']", path);
    }
    return res;
}

// check _jm_obj_0_must_coordinates ($.'$Point'.coordinates)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Point'.coordinates
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $position [$.'$Point'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_0_must_type ($.'$Point'.type)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Point'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "Point") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected Point [$.'$Point'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 2);
}

// check _jm_obj_0_may_bbox ($.'$Point'.bbox)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Point'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
            // $.'$Point'.bbox.0
            res = json_is_number(arr_3_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$Point'.bbox.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$Point'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 1);
}

// object $.'$Point'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Point']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Point']", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_0_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$Point']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Point']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Point']", path);
        return false;
    }
    return true;
}

// check $Point ($.'$Point')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Point'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Point']", path);
    }
    return res;
}

// check _jm_obj_1_must_coordinates ($.'$MultiPoint'.coordinates)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPoint'.coordinates
    res = json_is_array(val);
    if (res)
    {
        size_t arr_4_idx;
        json_t *arr_4_item;
        json_array_foreach(val, arr_4_idx, arr_4_item)
        {
            Path arr_4_lpath = (Path) { NULL, arr_4_idx, path, NULL };
            // $.'$MultiPoint'.coordinates.0
            res = json_model_2(arr_4_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $position [$.'$MultiPoint'.coordinates.0]", (path ? &arr_4_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiPoint'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_1_must_type ($.'$MultiPoint'.type)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPoint'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "MultiPoint") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected MultiPoint [$.'$MultiPoint'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 2);
}

// check _jm_obj_1_may_bbox ($.'$MultiPoint'.bbox)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPoint'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_5_idx;
        json_t *arr_5_item;
        json_array_foreach(val, arr_5_idx, arr_5_item)
        {
            Path arr_5_lpath = (Path) { NULL, arr_5_idx, path, NULL };
            // $.'$MultiPoint'.bbox.0
            res = json_is_number(arr_5_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$MultiPoint'.bbox.0]", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiPoint'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_may_tab, 1);
}

// object $.'$MultiPoint'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$MultiPoint']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_1_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_1 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$MultiPoint']", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_1_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_1 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$MultiPoint']", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$MultiPoint']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$MultiPoint']", path);
        return false;
    }
    return true;
}

// check $MultiPoint ($.'$MultiPoint')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPoint'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$MultiPoint']", path);
    }
    return res;
}

// check _jm_obj_2_must_coordinates ($.'$LineString'.coordinates)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$LineString'.coordinates
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $coord_array [$.'$LineString'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_2_must_type ($.'$LineString'.type)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$LineString'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "LineString") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected LineString [$.'$LineString'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 2);
}

// check _jm_obj_2_may_bbox ($.'$LineString'.bbox)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$LineString'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_6_idx;
        json_t *arr_6_item;
        json_array_foreach(val, arr_6_idx, arr_6_item)
        {
            Path arr_6_lpath = (Path) { NULL, arr_6_idx, path, NULL };
            // $.'$LineString'.bbox.0
            res = json_is_number(arr_6_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$LineString'.bbox.0]", (path ? &arr_6_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$LineString'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_may_tab, 1);
}

// object $.'$LineString'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$LineString']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_2_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$LineString']", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_2_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$LineString']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$LineString']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$LineString']", path);
        return false;
    }
    return true;
}

// check $LineString ($.'$LineString')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$LineString'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$LineString']", path);
    }
    return res;
}

// check _jm_obj_3_must_coordinates ($.'$MultiLineString'.coordinates)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiLineString'.coordinates
    res = json_is_array(val);
    if (res)
    {
        size_t arr_7_idx;
        json_t *arr_7_item;
        json_array_foreach(val, arr_7_idx, arr_7_item)
        {
            Path arr_7_lpath = (Path) { NULL, arr_7_idx, path, NULL };
            // $.'$MultiLineString'.coordinates.0
            res = json_model_3(arr_7_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $coord_array [$.'$MultiLineString'.coordinates.0]", (path ? &arr_7_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiLineString'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_3_must_type ($.'$MultiLineString'.type)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiLineString'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "MultiLineString") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected MultiLineString [$.'$MultiLineString'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_must_tab, 2);
}

// check _jm_obj_3_may_bbox ($.'$MultiLineString'.bbox)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiLineString'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_8_idx;
        json_t *arr_8_item;
        json_array_foreach(val, arr_8_idx, arr_8_item)
        {
            Path arr_8_lpath = (Path) { NULL, arr_8_idx, path, NULL };
            // $.'$MultiLineString'.bbox.0
            res = json_is_number(arr_8_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$MultiLineString'.bbox.0]", (path ? &arr_8_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiLineString'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_may_tab, 1);
}

// object $.'$MultiLineString'
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$MultiLineString']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_3_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_3 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$MultiLineString']", (path ? &lpath_3 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_3_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_3 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$MultiLineString']", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$MultiLineString']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$MultiLineString']", path);
        return false;
    }
    return true;
}

// check $MultiLineString ($.'$MultiLineString')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiLineString'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$MultiLineString']", path);
    }
    return res;
}

// check _jm_obj_4_must_coordinates ($.'$Polygon'.coordinates)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Polygon'.coordinates
    res = json_is_array(val);
    if (res)
    {
        size_t arr_9_idx;
        json_t *arr_9_item;
        json_array_foreach(val, arr_9_idx, arr_9_item)
        {
            Path arr_9_lpath = (Path) { NULL, arr_9_idx, path, NULL };
            // $.'$Polygon'.coordinates.0
            res = json_model_4(arr_9_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $linear_ring [$.'$Polygon'.coordinates.0]", (path ? &arr_9_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$Polygon'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_4_must_type ($.'$Polygon'.type)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Polygon'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "Polygon") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected Polygon [$.'$Polygon'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_must_tab, 2);
}

// check _jm_obj_4_may_bbox ($.'$Polygon'.bbox)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Polygon'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_10_idx;
        json_t *arr_10_item;
        json_array_foreach(val, arr_10_idx, arr_10_item)
        {
            Path arr_10_lpath = (Path) { NULL, arr_10_idx, path, NULL };
            // $.'$Polygon'.bbox.0
            res = json_is_number(arr_10_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$Polygon'.bbox.0]", (path ? &arr_10_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$Polygon'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_may_tab, 1);
}

// object $.'$Polygon'
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Polygon']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_4_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_4 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Polygon']", (path ? &lpath_4 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_4_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_4 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$Polygon']", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Polygon']", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Polygon']", path);
        return false;
    }
    return true;
}

// check $Polygon ($.'$Polygon')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Polygon'
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Polygon']", path);
    }
    return res;
}

// check _jm_obj_5_must_coordinates ($.'$MultiPolygon'.coordinates)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPolygon'.coordinates
    res = json_is_array(val);
    if (res)
    {
        size_t arr_11_idx;
        json_t *arr_11_item;
        json_array_foreach(val, arr_11_idx, arr_11_item)
        {
            Path arr_11_lpath = (Path) { NULL, arr_11_idx, path, NULL };
            // $.'$MultiPolygon'.coordinates.0
            res = json_is_array(arr_11_item);
            if (res)
            {
                size_t arr_12_idx;
                json_t *arr_12_item;
                json_array_foreach(arr_11_item, arr_12_idx, arr_12_item)
                {
                    Path arr_12_lpath = (Path) { NULL, arr_12_idx, (path ? &arr_11_lpath : NULL), NULL };
                    // $.'$MultiPolygon'.coordinates.0.0
                    res = json_model_4(arr_12_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $linear_ring [$.'$MultiPolygon'.coordinates.0.0]", ((path ? &arr_11_lpath : NULL) ? &arr_12_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiPolygon'.coordinates.0]", (path ? &arr_11_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiPolygon'.coordinates]", path);
    }
    return res;
}

// check _jm_obj_5_must_type ($.'$MultiPolygon'.type)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPolygon'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "MultiPolygon") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected MultiPolygon [$.'$MultiPolygon'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_must_tab, 2);
}

// check _jm_obj_5_may_bbox ($.'$MultiPolygon'.bbox)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPolygon'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_13_idx;
        json_t *arr_13_item;
        json_array_foreach(val, arr_13_idx, arr_13_item)
        {
            Path arr_13_lpath = (Path) { NULL, arr_13_idx, path, NULL };
            // $.'$MultiPolygon'.bbox.0
            res = json_is_number(arr_13_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$MultiPolygon'.bbox.0]", (path ? &arr_13_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$MultiPolygon'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_may_tab, 1);
}

// object $.'$MultiPolygon'
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$MultiPolygon']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_5_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_5 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$MultiPolygon']", (path ? &lpath_5 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_5_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_5 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$MultiPolygon']", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$MultiPolygon']", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$MultiPolygon']", path);
        return false;
    }
    return true;
}

// check $MultiPolygon ($.'$MultiPolygon')
static bool json_model_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$MultiPolygon'
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$MultiPolygon']", path);
    }
    return res;
}

static check_fun_t _jm_map_0(json_t *val)
{
    constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 6);
}

// check $geometry ($.'$geometry')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$geometry'
    res = json_is_object(val);
    if (res)
    {
        json_t * tag_0 = json_object_get(val, "type");
        if (tag_0 != NULL)
        {
            check_fun_t fun_0 = _jm_map_0(tag_0);
            if (fun_0 != NULL)
            {
                res = fun_0(val, path, rep);
            }
            else
            {
                res = false;
                if (rep) jm_report_add_entry(rep, "tag type value not found [$.'$geometry'.'|']", path);
            }
        }
        else
        {
            res = false;
            if (rep) jm_report_add_entry(rep, "tag prop type is missing [$.'$geometry'.'|']", path);
        }
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value is not an object [$.'$geometry'.'|']", path);
    }
    return res;
}

// check _jm_obj_6_must_geometries ($.'$GeometryCollection'.geometries)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$GeometryCollection'.geometries
    res = json_is_array(val);
    if (res)
    {
        size_t arr_14_idx;
        json_t *arr_14_item;
        json_array_foreach(val, arr_14_idx, arr_14_item)
        {
            Path arr_14_lpath = (Path) { NULL, arr_14_idx, path, NULL };
            // $.'$GeometryCollection'.geometries.0
            res = json_model_11(arr_14_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $geometry [$.'$GeometryCollection'.geometries.0]", (path ? &arr_14_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$GeometryCollection'.geometries]", path);
    }
    return res;
}

// check _jm_obj_6_must_type ($.'$GeometryCollection'.type)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$GeometryCollection'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "GeometryCollection") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected GeometryCollection [$.'$GeometryCollection'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_6_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_must_tab, 2);
}

// check _jm_obj_6_may_bbox ($.'$GeometryCollection'.bbox)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$GeometryCollection'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_15_idx;
        json_t *arr_15_item;
        json_array_foreach(val, arr_15_idx, arr_15_item)
        {
            Path arr_15_lpath = (Path) { NULL, arr_15_idx, path, NULL };
            // $.'$GeometryCollection'.bbox.0
            res = json_is_number(arr_15_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$GeometryCollection'.bbox.0]", (path ? &arr_15_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$GeometryCollection'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_6_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_may_tab, 1);
}

// object $.'$GeometryCollection'
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$GeometryCollection']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_6_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_6 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$GeometryCollection']", (path ? &lpath_6 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_6_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_6 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$GeometryCollection']", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$GeometryCollection']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$GeometryCollection']", path);
        return false;
    }
    return true;
}

// check $GeometryCollection ($.'$GeometryCollection')
static bool json_model_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$GeometryCollection'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$GeometryCollection']", path);
    }
    return res;
}

// check _jm_obj_7_must_geometry ($.'$Feature'.geometry)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'.geometry
    // $.'$Feature'.geometry.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [$.'$Feature'.geometry.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$Feature'.geometry.'|'.1
        res = json_model_11(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $geometry [$.'$Feature'.geometry.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$Feature'.geometry.'|'.2
            res = json_model_12(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $GeometryCollection [$.'$Feature'.geometry.'|'.2]", path);
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$Feature'.geometry.'|']", path);
    }
    return res;
}

// object $.'$Feature'.properties.'|'.1
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Feature'.properties.'|'.1]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_7_must_properties ($.'$Feature'.properties)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'.properties
    // $.'$Feature'.properties.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [$.'$Feature'.properties.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$Feature'.properties.'|'.1
        res = _jm_obj_8(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Feature'.properties.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$Feature'.properties.'|']", path);
    }
    return res;
}

// check _jm_obj_7_must_type ($.'$Feature'.type)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "Feature") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected Feature [$.'$Feature'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_7_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_7_must_tab, 3);
}

// check _jm_obj_7_may_bbox ($.'$Feature'.bbox)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_16_idx;
        json_t *arr_16_item;
        json_array_foreach(val, arr_16_idx, arr_16_item)
        {
            Path arr_16_lpath = (Path) { NULL, arr_16_idx, path, NULL };
            // $.'$Feature'.bbox.0
            res = json_is_number(arr_16_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$Feature'.bbox.0]", (path ? &arr_16_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$Feature'.bbox]", path);
    }
    return res;
}

// check _jm_obj_7_may_id ($.'$Feature'.id)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'.id
    // $.'$Feature'.id.'|'.0
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$Feature'.id.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$Feature'.id.'|'.1
        res = json_is_number(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$Feature'.id.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$Feature'.id.'|']", path);
    }
    return res;
}

static check_fun_t _jm_obj_7_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_7_may_tab, 2);
}

// object $.'$Feature'
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Feature']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_7_must(prop)))
        {
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_7 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Feature']", (path ? &lpath_7 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_7_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_7 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$Feature']", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Feature']", (path ? &lpath_7 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Feature']", path);
        return false;
    }
    return true;
}

// check $Feature ($.'$Feature')
static bool json_model_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Feature'
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Feature']", path);
    }
    return res;
}

// check _jm_obj_9_must_features ($.'$FeatureCollection'.features)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$FeatureCollection'.features
    res = json_is_array(val);
    if (res)
    {
        size_t arr_17_idx;
        json_t *arr_17_item;
        json_array_foreach(val, arr_17_idx, arr_17_item)
        {
            Path arr_17_lpath = (Path) { NULL, arr_17_idx, path, NULL };
            // $.'$FeatureCollection'.features.0
            res = json_model_13(arr_17_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Feature [$.'$FeatureCollection'.features.0]", (path ? &arr_17_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$FeatureCollection'.features]", path);
    }
    return res;
}

// check _jm_obj_9_must_type ($.'$FeatureCollection'.type)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$FeatureCollection'.type
    res = json_is_string(val) && strcmp(json_string_value(val), "FeatureCollection") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected FeatureCollection [$.'$FeatureCollection'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_9_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_must_tab, 2);
}

// check _jm_obj_9_may_bbox ($.'$FeatureCollection'.bbox)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$FeatureCollection'.bbox
    res = json_is_array(val);
    if (res)
    {
        size_t arr_18_idx;
        json_t *arr_18_item;
        json_array_foreach(val, arr_18_idx, arr_18_item)
        {
            Path arr_18_lpath = (Path) { NULL, arr_18_idx, path, NULL };
            // $.'$FeatureCollection'.bbox.0
            res = json_is_number(arr_18_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$FeatureCollection'.bbox.0]", (path ? &arr_18_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$FeatureCollection'.bbox]", path);
    }
    return res;
}

static check_fun_t _jm_obj_9_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_may_tab, 1);
}

// object $.'$FeatureCollection'
static bool _jm_obj_9(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$FeatureCollection']", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_8 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_9_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_8 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$FeatureCollection']", (path ? &lpath_8 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_9_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_8 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$FeatureCollection']", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$FeatureCollection']", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$FeatureCollection']", path);
        return false;
    }
    return true;
}

// check $FeatureCollection ($.'$FeatureCollection')
static bool json_model_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$FeatureCollection'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$FeatureCollection']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    // generic xor list
    int64_t xc_0 = 0;
    bool xr_0;
    // $.'^'.0
    xr_0 = json_model_11(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $geometry [$.'^'.0]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    // $.'^'.1
    xr_0 = json_model_12(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $GeometryCollection [$.'^'.1]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    if (xc_0 <= 1)
    {
        // $.'^'.2
        xr_0 = json_model_13(val, path, rep);
        if (! xr_0)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Feature [$.'^'.2]", path);
        }
        if (xr_0)
        {
            xc_0 += 1;
        }
    }
    if (xc_0 <= 1)
    {
        // $.'^'.3
        xr_0 = json_model_14(val, path, rep);
        if (! xr_0)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $FeatureCollection [$.'^'.3]", path);
        }
        if (xr_0)
        {
            xc_0 += 1;
        }
    }
    res = xc_0 == 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not one model match [$.'^']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 14);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_must_tab[0] = (propmap_t) { "coordinates", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "type", _jm_f_1 };
        jm_sort_propmap(_jm_obj_0_must_tab, 2);
        _jm_obj_0_may_tab[0] = (propmap_t) { "bbox", _jm_f_2 };
        jm_sort_propmap(_jm_obj_0_may_tab, 1);
        _jm_obj_1_must_tab[0] = (propmap_t) { "coordinates", _jm_f_3 };
        _jm_obj_1_must_tab[1] = (propmap_t) { "type", _jm_f_4 };
        jm_sort_propmap(_jm_obj_1_must_tab, 2);
        _jm_obj_1_may_tab[0] = (propmap_t) { "bbox", _jm_f_5 };
        jm_sort_propmap(_jm_obj_1_may_tab, 1);
        _jm_obj_2_must_tab[0] = (propmap_t) { "coordinates", _jm_f_6 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "type", _jm_f_7 };
        jm_sort_propmap(_jm_obj_2_must_tab, 2);
        _jm_obj_2_may_tab[0] = (propmap_t) { "bbox", _jm_f_8 };
        jm_sort_propmap(_jm_obj_2_may_tab, 1);
        _jm_obj_3_must_tab[0] = (propmap_t) { "coordinates", _jm_f_9 };
        _jm_obj_3_must_tab[1] = (propmap_t) { "type", _jm_f_10 };
        jm_sort_propmap(_jm_obj_3_must_tab, 2);
        _jm_obj_3_may_tab[0] = (propmap_t) { "bbox", _jm_f_11 };
        jm_sort_propmap(_jm_obj_3_may_tab, 1);
        _jm_obj_4_must_tab[0] = (propmap_t) { "coordinates", _jm_f_12 };
        _jm_obj_4_must_tab[1] = (propmap_t) { "type", _jm_f_13 };
        jm_sort_propmap(_jm_obj_4_must_tab, 2);
        _jm_obj_4_may_tab[0] = (propmap_t) { "bbox", _jm_f_14 };
        jm_sort_propmap(_jm_obj_4_may_tab, 1);
        _jm_obj_5_must_tab[0] = (propmap_t) { "coordinates", _jm_f_15 };
        _jm_obj_5_must_tab[1] = (propmap_t) { "type", _jm_f_16 };
        jm_sort_propmap(_jm_obj_5_must_tab, 2);
        _jm_obj_5_may_tab[0] = (propmap_t) { "bbox", _jm_f_17 };
        jm_sort_propmap(_jm_obj_5_may_tab, 1);
        _jm_map_0_tab[0] = (constmap_t) { (constant_t) { cst_is_string, { .s = "Point" } }, json_model_5 };
        _jm_map_0_tab[1] = (constmap_t) { (constant_t) { cst_is_string, { .s = "MultiPoint" } }, json_model_6 };
        _jm_map_0_tab[2] = (constmap_t) { (constant_t) { cst_is_string, { .s = "LineString" } }, json_model_7 };
        _jm_map_0_tab[3] = (constmap_t) { (constant_t) { cst_is_string, { .s = "MultiLineString" } }, json_model_8 };
        _jm_map_0_tab[4] = (constmap_t) { (constant_t) { cst_is_string, { .s = "Polygon" } }, json_model_9 };
        _jm_map_0_tab[5] = (constmap_t) { (constant_t) { cst_is_string, { .s = "MultiPolygon" } }, json_model_10 };
        jm_sort_constmap(_jm_map_0_tab, 6);
        _jm_obj_6_must_tab[0] = (propmap_t) { "geometries", _jm_f_18 };
        _jm_obj_6_must_tab[1] = (propmap_t) { "type", _jm_f_19 };
        jm_sort_propmap(_jm_obj_6_must_tab, 2);
        _jm_obj_6_may_tab[0] = (propmap_t) { "bbox", _jm_f_20 };
        jm_sort_propmap(_jm_obj_6_may_tab, 1);
        _jm_obj_7_must_tab[0] = (propmap_t) { "geometry", _jm_f_21 };
        _jm_obj_7_must_tab[1] = (propmap_t) { "properties", _jm_f_22 };
        _jm_obj_7_must_tab[2] = (propmap_t) { "type", _jm_f_23 };
        jm_sort_propmap(_jm_obj_7_must_tab, 3);
        _jm_obj_7_may_tab[0] = (propmap_t) { "bbox", _jm_f_24 };
        _jm_obj_7_may_tab[1] = (propmap_t) { "id", _jm_f_25 };
        jm_sort_propmap(_jm_obj_7_may_tab, 2);
        _jm_obj_9_must_tab[0] = (propmap_t) { "features", _jm_f_26 };
        _jm_obj_9_must_tab[1] = (propmap_t) { "type", _jm_f_27 };
        jm_sort_propmap(_jm_obj_9_must_tab, 2);
        _jm_obj_9_may_tab[0] = (propmap_t) { "bbox", _jm_f_28 };
        jm_sort_propmap(_jm_obj_9_may_tab, 1);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "position", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "coord_array", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "linear_ring", json_model_4 };
        check_model_map_tab[4] = (propmap_t) { "Point", json_model_5 };
        check_model_map_tab[5] = (propmap_t) { "MultiPoint", json_model_6 };
        check_model_map_tab[6] = (propmap_t) { "LineString", json_model_7 };
        check_model_map_tab[7] = (propmap_t) { "MultiLineString", json_model_8 };
        check_model_map_tab[8] = (propmap_t) { "Polygon", json_model_9 };
        check_model_map_tab[9] = (propmap_t) { "MultiPolygon", json_model_10 };
        check_model_map_tab[10] = (propmap_t) { "geometry", json_model_11 };
        check_model_map_tab[11] = (propmap_t) { "GeometryCollection", json_model_12 };
        check_model_map_tab[12] = (propmap_t) { "Feature", json_model_13 };
        check_model_map_tab[13] = (propmap_t) { "FeatureCollection", json_model_14 };
        jm_sort_propmap(check_model_map_tab, 14);
    }
    return NULL;
}

void CHECK_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
    }
}


/*
 * # API
 *
 * ```c
 * bool error;
 * char *message;
 *
 * bool valid = check(json_value, "model-name", &error, &message);
 *
 * if (message)
 *    free(message), message = NULL;
 * ```
 *
 * - `error` is set of there was an error during initialization or if the model does not exists.
 * - `message` is provided if a non NULL pointer is passed, and must be freed by the caller.
 */
bool
CHECK(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(CHECK_init, CHECK_fun, val, name, error, reasons);
}
