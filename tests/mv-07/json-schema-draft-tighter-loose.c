#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_3(const json_t* val, Path* path, Report* rep);
static bool json_model_1(const json_t* val, Path* path, Report* rep);
static bool json_model_27(const json_t* val, Path* path, Report* rep);
static bool json_model_25(const json_t* val, Path* path, Report* rep);
static bool _jm_f_0(const json_t* val, Path* path, Report* rep);
static bool _jm_f_1(const json_t* val, Path* path, Report* rep);
static bool _jm_f_2(const json_t* val, Path* path, Report* rep);
static bool _jm_f_3(const json_t* val, Path* path, Report* rep);
static bool _jm_f_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_6(const json_t* val, Path* path, Report* rep);
static bool _jm_f_7(const json_t* val, Path* path, Report* rep);
static bool _jm_f_8(const json_t* val, Path* path, Report* rep);
static bool _jm_f_9(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_1_map_tab[10];
static bool json_model_11(const json_t* val, Path* path, Report* rep);
static bool _jm_f_10(const json_t* val, Path* path, Report* rep);
static bool _jm_f_11(const json_t* val, Path* path, Report* rep);
static bool _jm_f_12(const json_t* val, Path* path, Report* rep);
static bool _jm_f_13(const json_t* val, Path* path, Report* rep);
static bool _jm_f_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_17(const json_t* val, Path* path, Report* rep);
static constant_t _jm_cst_0[27];
static bool _jm_f_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_22(const json_t* val, Path* path, Report* rep);
static bool _jm_f_23(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_4_map_tab[14];
static bool json_model_12(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_36(const json_t* val, Path* path, Report* rep);
static bool _jm_f_37(const json_t* val, Path* path, Report* rep);
static bool _jm_f_38(const json_t* val, Path* path, Report* rep);
static bool _jm_f_39(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_7_map_tab[16];
static bool json_model_13(const json_t* val, Path* path, Report* rep);
static bool json_model_6(const json_t* val, Path* path, Report* rep);
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
static bool _jm_f_50(const json_t* val, Path* path, Report* rep);
static bool _jm_f_51(const json_t* val, Path* path, Report* rep);
static bool _jm_f_52(const json_t* val, Path* path, Report* rep);
static bool _jm_f_53(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_10_map_tab[14];
static bool json_model_14(const json_t* val, Path* path, Report* rep);
static bool _jm_f_54(const json_t* val, Path* path, Report* rep);
static bool _jm_f_55(const json_t* val, Path* path, Report* rep);
static bool _jm_f_56(const json_t* val, Path* path, Report* rep);
static bool _jm_f_57(const json_t* val, Path* path, Report* rep);
static bool _jm_f_58(const json_t* val, Path* path, Report* rep);
static bool _jm_f_59(const json_t* val, Path* path, Report* rep);
static bool _jm_f_60(const json_t* val, Path* path, Report* rep);
static bool _jm_f_61(const json_t* val, Path* path, Report* rep);
static bool _jm_f_62(const json_t* val, Path* path, Report* rep);
static bool _jm_f_63(const json_t* val, Path* path, Report* rep);
static bool _jm_f_64(const json_t* val, Path* path, Report* rep);
static bool _jm_f_65(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_15_map_tab[12];
static bool json_model_15(const json_t* val, Path* path, Report* rep);
static bool _jm_f_66(const json_t* val, Path* path, Report* rep);
static bool _jm_f_67(const json_t* val, Path* path, Report* rep);
static bool _jm_f_68(const json_t* val, Path* path, Report* rep);
static bool _jm_f_69(const json_t* val, Path* path, Report* rep);
static bool _jm_f_70(const json_t* val, Path* path, Report* rep);
static bool _jm_f_71(const json_t* val, Path* path, Report* rep);
static bool _jm_f_72(const json_t* val, Path* path, Report* rep);
static bool _jm_f_73(const json_t* val, Path* path, Report* rep);
static bool _jm_f_74(const json_t* val, Path* path, Report* rep);
static bool _jm_f_75(const json_t* val, Path* path, Report* rep);
static bool _jm_f_76(const json_t* val, Path* path, Report* rep);
static bool _jm_f_77(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_18_map_tab[12];
static bool json_model_16(const json_t* val, Path* path, Report* rep);
static bool _jm_f_78(const json_t* val, Path* path, Report* rep);
static bool _jm_f_79(const json_t* val, Path* path, Report* rep);
static bool _jm_f_80(const json_t* val, Path* path, Report* rep);
static bool _jm_f_81(const json_t* val, Path* path, Report* rep);
static bool _jm_f_82(const json_t* val, Path* path, Report* rep);
static bool _jm_f_83(const json_t* val, Path* path, Report* rep);
static bool _jm_f_84(const json_t* val, Path* path, Report* rep);
static bool _jm_f_85(const json_t* val, Path* path, Report* rep);
static bool _jm_f_86(const json_t* val, Path* path, Report* rep);
static bool _jm_f_87(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_21_map_tab[10];
static bool json_model_17(const json_t* val, Path* path, Report* rep);
static bool _jm_f_88(const json_t* val, Path* path, Report* rep);
static bool _jm_f_89(const json_t* val, Path* path, Report* rep);
static bool _jm_f_90(const json_t* val, Path* path, Report* rep);
static bool _jm_f_91(const json_t* val, Path* path, Report* rep);
static bool _jm_f_92(const json_t* val, Path* path, Report* rep);
static bool _jm_f_93(const json_t* val, Path* path, Report* rep);
static bool _jm_f_94(const json_t* val, Path* path, Report* rep);
static bool _jm_f_95(const json_t* val, Path* path, Report* rep);
static bool _jm_f_96(const json_t* val, Path* path, Report* rep);
static bool _jm_f_97(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_24_map_tab[10];
static bool json_model_18(const json_t* val, Path* path, Report* rep);
static bool _jm_f_98(const json_t* val, Path* path, Report* rep);
static bool _jm_f_99(const json_t* val, Path* path, Report* rep);
static bool _jm_f_100(const json_t* val, Path* path, Report* rep);
static bool _jm_f_101(const json_t* val, Path* path, Report* rep);
static bool _jm_f_102(const json_t* val, Path* path, Report* rep);
static bool _jm_f_103(const json_t* val, Path* path, Report* rep);
static bool _jm_f_104(const json_t* val, Path* path, Report* rep);
static bool _jm_f_105(const json_t* val, Path* path, Report* rep);
static bool _jm_f_106(const json_t* val, Path* path, Report* rep);
static bool _jm_f_107(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_27_map_tab[10];
static bool json_model_19(const json_t* val, Path* path, Report* rep);
static bool _jm_f_108(const json_t* val, Path* path, Report* rep);
static bool _jm_f_109(const json_t* val, Path* path, Report* rep);
static bool _jm_f_110(const json_t* val, Path* path, Report* rep);
static bool _jm_f_111(const json_t* val, Path* path, Report* rep);
static bool _jm_f_112(const json_t* val, Path* path, Report* rep);
static bool _jm_f_113(const json_t* val, Path* path, Report* rep);
static bool _jm_f_114(const json_t* val, Path* path, Report* rep);
static bool _jm_f_115(const json_t* val, Path* path, Report* rep);
static bool _jm_f_116(const json_t* val, Path* path, Report* rep);
static bool _jm_f_117(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_30_map_tab[10];
static bool json_model_20(const json_t* val, Path* path, Report* rep);
static bool _jm_f_118(const json_t* val, Path* path, Report* rep);
static bool _jm_f_119(const json_t* val, Path* path, Report* rep);
static bool _jm_f_120(const json_t* val, Path* path, Report* rep);
static bool _jm_f_121(const json_t* val, Path* path, Report* rep);
static bool _jm_f_122(const json_t* val, Path* path, Report* rep);
static bool _jm_f_123(const json_t* val, Path* path, Report* rep);
static bool _jm_f_124(const json_t* val, Path* path, Report* rep);
static bool _jm_f_125(const json_t* val, Path* path, Report* rep);
static bool _jm_f_126(const json_t* val, Path* path, Report* rep);
static bool _jm_f_127(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_33_map_tab[10];
static bool json_model_21(const json_t* val, Path* path, Report* rep);
static bool _jm_f_128(const json_t* val, Path* path, Report* rep);
static bool _jm_f_129(const json_t* val, Path* path, Report* rep);
static bool _jm_f_130(const json_t* val, Path* path, Report* rep);
static bool _jm_f_131(const json_t* val, Path* path, Report* rep);
static bool _jm_f_132(const json_t* val, Path* path, Report* rep);
static bool _jm_f_133(const json_t* val, Path* path, Report* rep);
static bool _jm_f_134(const json_t* val, Path* path, Report* rep);
static bool _jm_f_135(const json_t* val, Path* path, Report* rep);
static bool _jm_f_136(const json_t* val, Path* path, Report* rep);
static bool _jm_f_137(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_36_map_tab[10];
static bool json_model_22(const json_t* val, Path* path, Report* rep);
static bool json_model_5(const json_t* val, Path* path, Report* rep);
static bool _jm_f_138(const json_t* val, Path* path, Report* rep);
static bool _jm_f_139(const json_t* val, Path* path, Report* rep);
static bool _jm_f_140(const json_t* val, Path* path, Report* rep);
static bool _jm_f_141(const json_t* val, Path* path, Report* rep);
static bool _jm_f_142(const json_t* val, Path* path, Report* rep);
static bool _jm_f_143(const json_t* val, Path* path, Report* rep);
static bool _jm_f_144(const json_t* val, Path* path, Report* rep);
static bool _jm_f_145(const json_t* val, Path* path, Report* rep);
static bool _jm_f_146(const json_t* val, Path* path, Report* rep);
static bool _jm_f_147(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_39_map_tab[10];
static bool json_model_23(const json_t* val, Path* path, Report* rep);
static bool json_model_4(const json_t* val, Path* path, Report* rep);
static bool _jm_f_148(const json_t* val, Path* path, Report* rep);
static bool _jm_f_149(const json_t* val, Path* path, Report* rep);
static bool _jm_f_150(const json_t* val, Path* path, Report* rep);
static bool _jm_f_151(const json_t* val, Path* path, Report* rep);
static bool _jm_f_152(const json_t* val, Path* path, Report* rep);
static bool _jm_f_153(const json_t* val, Path* path, Report* rep);
static bool _jm_f_154(const json_t* val, Path* path, Report* rep);
static bool _jm_f_155(const json_t* val, Path* path, Report* rep);
static bool _jm_f_156(const json_t* val, Path* path, Report* rep);
static bool _jm_f_157(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_42_map_tab[10];
static bool json_model_24(const json_t* val, Path* path, Report* rep);
static bool json_model_26(const json_t* val, Path* path, Report* rep);
static bool _jm_f_158(const json_t* val, Path* path, Report* rep);
static bool _jm_f_159(const json_t* val, Path* path, Report* rep);
static bool _jm_f_160(const json_t* val, Path* path, Report* rep);
static bool _jm_f_161(const json_t* val, Path* path, Report* rep);
static bool _jm_f_162(const json_t* val, Path* path, Report* rep);
static bool _jm_f_163(const json_t* val, Path* path, Report* rep);
static bool _jm_f_164(const json_t* val, Path* path, Report* rep);
static bool _jm_f_165(const json_t* val, Path* path, Report* rep);
static bool _jm_f_166(const json_t* val, Path* path, Report* rep);
static bool _jm_f_167(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_45_map_tab[10];
static bool json_model_28(const json_t* val, Path* path, Report* rep);
static bool _jm_f_168(const json_t* val, Path* path, Report* rep);
static bool _jm_f_169(const json_t* val, Path* path, Report* rep);
static bool _jm_f_170(const json_t* val, Path* path, Report* rep);
static bool _jm_f_171(const json_t* val, Path* path, Report* rep);
static bool _jm_f_172(const json_t* val, Path* path, Report* rep);
static bool _jm_f_173(const json_t* val, Path* path, Report* rep);
static bool _jm_f_174(const json_t* val, Path* path, Report* rep);
static bool _jm_f_175(const json_t* val, Path* path, Report* rep);
static bool _jm_f_176(const json_t* val, Path* path, Report* rep);
static bool _jm_f_177(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_48_map_tab[10];
static bool json_model_29(const json_t* val, Path* path, Report* rep);
static bool _jm_f_178(const json_t* val, Path* path, Report* rep);
static bool _jm_f_179(const json_t* val, Path* path, Report* rep);
static bool _jm_f_180(const json_t* val, Path* path, Report* rep);
static bool _jm_f_181(const json_t* val, Path* path, Report* rep);
static bool _jm_f_182(const json_t* val, Path* path, Report* rep);
static bool _jm_f_183(const json_t* val, Path* path, Report* rep);
static bool _jm_f_184(const json_t* val, Path* path, Report* rep);
static bool _jm_f_185(const json_t* val, Path* path, Report* rep);
static bool _jm_f_186(const json_t* val, Path* path, Report* rep);
static bool _jm_f_187(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_51_map_tab[10];
static bool json_model_30(const json_t* val, Path* path, Report* rep);
static bool _jm_f_188(const json_t* val, Path* path, Report* rep);
static bool _jm_f_189(const json_t* val, Path* path, Report* rep);
static bool _jm_f_190(const json_t* val, Path* path, Report* rep);
static bool _jm_f_191(const json_t* val, Path* path, Report* rep);
static bool _jm_f_192(const json_t* val, Path* path, Report* rep);
static bool _jm_f_193(const json_t* val, Path* path, Report* rep);
static bool _jm_f_194(const json_t* val, Path* path, Report* rep);
static bool _jm_f_195(const json_t* val, Path* path, Report* rep);
static bool _jm_f_196(const json_t* val, Path* path, Report* rep);
static bool _jm_f_197(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_54_map_tab[10];
static bool json_model_31(const json_t* val, Path* path, Report* rep);
static bool _jm_f_198(const json_t* val, Path* path, Report* rep);
static bool _jm_f_199(const json_t* val, Path* path, Report* rep);
static bool _jm_f_200(const json_t* val, Path* path, Report* rep);
static bool _jm_f_201(const json_t* val, Path* path, Report* rep);
static bool _jm_f_202(const json_t* val, Path* path, Report* rep);
static bool _jm_f_203(const json_t* val, Path* path, Report* rep);
static bool _jm_f_204(const json_t* val, Path* path, Report* rep);
static bool _jm_f_205(const json_t* val, Path* path, Report* rep);
static bool _jm_f_206(const json_t* val, Path* path, Report* rep);
static bool _jm_f_207(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_57_map_tab[10];
static bool json_model_32(const json_t* val, Path* path, Report* rep);
static bool _jm_f_208(const json_t* val, Path* path, Report* rep);
static bool _jm_f_209(const json_t* val, Path* path, Report* rep);
static bool _jm_f_210(const json_t* val, Path* path, Report* rep);
static bool _jm_f_211(const json_t* val, Path* path, Report* rep);
static bool _jm_f_212(const json_t* val, Path* path, Report* rep);
static bool _jm_f_213(const json_t* val, Path* path, Report* rep);
static bool _jm_f_214(const json_t* val, Path* path, Report* rep);
static bool _jm_f_215(const json_t* val, Path* path, Report* rep);
static bool _jm_f_216(const json_t* val, Path* path, Report* rep);
static bool _jm_f_217(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_60_map_tab[10];
static bool json_model_33(const json_t* val, Path* path, Report* rep);
static bool _jm_f_218(const json_t* val, Path* path, Report* rep);
static bool _jm_f_219(const json_t* val, Path* path, Report* rep);
static bool _jm_f_220(const json_t* val, Path* path, Report* rep);
static bool _jm_f_221(const json_t* val, Path* path, Report* rep);
static bool _jm_f_222(const json_t* val, Path* path, Report* rep);
static bool _jm_f_223(const json_t* val, Path* path, Report* rep);
static bool _jm_f_224(const json_t* val, Path* path, Report* rep);
static bool _jm_f_225(const json_t* val, Path* path, Report* rep);
static bool _jm_f_226(const json_t* val, Path* path, Report* rep);
static bool _jm_f_227(const json_t* val, Path* path, Report* rep);
static propmap_t _jm_obj_63_map_tab[10];
static bool json_model_34(const json_t* val, Path* path, Report* rep);
propmap_t check_model_map_tab[2];
const size_t check_model_map_size = 2;

// check $tight ($.'$tight')
static bool json_model_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight'
    res = json_model_27(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RootSchema [$.'$tight']", path);
    }
    return res;
}

// check $ ($)
static bool json_model_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $
    res = json_model_27(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $tight#RootSchema [$]", path);
    }
    return res;
}

// object $.'$tight#RootSchema'.'&'.0
static bool _jm_obj_0(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#RootSchema'.'&'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_0 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "$schema") == 0)
        {
            // handle must $schema property
            must_count += 1;
            // $.'$tight#RootSchema'.'&'.0.'$schema'
            res = json_is_string(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#RootSchema'.'&'.0.'$schema']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#RootSchema'.'&'.0.$schema]", (path ? &lpath_0 : NULL));
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
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#RootSchema'.'&'.0.'']", path);
        return false;
    }
    return true;
}

// check $tight#RootSchema ($.'$tight#RootSchema')
static bool json_model_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#RootSchema'
    res = true;
    if (res)
    {
        // $.'$tight#RootSchema'.'&'.0
        res = _jm_obj_0(val, path, rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#RootSchema'.'&'.0]", path);
        }
        if (res)
        {
            // $.'$tight#RootSchema'.'&'.1
            res = json_model_25(val, path, rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [$.'$tight#RootSchema'.'&'.1]", path);
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not all model match [$.'$tight#RootSchema'.'&']", path);
    }
    return res;
}

// check $tight#ObjectSchema ($.'$tight#ObjectSchema')
static bool json_model_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ObjectSchema'
    // $.'$tight#ObjectSchema'.'|'.0
    res = json_model_18(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Null [$.'$tight#ObjectSchema'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$tight#ObjectSchema'.'|'.1
        res = json_model_17(val, path, rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Bool [$.'$tight#ObjectSchema'.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$tight#ObjectSchema'.'|'.2
            res = json_model_23(val, path, rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Const [$.'$tight#ObjectSchema'.'|'.2]", path);
            }
            if (! res)
            {
                // $.'$tight#ObjectSchema'.'|'.3
                res = json_model_22(val, path, rep);
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Enum [$.'$tight#ObjectSchema'.'|'.3]", path);
                }
                if (! res)
                {
                    // $.'$tight#ObjectSchema'.'|'.4
                    res = json_model_15(val, path, rep);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected $Integer [$.'$tight#ObjectSchema'.'|'.4]", path);
                    }
                    if (! res)
                    {
                        // $.'$tight#ObjectSchema'.'|'.5
                        res = json_model_16(val, path, rep);
                        if (res)
                        {
                            if (rep) jm_report_free_entries(rep);
                        }
                        else
                        {
                            if (rep) jm_report_add_entry(rep, "unexpected $Number [$.'$tight#ObjectSchema'.'|'.5]", path);
                        }
                        if (! res)
                        {
                            // $.'$tight#ObjectSchema'.'|'.6
                            res = json_model_12(val, path, rep);
                            if (res)
                            {
                                if (rep) jm_report_free_entries(rep);
                            }
                            else
                            {
                                if (rep) jm_report_add_entry(rep, "unexpected $String [$.'$tight#ObjectSchema'.'|'.6]", path);
                            }
                            if (! res)
                            {
                                // $.'$tight#ObjectSchema'.'|'.7
                                res = json_model_13(val, path, rep);
                                if (res)
                                {
                                    if (rep) jm_report_free_entries(rep);
                                }
                                else
                                {
                                    if (rep) jm_report_add_entry(rep, "unexpected $Array [$.'$tight#ObjectSchema'.'|'.7]", path);
                                }
                                if (! res)
                                {
                                    // $.'$tight#ObjectSchema'.'|'.8
                                    res = json_model_14(val, path, rep);
                                    if (res)
                                    {
                                        if (rep) jm_report_free_entries(rep);
                                    }
                                    else
                                    {
                                        if (rep) jm_report_add_entry(rep, "unexpected $Object [$.'$tight#ObjectSchema'.'|'.8]", path);
                                    }
                                    if (! res)
                                    {
                                        // $.'$tight#ObjectSchema'.'|'.9
                                        res = json_model_19(val, path, rep);
                                        if (res)
                                        {
                                            if (rep) jm_report_free_entries(rep);
                                        }
                                        else
                                        {
                                            if (rep) jm_report_add_entry(rep, "unexpected $AllOf [$.'$tight#ObjectSchema'.'|'.9]", path);
                                        }
                                        if (! res)
                                        {
                                            // $.'$tight#ObjectSchema'.'|'.10
                                            res = json_model_20(val, path, rep);
                                            if (res)
                                            {
                                                if (rep) jm_report_free_entries(rep);
                                            }
                                            else
                                            {
                                                if (rep) jm_report_add_entry(rep, "unexpected $AnyOf [$.'$tight#ObjectSchema'.'|'.10]", path);
                                            }
                                            if (! res)
                                            {
                                                // $.'$tight#ObjectSchema'.'|'.11
                                                res = json_model_21(val, path, rep);
                                                if (res)
                                                {
                                                    if (rep) jm_report_free_entries(rep);
                                                }
                                                else
                                                {
                                                    if (rep) jm_report_add_entry(rep, "unexpected $OneOf [$.'$tight#ObjectSchema'.'|'.11]", path);
                                                }
                                                if (! res)
                                                {
                                                    // $.'$tight#ObjectSchema'.'|'.12
                                                    res = json_model_24(val, path, rep);
                                                    if (res)
                                                    {
                                                        if (rep) jm_report_free_entries(rep);
                                                    }
                                                    else
                                                    {
                                                        if (rep) jm_report_add_entry(rep, "unexpected $Ref [$.'$tight#ObjectSchema'.'|'.12]", path);
                                                    }
                                                    if (! res)
                                                    {
                                                        // $.'$tight#ObjectSchema'.'|'.13
                                                        res = json_model_11(val, path, rep);
                                                        if (res)
                                                        {
                                                            if (rep) jm_report_free_entries(rep);
                                                        }
                                                        else
                                                        {
                                                            if (rep) jm_report_add_entry(rep, "unexpected $metas [$.'$tight#ObjectSchema'.'|'.13]", path);
                                                        }
                                                        if (! res)
                                                        {
                                                            // $.'$tight#ObjectSchema'.'|'.14
                                                            res = json_model_28(val, path, rep);
                                                            if (res)
                                                            {
                                                                if (rep) jm_report_free_entries(rep);
                                                            }
                                                            else
                                                            {
                                                                if (rep) jm_report_add_entry(rep, "unexpected $EnumString [$.'$tight#ObjectSchema'.'|'.14]", path);
                                                            }
                                                            if (! res)
                                                            {
                                                                // $.'$tight#ObjectSchema'.'|'.15
                                                                res = json_model_29(val, path, rep);
                                                                if (res)
                                                                {
                                                                    if (rep) jm_report_free_entries(rep);
                                                                }
                                                                else
                                                                {
                                                                    if (rep) jm_report_add_entry(rep, "unexpected $EnumNum [$.'$tight#ObjectSchema'.'|'.15]", path);
                                                                }
                                                                if (! res)
                                                                {
                                                                    // $.'$tight#ObjectSchema'.'|'.16
                                                                    res = json_model_30(val, path, rep);
                                                                    if (res)
                                                                    {
                                                                        if (rep) jm_report_free_entries(rep);
                                                                    }
                                                                    else
                                                                    {
                                                                        if (rep) jm_report_add_entry(rep, "unexpected $EnumInt [$.'$tight#ObjectSchema'.'|'.16]", path);
                                                                    }
                                                                    if (! res)
                                                                    {
                                                                        // $.'$tight#ObjectSchema'.'|'.17
                                                                        res = json_model_31(val, path, rep);
                                                                        if (res)
                                                                        {
                                                                            if (rep) jm_report_free_entries(rep);
                                                                        }
                                                                        else
                                                                        {
                                                                            if (rep) jm_report_add_entry(rep, "unexpected $ConstString [$.'$tight#ObjectSchema'.'|'.17]", path);
                                                                        }
                                                                        if (! res)
                                                                        {
                                                                            // $.'$tight#ObjectSchema'.'|'.18
                                                                            res = json_model_32(val, path, rep);
                                                                            if (res)
                                                                            {
                                                                                if (rep) jm_report_free_entries(rep);
                                                                            }
                                                                            else
                                                                            {
                                                                                if (rep) jm_report_add_entry(rep, "unexpected $ConstNum [$.'$tight#ObjectSchema'.'|'.18]", path);
                                                                            }
                                                                            if (! res)
                                                                            {
                                                                                // $.'$tight#ObjectSchema'.'|'.19
                                                                                res = json_model_33(val, path, rep);
                                                                                if (res)
                                                                                {
                                                                                    if (rep) jm_report_free_entries(rep);
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (rep) jm_report_add_entry(rep, "unexpected $ConstInt [$.'$tight#ObjectSchema'.'|'.19]", path);
                                                                                }
                                                                                if (! res)
                                                                                {
                                                                                    // $.'$tight#ObjectSchema'.'|'.20
                                                                                    res = json_model_34(val, path, rep);
                                                                                    if (res)
                                                                                    {
                                                                                        if (rep) jm_report_free_entries(rep);
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if (rep) jm_report_add_entry(rep, "unexpected $ConstBool [$.'$tight#ObjectSchema'.'|'.20]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$tight#ObjectSchema'.'|']", path);
    }
    return res;
}

// check _jm_obj_1_map_$comment ($.'$tight#metas'.'$comment')
static bool _jm_f_0(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#metas'.'$defs'
static bool _jm_obj_2(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#metas'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_2 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#metas'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_2 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#metas'.'$defs'.'']", (path ? &lpath_2 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_1_map_$defs ($.'$tight#metas'.'$defs')
static bool _jm_f_1(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.'$defs'
    res = _jm_obj_2(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#metas'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_1_map_$id ($.'$tight#metas'.'$id')
static bool _jm_f_2(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.'$id']", path);
    }
    return res;
}

// check _jm_obj_1_map_$schema ($.'$tight#metas'.'$schema')
static bool _jm_f_3(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_1_map_default ($.'$tight#metas'.default)
static bool _jm_f_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#metas'.default]", path);
    }
    return res;
}

// object $.'$tight#metas'.definitions
static bool _jm_obj_3(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#metas'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_3 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#metas'.definitions.''
        res = json_model_26(pval, (path ? &lpath_3 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#metas'.definitions.'']", (path ? &lpath_3 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_1_map_definitions ($.'$tight#metas'.definitions)
static bool _jm_f_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.definitions
    res = _jm_obj_3(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#metas'.definitions]", path);
    }
    return res;
}

// check _jm_obj_1_map_description ($.'$tight#metas'.description)
static bool _jm_f_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.description]", path);
    }
    return res;
}

// check _jm_obj_1_map_examples ($.'$tight#metas'.examples)
static bool _jm_f_7(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#metas'.examples]", path);
    }
    return res;
}

// check _jm_obj_1_map_id ($.'$tight#metas'.id)
static bool _jm_f_8(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.id]", path);
    }
    return res;
}

// check _jm_obj_1_map_title ($.'$tight#metas'.title)
static bool _jm_f_9(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#metas'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_1_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_1_map_tab, 10);
}

// object $.'$tight#metas'
static bool _jm_obj_1(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#metas']", path);
        return false;
    }
    check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_1 = (Path) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_1_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_1 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#metas']", (path ? &lpath_1 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#metas']", (path ? &lpath_1 : NULL));
            return false;
        }
    }
    return true;
}

// check $tight#metas ($.'$tight#metas')
static bool json_model_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#metas'
    res = _jm_obj_1(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#metas']", path);
    }
    return res;
}

// check _jm_obj_4_map_$comment ($.'$tight#String'.'$comment')
static bool _jm_f_10(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#String'.'$defs'
static bool _jm_obj_5(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#String'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_5 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#String'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_5 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#String'.'$defs'.'']", (path ? &lpath_5 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_4_map_$defs ($.'$tight#String'.'$defs')
static bool _jm_f_11(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.'$defs'
    res = _jm_obj_5(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#String'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_4_map_$id ($.'$tight#String'.'$id')
static bool _jm_f_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.'$id']", path);
    }
    return res;
}

// check _jm_obj_4_map_$schema ($.'$tight#String'.'$schema')
static bool _jm_f_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_4_map_default ($.'$tight#String'.default)
static bool _jm_f_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#String'.default]", path);
    }
    return res;
}

// object $.'$tight#String'.definitions
static bool _jm_obj_6(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#String'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_6 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#String'.definitions.''
        res = json_model_26(pval, (path ? &lpath_6 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#String'.definitions.'']", (path ? &lpath_6 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_4_map_definitions ($.'$tight#String'.definitions)
static bool _jm_f_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.definitions
    res = _jm_obj_6(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#String'.definitions]", path);
    }
    return res;
}

// check _jm_obj_4_map_description ($.'$tight#String'.description)
static bool _jm_f_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.description]", path);
    }
    return res;
}

// check _jm_obj_4_map_examples ($.'$tight#String'.examples)
static bool _jm_f_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#String'.examples]", path);
    }
    return res;
}


// check _jm_obj_4_map_format ($.'$tight#String'.format)
static bool _jm_f_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.format
    res = _json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_0, 27);;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [$.'$tight#String'.format.'|']", path);
    }
    return res;
}

// check _jm_obj_4_map_id ($.'$tight#String'.id)
static bool _jm_f_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.id]", path);
    }
    return res;
}

// check _jm_obj_4_map_maxLength ($.'$tight#String'.maxLength)
static bool _jm_f_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$tight#String'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_4_map_minLength ($.'$tight#String'.minLength)
static bool _jm_f_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$tight#String'.minLength]", path);
    }
    return res;
}

// check _jm_obj_4_map_pattern ($.'$tight#String'.pattern)
static bool _jm_f_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.pattern
    res = jm_is_valid_regex(json_string_value(val));
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [$.'$tight#String'.pattern]", path);
    }
    return res;
}

// check _jm_obj_4_map_title ($.'$tight#String'.title)
static bool _jm_f_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_4_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_4_map_tab, 14);
}

// object $.'$tight#String'
static bool _jm_obj_4(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#String']", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#String'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#String'.type]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#String'.type]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_4_map(prop)))
        {
            // handle 14 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_4 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#String']", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#String']", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#String']", path);
        return false;
    }
    return true;
}

// check $tight#String ($.'$tight#String')
static bool json_model_12(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#String'
    res = _jm_obj_4(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#String']", path);
    }
    return res;
}

// check _jm_obj_7_map_$comment ($.'$tight#Array'.'$comment')
static bool _jm_f_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Array'.'$defs'
static bool _jm_obj_8(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Array'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_8 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Array'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_8 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Array'.'$defs'.'']", (path ? &lpath_8 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_7_map_$defs ($.'$tight#Array'.'$defs')
static bool _jm_f_25(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.'$defs'
    res = _jm_obj_8(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Array'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_7_map_$id ($.'$tight#Array'.'$id')
static bool _jm_f_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.'$id']", path);
    }
    return res;
}

// check _jm_obj_7_map_$schema ($.'$tight#Array'.'$schema')
static bool _jm_f_27(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_7_map_additionalItems ($.'$tight#Array'.additionalItems)
static bool _jm_f_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.additionalItems
    res = json_model_26(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Array'.additionalItems]", path);
    }
    return res;
}

// check _jm_obj_7_map_default ($.'$tight#Array'.default)
static bool _jm_f_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Array'.default]", path);
    }
    return res;
}

// object $.'$tight#Array'.definitions
static bool _jm_obj_9(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Array'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_9 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Array'.definitions.''
        res = json_model_26(pval, (path ? &lpath_9 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Array'.definitions.'']", (path ? &lpath_9 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_7_map_definitions ($.'$tight#Array'.definitions)
static bool _jm_f_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.definitions
    res = _jm_obj_9(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Array'.definitions]", path);
    }
    return res;
}

// check _jm_obj_7_map_description ($.'$tight#Array'.description)
static bool _jm_f_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.description]", path);
    }
    return res;
}

// check _jm_obj_7_map_examples ($.'$tight#Array'.examples)
static bool _jm_f_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Array'.examples]", path);
    }
    return res;
}

// check _jm_obj_7_map_id ($.'$tight#Array'.id)
static bool _jm_f_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.id]", path);
    }
    return res;
}

// check _jm_obj_7_map_items ($.'$tight#Array'.items)
static bool _jm_f_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.items
    // $.'$tight#Array'.items.'|'.0
    res = json_model_26(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Array'.items.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$tight#Array'.items.'|'.1
        res = json_model_6(val, path, rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$tight#Array'.items.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$tight#Array'.items.'|']", path);
    }
    return res;
}

// check _jm_obj_7_map_maxItems ($.'$tight#Array'.maxItems)
static bool _jm_f_35(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$tight#Array'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_7_map_minItems ($.'$tight#Array'.minItems)
static bool _jm_f_36(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [$.'$tight#Array'.minItems]", path);
    }
    return res;
}

// check _jm_obj_7_map_prefixItems ($.'$tight#Array'.prefixItems)
static bool _jm_f_37(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.prefixItems
    res = json_model_6(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$tight#Array'.prefixItems]", path);
    }
    return res;
}

// check _jm_obj_7_map_title ($.'$tight#Array'.title)
static bool _jm_f_38(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Array'.title]", path);
    }
    return res;
}

// check _jm_obj_7_map_uniqueItems ($.'$tight#Array'.uniqueItems)
static bool _jm_f_39(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'.uniqueItems
    res = json_is_boolean(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$tight#Array'.uniqueItems]", path);
    }
    return res;
}

static check_fun_t _jm_obj_7_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_7_map_tab, 16);
}

// object $.'$tight#Array'
static bool _jm_obj_7(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Array']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_7 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Array'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "array") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected array [$.'$tight#Array'.type]", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Array'.type]", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_7_map(prop)))
        {
            // handle 16 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_7 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Array']", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Array']", (path ? &lpath_7 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Array']", path);
        return false;
    }
    return true;
}

// check $tight#Array ($.'$tight#Array')
static bool json_model_13(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Array'
    res = _jm_obj_7(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Array']", path);
    }
    return res;
}

// check $tight#schemaArray ($.'$tight#schemaArray')
static bool json_model_6(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#schemaArray'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            Path arr_0_lpath = (Path) { NULL, arr_0_idx, path, NULL };
            // $.'$tight#schemaArray'.0
            res = json_model_26(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#schemaArray'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#schemaArray']", path);
    }
    return res;
}

// check _jm_obj_10_map_$comment ($.'$tight#Object'.'$comment')
static bool _jm_f_40(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Object'.'$defs'
static bool _jm_obj_11(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Object'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_11 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Object'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_11 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Object'.'$defs'.'']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_$defs ($.'$tight#Object'.'$defs')
static bool _jm_f_41(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.'$defs'
    res = _jm_obj_11(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Object'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_10_map_$id ($.'$tight#Object'.'$id')
static bool _jm_f_42(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.'$id']", path);
    }
    return res;
}

// check _jm_obj_10_map_$schema ($.'$tight#Object'.'$schema')
static bool _jm_f_43(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_10_map_additionalProperties ($.'$tight#Object'.additionalProperties)
static bool _jm_f_44(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.additionalProperties
    res = json_model_26(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Object'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_10_map_default ($.'$tight#Object'.default)
static bool _jm_f_45(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Object'.default]", path);
    }
    return res;
}

// object $.'$tight#Object'.definitions
static bool _jm_obj_12(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Object'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_12 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Object'.definitions.''
        res = json_model_26(pval, (path ? &lpath_12 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Object'.definitions.'']", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_definitions ($.'$tight#Object'.definitions)
static bool _jm_f_46(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.definitions
    res = _jm_obj_12(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Object'.definitions]", path);
    }
    return res;
}

// check _jm_obj_10_map_description ($.'$tight#Object'.description)
static bool _jm_f_47(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.description]", path);
    }
    return res;
}

// check _jm_obj_10_map_examples ($.'$tight#Object'.examples)
static bool _jm_f_48(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Object'.examples]", path);
    }
    return res;
}

// check _jm_obj_10_map_id ($.'$tight#Object'.id)
static bool _jm_f_49(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.id]", path);
    }
    return res;
}

// object $.'$tight#Object'.patternProperties
static bool _jm_obj_13(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Object'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_13 = (Path) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop))
        {
            // handle 1 key props
            // $.'$tight#Object'.patternProperties.'$REGEX'
            res = json_model_26(pval, (path ? &lpath_13 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Object'.patternProperties.'$REGEX']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Object'.patternProperties]", (path ? &lpath_13 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_patternProperties ($.'$tight#Object'.patternProperties)
static bool _jm_f_50(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.patternProperties
    res = _jm_obj_13(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Object'.patternProperties]", path);
    }
    return res;
}

// object $.'$tight#Object'.properties
static bool _jm_obj_14(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Object'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_14 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Object'.properties.''
        res = json_model_26(pval, (path ? &lpath_14 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Object'.properties.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_properties ($.'$tight#Object'.properties)
static bool _jm_f_51(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.properties
    res = _jm_obj_14(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Object'.properties]", path);
    }
    return res;
}

// check _jm_obj_10_map_required ($.'$tight#Object'.required)
static bool _jm_f_52(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.required
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            Path arr_1_lpath = (Path) { NULL, arr_1_idx, path, NULL };
            // $.'$tight#Object'.required.0
            res = json_is_string(arr_1_item);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.required.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Object'.required]", path);
    }
    return res;
}

// check _jm_obj_10_map_title ($.'$tight#Object'.title)
static bool _jm_f_53(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Object'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_10_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_10_map_tab, 14);
}

// object $.'$tight#Object'
static bool _jm_obj_10(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Object']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_10 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Object'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "object") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected object [$.'$tight#Object'.type]", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Object'.type]", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_10_map(prop)))
        {
            // handle 14 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_10 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Object']", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Object']", (path ? &lpath_10 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Object']", path);
        return false;
    }
    return true;
}

// check $tight#Object ($.'$tight#Object')
static bool json_model_14(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Object'
    res = _jm_obj_10(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Object']", path);
    }
    return res;
}

// check _jm_obj_15_map_$comment ($.'$tight#Integer'.'$comment')
static bool _jm_f_54(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Integer'.'$defs'
static bool _jm_obj_16(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Integer'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_16 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Integer'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_16 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Integer'.'$defs'.'']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_$defs ($.'$tight#Integer'.'$defs')
static bool _jm_f_55(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.'$defs'
    res = _jm_obj_16(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Integer'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_15_map_$id ($.'$tight#Integer'.'$id')
static bool _jm_f_56(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.'$id']", path);
    }
    return res;
}

// check _jm_obj_15_map_$schema ($.'$tight#Integer'.'$schema')
static bool _jm_f_57(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_15_map_default ($.'$tight#Integer'.default)
static bool _jm_f_58(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Integer'.default]", path);
    }
    return res;
}

// object $.'$tight#Integer'.definitions
static bool _jm_obj_17(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Integer'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_17 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Integer'.definitions.''
        res = json_model_26(pval, (path ? &lpath_17 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Integer'.definitions.'']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_15_map_definitions ($.'$tight#Integer'.definitions)
static bool _jm_f_59(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.definitions
    res = _jm_obj_17(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Integer'.definitions]", path);
    }
    return res;
}

// check _jm_obj_15_map_description ($.'$tight#Integer'.description)
static bool _jm_f_60(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.description]", path);
    }
    return res;
}

// check _jm_obj_15_map_examples ($.'$tight#Integer'.examples)
static bool _jm_f_61(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Integer'.examples]", path);
    }
    return res;
}

// check _jm_obj_15_map_id ($.'$tight#Integer'.id)
static bool _jm_f_62(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.id]", path);
    }
    return res;
}

// check _jm_obj_15_map_maximum ($.'$tight#Integer'.maximum)
static bool _jm_f_63(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.maximum
    res = json_is_real(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#Integer'.maximum]", path);
    }
    return res;
}

// check _jm_obj_15_map_minimum ($.'$tight#Integer'.minimum)
static bool _jm_f_64(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.minimum
    res = json_is_real(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#Integer'.minimum]", path);
    }
    return res;
}

// check _jm_obj_15_map_title ($.'$tight#Integer'.title)
static bool _jm_f_65(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Integer'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_15_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_15_map_tab, 12);
}

// object $.'$tight#Integer'
static bool _jm_obj_15(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Integer']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_15 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Integer'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected integer [$.'$tight#Integer'.type]", (path ? &lpath_15 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Integer'.type]", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_15_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_15 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Integer']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Integer']", (path ? &lpath_15 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Integer']", path);
        return false;
    }
    return true;
}

// check $tight#Integer ($.'$tight#Integer')
static bool json_model_15(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Integer'
    res = _jm_obj_15(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Integer']", path);
    }
    return res;
}

// check _jm_obj_18_map_$comment ($.'$tight#Number'.'$comment')
static bool _jm_f_66(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Number'.'$defs'
static bool _jm_obj_19(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Number'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_19 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Number'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_19 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Number'.'$defs'.'']", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_18_map_$defs ($.'$tight#Number'.'$defs')
static bool _jm_f_67(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.'$defs'
    res = _jm_obj_19(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Number'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_18_map_$id ($.'$tight#Number'.'$id')
static bool _jm_f_68(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.'$id']", path);
    }
    return res;
}

// check _jm_obj_18_map_$schema ($.'$tight#Number'.'$schema')
static bool _jm_f_69(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_18_map_default ($.'$tight#Number'.default)
static bool _jm_f_70(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Number'.default]", path);
    }
    return res;
}

// object $.'$tight#Number'.definitions
static bool _jm_obj_20(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Number'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_20 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Number'.definitions.''
        res = json_model_26(pval, (path ? &lpath_20 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Number'.definitions.'']", (path ? &lpath_20 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_18_map_definitions ($.'$tight#Number'.definitions)
static bool _jm_f_71(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.definitions
    res = _jm_obj_20(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Number'.definitions]", path);
    }
    return res;
}

// check _jm_obj_18_map_description ($.'$tight#Number'.description)
static bool _jm_f_72(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.description]", path);
    }
    return res;
}

// check _jm_obj_18_map_examples ($.'$tight#Number'.examples)
static bool _jm_f_73(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Number'.examples]", path);
    }
    return res;
}

// check _jm_obj_18_map_id ($.'$tight#Number'.id)
static bool _jm_f_74(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.id]", path);
    }
    return res;
}

// check _jm_obj_18_map_maximum ($.'$tight#Number'.maximum)
static bool _jm_f_75(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.maximum
    res = json_is_real(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#Number'.maximum]", path);
    }
    return res;
}

// check _jm_obj_18_map_minimum ($.'$tight#Number'.minimum)
static bool _jm_f_76(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.minimum
    res = json_is_real(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#Number'.minimum]", path);
    }
    return res;
}

// check _jm_obj_18_map_title ($.'$tight#Number'.title)
static bool _jm_f_77(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Number'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_18_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_18_map_tab, 12);
}

// object $.'$tight#Number'
static bool _jm_obj_18(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Number']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_18 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Number'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected number [$.'$tight#Number'.type]", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Number'.type]", (path ? &lpath_18 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_18_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_18 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Number']", (path ? &lpath_18 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Number']", (path ? &lpath_18 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Number']", path);
        return false;
    }
    return true;
}

// check $tight#Number ($.'$tight#Number')
static bool json_model_16(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Number'
    res = _jm_obj_18(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Number']", path);
    }
    return res;
}

// check _jm_obj_21_map_$comment ($.'$tight#Bool'.'$comment')
static bool _jm_f_78(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Bool'.'$defs'
static bool _jm_obj_22(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Bool'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_22 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Bool'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_22 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Bool'.'$defs'.'']", (path ? &lpath_22 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_21_map_$defs ($.'$tight#Bool'.'$defs')
static bool _jm_f_79(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.'$defs'
    res = _jm_obj_22(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Bool'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_21_map_$id ($.'$tight#Bool'.'$id')
static bool _jm_f_80(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.'$id']", path);
    }
    return res;
}

// check _jm_obj_21_map_$schema ($.'$tight#Bool'.'$schema')
static bool _jm_f_81(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_21_map_default ($.'$tight#Bool'.default)
static bool _jm_f_82(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Bool'.default]", path);
    }
    return res;
}

// object $.'$tight#Bool'.definitions
static bool _jm_obj_23(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Bool'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_23 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Bool'.definitions.''
        res = json_model_26(pval, (path ? &lpath_23 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Bool'.definitions.'']", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_21_map_definitions ($.'$tight#Bool'.definitions)
static bool _jm_f_83(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.definitions
    res = _jm_obj_23(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Bool'.definitions]", path);
    }
    return res;
}

// check _jm_obj_21_map_description ($.'$tight#Bool'.description)
static bool _jm_f_84(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.description]", path);
    }
    return res;
}

// check _jm_obj_21_map_examples ($.'$tight#Bool'.examples)
static bool _jm_f_85(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Bool'.examples]", path);
    }
    return res;
}

// check _jm_obj_21_map_id ($.'$tight#Bool'.id)
static bool _jm_f_86(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.id]", path);
    }
    return res;
}

// check _jm_obj_21_map_title ($.'$tight#Bool'.title)
static bool _jm_f_87(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Bool'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_21_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_21_map_tab, 10);
}

// object $.'$tight#Bool'
static bool _jm_obj_21(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Bool']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_21 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Bool'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "boolean") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected boolean [$.'$tight#Bool'.type]", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Bool'.type]", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_21_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_21 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Bool']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Bool']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Bool']", path);
        return false;
    }
    return true;
}

// check $tight#Bool ($.'$tight#Bool')
static bool json_model_17(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Bool'
    res = _jm_obj_21(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Bool']", path);
    }
    return res;
}

// check _jm_obj_24_map_$comment ($.'$tight#Null'.'$comment')
static bool _jm_f_88(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Null'.'$defs'
static bool _jm_obj_25(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Null'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_25 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Null'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_25 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Null'.'$defs'.'']", (path ? &lpath_25 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_24_map_$defs ($.'$tight#Null'.'$defs')
static bool _jm_f_89(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.'$defs'
    res = _jm_obj_25(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Null'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_24_map_$id ($.'$tight#Null'.'$id')
static bool _jm_f_90(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.'$id']", path);
    }
    return res;
}

// check _jm_obj_24_map_$schema ($.'$tight#Null'.'$schema')
static bool _jm_f_91(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_24_map_default ($.'$tight#Null'.default)
static bool _jm_f_92(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Null'.default]", path);
    }
    return res;
}

// object $.'$tight#Null'.definitions
static bool _jm_obj_26(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Null'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_26 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Null'.definitions.''
        res = json_model_26(pval, (path ? &lpath_26 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Null'.definitions.'']", (path ? &lpath_26 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_24_map_definitions ($.'$tight#Null'.definitions)
static bool _jm_f_93(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.definitions
    res = _jm_obj_26(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Null'.definitions]", path);
    }
    return res;
}

// check _jm_obj_24_map_description ($.'$tight#Null'.description)
static bool _jm_f_94(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.description]", path);
    }
    return res;
}

// check _jm_obj_24_map_examples ($.'$tight#Null'.examples)
static bool _jm_f_95(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Null'.examples]", path);
    }
    return res;
}

// check _jm_obj_24_map_id ($.'$tight#Null'.id)
static bool _jm_f_96(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.id]", path);
    }
    return res;
}

// check _jm_obj_24_map_title ($.'$tight#Null'.title)
static bool _jm_f_97(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Null'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_24_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_24_map_tab, 10);
}

// object $.'$tight#Null'
static bool _jm_obj_24(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Null']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_24 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#Null'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "null") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected null [$.'$tight#Null'.type]", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Null'.type]", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_24_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_24 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Null']", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Null']", (path ? &lpath_24 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Null']", path);
        return false;
    }
    return true;
}

// check $tight#Null ($.'$tight#Null')
static bool json_model_18(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Null'
    res = _jm_obj_24(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Null']", path);
    }
    return res;
}

// check _jm_obj_27_map_$comment ($.'$tight#AllOf'.'$comment')
static bool _jm_f_98(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#AllOf'.'$defs'
static bool _jm_obj_28(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AllOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_28 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#AllOf'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_28 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#AllOf'.'$defs'.'']", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_27_map_$defs ($.'$tight#AllOf'.'$defs')
static bool _jm_f_99(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.'$defs'
    res = _jm_obj_28(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AllOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_27_map_$id ($.'$tight#AllOf'.'$id')
static bool _jm_f_100(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_27_map_$schema ($.'$tight#AllOf'.'$schema')
static bool _jm_f_101(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_27_map_default ($.'$tight#AllOf'.default)
static bool _jm_f_102(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#AllOf'.default]", path);
    }
    return res;
}

// object $.'$tight#AllOf'.definitions
static bool _jm_obj_29(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AllOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_29 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#AllOf'.definitions.''
        res = json_model_26(pval, (path ? &lpath_29 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#AllOf'.definitions.'']", (path ? &lpath_29 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_27_map_definitions ($.'$tight#AllOf'.definitions)
static bool _jm_f_103(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.definitions
    res = _jm_obj_29(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AllOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_27_map_description ($.'$tight#AllOf'.description)
static bool _jm_f_104(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.description]", path);
    }
    return res;
}

// check _jm_obj_27_map_examples ($.'$tight#AllOf'.examples)
static bool _jm_f_105(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#AllOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_27_map_id ($.'$tight#AllOf'.id)
static bool _jm_f_106(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.id]", path);
    }
    return res;
}

// check _jm_obj_27_map_title ($.'$tight#AllOf'.title)
static bool _jm_f_107(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AllOf'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_27_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_27_map_tab, 10);
}

// object $.'$tight#AllOf'
static bool _jm_obj_27(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AllOf']", path);
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
        if (strcmp(prop, "allOf") == 0)
        {
            // handle must allOf property
            must_count += 1;
            // $.'$tight#AllOf'.allOf
            res = json_model_6(pval, (path ? &lpath_27 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$tight#AllOf'.allOf]", (path ? &lpath_27 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#AllOf'.allOf]", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_27_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_27 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#AllOf']", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#AllOf']", (path ? &lpath_27 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#AllOf']", path);
        return false;
    }
    return true;
}

// check $tight#AllOf ($.'$tight#AllOf')
static bool json_model_19(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AllOf'
    res = _jm_obj_27(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AllOf']", path);
    }
    return res;
}

// check _jm_obj_30_map_$comment ($.'$tight#AnyOf'.'$comment')
static bool _jm_f_108(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#AnyOf'.'$defs'
static bool _jm_obj_31(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AnyOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_31 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#AnyOf'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_31 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#AnyOf'.'$defs'.'']", (path ? &lpath_31 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_30_map_$defs ($.'$tight#AnyOf'.'$defs')
static bool _jm_f_109(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.'$defs'
    res = _jm_obj_31(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AnyOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_30_map_$id ($.'$tight#AnyOf'.'$id')
static bool _jm_f_110(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_30_map_$schema ($.'$tight#AnyOf'.'$schema')
static bool _jm_f_111(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_30_map_default ($.'$tight#AnyOf'.default)
static bool _jm_f_112(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#AnyOf'.default]", path);
    }
    return res;
}

// object $.'$tight#AnyOf'.definitions
static bool _jm_obj_32(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AnyOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_32 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#AnyOf'.definitions.''
        res = json_model_26(pval, (path ? &lpath_32 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#AnyOf'.definitions.'']", (path ? &lpath_32 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_30_map_definitions ($.'$tight#AnyOf'.definitions)
static bool _jm_f_113(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.definitions
    res = _jm_obj_32(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AnyOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_30_map_description ($.'$tight#AnyOf'.description)
static bool _jm_f_114(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.description]", path);
    }
    return res;
}

// check _jm_obj_30_map_examples ($.'$tight#AnyOf'.examples)
static bool _jm_f_115(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#AnyOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_30_map_id ($.'$tight#AnyOf'.id)
static bool _jm_f_116(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.id]", path);
    }
    return res;
}

// check _jm_obj_30_map_title ($.'$tight#AnyOf'.title)
static bool _jm_f_117(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#AnyOf'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_30_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_30_map_tab, 10);
}

// object $.'$tight#AnyOf'
static bool _jm_obj_30(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#AnyOf']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_30 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "anyOf") == 0)
        {
            // handle must anyOf property
            must_count += 1;
            // $.'$tight#AnyOf'.anyOf
            res = json_model_6(pval, (path ? &lpath_30 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$tight#AnyOf'.anyOf]", (path ? &lpath_30 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#AnyOf'.anyOf]", (path ? &lpath_30 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_30_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_30 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#AnyOf']", (path ? &lpath_30 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#AnyOf']", (path ? &lpath_30 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#AnyOf']", path);
        return false;
    }
    return true;
}

// check $tight#AnyOf ($.'$tight#AnyOf')
static bool json_model_20(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#AnyOf'
    res = _jm_obj_30(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#AnyOf']", path);
    }
    return res;
}

// check _jm_obj_33_map_$comment ($.'$tight#OneOf'.'$comment')
static bool _jm_f_118(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#OneOf'.'$defs'
static bool _jm_obj_34(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#OneOf'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_34 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#OneOf'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_34 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#OneOf'.'$defs'.'']", (path ? &lpath_34 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_33_map_$defs ($.'$tight#OneOf'.'$defs')
static bool _jm_f_119(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.'$defs'
    res = _jm_obj_34(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#OneOf'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_33_map_$id ($.'$tight#OneOf'.'$id')
static bool _jm_f_120(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.'$id']", path);
    }
    return res;
}

// check _jm_obj_33_map_$schema ($.'$tight#OneOf'.'$schema')
static bool _jm_f_121(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_33_map_default ($.'$tight#OneOf'.default)
static bool _jm_f_122(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#OneOf'.default]", path);
    }
    return res;
}

// object $.'$tight#OneOf'.definitions
static bool _jm_obj_35(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#OneOf'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_35 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#OneOf'.definitions.''
        res = json_model_26(pval, (path ? &lpath_35 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#OneOf'.definitions.'']", (path ? &lpath_35 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_33_map_definitions ($.'$tight#OneOf'.definitions)
static bool _jm_f_123(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.definitions
    res = _jm_obj_35(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#OneOf'.definitions]", path);
    }
    return res;
}

// check _jm_obj_33_map_description ($.'$tight#OneOf'.description)
static bool _jm_f_124(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.description]", path);
    }
    return res;
}

// check _jm_obj_33_map_examples ($.'$tight#OneOf'.examples)
static bool _jm_f_125(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#OneOf'.examples]", path);
    }
    return res;
}

// check _jm_obj_33_map_id ($.'$tight#OneOf'.id)
static bool _jm_f_126(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.id]", path);
    }
    return res;
}

// check _jm_obj_33_map_title ($.'$tight#OneOf'.title)
static bool _jm_f_127(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#OneOf'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_33_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_33_map_tab, 10);
}

// object $.'$tight#OneOf'
static bool _jm_obj_33(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#OneOf']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_33 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "oneOf") == 0)
        {
            // handle must oneOf property
            must_count += 1;
            // $.'$tight#OneOf'.oneOf
            res = json_model_6(pval, (path ? &lpath_33 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [$.'$tight#OneOf'.oneOf]", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#OneOf'.oneOf]", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_33_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_33 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#OneOf']", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#OneOf']", (path ? &lpath_33 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#OneOf']", path);
        return false;
    }
    return true;
}

// check $tight#OneOf ($.'$tight#OneOf')
static bool json_model_21(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#OneOf'
    res = _jm_obj_33(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#OneOf']", path);
    }
    return res;
}

// check _jm_obj_36_map_$comment ($.'$tight#Enum'.'$comment')
static bool _jm_f_128(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Enum'.'$defs'
static bool _jm_obj_37(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Enum'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_37 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Enum'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_37 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Enum'.'$defs'.'']", (path ? &lpath_37 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_36_map_$defs ($.'$tight#Enum'.'$defs')
static bool _jm_f_129(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.'$defs'
    res = _jm_obj_37(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Enum'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_36_map_$id ($.'$tight#Enum'.'$id')
static bool _jm_f_130(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.'$id']", path);
    }
    return res;
}

// check _jm_obj_36_map_$schema ($.'$tight#Enum'.'$schema')
static bool _jm_f_131(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_36_map_default ($.'$tight#Enum'.default)
static bool _jm_f_132(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Enum'.default]", path);
    }
    return res;
}

// object $.'$tight#Enum'.definitions
static bool _jm_obj_38(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Enum'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_38 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Enum'.definitions.''
        res = json_model_26(pval, (path ? &lpath_38 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Enum'.definitions.'']", (path ? &lpath_38 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_36_map_definitions ($.'$tight#Enum'.definitions)
static bool _jm_f_133(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.definitions
    res = _jm_obj_38(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Enum'.definitions]", path);
    }
    return res;
}

// check _jm_obj_36_map_description ($.'$tight#Enum'.description)
static bool _jm_f_134(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.description]", path);
    }
    return res;
}

// check _jm_obj_36_map_examples ($.'$tight#Enum'.examples)
static bool _jm_f_135(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Enum'.examples]", path);
    }
    return res;
}

// check _jm_obj_36_map_id ($.'$tight#Enum'.id)
static bool _jm_f_136(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.id]", path);
    }
    return res;
}

// check _jm_obj_36_map_title ($.'$tight#Enum'.title)
static bool _jm_f_137(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Enum'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_36_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_36_map_tab, 10);
}

// object $.'$tight#Enum'
static bool _jm_obj_36(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Enum']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_36 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "enum") == 0)
        {
            // handle must enum property
            must_count += 1;
            // $.'$tight#Enum'.enum
            res = json_model_5(pval, (path ? &lpath_36 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $enum [$.'$tight#Enum'.enum]", (path ? &lpath_36 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Enum'.enum]", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_36_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_36 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Enum']", (path ? &lpath_36 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Enum']", (path ? &lpath_36 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Enum']", path);
        return false;
    }
    return true;
}

// check $tight#Enum ($.'$tight#Enum')
static bool json_model_22(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Enum'
    res = _jm_obj_36(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Enum']", path);
    }
    return res;
}

// check $tight#enum ($.'$tight#enum')
static bool json_model_5(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#enum'
    res = json_is_array(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected type at [$.'$tight#enum'.'|']", path);
    }
    if (res)
    {
        // $.'$tight#enum'.'|'.0
        res = true;
        if (res)
        {
            size_t arr_4_idx;
            json_t *arr_4_item;
            json_array_foreach(val, arr_4_idx, arr_4_item)
            {
                Path arr_4_lpath = (Path) { NULL, arr_4_idx, path, NULL };
                // $.'$tight#enum'.'|'.0.0
                res = json_is_string(arr_4_item);
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#enum'.'|'.0.0]", (path ? &arr_4_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#enum'.'|'.0]", path);
        }
        if (! res)
        {
            // $.'$tight#enum'.'|'.1
            res = true;
            if (res)
            {
                size_t arr_3_idx;
                json_t *arr_3_item;
                json_array_foreach(val, arr_3_idx, arr_3_item)
                {
                    Path arr_3_lpath = (Path) { NULL, arr_3_idx, path, NULL };
                    // $.'$tight#enum'.'|'.1.0
                    res = json_is_integer(arr_3_item);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$tight#enum'.'|'.1.0]", (path ? &arr_3_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#enum'.'|'.1]", path);
            }
            if (! res)
            {
                // $.'$tight#enum'.'|'.2
                res = true;
                if (res)
                {
                    size_t arr_2_idx;
                    json_t *arr_2_item;
                    json_array_foreach(val, arr_2_idx, arr_2_item)
                    {
                        Path arr_2_lpath = (Path) { NULL, arr_2_idx, path, NULL };
                        // $.'$tight#enum'.'|'.2.0
                        res = json_is_boolean(arr_2_item);
                        if (res)
                        {
                            if (rep) jm_report_free_entries(rep);
                        }
                        else
                        {
                            if (rep) jm_report_add_entry(rep, "not a bool [$.'$tight#enum'.'|'.2.0]", (path ? &arr_2_lpath : NULL));
                        }
                        if (! res)
                        {
                            break;
                        }
                    }
                }
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#enum'.'|'.2]", path);
                }
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [$.'$tight#enum'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_39_map_$comment ($.'$tight#Const'.'$comment')
static bool _jm_f_138(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Const'.'$defs'
static bool _jm_obj_40(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Const'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_40 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Const'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_40 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Const'.'$defs'.'']", (path ? &lpath_40 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_39_map_$defs ($.'$tight#Const'.'$defs')
static bool _jm_f_139(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.'$defs'
    res = _jm_obj_40(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Const'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_39_map_$id ($.'$tight#Const'.'$id')
static bool _jm_f_140(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.'$id']", path);
    }
    return res;
}

// check _jm_obj_39_map_$schema ($.'$tight#Const'.'$schema')
static bool _jm_f_141(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_39_map_default ($.'$tight#Const'.default)
static bool _jm_f_142(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Const'.default]", path);
    }
    return res;
}

// object $.'$tight#Const'.definitions
static bool _jm_obj_41(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Const'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_41 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Const'.definitions.''
        res = json_model_26(pval, (path ? &lpath_41 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Const'.definitions.'']", (path ? &lpath_41 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_39_map_definitions ($.'$tight#Const'.definitions)
static bool _jm_f_143(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.definitions
    res = _jm_obj_41(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Const'.definitions]", path);
    }
    return res;
}

// check _jm_obj_39_map_description ($.'$tight#Const'.description)
static bool _jm_f_144(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.description]", path);
    }
    return res;
}

// check _jm_obj_39_map_examples ($.'$tight#Const'.examples)
static bool _jm_f_145(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Const'.examples]", path);
    }
    return res;
}

// check _jm_obj_39_map_id ($.'$tight#Const'.id)
static bool _jm_f_146(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.id]", path);
    }
    return res;
}

// check _jm_obj_39_map_title ($.'$tight#Const'.title)
static bool _jm_f_147(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Const'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_39_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_39_map_tab, 10);
}

// object $.'$tight#Const'
static bool _jm_obj_39(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Const']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_39 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // $.'$tight#Const'.const
            res = json_model_4(pval, (path ? &lpath_39 : NULL), rep);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $const [$.'$tight#Const'.const]", (path ? &lpath_39 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Const'.const]", (path ? &lpath_39 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_39_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_39 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Const']", (path ? &lpath_39 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Const']", (path ? &lpath_39 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Const']", path);
        return false;
    }
    return true;
}

// check $tight#Const ($.'$tight#Const')
static bool json_model_23(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Const'
    res = _jm_obj_39(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Const']", path);
    }
    return res;
}

// check $tight#const ($.'$tight#const')
static bool json_model_4(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#const'
    // $.'$tight#const'.'|'.0
    res = json_is_null(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not null [$.'$tight#const'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$tight#const'.'|'.1
        res = json_is_boolean(val);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "not a bool [$.'$tight#const'.'|'.1]", path);
        }
        if (! res)
        {
            // $.'$tight#const'.'|'.2
            res = json_is_integer(val);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$tight#const'.'|'.2]", path);
            }
            if (! res)
            {
                // $.'$tight#const'.'|'.3
                res = json_is_real(val);
                if (res)
                {
                    if (rep) jm_report_free_entries(rep);
                }
                else
                {
                    if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#const'.'|'.3]", path);
                }
                if (! res)
                {
                    // $.'$tight#const'.'|'.4
                    res = json_is_string(val);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#const'.'|'.4]", path);
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
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$tight#const'.'|']", path);
    }
    return res;
}

// check _jm_obj_42_map_$comment ($.'$tight#Ref'.'$comment')
static bool _jm_f_148(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#Ref'.'$defs'
static bool _jm_obj_43(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Ref'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_43 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Ref'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_43 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Ref'.'$defs'.'']", (path ? &lpath_43 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_42_map_$defs ($.'$tight#Ref'.'$defs')
static bool _jm_f_149(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.'$defs'
    res = _jm_obj_43(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Ref'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_42_map_$id ($.'$tight#Ref'.'$id')
static bool _jm_f_150(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.'$id']", path);
    }
    return res;
}

// check _jm_obj_42_map_$schema ($.'$tight#Ref'.'$schema')
static bool _jm_f_151(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_42_map_default ($.'$tight#Ref'.default)
static bool _jm_f_152(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#Ref'.default]", path);
    }
    return res;
}

// object $.'$tight#Ref'.definitions
static bool _jm_obj_44(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Ref'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_44 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#Ref'.definitions.''
        res = json_model_26(pval, (path ? &lpath_44 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#Ref'.definitions.'']", (path ? &lpath_44 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_42_map_definitions ($.'$tight#Ref'.definitions)
static bool _jm_f_153(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.definitions
    res = _jm_obj_44(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Ref'.definitions]", path);
    }
    return res;
}

// check _jm_obj_42_map_description ($.'$tight#Ref'.description)
static bool _jm_f_154(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.description]", path);
    }
    return res;
}

// check _jm_obj_42_map_examples ($.'$tight#Ref'.examples)
static bool _jm_f_155(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#Ref'.examples]", path);
    }
    return res;
}

// check _jm_obj_42_map_id ($.'$tight#Ref'.id)
static bool _jm_f_156(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.id]", path);
    }
    return res;
}

// check _jm_obj_42_map_title ($.'$tight#Ref'.title)
static bool _jm_f_157(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#Ref'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_42_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_42_map_tab, 10);
}

// object $.'$tight#Ref'
static bool _jm_obj_42(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#Ref']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_42 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "$ref") == 0)
        {
            // handle must $ref property
            must_count += 1;
            // $.'$tight#Ref'.'$ref'
            res = jm_is_valid_url(json_string_value(pval));
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [$.'$tight#Ref'.'$ref']", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#Ref'.$ref]", (path ? &lpath_42 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_42_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_42 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#Ref']", (path ? &lpath_42 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#Ref']", (path ? &lpath_42 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#Ref']", path);
        return false;
    }
    return true;
}

// check $tight#Ref ($.'$tight#Ref')
static bool json_model_24(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Ref'
    res = _jm_obj_42(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#Ref']", path);
    }
    return res;
}

// check $tight#Schema ($.'$tight#Schema')
static bool json_model_26(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#Schema'
    // $.'$tight#Schema'.'|'.0
    res = json_is_boolean(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not a bool [$.'$tight#Schema'.'|'.0]", path);
    }
    if (! res)
    {
        // $.'$tight#Schema'.'|'.1
        res = json_model_25(val, path, rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [$.'$tight#Schema'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [$.'$tight#Schema'.'|']", path);
    }
    return res;
}

// check _jm_obj_45_map_$comment ($.'$tight#EnumString'.'$comment')
static bool _jm_f_158(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#EnumString'.'$defs'
static bool _jm_obj_46(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumString'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_46 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumString'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_46 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumString'.'$defs'.'']", (path ? &lpath_46 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_45_map_$defs ($.'$tight#EnumString'.'$defs')
static bool _jm_f_159(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.'$defs'
    res = _jm_obj_46(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumString'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_45_map_$id ($.'$tight#EnumString'.'$id')
static bool _jm_f_160(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.'$id']", path);
    }
    return res;
}

// check _jm_obj_45_map_$schema ($.'$tight#EnumString'.'$schema')
static bool _jm_f_161(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_45_map_default ($.'$tight#EnumString'.default)
static bool _jm_f_162(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#EnumString'.default]", path);
    }
    return res;
}

// object $.'$tight#EnumString'.definitions
static bool _jm_obj_47(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumString'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_47 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumString'.definitions.''
        res = json_model_26(pval, (path ? &lpath_47 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumString'.definitions.'']", (path ? &lpath_47 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_45_map_definitions ($.'$tight#EnumString'.definitions)
static bool _jm_f_163(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.definitions
    res = _jm_obj_47(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumString'.definitions]", path);
    }
    return res;
}

// check _jm_obj_45_map_description ($.'$tight#EnumString'.description)
static bool _jm_f_164(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.description]", path);
    }
    return res;
}

// check _jm_obj_45_map_examples ($.'$tight#EnumString'.examples)
static bool _jm_f_165(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumString'.examples]", path);
    }
    return res;
}

// check _jm_obj_45_map_id ($.'$tight#EnumString'.id)
static bool _jm_f_166(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.id]", path);
    }
    return res;
}

// check _jm_obj_45_map_title ($.'$tight#EnumString'.title)
static bool _jm_f_167(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_45_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_45_map_tab, 10);
}

// object $.'$tight#EnumString'
static bool _jm_obj_45(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumString']", path);
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
        if (strcmp(prop, "enum") == 0)
        {
            // handle must enum property
            must_count += 1;
            // $.'$tight#EnumString'.enum
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_5_idx;
                json_t *arr_5_item;
                json_array_foreach(pval, arr_5_idx, arr_5_item)
                {
                    Path arr_5_lpath = (Path) { NULL, arr_5_idx, (path ? &lpath_45 : NULL), NULL };
                    // $.'$tight#EnumString'.enum.0
                    res = json_is_string(arr_5_item);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.enum.0]", ((path ? &lpath_45 : NULL) ? &arr_5_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumString'.enum]", (path ? &lpath_45 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumString'.enum]", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#EnumString'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumString'.type]", (path ? &lpath_45 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumString'.type]", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_45_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_45 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#EnumString']", (path ? &lpath_45 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#EnumString']", (path ? &lpath_45 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#EnumString']", path);
        return false;
    }
    return true;
}

// check $tight#EnumString ($.'$tight#EnumString')
static bool json_model_28(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumString'
    res = _jm_obj_45(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumString']", path);
    }
    return res;
}

// check _jm_obj_48_map_$comment ($.'$tight#EnumNum'.'$comment')
static bool _jm_f_168(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#EnumNum'.'$defs'
static bool _jm_obj_49(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumNum'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_49 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumNum'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_49 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumNum'.'$defs'.'']", (path ? &lpath_49 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_48_map_$defs ($.'$tight#EnumNum'.'$defs')
static bool _jm_f_169(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.'$defs'
    res = _jm_obj_49(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumNum'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_48_map_$id ($.'$tight#EnumNum'.'$id')
static bool _jm_f_170(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.'$id']", path);
    }
    return res;
}

// check _jm_obj_48_map_$schema ($.'$tight#EnumNum'.'$schema')
static bool _jm_f_171(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_48_map_default ($.'$tight#EnumNum'.default)
static bool _jm_f_172(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#EnumNum'.default]", path);
    }
    return res;
}

// object $.'$tight#EnumNum'.definitions
static bool _jm_obj_50(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumNum'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_50 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumNum'.definitions.''
        res = json_model_26(pval, (path ? &lpath_50 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumNum'.definitions.'']", (path ? &lpath_50 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_48_map_definitions ($.'$tight#EnumNum'.definitions)
static bool _jm_f_173(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.definitions
    res = _jm_obj_50(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumNum'.definitions]", path);
    }
    return res;
}

// check _jm_obj_48_map_description ($.'$tight#EnumNum'.description)
static bool _jm_f_174(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.description]", path);
    }
    return res;
}

// check _jm_obj_48_map_examples ($.'$tight#EnumNum'.examples)
static bool _jm_f_175(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumNum'.examples]", path);
    }
    return res;
}

// check _jm_obj_48_map_id ($.'$tight#EnumNum'.id)
static bool _jm_f_176(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.id]", path);
    }
    return res;
}

// check _jm_obj_48_map_title ($.'$tight#EnumNum'.title)
static bool _jm_f_177(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumNum'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_48_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_48_map_tab, 10);
}

// object $.'$tight#EnumNum'
static bool _jm_obj_48(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumNum']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_48 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "enum") == 0)
        {
            // handle must enum property
            must_count += 1;
            // $.'$tight#EnumNum'.enum
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_6_idx;
                json_t *arr_6_item;
                json_array_foreach(pval, arr_6_idx, arr_6_item)
                {
                    Path arr_6_lpath = (Path) { NULL, arr_6_idx, (path ? &lpath_48 : NULL), NULL };
                    // $.'$tight#EnumNum'.enum.0
                    res = json_is_real(arr_6_item);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#EnumNum'.enum.0]", ((path ? &lpath_48 : NULL) ? &arr_6_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumNum'.enum]", (path ? &lpath_48 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumNum'.enum]", (path ? &lpath_48 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#EnumNum'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected number [$.'$tight#EnumNum'.type]", (path ? &lpath_48 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumNum'.type]", (path ? &lpath_48 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_48_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_48 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#EnumNum']", (path ? &lpath_48 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#EnumNum']", (path ? &lpath_48 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#EnumNum']", path);
        return false;
    }
    return true;
}

// check $tight#EnumNum ($.'$tight#EnumNum')
static bool json_model_29(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumNum'
    res = _jm_obj_48(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumNum']", path);
    }
    return res;
}

// check _jm_obj_51_map_$comment ($.'$tight#EnumInt'.'$comment')
static bool _jm_f_178(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#EnumInt'.'$defs'
static bool _jm_obj_52(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumInt'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_52 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumInt'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_52 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumInt'.'$defs'.'']", (path ? &lpath_52 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_51_map_$defs ($.'$tight#EnumInt'.'$defs')
static bool _jm_f_179(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.'$defs'
    res = _jm_obj_52(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumInt'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_51_map_$id ($.'$tight#EnumInt'.'$id')
static bool _jm_f_180(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.'$id']", path);
    }
    return res;
}

// check _jm_obj_51_map_$schema ($.'$tight#EnumInt'.'$schema')
static bool _jm_f_181(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_51_map_default ($.'$tight#EnumInt'.default)
static bool _jm_f_182(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#EnumInt'.default]", path);
    }
    return res;
}

// object $.'$tight#EnumInt'.definitions
static bool _jm_obj_53(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumInt'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_53 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#EnumInt'.definitions.''
        res = json_model_26(pval, (path ? &lpath_53 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#EnumInt'.definitions.'']", (path ? &lpath_53 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_51_map_definitions ($.'$tight#EnumInt'.definitions)
static bool _jm_f_183(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.definitions
    res = _jm_obj_53(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumInt'.definitions]", path);
    }
    return res;
}

// check _jm_obj_51_map_description ($.'$tight#EnumInt'.description)
static bool _jm_f_184(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.description]", path);
    }
    return res;
}

// check _jm_obj_51_map_examples ($.'$tight#EnumInt'.examples)
static bool _jm_f_185(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumInt'.examples]", path);
    }
    return res;
}

// check _jm_obj_51_map_id ($.'$tight#EnumInt'.id)
static bool _jm_f_186(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.id]", path);
    }
    return res;
}

// check _jm_obj_51_map_title ($.'$tight#EnumInt'.title)
static bool _jm_f_187(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#EnumInt'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_51_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_51_map_tab, 10);
}

// object $.'$tight#EnumInt'
static bool _jm_obj_51(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#EnumInt']", path);
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
        if (strcmp(prop, "enum") == 0)
        {
            // handle must enum property
            must_count += 1;
            // $.'$tight#EnumInt'.enum
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_7_idx;
                json_t *arr_7_item;
                json_array_foreach(pval, arr_7_idx, arr_7_item)
                {
                    Path arr_7_lpath = (Path) { NULL, arr_7_idx, (path ? &lpath_51 : NULL), NULL };
                    // $.'$tight#EnumInt'.enum.0
                    res = json_is_integer(arr_7_item);
                    if (res)
                    {
                        if (rep) jm_report_free_entries(rep);
                    }
                    else
                    {
                        if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$tight#EnumInt'.enum.0]", ((path ? &lpath_51 : NULL) ? &arr_7_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#EnumInt'.enum]", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumInt'.enum]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#EnumInt'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected integer [$.'$tight#EnumInt'.type]", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#EnumInt'.type]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_51_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_51 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#EnumInt']", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#EnumInt']", (path ? &lpath_51 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#EnumInt']", path);
        return false;
    }
    return true;
}

// check $tight#EnumInt ($.'$tight#EnumInt')
static bool json_model_30(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#EnumInt'
    res = _jm_obj_51(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#EnumInt']", path);
    }
    return res;
}

// check _jm_obj_54_map_$comment ($.'$tight#ConstString'.'$comment')
static bool _jm_f_188(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#ConstString'.'$defs'
static bool _jm_obj_55(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstString'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_55 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstString'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_55 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstString'.'$defs'.'']", (path ? &lpath_55 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_54_map_$defs ($.'$tight#ConstString'.'$defs')
static bool _jm_f_189(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.'$defs'
    res = _jm_obj_55(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstString'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_54_map_$id ($.'$tight#ConstString'.'$id')
static bool _jm_f_190(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.'$id']", path);
    }
    return res;
}

// check _jm_obj_54_map_$schema ($.'$tight#ConstString'.'$schema')
static bool _jm_f_191(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_54_map_default ($.'$tight#ConstString'.default)
static bool _jm_f_192(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#ConstString'.default]", path);
    }
    return res;
}

// object $.'$tight#ConstString'.definitions
static bool _jm_obj_56(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstString'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_56 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstString'.definitions.''
        res = json_model_26(pval, (path ? &lpath_56 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstString'.definitions.'']", (path ? &lpath_56 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_54_map_definitions ($.'$tight#ConstString'.definitions)
static bool _jm_f_193(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.definitions
    res = _jm_obj_56(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstString'.definitions]", path);
    }
    return res;
}

// check _jm_obj_54_map_description ($.'$tight#ConstString'.description)
static bool _jm_f_194(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.description]", path);
    }
    return res;
}

// check _jm_obj_54_map_examples ($.'$tight#ConstString'.examples)
static bool _jm_f_195(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#ConstString'.examples]", path);
    }
    return res;
}

// check _jm_obj_54_map_id ($.'$tight#ConstString'.id)
static bool _jm_f_196(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.id]", path);
    }
    return res;
}

// check _jm_obj_54_map_title ($.'$tight#ConstString'.title)
static bool _jm_f_197(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_54_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_54_map_tab, 10);
}

// object $.'$tight#ConstString'
static bool _jm_obj_54(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstString']", path);
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
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // $.'$tight#ConstString'.const
            res = json_is_string(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.const]", (path ? &lpath_54 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstString'.const]", (path ? &lpath_54 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#ConstString'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstString'.type]", (path ? &lpath_54 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstString'.type]", (path ? &lpath_54 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_54_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_54 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#ConstString']", (path ? &lpath_54 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#ConstString']", (path ? &lpath_54 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#ConstString']", path);
        return false;
    }
    return true;
}

// check $tight#ConstString ($.'$tight#ConstString')
static bool json_model_31(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstString'
    res = _jm_obj_54(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstString']", path);
    }
    return res;
}

// check _jm_obj_57_map_$comment ($.'$tight#ConstNum'.'$comment')
static bool _jm_f_198(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#ConstNum'.'$defs'
static bool _jm_obj_58(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstNum'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_58 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstNum'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_58 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstNum'.'$defs'.'']", (path ? &lpath_58 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_57_map_$defs ($.'$tight#ConstNum'.'$defs')
static bool _jm_f_199(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.'$defs'
    res = _jm_obj_58(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstNum'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_57_map_$id ($.'$tight#ConstNum'.'$id')
static bool _jm_f_200(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.'$id']", path);
    }
    return res;
}

// check _jm_obj_57_map_$schema ($.'$tight#ConstNum'.'$schema')
static bool _jm_f_201(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_57_map_default ($.'$tight#ConstNum'.default)
static bool _jm_f_202(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#ConstNum'.default]", path);
    }
    return res;
}

// object $.'$tight#ConstNum'.definitions
static bool _jm_obj_59(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstNum'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_59 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstNum'.definitions.''
        res = json_model_26(pval, (path ? &lpath_59 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstNum'.definitions.'']", (path ? &lpath_59 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_57_map_definitions ($.'$tight#ConstNum'.definitions)
static bool _jm_f_203(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.definitions
    res = _jm_obj_59(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstNum'.definitions]", path);
    }
    return res;
}

// check _jm_obj_57_map_description ($.'$tight#ConstNum'.description)
static bool _jm_f_204(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.description]", path);
    }
    return res;
}

// check _jm_obj_57_map_examples ($.'$tight#ConstNum'.examples)
static bool _jm_f_205(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#ConstNum'.examples]", path);
    }
    return res;
}

// check _jm_obj_57_map_id ($.'$tight#ConstNum'.id)
static bool _jm_f_206(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.id]", path);
    }
    return res;
}

// check _jm_obj_57_map_title ($.'$tight#ConstNum'.title)
static bool _jm_f_207(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstNum'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_57_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_57_map_tab, 10);
}

// object $.'$tight#ConstNum'
static bool _jm_obj_57(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstNum']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_57 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // $.'$tight#ConstNum'.const
            res = json_is_real(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [$.'$tight#ConstNum'.const]", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstNum'.const]", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#ConstNum'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected number [$.'$tight#ConstNum'.type]", (path ? &lpath_57 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstNum'.type]", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_57_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_57 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#ConstNum']", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#ConstNum']", (path ? &lpath_57 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#ConstNum']", path);
        return false;
    }
    return true;
}

// check $tight#ConstNum ($.'$tight#ConstNum')
static bool json_model_32(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstNum'
    res = _jm_obj_57(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstNum']", path);
    }
    return res;
}

// check _jm_obj_60_map_$comment ($.'$tight#ConstInt'.'$comment')
static bool _jm_f_208(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#ConstInt'.'$defs'
static bool _jm_obj_61(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstInt'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_61 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstInt'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_61 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstInt'.'$defs'.'']", (path ? &lpath_61 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_60_map_$defs ($.'$tight#ConstInt'.'$defs')
static bool _jm_f_209(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.'$defs'
    res = _jm_obj_61(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstInt'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_60_map_$id ($.'$tight#ConstInt'.'$id')
static bool _jm_f_210(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.'$id']", path);
    }
    return res;
}

// check _jm_obj_60_map_$schema ($.'$tight#ConstInt'.'$schema')
static bool _jm_f_211(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_60_map_default ($.'$tight#ConstInt'.default)
static bool _jm_f_212(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#ConstInt'.default]", path);
    }
    return res;
}

// object $.'$tight#ConstInt'.definitions
static bool _jm_obj_62(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstInt'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_62 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstInt'.definitions.''
        res = json_model_26(pval, (path ? &lpath_62 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstInt'.definitions.'']", (path ? &lpath_62 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_60_map_definitions ($.'$tight#ConstInt'.definitions)
static bool _jm_f_213(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.definitions
    res = _jm_obj_62(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstInt'.definitions]", path);
    }
    return res;
}

// check _jm_obj_60_map_description ($.'$tight#ConstInt'.description)
static bool _jm_f_214(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.description]", path);
    }
    return res;
}

// check _jm_obj_60_map_examples ($.'$tight#ConstInt'.examples)
static bool _jm_f_215(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#ConstInt'.examples]", path);
    }
    return res;
}

// check _jm_obj_60_map_id ($.'$tight#ConstInt'.id)
static bool _jm_f_216(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.id]", path);
    }
    return res;
}

// check _jm_obj_60_map_title ($.'$tight#ConstInt'.title)
static bool _jm_f_217(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstInt'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_60_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_60_map_tab, 10);
}

// object $.'$tight#ConstInt'
static bool _jm_obj_60(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstInt']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_60 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // $.'$tight#ConstInt'.const
            res = json_is_integer(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a -1 strict int [$.'$tight#ConstInt'.const]", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstInt'.const]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#ConstInt'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected integer [$.'$tight#ConstInt'.type]", (path ? &lpath_60 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstInt'.type]", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_60_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_60 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#ConstInt']", (path ? &lpath_60 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#ConstInt']", (path ? &lpath_60 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#ConstInt']", path);
        return false;
    }
    return true;
}

// check $tight#ConstInt ($.'$tight#ConstInt')
static bool json_model_33(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstInt'
    res = _jm_obj_60(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstInt']", path);
    }
    return res;
}

// check _jm_obj_63_map_$comment ($.'$tight#ConstBool'.'$comment')
static bool _jm_f_218(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.'$comment'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.'$comment']", path);
    }
    return res;
}

// object $.'$tight#ConstBool'.'$defs'
static bool _jm_obj_64(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstBool'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_64 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstBool'.'$defs'.''
        res = json_model_26(pval, (path ? &lpath_64 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstBool'.'$defs'.'']", (path ? &lpath_64 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_63_map_$defs ($.'$tight#ConstBool'.'$defs')
static bool _jm_f_219(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.'$defs'
    res = _jm_obj_64(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstBool'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_63_map_$id ($.'$tight#ConstBool'.'$id')
static bool _jm_f_220(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.'$id'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.'$id']", path);
    }
    return res;
}

// check _jm_obj_63_map_$schema ($.'$tight#ConstBool'.'$schema')
static bool _jm_f_221(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.'$schema'
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.'$schema']", path);
    }
    return res;
}

// check _jm_obj_63_map_default ($.'$tight#ConstBool'.default)
static bool _jm_f_222(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.default
    res = true;
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [$.'$tight#ConstBool'.default]", path);
    }
    return res;
}

// object $.'$tight#ConstBool'.definitions
static bool _jm_obj_65(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstBool'.definitions]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_65 = (Path) { prop, 0, path, NULL };
        // handle other props
        // $.'$tight#ConstBool'.definitions.''
        res = json_model_26(pval, (path ? &lpath_65 : NULL), rep);
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [$.'$tight#ConstBool'.definitions.'']", (path ? &lpath_65 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_63_map_definitions ($.'$tight#ConstBool'.definitions)
static bool _jm_f_223(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.definitions
    res = _jm_obj_65(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstBool'.definitions]", path);
    }
    return res;
}

// check _jm_obj_63_map_description ($.'$tight#ConstBool'.description)
static bool _jm_f_224(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.description
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.description]", path);
    }
    return res;
}

// check _jm_obj_63_map_examples ($.'$tight#ConstBool'.examples)
static bool _jm_f_225(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [$.'$tight#ConstBool'.examples]", path);
    }
    return res;
}

// check _jm_obj_63_map_id ($.'$tight#ConstBool'.id)
static bool _jm_f_226(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.id
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.id]", path);
    }
    return res;
}

// check _jm_obj_63_map_title ($.'$tight#ConstBool'.title)
static bool _jm_f_227(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'.title
    res = json_is_string(val);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [$.'$tight#ConstBool'.title]", path);
    }
    return res;
}

static check_fun_t _jm_obj_63_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_63_map_tab, 10);
}

// object $.'$tight#ConstBool'
static bool _jm_obj_63(const json_t* val, Path* path, Report* rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [$.'$tight#ConstBool']", path);
        return false;
    }
    bool res;
    check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        Path lpath_63 = (Path) { prop, 0, path, NULL };
        if (strcmp(prop, "const") == 0)
        {
            // handle must const property
            must_count += 1;
            // $.'$tight#ConstBool'.const
            res = json_is_boolean(pval);
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "not a bool [$.'$tight#ConstBool'.const]", (path ? &lpath_63 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstBool'.const]", (path ? &lpath_63 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // $.'$tight#ConstBool'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "boolean") == 0;
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "unexpected boolean [$.'$tight#ConstBool'.type]", (path ? &lpath_63 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid must property value [$.'$tight#ConstBool'.type]", (path ? &lpath_63 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_63_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_63 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid may property value [$.'$tight#ConstBool']", (path ? &lpath_63 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no other prop expected [$.'$tight#ConstBool']", (path ? &lpath_63 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep) jm_report_add_entry(rep, "missing must prop [$.'$tight#ConstBool']", path);
        return false;
    }
    return true;
}

// check $tight#ConstBool ($.'$tight#ConstBool')
static bool json_model_34(const json_t* val, Path* path, Report* rep)
{
    bool res;
    // $.'$tight#ConstBool'
    res = _jm_obj_63(val, path, rep);
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "not an expected object at [$.'$tight#ConstBool']", path);
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
        _jm_obj_1_map_tab[0] = (propmap_t) { "$comment", _jm_f_0 };
        _jm_obj_1_map_tab[1] = (propmap_t) { "$defs", _jm_f_1 };
        _jm_obj_1_map_tab[2] = (propmap_t) { "$id", _jm_f_2 };
        _jm_obj_1_map_tab[3] = (propmap_t) { "$schema", _jm_f_3 };
        _jm_obj_1_map_tab[4] = (propmap_t) { "default", _jm_f_4 };
        _jm_obj_1_map_tab[5] = (propmap_t) { "definitions", _jm_f_5 };
        _jm_obj_1_map_tab[6] = (propmap_t) { "description", _jm_f_6 };
        _jm_obj_1_map_tab[7] = (propmap_t) { "examples", _jm_f_7 };
        _jm_obj_1_map_tab[8] = (propmap_t) { "id", _jm_f_8 };
        _jm_obj_1_map_tab[9] = (propmap_t) { "title", _jm_f_9 };
        jm_sort_propmap(_jm_obj_1_map_tab, 10);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (constant_t) { cst_is_string, { .s = "uri" } };
        _jm_cst_0[1] = (constant_t) { cst_is_string, { .s = "uri-reference" } };
        _jm_cst_0[2] = (constant_t) { cst_is_string, { .s = "iri" } };
        _jm_cst_0[3] = (constant_t) { cst_is_string, { .s = "iri-reference" } };
        _jm_cst_0[4] = (constant_t) { cst_is_string, { .s = "date" } };
        _jm_cst_0[5] = (constant_t) { cst_is_string, { .s = "time" } };
        _jm_cst_0[6] = (constant_t) { cst_is_string, { .s = "date-time" } };
        _jm_cst_0[7] = (constant_t) { cst_is_string, { .s = "ipv4" } };
        _jm_cst_0[8] = (constant_t) { cst_is_string, { .s = "ipv6" } };
        _jm_cst_0[9] = (constant_t) { cst_is_string, { .s = "regex" } };
        _jm_cst_0[10] = (constant_t) { cst_is_string, { .s = "uuid" } };
        _jm_cst_0[11] = (constant_t) { cst_is_string, { .s = "hostname" } };
        _jm_cst_0[12] = (constant_t) { cst_is_string, { .s = "email" } };
        _jm_cst_0[13] = (constant_t) { cst_is_string, { .s = "idn-hostname" } };
        _jm_cst_0[14] = (constant_t) { cst_is_string, { .s = "idn-email" } };
        _jm_cst_0[15] = (constant_t) { cst_is_string, { .s = "duration" } };
        _jm_cst_0[16] = (constant_t) { cst_is_string, { .s = "int32" } };
        _jm_cst_0[17] = (constant_t) { cst_is_string, { .s = "int64" } };
        _jm_cst_0[18] = (constant_t) { cst_is_string, { .s = "uint" } };
        _jm_cst_0[19] = (constant_t) { cst_is_string, { .s = "uint32" } };
        _jm_cst_0[20] = (constant_t) { cst_is_string, { .s = "uint64" } };
        _jm_cst_0[21] = (constant_t) { cst_is_string, { .s = "json-pointer" } };
        _jm_cst_0[22] = (constant_t) { cst_is_string, { .s = "relative-json-pointer" } };
        _jm_cst_0[23] = (constant_t) { cst_is_string, { .s = "byte" } };
        _jm_cst_0[24] = (constant_t) { cst_is_string, { .s = "double" } };
        _jm_cst_0[25] = (constant_t) { cst_is_string, { .s = "int" } };
        _jm_cst_0[26] = (constant_t) { cst_is_string, { .s = "mime-type" } };
        jm_sort_cst(_jm_cst_0, 27);
        _jm_obj_4_map_tab[0] = (propmap_t) { "$comment", _jm_f_10 };
        _jm_obj_4_map_tab[1] = (propmap_t) { "$defs", _jm_f_11 };
        _jm_obj_4_map_tab[2] = (propmap_t) { "$id", _jm_f_12 };
        _jm_obj_4_map_tab[3] = (propmap_t) { "$schema", _jm_f_13 };
        _jm_obj_4_map_tab[4] = (propmap_t) { "default", _jm_f_14 };
        _jm_obj_4_map_tab[5] = (propmap_t) { "definitions", _jm_f_15 };
        _jm_obj_4_map_tab[6] = (propmap_t) { "description", _jm_f_16 };
        _jm_obj_4_map_tab[7] = (propmap_t) { "examples", _jm_f_17 };
        _jm_obj_4_map_tab[8] = (propmap_t) { "format", _jm_f_18 };
        _jm_obj_4_map_tab[9] = (propmap_t) { "id", _jm_f_19 };
        _jm_obj_4_map_tab[10] = (propmap_t) { "maxLength", _jm_f_20 };
        _jm_obj_4_map_tab[11] = (propmap_t) { "minLength", _jm_f_21 };
        _jm_obj_4_map_tab[12] = (propmap_t) { "pattern", _jm_f_22 };
        _jm_obj_4_map_tab[13] = (propmap_t) { "title", _jm_f_23 };
        jm_sort_propmap(_jm_obj_4_map_tab, 14);
        _jm_obj_7_map_tab[0] = (propmap_t) { "$comment", _jm_f_24 };
        _jm_obj_7_map_tab[1] = (propmap_t) { "$defs", _jm_f_25 };
        _jm_obj_7_map_tab[2] = (propmap_t) { "$id", _jm_f_26 };
        _jm_obj_7_map_tab[3] = (propmap_t) { "$schema", _jm_f_27 };
        _jm_obj_7_map_tab[4] = (propmap_t) { "additionalItems", _jm_f_28 };
        _jm_obj_7_map_tab[5] = (propmap_t) { "default", _jm_f_29 };
        _jm_obj_7_map_tab[6] = (propmap_t) { "definitions", _jm_f_30 };
        _jm_obj_7_map_tab[7] = (propmap_t) { "description", _jm_f_31 };
        _jm_obj_7_map_tab[8] = (propmap_t) { "examples", _jm_f_32 };
        _jm_obj_7_map_tab[9] = (propmap_t) { "id", _jm_f_33 };
        _jm_obj_7_map_tab[10] = (propmap_t) { "items", _jm_f_34 };
        _jm_obj_7_map_tab[11] = (propmap_t) { "maxItems", _jm_f_35 };
        _jm_obj_7_map_tab[12] = (propmap_t) { "minItems", _jm_f_36 };
        _jm_obj_7_map_tab[13] = (propmap_t) { "prefixItems", _jm_f_37 };
        _jm_obj_7_map_tab[14] = (propmap_t) { "title", _jm_f_38 };
        _jm_obj_7_map_tab[15] = (propmap_t) { "uniqueItems", _jm_f_39 };
        jm_sort_propmap(_jm_obj_7_map_tab, 16);
        _jm_obj_10_map_tab[0] = (propmap_t) { "$comment", _jm_f_40 };
        _jm_obj_10_map_tab[1] = (propmap_t) { "$defs", _jm_f_41 };
        _jm_obj_10_map_tab[2] = (propmap_t) { "$id", _jm_f_42 };
        _jm_obj_10_map_tab[3] = (propmap_t) { "$schema", _jm_f_43 };
        _jm_obj_10_map_tab[4] = (propmap_t) { "additionalProperties", _jm_f_44 };
        _jm_obj_10_map_tab[5] = (propmap_t) { "default", _jm_f_45 };
        _jm_obj_10_map_tab[6] = (propmap_t) { "definitions", _jm_f_46 };
        _jm_obj_10_map_tab[7] = (propmap_t) { "description", _jm_f_47 };
        _jm_obj_10_map_tab[8] = (propmap_t) { "examples", _jm_f_48 };
        _jm_obj_10_map_tab[9] = (propmap_t) { "id", _jm_f_49 };
        _jm_obj_10_map_tab[10] = (propmap_t) { "patternProperties", _jm_f_50 };
        _jm_obj_10_map_tab[11] = (propmap_t) { "properties", _jm_f_51 };
        _jm_obj_10_map_tab[12] = (propmap_t) { "required", _jm_f_52 };
        _jm_obj_10_map_tab[13] = (propmap_t) { "title", _jm_f_53 };
        jm_sort_propmap(_jm_obj_10_map_tab, 14);
        _jm_obj_15_map_tab[0] = (propmap_t) { "$comment", _jm_f_54 };
        _jm_obj_15_map_tab[1] = (propmap_t) { "$defs", _jm_f_55 };
        _jm_obj_15_map_tab[2] = (propmap_t) { "$id", _jm_f_56 };
        _jm_obj_15_map_tab[3] = (propmap_t) { "$schema", _jm_f_57 };
        _jm_obj_15_map_tab[4] = (propmap_t) { "default", _jm_f_58 };
        _jm_obj_15_map_tab[5] = (propmap_t) { "definitions", _jm_f_59 };
        _jm_obj_15_map_tab[6] = (propmap_t) { "description", _jm_f_60 };
        _jm_obj_15_map_tab[7] = (propmap_t) { "examples", _jm_f_61 };
        _jm_obj_15_map_tab[8] = (propmap_t) { "id", _jm_f_62 };
        _jm_obj_15_map_tab[9] = (propmap_t) { "maximum", _jm_f_63 };
        _jm_obj_15_map_tab[10] = (propmap_t) { "minimum", _jm_f_64 };
        _jm_obj_15_map_tab[11] = (propmap_t) { "title", _jm_f_65 };
        jm_sort_propmap(_jm_obj_15_map_tab, 12);
        _jm_obj_18_map_tab[0] = (propmap_t) { "$comment", _jm_f_66 };
        _jm_obj_18_map_tab[1] = (propmap_t) { "$defs", _jm_f_67 };
        _jm_obj_18_map_tab[2] = (propmap_t) { "$id", _jm_f_68 };
        _jm_obj_18_map_tab[3] = (propmap_t) { "$schema", _jm_f_69 };
        _jm_obj_18_map_tab[4] = (propmap_t) { "default", _jm_f_70 };
        _jm_obj_18_map_tab[5] = (propmap_t) { "definitions", _jm_f_71 };
        _jm_obj_18_map_tab[6] = (propmap_t) { "description", _jm_f_72 };
        _jm_obj_18_map_tab[7] = (propmap_t) { "examples", _jm_f_73 };
        _jm_obj_18_map_tab[8] = (propmap_t) { "id", _jm_f_74 };
        _jm_obj_18_map_tab[9] = (propmap_t) { "maximum", _jm_f_75 };
        _jm_obj_18_map_tab[10] = (propmap_t) { "minimum", _jm_f_76 };
        _jm_obj_18_map_tab[11] = (propmap_t) { "title", _jm_f_77 };
        jm_sort_propmap(_jm_obj_18_map_tab, 12);
        _jm_obj_21_map_tab[0] = (propmap_t) { "$comment", _jm_f_78 };
        _jm_obj_21_map_tab[1] = (propmap_t) { "$defs", _jm_f_79 };
        _jm_obj_21_map_tab[2] = (propmap_t) { "$id", _jm_f_80 };
        _jm_obj_21_map_tab[3] = (propmap_t) { "$schema", _jm_f_81 };
        _jm_obj_21_map_tab[4] = (propmap_t) { "default", _jm_f_82 };
        _jm_obj_21_map_tab[5] = (propmap_t) { "definitions", _jm_f_83 };
        _jm_obj_21_map_tab[6] = (propmap_t) { "description", _jm_f_84 };
        _jm_obj_21_map_tab[7] = (propmap_t) { "examples", _jm_f_85 };
        _jm_obj_21_map_tab[8] = (propmap_t) { "id", _jm_f_86 };
        _jm_obj_21_map_tab[9] = (propmap_t) { "title", _jm_f_87 };
        jm_sort_propmap(_jm_obj_21_map_tab, 10);
        _jm_obj_24_map_tab[0] = (propmap_t) { "$comment", _jm_f_88 };
        _jm_obj_24_map_tab[1] = (propmap_t) { "$defs", _jm_f_89 };
        _jm_obj_24_map_tab[2] = (propmap_t) { "$id", _jm_f_90 };
        _jm_obj_24_map_tab[3] = (propmap_t) { "$schema", _jm_f_91 };
        _jm_obj_24_map_tab[4] = (propmap_t) { "default", _jm_f_92 };
        _jm_obj_24_map_tab[5] = (propmap_t) { "definitions", _jm_f_93 };
        _jm_obj_24_map_tab[6] = (propmap_t) { "description", _jm_f_94 };
        _jm_obj_24_map_tab[7] = (propmap_t) { "examples", _jm_f_95 };
        _jm_obj_24_map_tab[8] = (propmap_t) { "id", _jm_f_96 };
        _jm_obj_24_map_tab[9] = (propmap_t) { "title", _jm_f_97 };
        jm_sort_propmap(_jm_obj_24_map_tab, 10);
        _jm_obj_27_map_tab[0] = (propmap_t) { "$comment", _jm_f_98 };
        _jm_obj_27_map_tab[1] = (propmap_t) { "$defs", _jm_f_99 };
        _jm_obj_27_map_tab[2] = (propmap_t) { "$id", _jm_f_100 };
        _jm_obj_27_map_tab[3] = (propmap_t) { "$schema", _jm_f_101 };
        _jm_obj_27_map_tab[4] = (propmap_t) { "default", _jm_f_102 };
        _jm_obj_27_map_tab[5] = (propmap_t) { "definitions", _jm_f_103 };
        _jm_obj_27_map_tab[6] = (propmap_t) { "description", _jm_f_104 };
        _jm_obj_27_map_tab[7] = (propmap_t) { "examples", _jm_f_105 };
        _jm_obj_27_map_tab[8] = (propmap_t) { "id", _jm_f_106 };
        _jm_obj_27_map_tab[9] = (propmap_t) { "title", _jm_f_107 };
        jm_sort_propmap(_jm_obj_27_map_tab, 10);
        _jm_obj_30_map_tab[0] = (propmap_t) { "$comment", _jm_f_108 };
        _jm_obj_30_map_tab[1] = (propmap_t) { "$defs", _jm_f_109 };
        _jm_obj_30_map_tab[2] = (propmap_t) { "$id", _jm_f_110 };
        _jm_obj_30_map_tab[3] = (propmap_t) { "$schema", _jm_f_111 };
        _jm_obj_30_map_tab[4] = (propmap_t) { "default", _jm_f_112 };
        _jm_obj_30_map_tab[5] = (propmap_t) { "definitions", _jm_f_113 };
        _jm_obj_30_map_tab[6] = (propmap_t) { "description", _jm_f_114 };
        _jm_obj_30_map_tab[7] = (propmap_t) { "examples", _jm_f_115 };
        _jm_obj_30_map_tab[8] = (propmap_t) { "id", _jm_f_116 };
        _jm_obj_30_map_tab[9] = (propmap_t) { "title", _jm_f_117 };
        jm_sort_propmap(_jm_obj_30_map_tab, 10);
        _jm_obj_33_map_tab[0] = (propmap_t) { "$comment", _jm_f_118 };
        _jm_obj_33_map_tab[1] = (propmap_t) { "$defs", _jm_f_119 };
        _jm_obj_33_map_tab[2] = (propmap_t) { "$id", _jm_f_120 };
        _jm_obj_33_map_tab[3] = (propmap_t) { "$schema", _jm_f_121 };
        _jm_obj_33_map_tab[4] = (propmap_t) { "default", _jm_f_122 };
        _jm_obj_33_map_tab[5] = (propmap_t) { "definitions", _jm_f_123 };
        _jm_obj_33_map_tab[6] = (propmap_t) { "description", _jm_f_124 };
        _jm_obj_33_map_tab[7] = (propmap_t) { "examples", _jm_f_125 };
        _jm_obj_33_map_tab[8] = (propmap_t) { "id", _jm_f_126 };
        _jm_obj_33_map_tab[9] = (propmap_t) { "title", _jm_f_127 };
        jm_sort_propmap(_jm_obj_33_map_tab, 10);
        _jm_obj_36_map_tab[0] = (propmap_t) { "$comment", _jm_f_128 };
        _jm_obj_36_map_tab[1] = (propmap_t) { "$defs", _jm_f_129 };
        _jm_obj_36_map_tab[2] = (propmap_t) { "$id", _jm_f_130 };
        _jm_obj_36_map_tab[3] = (propmap_t) { "$schema", _jm_f_131 };
        _jm_obj_36_map_tab[4] = (propmap_t) { "default", _jm_f_132 };
        _jm_obj_36_map_tab[5] = (propmap_t) { "definitions", _jm_f_133 };
        _jm_obj_36_map_tab[6] = (propmap_t) { "description", _jm_f_134 };
        _jm_obj_36_map_tab[7] = (propmap_t) { "examples", _jm_f_135 };
        _jm_obj_36_map_tab[8] = (propmap_t) { "id", _jm_f_136 };
        _jm_obj_36_map_tab[9] = (propmap_t) { "title", _jm_f_137 };
        jm_sort_propmap(_jm_obj_36_map_tab, 10);
        _jm_obj_39_map_tab[0] = (propmap_t) { "$comment", _jm_f_138 };
        _jm_obj_39_map_tab[1] = (propmap_t) { "$defs", _jm_f_139 };
        _jm_obj_39_map_tab[2] = (propmap_t) { "$id", _jm_f_140 };
        _jm_obj_39_map_tab[3] = (propmap_t) { "$schema", _jm_f_141 };
        _jm_obj_39_map_tab[4] = (propmap_t) { "default", _jm_f_142 };
        _jm_obj_39_map_tab[5] = (propmap_t) { "definitions", _jm_f_143 };
        _jm_obj_39_map_tab[6] = (propmap_t) { "description", _jm_f_144 };
        _jm_obj_39_map_tab[7] = (propmap_t) { "examples", _jm_f_145 };
        _jm_obj_39_map_tab[8] = (propmap_t) { "id", _jm_f_146 };
        _jm_obj_39_map_tab[9] = (propmap_t) { "title", _jm_f_147 };
        jm_sort_propmap(_jm_obj_39_map_tab, 10);
        _jm_obj_42_map_tab[0] = (propmap_t) { "$comment", _jm_f_148 };
        _jm_obj_42_map_tab[1] = (propmap_t) { "$defs", _jm_f_149 };
        _jm_obj_42_map_tab[2] = (propmap_t) { "$id", _jm_f_150 };
        _jm_obj_42_map_tab[3] = (propmap_t) { "$schema", _jm_f_151 };
        _jm_obj_42_map_tab[4] = (propmap_t) { "default", _jm_f_152 };
        _jm_obj_42_map_tab[5] = (propmap_t) { "definitions", _jm_f_153 };
        _jm_obj_42_map_tab[6] = (propmap_t) { "description", _jm_f_154 };
        _jm_obj_42_map_tab[7] = (propmap_t) { "examples", _jm_f_155 };
        _jm_obj_42_map_tab[8] = (propmap_t) { "id", _jm_f_156 };
        _jm_obj_42_map_tab[9] = (propmap_t) { "title", _jm_f_157 };
        jm_sort_propmap(_jm_obj_42_map_tab, 10);
        _jm_obj_45_map_tab[0] = (propmap_t) { "$comment", _jm_f_158 };
        _jm_obj_45_map_tab[1] = (propmap_t) { "$defs", _jm_f_159 };
        _jm_obj_45_map_tab[2] = (propmap_t) { "$id", _jm_f_160 };
        _jm_obj_45_map_tab[3] = (propmap_t) { "$schema", _jm_f_161 };
        _jm_obj_45_map_tab[4] = (propmap_t) { "default", _jm_f_162 };
        _jm_obj_45_map_tab[5] = (propmap_t) { "definitions", _jm_f_163 };
        _jm_obj_45_map_tab[6] = (propmap_t) { "description", _jm_f_164 };
        _jm_obj_45_map_tab[7] = (propmap_t) { "examples", _jm_f_165 };
        _jm_obj_45_map_tab[8] = (propmap_t) { "id", _jm_f_166 };
        _jm_obj_45_map_tab[9] = (propmap_t) { "title", _jm_f_167 };
        jm_sort_propmap(_jm_obj_45_map_tab, 10);
        _jm_obj_48_map_tab[0] = (propmap_t) { "$comment", _jm_f_168 };
        _jm_obj_48_map_tab[1] = (propmap_t) { "$defs", _jm_f_169 };
        _jm_obj_48_map_tab[2] = (propmap_t) { "$id", _jm_f_170 };
        _jm_obj_48_map_tab[3] = (propmap_t) { "$schema", _jm_f_171 };
        _jm_obj_48_map_tab[4] = (propmap_t) { "default", _jm_f_172 };
        _jm_obj_48_map_tab[5] = (propmap_t) { "definitions", _jm_f_173 };
        _jm_obj_48_map_tab[6] = (propmap_t) { "description", _jm_f_174 };
        _jm_obj_48_map_tab[7] = (propmap_t) { "examples", _jm_f_175 };
        _jm_obj_48_map_tab[8] = (propmap_t) { "id", _jm_f_176 };
        _jm_obj_48_map_tab[9] = (propmap_t) { "title", _jm_f_177 };
        jm_sort_propmap(_jm_obj_48_map_tab, 10);
        _jm_obj_51_map_tab[0] = (propmap_t) { "$comment", _jm_f_178 };
        _jm_obj_51_map_tab[1] = (propmap_t) { "$defs", _jm_f_179 };
        _jm_obj_51_map_tab[2] = (propmap_t) { "$id", _jm_f_180 };
        _jm_obj_51_map_tab[3] = (propmap_t) { "$schema", _jm_f_181 };
        _jm_obj_51_map_tab[4] = (propmap_t) { "default", _jm_f_182 };
        _jm_obj_51_map_tab[5] = (propmap_t) { "definitions", _jm_f_183 };
        _jm_obj_51_map_tab[6] = (propmap_t) { "description", _jm_f_184 };
        _jm_obj_51_map_tab[7] = (propmap_t) { "examples", _jm_f_185 };
        _jm_obj_51_map_tab[8] = (propmap_t) { "id", _jm_f_186 };
        _jm_obj_51_map_tab[9] = (propmap_t) { "title", _jm_f_187 };
        jm_sort_propmap(_jm_obj_51_map_tab, 10);
        _jm_obj_54_map_tab[0] = (propmap_t) { "$comment", _jm_f_188 };
        _jm_obj_54_map_tab[1] = (propmap_t) { "$defs", _jm_f_189 };
        _jm_obj_54_map_tab[2] = (propmap_t) { "$id", _jm_f_190 };
        _jm_obj_54_map_tab[3] = (propmap_t) { "$schema", _jm_f_191 };
        _jm_obj_54_map_tab[4] = (propmap_t) { "default", _jm_f_192 };
        _jm_obj_54_map_tab[5] = (propmap_t) { "definitions", _jm_f_193 };
        _jm_obj_54_map_tab[6] = (propmap_t) { "description", _jm_f_194 };
        _jm_obj_54_map_tab[7] = (propmap_t) { "examples", _jm_f_195 };
        _jm_obj_54_map_tab[8] = (propmap_t) { "id", _jm_f_196 };
        _jm_obj_54_map_tab[9] = (propmap_t) { "title", _jm_f_197 };
        jm_sort_propmap(_jm_obj_54_map_tab, 10);
        _jm_obj_57_map_tab[0] = (propmap_t) { "$comment", _jm_f_198 };
        _jm_obj_57_map_tab[1] = (propmap_t) { "$defs", _jm_f_199 };
        _jm_obj_57_map_tab[2] = (propmap_t) { "$id", _jm_f_200 };
        _jm_obj_57_map_tab[3] = (propmap_t) { "$schema", _jm_f_201 };
        _jm_obj_57_map_tab[4] = (propmap_t) { "default", _jm_f_202 };
        _jm_obj_57_map_tab[5] = (propmap_t) { "definitions", _jm_f_203 };
        _jm_obj_57_map_tab[6] = (propmap_t) { "description", _jm_f_204 };
        _jm_obj_57_map_tab[7] = (propmap_t) { "examples", _jm_f_205 };
        _jm_obj_57_map_tab[8] = (propmap_t) { "id", _jm_f_206 };
        _jm_obj_57_map_tab[9] = (propmap_t) { "title", _jm_f_207 };
        jm_sort_propmap(_jm_obj_57_map_tab, 10);
        _jm_obj_60_map_tab[0] = (propmap_t) { "$comment", _jm_f_208 };
        _jm_obj_60_map_tab[1] = (propmap_t) { "$defs", _jm_f_209 };
        _jm_obj_60_map_tab[2] = (propmap_t) { "$id", _jm_f_210 };
        _jm_obj_60_map_tab[3] = (propmap_t) { "$schema", _jm_f_211 };
        _jm_obj_60_map_tab[4] = (propmap_t) { "default", _jm_f_212 };
        _jm_obj_60_map_tab[5] = (propmap_t) { "definitions", _jm_f_213 };
        _jm_obj_60_map_tab[6] = (propmap_t) { "description", _jm_f_214 };
        _jm_obj_60_map_tab[7] = (propmap_t) { "examples", _jm_f_215 };
        _jm_obj_60_map_tab[8] = (propmap_t) { "id", _jm_f_216 };
        _jm_obj_60_map_tab[9] = (propmap_t) { "title", _jm_f_217 };
        jm_sort_propmap(_jm_obj_60_map_tab, 10);
        _jm_obj_63_map_tab[0] = (propmap_t) { "$comment", _jm_f_218 };
        _jm_obj_63_map_tab[1] = (propmap_t) { "$defs", _jm_f_219 };
        _jm_obj_63_map_tab[2] = (propmap_t) { "$id", _jm_f_220 };
        _jm_obj_63_map_tab[3] = (propmap_t) { "$schema", _jm_f_221 };
        _jm_obj_63_map_tab[4] = (propmap_t) { "default", _jm_f_222 };
        _jm_obj_63_map_tab[5] = (propmap_t) { "definitions", _jm_f_223 };
        _jm_obj_63_map_tab[6] = (propmap_t) { "description", _jm_f_224 };
        _jm_obj_63_map_tab[7] = (propmap_t) { "examples", _jm_f_225 };
        _jm_obj_63_map_tab[8] = (propmap_t) { "id", _jm_f_226 };
        _jm_obj_63_map_tab[9] = (propmap_t) { "title", _jm_f_227 };
        jm_sort_propmap(_jm_obj_63_map_tab, 10);
        check_model_map_tab[0] = (propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (propmap_t) { "tight", json_model_3 };
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
