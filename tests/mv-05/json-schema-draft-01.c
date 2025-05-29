#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static constant_t _jm_cst_0[8];
static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static bool _jm_f_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_25(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_map_tab[26];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $allTypes ($.'$allTypes')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$allTypes'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 8);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$allTypes'.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_$schema ($.'$schema')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema']", path);
    }
    return res;
}

// check _jm_obj_0_map_additionalProperties ($.additionalProperties)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.additionalProperties
    // $.additionalProperties.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.additionalProperties.'|'.0]", path);
    }
    if (! res)
    {
        // $.additionalProperties.'|'.1
        res = json_model_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.additionalProperties.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.additionalProperties.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_contentEncoding ($.contentEncoding)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_0_map_default ($.default)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.default]", path);
    }
    return res;
}

// check _jm_obj_0_map_description ($.description)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.description]", path);
    }
    return res;
}

// check _jm_obj_0_map_disallow ($.disallow)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.disallow
    // $.disallow.'|'.0
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.disallow.'|'.0]", path);
    }
    if (! res)
    {
        // $.disallow.'|'.1
        res = json_is_array(val);
        if (res)
        {
            size_t arr_0_idx;
            json_t *arr_0_item;
            json_array_foreach(val, arr_0_idx, arr_0_item)
            {
                Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
                // $.disallow.'|'.1.0
                res = json_is_string(arr_0_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [$.disallow.'|'.1.0]", (path ? &arr_0_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.disallow.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.disallow.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_enum ($.enum)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.enum
    // $.enum.'@'
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.enum.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.enum]", path);
    }
    return res;
}

// check _jm_obj_0_map_extends ($.extends)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.extends
    // $.extends.'|'.0
    res = json_model_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.extends.'|'.0]", path);
    }
    if (! res)
    {
        // $.extends.'|'.1
        res = json_is_array(val);
        if (res)
        {
            size_t arr_1_idx;
            json_t *arr_1_item;
            json_array_foreach(val, arr_1_idx, arr_1_item)
            {
                Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
                // $.extends.'|'.1.0
                res = json_model_1(arr_1_item, (path ? &arr_1_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.extends.'|'.1.0]", (path ? &arr_1_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.extends.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.extends.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_format ($.format)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.format]", path);
    }
    return res;
}

// check _jm_obj_0_map_id ($.id)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.id]", path);
    }
    return res;
}

// check _jm_obj_0_map_items ($.items)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.items
    // $.items.'|'.0
    res = json_model_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.items.'|'.0]", path);
    }
    if (! res)
    {
        // $.items.'|'.1
        res = json_is_array(val);
        if (res)
        {
            size_t arr_2_idx;
            json_t *arr_2_item;
            json_array_foreach(val, arr_2_idx, arr_2_item)
            {
                Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
                // $.items.'|'.1.0
                res = json_model_1(arr_2_item, (path ? &arr_2_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.items.'|'.1.0]", (path ? &arr_2_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.items.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.items.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_maxDecimal ($.maxDecimal)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.maxDecimal
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.maxDecimal]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxItems ($.maxItems)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.maxItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxLength ($.maxLength)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.maxLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_maximum ($.maximum)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.maximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.maximum]", path);
    }
    return res;
}

// check _jm_obj_0_map_maximumCanEqual ($.maximumCanEqual)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.maximumCanEqual
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.maximumCanEqual]", path);
    }
    return res;
}

// check _jm_obj_0_map_minItems ($.minItems)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.minItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_minLength ($.minLength)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.minLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_minimum ($.minimum)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.minimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.minimum]", path);
    }
    return res;
}

// check _jm_obj_0_map_minimumCanEqual ($.minimumCanEqual)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.minimumCanEqual
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.minimumCanEqual]", path);
    }
    return res;
}

// check _jm_obj_0_map_optional ($.optional)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.optional
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.optional]", path);
    }
    return res;
}

// check _jm_obj_0_map_pattern ($.pattern)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.pattern
    res = jm_is_valid_regex(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [$.pattern]", path);
    }
    return res;
}

// object $.properties
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.properties.''
        res = json_model_1(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.properties.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_properties ($.properties)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.properties
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.properties]", path);
    }
    return res;
}

// check _jm_obj_0_map_requires ($.requires)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.requires
    // $.requires.'|'.0
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.requires.'|'.0]", path);
    }
    if (! res)
    {
        // $.requires.'|'.1
        res = json_model_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.requires.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.requires.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_title ($.title)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.title]", path);
    }
    return res;
}

// check _jm_obj_0_map_type ($.type)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.type
    // $.type.'|'.0
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $allTypes [$.type.'|'.0]", path);
    }
    if (! res)
    {
        // $.type.'|'.1
        res = json_is_array(val);
        if (res)
        {
            size_t arr_3_idx;
            json_t *arr_3_item;
            json_array_foreach(val, arr_3_idx, arr_3_item)
            {
                Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
                // $.type.'|'.1.0
                // $.type.'|'.1.0.'|'.0
                res = json_is_string(arr_3_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [$.type.'|'.1.0.'|'.0]", (path ? &arr_3_lpath : NULL));
                }
                if (! res)
                {
                    // $.type.'|'.1.0.'|'.1
                    res = json_model_1(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.type.'|'.1.0.'|'.1]", (path ? &arr_3_lpath : NULL));
                    }
                }
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "no model matched [$.type.'|'.1.0.'|']", (path ? &arr_3_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.type.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.type.'|']", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 26);
}

// object $
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$]", path);
        return false;
    }
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 26 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$]", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 3);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "null" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "number" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "string" } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "array" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "object" } };
        _jm_cst_0[7] = (constant_t) { cst_is_string, { .s = "any" } };
        jm_sort_cst(_jm_cst_0, 8);
        _jm_obj_0_map_tab[0] = (propmap_t) { "$schema", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (propmap_t) { "additionalProperties", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (propmap_t) { "contentEncoding", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (propmap_t) { "default", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (propmap_t) { "description", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (propmap_t) { "disallow", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (propmap_t) { "enum", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (propmap_t) { "extends", _jm_f_7 };
        _jm_obj_0_map_tab[8] = (propmap_t) { "format", _jm_f_8 };
        _jm_obj_0_map_tab[9] = (propmap_t) { "id", _jm_f_9 };
        _jm_obj_0_map_tab[10] = (propmap_t) { "items", _jm_f_10 };
        _jm_obj_0_map_tab[11] = (propmap_t) { "maxDecimal", _jm_f_11 };
        _jm_obj_0_map_tab[12] = (propmap_t) { "maxItems", _jm_f_12 };
        _jm_obj_0_map_tab[13] = (propmap_t) { "maxLength", _jm_f_13 };
        _jm_obj_0_map_tab[14] = (propmap_t) { "maximum", _jm_f_14 };
        _jm_obj_0_map_tab[15] = (propmap_t) { "maximumCanEqual", _jm_f_15 };
        _jm_obj_0_map_tab[16] = (propmap_t) { "minItems", _jm_f_16 };
        _jm_obj_0_map_tab[17] = (propmap_t) { "minLength", _jm_f_17 };
        _jm_obj_0_map_tab[18] = (propmap_t) { "minimum", _jm_f_18 };
        _jm_obj_0_map_tab[19] = (propmap_t) { "minimumCanEqual", _jm_f_19 };
        _jm_obj_0_map_tab[20] = (propmap_t) { "optional", _jm_f_20 };
        _jm_obj_0_map_tab[21] = (propmap_t) { "pattern", _jm_f_21 };
        _jm_obj_0_map_tab[22] = (propmap_t) { "properties", _jm_f_22 };
        _jm_obj_0_map_tab[23] = (propmap_t) { "requires", _jm_f_23 };
        _jm_obj_0_map_tab[24] = (propmap_t) { "title", _jm_f_24 };
        _jm_obj_0_map_tab[25] = (propmap_t) { "type", _jm_f_25 };
        jm_sort_propmap(_jm_obj_0_map_tab, 26);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "allTypes", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "Schema", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 3);
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
