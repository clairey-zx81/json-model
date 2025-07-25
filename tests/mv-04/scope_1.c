//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static cre2_regexp_t *_jm_re_0_re2 = NULL;
static int _jm_re_0_nn = 0;
static bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static cre2_regexp_t *_jm_re_1_re2 = NULL;
static int _jm_re_1_nn = 0;
static bool _jm_re_1(const char *s, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $R (.'$R')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$R'
    res = json_is_array(val) && json_array_size(val) == 2;
    if (res)
    {
        jm_path_t lpath_0 = (jm_path_t) { NULL, 0, path, NULL };
        // .'$R'.0
        res = json_model_5(json_array_get(val, 0), (path ? &lpath_0 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $S [.'$R'.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            jm_path_t lpath_0 = (jm_path_t) { NULL, 1, path, NULL };
            // .'$R'.1
            res = json_model_5(json_array_get(val, 1), (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $S [.'$R'.1]", (path ? &lpath_0 : NULL));
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$R']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(_jm_re_0_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}

// check $S (.'$S')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$S'
    // "/[a-z]/"
    res = json_is_string(val) && _jm_re_0(json_string_value(val), path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected /[a-z]/ [.'$S']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // a string with a lower case later or a digit
    // .
    // .'|'.0
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $S [.'|'.0]", path);
    }
    if (! res)
    {
        // .'|'.1
        res = json_model_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $R#S [.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'|']", path);
    }
    return res;
}

static bool _jm_re_1(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(_jm_re_1_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}

// check $R#S (.'$R#S')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$R#S'
    // "/[0-9]/"
    res = json_is_string(val) && _jm_re_1(json_string_value(val), path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected /[0-9]/ [.'$R#S']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 3);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_re_0_re2 = cre2_new("[a-z]", strlen("[a-z]"), NULL);
        if (cre2_error_code(_jm_re_0_re2))
            return cre2_error_string(_jm_re_0_re2);
        _jm_re_0_nn = cre2_num_capturing_groups(_jm_re_0_re2) + 1;
        _jm_re_1_re2 = cre2_new("[0-9]", strlen("[0-9]"), NULL);
        if (cre2_error_code(_jm_re_1_re2))
            return cre2_error_string(_jm_re_1_re2);
        _jm_re_1_nn = cre2_num_capturing_groups(_jm_re_1_re2) + 1;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "R", json_model_4 };
        check_model_map_tab[2] = (jm_propmap_t) { "S", json_model_3 };
        jm_sort_propmap(check_model_map_tab, 3);
    }
    return NULL;
}

void check_model_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
        cre2_delete(_jm_re_0_re2);
        _jm_re_0_re2 = NULL;
        _jm_re_0_nn = 0;
        cre2_delete(_jm_re_1_re2);
        _jm_re_1_re2 = NULL;
        _jm_re_1_nn = 0;
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
check_model(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(check_model_init, check_model_map, val, name, error, reasons);
}
