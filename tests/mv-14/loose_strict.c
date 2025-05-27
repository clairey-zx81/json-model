#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[4];
const size_t check_model_map_size = 4;

// object $.'$loose'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$loose']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "li") == 0)
        {
            // handle must li property
            must_count += 1;
            // $.'$loose'.li
            res = (json_is_integer(pval) || (json_is_real(pval) && json_real_value(pval) == ((int64_t) json_real_value(pval)))) && json_number_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 loose int [$.'$loose'.li]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$loose'.li]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$loose']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$loose']", path);
        return false;
    }
    return true;
}

// check $loose ($.'$loose')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$loose'
    res = _jm_obj_0(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$loose']", path);
    }
    return res;
}

// object $.'$strict'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$strict']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "si") == 0)
        {
            // handle must si property
            must_count += 1;
            // $.'$strict'.si
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$strict'.si]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$strict'.si]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$strict']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$strict']", path);
        return false;
    }
    return true;
}

// check $strict ($.'$strict')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$strict'
    res = _jm_obj_1(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$strict']", path);
    }
    return res;
}

// object $.'$combined'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$combined']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "li") == 0)
        {
            // handle must li property
            must_count += 1;
            // $.'$combined'.li
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$combined'.li]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$combined'.li]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "si") == 0)
        {
            // handle must si property
            must_count += 1;
            // $.'$combined'.si
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$combined'.si]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$combined'.si]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$combined']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$combined']", path);
        return false;
    }
    return true;
}

// check $combined ($.'$combined')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$combined'
    res = _jm_obj_2(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$combined']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_4(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $combined [$]", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 4);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "loose", json_model_5 };
        check_model_map_tab[2] = (propmap_t) { "strict", json_model_6 };
        check_model_map_tab[3] = (propmap_t) { "combined", json_model_4 };
        jm_sort_propmap(check_model_map_tab, 4);
    }
    return NULL;
}

void CHECK_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
    }
}


/*
 * # API
 *
 * ```c
 * bool error;
 * char *message;
 *
 * bool valid = check(json_value, "model-name", &error, &message);
 *
 * if (message)
 *    free(message), message = NULL;
 * ```
 *
 * - `error` is set of there was an error during initialization or if the model does not exists.
 * - `message` is provided if a non NULL pointer is passed, and must be freed by the caller.
 */
bool
CHECK(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(CHECK_init, CHECK_fun, val, name, error, reasons);
}
