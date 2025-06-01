#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// object .
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "mu1") == 0)
        {
            // handle must mu1 property
            must_count += 1;
            // .mu1
            res = json_is_null(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not null [.mu1]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [..mu1]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "mu2") == 0)
        {
            // handle must mu2 property
            must_count += 1;
            // .mu2
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.mu2]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [..mu2]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "mu3") == 0)
        {
            // handle must mu3 property
            must_count += 1;
            // .mu3
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.mu3]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [..mu3]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "ma1") == 0)
        {
            // handle may ma1 property
            // .ma1
            res = json_is_real(pval) && json_real_value(pval) >= 0.0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0.0 strict float [.ma1]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [..ma1]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "ma2") == 0)
        {
            // handle may ma2 property
            // .ma2
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.ma2]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [..ma2]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "ma3") == 0)
        {
            // handle may ma3 property
            // .ma3
            res = jm_is_valid_date(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $DATE [.ma3]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [..ma3]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "mu1") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <mu1> [.]", path);
            }
            if (! (json_object_get(val, "mu2") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <mu2> [.]", path);
            }
            if (! (json_object_get(val, "mu3") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <mu3> [.]", path);
            }
        }
        return false;
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
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 1);
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
