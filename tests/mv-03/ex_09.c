//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $ex08 (.'$ex08')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex08'
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX08 [.'$ex08']", path);
    }
    return res;
}

// check $EX08 (.'$EX08')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$EX08'
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ex08#EX08 [.'$EX08']", path);
    }
    return res;
}

// object .'$EX09'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$EX09']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$EX09'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$EX09'.'#']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$EX09'.'#']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (jm_is_valid_url(prop, (path ? &lpath_0 : NULL), rep))
        {
            // handle 1 key props
            // .'$EX09'.'$URL'
            res = json_model_6(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ex08#VAL [.'$EX09'.'$URL']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$EX09']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $EX09 (.'$EX09')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$EX09'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected element [.'$EX09']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX09 [.]", path);
    }
    return res;
}

// check $ex08#VAL (.'$ex08#VAL')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex08#VAL'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$ex08#VAL']", path);
    }
    return res;
}

// check $ex08#EX08 (.'$ex08#EX08')
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex08#EX08'
    // .'$ex08#EX08'.'|'.0
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $map [.'$ex08#EX08'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$ex08#EX08'.'|'.1
        res = jm_is_valid_url(json_string_value(val), path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$ex08#EX08'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$ex08#EX08'.'|'.2
            res = json_model_6(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $VAL [.'$ex08#EX08'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$ex08#EX08'.'|']", path);
    }
    return res;
}

// object .'$ex08#map'
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$ex08#map']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop, (path ? &lpath_1 : NULL), rep))
        {
            // handle 1 key props
            // .'$ex08#map'.'$URL'
            res = json_model_6(pval, (path ? &lpath_1 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $VAL [.'$ex08#map'.'$URL']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$ex08#map']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    return true;
}

// check $ex08#map (.'$ex08#map')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex08#map'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected element [.'$ex08#map']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 4);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "ex08", json_model_5 };
        check_model_map_tab[2] = (jm_propmap_t) { "EX08", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "EX09", json_model_4 };
        jm_sort_propmap(check_model_map_tab, 4);
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
