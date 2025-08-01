//
// Generated by JSON Model Compiler version 2.0b1
// see https://github.com/clairey-zx81/json-model
//

// regular expression engine
#include <stddef.h>
#include <cre2.h>

#include <json-model.h>
#define JSON_MODEL_VERSION "2.0b1"

static jm_constmap_t _jm_map_0_tab[2];
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// object .'|'.0
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "t") == 0)
        {
            // handle must t property
            must_count += 1;
            // .'|'.0.t
            res = json_is_integer(pval) && json_integer_value(pval) == 1;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected =1 [.'|'.0.t]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.0.t]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "a") == 0)
        {
            // handle must a property
            must_count += 1;
            // .'|'.0.a
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.0.a]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.0.a]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.0]", (path ? &lpath_0 : NULL));
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
            if (! (json_object_get(val, "t") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <t> [.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'|'.1
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "t") == 0)
        {
            // handle must t property
            must_count += 1;
            // .'|'.1.t
            res = json_is_integer(pval) && json_integer_value(pval) == 2;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected =2 [.'|'.1.t]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.1.t]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "b") == 0)
        {
            // handle must b property
            must_count += 1;
            // .'|'.1.b
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'|'.1.b]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'|'.1.b]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'|'.1]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "b") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <b> [.'|'.1]", path);
            }
            if (! (json_object_get(val, "t") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <t> [.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

static jm_check_fun_t _jm_map_0(json_t *val)
{
    jm_constant_t cst;
    jm_set_cst(&cst, val);
    return jm_search_constmap(&cst, _jm_map_0_tab, 2);
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_is_object(val);
    if (res)
    {
        json_t * tag_0 = json_object_get(val, "t");
        if (tag_0 != NULL)
        {
            jm_check_fun_t fun_0 = _jm_map_0(tag_0);
            if (fun_0 != NULL)
            {
                res = fun_0(val, path, rep);
            }
            else
            {
                res = false;
                if (rep) jm_report_add_entry(rep, "tag <t> value not found [.'|']", path);
            }
        }
        else
        {
            res = false;
            if (rep) jm_report_add_entry(rep, "tag prop <t> is missing [.'|']", path);
        }
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value is not an object [.'|']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 1);
}

static bool initialized = false;

const char *check_model_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_map_0_tab[0] = (jm_constmap_t) { (jm_constant_t) { cst_is_integer, { .i = 1 } }, _jm_obj_0 };
        _jm_map_0_tab[1] = (jm_constmap_t) { (jm_constant_t) { cst_is_integer, { .i = 2 } }, _jm_obj_1 };
        jm_sort_constmap(_jm_map_0_tab, 2);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        jm_sort_propmap(check_model_map_tab, 1);
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
