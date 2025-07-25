//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_0[7];
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

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
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.definitions.''
        res = json_model_3(pval, (path ? &lpath_0 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.definitions.'']", (path ? &lpath_0 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$schema'.properties
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.properties.''
        res = json_model_3(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.properties.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
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
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.patternProperties.''
        res = json_model_3(pval, (path ? &lpath_2 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.patternProperties.'']", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$schema'.dependencies
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema'.dependencies.''
        // .'$schema'.dependencies.''.'|'.0
        res = json_model_3(pval, (path ? &lpath_3 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.dependencies.''.'|'.0]", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            // .'$schema'.dependencies.''.'|'.1
            res = json_model_6(pval, (path ? &lpath_3 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema'.dependencies.''.'|'.1]", (path ? &lpath_3 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$schema'.dependencies.''.'|']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$schema'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    // check must only props
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema']", path);
        return false;
    }
    json_t * pval;
    bool res;
    if (json_object_get(val, "id") != NULL)
    {
        pval = json_object_get(val, "id");
        // .'$schema'.id
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.id]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <id> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "$schema") != NULL)
    {
        pval = json_object_get(val, "$schema");
        // .'$schema'.'$schema'
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.'$schema']", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <$schema> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "title") != NULL)
    {
        pval = json_object_get(val, "title");
        // .'$schema'.title
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.title]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <title> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "description") != NULL)
    {
        pval = json_object_get(val, "description");
        // .'$schema'.description
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.description]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <description> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "multipleOf") != NULL)
    {
        pval = json_object_get(val, "multipleOf");
        // .'$schema'.multipleOf
        res = json_is_number(pval) && json_number_value(pval) > 0.0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 1.0 loose float [.'$schema'.multipleOf]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <multipleOf> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "maximum") != NULL)
    {
        pval = json_object_get(val, "maximum");
        // .'$schema'.maximum
        res = json_is_number(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema'.maximum]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <maximum> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "exclusiveMaximum") != NULL)
    {
        pval = json_object_get(val, "exclusiveMaximum");
        // .'$schema'.exclusiveMaximum
        res = json_is_boolean(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.exclusiveMaximum]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <exclusiveMaximum> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "minimum") != NULL)
    {
        pval = json_object_get(val, "minimum");
        // .'$schema'.minimum
        res = json_is_number(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema'.minimum]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <minimum> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "exclusiveMinimum") != NULL)
    {
        pval = json_object_get(val, "exclusiveMinimum");
        // .'$schema'.exclusiveMinimum
        res = json_is_boolean(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.exclusiveMinimum]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <exclusiveMinimum> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "maxLength") != NULL)
    {
        pval = json_object_get(val, "maxLength");
        // .'$schema'.maxLength
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxLength]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <maxLength> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "minLength") != NULL)
    {
        pval = json_object_get(val, "minLength");
        // .'$schema'.minLength
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minLength]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <minLength> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "additionalItems") != NULL)
    {
        pval = json_object_get(val, "additionalItems");
        // .'$schema'.additionalItems
        // .'$schema'.additionalItems.'|'.0
        res = json_is_boolean(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.additionalItems.'|'.0]", path);
        }
        if (! res)
        {
            // .'$schema'.additionalItems.'|'.1
            res = json_model_3(pval, path, rep);
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <additionalItems> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "items") != NULL)
    {
        pval = json_object_get(val, "items");
        // .'$schema'.items
        // .'$schema'.items.'|'.0
        res = json_model_3(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.items.'|'.0]", path);
        }
        if (! res)
        {
            // .'$schema'.items.'|'.1
            res = json_model_4(pval, path, rep);
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <items> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "maxItems") != NULL)
    {
        pval = json_object_get(val, "maxItems");
        // .'$schema'.maxItems
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxItems]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <maxItems> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "minItems") != NULL)
    {
        pval = json_object_get(val, "minItems");
        // .'$schema'.minItems
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minItems]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <minItems> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "uniqueItems") != NULL)
    {
        pval = json_object_get(val, "uniqueItems");
        // .'$schema'.uniqueItems
        res = json_is_boolean(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.uniqueItems]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <uniqueItems> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "maxProperties") != NULL)
    {
        pval = json_object_get(val, "maxProperties");
        // .'$schema'.maxProperties
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.maxProperties]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <maxProperties> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "minProperties") != NULL)
    {
        pval = json_object_get(val, "minProperties");
        // .'$schema'.minProperties
        res = json_is_integer(pval) && json_integer_value(pval) >= 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$schema'.minProperties]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <minProperties> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "required") != NULL)
    {
        pval = json_object_get(val, "required");
        // .'$schema'.required
        res = json_model_6(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema'.required]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <required> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "additionalProperties") != NULL)
    {
        pval = json_object_get(val, "additionalProperties");
        // .'$schema'.additionalProperties
        // .'$schema'.additionalProperties.'|'.0
        res = json_is_boolean(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$schema'.additionalProperties.'|'.0]", path);
        }
        if (! res)
        {
            // .'$schema'.additionalProperties.'|'.1
            res = json_model_3(pval, path, rep);
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <additionalProperties> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "definitions") != NULL)
    {
        pval = json_object_get(val, "definitions");
        // .'$schema'.definitions
        res = _jm_obj_1(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$schema'.definitions]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <definitions> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "properties") != NULL)
    {
        pval = json_object_get(val, "properties");
        // .'$schema'.properties
        res = _jm_obj_2(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$schema'.properties]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <properties> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "patternProperties") != NULL)
    {
        pval = json_object_get(val, "patternProperties");
        // .'$schema'.patternProperties
        res = _jm_obj_3(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$schema'.patternProperties]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <patternProperties> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "dependencies") != NULL)
    {
        pval = json_object_get(val, "dependencies");
        // .'$schema'.dependencies
        res = _jm_obj_4(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$schema'.dependencies]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <dependencies> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "enum") != NULL)
    {
        pval = json_object_get(val, "enum");
        // .'$schema'.enum
        // .'$schema'.enum.'@'
        res = json_is_array(pval);
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
            int64_t ival_0 = json_array_size(pval);
            res = jm_array_is_unique(pval, path, rep) && ival_0 >= 1;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema'.enum]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <enum> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "type") != NULL)
    {
        pval = json_object_get(val, "type");
        // .'$schema'.type
        // .'$schema'.type.'|'.0
        res = json_model_5(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [.'$schema'.type.'|'.0]", path);
        }
        if (! res)
        {
            // .'$schema'.type.'|'.1
            res = json_model_7(pval, path, rep);
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <type> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "format") != NULL)
    {
        pval = json_object_get(val, "format");
        // .'$schema'.format
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.format]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <format> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "allOf") != NULL)
    {
        pval = json_object_get(val, "allOf");
        // .'$schema'.allOf
        res = json_model_4(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.allOf]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <allOf> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "anyOf") != NULL)
    {
        pval = json_object_get(val, "anyOf");
        // .'$schema'.anyOf
        res = json_model_4(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.anyOf]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <anyOf> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "oneOf") != NULL)
    {
        pval = json_object_get(val, "oneOf");
        // .'$schema'.oneOf
        res = json_model_4(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema'.oneOf]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <oneOf> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "not") != NULL)
    {
        pval = json_object_get(val, "not");
        // .'$schema'.not
        res = json_model_3(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.not]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <not> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "pattern") != NULL)
    {
        pval = json_object_get(val, "pattern");
        // .'$schema'.pattern
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.pattern]", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <pattern> [.'$schema']", path);
            return false;
        }
    }
    if (json_object_get(val, "$ref") != NULL)
    {
        pval = json_object_get(val, "$ref");
        // .'$schema'.'$ref'
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema'.'$ref']", path);
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected value for optional prop <$ref> [.'$schema']", path);
            return false;
        }
    }
    return true;
}

// check $schema (.'$schema')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // JSON Model for JSON Schema Draft 04 [JSON_MODEL_STRICT_INT, JSON_MODEL_LOOSE_FLOAT]
    // .'$schema'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected element [.'$schema']", path);
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
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#schemaArray']", path);
        }
    }
    return res;
}


// check $schema#simpleTypes (.'$schema#simpleTypes')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#stringArray']", path);
        }
    }
    return res;
}

// check $schema#typeArray (.'$schema#typeArray')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
            res = json_model_5(arr_2_item, (path ? &arr_2_lpath : NULL), rep);
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
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#typeArray']", path);
        }
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 2);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
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

void check_model_free(void)
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
check_model(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(check_model_init, check_model_map, val, name, error, reasons);
}
