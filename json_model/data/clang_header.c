#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <jansson.h>

#define array_length(arr) (sizeof(arr) / sizeof((arr)[0]))
typedef enum { false, true } bool;
typedef int (*cmp_fun_t)(const void *, const void *);

/*
 * JSON API extensions
 */
static bool _json_is_scalar(const json_t *val)
{
    const json_type tval = json_typeof(val);
    return (tval == JSON_STRING || tval == JSON_INTEGER || tval == JSON_REAL ||
            tval == JSON_TRUE || tval == JSON_FALSE || tval == JSON_NULL);
}

static int _json_cmp(const json_t *, const json_t *);

// fast JSON array comparison for a total order
static int _json_array_cmp(const json_t *v1, const json_t *v2)
{
    // try size
    size_t s1 = json_array_size(v1), s2 = json_array_size(v2);
    if (s1 != s2)
        return s2 - s1;
    // else same size, use lexicographic order: first diff concludes the comparison
    size_t index;
    json_t *iv1;
    json_array_foreach(v1, index, iv1)
    {
        json_t *iv2 = json_array_get(v2, index);
        int cmp = _json_cmp(iv1, iv2);
        if (cmp != 0)
            return cmp;
    }
    // no difference found
    return 0;
}

// keep object prop/vals as an array for sorting and fast get.
typedef struct {
    const char *prop;
    const json_t *val;
} json_propval_t;

// for sorting propvals by property names
static int _json_propval_cmp(const json_propval_t *pv1, const json_propval_t *pv2)
{
    return strcmp(pv1->prop, pv2->prop);
}

// fast (size ln(size)) JSON object comparison for a total order
static int _json_object_cmp(const json_t *v1, const json_t *v2)
{
    // try size
    size_t s1 = json_object_size(v1), s2 = json_object_size(v2);
    if (s1 != s2)
        return s2 - s1;
    // else same size, try by sorted keys
    json_propval_t pv1[s1], pv2[2];
    const char *key;
    json_t *value;
    size_t index = 0;
    json_object_foreach((json_t *) v1, key, value)
        pv1[index++] = (json_propval_t) { key, value };
    qsort(pv1, s1, sizeof(json_propval_t), (cmp_fun_t) _json_propval_cmp);
    index = 0;
    json_object_foreach((json_t *) v2, key, value)
        pv2[index++] = (json_propval_t) { key, value };
    qsort(pv2, s2, sizeof(json_propval_t), (cmp_fun_t) _json_propval_cmp);
    // first, lexicographic order of keys
    for (int i = 0; i < s1; i++)
    {
        int cmp = strcmp(pv1[i].prop, pv2[i].prop);
        if (cmp != 0)
            return cmp;
    }
    // same keys, try lexicographic order of values
    for (int i = 0; i < s1; i++)
    {
        int cmp = _json_cmp(pv1[i].val, pv2[i].val);
        if (cmp != 0)
            return cmp;
    }
    // same values
    return 0;
}

static int _json_cmp(const json_t *v1, const json_t *v2)
{
    const json_type t1 = json_typeof(v1), t2 = json_typeof(v2);
    if (t1 != t2)
        return t1 - t2;  // intentionally inverted to have scalars ahead

    // else same type
    switch (t1)
    {
        case JSON_NULL:
        case JSON_FALSE:
        case JSON_TRUE:
            return 0;
        case JSON_INTEGER:
            int64_t i1 = json_integer_value(v1), i2 = json_integer_value(v2);
            return i1 < i2 ? -1 : i1 == i2 ? 0 : 1;
        case JSON_REAL:
            double r1 = json_real_value(v1), r2 = json_real_value(v2);
            return r1 < r2 ? -1 : r1 == r2 ? 0 : 1;
        case JSON_STRING:
            return strcmp(json_string_value(v1), json_string_value(v2));
        case JSON_ARRAY:
            return _json_array_cmp(v1, v2);
        case JSON_OBJECT:
            return _json_object_cmp(v1, v2);
    }

    // default: panic, internal error
    assert(false);
    return 0;
}

// fast version which stops comparing once a duplicate has been seen:
// hopefully an optimized qsort implementation can use this to return early.
static int _json_cmp_r(const json_t *v1, const json_t *v2, void *duplicate)
{
    if (*((bool *) duplicate))
        return 0;
    int cmp = _json_cmp(v1, v2);
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

static bool _json_array_unique(const json_t *val)
{
    assert(json_is_array(val));
    // extract as an actual array for sorting
    size_t size = json_array_size(val);
    const json_t *array[size];
    for (size_t i = 0; i < size; i++)
        array[i] = json_array_get(val, i);
    bool duplicate = false;
    qsort_r(array, size, sizeof(json_t *), (cmp_fun_t) _json_cmp_r, &duplicate);
    return !duplicate;
}

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

static void report_add_entry(Report* rep, const char *msg, Path *path)
{
    ReportEntry *entry = malloc(sizeof(ReportEntry));
    *entry = (ReportEntry) { msg, NULL, rep->entry };
    rep->entry = entry;
    if (path)
    {
        // path segments are stored in reverse order
        size_t size = 1;
        Path *current = path;
        Path *next = NULL;
        // dive to compute the path length and build the back path
        while (current != NULL)
        {
            // "." name or "." number
            size += 1 + (current->name ? strlen(current->name) : (3 * sizeof(size_t)));
            Path *prev = current->prev;
            current->next = next;  // needed to backtrack
            next = current;  // future next
            current = prev;
        }
        // allocate path
        char *spath = malloc(size);
        char *spos = spath;
        bool first = true;
        // backtrack along path upward
        current = next;
        while (current != NULL)
        {
            // append "." and segment name/number unless first
            if (!first || !current->next)
                *spos++ = '.';
            if (current->name)
                spos = stpcpy(spos, current->name);
            else
                spos += sprintf(spos, "%zu", current->index);
            current = current->next;
            first = false;
        }
        *spos = '\0';
        entry->path = spath;
    }
}

static void report_free_entries(Report *rep)
{
    ReportEntry *entry = rep->entry;
    rep->entry = NULL;

    while (entry != NULL) {
        ReportEntry *follow = entry->prev;
        if (entry->path)
            free(entry->path);
        free(entry);
        entry = follow;
    }
}

typedef bool (*check_fun_t)(const json_t *, Path *, Report *);

/*
 * property mapping management
 */

typedef struct {
    const char *name;
    check_fun_t val_check;
} check_prop_t;

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

/*
 * set of constants
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

static void dbg_cst(const constant_t *c, const char *describe)
{
    fprintf(stderr, "%s (%s): %s\n",
            describe,
            c->tag == cst_is_string? "string": "?",
            c->tag == cst_is_string? c->val.s: "?");
}

static int cmp_cst(const constant_t *c1, const constant_t *c2)
{
    // sort by types: null < bool < int < float < string
    if (c1->tag != c2->tag)
      return c2->tag - c1->tag;
    // else compare values
    switch (c1->tag)
    {
    case cst_is_null:
        return 0;
    case cst_is_bool:  // false < true
        return c2->val.b - c1->val.b;
    case cst_is_integer:
        int64_t i1 = c1->val.i, i2 = c2->val.i;
        return i1 < i2 ? -1 : i1 == i2 ? 0 : 1;
    case cst_is_float:
        double f1 = c1->val.f, f2 = c2->val.f;
        return f1 < f2 ? -1 : f1 == f2 ? 0 : 1;
    case cst_is_string:
        return strcmp(c1->val.s, c2->val.s);
    default:  // internal error?!
        return 0;
    }
}

static void sort_cst(constant_t *array, size_t size)
{
    qsort(array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst);
}

static bool search_cst(const constant_t *value, const constant_t *array, size_t size)
{
    return bsearch(value, array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst) != NULL;
}

/*
 * generated API
 */
static bool initialized = false;

/* module API: FIXME, report free is missing? hide function retrieval? */
char *CHECK_FUNCTION_NAME_init(void);
check_fun_t CHECK_FUNCTION_NAME_fun(const char *name);
bool CHECK_FUNCTION_NAME(json_t* val, const char *name, bool *error, char **reasons);
void CHECK_FUNCTION_NAME_free(void);
