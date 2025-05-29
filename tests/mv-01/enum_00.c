#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static constant_t _jm_cst_0[5];
static bool json_model_2(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_1[5];
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $p1 ($.'$p1')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$p1'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 5);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$p1'.'|']", path);
    }
    return res;
}


// check $p2 ($.'$p2')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$p2'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 5);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$p2'.'|']", path);
    }
    return res;
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
    xr_0 = json_model_2(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $p1 [$.'^'.0]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    // $.'^'.1
    xr_0 = json_model_3(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $p2 [$.'^'.1]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    res = xc_0 == 1;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not one model match [$.'^']", path);
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
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "Susie" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "Calvin" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "Hobbes" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "Moe" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "Bad" } };
        jm_sort_cst(_jm_cst_0, 5);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (constant_t) { cst_is_string, { .s = "Castafiore" } };
        _jm_cst_1[1] = (constant_t) { cst_is_string, { .s = "Haddock" } };
        _jm_cst_1[2] = (constant_t) { cst_is_string, { .s = "Milou" } };
        _jm_cst_1[3] = (constant_t) { cst_is_string, { .s = "Tintin" } };
        _jm_cst_1[4] = (constant_t) { cst_is_string, { .s = "Bad" } };
        jm_sort_cst(_jm_cst_1, 5);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "p1", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "p2", json_model_3 };
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
