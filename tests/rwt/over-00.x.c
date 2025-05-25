#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[1];
static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check _jm_obj_0_may_foo ($.'$Foo'.foo)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Foo'.foo
    res = json_is_string(val) && strcmp(json_string_value(val), "initial foo") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _initial foo [$.'$Foo'.foo]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 1);
}

// object $.'$Foo'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Foo']", path);
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
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$Foo']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Foo']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $Foo ($.'$Foo')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Foo'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Foo']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Foo [$]", path);
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
        check_model_map_tab[1] = (propmap_t) { "Foo", json_model_2 };
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
