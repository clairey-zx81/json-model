#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_0_map_tab[34];
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_0[7];
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check _jm_obj_0_map_$ref (.'$schema'.'$ref')
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.'$ref'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_0_map_$schema (.'$schema'.'$schema')
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_0_map_additionalItems (.'$schema'.additionalItems)
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.additionalItems
    // .'$schema'.additionalItems.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.additionalItems.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema'.additionalItems.'|'.1
        res = json_model_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.additionalItems.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.additionalItems.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_additionalProperties (.'$schema'.additionalProperties)
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.additionalProperties
    // .'$schema'.additionalProperties.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.additionalProperties.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema'.additionalProperties.'|'.1
        res = json_model_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.additionalProperties.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.additionalProperties.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_allOf (.'$schema'.allOf)
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.allOf
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.allOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_anyOf (.'$schema'.anyOf)
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.anyOf
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_default (.'$schema'.default)
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$schema'.default]", path);
    }
    return res;
}

// object .'$schema'.definitions
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.definitions.''
        res = json_model_3(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.definitions.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_definitions (.'$schema'.definitions)
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.definitions
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema'.definitions]", path);
    }
    return res;
}

// object .'$schema'.dependencies
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema'.dependencies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.dependencies.''
        // .'$schema'.dependencies.''.'|'.0
        res = json_model_3(pval, (path ? &lpath_2 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.dependencies.''.'|'.0]", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            // .'$schema'.dependencies.''.'|'.1
            res = json_model_7(pval, (path ? &lpath_2 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema'.dependencies.''.'|'.1]", (path ? &lpath_2 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.dependencies.''.'|']", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_dependencies (.'$schema'.dependencies)
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.dependencies
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema'.dependencies]", path);
    }
    return res;
}

// check _jm_obj_0_map_description (.'$schema'.description)
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.description]", path);
    }
    return res;
}

// check _jm_obj_0_map_enum (.'$schema'.enum)
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.enum
    // .'$schema'.enum.'@'
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema'.enum.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema'.enum]", path);
    }
    return res;
}

// check _jm_obj_0_map_exclusiveMaximum (.'$schema'.exclusiveMaximum)
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.exclusiveMaximum
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_0_map_exclusiveMinimum (.'$schema'.exclusiveMinimum)
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.exclusiveMinimum
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_0_map_format (.'$schema'.format)
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.format]", path);
    }
    return res;
}

// check _jm_obj_0_map_id (.'$schema'.id)
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.id]", path);
    }
    return res;
}

// check _jm_obj_0_map_items (.'$schema'.items)
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.items
    // .'$schema'.items.'|'.0
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.items.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema'.items.'|'.1
        res = json_model_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.items.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.items.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_maxItems (.'$schema'.maxItems)
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxLength (.'$schema'.maxLength)
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxProperties (.'$schema'.maxProperties)
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.maxProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_maximum (.'$schema'.maximum)
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.maximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema'.maximum]", path);
    }
    return res;
}

// check _jm_obj_0_map_minItems (.'$schema'.minItems)
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_minLength (.'$schema'.minLength)
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_minProperties (.'$schema'.minProperties)
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.minProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_minimum (.'$schema'.minimum)
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.minimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema'.minimum]", path);
    }
    return res;
}

// check _jm_obj_0_map_multipleOf (.'$schema'.multipleOf)
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.multipleOf
    res = json_is_number(val) && json_number_value(val) > 0.0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1.0 loose float [.'$schema'.multipleOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_not (.'$schema'.not)
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.not
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.not]", path);
    }
    return res;
}

// check _jm_obj_0_map_oneOf (.'$schema'.oneOf)
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.oneOf
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_pattern (.'$schema'.pattern)
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.pattern
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.pattern]", path);
    }
    return res;
}

// object .'$schema'.patternProperties
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.patternProperties.''
        res = json_model_3(pval, (path ? &lpath_3 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.patternProperties.'']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_patternProperties (.'$schema'.patternProperties)
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.patternProperties
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema'.patternProperties]", path);
    }
    return res;
}

// object .'$schema'.properties
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.properties.''
        res = json_model_3(pval, (path ? &lpath_4 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.properties.'']", (path ? &lpath_4 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_properties (.'$schema'.properties)
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.properties
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema'.properties]", path);
    }
    return res;
}

// check _jm_obj_0_map_required (.'$schema'.required)
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.required
    res = json_model_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema'.required]", path);
    }
    return res;
}

// check _jm_obj_0_map_title (.'$schema'.title)
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.title]", path);
    }
    return res;
}

// check _jm_obj_0_map_type (.'$schema'.type)
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.type
    // .'$schema'.type.'|'.0
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [.'$schema'.type.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema'.type.'|'.1
        res = json_model_8(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $typeArray [.'$schema'.type.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.type.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_uniqueItems (.'$schema'.uniqueItems)
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.uniqueItems]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 34);
}

// object .'$schema'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 34 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$schema']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            // accept any other props
        }
    }
    return true;
}

// check $schema (.'$schema')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema [.]", path);
    }
    return res;
}

// check $schema#schemaArray (.'$schema#schemaArray')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#schemaArray'
    // .'$schema#schemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
            // .'$schema#schemaArray'.'@'.0
            res = json_model_3(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#schemaArray'.'@'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#schemaArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_1 = json_array_size(val);
        res = ival_1 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#schemaArray']", path);
    }
    return res;
}


// check $schema#simpleTypes (.'$schema#simpleTypes')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#simpleTypes'
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$schema#simpleTypes'.'|']", path);
    }
    return res;
}

// check $schema#stringArray (.'$schema#stringArray')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#stringArray'
    // .'$schema#stringArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, path, NULL };
            // .'$schema#stringArray'.'@'.0
            res = json_is_string(arr_1_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#stringArray'.'@'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#stringArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_2 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_2 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#stringArray']", path);
    }
    return res;
}

// check $schema#typeArray (.'$schema#typeArray')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#typeArray'
    // .'$schema#typeArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            jm_path_t arr_2_lpath = (jm_path_t) { NULL, arr_2_idx, path, NULL };
            // .'$schema#typeArray'.'@'.0
            res = json_model_6(arr_2_item, (path ? &arr_2_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [.'$schema#typeArray'.'@'.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#typeArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_3 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_3 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#typeArray']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 2);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_map_tab[0] = (jm_propmap_t) { "$ref", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (jm_propmap_t) { "$schema", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (jm_propmap_t) { "additionalItems", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (jm_propmap_t) { "additionalProperties", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (jm_propmap_t) { "allOf", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (jm_propmap_t) { "anyOf", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (jm_propmap_t) { "default", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (jm_propmap_t) { "definitions", _jm_f_7 };
        _jm_obj_0_map_tab[8] = (jm_propmap_t) { "dependencies", _jm_f_8 };
        _jm_obj_0_map_tab[9] = (jm_propmap_t) { "description", _jm_f_9 };
        _jm_obj_0_map_tab[10] = (jm_propmap_t) { "enum", _jm_f_10 };
        _jm_obj_0_map_tab[11] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_11 };
        _jm_obj_0_map_tab[12] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_12 };
        _jm_obj_0_map_tab[13] = (jm_propmap_t) { "format", _jm_f_13 };
        _jm_obj_0_map_tab[14] = (jm_propmap_t) { "id", _jm_f_14 };
        _jm_obj_0_map_tab[15] = (jm_propmap_t) { "items", _jm_f_15 };
        _jm_obj_0_map_tab[16] = (jm_propmap_t) { "maxItems", _jm_f_16 };
        _jm_obj_0_map_tab[17] = (jm_propmap_t) { "maxLength", _jm_f_17 };
        _jm_obj_0_map_tab[18] = (jm_propmap_t) { "maxProperties", _jm_f_18 };
        _jm_obj_0_map_tab[19] = (jm_propmap_t) { "maximum", _jm_f_19 };
        _jm_obj_0_map_tab[20] = (jm_propmap_t) { "minItems", _jm_f_20 };
        _jm_obj_0_map_tab[21] = (jm_propmap_t) { "minLength", _jm_f_21 };
        _jm_obj_0_map_tab[22] = (jm_propmap_t) { "minProperties", _jm_f_22 };
        _jm_obj_0_map_tab[23] = (jm_propmap_t) { "minimum", _jm_f_23 };
        _jm_obj_0_map_tab[24] = (jm_propmap_t) { "multipleOf", _jm_f_24 };
        _jm_obj_0_map_tab[25] = (jm_propmap_t) { "not", _jm_f_25 };
        _jm_obj_0_map_tab[26] = (jm_propmap_t) { "oneOf", _jm_f_26 };
        _jm_obj_0_map_tab[27] = (jm_propmap_t) { "pattern", _jm_f_27 };
        _jm_obj_0_map_tab[28] = (jm_propmap_t) { "patternProperties", _jm_f_28 };
        _jm_obj_0_map_tab[29] = (jm_propmap_t) { "properties", _jm_f_29 };
        _jm_obj_0_map_tab[30] = (jm_propmap_t) { "required", _jm_f_30 };
        _jm_obj_0_map_tab[31] = (jm_propmap_t) { "title", _jm_f_31 };
        _jm_obj_0_map_tab[32] = (jm_propmap_t) { "type", _jm_f_32 };
        _jm_obj_0_map_tab[33] = (jm_propmap_t) { "uniqueItems", _jm_f_33 };
        jm_sort_propmap(_jm_obj_0_map_tab, 34);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (jm_constant_t) { cst_is_string, { .s = "null" } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_0[3] = (jm_constant_t) { cst_is_string, { .s = "number" } };
        _jm_cst_0[4] = (jm_constant_t) { cst_is_string, { .s = "string" } };
        _jm_cst_0[5] = (jm_constant_t) { cst_is_string, { .s = "array" } };
        _jm_cst_0[6] = (jm_constant_t) { cst_is_string, { .s = "object" } };
        jm_sort_cst(_jm_cst_0, 7);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "schema", json_model_3 };
        jm_sort_propmap(check_model_map_tab, 2);
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
