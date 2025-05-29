#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t* val, Path* path, Report* rep);
static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[6];
const size_t check_model_map_size = 6;

// check $V ($.'$V')
static bool json_model_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$V'
    // $.'$V'.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$V'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$V'.'|'.1
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [$.'$V'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$V'.'|']", path);
    }
    return res;
}

// object $.'$X'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$X']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "X") == 0)
        {
            // handle must X property
            must_count += 1;
            // $.'$X'.X
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$X'.X]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$X'.X]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$X']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$X']", path);
        return false;
    }
    return true;
}

// check $X ($.'$X')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$X'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$X']", path);
    }
    return res;
}

// object $.'$Y'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$Y']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "Y") == 0)
        {
            // handle must Y property
            must_count += 1;
            // $.'$Y'.Y
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$Y'.Y]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$Y'.Y]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$Y']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$Y']", path);
        return false;
    }
    return true;
}

// check $Y ($.'$Y')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$Y'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$Y']", path);
    }
    return res;
}

// object $.'$E'.'|'.1
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$E'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "Y") == 0)
        {
            // handle must Y property
            must_count += 1;
            // $.'$E'.'|'.1.Y
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$E'.'|'.1.Y]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$E'.'|'.1.Y]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "Z") == 0)
        {
            // handle may Z property
            // $.'$E'.'|'.1.Z
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$E'.'|'.1.Z]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$E'.'|'.1.Z]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$E'.'|'.1]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$E'.'|'.1]", path);
        return false;
    }
    return true;
}

// object $.'$E'.'|'.0
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$E'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "X") == 0)
        {
            // handle must X property
            must_count += 1;
            // $.'$E'.'|'.0.X
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$E'.'|'.0.X]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$E'.'|'.0.X]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "Z") == 0)
        {
            // handle may Z property
            // $.'$E'.'|'.0.Z
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$E'.'|'.0.Z]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$E'.'|'.0.Z]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$E'.'|'.0]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$E'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $E ($.'$E')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$E'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$E'.'|']", path);
    }
    if (res)
    {
        // $.'$E'.'|'.0
        res = _jm_obj_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$E'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$E'.'|'.1
            res = _jm_obj_2(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$E'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$E'.'|']", path);
        }
    }
    return res;
}

// check $M ($.'$M')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$M'
    // generic xor list
    int64_t xc_0 = 0;
    bool xr_0;
    // $.'$M'.'^'.0
    xr_0 = json_model_2(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $V [$.'$M'.'^'.0]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    // $.'$M'.'^'.1
    xr_0 = json_model_5(val, path, rep);
    if (! xr_0)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $E [$.'$M'.'^'.1]", path);
    }
    if (xr_0)
    {
        xc_0 += 1;
    }
    res = xc_0 == 1;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not one model match [$.'$M'.'^']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $M [$]", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 6);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "V", json_model_2 };
        check_model_map_tab[2] = (propmap_t) { "X", json_model_3 };
        check_model_map_tab[3] = (propmap_t) { "Y", json_model_4 };
        check_model_map_tab[4] = (propmap_t) { "E", json_model_5 };
        check_model_map_tab[5] = (propmap_t) { "M", json_model_6 };
        jm_sort_propmap(check_model_map_tab, 6);
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
