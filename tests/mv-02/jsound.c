#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_map_tab[4];
static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[14];
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_1[3];
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_map_tab[13];
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_map_tab[4];
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static bool _jm_f_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_25(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_map_tab[5];
static bool json_model_9(const json_t* val, Path* path, Report* rep);
static bool json_model_10(const json_t* val, Path* path, Report* rep);
static bool json_model_11(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[11];
const size_t check_model_map_size = 11;

// check _jm_obj_1_map_authors (.'$Schema'.metadata.authors)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Schema'.metadata.authors
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // .'$Schema'.metadata.authors.0
            res = json_is_string(arr_1_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.metadata.authors.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Schema'.metadata.authors]", path);
    }
    return res;
}

// check _jm_obj_1_map_date (.'$Schema'.metadata.date)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Schema'.metadata.date
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.metadata.date]", path);
    }
    return res;
}

// check _jm_obj_1_map_name (.'$Schema'.metadata.name)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Schema'.metadata.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.metadata.name]", path);
    }
    return res;
}

// check _jm_obj_1_map_previous (.'$Schema'.metadata.previous)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Schema'.metadata.previous
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.metadata.previous]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_map_tab, 4);
}

// object .'$Schema'.metadata
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.metadata]", path);
        return false;
    }
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_1_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_1 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Schema'.metadata]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Schema'.metadata]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    return true;
}

// object .'$Schema'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "types") == 0)
        {
            // handle must types property
            must_count += 1;
            // .'$Schema'.types
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_0_idx;
                json_t *arr_0_item;
                json_array_foreach(pval, arr_0_idx, arr_0_item)
                {
                    Path arr_0_lpath = (Path) { NULL, arr_0_idx, (path ? &lpath_0 : NULL), NULL };
                    // .'$Schema'.types.0
                    res = json_model_3(arr_0_item, ((path ? &lpath_0 : NULL) ? &arr_0_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Type [.'$Schema'.types.0]", ((path ? &lpath_0 : NULL) ? &arr_0_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Schema'.types]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Schema'.types]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "metadata") == 0)
        {
            // handle may metadata property
            // .'$Schema'.metadata
            res = _jm_obj_1(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Schema'.metadata]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Schema'.metadata]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Schema']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "types") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <types> [.'$Schema']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Schema (.'$Schema')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Schema'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Schema']", path);
    }
    return res;
}

// check $Type (.'$Type')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Type'
    // .'$Type'.'|'.0
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Atomic [.'$Type'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Type'.'|'.1
        res = json_model_7(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Object [.'$Type'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Type'.'|'.2
            res = json_model_9(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$Type'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$Type'.'|'.3
                res = json_model_10(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Union [.'$Type'.'|'.3]", path);
                }
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Type'.'|']", path);
    }
    return res;
}


// check $atomic-types (.'$atomic-types')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$atomic-types'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 14);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$atomic-types'.'|']", path);
    }
    return res;
}

// check $atomic (.'$atomic')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$atomic'
    // .'$atomic'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [.'$atomic'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$atomic'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$atomic'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$atomic'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$atomic'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$atomic'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$atomic'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$atomic'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$atomic'.'|'.4]", path);
                    }
                }
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$atomic'.'|']", path);
    }
    return res;
}

// check _jm_obj_2_map_enumeration (.'$Atomic'.enumeration)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.enumeration
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
            // .'$Atomic'.enumeration.0
            res = json_model_5(arr_2_item, (path ? &arr_2_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $atomic [.'$Atomic'.enumeration.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Atomic'.enumeration]", path);
    }
    return res;
}


// check _jm_obj_2_map_explicitTypeZone (.'$Atomic'.explicitTypeZone)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.explicitTypeZone
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 3);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$Atomic'.explicitTypeZone.'|']", path);
    }
    return res;
}

// check _jm_obj_2_map_fractionDigits (.'$Atomic'.fractionDigits)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.fractionDigits
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Atomic'.fractionDigits]", path);
    }
    return res;
}

// check _jm_obj_2_map_length (.'$Atomic'.length)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.length
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Atomic'.length]", path);
    }
    return res;
}

// check _jm_obj_2_map_maxExclusive (.'$Atomic'.maxExclusive)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.maxExclusive
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $atomic [.'$Atomic'.maxExclusive]", path);
    }
    return res;
}

// check _jm_obj_2_map_maxInclusive (.'$Atomic'.maxInclusive)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.maxInclusive
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $atomic [.'$Atomic'.maxInclusive]", path);
    }
    return res;
}

// check _jm_obj_2_map_maxLength (.'$Atomic'.maxLength)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Atomic'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_2_map_minExclusive (.'$Atomic'.minExclusive)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.minExclusive
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $atomic [.'$Atomic'.minExclusive]", path);
    }
    return res;
}

// check _jm_obj_2_map_minInclusive (.'$Atomic'.minInclusive)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.minInclusive
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $atomic [.'$Atomic'.minInclusive]", path);
    }
    return res;
}

// check _jm_obj_2_map_minLength (.'$Atomic'.minLength)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Atomic'.minLength]", path);
    }
    return res;
}

// check _jm_obj_2_map_name (.'$Atomic'.name)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Atomic'.name]", path);
    }
    return res;
}

// check _jm_obj_2_map_pattern (.'$Atomic'.pattern)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.pattern
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Atomic'.pattern]", path);
    }
    return res;
}

// check _jm_obj_2_map_totalDigits (.'$Atomic'.totalDigits)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'.totalDigits
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Atomic'.totalDigits]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_map_tab, 13);
}

// object .'$Atomic'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Atomic']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "kind") == 0)
        {
            // handle must kind property
            must_count += 1;
            // .'$Atomic'.kind
            res = json_is_string(pval) && strcmp(json_string_value(pval), "atomic") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected atomic [.'$Atomic'.kind]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Atomic'.kind]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "baseType") == 0)
        {
            // handle must baseType property
            must_count += 1;
            // .'$Atomic'.baseType
            res = json_model_4(pval, (path ? &lpath_2 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $atomic-types [.'$Atomic'.baseType]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Atomic'.baseType]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_2_map(prop)))
        {
            // handle 13 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Atomic']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Atomic']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "baseType") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <baseType> [.'$Atomic']", path);
            }
            if (! (json_object_get(val, "kind") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <kind> [.'$Atomic']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Atomic (.'$Atomic')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Atomic'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Atomic']", path);
    }
    return res;
}

// check _jm_obj_3_map_baseType (.'$Object'.baseType)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Object'.baseType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.baseType]", path);
    }
    return res;
}

// check _jm_obj_3_map_closed (.'$Object'.closed)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Object'.closed
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Object'.closed]", path);
    }
    return res;
}

// check _jm_obj_3_map_content (.'$Object'.content)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Object'.content
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
            // .'$Object'.content.0
            res = json_model_8(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Fields [.'$Object'.content.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Object'.content]", path);
    }
    return res;
}

// check _jm_obj_3_map_name (.'$Object'.name)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Object'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.name]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_map_tab, 4);
}

// object .'$Object'
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "kind") == 0)
        {
            // handle must kind property
            must_count += 1;
            // .'$Object'.kind
            res = json_is_string(pval) && strcmp(json_string_value(pval), "object") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected object [.'$Object'.kind]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Object'.kind]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_3_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_3 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Object']", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Object']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "kind") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <kind> [.'$Object']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Object (.'$Object')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Object'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Object']", path);
    }
    return res;
}

// object .'$Fields'
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Fields']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$Fields'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Fields'.name]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Fields'.name]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Fields'.type
            res = json_model_11(pval, (path ? &lpath_4 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $type-or-ref [.'$Fields'.type]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Fields'.type]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "required") == 0)
        {
            // handle may required property
            // .'$Fields'.required
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Fields'.required]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Fields'.required]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "default") == 0)
        {
            // handle may default property
            // .'$Fields'.default
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Fields'.default]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Fields'.default]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "unique") == 0)
        {
            // handle may unique property
            // .'$Fields'.unique
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Fields'.unique]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Fields'.unique]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Fields']", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$Fields']", path);
            }
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Fields']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Fields (.'$Fields')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Fields'
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Fields']", path);
    }
    return res;
}

// check _jm_obj_5_map_baseType (.'$Array'.baseType)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'.baseType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.baseType]", path);
    }
    return res;
}

// check _jm_obj_5_map_content (.'$Array'.content)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'.content
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $type-or-ref [.'$Array'.content]", path);
    }
    return res;
}

// check _jm_obj_5_map_maxLength (.'$Array'.maxLength)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_5_map_minLength (.'$Array'.minLength)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.minLength]", path);
    }
    return res;
}

// check _jm_obj_5_map_name (.'$Array'.name)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.name]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_map_tab, 5);
}

// object .'$Array'
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Array']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "kind") == 0)
        {
            // handle must kind property
            must_count += 1;
            // .'$Array'.kind
            res = json_is_string(pval) && strcmp(json_string_value(pval), "array") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected array [.'$Array'.kind]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Array'.kind]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_5_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_5 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Array']", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Array']", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "kind") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <kind> [.'$Array']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Array (.'$Array')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Array'
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Array']", path);
    }
    return res;
}

// object .'$Union'
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Union']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$Union'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Union'.name]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Union'.name]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "kind") == 0)
        {
            // handle must kind property
            must_count += 1;
            // .'$Union'.kind
            res = json_is_string(pval) && strcmp(json_string_value(pval), "union") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected union [.'$Union'.kind]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Union'.kind]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "content") == 0)
        {
            // handle must content property
            must_count += 1;
            // .'$Union'.content
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_4_idx;
                json_t *arr_4_item;
                json_array_foreach(pval, arr_4_idx, arr_4_item)
                {
                    Path arr_4_lpath = (Path) { NULL, arr_4_idx, (path ? &lpath_6 : NULL), NULL };
                    // .'$Union'.content.0
                    res = json_model_11(arr_4_item, ((path ? &lpath_6 : NULL) ? &arr_4_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $type-or-ref [.'$Union'.content.0]", ((path ? &lpath_6 : NULL) ? &arr_4_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Union'.content]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$Union'.content]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "baseType") == 0)
        {
            // handle may baseType property
            // .'$Union'.baseType
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Union'.baseType]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Union'.baseType]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Union']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "content") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <content> [.'$Union']", path);
            }
            if (! (json_object_get(val, "kind") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <kind> [.'$Union']", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$Union']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Union (.'$Union')
static bool json_model_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Union'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Union']", path);
    }
    return res;
}

// check $type-or-ref (.'$type-or-ref')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$type-or-ref'
    // .'$type-or-ref'.'|'.0
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$type-or-ref'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$type-or-ref'.'|'.1
        res = json_model_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Type [.'$type-or-ref'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$type-or-ref'.'|']", path);
    }
    return res;
}

// check $ ()
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    //
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema []", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 11);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_1_map_tab[0] = (propmap_t) { "authors", _jm_f_0 };
        _jm_obj_1_map_tab[1] = (propmap_t) { "date", _jm_f_1 };
        _jm_obj_1_map_tab[2] = (propmap_t) { "name", _jm_f_2 };
        _jm_obj_1_map_tab[3] = (propmap_t) { "previous", _jm_f_3 };
        jm_sort_propmap(_jm_obj_1_map_tab, 4);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "string" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "decimal" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "double" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "anyURI" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "base64Binary" } };
        _jm_cst_0[7] = (constant_t) { cst_is_string, { .s = "hexBinary" } };
        _jm_cst_0[8] = (constant_t) { cst_is_string, { .s = "date" } };
        _jm_cst_0[9] = (constant_t) { cst_is_string, { .s = "dateTime" } };
        _jm_cst_0[10] = (constant_t) { cst_is_string, { .s = "time" } };
        _jm_cst_0[11] = (constant_t) { cst_is_string, { .s = "dateTimeStamp" } };
        _jm_cst_0[12] = (constant_t) { cst_is_string, { .s = "duration" } };
        _jm_cst_0[13] = (constant_t) { cst_is_string, { .s = "null" } };
        jm_sort_cst(_jm_cst_0, 14);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (constant_t) { cst_is_string, { .s = "required" } };
        _jm_cst_1[1] = (constant_t) { cst_is_string, { .s = "prohibited" } };
        _jm_cst_1[2] = (constant_t) { cst_is_string, { .s = "optional" } };
        jm_sort_cst(_jm_cst_1, 3);
        _jm_obj_2_map_tab[0] = (propmap_t) { "enumeration", _jm_f_4 };
        _jm_obj_2_map_tab[1] = (propmap_t) { "explicitTypeZone", _jm_f_5 };
        _jm_obj_2_map_tab[2] = (propmap_t) { "fractionDigits", _jm_f_6 };
        _jm_obj_2_map_tab[3] = (propmap_t) { "length", _jm_f_7 };
        _jm_obj_2_map_tab[4] = (propmap_t) { "maxExclusive", _jm_f_8 };
        _jm_obj_2_map_tab[5] = (propmap_t) { "maxInclusive", _jm_f_9 };
        _jm_obj_2_map_tab[6] = (propmap_t) { "maxLength", _jm_f_10 };
        _jm_obj_2_map_tab[7] = (propmap_t) { "minExclusive", _jm_f_11 };
        _jm_obj_2_map_tab[8] = (propmap_t) { "minInclusive", _jm_f_12 };
        _jm_obj_2_map_tab[9] = (propmap_t) { "minLength", _jm_f_13 };
        _jm_obj_2_map_tab[10] = (propmap_t) { "name", _jm_f_14 };
        _jm_obj_2_map_tab[11] = (propmap_t) { "pattern", _jm_f_15 };
        _jm_obj_2_map_tab[12] = (propmap_t) { "totalDigits", _jm_f_16 };
        jm_sort_propmap(_jm_obj_2_map_tab, 13);
        _jm_obj_3_map_tab[0] = (propmap_t) { "baseType", _jm_f_17 };
        _jm_obj_3_map_tab[1] = (propmap_t) { "closed", _jm_f_18 };
        _jm_obj_3_map_tab[2] = (propmap_t) { "content", _jm_f_19 };
        _jm_obj_3_map_tab[3] = (propmap_t) { "name", _jm_f_20 };
        jm_sort_propmap(_jm_obj_3_map_tab, 4);
        _jm_obj_5_map_tab[0] = (propmap_t) { "baseType", _jm_f_21 };
        _jm_obj_5_map_tab[1] = (propmap_t) { "content", _jm_f_22 };
        _jm_obj_5_map_tab[2] = (propmap_t) { "maxLength", _jm_f_23 };
        _jm_obj_5_map_tab[3] = (propmap_t) { "minLength", _jm_f_24 };
        _jm_obj_5_map_tab[4] = (propmap_t) { "name", _jm_f_25 };
        jm_sort_propmap(_jm_obj_5_map_tab, 5);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "Schema", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "Type", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "atomic-types", json_model_4 };
        check_model_map_tab[4] = (propmap_t) { "atomic", json_model_5 };
        check_model_map_tab[5] = (propmap_t) { "Atomic", json_model_6 };
        check_model_map_tab[6] = (propmap_t) { "Object", json_model_7 };
        check_model_map_tab[7] = (propmap_t) { "Fields", json_model_8 };
        check_model_map_tab[8] = (propmap_t) { "Array", json_model_9 };
        check_model_map_tab[9] = (propmap_t) { "Union", json_model_10 };
        check_model_map_tab[10] = (propmap_t) { "type-or-ref", json_model_11 };
        jm_sort_propmap(check_model_map_tab, 11);
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
