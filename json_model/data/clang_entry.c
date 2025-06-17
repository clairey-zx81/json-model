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
CHECK_FUNCTION_NAME(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(CHECK_FUNCTION_NAME_init, CHECK_FUNCTION_NAME_map, val, name, error, reasons);
}
