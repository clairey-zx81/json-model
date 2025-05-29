#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $Z ($.'$Z')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Z'
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $zero [$.'$Z']", path);
    }
    return res;
}

// check $z ($.'$z')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$z'
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Z#zero [$.'$z']", path);
    }
    return res;
}

// check $l ($.'$l')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$l'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$l'.0
            res = json_model_3(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $z [$.'$l'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$l']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $l [$]", path);
    }
    return res;
}

// object $.'$Z#zero'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Z#zero']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "za") == 0)
        {
            // handle must za property
            must_count += 1;
            // $.'$Z#zero'.za
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$Z#zero'.za]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Z#zero'.za]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "zb") == 0)
        {
            // handle must zb property
            must_count += 1;
            // $.'$Z#zero'.zb
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$Z#zero'.zb]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Z#zero'.zb]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Z#zero']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Z#zero']", path);
        return false;
    }
    return true;
}

// check $Z#zero ($.'$Z#zero')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Z#zero'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Z#zero']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 4);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "Z", json_model_5 };
        check_model_map_tab[2] = (propmap_t) { "z", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "l", json_model_4 };
        jm_sort_propmap(check_model_map_tab, 4);
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
