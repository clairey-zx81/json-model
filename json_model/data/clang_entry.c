/* entry function, function name is expected to be substituted */

check_fun_t CHECK_FUNCTION_NAME_fun(const char* name)
{
    // lazy init
    CHECK_FUNCTION_NAME_init();
    return check_prop_find(name, _check_model_map, array_length(_check_model_map));
}

bool CHECK_FUNCTION_NAME(json_t* val, const char* name, Report* rep, bool* error)
{
    check_fun_t checker = CHECK_FUNCTION_NAME_fun(name);
    Path root = (Path) { "$", 0, NULL };
    *error = checker == NULL;
    if (*error)
    {
        // TODO report on error: "unexpected model name: %s\n"
        return false;
    }
    // no path collection if no report
    return checker(val, rep ? &root : NULL, rep);
}
