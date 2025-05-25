#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[2];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_0_must_f ($.f)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.f
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.f]", path);
    }
    return res;
}

// check _jm_obj_0_must_i ($.i)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.i
    res = (json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val))));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 loose int [$.i]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 2);
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
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$]", path);
        return false;
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
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_must_tab[0] = (propmap_t) { "f", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "i", _jm_f_1 };
        jm_sort_propmap(_jm_obj_0_must_tab, 2);
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
