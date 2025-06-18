static bool FUNCTION_NAME(const char *s, jm_path_t *path, jm_report_t *rep)
{
    size_t slen = strlen(s);
    return cre2_match(FUNCTION_NAME_re2, s, slen, 0, slen, CRE2_UNANCHORED, NULL, 0);
}
