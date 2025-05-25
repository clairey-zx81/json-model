#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

// check $x1 ($.'$x1')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x1'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x1']", path);
    }
    return res;
}

// check $x2 ($.'$x2')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x2'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x2']", path);
    }
    return res;
}

// check $x3 ($.'$x3')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x3'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x3']", path);
    }
    return res;
}

// check $__external_0 ($.'$__external_0')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$__external_0'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$__external_0']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val) && json_array_size(val) == 4;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.0
        res = json_is_string(json_array_get(val, 0)) && strcmp(json_string_value(json_array_get(val, 0)), "Susie") == 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.1
            res = json_is_string(json_array_get(val, 1)) && strcmp(json_string_value(json_array_get(val, 1)), "Susie") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                Path lpath_0 = (Path) { NULL, 2, path, NULL };
                // $.2
                res = json_is_string(json_array_get(val, 2)) && strcmp(json_string_value(json_array_get(val, 2)), "Susie") == 0;
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.2]", (path ? &lpath_0 : NULL));
                }
                if (res)
                {
                    Path lpath_0 = (Path) { NULL, 3, path, NULL };
                    // $.3
                    res = json_is_string(json_array_get(val, 3)) && strcmp(json_string_value(json_array_get(val, 3)), "Susie") == 0;
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.3]", (path ? &lpath_0 : NULL));
                    }
                }
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$]", path);
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
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "x1", json_model_5 };
        check_model_map_tab[2] = (propmap_t) { "x2", json_model_6 };
        check_model_map_tab[3] = (propmap_t) { "x3", json_model_7 };
        check_model_map_tab[4] = (propmap_t) { "__external_0", json_model_8 };
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
