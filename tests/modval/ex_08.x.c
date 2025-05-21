#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[5];
const size_t check_model_map_size = 5;

// check $VAL ($.'$VAL')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$VAL'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$VAL']", path);
    }
    return res;
}

// check $KEY ($.'$KEY')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$KEY'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$KEY']", path);
    }
    return res;
}

// object $.'$map'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$map']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle {len(defs)} key props
            // $.'$map'.'$URL'
            res = json_model_2(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $VAL [$.'$map'.'$URL']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$map']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $map ($.'$map')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$map'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$map']", path);
    }
    return res;
}

// check $EX08 ($.'$EX08')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$EX08'
    // $.'$EX08'.'|'.0
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $map [$.'$EX08'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$EX08'.'|'.1
        res = jm_is_valid_url(json_string_value(val));
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$EX08'.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$EX08'.'|'.2
            res = json_model_2(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $VAL [$.'$EX08'.'|'.2]", path);
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$EX08'.'|']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $EX08 [$]", path);
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
        check_model_map_tab[1] = (propmap_t) { "VAL", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "KEY", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "map", json_model_4 };
        check_model_map_tab[4] = (propmap_t) { "EX08", json_model_5 };
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
