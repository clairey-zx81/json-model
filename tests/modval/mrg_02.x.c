#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[4];
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[2];
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[6];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $T ($.'$T')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$T'
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_02") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_02 [$.'$T']", path);
    }
    return res;
}

// check _jm_obj_0_must_a ($.'$R'.a)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'.a
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$R'.a]", path);
    }
    return res;
}

// check _jm_obj_0_must_b ($.'$R'.b)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'.b
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$R'.b]", path);
    }
    return res;
}

// check _jm_obj_0_must_c ($.'$R'.c)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'.c
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$R'.c]", path);
    }
    return res;
}

// check _jm_obj_0_must_d ($.'$R'.d)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'.d
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_01") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_01 [$.'$R'.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 4);
}

// object $.'$R'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$R']", path);
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
            // handle 4 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$R']", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$R']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 4)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$R']", path);
        return false;
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

// check _jm_obj_1_must_e ($.'$Z'.e)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Z'.e
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_02") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_02 [$.'$Z'.e]", path);
    }
    return res;
}

// check _jm_obj_1_must_f ($.'$Z'.f)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Z'.f
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_02") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_02 [$.'$Z'.f]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 2);
}

// object $.'$Z'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Z']", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Z']", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Z']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Z']", path);
        return false;
    }
    return true;
}

// check $Z ($.'$Z')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Z'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Z']", path);
    }
    return res;
}

// check _jm_obj_2_must_a ($.a)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_2_must_b ($.b)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_2_must_c ($.c)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_2_must_d ($.d)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
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

// check _jm_obj_2_must_e ($.e)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.e
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_02") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_02 [$.e]", path);
    }
    return res;
}

// check _jm_obj_2_must_f ($.f)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.f
    res = json_is_string(val) && strcmp(json_string_value(val), "cst_02") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _cst_02 [$.f]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 6);
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
        if ((pfun = _jm_obj_2_must(prop)))
        {
            // handle 6 must props
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
    if (must_count != 6)
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
        _jm_obj_0_must_tab[0] = (propmap_t) { "a", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "b", _jm_f_1 };
        _jm_obj_0_must_tab[2] = (propmap_t) { "c", _jm_f_2 };
        _jm_obj_0_must_tab[3] = (propmap_t) { "d", _jm_f_3 };
        jm_sort_propmap(_jm_obj_0_must_tab, 4);
        _jm_obj_1_must_tab[0] = (propmap_t) { "e", _jm_f_4 };
        _jm_obj_1_must_tab[1] = (propmap_t) { "f", _jm_f_5 };
        jm_sort_propmap(_jm_obj_1_must_tab, 2);
        _jm_obj_2_must_tab[0] = (propmap_t) { "a", _jm_f_6 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "b", _jm_f_7 };
        _jm_obj_2_must_tab[2] = (propmap_t) { "c", _jm_f_8 };
        _jm_obj_2_must_tab[3] = (propmap_t) { "d", _jm_f_9 };
        _jm_obj_2_must_tab[4] = (propmap_t) { "e", _jm_f_10 };
        _jm_obj_2_must_tab[5] = (propmap_t) { "f", _jm_f_11 };
        jm_sort_propmap(_jm_obj_2_must_tab, 6);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "T", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "R", json_model_5 };
        check_model_map_tab[3] = (propmap_t) { "Z", json_model_4 };
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
