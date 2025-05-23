#ifndef JSON_MODEL_H_INCLUDED
#define JSON_MODEL_H_INCLUDED

#define _GNU_SOURCE  // for qsort_r?
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include <jansson.h>

/*
 * build generated API names
 */
#ifndef CHECK_FUNCTION_NAME
#warning defining CHECK_FUNCTION_NAME macro
#define CHECK_FUNCTION_NAME check_model
#endif  // !CHECK_FUNCTION_NAME

#define concat(prefix, suffix) prefix ## suffix
#define newname(prefix, suffix) concat(prefix, suffix)

#define CHECK_map_size newname(CHECK_FUNCTION_NAME, _map_size)
#define CHECK_map_tab newname(CHECK_FUNCTION_NAME, _map_tab)
#define CHECK_fun newname(CHECK_FUNCTION_NAME, _map)
#define CHECK_init newname(CHECK_FUNCTION_NAME, _init)
#define CHECK CHECK_FUNCTION_NAME
#define CHECK_free newname(CHECK_FUNCTION_NAME, _free)

// set on init
extern char * jm_version_string;

#define array_length(arr) (sizeof(arr) / sizeof((arr)[0]))
typedef enum { false, true } bool;
typedef int (*cmp_fun_t)(const void *, const void *);
typedef int (*cmp_r_fun_t)(const void *, const void *, void *);

/*
 * JSON API extensions
 */

// keep object prop/vals as an array for sorting and fast get.
typedef struct {
    const char *prop;
    const json_t *val;
} json_propval_t;

extern bool _json_is_scalar(const json_t *);
extern int _json_cmp(const json_t *, const json_t *);
extern int _json_array_cmp(const json_t *, const json_t *);
extern int _json_object_cmp(const json_t *, const json_t *);
extern int _json_propval_cmp(const json_propval_t *, const json_propval_t *);
extern bool _json_array_unique(const json_t *);

/*
 * reporting
 */
// linked list of report entries
typedef struct ReportEntry {
  const char *message;
  char *path;
  struct ReportEntry *prev;
} ReportEntry;

typedef struct Report {
  ReportEntry *entry;
} Report;

// path segment, name == NULL means use index
typedef struct Path {
    const char *name;
    size_t index;
    struct Path *prev;  // link to previous (in stack) segment
    struct Path *next;  // used for backtacking
} Path;

extern void jm_report_add_entry(Report* rep, const char *msg, Path *path);
extern void jm_report_free_entries(Report *rep);

typedef bool (*check_fun_t)(const json_t *, Path *, Report *);

extern bool jm_check_fun_string(check_fun_t, const char *, Path *, Report *);
extern bool jm_array_is_unique(const json_t *, Path *, Report *);

/*
 * property mapping management
 */
typedef struct {
    const char *name;
    check_fun_t val_check;
} propmap_t;

extern void jm_sort_propmap(propmap_t *, int);
extern check_fun_t jm_search_propmap(const char *, const propmap_t *, int);

/*
 * set of scalar constants
 */
typedef enum {
    cst_is_null,
    cst_is_bool,
    cst_is_integer,
    cst_is_float,
    cst_is_string
    // cst_is_array + const json_t * + free
    // cst_is_object + const json_t * + free
} constant_tag;

typedef struct
{
    constant_tag tag;
    union {
        bool b;
        int64_t i;
        double f;
        const char *s;
    } val;
} constant_t;

extern bool jm_set_cst(constant_t *, const json_t *);
extern void jm_dbg_cst(const constant_t *, const char *);
extern void jm_sort_cst(constant_t *, size_t);
extern bool jm_search_cst(const constant_t *, const constant_t *, size_t);

/*
 * constant mapping management for discriminant optimization
 */
typedef struct {
    constant_t cst;
    check_fun_t check_val;
} constmap_t;

extern void jm_sort_constmap(constmap_t *, size_t);
extern check_fun_t jm_search_constmap(const constant_t *, const constmap_t *, size_t);

/*
 * Miscellaneous support functions and related data
 */
extern bool jm_is_valid_date(const char *);
extern pcre2_code *jm_is_valid_uuid_code;
extern pcre2_match_data *jm_is_valid_uuid_data;
extern bool jm_is_valid_uuid(const char *);
extern size_t jm_any_len(json_t *);
extern bool jm_is_valid_regex(const char *);
extern bool jm_is_valid_url(const char *);

typedef enum {
    op_eq,
    op_ne,
    op_le,
    op_lt,
    op_ge,
    op_gt
} constraint_op_t;

extern bool
jm_check_constraint(const json_t *, constraint_op_t, const constant_t *, Path *, Report *);

/*
 * Shared high-level entry point
 */
extern bool jm_generic_entry(char *(*)(void), check_fun_t (*)(const char *),
                             json_t *, const char *, bool *, char **);

/*
 * Generated stuff
 */
// low-level interface
extern const size_t CHECK_map_size;
extern propmap_t CHECK_map_tab[];
extern check_fun_t CHECK_fun(const char *);
// high-level interface
extern char *CHECK_init(void);
extern bool CHECK(json_t *, const char *, bool *, char **);
extern void CHECK_free(void);

#endif  // JSON_MODEL_H_INCLUDED
