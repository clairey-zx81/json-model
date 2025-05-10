#include <string.h>
#include <stdlib.h>
#include <jansson.h>

typedef enum { false, true } bool;
typedef char * string;
typedef void Path;
typedef void Report;
typedef bool (*check_fun_t)(const json_t *, Path *, Report *);
typedef int (*cmp_fun_t)(const void *, const void *);

static bool initialized = false;
static void initialize(void);
