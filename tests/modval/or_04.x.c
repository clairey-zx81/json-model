#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static constant_t _jm_cst_0[2];
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

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

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 2);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'|']", path);
    }
    if (! res)
    {
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected type at [$.'|']", path);
        }
        if (res)
        {
            // $.'|'.0
            // "/[0-9]/"
            res = _jm_re_1(json_string_value(val));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'|'.0]", path);
            }
            if (! res)
            {
                // $.'|'.1
                // "/[a-z]/"
                res = _jm_re_0(json_string_value(val));
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'|'.1]", path);
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'|']", path);
            }
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
        // initialize sorted set {name}
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "Susie" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "Calvin" } };
        jm_sort_cst(_jm_cst_0, 2);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "[a-z]", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "[0-9]", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
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
