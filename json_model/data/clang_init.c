char *CHECK_FUNCTION_NAME_init(void)
{
    if (!initialized)
    {
        initialized = true;

        // silent gcc warnings about unused functions
        (void) search_propmap;
        (void) sort_propmap;
        (void) search_constmap;
        (void) sort_constmap;
        (void) search_cst;
        (void) sort_cst;
        (void) dbg_cst;
        (void) set_cst;
        (void) _json_array_unique;
        (void) _json_is_scalar;

        // other initializations
CODE_BLOCK
    }
    return NULL;
}
