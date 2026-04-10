
// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2"

static bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep);
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

static INLINE bool _jm_re_0(const char *s, jm_path_t *path, jm_report_t *rep)
{
    if (unlikely(!isalpha(*s++)))
        return false;
    while (likely(isalpha(*s)))
        s++;
    return *s == '\0';
}

static INLINE bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (unlikely(! json_is_object(val)))
        return false;
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        if (likely(_jm_re_0(prop, NULL, NULL)))
        {
            res = json_is_string(pval) && jm_str_eq_3(json_string_value(pval), 0x00616c62);
            if (unlikely(! res))
                return false;
        }
        else
            return false;
    }
    return true;
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
            res = json_is_string(arr_0_item) && jm_str_eq_3(json_string_value(arr_0_item), 0x006f6f66);
            if (unlikely(! res))
                break;
        }
    }
    return res || _jm_obj_0(val, NULL, NULL);
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 1);
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
