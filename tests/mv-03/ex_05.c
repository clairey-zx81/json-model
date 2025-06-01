#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $EX05a (.'$EX05a')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$EX05a']", path);
    }
    return res;
}

// check $EX05b (.'$EX05b')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$EX05b']", path);
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
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [.'|'.0]", path);
    }
    if (! res)
    {
        // .'|'.1
        res = json_model_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [.'|'.1]", path);
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
    return jm_search_propmap(pname, check_model_map_tab, 3);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "EX05a", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "EX05b", json_model_3 };
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
