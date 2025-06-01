#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $a (.'$a')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$a'
    res = json_is_string(val) && strcmp(json_string_value(val), "a") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _a [.'$a']", path);
    }
    return res;
}

// check $A (.'$A')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$A'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$A']", path);
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
        if (strcmp(prop, "a") == 0)
        {
            // handle may a property
            // .a
            res = json_model_3(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $A [.a]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [..a]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.]", path);
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
        check_model_map_tab[1] = (jm_propmap_t) { "a", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "A", json_model_3 };
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
