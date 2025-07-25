//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static jm_constant_t _jm_cst_0[3];
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $XXX (.'$XXX')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XXX'
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 3);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$XXX'.'|']", path);
    }
    return res;
}

// object .
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_check_fun_string(json_model_2, prop, (path ? &lpath_0 : NULL), rep))
        {
            // handle 1 key props
            // .'$XXX'
            res = json_is_real(pval) && json_real_value(pval) >= 0.0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0.0 strict float [.'$XXX']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // prop ref to enum
    // .
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected element [.]", path);
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
        _jm_cst_0[0] = (jm_constant_t) { cst_is_string, { .s = "X" } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_string, { .s = "XX" } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_string, { .s = "XXX" } };
        jm_sort_cst(_jm_cst_0, 3);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "XXX", json_model_2 };
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
