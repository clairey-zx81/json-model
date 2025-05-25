#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[8];
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
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
static constant_t _jm_cst_1[13];
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
static bool _jm_f_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_27(const json_t* val, Path* path, Report* rep);
static bool _jm_f_28(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[29];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

// check $URI ($.'$URI')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$URI'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$URI']", path);
    }
    return res;
}


// check $allTypes ($.'$allTypes')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
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

// check $distinctSchemaArray ($.'$distinctSchemaArray')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$distinctSchemaArray'
    // $.'$distinctSchemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$distinctSchemaArray'.'@'.0
            // $.'$distinctSchemaArray'.'@'.0.'|'.0
            res = json_is_string(arr_0_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$distinctSchemaArray'.'@'.0.'|'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                // $.'$distinctSchemaArray'.'@'.0.'|'.1
                res = json_model_1(arr_0_item, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$distinctSchemaArray'.'@'.0.'|'.1]", (path ? &arr_0_lpath : NULL));
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$distinctSchemaArray'.'@'.0.'|']", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$distinctSchemaArray'.'@']", path);
    }
    if (res)
    {
        res = jm_array_is_unique(val, path, rep);
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$distinctSchemaArray']", path);
    }
    return res;
}

// check _jm_obj_0_may_$ref ($.'$ref')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ref'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$ref']", path);
    }
    return res;
}

// check _jm_obj_0_may_$schema ($.'$schema')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_additionalItems ($.additionalItems)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.additionalItems
    // $.additionalItems.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.additionalItems.'|'.0]", path);
    }
    if (! res)
    {
        // $.additionalItems.'|'.1
        res = json_model_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.additionalItems.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.additionalItems.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_additionalProperties ($.additionalProperties)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
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
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.additionalProperties.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_default ($.default)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
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

// object $.dependencies
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.dependencies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.dependencies.''
        // $.dependencies.''.'|'.0
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [$.dependencies.''.'|'.0]", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            // $.dependencies.''.'|'.1
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_1_idx;
                json_t *arr_1_item;
                json_array_foreach(pval, arr_1_idx, arr_1_item)
                {
                    Path arr_1_lpath = (Path) { NULL, arr_1_idx, (path ? &lpath_1 : NULL), NULL };
                    // $.dependencies.''.'|'.1.0
                    res = json_is_string(arr_1_item);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [$.dependencies.''.'|'.1.0]", ((path ? &lpath_1 : NULL) ? &arr_1_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.dependencies.''.'|'.1]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                // $.dependencies.''.'|'.2
                res = json_model_1(pval, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.dependencies.''.'|'.2]", (path ? &lpath_1 : NULL));
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.dependencies.''.'|']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_dependencies ($.dependencies)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.dependencies
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.dependencies]", path);
    }
    return res;
}

// check _jm_obj_0_may_description ($.description)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_disallow ($.disallow)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
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
        res = json_model_4(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $distinctSchemaArray [$.disallow.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.disallow.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_divisibleBy ($.divisibleBy)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.divisibleBy
    res = json_is_number(val) && json_number_value(val) > 0.0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1.0 loose float [$.divisibleBy]", path);
    }
    return res;
}

// check _jm_obj_0_may_enum ($.enum)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
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
        res = jm_array_is_unique(val, path, rep) && ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.enum]", path);
    }
    return res;
}

// check _jm_obj_0_may_exclusiveMaximum ($.exclusiveMaximum)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.exclusiveMaximum
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_0_may_exclusiveMinimum ($.exclusiveMinimum)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.exclusiveMinimum
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_0_may_extends ($.extends)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
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
            size_t arr_2_idx;
            json_t *arr_2_item;
            json_array_foreach(val, arr_2_idx, arr_2_item)
            {
                Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
                // $.extends.'|'.1.0
                res = json_model_1(arr_2_item, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.extends.'|'.1.0]", (path ? &arr_2_lpath : NULL));
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
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.extends.'|']", path);
    }
    return res;
}


// check _jm_obj_0_may_format ($.format)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.format
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 13);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.format.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_id ($.id)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_items ($.items)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
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
            size_t arr_3_idx;
            json_t *arr_3_item;
            json_array_foreach(val, arr_3_idx, arr_3_item)
            {
                Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
                // $.items.'|'.1.0
                res = json_model_1(arr_3_item, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.items.'|'.1.0]", (path ? &arr_3_lpath : NULL));
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
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.items.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_maxItems ($.maxItems)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_maxLength ($.maxLength)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_maximum ($.maximum)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_minItems ($.minItems)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_minLength ($.minLength)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_minimum ($.minimum)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_pattern ($.pattern)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
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

// object $.patternProperties
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.patternProperties.''
        res = json_model_1(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.patternProperties.'']", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_patternProperties ($.patternProperties)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.patternProperties
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.patternProperties]", path);
    }
    return res;
}

// object $.properties
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
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
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.properties.''
        res = json_model_1(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.properties.'']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_properties ($.properties)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.properties
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.properties]", path);
    }
    return res;
}

// check _jm_obj_0_may_required ($.required)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.required]", path);
    }
    return res;
}

// check _jm_obj_0_may_title ($.title)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_may_type ($.type)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.type
    // $.type.'|'.0
    res = json_model_3(val, path, rep);
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
            size_t arr_4_idx;
            json_t *arr_4_item;
            json_array_foreach(val, arr_4_idx, arr_4_item)
            {
                Path arr_4_lpath = (Path) { NULL, arr_4_idx, path, NULL };
                // $.type.'|'.1.0
                // $.type.'|'.1.0.'|'.0
                res = json_is_string(arr_4_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [$.type.'|'.1.0.'|'.0]", (path ? &arr_4_lpath : NULL));
                }
                if (! res)
                {
                    // $.type.'|'.1.0.'|'.1
                    res = json_model_1(arr_4_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.type.'|'.1.0.'|'.1]", (path ? &arr_4_lpath : NULL));
                    }
                }
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "no model matched [$.type.'|'.1.0.'|']", (path ? &arr_4_lpath : NULL));
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
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.type.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_uniqueItems ($.uniqueItems)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.uniqueItems]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 29);
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
        if ((pfun = _jm_obj_0_may(prop)))
        {
            // handle {len(may)} may props
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
    return jm_search_propmap(pname, check_model_map_tab, 5);
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
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (constant_t) { cst_is_string, { .s = "date-time" } };
        _jm_cst_1[1] = (constant_t) { cst_is_string, { .s = "date" } };
        _jm_cst_1[2] = (constant_t) { cst_is_string, { .s = "time" } };
        _jm_cst_1[3] = (constant_t) { cst_is_string, { .s = "utc-millisec" } };
        _jm_cst_1[4] = (constant_t) { cst_is_string, { .s = "regex" } };
        _jm_cst_1[5] = (constant_t) { cst_is_string, { .s = "color" } };
        _jm_cst_1[6] = (constant_t) { cst_is_string, { .s = "style" } };
        _jm_cst_1[7] = (constant_t) { cst_is_string, { .s = "phone" } };
        _jm_cst_1[8] = (constant_t) { cst_is_string, { .s = "uri" } };
        _jm_cst_1[9] = (constant_t) { cst_is_string, { .s = "email" } };
        _jm_cst_1[10] = (constant_t) { cst_is_string, { .s = "ip-address" } };
        _jm_cst_1[11] = (constant_t) { cst_is_string, { .s = "ipv6" } };
        _jm_cst_1[12] = (constant_t) { cst_is_string, { .s = "host-name" } };
        jm_sort_cst(_jm_cst_1, 13);
        _jm_obj_0_may_tab[0] = (propmap_t) { "$ref", _jm_f_0 };
        _jm_obj_0_may_tab[1] = (propmap_t) { "$schema", _jm_f_1 };
        _jm_obj_0_may_tab[2] = (propmap_t) { "additionalItems", _jm_f_2 };
        _jm_obj_0_may_tab[3] = (propmap_t) { "additionalProperties", _jm_f_3 };
        _jm_obj_0_may_tab[4] = (propmap_t) { "default", _jm_f_4 };
        _jm_obj_0_may_tab[5] = (propmap_t) { "dependencies", _jm_f_5 };
        _jm_obj_0_may_tab[6] = (propmap_t) { "description", _jm_f_6 };
        _jm_obj_0_may_tab[7] = (propmap_t) { "disallow", _jm_f_7 };
        _jm_obj_0_may_tab[8] = (propmap_t) { "divisibleBy", _jm_f_8 };
        _jm_obj_0_may_tab[9] = (propmap_t) { "enum", _jm_f_9 };
        _jm_obj_0_may_tab[10] = (propmap_t) { "exclusiveMaximum", _jm_f_10 };
        _jm_obj_0_may_tab[11] = (propmap_t) { "exclusiveMinimum", _jm_f_11 };
        _jm_obj_0_may_tab[12] = (propmap_t) { "extends", _jm_f_12 };
        _jm_obj_0_may_tab[13] = (propmap_t) { "format", _jm_f_13 };
        _jm_obj_0_may_tab[14] = (propmap_t) { "id", _jm_f_14 };
        _jm_obj_0_may_tab[15] = (propmap_t) { "items", _jm_f_15 };
        _jm_obj_0_may_tab[16] = (propmap_t) { "maxItems", _jm_f_16 };
        _jm_obj_0_may_tab[17] = (propmap_t) { "maxLength", _jm_f_17 };
        _jm_obj_0_may_tab[18] = (propmap_t) { "maximum", _jm_f_18 };
        _jm_obj_0_may_tab[19] = (propmap_t) { "minItems", _jm_f_19 };
        _jm_obj_0_may_tab[20] = (propmap_t) { "minLength", _jm_f_20 };
        _jm_obj_0_may_tab[21] = (propmap_t) { "minimum", _jm_f_21 };
        _jm_obj_0_may_tab[22] = (propmap_t) { "pattern", _jm_f_22 };
        _jm_obj_0_may_tab[23] = (propmap_t) { "patternProperties", _jm_f_23 };
        _jm_obj_0_may_tab[24] = (propmap_t) { "properties", _jm_f_24 };
        _jm_obj_0_may_tab[25] = (propmap_t) { "required", _jm_f_25 };
        _jm_obj_0_may_tab[26] = (propmap_t) { "title", _jm_f_26 };
        _jm_obj_0_may_tab[27] = (propmap_t) { "type", _jm_f_27 };
        _jm_obj_0_may_tab[28] = (propmap_t) { "uniqueItems", _jm_f_28 };
        jm_sort_propmap(_jm_obj_0_may_tab, 29);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "URI", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "allTypes", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "distinctSchemaArray", json_model_4 };
        check_model_map_tab[4] = (propmap_t) { "Schema", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 5);
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
