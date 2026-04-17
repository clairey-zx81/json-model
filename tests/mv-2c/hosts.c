
// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2"

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;
static cre2_regexp_t *jm_is_host_re2 = NULL;
static int jm_is_host_nn = 0;
static bool jm_is_host(const char *s, jm_path_t *path, jm_report_t *rep);
static cre2_regexp_t *jm_is_ip4_re2 = NULL;
static int jm_is_ip4_nn = 0;
static bool jm_is_ip4(const char *s, jm_path_t *path, jm_report_t *rep);
static cre2_regexp_t *jm_is_ip6_re2 = NULL;
static int jm_is_ip6_nn = 0;
static bool jm_is_ip6(const char *s, jm_path_t *path, jm_report_t *rep);

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (unlikely(! json_is_object(val)))
        return false;
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        if (unlikely(jm_str_eq_5(prop, 0x0000000034767069LL)))
        {
            res = json_is_string(pval) && jm_is_ip4(json_string_value(pval), NULL, NULL);
            if (unlikely(! res))
                return false;
            continue;
        }
        else if (unlikely(jm_str_eq_5(prop, 0x0000000036767069LL)))
        {
            res = json_is_string(pval) && jm_is_ip6(json_string_value(pval), NULL, NULL);
            if (unlikely(! res))
                return false;
            continue;
        }
        else if (jm_str_eq_5(prop, 0x0000000074736f68LL))
        {
            res = json_is_string(pval) && jm_is_host(json_string_value(pval), NULL, NULL) && jm_str_len(json_string_value(pval)) <= 255;
            if (unlikely(! res))
                return false;
            continue;
        }
        else if (likely(jm_str_eq_4(prop, 0x00687465)))
        {
            res = jm_is_valid_eth(json_string_value(pval), NULL, NULL);
            if (unlikely(! res))
                return false;
            continue;
        }
        return false;
    }
    return true;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool jm_is_host(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(jm_is_host_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}

static bool jm_is_ip4(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(jm_is_ip4_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}

static bool jm_is_ip6(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(jm_is_ip6_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
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
        jm_is_host_re2 = cre2_new("(?i)^([a-z0-9][-a-z0-9]{0,62})(\\.([a-z0-9][-a-z0-9]{0,62}))*$", strlen("(?i)^([a-z0-9][-a-z0-9]{0,62})(\\.([a-z0-9][-a-z0-9]{0,62}))*$"), NULL);
        if (cre2_error_code(jm_is_host_re2))
            return cre2_error_string(jm_is_host_re2);
        jm_is_host_nn = cre2_num_capturing_groups(jm_is_host_re2) + 1;
        jm_is_ip4_re2 = cre2_new("^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$", strlen("^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$"), NULL);
        if (cre2_error_code(jm_is_ip4_re2))
            return cre2_error_string(jm_is_ip4_re2);
        jm_is_ip4_nn = cre2_num_capturing_groups(jm_is_ip4_re2) + 1;
        jm_is_ip6_re2 = cre2_new("(?i)^(([0-9a-f]{1,4}:){7}[0-9a-f]{1,4}|([0-9a-f]{1,4}:){1,7}:|([0-9a-f]{1,4}:){1,6}(:[0-9a-f]{1,4}){1}|([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|[0-9a-f]{1,4}:(:[0-9a-f]{1,4}){1,6}|:(:[0-9a-f]{1,4}){1,7}|::)$", strlen("(?i)^(([0-9a-f]{1,4}:){7}[0-9a-f]{1,4}|([0-9a-f]{1,4}:){1,7}:|([0-9a-f]{1,4}:){1,6}(:[0-9a-f]{1,4}){1}|([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|[0-9a-f]{1,4}:(:[0-9a-f]{1,4}){1,6}|:(:[0-9a-f]{1,4}){1,7}|::)$"), NULL);
        if (cre2_error_code(jm_is_ip6_re2))
            return cre2_error_string(jm_is_ip6_re2);
        jm_is_ip6_nn = cre2_num_capturing_groups(jm_is_ip6_re2) + 1;
    }
    return NULL;
}

void check_model_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
        cre2_delete(jm_is_host_re2);
        jm_is_host_re2 = NULL;
        jm_is_host_nn = 0;
        cre2_delete(jm_is_ip4_re2);
        jm_is_ip4_re2 = NULL;
        jm_is_ip4_nn = 0;
        cre2_delete(jm_is_ip6_re2);
        jm_is_ip6_re2 = NULL;
        jm_is_ip6_nn = 0;
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
