#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $ex5 ($.'$ex5')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5'
    // $.'$ex5'.'|'.0
    res = json_model_5(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [$.'$ex5'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$ex5'.'|'.1
        res = json_model_6(val, path, rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [$.'$ex5'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$ex5'.'|']", path);
    }
    return res;
}

// check $EX06 ($.'$EX06')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$EX06'
    res = json_is_boolean(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$EX06']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val) && json_array_size(val) == 3;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.0
        res = json_model_5(json_array_get(val, 0), (path ? &lpath_0 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05a [$.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.1
            res = json_model_6(json_array_get(val, 1), (path ? &lpath_0 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05b [$.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                Path lpath_0 = (Path) { NULL, 2, path, NULL };
                // $.2
                res = json_model_3(json_array_get(val, 2), (path ? &lpath_0 : NULL), rep);
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $EX06 [$.2]", (path ? &lpath_0 : NULL));
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
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$]", path);
    }
    return res;
}

// check $ex5#EX05a ($.'$ex5#EX05a')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$ex5#EX05a']", path);
    }
    return res;
}

// check $ex5#EX05b ($.'$ex5#EX05b')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05b'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$ex5#EX05b']", path);
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
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "ex5", json_model_4 };
        check_model_map_tab[2] = (propmap_t) { "EX06", json_model_3 };
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
