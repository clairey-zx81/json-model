#define JSON_MODEL_VERSION "2.0a0"
#define _GNU_SOURCE  // for qsort_r?
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

// fast JSON object comparison for a total order
static int _json_object_cmp(const json_t *v1, const json_t *v2)
{
    // first, try size
    size_t s1 = json_object_size(v1), s2 = json_object_size(v2);
    if (s1 != s2)
        return s2 - s1;
    // else same size, extract property/value pairs
    json_propval_t pv1[s1], pv2[2];
    const char *key;
    json_t *value;
    size_t index = 0;
    // borrow properties and values from both objects
    json_object_foreach((json_t *) v1, key, value)
        pv1[index++] = (json_propval_t) { key, value };
    qsort(pv1, s1, sizeof(json_propval_t), (cmp_fun_t) _json_propval_cmp);
    index = 0;
    json_object_foreach((json_t *) v2, key, value)
        pv2[index++] = (json_propval_t) { key, value };
    qsort(pv2, s2, sizeof(json_propval_t), (cmp_fun_t) _json_propval_cmp);
    // second, try lexicographic order of keys
    for (size_t i = 0; i < s1; i++)
    {
        int cmp = strcmp(pv1[i].prop, pv2[i].prop);
        if (cmp != 0)
            return cmp;
    }
    // same keys, third, try lexicographic order of values
    for (size_t i = 0; i < s1; i++)
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
            // only value is equal with itself
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

typedef int(*cmp_r_fun_t)(const void *, const void *, void *);

// NOTE this assumes ISO, and won't work on MacOS/BSD nor Windows
// which have their own view of qsort_r, including different names and/or argument orders.
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

// tell whether a JSON array holds distinct values.
static bool _json_array_unique(const json_t *val)
{
    assert(json_is_array(val));
    // extract as an actual array for sorting
    size_t size = json_array_size(val);
    const json_t *array[size];
    // borrow array items
    for (size_t i = 0; i < size; i++)
        array[i] = json_array_get(val, i);
    // relying only on qsort works because in the end
    // all items have been compared to their neighbours
    bool duplicate = false;
    // life is fun
    qsort_r(array, size, sizeof(json_t *), (cmp_r_fun_t) _json_cmp_r, &duplicate);
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
        bool dot = false;  // skip first
        // backtrack along path upward
        current = next;
        while (current != NULL)
        {
            // append "." and segment name/number unless first
            if (dot || !current->next)
                *spos++ = '.';
            if (current->name)
                spos = stpcpy(spos, current->name);
            else
                spos += sprintf(spos, "%zu", current->index);
            current = current->next;
            dot = true;
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
} propmap_t;

static int
cmp_propmap(const propmap_t *e1, const propmap_t *e2)
{
    return strcmp(e1->name, e2->name);
}

static void
sort_propmap(propmap_t *props, int nprops)
{
    qsort(props, nprops, sizeof(propmap_t), (cmp_fun_t) cmp_propmap);
}

static check_fun_t
search_propmap(const char *name, const propmap_t *props, int nprops)
{
    propmap_t searched = (propmap_t) { name, NULL };
    propmap_t *entry = (propmap_t *)
        bsearch(&searched, props, nprops, sizeof(propmap_t), (cmp_fun_t) cmp_propmap);
    return entry ? entry->val_check : NULL;
}

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

static inline bool
set_cst(constant_t *c, const json_t *val)
{
    switch (json_typeof(val))
    {
        case JSON_STRING:
            *c = (constant_t) { cst_is_string, { .s = json_string_value(val) } };
            break;
        case JSON_INTEGER:
            *c = (constant_t) { cst_is_integer, { .i = json_integer_value(val) } };
            break;
        case JSON_REAL:
            *c = (constant_t) { cst_is_float, { .f = json_real_value(val) } };
            break;
        case JSON_TRUE:
            *c = (constant_t) { cst_is_bool, { .b = true } };
            break;
        case JSON_FALSE:
            *c = (constant_t) { cst_is_bool, { .b = false } };
            break;
        case JSON_NULL:
            *c = (constant_t) { cst_is_null, { .s = NULL } };
            break;
        default:
            return false;
    }
    return true;
}

static void
dbg_cst(const constant_t *c, const char *describe)
{
    fprintf(stderr, "%s (%s): %s\n",
            describe,
            c->tag == cst_is_string? "string": "?",
            c->tag == cst_is_string? c->val.s: "?");
}

static int
cmp_cst(const constant_t *c1, const constant_t *c2)
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

static void
sort_cst(constant_t *array, size_t size)
{
    qsort(array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst);
}

static inline bool
search_cst(const constant_t *value, const constant_t *array, size_t size)
{
    return bsearch(value, array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst) != NULL;
}

/*
 * constant mapping management for discriminant optimization
 */
typedef struct {
    constant_t cst;
    check_fun_t check_val;
} constmap_t;

static int
cmp_constmap(const constmap_t *cm1, const constmap_t *cm2)
{
    return cmp_cst(&cm1->cst, &cm2->cst);
}

static void
sort_constmap(constmap_t *array, size_t size)
{
    qsort(array, size, sizeof(constmap_t), (cmp_fun_t) cmp_constmap);
}

static check_fun_t
search_constmap(const constant_t *val, const constmap_t *array, size_t size)
{
    constmap_t value = (constmap_t) { *val, NULL };
    constmap_t *found = (constmap_t *)
        bsearch(&value, array, size, sizeof(constmap_t), (cmp_fun_t) cmp_constmap);
    return found ? found->check_val : NULL;
}

/*
 * generated API
 */
static bool initialized = false;

/* module API: FIXME, report free is missing? hide function retrieval? */
char *check_model_init(void);
check_fun_t check_model_fun(const char *name);
bool check_model(json_t* val, const char *name, bool *error, char **reasons);
void check_model_free(void);

static bool json_model_1(const json_t* val, Path* path, Report* rep);
static propmap_t _check_model_map_tab[1];

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) report_add_entry(rep, "not array or unexpected array [$]", path);
    }
    return res;
}

static inline check_fun_t _check_model_map(const char *pname)
{
    return search_propmap(pname, _check_model_map_tab, 1);
}

char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;

        // silent gcc warnings about unused functions
        (void) search_propmap;
        (void) sort_propmap;
        (void) search_constmap;
        (void) sort_constmap;
        (void) search_cst;
        (void) sort_cst;
        (void) dbg_cst;
        (void) set_cst;
        (void) _json_array_unique;
        (void) _json_is_scalar;

        // other initializations
        _check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        sort_propmap(_check_model_map_tab, 1);
    }
    return NULL;
}

void check_model_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
    }
}


/*
 * return check function from identifier.
 */
check_fun_t check_model_fun(const char *name)
{
    return _check_model_map(name);
}

/*
 * API: bool check_model(json_t *, const char *, bool *, char **);
 *
 * valid = check(value, "model-name", &error, &message);
 *
 * - error is set of there was an error during initialization or if the model does not exists.
 * - message is provided if a non NULL pointer is passed, and must be freed by the caller.
 *
 *
 * if the model is not found, report error and reasons if required, else coldly exit.
 */
bool check_model(json_t *val, const char *name, bool *error, char **reasons)
{
    check_model_init();  // lazy
    check_fun_t checker = check_model_fun(name);

    bool not_found = checker == NULL;
    if (error)
        *error = not_found;

    if (not_found)
    {
        const char *format = "JSON Model check function not found for <%s>\n";

        if (!error)
        {
            fprintf(stderr, format, name);
            exit(1);
        }

        if (reasons)
        {
            size_t size = strlen(format) + strlen(name);
            char *message = malloc(size);
            sprintf(message, format, name);
            *reasons = message;
        }

        return false;
    }

    Path root = (Path) { "$", 0, NULL, NULL };
    Report report = (Report) { NULL };

    bool valid = checker(val, reasons ? &root : NULL, reasons ? &report : NULL);

    // generate explanations if a report is required and the value failed to validate
    if  (reasons && report.entry && !valid)
    {
        size_t size = 1;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            size += strlen(entry->message) + strlen(entry->path) + 3;

        char *message = malloc(size);
        *reasons = message;

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            message += sprintf("%s: %s\n", entry->path, entry->message);
    }

    report_free_entries(&report);

    return valid;
}

#ifdef WITH_MAIN
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

typedef enum {
    expect_nothing,
    expect_fail,
    expect_pass
} process_mode_t;

// check value and report if there was some error wrt expectations
static bool
process_value(check_fun_t checker, json_t * value,
    const char *fname, size_t index, process_mode_t mode, bool report)
{
    // check value against model, fast (no path nor reasons)
    bool valid = checker(value, NULL, NULL);
    bool unexpected = (mode == expect_fail && valid) || (mode == expect_pass && !valid);

    if (mode == expect_nothing)  // just show
        fprintf(stdout, "%s: %s", fname, valid ? "PASS" : "FAIL");
    else if (unexpected)
        fprintf(stdout, "%s[%zu]: ERROR unexpected %s", fname, index, valid ? "PASS" : "FAIL");
    else  // as expected
        fprintf(stdout, "%s[%zu]: %s", fname, index, valid ? "PASS" : "FAIL");

    // second pass with report collection
    if (!valid && report)
    {
        Path path = (Path) { "", 0, NULL, NULL };
        Report report = (Report) { NULL };

        bool valid2 = checker(value, &path, &report);
        assert(valid == valid2);

        for (ReportEntry *entry = report.entry; entry != NULL; entry = entry->prev)
            fprintf(stdout, " (%s: %s)", entry->path, entry->message);

        report_free_entries(&report);
    }

    fprintf(stdout, "\n");

    return unexpected;
}

int main(int argc, char* argv[])
{
    // get options
    int opt;
    char *name = "";
    bool report = false;
    bool test = false;
    while ((opt = getopt(argc, argv, "hvln:rt")) != -1)
    {
        switch (opt) {
            case 'h':
                fprintf(stdout,
                        "Usage: %s [-h] [-v] [-l] [-n name] [files...]\n"
                        "Check JSON values validity against a JSON model\n"
                        "Generated by jmc (JSON Model Compiler) version %s\n"
                        "see https://github.com/clairey-zx81/json-model\n",
                        argv[0], JSON_MODEL_VERSION);
                return 0;
            case 'l':
                fprintf(stdout, "JSON Model names (empty for default):");
                for (int i = 0; i < array_length(_check_model_map_tab); i++)
                    fprintf(stdout, "%s ", _check_model_map_tab[i].name);
                fprintf(stdout, "\n");
                return 0;
            case 'v':
                fprintf(stdout, "C from JSON Model compiler version %s\n", JSON_MODEL_VERSION);
                return 0;
            case 'n':
                name = optarg;
                break;
            case 'r':
                report = true;
                break;
            case 't':
                test = true;
                break;
            case '?':
            default:
                fprintf(stdout, "unexpected option encountered\n");
                return 1;
        }
    }

    // initialization
    char *error;
    if ((error = check_model_init()) != NULL)
    {
        fprintf(stderr, "check_model initialization error: %s\n", error);
        return 2;
    }


    // check checker function
    const check_fun_t checker = check_model_fun(name);
    if (checker == NULL)
    {
        fprintf(stderr, "check function not found for %s\n", name);
        return 3;
    }

    int errors = 0;

    for (int i = optind; i < argc; i++)
    {
        json_error_t error;

        // read and parse JSON file
        json_t *value = json_load_file(argv[i], JSON_DECODE_ANY|JSON_ALLOW_NUL, &error);
        if (value == NULL)
        {
            errors++;
            fprintf(stdout, "%s: ERROR (%s at %d:%d)\n",
                    argv[i], error.text, error.line, error.column);
            continue;
        }

        if (test)
        {
            if (!json_is_array(value))
            {
                fprintf(stdout, "%s: ERROR not a JSON array in test mode\n", argv[i]);
                errors++;
                continue;
            }

            size_t index;
            json_t *val;
            json_array_foreach(value, index, val)
            {
                if (!json_is_array(val) || json_array_size(val) != 2 ||
                    !json_is_boolean(json_array_get(val, 0)))
                {
                    fprintf(stdout,
                            "%s[%zu]: ERROR not an ordered pair with a boolean first element\n",
                            argv[i], index);
                    errors++;
                    continue;
                }

                process_mode_t
                    mode = json_is_true(json_array_get(val, 0)) ? expect_pass : expect_fail;

                if (!process_value(checker, json_array_get(val, 1), argv[i], index, mode, report))
                    errors++;
            }
        }
        else
            (void) process_value(checker, value, argv[i], 0, expect_nothing, report);

        // free json value
        json_decref(value);
    }

    check_model_free();

    return errors? 4: 0;
}
#endif  // WITH_MAIN
