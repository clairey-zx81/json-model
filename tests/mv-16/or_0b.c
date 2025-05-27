#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool _jm_cst_0_test(const json_t *);
static constant_t _jm_cst_0[7];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

static bool _jm_cst_0_test(const json_t *val)
{
  constant_t cst;
  jm_set_cst(&cst, val);
  return jm_search_cst(&cst, _jm_cst_0, 7);
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = _json_is_scalar(val) && _jm_cst_0_test(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'|']", path);
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
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_null, { .s = NULL } };
        _jm_cst_0[1] = (constant_t) { cst_is_bool, { .b = false } };
        _jm_cst_0[2] = (constant_t) { cst_is_integer, { .i = 42 } };
        _jm_cst_0[3] = (constant_t) { cst_is_float, { .f = 3.14159 } };
        _jm_cst_0[4] = (constant_t) { cst_is_float, { .f = 1e+101 } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "Susie" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "Calvin" } };
        jm_sort_cst(_jm_cst_0, 7);
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
