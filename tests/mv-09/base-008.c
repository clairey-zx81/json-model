#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_1(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[1];
const size_t check_model_map_size = 1;

// object 
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object []", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "nom") == 0)
        {
            // handle must nom property
            must_count += 1;
            // .nom
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.nom]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.nom]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "prenom") == 0)
        {
            // handle must prenom property
            must_count += 1;
            // .prenom
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.prenom]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory property value [.prenom]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "age") == 0)
        {
            // handle may age property
            // .age
            res = json_is_integer(pval) && json_integer_value(pval) >= 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a 0 strict int [.age]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.age]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected []", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "nom") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <nom> []", path);
            }
            if (! (json_object_get(val, "prenom") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <prenom> []", path);
            }
        }
        return false;
    }
    return true;
}

// check $ ()
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    //
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at []", path);
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
