#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_4(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $R ($.'$R')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R'
    res = json_is_array(val) && json_array_size(val) == 2;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.'$R'.0
        res = json_model_5(json_array_get(val, 0), (path ? &lpath_0 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $S [$.'$R'.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.'$R'.1
            res = json_model_5(json_array_get(val, 1), (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $S [$.'$R'.1]", (path ? &lpath_0 : NULL));
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$R']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check $S ($.'$S')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$S'
    // "/[a-z]/"
    res = json_is_string(val) && _jm_re_0(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'$S']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    // $.'|'.0
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $S [$.'|'.0]", path);
    }
    if (! res)
    {
        // $.'|'.1
        res = json_model_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $R#S [$.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'|']", path);
    }
    return res;
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

// check $R#S ($.'$R#S')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$R#S'
    // "/[0-9]/"
    res = json_is_string(val) && _jm_re_1(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'$R#S']", path);
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
        check_model_map_tab[1] = (propmap_t) { "R", json_model_4 };
        check_model_map_tab[2] = (propmap_t) { "S", json_model_3 };
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
