static size_t _any_len(json_t *val)
{
  if (json_is_object(val))
    return json_object_size(val)
  else if (json_is_array(val))
    return json_array_size(val)
  else if (json_is_string(var))
    return mbstowcs(NULL, json_string_value(val), 0);
}
