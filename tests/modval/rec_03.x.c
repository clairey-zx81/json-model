#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[1];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $root ($.'$root')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$root'
    res = json_model_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $# [$.'$root']", path);
    }
    return res;
}

// check _jm_obj_0_may_foo ($.foo)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.foo
    // $.foo.'|'.0
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $root [$.foo.'|'.0]", path);
    }
    if (! res)
    {
        // $.foo.'|'.1
        res = json_is_array(val);
        if (res)
        {
            size_t arr_0_idx;
            json_t *arr_0_item;
            json_array_foreach(val, arr_0_idx, arr_0_item)
            {
                Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
                // $.foo.'|'.1.0
                res = json_model_2(arr_0_item, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $root [$.foo.'|'.1.0]", (path ? &arr_0_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.foo.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.foo.'|']", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 1);
}

// object $
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$]", path);
        return false;
    }
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$]", path);
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
        _jm_obj_0_may_tab[0] = (propmap_t) { "foo", _jm_f_0 };
        jm_sort_propmap(_jm_obj_0_may_tab, 1);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "root", json_model_2 };
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
 * API: bool check_model(json_t *, const char *, bool *, char **);
 *
 * valid = check(value, "model-name", &error, &message);
 *
 * - error is set of there was an error during initialization or if the model does not exists.
 * - message is provided if a non NULL pointer is passed, and must be freed by the caller.
 *
 *
 * if the model is not found, report error and reasons if required, else coldly exit.
 */
bool
CHECK(json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(CHECK_init, CHECK_fun, val, name, error, reasons);
}
