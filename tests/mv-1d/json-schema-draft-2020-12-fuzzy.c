#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_19(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_38(const json_t* val, Path* path, Report* rep);
static bool _jm_f_39(const json_t* val, Path* path, Report* rep);
static bool _jm_f_40(const json_t* val, Path* path, Report* rep);
static bool _jm_f_41(const json_t* val, Path* path, Report* rep);
static bool _jm_f_42(const json_t* val, Path* path, Report* rep);
static bool _jm_f_43(const json_t* val, Path* path, Report* rep);
static bool _jm_f_44(const json_t* val, Path* path, Report* rep);
static bool _jm_f_45(const json_t* val, Path* path, Report* rep);
static bool _jm_f_46(const json_t* val, Path* path, Report* rep);
static bool _jm_f_47(const json_t* val, Path* path, Report* rep);
static bool _jm_f_48(const json_t* val, Path* path, Report* rep);
static bool _jm_f_49(const json_t* val, Path* path, Report* rep);
static bool _jm_f_50(const json_t* val, Path* path, Report* rep);
static bool _jm_f_51(const json_t* val, Path* path, Report* rep);
static bool _jm_f_52(const json_t* val, Path* path, Report* rep);
static bool _jm_f_53(const json_t* val, Path* path, Report* rep);
static bool _jm_f_54(const json_t* val, Path* path, Report* rep);
static bool _jm_f_55(const json_t* val, Path* path, Report* rep);
static bool _jm_f_56(const json_t* val, Path* path, Report* rep);
static bool _jm_f_57(const json_t* val, Path* path, Report* rep);
static bool _jm_f_58(const json_t* val, Path* path, Report* rep);
static bool _jm_f_59(const json_t* val, Path* path, Report* rep);
static bool _jm_f_60(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_map_tab[61];
static bool json_model_18(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[7];
static bool json_model_11(const json_t* val, Path* path, Report* rep);
static bool json_model_12(const json_t* val, Path* path, Report* rep);
static bool json_model_13(const json_t* val, Path* path, Report* rep);
static bool json_model_14(const json_t* val, Path* path, Report* rep);
static bool json_model_16(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $schema ($.'$schema')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema'
    // $.'$schema'.'@'
    res = json_model_19(val, path, rep);
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
static bool json_model_19(const json_t* val, Path* path, Report* rep)
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
        res = json_model_18(val, path, rep);
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

// check _jm_obj_0_map_$anchor ($.'$schema#ObjectSchema'.'$anchor')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$anchor'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [$.'$schema#ObjectSchema'.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_0_map_$comment ($.'$schema#ObjectSchema'.'$comment')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.'$comment']", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.'$defs'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.'$defs'.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.'$defs'.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_$defs ($.'$schema#ObjectSchema'.'$defs')
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$defs'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_0_map_$dynamicAnchor ($.'$schema#ObjectSchema'.'$dynamicAnchor')
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$dynamicAnchor'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [$.'$schema#ObjectSchema'.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_0_map_$dynamicRef ($.'$schema#ObjectSchema'.'$dynamicRef')
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$dynamicRef'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [$.'$schema#ObjectSchema'.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_0_map_$id ($.'$schema#ObjectSchema'.'$id')
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_$recursiveAnchor ($.'$schema#ObjectSchema'.'$recursiveAnchor')
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$recursiveAnchor'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.'$recursiveAnchor']", path);
    }
    return res;
}

// check _jm_obj_0_map_$recursiveRef ($.'$schema#ObjectSchema'.'$recursiveRef')
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$recursiveRef'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.'$recursiveRef']", path);
    }
    return res;
}

// check _jm_obj_0_map_$ref ($.'$schema#ObjectSchema'.'$ref')
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_$schema ($.'$schema#ObjectSchema'.'$schema')
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
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

// object $.'$schema#ObjectSchema'.'$vocabulary'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle {len(defs)} key props
            // $.'$schema#ObjectSchema'.'$vocabulary'.'$URL'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#ObjectSchema'.'$vocabulary'.'$URL']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$schema#ObjectSchema'.'$vocabulary']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_$vocabulary ($.'$schema#ObjectSchema'.'$vocabulary')
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.'$vocabulary'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_0_map_additionalProperties ($.'$schema#ObjectSchema'.additionalProperties)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.additionalProperties
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_allOf ($.'$schema#ObjectSchema'.allOf)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.allOf
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.allOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_anyOf ($.'$schema#ObjectSchema'.anyOf)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.anyOf
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_const ($.'$schema#ObjectSchema'.const)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_contains ($.'$schema#ObjectSchema'.contains)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.contains
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.contains]", path);
    }
    return res;
}

// check _jm_obj_0_map_contentEncoding ($.'$schema#ObjectSchema'.contentEncoding)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_0_map_contentMediaType ($.'$schema#ObjectSchema'.contentMediaType)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.contentMediaType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#ObjectSchema'.contentMediaType]", path);
    }
    return res;
}

// check _jm_obj_0_map_contentSchema ($.'$schema#ObjectSchema'.contentSchema)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.contentSchema
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.contentSchema]", path);
    }
    return res;
}

// check _jm_obj_0_map_default ($.'$schema#ObjectSchema'.default)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
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
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
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
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.definitions.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.definitions.'']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_definitions ($.'$schema#ObjectSchema'.definitions)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.definitions
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.definitions]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.dependencies
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
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
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.dependencies.''
        // $.'$schema#ObjectSchema'.dependencies.''.'|'.0
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.dependencies.''.'|'.0]", (path ? &lpath_4 : NULL));
        }
        if (! res)
        {
            // $.'$schema#ObjectSchema'.dependencies.''.'|'.1
            res = json_model_13(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $stringArray [$.'$schema#ObjectSchema'.dependencies.''.'|'.1]", (path ? &lpath_4 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#ObjectSchema'.dependencies.''.'|']", (path ? &lpath_4 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_dependencies ($.'$schema#ObjectSchema'.dependencies)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.dependencies
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.dependencies]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.dependentRequired
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.dependentRequired]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.dependentRequired.''
        res = json_model_13(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $stringArray [$.'$schema#ObjectSchema'.dependentRequired.'']", (path ? &lpath_5 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_dependentRequired ($.'$schema#ObjectSchema'.dependentRequired)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.dependentRequired
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.dependentRequired]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.dependentSchemas
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$schema#ObjectSchema'.dependentSchemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.dependentSchemas.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.dependentSchemas.'']", (path ? &lpath_6 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_dependentSchemas ($.'$schema#ObjectSchema'.dependentSchemas)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.dependentSchemas
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.dependentSchemas]", path);
    }
    return res;
}

// check _jm_obj_0_map_deprecated ($.'$schema#ObjectSchema'.deprecated)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#ObjectSchema'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_0_map_description ($.'$schema#ObjectSchema'.description)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_else ($.'$schema#ObjectSchema'.else)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.else
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.else]", path);
    }
    return res;
}

// check _jm_obj_0_map_enum ($.'$schema#ObjectSchema'.enum)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.enum
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#ObjectSchema'.enum]", path);
    }
    return res;
}

// check _jm_obj_0_map_examples ($.'$schema#ObjectSchema'.examples)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_exclusiveMaximum ($.'$schema#ObjectSchema'.exclusiveMaximum)
static bool _jm_f_29(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_exclusiveMinimum ($.'$schema#ObjectSchema'.exclusiveMinimum)
static bool _jm_f_30(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_format ($.'$schema#ObjectSchema'.format)
static bool _jm_f_31(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_if ($.'$schema#ObjectSchema'.if)
static bool _jm_f_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.if
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.if]", path);
    }
    return res;
}

// check _jm_obj_0_map_items ($.'$schema#ObjectSchema'.items)
static bool _jm_f_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.items
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.items]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxContains ($.'$schema#ObjectSchema'.maxContains)
static bool _jm_f_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxContains
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.maxContains]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxItems ($.'$schema#ObjectSchema'.maxItems)
static bool _jm_f_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxItems
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxLength ($.'$schema#ObjectSchema'.maxLength)
static bool _jm_f_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxLength
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_maxProperties ($.'$schema#ObjectSchema'.maxProperties)
static bool _jm_f_37(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.maxProperties
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_maximum ($.'$schema#ObjectSchema'.maximum)
static bool _jm_f_38(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_minContains ($.'$schema#ObjectSchema'.minContains)
static bool _jm_f_39(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minContains
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.minContains]", path);
    }
    return res;
}

// check _jm_obj_0_map_minItems ($.'$schema#ObjectSchema'.minItems)
static bool _jm_f_40(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minItems
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.minItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_minLength ($.'$schema#ObjectSchema'.minLength)
static bool _jm_f_41(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minLength
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.minLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_minProperties ($.'$schema#ObjectSchema'.minProperties)
static bool _jm_f_42(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.minProperties
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [$.'$schema#ObjectSchema'.minProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_minimum ($.'$schema#ObjectSchema'.minimum)
static bool _jm_f_43(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_multipleOf ($.'$schema#ObjectSchema'.multipleOf)
static bool _jm_f_44(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_not ($.'$schema#ObjectSchema'.not)
static bool _jm_f_45(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.not
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.not]", path);
    }
    return res;
}

// check _jm_obj_0_map_oneOf ($.'$schema#ObjectSchema'.oneOf)
static bool _jm_f_46(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.oneOf
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_0_map_pattern ($.'$schema#ObjectSchema'.pattern)
static bool _jm_f_47(const json_t* val, Path* path, Report* rep)
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
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
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
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.patternProperties.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.patternProperties.'']", (path ? &lpath_7 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_patternProperties ($.'$schema#ObjectSchema'.patternProperties)
static bool _jm_f_48(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.patternProperties
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.patternProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_prefixItems ($.'$schema#ObjectSchema'.prefixItems)
static bool _jm_f_49(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.prefixItems
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$schema#ObjectSchema'.prefixItems]", path);
    }
    return res;
}

// object $.'$schema#ObjectSchema'.properties
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
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
        Path lpath_8 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$schema#ObjectSchema'.properties.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.properties.'']", (path ? &lpath_8 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_properties ($.'$schema#ObjectSchema'.properties)
static bool _jm_f_50(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.properties
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$schema#ObjectSchema'.properties]", path);
    }
    return res;
}

// check _jm_obj_0_map_propertyNames ($.'$schema#ObjectSchema'.propertyNames)
static bool _jm_f_51(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.propertyNames
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_0_map_readOnly ($.'$schema#ObjectSchema'.readOnly)
static bool _jm_f_52(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#ObjectSchema'.readOnly]", path);
    }
    return res;
}

// check _jm_obj_0_map_required ($.'$schema#ObjectSchema'.required)
static bool _jm_f_53(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.required
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [$.'$schema#ObjectSchema'.required]", path);
    }
    return res;
}

// check _jm_obj_0_map_then ($.'$schema#ObjectSchema'.then)
static bool _jm_f_54(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.then
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.then]", path);
    }
    return res;
}

// check _jm_obj_0_map_title ($.'$schema#ObjectSchema'.title)
static bool _jm_f_55(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_type ($.'$schema#ObjectSchema'.type)
static bool _jm_f_56(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.type
    // $.'$schema#ObjectSchema'.type.'|'.0
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [$.'$schema#ObjectSchema'.type.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$schema#ObjectSchema'.type.'|'.1
        res = json_model_12(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $simpleTypesArray [$.'$schema#ObjectSchema'.type.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$schema#ObjectSchema'.type.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_unevaluatedItems ($.'$schema#ObjectSchema'.unevaluatedItems)
static bool _jm_f_57(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.unevaluatedItems
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.unevaluatedItems]", path);
    }
    return res;
}

// check _jm_obj_0_map_unevaluatedProperties ($.'$schema#ObjectSchema'.unevaluatedProperties)
static bool _jm_f_58(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.unevaluatedProperties
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#ObjectSchema'.unevaluatedProperties]", path);
    }
    return res;
}

// check _jm_obj_0_map_uniqueItems ($.'$schema#ObjectSchema'.uniqueItems)
static bool _jm_f_59(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_0_map_writeOnly ($.'$schema#ObjectSchema'.writeOnly)
static bool _jm_f_60(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#ObjectSchema'.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$schema#ObjectSchema'.writeOnly]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 61);
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
        if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 61 may props
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
static bool json_model_18(const json_t* val, Path* path, Report* rep)
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


// check $schema#simpleTypes ($.'$schema#simpleTypes')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
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

// check $schema#simpleTypesArray ($.'$schema#simpleTypesArray')
static bool json_model_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#simpleTypesArray'
    // $.'$schema#simpleTypesArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$schema#simpleTypesArray'.'@'.0
            res = json_model_11(arr_0_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [$.'$schema#simpleTypesArray'.'@'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#simpleTypesArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$schema#simpleTypesArray']", path);
    }
    return res;
}

// check $schema#stringArray ($.'$schema#stringArray')
static bool json_model_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#stringArray'
    // $.'$schema#stringArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // $.'$schema#stringArray'.'@'.0
            res = json_is_string(arr_1_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$schema#stringArray'.'@'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$schema#stringArray'.'@']", path);
    }
    if (res)
    {
        res = jm_array_is_unique(val, path, rep);
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed at [$.'$schema#stringArray']", path);
    }
    return res;
}

// check $schema#nonNegativeInteger ($.'$schema#nonNegativeInteger')
static bool json_model_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#nonNegativeInteger'
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val)))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$schema#nonNegativeInteger']", path);
    }
    return res;
}

// check $schema#schemaArray ($.'$schema#schemaArray')
static bool json_model_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$schema#schemaArray'
    // $.'$schema#schemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
            // $.'$schema#schemaArray'.'@'.0
            res = json_model_19(arr_2_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$schema#schemaArray'.'@'.0]", (path ? &arr_2_lpath : NULL));
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
        _jm_obj_0_map_tab[0] = (propmap_t) { "$anchor", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (propmap_t) { "$comment", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (propmap_t) { "$defs", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (propmap_t) { "$dynamicAnchor", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (propmap_t) { "$dynamicRef", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (propmap_t) { "$id", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (propmap_t) { "$recursiveAnchor", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (propmap_t) { "$recursiveRef", _jm_f_7 };
        _jm_obj_0_map_tab[8] = (propmap_t) { "$ref", _jm_f_8 };
        _jm_obj_0_map_tab[9] = (propmap_t) { "$schema", _jm_f_9 };
        _jm_obj_0_map_tab[10] = (propmap_t) { "$vocabulary", _jm_f_10 };
        _jm_obj_0_map_tab[11] = (propmap_t) { "additionalProperties", _jm_f_11 };
        _jm_obj_0_map_tab[12] = (propmap_t) { "allOf", _jm_f_12 };
        _jm_obj_0_map_tab[13] = (propmap_t) { "anyOf", _jm_f_13 };
        _jm_obj_0_map_tab[14] = (propmap_t) { "const", _jm_f_14 };
        _jm_obj_0_map_tab[15] = (propmap_t) { "contains", _jm_f_15 };
        _jm_obj_0_map_tab[16] = (propmap_t) { "contentEncoding", _jm_f_16 };
        _jm_obj_0_map_tab[17] = (propmap_t) { "contentMediaType", _jm_f_17 };
        _jm_obj_0_map_tab[18] = (propmap_t) { "contentSchema", _jm_f_18 };
        _jm_obj_0_map_tab[19] = (propmap_t) { "default", _jm_f_19 };
        _jm_obj_0_map_tab[20] = (propmap_t) { "definitions", _jm_f_20 };
        _jm_obj_0_map_tab[21] = (propmap_t) { "dependencies", _jm_f_21 };
        _jm_obj_0_map_tab[22] = (propmap_t) { "dependentRequired", _jm_f_22 };
        _jm_obj_0_map_tab[23] = (propmap_t) { "dependentSchemas", _jm_f_23 };
        _jm_obj_0_map_tab[24] = (propmap_t) { "deprecated", _jm_f_24 };
        _jm_obj_0_map_tab[25] = (propmap_t) { "description", _jm_f_25 };
        _jm_obj_0_map_tab[26] = (propmap_t) { "else", _jm_f_26 };
        _jm_obj_0_map_tab[27] = (propmap_t) { "enum", _jm_f_27 };
        _jm_obj_0_map_tab[28] = (propmap_t) { "examples", _jm_f_28 };
        _jm_obj_0_map_tab[29] = (propmap_t) { "exclusiveMaximum", _jm_f_29 };
        _jm_obj_0_map_tab[30] = (propmap_t) { "exclusiveMinimum", _jm_f_30 };
        _jm_obj_0_map_tab[31] = (propmap_t) { "format", _jm_f_31 };
        _jm_obj_0_map_tab[32] = (propmap_t) { "if", _jm_f_32 };
        _jm_obj_0_map_tab[33] = (propmap_t) { "items", _jm_f_33 };
        _jm_obj_0_map_tab[34] = (propmap_t) { "maxContains", _jm_f_34 };
        _jm_obj_0_map_tab[35] = (propmap_t) { "maxItems", _jm_f_35 };
        _jm_obj_0_map_tab[36] = (propmap_t) { "maxLength", _jm_f_36 };
        _jm_obj_0_map_tab[37] = (propmap_t) { "maxProperties", _jm_f_37 };
        _jm_obj_0_map_tab[38] = (propmap_t) { "maximum", _jm_f_38 };
        _jm_obj_0_map_tab[39] = (propmap_t) { "minContains", _jm_f_39 };
        _jm_obj_0_map_tab[40] = (propmap_t) { "minItems", _jm_f_40 };
        _jm_obj_0_map_tab[41] = (propmap_t) { "minLength", _jm_f_41 };
        _jm_obj_0_map_tab[42] = (propmap_t) { "minProperties", _jm_f_42 };
        _jm_obj_0_map_tab[43] = (propmap_t) { "minimum", _jm_f_43 };
        _jm_obj_0_map_tab[44] = (propmap_t) { "multipleOf", _jm_f_44 };
        _jm_obj_0_map_tab[45] = (propmap_t) { "not", _jm_f_45 };
        _jm_obj_0_map_tab[46] = (propmap_t) { "oneOf", _jm_f_46 };
        _jm_obj_0_map_tab[47] = (propmap_t) { "pattern", _jm_f_47 };
        _jm_obj_0_map_tab[48] = (propmap_t) { "patternProperties", _jm_f_48 };
        _jm_obj_0_map_tab[49] = (propmap_t) { "prefixItems", _jm_f_49 };
        _jm_obj_0_map_tab[50] = (propmap_t) { "properties", _jm_f_50 };
        _jm_obj_0_map_tab[51] = (propmap_t) { "propertyNames", _jm_f_51 };
        _jm_obj_0_map_tab[52] = (propmap_t) { "readOnly", _jm_f_52 };
        _jm_obj_0_map_tab[53] = (propmap_t) { "required", _jm_f_53 };
        _jm_obj_0_map_tab[54] = (propmap_t) { "then", _jm_f_54 };
        _jm_obj_0_map_tab[55] = (propmap_t) { "title", _jm_f_55 };
        _jm_obj_0_map_tab[56] = (propmap_t) { "type", _jm_f_56 };
        _jm_obj_0_map_tab[57] = (propmap_t) { "unevaluatedItems", _jm_f_57 };
        _jm_obj_0_map_tab[58] = (propmap_t) { "unevaluatedProperties", _jm_f_58 };
        _jm_obj_0_map_tab[59] = (propmap_t) { "uniqueItems", _jm_f_59 };
        _jm_obj_0_map_tab[60] = (propmap_t) { "writeOnly", _jm_f_60 };
        jm_sort_propmap(_jm_obj_0_map_tab, 61);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "array" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "null" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "number" } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "object" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "string" } };
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
