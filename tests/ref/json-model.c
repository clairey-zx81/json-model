#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static pcre2_code *_jm_re_2_code = NULL;
static pcre2_match_data *_jm_re_2_data = NULL;
static bool _jm_re_2(const char *s);
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_3_code = NULL;
static pcre2_match_data *_jm_re_3_data = NULL;
static bool _jm_re_3(const char *s);
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_cst_0_test(const json_t *);
static jm_constant_t _jm_cst_0[8];
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_4_code = NULL;
static pcre2_match_data *_jm_re_4_data = NULL;
static bool _jm_re_4(const char *s);
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_5_code = NULL;
static pcre2_match_data *_jm_re_5_data = NULL;
static bool _jm_re_5(const char *s);
static pcre2_code *_jm_re_6_code = NULL;
static pcre2_match_data *_jm_re_6_data = NULL;
static bool _jm_re_6(const char *s);
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_7_code = NULL;
static pcre2_match_data *_jm_re_7_data = NULL;
static bool _jm_re_7(const char *s);
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_23_map_tab[4];
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_26_map_tab[4];
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_29_map_tab[4];
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_32_map_tab[4];
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_35_map_tab[4];
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_38_map_tab[5];
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[23];
const size_t check_model_map_size = 23;

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check $Url (.'$Url')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Url'
    // "/^((file|https?)://.+|\\./.*|\\.\\./.*)$/"
    res = json_is_string(val) && _jm_re_0(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected /^((file|https?)://.+|\\./.*|\\.\\./.*)$/ [.'$Url']", path);
    }
    return res;
}

// check $Val (.'$Val')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Val'
    // .'$Val'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [.'$Val'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Val'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$Val'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Val'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Val'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$Val'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Val'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$Val'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Val'.'|'.4]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Val'.'|']", path);
    }
    return res;
}

// check $Any (.'$Any')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Any'
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Any']", path);
    }
    return res;
}

// check $None (.'$None')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$None'
    res = false;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$None']", path);
    }
    return res;
}

// object .'$Common'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Common']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Common'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Common'.'#']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Common'.'#']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Common']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $Common (.'$Common')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Common'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Common']", path);
    }
    return res;
}

// check $Array (.'$Array')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
            // .'$Array'.0
            res = json_model_17(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Array'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Array']", path);
    }
    return res;
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

// object .'$Constraint'
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Constraint']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$Constraint'.'@'
            res = json_model_17(pval, (path ? &lpath_1 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Constraint'.'@']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Constraint'.'@']", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "!") == 0)
        {
            // handle may ! property
            // .'$Constraint'.'!'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Constraint'.'!']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Constraint'.'!']", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                // .'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_1 : NULL));
                }
                if (! res)
                {
                    // .'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_1 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Constraint'.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Constraint'.'/^(=|!=|≠)$/'
            res = json_model_3(pval, (path ? &lpath_1 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$Constraint'.'/^(=|!=|≠)$/']", (path ? &lpath_1 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Constraint']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <@> [.'$Constraint']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Constraint (.'$Constraint')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Constraint'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Constraint']", path);
    }
    return res;
}

// object .'$Or'
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Or']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$Or'.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_1_idx;
                json_t *arr_1_item;
                json_array_foreach(pval, arr_1_idx, arr_1_item)
                {
                    jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, (path ? &lpath_2 : NULL), NULL };
                    // .'$Or'.'|'.0
                    res = json_model_17(arr_1_item, ((path ? &lpath_2 : NULL) ? &arr_1_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Or'.'|'.0]", ((path ? &lpath_2 : NULL) ? &arr_1_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Or'.'|']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Or'.'|']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Or']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <|> [.'$Or']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Or (.'$Or')
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Or'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Or']", path);
    }
    return res;
}

// object .'$And'
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$And']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$And'.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_2_idx;
                json_t *arr_2_item;
                json_array_foreach(pval, arr_2_idx, arr_2_item)
                {
                    jm_path_t arr_2_lpath = (jm_path_t) { NULL, arr_2_idx, (path ? &lpath_3 : NULL), NULL };
                    // .'$And'.'&'.0
                    res = json_model_17(arr_2_item, ((path ? &lpath_3 : NULL) ? &arr_2_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$And'.'&'.0]", ((path ? &lpath_3 : NULL) ? &arr_2_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$And'.'&']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$And'.'&']", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$And']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <&> [.'$And']", path);
            }
        }
        return false;
    }
    return true;
}

// check $And (.'$And')
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$And'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$And']", path);
    }
    return res;
}

// object .'$Xor'
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Xor']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$Xor'.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_3_idx;
                json_t *arr_3_item;
                json_array_foreach(pval, arr_3_idx, arr_3_item)
                {
                    jm_path_t arr_3_lpath = (jm_path_t) { NULL, arr_3_idx, (path ? &lpath_4 : NULL), NULL };
                    // .'$Xor'.'^'.0
                    res = json_model_17(arr_3_item, ((path ? &lpath_4 : NULL) ? &arr_3_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Xor'.'^'.0]", ((path ? &lpath_4 : NULL) ? &arr_3_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Xor'.'^']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Xor'.'^']", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Xor']", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <^> [.'$Xor']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Xor (.'$Xor')
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Xor'
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Xor']", path);
    }
    return res;
}

// object .'$Add'
static bool _jm_obj_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Add']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_5 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "+") == 0)
        {
            // handle must + property
            must_count += 1;
            // .'$Add'.'+'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_4_idx;
                json_t *arr_4_item;
                json_array_foreach(pval, arr_4_idx, arr_4_item)
                {
                    jm_path_t arr_4_lpath = (jm_path_t) { NULL, arr_4_idx, (path ? &lpath_5 : NULL), NULL };
                    // .'$Add'.'+'.0
                    res = json_model_17(arr_4_item, ((path ? &lpath_5 : NULL) ? &arr_4_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Add'.'+'.0]", ((path ? &lpath_5 : NULL) ? &arr_4_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Add'.'+']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Add'.'+']", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Add']", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "+") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <+> [.'$Add']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Add (.'$Add')
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Add'
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Add']", path);
    }
    return res;
}

static bool _jm_re_3(const char *s)
{
  int rc = pcre2_match(_jm_re_3_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_3_data, NULL);
  return rc >= 0;
}

// object .'$Obj'
static bool _jm_obj_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Obj']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_6 = (jm_path_t) { prop, 0, path, NULL };
        if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Obj'.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$Obj'.'/^[@|&^+/*]$/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$Obj'.''
            res = json_model_17(pval, (path ? &lpath_6 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Obj'.'']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// check $Obj (.'$Obj')
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Obj'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Obj']", path);
    }
    return res;
}

// object .'$Elem'.'|'.5
static bool _jm_obj_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.5]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_7 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.5.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.5.'#']", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.5.'#']", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Elem'.'|'.5.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$Elem'.'|'.5.'/^[@|&^+/*]$/']", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$Elem'.'|'.5.''
            res = json_model_17(pval, (path ? &lpath_7 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.5.'']", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// object .'$Elem'.'|'.4
static bool _jm_obj_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.4]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_8 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "+") == 0)
        {
            // handle must + property
            must_count += 1;
            // .'$Elem'.'|'.4.'+'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_5_idx;
                json_t *arr_5_item;
                json_array_foreach(pval, arr_5_idx, arr_5_item)
                {
                    jm_path_t arr_5_lpath = (jm_path_t) { NULL, arr_5_idx, (path ? &lpath_8 : NULL), NULL };
                    // .'$Elem'.'|'.4.'+'.0
                    res = json_model_17(arr_5_item, ((path ? &lpath_8 : NULL) ? &arr_5_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.4.'+'.0]", ((path ? &lpath_8 : NULL) ? &arr_5_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Elem'.'|'.4.'+']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Elem'.'|'.4.'+']", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.4.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.4.'#']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.4.'#']", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Elem'.'|'.4]", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "+") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <+> [.'$Elem'.'|'.4]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Elem'.'|'.3
static bool _jm_obj_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.3]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_9 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$Elem'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_6_idx;
                json_t *arr_6_item;
                json_array_foreach(pval, arr_6_idx, arr_6_item)
                {
                    jm_path_t arr_6_lpath = (jm_path_t) { NULL, arr_6_idx, (path ? &lpath_9 : NULL), NULL };
                    // .'$Elem'.'|'.3.'^'.0
                    res = json_model_17(arr_6_item, ((path ? &lpath_9 : NULL) ? &arr_6_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.3.'^'.0]", ((path ? &lpath_9 : NULL) ? &arr_6_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Elem'.'|'.3.'^']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Elem'.'|'.3.'^']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.3.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.3.'#']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.3.'#']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Elem'.'|'.3]", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <^> [.'$Elem'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Elem'.'|'.2
static bool _jm_obj_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_10 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$Elem'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_7_idx;
                json_t *arr_7_item;
                json_array_foreach(pval, arr_7_idx, arr_7_item)
                {
                    jm_path_t arr_7_lpath = (jm_path_t) { NULL, arr_7_idx, (path ? &lpath_10 : NULL), NULL };
                    // .'$Elem'.'|'.2.'&'.0
                    res = json_model_17(arr_7_item, ((path ? &lpath_10 : NULL) ? &arr_7_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.2.'&'.0]", ((path ? &lpath_10 : NULL) ? &arr_7_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Elem'.'|'.2.'&']", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Elem'.'|'.2.'&']", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.2.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.2.'#']", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.2.'#']", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Elem'.'|'.2]", (path ? &lpath_10 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <&> [.'$Elem'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Elem'.'|'.1
static bool _jm_obj_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_11 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$Elem'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_8_idx;
                json_t *arr_8_item;
                json_array_foreach(pval, arr_8_idx, arr_8_item)
                {
                    jm_path_t arr_8_lpath = (jm_path_t) { NULL, arr_8_idx, (path ? &lpath_11 : NULL), NULL };
                    // .'$Elem'.'|'.1.'|'.0
                    res = json_model_17(arr_8_item, ((path ? &lpath_11 : NULL) ? &arr_8_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.1.'|'.0]", ((path ? &lpath_11 : NULL) ? &arr_8_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Elem'.'|'.1.'|']", (path ? &lpath_11 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Elem'.'|'.1.'|']", (path ? &lpath_11 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.1.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.1.'#']", (path ? &lpath_11 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.1.'#']", (path ? &lpath_11 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Elem'.'|'.1]", (path ? &lpath_11 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <|> [.'$Elem'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Elem'.'|'.0
static bool _jm_obj_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Elem'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_12 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$Elem'.'|'.0.'@'
            res = json_model_17(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Elem'.'|'.0.'@']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Elem'.'|'.0.'@']", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Elem'.'|'.0.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.0.'#']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.0.'#']", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "!") == 0)
        {
            // handle may ! property
            // .'$Elem'.'|'.0.'!'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Elem'.'|'.0.'!']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Elem'.'|'.0.'!']", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                // .'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_12 : NULL));
                }
                if (! res)
                {
                    // .'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_12 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Elem'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_3(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$Elem'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Elem'.'|'.0]", (path ? &lpath_12 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <@> [.'$Elem'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Elem (.'$Elem')
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Elem'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$Elem'.'|']", path);
    }
    if (res)
    {
        // .'$Elem'.'|'.0
        res = _jm_obj_12(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Elem'.'|'.1
            res = _jm_obj_11(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$Elem'.'|'.2
                res = _jm_obj_10(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$Elem'.'|'.3
                    res = _jm_obj_9(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$Elem'.'|'.4
                        res = _jm_obj_8(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // .'$Elem'.'|'.5
                            res = _jm_obj_7(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Elem'.'|'.5]", path);
                            }
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Elem'.'|']", path);
        }
    }
    return res;
}

// object .'$Trafo'.'|'.2.'*'.'|'.1
static bool _jm_obj_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Trafo'.'|'.2.'*'.'|'.1]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_14 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Trafo'.'|'.2.'*'.'|'.1.''
        res = json_model_17(pval, (path ? &lpath_14 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Trafo'.'|'.2.'*'.'|'.1.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$Trafo'.'|'.2
static bool _jm_obj_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Trafo'.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_13 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "*") == 0)
        {
            // handle must * property
            must_count += 1;
            // .'$Trafo'.'|'.2.'*'
            // .'$Trafo'.'|'.2.'*'.'|'.0
            res = json_is_array(pval);
            if (res)
            {
                // accept any array
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Trafo'.'|'.2.'*'.'|'.0]", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                // .'$Trafo'.'|'.2.'*'.'|'.1
                res = _jm_obj_14(pval, (path ? &lpath_13 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$Trafo'.'|'.2.'*'.'|'.1]", (path ? &lpath_13 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Trafo'.'|'.2.'*'.'|']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Trafo'.'|'.2.'*']", (path ? &lpath_13 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Trafo'.'|'.2.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Trafo'.'|'.2.'#']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Trafo'.'|'.2.'#']", (path ? &lpath_13 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "/") == 0)
        {
            // handle may / property
            // .'$Trafo'.'|'.2.'/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Trafo'.'|'.2.'/']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Trafo'.'|'.2.'/']", (path ? &lpath_13 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Trafo'.'|'.2]", (path ? &lpath_13 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "*") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <*> [.'$Trafo'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$Trafo'.'|'.1.'*'.'|'.1
static bool _jm_obj_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Trafo'.'|'.1.'*'.'|'.1]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_16 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Trafo'.'|'.1.'*'.'|'.1.''
        res = json_model_17(pval, (path ? &lpath_16 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Trafo'.'|'.1.'*'.'|'.1.'']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$Trafo'.'|'.1
static bool _jm_obj_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Trafo'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_15 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "/") == 0)
        {
            // handle must / property
            must_count += 1;
            // .'$Trafo'.'|'.1.'/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Trafo'.'|'.1.'/']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Trafo'.'|'.1.'/']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Trafo'.'|'.1.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Trafo'.'|'.1.'#']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Trafo'.'|'.1.'#']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "*") == 0)
        {
            // handle may * property
            // .'$Trafo'.'|'.1.'*'
            // .'$Trafo'.'|'.1.'*'.'|'.0
            res = json_is_array(pval);
            if (res)
            {
                // accept any array
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Trafo'.'|'.1.'*'.'|'.0]", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                // .'$Trafo'.'|'.1.'*'.'|'.1
                res = _jm_obj_16(pval, (path ? &lpath_15 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$Trafo'.'|'.1.'*'.'|'.1]", (path ? &lpath_15 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Trafo'.'|'.1.'*'.'|']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Trafo'.'|'.1.'*']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Trafo'.'|'.1]", (path ? &lpath_15 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "/") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop </> [.'$Trafo'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Trafo (.'$Trafo')
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Trafo'
    // .'$Trafo'.'|'.0
    res = json_model_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Trafo'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Trafo'.'|'.1
        res = _jm_obj_15(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Trafo'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Trafo'.'|'.2
            res = _jm_obj_13(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Trafo'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Trafo'.'|']", path);
    }
    return res;
}

static bool _jm_cst_0_test(const json_t *val)
{
  jm_constant_t cst;
  jm_set_cst(&cst, val);
  return jm_search_cst(&cst, _jm_cst_0, 8);
}

// check $Scalar (.'$Scalar')
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Scalar'
    res = jm_json_is_scalar(val) && _jm_cst_0_test(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$Scalar'.'|']", path);
    }
    if (! res)
    {
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected type [.'$Scalar'.'|']", path);
        }
        if (res)
        {
            // .'$Scalar'.'|'.0
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Scalar'.'|'.0]", path);
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Scalar'.'|']", path);
            }
        }
    }
    return res;
}

// check $Model (.'$Model')
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Model'
    // .'$Model'.'|'.0
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [.'$Model'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Model'.'|'.1
        res = json_model_7(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$Model'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$Model'.'|'.2
            res = json_model_14(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Elem [.'$Model'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Model'.'|']", path);
    }
    return res;
}

static bool _jm_re_4(const char *s)
{
  int rc = pcre2_match(_jm_re_4_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_4_data, NULL);
  return rc >= 0;
}

// object .'$Defs'
static bool _jm_obj_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_17 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Defs'.''
            res = json_model_2(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Defs'.'']", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Defs'.'']", (path ? &lpath_17 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Defs'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Defs'.'/.+/']", (path ? &lpath_17 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Defs']", (path ? &lpath_17 : NULL));
            return false;
        }
    }
    return true;
}

// check $Defs (.'$Defs')
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Defs'
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Defs']", path);
    }
    return res;
}

static bool _jm_re_5(const char *s)
{
  int rc = pcre2_match(_jm_re_5_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_5_data, NULL);
  return rc >= 0;
}

static bool _jm_re_6(const char *s)
{
  int rc = pcre2_match(_jm_re_6_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_6_data, NULL);
  return rc >= 0;
}

// object .'$Rename'
static bool _jm_obj_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Rename']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_18 = (jm_path_t) { prop, 0, path, NULL };
        if (_jm_re_5(prop))
        {
            // handle 1 re props
            // .'$Rename'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Rename'.'/^\\\\..+$/']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Rename']", (path ? &lpath_18 : NULL));
            return false;
        }
    }
    return true;
}

// check $Rename (.'$Rename')
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Rename'
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Rename']", path);
    }
    return res;
}

static bool _jm_re_7(const char *s)
{
  int rc = pcre2_match(_jm_re_7_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_7_data, NULL);
  return rc >= 0;
}

// object .'$Rewrite'
static bool _jm_obj_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Rewrite']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_19 = (jm_path_t) { prop, 0, path, NULL };
        if (_jm_re_7(prop))
        {
            // handle 1 re props
            // .'$Rewrite'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_19 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Rewrite'.'/^\\\\$.*$/']", (path ? &lpath_19 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Rewrite']", (path ? &lpath_19 : NULL));
            return false;
        }
    }
    return true;
}

// check $Rewrite (.'$Rewrite')
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Rewrite'
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Rewrite']", path);
    }
    return res;
}

// object .'$RootOnly'.'$'
static bool _jm_obj_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RootOnly'.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_21 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$RootOnly'.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$RootOnly'.'$'.'#']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'$'.'#']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$RootOnly'.'$'.''
            res = json_model_2(pval, (path ? &lpath_21 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$RootOnly'.'$'.'']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'$'.'']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$RootOnly'.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_21 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$RootOnly'.'$'.'/.+/']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$RootOnly'.'$']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    return true;
}

// object .'$RootOnly'.'%'
static bool _jm_obj_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RootOnly'.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_22 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$RootOnly'.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$RootOnly'.'%'.'#']", (path ? &lpath_22 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'%'.'#']", (path ? &lpath_22 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$RootOnly'.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$RootOnly'.'%'.'/^\\\\..+$/']", (path ? &lpath_22 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$RootOnly'.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_22 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$RootOnly'.'%'.'/^\\\\$.*$/']", (path ? &lpath_22 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$RootOnly'.'%']", (path ? &lpath_22 : NULL));
            return false;
        }
    }
    return true;
}

// object .'$RootOnly'
static bool _jm_obj_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RootOnly']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_20 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "~") == 0)
        {
            // handle may ~ property
            // .'$RootOnly'.'~'
            res = json_model_2(pval, (path ? &lpath_20 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$RootOnly'.'~']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'~']", (path ? &lpath_20 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "$") == 0)
        {
            // handle may $ property
            // .'$RootOnly'.'$'
            res = _jm_obj_21(pval, (path ? &lpath_20 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$RootOnly'.'$']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'$']", (path ? &lpath_20 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "%") == 0)
        {
            // handle may % property
            // .'$RootOnly'.'%'
            res = _jm_obj_22(pval, (path ? &lpath_20 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$RootOnly'.'%']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RootOnly'.'%']", (path ? &lpath_20 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$RootOnly']", (path ? &lpath_20 : NULL));
            return false;
        }
    }
    return true;
}

// check $RootOnly (.'$RootOnly')
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$RootOnly'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$RootOnly']", path);
    }
    return res;
}

// check _jm_obj_23_map_# (.'$Root'.'|'.5.'#')
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.5.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.5.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.5.'$'
static bool _jm_obj_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.5.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_24 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.5.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.5.'$'.'#']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.5.'$'.'#']", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.5.'$'.''
            res = json_model_2(pval, (path ? &lpath_24 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.5.'$'.'']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.5.'$'.'']", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.5.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_24 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.5.'$'.'/.+/']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.5.'$']", (path ? &lpath_24 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_map_$ (.'$Root'.'|'.5.'$')
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.5.'$'
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.5.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.5.'%'
static bool _jm_obj_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.5.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_25 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.5.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.5.'%'.'#']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.5.'%'.'#']", (path ? &lpath_25 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.5.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.5.'%'.'/^\\\\..+$/']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.5.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_25 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.5.'%'.'/^\\\\$.*$/']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.5.'%']", (path ? &lpath_25 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_map_% (.'$Root'.'|'.5.'%')
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.5.'%'
    res = _jm_obj_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.5.'%']", path);
    }
    return res;
}

// check _jm_obj_23_map_~ (.'$Root'.'|'.5.'~')
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.5.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.5.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_23_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_23_map_tab, 4);
}

// object .'$Root'.'|'.5
static bool _jm_obj_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.5]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_23 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_23_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_23 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.5]", (path ? &lpath_23 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.5.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$Root'.'|'.5.'/^[@|&^+/*]$/']", (path ? &lpath_23 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$Root'.'|'.5.''
            res = json_model_17(pval, (path ? &lpath_23 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.5.'']", (path ? &lpath_23 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// check _jm_obj_26_map_# (.'$Root'.'|'.4.'#')
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.4.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.4.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.4.'$'
static bool _jm_obj_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.4.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_27 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.4.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.4.'$'.'#']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.4.'$'.'#']", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.4.'$'.''
            res = json_model_2(pval, (path ? &lpath_27 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.4.'$'.'']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.4.'$'.'']", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.4.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_27 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.4.'$'.'/.+/']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.4.'$']", (path ? &lpath_27 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_$ (.'$Root'.'|'.4.'$')
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.4.'$'
    res = _jm_obj_27(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.4.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.4.'%'
static bool _jm_obj_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.4.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_28 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.4.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.4.'%'.'#']", (path ? &lpath_28 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.4.'%'.'#']", (path ? &lpath_28 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.4.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.4.'%'.'/^\\\\..+$/']", (path ? &lpath_28 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.4.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_28 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.4.'%'.'/^\\\\$.*$/']", (path ? &lpath_28 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.4.'%']", (path ? &lpath_28 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_% (.'$Root'.'|'.4.'%')
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.4.'%'
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.4.'%']", path);
    }
    return res;
}

// check _jm_obj_26_map_~ (.'$Root'.'|'.4.'~')
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.4.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.4.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_26_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_26_map_tab, 4);
}

// object .'$Root'.'|'.4
static bool _jm_obj_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.4]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_26 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "+") == 0)
        {
            // handle must + property
            must_count += 1;
            // .'$Root'.'|'.4.'+'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_9_idx;
                json_t *arr_9_item;
                json_array_foreach(pval, arr_9_idx, arr_9_item)
                {
                    jm_path_t arr_9_lpath = (jm_path_t) { NULL, arr_9_idx, (path ? &lpath_26 : NULL), NULL };
                    // .'$Root'.'|'.4.'+'.0
                    res = json_model_17(arr_9_item, ((path ? &lpath_26 : NULL) ? &arr_9_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.4.'+'.0]", ((path ? &lpath_26 : NULL) ? &arr_9_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Root'.'|'.4.'+']", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Root'.'|'.4.'+']", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_26_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_26 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.4]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.4]", (path ? &lpath_26 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "+") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <+> [.'$Root'.'|'.4]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_29_map_# (.'$Root'.'|'.3.'#')
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.3.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.3.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.3.'$'
static bool _jm_obj_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.3.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_30 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.3.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.3.'$'.'#']", (path ? &lpath_30 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.3.'$'.'#']", (path ? &lpath_30 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.3.'$'.''
            res = json_model_2(pval, (path ? &lpath_30 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.3.'$'.'']", (path ? &lpath_30 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.3.'$'.'']", (path ? &lpath_30 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.3.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_30 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.3.'$'.'/.+/']", (path ? &lpath_30 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.3.'$']", (path ? &lpath_30 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_$ (.'$Root'.'|'.3.'$')
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.3.'$'
    res = _jm_obj_30(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.3.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.3.'%'
static bool _jm_obj_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.3.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_31 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.3.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.3.'%'.'#']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.3.'%'.'#']", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.3.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.3.'%'.'/^\\\\..+$/']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.3.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_31 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.3.'%'.'/^\\\\$.*$/']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.3.'%']", (path ? &lpath_31 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_% (.'$Root'.'|'.3.'%')
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.3.'%'
    res = _jm_obj_31(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.3.'%']", path);
    }
    return res;
}

// check _jm_obj_29_map_~ (.'$Root'.'|'.3.'~')
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.3.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.3.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_29_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_29_map_tab, 4);
}

// object .'$Root'.'|'.3
static bool _jm_obj_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.3]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_29 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$Root'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_10_idx;
                json_t *arr_10_item;
                json_array_foreach(pval, arr_10_idx, arr_10_item)
                {
                    jm_path_t arr_10_lpath = (jm_path_t) { NULL, arr_10_idx, (path ? &lpath_29 : NULL), NULL };
                    // .'$Root'.'|'.3.'^'.0
                    res = json_model_17(arr_10_item, ((path ? &lpath_29 : NULL) ? &arr_10_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.3.'^'.0]", ((path ? &lpath_29 : NULL) ? &arr_10_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Root'.'|'.3.'^']", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Root'.'|'.3.'^']", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_29_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_29 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.3]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.3]", (path ? &lpath_29 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <^> [.'$Root'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_32_map_# (.'$Root'.'|'.2.'#')
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.2.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.2.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.2.'$'
static bool _jm_obj_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.2.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_33 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.2.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.2.'$'.'#']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.2.'$'.'#']", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.2.'$'.''
            res = json_model_2(pval, (path ? &lpath_33 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.2.'$'.'']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.2.'$'.'']", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.2.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_33 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.2.'$'.'/.+/']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.2.'$']", (path ? &lpath_33 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_$ (.'$Root'.'|'.2.'$')
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.2.'$'
    res = _jm_obj_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.2.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.2.'%'
static bool _jm_obj_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.2.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_34 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.2.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.2.'%'.'#']", (path ? &lpath_34 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.2.'%'.'#']", (path ? &lpath_34 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.2.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.2.'%'.'/^\\\\..+$/']", (path ? &lpath_34 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.2.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_34 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.2.'%'.'/^\\\\$.*$/']", (path ? &lpath_34 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.2.'%']", (path ? &lpath_34 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_% (.'$Root'.'|'.2.'%')
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.2.'%'
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.2.'%']", path);
    }
    return res;
}

// check _jm_obj_32_map_~ (.'$Root'.'|'.2.'~')
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.2.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.2.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_32_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_32_map_tab, 4);
}

// object .'$Root'.'|'.2
static bool _jm_obj_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.2]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_32 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$Root'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_11_idx;
                json_t *arr_11_item;
                json_array_foreach(pval, arr_11_idx, arr_11_item)
                {
                    jm_path_t arr_11_lpath = (jm_path_t) { NULL, arr_11_idx, (path ? &lpath_32 : NULL), NULL };
                    // .'$Root'.'|'.2.'&'.0
                    res = json_model_17(arr_11_item, ((path ? &lpath_32 : NULL) ? &arr_11_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.2.'&'.0]", ((path ? &lpath_32 : NULL) ? &arr_11_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Root'.'|'.2.'&']", (path ? &lpath_32 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Root'.'|'.2.'&']", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_32_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_32 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.2]", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.2]", (path ? &lpath_32 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <&> [.'$Root'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_35_map_# (.'$Root'.'|'.1.'#')
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.1.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.1.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.1.'$'
static bool _jm_obj_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.1.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_36 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.1.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.1.'$'.'#']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.1.'$'.'#']", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.1.'$'.''
            res = json_model_2(pval, (path ? &lpath_36 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.1.'$'.'']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.1.'$'.'']", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.1.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_36 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.1.'$'.'/.+/']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.1.'$']", (path ? &lpath_36 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_$ (.'$Root'.'|'.1.'$')
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.1.'$'
    res = _jm_obj_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.1.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.1.'%'
static bool _jm_obj_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.1.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_37 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.1.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.1.'%'.'#']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.1.'%'.'#']", (path ? &lpath_37 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.1.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.1.'%'.'/^\\\\..+$/']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.1.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_37 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.1.'%'.'/^\\\\$.*$/']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.1.'%']", (path ? &lpath_37 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_% (.'$Root'.'|'.1.'%')
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.1.'%'
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.1.'%']", path);
    }
    return res;
}

// check _jm_obj_35_map_~ (.'$Root'.'|'.1.'~')
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.1.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.1.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_35_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_35_map_tab, 4);
}

// object .'$Root'.'|'.1
static bool _jm_obj_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.1]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_35 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$Root'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_12_idx;
                json_t *arr_12_item;
                json_array_foreach(pval, arr_12_idx, arr_12_item)
                {
                    jm_path_t arr_12_lpath = (jm_path_t) { NULL, arr_12_idx, (path ? &lpath_35 : NULL), NULL };
                    // .'$Root'.'|'.1.'|'.0
                    res = json_model_17(arr_12_item, ((path ? &lpath_35 : NULL) ? &arr_12_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.1.'|'.0]", ((path ? &lpath_35 : NULL) ? &arr_12_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Root'.'|'.1.'|']", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Root'.'|'.1.'|']", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_35_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_35 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.1]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.1]", (path ? &lpath_35 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <|> [.'$Root'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_38_map_! (.'$Root'.'|'.0.'!')
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.0.'!'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Root'.'|'.0.'!']", path);
    }
    return res;
}

// check _jm_obj_38_map_# (.'$Root'.'|'.0.'#')
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.0.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.0.'#']", path);
    }
    return res;
}

// object .'$Root'.'|'.0.'$'
static bool _jm_obj_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.0.'$']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_39 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.0.'$'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.0.'$'.'#']", (path ? &lpath_39 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.0.'$'.'#']", (path ? &lpath_39 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "") == 0)
        {
            // handle may  property
            // .'$Root'.'|'.0.'$'.''
            res = json_model_2(pval, (path ? &lpath_39 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.0.'$'.'']", (path ? &lpath_39 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.0.'$'.'']", (path ? &lpath_39 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$Root'.'|'.0.'$'.'/.+/'
            res = json_model_17(pval, (path ? &lpath_39 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.0.'$'.'/.+/']", (path ? &lpath_39 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.0.'$']", (path ? &lpath_39 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_$ (.'$Root'.'|'.0.'$')
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.0.'$'
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.0.'$']", path);
    }
    return res;
}

// object .'$Root'.'|'.0.'%'
static bool _jm_obj_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.0.'%']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_40 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$Root'.'|'.0.'%'.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.0.'%'.'#']", (path ? &lpath_40 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.0.'%'.'#']", (path ? &lpath_40 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.0.'%'.'/^\\..+$/'
            // "/^([#|&^+/*@~=$%]|[<>!]=?)$/"
            res = json_is_string(pval) && _jm_re_6(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^([#|&^+/*@~=$%]|[<>!]=?)$/ [.'$Root'.'|'.0.'%'.'/^\\\\..+$/']", (path ? &lpath_40 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_7(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.0.'%'.'/^\\$.*$/'
            res = json_model_15(pval, (path ? &lpath_40 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Trafo [.'$Root'.'|'.0.'%'.'/^\\\\$.*$/']", (path ? &lpath_40 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.0.'%']", (path ? &lpath_40 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_% (.'$Root'.'|'.0.'%')
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.0.'%'
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.0.'%']", path);
    }
    return res;
}

// check _jm_obj_38_map_~ (.'$Root'.'|'.0.'~')
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'.'|'.0.'~'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Url [.'$Root'.'|'.0.'~']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_38_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_38_map_tab, 5);
}

// object .'$Root'.'|'.0
static bool _jm_obj_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Root'.'|'.0]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_38 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$Root'.'|'.0.'@'
            res = json_model_17(pval, (path ? &lpath_38 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$Root'.'|'.0.'@']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Root'.'|'.0.'@']", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_38_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_38 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Root'.'|'.0]", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                // .'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_38 : NULL));
                }
                if (! res)
                {
                    // .'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_38 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Root'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Root'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_3(pval, (path ? &lpath_38 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$Root'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Root'.'|'.0]", (path ? &lpath_38 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <@> [.'$Root'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Root (.'$Root')
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Root'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$Root'.'|']", path);
    }
    if (res)
    {
        // .'$Root'.'|'.0
        res = _jm_obj_38(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Root'.'|'.1
            res = _jm_obj_35(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$Root'.'|'.2
                res = _jm_obj_32(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$Root'.'|'.3
                    res = _jm_obj_29(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$Root'.'|'.4
                        res = _jm_obj_26(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // .'$Root'.'|'.5
                            res = _jm_obj_23(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Root'.'|'.5]", path);
                            }
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Root'.'|']", path);
        }
    }
    return res;
}

// check $RootModel (.'$RootModel')
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$RootModel'
    // .'$RootModel'.'|'.0
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [.'$RootModel'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$RootModel'.'|'.1
        res = json_model_7(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$RootModel'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$RootModel'.'|'.2
            res = json_model_22(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Root [.'$RootModel'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$RootModel'.'|']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RootModel [.]", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 23);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^((file|https?)://.+|\\./.*|\\.\\./.*)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
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
        _jm_re_3_code = pcre2_compile((PCRE2_SPTR) "^[@|&^+/*]$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_3_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_3_data = pcre2_match_data_create_from_pattern(_jm_re_3_code, NULL);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (jm_constant_t) { cst_is_null, { .s = NULL } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_bool, { .b = true } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_integer, { .i = 0 } };
        _jm_cst_0[3] = (jm_constant_t) { cst_is_integer, { .i = 1 } };
        _jm_cst_0[4] = (jm_constant_t) { cst_is_integer, { .i = -1 } };
        _jm_cst_0[5] = (jm_constant_t) { cst_is_float, { .f = 0.0 } };
        _jm_cst_0[6] = (jm_constant_t) { cst_is_float, { .f = 1.0 } };
        _jm_cst_0[7] = (jm_constant_t) { cst_is_float, { .f = -1.0 } };
        jm_sort_cst(_jm_cst_0, 8);
        _jm_re_4_code = pcre2_compile((PCRE2_SPTR) ".+", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_4_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_4_data = pcre2_match_data_create_from_pattern(_jm_re_4_code, NULL);
        _jm_re_5_code = pcre2_compile((PCRE2_SPTR) "^\\..+$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_5_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_5_data = pcre2_match_data_create_from_pattern(_jm_re_5_code, NULL);
        _jm_re_6_code = pcre2_compile((PCRE2_SPTR) "^([#|&^+/*@~=$%]|[<>!]=?)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_6_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_6_data = pcre2_match_data_create_from_pattern(_jm_re_6_code, NULL);
        _jm_re_7_code = pcre2_compile((PCRE2_SPTR) "^\\$.*$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_7_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_7_data = pcre2_match_data_create_from_pattern(_jm_re_7_code, NULL);
        _jm_obj_23_map_tab[0] = (jm_propmap_t) { "#", _jm_f_0 };
        _jm_obj_23_map_tab[1] = (jm_propmap_t) { "$", _jm_f_1 };
        _jm_obj_23_map_tab[2] = (jm_propmap_t) { "%", _jm_f_2 };
        _jm_obj_23_map_tab[3] = (jm_propmap_t) { "~", _jm_f_3 };
        jm_sort_propmap(_jm_obj_23_map_tab, 4);
        _jm_obj_26_map_tab[0] = (jm_propmap_t) { "#", _jm_f_4 };
        _jm_obj_26_map_tab[1] = (jm_propmap_t) { "$", _jm_f_5 };
        _jm_obj_26_map_tab[2] = (jm_propmap_t) { "%", _jm_f_6 };
        _jm_obj_26_map_tab[3] = (jm_propmap_t) { "~", _jm_f_7 };
        jm_sort_propmap(_jm_obj_26_map_tab, 4);
        _jm_obj_29_map_tab[0] = (jm_propmap_t) { "#", _jm_f_8 };
        _jm_obj_29_map_tab[1] = (jm_propmap_t) { "$", _jm_f_9 };
        _jm_obj_29_map_tab[2] = (jm_propmap_t) { "%", _jm_f_10 };
        _jm_obj_29_map_tab[3] = (jm_propmap_t) { "~", _jm_f_11 };
        jm_sort_propmap(_jm_obj_29_map_tab, 4);
        _jm_obj_32_map_tab[0] = (jm_propmap_t) { "#", _jm_f_12 };
        _jm_obj_32_map_tab[1] = (jm_propmap_t) { "$", _jm_f_13 };
        _jm_obj_32_map_tab[2] = (jm_propmap_t) { "%", _jm_f_14 };
        _jm_obj_32_map_tab[3] = (jm_propmap_t) { "~", _jm_f_15 };
        jm_sort_propmap(_jm_obj_32_map_tab, 4);
        _jm_obj_35_map_tab[0] = (jm_propmap_t) { "#", _jm_f_16 };
        _jm_obj_35_map_tab[1] = (jm_propmap_t) { "$", _jm_f_17 };
        _jm_obj_35_map_tab[2] = (jm_propmap_t) { "%", _jm_f_18 };
        _jm_obj_35_map_tab[3] = (jm_propmap_t) { "~", _jm_f_19 };
        jm_sort_propmap(_jm_obj_35_map_tab, 4);
        _jm_obj_38_map_tab[0] = (jm_propmap_t) { "!", _jm_f_20 };
        _jm_obj_38_map_tab[1] = (jm_propmap_t) { "#", _jm_f_21 };
        _jm_obj_38_map_tab[2] = (jm_propmap_t) { "$", _jm_f_22 };
        _jm_obj_38_map_tab[3] = (jm_propmap_t) { "%", _jm_f_23 };
        _jm_obj_38_map_tab[4] = (jm_propmap_t) { "~", _jm_f_24 };
        jm_sort_propmap(_jm_obj_38_map_tab, 5);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "Url", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "Val", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "Any", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "None", json_model_5 };
        check_model_map_tab[5] = (jm_propmap_t) { "Common", json_model_6 };
        check_model_map_tab[6] = (jm_propmap_t) { "Array", json_model_7 };
        check_model_map_tab[7] = (jm_propmap_t) { "Constraint", json_model_8 };
        check_model_map_tab[8] = (jm_propmap_t) { "Or", json_model_9 };
        check_model_map_tab[9] = (jm_propmap_t) { "And", json_model_10 };
        check_model_map_tab[10] = (jm_propmap_t) { "Xor", json_model_11 };
        check_model_map_tab[11] = (jm_propmap_t) { "Add", json_model_12 };
        check_model_map_tab[12] = (jm_propmap_t) { "Obj", json_model_13 };
        check_model_map_tab[13] = (jm_propmap_t) { "Elem", json_model_14 };
        check_model_map_tab[14] = (jm_propmap_t) { "Trafo", json_model_15 };
        check_model_map_tab[15] = (jm_propmap_t) { "Scalar", json_model_16 };
        check_model_map_tab[16] = (jm_propmap_t) { "Model", json_model_17 };
        check_model_map_tab[17] = (jm_propmap_t) { "Defs", json_model_18 };
        check_model_map_tab[18] = (jm_propmap_t) { "Rename", json_model_19 };
        check_model_map_tab[19] = (jm_propmap_t) { "Rewrite", json_model_20 };
        check_model_map_tab[20] = (jm_propmap_t) { "RootOnly", json_model_21 };
        check_model_map_tab[21] = (jm_propmap_t) { "Root", json_model_22 };
        check_model_map_tab[22] = (jm_propmap_t) { "RootModel", json_model_23 };
        jm_sort_propmap(check_model_map_tab, 23);
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
        pcre2_match_data_free(_jm_re_7_data);
        pcre2_code_free(_jm_re_7_code);
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
