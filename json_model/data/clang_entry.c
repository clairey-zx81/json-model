/* entry function name is expected to be substituted */

check_fun_t CHECK_FUNCTION_NAME_fun(const char *name)
{
    return check_prop_find(name, _check_model_map, array_length(_check_model_map));
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
 * if the model is not found, error
 *
 */
bool CHECK_FUNCTION_NAME(json_t *val, const char *name, bool *error, char **reasons)
{
    CHECK_FUNCTION_NAME_init();  // lazy
    check_fun_t checker = CHECK_FUNCTION_NAME_fun(name);

    *error = checker == NULL;

    if (*error)
    {
        if (reasons)
        {
            const char *format = "model checking function not found for <%s>\n";
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

    if (reasons)
        report_free_entries(&report);

    return valid;
}
