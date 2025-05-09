#include <stdio.h>

int main(int argc, char * argv[])
{
  int errors = 0;
  // fprintf(stderr, "version %s\n", JANSSON_VERSION);

  for (int i = 1; i < argc; i++)
  {
    json_error_t error;
    json_t *value = json_load_file(argv[i], JSON_DECODE_ANY|JSON_ALLOW_NUL, &error);
    if (value == NULL)
    {
      errors++;
      fprintf(stdout, "%s: FILE READ ERROR (%s at %d:%d)\n",
              argv[i], error.text, error.line, error.column);
      continue;
    }
    if (check_model(value, NULL, NULL))
      fprintf(stdout, "%s: PASS\n", argv[i]);
    else
      fprintf(stdout, "%s: FAIL\n", argv[i]);
  }

  return errors? 1: 0;
}
