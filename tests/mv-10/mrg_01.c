#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_mup_tab[4];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $T ($.'$T')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$T'
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$T']", path);
    }
    return res;
}

// object $.'$X'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$X']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // $.'$X'.a
            res = json_is_string(pval) && strcmp(json_string_value(pval), "cst_01") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$X'.a]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$X'.a]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // $.'$X'.b
            res = json_is_string(pval) && strcmp(json_string_value(pval), "cst_01") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$X'.b]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$X'.b]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$X']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$X']", path);
        return false;
    }
    return true;
}

// check $X ($.'$X')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$X'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$X']", path);
    }
    return res;
}

// object $.'$Y'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Y']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "c") == 0)
        {
            // handle must c property
            must_count += 1;
            // $.'$Y'.c
            res = json_is_string(pval) && strcmp(json_string_value(pval), "cst_01") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$Y'.c]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Y'.c]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // $.'$Y'.d
            res = json_is_string(pval) && strcmp(json_string_value(pval), "cst_01") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$Y'.d]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Y'.d]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Y']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Y']", path);
        return false;
    }
    return true;
}

// check $Y ($.'$Y')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Y'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Y']", path);
    }
    return res;
}

// check _jm_obj_2_mup_a ($.a)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.a
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.a]", path);
    }
    return res;
}

// check _jm_obj_2_mup_b ($.b)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.b
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.b]", path);
    }
    return res;
}

// check _jm_obj_2_mup_c ($.c)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.c
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.c]", path);
    }
    return res;
}

// check _jm_obj_2_mup_d ($.d)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.d
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_mup(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_mup_tab, 4);
}

// object $
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
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
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_2_mup(prop)))
        {
            // handle 4 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$]", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 4)
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
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$]", path);
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
        _jm_obj_2_mup_tab[0] = (propmap_t) { "a", _jm_f_0 };
        _jm_obj_2_mup_tab[1] = (propmap_t) { "b", _jm_f_1 };
        _jm_obj_2_mup_tab[2] = (propmap_t) { "c", _jm_f_2 };
        _jm_obj_2_mup_tab[3] = (propmap_t) { "d", _jm_f_3 };
        jm_sort_propmap(_jm_obj_2_mup_tab, 4);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "T", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "X", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "Y", json_model_4 };
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
