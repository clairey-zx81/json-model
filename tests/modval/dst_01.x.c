#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[3];
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[3];
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[3];
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_must_tab[3];
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_must_tab[3];
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_must_tab[3];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_0_must_a ($.'|'.5.a)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.5.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.5.a]", path);
    }
    return res;
}

// check _jm_obj_0_must_c ($.'|'.5.c)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.5.c
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.5.c]", path);
    }
    return res;
}

// check _jm_obj_0_must_f ($.'|'.5.f)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.5.f
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.5.f]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 3);
}

// object $.'|'.5
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.5]", path);
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
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.5]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.5]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.5]", path);
        return false;
    }
    return true;
}

// check _jm_obj_1_must_a ($.'|'.4.a)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.4.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.4.a]", path);
    }
    return res;
}

// check _jm_obj_1_must_c ($.'|'.4.c)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.4.c
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.4.c]", path);
    }
    return res;
}

// check _jm_obj_1_must_e ($.'|'.4.e)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.4.e
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.4.e]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 3);
}

// object $.'|'.4
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.4]", path);
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
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_1 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.4]", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.4]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.4]", path);
        return false;
    }
    return true;
}

// check _jm_obj_2_must_a ($.'|'.3.a)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.3.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.3.a]", path);
    }
    return res;
}

// check _jm_obj_2_must_c ($.'|'.3.c)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.3.c
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.3.c]", path);
    }
    return res;
}

// check _jm_obj_2_must_d ($.'|'.3.d)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.3.d
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.3.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 3);
}

// object $.'|'.3
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'|'.3]", path);
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
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.3]", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.3]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.3]", path);
        return false;
    }
    return true;
}

// check _jm_obj_3_must_a ($.'|'.2.a)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.2.a]", path);
    }
    return res;
}

// check _jm_obj_3_must_b ($.'|'.2.b)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.b
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.2.b]", path);
    }
    return res;
}

// check _jm_obj_3_must_f ($.'|'.2.f)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.f
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.2.f]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_must_tab, 3);
}

// object $.'|'.2
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
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
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_3_must(prop)))
        {
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_3 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.2]", (path ? &lpath_3 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.2]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.2]", path);
        return false;
    }
    return true;
}

// check _jm_obj_4_must_a ($.'|'.1.a)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.1.a]", path);
    }
    return res;
}

// check _jm_obj_4_must_b ($.'|'.1.b)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.b
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.1.b]", path);
    }
    return res;
}

// check _jm_obj_4_must_e ($.'|'.1.e)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.e
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.1.e]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_must_tab, 3);
}

// object $.'|'.1
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
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
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_4_must(prop)))
        {
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_4 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.1]", (path ? &lpath_4 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.1]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_5_must_a ($.'|'.0.a)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'|'.0.a]", path);
    }
    return res;
}

// check _jm_obj_5_must_b ($.'|'.0.b)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.b
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 int [$.'|'.0.b]", path);
    }
    return res;
}

// check _jm_obj_5_must_d ($.'|'.0.d)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.d
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'|'.0.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_must_tab, 3);
}

// object $.'|'.0
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
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
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_5_must(prop)))
        {
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_5 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.0]", (path ? &lpath_5 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.0]", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.0]", path);
        return false;
    }
    return true;
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
        res = _jm_obj_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.0]", path);
        }
        if (! res)
        {
            // $.'|'.1
            res = _jm_obj_4(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.1]", path);
            }
            if (! res)
            {
                // $.'|'.2
                res = _jm_obj_3(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.2]", path);
                }
                if (! res)
                {
                    // $.'|'.3
                    res = _jm_obj_2(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // $.'|'.4
                        res = _jm_obj_1(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // $.'|'.5
                            res = _jm_obj_0(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.5]", path);
                            }
                        }
                    }
                }
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
        _jm_obj_0_must_tab[0] = (propmap_t) { "a", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "c", _jm_f_1 };
        _jm_obj_0_must_tab[2] = (propmap_t) { "f", _jm_f_2 };
        jm_sort_propmap(_jm_obj_0_must_tab, 3);
        _jm_obj_1_must_tab[0] = (propmap_t) { "a", _jm_f_3 };
        _jm_obj_1_must_tab[1] = (propmap_t) { "c", _jm_f_4 };
        _jm_obj_1_must_tab[2] = (propmap_t) { "e", _jm_f_5 };
        jm_sort_propmap(_jm_obj_1_must_tab, 3);
        _jm_obj_2_must_tab[0] = (propmap_t) { "a", _jm_f_6 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "c", _jm_f_7 };
        _jm_obj_2_must_tab[2] = (propmap_t) { "d", _jm_f_8 };
        jm_sort_propmap(_jm_obj_2_must_tab, 3);
        _jm_obj_3_must_tab[0] = (propmap_t) { "a", _jm_f_9 };
        _jm_obj_3_must_tab[1] = (propmap_t) { "b", _jm_f_10 };
        _jm_obj_3_must_tab[2] = (propmap_t) { "f", _jm_f_11 };
        jm_sort_propmap(_jm_obj_3_must_tab, 3);
        _jm_obj_4_must_tab[0] = (propmap_t) { "a", _jm_f_12 };
        _jm_obj_4_must_tab[1] = (propmap_t) { "b", _jm_f_13 };
        _jm_obj_4_must_tab[2] = (propmap_t) { "e", _jm_f_14 };
        jm_sort_propmap(_jm_obj_4_must_tab, 3);
        _jm_obj_5_must_tab[0] = (propmap_t) { "a", _jm_f_15 };
        _jm_obj_5_must_tab[1] = (propmap_t) { "b", _jm_f_16 };
        _jm_obj_5_must_tab[2] = (propmap_t) { "d", _jm_f_17 };
        jm_sort_propmap(_jm_obj_5_must_tab, 3);
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
    CHECK_init();  // lazy
    check_fun_t checker = CHECK_fun(name);

    bool not_found = checker == NULL;
    if (error)
        *error = not_found;

    if (not_found)
    {
        const char *format = "JSON Model check function not found for <%s>\n";

        if (!error)
        {
            fprintf(stderr, format, name);
            exit(1);
        }

        if (reasons)
        {
            size_t size = strlen(format) + strlen(name);
            char *message = malloc(size);
            sprintf(message, format, name);
            *reasons = message;
        }

        return false;
    }

    Path root = (Path) { "$", 0, NULL, NULL };
    Report report = (Report) { NULL };

    bool valid = checker(val, reasons ? &root : NULL, reasons ? &report : NULL);

    // generate explanations if a report is required and the value failed to validate
    if  (reasons && report.entry && !valid)
    {
        size_t size = 1;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            size += strlen(entry->message) + strlen(entry->path) + 3;

        char *message = malloc(size);
        *reasons = message;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            message += sprintf("%s: %s\n", entry->path, entry->message);
    }

    jm_report_free_entries(&report);

    return valid;
}
