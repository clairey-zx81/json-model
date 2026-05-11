#include <json-model.h>

#include <stdio.h>
#include <ctype.h>
#include <time.h>

char *jm_version_string = "<unknown>";

// regular expression engine
#if defined(REGEX_ENGINE_PCRE2)
#  define PCRE2_CODE_UNIT_WIDTH 8
#  include <pcre2.h>
#elif defined(REGEX_ENGINE_RE2)
#  include <stddef.h>
#  include <cre2.h>
#else
#  error missing regex engine definition
#endif

/*
 * JSON API extensions
 */
bool
jm_json_is_scalar(const json_t *val)
{
    const json_type tval = json_typeof(val);
    return (tval == JSON_STRING || tval == JSON_INTEGER || tval == JSON_REAL ||
            tval == JSON_TRUE || tval == JSON_FALSE || tval == JSON_NULL);
}

/*
 * HASH
 */
// left rotation
static INLINE uint64_t lrot(const uint64_t v, int n)
{
    n &= 0x3f; // % 64
    return (v >> n) | (v << (64-n));
}

static INLINE uint64_t lrot1(uint64_t v) { return (v >> 1) | (v << 63); }

// extract string length based on json_t layout
#define jansson_string_length(v) (*(((size_t *) (v + 1)) + 1))

#define extract_string_value(str, len) \
    (unlikely(len < 3) ?  ((uint8_t) *(str)) : (*(uint32_t *) (str)))

// TODO improve string hashing?

static uint64_t
jm_fast_hash(const json_t *v)
{
    const json_type t = json_typeof(v);
    uint64_t hash = ((uint64_t) t) << 48;
    switch (t)
    {
        case JSON_INTEGER:
            hash += json_integer_value(v);
            break;
        case JSON_REAL:
            hash += (int) (1024.0 * json_real_value(v));
            break;
        case JSON_STRING:  // consider first byte
        {
            const size_t length = jansson_string_length(v);
            hash += extract_string_value(json_string_value(v), length) + (length << 16);
            break;
        }
        case JSON_ARRAY:
        {
            size_t n = json_array_size(v);
            while (n--)
                hash = lrot1(hash) + jm_fast_hash(json_array_get(v, n));
            break;
        }
        case JSON_OBJECT:
        {
            const char *key;
            json_t *value;
            json_object_foreach((json_t *) v, key, value)
                hash += extract_string_value(key, strlen(key)) + lrot(jm_fast_hash(value), 32);
            break;
        }
        default:
            // NULL, TRUE, FALSE: okay through type
            break;
    }
    return hash;
}

/*
 * JSON ORDERING
 */
// fast JSON array comparison for a total order
int
jm_json_array_cmp(const json_t *v1, const json_t *v2)
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
        int cmp = jm_json_cmp(iv1, iv2);
        if (cmp != 0)
            return cmp;
    }

    // no difference found
    return 0;
}

// for sorting propvals by property names
int
jm_propval_cmp(const jm_propval_t *pv1, const jm_propval_t *pv2)
{
    return strcmp(pv1->prop, pv2->prop);
}

static INLINE int
jm_json_object_pv_cmp(const jm_propval_t *pv1, const jm_propval_t *pv2, size_t size)
{
    // try lexicographic order of keys
    for (size_t i = 0; i < size; i++)
    {
        int cmp = strcmp(pv1[i].prop, pv2[i].prop);
        if (cmp != 0)
            return cmp;
    }
    // same keys, try lexicographic order of values
    for (size_t i = 0; i < size; i++)
    {
        int cmp = jm_json_cmp(pv1[i].val, pv2[i].val);
        if (cmp != 0)
            return cmp;
    }
    // same keys and values
    return 0;
}

// fast JSON object comparison for a total order
int
jm_json_object_cmp(const json_t *v1, const json_t *v2)
{
    // first, try size
    size_t s1 = json_object_size(v1), s2 = json_object_size(v2);
    if (s1 != s2)
        return s2 - s1;

    // else same size, extract property/value pairs
    jm_propval_t pv1[s1], pv2[s1];
    const char *key;
    json_t *value;

    // borrow properties and values from both objects
    size_t index = 0;
    json_object_foreach((json_t *) v1, key, value)
        pv1[index++] = (jm_propval_t) { key, value };
    qsort(pv1, s1, sizeof(jm_propval_t), (jm_cmp_fun_t) jm_propval_cmp);

    index = 0;
    json_object_foreach((json_t *) v2, key, value)
        pv2[index++] = (jm_propval_t) { key, value };
    qsort(pv2, s2, sizeof(jm_propval_t), (jm_cmp_fun_t) jm_propval_cmp);

    return jm_json_object_pv_cmp(pv1, pv2, s1);
}

int
jm_json_cmp(const json_t *v1, const json_t *v2)
{
    const json_type t1 = json_typeof(v1), t2 = json_typeof(v2);
    if (t1 != t2)
        return t1 - t2;  // inverted to have simpler types ahead

    // else same type
    switch (t1)
    {
        case JSON_NULL:
        case JSON_FALSE:
        case JSON_TRUE:
            // one only value is equal to itself
            return 0;
        case JSON_INTEGER:
        {
            int64_t i1 = json_integer_value(v1), i2 = json_integer_value(v2);
            // do not substract to avoid overflows
            return i1 < i2 ? -1 : i1 == i2 ? 0 : 1;
        }
        case JSON_REAL:
        {
            double r1 = json_real_value(v1), r2 = json_real_value(v2);
            return r1 < r2 ? -1 : r1 == r2 ? 0 : 1;
        }
        case JSON_STRING:
            return strcmp(json_string_value(v1), json_string_value(v2));
        case JSON_ARRAY:
            return jm_json_array_cmp(v1, v2);
        case JSON_OBJECT:
            return jm_json_object_cmp(v1, v2);
    }

    // default: panic, internal error
    assert(false);
    return 0;
}

/*
 * QUADRATIC UNIQUE ARRAY WITH HASH
 *
 * This is based on blaze core "unique()" implementation which fares quite better
 * for small arrays.
 */
#ifndef UNIQUE_STRING_ARRAY_HASH_LIMIT
#define UNIQUE_STRING_ARRAY_HASH_LIMIT 64
#endif // UNIQUE_STRING_ARRAY_HASH_LIMIT

// tested on integers
#ifndef UNIQUE_JSON_ARRAY_HASH_LIMIT
#define UNIQUE_JSON_ARRAY_HASH_LIMIT 200
#endif // UNIQUE_JSON_ARRAY_HASH_LIMIT

// even higher seems ok, up to 1024
#ifndef UNIQUE_OBJECT_ARRAY_HASH_LIMIT
#define UNIQUE_OBJECT_ARRAY_HASH_LIMIT 512
#endif // UNIQUE_OBJECT_ARRAY_HASH_LIMIT

#ifndef UNIQUE_INTEGER_ARRAY_HASH_LIMIT
#define UNIQUE_INTEGER_ARRAY_HASH_LIMIT 54
#endif // UNIQUE_INTEGER_ARRAY_HASH_LIMIT

typedef struct {
    json_t *json;
    uint64_t hash;
} jm_json_hash_t;

static bool
jm_json_array_unique_hash(const json_t *val, size_t size)
{
    jm_json_hash_t array[size];

    for (size_t i = 0; i < size; i++)
    {
        const json_t *json = json_array_get(val, i);
        array[i] = (jm_json_hash_t) { (json_t *) json, jm_fast_hash(json) };
    }

    for (size_t i = 0; i < size; i++)
        for (size_t j = i + 1; j < size; j++)
            if (array[i].hash == array[j].hash && json_equal(array[i].json, array[j].json))
                return false;
    return true;
}

// re-entrant quick sort helpers
#if defined(_WIN64)
#  define qsort_r qsort_s
#endif

#if defined(_WIN64) || defined(__APPLE__)
typedef int(*jm_cmp_r_fun_t)(void *, const void *, const void *);
#  define CMP_R(name, vtype) \
     name(void *duplicate, const vtype *v1, const vtype *v2)
#else  // ISO - Linux, Unix, whatever
typedef int(*jm_cmp_r_fun_t)(const void *, const void *, void *);
#  define CMP_R(name, vtype) \
     name(const vtype *v1, const vtype *v2, void *duplicate)
#endif

/*
 * UNIQUE ANY JSON ARRAY
 */
// NOTE fast version which stops comparing once a duplicate has been seen:
// hopefully an optimized qsort implementation can use this to return early.
static int CMP_R(jm_json_cmp_r, json_t *)
{
    // shortcut: no sorting once a duplicate has been found
    if (*((bool *) duplicate))
        return 0;
    // else do compare
    int cmp = jm_json_cmp(*v1, *v2);
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

// tell whether a JSON array holds distinct values in n log n.
bool
jm_json_array_unique(const json_t *val)
{
    // extract as an actual array for sorting
    // NOTE safe: if not an array, the size is 0
    size_t size = json_array_size(val);
    if (size <= 1)
        return true;
    if (size <= UNIQUE_JSON_ARRAY_HASH_LIMIT)
        return jm_json_array_unique_hash(val, size);

    const json_t *array[size];
    // borrow array items into a copy for sorting
    for (size_t i = 0; i < size; i++)
        array[i] = json_array_get(val, i);
    // relying only on qsort works because in the end
    // all items have been compared to their neighbours
    bool duplicate = false;
    qsort_r(array, size, sizeof(json_t *), (jm_cmp_r_fun_t) jm_json_cmp_r, &duplicate);
    return !duplicate;
}

// idem with reporting
bool
jm_json_array_is_unique(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool unique = jm_json_array_unique(val);
    if (unlikely(!unique && rep))
        jm_report_add_entry(rep, "non unique json array", path);
    return unique;
}

/*
 * UNIQUE STRING ARRAY
 */
static int CMP_R(jm_str_cmp_r, char *)
{
    // shortcut: no sorting once a duplicate has been found
    if (*((bool *) duplicate))
        return 0;
    // else do compare
    int cmp = strcmp(*v1, *v2);
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

// we assume that the array type is already checked
bool
jm_str_array_unique(const json_t *val)
{
    size_t size = json_array_size(val);
    if (size <= 1)
        return true;
    if (size <= UNIQUE_STRING_ARRAY_HASH_LIMIT)
        return jm_json_array_unique_hash(val, size);

    const char *array[size];
    for (size_t i = 0; i < size; i++)
        array[i] = json_string_value(json_array_get(val, i));
    bool duplicate = false;
    qsort_r(array, size, sizeof(char *), (jm_cmp_r_fun_t) jm_str_cmp_r, &duplicate);
    return !duplicate;
}

// idem with reporting
bool
jm_str_array_is_unique(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool unique = jm_str_array_unique(val);
    if (unlikely(!unique && rep))
        jm_report_add_entry(rep, "non unique string array", path);
    return unique;
}

/*
 * UNIQUE OBJECT ARRAY
 */

typedef struct {
    json_t *object;
    jm_propval_t *propvals;
} jm_object_propval_t;

static int
jm_object_propval_prop_cmp(const jm_object_propval_t *op1, const jm_object_propval_t *op2)
{
    return jm_propval_cmp(op1->propvals, op2->propvals);
}

static int
jm_object_propval_obj_cmp(const jm_object_propval_t *op1, const jm_object_propval_t *op2)
{
    const json_t *o1 = op1->object, *o2 = op2->object;

    // first on size
    const size_t os1 = json_object_size(o1), os2 = json_object_size(o2);
    if (os1 != os2)
        return os2 - os1;

    // then on property names and then on values
    return jm_json_object_pv_cmp(op1->propvals, op2->propvals, os1);
}

static int CMP_R(jm_obj_cmp_r, jm_object_propval_t)
{
    // shortcut: no sorting once a duplicate has been found
    if (*((bool *) duplicate))
        return 0;
    // else do compare
    int cmp = jm_object_propval_obj_cmp(v1, v2);
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

// we assume that the array type is already checked
bool
jm_obj_array_unique(const json_t *val)
{
    size_t size = json_array_size(val);
    if (size <= 1)
        return true;
    if (size <= UNIQUE_OBJECT_ARRAY_HASH_LIMIT)
        return jm_json_array_unique_hash(val, size);

    size_t nprops = 0;

    // array of objects
    jm_object_propval_t array[size];
    for (size_t i = 0; i < size; i++)
    {
        const json_t *object = json_array_get(val, i);
        array[i].object = (json_t *) object;
        nprops += json_object_size(object);
    }

    // shared array of properties and values
    jm_propval_t propval_array[nprops];
    size_t index = 0;
    for (size_t o = 0; o < size; o++)
    {
        const char *key;
        json_t *value;
        array[o].propvals = propval_array + index;
        json_object_foreach((json_t *)  array[o].object, key, value)
            propval_array[index++] = (jm_propval_t) { key, value };
        // NOTE we could skip this if the order is deterministic
        qsort(array[o].propvals, json_object_size(array[o].object), sizeof(jm_propval_t), (jm_cmp_fun_t) jm_propval_cmp);
    }
    assert(index == nprops);

    // unique!
    bool duplicate = false;
    qsort_r(array, size, sizeof(jm_object_propval_t), (jm_cmp_r_fun_t) jm_obj_cmp_r, &duplicate);
    return !duplicate;
}

// idem with reporting
bool
jm_obj_array_is_unique(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool unique = jm_obj_array_unique(val);
    if (unlikely(!unique && rep))
        jm_report_add_entry(rep, "non unique object array", path);
    return unique;
}

/* UNIQUE INT ARRAY
 */
static int CMP_R(jm_int_cmp_r, int64_t)
{
    // shortcut: no sorting once a duplicate has been found
    if (*((bool *) duplicate))
        return 0;
    // else do compare
    int cmp = v2 < v1 ? -1 : v2 > v1 ? 1 : 0;
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

// we assume that the array type is already checked
bool
jm_int_array_unique(const json_t *val)
{
    size_t size = json_array_size(val);
    if (size <= 1)
        return true;

    int64_t array[size];

    // value based
    if (size <= UNIQUE_INTEGER_ARRAY_HASH_LIMIT)
    {
        for (int i = 0; i < size; i++)
        {
            int64_t ival = json_integer_value(json_array_get(val, i));
            for (int j = 0; j < i; j++)
                if (ival == array[j])
                    return false;
            array[i] = ival;
        }
        return true;
    }

    // else sort based
    for (int i = 0; i < size; i++)
        array[i] = json_integer_value(json_array_get(val, i));

    bool duplicate = false;
    qsort_r(array, size, sizeof(int64_t), (jm_cmp_r_fun_t) jm_int_cmp_r, &duplicate);
    return !duplicate;
}

bool
jm_int_array_is_unique(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool unique = jm_int_array_unique(val);
    if (unlikely(!unique && rep))
        jm_report_add_entry(rep, "non unique integer array", path);
    return unique;
}

/*
 * REPORTING
 */

void
jm_report_add_entry(jm_report_t* rep, const char *msg, jm_path_t *path)
{
    jm_report_entry_t *entry = malloc(sizeof(jm_report_entry_t));
    *entry = (jm_report_entry_t) { msg, NULL, rep->entry };
    rep->entry = entry;
    if (path)
    {
        // path segments are stored in reverse order
        size_t size = 1;
        jm_path_t *current = path;
        jm_path_t *next = NULL;
        // dive to compute the path length and build the back path
        while (current != NULL)
        {
            // "." name or "." number
            size += 1 + (current->name ? strlen(current->name) : (3 * sizeof(size_t)));
            jm_path_t *prev = current->prev;
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

void
jm_report_free_entries(jm_report_t *rep)
{
    jm_report_entry_t *entry = rep->entry;
    rep->entry = NULL;

    while (entry != NULL) {
        jm_report_entry_t *follow = entry->prev;
        if (entry->path)
            free(entry->path);
        free(entry);
        entry = follow;
    }
}

/*
 * property mapping management
 */
static int
jm_cmp_propmap(const jm_propmap_t *e1, const jm_propmap_t *e2)
{
    return strcmp(e1->name, e2->name);
}

void
jm_sort_propmap(jm_propmap_t *props, int nprops)
{
    qsort(props, nprops, sizeof(jm_propmap_t), (jm_cmp_fun_t) jm_cmp_propmap);
}

jm_check_fun_t
jm_search_propmap(const char *name, const jm_propmap_t *props, int nprops)
{
    jm_propmap_t searched = (jm_propmap_t) { name, NULL };
    jm_propmap_t *entry = (jm_propmap_t *)
        bsearch(&searched, props, nprops, sizeof(jm_propmap_t), (jm_cmp_fun_t) jm_cmp_propmap);
    return entry ? entry->val_check : NULL;
}

/*
 * set of scalar constants
 */
bool
jm_set_cst(jm_constant_t *c, const json_t *val)
{
    switch (json_typeof(val))
    {
        case JSON_STRING:
        {
            const char * s = json_string_value(val);
            *c = (jm_constant_t) { strlen(s) + 1, { .s = s } };
            break;
        }
        case JSON_INTEGER:
            *c = (jm_constant_t) { cst_is_integer, { .i = json_integer_value(val) } };
            break;
        case JSON_REAL:
            *c = (jm_constant_t) { cst_is_float, { .f = json_real_value(val) } };
            break;
        case JSON_TRUE:
            *c = (jm_constant_t) { cst_is_bool, { .b = true } };
            break;
        case JSON_FALSE:
            *c = (jm_constant_t) { cst_is_bool, { .b = false } };
            break;
        case JSON_NULL:
            *c = (jm_constant_t) { cst_is_null, { .s = NULL } };
            break;
        default:
            return false;
    }
    return true;
}

void
jm_dbg_cst(const jm_constant_t *c, const char *describe)
{
    fprintf(stderr, "%s (%s): %s\n",
            describe,
            c->tag > 0 ? "string" : "?",
            c->tag > 0 ? c->val.s : "?");
}

static int
jm_cmp_cst(const jm_constant_t *c1, const jm_constant_t *c2)
{
    // sort by types: null < bool < int < float < strings by length
    if (c1->tag != c2->tag)
      return c2->tag - c1->tag;
    // else compare actual values
    if (c1->tag > 0)
        return memcmp(c1->val.s, c2->val.s, c1->tag);
    // other types
    switch (c1->tag)
    {
    case cst_is_null:
        return 0;
    case cst_is_bool:  // false < true
        return c2->val.b - c1->val.b;
    case cst_is_integer:
    {
        int64_t i1 = c1->val.i, i2 = c2->val.i;
        return i1 < i2 ? -1 : i1 == i2 ? 0 : 1;
    }
    case cst_is_float:
    {
        double f1 = c1->val.f, f2 = c2->val.f;
        return f1 < f2 ? -1 : f1 == f2 ? 0 : 1;
    }
    default:  // internal error?!
        return 0;
    }
}

void
jm_sort_cst(jm_constant_t *array, size_t size)
{
    qsort(array, size, sizeof(jm_constant_t), (jm_cmp_fun_t) jm_cmp_cst);
}

bool
jm_search_cst(const jm_constant_t *value, const jm_constant_t *array, size_t size)
{
    return bsearch(value, array, size, sizeof(jm_constant_t), (jm_cmp_fun_t) jm_cmp_cst) != NULL;
}

/*
 * constant mapping management for discriminant optimization
 */
static int
jm_cmp_constmap(const jm_constmap_t *cm1, const jm_constmap_t *cm2)
{
    return jm_cmp_cst(&cm1->cst, &cm2->cst);
}

void
jm_sort_constmap(jm_constmap_t *array, size_t size)
{
    qsort(array, size, sizeof(jm_constmap_t), (jm_cmp_fun_t) jm_cmp_constmap);
}

jm_check_fun_t
jm_search_constmap(const jm_constant_t *val, const jm_constmap_t *array, size_t size)
{
    jm_constmap_t value = (jm_constmap_t) { *val, NULL };
    jm_constmap_t *found = (jm_constmap_t *)
        bsearch(&value, array, size, sizeof(jm_constmap_t), (jm_cmp_fun_t) jm_cmp_constmap);
    return found ? found->check_val : NULL;
}

size_t
jm_str_len(const char *s)
{
    size_t count = 0;
    while (*s) {
        count += (*s++ & 0xc0) != 0x80;
    }
    return count;
}

size_t
jm_any_len(json_t *val)
{
    if (json_is_object(val))
        return json_object_size(val);
    else if (json_is_array(val))
        return json_array_size(val);
    else if (json_is_string(val))
        return jm_str_len(json_string_value(val));
    // panic
    return 0;
}

// NOTE this version is beyond slow because of mktime.
bool
jm_is_valid_date_slow(const char *date, jm_path_t *path, jm_report_t *rep)
{
    int year, month, day;

    if (date == NULL || sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;

    struct tm ti = (struct tm) { .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day};
    time_t t = mktime(&ti);

    // checks no error *and* no "funny" normalization
    return t != -1 && ti.tm_year == year - 1900 && ti.tm_mon == month - 1 && ti.tm_mday == day;
}

static INLINE bool
is_valid_date(const char *date, jm_path_t *path, jm_report_t *rep, bool full)
{
    if (date == NULL)
        return false;

    static int MONTH_DAYS[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int year = 0, month = 0, day = 0, idx = 0;

    // manual parsing for DDDD-DD-DD and value validation
    while (idx < 4 && likely(isdigit(date[idx])))
        year = year * 10 + date[idx++] - '0';

    if (unlikely(idx++ != 4 || date[4] != '-' || year <= 0)) {
        if (rep) jm_report_add_entry(rep, "unexpected date year", path);
        return false;
    }

    while (idx < 7 && likely(isdigit(date[idx])))
        month = month * 10 + date[idx++] - '0';

    if (unlikely((idx++ != 7 || date[7] != '-' || month < 1 || month > 12))) {
        if (rep) jm_report_add_entry(rep, "unexpected date month", path);
        return false;
    }

    while (idx < 10 && likely(isdigit(date[idx])))
        day = day * 10 + date[idx++] - '0';

    if (unlikely(idx != 10 || (full && date[10] != '\0') || day < 1 || day > MONTH_DAYS[month - 1]))
    {
        if (rep) jm_report_add_entry(rep, "unexpected date day", path);
        return false;
    }

    // allow February 29th only on leap years
    if (unlikely(day == 29 && month == 2)) {
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (rep && !leap) jm_report_add_entry(rep, "unexpected date, not a leap year", path);
        return leap;
    }

    return true;
}

// NOTE this version runs about 50 times faster
bool
jm_is_valid_date_fast(const char *date, jm_path_t *path, jm_report_t *rep)
{
    return is_valid_date(date, path, rep, true);
}

// default version
bool (*jm_is_valid_date)(const char *, jm_path_t *, jm_report_t *) = jm_is_valid_date_fast;

// time parsing
static INLINE bool
is_valid_time(const char *time, jm_path_t *path, jm_report_t *rep, bool sep, bool withtz)
{
    bool with_colon;
    int hour = 0, minute = 0, second = 0, idx = 0;

    // handle optional or mandatory separator, possibly accepting space
    if (time[idx] != 'T' && time[idx] != ' ') {
        if (sep)
            return false;
    }
    else
        idx++;

    // 00..23 hour
    if (unlikely(!isdigit(time[idx])))
        return false;
    hour = 10 * (time[idx++] - '0');
    if (unlikely(!isdigit(time[idx])))
        return false;
    hour += time[idx++] - '0';

    if (unlikely(hour >= 24)) {
        if (rep) jm_report_add_entry(rep, "unexpected time hour", path);
        return false;
    }
    with_colon = time[idx] == ':';
    if (with_colon)
        idx++;

    // 00..59 minute
    if (unlikely(!isdigit(time[idx])))
        return false;
    minute = 10 * (time[idx++] - '0');
    if (unlikely(!isdigit(time[idx])))
        return false;
    minute += time[idx++] - '0';

    if (unlikely(minute >= 60)) {
        if (rep) jm_report_add_entry(rep, "unexpected time minute", path);
        return false;
    }
    if (with_colon && time[idx++] != ':')
        return false;

    // 00..60 second
    if (unlikely(!isdigit(time[idx])))
        return false;
    second = 10 * (time[idx++] - '0');
    if (unlikely(!isdigit(time[idx])))
        return false;
    second += time[idx++] - '0';
    if (unlikely(second > 60)) {
        if (rep) jm_report_add_entry(rep, "unexpected time second", path);
        return false;
    }
    bool leap = second == 60;

    // optional millis (3, sometimes more, let us be nice)
    if (time[idx] == '.') {
        idx++;
        if (unlikely(!isdigit(time[idx++])))
            return false;
        while (isdigit(time[idx]))
            idx++;
    }

    // timezone
    int hshift = 0, mshift = 0;
    bool neg = false;
    if (time[idx] == 'Z' || time[idx] == 'z')
        idx++;
    else if (time[idx] == '+' || time[idx] == '-')
    {
        neg = time[idx] == '-';
        idx++;
        // hours
        hshift = time[idx] - '0';
        if (unlikely(!isdigit(time[idx++])))
            return false;
        hshift = hshift * 10 + time[idx] - '0';
        if (unlikely(!isdigit(time[idx++])))
            return false;
        if (hshift >= 24)
            return false;
        // optional minutes
        if (time[idx] == ':')
        {
            idx++;
            mshift = 10 * (time[idx] - '0');
            if (unlikely(!isdigit(time[idx++])))
                return false;
            mshift += time[idx] - '0';
            if (unlikely(!isdigit(time[idx++])))
                return false;
        }
        else if (isdigit(time[idx]))
        {
            mshift = 10 * (time[idx] - '0');
            idx++;
            mshift += time[idx] - '0';
            if (unlikely(!isdigit(time[idx++])))
                return false;
        }
        if (mshift >= 60)
            return false;
    }
    else if (withtz)
        return false;

    if (unlikely(leap))
    {
        // switch to utc
        if (neg)
            hour += hshift, minute += mshift;
        else
            hour -= hshift, minute -= mshift;

        // normalize
        if (minute < 0)
            hour -= 1, minute += 60;
        else if (minute >= 60)
            hour += 1, minute -= 60;
        if (hour < 0)
            hour += 24;
        else if (hour >= 24)
            hour -= 24;

        // leap seconds must be at midnight gmt
        if (unlikely(hour != 23 || minute != 59))
            return false;
    }

    return time[idx] == '\0';
}

bool
jm_is_valid_time(const char *time, jm_path_t *path, jm_report_t *rep)
{
    if (time == NULL)
        return false;
    return is_valid_time(time, path, rep, false, false);
}

bool
jm_is_valid_timetz(const char *time, jm_path_t *path, jm_report_t *rep)
{
    if (time == NULL)
        return false;
    return is_valid_time(time, path, rep, false, true);
}


bool
jm_is_valid_datetime(const char *datetime, jm_path_t *path, jm_report_t *rep)
{
    if (unlikely(!is_valid_date(datetime, path, rep, false)))
        return false;
    return is_valid_time(datetime + 10, path, rep, true, true);
}

// hardcoded version for ASCII and UTF-8
bool
jm_is_valid_uuid(const char *uuid, jm_path_t *path, jm_report_t *rep)
{
    if (!uuid)
        return false;

    size_t i = 0;

#define subsection(upto)                        \
    while (i < upto)                            \
        if (unlikely(!isxdigit(uuid[i++])))     \
            return false

#define section(upto)                           \
    subsection(upto);                           \
    if (unlikely(uuid[i++] != '-'))             \
        return false

    section(8);
    section(13);
    section(18);
    section(23);
    subsection(36);

    return uuid[i] == '\0';
}

// hardcoded version for ASCII and UTF-8
bool
jm_is_valid_eth(const char *eth, jm_path_t *path, jm_report_t *rep)
{
    if (!eth)
        return false;

    size_t i = 0;

#define hexhex()                                \
    if (unlikely(!isxdigit(eth[i++])))          \
        return false;                           \
    if (unlikely(!isxdigit(eth[i++])))          \
        return false

#define hexhexcol()                             \
    hexhex();                                   \
    if (unlikely(eth[i++] != ':'))              \
        return false

    hexhexcol();
    hexhexcol();
    hexhexcol();
    hexhexcol();
    hexhexcol();
    hexhex();

    return eth[i] == '\0';
}


// check regex validity by attempting to compile it with PCRE2, probably not very efficient
bool
jm_is_valid_regex_slow(const char *pattern, bool extended, jm_path_t *path, jm_report_t *rep)
{
    if (!pattern)
        return false;
    bool valid = false;
#if defined(REGEX_ENGINE_PCRE2)
    int err_code;
    PCRE2_SIZE err_offset;
    pcre2_code *code =
        pcre2_compile((PCRE2_SPTR) pattern, PCRE2_ZERO_TERMINATED,
                      PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
    valid = code != NULL;
    if (code)
        pcre2_code_free(code);
#elif defined(REGEX_ENGINE_RE2)
    cre2_regexp_t *rx = cre2_new(pattern, strlen(pattern), NULL);
    valid = cre2_error_code(rx) == 0;
    cre2_delete(rx);
#endif
    return valid;
}

// hardcoded regex parser for https://github.com/google/re2/wiki/syntax
// TODO consider a subset simple regex syntax
bool
jm_is_valid_regex_fast(const char *pattern, bool extended, jm_path_t *path, jm_report_t *rep)
{
    if (!pattern)
        return false;

    char *c = (char *) pattern;

    int paren = 0;
    bool start = true;
    bool okay = true;

    while (*c && okay)
    {
        if (start) {
            // cannot start with a repeat
            okay &= strchr("*+?{", *c) == NULL;
            start = false;
        }

        // TODO we could check for repeat consistency? eg ?? bad but +? ok.

        switch (*c) {
            case '\\':  // TODO \p{Greek}
                c++;  // skip next, whatever, possibly some character class

                if ((*c == 'p' || *c == 'P') && *(c+1) == '{')  // handle \p{Greek}
                {
                    c+=2;
                    while (isalpha(*c))
                        c++;
                    okay &= *c == '}';
                }
                else
                    okay &= *c != '\0';
                break;
            case '[':
                c++;
                if (*c == '[' && *(c+1) == ':')  // [[: something
                {
                    c += 2;
                    if (*c == '^')  // [[:^
                        c++;
                    while (isalpha(*c))  // caracter class name
                        c++;
                    okay &= *c == ':' && *(c+1) == ']';  // :], check for following ] below
                    if (okay)
                        c += 2;
                }
                else  // [C] [^C]
                {
                    // FIXME what about -? ^ in corner cases?
                    if (*c == '^')
                        c++;
                    while (*c && *c != ']')
                        c++;
                }
                okay &= *c == ']';  // else final ] not found!
                break;
            case '{':  // {123} or {12,34} or {12,}
                c++;  // to digit
                okay = okay && isdigit(*c);  // must be a number
                while (isdigit(*c))
                    c++;
                if (*c == ',') {  // second part, may be empty
                    c++;  // skip , to digit
                    while (isdigit(*c))
                        c++;
                }
                okay &= *c == '}';
                break;
            case '(':
                paren++;

                if (extended && *(c+1) == '$')  // start of JSON MODEL extension
                {
                    c += 2;

                    while (isalnum(*c))  // skip name
                        c++;

                    if (*c == ':')  // optional regex
                        start = true;
                    else if (*c == ')')
                        start = true, paren--;
                    else
                        okay = false;
                }
                else if (*(c+1) == '?')  // start of a usual extension
                {
                    c += 2;

                    if (islower(*c))  // start of flags
                    {
                        while (islower(*c))
                            c++;
                        if (*c == ':')  // (?flags:re)
                            start = true;
                        else if (*c == ')')  // (?flags)
                            start = true, paren--;
                        else
                            okay = false;
                    }
                    else if (*c == 'P' || *c == '<')  // (?P<name>...) or (?<name>...)
                    {
                        if (*c == 'P')
                            c++;
                        okay &= *c == '<';
                        c++;
                        while (isalnum(*c))  // skip name
                            c++;
                        okay &= *c == '>';
                        start = true;
                    }
                    else if (*c == ':')  // non capturing group (?:...)
                        start = true;
                    else
                        okay = false;
                }
                else
                    start = true;
                break;
            case ')':
                paren--;
                okay &= paren >= 0;
                break;
            default:  // ignore
                break;
        }
        c++;
    }

    okay &= *c == '\0' && paren == 0;

    return okay;
}

// default version
bool (*jm_is_valid_regex)(const char *, bool, jm_path_t *, jm_report_t *) = jm_is_valid_regex_fast;

// this is utf-8 compatible because multi-byte encoding uses chars over 128.
bool
jm_is_valid_url(const char *url, jm_path_t *path, jm_report_t *rep)
{
    if (!url)
        return false;
    char *c = (char *) url;
    while (*c) {
        // check url validity (hmmm, just check for strange characters)
        if (!(*c >= 33 && *c < 126 && *c != '"' && *c != '<' && *c != '>'))
            return false;
        c++;
    }
    return true;
}

/*
bool
jm_is_valid_host(const char *host, jm_path_t *path, jm_report_t *rep)
{
    if (!host)
        return false;
}
*/

// FIXME no .., more chars
static INLINE bool is_email_char(int c)
{
    return isalnum(c) || c == '_' || c == '.' || c == '-';
}

// ...@... for ASCII and UTF-8
bool
jm_is_valid_email(const char *email, jm_path_t *path, jm_report_t *rep)
{
    if (!email)
        return false;
    char *c = (char *) email;
    if (!is_email_char(*c++))
        return false;
    while (is_email_char(*c))
        c++;
    if (*c++ != '@')
        return false;
    if (!is_email_char(*c++))
        return false;
    while (is_email_char(*c))
        c++;
    return *c == '\0';
}

// fast UTF-8 JSON scanner
static const char * valid_json(const char *);
static const char * valid_json_string(const char *);

#define skip_blanks(s) while (isspace(*s)) s++

static INLINE const char * valid_json_object(const char *s)
{
    // skip leading {
    s++;
    skip_blanks(s);
    if (*s == '}')
        return s + 1;
    while (*s)
    {
        s = valid_json_string(s);
        if (s == NULL)
            return NULL;
        skip_blanks(s);
        if (*s++ != ':')
            return NULL;
        s = valid_json(s);
        if (s == NULL)
            return NULL;
        skip_blanks(s);
        if (*s == ',')
        {
            s++;
            skip_blanks(s);
        }
        else
            break;
    }
    return *s == '}' ? s + 1 : NULL;
}

static INLINE const char * valid_json_array(const char *s)
{
    // skip leading [
    s++;
    skip_blanks(s);
    if (*s == ']')
        return s + 1;
    while (*s)
    {
        s = valid_json(s);
        if (s == NULL)
            return NULL;
        skip_blanks(s);
        if (*s == ',')
        {
            s++;
            skip_blanks(s);
        }
        else
            break;
    }
    return *s == ']' ? s + 1 : NULL;
}

static INLINE const char * valid_json_string(const char *s)
{
    if (*s != '"')
        return NULL;
    s++;
    // proceed inside the string
    while (*s && *s != '"')
    {
        if (*s == '\\')
        {
            s++;
            if (! *s)
                return NULL;
            if (*s == 'u') {  // handle \uXXXX
                s++;
                if (!isxdigit(*s++)) return NULL;
                if (!isxdigit(*s++)) return NULL;
                if (!isxdigit(*s++)) return NULL;
                if (!isxdigit(*s++)) return NULL;
            }
            // NOTE we do not need to check utf8 encoding if the file was loaded
        }
        s++;
    }
    // check expected end of string
    if (*s == '"')
        return s + 1;
    return NULL;
}

static INLINE const char * valid_json_number(const char *s)
{
    // skip optional sign
    if (*s == '-' || *s == '+')
        s++;
    if (!isdigit(*s))
        return NULL;
    s++;  // first digit
    while (isdigit(*s))
        s++;
    if (*s == '.')  // optional rational part
    {
        s++;
        while (isdigit(*s))
            s++;
    }
    if (*s == 'e' || *s == 'E')  // optional exponent
    {
        s++;
        if (*s == '-' || *s == '+')
            s++;
        if (!isdigit(*s))
            return NULL;
        s++;
        while (isdigit(*s))
            s++;
    }
    return s;
}

static const char * valid_json(const char *s)
{
    skip_blanks(s);
    if (! *s)
        return NULL;
    if (*s == '"')
        return valid_json_string(s);
    if (*s == '{')
        return valid_json_object(s);
    if (*s == '[')
        return valid_json_array(s);
    if (*s == '-' || *s == '+' || ('0' <= *s && *s <= '9'))
        return valid_json_number(s);
    if (strncmp(s, "null", 4) == 0 || strncmp(s, "true", 4) == 0)
        return s + 4;
    if (strncmp(s, "false", 5) == 0)
        return s + 5;
    return NULL;
}

bool
jm_is_valid_json(const char *json, jm_path_t *path, jm_report_t *rep)
{
    if (!json)
        return false;
    const char * s = valid_json(json);
    if (s == NULL)
        return false;
    skip_blanks(s);
    return *s == '\0';
}

// /./ match first non newline char
bool jm_re_dot(const char *s)
{
    while (*s == '\n')
        s++;
    return *s != '\0';
}

// check /^.+$/
bool jm_re_anchored_dotplus(const char *s)
{
    if (*s == '\0' || *s == '\n')
        return false;
    s++;
    while (*s && *s != '\n')
        s++;
    return *s == '\0';
}

bool jm_re_anchored_dotstar(const char *s)
{
    while (*s && *s != '\n')
        s++;
    return *s == '\0';
}

static bool
check_luhn(const char *value, int length)
{
    const int odd = length & 1;
    int sum = 0;
    for (int i = 0; i < length - 1; i++)
    {
        const char c = value[i];
        if (! isdigit(c))
            return false;
        if ((i & 1) ^ odd)
            sum += (c - '0');
        else {
            const int v = 2 * (c - '0');
            sum += v >= 10 ? v - 9 : v;
        }
    }
    const int digit = 9 - ((sum + 9) % 10);
    return value[length-1] == ('0' + digit) && value[length] == '\0';
}

bool
jm_is_valid_card(const char *card, jm_path_t *path, jm_report_t *rep)
{
    return card ? check_luhn(card, 16) : false;
}

double
jm_float_modulo(double d1, double d2)
{
    // for .mo extension (js backend), however not numerically sound
    double m = d1 / d2;
    return m - ((int64_t) m);
}

// generic constraint check.
bool
jm_check_constraint(const json_t * val, jm_constraint_op_t op, const jm_constant_t *cst,
                    jm_path_t *path, jm_report_t *rep)
{
    bool res = false;

    if (!val || json_is_null(val) || json_is_boolean(val))
    {
        if (rep)
            jm_report_add_entry(rep, "unexpected null or bool type for any constraint", path);
        return false;
    }

    if (cst->tag == cst_is_integer)
    {
        int64_t icst = cst->val.i, ival = 0;
        if (json_is_object(val))
            ival = (int64_t) json_object_size(val);
        else if (json_is_array(val))
            ival = (int64_t) json_array_size(val);
        else if (json_is_string(val))
            ival = (int64_t) mbstowcs(NULL, json_string_value(val), 0);
        else if (json_is_integer(val))
            ival = json_integer_value(val);
        else if (json_is_real(val)) {
            // special case
            double fval = json_real_value(val);
            switch (op) {
                case op_eq:
                    res = fval == icst;
                    break;
                case op_ne:
                    res = fval != icst;
                    break;
                case op_le:
                    res = fval <= icst;
                    break;
                case op_lt:
                    res = fval < icst;
                    break;
                case op_ge:
                    res = fval >= icst;
                    break;
                case op_gt:
                    res = fval > icst;
                    break;
            }
            if (!res && rep)
                jm_report_add_entry(rep, "invalid float/int constraint", path);
            return res;
        }
        // else cannot happen

        // ival / icst comparison
        switch (op) {
            case op_eq:
                res = ival == icst;
                break;
            case op_ne:
                res = ival != icst;
                break;
            case op_le:
                res = ival <= icst;
                break;
            case op_lt:
                res = ival < icst;
                break;
            case op_ge:
                res = ival >= icst;
                break;
            case op_gt:
                res = ival > icst;
                break;
        }
        if (!res && rep)
            jm_report_add_entry(rep, "invalid int constraint", path);
        return res;
    }
    else if (cst->tag == cst_is_float)
    {
        double fcst = cst->val.f;
        if (!json_is_number(val))
        {
            if (rep)
                jm_report_add_entry(rep, "invalid type for float constraint", path);
            return false;
        }

        double fval = json_number_value(val);
        switch (op) {
            case op_eq:
                res = fval == fcst;
                break;
            case op_ne:
                res = fval != fcst;
                break;
            case op_le:
                res = fval <= fcst;
                break;
            case op_lt:
                res = fval < fcst;
                break;
            case op_ge:
                res = fval >= fcst;
                break;
            case op_gt:
                res = fval > fcst;
                break;
        }
        if (!res && rep)
            jm_report_add_entry(rep, "invalid float constraint", path);
        return res;
    }
    else if (cst->tag > 0)
    {
        if (!json_is_string(val))
        {
            if (rep)
                jm_report_add_entry(rep, "invalid type for string constraint", path);
            return false;
        }

        const char *sval = json_string_value(val);
        const char *scst = cst->val.s;
        int sclen = cst->tag;  // size include final 0

        switch (op) {
            case op_eq:
                res = memcmp(sval, scst, sclen) == 0;
                break;
            case op_ne:
                res = memcmp(sval, scst, sclen) != 0;
                break;
            case op_le:
                res = memcmp(sval, scst, sclen) <= 0;
                break;
            case op_lt:
                res = memcmp(sval, scst, sclen) < 0;
                break;
            case op_ge:
                res = memcmp(sval, scst, sclen) >= 0;
                break;
            case op_gt:
                res = memcmp(sval, scst, sclen) > 0;
                break;
        }
        if (!res && rep)
            jm_report_add_entry(rep, "invalid string constraint", path);
        return res;
    }

    // else cannot happen
    if (rep)
        jm_report_add_entry(rep, "invalid constant type in constraint", path);
    return false;
}


// MUST BE CONSISTENT WITH "jansson_private.h"
typedef struct {
    json_t  json;
    char    *value;
    size_t  length;
} json_string_t;

// call a check function with a string instead of a json objet.
bool
jm_check_fun_string(jm_check_fun_t fun, const char *val, jm_path_t *path, jm_report_t *rep)
{
    // create a temporary non-malloced json head for the string
    const json_string_t holder = (json_string_t) {
        .json = { JSON_STRING, 1 },
        .value = (char *) val,
        .length = strlen(val)
    };
    return fun((const json_t *) &holder, path, rep);
}

bool
jm_generic_entry(
    const char *(*model_init)(void),
    jm_check_fun_t (*model_fun)(const char *),
    // void (*model_free)(void),
    const json_t *val, const char *name, bool *error, char **reasons)
{
    model_init();  // lazy
    jm_check_fun_t checker = model_fun(name);

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

    jm_path_t root = (jm_path_t) { "$", 0, NULL, NULL };
    jm_report_t report = (jm_report_t) { NULL };

    bool valid = checker(val, reasons ? &root : NULL, reasons ? &report : NULL);

    // generate explanations if a report is required and the value failed to validate
    if  (reasons && report.entry && !valid)
    {
        size_t size = 1;

        for (jm_report_entry_t *entry = report.entry; entry != NULL; entry = entry->prev)
            size += strlen(entry->message) + strlen(entry->path) + 3;

        char *message = malloc(size);
        *reasons = message;

        for (jm_report_entry_t *entry = report.entry; entry != NULL; entry = entry->prev)
            message += sprintf("%s: %s\n", entry->path, entry->message);
    }

    jm_report_free_entries(&report);

    return valid;
}
