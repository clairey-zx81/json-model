#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// object .'$un'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$un']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "ua") == 0)
        {
            // handle must ua property
            must_count += 1;
            // .'$un'.ua
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$un'.ua]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$un'.ua]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "ub") == 0)
        {
            // handle must ub property
            must_count += 1;
            // .'$un'.ub
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$un'.ub]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$un'.ub]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$un']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "ua") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <ua> [.'$un']", path);
            }
            if (! (json_object_get(val, "ub") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <ub> [.'$un']", path);
            }
        }
        return false;
    }
    return true;
}

// check $un (.'$un')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$un'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$un']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $un [.]", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
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
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "un", json_model_2 };
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
