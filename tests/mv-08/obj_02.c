//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

// check $li0 (.'$li0')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$li0'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
            // .'$li0'.0
            res = json_is_integer(arr_0_item) && json_integer_value(arr_0_item) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$li0'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$li0']", path);
    }
    return res;
}

// check $ls0 (.'$ls0')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ls0'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, path, NULL };
            // .'$ls0'.0
            res = jm_is_valid_url(json_string_value(arr_1_item), (path ? &arr_1_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$ls0'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$ls0']", path);
    }
    return res;
}

// check $lb0 (.'$lb0')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$lb0'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            jm_path_t arr_2_lpath = (jm_path_t) { NULL, arr_2_idx, path, NULL };
            // .'$lb0'.0
            res = json_is_boolean(arr_2_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $BOOL [.'$lb0'.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$lb0']", path);
    }
    return res;
}

// check $lf0 (.'$lf0')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$lf0'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            jm_path_t arr_3_lpath = (jm_path_t) { NULL, arr_3_idx, path, NULL };
            // .'$lf0'.0
            res = json_is_real(arr_3_item) && json_real_value(arr_3_item) >= 0.0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0.0 strict float [.'$lf0'.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$lf0']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    // .'|'.0
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $li0 [.'|'.0]", path);
    }
    if (! res)
    {
        // .'|'.1
        res = json_model_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ls0 [.'|'.1]", path);
        }
        if (! res)
        {
            // .'|'.2
            res = json_model_4(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $lb0 [.'|'.2]", path);
            }
            if (! res)
            {
                // .'|'.3
                res = json_model_5(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $lf0 [.'|'.3]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'|']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 5);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "li0", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "ls0", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "lb0", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "lf0", json_model_5 };
        jm_sort_propmap(check_model_map_tab, 5);
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
