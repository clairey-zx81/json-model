#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// check $ex5 ($.'$ex5')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5'
    // $.'$ex5'.'|'.0
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX05a [$.'$ex5'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$ex5'.'|'.1
        res = json_model_6(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $EX05b [$.'$ex5'.'|'.1]", path);
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$ex5'.'|']", path);
    }
    return res;
}

// check $EX06 ($.'$EX06')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$EX06'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$EX06']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val) && json_array_size(val) == 3;
    if (res)
    {
        Path lpath_0 = (Path) { NULL, 0, path, NULL };
        // $.0
        res = json_model_5(json_array_get(val, 0), path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05a [$.0]", (path ? &lpath_0 : NULL));
        }
        if (res)
        {
            Path lpath_0 = (Path) { NULL, 1, path, NULL };
            // $.1
            res = json_model_6(json_array_get(val, 1), path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ex5#EX05b [$.1]", (path ? &lpath_0 : NULL));
            }
            if (res)
            {
                Path lpath_0 = (Path) { NULL, 2, path, NULL };
                // $.2
                res = json_model_3(json_array_get(val, 2), path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $EX06 [$.2]", (path ? &lpath_0 : NULL));
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

// check $ex5#EX05a ($.'$ex5#EX05a')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05a'
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 int [$.'$ex5#EX05a']", path);
    }
    return res;
}

// check $ex5#EX05b ($.'$ex5#EX05b')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$ex5#EX05b'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$ex5#EX05b']", path);
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
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "ex5", json_model_4 };
        check_model_map_tab[2] = (propmap_t) { "EX06", json_model_3 };
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
