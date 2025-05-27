#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static constmap_t _jm_map_0_tab[2];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// object $.'$A'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$A']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "t") == 0)
        {
            // handle must t property
            must_count += 1;
            // $.'$A'.t
            res = json_is_integer(pval) && json_integer_value(pval) == 1;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected =1 [$.'$A'.t]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$A'.t]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // $.'$A'.a
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$A'.a]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$A'.a]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$A']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$A']", path);
        return false;
    }
    return true;
}

// check $A ($.'$A')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$A'
    res = _jm_obj_0(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$A']", path);
    }
    return res;
}

// object $.'$B'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$B']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "t") == 0)
        {
            // handle must t property
            must_count += 1;
            // $.'$B'.t
            res = json_is_integer(pval) && json_integer_value(pval) == 2;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected =2 [$.'$B'.t]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$B'.t]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // $.'$B'.b
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$B'.b]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$B'.b]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$B']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$B']", path);
        return false;
    }
    return true;
}

// check $B ($.'$B')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$B'
    res = _jm_obj_1(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$B']", path);
    }
    return res;
}

static check_fun_t _jm_map_0(json_t *val)
{
    constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 2);
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_object(val);
    if (res)
    {
        json_t * tag_0 = json_object_get(val, "t");
        if (tag_0 != NULL)
        {
            check_fun_t fun_0 = _jm_map_0(tag_0);
            if (fun_0 != NULL)
            {
                res = fun_0(val, path, rep);
            }
            else
            {
                res = false;
                if (rep) jm_report_add_entry(rep, "tag t value not found [$.'|']", path);
            }
        }
        else
        {
            res = false;
            if (rep) jm_report_add_entry(rep, "tag prop t is missing [$.'|']", path);
        }
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value is not an object [$.'|']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
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
        _jm_map_0_tab[0] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 1 } }, json_model_2 };
        _jm_map_0_tab[1] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 2 } }, json_model_3 };
        jm_sort_constmap(_jm_map_0_tab, 2);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "A", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "B", json_model_3 };
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
