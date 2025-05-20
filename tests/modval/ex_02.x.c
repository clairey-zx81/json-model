#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

// check $x1 ($.'$x1')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x1'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x1']", path);
    }
    return res;
}

// check $x2 ($.'$x2')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x2'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x2']", path);
    }
    return res;
}

// check $x3 ($.'$x3')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$x3'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$x3']", path);
    }
    return res;
}

// check $__external_0 ($.'$__external_0')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$__external_0'
    res = json_is_string(val) && strcmp(json_string_value(val), "Susie") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.'$__external_0']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val) && json_array_size(val) == 4;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.0
        res = json_is_string(json_array_get(val, 0)) && strcmp(json_string_value(json_array_get(val, 0)), "Susie") == 0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.1
            res = json_is_string(json_array_get(val, 1)) && strcmp(json_string_value(json_array_get(val, 1)), "Susie") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                Path lpath_0 = (Path) { NULL, 2, path, NULL };
                // $.2
                res = json_is_string(json_array_get(val, 2)) && strcmp(json_string_value(json_array_get(val, 2)), "Susie") == 0;
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.2]", (path ? &lpath_0 : NULL));
                }
                if (res)
                {
                    Path lpath_0 = (Path) { NULL, 3, path, NULL };
                    // $.3
                    res = json_is_string(json_array_get(val, 3)) && strcmp(json_string_value(json_array_get(val, 3)), "Susie") == 0;
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected _Susie [$.3]", (path ? &lpath_0 : NULL));
                    }
                }
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$]", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 5);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "x1", json_model_5 };
        check_model_map_tab[2] = (propmap_t) { "x2", json_model_6 };
        check_model_map_tab[3] = (propmap_t) { "x3", json_model_7 };
        check_model_map_tab[4] = (propmap_t) { "__external_0", json_model_8 };
        jm_sort_propmap(check_model_map_tab, 5);
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
    check_fun_t checker = CHECK_fun(name);

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
