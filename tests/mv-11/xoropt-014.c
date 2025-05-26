#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[2];
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[2];
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_must_tab[2];
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_must_tab[2];
static constmap_t _jm_map_0_tab[4];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_1_must_t ($.movie.'|'.0.t)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.0.t
    res = json_is_string(val) && strcmp(json_string_value(val), "fr") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected fr [$.movie.'|'.0.t]", path);
    }
    return res;
}

// check _jm_obj_1_must_titre ($.movie.'|'.0.titre)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.0.titre
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.movie.'|'.0.titre]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 2);
}

// object $.movie.'|'.0
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.movie.'|'.0]", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.movie.'|'.0]", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.movie.'|'.0]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.movie.'|'.0]", path);
        return false;
    }
    return true;
}

// check _jm_obj_2_must_t ($.movie.'|'.1.t)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.1.t
    res = json_is_string(val) && strcmp(json_string_value(val), "en") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected en [$.movie.'|'.1.t]", path);
    }
    return res;
}

// check _jm_obj_2_must_title ($.movie.'|'.1.title)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.1.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.movie.'|'.1.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 2);
}

// object $.movie.'|'.1
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.movie.'|'.1]", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.movie.'|'.1]", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.movie.'|'.1]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.movie.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_3_must_Title ($.movie.'|'.2.Title)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.2.Title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.movie.'|'.2.Title]", path);
    }
    return res;
}

// check _jm_obj_3_must_t ($.movie.'|'.2.t)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.2.t
    res = json_is_string(val) && strcmp(json_string_value(val), "de") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected de [$.movie.'|'.2.t]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_must_tab, 2);
}

// object $.movie.'|'.2
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.movie.'|'.2]", path);
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
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_3 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.movie.'|'.2]", (path ? &lpath_3 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.movie.'|'.2]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.movie.'|'.2]", path);
        return false;
    }
    return true;
}

// check _jm_obj_4_must_suti ($.movie.'|'.3.suti)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.3.suti
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.movie.'|'.3.suti]", path);
    }
    return res;
}

// check _jm_obj_4_must_t ($.movie.'|'.3.t)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.movie.'|'.3.t
    res = json_is_string(val) && strcmp(json_string_value(val), "ru") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected ru [$.movie.'|'.3.t]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_must_tab, 2);
}

// object $.movie.'|'.3
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.movie.'|'.3]", path);
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.movie.'|'.3]", (path ? &lpath_4 : NULL));
                    return false;
                }
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.movie.'|'.3]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.movie.'|'.3]", path);
        return false;
    }
    return true;
}

static check_fun_t _jm_map_0(json_t *val)
{
    constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 4);
}

// object $
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "movie") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.movie
            res = json_is_object(pval);
            if (res)
            {
                json_t * tag_0 = json_object_get(pval, "t");
                if (tag_0 != NULL)
                {
                    check_fun_t fun_0 = _jm_map_0(tag_0);
                    if (fun_0 != NULL)
                    {
                        res = fun_0(pval, (path ? &lpath_0 : NULL), rep);
                    }
                    else
                    {
                        res = false;
                        if (rep) jm_report_add_entry(rep, "tag t value not found [$.movie.'|']", (path ? &lpath_0 : NULL));
                    }
                }
                else
                {
                    res = false;
                    if (rep) jm_report_add_entry(rep, "tag prop t is missing [$.movie.'|']", (path ? &lpath_0 : NULL));
                }
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "value is not an object [$.movie.'|']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.movie]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_0 : NULL));
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
        _jm_obj_1_must_tab[0] = (propmap_t) { "t", _jm_f_0 };
        _jm_obj_1_must_tab[1] = (propmap_t) { "titre", _jm_f_1 };
        jm_sort_propmap(_jm_obj_1_must_tab, 2);
        _jm_obj_2_must_tab[0] = (propmap_t) { "t", _jm_f_2 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "title", _jm_f_3 };
        jm_sort_propmap(_jm_obj_2_must_tab, 2);
        _jm_obj_3_must_tab[0] = (propmap_t) { "Title", _jm_f_4 };
        _jm_obj_3_must_tab[1] = (propmap_t) { "t", _jm_f_5 };
        jm_sort_propmap(_jm_obj_3_must_tab, 2);
        _jm_obj_4_must_tab[0] = (propmap_t) { "suti", _jm_f_6 };
        _jm_obj_4_must_tab[1] = (propmap_t) { "t", _jm_f_7 };
        jm_sort_propmap(_jm_obj_4_must_tab, 2);
        _jm_map_0_tab[0] = (constmap_t) { (constant_t) { cst_is_string, { .s = "fr" } }, _jm_obj_1 };
        _jm_map_0_tab[1] = (constmap_t) { (constant_t) { cst_is_string, { .s = "en" } }, _jm_obj_2 };
        _jm_map_0_tab[2] = (constmap_t) { (constant_t) { cst_is_string, { .s = "de" } }, _jm_obj_3 };
        _jm_map_0_tab[3] = (constmap_t) { (constant_t) { cst_is_string, { .s = "ru" } }, _jm_obj_4 };
        jm_sort_constmap(_jm_map_0_tab, 4);
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
