#include <json-model.h>

#include <stdio.h>
#include <ctype.h>
#include <time.h>

char *jm_version_string = "<unknown>";

/*
 * JSON API extensions
 */
bool
_json_is_scalar(const json_t *val)
{
    const json_type tval = json_typeof(val);
    return (tval == JSON_STRING || tval == JSON_INTEGER || tval == JSON_REAL ||
            tval == JSON_TRUE || tval == JSON_FALSE || tval == JSON_NULL);
}

// fast JSON array comparison for a total order
int
_json_array_cmp(const json_t *v1, const json_t *v2)
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

// for sorting propvals by property names
int
_json_propval_cmp(const json_propval_t *pv1, const json_propval_t *pv2)
{
    return strcmp(pv1->prop, pv2->prop);
}

// fast JSON object comparison for a total order
int
_json_object_cmp(const json_t *v1, const json_t *v2)
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

int
_json_cmp(const json_t *v1, const json_t *v2)
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

// typedef int(*cmp_r_fun_t)(const void *, const void *, void *);

// NOTE this assumes ISO, and won't work on MacOS/BSD nor Windows
// which have their own view of qsort_r, including different names and/or argument orders.
// fast version which stops comparing once a duplicate has been seen:
// hopefully an optimized qsort implementation can use this to return early.
static int
_json_cmp_r(const json_t *v1, const json_t *v2, void *duplicate)
{
    if (*((bool *) duplicate))
        return 0;
    int cmp = _json_cmp(v1, v2);
    if (cmp == 0)
        *((bool *) duplicate) = true;
    return cmp;
}

// tell whether a JSON array holds distinct values.
bool
_json_array_unique(const json_t *val)
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
void
jm_report_add_entry(Report* rep, const char *msg, Path *path)
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

void
jm_report_free_entries(Report *rep)
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

/*
 * property mapping management
 */
static int
cmp_propmap(const propmap_t *e1, const propmap_t *e2)
{
    return strcmp(e1->name, e2->name);
}

void
jm_sort_propmap(propmap_t *props, int nprops)
{
    qsort(props, nprops, sizeof(propmap_t), (cmp_fun_t) cmp_propmap);
}

check_fun_t
jm_search_propmap(const char *name, const propmap_t *props, int nprops)
{
    propmap_t searched = (propmap_t) { name, NULL };
    propmap_t *entry = (propmap_t *)
        bsearch(&searched, props, nprops, sizeof(propmap_t), (cmp_fun_t) cmp_propmap);
    return entry ? entry->val_check : NULL;
}

/*
 * set of scalar constants
 */
bool
jm_set_cst(constant_t *c, const json_t *val)
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

void
jm_dbg_cst(const constant_t *c, const char *describe)
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

void
jm_sort_cst(constant_t *array, size_t size)
{
    qsort(array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst);
}

bool
jm_search_cst(const constant_t *value, const constant_t *array, size_t size)
{
    return bsearch(value, array, size, sizeof(constant_t), (cmp_fun_t) cmp_cst) != NULL;
}

/*
 * constant mapping management for discriminant optimization
 */
static int
cmp_constmap(const constmap_t *cm1, const constmap_t *cm2)
{
    return cmp_cst(&cm1->cst, &cm2->cst);
}

void
jm_sort_constmap(constmap_t *array, size_t size)
{
    qsort(array, size, sizeof(constmap_t), (cmp_fun_t) cmp_constmap);
}

check_fun_t
jm_search_constmap(const constant_t *val, const constmap_t *array, size_t size)
{
    constmap_t value = (constmap_t) { *val, NULL };
    constmap_t *found = (constmap_t *)
        bsearch(&value, array, size, sizeof(constmap_t), (cmp_fun_t) cmp_constmap);
    return found ? found->check_val : NULL;
}

size_t
jm_any_len(json_t *val)
{
    if (json_is_object(val))
        return json_object_size(val);
    else if (json_is_array(val))
        return json_array_size(val);
    else if (json_is_string(val))
        return mbstowcs(NULL, json_string_value(val), 0);
    // panic
    return 0;
}

bool
jm_is_valid_date(const char *value)
{
    int year, month, day;

    if (value == NULL || sscanf(value, "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;

    struct tm ti = (struct tm) { .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day};
    time_t t = mktime(&ti);

    return t != -1 && ti.tm_year == year - 1900 && ti.tm_mon == month - 1 && ti.tm_mday == day;
}

// this must be initialized!
pcre2_code *jm_is_valid_uuid_code = NULL;
pcre2_match_data *jm_is_valid_uuid_data = NULL;

bool
jm_is_valid_uuid(const char *s)
{
  int rc = pcre2_match(jm_is_valid_uuid_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, jm_is_valid_uuid_data, NULL);
  return rc >= 0;
}

bool
jm_is_valid_regex(const char *pattern)
{
    int err_code;
    PCRE2_SIZE err_offset;
    pcre2_code *code =
        pcre2_compile((PCRE2_SPTR) pattern, PCRE2_ZERO_TERMINATED,
                      PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
    bool valid = code != NULL;
    if (code)
        pcre2_code_free(code);
    return valid;
}
