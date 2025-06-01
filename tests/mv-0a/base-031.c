#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// object .'$bibi'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$bibi']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "bibi") == 0)
        {
            // handle must bibi property
            must_count += 1;
            // .'$bibi'.bibi
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_0_idx;
                json_t *arr_0_item;
                json_array_foreach(pval, arr_0_idx, arr_0_item)
                {
                    Path arr_0_lpath = (Path) { NULL, arr_0_idx, (path ? &lpath_0 : NULL), NULL };
                    // .'$bibi'.bibi.0
                    res = json_model_2(arr_0_item, ((path ? &lpath_0 : NULL) ? &arr_0_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $bibi [.'$bibi'.bibi.0]", ((path ? &lpath_0 : NULL) ? &arr_0_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$bibi'.bibi]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.'$bibi'.bibi]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$bibi']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "bibi") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <bibi> [.'$bibi']", path);
            }
        }
        return false;
    }
    return true;
}

// check $bibi (.'$bibi')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$bibi'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$bibi']", path);
    }
    return res;
}

// check $ ()
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    //
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $bibi []", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
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
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "bibi", json_model_2 };
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
