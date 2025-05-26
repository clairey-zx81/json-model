#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_must_tab[2];
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_0_may_tab[8];
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_must_tab[2];
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_2_may_tab[5];
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_3_may_tab[3];
static bool json_model_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_must_tab[2];
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_5_must_tab[2];
static bool json_model_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_25(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_6_may_tab[2];
static bool json_model_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_27(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_8_may_tab[2];
static bool json_model_9(const json_t* val, Path* path, Report* rep);
static bool _jm_f_28(const json_t* val, Path* path, Report* rep);
static bool _jm_f_29(const json_t* val, Path* path, Report* rep);
static bool _jm_f_30(const json_t* val, Path* path, Report* rep);
static bool _jm_f_31(const json_t* val, Path* path, Report* rep);
static bool _jm_f_32(const json_t* val, Path* path, Report* rep);
static bool _jm_f_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_34(const json_t* val, Path* path, Report* rep);
static bool _jm_f_35(const json_t* val, Path* path, Report* rep);
static bool _jm_f_36(const json_t* val, Path* path, Report* rep);
static bool _jm_f_37(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_9_may_tab[10];
static bool json_model_10(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool json_model_11(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_48(const json_t* val, Path* path, Report* rep);
static bool _jm_f_49(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_21_may_tab[12];
static bool json_model_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_50(const json_t* val, Path* path, Report* rep);
static bool _jm_f_51(const json_t* val, Path* path, Report* rep);
static bool _jm_f_52(const json_t* val, Path* path, Report* rep);
static bool _jm_f_53(const json_t* val, Path* path, Report* rep);
static bool _jm_f_54(const json_t* val, Path* path, Report* rep);
static bool _jm_f_55(const json_t* val, Path* path, Report* rep);
static bool _jm_f_56(const json_t* val, Path* path, Report* rep);
static bool _jm_f_57(const json_t* val, Path* path, Report* rep);
static bool _jm_f_58(const json_t* val, Path* path, Report* rep);
static bool _jm_f_59(const json_t* val, Path* path, Report* rep);
static bool _jm_f_60(const json_t* val, Path* path, Report* rep);
static bool _jm_f_61(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_23_may_tab[12];
static bool json_model_13(const json_t* val, Path* path, Report* rep);
static bool json_model_14(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[4];
static bool _jm_f_62(const json_t* val, Path* path, Report* rep);
static bool _jm_f_63(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_28_must_tab[2];
static bool _jm_f_64(const json_t* val, Path* path, Report* rep);
static bool _jm_f_65(const json_t* val, Path* path, Report* rep);
static bool _jm_f_66(const json_t* val, Path* path, Report* rep);
static bool _jm_f_67(const json_t* val, Path* path, Report* rep);
static bool _jm_f_68(const json_t* val, Path* path, Report* rep);
static bool _jm_f_69(const json_t* val, Path* path, Report* rep);
static bool _jm_f_70(const json_t* val, Path* path, Report* rep);
static bool _jm_f_71(const json_t* val, Path* path, Report* rep);
static bool _jm_f_72(const json_t* val, Path* path, Report* rep);
static bool _jm_f_73(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_1[7];
static bool _jm_f_74(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_28_may_tab[11];
static bool json_model_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_75(const json_t* val, Path* path, Report* rep);
static bool _jm_f_76(const json_t* val, Path* path, Report* rep);
static bool _jm_f_77(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_31_may_tab[3];
static bool json_model_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_78(const json_t* val, Path* path, Report* rep);
static bool _jm_f_79(const json_t* val, Path* path, Report* rep);
static bool _jm_f_80(const json_t* val, Path* path, Report* rep);
static bool _jm_f_81(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_33_may_tab[4];
static bool json_model_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_82(const json_t* val, Path* path, Report* rep);
static bool _jm_f_83(const json_t* val, Path* path, Report* rep);
static bool _jm_f_84(const json_t* val, Path* path, Report* rep);
static bool _jm_f_85(const json_t* val, Path* path, Report* rep);
static bool _jm_f_86(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_36_may_tab[5];
static bool json_model_19(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_2_code = NULL;
static pcre2_match_data *_jm_re_2_data = NULL;
static bool _jm_re_2(const char *s);
static bool json_model_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_87(const json_t* val, Path* path, Report* rep);
static bool _jm_f_88(const json_t* val, Path* path, Report* rep);
static bool _jm_f_89(const json_t* val, Path* path, Report* rep);
static bool _jm_f_90(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_39_may_tab[4];
static bool json_model_21(const json_t* val, Path* path, Report* rep);
static bool json_model_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_91(const json_t* val, Path* path, Report* rep);
static bool _jm_f_92(const json_t* val, Path* path, Report* rep);
static bool _jm_f_93(const json_t* val, Path* path, Report* rep);
static bool _jm_f_94(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_44_may_tab[4];
static bool json_model_23(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_3_code = NULL;
static pcre2_match_data *_jm_re_3_data = NULL;
static bool _jm_re_3(const char *s);
static bool json_model_24(const json_t* val, Path* path, Report* rep);
static bool _jm_f_95(const json_t* val, Path* path, Report* rep);
static bool _jm_f_96(const json_t* val, Path* path, Report* rep);
static bool _jm_f_97(const json_t* val, Path* path, Report* rep);
static bool _jm_f_98(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_45_may_tab[4];
static bool _jm_f_99(const json_t* val, Path* path, Report* rep);
static bool _jm_f_100(const json_t* val, Path* path, Report* rep);
static bool _jm_f_101(const json_t* val, Path* path, Report* rep);
static bool _jm_f_102(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_47_may_tab[4];
static bool json_model_25(const json_t* val, Path* path, Report* rep);
static bool json_model_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_103(const json_t* val, Path* path, Report* rep);
static bool _jm_f_104(const json_t* val, Path* path, Report* rep);
static bool _jm_f_105(const json_t* val, Path* path, Report* rep);
static bool _jm_f_106(const json_t* val, Path* path, Report* rep);
static bool _jm_f_107(const json_t* val, Path* path, Report* rep);
static bool _jm_f_108(const json_t* val, Path* path, Report* rep);
static bool _jm_f_109(const json_t* val, Path* path, Report* rep);
static bool _jm_f_110(const json_t* val, Path* path, Report* rep);
static bool _jm_f_111(const json_t* val, Path* path, Report* rep);
static bool _jm_f_112(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_2[7];
static bool _jm_f_113(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_49_may_tab[11];
static bool json_model_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_114(const json_t* val, Path* path, Report* rep);
static bool _jm_f_115(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_52_may_tab[2];
static bool json_model_27(const json_t* val, Path* path, Report* rep);
static bool _jm_f_116(const json_t* val, Path* path, Report* rep);
static bool _jm_f_117(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_53_may_tab[2];
static bool json_model_28(const json_t* val, Path* path, Report* rep);
static bool _jm_f_118(const json_t* val, Path* path, Report* rep);
static bool _jm_f_119(const json_t* val, Path* path, Report* rep);
static bool _jm_f_120(const json_t* val, Path* path, Report* rep);
static bool _jm_f_121(const json_t* val, Path* path, Report* rep);
static bool _jm_f_122(const json_t* val, Path* path, Report* rep);
static bool _jm_f_123(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_54_must_tab[6];
static bool _jm_f_124(const json_t* val, Path* path, Report* rep);
static bool _jm_f_125(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_54_may_tab[2];
static bool json_model_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_126(const json_t* val, Path* path, Report* rep);
static bool _jm_f_127(const json_t* val, Path* path, Report* rep);
static bool _jm_f_128(const json_t* val, Path* path, Report* rep);
static bool _jm_f_129(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_55_may_tab[4];
static bool json_model_34(const json_t* val, Path* path, Report* rep);
static bool _jm_f_130(const json_t* val, Path* path, Report* rep);
static bool _jm_f_131(const json_t* val, Path* path, Report* rep);
static bool _jm_f_132(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_56_must_tab[3];
static bool json_model_35(const json_t* val, Path* path, Report* rep);
static bool json_model_36(const json_t* val, Path* path, Report* rep);
static bool json_model_56(const json_t* val, Path* path, Report* rep);
static bool json_model_73(const json_t* val, Path* path, Report* rep);
static bool json_model_63(const json_t* val, Path* path, Report* rep);
static pcre2_code *_jm_re_4_code = NULL;
static pcre2_match_data *_jm_re_4_data = NULL;
static bool _jm_re_4(const char *s);
static bool _jm_f_133(const json_t* val, Path* path, Report* rep);
static bool _jm_f_134(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_64_may_tab[2];
static pcre2_code *_jm_re_5_code = NULL;
static pcre2_match_data *_jm_re_5_data = NULL;
static bool _jm_re_5(const char *s);
static pcre2_code *_jm_re_6_code = NULL;
static pcre2_match_data *_jm_re_6_data = NULL;
static bool _jm_re_6(const char *s);
static bool json_model_70(const json_t* val, Path* path, Report* rep);
static bool json_model_59(const json_t* val, Path* path, Report* rep);
static bool _jm_cst_3_test(const json_t *);
static constant_t _jm_cst_3[8];
static bool json_model_72(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $openapi ($.'$openapi')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi'
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OpenAPI [$.'$openapi']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $openapi [$]", path);
    }
    return res;
}

// check _jm_obj_0_must_info ($.'$openapi#OpenAPI'.info)
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.info
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Info [$.'$openapi#OpenAPI'.info]", path);
    }
    return res;
}

// check _jm_obj_0_must_openapi ($.'$openapi#OpenAPI'.openapi)
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.openapi
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OpenAPI'.openapi]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_must_tab, 2);
}

// check _jm_obj_0_may_component ($.'$openapi#OpenAPI'.component)
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.component
    res = json_model_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Components [$.'$openapi#OpenAPI'.component]", path);
    }
    return res;
}

// check _jm_obj_0_may_externalDocs ($.'$openapi#OpenAPI'.externalDocs)
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.externalDocs
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [$.'$openapi#OpenAPI'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_0_may_jsonSchemaDialect ($.'$openapi#OpenAPI'.jsonSchemaDialect)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.jsonSchemaDialect
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OpenAPI'.jsonSchemaDialect]", path);
    }
    return res;
}

// check _jm_obj_0_may_paths ($.'$openapi#OpenAPI'.paths)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.paths
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Paths [$.'$openapi#OpenAPI'.paths]", path);
    }
    return res;
}

// check _jm_obj_0_may_security ($.'$openapi#OpenAPI'.security)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.security
    res = json_model_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [$.'$openapi#OpenAPI'.security]", path);
    }
    return res;
}

// check _jm_obj_0_may_servers ($.'$openapi#OpenAPI'.servers)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$openapi#OpenAPI'.servers.0
            res = json_model_8(arr_0_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [$.'$openapi#OpenAPI'.servers.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#OpenAPI'.servers]", path);
    }
    return res;
}

// check _jm_obj_0_may_tags ($.'$openapi#OpenAPI'.tags)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // $.'$openapi#OpenAPI'.tags.0
            res = json_model_27(arr_1_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Tag [$.'$openapi#OpenAPI'.tags.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#OpenAPI'.tags]", path);
    }
    return res;
}

// object $.'$openapi#OpenAPI'.webhooks
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#OpenAPI'.webhooks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#OpenAPI'.webhooks.''
        // $.'$openapi#OpenAPI'.webhooks.''.'|'.0
        res = json_model_12(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [$.'$openapi#OpenAPI'.webhooks.''.'|'.0]", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#OpenAPI'.webhooks.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#OpenAPI'.webhooks.''.'|'.1]", (path ? &lpath_1 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#OpenAPI'.webhooks.''.'|']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_may_webhooks ($.'$openapi#OpenAPI'.webhooks)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'.webhooks
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#OpenAPI'.webhooks]", path);
    }
    return res;
}

static check_fun_t _jm_obj_0_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_may_tab, 8);
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// object $.'$openapi#OpenAPI'
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#OpenAPI']", path);
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
        if ((pfun = _jm_obj_0_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_0 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#OpenAPI']", (path ? &lpath_0 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_0_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#OpenAPI']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#OpenAPI'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#OpenAPI'.'/^x\\\\-.*$/']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#OpenAPI']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#OpenAPI']", path);
        return false;
    }
    return true;
}

// check $openapi#OpenAPI ($.'$openapi#OpenAPI')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OpenAPI'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#OpenAPI']", path);
    }
    return res;
}

// check _jm_obj_2_must_title ($.'$openapi#Info'.title)
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Info'.title]", path);
    }
    return res;
}

// check _jm_obj_2_must_version ($.'$openapi#Info'.version)
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.version
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Info'.version]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_must_tab, 2);
}

// check _jm_obj_2_may_contact ($.'$openapi#Info'.contact)
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.contact
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Contact [$.'$openapi#Info'.contact]", path);
    }
    return res;
}

// check _jm_obj_2_may_description ($.'$openapi#Info'.description)
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Info'.description]", path);
    }
    return res;
}

// check _jm_obj_2_may_license ($.'$openapi#Info'.license)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.license
    res = json_model_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $License [$.'$openapi#Info'.license]", path);
    }
    return res;
}

// check _jm_obj_2_may_summary ($.'$openapi#Info'.summary)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Info'.summary]", path);
    }
    return res;
}

// check _jm_obj_2_may_termsOfService ($.'$openapi#Info'.termsOfService)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'.termsOfService
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Info'.termsOfService]", path);
    }
    return res;
}

static check_fun_t _jm_obj_2_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_may_tab, 5);
}

// object $.'$openapi#Info'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Info']", path);
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
        if ((pfun = _jm_obj_2_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_2 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Info']", (path ? &lpath_2 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_2_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Info']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Info'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Info'.'/^x\\\\-.*$/']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Info']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Info']", path);
        return false;
    }
    return true;
}

// check $openapi#Info ($.'$openapi#Info')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Info'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Info']", path);
    }
    return res;
}

// check _jm_obj_3_may_email ($.'$openapi#Contact'.email)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Contact'.email
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Contact'.email]", path);
    }
    return res;
}

// check _jm_obj_3_may_name ($.'$openapi#Contact'.name)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Contact'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Contact'.name]", path);
    }
    return res;
}

// check _jm_obj_3_may_url ($.'$openapi#Contact'.url)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Contact'.url
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$openapi#Contact'.url]", path);
    }
    return res;
}

static check_fun_t _jm_obj_3_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_may_tab, 3);
}

// object $.'$openapi#Contact'
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Contact']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_3_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_3 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Contact']", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Contact'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Contact'.'/^x\\\\-.*$/']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Contact']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Contact ($.'$openapi#Contact')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Contact'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Contact']", path);
    }
    return res;
}

// check _jm_obj_4_must_name ($.'$openapi#License'.'|'.1.name)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#License'.'|'.1.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#License'.'|'.1.name]", path);
    }
    return res;
}

// check _jm_obj_4_must_url ($.'$openapi#License'.'|'.1.url)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#License'.'|'.1.url
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$openapi#License'.'|'.1.url]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_must_tab, 2);
}

// object $.'$openapi#License'.'|'.1
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#License'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_4 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_4_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_4 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#License'.'|'.1]", (path ? &lpath_4 : NULL));
                    return false;
                }
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#License'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#License'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#License'.'|'.1]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#License'.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_5_must_identifier ($.'$openapi#License'.'|'.0.identifier)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#License'.'|'.0.identifier
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#License'.'|'.0.identifier]", path);
    }
    return res;
}

// check _jm_obj_5_must_name ($.'$openapi#License'.'|'.0.name)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#License'.'|'.0.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#License'.'|'.0.name]", path);
    }
    return res;
}

static check_fun_t _jm_obj_5_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_5_must_tab, 2);
}

// object $.'$openapi#License'.'|'.0
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#License'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_5_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_5 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#License'.'|'.0]", (path ? &lpath_5 : NULL));
                    return false;
                }
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#License'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#License'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#License'.'|'.0]", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#License'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $openapi#License ($.'$openapi#License')
static bool json_model_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#License'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$openapi#License'.'|']", path);
    }
    if (res)
    {
        // $.'$openapi#License'.'|'.0
        res = _jm_obj_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#License'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$openapi#License'.'|'.1
            res = _jm_obj_4(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#License'.'|'.1]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#License'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_6_may_description ($.'$openapi#Server'.description)
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Server'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Server'.description]", path);
    }
    return res;
}

// object $.'$openapi#Server'.variables
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Server'.variables]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Server'.variables.''
        res = json_model_9(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ServerVariable [$.'$openapi#Server'.variables.'']", (path ? &lpath_7 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_6_may_variables ($.'$openapi#Server'.variables)
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Server'.variables
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Server'.variables]", path);
    }
    return res;
}

static check_fun_t _jm_obj_6_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_may_tab, 2);
}

// object $.'$openapi#Server'
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Server']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#Server'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$openapi#Server'.url]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Server'.url]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_6_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_6 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Server']", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Server'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Server'.'/^x\\\\-.*$/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Server']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Server']", path);
        return false;
    }
    return true;
}

// check $openapi#Server ($.'$openapi#Server')
static bool json_model_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Server'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Server']", path);
    }
    return res;
}

// check _jm_obj_8_may_description ($.'$openapi#ServerVariable'.description)
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#ServerVariable'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#ServerVariable'.description]", path);
    }
    return res;
}

// check _jm_obj_8_may_enum ($.'$openapi#ServerVariable'.enum)
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#ServerVariable'.enum
    res = json_is_array(val);
    if (res)
    {
        size_t arr_2_idx;
        json_t *arr_2_item;
        json_array_foreach(val, arr_2_idx, arr_2_item)
        {
            Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
            // $.'$openapi#ServerVariable'.enum.0
            res = json_is_string(arr_2_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#ServerVariable'.enum.0]", (path ? &arr_2_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#ServerVariable'.enum]", path);
    }
    return res;
}

static check_fun_t _jm_obj_8_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_8_may_tab, 2);
}

// object $.'$openapi#ServerVariable'
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#ServerVariable']", path);
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
        if (strcmp(prop, "default") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#ServerVariable'.default
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#ServerVariable'.default]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#ServerVariable'.default]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_8_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_8 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#ServerVariable']", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#ServerVariable'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#ServerVariable'.'/^x\\\\-.*$/']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#ServerVariable']", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#ServerVariable']", path);
        return false;
    }
    return true;
}

// check $openapi#ServerVariable ($.'$openapi#ServerVariable')
static bool json_model_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#ServerVariable'
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#ServerVariable']", path);
    }
    return res;
}

// object $.'$openapi#Components'.callbacks
static bool _jm_obj_10(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_10 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.callbacks.''
        // $.'$openapi#Components'.callbacks.''.'|'.0
        res = json_model_22(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [$.'$openapi#Components'.callbacks.''.'|'.0]", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.callbacks.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.callbacks.''.'|'.1]", (path ? &lpath_10 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.callbacks.''.'|']", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_callbacks ($.'$openapi#Components'.callbacks)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.callbacks
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.callbacks]", path);
    }
    return res;
}

// object $.'$openapi#Components'.examples
static bool _jm_obj_11(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_11 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.examples.''
        // $.'$openapi#Components'.examples.''.'|'.0
        res = json_model_23(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [$.'$openapi#Components'.examples.''.'|'.0]", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.examples.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.examples.''.'|'.1]", (path ? &lpath_11 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.examples.''.'|']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_examples ($.'$openapi#Components'.examples)
static bool _jm_f_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.examples
    res = _jm_obj_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.examples]", path);
    }
    return res;
}

// object $.'$openapi#Components'.headers
static bool _jm_obj_12(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_12 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.headers.''
        // $.'$openapi#Components'.headers.''.'|'.0
        res = json_model_26(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [$.'$openapi#Components'.headers.''.'|'.0]", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.headers.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.headers.''.'|'.1]", (path ? &lpath_12 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.headers.''.'|']", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_headers ($.'$openapi#Components'.headers)
static bool _jm_f_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.headers
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.headers]", path);
    }
    return res;
}

// object $.'$openapi#Components'.links
static bool _jm_obj_13(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_13 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.links.''
        // $.'$openapi#Components'.links.''.'|'.0
        res = json_model_25(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [$.'$openapi#Components'.links.''.'|'.0]", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.links.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.links.''.'|'.1]", (path ? &lpath_13 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.links.''.'|']", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_links ($.'$openapi#Components'.links)
static bool _jm_f_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.links
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.links]", path);
    }
    return res;
}

// object $.'$openapi#Components'.models
static bool _jm_obj_14(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.models]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_14 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.models.''
        res = json_model_56(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#Components'.models.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_models ($.'$openapi#Components'.models)
static bool _jm_f_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.models
    res = _jm_obj_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.models]", path);
    }
    return res;
}

// object $.'$openapi#Components'.parameters
static bool _jm_obj_15(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.parameters]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_15 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.parameters.''
        // $.'$openapi#Components'.parameters.''.'|'.0
        res = json_model_16(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Parameter [$.'$openapi#Components'.parameters.''.'|'.0]", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.parameters.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.parameters.''.'|'.1]", (path ? &lpath_15 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.parameters.''.'|']", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_parameters ($.'$openapi#Components'.parameters)
static bool _jm_f_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.parameters
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.parameters]", path);
    }
    return res;
}

// object $.'$openapi#Components'.pathItems
static bool _jm_obj_16(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.pathItems]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_16 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.pathItems.''
        // $.'$openapi#Components'.pathItems.''.'|'.0
        res = json_model_12(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [$.'$openapi#Components'.pathItems.''.'|'.0]", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.pathItems.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.pathItems.''.'|'.1]", (path ? &lpath_16 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.pathItems.''.'|']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_pathItems ($.'$openapi#Components'.pathItems)
static bool _jm_f_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.pathItems
    res = _jm_obj_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.pathItems]", path);
    }
    return res;
}

// object $.'$openapi#Components'.requestBodies
static bool _jm_obj_17(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.requestBodies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_17 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.requestBodies.''
        // $.'$openapi#Components'.requestBodies.''.'|'.0
        res = json_model_17(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [$.'$openapi#Components'.requestBodies.''.'|'.0]", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.requestBodies.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.requestBodies.''.'|'.1]", (path ? &lpath_17 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.requestBodies.''.'|']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_requestBodies ($.'$openapi#Components'.requestBodies)
static bool _jm_f_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.requestBodies
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.requestBodies]", path);
    }
    return res;
}

// object $.'$openapi#Components'.responses
static bool _jm_obj_18(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.responses]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_18 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.responses.''
        // $.'$openapi#Components'.responses.''.'|'.0
        res = json_model_21(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Response [$.'$openapi#Components'.responses.''.'|'.0]", (path ? &lpath_18 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.responses.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.responses.''.'|'.1]", (path ? &lpath_18 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.responses.''.'|']", (path ? &lpath_18 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_responses ($.'$openapi#Components'.responses)
static bool _jm_f_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.responses
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.responses]", path);
    }
    return res;
}

// object $.'$openapi#Components'.securitySchemes
static bool _jm_obj_19(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components'.securitySchemes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_19 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Components'.securitySchemes.''
        // $.'$openapi#Components'.securitySchemes.''.'|'.0
        res = json_model_33(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $SecurityScheme [$.'$openapi#Components'.securitySchemes.''.'|'.0]", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Components'.securitySchemes.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Components'.securitySchemes.''.'|'.1]", (path ? &lpath_19 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Components'.securitySchemes.''.'|']", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_may_securitySchemes ($.'$openapi#Components'.securitySchemes)
static bool _jm_f_37(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'.securitySchemes
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components'.securitySchemes]", path);
    }
    return res;
}

static check_fun_t _jm_obj_9_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_may_tab, 10);
}

// object $.'$openapi#Components'
static bool _jm_obj_9(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Components']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_9 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_9_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_9 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Components']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Components'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Components'.'/^x\\\\-.*$/']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Components']", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Components ($.'$openapi#Components')
static bool json_model_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Components'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Components']", path);
    }
    return res;
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

// object $.'$openapi#Paths'
static bool _jm_obj_20(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Paths']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_20 = (Path) { prop, 0, path, NULL };
        if (_jm_re_1(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Paths'.'/^//'
            res = json_model_12(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [$.'$openapi#Paths'.'/^//']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Paths'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Paths'.'/^x\\\\-.*$/']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Paths']", (path ? &lpath_20 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Paths ($.'$openapi#Paths')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Paths'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Paths']", path);
    }
    return res;
}

// check _jm_obj_21_may_$ref ($.'$openapi#PathItem'.'$ref')
static bool _jm_f_38(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.'$ref'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#PathItem'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_21_may_description ($.'$openapi#PathItem'.description)
static bool _jm_f_39(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#PathItem'.description]", path);
    }
    return res;
}

// check _jm_obj_21_may_get ($.'$openapi#PathItem'.get)
static bool _jm_f_40(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.get
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.get]", path);
    }
    return res;
}

// check _jm_obj_21_may_head ($.'$openapi#PathItem'.head)
static bool _jm_f_41(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.head
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.head]", path);
    }
    return res;
}

// check _jm_obj_21_may_options ($.'$openapi#PathItem'.options)
static bool _jm_f_42(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.options
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.options]", path);
    }
    return res;
}

// object $.'$openapi#PathItem'.parameters
static bool _jm_obj_22(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#PathItem'.parameters]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_22 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#PathItem'.parameters.''
        // $.'$openapi#PathItem'.parameters.''.'|'.0
        res = json_model_16(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Parameter [$.'$openapi#PathItem'.parameters.''.'|'.0]", (path ? &lpath_22 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#PathItem'.parameters.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#PathItem'.parameters.''.'|'.1]", (path ? &lpath_22 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#PathItem'.parameters.''.'|']", (path ? &lpath_22 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_21_may_parameters ($.'$openapi#PathItem'.parameters)
static bool _jm_f_43(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.parameters
    res = _jm_obj_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#PathItem'.parameters]", path);
    }
    return res;
}

// check _jm_obj_21_may_patch ($.'$openapi#PathItem'.patch)
static bool _jm_f_44(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.patch
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.patch]", path);
    }
    return res;
}

// check _jm_obj_21_may_post ($.'$openapi#PathItem'.post)
static bool _jm_f_45(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.post
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.post]", path);
    }
    return res;
}

// check _jm_obj_21_may_put ($.'$openapi#PathItem'.put)
static bool _jm_f_46(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.put
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.put]", path);
    }
    return res;
}

// check _jm_obj_21_may_servers ($.'$openapi#PathItem'.servers)
static bool _jm_f_47(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.servers
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.servers]", path);
    }
    return res;
}

// check _jm_obj_21_may_summary ($.'$openapi#PathItem'.summary)
static bool _jm_f_48(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#PathItem'.summary]", path);
    }
    return res;
}

// check _jm_obj_21_may_trace ($.'$openapi#PathItem'.trace)
static bool _jm_f_49(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'.trace
    res = json_model_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [$.'$openapi#PathItem'.trace]", path);
    }
    return res;
}

static check_fun_t _jm_obj_21_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_21_may_tab, 12);
}

// object $.'$openapi#PathItem'
static bool _jm_obj_21(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#PathItem']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_21 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_21_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_21 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#PathItem']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#PathItem'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#PathItem'.'/^x\\\\-.*$/']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#PathItem']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#PathItem ($.'$openapi#PathItem')
static bool json_model_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#PathItem'
    res = _jm_obj_21(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#PathItem']", path);
    }
    return res;
}

// object $.'$openapi#Operation'.callbacks
static bool _jm_obj_24(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Operation'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_24 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Operation'.callbacks.''
        // $.'$openapi#Operation'.callbacks.''.'|'.0
        res = json_model_22(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [$.'$openapi#Operation'.callbacks.''.'|'.0]", (path ? &lpath_24 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Operation'.callbacks.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Operation'.callbacks.''.'|'.1]", (path ? &lpath_24 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Operation'.callbacks.''.'|']", (path ? &lpath_24 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_may_callbacks ($.'$openapi#Operation'.callbacks)
static bool _jm_f_50(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.callbacks
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Operation'.callbacks]", path);
    }
    return res;
}

// check _jm_obj_23_may_deprecated ($.'$openapi#Operation'.deprecated)
static bool _jm_f_51(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Operation'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_23_may_description ($.'$openapi#Operation'.description)
static bool _jm_f_52(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Operation'.description]", path);
    }
    return res;
}

// check _jm_obj_23_may_externalDocs ($.'$openapi#Operation'.externalDocs)
static bool _jm_f_53(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.externalDocs
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [$.'$openapi#Operation'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_23_may_operationId ($.'$openapi#Operation'.operationId)
static bool _jm_f_54(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.operationId
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Operation'.operationId]", path);
    }
    return res;
}

// object $.'$openapi#Operation'.parameters
static bool _jm_obj_25(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Operation'.parameters]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_25 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Operation'.parameters.''
        // $.'$openapi#Operation'.parameters.''.'|'.0
        res = json_model_16(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Parameter [$.'$openapi#Operation'.parameters.''.'|'.0]", (path ? &lpath_25 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Operation'.parameters.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Operation'.parameters.''.'|'.1]", (path ? &lpath_25 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Operation'.parameters.''.'|']", (path ? &lpath_25 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_may_parameters ($.'$openapi#Operation'.parameters)
static bool _jm_f_55(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.parameters
    res = _jm_obj_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Operation'.parameters]", path);
    }
    return res;
}

// object $.'$openapi#Operation'.requestBody
static bool _jm_obj_26(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Operation'.requestBody]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_26 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Operation'.requestBody.''
        // $.'$openapi#Operation'.requestBody.''.'|'.0
        res = json_model_17(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [$.'$openapi#Operation'.requestBody.''.'|'.0]", (path ? &lpath_26 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Operation'.requestBody.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Operation'.requestBody.''.'|'.1]", (path ? &lpath_26 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Operation'.requestBody.''.'|']", (path ? &lpath_26 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_may_requestBody ($.'$openapi#Operation'.requestBody)
static bool _jm_f_56(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.requestBody
    res = _jm_obj_26(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Operation'.requestBody]", path);
    }
    return res;
}

// check _jm_obj_23_may_responses ($.'$openapi#Operation'.responses)
static bool _jm_f_57(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.responses
    res = json_model_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Responses [$.'$openapi#Operation'.responses]", path);
    }
    return res;
}

// check _jm_obj_23_may_security ($.'$openapi#Operation'.security)
static bool _jm_f_58(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.security
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
            // $.'$openapi#Operation'.security.0
            res = json_model_36(arr_3_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [$.'$openapi#Operation'.security.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#Operation'.security]", path);
    }
    return res;
}

// check _jm_obj_23_may_servers ($.'$openapi#Operation'.servers)
static bool _jm_f_59(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_4_idx;
        json_t *arr_4_item;
        json_array_foreach(val, arr_4_idx, arr_4_item)
        {
            Path arr_4_lpath = (Path) { NULL, arr_4_idx, path, NULL };
            // $.'$openapi#Operation'.servers.0
            res = json_model_8(arr_4_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [$.'$openapi#Operation'.servers.0]", (path ? &arr_4_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#Operation'.servers]", path);
    }
    return res;
}

// check _jm_obj_23_may_summary ($.'$openapi#Operation'.summary)
static bool _jm_f_60(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Operation'.summary]", path);
    }
    return res;
}

// check _jm_obj_23_may_tags ($.'$openapi#Operation'.tags)
static bool _jm_f_61(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_5_idx;
        json_t *arr_5_item;
        json_array_foreach(val, arr_5_idx, arr_5_item)
        {
            Path arr_5_lpath = (Path) { NULL, arr_5_idx, path, NULL };
            // $.'$openapi#Operation'.tags.0
            res = json_is_string(arr_5_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Operation'.tags.0]", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#Operation'.tags]", path);
    }
    return res;
}

static check_fun_t _jm_obj_23_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_23_may_tab, 12);
}

// object $.'$openapi#Operation'
static bool _jm_obj_23(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Operation']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_23 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_23_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_23 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Operation']", (path ? &lpath_23 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Operation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Operation'.'/^x\\\\-.*$/']", (path ? &lpath_23 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Operation']", (path ? &lpath_23 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Operation ($.'$openapi#Operation')
static bool json_model_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Operation'
    res = _jm_obj_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Operation']", path);
    }
    return res;
}

// object $.'$openapi#ExternalDocumentation'
static bool _jm_obj_27(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#ExternalDocumentation']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_27 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#ExternalDocumentation'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$openapi#ExternalDocumentation'.url]", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#ExternalDocumentation'.url]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle one may property
            // $.'$openapi#ExternalDocumentation'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#ExternalDocumentation'.description]", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#ExternalDocumentation'.description]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#ExternalDocumentation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#ExternalDocumentation'.'/^x\\\\-.*$/']", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#ExternalDocumentation']", (path ? &lpath_27 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#ExternalDocumentation']", path);
        return false;
    }
    return true;
}

// check $openapi#ExternalDocumentation ($.'$openapi#ExternalDocumentation')
static bool json_model_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#ExternalDocumentation'
    res = _jm_obj_27(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#ExternalDocumentation']", path);
    }
    return res;
}


// check _jm_obj_28_must_in ($.'$openapi#Parameter'.in)
static bool _jm_f_62(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.in
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 4);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$openapi#Parameter'.in.'|']", path);
    }
    return res;
}

// check _jm_obj_28_must_name ($.'$openapi#Parameter'.name)
static bool _jm_f_63(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Parameter'.name]", path);
    }
    return res;
}

static check_fun_t _jm_obj_28_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_28_must_tab, 2);
}

// check _jm_obj_28_may_allowEmptyValue ($.'$openapi#Parameter'.allowEmptyValue)
static bool _jm_f_64(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Parameter'.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_28_may_allowReserved ($.'$openapi#Parameter'.allowReserved)
static bool _jm_f_65(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Parameter'.allowReserved]", path);
    }
    return res;
}

// object $.'$openapi#Parameter'.content
static bool _jm_obj_29(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Parameter'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_29 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Parameter'.content.''
        res = json_model_18(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [$.'$openapi#Parameter'.content.'']", (path ? &lpath_29 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_28_may_content ($.'$openapi#Parameter'.content)
static bool _jm_f_66(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.content
    res = _jm_obj_29(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Parameter'.content]", path);
    }
    return res;
}

// check _jm_obj_28_may_deprecated ($.'$openapi#Parameter'.deprecated)
static bool _jm_f_67(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Parameter'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_28_may_description ($.'$openapi#Parameter'.description)
static bool _jm_f_68(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Parameter'.description]", path);
    }
    return res;
}

// check _jm_obj_28_may_example ($.'$openapi#Parameter'.example)
static bool _jm_f_69(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Parameter'.example]", path);
    }
    return res;
}

// object $.'$openapi#Parameter'.examples
static bool _jm_obj_30(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Parameter'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_30 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Parameter'.examples.''
        // $.'$openapi#Parameter'.examples.''.'|'.0
        res = json_model_23(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [$.'$openapi#Parameter'.examples.''.'|'.0]", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Parameter'.examples.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Parameter'.examples.''.'|'.1]", (path ? &lpath_30 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Parameter'.examples.''.'|']", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_28_may_examples ($.'$openapi#Parameter'.examples)
static bool _jm_f_70(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.examples
    res = _jm_obj_30(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Parameter'.examples]", path);
    }
    return res;
}

// check _jm_obj_28_may_explode ($.'$openapi#Parameter'.explode)
static bool _jm_f_71(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Parameter'.explode]", path);
    }
    return res;
}

// check _jm_obj_28_may_model ($.'$openapi#Parameter'.model)
static bool _jm_f_72(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.model
    res = json_model_56(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#Parameter'.model]", path);
    }
    return res;
}

// check _jm_obj_28_may_required ($.'$openapi#Parameter'.required)
static bool _jm_f_73(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Parameter'.required]", path);
    }
    return res;
}


// check _jm_obj_28_may_style ($.'$openapi#Parameter'.style)
static bool _jm_f_74(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'.style
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$openapi#Parameter'.style.'|']", path);
    }
    return res;
}

static check_fun_t _jm_obj_28_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_28_may_tab, 11);
}

// object $.'$openapi#Parameter'
static bool _jm_obj_28(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Parameter']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_28 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_28_must(prop)))
        {
            // handle 2 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_28 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Parameter']", (path ? &lpath_28 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_28_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_28 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Parameter']", (path ? &lpath_28 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Parameter'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Parameter'.'/^x\\\\-.*$/']", (path ? &lpath_28 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Parameter']", (path ? &lpath_28 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Parameter']", path);
        return false;
    }
    return true;
}

// check $openapi#Parameter ($.'$openapi#Parameter')
static bool json_model_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Parameter'
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Parameter']", path);
    }
    return res;
}

// object $.'$openapi#RequestBody'.content
static bool _jm_obj_32(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#RequestBody'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_32 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#RequestBody'.content.''
        res = json_model_18(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [$.'$openapi#RequestBody'.content.'']", (path ? &lpath_32 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_31_may_content ($.'$openapi#RequestBody'.content)
static bool _jm_f_75(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#RequestBody'.content
    res = _jm_obj_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#RequestBody'.content]", path);
    }
    return res;
}

// check _jm_obj_31_may_description ($.'$openapi#RequestBody'.description)
static bool _jm_f_76(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#RequestBody'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#RequestBody'.description]", path);
    }
    return res;
}

// check _jm_obj_31_may_required ($.'$openapi#RequestBody'.required)
static bool _jm_f_77(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#RequestBody'.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#RequestBody'.required]", path);
    }
    return res;
}

static check_fun_t _jm_obj_31_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_31_may_tab, 3);
}

// object $.'$openapi#RequestBody'
static bool _jm_obj_31(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#RequestBody']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_31 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_31_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_31 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#RequestBody']", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#RequestBody'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#RequestBody'.'/^x\\\\-.*$/']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#RequestBody']", (path ? &lpath_31 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#RequestBody ($.'$openapi#RequestBody')
static bool json_model_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#RequestBody'
    res = _jm_obj_31(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#RequestBody']", path);
    }
    return res;
}

// object $.'$openapi#MediaType'.encoding
static bool _jm_obj_34(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#MediaType'.encoding]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_34 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#MediaType'.encoding.''
        res = json_model_19(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Encoding [$.'$openapi#MediaType'.encoding.'']", (path ? &lpath_34 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_33_may_encoding ($.'$openapi#MediaType'.encoding)
static bool _jm_f_78(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#MediaType'.encoding
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#MediaType'.encoding]", path);
    }
    return res;
}

// check _jm_obj_33_may_example ($.'$openapi#MediaType'.example)
static bool _jm_f_79(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#MediaType'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#MediaType'.example]", path);
    }
    return res;
}

// object $.'$openapi#MediaType'.examples
static bool _jm_obj_35(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#MediaType'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_35 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#MediaType'.examples.''
        // $.'$openapi#MediaType'.examples.''.'|'.0
        res = json_model_23(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [$.'$openapi#MediaType'.examples.''.'|'.0]", (path ? &lpath_35 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#MediaType'.examples.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#MediaType'.examples.''.'|'.1]", (path ? &lpath_35 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#MediaType'.examples.''.'|']", (path ? &lpath_35 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_33_may_examples ($.'$openapi#MediaType'.examples)
static bool _jm_f_80(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#MediaType'.examples
    res = _jm_obj_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#MediaType'.examples]", path);
    }
    return res;
}

// check _jm_obj_33_may_model ($.'$openapi#MediaType'.model)
static bool _jm_f_81(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#MediaType'.model
    res = json_model_56(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#MediaType'.model]", path);
    }
    return res;
}

static check_fun_t _jm_obj_33_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_33_may_tab, 4);
}

// object $.'$openapi#MediaType'
static bool _jm_obj_33(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#MediaType']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_33 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_33_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_33 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#MediaType']", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#MediaType'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#MediaType'.'/^x\\\\-.*$/']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#MediaType']", (path ? &lpath_33 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#MediaType ($.'$openapi#MediaType')
static bool json_model_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#MediaType'
    res = _jm_obj_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#MediaType']", path);
    }
    return res;
}

// check _jm_obj_36_may_allowReserved ($.'$openapi#Encoding'.allowReserved)
static bool _jm_f_82(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Encoding'.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_36_may_contentType ($.'$openapi#Encoding'.contentType)
static bool _jm_f_83(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'.contentType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Encoding'.contentType]", path);
    }
    return res;
}

// check _jm_obj_36_may_explode ($.'$openapi#Encoding'.explode)
static bool _jm_f_84(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#Encoding'.explode]", path);
    }
    return res;
}

// object $.'$openapi#Encoding'.headers
static bool _jm_obj_37(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Encoding'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_37 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Encoding'.headers.''
        // $.'$openapi#Encoding'.headers.''.'|'.0
        res = json_model_26(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [$.'$openapi#Encoding'.headers.''.'|'.0]", (path ? &lpath_37 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Encoding'.headers.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Encoding'.headers.''.'|'.1]", (path ? &lpath_37 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Encoding'.headers.''.'|']", (path ? &lpath_37 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_36_may_headers ($.'$openapi#Encoding'.headers)
static bool _jm_f_85(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'.headers
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Encoding'.headers]", path);
    }
    return res;
}

// check _jm_obj_36_may_style ($.'$openapi#Encoding'.style)
static bool _jm_f_86(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'.style
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Encoding'.style]", path);
    }
    return res;
}

static check_fun_t _jm_obj_36_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_36_may_tab, 5);
}

// object $.'$openapi#Encoding'
static bool _jm_obj_36(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Encoding']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_36 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_36_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_36 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Encoding']", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Encoding'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Encoding'.'/^x\\\\-.*$/']", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Encoding']", (path ? &lpath_36 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Encoding ($.'$openapi#Encoding')
static bool json_model_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Encoding'
    res = _jm_obj_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Encoding']", path);
    }
    return res;
}

static bool _jm_re_2(const char *s)
{
  int rc = pcre2_match(_jm_re_2_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_2_data, NULL);
  return rc >= 0;
}

// object $.'$openapi#Responses'
static bool _jm_obj_38(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Responses']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_38 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "default") == 0)
        {
            // handle one may property
            // $.'$openapi#Responses'.default
            // $.'$openapi#Responses'.default.'|'.0
            res = json_model_21(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [$.'$openapi#Responses'.default.'|'.0]", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                // $.'$openapi#Responses'.default.'|'.1
                res = json_model_28(pval, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Responses'.default.'|'.1]", (path ? &lpath_38 : NULL));
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Responses'.default.'|']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Responses'.default]", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if (_jm_re_2(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'
            // $.'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.0
            res = json_model_21(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [$.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.0]", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                // $.'$openapi#Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.1
                res = json_model_28(pval, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.1]", (path ? &lpath_38 : NULL));
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Responses'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Responses'.'/^x\\\\-.*$/']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Responses']", (path ? &lpath_38 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Responses ($.'$openapi#Responses')
static bool json_model_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Responses'
    res = _jm_obj_38(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Responses']", path);
    }
    return res;
}

// object $.'$openapi#Response'.content
static bool _jm_obj_40(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Response'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_40 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Response'.content.''
        res = json_model_18(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [$.'$openapi#Response'.content.'']", (path ? &lpath_40 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_39_may_content ($.'$openapi#Response'.content)
static bool _jm_f_87(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Response'.content
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Response'.content]", path);
    }
    return res;
}

// check _jm_obj_39_may_description ($.'$openapi#Response'.description)
static bool _jm_f_88(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Response'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Response'.description]", path);
    }
    return res;
}

// object $.'$openapi#Response'.headers
static bool _jm_obj_41(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Response'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_41 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Response'.headers.''
        // $.'$openapi#Response'.headers.''.'|'.0
        res = json_model_26(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [$.'$openapi#Response'.headers.''.'|'.0]", (path ? &lpath_41 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Response'.headers.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Response'.headers.''.'|'.1]", (path ? &lpath_41 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Response'.headers.''.'|']", (path ? &lpath_41 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_39_may_headers ($.'$openapi#Response'.headers)
static bool _jm_f_89(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Response'.headers
    res = _jm_obj_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Response'.headers]", path);
    }
    return res;
}

// object $.'$openapi#Response'.links
static bool _jm_obj_42(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Response'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_42 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#Response'.links.''
        // $.'$openapi#Response'.links.''.'|'.0
        res = json_model_25(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [$.'$openapi#Response'.links.''.'|'.0]", (path ? &lpath_42 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#Response'.links.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Response'.links.''.'|'.1]", (path ? &lpath_42 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Response'.links.''.'|']", (path ? &lpath_42 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_39_may_links ($.'$openapi#Response'.links)
static bool _jm_f_90(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Response'.links
    res = _jm_obj_42(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Response'.links]", path);
    }
    return res;
}

static check_fun_t _jm_obj_39_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_39_may_tab, 4);
}

// object $.'$openapi#Response'
static bool _jm_obj_39(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Response']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_39 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_39_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_39 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Response']", (path ? &lpath_39 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Response'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Response'.'/^x\\\\-.*$/']", (path ? &lpath_39 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Response']", (path ? &lpath_39 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Response ($.'$openapi#Response')
static bool json_model_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Response'
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Response']", path);
    }
    return res;
}

// object $.'$openapi#Callback'
static bool _jm_obj_43(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Callback']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_43 = (Path) { prop, 0, path, NULL };
        if (jm_check_fun_string(json_model_24, prop, (path ? &lpath_43 : NULL), rep))
        {
            // handle {len(defs)} key props
            // $.'$openapi#Callback'.'$Expression'
            // $.'$openapi#Callback'.'$Expression'.'|'.0
            res = json_model_12(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [$.'$openapi#Callback'.'$Expression'.'|'.0]", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                // $.'$openapi#Callback'.'$Expression'.'|'.1
                res = json_model_28(pval, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#Callback'.'$Expression'.'|'.1]", (path ? &lpath_43 : NULL));
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Callback'.'$Expression'.'|']", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Callback'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Callback'.'/^x\\\\-.*$/']", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Callback']", (path ? &lpath_43 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Callback ($.'$openapi#Callback')
static bool json_model_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Callback'
    res = _jm_obj_43(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Callback']", path);
    }
    return res;
}

// check _jm_obj_44_may_description ($.'$openapi#Example'.description)
static bool _jm_f_91(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Example'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Example'.description]", path);
    }
    return res;
}

// check _jm_obj_44_may_externalValue ($.'$openapi#Example'.externalValue)
static bool _jm_f_92(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Example'.externalValue
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Example'.externalValue]", path);
    }
    return res;
}

// check _jm_obj_44_may_summary ($.'$openapi#Example'.summary)
static bool _jm_f_93(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Example'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Example'.summary]", path);
    }
    return res;
}

// check _jm_obj_44_may_value ($.'$openapi#Example'.value)
static bool _jm_f_94(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Example'.value
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Example'.value]", path);
    }
    return res;
}

static check_fun_t _jm_obj_44_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_44_may_tab, 4);
}

// object $.'$openapi#Example'
static bool _jm_obj_44(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Example']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_44 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_44_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_44 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Example']", (path ? &lpath_44 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Example'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Example'.'/^x\\\\-.*$/']", (path ? &lpath_44 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Example']", (path ? &lpath_44 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#Example ($.'$openapi#Example')
static bool json_model_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Example'
    res = _jm_obj_44(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Example']", path);
    }
    return res;
}

static bool _jm_re_3(const char *s)
{
  int rc = pcre2_match(_jm_re_3_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_3_data, NULL);
  return rc >= 0;
}

// check $openapi#Expression ($.'$openapi#Expression')
static bool json_model_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Expression'
    // "/\\{.*\\}/"
    res = json_is_string(val) && _jm_re_3(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected REGEX [$.'$openapi#Expression']", path);
    }
    return res;
}

// check _jm_obj_45_may_description ($.'$openapi#Link'.'|'.1.description)
static bool _jm_f_95(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Link'.'|'.1.description]", path);
    }
    return res;
}

// object $.'$openapi#Link'.'|'.1.parameters
static bool _jm_obj_46(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Link'.'|'.1.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_45_may_parameters ($.'$openapi#Link'.'|'.1.parameters)
static bool _jm_f_96(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.1.parameters
    res = _jm_obj_46(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Link'.'|'.1.parameters]", path);
    }
    return res;
}

// check _jm_obj_45_may_requestBody ($.'$openapi#Link'.'|'.1.requestBody)
static bool _jm_f_97(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.1.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Link'.'|'.1.requestBody]", path);
    }
    return res;
}

// check _jm_obj_45_may_server ($.'$openapi#Link'.'|'.1.server)
static bool _jm_f_98(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.1.server
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [$.'$openapi#Link'.'|'.1.server]", path);
    }
    return res;
}

static check_fun_t _jm_obj_45_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_45_may_tab, 4);
}

// object $.'$openapi#Link'.'|'.1
static bool _jm_obj_45(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Link'.'|'.1]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_45 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "operationId") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#Link'.'|'.1.operationId
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Link'.'|'.1.operationId]", (path ? &lpath_45 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Link'.'|'.1.operationId]", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_45_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_45 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Link'.'|'.1]", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Link'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Link'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_45 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Link'.'|'.1]", (path ? &lpath_45 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Link'.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_47_may_description ($.'$openapi#Link'.'|'.0.description)
static bool _jm_f_99(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Link'.'|'.0.description]", path);
    }
    return res;
}

// object $.'$openapi#Link'.'|'.0.parameters
static bool _jm_obj_48(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Link'.'|'.0.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_47_may_parameters ($.'$openapi#Link'.'|'.0.parameters)
static bool _jm_f_100(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.0.parameters
    res = _jm_obj_48(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Link'.'|'.0.parameters]", path);
    }
    return res;
}

// check _jm_obj_47_may_requestBody ($.'$openapi#Link'.'|'.0.requestBody)
static bool _jm_f_101(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.0.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Link'.'|'.0.requestBody]", path);
    }
    return res;
}

// check _jm_obj_47_may_server ($.'$openapi#Link'.'|'.0.server)
static bool _jm_f_102(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'.'|'.0.server
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [$.'$openapi#Link'.'|'.0.server]", path);
    }
    return res;
}

static check_fun_t _jm_obj_47_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_47_may_tab, 4);
}

// object $.'$openapi#Link'.'|'.0
static bool _jm_obj_47(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Link'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_46 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "operationRef") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#Link'.'|'.0.operationRef
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Link'.'|'.0.operationRef]", (path ? &lpath_46 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Link'.'|'.0.operationRef]", (path ? &lpath_46 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_47_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_46 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Link'.'|'.0]", (path ? &lpath_46 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Link'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Link'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_46 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Link'.'|'.0]", (path ? &lpath_46 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Link'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $openapi#Link ($.'$openapi#Link')
static bool json_model_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Link'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$openapi#Link'.'|']", path);
    }
    if (res)
    {
        // $.'$openapi#Link'.'|'.0
        res = _jm_obj_47(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Link'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$openapi#Link'.'|'.1
            res = _jm_obj_45(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Link'.'|'.1]", path);
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#Link'.'|']", path);
        }
    }
    return res;
}

// check $openapi#Header ($.'$openapi#Header')
static bool json_model_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Header'
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $parameterShare [$.'$openapi#Header']", path);
    }
    return res;
}

// check _jm_obj_49_may_allowEmptyValue ($.'$openapi#parameterShare'.allowEmptyValue)
static bool _jm_f_103(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#parameterShare'.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_49_may_allowReserved ($.'$openapi#parameterShare'.allowReserved)
static bool _jm_f_104(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#parameterShare'.allowReserved]", path);
    }
    return res;
}

// object $.'$openapi#parameterShare'.content
static bool _jm_obj_50(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#parameterShare'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_48 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#parameterShare'.content.''
        res = json_model_18(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [$.'$openapi#parameterShare'.content.'']", (path ? &lpath_48 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_49_may_content ($.'$openapi#parameterShare'.content)
static bool _jm_f_105(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.content
    res = _jm_obj_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#parameterShare'.content]", path);
    }
    return res;
}

// check _jm_obj_49_may_deprecated ($.'$openapi#parameterShare'.deprecated)
static bool _jm_f_106(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#parameterShare'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_49_may_description ($.'$openapi#parameterShare'.description)
static bool _jm_f_107(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#parameterShare'.description]", path);
    }
    return res;
}

// check _jm_obj_49_may_example ($.'$openapi#parameterShare'.example)
static bool _jm_f_108(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#parameterShare'.example]", path);
    }
    return res;
}

// object $.'$openapi#parameterShare'.examples
static bool _jm_obj_51(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#parameterShare'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_49 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#parameterShare'.examples.''
        // $.'$openapi#parameterShare'.examples.''.'|'.0
        res = json_model_23(pval, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [$.'$openapi#parameterShare'.examples.''.'|'.0]", (path ? &lpath_49 : NULL));
        }
        if (! res)
        {
            // $.'$openapi#parameterShare'.examples.''.'|'.1
            res = json_model_28(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [$.'$openapi#parameterShare'.examples.''.'|'.1]", (path ? &lpath_49 : NULL));
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#parameterShare'.examples.''.'|']", (path ? &lpath_49 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_49_may_examples ($.'$openapi#parameterShare'.examples)
static bool _jm_f_109(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.examples
    res = _jm_obj_51(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#parameterShare'.examples]", path);
    }
    return res;
}

// check _jm_obj_49_may_explode ($.'$openapi#parameterShare'.explode)
static bool _jm_f_110(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#parameterShare'.explode]", path);
    }
    return res;
}

// check _jm_obj_49_may_model ($.'$openapi#parameterShare'.model)
static bool _jm_f_111(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.model
    res = json_model_56(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#parameterShare'.model]", path);
    }
    return res;
}

// check _jm_obj_49_may_required ($.'$openapi#parameterShare'.required)
static bool _jm_f_112(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#parameterShare'.required]", path);
    }
    return res;
}


// check _jm_obj_49_may_style ($.'$openapi#parameterShare'.style)
static bool _jm_f_113(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'.style
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_2, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$openapi#parameterShare'.style.'|']", path);
    }
    return res;
}

static check_fun_t _jm_obj_49_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_49_may_tab, 11);
}

// object $.'$openapi#parameterShare'
static bool _jm_obj_49(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#parameterShare']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_47 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_49_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_47 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#parameterShare']", (path ? &lpath_47 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#parameterShare'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#parameterShare'.'/^x\\\\-.*$/']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#parameterShare']", (path ? &lpath_47 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#parameterShare ($.'$openapi#parameterShare')
static bool json_model_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#parameterShare'
    res = _jm_obj_49(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#parameterShare']", path);
    }
    return res;
}

// check _jm_obj_52_may_description ($.'$openapi#Tag'.description)
static bool _jm_f_114(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Tag'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Tag'.description]", path);
    }
    return res;
}

// check _jm_obj_52_may_externalDocs ($.'$openapi#Tag'.externalDocs)
static bool _jm_f_115(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Tag'.externalDocs
    res = json_model_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [$.'$openapi#Tag'.externalDocs]", path);
    }
    return res;
}

static check_fun_t _jm_obj_52_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_52_may_tab, 2);
}

// object $.'$openapi#Tag'
static bool _jm_obj_52(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Tag']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_50 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#Tag'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Tag'.name]", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Tag'.name]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_52_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_50 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Tag']", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#Tag'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#Tag'.'/^x\\\\-.*$/']", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Tag']", (path ? &lpath_50 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Tag']", path);
        return false;
    }
    return true;
}

// check $openapi#Tag ($.'$openapi#Tag')
static bool json_model_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Tag'
    res = _jm_obj_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Tag']", path);
    }
    return res;
}

// check _jm_obj_53_may_description ($.'$openapi#Reference'.description)
static bool _jm_f_116(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Reference'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Reference'.description]", path);
    }
    return res;
}

// check _jm_obj_53_may_summary ($.'$openapi#Reference'.summary)
static bool _jm_f_117(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Reference'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Reference'.summary]", path);
    }
    return res;
}

static check_fun_t _jm_obj_53_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_53_may_tab, 2);
}

// object $.'$openapi#Reference'
static bool _jm_obj_53(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#Reference']", path);
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
        if (strcmp(prop, "$ref") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#Reference'.'$ref'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#Reference'.'$ref']", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#Reference'.$ref]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_53_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_51 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#Reference']", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#Reference']", (path ? &lpath_51 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#Reference']", path);
        return false;
    }
    return true;
}

// check $openapi#Reference ($.'$openapi#Reference')
static bool json_model_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Reference'
    res = _jm_obj_53(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#Reference']", path);
    }
    return res;
}

// check _jm_obj_54_must_flows ($.'$openapi#SecurityScheme'.flows)
static bool _jm_f_118(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.flows
    res = json_model_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlows [$.'$openapi#SecurityScheme'.flows]", path);
    }
    return res;
}

// check _jm_obj_54_must_in ($.'$openapi#SecurityScheme'.in)
static bool _jm_f_119(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.in
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.in]", path);
    }
    return res;
}

// check _jm_obj_54_must_name ($.'$openapi#SecurityScheme'.name)
static bool _jm_f_120(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.name]", path);
    }
    return res;
}

// check _jm_obj_54_must_openIdConnectUrl ($.'$openapi#SecurityScheme'.openIdConnectUrl)
static bool _jm_f_121(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.openIdConnectUrl
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.openIdConnectUrl]", path);
    }
    return res;
}

// check _jm_obj_54_must_scheme ($.'$openapi#SecurityScheme'.scheme)
static bool _jm_f_122(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.scheme
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.scheme]", path);
    }
    return res;
}

// check _jm_obj_54_must_type ($.'$openapi#SecurityScheme'.type)
static bool _jm_f_123(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.type
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.type]", path);
    }
    return res;
}

static check_fun_t _jm_obj_54_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_54_must_tab, 6);
}

// check _jm_obj_54_may_bearerFormat ($.'$openapi#SecurityScheme'.bearerFormat)
static bool _jm_f_124(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.bearerFormat
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.bearerFormat]", path);
    }
    return res;
}

// check _jm_obj_54_may_description ($.'$openapi#SecurityScheme'.description)
static bool _jm_f_125(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityScheme'.description]", path);
    }
    return res;
}

static check_fun_t _jm_obj_54_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_54_may_tab, 2);
}

// object $.'$openapi#SecurityScheme'
static bool _jm_obj_54(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#SecurityScheme']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_52 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_54_must(prop)))
        {
            // handle 6 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_52 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#SecurityScheme']", (path ? &lpath_52 : NULL));
                    return false;
                }
            }
        }
        else if ((pfun = _jm_obj_54_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_52 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#SecurityScheme']", (path ? &lpath_52 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#SecurityScheme'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#SecurityScheme'.'/^x\\\\-.*$/']", (path ? &lpath_52 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#SecurityScheme']", (path ? &lpath_52 : NULL));
            return false;
        }
    }
    if (must_count != 6)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#SecurityScheme']", path);
        return false;
    }
    return true;
}

// check $openapi#SecurityScheme ($.'$openapi#SecurityScheme')
static bool json_model_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityScheme'
    res = _jm_obj_54(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#SecurityScheme']", path);
    }
    return res;
}

// check _jm_obj_55_may_authorizationCode ($.'$openapi#OAuthFlows'.authorizationCode)
static bool _jm_f_126(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlows'.authorizationCode
    res = json_model_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [$.'$openapi#OAuthFlows'.authorizationCode]", path);
    }
    return res;
}

// check _jm_obj_55_may_clientCredentials ($.'$openapi#OAuthFlows'.clientCredentials)
static bool _jm_f_127(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlows'.clientCredentials
    res = json_model_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [$.'$openapi#OAuthFlows'.clientCredentials]", path);
    }
    return res;
}

// check _jm_obj_55_may_implicit ($.'$openapi#OAuthFlows'.implicit)
static bool _jm_f_128(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlows'.implicit
    res = json_model_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [$.'$openapi#OAuthFlows'.implicit]", path);
    }
    return res;
}

// check _jm_obj_55_may_password ($.'$openapi#OAuthFlows'.password)
static bool _jm_f_129(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlows'.password
    res = json_model_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [$.'$openapi#OAuthFlows'.password]", path);
    }
    return res;
}

static check_fun_t _jm_obj_55_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_55_may_tab, 4);
}

// object $.'$openapi#OAuthFlows'
static bool _jm_obj_55(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#OAuthFlows']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_53 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_55_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_53 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#OAuthFlows']", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#OAuthFlows'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#OAuthFlows'.'/^x\\\\-.*$/']", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#OAuthFlows']", (path ? &lpath_53 : NULL));
            return false;
        }
    }
    return true;
}

// check $openapi#OAuthFlows ($.'$openapi#OAuthFlows')
static bool json_model_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlows'
    res = _jm_obj_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#OAuthFlows']", path);
    }
    return res;
}

// check _jm_obj_56_must_authorizationUrl ($.'$openapi#OAuthFlow'.authorizationUrl)
static bool _jm_f_130(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlow'.authorizationUrl
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OAuthFlow'.authorizationUrl]", path);
    }
    return res;
}

// object $.'$openapi#OAuthFlow'.scopes
static bool _jm_obj_57(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#OAuthFlow'.scopes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_55 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#OAuthFlow'.scopes.''
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OAuthFlow'.scopes.'']", (path ? &lpath_55 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_56_must_scopes ($.'$openapi#OAuthFlow'.scopes)
static bool _jm_f_131(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlow'.scopes
    res = _jm_obj_57(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#OAuthFlow'.scopes]", path);
    }
    return res;
}

// check _jm_obj_56_must_tokenUrl ($.'$openapi#OAuthFlow'.tokenUrl)
static bool _jm_f_132(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlow'.tokenUrl
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OAuthFlow'.tokenUrl]", path);
    }
    return res;
}

static check_fun_t _jm_obj_56_must(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_56_must_tab, 3);
}

// object $.'$openapi#OAuthFlow'
static bool _jm_obj_56(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#OAuthFlow']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_54 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_56_must(prop)))
        {
            // handle 3 must props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_54 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#OAuthFlow']", (path ? &lpath_54 : NULL));
                    return false;
                }
            }
        }
        else if (strcmp(prop, "refreshUrl") == 0)
        {
            // handle one may property
            // $.'$openapi#OAuthFlow'.refreshUrl
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#OAuthFlow'.refreshUrl]", (path ? &lpath_54 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#OAuthFlow'.refreshUrl]", (path ? &lpath_54 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#OAuthFlow'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$openapi#OAuthFlow'.'/^x\\\\-.*$/']", (path ? &lpath_54 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#OAuthFlow']", (path ? &lpath_54 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#OAuthFlow']", path);
        return false;
    }
    return true;
}

// check $openapi#OAuthFlow ($.'$openapi#OAuthFlow')
static bool json_model_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#OAuthFlow'
    res = _jm_obj_56(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#OAuthFlow']", path);
    }
    return res;
}

// object $.'$openapi#SecurityRequirement'
static bool _jm_obj_58(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#SecurityRequirement']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_56 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$openapi#SecurityRequirement'.''
        res = json_is_array(pval);
        if (res)
        {
            size_t arr_6_idx;
            json_t *arr_6_item;
            json_array_foreach(pval, arr_6_idx, arr_6_item)
            {
                Path arr_6_lpath = (Path) { NULL, arr_6_idx, (path ? &lpath_56 : NULL), NULL };
                // $.'$openapi#SecurityRequirement'.''.0
                res = json_is_string(arr_6_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#SecurityRequirement'.''.0]", ((path ? &lpath_56 : NULL) ? &arr_6_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#SecurityRequirement'.'']", (path ? &lpath_56 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check $openapi#SecurityRequirement ($.'$openapi#SecurityRequirement')
static bool json_model_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#SecurityRequirement'
    res = _jm_obj_58(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#SecurityRequirement']", path);
    }
    return res;
}

// check $openapi#Model ($.'$openapi#Model')
static bool json_model_56(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#Model'
    res = json_model_73(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $model#Model [$.'$openapi#Model']", path);
    }
    return res;
}

// check $openapi#model#Model ($.'$openapi#model#Model')
static bool json_model_73(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Model'
    // $.'$openapi#model#Model'.'|'.0
    res = json_model_72(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Scalar [$.'$openapi#model#Model'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$openapi#model#Model'.'|'.1
        res = json_model_63(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Array [$.'$openapi#model#Model'.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$openapi#model#Model'.'|'.2
            res = json_model_70(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Elem [$.'$openapi#model#Model'.'|'.2]", path);
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#model#Model'.'|']", path);
    }
    return res;
}

// check $openapi#model#Array ($.'$openapi#model#Array')
static bool json_model_63(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Array'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_7_idx;
        json_t *arr_7_item;
        json_array_foreach(val, arr_7_idx, arr_7_item)
        {
            Path arr_7_lpath = (Path) { NULL, arr_7_idx, path, NULL };
            // $.'$openapi#model#Array'.0
            res = json_model_73(arr_7_item, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Array'.0]", (path ? &arr_7_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#model#Array']", path);
    }
    return res;
}

static bool _jm_re_4(const char *s)
{
  int rc = pcre2_match(_jm_re_4_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_4_data, NULL);
  return rc >= 0;
}

// object $.'$openapi#model#Elem'.'|'.5
static bool _jm_obj_59(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.5]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_57 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "#") == 0)
        {
            // handle one may property
            // $.'$openapi#model#Elem'.'|'.5.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.5.'#']", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.5.#]", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else if (_jm_re_4(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#model#Elem'.'|'.5.'/^[@|&^+/*]$/'
            res = false;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $NONE [$.'$openapi#model#Elem'.'|'.5.'/^[@|&^+/*]$/']", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            // handle other props
            // $.'$openapi#model#Elem'.'|'.5.''
            res = json_model_73(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.5.'']", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
    }
    return true;
}

// object $.'$openapi#model#Elem'.'|'.4
static bool _jm_obj_60(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.4]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_58 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "+") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#model#Elem'.'|'.4.'+'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_8_idx;
                json_t *arr_8_item;
                json_array_foreach(pval, arr_8_idx, arr_8_item)
                {
                    Path arr_8_lpath = (Path) { NULL, arr_8_idx, (path ? &lpath_58 : NULL), NULL };
                    // $.'$openapi#model#Elem'.'|'.4.'+'.0
                    res = json_model_73(arr_8_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.4.'+'.0]", ((path ? &lpath_58 : NULL) ? &arr_8_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#model#Elem'.'|'.4.'+']", (path ? &lpath_58 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#model#Elem'.'|'.4.+]", (path ? &lpath_58 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle one may property
            // $.'$openapi#model#Elem'.'|'.4.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.4.'#']", (path ? &lpath_58 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.4.#]", (path ? &lpath_58 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#model#Elem'.'|'.4]", (path ? &lpath_58 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#model#Elem'.'|'.4]", path);
        return false;
    }
    return true;
}

// object $.'$openapi#model#Elem'.'|'.3
static bool _jm_obj_61(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.3]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_59 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "^") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#model#Elem'.'|'.3.'^'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_9_idx;
                json_t *arr_9_item;
                json_array_foreach(pval, arr_9_idx, arr_9_item)
                {
                    Path arr_9_lpath = (Path) { NULL, arr_9_idx, (path ? &lpath_59 : NULL), NULL };
                    // $.'$openapi#model#Elem'.'|'.3.'^'.0
                    res = json_model_73(arr_9_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.3.'^'.0]", ((path ? &lpath_59 : NULL) ? &arr_9_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#model#Elem'.'|'.3.'^']", (path ? &lpath_59 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#model#Elem'.'|'.3.^]", (path ? &lpath_59 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle one may property
            // $.'$openapi#model#Elem'.'|'.3.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.3.'#']", (path ? &lpath_59 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.3.#]", (path ? &lpath_59 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#model#Elem'.'|'.3]", (path ? &lpath_59 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#model#Elem'.'|'.3]", path);
        return false;
    }
    return true;
}

// object $.'$openapi#model#Elem'.'|'.2
static bool _jm_obj_62(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.2]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_60 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "&") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#model#Elem'.'|'.2.'&'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_10_idx;
                json_t *arr_10_item;
                json_array_foreach(pval, arr_10_idx, arr_10_item)
                {
                    Path arr_10_lpath = (Path) { NULL, arr_10_idx, (path ? &lpath_60 : NULL), NULL };
                    // $.'$openapi#model#Elem'.'|'.2.'&'.0
                    res = json_model_73(arr_10_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.2.'&'.0]", ((path ? &lpath_60 : NULL) ? &arr_10_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#model#Elem'.'|'.2.'&']", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#model#Elem'.'|'.2.&]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle one may property
            // $.'$openapi#model#Elem'.'|'.2.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.2.'#']", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.2.#]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#model#Elem'.'|'.2]", (path ? &lpath_60 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#model#Elem'.'|'.2]", path);
        return false;
    }
    return true;
}

// object $.'$openapi#model#Elem'.'|'.1
static bool _jm_obj_63(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_61 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "|") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#model#Elem'.'|'.1.'|'
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_11_idx;
                json_t *arr_11_item;
                json_array_foreach(pval, arr_11_idx, arr_11_item)
                {
                    Path arr_11_lpath = (Path) { NULL, arr_11_idx, (path ? &lpath_61 : NULL), NULL };
                    // $.'$openapi#model#Elem'.'|'.1.'|'.0
                    res = json_model_73(arr_11_item, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.1.'|'.0]", ((path ? &lpath_61 : NULL) ? &arr_11_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$openapi#model#Elem'.'|'.1.'|']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#model#Elem'.'|'.1.|]", (path ? &lpath_61 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "#") == 0)
        {
            // handle one may property
            // $.'$openapi#model#Elem'.'|'.1.'#'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.1.'#']", (path ? &lpath_61 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.1.#]", (path ? &lpath_61 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#model#Elem'.'|'.1]", (path ? &lpath_61 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#model#Elem'.'|'.1]", path);
        return false;
    }
    return true;
}

// check _jm_obj_64_may_! ($.'$openapi#model#Elem'.'|'.0.'!')
static bool _jm_f_133(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Elem'.'|'.0.'!'
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#model#Elem'.'|'.0.'!']", path);
    }
    return res;
}

// check _jm_obj_64_may_# ($.'$openapi#model#Elem'.'|'.0.'#')
static bool _jm_f_134(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Elem'.'|'.0.'#'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.0.'#']", path);
    }
    return res;
}

static check_fun_t _jm_obj_64_may(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_64_may_tab, 2);
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

// object $.'$openapi#model#Elem'.'|'.0
static bool _jm_obj_64(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$openapi#model#Elem'.'|'.0]", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_62 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "@") == 0)
        {
            // handle one must property
            must_count += 1;
            // $.'$openapi#model#Elem'.'|'.0.'@'
            res = json_model_73(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Model [$.'$openapi#model#Elem'.'|'.0.'@']", (path ? &lpath_62 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$openapi#model#Elem'.'|'.0.@]", (path ? &lpath_62 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_64_may(prop)))
        {
            // handle {len(may)} may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_62 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$openapi#model#Elem'.'|'.0]", (path ? &lpath_62 : NULL));
                return false;
            }
        }
        else if (_jm_re_5(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'
            // $.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0
            res = json_is_integer(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.0]", (path ? &lpath_62 : NULL));
            }
            if (! res)
            {
                // $.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1
                res = json_is_real(pval);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.1]", (path ? &lpath_62 : NULL));
                }
                if (! res)
                {
                    // $.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2
                    res = json_is_string(pval);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|'.2]", (path ? &lpath_62 : NULL));
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#model#Elem'.'|'.0.'/^(<=|>=|<|>|≥|≤)$/'.'|']", (path ? &lpath_62 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_6(prop))
        {
            // handle {len(regs)} re props
            // $.'$openapi#model#Elem'.'|'.0.'/^(=|!=|≠)$/'
            res = json_model_59(pval, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Val [$.'$openapi#model#Elem'.'|'.0.'/^(=|!=|≠)$/']", (path ? &lpath_62 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$openapi#model#Elem'.'|'.0]", (path ? &lpath_62 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$openapi#model#Elem'.'|'.0]", path);
        return false;
    }
    return true;
}

// check $openapi#model#Elem ($.'$openapi#model#Elem')
static bool json_model_70(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Elem'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$openapi#model#Elem'.'|']", path);
    }
    if (res)
    {
        // $.'$openapi#model#Elem'.'|'.0
        res = _jm_obj_64(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$openapi#model#Elem'.'|'.1
            res = _jm_obj_63(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.1]", path);
            }
            if (! res)
            {
                // $.'$openapi#model#Elem'.'|'.2
                res = _jm_obj_62(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.2]", path);
                }
                if (! res)
                {
                    // $.'$openapi#model#Elem'.'|'.3
                    res = _jm_obj_61(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // $.'$openapi#model#Elem'.'|'.4
                        res = _jm_obj_60(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // $.'$openapi#model#Elem'.'|'.5
                            res = _jm_obj_59(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$openapi#model#Elem'.'|'.5]", path);
                            }
                        }
                    }
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#model#Elem'.'|']", path);
        }
    }
    return res;
}

// check $openapi#model#Val ($.'$openapi#model#Val')
static bool json_model_59(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Val'
    // $.'$openapi#model#Val'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [$.'$openapi#model#Val'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$openapi#model#Val'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [$.'$openapi#model#Val'.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$openapi#model#Val'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$openapi#model#Val'.'|'.2]", path);
            }
            if (! res)
            {
                // $.'$openapi#model#Val'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$openapi#model#Val'.'|'.3]", path);
                }
                if (! res)
                {
                    // $.'$openapi#model#Val'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Val'.'|'.4]", path);
                    }
                }
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#model#Val'.'|']", path);
    }
    return res;
}

static bool _jm_cst_3_test(const json_t *val)
{
  constant_t cst;
  jm_set_cst(&cst, val);
  return jm_search_cst(&cst, _jm_cst_3, 8);
}

// check $openapi#model#Scalar ($.'$openapi#model#Scalar')
static bool json_model_72(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$openapi#model#Scalar'
    res = _json_is_scalar(val) && _jm_cst_3_test(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$openapi#model#Scalar'.'|']", path);
    }
    if (! res)
    {
        res = json_is_string(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$openapi#model#Scalar'.'|']", path);
        }
        if (res)
        {
            // $.'$openapi#model#Scalar'.'|'.0
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$openapi#model#Scalar'.'|'.0]", path);
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "no model matched [$.'$openapi#model#Scalar'.'|']", path);
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
        _jm_obj_0_must_tab[0] = (propmap_t) { "info", _jm_f_0 };
        _jm_obj_0_must_tab[1] = (propmap_t) { "openapi", _jm_f_1 };
        jm_sort_propmap(_jm_obj_0_must_tab, 2);
        _jm_obj_0_may_tab[0] = (propmap_t) { "component", _jm_f_2 };
        _jm_obj_0_may_tab[1] = (propmap_t) { "externalDocs", _jm_f_3 };
        _jm_obj_0_may_tab[2] = (propmap_t) { "jsonSchemaDialect", _jm_f_4 };
        _jm_obj_0_may_tab[3] = (propmap_t) { "paths", _jm_f_5 };
        _jm_obj_0_may_tab[4] = (propmap_t) { "security", _jm_f_6 };
        _jm_obj_0_may_tab[5] = (propmap_t) { "servers", _jm_f_7 };
        _jm_obj_0_may_tab[6] = (propmap_t) { "tags", _jm_f_8 };
        _jm_obj_0_may_tab[7] = (propmap_t) { "webhooks", _jm_f_9 };
        jm_sort_propmap(_jm_obj_0_may_tab, 8);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^x\\-.*$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        _jm_obj_2_must_tab[0] = (propmap_t) { "title", _jm_f_10 };
        _jm_obj_2_must_tab[1] = (propmap_t) { "version", _jm_f_11 };
        jm_sort_propmap(_jm_obj_2_must_tab, 2);
        _jm_obj_2_may_tab[0] = (propmap_t) { "contact", _jm_f_12 };
        _jm_obj_2_may_tab[1] = (propmap_t) { "description", _jm_f_13 };
        _jm_obj_2_may_tab[2] = (propmap_t) { "license", _jm_f_14 };
        _jm_obj_2_may_tab[3] = (propmap_t) { "summary", _jm_f_15 };
        _jm_obj_2_may_tab[4] = (propmap_t) { "termsOfService", _jm_f_16 };
        jm_sort_propmap(_jm_obj_2_may_tab, 5);
        _jm_obj_3_may_tab[0] = (propmap_t) { "email", _jm_f_17 };
        _jm_obj_3_may_tab[1] = (propmap_t) { "name", _jm_f_18 };
        _jm_obj_3_may_tab[2] = (propmap_t) { "url", _jm_f_19 };
        jm_sort_propmap(_jm_obj_3_may_tab, 3);
        _jm_obj_4_must_tab[0] = (propmap_t) { "name", _jm_f_20 };
        _jm_obj_4_must_tab[1] = (propmap_t) { "url", _jm_f_21 };
        jm_sort_propmap(_jm_obj_4_must_tab, 2);
        _jm_obj_5_must_tab[0] = (propmap_t) { "identifier", _jm_f_22 };
        _jm_obj_5_must_tab[1] = (propmap_t) { "name", _jm_f_23 };
        jm_sort_propmap(_jm_obj_5_must_tab, 2);
        _jm_obj_6_may_tab[0] = (propmap_t) { "description", _jm_f_24 };
        _jm_obj_6_may_tab[1] = (propmap_t) { "variables", _jm_f_25 };
        jm_sort_propmap(_jm_obj_6_may_tab, 2);
        _jm_obj_8_may_tab[0] = (propmap_t) { "description", _jm_f_26 };
        _jm_obj_8_may_tab[1] = (propmap_t) { "enum", _jm_f_27 };
        jm_sort_propmap(_jm_obj_8_may_tab, 2);
        _jm_obj_9_may_tab[0] = (propmap_t) { "callbacks", _jm_f_28 };
        _jm_obj_9_may_tab[1] = (propmap_t) { "examples", _jm_f_29 };
        _jm_obj_9_may_tab[2] = (propmap_t) { "headers", _jm_f_30 };
        _jm_obj_9_may_tab[3] = (propmap_t) { "links", _jm_f_31 };
        _jm_obj_9_may_tab[4] = (propmap_t) { "models", _jm_f_32 };
        _jm_obj_9_may_tab[5] = (propmap_t) { "parameters", _jm_f_33 };
        _jm_obj_9_may_tab[6] = (propmap_t) { "pathItems", _jm_f_34 };
        _jm_obj_9_may_tab[7] = (propmap_t) { "requestBodies", _jm_f_35 };
        _jm_obj_9_may_tab[8] = (propmap_t) { "responses", _jm_f_36 };
        _jm_obj_9_may_tab[9] = (propmap_t) { "securitySchemes", _jm_f_37 };
        jm_sort_propmap(_jm_obj_9_may_tab, 10);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "^/", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
        _jm_obj_21_may_tab[0] = (propmap_t) { "$ref", _jm_f_38 };
        _jm_obj_21_may_tab[1] = (propmap_t) { "description", _jm_f_39 };
        _jm_obj_21_may_tab[2] = (propmap_t) { "get", _jm_f_40 };
        _jm_obj_21_may_tab[3] = (propmap_t) { "head", _jm_f_41 };
        _jm_obj_21_may_tab[4] = (propmap_t) { "options", _jm_f_42 };
        _jm_obj_21_may_tab[5] = (propmap_t) { "parameters", _jm_f_43 };
        _jm_obj_21_may_tab[6] = (propmap_t) { "patch", _jm_f_44 };
        _jm_obj_21_may_tab[7] = (propmap_t) { "post", _jm_f_45 };
        _jm_obj_21_may_tab[8] = (propmap_t) { "put", _jm_f_46 };
        _jm_obj_21_may_tab[9] = (propmap_t) { "servers", _jm_f_47 };
        _jm_obj_21_may_tab[10] = (propmap_t) { "summary", _jm_f_48 };
        _jm_obj_21_may_tab[11] = (propmap_t) { "trace", _jm_f_49 };
        jm_sort_propmap(_jm_obj_21_may_tab, 12);
        _jm_obj_23_may_tab[0] = (propmap_t) { "callbacks", _jm_f_50 };
        _jm_obj_23_may_tab[1] = (propmap_t) { "deprecated", _jm_f_51 };
        _jm_obj_23_may_tab[2] = (propmap_t) { "description", _jm_f_52 };
        _jm_obj_23_may_tab[3] = (propmap_t) { "externalDocs", _jm_f_53 };
        _jm_obj_23_may_tab[4] = (propmap_t) { "operationId", _jm_f_54 };
        _jm_obj_23_may_tab[5] = (propmap_t) { "parameters", _jm_f_55 };
        _jm_obj_23_may_tab[6] = (propmap_t) { "requestBody", _jm_f_56 };
        _jm_obj_23_may_tab[7] = (propmap_t) { "responses", _jm_f_57 };
        _jm_obj_23_may_tab[8] = (propmap_t) { "security", _jm_f_58 };
        _jm_obj_23_may_tab[9] = (propmap_t) { "servers", _jm_f_59 };
        _jm_obj_23_may_tab[10] = (propmap_t) { "summary", _jm_f_60 };
        _jm_obj_23_may_tab[11] = (propmap_t) { "tags", _jm_f_61 };
        jm_sort_propmap(_jm_obj_23_may_tab, 12);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_0, 4);
        _jm_obj_28_must_tab[0] = (propmap_t) { "in", _jm_f_62 };
        _jm_obj_28_must_tab[1] = (propmap_t) { "name", _jm_f_63 };
        jm_sort_propmap(_jm_obj_28_must_tab, 2);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (constant_t) { cst_is_string, { .s = "matrix" } };
        _jm_cst_1[1] = (constant_t) { cst_is_string, { .s = "label" } };
        _jm_cst_1[2] = (constant_t) { cst_is_string, { .s = "form" } };
        _jm_cst_1[3] = (constant_t) { cst_is_string, { .s = "simple" } };
        _jm_cst_1[4] = (constant_t) { cst_is_string, { .s = "spaceDelimited" } };
        _jm_cst_1[5] = (constant_t) { cst_is_string, { .s = "pipeDelimited" } };
        _jm_cst_1[6] = (constant_t) { cst_is_string, { .s = "deepObject" } };
        jm_sort_cst(_jm_cst_1, 7);
        _jm_obj_28_may_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_64 };
        _jm_obj_28_may_tab[1] = (propmap_t) { "allowReserved", _jm_f_65 };
        _jm_obj_28_may_tab[2] = (propmap_t) { "content", _jm_f_66 };
        _jm_obj_28_may_tab[3] = (propmap_t) { "deprecated", _jm_f_67 };
        _jm_obj_28_may_tab[4] = (propmap_t) { "description", _jm_f_68 };
        _jm_obj_28_may_tab[5] = (propmap_t) { "example", _jm_f_69 };
        _jm_obj_28_may_tab[6] = (propmap_t) { "examples", _jm_f_70 };
        _jm_obj_28_may_tab[7] = (propmap_t) { "explode", _jm_f_71 };
        _jm_obj_28_may_tab[8] = (propmap_t) { "model", _jm_f_72 };
        _jm_obj_28_may_tab[9] = (propmap_t) { "required", _jm_f_73 };
        _jm_obj_28_may_tab[10] = (propmap_t) { "style", _jm_f_74 };
        jm_sort_propmap(_jm_obj_28_may_tab, 11);
        _jm_obj_31_may_tab[0] = (propmap_t) { "content", _jm_f_75 };
        _jm_obj_31_may_tab[1] = (propmap_t) { "description", _jm_f_76 };
        _jm_obj_31_may_tab[2] = (propmap_t) { "required", _jm_f_77 };
        jm_sort_propmap(_jm_obj_31_may_tab, 3);
        _jm_obj_33_may_tab[0] = (propmap_t) { "encoding", _jm_f_78 };
        _jm_obj_33_may_tab[1] = (propmap_t) { "example", _jm_f_79 };
        _jm_obj_33_may_tab[2] = (propmap_t) { "examples", _jm_f_80 };
        _jm_obj_33_may_tab[3] = (propmap_t) { "model", _jm_f_81 };
        jm_sort_propmap(_jm_obj_33_may_tab, 4);
        _jm_obj_36_may_tab[0] = (propmap_t) { "allowReserved", _jm_f_82 };
        _jm_obj_36_may_tab[1] = (propmap_t) { "contentType", _jm_f_83 };
        _jm_obj_36_may_tab[2] = (propmap_t) { "explode", _jm_f_84 };
        _jm_obj_36_may_tab[3] = (propmap_t) { "headers", _jm_f_85 };
        _jm_obj_36_may_tab[4] = (propmap_t) { "style", _jm_f_86 };
        jm_sort_propmap(_jm_obj_36_may_tab, 5);
        _jm_re_2_code = pcre2_compile((PCRE2_SPTR) "^[1-5](\\d\\d|XX)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_2_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_2_data = pcre2_match_data_create_from_pattern(_jm_re_2_code, NULL);
        _jm_obj_39_may_tab[0] = (propmap_t) { "content", _jm_f_87 };
        _jm_obj_39_may_tab[1] = (propmap_t) { "description", _jm_f_88 };
        _jm_obj_39_may_tab[2] = (propmap_t) { "headers", _jm_f_89 };
        _jm_obj_39_may_tab[3] = (propmap_t) { "links", _jm_f_90 };
        jm_sort_propmap(_jm_obj_39_may_tab, 4);
        _jm_obj_44_may_tab[0] = (propmap_t) { "description", _jm_f_91 };
        _jm_obj_44_may_tab[1] = (propmap_t) { "externalValue", _jm_f_92 };
        _jm_obj_44_may_tab[2] = (propmap_t) { "summary", _jm_f_93 };
        _jm_obj_44_may_tab[3] = (propmap_t) { "value", _jm_f_94 };
        jm_sort_propmap(_jm_obj_44_may_tab, 4);
        _jm_re_3_code = pcre2_compile((PCRE2_SPTR) "\\{.*\\}", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_3_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_3_data = pcre2_match_data_create_from_pattern(_jm_re_3_code, NULL);
        _jm_obj_45_may_tab[0] = (propmap_t) { "description", _jm_f_95 };
        _jm_obj_45_may_tab[1] = (propmap_t) { "parameters", _jm_f_96 };
        _jm_obj_45_may_tab[2] = (propmap_t) { "requestBody", _jm_f_97 };
        _jm_obj_45_may_tab[3] = (propmap_t) { "server", _jm_f_98 };
        jm_sort_propmap(_jm_obj_45_may_tab, 4);
        _jm_obj_47_may_tab[0] = (propmap_t) { "description", _jm_f_99 };
        _jm_obj_47_may_tab[1] = (propmap_t) { "parameters", _jm_f_100 };
        _jm_obj_47_may_tab[2] = (propmap_t) { "requestBody", _jm_f_101 };
        _jm_obj_47_may_tab[3] = (propmap_t) { "server", _jm_f_102 };
        jm_sort_propmap(_jm_obj_47_may_tab, 4);
        // initialize sorted set _jm_cst_2
        _jm_cst_2[0] = (constant_t) { cst_is_string, { .s = "matrix" } };
        _jm_cst_2[1] = (constant_t) { cst_is_string, { .s = "label" } };
        _jm_cst_2[2] = (constant_t) { cst_is_string, { .s = "form" } };
        _jm_cst_2[3] = (constant_t) { cst_is_string, { .s = "simple" } };
        _jm_cst_2[4] = (constant_t) { cst_is_string, { .s = "spaceDelimited" } };
        _jm_cst_2[5] = (constant_t) { cst_is_string, { .s = "pipeDelimited" } };
        _jm_cst_2[6] = (constant_t) { cst_is_string, { .s = "deepObject" } };
        jm_sort_cst(_jm_cst_2, 7);
        _jm_obj_49_may_tab[0] = (propmap_t) { "allowEmptyValue", _jm_f_103 };
        _jm_obj_49_may_tab[1] = (propmap_t) { "allowReserved", _jm_f_104 };
        _jm_obj_49_may_tab[2] = (propmap_t) { "content", _jm_f_105 };
        _jm_obj_49_may_tab[3] = (propmap_t) { "deprecated", _jm_f_106 };
        _jm_obj_49_may_tab[4] = (propmap_t) { "description", _jm_f_107 };
        _jm_obj_49_may_tab[5] = (propmap_t) { "example", _jm_f_108 };
        _jm_obj_49_may_tab[6] = (propmap_t) { "examples", _jm_f_109 };
        _jm_obj_49_may_tab[7] = (propmap_t) { "explode", _jm_f_110 };
        _jm_obj_49_may_tab[8] = (propmap_t) { "model", _jm_f_111 };
        _jm_obj_49_may_tab[9] = (propmap_t) { "required", _jm_f_112 };
        _jm_obj_49_may_tab[10] = (propmap_t) { "style", _jm_f_113 };
        jm_sort_propmap(_jm_obj_49_may_tab, 11);
        _jm_obj_52_may_tab[0] = (propmap_t) { "description", _jm_f_114 };
        _jm_obj_52_may_tab[1] = (propmap_t) { "externalDocs", _jm_f_115 };
        jm_sort_propmap(_jm_obj_52_may_tab, 2);
        _jm_obj_53_may_tab[0] = (propmap_t) { "description", _jm_f_116 };
        _jm_obj_53_may_tab[1] = (propmap_t) { "summary", _jm_f_117 };
        jm_sort_propmap(_jm_obj_53_may_tab, 2);
        _jm_obj_54_must_tab[0] = (propmap_t) { "flows", _jm_f_118 };
        _jm_obj_54_must_tab[1] = (propmap_t) { "in", _jm_f_119 };
        _jm_obj_54_must_tab[2] = (propmap_t) { "name", _jm_f_120 };
        _jm_obj_54_must_tab[3] = (propmap_t) { "openIdConnectUrl", _jm_f_121 };
        _jm_obj_54_must_tab[4] = (propmap_t) { "scheme", _jm_f_122 };
        _jm_obj_54_must_tab[5] = (propmap_t) { "type", _jm_f_123 };
        jm_sort_propmap(_jm_obj_54_must_tab, 6);
        _jm_obj_54_may_tab[0] = (propmap_t) { "bearerFormat", _jm_f_124 };
        _jm_obj_54_may_tab[1] = (propmap_t) { "description", _jm_f_125 };
        jm_sort_propmap(_jm_obj_54_may_tab, 2);
        _jm_obj_55_may_tab[0] = (propmap_t) { "authorizationCode", _jm_f_126 };
        _jm_obj_55_may_tab[1] = (propmap_t) { "clientCredentials", _jm_f_127 };
        _jm_obj_55_may_tab[2] = (propmap_t) { "implicit", _jm_f_128 };
        _jm_obj_55_may_tab[3] = (propmap_t) { "password", _jm_f_129 };
        jm_sort_propmap(_jm_obj_55_may_tab, 4);
        _jm_obj_56_must_tab[0] = (propmap_t) { "authorizationUrl", _jm_f_130 };
        _jm_obj_56_must_tab[1] = (propmap_t) { "scopes", _jm_f_131 };
        _jm_obj_56_must_tab[2] = (propmap_t) { "tokenUrl", _jm_f_132 };
        jm_sort_propmap(_jm_obj_56_must_tab, 3);
        _jm_re_4_code = pcre2_compile((PCRE2_SPTR) "^[@|&^+/*]$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_4_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_4_data = pcre2_match_data_create_from_pattern(_jm_re_4_code, NULL);
        _jm_obj_64_may_tab[0] = (propmap_t) { "!", _jm_f_133 };
        _jm_obj_64_may_tab[1] = (propmap_t) { "#", _jm_f_134 };
        jm_sort_propmap(_jm_obj_64_may_tab, 2);
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
        // initialize sorted set _jm_cst_3
        _jm_cst_3[0] = (constant_t) { cst_is_null, { .s = NULL } };
        _jm_cst_3[1] = (constant_t) { cst_is_bool, { .b = true } };
        _jm_cst_3[2] = (constant_t) { cst_is_integer, { .i = 0 } };
        _jm_cst_3[3] = (constant_t) { cst_is_integer, { .i = 1 } };
        _jm_cst_3[4] = (constant_t) { cst_is_integer, { .i = -1 } };
        _jm_cst_3[5] = (constant_t) { cst_is_float, { .f = 0.0 } };
        _jm_cst_3[6] = (constant_t) { cst_is_float, { .f = 1.0 } };
        _jm_cst_3[7] = (constant_t) { cst_is_float, { .f = -1.0 } };
        jm_sort_cst(_jm_cst_3, 8);
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
