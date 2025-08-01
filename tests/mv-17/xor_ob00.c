//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[3];
const size_t check_model_map_size = 3;

// object .'$A'.'|'.1
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$A'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // .'$A'.'|'.1.b
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$A'.'|'.1.b]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$A'.'|'.1.b]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$A'.'|'.1]", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "b") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <b> [.'$A'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$A'.'|'.0
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$A'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // .'$A'.'|'.0.a
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$A'.'|'.0.a]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$A'.'|'.0.a]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$A'.'|'.0]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "a") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <a> [.'$A'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $A (.'$A')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$A'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$A'.'|']", path);
    }
    if (res)
    {
        // .'$A'.'|'.0
        res = _jm_obj_1(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$A'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$A'.'|'.1
            res = _jm_obj_0(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected element [.'$A'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$A'.'|']", path);
        }
    }
    return res;
}

// object .'$B'.'|'.1
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$B'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'$B'.'|'.1.d
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$B'.'|'.1.d]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$B'.'|'.1.d]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$B'.'|'.1]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <d> [.'$B'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$B'.'|'.0
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$B'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "c") == 0)
        {
            // handle must c property
            must_count += 1;
            // .'$B'.'|'.0.c
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$B'.'|'.0.c]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$B'.'|'.0.c]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$B'.'|'.0]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "c") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <c> [.'$B'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $B (.'$B')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$B'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$B'.'|']", path);
    }
    if (res)
    {
        // .'$B'.'|'.0
        res = _jm_obj_3(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'$B'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$B'.'|'.1
            res = _jm_obj_2(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected element [.'$B'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$B'.'|']", path);
        }
    }
    return res;
}

// object .'|'.3
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'|'.3]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // .'|'.3.b
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.3.b]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.3.b]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'|'.3.d
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.3.d]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.3.d]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.3]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "b") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <b> [.'|'.3]", path);
            }
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <d> [.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.2
static bool _jm_obj_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_5 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // .'|'.2.b
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.2.b]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.2.b]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "c") == 0)
        {
            // handle must c property
            must_count += 1;
            // .'|'.2.c
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.2.c]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.2.c]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.2]", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "b") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <b> [.'|'.2]", path);
            }
            if (! (json_object_get(val, "c") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <c> [.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.1
static bool _jm_obj_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_6 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // .'|'.1.a
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.1.a]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.1.a]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "d") == 0)
        {
            // handle must d property
            must_count += 1;
            // .'|'.1.d
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.1.d]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.1.d]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.1]", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "a") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <a> [.'|'.1]", path);
            }
            if (! (json_object_get(val, "d") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <d> [.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.0
static bool _jm_obj_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_7 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // .'|'.0.a
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.0.a]", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.0.a]", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "c") == 0)
        {
            // handle must c property
            must_count += 1;
            // .'|'.0.c
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.0.c]", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.0.c]", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.0]", (path ? &lpath_7 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "a") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <a> [.'|'.0]", path);
            }
            if (! (json_object_get(val, "c") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <c> [.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // 4 property combinations: ac ad bc bd
    // .
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'|']", path);
    }
    if (res)
    {
        // .'|'.0
        res = _jm_obj_7(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected element [.'|'.0]", path);
        }
        if (! res)
        {
            // .'|'.1
            res = _jm_obj_6(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected element [.'|'.1]", path);
            }
            if (! res)
            {
                // .'|'.2
                res = _jm_obj_5(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected element [.'|'.2]", path);
                }
                if (! res)
                {
                    // .'|'.3
                    res = _jm_obj_4(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected element [.'|'.3]", path);
                    }
                }
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'|']", path);
        }
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 3);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "A", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "B", json_model_3 };
        jm_sort_propmap(check_model_map_tab, 3);
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
check_model(const json_t *val, const char *name, bool *error, char **reasons)
{
    return jm_generic_entry(check_model_init, check_model_map, val, name, error, reasons);
}
