#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[2];
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[2];
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[2];
static constmap_t _jm_map_0_tab[3];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_0_must_d ($.'|'.0.d)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.d
    res = json_is_integer(val) && json_integer_value(val) == 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected =1 [$.'|'.0.d]", path);
    }
    return res;
}

// check _jm_obj_0_must_val ($.'|'.0.val)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.val
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'|'.0.val]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 2);
}

// object $.'|'.0
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.0]", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.0]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.0]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.0]", path);
        return false;
    }
    return true;
}

// check _jm_obj_1_must_d ($.'|'.1.d)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.d
    res = json_is_integer(val) && json_integer_value(val) == 2;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected =2 [$.'|'.1.d]", path);
    }
    return res;
}

// check _jm_obj_1_must_val ($.'|'.1.val)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.val
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.1.val]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 2);
}

// object $.'|'.1
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
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
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_1_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_1 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.1]", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.1]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_2_must_d ($.'|'.2.d)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.d
    res = json_is_integer(val) && json_integer_value(val) == 3;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected =3 [$.'|'.2.d]", path);
    }
    return res;
}

// check _jm_obj_2_must_val ($.'|'.2.val)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.val
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'|'.2.val]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 2);
}

// object $.'|'.2
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.2]", path);
        return false;
    }
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_2_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.2]", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.2]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.2]", path);
        return false;
    }
    return true;
}

static check_fun_t _jm_map_0(json_t *val)
{
    constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 3);
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_object(val);
    if (res)
    {
        json_t * tag_0 = json_object_get(val, "d");
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
                if (rep) jm_report_add_entry(rep, "tag d value not found [$.'|']", path);
            }
        }
        else
        {
            res = false;
            if (rep) jm_report_add_entry(rep, "tag prop d is missing [$.'|']", path);
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
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_must_tab[0] = (propmap_t) { "d", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "val", _jm_f_1 };
        jm_sort_propmap(_jm_obj_0_must_tab, 2);
        _jm_obj_1_must_tab[0] = (propmap_t) { "d", _jm_f_2 };
        _jm_obj_1_must_tab[1] = (propmap_t) { "val", _jm_f_3 };
        jm_sort_propmap(_jm_obj_1_must_tab, 2);
        _jm_obj_2_must_tab[0] = (propmap_t) { "d", _jm_f_4 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "val", _jm_f_5 };
        jm_sort_propmap(_jm_obj_2_must_tab, 2);
        _jm_map_0_tab[0] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 1 } }, _jm_obj_0 };
        _jm_map_0_tab[1] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 2 } }, _jm_obj_1 };
        _jm_map_0_tab[2] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 3 } }, _jm_obj_2 };
        jm_sort_constmap(_jm_map_0_tab, 3);
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
