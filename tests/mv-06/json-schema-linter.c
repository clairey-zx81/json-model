#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_0[27];
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_0_map_tab[4];
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_1_map_tab[6];
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_2_map_tab[4];
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_6_map_tab[10];
static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_1[27];
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_9_map_tab[14];
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_38(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_39(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_40(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_41(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_42(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_43(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_44(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_45(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_46(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_47(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_48(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_49(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_50(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_51(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_12_map_tab[16];
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_67(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_15_map_tab[14];
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_68(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_69(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_70(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_71(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_72(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_73(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_74(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_75(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_76(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_20_map_tab[12];
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_23_map_tab[12];
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_92(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_93(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_94(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_95(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_96(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_97(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_98(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_99(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_100(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_101(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_26_map_tab[10];
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_102(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_103(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_104(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_105(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_106(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_107(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_108(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_109(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_110(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_111(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_29_map_tab[10];
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_112(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_113(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_114(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_115(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_116(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_117(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_118(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_119(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_120(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_121(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_32_map_tab[10];
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_122(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_123(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_124(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_125(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_126(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_127(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_128(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_129(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_130(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_131(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_35_map_tab[10];
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_132(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_133(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_134(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_135(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_136(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_137(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_138(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_139(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_140(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_141(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_38_map_tab[10];
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_142(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_143(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_144(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_145(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_146(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_147(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_148(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_149(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_150(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_151(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_41_map_tab[10];
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_152(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_153(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_154(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_155(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_156(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_157(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_158(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_159(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_160(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_161(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_44_map_tab[10];
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_162(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_163(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_164(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_165(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_166(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_167(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_168(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_169(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_170(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_171(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_47_map_tab[10];
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[25];
const size_t check_model_map_size = 25;

// check $const (.'$const')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$const'
    // .'$const'.'|'.0
    res = json_is_null(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not null [.'$const'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$const'.'|'.1
        res = json_is_boolean(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a bool [.'$const'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$const'.'|'.2
            res = json_is_integer(val);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$const'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$const'.'|'.3
                res = json_is_real(val);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$const'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$const'.'|'.4
                    res = json_is_string(val);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$const'.'|'.4]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'$const'.'|']", path);
    }
    return res;
}

// check $enum (.'$enum')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$enum'
    res = json_is_array(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$enum'.'|']", path);
    }
    if (res)
    {
        // .'$enum'.'|'.0
        res = true;
        if (res)
        {
            size_t arr_2_idx;
            json_t *arr_2_item;
            json_array_foreach(val, arr_2_idx, arr_2_item)
            {
                jm_path_t arr_2_lpath = (jm_path_t) { NULL, arr_2_idx, path, NULL };
                // .'$enum'.'|'.0.0
                res = json_is_string(arr_2_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [.'$enum'.'|'.0.0]", (path ? &arr_2_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$enum'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$enum'.'|'.1
            res = true;
            if (res)
            {
                size_t arr_1_idx;
                json_t *arr_1_item;
                json_array_foreach(val, arr_1_idx, arr_1_item)
                {
                    jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, path, NULL };
                    // .'$enum'.'|'.1.0
                    res = json_is_integer(arr_1_item);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$enum'.'|'.1.0]", (path ? &arr_1_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$enum'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$enum'.'|'.2
                res = true;
                if (res)
                {
                    size_t arr_0_idx;
                    json_t *arr_0_item;
                    json_array_foreach(val, arr_0_idx, arr_0_item)
                    {
                        jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
                        // .'$enum'.'|'.2.0
                        res = json_is_boolean(arr_0_item);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not a bool [.'$enum'.'|'.2.0]", (path ? &arr_0_lpath : NULL));
                        }
                        if (! res)
                        {
                            break;
                        }
                    }
                }
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$enum'.'|'.2]", path);
                }
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$enum'.'|']", path);
        }
    }
    return res;
}

// check $schemaArray (.'$schemaArray')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schemaArray'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            jm_path_t arr_3_lpath = (jm_path_t) { NULL, arr_3_idx, path, NULL };
            // .'$schemaArray'.0
            res = json_model_24(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schemaArray'.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schemaArray']", path);
    }
    return res;
}


// check _jm_obj_0_map_format (.'$stringKeywords'.format)
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringKeywords'.format
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 27);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$stringKeywords'.format.'|']", path);
    }
    return res;
}

// check _jm_obj_0_map_maxLength (.'$stringKeywords'.maxLength)
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringKeywords'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$stringKeywords'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_minLength (.'$stringKeywords'.minLength)
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringKeywords'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$stringKeywords'.minLength]", path);
    }
    return res;
}

// check _jm_obj_0_map_pattern (.'$stringKeywords'.pattern)
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringKeywords'.pattern
    res = jm_is_valid_regex(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$stringKeywords'.pattern]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 4);
}

// object .'$stringKeywords'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$stringKeywords']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$stringKeywords']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$stringKeywords']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $stringKeywords (.'$stringKeywords')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringKeywords'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$stringKeywords']", path);
    }
    return res;
}

// check _jm_obj_1_map_additionalItems (.'$arrayKeywords'.additionalItems)
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.additionalItems
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$arrayKeywords'.additionalItems]", path);
    }
    return res;
}

// check _jm_obj_1_map_items (.'$arrayKeywords'.items)
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.items
    // .'$arrayKeywords'.items.'|'.0
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$arrayKeywords'.items.'|'.0]", path);
    }
    if (! res)
    {
        // .'$arrayKeywords'.items.'|'.1
        res = json_model_4(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$arrayKeywords'.items.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$arrayKeywords'.items.'|']", path);
    }
    return res;
}

// check _jm_obj_1_map_maxItems (.'$arrayKeywords'.maxItems)
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$arrayKeywords'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_1_map_minItems (.'$arrayKeywords'.minItems)
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$arrayKeywords'.minItems]", path);
    }
    return res;
}

// check _jm_obj_1_map_prefixItems (.'$arrayKeywords'.prefixItems)
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.prefixItems
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$arrayKeywords'.prefixItems]", path);
    }
    return res;
}

// check _jm_obj_1_map_uniqueItems (.'$arrayKeywords'.uniqueItems)
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$arrayKeywords'.uniqueItems]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_1_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_map_tab, 6);
}

// object .'$arrayKeywords'
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$arrayKeywords']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_1_map(prop)))
        {
            // handle 6 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_1 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$arrayKeywords']", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$arrayKeywords']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    return true;
}

// check $arrayKeywords (.'$arrayKeywords')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$arrayKeywords'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$arrayKeywords']", path);
    }
    return res;
}

// check _jm_obj_2_map_additionalProperties (.'$objectKeywords'.additionalProperties)
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$objectKeywords'.additionalProperties
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$objectKeywords'.additionalProperties]", path);
    }
    return res;
}

// object .'$objectKeywords'.patternProperties
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$objectKeywords'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop))
        {
            // handle 1 key props
            // .'$objectKeywords'.patternProperties.'$REGEX'
            res = json_model_24(pval, (path ? &lpath_3 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$objectKeywords'.patternProperties.'$REGEX']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$objectKeywords'.patternProperties]", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_2_map_patternProperties (.'$objectKeywords'.patternProperties)
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$objectKeywords'.patternProperties
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$objectKeywords'.patternProperties]", path);
    }
    return res;
}

// object .'$objectKeywords'.properties
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$objectKeywords'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$objectKeywords'.properties.''
        res = json_model_24(pval, (path ? &lpath_4 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$objectKeywords'.properties.'']", (path ? &lpath_4 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_2_map_properties (.'$objectKeywords'.properties)
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$objectKeywords'.properties
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$objectKeywords'.properties]", path);
    }
    return res;
}

// check _jm_obj_2_map_required (.'$objectKeywords'.required)
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$objectKeywords'.required
    res = json_is_array(val);
    if (res)
    {
        size_t arr_4_idx;
        json_t *arr_4_item;
        json_array_foreach(val, arr_4_idx, arr_4_item)
        {
            jm_path_t arr_4_lpath = (jm_path_t) { NULL, arr_4_idx, path, NULL };
            // .'$objectKeywords'.required.0
            res = json_is_string(arr_4_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$objectKeywords'.required.0]", (path ? &arr_4_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$objectKeywords'.required]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_2_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_map_tab, 4);
}

// object .'$objectKeywords'
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$objectKeywords']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_2_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$objectKeywords']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$objectKeywords']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    return true;
}

// check $objectKeywords (.'$objectKeywords')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$objectKeywords'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$objectKeywords']", path);
    }
    return res;
}

// object .'$numberKeywords'
static bool _jm_obj_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$numberKeywords']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_5 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "minimum") == 0)
        {
            // handle may minimum property
            // .'$numberKeywords'.minimum
            res = json_is_real(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$numberKeywords'.minimum]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$numberKeywords'.minimum]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "maximum") == 0)
        {
            // handle may maximum property
            // .'$numberKeywords'.maximum
            res = json_is_real(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$numberKeywords'.maximum]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$numberKeywords'.maximum]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$numberKeywords']", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    return true;
}

// check $numberKeywords (.'$numberKeywords')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$numberKeywords'
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$numberKeywords']", path);
    }
    return res;
}

// check _jm_obj_6_map_$comment (.'$metas'.'$comment')
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.'$comment']", path);
    }
    return res;
}

// object .'$metas'.'$defs'
static bool _jm_obj_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$metas'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_7 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$metas'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_7 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$metas'.'$defs'.'']", (path ? &lpath_7 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_6_map_$defs (.'$metas'.'$defs')
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.'$defs'
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$metas'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_6_map_$id (.'$metas'.'$id')
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.'$id']", path);
    }
    return res;
}

// check _jm_obj_6_map_$schema (.'$metas'.'$schema')
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_6_map_default (.'$metas'.default)
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$metas'.default]", path);
    }
    return res;
}

// object .'$metas'.definitions
static bool _jm_obj_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$metas'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_8 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$metas'.definitions.''
        res = json_model_24(pval, (path ? &lpath_8 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$metas'.definitions.'']", (path ? &lpath_8 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_6_map_definitions (.'$metas'.definitions)
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.definitions
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$metas'.definitions]", path);
    }
    return res;
}

// check _jm_obj_6_map_description (.'$metas'.description)
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.description]", path);
    }
    return res;
}

// check _jm_obj_6_map_examples (.'$metas'.examples)
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$metas'.examples]", path);
    }
    return res;
}

// check _jm_obj_6_map_id (.'$metas'.id)
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.id]", path);
    }
    return res;
}

// check _jm_obj_6_map_title (.'$metas'.title)
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$metas'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_6_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_map_tab, 10);
}

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// object .'$metas'
static bool _jm_obj_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$metas']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_6 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_6_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_6 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$metas']", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$metas'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$metas'.'/^x-.*/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$metas']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    return true;
}

// check $metas (.'$metas')
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$metas'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$metas']", path);
    }
    return res;
}

// check _jm_obj_9_map_$comment (.'$String'.'$comment')
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.'$comment']", path);
    }
    return res;
}

// object .'$String'.'$defs'
static bool _jm_obj_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$String'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_10 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$String'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_10 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$String'.'$defs'.'']", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_$defs (.'$String'.'$defs')
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.'$defs'
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$String'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_9_map_$id (.'$String'.'$id')
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.'$id']", path);
    }
    return res;
}

// check _jm_obj_9_map_$schema (.'$String'.'$schema')
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_9_map_default (.'$String'.default)
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$String'.default]", path);
    }
    return res;
}

// object .'$String'.definitions
static bool _jm_obj_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$String'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_11 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$String'.definitions.''
        res = json_model_24(pval, (path ? &lpath_11 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$String'.definitions.'']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_definitions (.'$String'.definitions)
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.definitions
    res = _jm_obj_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$String'.definitions]", path);
    }
    return res;
}

// check _jm_obj_9_map_description (.'$String'.description)
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.description]", path);
    }
    return res;
}

// check _jm_obj_9_map_examples (.'$String'.examples)
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$String'.examples]", path);
    }
    return res;
}


// check _jm_obj_9_map_format (.'$String'.format)
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.format
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 27);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$String'.format.'|']", path);
    }
    return res;
}

// check _jm_obj_9_map_id (.'$String'.id)
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.id]", path);
    }
    return res;
}

// check _jm_obj_9_map_maxLength (.'$String'.maxLength)
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$String'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_9_map_minLength (.'$String'.minLength)
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$String'.minLength]", path);
    }
    return res;
}

// check _jm_obj_9_map_pattern (.'$String'.pattern)
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.pattern
    res = jm_is_valid_regex(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$String'.pattern]", path);
    }
    return res;
}

// check _jm_obj_9_map_title (.'$String'.title)
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_9_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_map_tab, 14);
}

// object .'$String'
static bool _jm_obj_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$String']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_9 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$String'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.type]", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$String'.type]", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_9_map(prop)))
        {
            // handle 14 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_9 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$String']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$String'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$String'.'/^x-.*/']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$String']", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$String']", path);
            }
        }
        return false;
    }
    return true;
}

// check $String (.'$String')
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$String']", path);
    }
    return res;
}

// check _jm_obj_12_map_$comment (.'$Array'.'$comment')
static bool _jm_f_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.'$comment']", path);
    }
    return res;
}

// object .'$Array'.'$defs'
static bool _jm_obj_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Array'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_13 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Array'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_13 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.'$defs'.'']", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_12_map_$defs (.'$Array'.'$defs')
static bool _jm_f_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.'$defs'
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Array'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_12_map_$id (.'$Array'.'$id')
static bool _jm_f_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.'$id']", path);
    }
    return res;
}

// check _jm_obj_12_map_$schema (.'$Array'.'$schema')
static bool _jm_f_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_12_map_additionalItems (.'$Array'.additionalItems)
static bool _jm_f_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.additionalItems
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.additionalItems]", path);
    }
    return res;
}

// check _jm_obj_12_map_default (.'$Array'.default)
static bool _jm_f_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Array'.default]", path);
    }
    return res;
}

// object .'$Array'.definitions
static bool _jm_obj_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Array'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_14 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Array'.definitions.''
        res = json_model_24(pval, (path ? &lpath_14 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.definitions.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_12_map_definitions (.'$Array'.definitions)
static bool _jm_f_44(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.definitions
    res = _jm_obj_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Array'.definitions]", path);
    }
    return res;
}

// check _jm_obj_12_map_description (.'$Array'.description)
static bool _jm_f_45(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.description]", path);
    }
    return res;
}

// check _jm_obj_12_map_examples (.'$Array'.examples)
static bool _jm_f_46(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Array'.examples]", path);
    }
    return res;
}

// check _jm_obj_12_map_id (.'$Array'.id)
static bool _jm_f_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.id]", path);
    }
    return res;
}

// check _jm_obj_12_map_items (.'$Array'.items)
static bool _jm_f_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.items
    // .'$Array'.items.'|'.0
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.items.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Array'.items.'|'.1
        res = json_model_4(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Array'.items.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Array'.items.'|']", path);
    }
    return res;
}

// check _jm_obj_12_map_maxItems (.'$Array'.maxItems)
static bool _jm_f_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_12_map_minItems (.'$Array'.minItems)
static bool _jm_f_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.minItems]", path);
    }
    return res;
}

// check _jm_obj_12_map_prefixItems (.'$Array'.prefixItems)
static bool _jm_f_51(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.prefixItems
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Array'.prefixItems]", path);
    }
    return res;
}

// check _jm_obj_12_map_title (.'$Array'.title)
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Array'.title]", path);
    }
    return res;
}

// check _jm_obj_12_map_uniqueItems (.'$Array'.uniqueItems)
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Array'.uniqueItems]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_12_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_12_map_tab, 16);
}

// object .'$Array'
static bool _jm_obj_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Array']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_12 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Array'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "array") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected array [.'$Array'.type]", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Array'.type]", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_12_map(prop)))
        {
            // handle 16 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_12 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Array']", (path ? &lpath_12 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Array'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Array'.'/^x-.*/']", (path ? &lpath_12 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Array']", (path ? &lpath_12 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Array']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Array (.'$Array')
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Array']", path);
    }
    return res;
}

// check _jm_obj_15_map_$comment (.'$Object'.'$comment')
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.'$comment']", path);
    }
    return res;
}

// object .'$Object'.'$defs'
static bool _jm_obj_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_16 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_16 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.'$defs'.'']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_$defs (.'$Object'.'$defs')
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.'$defs'
    res = _jm_obj_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_15_map_$id (.'$Object'.'$id')
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.'$id']", path);
    }
    return res;
}

// check _jm_obj_15_map_$schema (.'$Object'.'$schema')
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_15_map_additionalProperties (.'$Object'.additionalProperties)
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.additionalProperties
    res = json_model_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_15_map_default (.'$Object'.default)
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Object'.default]", path);
    }
    return res;
}

// object .'$Object'.definitions
static bool _jm_obj_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_17 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.definitions.''
        res = json_model_24(pval, (path ? &lpath_17 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.definitions.'']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_definitions (.'$Object'.definitions)
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.definitions
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.definitions]", path);
    }
    return res;
}

// check _jm_obj_15_map_description (.'$Object'.description)
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.description]", path);
    }
    return res;
}

// check _jm_obj_15_map_examples (.'$Object'.examples)
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Object'.examples]", path);
    }
    return res;
}

// check _jm_obj_15_map_id (.'$Object'.id)
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.id]", path);
    }
    return res;
}

// object .'$Object'.patternProperties
static bool _jm_obj_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_18 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop))
        {
            // handle 1 key props
            // .'$Object'.patternProperties.'$REGEX'
            res = json_model_24(pval, (path ? &lpath_18 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.patternProperties.'$REGEX']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Object'.patternProperties]", (path ? &lpath_18 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_patternProperties (.'$Object'.patternProperties)
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.patternProperties
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.patternProperties]", path);
    }
    return res;
}

// object .'$Object'.properties
static bool _jm_obj_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_19 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.properties.''
        res = json_model_24(pval, (path ? &lpath_19 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.properties.'']", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_properties (.'$Object'.properties)
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.properties
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.properties]", path);
    }
    return res;
}

// check _jm_obj_15_map_required (.'$Object'.required)
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.required
    res = json_is_array(val);
    if (res)
    {
        size_t arr_5_idx;
        json_t *arr_5_item;
        json_array_foreach(val, arr_5_idx, arr_5_item)
        {
            jm_path_t arr_5_lpath = (jm_path_t) { NULL, arr_5_idx, path, NULL };
            // .'$Object'.required.0
            res = json_is_string(arr_5_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.required.0]", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Object'.required]", path);
    }
    return res;
}

// check _jm_obj_15_map_title (.'$Object'.title)
static bool _jm_f_67(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Object'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_15_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_15_map_tab, 14);
}

// object .'$Object'
static bool _jm_obj_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_15 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Object'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "object") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected object [.'$Object'.type]", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Object'.type]", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_15_map(prop)))
        {
            // handle 14 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_15 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Object']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Object'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Object'.'/^x-.*/']", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Object']", (path ? &lpath_15 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Object']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Object (.'$Object')
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object']", path);
    }
    return res;
}

// check _jm_obj_20_map_$comment (.'$Integer'.'$comment')
static bool _jm_f_68(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.'$comment']", path);
    }
    return res;
}

// object .'$Integer'.'$defs'
static bool _jm_obj_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Integer'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_21 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Integer'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_21 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Integer'.'$defs'.'']", (path ? &lpath_21 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_20_map_$defs (.'$Integer'.'$defs')
static bool _jm_f_69(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.'$defs'
    res = _jm_obj_21(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Integer'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_20_map_$id (.'$Integer'.'$id')
static bool _jm_f_70(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.'$id']", path);
    }
    return res;
}

// check _jm_obj_20_map_$schema (.'$Integer'.'$schema')
static bool _jm_f_71(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_20_map_default (.'$Integer'.default)
static bool _jm_f_72(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Integer'.default]", path);
    }
    return res;
}

// object .'$Integer'.definitions
static bool _jm_obj_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Integer'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_22 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Integer'.definitions.''
        res = json_model_24(pval, (path ? &lpath_22 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Integer'.definitions.'']", (path ? &lpath_22 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_20_map_definitions (.'$Integer'.definitions)
static bool _jm_f_73(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.definitions
    res = _jm_obj_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Integer'.definitions]", path);
    }
    return res;
}

// check _jm_obj_20_map_description (.'$Integer'.description)
static bool _jm_f_74(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.description]", path);
    }
    return res;
}

// check _jm_obj_20_map_examples (.'$Integer'.examples)
static bool _jm_f_75(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Integer'.examples]", path);
    }
    return res;
}

// check _jm_obj_20_map_id (.'$Integer'.id)
static bool _jm_f_76(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.id]", path);
    }
    return res;
}

// check _jm_obj_20_map_maximum (.'$Integer'.maximum)
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.maximum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Integer'.maximum]", path);
    }
    return res;
}

// check _jm_obj_20_map_minimum (.'$Integer'.minimum)
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.minimum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Integer'.minimum]", path);
    }
    return res;
}

// check _jm_obj_20_map_title (.'$Integer'.title)
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Integer'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_20_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_20_map_tab, 12);
}

// object .'$Integer'
static bool _jm_obj_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Integer']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_20 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Integer'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected integer [.'$Integer'.type]", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Integer'.type]", (path ? &lpath_20 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_20_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_20 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Integer']", (path ? &lpath_20 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Integer'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Integer'.'/^x-.*/']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Integer']", (path ? &lpath_20 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Integer']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Integer (.'$Integer')
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Integer']", path);
    }
    return res;
}

// check _jm_obj_23_map_$comment (.'$Number'.'$comment')
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.'$comment']", path);
    }
    return res;
}

// object .'$Number'.'$defs'
static bool _jm_obj_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Number'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_24 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Number'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_24 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Number'.'$defs'.'']", (path ? &lpath_24 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_map_$defs (.'$Number'.'$defs')
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.'$defs'
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Number'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_23_map_$id (.'$Number'.'$id')
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.'$id']", path);
    }
    return res;
}

// check _jm_obj_23_map_$schema (.'$Number'.'$schema')
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_23_map_default (.'$Number'.default)
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Number'.default]", path);
    }
    return res;
}

// object .'$Number'.definitions
static bool _jm_obj_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Number'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_25 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Number'.definitions.''
        res = json_model_24(pval, (path ? &lpath_25 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Number'.definitions.'']", (path ? &lpath_25 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_23_map_definitions (.'$Number'.definitions)
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.definitions
    res = _jm_obj_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Number'.definitions]", path);
    }
    return res;
}

// check _jm_obj_23_map_description (.'$Number'.description)
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.description]", path);
    }
    return res;
}

// check _jm_obj_23_map_examples (.'$Number'.examples)
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Number'.examples]", path);
    }
    return res;
}

// check _jm_obj_23_map_id (.'$Number'.id)
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.id]", path);
    }
    return res;
}

// check _jm_obj_23_map_maximum (.'$Number'.maximum)
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.maximum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.maximum]", path);
    }
    return res;
}

// check _jm_obj_23_map_minimum (.'$Number'.minimum)
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.minimum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.minimum]", path);
    }
    return res;
}

// check _jm_obj_23_map_title (.'$Number'.title)
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Number'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_23_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_23_map_tab, 12);
}

// object .'$Number'
static bool _jm_obj_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Number']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_23 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Number'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected number [.'$Number'.type]", (path ? &lpath_23 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Number'.type]", (path ? &lpath_23 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_23_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_23 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Number']", (path ? &lpath_23 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Number'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Number'.'/^x-.*/']", (path ? &lpath_23 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Number']", (path ? &lpath_23 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Number']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Number (.'$Number')
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'
    res = _jm_obj_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Number']", path);
    }
    return res;
}

// check _jm_obj_26_map_$comment (.'$Bool'.'$comment')
static bool _jm_f_92(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.'$comment']", path);
    }
    return res;
}

// object .'$Bool'.'$defs'
static bool _jm_obj_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Bool'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_27 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Bool'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_27 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Bool'.'$defs'.'']", (path ? &lpath_27 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_$defs (.'$Bool'.'$defs')
static bool _jm_f_93(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.'$defs'
    res = _jm_obj_27(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Bool'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_26_map_$id (.'$Bool'.'$id')
static bool _jm_f_94(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.'$id']", path);
    }
    return res;
}

// check _jm_obj_26_map_$schema (.'$Bool'.'$schema')
static bool _jm_f_95(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_26_map_default (.'$Bool'.default)
static bool _jm_f_96(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Bool'.default]", path);
    }
    return res;
}

// object .'$Bool'.definitions
static bool _jm_obj_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Bool'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_28 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Bool'.definitions.''
        res = json_model_24(pval, (path ? &lpath_28 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Bool'.definitions.'']", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_definitions (.'$Bool'.definitions)
static bool _jm_f_97(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.definitions
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Bool'.definitions]", path);
    }
    return res;
}

// check _jm_obj_26_map_description (.'$Bool'.description)
static bool _jm_f_98(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.description]", path);
    }
    return res;
}

// check _jm_obj_26_map_examples (.'$Bool'.examples)
static bool _jm_f_99(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Bool'.examples]", path);
    }
    return res;
}

// check _jm_obj_26_map_id (.'$Bool'.id)
static bool _jm_f_100(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.id]", path);
    }
    return res;
}

// check _jm_obj_26_map_title (.'$Bool'.title)
static bool _jm_f_101(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Bool'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_26_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_26_map_tab, 10);
}

// object .'$Bool'
static bool _jm_obj_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Bool']", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Bool'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "boolean") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected boolean [.'$Bool'.type]", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Bool'.type]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_26_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_26 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Bool']", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Bool'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Bool'.'/^x-.*/']", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Bool']", (path ? &lpath_26 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Bool']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Bool (.'$Bool')
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Bool'
    res = _jm_obj_26(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Bool']", path);
    }
    return res;
}

// check _jm_obj_29_map_$comment (.'$Null'.'$comment')
static bool _jm_f_102(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.'$comment']", path);
    }
    return res;
}

// object .'$Null'.'$defs'
static bool _jm_obj_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Null'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_30 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Null'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_30 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Null'.'$defs'.'']", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_$defs (.'$Null'.'$defs')
static bool _jm_f_103(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.'$defs'
    res = _jm_obj_30(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Null'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_29_map_$id (.'$Null'.'$id')
static bool _jm_f_104(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.'$id']", path);
    }
    return res;
}

// check _jm_obj_29_map_$schema (.'$Null'.'$schema')
static bool _jm_f_105(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_29_map_default (.'$Null'.default)
static bool _jm_f_106(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Null'.default]", path);
    }
    return res;
}

// object .'$Null'.definitions
static bool _jm_obj_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Null'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_31 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Null'.definitions.''
        res = json_model_24(pval, (path ? &lpath_31 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Null'.definitions.'']", (path ? &lpath_31 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_definitions (.'$Null'.definitions)
static bool _jm_f_107(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.definitions
    res = _jm_obj_31(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Null'.definitions]", path);
    }
    return res;
}

// check _jm_obj_29_map_description (.'$Null'.description)
static bool _jm_f_108(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.description]", path);
    }
    return res;
}

// check _jm_obj_29_map_examples (.'$Null'.examples)
static bool _jm_f_109(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Null'.examples]", path);
    }
    return res;
}

// check _jm_obj_29_map_id (.'$Null'.id)
static bool _jm_f_110(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.id]", path);
    }
    return res;
}

// check _jm_obj_29_map_title (.'$Null'.title)
static bool _jm_f_111(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Null'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_29_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_29_map_tab, 10);
}

// object .'$Null'
static bool _jm_obj_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Null']", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Null'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "null") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected null [.'$Null'.type]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Null'.type]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_29_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_29 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Null']", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Null'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Null'.'/^x-.*/']", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Null']", (path ? &lpath_29 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Null']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Null (.'$Null')
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'
    res = _jm_obj_29(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Null']", path);
    }
    return res;
}

// check _jm_obj_32_map_$comment (.'$AllOf'.'$comment')
static bool _jm_f_112(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.'$comment']", path);
    }
    return res;
}

// object .'$AllOf'.'$defs'
static bool _jm_obj_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AllOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_33 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$AllOf'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_33 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$AllOf'.'$defs'.'']", (path ? &lpath_33 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_$defs (.'$AllOf'.'$defs')
static bool _jm_f_113(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.'$defs'
    res = _jm_obj_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AllOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_32_map_$id (.'$AllOf'.'$id')
static bool _jm_f_114(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_32_map_$schema (.'$AllOf'.'$schema')
static bool _jm_f_115(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_32_map_default (.'$AllOf'.default)
static bool _jm_f_116(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$AllOf'.default]", path);
    }
    return res;
}

// object .'$AllOf'.definitions
static bool _jm_obj_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AllOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_34 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$AllOf'.definitions.''
        res = json_model_24(pval, (path ? &lpath_34 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$AllOf'.definitions.'']", (path ? &lpath_34 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_definitions (.'$AllOf'.definitions)
static bool _jm_f_117(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.definitions
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AllOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_32_map_description (.'$AllOf'.description)
static bool _jm_f_118(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.description]", path);
    }
    return res;
}

// check _jm_obj_32_map_examples (.'$AllOf'.examples)
static bool _jm_f_119(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$AllOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_32_map_id (.'$AllOf'.id)
static bool _jm_f_120(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.id]", path);
    }
    return res;
}

// check _jm_obj_32_map_title (.'$AllOf'.title)
static bool _jm_f_121(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AllOf'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_32_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_32_map_tab, 10);
}

// object .'$AllOf'
static bool _jm_obj_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AllOf']", path);
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
        if (strcmp(prop, "allOf") == 0)
        {
            // handle must allOf property
            must_count += 1;
            // .'$AllOf'.allOf
            res = json_model_4(pval, (path ? &lpath_32 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$AllOf'.allOf]", (path ? &lpath_32 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$AllOf'.allOf]", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_32_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_32 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$AllOf']", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$AllOf'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$AllOf'.'/^x-.*/']", (path ? &lpath_32 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$AllOf']", (path ? &lpath_32 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "allOf") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <allOf> [.'$AllOf']", path);
            }
        }
        return false;
    }
    return true;
}

// check $AllOf (.'$AllOf')
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AllOf'
    res = _jm_obj_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AllOf']", path);
    }
    return res;
}

// check _jm_obj_35_map_$comment (.'$AnyOf'.'$comment')
static bool _jm_f_122(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.'$comment']", path);
    }
    return res;
}

// object .'$AnyOf'.'$defs'
static bool _jm_obj_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AnyOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_36 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$AnyOf'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_36 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$AnyOf'.'$defs'.'']", (path ? &lpath_36 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_$defs (.'$AnyOf'.'$defs')
static bool _jm_f_123(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.'$defs'
    res = _jm_obj_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AnyOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_35_map_$id (.'$AnyOf'.'$id')
static bool _jm_f_124(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_35_map_$schema (.'$AnyOf'.'$schema')
static bool _jm_f_125(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_35_map_default (.'$AnyOf'.default)
static bool _jm_f_126(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$AnyOf'.default]", path);
    }
    return res;
}

// object .'$AnyOf'.definitions
static bool _jm_obj_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AnyOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_37 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$AnyOf'.definitions.''
        res = json_model_24(pval, (path ? &lpath_37 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$AnyOf'.definitions.'']", (path ? &lpath_37 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_definitions (.'$AnyOf'.definitions)
static bool _jm_f_127(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.definitions
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AnyOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_35_map_description (.'$AnyOf'.description)
static bool _jm_f_128(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.description]", path);
    }
    return res;
}

// check _jm_obj_35_map_examples (.'$AnyOf'.examples)
static bool _jm_f_129(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$AnyOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_35_map_id (.'$AnyOf'.id)
static bool _jm_f_130(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.id]", path);
    }
    return res;
}

// check _jm_obj_35_map_title (.'$AnyOf'.title)
static bool _jm_f_131(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$AnyOf'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_35_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_35_map_tab, 10);
}

// object .'$AnyOf'
static bool _jm_obj_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$AnyOf']", path);
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
        if (strcmp(prop, "anyOf") == 0)
        {
            // handle must anyOf property
            must_count += 1;
            // .'$AnyOf'.anyOf
            res = json_model_4(pval, (path ? &lpath_35 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$AnyOf'.anyOf]", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$AnyOf'.anyOf]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_35_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_35 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$AnyOf']", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$AnyOf'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$AnyOf'.'/^x-.*/']", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$AnyOf']", (path ? &lpath_35 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "anyOf") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <anyOf> [.'$AnyOf']", path);
            }
        }
        return false;
    }
    return true;
}

// check $AnyOf (.'$AnyOf')
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$AnyOf'
    res = _jm_obj_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$AnyOf']", path);
    }
    return res;
}

// check _jm_obj_38_map_$comment (.'$OneOf'.'$comment')
static bool _jm_f_132(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.'$comment']", path);
    }
    return res;
}

// object .'$OneOf'.'$defs'
static bool _jm_obj_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OneOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_39 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$OneOf'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_39 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$OneOf'.'$defs'.'']", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_$defs (.'$OneOf'.'$defs')
static bool _jm_f_133(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.'$defs'
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OneOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_38_map_$id (.'$OneOf'.'$id')
static bool _jm_f_134(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_38_map_$schema (.'$OneOf'.'$schema')
static bool _jm_f_135(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_38_map_default (.'$OneOf'.default)
static bool _jm_f_136(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$OneOf'.default]", path);
    }
    return res;
}

// object .'$OneOf'.definitions
static bool _jm_obj_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OneOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_40 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$OneOf'.definitions.''
        res = json_model_24(pval, (path ? &lpath_40 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$OneOf'.definitions.'']", (path ? &lpath_40 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_definitions (.'$OneOf'.definitions)
static bool _jm_f_137(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.definitions
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OneOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_38_map_description (.'$OneOf'.description)
static bool _jm_f_138(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.description]", path);
    }
    return res;
}

// check _jm_obj_38_map_examples (.'$OneOf'.examples)
static bool _jm_f_139(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$OneOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_38_map_id (.'$OneOf'.id)
static bool _jm_f_140(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.id]", path);
    }
    return res;
}

// check _jm_obj_38_map_title (.'$OneOf'.title)
static bool _jm_f_141(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$OneOf'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_38_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_38_map_tab, 10);
}

// object .'$OneOf'
static bool _jm_obj_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OneOf']", path);
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
        if (strcmp(prop, "oneOf") == 0)
        {
            // handle must oneOf property
            must_count += 1;
            // .'$OneOf'.oneOf
            res = json_model_4(pval, (path ? &lpath_38 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$OneOf'.oneOf]", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OneOf'.oneOf]", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_38_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_38 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$OneOf']", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$OneOf'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$OneOf'.'/^x-.*/']", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$OneOf']", (path ? &lpath_38 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "oneOf") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <oneOf> [.'$OneOf']", path);
            }
        }
        return false;
    }
    return true;
}

// check $OneOf (.'$OneOf')
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OneOf'
    res = _jm_obj_38(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OneOf']", path);
    }
    return res;
}

// check _jm_obj_41_map_$comment (.'$Enum'.'$comment')
static bool _jm_f_142(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.'$comment']", path);
    }
    return res;
}

// object .'$Enum'.'$defs'
static bool _jm_obj_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Enum'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_42 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Enum'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_42 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Enum'.'$defs'.'']", (path ? &lpath_42 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_41_map_$defs (.'$Enum'.'$defs')
static bool _jm_f_143(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.'$defs'
    res = _jm_obj_42(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Enum'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_41_map_$id (.'$Enum'.'$id')
static bool _jm_f_144(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.'$id']", path);
    }
    return res;
}

// check _jm_obj_41_map_$schema (.'$Enum'.'$schema')
static bool _jm_f_145(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_41_map_default (.'$Enum'.default)
static bool _jm_f_146(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Enum'.default]", path);
    }
    return res;
}

// object .'$Enum'.definitions
static bool _jm_obj_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Enum'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_43 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Enum'.definitions.''
        res = json_model_24(pval, (path ? &lpath_43 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Enum'.definitions.'']", (path ? &lpath_43 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_41_map_definitions (.'$Enum'.definitions)
static bool _jm_f_147(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.definitions
    res = _jm_obj_43(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Enum'.definitions]", path);
    }
    return res;
}

// check _jm_obj_41_map_description (.'$Enum'.description)
static bool _jm_f_148(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.description]", path);
    }
    return res;
}

// check _jm_obj_41_map_examples (.'$Enum'.examples)
static bool _jm_f_149(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Enum'.examples]", path);
    }
    return res;
}

// check _jm_obj_41_map_id (.'$Enum'.id)
static bool _jm_f_150(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.id]", path);
    }
    return res;
}

// check _jm_obj_41_map_title (.'$Enum'.title)
static bool _jm_f_151(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Enum'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_41_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_41_map_tab, 10);
}

// object .'$Enum'
static bool _jm_obj_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Enum']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_41 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "enum") == 0)
        {
            // handle must enum property
            must_count += 1;
            // .'$Enum'.enum
            res = json_model_3(pval, (path ? &lpath_41 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $enum [.'$Enum'.enum]", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Enum'.enum]", (path ? &lpath_41 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_41_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_41 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Enum']", (path ? &lpath_41 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Enum'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Enum'.'/^x-.*/']", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Enum']", (path ? &lpath_41 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "enum") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <enum> [.'$Enum']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Enum (.'$Enum')
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Enum'
    res = _jm_obj_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Enum']", path);
    }
    return res;
}

// check _jm_obj_44_map_$comment (.'$Const'.'$comment')
static bool _jm_f_152(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.'$comment']", path);
    }
    return res;
}

// object .'$Const'.'$defs'
static bool _jm_obj_45(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Const'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_45 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Const'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_45 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Const'.'$defs'.'']", (path ? &lpath_45 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_44_map_$defs (.'$Const'.'$defs')
static bool _jm_f_153(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.'$defs'
    res = _jm_obj_45(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Const'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_44_map_$id (.'$Const'.'$id')
static bool _jm_f_154(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.'$id']", path);
    }
    return res;
}

// check _jm_obj_44_map_$schema (.'$Const'.'$schema')
static bool _jm_f_155(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_44_map_default (.'$Const'.default)
static bool _jm_f_156(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Const'.default]", path);
    }
    return res;
}

// object .'$Const'.definitions
static bool _jm_obj_46(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Const'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_46 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Const'.definitions.''
        res = json_model_24(pval, (path ? &lpath_46 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Const'.definitions.'']", (path ? &lpath_46 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_44_map_definitions (.'$Const'.definitions)
static bool _jm_f_157(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.definitions
    res = _jm_obj_46(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Const'.definitions]", path);
    }
    return res;
}

// check _jm_obj_44_map_description (.'$Const'.description)
static bool _jm_f_158(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.description]", path);
    }
    return res;
}

// check _jm_obj_44_map_examples (.'$Const'.examples)
static bool _jm_f_159(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Const'.examples]", path);
    }
    return res;
}

// check _jm_obj_44_map_id (.'$Const'.id)
static bool _jm_f_160(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.id]", path);
    }
    return res;
}

// check _jm_obj_44_map_title (.'$Const'.title)
static bool _jm_f_161(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Const'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_44_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_44_map_tab, 10);
}

// object .'$Const'
static bool _jm_obj_44(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Const']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_44 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // .'$Const'.const
            res = json_model_2(pval, (path ? &lpath_44 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $const [.'$Const'.const]", (path ? &lpath_44 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Const'.const]", (path ? &lpath_44 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_44_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_44 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Const']", (path ? &lpath_44 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Const'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Const'.'/^x-.*/']", (path ? &lpath_44 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Const']", (path ? &lpath_44 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "const") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <const> [.'$Const']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Const (.'$Const')
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Const'
    res = _jm_obj_44(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Const']", path);
    }
    return res;
}

// check _jm_obj_47_map_$comment (.'$Ref'.'$comment')
static bool _jm_f_162(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.'$comment']", path);
    }
    return res;
}

// object .'$Ref'.'$defs'
static bool _jm_obj_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Ref'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_48 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Ref'.'$defs'.''
        res = json_model_24(pval, (path ? &lpath_48 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Ref'.'$defs'.'']", (path ? &lpath_48 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_47_map_$defs (.'$Ref'.'$defs')
static bool _jm_f_163(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.'$defs'
    res = _jm_obj_48(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Ref'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_47_map_$id (.'$Ref'.'$id')
static bool _jm_f_164(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.'$id'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.'$id']", path);
    }
    return res;
}

// check _jm_obj_47_map_$schema (.'$Ref'.'$schema')
static bool _jm_f_165(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.'$schema'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_47_map_default (.'$Ref'.default)
static bool _jm_f_166(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Ref'.default]", path);
    }
    return res;
}

// object .'$Ref'.definitions
static bool _jm_obj_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Ref'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_49 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Ref'.definitions.''
        res = json_model_24(pval, (path ? &lpath_49 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Ref'.definitions.'']", (path ? &lpath_49 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_47_map_definitions (.'$Ref'.definitions)
static bool _jm_f_167(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.definitions
    res = _jm_obj_49(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Ref'.definitions]", path);
    }
    return res;
}

// check _jm_obj_47_map_description (.'$Ref'.description)
static bool _jm_f_168(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.description]", path);
    }
    return res;
}

// check _jm_obj_47_map_examples (.'$Ref'.examples)
static bool _jm_f_169(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Ref'.examples]", path);
    }
    return res;
}

// check _jm_obj_47_map_id (.'$Ref'.id)
static bool _jm_f_170(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.id
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.id]", path);
    }
    return res;
}

// check _jm_obj_47_map_title (.'$Ref'.title)
static bool _jm_f_171(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Ref'.title]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_47_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_47_map_tab, 10);
}

// object .'$Ref'
static bool _jm_obj_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Ref']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_47 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "$ref") == 0)
        {
            // handle must $ref property
            must_count += 1;
            // .'$Ref'.'$ref'
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$Ref'.'$ref']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Ref'.'$ref']", (path ? &lpath_47 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_47_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_47 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Ref']", (path ? &lpath_47 : NULL));
                return false;
            }
        }
        else if (_jm_re_0(prop))
        {
            // handle 1 re props
            // .'$Ref'.'/^x-.*/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Ref'.'/^x-.*/']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Ref']", (path ? &lpath_47 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "$ref") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <$ref> [.'$Ref']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Ref (.'$Ref')
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Ref'
    res = _jm_obj_47(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Ref']", path);
    }
    return res;
}

// check $ObjectSchema (.'$ObjectSchema')
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ObjectSchema'
    // .'$ObjectSchema'.'|'.0
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Null [.'$ObjectSchema'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$ObjectSchema'.'|'.1
        res = json_model_15(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Bool [.'$ObjectSchema'.'|'.1]", path);
        }
        if (! res)
        {
            // .'$ObjectSchema'.'|'.2
            res = json_model_21(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Const [.'$ObjectSchema'.'|'.2]", path);
            }
            if (! res)
            {
                // .'$ObjectSchema'.'|'.3
                res = json_model_20(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Enum [.'$ObjectSchema'.'|'.3]", path);
                }
                if (! res)
                {
                    // .'$ObjectSchema'.'|'.4
                    res = json_model_13(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Integer [.'$ObjectSchema'.'|'.4]", path);
                    }
                    if (! res)
                    {
                        // .'$ObjectSchema'.'|'.5
                        res = json_model_14(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "unexpected $Number [.'$ObjectSchema'.'|'.5]", path);
                        }
                        if (! res)
                        {
                            // .'$ObjectSchema'.'|'.6
                            res = json_model_10(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "unexpected $String [.'$ObjectSchema'.'|'.6]", path);
                            }
                            if (! res)
                            {
                                // .'$ObjectSchema'.'|'.7
                                res = json_model_11(val, path, rep);
                                if (! res)
                                {
                                    if (rep) jm_report_add_entry(rep, "unexpected $Array [.'$ObjectSchema'.'|'.7]", path);
                                }
                                if (! res)
                                {
                                    // .'$ObjectSchema'.'|'.8
                                    res = json_model_12(val, path, rep);
                                    if (! res)
                                    {
                                        if (rep) jm_report_add_entry(rep, "unexpected $Object [.'$ObjectSchema'.'|'.8]", path);
                                    }
                                    if (! res)
                                    {
                                        // .'$ObjectSchema'.'|'.9
                                        res = json_model_17(val, path, rep);
                                        if (! res)
                                        {
                                            if (rep) jm_report_add_entry(rep, "unexpected $AllOf [.'$ObjectSchema'.'|'.9]", path);
                                        }
                                        if (! res)
                                        {
                                            // .'$ObjectSchema'.'|'.10
                                            res = json_model_18(val, path, rep);
                                            if (! res)
                                            {
                                                if (rep) jm_report_add_entry(rep, "unexpected $AnyOf [.'$ObjectSchema'.'|'.10]", path);
                                            }
                                            if (! res)
                                            {
                                                // .'$ObjectSchema'.'|'.11
                                                res = json_model_19(val, path, rep);
                                                if (! res)
                                                {
                                                    if (rep) jm_report_add_entry(rep, "unexpected $OneOf [.'$ObjectSchema'.'|'.11]", path);
                                                }
                                                if (! res)
                                                {
                                                    // .'$ObjectSchema'.'|'.12
                                                    res = json_model_22(val, path, rep);
                                                    if (! res)
                                                    {
                                                        if (rep) jm_report_add_entry(rep, "unexpected $Ref [.'$ObjectSchema'.'|'.12]", path);
                                                    }
                                                    if (! res)
                                                    {
                                                        // .'$ObjectSchema'.'|'.13
                                                        res = json_model_9(val, path, rep);
                                                        if (! res)
                                                        {
                                                            if (rep) jm_report_add_entry(rep, "unexpected $metas [.'$ObjectSchema'.'|'.13]", path);
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
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
        if (rep) jm_report_add_entry(rep, "no model matched [.'$ObjectSchema'.'|']", path);
    }
    return res;
}

// check $Schema (.'$Schema')
static bool json_model_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'
    // .'$Schema'.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Schema'.'|'.1
        res = json_model_23(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [.'$Schema'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Schema'.'|']", path);
    }
    return res;
}

// object .'$RootSchema'.'&'.0
static bool _jm_obj_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RootSchema'.'&'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_50 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "$schema") == 0)
        {
            // handle must $schema property
            must_count += 1;
            // .'$RootSchema'.'&'.0.'$schema'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$RootSchema'.'&'.0.'$schema']", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$RootSchema'.'&'.0.'$schema']", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else
        {
            // accept any other props
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "$schema") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <$schema> [.'$RootSchema'.'&'.0.'']", path);
            }
        }
        return false;
    }
    return true;
}

// check $RootSchema (.'$RootSchema')
static bool json_model_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$RootSchema'
    res = true;
    if (res)
    {
        // .'$RootSchema'.'&'.0
        res = _jm_obj_50(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$RootSchema'.'&'.0]", path);
        }
        if (res)
        {
            // .'$RootSchema'.'&'.1
            res = json_model_23(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [.'$RootSchema'.'&'.1]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not all model match [.'$RootSchema'.'&']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RootSchema [.]", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 25);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (jm_constant_t) { cst_is_string, { .s = "uri" } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_string, { .s = "uri-reference" } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_string, { .s = "iri" } };
        _jm_cst_0[3] = (jm_constant_t) { cst_is_string, { .s = "iri-reference" } };
        _jm_cst_0[4] = (jm_constant_t) { cst_is_string, { .s = "date" } };
        _jm_cst_0[5] = (jm_constant_t) { cst_is_string, { .s = "time" } };
        _jm_cst_0[6] = (jm_constant_t) { cst_is_string, { .s = "date-time" } };
        _jm_cst_0[7] = (jm_constant_t) { cst_is_string, { .s = "ipv4" } };
        _jm_cst_0[8] = (jm_constant_t) { cst_is_string, { .s = "ipv6" } };
        _jm_cst_0[9] = (jm_constant_t) { cst_is_string, { .s = "regex" } };
        _jm_cst_0[10] = (jm_constant_t) { cst_is_string, { .s = "uuid" } };
        _jm_cst_0[11] = (jm_constant_t) { cst_is_string, { .s = "hostname" } };
        _jm_cst_0[12] = (jm_constant_t) { cst_is_string, { .s = "email" } };
        _jm_cst_0[13] = (jm_constant_t) { cst_is_string, { .s = "idn-hostname" } };
        _jm_cst_0[14] = (jm_constant_t) { cst_is_string, { .s = "idn-email" } };
        _jm_cst_0[15] = (jm_constant_t) { cst_is_string, { .s = "duration" } };
        _jm_cst_0[16] = (jm_constant_t) { cst_is_string, { .s = "int32" } };
        _jm_cst_0[17] = (jm_constant_t) { cst_is_string, { .s = "int64" } };
        _jm_cst_0[18] = (jm_constant_t) { cst_is_string, { .s = "uint" } };
        _jm_cst_0[19] = (jm_constant_t) { cst_is_string, { .s = "uint32" } };
        _jm_cst_0[20] = (jm_constant_t) { cst_is_string, { .s = "uint64" } };
        _jm_cst_0[21] = (jm_constant_t) { cst_is_string, { .s = "json-pointer" } };
        _jm_cst_0[22] = (jm_constant_t) { cst_is_string, { .s = "relative-json-pointer" } };
        _jm_cst_0[23] = (jm_constant_t) { cst_is_string, { .s = "byte" } };
        _jm_cst_0[24] = (jm_constant_t) { cst_is_string, { .s = "double" } };
        _jm_cst_0[25] = (jm_constant_t) { cst_is_string, { .s = "int" } };
        _jm_cst_0[26] = (jm_constant_t) { cst_is_string, { .s = "mime-type" } };
        jm_sort_cst(_jm_cst_0, 27);
        _jm_obj_0_map_tab[0] = (jm_propmap_t) { "format", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (jm_propmap_t) { "maxLength", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (jm_propmap_t) { "minLength", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (jm_propmap_t) { "pattern", _jm_f_3 };
        jm_sort_propmap(_jm_obj_0_map_tab, 4);
        _jm_obj_1_map_tab[0] = (jm_propmap_t) { "additionalItems", _jm_f_4 };
        _jm_obj_1_map_tab[1] = (jm_propmap_t) { "items", _jm_f_5 };
        _jm_obj_1_map_tab[2] = (jm_propmap_t) { "maxItems", _jm_f_6 };
        _jm_obj_1_map_tab[3] = (jm_propmap_t) { "minItems", _jm_f_7 };
        _jm_obj_1_map_tab[4] = (jm_propmap_t) { "prefixItems", _jm_f_8 };
        _jm_obj_1_map_tab[5] = (jm_propmap_t) { "uniqueItems", _jm_f_9 };
        jm_sort_propmap(_jm_obj_1_map_tab, 6);
        _jm_obj_2_map_tab[0] = (jm_propmap_t) { "additionalProperties", _jm_f_10 };
        _jm_obj_2_map_tab[1] = (jm_propmap_t) { "patternProperties", _jm_f_11 };
        _jm_obj_2_map_tab[2] = (jm_propmap_t) { "properties", _jm_f_12 };
        _jm_obj_2_map_tab[3] = (jm_propmap_t) { "required", _jm_f_13 };
        jm_sort_propmap(_jm_obj_2_map_tab, 4);
        _jm_obj_6_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_14 };
        _jm_obj_6_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_15 };
        _jm_obj_6_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_16 };
        _jm_obj_6_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_17 };
        _jm_obj_6_map_tab[4] = (jm_propmap_t) { "default", _jm_f_18 };
        _jm_obj_6_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_19 };
        _jm_obj_6_map_tab[6] = (jm_propmap_t) { "description", _jm_f_20 };
        _jm_obj_6_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_21 };
        _jm_obj_6_map_tab[8] = (jm_propmap_t) { "id", _jm_f_22 };
        _jm_obj_6_map_tab[9] = (jm_propmap_t) { "title", _jm_f_23 };
        jm_sort_propmap(_jm_obj_6_map_tab, 10);
        int err_code;
        PCRE2_SIZE err_offset;
        static PCRE2_UCHAR err_message[1024];
        _jm_re_0_code = pcre2_compile((PCRE2_SPTR) "^x-.*", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_0_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_0_data = pcre2_match_data_create_from_pattern(_jm_re_0_code, NULL);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (jm_constant_t) { cst_is_string, { .s = "uri" } };
        _jm_cst_1[1] = (jm_constant_t) { cst_is_string, { .s = "uri-reference" } };
        _jm_cst_1[2] = (jm_constant_t) { cst_is_string, { .s = "iri" } };
        _jm_cst_1[3] = (jm_constant_t) { cst_is_string, { .s = "iri-reference" } };
        _jm_cst_1[4] = (jm_constant_t) { cst_is_string, { .s = "date" } };
        _jm_cst_1[5] = (jm_constant_t) { cst_is_string, { .s = "time" } };
        _jm_cst_1[6] = (jm_constant_t) { cst_is_string, { .s = "date-time" } };
        _jm_cst_1[7] = (jm_constant_t) { cst_is_string, { .s = "ipv4" } };
        _jm_cst_1[8] = (jm_constant_t) { cst_is_string, { .s = "ipv6" } };
        _jm_cst_1[9] = (jm_constant_t) { cst_is_string, { .s = "regex" } };
        _jm_cst_1[10] = (jm_constant_t) { cst_is_string, { .s = "uuid" } };
        _jm_cst_1[11] = (jm_constant_t) { cst_is_string, { .s = "hostname" } };
        _jm_cst_1[12] = (jm_constant_t) { cst_is_string, { .s = "email" } };
        _jm_cst_1[13] = (jm_constant_t) { cst_is_string, { .s = "idn-hostname" } };
        _jm_cst_1[14] = (jm_constant_t) { cst_is_string, { .s = "idn-email" } };
        _jm_cst_1[15] = (jm_constant_t) { cst_is_string, { .s = "duration" } };
        _jm_cst_1[16] = (jm_constant_t) { cst_is_string, { .s = "int32" } };
        _jm_cst_1[17] = (jm_constant_t) { cst_is_string, { .s = "int64" } };
        _jm_cst_1[18] = (jm_constant_t) { cst_is_string, { .s = "uint" } };
        _jm_cst_1[19] = (jm_constant_t) { cst_is_string, { .s = "uint32" } };
        _jm_cst_1[20] = (jm_constant_t) { cst_is_string, { .s = "uint64" } };
        _jm_cst_1[21] = (jm_constant_t) { cst_is_string, { .s = "json-pointer" } };
        _jm_cst_1[22] = (jm_constant_t) { cst_is_string, { .s = "relative-json-pointer" } };
        _jm_cst_1[23] = (jm_constant_t) { cst_is_string, { .s = "byte" } };
        _jm_cst_1[24] = (jm_constant_t) { cst_is_string, { .s = "double" } };
        _jm_cst_1[25] = (jm_constant_t) { cst_is_string, { .s = "int" } };
        _jm_cst_1[26] = (jm_constant_t) { cst_is_string, { .s = "mime-type" } };
        jm_sort_cst(_jm_cst_1, 27);
        _jm_obj_9_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_24 };
        _jm_obj_9_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_25 };
        _jm_obj_9_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_26 };
        _jm_obj_9_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_27 };
        _jm_obj_9_map_tab[4] = (jm_propmap_t) { "default", _jm_f_28 };
        _jm_obj_9_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_29 };
        _jm_obj_9_map_tab[6] = (jm_propmap_t) { "description", _jm_f_30 };
        _jm_obj_9_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_31 };
        _jm_obj_9_map_tab[8] = (jm_propmap_t) { "format", _jm_f_32 };
        _jm_obj_9_map_tab[9] = (jm_propmap_t) { "id", _jm_f_33 };
        _jm_obj_9_map_tab[10] = (jm_propmap_t) { "maxLength", _jm_f_34 };
        _jm_obj_9_map_tab[11] = (jm_propmap_t) { "minLength", _jm_f_35 };
        _jm_obj_9_map_tab[12] = (jm_propmap_t) { "pattern", _jm_f_36 };
        _jm_obj_9_map_tab[13] = (jm_propmap_t) { "title", _jm_f_37 };
        jm_sort_propmap(_jm_obj_9_map_tab, 14);
        _jm_obj_12_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_38 };
        _jm_obj_12_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_39 };
        _jm_obj_12_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_40 };
        _jm_obj_12_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_41 };
        _jm_obj_12_map_tab[4] = (jm_propmap_t) { "additionalItems", _jm_f_42 };
        _jm_obj_12_map_tab[5] = (jm_propmap_t) { "default", _jm_f_43 };
        _jm_obj_12_map_tab[6] = (jm_propmap_t) { "definitions", _jm_f_44 };
        _jm_obj_12_map_tab[7] = (jm_propmap_t) { "description", _jm_f_45 };
        _jm_obj_12_map_tab[8] = (jm_propmap_t) { "examples", _jm_f_46 };
        _jm_obj_12_map_tab[9] = (jm_propmap_t) { "id", _jm_f_47 };
        _jm_obj_12_map_tab[10] = (jm_propmap_t) { "items", _jm_f_48 };
        _jm_obj_12_map_tab[11] = (jm_propmap_t) { "maxItems", _jm_f_49 };
        _jm_obj_12_map_tab[12] = (jm_propmap_t) { "minItems", _jm_f_50 };
        _jm_obj_12_map_tab[13] = (jm_propmap_t) { "prefixItems", _jm_f_51 };
        _jm_obj_12_map_tab[14] = (jm_propmap_t) { "title", _jm_f_52 };
        _jm_obj_12_map_tab[15] = (jm_propmap_t) { "uniqueItems", _jm_f_53 };
        jm_sort_propmap(_jm_obj_12_map_tab, 16);
        _jm_obj_15_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_54 };
        _jm_obj_15_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_55 };
        _jm_obj_15_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_56 };
        _jm_obj_15_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_57 };
        _jm_obj_15_map_tab[4] = (jm_propmap_t) { "additionalProperties", _jm_f_58 };
        _jm_obj_15_map_tab[5] = (jm_propmap_t) { "default", _jm_f_59 };
        _jm_obj_15_map_tab[6] = (jm_propmap_t) { "definitions", _jm_f_60 };
        _jm_obj_15_map_tab[7] = (jm_propmap_t) { "description", _jm_f_61 };
        _jm_obj_15_map_tab[8] = (jm_propmap_t) { "examples", _jm_f_62 };
        _jm_obj_15_map_tab[9] = (jm_propmap_t) { "id", _jm_f_63 };
        _jm_obj_15_map_tab[10] = (jm_propmap_t) { "patternProperties", _jm_f_64 };
        _jm_obj_15_map_tab[11] = (jm_propmap_t) { "properties", _jm_f_65 };
        _jm_obj_15_map_tab[12] = (jm_propmap_t) { "required", _jm_f_66 };
        _jm_obj_15_map_tab[13] = (jm_propmap_t) { "title", _jm_f_67 };
        jm_sort_propmap(_jm_obj_15_map_tab, 14);
        _jm_obj_20_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_68 };
        _jm_obj_20_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_69 };
        _jm_obj_20_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_70 };
        _jm_obj_20_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_71 };
        _jm_obj_20_map_tab[4] = (jm_propmap_t) { "default", _jm_f_72 };
        _jm_obj_20_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_73 };
        _jm_obj_20_map_tab[6] = (jm_propmap_t) { "description", _jm_f_74 };
        _jm_obj_20_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_75 };
        _jm_obj_20_map_tab[8] = (jm_propmap_t) { "id", _jm_f_76 };
        _jm_obj_20_map_tab[9] = (jm_propmap_t) { "maximum", _jm_f_77 };
        _jm_obj_20_map_tab[10] = (jm_propmap_t) { "minimum", _jm_f_78 };
        _jm_obj_20_map_tab[11] = (jm_propmap_t) { "title", _jm_f_79 };
        jm_sort_propmap(_jm_obj_20_map_tab, 12);
        _jm_obj_23_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_80 };
        _jm_obj_23_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_81 };
        _jm_obj_23_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_82 };
        _jm_obj_23_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_83 };
        _jm_obj_23_map_tab[4] = (jm_propmap_t) { "default", _jm_f_84 };
        _jm_obj_23_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_85 };
        _jm_obj_23_map_tab[6] = (jm_propmap_t) { "description", _jm_f_86 };
        _jm_obj_23_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_87 };
        _jm_obj_23_map_tab[8] = (jm_propmap_t) { "id", _jm_f_88 };
        _jm_obj_23_map_tab[9] = (jm_propmap_t) { "maximum", _jm_f_89 };
        _jm_obj_23_map_tab[10] = (jm_propmap_t) { "minimum", _jm_f_90 };
        _jm_obj_23_map_tab[11] = (jm_propmap_t) { "title", _jm_f_91 };
        jm_sort_propmap(_jm_obj_23_map_tab, 12);
        _jm_obj_26_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_92 };
        _jm_obj_26_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_93 };
        _jm_obj_26_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_94 };
        _jm_obj_26_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_95 };
        _jm_obj_26_map_tab[4] = (jm_propmap_t) { "default", _jm_f_96 };
        _jm_obj_26_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_97 };
        _jm_obj_26_map_tab[6] = (jm_propmap_t) { "description", _jm_f_98 };
        _jm_obj_26_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_99 };
        _jm_obj_26_map_tab[8] = (jm_propmap_t) { "id", _jm_f_100 };
        _jm_obj_26_map_tab[9] = (jm_propmap_t) { "title", _jm_f_101 };
        jm_sort_propmap(_jm_obj_26_map_tab, 10);
        _jm_obj_29_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_102 };
        _jm_obj_29_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_103 };
        _jm_obj_29_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_104 };
        _jm_obj_29_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_105 };
        _jm_obj_29_map_tab[4] = (jm_propmap_t) { "default", _jm_f_106 };
        _jm_obj_29_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_107 };
        _jm_obj_29_map_tab[6] = (jm_propmap_t) { "description", _jm_f_108 };
        _jm_obj_29_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_109 };
        _jm_obj_29_map_tab[8] = (jm_propmap_t) { "id", _jm_f_110 };
        _jm_obj_29_map_tab[9] = (jm_propmap_t) { "title", _jm_f_111 };
        jm_sort_propmap(_jm_obj_29_map_tab, 10);
        _jm_obj_32_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_112 };
        _jm_obj_32_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_113 };
        _jm_obj_32_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_114 };
        _jm_obj_32_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_115 };
        _jm_obj_32_map_tab[4] = (jm_propmap_t) { "default", _jm_f_116 };
        _jm_obj_32_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_117 };
        _jm_obj_32_map_tab[6] = (jm_propmap_t) { "description", _jm_f_118 };
        _jm_obj_32_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_119 };
        _jm_obj_32_map_tab[8] = (jm_propmap_t) { "id", _jm_f_120 };
        _jm_obj_32_map_tab[9] = (jm_propmap_t) { "title", _jm_f_121 };
        jm_sort_propmap(_jm_obj_32_map_tab, 10);
        _jm_obj_35_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_122 };
        _jm_obj_35_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_123 };
        _jm_obj_35_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_124 };
        _jm_obj_35_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_125 };
        _jm_obj_35_map_tab[4] = (jm_propmap_t) { "default", _jm_f_126 };
        _jm_obj_35_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_127 };
        _jm_obj_35_map_tab[6] = (jm_propmap_t) { "description", _jm_f_128 };
        _jm_obj_35_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_129 };
        _jm_obj_35_map_tab[8] = (jm_propmap_t) { "id", _jm_f_130 };
        _jm_obj_35_map_tab[9] = (jm_propmap_t) { "title", _jm_f_131 };
        jm_sort_propmap(_jm_obj_35_map_tab, 10);
        _jm_obj_38_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_132 };
        _jm_obj_38_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_133 };
        _jm_obj_38_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_134 };
        _jm_obj_38_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_135 };
        _jm_obj_38_map_tab[4] = (jm_propmap_t) { "default", _jm_f_136 };
        _jm_obj_38_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_137 };
        _jm_obj_38_map_tab[6] = (jm_propmap_t) { "description", _jm_f_138 };
        _jm_obj_38_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_139 };
        _jm_obj_38_map_tab[8] = (jm_propmap_t) { "id", _jm_f_140 };
        _jm_obj_38_map_tab[9] = (jm_propmap_t) { "title", _jm_f_141 };
        jm_sort_propmap(_jm_obj_38_map_tab, 10);
        _jm_obj_41_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_142 };
        _jm_obj_41_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_143 };
        _jm_obj_41_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_144 };
        _jm_obj_41_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_145 };
        _jm_obj_41_map_tab[4] = (jm_propmap_t) { "default", _jm_f_146 };
        _jm_obj_41_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_147 };
        _jm_obj_41_map_tab[6] = (jm_propmap_t) { "description", _jm_f_148 };
        _jm_obj_41_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_149 };
        _jm_obj_41_map_tab[8] = (jm_propmap_t) { "id", _jm_f_150 };
        _jm_obj_41_map_tab[9] = (jm_propmap_t) { "title", _jm_f_151 };
        jm_sort_propmap(_jm_obj_41_map_tab, 10);
        _jm_obj_44_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_152 };
        _jm_obj_44_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_153 };
        _jm_obj_44_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_154 };
        _jm_obj_44_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_155 };
        _jm_obj_44_map_tab[4] = (jm_propmap_t) { "default", _jm_f_156 };
        _jm_obj_44_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_157 };
        _jm_obj_44_map_tab[6] = (jm_propmap_t) { "description", _jm_f_158 };
        _jm_obj_44_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_159 };
        _jm_obj_44_map_tab[8] = (jm_propmap_t) { "id", _jm_f_160 };
        _jm_obj_44_map_tab[9] = (jm_propmap_t) { "title", _jm_f_161 };
        jm_sort_propmap(_jm_obj_44_map_tab, 10);
        _jm_obj_47_map_tab[0] = (jm_propmap_t) { "$comment", _jm_f_162 };
        _jm_obj_47_map_tab[1] = (jm_propmap_t) { "$defs", _jm_f_163 };
        _jm_obj_47_map_tab[2] = (jm_propmap_t) { "$id", _jm_f_164 };
        _jm_obj_47_map_tab[3] = (jm_propmap_t) { "$schema", _jm_f_165 };
        _jm_obj_47_map_tab[4] = (jm_propmap_t) { "default", _jm_f_166 };
        _jm_obj_47_map_tab[5] = (jm_propmap_t) { "definitions", _jm_f_167 };
        _jm_obj_47_map_tab[6] = (jm_propmap_t) { "description", _jm_f_168 };
        _jm_obj_47_map_tab[7] = (jm_propmap_t) { "examples", _jm_f_169 };
        _jm_obj_47_map_tab[8] = (jm_propmap_t) { "id", _jm_f_170 };
        _jm_obj_47_map_tab[9] = (jm_propmap_t) { "title", _jm_f_171 };
        jm_sort_propmap(_jm_obj_47_map_tab, 10);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "const", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "enum", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "schemaArray", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "stringKeywords", json_model_5 };
        check_model_map_tab[5] = (jm_propmap_t) { "arrayKeywords", json_model_6 };
        check_model_map_tab[6] = (jm_propmap_t) { "objectKeywords", json_model_7 };
        check_model_map_tab[7] = (jm_propmap_t) { "numberKeywords", json_model_8 };
        check_model_map_tab[8] = (jm_propmap_t) { "metas", json_model_9 };
        check_model_map_tab[9] = (jm_propmap_t) { "String", json_model_10 };
        check_model_map_tab[10] = (jm_propmap_t) { "Array", json_model_11 };
        check_model_map_tab[11] = (jm_propmap_t) { "Object", json_model_12 };
        check_model_map_tab[12] = (jm_propmap_t) { "Integer", json_model_13 };
        check_model_map_tab[13] = (jm_propmap_t) { "Number", json_model_14 };
        check_model_map_tab[14] = (jm_propmap_t) { "Bool", json_model_15 };
        check_model_map_tab[15] = (jm_propmap_t) { "Null", json_model_16 };
        check_model_map_tab[16] = (jm_propmap_t) { "AllOf", json_model_17 };
        check_model_map_tab[17] = (jm_propmap_t) { "AnyOf", json_model_18 };
        check_model_map_tab[18] = (jm_propmap_t) { "OneOf", json_model_19 };
        check_model_map_tab[19] = (jm_propmap_t) { "Enum", json_model_20 };
        check_model_map_tab[20] = (jm_propmap_t) { "Const", json_model_21 };
        check_model_map_tab[21] = (jm_propmap_t) { "Ref", json_model_22 };
        check_model_map_tab[22] = (jm_propmap_t) { "ObjectSchema", json_model_23 };
        check_model_map_tab[23] = (jm_propmap_t) { "Schema", json_model_24 };
        check_model_map_tab[24] = (jm_propmap_t) { "RootSchema", json_model_25 };
        jm_sort_propmap(check_model_map_tab, 25);
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
