#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_map_tab[8];
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_map_tab[5];
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool json_model_9(const json_t* val, Path* path, Report* rep);
static bool json_model_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_9_map_tab[10];
static bool json_model_11(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_2_code = NULL;
static pcre2_match_data *_jm_re_2_data = NULL;
static bool _jm_re_2(const char *s);
static bool json_model_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static bool _jm_f_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_25(const json_t* val, Path* path, Report* rep);
static bool _jm_f_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_27(const json_t* val, Path* path, Report* rep);
static bool _jm_f_28(const json_t* val, Path* path, Report* rep);
static bool _jm_f_29(const json_t* val, Path* path, Report* rep);
static bool _jm_f_30(const json_t* val, Path* path, Report* rep);
static bool _jm_f_31(const json_t* val, Path* path, Report* rep);
static bool _jm_f_32(const json_t* val, Path* path, Report* rep);
static bool _jm_f_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_34(const json_t* val, Path* path, Report* rep);
static bool _jm_f_35(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_21_map_tab[13];
static bool json_model_13(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_36(const json_t* val, Path* path, Report* rep);
static bool _jm_f_37(const json_t* val, Path* path, Report* rep);
static bool _jm_f_38(const json_t* val, Path* path, Report* rep);
static bool _jm_f_39(const json_t* val, Path* path, Report* rep);
static bool _jm_f_40(const json_t* val, Path* path, Report* rep);
static bool _jm_f_41(const json_t* val, Path* path, Report* rep);
static bool _jm_f_42(const json_t* val, Path* path, Report* rep);
static bool _jm_f_43(const json_t* val, Path* path, Report* rep);
static bool _jm_f_44(const json_t* val, Path* path, Report* rep);
static bool _jm_f_45(const json_t* val, Path* path, Report* rep);
static bool _jm_f_46(const json_t* val, Path* path, Report* rep);
static bool _jm_f_47(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_22_map_tab[12];
static bool json_model_14(const json_t* val, Path* path, Report* rep);
static bool json_model_15(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[4];
static bool _jm_f_48(const json_t* val, Path* path, Report* rep);
static bool _jm_f_49(const json_t* val, Path* path, Report* rep);
static bool _jm_f_50(const json_t* val, Path* path, Report* rep);
static bool _jm_f_51(const json_t* val, Path* path, Report* rep);
static bool _jm_f_52(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_25_map_tab[5];
static constant_t _jm_cst_1[4];
static bool _jm_f_53(const json_t* val, Path* path, Report* rep);
static bool _jm_f_54(const json_t* val, Path* path, Report* rep);
static bool _jm_f_55(const json_t* val, Path* path, Report* rep);
static bool _jm_f_56(const json_t* val, Path* path, Report* rep);
static bool _jm_f_57(const json_t* val, Path* path, Report* rep);
static bool _jm_f_58(const json_t* val, Path* path, Report* rep);
static bool _jm_f_59(const json_t* val, Path* path, Report* rep);
static bool _jm_f_60(const json_t* val, Path* path, Report* rep);
static bool _jm_f_61(const json_t* val, Path* path, Report* rep);
static bool _jm_f_62(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_27_map_tab[10];
static bool json_model_21(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_2[7];
static bool json_model_18(const json_t* val, Path* path, Report* rep);
static bool json_model_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_63(const json_t* val, Path* path, Report* rep);
static bool _jm_f_64(const json_t* val, Path* path, Report* rep);
static bool _jm_f_65(const json_t* val, Path* path, Report* rep);
static bool _jm_f_66(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_31_map_tab[4];
static bool json_model_23(const json_t* val, Path* path, Report* rep);
static bool _jm_f_67(const json_t* val, Path* path, Report* rep);
static bool _jm_f_68(const json_t* val, Path* path, Report* rep);
static bool _jm_f_69(const json_t* val, Path* path, Report* rep);
static bool _jm_f_70(const json_t* val, Path* path, Report* rep);
static bool _jm_f_71(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_34_map_tab[5];
static bool json_model_24(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_3_code = NULL;
static pcre2_match_data *_jm_re_3_data = NULL;
static bool _jm_re_3(const char *s);
static bool json_model_25(const json_t* val, Path* path, Report* rep);
static bool _jm_f_72(const json_t* val, Path* path, Report* rep);
static bool _jm_f_73(const json_t* val, Path* path, Report* rep);
static bool _jm_f_74(const json_t* val, Path* path, Report* rep);
static bool _jm_f_75(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_37_map_tab[4];
static bool json_model_26(const json_t* val, Path* path, Report* rep);
static bool json_model_27(const json_t* val, Path* path, Report* rep);
static bool _jm_f_76(const json_t* val, Path* path, Report* rep);
static bool _jm_f_77(const json_t* val, Path* path, Report* rep);
static bool _jm_f_78(const json_t* val, Path* path, Report* rep);
static bool _jm_f_79(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_42_map_tab[4];
static bool json_model_28(const json_t* val, Path* path, Report* rep);
static bool json_model_29(const json_t* val, Path* path, Report* rep);
static bool _jm_f_80(const json_t* val, Path* path, Report* rep);
static bool _jm_f_81(const json_t* val, Path* path, Report* rep);
static bool _jm_f_82(const json_t* val, Path* path, Report* rep);
static bool _jm_f_83(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_43_map_tab[4];
static bool _jm_f_84(const json_t* val, Path* path, Report* rep);
static bool _jm_f_85(const json_t* val, Path* path, Report* rep);
static bool _jm_f_86(const json_t* val, Path* path, Report* rep);
static bool _jm_f_87(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_45_map_tab[4];
static bool json_model_30(const json_t* val, Path* path, Report* rep);
static bool _jm_f_88(const json_t* val, Path* path, Report* rep);
static bool _jm_f_89(const json_t* val, Path* path, Report* rep);
static bool _jm_f_90(const json_t* val, Path* path, Report* rep);
static bool _jm_f_91(const json_t* val, Path* path, Report* rep);
static bool _jm_f_92(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_47_map_tab[5];
static bool _jm_f_93(const json_t* val, Path* path, Report* rep);
static bool _jm_f_94(const json_t* val, Path* path, Report* rep);
static bool _jm_f_95(const json_t* val, Path* path, Report* rep);
static bool _jm_f_96(const json_t* val, Path* path, Report* rep);
static bool _jm_f_97(const json_t* val, Path* path, Report* rep);
static bool _jm_f_98(const json_t* val, Path* path, Report* rep);
static bool _jm_f_99(const json_t* val, Path* path, Report* rep);
static bool _jm_f_100(const json_t* val, Path* path, Report* rep);
static bool _jm_f_101(const json_t* val, Path* path, Report* rep);
static bool _jm_f_102(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_49_map_tab[10];
static bool json_model_31(const json_t* val, Path* path, Report* rep);
static bool json_model_32(const json_t* val, Path* path, Report* rep);
static bool json_model_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_103(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_3[3];
static bool _jm_f_104(const json_t* val, Path* path, Report* rep);
static bool _jm_f_105(const json_t* val, Path* path, Report* rep);
static bool _jm_f_106(const json_t* val, Path* path, Report* rep);
static bool _jm_f_107(const json_t* val, Path* path, Report* rep);
static bool _jm_f_108(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_53_mup_tab[6];
static bool json_model_38(const json_t* val, Path* path, Report* rep);
static bool _jm_f_109(const json_t* val, Path* path, Report* rep);
static bool _jm_f_110(const json_t* val, Path* path, Report* rep);
static bool _jm_f_111(const json_t* val, Path* path, Report* rep);
static bool _jm_f_112(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_54_map_tab[4];
static bool json_model_39(const json_t* val, Path* path, Report* rep);
static bool json_model_40(const json_t* val, Path* path, Report* rep);
static bool json_model_41(const json_t* val, Path* path, Report* rep);
static bool json_model_61(const json_t* val, Path* path, Report* rep);
static bool json_model_78(const json_t* val, Path* path, Report* rep);
static bool json_model_68(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_4_code = NULL;
static pcre2_match_data *_jm_re_4_data = NULL;
static bool _jm_re_4(const char *s);
static pcre2_code *_jm_re_5_code = NULL;
static pcre2_match_data *_jm_re_5_data = NULL;
static bool _jm_re_5(const char *s);
static pcre2_code *_jm_re_6_code = NULL;
static pcre2_match_data *_jm_re_6_data = NULL;
static bool _jm_re_6(const char *s);
static bool json_model_75(const json_t* val, Path* path, Report* rep);
static bool json_model_64(const json_t* val, Path* path, Report* rep);
static bool _jm_cst_4_test(const json_t *);
static constant_t _jm_cst_4[8];
static bool json_model_77(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $openapi (.'$openapi')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi'
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OpenAPI [.'$openapi']", path);
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
        if (rep) jm_report_add_entry(rep, "unexpected $openapi []", path);
    }
    return res;
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check _jm_obj_0_map_component (.'$openapi#OpenAPI'.component)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.component
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Components [.'$openapi#OpenAPI'.component]", path);
    }
    return res;
}

// check _jm_obj_0_map_externalDocs (.'$openapi#OpenAPI'.externalDocs)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.externalDocs
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$openapi#OpenAPI'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_0_map_jsonSchemaDialect (.'$openapi#OpenAPI'.jsonSchemaDialect)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.jsonSchemaDialect
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#OpenAPI'.jsonSchemaDialect]", path);
    }
    return res;
}

// check _jm_obj_0_map_paths (.'$openapi#OpenAPI'.paths)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.paths
    res = json_model_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Paths [.'$openapi#OpenAPI'.paths]", path);
    }
    return res;
}

// check _jm_obj_0_map_security (.'$openapi#OpenAPI'.security)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.security
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [.'$openapi#OpenAPI'.security]", path);
    }
    return res;
}

// check _jm_obj_0_map_servers (.'$openapi#OpenAPI'.servers)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // .'$openapi#OpenAPI'.servers.0
            res = json_model_9(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$openapi#OpenAPI'.servers.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#OpenAPI'.servers]", path);
    }
    return res;
}

// check _jm_obj_0_map_tags (.'$openapi#OpenAPI'.tags)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // .'$openapi#OpenAPI'.tags.0
            res = json_model_32(arr_1_item, (path ? &arr_1_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Tag [.'$openapi#OpenAPI'.tags.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#OpenAPI'.tags]", path);
    }
    return res;
}

// object .'$openapi#OpenAPI'.webhooks
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#OpenAPI'.webhooks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#OpenAPI'.webhooks.''
        res = json_model_13(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$openapi#OpenAPI'.webhooks.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_webhooks (.'$openapi#OpenAPI'.webhooks)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'.webhooks
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#OpenAPI'.webhooks]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 8);
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

// object .'$openapi#OpenAPI'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#OpenAPI']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "openapi") == 0)
        {
            // handle must openapi property
            must_count += 1;
            // .'$openapi#OpenAPI'.openapi
            // "/^3\\.1\\.\\d+(-.+)?$/"
            res = json_is_string(pval) && _jm_re_0(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected REGEX [.'$openapi#OpenAPI'.openapi]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#OpenAPI'.openapi]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "info") == 0)
        {
            // handle must info property
            must_count += 1;
            // .'$openapi#OpenAPI'.info
            res = json_model_6(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Info [.'$openapi#OpenAPI'.info]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#OpenAPI'.info]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 8 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#OpenAPI']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#OpenAPI'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#OpenAPI'.'/^x\\\\-.*$/']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#OpenAPI']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "info") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <info> [.'$openapi#OpenAPI']", path);
            }
            if (! (json_object_get(val, "openapi") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <openapi> [.'$openapi#OpenAPI']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#OpenAPI (.'$openapi#OpenAPI')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OpenAPI'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#OpenAPI']", path);
    }
    return res;
}

// check _jm_obj_2_map_contact (.'$openapi#Info'.contact)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'.contact
    res = json_model_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Contact [.'$openapi#Info'.contact]", path);
    }
    return res;
}

// check _jm_obj_2_map_description (.'$openapi#Info'.description)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Info'.description]", path);
    }
    return res;
}

// check _jm_obj_2_map_license (.'$openapi#Info'.license)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'.license
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $License [.'$openapi#Info'.license]", path);
    }
    return res;
}

// check _jm_obj_2_map_summary (.'$openapi#Info'.summary)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Info'.summary]", path);
    }
    return res;
}

// check _jm_obj_2_map_termsOfService (.'$openapi#Info'.termsOfService)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'.termsOfService
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Info'.termsOfService]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_map_tab, 5);
}

// object .'$openapi#Info'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Info']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "title") == 0)
        {
            // handle must title property
            must_count += 1;
            // .'$openapi#Info'.title
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Info'.title]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Info'.title]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "version") == 0)
        {
            // handle must version property
            must_count += 1;
            // .'$openapi#Info'.version
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Info'.version]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Info'.version]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_2_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Info']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Info'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Info'.'/^x\\\\-.*$/']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Info']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "title") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <title> [.'$openapi#Info']", path);
            }
            if (! (json_object_get(val, "version") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <version> [.'$openapi#Info']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Info (.'$openapi#Info')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Info'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Info']", path);
    }
    return res;
}

// object .'$openapi#Contact'
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Contact']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle may name property
            // .'$openapi#Contact'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Contact'.name]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Contact'.name]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "url") == 0)
        {
            // handle may url property
            // .'$openapi#Contact'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#Contact'.url]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Contact'.url]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "email") == 0)
        {
            // handle may email property
            // .'$openapi#Contact'.email
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Contact'.email]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Contact'.email]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Contact'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Contact'.'/^x\\\\-.*$/']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Contact']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Contact (.'$openapi#Contact')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Contact'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Contact']", path);
    }
    return res;
}

// object .'$openapi#License'.'|'.1
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#License'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$openapi#License'.'|'.1.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#License'.'|'.1.name]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#License'.'|'.1.name]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$openapi#License'.'|'.1.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#License'.'|'.1.url]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#License'.'|'.1.url]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#License'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#License'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#License'.'|'.1]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#License'.'|'.1]", path);
            }
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <url> [.'$openapi#License'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$openapi#License'.'|'.0
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#License'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$openapi#License'.'|'.0.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#License'.'|'.0.name]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#License'.'|'.0.name]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "identifier") == 0)
        {
            // handle must identifier property
            must_count += 1;
            // .'$openapi#License'.'|'.0.identifier
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#License'.'|'.0.identifier]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#License'.'|'.0.identifier]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#License'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#License'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#License'.'|'.0]", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "identifier") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <identifier> [.'$openapi#License'.'|'.0]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#License'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#License (.'$openapi#License')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#License'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#License'.'|']", path);
    }
    if (res)
    {
        // .'$openapi#License'.'|'.0
        res = _jm_obj_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#License'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$openapi#License'.'|'.1
            res = _jm_obj_4(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#License'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#License'.'|']", path);
        }
    }
    return res;
}

// object .'$openapi#Server'.variables
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Server'.variables]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Server'.variables.''
        res = json_model_10(pval, (path ? &lpath_7 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ServerVariable [.'$openapi#Server'.variables.'']", (path ? &lpath_7 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$openapi#Server'
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Server']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$openapi#Server'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#Server'.url]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Server'.url]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#Server'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Server'.description]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Server'.description]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "variables") == 0)
        {
            // handle may variables property
            // .'$openapi#Server'.variables
            res = _jm_obj_7(pval, (path ? &lpath_6 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Server'.variables]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Server'.variables]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Server'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Server'.'/^x\\\\-.*$/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Server']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <url> [.'$openapi#Server']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Server (.'$openapi#Server')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Server'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Server']", path);
    }
    return res;
}

// object .'$openapi#ServerVariable'
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#ServerVariable']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_8 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "default") == 0)
        {
            // handle must default property
            must_count += 1;
            // .'$openapi#ServerVariable'.default
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#ServerVariable'.default]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#ServerVariable'.default]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "enum") == 0)
        {
            // handle may enum property
            // .'$openapi#ServerVariable'.enum
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_2_idx;
                json_t *arr_2_item;
                json_array_foreach(pval, arr_2_idx, arr_2_item)
                {
                    Path arr_2_lpath = (Path) { NULL, arr_2_idx, (path ? &lpath_8 : NULL), NULL };
                    // .'$openapi#ServerVariable'.enum.0
                    res = json_is_string(arr_2_item);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#ServerVariable'.enum.0]", ((path ? &lpath_8 : NULL) ? &arr_2_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#ServerVariable'.enum]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#ServerVariable'.enum]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#ServerVariable'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#ServerVariable'.description]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#ServerVariable'.description]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#ServerVariable'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#ServerVariable'.'/^x\\\\-.*$/']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#ServerVariable']", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "default") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <default> [.'$openapi#ServerVariable']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#ServerVariable (.'$openapi#ServerVariable')
static bool json_model_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#ServerVariable'
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#ServerVariable']", path);
    }
    return res;
}

// object .'$openapi#Components'.callbacks
static bool _jm_obj_10(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_10 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.callbacks.''
        // .'$openapi#Components'.callbacks.''.'|'.0
        res = json_model_27(pval, (path ? &lpath_10 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [.'$openapi#Components'.callbacks.''.'|'.0]", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.callbacks.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_10 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.callbacks.''.'|'.1]", (path ? &lpath_10 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.callbacks.''.'|']", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_callbacks (.'$openapi#Components'.callbacks)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.callbacks
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.callbacks]", path);
    }
    return res;
}

// object .'$openapi#Components'.examples
static bool _jm_obj_11(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_11 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.examples.''
        // .'$openapi#Components'.examples.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_11 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$openapi#Components'.examples.''.'|'.0]", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.examples.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_11 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.examples.''.'|'.1]", (path ? &lpath_11 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.examples.''.'|']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_examples (.'$openapi#Components'.examples)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.examples
    res = _jm_obj_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.examples]", path);
    }
    return res;
}

// object .'$openapi#Components'.headers
static bool _jm_obj_12(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_12 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.headers.''
        // .'$openapi#Components'.headers.''.'|'.0
        res = json_model_31(pval, (path ? &lpath_12 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$openapi#Components'.headers.''.'|'.0]", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.headers.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.headers.''.'|'.1]", (path ? &lpath_12 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.headers.''.'|']", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_headers (.'$openapi#Components'.headers)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.headers
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.headers]", path);
    }
    return res;
}

// object .'$openapi#Components'.links
static bool _jm_obj_13(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_13 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.links.''
        // .'$openapi#Components'.links.''.'|'.0
        res = json_model_30(pval, (path ? &lpath_13 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [.'$openapi#Components'.links.''.'|'.0]", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.links.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_13 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.links.''.'|'.1]", (path ? &lpath_13 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.links.''.'|']", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_links (.'$openapi#Components'.links)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.links
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.links]", path);
    }
    return res;
}

// object .'$openapi#Components'.models
static bool _jm_obj_14(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.models]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_14 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.models.''
        res = json_model_61(pval, (path ? &lpath_14 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#Components'.models.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_models (.'$openapi#Components'.models)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.models
    res = _jm_obj_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.models]", path);
    }
    return res;
}

// object .'$openapi#Components'.parameters
static bool _jm_obj_15(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.parameters]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_15 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.parameters.''
        // .'$openapi#Components'.parameters.''.'|'.0
        res = json_model_21(pval, (path ? &lpath_15 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$openapi#Components'.parameters.''.'|'.0]", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.parameters.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_15 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.parameters.''.'|'.1]", (path ? &lpath_15 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.parameters.''.'|']", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_parameters (.'$openapi#Components'.parameters)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.parameters
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.parameters]", path);
    }
    return res;
}

// object .'$openapi#Components'.pathItems
static bool _jm_obj_16(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.pathItems]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_16 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.pathItems.''
        // .'$openapi#Components'.pathItems.''.'|'.0
        res = json_model_13(pval, (path ? &lpath_16 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$openapi#Components'.pathItems.''.'|'.0]", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.pathItems.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_16 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.pathItems.''.'|'.1]", (path ? &lpath_16 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.pathItems.''.'|']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_pathItems (.'$openapi#Components'.pathItems)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.pathItems
    res = _jm_obj_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.pathItems]", path);
    }
    return res;
}

// object .'$openapi#Components'.requestBodies
static bool _jm_obj_17(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.requestBodies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_17 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.requestBodies.''
        // .'$openapi#Components'.requestBodies.''.'|'.0
        res = json_model_22(pval, (path ? &lpath_17 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [.'$openapi#Components'.requestBodies.''.'|'.0]", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.requestBodies.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.requestBodies.''.'|'.1]", (path ? &lpath_17 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.requestBodies.''.'|']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_requestBodies (.'$openapi#Components'.requestBodies)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.requestBodies
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.requestBodies]", path);
    }
    return res;
}

// object .'$openapi#Components'.responses
static bool _jm_obj_18(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.responses]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_18 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.responses.''
        // .'$openapi#Components'.responses.''.'|'.0
        res = json_model_26(pval, (path ? &lpath_18 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$openapi#Components'.responses.''.'|'.0]", (path ? &lpath_18 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.responses.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_18 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.responses.''.'|'.1]", (path ? &lpath_18 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.responses.''.'|']", (path ? &lpath_18 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_responses (.'$openapi#Components'.responses)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.responses
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.responses]", path);
    }
    return res;
}

// object .'$openapi#Components'.securitySchemes
static bool _jm_obj_19(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components'.securitySchemes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_19 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Components'.securitySchemes.''
        // .'$openapi#Components'.securitySchemes.''.'|'.0
        res = json_model_38(pval, (path ? &lpath_19 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $SecurityScheme [.'$openapi#Components'.securitySchemes.''.'|'.0]", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Components'.securitySchemes.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_19 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Components'.securitySchemes.''.'|'.1]", (path ? &lpath_19 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Components'.securitySchemes.''.'|']", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_securitySchemes (.'$openapi#Components'.securitySchemes)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'.securitySchemes
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components'.securitySchemes]", path);
    }
    return res;
}

static check_fun_t _jm_obj_9_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_map_tab, 10);
}

// object .'$openapi#Components'
static bool _jm_obj_9(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Components']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_9 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_9_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_9 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Components']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Components'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Components'.'/^x\\\\-.*$/']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Components']", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Components (.'$openapi#Components')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Components'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Components']", path);
    }
    return res;
}

static bool _jm_re_2(const char *s)
{
  int rc = pcre2_match(_jm_re_2_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_2_data, NULL);
  return rc >= 0;
}

// object .'$openapi#Paths'
static bool _jm_obj_20(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Paths']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_20 = (Path) { prop, 0, path, NULL };
        if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$openapi#Paths'.'/^//'
            res = json_model_13(pval, (path ? &lpath_20 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$openapi#Paths'.'/^//']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$openapi#Paths'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Paths'.'/^x\\\\-.*$/']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Paths']", (path ? &lpath_20 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Paths (.'$openapi#Paths')
static bool json_model_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Paths'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Paths']", path);
    }
    return res;
}

// check _jm_obj_21_map_$ref (.'$openapi#PathItem'.'$ref')
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.'$ref'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$openapi#PathItem'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_21_map_delete (.'$openapi#PathItem'.delete)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.delete
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.delete]", path);
    }
    return res;
}

// check _jm_obj_21_map_description (.'$openapi#PathItem'.description)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#PathItem'.description]", path);
    }
    return res;
}

// check _jm_obj_21_map_get (.'$openapi#PathItem'.get)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.get
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.get]", path);
    }
    return res;
}

// check _jm_obj_21_map_head (.'$openapi#PathItem'.head)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.head
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.head]", path);
    }
    return res;
}

// check _jm_obj_21_map_options (.'$openapi#PathItem'.options)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.options
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.options]", path);
    }
    return res;
}

// check _jm_obj_21_map_parameters (.'$openapi#PathItem'.parameters)
static bool _jm_f_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.parameters
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
            // .'$openapi#PathItem'.parameters.0
            // .'$openapi#PathItem'.parameters.0.'|'.0
            res = json_model_21(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$openapi#PathItem'.parameters.0.'|'.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                // .'$openapi#PathItem'.parameters.0.'|'.1
                res = json_model_33(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#PathItem'.parameters.0.'|'.1]", (path ? &arr_3_lpath : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#PathItem'.parameters.0.'|']", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#PathItem'.parameters]", path);
    }
    return res;
}

// check _jm_obj_21_map_patch (.'$openapi#PathItem'.patch)
static bool _jm_f_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.patch
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.patch]", path);
    }
    return res;
}

// check _jm_obj_21_map_post (.'$openapi#PathItem'.post)
static bool _jm_f_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.post
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.post]", path);
    }
    return res;
}

// check _jm_obj_21_map_put (.'$openapi#PathItem'.put)
static bool _jm_f_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.put
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.put]", path);
    }
    return res;
}

// check _jm_obj_21_map_servers (.'$openapi#PathItem'.servers)
static bool _jm_f_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_4_idx;
        json_t *arr_4_item;
        json_array_foreach(val, arr_4_idx, arr_4_item)
        {
            Path arr_4_lpath = (Path) { NULL, arr_4_idx, path, NULL };
            // .'$openapi#PathItem'.servers.0
            res = json_model_14(arr_4_item, (path ? &arr_4_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.servers.0]", (path ? &arr_4_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#PathItem'.servers]", path);
    }
    return res;
}

// check _jm_obj_21_map_summary (.'$openapi#PathItem'.summary)
static bool _jm_f_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#PathItem'.summary]", path);
    }
    return res;
}

// check _jm_obj_21_map_trace (.'$openapi#PathItem'.trace)
static bool _jm_f_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'.trace
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$openapi#PathItem'.trace]", path);
    }
    return res;
}

static check_fun_t _jm_obj_21_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_21_map_tab, 13);
}

// object .'$openapi#PathItem'
static bool _jm_obj_21(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#PathItem']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_21 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_21_map(prop)))
        {
            // handle 13 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_21 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#PathItem']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#PathItem'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#PathItem'.'/^x\\\\-.*$/']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#PathItem']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#PathItem (.'$openapi#PathItem')
static bool json_model_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#PathItem'
    res = _jm_obj_21(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#PathItem']", path);
    }
    return res;
}

// check $openapi#URI (.'$openapi#URI')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#URI'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#URI']", path);
    }
    return res;
}

// object .'$openapi#Operation'.callbacks
static bool _jm_obj_23(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Operation'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_23 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Operation'.callbacks.''
        // .'$openapi#Operation'.callbacks.''.'|'.0
        res = json_model_27(pval, (path ? &lpath_23 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [.'$openapi#Operation'.callbacks.''.'|'.0]", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Operation'.callbacks.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_23 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Operation'.callbacks.''.'|'.1]", (path ? &lpath_23 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Operation'.callbacks.''.'|']", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_22_map_callbacks (.'$openapi#Operation'.callbacks)
static bool _jm_f_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.callbacks
    res = _jm_obj_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Operation'.callbacks]", path);
    }
    return res;
}

// check _jm_obj_22_map_deprecated (.'$openapi#Operation'.deprecated)
static bool _jm_f_37(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Operation'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_22_map_description (.'$openapi#Operation'.description)
static bool _jm_f_38(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Operation'.description]", path);
    }
    return res;
}

// check _jm_obj_22_map_externalDocs (.'$openapi#Operation'.externalDocs)
static bool _jm_f_39(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.externalDocs
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$openapi#Operation'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_22_map_operationId (.'$openapi#Operation'.operationId)
static bool _jm_f_40(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.operationId
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Operation'.operationId]", path);
    }
    return res;
}

// check _jm_obj_22_map_parameters (.'$openapi#Operation'.parameters)
static bool _jm_f_41(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.parameters
    res = json_is_array(val);
    if (res)
    {
        size_t arr_5_idx;
        json_t *arr_5_item;
        json_array_foreach(val, arr_5_idx, arr_5_item)
        {
            Path arr_5_lpath = (Path) { NULL, arr_5_idx, path, NULL };
            // .'$openapi#Operation'.parameters.0
            // .'$openapi#Operation'.parameters.0.'|'.0
            res = json_model_21(arr_5_item, (path ? &arr_5_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$openapi#Operation'.parameters.0.'|'.0]", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                // .'$openapi#Operation'.parameters.0.'|'.1
                res = json_model_33(arr_5_item, (path ? &arr_5_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Operation'.parameters.0.'|'.1]", (path ? &arr_5_lpath : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Operation'.parameters.0.'|']", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#Operation'.parameters]", path);
    }
    return res;
}

// check _jm_obj_22_map_requestBody (.'$openapi#Operation'.requestBody)
static bool _jm_f_42(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.requestBody
    // .'$openapi#Operation'.requestBody.'|'.0
    res = json_model_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [.'$openapi#Operation'.requestBody.'|'.0]", path);
    }
    if (! res)
    {
        // .'$openapi#Operation'.requestBody.'|'.1
        res = json_model_33(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Operation'.requestBody.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Operation'.requestBody.'|']", path);
    }
    return res;
}

// check _jm_obj_22_map_responses (.'$openapi#Operation'.responses)
static bool _jm_f_43(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.responses
    res = json_model_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Responses [.'$openapi#Operation'.responses]", path);
    }
    return res;
}

// check _jm_obj_22_map_security (.'$openapi#Operation'.security)
static bool _jm_f_44(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.security
    res = json_is_array(val);
    if (res)
    {
        size_t arr_6_idx;
        json_t *arr_6_item;
        json_array_foreach(val, arr_6_idx, arr_6_item)
        {
            Path arr_6_lpath = (Path) { NULL, arr_6_idx, path, NULL };
            // .'$openapi#Operation'.security.0
            res = json_model_41(arr_6_item, (path ? &arr_6_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [.'$openapi#Operation'.security.0]", (path ? &arr_6_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#Operation'.security]", path);
    }
    return res;
}

// check _jm_obj_22_map_servers (.'$openapi#Operation'.servers)
static bool _jm_f_45(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_7_idx;
        json_t *arr_7_item;
        json_array_foreach(val, arr_7_idx, arr_7_item)
        {
            Path arr_7_lpath = (Path) { NULL, arr_7_idx, path, NULL };
            // .'$openapi#Operation'.servers.0
            res = json_model_9(arr_7_item, (path ? &arr_7_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$openapi#Operation'.servers.0]", (path ? &arr_7_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#Operation'.servers]", path);
    }
    return res;
}

// check _jm_obj_22_map_summary (.'$openapi#Operation'.summary)
static bool _jm_f_46(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Operation'.summary]", path);
    }
    return res;
}

// check _jm_obj_22_map_tags (.'$openapi#Operation'.tags)
static bool _jm_f_47(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_8_idx;
        json_t *arr_8_item;
        json_array_foreach(val, arr_8_idx, arr_8_item)
        {
            Path arr_8_lpath = (Path) { NULL, arr_8_idx, path, NULL };
            // .'$openapi#Operation'.tags.0
            res = json_is_string(arr_8_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Operation'.tags.0]", (path ? &arr_8_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#Operation'.tags]", path);
    }
    return res;
}

static check_fun_t _jm_obj_22_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_22_map_tab, 12);
}

// object .'$openapi#Operation'
static bool _jm_obj_22(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Operation']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_22 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_22_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_22 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Operation']", (path ? &lpath_22 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Operation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Operation'.'/^x\\\\-.*$/']", (path ? &lpath_22 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Operation']", (path ? &lpath_22 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Operation (.'$openapi#Operation')
static bool json_model_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Operation'
    res = _jm_obj_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Operation']", path);
    }
    return res;
}

// object .'$openapi#ExternalDocumentation'
static bool _jm_obj_24(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#ExternalDocumentation']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_24 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$openapi#ExternalDocumentation'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#ExternalDocumentation'.url]", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#ExternalDocumentation'.url]", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#ExternalDocumentation'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#ExternalDocumentation'.description]", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#ExternalDocumentation'.description]", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#ExternalDocumentation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#ExternalDocumentation'.'/^x\\\\-.*$/']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#ExternalDocumentation']", (path ? &lpath_24 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <url> [.'$openapi#ExternalDocumentation']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#ExternalDocumentation (.'$openapi#ExternalDocumentation')
static bool json_model_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#ExternalDocumentation'
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#ExternalDocumentation']", path);
    }
    return res;
}


// check _jm_obj_25_map_allowEmptyValue (.'$openapi#Parameter'.'|'.1.allowEmptyValue)
static bool _jm_f_48(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.1.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.1.allowEmptyValue]", path);
    }
    return res;
}

// object .'$openapi#Parameter'.'|'.1.content
static bool _jm_obj_26(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Parameter'.'|'.1.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_26 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Parameter'.'|'.1.content.''
        res = json_model_23(pval, (path ? &lpath_26 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$openapi#Parameter'.'|'.1.content.'']", (path ? &lpath_26 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_25_map_content (.'$openapi#Parameter'.'|'.1.content)
static bool _jm_f_49(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.1.content
    res = _jm_obj_26(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Parameter'.'|'.1.content]", path);
    }
    return res;
}

// check _jm_obj_25_map_deprecated (.'$openapi#Parameter'.'|'.1.deprecated)
static bool _jm_f_50(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.1.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.1.deprecated]", path);
    }
    return res;
}

// check _jm_obj_25_map_description (.'$openapi#Parameter'.'|'.1.description)
static bool _jm_f_51(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Parameter'.'|'.1.description]", path);
    }
    return res;
}

// check _jm_obj_25_map_required (.'$openapi#Parameter'.'|'.1.required)
static bool _jm_f_52(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.1.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.1.required]", path);
    }
    return res;
}

static check_fun_t _jm_obj_25_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_25_map_tab, 5);
}

// object .'$openapi#Parameter'.'|'.1
static bool _jm_obj_25(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Parameter'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_25 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$openapi#Parameter'.'|'.1.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Parameter'.'|'.1.name]", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Parameter'.'|'.1.name]", (path ? &lpath_25 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "in") == 0)
        {
            // handle must in property
            must_count += 1;
            // .'$openapi#Parameter'.'|'.1.in
            res = _json_is_scalar(pval) && json_is_string(pval) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(pval) } }, _jm_cst_0, 4);;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "value not in enum [.'$openapi#Parameter'.'|'.1.in.'|']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Parameter'.'|'.1.in]", (path ? &lpath_25 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_25_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_25 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Parameter'.'|'.1]", (path ? &lpath_25 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Parameter'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Parameter'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Parameter'.'|'.1]", (path ? &lpath_25 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <in> [.'$openapi#Parameter'.'|'.1]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#Parameter'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}


// check _jm_obj_27_map_allowEmptyValue (.'$openapi#Parameter'.'|'.0.allowEmptyValue)
static bool _jm_f_53(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.0.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_27_map_allowReserved (.'$openapi#Parameter'.'|'.0.allowReserved)
static bool _jm_f_54(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.0.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_27_map_deprecated (.'$openapi#Parameter'.'|'.0.deprecated)
static bool _jm_f_55(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.0.deprecated]", path);
    }
    return res;
}

// check _jm_obj_27_map_description (.'$openapi#Parameter'.'|'.0.description)
static bool _jm_f_56(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Parameter'.'|'.0.description]", path);
    }
    return res;
}

// check _jm_obj_27_map_example (.'$openapi#Parameter'.'|'.0.example)
static bool _jm_f_57(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Parameter'.'|'.0.example]", path);
    }
    return res;
}

// object .'$openapi#Parameter'.'|'.0.examples
static bool _jm_obj_28(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Parameter'.'|'.0.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_28 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Parameter'.'|'.0.examples.''
        // .'$openapi#Parameter'.'|'.0.examples.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_28 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$openapi#Parameter'.'|'.0.examples.''.'|'.0]", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Parameter'.'|'.0.examples.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_28 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Parameter'.'|'.0.examples.''.'|'.1]", (path ? &lpath_28 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Parameter'.'|'.0.examples.''.'|']", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_27_map_examples (.'$openapi#Parameter'.'|'.0.examples)
static bool _jm_f_58(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.examples
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Parameter'.'|'.0.examples]", path);
    }
    return res;
}

// check _jm_obj_27_map_explode (.'$openapi#Parameter'.'|'.0.explode)
static bool _jm_f_59(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.0.explode]", path);
    }
    return res;
}

// check _jm_obj_27_map_model (.'$openapi#Parameter'.'|'.0.model)
static bool _jm_f_60(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.model
    res = json_model_61(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#Parameter'.'|'.0.model]", path);
    }
    return res;
}

// check _jm_obj_27_map_required (.'$openapi#Parameter'.'|'.0.required)
static bool _jm_f_61(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Parameter'.'|'.0.required]", path);
    }
    return res;
}

// check _jm_obj_27_map_style (.'$openapi#Parameter'.'|'.0.style)
static bool _jm_f_62(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'.'|'.0.style
    res = json_model_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$openapi#Parameter'.'|'.0.style]", path);
    }
    return res;
}

static check_fun_t _jm_obj_27_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_27_map_tab, 10);
}

// object .'$openapi#Parameter'.'|'.0
static bool _jm_obj_27(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Parameter'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_27 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$openapi#Parameter'.'|'.0.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Parameter'.'|'.0.name]", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Parameter'.'|'.0.name]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "in") == 0)
        {
            // handle must in property
            must_count += 1;
            // .'$openapi#Parameter'.'|'.0.in
            res = _json_is_scalar(pval) && json_is_string(pval) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(pval) } }, _jm_cst_1, 4);;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "value not in enum [.'$openapi#Parameter'.'|'.0.in.'|']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Parameter'.'|'.0.in]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_27_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_27 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Parameter'.'|'.0]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Parameter'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Parameter'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Parameter'.'|'.0]", (path ? &lpath_27 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <in> [.'$openapi#Parameter'.'|'.0]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#Parameter'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Parameter (.'$openapi#Parameter')
static bool json_model_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Parameter'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#Parameter'.'|']", path);
    }
    if (res)
    {
        // .'$openapi#Parameter'.'|'.0
        res = _jm_obj_27(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Parameter'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$openapi#Parameter'.'|'.1
            res = _jm_obj_25(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Parameter'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Parameter'.'|']", path);
        }
    }
    return res;
}


// check $openapi#Style (.'$openapi#Style')
static bool json_model_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Style'
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_2, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$openapi#Style'.'|']", path);
    }
    return res;
}

// object .'$openapi#RequestBody'.content
static bool _jm_obj_30(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#RequestBody'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_30 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#RequestBody'.content.''
        res = json_model_23(pval, (path ? &lpath_30 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$openapi#RequestBody'.content.'']", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$openapi#RequestBody'
static bool _jm_obj_29(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#RequestBody']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_29 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#RequestBody'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#RequestBody'.description]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#RequestBody'.description]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "content") == 0)
        {
            // handle may content property
            // .'$openapi#RequestBody'.content
            res = _jm_obj_30(pval, (path ? &lpath_29 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#RequestBody'.content]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#RequestBody'.content]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "required") == 0)
        {
            // handle may required property
            // .'$openapi#RequestBody'.required
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#RequestBody'.required]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#RequestBody'.required]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#RequestBody'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#RequestBody'.'/^x\\\\-.*$/']", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#RequestBody']", (path ? &lpath_29 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#RequestBody (.'$openapi#RequestBody')
static bool json_model_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#RequestBody'
    res = _jm_obj_29(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#RequestBody']", path);
    }
    return res;
}

// object .'$openapi#MediaType'.encoding
static bool _jm_obj_32(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#MediaType'.encoding]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_32 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#MediaType'.encoding.''
        res = json_model_24(pval, (path ? &lpath_32 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Encoding [.'$openapi#MediaType'.encoding.'']", (path ? &lpath_32 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_31_map_encoding (.'$openapi#MediaType'.encoding)
static bool _jm_f_63(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#MediaType'.encoding
    res = _jm_obj_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#MediaType'.encoding]", path);
    }
    return res;
}

// check _jm_obj_31_map_example (.'$openapi#MediaType'.example)
static bool _jm_f_64(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#MediaType'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#MediaType'.example]", path);
    }
    return res;
}

// object .'$openapi#MediaType'.examples
static bool _jm_obj_33(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#MediaType'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_33 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#MediaType'.examples.''
        // .'$openapi#MediaType'.examples.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_33 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$openapi#MediaType'.examples.''.'|'.0]", (path ? &lpath_33 : NULL));
        }
        if (! res)
        {
            // .'$openapi#MediaType'.examples.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_33 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#MediaType'.examples.''.'|'.1]", (path ? &lpath_33 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#MediaType'.examples.''.'|']", (path ? &lpath_33 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_31_map_examples (.'$openapi#MediaType'.examples)
static bool _jm_f_65(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#MediaType'.examples
    res = _jm_obj_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#MediaType'.examples]", path);
    }
    return res;
}

// check _jm_obj_31_map_model (.'$openapi#MediaType'.model)
static bool _jm_f_66(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#MediaType'.model
    res = json_model_61(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#MediaType'.model]", path);
    }
    return res;
}

static check_fun_t _jm_obj_31_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_31_map_tab, 4);
}

// object .'$openapi#MediaType'
static bool _jm_obj_31(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#MediaType']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_31 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_31_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_31 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#MediaType']", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#MediaType'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#MediaType'.'/^x\\\\-.*$/']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#MediaType']", (path ? &lpath_31 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#MediaType (.'$openapi#MediaType')
static bool json_model_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#MediaType'
    res = _jm_obj_31(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#MediaType']", path);
    }
    return res;
}

// check _jm_obj_34_map_allowReserved (.'$openapi#Encoding'.allowReserved)
static bool _jm_f_67(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Encoding'.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_34_map_contentType (.'$openapi#Encoding'.contentType)
static bool _jm_f_68(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'.contentType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Encoding'.contentType]", path);
    }
    return res;
}

// check _jm_obj_34_map_explode (.'$openapi#Encoding'.explode)
static bool _jm_f_69(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Encoding'.explode]", path);
    }
    return res;
}

// object .'$openapi#Encoding'.headers
static bool _jm_obj_35(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Encoding'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_35 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Encoding'.headers.''
        // .'$openapi#Encoding'.headers.''.'|'.0
        res = json_model_31(pval, (path ? &lpath_35 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$openapi#Encoding'.headers.''.'|'.0]", (path ? &lpath_35 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Encoding'.headers.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_35 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Encoding'.headers.''.'|'.1]", (path ? &lpath_35 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Encoding'.headers.''.'|']", (path ? &lpath_35 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_34_map_headers (.'$openapi#Encoding'.headers)
static bool _jm_f_70(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'.headers
    res = _jm_obj_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Encoding'.headers]", path);
    }
    return res;
}

// check _jm_obj_34_map_style (.'$openapi#Encoding'.style)
static bool _jm_f_71(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'.style
    res = json_model_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$openapi#Encoding'.style]", path);
    }
    return res;
}

static check_fun_t _jm_obj_34_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_34_map_tab, 5);
}

// object .'$openapi#Encoding'
static bool _jm_obj_34(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Encoding']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_34 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_34_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_34 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Encoding']", (path ? &lpath_34 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Encoding'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Encoding'.'/^x\\\\-.*$/']", (path ? &lpath_34 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Encoding']", (path ? &lpath_34 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Encoding (.'$openapi#Encoding')
static bool json_model_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Encoding'
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Encoding']", path);
    }
    return res;
}

static bool _jm_re_3(const char *s)
{
  int rc = pcre2_match(_jm_re_3_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_3_data, NULL);
  return rc >= 0;
}

// object .'$openapi#Responses'
static bool _jm_obj_36(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Responses']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_36 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "default") == 0)
        {
            // handle may default property
            // .'$openapi#Responses'.default
            // .'$openapi#Responses'.default.'|'.0
            res = json_model_26(pval, (path ? &lpath_36 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$openapi#Responses'.default.'|'.0]", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                // .'$openapi#Responses'.default.'|'.1
                res = json_model_33(pval, (path ? &lpath_36 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Responses'.default.'|'.1]", (path ? &lpath_36 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Responses'.default.'|']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Responses'.default]", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 2 re props
            // .'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'
            // .'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.0
            res = json_model_26(pval, (path ? &lpath_36 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.0]", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                // .'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.1
                res = json_model_33(pval, (path ? &lpath_36 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.1]", (path ? &lpath_36 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$openapi#Responses'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Responses'.'/^x\\\\-.*$/']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Responses']", (path ? &lpath_36 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Responses (.'$openapi#Responses')
static bool json_model_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Responses'
    res = _jm_obj_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Responses']", path);
    }
    return res;
}

// object .'$openapi#Response'.content
static bool _jm_obj_38(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Response'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_38 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Response'.content.''
        res = json_model_23(pval, (path ? &lpath_38 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$openapi#Response'.content.'']", (path ? &lpath_38 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_37_map_content (.'$openapi#Response'.content)
static bool _jm_f_72(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Response'.content
    res = _jm_obj_38(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Response'.content]", path);
    }
    return res;
}

// check _jm_obj_37_map_description (.'$openapi#Response'.description)
static bool _jm_f_73(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Response'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Response'.description]", path);
    }
    return res;
}

// object .'$openapi#Response'.headers
static bool _jm_obj_39(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Response'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_39 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Response'.headers.''
        // .'$openapi#Response'.headers.''.'|'.0
        res = json_model_31(pval, (path ? &lpath_39 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$openapi#Response'.headers.''.'|'.0]", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Response'.headers.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_39 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Response'.headers.''.'|'.1]", (path ? &lpath_39 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Response'.headers.''.'|']", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_37_map_headers (.'$openapi#Response'.headers)
static bool _jm_f_74(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Response'.headers
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Response'.headers]", path);
    }
    return res;
}

// object .'$openapi#Response'.links
static bool _jm_obj_40(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Response'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_40 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Response'.links.''
        // .'$openapi#Response'.links.''.'|'.0
        res = json_model_30(pval, (path ? &lpath_40 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [.'$openapi#Response'.links.''.'|'.0]", (path ? &lpath_40 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Response'.links.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_40 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Response'.links.''.'|'.1]", (path ? &lpath_40 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Response'.links.''.'|']", (path ? &lpath_40 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_37_map_links (.'$openapi#Response'.links)
static bool _jm_f_75(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Response'.links
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Response'.links]", path);
    }
    return res;
}

static check_fun_t _jm_obj_37_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_37_map_tab, 4);
}

// object .'$openapi#Response'
static bool _jm_obj_37(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Response']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_37 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_37_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_37 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Response']", (path ? &lpath_37 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Response'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Response'.'/^x\\\\-.*$/']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Response']", (path ? &lpath_37 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Response (.'$openapi#Response')
static bool json_model_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Response'
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Response']", path);
    }
    return res;
}

// object .'$openapi#Callback'
static bool _jm_obj_41(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Callback']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_41 = (Path) { prop, 0, path, NULL };
        if (jm_check_fun_string(json_model_29, prop, (path ? &lpath_41 : NULL), rep))
        {
            // handle 1 key props
            // .'$openapi#Callback'.'$Expression'
            // .'$openapi#Callback'.'$Expression'.'|'.0
            res = json_model_13(pval, (path ? &lpath_41 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$openapi#Callback'.'$Expression'.'|'.0]", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                // .'$openapi#Callback'.'$Expression'.'|'.1
                res = json_model_33(pval, (path ? &lpath_41 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Callback'.'$Expression'.'|'.1]", (path ? &lpath_41 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Callback'.'$Expression'.'|']", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Callback'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Callback'.'/^x\\\\-.*$/']", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Callback']", (path ? &lpath_41 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Callback (.'$openapi#Callback')
static bool json_model_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Callback'
    res = _jm_obj_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Callback']", path);
    }
    return res;
}

// check _jm_obj_42_map_description (.'$openapi#Example'.description)
static bool _jm_f_76(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Example'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Example'.description]", path);
    }
    return res;
}

// check _jm_obj_42_map_externalValue (.'$openapi#Example'.externalValue)
static bool _jm_f_77(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Example'.externalValue
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Example'.externalValue]", path);
    }
    return res;
}

// check _jm_obj_42_map_summary (.'$openapi#Example'.summary)
static bool _jm_f_78(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Example'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Example'.summary]", path);
    }
    return res;
}

// check _jm_obj_42_map_value (.'$openapi#Example'.value)
static bool _jm_f_79(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Example'.value
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Example'.value]", path);
    }
    return res;
}

static check_fun_t _jm_obj_42_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_42_map_tab, 4);
}

// object .'$openapi#Example'
static bool _jm_obj_42(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Example']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_42 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_42_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_42 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Example']", (path ? &lpath_42 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Example'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Example'.'/^x\\\\-.*$/']", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Example']", (path ? &lpath_42 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Example (.'$openapi#Example')
static bool json_model_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Example'
    res = _jm_obj_42(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Example']", path);
    }
    return res;
}

// check $openapi#Expression (.'$openapi#Expression')
static bool json_model_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Expression'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Expression']", path);
    }
    return res;
}

// check _jm_obj_43_map_description (.'$openapi#Link'.'|'.1.description)
static bool _jm_f_80(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Link'.'|'.1.description]", path);
    }
    return res;
}

// object .'$openapi#Link'.'|'.1.parameters
static bool _jm_obj_44(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Link'.'|'.1.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_43_map_parameters (.'$openapi#Link'.'|'.1.parameters)
static bool _jm_f_81(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.1.parameters
    res = _jm_obj_44(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Link'.'|'.1.parameters]", path);
    }
    return res;
}

// check _jm_obj_43_map_requestBody (.'$openapi#Link'.'|'.1.requestBody)
static bool _jm_f_82(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.1.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Link'.'|'.1.requestBody]", path);
    }
    return res;
}

// check _jm_obj_43_map_server (.'$openapi#Link'.'|'.1.server)
static bool _jm_f_83(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.1.server
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$openapi#Link'.'|'.1.server]", path);
    }
    return res;
}

static check_fun_t _jm_obj_43_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_43_map_tab, 4);
}

// object .'$openapi#Link'.'|'.1
static bool _jm_obj_43(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Link'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_43 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "operationId") == 0)
        {
            // handle must operationId property
            must_count += 1;
            // .'$openapi#Link'.'|'.1.operationId
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Link'.'|'.1.operationId]", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Link'.'|'.1.operationId]", (path ? &lpath_43 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_43_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_43 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Link'.'|'.1]", (path ? &lpath_43 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Link'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Link'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Link'.'|'.1]", (path ? &lpath_43 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "operationId") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <operationId> [.'$openapi#Link'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_45_map_description (.'$openapi#Link'.'|'.0.description)
static bool _jm_f_84(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Link'.'|'.0.description]", path);
    }
    return res;
}

// object .'$openapi#Link'.'|'.0.parameters
static bool _jm_obj_46(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Link'.'|'.0.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_45_map_parameters (.'$openapi#Link'.'|'.0.parameters)
static bool _jm_f_85(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.0.parameters
    res = _jm_obj_46(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Link'.'|'.0.parameters]", path);
    }
    return res;
}

// check _jm_obj_45_map_requestBody (.'$openapi#Link'.'|'.0.requestBody)
static bool _jm_f_86(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.0.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Link'.'|'.0.requestBody]", path);
    }
    return res;
}

// check _jm_obj_45_map_server (.'$openapi#Link'.'|'.0.server)
static bool _jm_f_87(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'.'|'.0.server
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$openapi#Link'.'|'.0.server]", path);
    }
    return res;
}

static check_fun_t _jm_obj_45_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_45_map_tab, 4);
}

// object .'$openapi#Link'.'|'.0
static bool _jm_obj_45(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Link'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_44 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "operationRef") == 0)
        {
            // handle must operationRef property
            must_count += 1;
            // .'$openapi#Link'.'|'.0.operationRef
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Link'.'|'.0.operationRef]", (path ? &lpath_44 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Link'.'|'.0.operationRef]", (path ? &lpath_44 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_45_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_44 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Link'.'|'.0]", (path ? &lpath_44 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Link'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Link'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_44 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Link'.'|'.0]", (path ? &lpath_44 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "operationRef") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <operationRef> [.'$openapi#Link'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Link (.'$openapi#Link')
static bool json_model_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Link'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#Link'.'|']", path);
    }
    if (res)
    {
        // .'$openapi#Link'.'|'.0
        res = _jm_obj_45(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Link'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$openapi#Link'.'|'.1
            res = _jm_obj_43(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Link'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Link'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_47_map_allowEmptyValue (.'$openapi#Header'.'|'.1.allowEmptyValue)
static bool _jm_f_88(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.1.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.1.allowEmptyValue]", path);
    }
    return res;
}

// object .'$openapi#Header'.'|'.1.content
static bool _jm_obj_48(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Header'.'|'.1.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_46 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Header'.'|'.1.content.''
        res = json_model_23(pval, (path ? &lpath_46 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$openapi#Header'.'|'.1.content.'']", (path ? &lpath_46 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_47_map_content (.'$openapi#Header'.'|'.1.content)
static bool _jm_f_89(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.1.content
    res = _jm_obj_48(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Header'.'|'.1.content]", path);
    }
    return res;
}

// check _jm_obj_47_map_deprecated (.'$openapi#Header'.'|'.1.deprecated)
static bool _jm_f_90(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.1.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.1.deprecated]", path);
    }
    return res;
}

// check _jm_obj_47_map_description (.'$openapi#Header'.'|'.1.description)
static bool _jm_f_91(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Header'.'|'.1.description]", path);
    }
    return res;
}

// check _jm_obj_47_map_required (.'$openapi#Header'.'|'.1.required)
static bool _jm_f_92(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.1.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.1.required]", path);
    }
    return res;
}

static check_fun_t _jm_obj_47_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_47_map_tab, 5);
}

// object .'$openapi#Header'.'|'.1
static bool _jm_obj_47(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Header'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_45 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_47_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_45 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Header'.'|'.1]", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Header'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Header'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_45 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Header'.'|'.1]", (path ? &lpath_45 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_49_map_allowEmptyValue (.'$openapi#Header'.'|'.0.allowEmptyValue)
static bool _jm_f_93(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.0.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_49_map_allowReserved (.'$openapi#Header'.'|'.0.allowReserved)
static bool _jm_f_94(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.0.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_49_map_deprecated (.'$openapi#Header'.'|'.0.deprecated)
static bool _jm_f_95(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.0.deprecated]", path);
    }
    return res;
}

// check _jm_obj_49_map_description (.'$openapi#Header'.'|'.0.description)
static bool _jm_f_96(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Header'.'|'.0.description]", path);
    }
    return res;
}

// check _jm_obj_49_map_example (.'$openapi#Header'.'|'.0.example)
static bool _jm_f_97(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Header'.'|'.0.example]", path);
    }
    return res;
}

// object .'$openapi#Header'.'|'.0.examples
static bool _jm_obj_50(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Header'.'|'.0.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_48 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#Header'.'|'.0.examples.''
        // .'$openapi#Header'.'|'.0.examples.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_48 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$openapi#Header'.'|'.0.examples.''.'|'.0]", (path ? &lpath_48 : NULL));
        }
        if (! res)
        {
            // .'$openapi#Header'.'|'.0.examples.''.'|'.1
            res = json_model_33(pval, (path ? &lpath_48 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$openapi#Header'.'|'.0.examples.''.'|'.1]", (path ? &lpath_48 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Header'.'|'.0.examples.''.'|']", (path ? &lpath_48 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_49_map_examples (.'$openapi#Header'.'|'.0.examples)
static bool _jm_f_98(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.examples
    res = _jm_obj_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Header'.'|'.0.examples]", path);
    }
    return res;
}

// check _jm_obj_49_map_explode (.'$openapi#Header'.'|'.0.explode)
static bool _jm_f_99(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.0.explode]", path);
    }
    return res;
}

// check _jm_obj_49_map_model (.'$openapi#Header'.'|'.0.model)
static bool _jm_f_100(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.model
    res = json_model_61(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#Header'.'|'.0.model]", path);
    }
    return res;
}

// check _jm_obj_49_map_required (.'$openapi#Header'.'|'.0.required)
static bool _jm_f_101(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#Header'.'|'.0.required]", path);
    }
    return res;
}

// check _jm_obj_49_map_style (.'$openapi#Header'.'|'.0.style)
static bool _jm_f_102(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'.'|'.0.style
    res = json_model_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$openapi#Header'.'|'.0.style]", path);
    }
    return res;
}

static check_fun_t _jm_obj_49_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_49_map_tab, 10);
}

// object .'$openapi#Header'.'|'.0
static bool _jm_obj_49(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Header'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_47 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_49_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_47 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Header'.'|'.0]", (path ? &lpath_47 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Header'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Header'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Header'.'|'.0]", (path ? &lpath_47 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Header (.'$openapi#Header')
static bool json_model_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Header'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#Header'.'|']", path);
    }
    if (res)
    {
        // .'$openapi#Header'.'|'.0
        res = _jm_obj_49(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Header'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$openapi#Header'.'|'.1
            res = _jm_obj_47(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Header'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#Header'.'|']", path);
        }
    }
    return res;
}

// object .'$openapi#Tag'
static bool _jm_obj_51(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Tag']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_49 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$openapi#Tag'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Tag'.name]", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Tag'.name]", (path ? &lpath_49 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#Tag'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Tag'.description]", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Tag'.description]", (path ? &lpath_49 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "externalDocs") == 0)
        {
            // handle may externalDocs property
            // .'$openapi#Tag'.externalDocs
            res = json_model_15(pval, (path ? &lpath_49 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$openapi#Tag'.externalDocs]", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Tag'.externalDocs]", (path ? &lpath_49 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#Tag'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#Tag'.'/^x\\\\-.*$/']", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Tag']", (path ? &lpath_49 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#Tag']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Tag (.'$openapi#Tag')
static bool json_model_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Tag'
    res = _jm_obj_51(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Tag']", path);
    }
    return res;
}

// object .'$openapi#Reference'
static bool _jm_obj_52(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#Reference']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_50 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "$ref") == 0)
        {
            // handle must $ref property
            must_count += 1;
            // .'$openapi#Reference'.'$ref'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Reference'.'$ref']", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#Reference'.$ref]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "summary") == 0)
        {
            // handle may summary property
            // .'$openapi#Reference'.summary
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Reference'.summary]", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Reference'.summary]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#Reference'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#Reference'.description]", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#Reference'.description]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#Reference']", (path ? &lpath_50 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "$ref") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <$ref> [.'$openapi#Reference']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#Reference (.'$openapi#Reference')
static bool json_model_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Reference'
    res = _jm_obj_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#Reference']", path);
    }
    return res;
}

// check _jm_obj_53_mup_flows (.'$openapi#SecurityScheme'.flows)
static bool _jm_f_103(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.flows
    res = json_model_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlows [.'$openapi#SecurityScheme'.flows]", path);
    }
    return res;
}


// check _jm_obj_53_mup_in (.'$openapi#SecurityScheme'.in)
static bool _jm_f_104(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.in
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_3, 3);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$openapi#SecurityScheme'.in.'|']", path);
    }
    return res;
}

// check _jm_obj_53_mup_name (.'$openapi#SecurityScheme'.name)
static bool _jm_f_105(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.name]", path);
    }
    return res;
}

// check _jm_obj_53_mup_openIdConnectUrl (.'$openapi#SecurityScheme'.openIdConnectUrl)
static bool _jm_f_106(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.openIdConnectUrl
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.openIdConnectUrl]", path);
    }
    return res;
}

// check _jm_obj_53_mup_scheme (.'$openapi#SecurityScheme'.scheme)
static bool _jm_f_107(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.scheme
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.scheme]", path);
    }
    return res;
}

// check _jm_obj_53_mup_type (.'$openapi#SecurityScheme'.type)
static bool _jm_f_108(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'.type
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_53_mup(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_53_mup_tab, 6);
}

// object .'$openapi#SecurityScheme'
static bool _jm_obj_53(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#SecurityScheme']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_51 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_53_mup(prop)))
        {
            // handle 6 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_51 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#SecurityScheme']", (path ? &lpath_51 : NULL));
                    return false;
                }
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$openapi#SecurityScheme'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.description]", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#SecurityScheme'.description]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "bearerFormat") == 0)
        {
            // handle may bearerFormat property
            // .'$openapi#SecurityScheme'.bearerFormat
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityScheme'.bearerFormat]", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#SecurityScheme'.bearerFormat]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#SecurityScheme'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#SecurityScheme'.'/^x\\\\-.*$/']", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#SecurityScheme']", (path ? &lpath_51 : NULL));
            return false;
        }
    }
    if (must_count != 6)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "flows") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <flows> [.'$openapi#SecurityScheme']", path);
            }
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <in> [.'$openapi#SecurityScheme']", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <name> [.'$openapi#SecurityScheme']", path);
            }
            if (! (json_object_get(val, "openIdConnectUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <openIdConnectUrl> [.'$openapi#SecurityScheme']", path);
            }
            if (! (json_object_get(val, "scheme") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <scheme> [.'$openapi#SecurityScheme']", path);
            }
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <type> [.'$openapi#SecurityScheme']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#SecurityScheme (.'$openapi#SecurityScheme')
static bool json_model_38(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityScheme'
    res = _jm_obj_53(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#SecurityScheme']", path);
    }
    return res;
}

// check _jm_obj_54_map_authorizationCode (.'$openapi#OAuthFlows'.authorizationCode)
static bool _jm_f_109(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlows'.authorizationCode
    res = json_model_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$openapi#OAuthFlows'.authorizationCode]", path);
    }
    return res;
}

// check _jm_obj_54_map_clientCredentials (.'$openapi#OAuthFlows'.clientCredentials)
static bool _jm_f_110(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlows'.clientCredentials
    res = json_model_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$openapi#OAuthFlows'.clientCredentials]", path);
    }
    return res;
}

// check _jm_obj_54_map_implicit (.'$openapi#OAuthFlows'.implicit)
static bool _jm_f_111(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlows'.implicit
    res = json_model_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$openapi#OAuthFlows'.implicit]", path);
    }
    return res;
}

// check _jm_obj_54_map_password (.'$openapi#OAuthFlows'.password)
static bool _jm_f_112(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlows'.password
    res = json_model_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$openapi#OAuthFlows'.password]", path);
    }
    return res;
}

static check_fun_t _jm_obj_54_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_54_map_tab, 4);
}

// object .'$openapi#OAuthFlows'
static bool _jm_obj_54(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#OAuthFlows']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_52 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_54_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_52 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#OAuthFlows']", (path ? &lpath_52 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#OAuthFlows'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#OAuthFlows'.'/^x\\\\-.*$/']", (path ? &lpath_52 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#OAuthFlows']", (path ? &lpath_52 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#OAuthFlows (.'$openapi#OAuthFlows')
static bool json_model_39(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlows'
    res = _jm_obj_54(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#OAuthFlows']", path);
    }
    return res;
}

// object .'$openapi#OAuthFlow'.scopes
static bool _jm_obj_56(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#OAuthFlow'.scopes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_54 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#OAuthFlow'.scopes.''
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#OAuthFlow'.scopes.'']", (path ? &lpath_54 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$openapi#OAuthFlow'
static bool _jm_obj_55(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#OAuthFlow']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_53 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "authorizationUrl") == 0)
        {
            // handle must authorizationUrl property
            must_count += 1;
            // .'$openapi#OAuthFlow'.authorizationUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#OAuthFlow'.authorizationUrl]", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#OAuthFlow'.authorizationUrl]", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "tokenUrl") == 0)
        {
            // handle must tokenUrl property
            must_count += 1;
            // .'$openapi#OAuthFlow'.tokenUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#OAuthFlow'.tokenUrl]", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#OAuthFlow'.tokenUrl]", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "scopes") == 0)
        {
            // handle must scopes property
            must_count += 1;
            // .'$openapi#OAuthFlow'.scopes
            res = _jm_obj_56(pval, (path ? &lpath_53 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#OAuthFlow'.scopes]", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#OAuthFlow'.scopes]", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "refreshUrl") == 0)
        {
            // handle may refreshUrl property
            // .'$openapi#OAuthFlow'.refreshUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$openapi#OAuthFlow'.refreshUrl]", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#OAuthFlow'.refreshUrl]", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$openapi#OAuthFlow'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$openapi#OAuthFlow'.'/^x\\\\-.*$/']", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#OAuthFlow']", (path ? &lpath_53 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "authorizationUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <authorizationUrl> [.'$openapi#OAuthFlow']", path);
            }
            if (! (json_object_get(val, "scopes") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <scopes> [.'$openapi#OAuthFlow']", path);
            }
            if (! (json_object_get(val, "tokenUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <tokenUrl> [.'$openapi#OAuthFlow']", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#OAuthFlow (.'$openapi#OAuthFlow')
static bool json_model_40(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#OAuthFlow'
    res = _jm_obj_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#OAuthFlow']", path);
    }
    return res;
}

// object .'$openapi#SecurityRequirement'
static bool _jm_obj_57(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#SecurityRequirement']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_55 = (Path) { prop, 0, path, NULL };
        // handle other props
        // .'$openapi#SecurityRequirement'.''
        res = json_is_array(pval);
        if (res)
        {
            size_t arr_9_idx;
            json_t *arr_9_item;
            json_array_foreach(pval, arr_9_idx, arr_9_item)
            {
                Path arr_9_lpath = (Path) { NULL, arr_9_idx, (path ? &lpath_55 : NULL), NULL };
                // .'$openapi#SecurityRequirement'.''.0
                res = json_is_string(arr_9_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#SecurityRequirement'.''.0]", ((path ? &lpath_55 : NULL) ? &arr_9_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#SecurityRequirement'.'']", (path ? &lpath_55 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check $openapi#SecurityRequirement (.'$openapi#SecurityRequirement')
static bool json_model_41(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#SecurityRequirement'
    res = _jm_obj_57(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#SecurityRequirement']", path);
    }
    return res;
}

// check $openapi#Model (.'$openapi#Model')
static bool json_model_61(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#Model'
    res = json_model_78(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $model#Model [.'$openapi#Model']", path);
    }
    return res;
}

// check $openapi#model#Model (.'$openapi#model#Model')
static bool json_model_78(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#model#Model'
    // .'$openapi#model#Model'.'|'.0
    res = json_model_77(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [.'$openapi#model#Model'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$openapi#model#Model'.'|'.1
        res = json_model_68(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$openapi#model#Model'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$openapi#model#Model'.'|'.2
            res = json_model_75(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Elem [.'$openapi#model#Model'.'|'.2]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#model#Model'.'|']", path);
    }
    return res;
}

// check $openapi#model#Array (.'$openapi#model#Array')
static bool json_model_68(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#model#Array'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_10_idx;
        json_t *arr_10_item;
        json_array_foreach(val, arr_10_idx, arr_10_item)
        {
            Path arr_10_lpath = (Path) { NULL, arr_10_idx, path, NULL };
            // .'$openapi#model#Array'.0
            res = json_model_78(arr_10_item, (path ? &arr_10_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Array'.0]", (path ? &arr_10_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#model#Array']", path);
    }
    return res;
}

static bool _jm_re_4(const char *s)
{
  int rc = pcre2_match(_jm_re_4_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_4_data, NULL);
  return rc >= 0;
}

// object .'$openapi#model#Elem'.'|'.5
static bool _jm_obj_58(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.5]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_56 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.5.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.5.'#']", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.5.#]", (path ? &lpath_56 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle 1 re props
            // .'$openapi#model#Elem'.'|'.5.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [.'$openapi#model#Elem'.'|'.5.'/^[@|&^+/*]$/']", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // .'$openapi#model#Elem'.'|'.5.''
            res = json_model_78(pval, (path ? &lpath_56 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.5.'']", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// object .'$openapi#model#Elem'.'|'.4
static bool _jm_obj_59(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.4]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_57 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "+") == 0)
        {
            // handle must + property
            must_count += 1;
            // .'$openapi#model#Elem'.'|'.4.'+'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_11_idx;
                json_t *arr_11_item;
                json_array_foreach(pval, arr_11_idx, arr_11_item)
                {
                    Path arr_11_lpath = (Path) { NULL, arr_11_idx, (path ? &lpath_57 : NULL), NULL };
                    // .'$openapi#model#Elem'.'|'.4.'+'.0
                    res = json_model_78(arr_11_item, ((path ? &lpath_57 : NULL) ? &arr_11_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.4.'+'.0]", ((path ? &lpath_57 : NULL) ? &arr_11_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#model#Elem'.'|'.4.'+']", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#model#Elem'.'|'.4.+]", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.4.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.4.'#']", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.4.#]", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#model#Elem'.'|'.4]", (path ? &lpath_57 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "+") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <+> [.'$openapi#model#Elem'.'|'.4]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$openapi#model#Elem'.'|'.3
static bool _jm_obj_60(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.3]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_58 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle must ^ property
            must_count += 1;
            // .'$openapi#model#Elem'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_12_idx;
                json_t *arr_12_item;
                json_array_foreach(pval, arr_12_idx, arr_12_item)
                {
                    Path arr_12_lpath = (Path) { NULL, arr_12_idx, (path ? &lpath_58 : NULL), NULL };
                    // .'$openapi#model#Elem'.'|'.3.'^'.0
                    res = json_model_78(arr_12_item, ((path ? &lpath_58 : NULL) ? &arr_12_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.3.'^'.0]", ((path ? &lpath_58 : NULL) ? &arr_12_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#model#Elem'.'|'.3.'^']", (path ? &lpath_58 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#model#Elem'.'|'.3.^]", (path ? &lpath_58 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.3.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.3.'#']", (path ? &lpath_58 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.3.#]", (path ? &lpath_58 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#model#Elem'.'|'.3]", (path ? &lpath_58 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "^") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <^> [.'$openapi#model#Elem'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$openapi#model#Elem'.'|'.2
static bool _jm_obj_61(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_59 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle must & property
            must_count += 1;
            // .'$openapi#model#Elem'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_13_idx;
                json_t *arr_13_item;
                json_array_foreach(pval, arr_13_idx, arr_13_item)
                {
                    Path arr_13_lpath = (Path) { NULL, arr_13_idx, (path ? &lpath_59 : NULL), NULL };
                    // .'$openapi#model#Elem'.'|'.2.'&'.0
                    res = json_model_78(arr_13_item, ((path ? &lpath_59 : NULL) ? &arr_13_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.2.'&'.0]", ((path ? &lpath_59 : NULL) ? &arr_13_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#model#Elem'.'|'.2.'&']", (path ? &lpath_59 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#model#Elem'.'|'.2.&]", (path ? &lpath_59 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.2.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.2.'#']", (path ? &lpath_59 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.2.#]", (path ? &lpath_59 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#model#Elem'.'|'.2]", (path ? &lpath_59 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "&") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <&> [.'$openapi#model#Elem'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$openapi#model#Elem'.'|'.1
static bool _jm_obj_62(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_60 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle must | property
            must_count += 1;
            // .'$openapi#model#Elem'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_14_idx;
                json_t *arr_14_item;
                json_array_foreach(pval, arr_14_idx, arr_14_item)
                {
                    Path arr_14_lpath = (Path) { NULL, arr_14_idx, (path ? &lpath_60 : NULL), NULL };
                    // .'$openapi#model#Elem'.'|'.1.'|'.0
                    res = json_model_78(arr_14_item, ((path ? &lpath_60 : NULL) ? &arr_14_lpath : NULL), rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.1.'|'.0]", ((path ? &lpath_60 : NULL) ? &arr_14_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$openapi#model#Elem'.'|'.1.'|']", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#model#Elem'.'|'.1.|]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.1.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.1.'#']", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.1.#]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#model#Elem'.'|'.1]", (path ? &lpath_60 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "|") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <|> [.'$openapi#model#Elem'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
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

// object .'$openapi#model#Elem'.'|'.0
static bool _jm_obj_63(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$openapi#model#Elem'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_61 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle must @ property
            must_count += 1;
            // .'$openapi#model#Elem'.'|'.0.'@'
            res = json_model_78(pval, (path ? &lpath_61 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [.'$openapi#model#Elem'.'|'.0.'@']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [.'$openapi#model#Elem'.'|'.0.@]", (path ? &lpath_61 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle may # property
            // .'$openapi#model#Elem'.'|'.0.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.0.'#']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.0.#]", (path ? &lpath_61 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "!") == 0)
        {
            // handle may ! property
            // .'$openapi#model#Elem'.'|'.0.'!'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#model#Elem'.'|'.0.'!']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [.'$openapi#model#Elem'.'|'.0.!]", (path ? &lpath_61 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle 2 re props
            // .'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // .'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                // .'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_61 : NULL));
                }
                if (! res)
                {
                    // .'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_61 : NULL));
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_6(prop))
        {
            // handle 2 re props
            // .'$openapi#model#Elem'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_64(pval, (path ? &lpath_61 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [.'$openapi#model#Elem'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [.'$openapi#model#Elem'.'|'.0]", (path ? &lpath_61 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "@") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing must prop <@> [.'$openapi#model#Elem'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $openapi#model#Elem (.'$openapi#model#Elem')
static bool json_model_75(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#model#Elem'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#model#Elem'.'|']", path);
    }
    if (res)
    {
        // .'$openapi#model#Elem'.'|'.0
        res = _jm_obj_63(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$openapi#model#Elem'.'|'.1
            res = _jm_obj_62(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$openapi#model#Elem'.'|'.2
                res = _jm_obj_61(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$openapi#model#Elem'.'|'.3
                    res = _jm_obj_60(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$openapi#model#Elem'.'|'.4
                        res = _jm_obj_59(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // .'$openapi#model#Elem'.'|'.5
                            res = _jm_obj_58(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object at [.'$openapi#model#Elem'.'|'.5]", path);
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#model#Elem'.'|']", path);
        }
    }
    return res;
}

// check $openapi#model#Val (.'$openapi#model#Val')
static bool json_model_64(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#model#Val'
    // .'$openapi#model#Val'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [.'$openapi#model#Val'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$openapi#model#Val'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$openapi#model#Val'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$openapi#model#Val'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$openapi#model#Val'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$openapi#model#Val'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$openapi#model#Val'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$openapi#model#Val'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Val'.'|'.4]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#model#Val'.'|']", path);
    }
    return res;
}

static bool _jm_cst_4_test(const json_t *val)
{
  constant_t cst;
  jm_set_cst(&cst, val);
  return jm_search_cst(&cst, _jm_cst_4, 8);
}

// check $openapi#model#Scalar (.'$openapi#model#Scalar')
static bool json_model_77(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // .'$openapi#model#Scalar'
    res = _json_is_scalar(val) && _jm_cst_4_test(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$openapi#model#Scalar'.'|']", path);
    }
    if (! res)
    {
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected type at [.'$openapi#model#Scalar'.'|']", path);
        }
        if (res)
        {
            // .'$openapi#model#Scalar'.'|'.0
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$openapi#model#Scalar'.'|'.0]", path);
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$openapi#model#Scalar'.'|']", path);
            }
        }
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
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^3\\.1\\.\\d+(-.+)?$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_obj_0_map_tab[0] = (propmap_t) { "component", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (propmap_t) { "externalDocs", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (propmap_t) { "jsonSchemaDialect", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (propmap_t) { "paths", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (propmap_t) { "security", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (propmap_t) { "servers", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (propmap_t) { "tags", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (propmap_t) { "webhooks", _jm_f_7 };
        jm_sort_propmap(_jm_obj_0_map_tab, 8);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "^x\\-.*$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
        _jm_obj_2_map_tab[0] = (propmap_t) { "contact", _jm_f_8 };
        _jm_obj_2_map_tab[1] = (propmap_t) { "description", _jm_f_9 };
        _jm_obj_2_map_tab[2] = (propmap_t) { "license", _jm_f_10 };
        _jm_obj_2_map_tab[3] = (propmap_t) { "summary", _jm_f_11 };
        _jm_obj_2_map_tab[4] = (propmap_t) { "termsOfService", _jm_f_12 };
        jm_sort_propmap(_jm_obj_2_map_tab, 5);
        _jm_obj_9_map_tab[0] = (propmap_t) { "callbacks", _jm_f_13 };
        _jm_obj_9_map_tab[1] = (propmap_t) { "examples", _jm_f_14 };
        _jm_obj_9_map_tab[2] = (propmap_t) { "headers", _jm_f_15 };
        _jm_obj_9_map_tab[3] = (propmap_t) { "links", _jm_f_16 };
        _jm_obj_9_map_tab[4] = (propmap_t) { "models", _jm_f_17 };
        _jm_obj_9_map_tab[5] = (propmap_t) { "parameters", _jm_f_18 };
        _jm_obj_9_map_tab[6] = (propmap_t) { "pathItems", _jm_f_19 };
        _jm_obj_9_map_tab[7] = (propmap_t) { "requestBodies", _jm_f_20 };
        _jm_obj_9_map_tab[8] = (propmap_t) { "responses", _jm_f_21 };
        _jm_obj_9_map_tab[9] = (propmap_t) { "securitySchemes", _jm_f_22 };
        jm_sort_propmap(_jm_obj_9_map_tab, 10);
        _jm_re_2_code = pcre2_compile((PCRE2_SPTR) "^/", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_2_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_2_data = pcre2_match_data_create_from_pattern(_jm_re_2_code, NULL);
        _jm_obj_21_map_tab[0] = (propmap_t) { "$ref", _jm_f_23 };
        _jm_obj_21_map_tab[1] = (propmap_t) { "delete", _jm_f_24 };
        _jm_obj_21_map_tab[2] = (propmap_t) { "description", _jm_f_25 };
        _jm_obj_21_map_tab[3] = (propmap_t) { "get", _jm_f_26 };
        _jm_obj_21_map_tab[4] = (propmap_t) { "head", _jm_f_27 };
        _jm_obj_21_map_tab[5] = (propmap_t) { "options", _jm_f_28 };
        _jm_obj_21_map_tab[6] = (propmap_t) { "parameters", _jm_f_29 };
        _jm_obj_21_map_tab[7] = (propmap_t) { "patch", _jm_f_30 };
        _jm_obj_21_map_tab[8] = (propmap_t) { "post", _jm_f_31 };
        _jm_obj_21_map_tab[9] = (propmap_t) { "put", _jm_f_32 };
        _jm_obj_21_map_tab[10] = (propmap_t) { "servers", _jm_f_33 };
        _jm_obj_21_map_tab[11] = (propmap_t) { "summary", _jm_f_34 };
        _jm_obj_21_map_tab[12] = (propmap_t) { "trace", _jm_f_35 };
        jm_sort_propmap(_jm_obj_21_map_tab, 13);
        _jm_obj_22_map_tab[0] = (propmap_t) { "callbacks", _jm_f_36 };
        _jm_obj_22_map_tab[1] = (propmap_t) { "deprecated", _jm_f_37 };
        _jm_obj_22_map_tab[2] = (propmap_t) { "description", _jm_f_38 };
        _jm_obj_22_map_tab[3] = (propmap_t) { "externalDocs", _jm_f_39 };
        _jm_obj_22_map_tab[4] = (propmap_t) { "operationId", _jm_f_40 };
        _jm_obj_22_map_tab[5] = (propmap_t) { "parameters", _jm_f_41 };
        _jm_obj_22_map_tab[6] = (propmap_t) { "requestBody", _jm_f_42 };
        _jm_obj_22_map_tab[7] = (propmap_t) { "responses", _jm_f_43 };
        _jm_obj_22_map_tab[8] = (propmap_t) { "security", _jm_f_44 };
        _jm_obj_22_map_tab[9] = (propmap_t) { "servers", _jm_f_45 };
        _jm_obj_22_map_tab[10] = (propmap_t) { "summary", _jm_f_46 };
        _jm_obj_22_map_tab[11] = (propmap_t) { "tags", _jm_f_47 };
        jm_sort_propmap(_jm_obj_22_map_tab, 12);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_0, 4);
        _jm_obj_25_map_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_48 };
        _jm_obj_25_map_tab[1] = (propmap_t) { "content", _jm_f_49 };
        _jm_obj_25_map_tab[2] = (propmap_t) { "deprecated", _jm_f_50 };
        _jm_obj_25_map_tab[3] = (propmap_t) { "description", _jm_f_51 };
        _jm_obj_25_map_tab[4] = (propmap_t) { "required", _jm_f_52 };
        jm_sort_propmap(_jm_obj_25_map_tab, 5);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_1[1] = (constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_1[2] = (constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_1[3] = (constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_1, 4);
        _jm_obj_27_map_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_53 };
        _jm_obj_27_map_tab[1] = (propmap_t) { "allowReserved", _jm_f_54 };
        _jm_obj_27_map_tab[2] = (propmap_t) { "deprecated", _jm_f_55 };
        _jm_obj_27_map_tab[3] = (propmap_t) { "description", _jm_f_56 };
        _jm_obj_27_map_tab[4] = (propmap_t) { "example", _jm_f_57 };
        _jm_obj_27_map_tab[5] = (propmap_t) { "examples", _jm_f_58 };
        _jm_obj_27_map_tab[6] = (propmap_t) { "explode", _jm_f_59 };
        _jm_obj_27_map_tab[7] = (propmap_t) { "model", _jm_f_60 };
        _jm_obj_27_map_tab[8] = (propmap_t) { "required", _jm_f_61 };
        _jm_obj_27_map_tab[9] = (propmap_t) { "style", _jm_f_62 };
        jm_sort_propmap(_jm_obj_27_map_tab, 10);
        // initialize sorted set _jm_cst_2
        _jm_cst_2[0] = (constant_t) { cst_is_string, { .s = "matrix" } };
        _jm_cst_2[1] = (constant_t) { cst_is_string, { .s = "label" } };
        _jm_cst_2[2] = (constant_t) { cst_is_string, { .s = "form" } };
        _jm_cst_2[3] = (constant_t) { cst_is_string, { .s = "simple" } };
        _jm_cst_2[4] = (constant_t) { cst_is_string, { .s = "spaceDelimited" } };
        _jm_cst_2[5] = (constant_t) { cst_is_string, { .s = "pipeDelimited" } };
        _jm_cst_2[6] = (constant_t) { cst_is_string, { .s = "deepObject" } };
        jm_sort_cst(_jm_cst_2, 7);
        _jm_obj_31_map_tab[0] = (propmap_t) { "encoding", _jm_f_63 };
        _jm_obj_31_map_tab[1] = (propmap_t) { "example", _jm_f_64 };
        _jm_obj_31_map_tab[2] = (propmap_t) { "examples", _jm_f_65 };
        _jm_obj_31_map_tab[3] = (propmap_t) { "model", _jm_f_66 };
        jm_sort_propmap(_jm_obj_31_map_tab, 4);
        _jm_obj_34_map_tab[0] = (propmap_t) { "allowReserved", _jm_f_67 };
        _jm_obj_34_map_tab[1] = (propmap_t) { "contentType", _jm_f_68 };
        _jm_obj_34_map_tab[2] = (propmap_t) { "explode", _jm_f_69 };
        _jm_obj_34_map_tab[3] = (propmap_t) { "headers", _jm_f_70 };
        _jm_obj_34_map_tab[4] = (propmap_t) { "style", _jm_f_71 };
        jm_sort_propmap(_jm_obj_34_map_tab, 5);
        _jm_re_3_code = pcre2_compile((PCRE2_SPTR) "^[1-5](\\d\\d|XX)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_3_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_3_data = pcre2_match_data_create_from_pattern(_jm_re_3_code, NULL);
        _jm_obj_37_map_tab[0] = (propmap_t) { "content", _jm_f_72 };
        _jm_obj_37_map_tab[1] = (propmap_t) { "description", _jm_f_73 };
        _jm_obj_37_map_tab[2] = (propmap_t) { "headers", _jm_f_74 };
        _jm_obj_37_map_tab[3] = (propmap_t) { "links", _jm_f_75 };
        jm_sort_propmap(_jm_obj_37_map_tab, 4);
        _jm_obj_42_map_tab[0] = (propmap_t) { "description", _jm_f_76 };
        _jm_obj_42_map_tab[1] = (propmap_t) { "externalValue", _jm_f_77 };
        _jm_obj_42_map_tab[2] = (propmap_t) { "summary", _jm_f_78 };
        _jm_obj_42_map_tab[3] = (propmap_t) { "value", _jm_f_79 };
        jm_sort_propmap(_jm_obj_42_map_tab, 4);
        _jm_obj_43_map_tab[0] = (propmap_t) { "description", _jm_f_80 };
        _jm_obj_43_map_tab[1] = (propmap_t) { "parameters", _jm_f_81 };
        _jm_obj_43_map_tab[2] = (propmap_t) { "requestBody", _jm_f_82 };
        _jm_obj_43_map_tab[3] = (propmap_t) { "server", _jm_f_83 };
        jm_sort_propmap(_jm_obj_43_map_tab, 4);
        _jm_obj_45_map_tab[0] = (propmap_t) { "description", _jm_f_84 };
        _jm_obj_45_map_tab[1] = (propmap_t) { "parameters", _jm_f_85 };
        _jm_obj_45_map_tab[2] = (propmap_t) { "requestBody", _jm_f_86 };
        _jm_obj_45_map_tab[3] = (propmap_t) { "server", _jm_f_87 };
        jm_sort_propmap(_jm_obj_45_map_tab, 4);
        _jm_obj_47_map_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_88 };
        _jm_obj_47_map_tab[1] = (propmap_t) { "content", _jm_f_89 };
        _jm_obj_47_map_tab[2] = (propmap_t) { "deprecated", _jm_f_90 };
        _jm_obj_47_map_tab[3] = (propmap_t) { "description", _jm_f_91 };
        _jm_obj_47_map_tab[4] = (propmap_t) { "required", _jm_f_92 };
        jm_sort_propmap(_jm_obj_47_map_tab, 5);
        _jm_obj_49_map_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_93 };
        _jm_obj_49_map_tab[1] = (propmap_t) { "allowReserved", _jm_f_94 };
        _jm_obj_49_map_tab[2] = (propmap_t) { "deprecated", _jm_f_95 };
        _jm_obj_49_map_tab[3] = (propmap_t) { "description", _jm_f_96 };
        _jm_obj_49_map_tab[4] = (propmap_t) { "example", _jm_f_97 };
        _jm_obj_49_map_tab[5] = (propmap_t) { "examples", _jm_f_98 };
        _jm_obj_49_map_tab[6] = (propmap_t) { "explode", _jm_f_99 };
        _jm_obj_49_map_tab[7] = (propmap_t) { "model", _jm_f_100 };
        _jm_obj_49_map_tab[8] = (propmap_t) { "required", _jm_f_101 };
        _jm_obj_49_map_tab[9] = (propmap_t) { "style", _jm_f_102 };
        jm_sort_propmap(_jm_obj_49_map_tab, 10);
        // initialize sorted set _jm_cst_3
        _jm_cst_3[0] = (constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_3[1] = (constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_3[2] = (constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_3, 3);
        _jm_obj_53_mup_tab[0] = (propmap_t) { "flows", _jm_f_103 };
        _jm_obj_53_mup_tab[1] = (propmap_t) { "in", _jm_f_104 };
        _jm_obj_53_mup_tab[2] = (propmap_t) { "name", _jm_f_105 };
        _jm_obj_53_mup_tab[3] = (propmap_t) { "openIdConnectUrl", _jm_f_106 };
        _jm_obj_53_mup_tab[4] = (propmap_t) { "scheme", _jm_f_107 };
        _jm_obj_53_mup_tab[5] = (propmap_t) { "type", _jm_f_108 };
        jm_sort_propmap(_jm_obj_53_mup_tab, 6);
        _jm_obj_54_map_tab[0] = (propmap_t) { "authorizationCode", _jm_f_109 };
        _jm_obj_54_map_tab[1] = (propmap_t) { "clientCredentials", _jm_f_110 };
        _jm_obj_54_map_tab[2] = (propmap_t) { "implicit", _jm_f_111 };
        _jm_obj_54_map_tab[3] = (propmap_t) { "password", _jm_f_112 };
        jm_sort_propmap(_jm_obj_54_map_tab, 4);
        _jm_re_4_code = pcre2_compile((PCRE2_SPTR) "^[@|&^+/*]$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_4_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_4_data = pcre2_match_data_create_from_pattern(_jm_re_4_code, NULL);
        _jm_re_5_code = pcre2_compile((PCRE2_SPTR) "^(<=|>=|<|>|≥|≤)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_5_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_5_data = pcre2_match_data_create_from_pattern(_jm_re_5_code, NULL);
        _jm_re_6_code = pcre2_compile((PCRE2_SPTR) "^(=|!=|≠)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_6_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_6_data = pcre2_match_data_create_from_pattern(_jm_re_6_code, NULL);
        // initialize sorted set _jm_cst_4
        _jm_cst_4[0] = (constant_t) { cst_is_null, { .s = NULL } };
        _jm_cst_4[1] = (constant_t) { cst_is_bool, { .b = true } };
        _jm_cst_4[2] = (constant_t) { cst_is_integer, { .i = 0 } };
        _jm_cst_4[3] = (constant_t) { cst_is_integer, { .i = 1 } };
        _jm_cst_4[4] = (constant_t) { cst_is_integer, { .i = -1 } };
        _jm_cst_4[5] = (constant_t) { cst_is_float, { .f = 0.0 } };
        _jm_cst_4[6] = (constant_t) { cst_is_float, { .f = 1.0 } };
        _jm_cst_4[7] = (constant_t) { cst_is_float, { .f = -1.0 } };
        jm_sort_cst(_jm_cst_4, 8);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "openapi", json_model_3 };
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
