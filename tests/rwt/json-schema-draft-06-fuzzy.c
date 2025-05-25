#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_11(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_27(const json_t* val, Path* path, Report* rep);
static bool _jm_f_28(const json_t* val, Path* path, Report* rep);
static bool _jm_f_29(const json_t* val, Path* path, Report* rep);
static bool _jm_f_30(const json_t* val, Path* path, Report* rep);
static bool _jm_f_31(const json_t* val, Path* path, Report* rep);
static bool _jm_f_32(const json_t* val, Path* path, Report* rep);
static bool _jm_f_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_34(const json_t* val, Path* path, Report* rep);
static bool _jm_f_35(const json_t* val, Path* path, Report* rep);
static bool _jm_f_36(const json_t* val, Path* path, Report* rep);
static bool _jm_f_37(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[38];
static bool json_model_10(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[7];
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool json_model_9(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $schema ($.'$schema')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema'
    // $.'$schema'.'@'
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema'.'@']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema [$]", path);
    }
    return res;
}

// check $schema#Schema ($.'$schema#Schema')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#Schema'
    // $.'$schema#Schema'.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#Schema'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$schema#Schema'.'|'.1
        res = json_model_10(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [$.'$schema#Schema'.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#Schema'.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_$id ($.'$schema#ObjectSchema'.'$id')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$id'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [$.'$schema#ObjectSchema'.'$id']", path);
    }
    return res;
}

// check _jm_obj_0_may_$ref ($.'$schema#ObjectSchema'.'$ref')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$ref'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [$.'$schema#ObjectSchema'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_0_may_$schema ($.'$schema#ObjectSchema'.'$schema')
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$schema#ObjectSchema'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_0_may_additionalItems ($.'$schema#ObjectSchema'.additionalItems)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.additionalItems
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.additionalItems]", path);
    }
    return res;
}

// check _jm_obj_0_may_additionalProperties ($.'$schema#ObjectSchema'.additionalProperties)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.additionalProperties
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_0_may_allOf ($.'$schema#ObjectSchema'.allOf)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.allOf
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.allOf]", path);
    }
    return res;
}

// check _jm_obj_0_may_anyOf ($.'$schema#ObjectSchema'.anyOf)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.anyOf
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_0_may_const ($.'$schema#ObjectSchema'.const)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.const
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$schema#ObjectSchema'.const]", path);
    }
    return res;
}

// check _jm_obj_0_may_contains ($.'$schema#ObjectSchema'.contains)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.contains
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.contains]", path);
    }
    return res;
}

// check _jm_obj_0_may_default ($.'$schema#ObjectSchema'.default)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$schema#ObjectSchema'.default]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.definitions
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.definitions.''
        res = json_model_11(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.definitions.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_definitions ($.'$schema#ObjectSchema'.definitions)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.definitions
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.definitions]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.dependencies
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.dependencies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.dependencies.''
        // $.'$schema#ObjectSchema'.dependencies.''.'|'.0
        res = json_model_11(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.dependencies.''.'|'.0]", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            // $.'$schema#ObjectSchema'.dependencies.''.'|'.1
            res = json_model_9(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $stringArray [$.'$schema#ObjectSchema'.dependencies.''.'|'.1]", (path ? &lpath_2 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#ObjectSchema'.dependencies.''.'|']", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_dependencies ($.'$schema#ObjectSchema'.dependencies)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.dependencies
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.dependencies]", path);
    }
    return res;
}

// check _jm_obj_0_may_description ($.'$schema#ObjectSchema'.description)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.description]", path);
    }
    return res;
}

// check _jm_obj_0_may_enum ($.'$schema#ObjectSchema'.enum)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.enum
    // $.'$schema#ObjectSchema'.enum.'@'
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#ObjectSchema'.enum.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$schema#ObjectSchema'.enum]", path);
    }
    return res;
}

// check _jm_obj_0_may_examples ($.'$schema#ObjectSchema'.examples)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#ObjectSchema'.examples]", path);
    }
    return res;
}

// check _jm_obj_0_may_exclusiveMaximum ($.'$schema#ObjectSchema'.exclusiveMaximum)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.exclusiveMaximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$schema#ObjectSchema'.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_0_may_exclusiveMinimum ($.'$schema#ObjectSchema'.exclusiveMinimum)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.exclusiveMinimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$schema#ObjectSchema'.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_0_may_format ($.'$schema#ObjectSchema'.format)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.format]", path);
    }
    return res;
}

// check _jm_obj_0_may_items ($.'$schema#ObjectSchema'.items)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.items
    // $.'$schema#ObjectSchema'.items.'|'.0
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.items.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$schema#ObjectSchema'.items.'|'.1
        res = json_model_6(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.items.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#ObjectSchema'.items.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_maxItems ($.'$schema#ObjectSchema'.maxItems)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxItems
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_0_may_maxLength ($.'$schema#ObjectSchema'.maxLength)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxLength
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_0_may_maxProperties ($.'$schema#ObjectSchema'.maxProperties)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxProperties
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_0_may_maximum ($.'$schema#ObjectSchema'.maximum)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$schema#ObjectSchema'.maximum]", path);
    }
    return res;
}

// check _jm_obj_0_may_minItems ($.'$schema#ObjectSchema'.minItems)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minItems
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.minItems]", path);
    }
    return res;
}

// check _jm_obj_0_may_minLength ($.'$schema#ObjectSchema'.minLength)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minLength
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.minLength]", path);
    }
    return res;
}

// check _jm_obj_0_may_minProperties ($.'$schema#ObjectSchema'.minProperties)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minProperties
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#ObjectSchema'.minProperties]", path);
    }
    return res;
}

// check _jm_obj_0_may_minimum ($.'$schema#ObjectSchema'.minimum)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [$.'$schema#ObjectSchema'.minimum]", path);
    }
    return res;
}

// check _jm_obj_0_may_multipleOf ($.'$schema#ObjectSchema'.multipleOf)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.multipleOf
    res = json_is_number(val) && json_number_value(val) > 0.0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1.0 loose float [$.'$schema#ObjectSchema'.multipleOf]", path);
    }
    return res;
}

// check _jm_obj_0_may_not ($.'$schema#ObjectSchema'.not)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.not
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.not]", path);
    }
    return res;
}

// check _jm_obj_0_may_oneOf ($.'$schema#ObjectSchema'.oneOf)
static bool _jm_f_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.oneOf
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_0_may_pattern ($.'$schema#ObjectSchema'.pattern)
static bool _jm_f_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.pattern
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.pattern]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.patternProperties
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.patternProperties.''
        res = json_model_11(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.patternProperties.'']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_patternProperties ($.'$schema#ObjectSchema'.patternProperties)
static bool _jm_f_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.patternProperties
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.patternProperties]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.properties
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.properties.''
        res = json_model_11(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.properties.'']", (path ? &lpath_4 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_properties ($.'$schema#ObjectSchema'.properties)
static bool _jm_f_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.properties
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.properties]", path);
    }
    return res;
}

// check _jm_obj_0_may_propertyNames ($.'$schema#ObjectSchema'.propertyNames)
static bool _jm_f_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.propertyNames
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_0_may_required ($.'$schema#ObjectSchema'.required)
static bool _jm_f_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.required
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [$.'$schema#ObjectSchema'.required]", path);
    }
    return res;
}

// check _jm_obj_0_may_title ($.'$schema#ObjectSchema'.title)
static bool _jm_f_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.title]", path);
    }
    return res;
}

// check _jm_obj_0_may_type ($.'$schema#ObjectSchema'.type)
static bool _jm_f_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.type
    // $.'$schema#ObjectSchema'.type.'|'.0
    res = json_model_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [$.'$schema#ObjectSchema'.type.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$schema#ObjectSchema'.type.'|'.1
        res = json_model_8(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $typeArray [$.'$schema#ObjectSchema'.type.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#ObjectSchema'.type.'|']", path);
    }
    return res;
}

// check _jm_obj_0_may_uniqueItems ($.'$schema#ObjectSchema'.uniqueItems)
static bool _jm_f_37(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#ObjectSchema'.uniqueItems]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 38);
}

// object $.'$schema#ObjectSchema'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema']", path);
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
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$schema#ObjectSchema']", (path ? &lpath_0 : NULL));
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

// check $schema#ObjectSchema ($.'$schema#ObjectSchema')
static bool json_model_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema']", path);
    }
    return res;
}

// check $schema#URI-REFERENCE ($.'$schema#URI-REFERENCE')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#URI-REFERENCE'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#URI-REFERENCE']", path);
    }
    return res;
}

// check $schema#schemaArray ($.'$schema#schemaArray')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#schemaArray'
    // $.'$schema#schemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$schema#schemaArray'.'@'.0
            res = json_model_11(arr_0_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#schemaArray'.'@'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#schemaArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_1 = json_array_size(val);
        res = ival_1 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$schema#schemaArray']", path);
    }
    return res;
}


// check $schema#simpleTypes ($.'$schema#simpleTypes')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#simpleTypes'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$schema#simpleTypes'.'|']", path);
    }
    return res;
}

// check $schema#typeArray ($.'$schema#typeArray')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#typeArray'
    // $.'$schema#typeArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // $.'$schema#typeArray'.'@'.0
            res = json_model_7(arr_1_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [$.'$schema#typeArray'.'@'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#typeArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_2 = json_array_size(val);
        res = ival_2 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$schema#typeArray']", path);
    }
    return res;
}

// check $schema#stringArray ($.'$schema#stringArray')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#stringArray'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
            // $.'$schema#stringArray'.0
            res = json_is_string(arr_2_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#stringArray'.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#stringArray']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
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
        _jm_obj_0_may_tab[0] = (propmap_t) { "$id", _jm_f_0 };
        _jm_obj_0_may_tab[1] = (propmap_t) { "$ref", _jm_f_1 };
        _jm_obj_0_may_tab[2] = (propmap_t) { "$schema", _jm_f_2 };
        _jm_obj_0_may_tab[3] = (propmap_t) { "additionalItems", _jm_f_3 };
        _jm_obj_0_may_tab[4] = (propmap_t) { "additionalProperties", _jm_f_4 };
        _jm_obj_0_may_tab[5] = (propmap_t) { "allOf", _jm_f_5 };
        _jm_obj_0_may_tab[6] = (propmap_t) { "anyOf", _jm_f_6 };
        _jm_obj_0_may_tab[7] = (propmap_t) { "const", _jm_f_7 };
        _jm_obj_0_may_tab[8] = (propmap_t) { "contains", _jm_f_8 };
        _jm_obj_0_may_tab[9] = (propmap_t) { "default", _jm_f_9 };
        _jm_obj_0_may_tab[10] = (propmap_t) { "definitions", _jm_f_10 };
        _jm_obj_0_may_tab[11] = (propmap_t) { "dependencies", _jm_f_11 };
        _jm_obj_0_may_tab[12] = (propmap_t) { "description", _jm_f_12 };
        _jm_obj_0_may_tab[13] = (propmap_t) { "enum", _jm_f_13 };
        _jm_obj_0_may_tab[14] = (propmap_t) { "examples", _jm_f_14 };
        _jm_obj_0_may_tab[15] = (propmap_t) { "exclusiveMaximum", _jm_f_15 };
        _jm_obj_0_may_tab[16] = (propmap_t) { "exclusiveMinimum", _jm_f_16 };
        _jm_obj_0_may_tab[17] = (propmap_t) { "format", _jm_f_17 };
        _jm_obj_0_may_tab[18] = (propmap_t) { "items", _jm_f_18 };
        _jm_obj_0_may_tab[19] = (propmap_t) { "maxItems", _jm_f_19 };
        _jm_obj_0_may_tab[20] = (propmap_t) { "maxLength", _jm_f_20 };
        _jm_obj_0_may_tab[21] = (propmap_t) { "maxProperties", _jm_f_21 };
        _jm_obj_0_may_tab[22] = (propmap_t) { "maximum", _jm_f_22 };
        _jm_obj_0_may_tab[23] = (propmap_t) { "minItems", _jm_f_23 };
        _jm_obj_0_may_tab[24] = (propmap_t) { "minLength", _jm_f_24 };
        _jm_obj_0_may_tab[25] = (propmap_t) { "minProperties", _jm_f_25 };
        _jm_obj_0_may_tab[26] = (propmap_t) { "minimum", _jm_f_26 };
        _jm_obj_0_may_tab[27] = (propmap_t) { "multipleOf", _jm_f_27 };
        _jm_obj_0_may_tab[28] = (propmap_t) { "not", _jm_f_28 };
        _jm_obj_0_may_tab[29] = (propmap_t) { "oneOf", _jm_f_29 };
        _jm_obj_0_may_tab[30] = (propmap_t) { "pattern", _jm_f_30 };
        _jm_obj_0_may_tab[31] = (propmap_t) { "patternProperties", _jm_f_31 };
        _jm_obj_0_may_tab[32] = (propmap_t) { "properties", _jm_f_32 };
        _jm_obj_0_may_tab[33] = (propmap_t) { "propertyNames", _jm_f_33 };
        _jm_obj_0_may_tab[34] = (propmap_t) { "required", _jm_f_34 };
        _jm_obj_0_may_tab[35] = (propmap_t) { "title", _jm_f_35 };
        _jm_obj_0_may_tab[36] = (propmap_t) { "type", _jm_f_36 };
        _jm_obj_0_may_tab[37] = (propmap_t) { "uniqueItems", _jm_f_37 };
        jm_sort_propmap(_jm_obj_0_may_tab, 38);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "null" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "number" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "string" } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "array" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "object" } };
        jm_sort_cst(_jm_cst_0, 7);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "schema", json_model_3 };
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
