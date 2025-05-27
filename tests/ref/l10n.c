#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_mup_tab[4];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// object $.'$'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "Model") == 0)
        {
            // handle must Model property
            must_count += 1;
            // $.'$'.Model
            res = json_is_string(pval) && strcmp(json_string_value(pval), "$https://json-model.org/models/json-model") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected _$https://json-model.org/models/json-model [$.'$'.Model]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$'.Model]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // $.'$'.''
            res = jm_is_valid_url(json_string_value(pval));
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$'.'']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$'.]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$']", path);
        return false;
    }
    return true;
}

// check _jm_obj_0_mup_$ ($.'$')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$'
    res = _jm_obj_1(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

// object $.'%'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (_jm_re_0(prop))
        {
            // handle 1 re props
            // $.'%'.'/^\\..+$/'
            // "/^([#~$%@|&+^/*=]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_1(json_string_value(pval));
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'%'.'/^\\\\..+$/']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'%']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_mup_% ($.'%')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'%'
    res = _jm_obj_2(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'%']", path);
    }
    return res;
}

// check _jm_obj_0_mup_@ ($.'@')
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'@'
    res = json_is_string(val) && strcmp(json_string_value(val), "$Model") == 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected _$Model [$.'@']", path);
    }
    return res;
}

// check _jm_obj_0_mup_~ ($.'~')
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'~'
    res = json_is_string(val) && strcmp(json_string_value(val), "https://json-model.org/models/l10n") == 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected _https://json-model.org/models/l10n [$.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_mup(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_mup_tab, 4);
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
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_mup(prop)))
        {
            // handle 4 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$]", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // $.'#'
            res = json_is_string(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'#']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.#]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$]", (path ? &lpath_0 : NULL));
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
    res = _jm_obj_0(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
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
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^\\..+$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "^([#~$%@|&+^/*=]|[<>!]=?)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
        _jm_obj_0_mup_tab[0] = (propmap_t) { "$", _jm_f_0 };
        _jm_obj_0_mup_tab[1] = (propmap_t) { "%", _jm_f_1 };
        _jm_obj_0_mup_tab[2] = (propmap_t) { "@", _jm_f_2 };
        _jm_obj_0_mup_tab[3] = (propmap_t) { "~", _jm_f_3 };
        jm_sort_propmap(_jm_obj_0_mup_tab, 4);
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
        pcre2_match_data_free(_jm_re_1_data);
        pcre2_code_free(_jm_re_1_code);
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
