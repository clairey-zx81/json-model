#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static constmap_t _jm_map_0_tab[3];
static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// object .'|'.0
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'|'.0.d
            res = json_is_integer(pval) && json_integer_value(pval) == 1;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected =1 [.'|'.0.d]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.0.d]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "val") == 0)
        {
            // handle must val property
            must_count += 1;
            // .'|'.0.val
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'|'.0.val]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.0.val]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'|'.0]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <d> [.'|'.0]", path);
            }
            if (! (json_object_get(val, "val") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <val> [.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.1
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'|'.1.d
            res = json_is_integer(pval) && json_integer_value(pval) == 2;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected =2 [.'|'.1.d]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.1.d]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "val") == 0)
        {
            // handle must val property
            must_count += 1;
            // .'|'.1.val
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'|'.1.val]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.1.val]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'|'.1]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <d> [.'|'.1]", path);
            }
            if (! (json_object_get(val, "val") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <val> [.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.2
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'|'.2.d
            res = json_is_integer(pval) && json_integer_value(pval) == 3;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected =3 [.'|'.2.d]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.2.d]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "val") == 0)
        {
            // handle must val property
            must_count += 1;
            // .'|'.2.val
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'|'.2.val]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'|'.2.val]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'|'.2]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <d> [.'|'.2]", path);
            }
            if (! (json_object_get(val, "val") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <val> [.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

static check_fun_t _jm_map_0(json_t *val)
{
    constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 3);
}

// check $ ()
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    //
    res = json_is_object(val);
    if (res)
    {
        json_t * tag_0 = json_object_get(val, "d");
        if (tag_0 != NULL)
        {
            check_fun_t fun_0 = _jm_map_0(tag_0);
            if (fun_0 != NULL)
            {
                res = fun_0(val, path, rep);
            }
            else
            {
                res = false;
                if (rep) jm_report_add_entry(rep, "tag d value not found [.'|']", path);
            }
        }
        else
        {
            res = false;
            if (rep) jm_report_add_entry(rep, "tag prop d is missing [.'|']", path);
        }
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value is not an object [.'|']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_map_0_tab[0] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 1 } }, _jm_obj_0 };
        _jm_map_0_tab[1] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 2 } }, _jm_obj_1 };
        _jm_map_0_tab[2] = (constmap_t) { (constant_t) { cst_is_integer, { .i = 3 } }, _jm_obj_2 };
        jm_sort_constmap(_jm_map_0_tab, 3);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 1);
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
