#ifndef JSON_MODEL_H_INCLUDED
#define JSON_MODEL_H_INCLUDED

#define _GNU_SOURCE  // for qsort_r?
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <jansson.h>

/*
 * build generated API names
 */
#ifndef CHECK_FUNCTION_NAME
#warning defining CHECK_FUNCTION_NAME macro
#define CHECK_FUNCTION_NAME check_model
#endif  // !CHECK_FUNCTION_NAME

// branch hints
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

// inlining hints
#if defined(NO_INLINE_HINT)
#define INLINE
#else
#if defined(__clang__)
#define INLINE __attribute__((always_inline))
#elif defined(__GNUC__)
#define INLINE inline
// #elif defined(_MSC_VER)
#else
#define INLINE
#endif  // clang/gcc/...
#endif  // NO_INLINE_HINT

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
typedef int (*jm_cmp_fun_t)(const void *, const void *);

/*
 * JSON API extensions
 */

// keep object prop/vals as an array for sorting and fast get.
typedef struct {
    const char *prop;
    const json_t *val;
} jm_propval_t;

extern int jm_propval_cmp(const jm_propval_t *, const jm_propval_t *);

extern bool jm_json_is_scalar(const json_t *);
extern int jm_json_cmp(const json_t *, const json_t *);
extern int jm_json_array_cmp(const json_t *, const json_t *);
extern int jm_json_object_cmp(const json_t *, const json_t *);
extern bool jm_json_array_unique(const json_t *);

/*
 * reporting
 */
// linked list of report entries
typedef struct jm_report_entry {
  const char *message;
  char *path;
  struct jm_report_entry *prev;
} jm_report_entry_t;

typedef struct {
  jm_report_entry_t *entry;
} jm_report_t;

// path segment, name == NULL means use index
typedef struct jm_path {
    const char *name;
    size_t index;
    struct jm_path *prev;  // link to previous (in stack) segment
    struct jm_path *next;  // used for backtacking
} jm_path_t;

extern void jm_report_add_entry(jm_report_t* rep, const char *msg, jm_path_t *path);
extern void jm_report_free_entries(jm_report_t *rep);

typedef bool (*jm_check_fun_t)(const json_t *, jm_path_t *, jm_report_t *);

extern bool jm_check_fun_string(jm_check_fun_t, const char *, jm_path_t *, jm_report_t *);
extern bool jm_array_is_unique(const json_t *, jm_path_t *, jm_report_t *);

/*
 * property mapping management
 */
typedef struct {
    const char *name;
    jm_check_fun_t val_check;
} jm_propmap_t;

extern void jm_sort_propmap(jm_propmap_t *, int);
extern jm_check_fun_t jm_search_propmap(const char *, const jm_propmap_t *, int);

/*
 * set of scalar constants
 */
typedef enum {
    cst_is_null = -4,
    cst_is_bool = -3,
    cst_is_integer = -2,
    cst_is_float = -1
    // cst_is_string = 1 > 0 => string length, including trailing null
    // cst_is_array + const json_t * + free
    // cst_is_object + const json_t * + free
} jm_constant_tag;

typedef struct
{
    jm_constant_tag tag;
    union {
        bool b;
        int64_t i;
        double f;
        const char *s;
    } val;
} jm_constant_t;

extern bool jm_set_cst(jm_constant_t *, const json_t *);
extern void jm_dbg_cst(const jm_constant_t *, const char *);
extern void jm_sort_cst(jm_constant_t *, size_t);
extern bool jm_search_cst(const jm_constant_t *, const jm_constant_t *, size_t);

/*
 * constant mapping management for discriminant optimization
 */
typedef struct {
    jm_constant_t cst;
    jm_check_fun_t check_val;
} jm_constmap_t;

extern void jm_sort_constmap(jm_constmap_t *, size_t);
extern jm_check_fun_t jm_search_constmap(const jm_constant_t *, const jm_constmap_t *, size_t);

/*
 * Miscellaneous support functions and related data
 */
extern bool jm_is_valid_date_slow(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_date_fast(const char *, jm_path_t *, jm_report_t *);
extern bool (*jm_is_valid_date)(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_time(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_datetime(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_uuid(const char *, jm_path_t *, jm_report_t *);
extern size_t jm_str_len(const char *);
extern size_t jm_any_len(json_t *);
extern bool jm_is_valid_regex_slow(const char *, bool, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_regex_fast(const char *, bool, jm_path_t *, jm_report_t *);
extern bool (*jm_is_valid_regex)(const char *, bool, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_url(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_email(const char *, jm_path_t *, jm_report_t *);
extern bool jm_is_valid_json(const char *, jm_path_t *, jm_report_t *);

typedef enum {
    op_eq,
    op_ne,
    op_le,
    op_lt,
    op_ge,
    op_gt
} jm_constraint_op_t;

extern bool
jm_check_constraint(const json_t *, jm_constraint_op_t, const jm_constant_t *,
                    jm_path_t *, jm_report_t *);

/*
 * Variable to constant string comparison depending on known length.
 */
#define jm_str_eq(s1, s2) (strcmp(s1, s2) == 0)
#define jm_str_ne(s1, s2) (strcmp(s1, s2) != 0)

#define jm_i4(s) (*(uint32_t *)(s))
#define jm_i8(s) (*(uint64_t *)(s))

// byte masks
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#  define jm_B1 0x000000ff
#  define jm_B2 0x0000ffff
#  define jm_B3 0x00ffffff
#  define jm_B5 0x000000ffffffffffLL
#  define jm_B6 0x0000ffffffffffffLL
#  define jm_B7 0x00ffffffffffffffLL
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  define jm_B1 0xff000000
#  define jm_B2 0xffff0000
#  define jm_B3 0xffffff00
#  define jm_B5 0xffffffffff000000LL
#  define jm_B6 0xffffffffffff0000LL
#  define jm_B7 0xffffffffffffff00LL
#else
#  error FIXME unhandled byte order
#endif

// known size (number of null-terminated bytes) string comparisons
#define jm_str_eq_0(s) ((*(s)) == '\0')
#define jm_str_eq_1(s, c) ((*(s)) == ((uint8_t) (c)))
#define jm_str_eq_2(s, c) ((jm_i4(s) & jm_B2) == (c))
#define jm_str_eq_3(s, c) ((jm_i4(s) & jm_B3) == (c))
#define jm_str_eq_4(s, c) (jm_i4(s) == (c))
#define jm_str_eq_5(s, c) ((jm_i8(s) & jm_B5) == (c))
#define jm_str_eq_6(s, c) ((jm_i8(s) & jm_B6) == (c))
#define jm_str_eq_7(s, c) ((jm_i8(s) & jm_B7) == (c))
#define jm_str_eq_8(s, c) (jm_i8(s) == (c))

#define jm_str_ne_0(s) ((*(s)) != '\0')
#define jm_str_ne_1(s, c) ((*(s)) != ((uint8_t) (c)))
#define jm_str_ne_2(s, c) ((jm_i4(s) & jm_B2) != (c))
#define jm_str_ne_3(s, c) ((jm_i4(s) & jm_B3) != (c))
#define jm_str_ne_4(s, c) (jm_i4(s) != (c))
#define jm_str_ne_5(s, c) ((jm_i8(s) & jm_B5) != (c))
#define jm_str_ne_6(s, c) ((jm_i8(s) & jm_B6) != (c))
#define jm_str_ne_7(s, c) ((jm_i8(s) & jm_B7) != (c))
#define jm_str_ne_8(s, c) (jm_i8(s) != (c))
/*
 * Shared high-level entry point
 */
extern bool jm_generic_entry(const char *(*)(void), jm_check_fun_t (*)(const char *),
                             const json_t *, const char *, bool *, char **);

/*
 * Generated stuff
 */
// low-level interface
extern const size_t CHECK_map_size;
extern jm_propmap_t CHECK_map_tab[];
extern jm_check_fun_t CHECK_fun(const char *);
// high-level interface
extern const char *CHECK_init(void);
extern bool CHECK(const json_t *, const char *, bool *, char **);
extern void CHECK_free(void);

#endif  // JSON_MODEL_H_INCLUDED
