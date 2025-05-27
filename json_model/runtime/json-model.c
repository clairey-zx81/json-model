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
    json_propval_t pv1[s1], pv2[s2];
    const char *key;
    json_t *value;

    // borrow properties and values from both objects
    size_t index = 0;
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
            int64_t i1 = json_integer_value(v1), i2 = json_integer_value(v2);
            // do not substract to avoid overflows
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

// FIXME this assumes ISO, and won't work on MacOS/BSD nor Windows
// which have their own view of qsort_r, including different names and/or argument orders.
// NOTE fast version which stops comparing once a duplicate has been seen:
// hopefully an optimized qsort implementation can use this to return early.
static int
_json_cmp_r(const json_t **v1, const json_t **v2, void *duplicate)
{
    if (*((bool *) duplicate))
        return 0;
    int cmp = _json_cmp(*v1, *v2);
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

// idem with reporting
bool
jm_array_is_unique(const json_t *val, Path *path, Report *rep)
{
    bool unique = _json_array_unique(val);
    if (!unique && rep)
        jm_report_add_entry(rep, "non unique array", path);
    return unique;
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
jm_is_valid_date(const char *date)
{
    int year, month, day;

    if (date == NULL || sscanf(date, "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;

    struct tm ti = (struct tm) { .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day};
    time_t t = mktime(&ti);

    // checks no error *and* no "funny" normalization
    return t != -1 && ti.tm_year == year - 1900 && ti.tm_mon == month - 1 && ti.tm_mday == day;
}

bool
jm_is_valid_uuid(const char *uuid)
{
    if (!uuid)
        return false;
    // hardcoded version for ASCII and UTF-8
    for (size_t i = 0; i < 8; i++)
        if (!isxdigit(uuid[i]))
            return false;
    if (uuid[8] != '-')
        return false;
    for (size_t i = 9; i < 13; i++)
        if (!isxdigit(uuid[i]))
            return false;
    if (uuid[13] != '-')
        return false;
    for (size_t i = 14; i < 18; i++)
        if (!isxdigit(uuid[i]))
            return false;
    if (uuid[18] != '-')
        return false;
    for (size_t i = 19; i < 23; i++)
        if (!isxdigit(uuid[i]))
            return false;
    if (uuid[23] != '-')
        return false;
    for (size_t i = 24; i < 36; i++)
        if (!isxdigit(uuid[i]))
            return false;
    return uuid[36] == '\0';
}

// check regex validity by attempting to compile it with PCRE2, probably not very efficient
bool
jm_is_valid_regex_slow(const char *pattern)
{
    if (!pattern)
        return false;
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

// hardcoded regex parser for https://github.com/google/re2/wiki/syntax
bool
jm_is_valid_regex_fast(const char *pattern)
{
    if (!pattern)
        return false;

    char *c = (char *) pattern;

    int paren = 0;
    bool start = true;
    bool okay = true;

    fprintf(stderr, "pattern = %s\n", pattern);

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
                c++;  // next char
                okay &= isdigit(*c);  // must be a number
                while (isdigit(*c))
                    c++;
                if (*c == ',') {  // second part, may be empty
                    c++;  // first char
                    while (isdigit(*c))
                        c++;
                }
                okay &= *c == '}';
                break;
            case '(':
                paren++;

                if (*(c+1) == '?')  // start of extension
                {
                    c += 2;

                    if (islower(*c))  // start of flags
                    {
                        while (islower(*c))
                            c++;
                        if (*c == ':')  // (?flags:re)
                        {
                            start = true;
                        }
                        else if (*c == ')')  // (?flags)
                        {
                            start = true;
                            paren--;
                        }
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
                    {
                        start = true;
                    }
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
            default:
        }
        c++;
    }

    okay &= *c == '\0' && paren == 0;

    return okay;
}

// this is utf-8 compatible because multi-byte encoding uses chars over 128.
bool
jm_is_valid_url(const char *url)
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

// generic constraint check.
bool
jm_check_constraint(const json_t * val, constraint_op_t op, const constant_t *cst,
                    Path *path, Report *rep)
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
    else if (cst->tag == cst_is_string)
    {
        const char *scst = cst->val.s;
        if (!json_is_string(val))
        {
            if (rep)
                jm_report_add_entry(rep, "invalid type for string constraint", path);
            return false;
        }

        const char *sval = json_string_value(val);
        switch (op) {
            case op_eq:
                res = strcmp(sval, scst) == 0;
                break;
            case op_ne:
                res = strcmp(sval, scst) != 0;
                break;
            case op_le:
                res = strcmp(sval, scst) <= 0;
                break;
            case op_lt:
                res = strcmp(sval, scst) < 0;
                break;
            case op_ge:
                res = strcmp(sval, scst) >= 0;
                break;
            case op_gt:
                res = strcmp(sval, scst) > 0;
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
jm_check_fun_string(check_fun_t fun, const char *val, Path *path, Report *rep)
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
    char *(*model_init)(void),
    check_fun_t (*model_fun)(const char *),
    // void (*model_free)(void),
    const json_t *val, const char *name, bool *error, char **reasons)
{
    model_init();  // lazy
    check_fun_t checker = model_fun(name);

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

    jm_report_free_entries(&report);

    return valid;
}
