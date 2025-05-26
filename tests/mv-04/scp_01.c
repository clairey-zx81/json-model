#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_may_tab[2];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_7(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $b ($.'$b')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$b'
    res = json_is_string(val) && strcmp(json_string_value(val), "b") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _b [$.'$b']", path);
    }
    return res;
}

// check $B ($.'$B')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$B'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$B']", path);
    }
    return res;
}

// object $.'$R'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$R']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "a") == 0)
        {
            // handle one may property
            // $.'$R'.a
            res = json_model_7(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $A [$.'$R'.a]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$R'.a]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$R']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $R ($.'$R')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$R']", path);
    }
    return res;
}

// check _jm_obj_1_may_a ($.a)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.a
    res = json_model_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $R#A [$.a]", path);
    }
    return res;
}

// check _jm_obj_1_may_b ($.b)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.b
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $B [$.b]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_may_tab, 2);
}

// object $
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "RA") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.RA
            res = json_model_5(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $R [$.RA]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.RA]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_1_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_1 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
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
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$]", path);
    }
    return res;
}

// check $R#A ($.'$R#A')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R#A'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$R#A']", path);
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
        _jm_obj_1_may_tab[0] = (propmap_t) { "a", _jm_f_0 };
        _jm_obj_1_may_tab[1] = (propmap_t) { "b", _jm_f_1 };
        jm_sort_propmap(_jm_obj_1_may_tab, 2);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "b", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "B", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "R", json_model_5 };
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
