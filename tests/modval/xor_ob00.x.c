#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[1];
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[1];
static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[1];
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_must_tab[1];
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_must_tab[2];
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_must_tab[2];
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_6_must_tab[2];
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_7_must_tab[2];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check _jm_obj_0_must_b ($.'$A'.'|'.1.b)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$A'.'|'.1.b
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$A'.'|'.1.b]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 1);
}

// object $.'$A'.'|'.1
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$A'.'|'.1]", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$A'.'|'.1]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$A'.'|'.1]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$A'.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_1_must_a ($.'$A'.'|'.0.a)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$A'.'|'.0.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$A'.'|'.0.a]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 1);
}

// object $.'$A'.'|'.0
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$A'.'|'.0]", path);
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
            // handle 1 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_1 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$A'.'|'.0]", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$A'.'|'.0]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$A'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $A ($.'$A')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$A'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$A'.'|']", path);
    }
    if (res)
    {
        // $.'$A'.'|'.0
        res = _jm_obj_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$A'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$A'.'|'.1
            res = _jm_obj_0(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$A'.'|'.1]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$A'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_2_must_d ($.'$B'.'|'.1.d)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$B'.'|'.1.d
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$B'.'|'.1.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 1);
}

// object $.'$B'.'|'.1
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$B'.'|'.1]", path);
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
            // handle 1 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$B'.'|'.1]", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$B'.'|'.1]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$B'.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_3_must_c ($.'$B'.'|'.0.c)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$B'.'|'.0.c
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$B'.'|'.0.c]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_must_tab, 1);
}

// object $.'$B'.'|'.0
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$B'.'|'.0]", path);
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
            // handle 1 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_3 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$B'.'|'.0]", (path ? &lpath_3 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$B'.'|'.0]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$B'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $B ($.'$B')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$B'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$B'.'|']", path);
    }
    if (res)
    {
        // $.'$B'.'|'.0
        res = _jm_obj_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$B'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$B'.'|'.1
            res = _jm_obj_2(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$B'.'|'.1]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$B'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_4_must_b ($.'|'.3.b)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.3.b
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.3.b]", path);
    }
    return res;
}

// check _jm_obj_4_must_d ($.'|'.3.d)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.3.d
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.3.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_must_tab, 2);
}

// object $.'|'.3
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
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
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_4_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_4 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.3]", (path ? &lpath_4 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.3]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'|'.3]", path);
        return false;
    }
    return true;
}

// check _jm_obj_5_must_b ($.'|'.2.b)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.b
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.2.b]", path);
    }
    return res;
}

// check _jm_obj_5_must_c ($.'|'.2.c)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.2.c
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.2.c]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_must_tab, 2);
}

// object $.'|'.2
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
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
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_5_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_5 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.2]", (path ? &lpath_5 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.2]", (path ? &lpath_5 : NULL));
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

// check _jm_obj_6_must_a ($.'|'.1.a)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.1.a]", path);
    }
    return res;
}

// check _jm_obj_6_must_d ($.'|'.1.d)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.1.d
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.1.d]", path);
    }
    return res;
}

static check_fun_t _jm_obj_6_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_must_tab, 2);
}

// object $.'|'.1
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
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
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_6_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_6 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.1]", (path ? &lpath_6 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.1]", (path ? &lpath_6 : NULL));
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

// check _jm_obj_7_must_a ($.'|'.0.a)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.a
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.0.a]", path);
    }
    return res;
}

// check _jm_obj_7_must_c ($.'|'.0.c)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'|'.0.c
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'|'.0.c]", path);
    }
    return res;
}

static check_fun_t _jm_obj_7_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_7_must_tab, 2);
}

// object $.'|'.0
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
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
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_7_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_7 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'|'.0]", (path ? &lpath_7 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'|'.0]", (path ? &lpath_7 : NULL));
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
        res = _jm_obj_7(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.0]", path);
        }
        if (! res)
        {
            // $.'|'.1
            res = _jm_obj_6(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.1]", path);
            }
            if (! res)
            {
                // $.'|'.2
                res = _jm_obj_5(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.2]", path);
                }
                if (! res)
                {
                    // $.'|'.3
                    res = _jm_obj_4(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'|'.3]", path);
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
    return jm_search_propmap(pname, check_model_map_tab, 3);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_must_tab[0] = (propmap_t) { "b", _jm_f_0 };
        jm_sort_propmap(_jm_obj_0_must_tab, 1);
        _jm_obj_1_must_tab[0] = (propmap_t) { "a", _jm_f_1 };
        jm_sort_propmap(_jm_obj_1_must_tab, 1);
        _jm_obj_2_must_tab[0] = (propmap_t) { "d", _jm_f_2 };
        jm_sort_propmap(_jm_obj_2_must_tab, 1);
        _jm_obj_3_must_tab[0] = (propmap_t) { "c", _jm_f_3 };
        jm_sort_propmap(_jm_obj_3_must_tab, 1);
        _jm_obj_4_must_tab[0] = (propmap_t) { "b", _jm_f_4 };
        _jm_obj_4_must_tab[1] = (propmap_t) { "d", _jm_f_5 };
        jm_sort_propmap(_jm_obj_4_must_tab, 2);
        _jm_obj_5_must_tab[0] = (propmap_t) { "b", _jm_f_6 };
        _jm_obj_5_must_tab[1] = (propmap_t) { "c", _jm_f_7 };
        jm_sort_propmap(_jm_obj_5_must_tab, 2);
        _jm_obj_6_must_tab[0] = (propmap_t) { "a", _jm_f_8 };
        _jm_obj_6_must_tab[1] = (propmap_t) { "d", _jm_f_9 };
        jm_sort_propmap(_jm_obj_6_must_tab, 2);
        _jm_obj_7_must_tab[0] = (propmap_t) { "a", _jm_f_10 };
        _jm_obj_7_must_tab[1] = (propmap_t) { "c", _jm_f_11 };
        jm_sort_propmap(_jm_obj_7_must_tab, 2);
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
