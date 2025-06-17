static bool initialized = false;

const char *CHECK_FUNCTION_NAME_init(void)
{
    if (!initialized)
    {
        initialized = true;
CODE_BLOCK
    }
    return NULL;
}
