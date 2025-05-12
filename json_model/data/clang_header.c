#include <string.h>
#include <stdlib.h>
#include <jansson.h>

#define array_length(arr) (sizeof(arr) / sizeof((arr)[0]))
typedef enum { false, true } bool;

/* check function types */
typedef void Report;

typedef struct Path {
    const char* name;
    int64_t index;
    struct Path* next;
} Path;

typedef bool (*check_fun_t)(const json_t *, Path *, Report *);

/* property mapping management */
typedef int (*cmp_fun_t)(const void *, const void *);

typedef struct {
    const char* name;
    check_fun_t val_check;
} check_prop_t;

static bool initialized = false;

static void CHECK_FUNCTION_NAME_init(void);
check_fun_t CHECK_FUNCTION_NAME_fun(const char* name);
bool CHECK_FUNCTION_NAME(json_t* val, const char* name, Report* rep, bool* error);

static int prop_cmp(const check_prop_t *e1, const check_prop_t *e2)
{
    return strcmp(e1->name, e2->name);
}

static check_fun_t
check_prop_find(const char *name, const check_prop_t *props, int nprops)
{
    check_prop_t searched = (check_prop_t) { name, NULL };
    check_prop_t *entry = (check_prop_t *)
        bsearch(&searched, props, nprops, sizeof(check_prop_t), (cmp_fun_t) prop_cmp);
    return entry ? entry->val_check : NULL;
}
