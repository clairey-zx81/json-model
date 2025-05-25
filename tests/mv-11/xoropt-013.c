#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[1];
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_must_tab[1];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// check _jm_obj_0_must_a ($.'^'.0.a)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'^'.0.a
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'^'.0.a]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 1);
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// object $.'^'.0
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'^'.0]", path);
        return false;
    }
    bool res;
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
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'^'.0]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else
        {
            // handle other props
            // $.'^'.0.''
            // "/.../"
            res = json_is_string(pval) && _jm_re_0(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'^'.0.'']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'^'.0.'']", path);
        return false;
    }
    return true;
}

// check _jm_obj_1_must_b ($.'^'.1.b)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'^'.1.b
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'^'.1.b]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_must_tab, 1);
}

// object $.'^'.1
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'^'.1]", path);
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
        if ((pfun = _jm_obj_1_must(prop)))
        {
            // handle 1 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_1 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'^'.1]", (path ? &lpath_1 : NULL));
                    return false;
                }
            }
        }
        else
        {
            // handle other props
            // $.'^'.1.''
            // "/.../"
            res = json_is_string(pval) && _jm_re_0(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'^'.1.'']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'^'.1.'']", path);
        return false;
    }
    return true;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    // generic xor list
    int64_t xc_0 = 0;
    bool xr_0;
    // $.'^'.0
    xr_0 = _jm_obj_0(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'^'.0]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    // $.'^'.1
    xr_0 = _jm_obj_1(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'^'.1]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    res = xc_0 == 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not one model match [$.'^']", path);
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
        jm_sort_propmap(_jm_obj_0_must_tab, 1);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "...", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_obj_1_must_tab[0] = (propmap_t) { "b", _jm_f_1 };
        jm_sort_propmap(_jm_obj_1_must_tab, 1);
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
        pcre2_match_data_free(_jm_re_0_data);
        pcre2_code_free(_jm_re_0_code);
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
