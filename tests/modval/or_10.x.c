#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[1];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_0_must_name ($.'|'.1.name)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.1.name]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 1);
}

// object $.'|'.1
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.1]", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_must(prop)))
        {
            // handle 1 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.1]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.1]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.1]", path);
        return false;
    }
    return true;
}

// object $.'|'.0
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.0]", path);
        return false;
    }
    if (json_object_size(val) == 0)
    {
        return true;
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "expecting empty object [$.'|'.0]", path);
        return false;
    }
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'|']", path);
    }
    if (res)
    {
        // $.'|'.0
        res = _jm_obj_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.0]", path);
        }
        if (! res)
        {
            // $.'|'.1
            res = _jm_obj_0(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.1]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'|']", path);
        }
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
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
        _jm_obj_0_must_tab[0] = (propmap_t) { "name", _jm_f_0 };
        jm_sort_propmap(_jm_obj_0_must_tab, 1);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
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
