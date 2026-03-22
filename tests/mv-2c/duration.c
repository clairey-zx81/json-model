
// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2"

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;
static cre2_regexp_t *jm_is_duration_re2 = NULL;
static int jm_is_duration_nn = 0;
static bool jm_is_duration(const char *s, jm_path_t *path, jm_report_t *rep);

static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    return json_is_string(val) && jm_is_duration(json_string_value(val), NULL, NULL);
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool jm_is_duration(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(jm_is_duration_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
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
        jm_is_duration_re2 = cre2_new("^P(([0-9]+D|[0-9]+M([0-9]+D)?|[0-9]+Y([0-9]+M([0-9]+D)?)?)(T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S))?|T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S)|[0-9]+W)$", strlen("^P(([0-9]+D|[0-9]+M([0-9]+D)?|[0-9]+Y([0-9]+M([0-9]+D)?)?)(T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S))?|T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S)|[0-9]+W)$"), NULL);
        if (cre2_error_code(jm_is_duration_re2))
            return cre2_error_string(jm_is_duration_re2);
        jm_is_duration_nn = cre2_num_capturing_groups(jm_is_duration_re2) + 1;
    }
    return NULL;
}

void check_model_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
        cre2_delete(jm_is_duration_re2);
        jm_is_duration_re2 = NULL;
        jm_is_duration_nn = 0;
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
