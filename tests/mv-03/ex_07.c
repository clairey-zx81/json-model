#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_4(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool json_model_9(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $ex5 ($.'$ex5')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5'
    // $.'$ex5'.'|'.0
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [$.'$ex5'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$ex5'.'|'.1
        res = json_model_6(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [$.'$ex5'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$ex5'.'|']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check $EX07 ($.'$EX07')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$EX07'
    // "/[a-z]/"
    res = json_is_string(val) && _jm_re_0(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'$EX07']", path);
    }
    return res;
}

// check $__external_0 ($.'$__external_0')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$__external_0'
    // $.'$__external_0'.'|'.0
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [$.'$__external_0'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$__external_0'.'|'.1
        res = json_model_9(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [$.'$__external_0'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$__external_0'.'|']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val) && json_array_size(val) == 3;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.0
        res = json_model_5(json_array_get(val, 0), (path ? &lpath_0 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05a [$.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.1
            res = json_model_9(json_array_get(val, 1), (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $__external_0#EX05b [$.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                Path lpath_0 = (Path) { NULL, 2, path, NULL };
                // $.2
                res = json_model_3(json_array_get(val, 2), (path ? &lpath_0 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $EX07 [$.2]", (path ? &lpath_0 : NULL));
                }
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$]", path);
    }
    return res;
}

// check $ex5#EX05a ($.'$ex5#EX05a')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$ex5#EX05a']", path);
    }
    return res;
}

// check $ex5#EX05b ($.'$ex5#EX05b')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$ex5#EX05b']", path);
    }
    return res;
}

// check $__external_0#EX05a ($.'$__external_0#EX05a')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$__external_0#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$__external_0#EX05a']", path);
    }
    return res;
}

// check $__external_0#EX05b ($.'$__external_0#EX05b')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$__external_0#EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$__external_0#EX05b']", path);
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
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "ex5", json_model_4 };
        check_model_map_tab[2] = (propmap_t) { "EX07", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "__external_0", json_model_7 };
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
