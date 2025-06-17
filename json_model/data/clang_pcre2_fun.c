static bool FUNCTION_NAME(const char *s, jm_path_t *path, jm_report_t *rep)
{
    int rc = pcre2_match(FUNCTION_NAME_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                         0, 0, FUNCTION_NAME_data, NULL);
    return rc >= 0;
}
