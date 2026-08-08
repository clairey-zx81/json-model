
#include <json-model.h>
#define JSON_MODEL_VERSION "2"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    return json_is_string(val) && jm_str_eq_1(json_string_value(val), 0x23);
}

static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res = json_is_array(val) && json_array_size(val) == 2;
    if (likely(res))
    {
        res = json_is_boolean(json_array_get(val, 0));
        if (likely(res))
            res = true;
    }
    return res;
}

static INLINE bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep)
{
    while (likely(jm_ident_dash(*s)))
        s++;
    return *s == '\0';
}

static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res = json_is_array(val) && json_array_size(val) == 3;
    if (likely(res))
    {
        res = json_is_boolean(json_array_get(val, 0));
        if (likely(res))
        {
            res = json_is_string(json_array_get(val, 1)) && _jm_re_0(json_string_value(json_array_get(val, 1)), NULL, NULL);
            if (likely(res))
                res = true;
        }
    }
    return res;
}

static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    return json_model_2(val, NULL, NULL) || json_model_3(val, NULL, NULL) || json_model_4(val, NULL, NULL);
}

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res = json_is_array(val);
    if (likely(res))
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            res = json_model_5(arr_0_item, NULL, NULL);
            if (unlikely(! res))
                break;
        }
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 5);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "Comment", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "Test2", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "Test3", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "Test", json_model_5 };
        jm_sort_propmap(check_model_map_tab, 5);
    }
    return NULL;
}

void check_model_free(void)
{
    if (initialized)
        initialized = false;

        // cleanup code
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
