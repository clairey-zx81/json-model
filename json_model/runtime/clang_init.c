static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
CODE_BLOCK
    }
    return NULL;
}
