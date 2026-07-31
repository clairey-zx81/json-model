
#include <json-model.h>
#define JSON_MODEL_VERSION "2"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res = json_is_array(val);
    if (likely(res))
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            res = json_is_integer(arr_0_item) && json_integer_value(arr_0_item) >= 0;
            if (unlikely(! res))
                break;
        }
    }
    if (likely(res))
        res = jm_int_array_is_unique(val, NULL, NULL);
    return res;
}

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (unlikely(! json_is_object(val)))
        return false;
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        uint32_t hash_0 = (*((uint32_t *) (prop))) & 0xffff;
        if (hash_0 <= 0x6c70)
        {
            if (jm_str_eq_7(prop, 0x0000616d65686373LL))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_3(prop, 0x00006c70))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_5(prop, 0x000000006176616aLL))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_2(prop, 0x00000063))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
        }
        else
        {
            if (jm_str_eq_6(prop, 0x00000079706e7964LL))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_3(prop, 0x0000736a))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_4(prop, 0x006c7173))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_3(prop, 0x00007970))
            {
                res = json_model_2(pval, NULL, NULL);
                if (unlikely(! res))
                    return false;
                continue;
            }
            else if (jm_str_eq_3(prop, 0x00007374))
            {
                res = json_is_boolean(pval);
                if (unlikely(! res))
                    return false;
                continue;
            }
        }
        if (likely(jm_str_eq_1(prop, 0x23)))
        {
            res = json_is_string(pval);
            if (unlikely(! res))
                return false;
        }
        else
            return false;
    }
    return true;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 2);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "ErrorIndex", json_model_2 };
        jm_sort_propmap(check_model_map_tab, 2);
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
