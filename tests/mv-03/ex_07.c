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
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// check $ex5 (.'$ex5')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex5'
    // .'$ex5'.'|'.0
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [.'$ex5'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$ex5'.'|'.1
        res = json_model_6(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [.'$ex5'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$ex5'.'|']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(_jm_re_0_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}

// check $EX07 (.'$EX07')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$EX07'
    // "/[a-z]/"
    res = json_is_string(val) && _jm_re_0(json_string_value(val), path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected /[a-z]/ [.'$EX07']", path);
    }
    return res;
}

// check $__external_0 (.'$__external_0')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$__external_0'
    // .'$__external_0'.'|'.0
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [.'$__external_0'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$__external_0'.'|'.1
        res = json_model_9(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [.'$__external_0'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$__external_0'.'|']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_is_array(val) && json_array_size(val) == 3;
    if (res)
    {
        jm_path_t lpath_0 = (jm_path_t) { NULL, 0, path, NULL };
        // .0
        res = json_model_5(json_array_get(val, 0), (path ? &lpath_0 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05a [.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            jm_path_t lpath_0 = (jm_path_t) { NULL, 1, path, NULL };
            // .1
            res = json_model_9(json_array_get(val, 1), (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $__external_0#EX05b [.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                jm_path_t lpath_0 = (jm_path_t) { NULL, 2, path, NULL };
                // .2
                res = json_model_3(json_array_get(val, 2), (path ? &lpath_0 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $EX07 [.2]", (path ? &lpath_0 : NULL));
                }
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.]", path);
    }
    return res;
}

// check $ex5#EX05a (.'$ex5#EX05a')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex5#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$ex5#EX05a']", path);
    }
    return res;
}

// check $ex5#EX05b (.'$ex5#EX05b')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ex5#EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$ex5#EX05b']", path);
    }
    return res;
}

// check $__external_0#EX05a (.'$__external_0#EX05a')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$__external_0#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$__external_0#EX05a']", path);
    }
    return res;
}

// check $__external_0#EX05b (.'$__external_0#EX05b')
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$__external_0#EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$__external_0#EX05b']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 4);
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
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "ex5", json_model_4 };
        check_model_map_tab[2] = (jm_propmap_t) { "EX07", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "__external_0", json_model_7 };
        jm_sort_propmap(check_model_map_tab, 4);
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
