#include <string.h>
#include <stdlib.h>
#include <jansson.h>

typedef enum { false, true } bool;
typedef char *string;
typedef void Path;
typedef void Report;
typedef bool (*check_fun_t)(json_t *, Path *, Report *);

/*
typedef enum {
  PROP_MUST,
  PROP_MAY,
  PROP_REGEX,
  PROP_REF,
  PROP_ALL
} prop_type_t;

typedef struct {
  string property;
  key_check check_fun_t;
  val_check check_fun_t;
  type prop_type_t;
} check_prop_t;

static check_prop_t *
check_prop_find(const string name, const check_prop_t *props, int nprops)
{
  for (int i = 0; i < nprops; i++)
    if (strcmp(props[i].name, name) == 0)
      return &props[i]
  return NULL;
}
*/
