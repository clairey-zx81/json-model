#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static jm_constant_t _jm_cst_0[3];
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $XXX (.'$XXX')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XXX'
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 3);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$XXX'.'|']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// object .
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "foo") == 0)
        {
            // handle must foo property
            must_count += 1;
            // .foo
            res = jm_is_valid_date(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $DATE [.foo]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.foo]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "bla") == 0)
        {
            // handle may bla property
            // .bla
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.bla]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.bla]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (jm_check_fun_string(json_model_2, prop, (path ? &lpath_0 : NULL), rep))
        {
            // handle 1 key props
            // .'$XXX'
            res = json_is_real(pval) && json_real_value(pval) >= 0.0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0.0 strict float [.'$XXX']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'/^[0-9]+$/'
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'/^[0-9]+$/']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .''
            res = json_is_null(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not null [.'']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "foo") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <foo> [.'']", path);
            }
        }
        return false;
    }
    return true;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.]", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
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
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (jm_constant_t) { cst_is_string, { .s = "X" } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_string, { .s = "XX" } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_string, { .s = "XXX" } };
        jm_sort_cst(_jm_cst_0, 3);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^[0-9]+$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "XXX", json_model_2 };
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
