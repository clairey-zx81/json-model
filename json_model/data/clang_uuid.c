static pcre2_code *_is_valid_uuid_code = NULL;
static pcre2_match_data *_is_valid_uuid_data = NULL;

static bool _is_valid_uuid(const char *s)
{
  int rc = pcre2_match(_is_valid_uuid_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _is_valid_uuid_data, NULL);
  return rc >= 0;
}
