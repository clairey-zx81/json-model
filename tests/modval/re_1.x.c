#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static propmap_t jm_check_model_map_tab[1];

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    // "/^S/i"
    res = json_is_string(val) && _jm_re_0(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [$]", path);
    }
    return res;
}

static check_fun_t jm_check_model_map(const char *pname)
{
    return jm_search_propmap(pname, jm_check_model_map_tab, 1);
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
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "(?i)^S", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        jm_check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        jm_sort_propmap(jm_check_model_map_tab, 1);
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


check_fun_t
CHECK_fun(const char *name)
{
    return jm_check_model_map(name);
}

/*
 * API: bool check_model(json_t *, const char *, bool *, char **);
 *
 * valid = check(value, "model-name", &error, &message);
 *
 * - error is set of there was an error during initialization or if the model does not exists.
 * - message is provided if a non NULL pointer is passed, and must be freed by the caller.
 *
 *
 * if the model is not found, report error and reasons if required, else coldly exit.
 */
bool
CHECK(json_t *val, const char *name, bool *error, char **reasons)
{
    CHECK_init();  // lazy
    check_fun_t checker = jm_check_model_map(name);

    bool not_found = checker == NULL;
    if (error)
        *error = not_found;

    if (not_found)
    {
        const char *format = "JSON Model check function not found for <%s>\n";

        if (!error)
        {
            fprintf(stderr, format, name);
            exit(1);
        }

        if (reasons)
        {
            size_t size = strlen(format) + strlen(name);
            char *message = malloc(size);
            sprintf(message, format, name);
            *reasons = message;
        }

        return false;
    }

    Path root = (Path) { "$", 0, NULL, NULL };
    Report report = (Report) { NULL };

    bool valid = checker(val, reasons ? &root : NULL, reasons ? &report : NULL);

    // generate explanations if a report is required and the value failed to validate
    if  (reasons && report.entry && !valid)
    {
        size_t size = 1;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            size += strlen(entry->message) + strlen(entry->path) + 3;

        char *message = malloc(size);
        *reasons = message;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            message += sprintf("%s: %s\n", entry->path, entry->message);
    }

    jm_report_free_entries(&report);

    return valid;
}
