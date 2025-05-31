#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_25(const json_t* val, Path* path, Report* rep);
static bool json_model_9(const json_t* val, Path* path, Report* rep);
static bool _jm_cst_0_test(const json_t *);
static constant_t _jm_cst_0[8];
static bool json_model_18(const json_t* val, Path* path, Report* rep);
static bool json_model_19(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static pcre2_code *_jm_re_2_code = NULL;
static pcre2_match_data *_jm_re_2_data = NULL;
static bool _jm_re_2(const char *s);
static bool json_model_16(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_3_code = NULL;
static pcre2_match_data *_jm_re_3_data = NULL;
static bool _jm_re_3(const char *s);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_4_code = NULL;
static pcre2_match_data *_jm_re_4_data = NULL;
static bool _jm_re_4(const char *s);
static pcre2_code *_jm_re_5_code = NULL;
static pcre2_match_data *_jm_re_5_data = NULL;
static bool _jm_re_5(const char *s);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_map_tab[4];
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_8_map_tab[4];
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_11_map_tab[4];
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_14_map_tab[4];
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_17_map_tab[5];
static bool json_model_24(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_6_code = NULL;
static pcre2_match_data *_jm_re_6_data = NULL;
static bool _jm_re_6(const char *s);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $Model (.'$Model')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model'
    res = json_model_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RootModel [.'$Model']", path);
    }
    return res;
}

// check $ ()
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    //
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model []", path);
    }
    return res;
}

// check $Model#RootModel (.'$Model#RootModel')
static bool json_model_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#RootModel'
    // .'$Model#RootModel'.'|'.0
    res = json_model_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [.'$Model#RootModel'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Model#RootModel'.'|'.1
        res = json_model_9(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$Model#RootModel'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Model#RootModel'.'|'.2
            res = json_model_24(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Root [.'$Model#RootModel'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#RootModel'.'|']", path);
    }
    return res;
}

// check $Model#Array (.'$Model#Array')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Array'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // .'$Model#Array'.0
            res = json_model_19(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Array'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Array']", path);
    }
    return res;
}

static bool _jm_cst_0_test(const json_t *val)
{
  constant_t cst;
  jm_set_cst(&cst, val);
  return jm_search_cst(&cst, _jm_cst_0, 8);
}

// check $Model#Scalar (.'$Model#Scalar')
static bool json_model_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Scalar'
    res = _json_is_scalar(val) && _jm_cst_0_test(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$Model#Scalar'.'|']", path);
    }
    if (! res)
    {
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected type at [.'$Model#Scalar'.'|']", path);
        }
        if (res)
        {
            // .'$Model#Scalar'.'|'.0
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Scalar'.'|'.0]", path);
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Scalar'.'|']", path);
            }
        }
    }
    return res;
}

// check $Model#Model (.'$Model#Model')
static bool json_model_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Model'
    // .'$Model#Model'.'|'.0
    res = json_model_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [.'$Model#Model'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Model#Model'.'|'.1
        res = json_model_9(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$Model#Model'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Model#Model'.'|'.2
            res = json_model_16(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Elem [.'$Model#Model'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Model'.'|']", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// object .'$Model#Elem'.'|'.4
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Elem'.'|'.4]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Elem'.'|'.4.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.4.'#']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.4.#]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Model#Elem'.'|'.4.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$Model#Elem'.'|'.4.'/^[@|&^+/*]$/']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$Model#Elem'.'|'.4.''
            res = json_model_19(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Elem'.'|'.4.'']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// object .'$Model#Elem'.'|'.3
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Elem'.'|'.3]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$Model#Elem'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_1_idx;
                json_t *arr_1_item;
                json_array_foreach(pval, arr_1_idx, arr_1_item)
                {
                    Path arr_1_lpath = (Path) { NULL, arr_1_idx, (path ? &lpath_1 : NULL), NULL };
                    // .'$Model#Elem'.'|'.3.'^'.0
                    res = json_model_19(arr_1_item, ((path ? &lpath_1 : NULL) ? &arr_1_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Elem'.'|'.3.'^'.0]", ((path ? &lpath_1 : NULL) ? &arr_1_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Elem'.'|'.3.'^']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Elem'.'|'.3.^]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Elem'.'|'.3.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.3.'#']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.3.#]", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Elem'.'|'.3]", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <^> [.'$Model#Elem'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Model#Elem'.'|'.2
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Elem'.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$Model#Elem'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_2_idx;
                json_t *arr_2_item;
                json_array_foreach(pval, arr_2_idx, arr_2_item)
                {
                    Path arr_2_lpath = (Path) { NULL, arr_2_idx, (path ? &lpath_2 : NULL), NULL };
                    // .'$Model#Elem'.'|'.2.'&'.0
                    res = json_model_19(arr_2_item, ((path ? &lpath_2 : NULL) ? &arr_2_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Elem'.'|'.2.'&'.0]", ((path ? &lpath_2 : NULL) ? &arr_2_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Elem'.'|'.2.'&']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Elem'.'|'.2.&]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Elem'.'|'.2.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.2.'#']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.2.#]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Elem'.'|'.2]", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <&> [.'$Model#Elem'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Model#Elem'.'|'.1
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Elem'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$Model#Elem'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_3_idx;
                json_t *arr_3_item;
                json_array_foreach(pval, arr_3_idx, arr_3_item)
                {
                    Path arr_3_lpath = (Path) { NULL, arr_3_idx, (path ? &lpath_3 : NULL), NULL };
                    // .'$Model#Elem'.'|'.1.'|'.0
                    res = json_model_19(arr_3_item, ((path ? &lpath_3 : NULL) ? &arr_3_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Elem'.'|'.1.'|'.0]", ((path ? &lpath_3 : NULL) ? &arr_3_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Elem'.'|'.1.'|']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Elem'.'|'.1.|]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Elem'.'|'.1.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.1.'#']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.1.#]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Elem'.'|'.1]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <|> [.'$Model#Elem'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

static bool _jm_re_2(const char *s)
{
  int rc = pcre2_match(_jm_re_2_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_2_data, NULL);
  return rc >= 0;
}

// object .'$Model#Elem'.'|'.0
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Elem'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$Model#Elem'.'|'.0.'@'
            res = json_model_19(pval, (path ? &lpath_4 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Elem'.'|'.0.'@']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Elem'.'|'.0.@]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Elem'.'|'.0.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.0.'#']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.0.#]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "!") == 0)
        {
            // handle may ! property
            // .'$Model#Elem'.'|'.0.'!'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Model#Elem'.'|'.0.'!']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Elem'.'|'.0.!]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                // .'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_4 : NULL));
                }
                if (! res)
                {
                    // .'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_4 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Model#Elem'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_5(pval, (path ? &lpath_4 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$Model#Elem'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Elem'.'|'.0]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <@> [.'$Model#Elem'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Model#Elem (.'$Model#Elem')
static bool json_model_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Elem'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$Model#Elem'.'|']", path);
    }
    if (res)
    {
        // .'$Model#Elem'.'|'.0
        res = _jm_obj_4(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Elem'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Model#Elem'.'|'.1
            res = _jm_obj_3(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Elem'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$Model#Elem'.'|'.2
                res = _jm_obj_2(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Elem'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$Model#Elem'.'|'.3
                    res = _jm_obj_1(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Elem'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$Model#Elem'.'|'.4
                        res = _jm_obj_0(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Elem'.'|'.4]", path);
                        }
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Elem'.'|']", path);
        }
    }
    return res;
}

// check $Model#Val (.'$Model#Val')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Val'
    // .'$Model#Val'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [.'$Model#Val'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Model#Val'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$Model#Val'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Model#Val'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Model#Val'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$Model#Val'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Model#Val'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$Model#Val'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Val'.'|'.4]", path);
                    }
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Val'.'|']", path);
    }
    return res;
}

// check _jm_obj_5_map_# (.'$Model#Root'.'|'.4.'#')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.4.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.4.'#']", path);
    }
    return res;
}

static bool _jm_re_3(const char *s)
{
  int rc = pcre2_match(_jm_re_3_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_3_data, NULL);
  return rc >= 0;
}

// object .'$Model#Root'.'|'.4.'$'
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.4.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.4.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.4.'$'.'#']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.4.'$'.#]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Model#Root'.'|'.4.'$'.''
            res = json_model_4(pval, (path ? &lpath_6 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.4.'$'.'']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.4.'$'.]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.4.'$'.'/.+/'
            res = json_model_19(pval, (path ? &lpath_6 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.4.'$'.'/.+/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.4.'$']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_5_map_$ (.'$Model#Root'.'|'.4.'$')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.4.'$'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.4.'$']", path);
    }
    return res;
}

static bool _jm_re_4(const char *s)
{
  int rc = pcre2_match(_jm_re_4_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_4_data, NULL);
  return rc >= 0;
}

static bool _jm_re_5(const char *s)
{
  int rc = pcre2_match(_jm_re_5_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_5_data, NULL);
  return rc >= 0;
}

// object .'$Model#Root'.'|'.4.'%'
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.4.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.4.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.4.'%'.'#']", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.4.'%'.#]", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.4.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_5(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Root'.'|'.4.'%'.'/^\\\\..+$/']", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.4.'%']", (path ? &lpath_7 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_5_map_% (.'$Model#Root'.'|'.4.'%')
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.4.'%'
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.4.'%']", path);
    }
    return res;
}

// check _jm_obj_5_map_~ (.'$Model#Root'.'|'.4.'~')
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.4.'~'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.4.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_map_tab, 4);
}

// object .'$Model#Root'.'|'.4
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.4]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_5_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_5 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.4]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.4.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$Model#Root'.'|'.4.'/^[@|&^+/*]$/']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$Model#Root'.'|'.4.''
            res = json_model_19(pval, (path ? &lpath_5 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.4.'']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// check _jm_obj_8_map_# (.'$Model#Root'.'|'.3.'#')
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.3.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.3.'#']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.3.'$'
static bool _jm_obj_9(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.3.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_9 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.3.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.3.'$'.'#']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.3.'$'.#]", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Model#Root'.'|'.3.'$'.''
            res = json_model_4(pval, (path ? &lpath_9 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.3.'$'.'']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.3.'$'.]", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.3.'$'.'/.+/'
            res = json_model_19(pval, (path ? &lpath_9 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.3.'$'.'/.+/']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.3.'$']", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_8_map_$ (.'$Model#Root'.'|'.3.'$')
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.3.'$'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.3.'$']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.3.'%'
static bool _jm_obj_10(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.3.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_10 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.3.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.3.'%'.'#']", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.3.'%'.#]", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.3.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_5(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Root'.'|'.3.'%'.'/^\\\\..+$/']", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.3.'%']", (path ? &lpath_10 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_8_map_% (.'$Model#Root'.'|'.3.'%')
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.3.'%'
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.3.'%']", path);
    }
    return res;
}

// check _jm_obj_8_map_~ (.'$Model#Root'.'|'.3.'~')
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.3.'~'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.3.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_8_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_8_map_tab, 4);
}

// object .'$Model#Root'.'|'.3
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.3]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_8 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$Model#Root'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_4_idx;
                json_t *arr_4_item;
                json_array_foreach(pval, arr_4_idx, arr_4_item)
                {
                    Path arr_4_lpath = (Path) { NULL, arr_4_idx, (path ? &lpath_8 : NULL), NULL };
                    // .'$Model#Root'.'|'.3.'^'.0
                    res = json_model_19(arr_4_item, ((path ? &lpath_8 : NULL) ? &arr_4_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.3.'^'.0]", ((path ? &lpath_8 : NULL) ? &arr_4_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Root'.'|'.3.'^']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Root'.'|'.3.^]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_8_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_8 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.3]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.3]", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <^> [.'$Model#Root'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_11_map_# (.'$Model#Root'.'|'.2.'#')
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.2.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.2.'#']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.2.'$'
static bool _jm_obj_12(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.2.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_12 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.2.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.2.'$'.'#']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.2.'$'.#]", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Model#Root'.'|'.2.'$'.''
            res = json_model_4(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.2.'$'.'']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.2.'$'.]", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.2.'$'.'/.+/'
            res = json_model_19(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.2.'$'.'/.+/']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.2.'$']", (path ? &lpath_12 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_11_map_$ (.'$Model#Root'.'|'.2.'$')
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.2.'$'
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.2.'$']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.2.'%'
static bool _jm_obj_13(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.2.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_13 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.2.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.2.'%'.'#']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.2.'%'.#]", (path ? &lpath_13 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.2.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_5(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Root'.'|'.2.'%'.'/^\\\\..+$/']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.2.'%']", (path ? &lpath_13 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_11_map_% (.'$Model#Root'.'|'.2.'%')
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.2.'%'
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.2.'%']", path);
    }
    return res;
}

// check _jm_obj_11_map_~ (.'$Model#Root'.'|'.2.'~')
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.2.'~'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.2.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_11_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_11_map_tab, 4);
}

// object .'$Model#Root'.'|'.2
static bool _jm_obj_11(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.2]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_11 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$Model#Root'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_5_idx;
                json_t *arr_5_item;
                json_array_foreach(pval, arr_5_idx, arr_5_item)
                {
                    Path arr_5_lpath = (Path) { NULL, arr_5_idx, (path ? &lpath_11 : NULL), NULL };
                    // .'$Model#Root'.'|'.2.'&'.0
                    res = json_model_19(arr_5_item, ((path ? &lpath_11 : NULL) ? &arr_5_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.2.'&'.0]", ((path ? &lpath_11 : NULL) ? &arr_5_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Root'.'|'.2.'&']", (path ? &lpath_11 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Root'.'|'.2.&]", (path ? &lpath_11 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_11_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_11 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.2]", (path ? &lpath_11 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.2]", (path ? &lpath_11 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <&> [.'$Model#Root'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_14_map_# (.'$Model#Root'.'|'.1.'#')
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.1.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.1.'#']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.1.'$'
static bool _jm_obj_15(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.1.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_15 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.1.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.1.'$'.'#']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.1.'$'.#]", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Model#Root'.'|'.1.'$'.''
            res = json_model_4(pval, (path ? &lpath_15 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.1.'$'.'']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.1.'$'.]", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.1.'$'.'/.+/'
            res = json_model_19(pval, (path ? &lpath_15 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.1.'$'.'/.+/']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.1.'$']", (path ? &lpath_15 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_14_map_$ (.'$Model#Root'.'|'.1.'$')
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.1.'$'
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.1.'$']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.1.'%'
static bool _jm_obj_16(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.1.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_16 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.1.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.1.'%'.'#']", (path ? &lpath_16 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.1.'%'.#]", (path ? &lpath_16 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.1.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_5(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Root'.'|'.1.'%'.'/^\\\\..+$/']", (path ? &lpath_16 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.1.'%']", (path ? &lpath_16 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_14_map_% (.'$Model#Root'.'|'.1.'%')
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.1.'%'
    res = _jm_obj_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.1.'%']", path);
    }
    return res;
}

// check _jm_obj_14_map_~ (.'$Model#Root'.'|'.1.'~')
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.1.'~'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.1.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_14_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_14_map_tab, 4);
}

// object .'$Model#Root'.'|'.1
static bool _jm_obj_14(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_14 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$Model#Root'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_6_idx;
                json_t *arr_6_item;
                json_array_foreach(pval, arr_6_idx, arr_6_item)
                {
                    Path arr_6_lpath = (Path) { NULL, arr_6_idx, (path ? &lpath_14 : NULL), NULL };
                    // .'$Model#Root'.'|'.1.'|'.0
                    res = json_model_19(arr_6_item, ((path ? &lpath_14 : NULL) ? &arr_6_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.1.'|'.0]", ((path ? &lpath_14 : NULL) ? &arr_6_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Model#Root'.'|'.1.'|']", (path ? &lpath_14 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Root'.'|'.1.|]", (path ? &lpath_14 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_14_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_14 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.1]", (path ? &lpath_14 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.1]", (path ? &lpath_14 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <|> [.'$Model#Root'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_17_map_! (.'$Model#Root'.'|'.0.'!')
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.0.'!'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Model#Root'.'|'.0.'!']", path);
    }
    return res;
}

// check _jm_obj_17_map_# (.'$Model#Root'.'|'.0.'#')
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.0.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.0.'#']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.0.'$'
static bool _jm_obj_18(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.0.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_18 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.0.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.0.'$'.'#']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.0.'$'.#]", (path ? &lpath_18 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Model#Root'.'|'.0.'$'.''
            res = json_model_4(pval, (path ? &lpath_18 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.0.'$'.'']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.0.'$'.]", (path ? &lpath_18 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.0.'$'.'/.+/'
            res = json_model_19(pval, (path ? &lpath_18 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.0.'$'.'/.+/']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.0.'$']", (path ? &lpath_18 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_17_map_$ (.'$Model#Root'.'|'.0.'$')
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.0.'$'
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.0.'$']", path);
    }
    return res;
}

// object .'$Model#Root'.'|'.0.'%'
static bool _jm_obj_19(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.0.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_19 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Model#Root'.'|'.0.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.0.'%'.'#']", (path ? &lpath_19 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.0.'%'.#]", (path ? &lpath_19 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Model#Root'.'|'.0.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_5(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Root'.'|'.0.'%'.'/^\\\\..+$/']", (path ? &lpath_19 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.0.'%']", (path ? &lpath_19 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_17_map_% (.'$Model#Root'.'|'.0.'%')
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.0.'%'
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.0.'%']", path);
    }
    return res;
}

// check _jm_obj_17_map_~ (.'$Model#Root'.'|'.0.'~')
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'.'|'.0.'~'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Model#Root'.'|'.0.'~']", path);
    }
    return res;
}

static check_fun_t _jm_obj_17_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_17_map_tab, 5);
}

// object .'$Model#Root'.'|'.0
static bool _jm_obj_17(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Model#Root'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_17 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$Model#Root'.'|'.0.'@'
            res = json_model_19(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Model#Root'.'|'.0.'@']", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$Model#Root'.'|'.0.@]", (path ? &lpath_17 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_17_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_17 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$Model#Root'.'|'.0]", (path ? &lpath_17 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                // .'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_17 : NULL));
                }
                if (! res)
                {
                    // .'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_17 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Model#Root'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_5(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$Model#Root'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$Model#Root'.'|'.0]", (path ? &lpath_17 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <@> [.'$Model#Root'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Model#Root (.'$Model#Root')
static bool json_model_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Root'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$Model#Root'.'|']", path);
    }
    if (res)
    {
        // .'$Model#Root'.'|'.0
        res = _jm_obj_17(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Model#Root'.'|'.1
            res = _jm_obj_14(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$Model#Root'.'|'.2
                res = _jm_obj_11(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$Model#Root'.'|'.3
                    res = _jm_obj_8(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$Model#Root'.'|'.4
                        res = _jm_obj_5(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$Model#Root'.'|'.4]", path);
                        }
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Model#Root'.'|']", path);
        }
    }
    return res;
}

static bool _jm_re_6(const char *s)
{
  int rc = pcre2_match(_jm_re_6_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_6_data, NULL);
  return rc >= 0;
}

// check $Model#Url (.'$Model#Url')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$Model#Url'
    // "/^((file|https?)://.+|\\./.*|\\.\\./.*)$/"
    res = json_is_string(val) && _jm_re_6(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$Model#Url']", path);
    }
    return res;
}

check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 2);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_null, { .s = NULL } };
        _jm_cst_0[1] = (constant_t) { cst_is_bool, { .b = true } };
        _jm_cst_0[2] = (constant_t) { cst_is_integer, { .i = 0 } };
        _jm_cst_0[3] = (constant_t) { cst_is_integer, { .i = 1 } };
        _jm_cst_0[4] = (constant_t) { cst_is_integer, { .i = -1 } };
        _jm_cst_0[5] = (constant_t) { cst_is_float, { .f = 0.0 } };
        _jm_cst_0[6] = (constant_t) { cst_is_float, { .f = 1.0 } };
        _jm_cst_0[7] = (constant_t) { cst_is_float, { .f = -1.0 } };
        jm_sort_cst(_jm_cst_0, 8);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^[@|&^+/*]$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "^(<=|>=|<|>|≥|≤)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
        _jm_re_2_code = pcre2_compile((PCRE2_SPTR) "^(=|!=|≠)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_2_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_2_data = pcre2_match_data_create_from_pattern(_jm_re_2_code, NULL);
        _jm_re_3_code = pcre2_compile((PCRE2_SPTR) ".+", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_3_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_3_data = pcre2_match_data_create_from_pattern(_jm_re_3_code, NULL);
        _jm_re_4_code = pcre2_compile((PCRE2_SPTR) "^\\..+$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_4_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_4_data = pcre2_match_data_create_from_pattern(_jm_re_4_code, NULL);
        _jm_re_5_code = pcre2_compile((PCRE2_SPTR) "^([#|&^+/*@~=$%]|[<>!]=?)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_5_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_5_data = pcre2_match_data_create_from_pattern(_jm_re_5_code, NULL);
        _jm_obj_5_map_tab[0] = (propmap_t) { "#", _jm_f_0 };
        _jm_obj_5_map_tab[1] = (propmap_t) { "$", _jm_f_1 };
        _jm_obj_5_map_tab[2] = (propmap_t) { "%", _jm_f_2 };
        _jm_obj_5_map_tab[3] = (propmap_t) { "~", _jm_f_3 };
        jm_sort_propmap(_jm_obj_5_map_tab, 4);
        _jm_obj_8_map_tab[0] = (propmap_t) { "#", _jm_f_4 };
        _jm_obj_8_map_tab[1] = (propmap_t) { "$", _jm_f_5 };
        _jm_obj_8_map_tab[2] = (propmap_t) { "%", _jm_f_6 };
        _jm_obj_8_map_tab[3] = (propmap_t) { "~", _jm_f_7 };
        jm_sort_propmap(_jm_obj_8_map_tab, 4);
        _jm_obj_11_map_tab[0] = (propmap_t) { "#", _jm_f_8 };
        _jm_obj_11_map_tab[1] = (propmap_t) { "$", _jm_f_9 };
        _jm_obj_11_map_tab[2] = (propmap_t) { "%", _jm_f_10 };
        _jm_obj_11_map_tab[3] = (propmap_t) { "~", _jm_f_11 };
        jm_sort_propmap(_jm_obj_11_map_tab, 4);
        _jm_obj_14_map_tab[0] = (propmap_t) { "#", _jm_f_12 };
        _jm_obj_14_map_tab[1] = (propmap_t) { "$", _jm_f_13 };
        _jm_obj_14_map_tab[2] = (propmap_t) { "%", _jm_f_14 };
        _jm_obj_14_map_tab[3] = (propmap_t) { "~", _jm_f_15 };
        jm_sort_propmap(_jm_obj_14_map_tab, 4);
        _jm_obj_17_map_tab[0] = (propmap_t) { "!", _jm_f_16 };
        _jm_obj_17_map_tab[1] = (propmap_t) { "#", _jm_f_17 };
        _jm_obj_17_map_tab[2] = (propmap_t) { "$", _jm_f_18 };
        _jm_obj_17_map_tab[3] = (propmap_t) { "%", _jm_f_19 };
        _jm_obj_17_map_tab[4] = (propmap_t) { "~", _jm_f_20 };
        jm_sort_propmap(_jm_obj_17_map_tab, 5);
        _jm_re_6_code = pcre2_compile((PCRE2_SPTR) "^((file|https?)://.+|\\./.*|\\.\\./.*)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_6_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_6_data = pcre2_match_data_create_from_pattern(_jm_re_6_code, NULL);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "Model", json_model_3 };
        jm_sort_propmap(check_model_map_tab, 2);
    }
    return NULL;
}

void CHECK_free(void)
{
    if (initialized)
    {
        initialized = false;

        // cleanup code
        pcre2_match_data_free(_jm_re_0_data);
        pcre2_code_free(_jm_re_0_code);
        pcre2_match_data_free(_jm_re_1_data);
        pcre2_code_free(_jm_re_1_code);
        pcre2_match_data_free(_jm_re_2_data);
        pcre2_code_free(_jm_re_2_code);
        pcre2_match_data_free(_jm_re_3_data);
        pcre2_code_free(_jm_re_3_code);
        pcre2_match_data_free(_jm_re_4_data);
        pcre2_code_free(_jm_re_4_code);
        pcre2_match_data_free(_jm_re_5_data);
        pcre2_code_free(_jm_re_5_code);
        pcre2_match_data_free(_jm_re_6_data);
        pcre2_code_free(_jm_re_6_code);
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
