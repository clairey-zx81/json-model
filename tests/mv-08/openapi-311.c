#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static pcre2_code *_jm_re_0_code = NULL;
static pcre2_match_data *_jm_re_0_data = NULL;
static bool _jm_re_0(const char *s);
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_0_map_tab[8];
static pcre2_code *_jm_re_1_code = NULL;
static pcre2_match_data *_jm_re_1_data = NULL;
static bool _jm_re_1(const char *s);
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_2_map_tab[5];
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_9_map_tab[10];
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_2_code = NULL;
static pcre2_match_data *_jm_re_2_data = NULL;
static bool _jm_re_2(const char *s);
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_21_map_tab[13];
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep);
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
static jm_propmap_t _jm_obj_22_map_tab[12];
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_48(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_49(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_50(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_51(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_25_map_tab[4];
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_0[4];
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_26_map_tab[4];
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_1[7];
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_27_map_tab[6];
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_2[4];
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_31_map_tab[5];
static jm_constant_t _jm_cst_3[4];
static bool _jm_f_67(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_68(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_69(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_70(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_71(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_72(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_73(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_74(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_75(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_76(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_33_map_tab[10];
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_37_map_tab[4];
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_40_map_tab[5];
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static pcre2_code *_jm_re_3_code = NULL;
static pcre2_match_data *_jm_re_3_data = NULL;
static bool _jm_re_3(const char *s);
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_43_map_tab[4];
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_92(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_93(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_48_map_tab[4];
static bool json_model_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_26(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_94(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_95(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_96(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_97(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_49_map_tab[4];
static bool _jm_f_98(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_99(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_100(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_101(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_51_map_tab[4];
static bool json_model_27(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_102(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_103(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_104(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_105(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_106(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_53_map_tab[5];
static bool _jm_f_107(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_108(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_109(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_110(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_111(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_112(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_113(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_114(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_115(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_116(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_55_map_tab[10];
static bool json_model_28(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_29(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_30(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_40(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_117(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_118(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_119(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_120(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_121(const json_t *val, jm_path_t *path, jm_report_t *rep);
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
static bool _jm_f_172(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_173(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_174(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_175(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_176(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_177(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_59_map_tab[61];
static bool json_model_32(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_33(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_178(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_179(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_180(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_181(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_182(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_68_map_tab[5];
static bool json_model_34(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_183(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_4[3];
static bool _jm_f_184(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_185(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_186(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_187(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_188(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_69_mup_tab[6];
static bool json_model_35(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_189(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_190(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_191(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_192(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_70_map_tab[4];
static bool json_model_36(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_37(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_38(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_39(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_41(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_constant_t _jm_cst_5[7];
static bool json_model_47(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_48(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_49(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_50(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_52(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_55(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_193(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_194(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_195(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_196(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_197(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_198(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_199(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_200(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_201(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_202(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_203(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_204(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_205(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_206(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_207(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_208(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_209(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_210(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_211(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_212(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_213(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_214(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_215(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_216(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_217(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_218(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_219(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_220(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_221(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_222(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_223(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_224(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_225(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_226(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_227(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_228(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_229(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_230(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_231(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_232(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_233(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_234(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_235(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_236(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_237(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_238(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_239(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_240(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_241(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_242(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_243(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_244(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_245(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_246(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_247(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_248(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_249(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_75_map_tab[57];
static bool json_model_54(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[39];
const size_t check_model_map_size = 39;

static bool _jm_re_0(const char *s)
{
  int rc = pcre2_match(_jm_re_0_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_0_data, NULL);
  return rc >= 0;
}

// check _jm_obj_0_map_component (.'$OpenAPI'.component)
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.component
    res = json_model_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Components [.'$OpenAPI'.component]", path);
    }
    return res;
}

// check _jm_obj_0_map_externalDocs (.'$OpenAPI'.externalDocs)
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.externalDocs
    res = json_model_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$OpenAPI'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_0_map_jsonSchemaDialect (.'$OpenAPI'.jsonSchemaDialect)
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.jsonSchemaDialect
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$OpenAPI'.jsonSchemaDialect]", path);
    }
    return res;
}

// check _jm_obj_0_map_paths (.'$OpenAPI'.paths)
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.paths
    res = json_model_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Paths [.'$OpenAPI'.paths]", path);
    }
    return res;
}

// check _jm_obj_0_map_security (.'$OpenAPI'.security)
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.security
    res = json_model_38(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [.'$OpenAPI'.security]", path);
    }
    return res;
}

// check _jm_obj_0_map_servers (.'$OpenAPI'.servers)
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
            // .'$OpenAPI'.servers.0
            res = json_model_6(arr_0_item, (path ? &arr_0_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$OpenAPI'.servers.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$OpenAPI'.servers]", path);
    }
    return res;
}

// check _jm_obj_0_map_tags (.'$OpenAPI'.tags)
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, path, NULL };
            // .'$OpenAPI'.tags.0
            res = json_model_29(arr_1_item, (path ? &arr_1_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Tag [.'$OpenAPI'.tags.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$OpenAPI'.tags]", path);
    }
    return res;
}

// object .'$OpenAPI'.webhooks
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OpenAPI'.webhooks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$OpenAPI'.webhooks.''
        res = json_model_10(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$OpenAPI'.webhooks.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_webhooks (.'$OpenAPI'.webhooks)
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'.webhooks
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OpenAPI'.webhooks]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 8);
}

static bool _jm_re_1(const char *s)
{
  int rc = pcre2_match(_jm_re_1_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_1_data, NULL);
  return rc >= 0;
}

// object .'$OpenAPI'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OpenAPI']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_0 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "openapi") == 0)
        {
            // handle must openapi property
            must_count += 1;
            // .'$OpenAPI'.openapi
            // "/^3\\.1\\.\\d+(-.+)?$/"
            res = json_is_string(pval) && _jm_re_0(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected /^3\\.1\\.\\d+(-.+)?$/ [.'$OpenAPI'.openapi]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OpenAPI'.openapi]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "info") == 0)
        {
            // handle must info property
            must_count += 1;
            // .'$OpenAPI'.info
            res = json_model_3(pval, (path ? &lpath_0 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Info [.'$OpenAPI'.info]", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OpenAPI'.info]", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_0_map(prop)))
        {
            // handle 8 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$OpenAPI']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$OpenAPI'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$OpenAPI'.'/^x\\\\-.*$/']", (path ? &lpath_0 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$OpenAPI']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "info") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <info> [.'$OpenAPI']", path);
            }
            if (! (json_object_get(val, "openapi") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <openapi> [.'$OpenAPI']", path);
            }
        }
        return false;
    }
    return true;
}

// check $OpenAPI (.'$OpenAPI')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OpenAPI'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OpenAPI']", path);
    }
    return res;
}

// check _jm_obj_2_map_contact (.'$Info'.contact)
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'.contact
    res = json_model_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Contact [.'$Info'.contact]", path);
    }
    return res;
}

// check _jm_obj_2_map_description (.'$Info'.description)
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Info'.description]", path);
    }
    return res;
}

// check _jm_obj_2_map_license (.'$Info'.license)
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'.license
    res = json_model_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $License [.'$Info'.license]", path);
    }
    return res;
}

// check _jm_obj_2_map_summary (.'$Info'.summary)
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Info'.summary]", path);
    }
    return res;
}

// check _jm_obj_2_map_termsOfService (.'$Info'.termsOfService)
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'.termsOfService
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Info'.termsOfService]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_2_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_2_map_tab, 5);
}

// object .'$Info'
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Info']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "title") == 0)
        {
            // handle must title property
            must_count += 1;
            // .'$Info'.title
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Info'.title]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Info'.title]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "version") == 0)
        {
            // handle must version property
            must_count += 1;
            // .'$Info'.version
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Info'.version]", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Info'.version]", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_2_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_2 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Info']", (path ? &lpath_2 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Info'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Info'.'/^x\\\\-.*$/']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Info']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "title") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <title> [.'$Info']", path);
            }
            if (! (json_object_get(val, "version") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <version> [.'$Info']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Info (.'$Info')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Info'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Info']", path);
    }
    return res;
}

// object .'$Contact'
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Contact']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle may name property
            // .'$Contact'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Contact'.name]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Contact'.name]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "url") == 0)
        {
            // handle may url property
            // .'$Contact'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$Contact'.url]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Contact'.url]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "email") == 0)
        {
            // handle may email property
            // .'$Contact'.email
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Contact'.email]", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Contact'.email]", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Contact'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Contact'.'/^x\\\\-.*$/']", (path ? &lpath_3 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Contact']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    return true;
}

// check $Contact (.'$Contact')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Contact'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Contact']", path);
    }
    return res;
}

// object .'$License'.'|'.1
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$License'.'|'.1]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$License'.'|'.1.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$License'.'|'.1.name]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$License'.'|'.1.name]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$License'.'|'.1.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$License'.'|'.1.url]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$License'.'|'.1.url]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$License'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$License'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$License'.'|'.1]", (path ? &lpath_4 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$License'.'|'.1]", path);
            }
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <url> [.'$License'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// object .'$License'.'|'.0
static bool _jm_obj_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$License'.'|'.0]", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_5 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$License'.'|'.0.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$License'.'|'.0.name]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$License'.'|'.0.name]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "identifier") == 0)
        {
            // handle must identifier property
            must_count += 1;
            // .'$License'.'|'.0.identifier
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$License'.'|'.0.identifier]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$License'.'|'.0.identifier]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$License'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$License'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$License'.'|'.0]", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "identifier") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <identifier> [.'$License'.'|'.0]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$License'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $License (.'$License')
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$License'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$License'.'|']", path);
    }
    if (res)
    {
        // .'$License'.'|'.0
        res = _jm_obj_5(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$License'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$License'.'|'.1
            res = _jm_obj_4(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$License'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$License'.'|']", path);
        }
    }
    return res;
}

// object .'$Server'.variables
static bool _jm_obj_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Server'.variables]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_7 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Server'.variables.''
        res = json_model_7(pval, (path ? &lpath_7 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ServerVariable [.'$Server'.variables.'']", (path ? &lpath_7 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$Server'
static bool _jm_obj_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Server']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_6 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$Server'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$Server'.url]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Server'.url]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$Server'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Server'.description]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Server'.description]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "variables") == 0)
        {
            // handle may variables property
            // .'$Server'.variables
            res = _jm_obj_7(pval, (path ? &lpath_6 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Server'.variables]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Server'.variables]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Server'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Server'.'/^x\\\\-.*$/']", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Server']", (path ? &lpath_6 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <url> [.'$Server']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Server (.'$Server')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Server'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Server']", path);
    }
    return res;
}

// object .'$ServerVariable'
static bool _jm_obj_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$ServerVariable']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_8 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "default") == 0)
        {
            // handle must default property
            must_count += 1;
            // .'$ServerVariable'.default
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$ServerVariable'.default]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$ServerVariable'.default]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "enum") == 0)
        {
            // handle may enum property
            // .'$ServerVariable'.enum
            res = json_is_array(pval);
            if (res)
            {
                size_t arr_2_idx;
                json_t *arr_2_item;
                json_array_foreach(pval, arr_2_idx, arr_2_item)
                {
                    jm_path_t arr_2_lpath = (jm_path_t) { NULL, arr_2_idx, (path ? &lpath_8 : NULL), NULL };
                    // .'$ServerVariable'.enum.0
                    res = json_is_string(arr_2_item);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "unexpected string [.'$ServerVariable'.enum.0]", ((path ? &lpath_8 : NULL) ? &arr_2_lpath : NULL));
                    }
                    if (! res)
                    {
                        break;
                    }
                }
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$ServerVariable'.enum]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$ServerVariable'.enum]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$ServerVariable'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$ServerVariable'.description]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$ServerVariable'.description]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$ServerVariable'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$ServerVariable'.'/^x\\\\-.*$/']", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$ServerVariable']", (path ? &lpath_8 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "default") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <default> [.'$ServerVariable']", path);
            }
        }
        return false;
    }
    return true;
}

// check $ServerVariable (.'$ServerVariable')
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ServerVariable'
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$ServerVariable']", path);
    }
    return res;
}

// object .'$Components'.callbacks
static bool _jm_obj_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_10 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.callbacks.''
        // .'$Components'.callbacks.''.'|'.0
        res = json_model_24(pval, (path ? &lpath_10 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [.'$Components'.callbacks.''.'|'.0]", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            // .'$Components'.callbacks.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_10 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.callbacks.''.'|'.1]", (path ? &lpath_10 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.callbacks.''.'|']", (path ? &lpath_10 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_callbacks (.'$Components'.callbacks)
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.callbacks
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.callbacks]", path);
    }
    return res;
}

// object .'$Components'.examples
static bool _jm_obj_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_11 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.examples.''
        // .'$Components'.examples.''.'|'.0
        res = json_model_25(pval, (path ? &lpath_11 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$Components'.examples.''.'|'.0]", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            // .'$Components'.examples.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_11 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.examples.''.'|'.1]", (path ? &lpath_11 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.examples.''.'|']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_examples (.'$Components'.examples)
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.examples
    res = _jm_obj_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.examples]", path);
    }
    return res;
}

// object .'$Components'.headers
static bool _jm_obj_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_12 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.headers.''
        // .'$Components'.headers.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_12 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$Components'.headers.''.'|'.0]", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            // .'$Components'.headers.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_12 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.headers.''.'|'.1]", (path ? &lpath_12 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.headers.''.'|']", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_headers (.'$Components'.headers)
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.headers
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.headers]", path);
    }
    return res;
}

// object .'$Components'.links
static bool _jm_obj_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_13 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.links.''
        // .'$Components'.links.''.'|'.0
        res = json_model_27(pval, (path ? &lpath_13 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [.'$Components'.links.''.'|'.0]", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            // .'$Components'.links.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_13 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.links.''.'|'.1]", (path ? &lpath_13 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.links.''.'|']", (path ? &lpath_13 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_links (.'$Components'.links)
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.links
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.links]", path);
    }
    return res;
}

// object .'$Components'.parameters
static bool _jm_obj_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.parameters]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_14 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.parameters.''
        // .'$Components'.parameters.''.'|'.0
        res = json_model_18(pval, (path ? &lpath_14 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$Components'.parameters.''.'|'.0]", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            // .'$Components'.parameters.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_14 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.parameters.''.'|'.1]", (path ? &lpath_14 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.parameters.''.'|']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_parameters (.'$Components'.parameters)
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.parameters
    res = _jm_obj_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.parameters]", path);
    }
    return res;
}

// object .'$Components'.pathItems
static bool _jm_obj_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.pathItems]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_15 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.pathItems.''
        // .'$Components'.pathItems.''.'|'.0
        res = json_model_10(pval, (path ? &lpath_15 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$Components'.pathItems.''.'|'.0]", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            // .'$Components'.pathItems.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_15 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.pathItems.''.'|'.1]", (path ? &lpath_15 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.pathItems.''.'|']", (path ? &lpath_15 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_pathItems (.'$Components'.pathItems)
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.pathItems
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.pathItems]", path);
    }
    return res;
}

// object .'$Components'.requestBodies
static bool _jm_obj_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.requestBodies]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_16 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.requestBodies.''
        // .'$Components'.requestBodies.''.'|'.0
        res = json_model_19(pval, (path ? &lpath_16 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [.'$Components'.requestBodies.''.'|'.0]", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            // .'$Components'.requestBodies.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_16 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.requestBodies.''.'|'.1]", (path ? &lpath_16 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.requestBodies.''.'|']", (path ? &lpath_16 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_requestBodies (.'$Components'.requestBodies)
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.requestBodies
    res = _jm_obj_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.requestBodies]", path);
    }
    return res;
}

// object .'$Components'.responses
static bool _jm_obj_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.responses]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_17 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.responses.''
        // .'$Components'.responses.''.'|'.0
        res = json_model_23(pval, (path ? &lpath_17 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$Components'.responses.''.'|'.0]", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            // .'$Components'.responses.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_17 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.responses.''.'|'.1]", (path ? &lpath_17 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.responses.''.'|']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_responses (.'$Components'.responses)
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.responses
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.responses]", path);
    }
    return res;
}

// object .'$Components'.schemas
static bool _jm_obj_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.schemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_18 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.schemas.''
        res = json_model_32(pval, (path ? &lpath_18 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Components'.schemas.'']", (path ? &lpath_18 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_schemas (.'$Components'.schemas)
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.schemas
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.schemas]", path);
    }
    return res;
}

// object .'$Components'.securitySchemes
static bool _jm_obj_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components'.securitySchemes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_19 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Components'.securitySchemes.''
        // .'$Components'.securitySchemes.''.'|'.0
        res = json_model_35(pval, (path ? &lpath_19 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $SecurityScheme [.'$Components'.securitySchemes.''.'|'.0]", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            // .'$Components'.securitySchemes.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_19 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Components'.securitySchemes.''.'|'.1]", (path ? &lpath_19 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Components'.securitySchemes.''.'|']", (path ? &lpath_19 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_9_map_securitySchemes (.'$Components'.securitySchemes)
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'.securitySchemes
    res = _jm_obj_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components'.securitySchemes]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_9_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_map_tab, 10);
}

// object .'$Components'
static bool _jm_obj_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Components']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_9 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_9_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_9 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Components']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Components'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Components'.'/^x\\\\-.*$/']", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Components']", (path ? &lpath_9 : NULL));
            return false;
        }
    }
    return true;
}

// check $Components (.'$Components')
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Components'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Components']", path);
    }
    return res;
}

static bool _jm_re_2(const char *s)
{
  int rc = pcre2_match(_jm_re_2_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_2_data, NULL);
  return rc >= 0;
}

// object .'$Paths'
static bool _jm_obj_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Paths']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_20 = (jm_path_t) { prop, 0, path, NULL };
        if (_jm_re_2(prop))
        {
            // handle 2 re props
            // .'$Paths'.'/^//'
            res = json_model_10(pval, (path ? &lpath_20 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$Paths'.'/^//']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Paths'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Paths'.'/^x\\\\-.*$/']", (path ? &lpath_20 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Paths']", (path ? &lpath_20 : NULL));
            return false;
        }
    }
    return true;
}

// check $Paths (.'$Paths')
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Paths'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Paths']", path);
    }
    return res;
}

// check _jm_obj_21_map_$ref (.'$PathItem'.'$ref')
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.'$ref'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$PathItem'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_21_map_delete (.'$PathItem'.delete)
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.delete
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.delete]", path);
    }
    return res;
}

// check _jm_obj_21_map_description (.'$PathItem'.description)
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$PathItem'.description]", path);
    }
    return res;
}

// check _jm_obj_21_map_get (.'$PathItem'.get)
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.get
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.get]", path);
    }
    return res;
}

// check _jm_obj_21_map_head (.'$PathItem'.head)
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.head
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.head]", path);
    }
    return res;
}

// check _jm_obj_21_map_options (.'$PathItem'.options)
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.options
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.options]", path);
    }
    return res;
}

// check _jm_obj_21_map_parameters (.'$PathItem'.parameters)
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.parameters
    res = json_is_array(val);
    if (res)
    {
        size_t arr_3_idx;
        json_t *arr_3_item;
        json_array_foreach(val, arr_3_idx, arr_3_item)
        {
            jm_path_t arr_3_lpath = (jm_path_t) { NULL, arr_3_idx, path, NULL };
            // .'$PathItem'.parameters.0
            // .'$PathItem'.parameters.0.'|'.0
            res = json_model_18(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$PathItem'.parameters.0.'|'.0]", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                // .'$PathItem'.parameters.0.'|'.1
                res = json_model_30(arr_3_item, (path ? &arr_3_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$PathItem'.parameters.0.'|'.1]", (path ? &arr_3_lpath : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$PathItem'.parameters.0.'|']", (path ? &arr_3_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$PathItem'.parameters]", path);
    }
    return res;
}

// check _jm_obj_21_map_patch (.'$PathItem'.patch)
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.patch
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.patch]", path);
    }
    return res;
}

// check _jm_obj_21_map_post (.'$PathItem'.post)
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.post
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.post]", path);
    }
    return res;
}

// check _jm_obj_21_map_put (.'$PathItem'.put)
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.put
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.put]", path);
    }
    return res;
}

// check _jm_obj_21_map_servers (.'$PathItem'.servers)
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_4_idx;
        json_t *arr_4_item;
        json_array_foreach(val, arr_4_idx, arr_4_item)
        {
            jm_path_t arr_4_lpath = (jm_path_t) { NULL, arr_4_idx, path, NULL };
            // .'$PathItem'.servers.0
            res = json_model_11(arr_4_item, (path ? &arr_4_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.servers.0]", (path ? &arr_4_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$PathItem'.servers]", path);
    }
    return res;
}

// check _jm_obj_21_map_summary (.'$PathItem'.summary)
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$PathItem'.summary]", path);
    }
    return res;
}

// check _jm_obj_21_map_trace (.'$PathItem'.trace)
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'.trace
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Operation [.'$PathItem'.trace]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_21_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_21_map_tab, 13);
}

// object .'$PathItem'
static bool _jm_obj_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$PathItem']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_21 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_21_map(prop)))
        {
            // handle 13 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_21 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$PathItem']", (path ? &lpath_21 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$PathItem'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$PathItem'.'/^x\\\\-.*$/']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$PathItem']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    return true;
}

// check $PathItem (.'$PathItem')
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$PathItem'
    res = _jm_obj_21(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$PathItem']", path);
    }
    return res;
}

// object .'$Operation'.callbacks
static bool _jm_obj_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Operation'.callbacks]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_23 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Operation'.callbacks.''
        // .'$Operation'.callbacks.''.'|'.0
        res = json_model_24(pval, (path ? &lpath_23 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Callback [.'$Operation'.callbacks.''.'|'.0]", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            // .'$Operation'.callbacks.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_23 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Operation'.callbacks.''.'|'.1]", (path ? &lpath_23 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Operation'.callbacks.''.'|']", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_22_map_callbacks (.'$Operation'.callbacks)
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.callbacks
    res = _jm_obj_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Operation'.callbacks]", path);
    }
    return res;
}

// check _jm_obj_22_map_deprecated (.'$Operation'.deprecated)
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Operation'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_22_map_description (.'$Operation'.description)
static bool _jm_f_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Operation'.description]", path);
    }
    return res;
}

// check _jm_obj_22_map_externalDocs (.'$Operation'.externalDocs)
static bool _jm_f_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.externalDocs
    res = json_model_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$Operation'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_22_map_operationId (.'$Operation'.operationId)
static bool _jm_f_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.operationId
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Operation'.operationId]", path);
    }
    return res;
}

// check _jm_obj_22_map_parameters (.'$Operation'.parameters)
static bool _jm_f_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.parameters
    res = json_is_array(val);
    if (res)
    {
        size_t arr_5_idx;
        json_t *arr_5_item;
        json_array_foreach(val, arr_5_idx, arr_5_item)
        {
            jm_path_t arr_5_lpath = (jm_path_t) { NULL, arr_5_idx, path, NULL };
            // .'$Operation'.parameters.0
            // .'$Operation'.parameters.0.'|'.0
            res = json_model_18(arr_5_item, (path ? &arr_5_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Parameter [.'$Operation'.parameters.0.'|'.0]", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                // .'$Operation'.parameters.0.'|'.1
                res = json_model_30(arr_5_item, (path ? &arr_5_lpath : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Operation'.parameters.0.'|'.1]", (path ? &arr_5_lpath : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Operation'.parameters.0.'|']", (path ? &arr_5_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Operation'.parameters]", path);
    }
    return res;
}

// check _jm_obj_22_map_requestBody (.'$Operation'.requestBody)
static bool _jm_f_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.requestBody
    // .'$Operation'.requestBody.'|'.0
    res = json_model_19(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $RequestBody [.'$Operation'.requestBody.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Operation'.requestBody.'|'.1
        res = json_model_30(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Operation'.requestBody.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Operation'.requestBody.'|']", path);
    }
    return res;
}

// check _jm_obj_22_map_responses (.'$Operation'.responses)
static bool _jm_f_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.responses
    res = json_model_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Responses [.'$Operation'.responses]", path);
    }
    return res;
}

// check _jm_obj_22_map_security (.'$Operation'.security)
static bool _jm_f_44(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.security
    res = json_is_array(val);
    if (res)
    {
        size_t arr_6_idx;
        json_t *arr_6_item;
        json_array_foreach(val, arr_6_idx, arr_6_item)
        {
            jm_path_t arr_6_lpath = (jm_path_t) { NULL, arr_6_idx, path, NULL };
            // .'$Operation'.security.0
            res = json_model_38(arr_6_item, (path ? &arr_6_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $SecurityRequirement [.'$Operation'.security.0]", (path ? &arr_6_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Operation'.security]", path);
    }
    return res;
}

// check _jm_obj_22_map_servers (.'$Operation'.servers)
static bool _jm_f_45(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.servers
    res = json_is_array(val);
    if (res)
    {
        size_t arr_7_idx;
        json_t *arr_7_item;
        json_array_foreach(val, arr_7_idx, arr_7_item)
        {
            jm_path_t arr_7_lpath = (jm_path_t) { NULL, arr_7_idx, path, NULL };
            // .'$Operation'.servers.0
            res = json_model_6(arr_7_item, (path ? &arr_7_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$Operation'.servers.0]", (path ? &arr_7_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Operation'.servers]", path);
    }
    return res;
}

// check _jm_obj_22_map_summary (.'$Operation'.summary)
static bool _jm_f_46(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Operation'.summary]", path);
    }
    return res;
}

// check _jm_obj_22_map_tags (.'$Operation'.tags)
static bool _jm_f_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'.tags
    res = json_is_array(val);
    if (res)
    {
        size_t arr_8_idx;
        json_t *arr_8_item;
        json_array_foreach(val, arr_8_idx, arr_8_item)
        {
            jm_path_t arr_8_lpath = (jm_path_t) { NULL, arr_8_idx, path, NULL };
            // .'$Operation'.tags.0
            res = json_is_string(arr_8_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Operation'.tags.0]", (path ? &arr_8_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Operation'.tags]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_22_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_22_map_tab, 12);
}

// object .'$Operation'
static bool _jm_obj_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Operation']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_22 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_22_map(prop)))
        {
            // handle 12 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_22 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Operation']", (path ? &lpath_22 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Operation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Operation'.'/^x\\\\-.*$/']", (path ? &lpath_22 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Operation']", (path ? &lpath_22 : NULL));
            return false;
        }
    }
    return true;
}

// check $Operation (.'$Operation')
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Operation'
    res = _jm_obj_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Operation']", path);
    }
    return res;
}

// object .'$ExternalDocumentation'
static bool _jm_obj_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$ExternalDocumentation']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_24 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "url") == 0)
        {
            // handle must url property
            must_count += 1;
            // .'$ExternalDocumentation'.url
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$ExternalDocumentation'.url]", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$ExternalDocumentation'.url]", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$ExternalDocumentation'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$ExternalDocumentation'.description]", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$ExternalDocumentation'.description]", (path ? &lpath_24 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$ExternalDocumentation'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$ExternalDocumentation'.'/^x\\\\-.*$/']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$ExternalDocumentation']", (path ? &lpath_24 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "url") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <url> [.'$ExternalDocumentation']", path);
            }
        }
        return false;
    }
    return true;
}

// check $ExternalDocumentation (.'$ExternalDocumentation')
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$ExternalDocumentation'
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$ExternalDocumentation']", path);
    }
    return res;
}

// check _jm_obj_25_map_allowEmptyValue (.'$parameterShare'.allowEmptyValue)
static bool _jm_f_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterShare'.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$parameterShare'.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_25_map_deprecated (.'$parameterShare'.deprecated)
static bool _jm_f_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterShare'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$parameterShare'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_25_map_description (.'$parameterShare'.description)
static bool _jm_f_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterShare'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$parameterShare'.description]", path);
    }
    return res;
}

// check _jm_obj_25_map_required (.'$parameterShare'.required)
static bool _jm_f_51(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterShare'.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$parameterShare'.required]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_25_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_25_map_tab, 4);
}

// object .'$parameterShare'
static bool _jm_obj_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$parameterShare']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_25 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_25_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_25 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$parameterShare']", (path ? &lpath_25 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$parameterShare'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$parameterShare'.'/^x\\\\-.*$/']", (path ? &lpath_25 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$parameterShare']", (path ? &lpath_25 : NULL));
            return false;
        }
    }
    return true;
}

// check $parameterShare (.'$parameterShare')
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterShare'
    res = _jm_obj_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$parameterShare']", path);
    }
    return res;
}


// check _jm_obj_26_map_allowEmptyValue (.'$commonParameter'.allowEmptyValue)
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$commonParameter'.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$commonParameter'.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_26_map_deprecated (.'$commonParameter'.deprecated)
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$commonParameter'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$commonParameter'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_26_map_description (.'$commonParameter'.description)
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$commonParameter'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$commonParameter'.description]", path);
    }
    return res;
}

// check _jm_obj_26_map_required (.'$commonParameter'.required)
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$commonParameter'.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$commonParameter'.required]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_26_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_26_map_tab, 4);
}

// object .'$commonParameter'
static bool _jm_obj_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$commonParameter']", path);
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
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$commonParameter'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$commonParameter'.name]", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$commonParameter'.name]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "in") == 0)
        {
            // handle must in property
            must_count += 1;
            // .'$commonParameter'.in
            res = jm_json_is_scalar(pval) && json_is_string(pval) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(pval) } }, _jm_cst_0, 4);;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "value not in enum [.'$commonParameter'.in.'|']", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$commonParameter'.in]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_26_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_26 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$commonParameter']", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$commonParameter'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$commonParameter'.'/^x\\\\-.*$/']", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$commonParameter']", (path ? &lpath_26 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <in> [.'$commonParameter']", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$commonParameter']", path);
            }
        }
        return false;
    }
    return true;
}

// check $commonParameter (.'$commonParameter')
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$commonParameter'
    res = _jm_obj_26(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$commonParameter']", path);
    }
    return res;
}


// check $Style (.'$Style')
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Style'
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_1, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$Style'.'|']", path);
    }
    return res;
}

// check _jm_obj_27_map_allowReserved (.'$parameterSchemaOnly'.allowReserved)
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$parameterSchemaOnly'.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_27_map_example (.'$parameterSchemaOnly'.example)
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$parameterSchemaOnly'.example]", path);
    }
    return res;
}

// object .'$parameterSchemaOnly'.examples
static bool _jm_obj_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$parameterSchemaOnly'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_28 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$parameterSchemaOnly'.examples.''
        // .'$parameterSchemaOnly'.examples.''.'|'.0
        res = json_model_25(pval, (path ? &lpath_28 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$parameterSchemaOnly'.examples.''.'|'.0]", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            // .'$parameterSchemaOnly'.examples.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_28 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$parameterSchemaOnly'.examples.''.'|'.1]", (path ? &lpath_28 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$parameterSchemaOnly'.examples.''.'|']", (path ? &lpath_28 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_27_map_examples (.'$parameterSchemaOnly'.examples)
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.examples
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$parameterSchemaOnly'.examples]", path);
    }
    return res;
}

// check _jm_obj_27_map_explode (.'$parameterSchemaOnly'.explode)
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$parameterSchemaOnly'.explode]", path);
    }
    return res;
}

// check _jm_obj_27_map_schema (.'$parameterSchemaOnly'.schema)
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.schema
    res = json_model_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$parameterSchemaOnly'.schema]", path);
    }
    return res;
}

// check _jm_obj_27_map_style (.'$parameterSchemaOnly'.style)
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'.style
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$parameterSchemaOnly'.style]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_27_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_27_map_tab, 6);
}

// object .'$parameterSchemaOnly'
static bool _jm_obj_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$parameterSchemaOnly']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_27 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_27_map(prop)))
        {
            // handle 6 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_27 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$parameterSchemaOnly']", (path ? &lpath_27 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$parameterSchemaOnly']", (path ? &lpath_27 : NULL));
            return false;
        }
    }
    return true;
}

// check $parameterSchemaOnly (.'$parameterSchemaOnly')
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterSchemaOnly'
    res = _jm_obj_27(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$parameterSchemaOnly']", path);
    }
    return res;
}

// object .'$parameterContentOnly'.content
static bool _jm_obj_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$parameterContentOnly'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_30 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$parameterContentOnly'.content.''
        res = json_model_20(pval, (path ? &lpath_30 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$parameterContentOnly'.content.'']", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$parameterContentOnly'
static bool _jm_obj_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$parameterContentOnly']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_29 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "content") == 0)
        {
            // handle may content property
            // .'$parameterContentOnly'.content
            res = _jm_obj_30(pval, (path ? &lpath_29 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$parameterContentOnly'.content]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$parameterContentOnly'.content]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$parameterContentOnly']", (path ? &lpath_29 : NULL));
            return false;
        }
    }
    return true;
}

// check $parameterContentOnly (.'$parameterContentOnly')
static bool json_model_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$parameterContentOnly'
    res = _jm_obj_29(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$parameterContentOnly']", path);
    }
    return res;
}


// check _jm_obj_31_map_allowEmptyValue (.'$Parameter'.'|'.1.allowEmptyValue)
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.1.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.1.allowEmptyValue]", path);
    }
    return res;
}

// object .'$Parameter'.'|'.1.content
static bool _jm_obj_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Parameter'.'|'.1.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_32 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Parameter'.'|'.1.content.''
        res = json_model_20(pval, (path ? &lpath_32 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$Parameter'.'|'.1.content.'']", (path ? &lpath_32 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_31_map_content (.'$Parameter'.'|'.1.content)
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.1.content
    res = _jm_obj_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Parameter'.'|'.1.content]", path);
    }
    return res;
}

// check _jm_obj_31_map_deprecated (.'$Parameter'.'|'.1.deprecated)
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.1.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.1.deprecated]", path);
    }
    return res;
}

// check _jm_obj_31_map_description (.'$Parameter'.'|'.1.description)
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Parameter'.'|'.1.description]", path);
    }
    return res;
}

// check _jm_obj_31_map_required (.'$Parameter'.'|'.1.required)
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.1.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.1.required]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_31_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_31_map_tab, 5);
}

// object .'$Parameter'.'|'.1
static bool _jm_obj_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Parameter'.'|'.1]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_31 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$Parameter'.'|'.1.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Parameter'.'|'.1.name]", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Parameter'.'|'.1.name]", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "in") == 0)
        {
            // handle must in property
            must_count += 1;
            // .'$Parameter'.'|'.1.in
            res = jm_json_is_scalar(pval) && json_is_string(pval) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(pval) } }, _jm_cst_2, 4);;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "value not in enum [.'$Parameter'.'|'.1.in.'|']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Parameter'.'|'.1.in]", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_31_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_31 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Parameter'.'|'.1]", (path ? &lpath_31 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Parameter'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Parameter'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Parameter'.'|'.1]", (path ? &lpath_31 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <in> [.'$Parameter'.'|'.1]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$Parameter'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}


// check _jm_obj_33_map_allowEmptyValue (.'$Parameter'.'|'.0.allowEmptyValue)
static bool _jm_f_67(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.0.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_33_map_allowReserved (.'$Parameter'.'|'.0.allowReserved)
static bool _jm_f_68(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.0.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_33_map_deprecated (.'$Parameter'.'|'.0.deprecated)
static bool _jm_f_69(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.0.deprecated]", path);
    }
    return res;
}

// check _jm_obj_33_map_description (.'$Parameter'.'|'.0.description)
static bool _jm_f_70(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Parameter'.'|'.0.description]", path);
    }
    return res;
}

// check _jm_obj_33_map_example (.'$Parameter'.'|'.0.example)
static bool _jm_f_71(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Parameter'.'|'.0.example]", path);
    }
    return res;
}

// object .'$Parameter'.'|'.0.examples
static bool _jm_obj_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Parameter'.'|'.0.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_34 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Parameter'.'|'.0.examples.''
        // .'$Parameter'.'|'.0.examples.''.'|'.0
        res = json_model_25(pval, (path ? &lpath_34 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$Parameter'.'|'.0.examples.''.'|'.0]", (path ? &lpath_34 : NULL));
        }
        if (! res)
        {
            // .'$Parameter'.'|'.0.examples.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_34 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Parameter'.'|'.0.examples.''.'|'.1]", (path ? &lpath_34 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Parameter'.'|'.0.examples.''.'|']", (path ? &lpath_34 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_33_map_examples (.'$Parameter'.'|'.0.examples)
static bool _jm_f_72(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.examples
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Parameter'.'|'.0.examples]", path);
    }
    return res;
}

// check _jm_obj_33_map_explode (.'$Parameter'.'|'.0.explode)
static bool _jm_f_73(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.0.explode]", path);
    }
    return res;
}

// check _jm_obj_33_map_required (.'$Parameter'.'|'.0.required)
static bool _jm_f_74(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Parameter'.'|'.0.required]", path);
    }
    return res;
}

// check _jm_obj_33_map_schema (.'$Parameter'.'|'.0.schema)
static bool _jm_f_75(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.schema
    res = json_model_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Parameter'.'|'.0.schema]", path);
    }
    return res;
}

// check _jm_obj_33_map_style (.'$Parameter'.'|'.0.style)
static bool _jm_f_76(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'.'|'.0.style
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$Parameter'.'|'.0.style]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_33_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_33_map_tab, 10);
}

// object .'$Parameter'.'|'.0
static bool _jm_obj_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Parameter'.'|'.0]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_33 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$Parameter'.'|'.0.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Parameter'.'|'.0.name]", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Parameter'.'|'.0.name]", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "in") == 0)
        {
            // handle must in property
            must_count += 1;
            // .'$Parameter'.'|'.0.in
            res = jm_json_is_scalar(pval) && json_is_string(pval) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(pval) } }, _jm_cst_3, 4);;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "value not in enum [.'$Parameter'.'|'.0.in.'|']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Parameter'.'|'.0.in]", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_33_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_33 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Parameter'.'|'.0]", (path ? &lpath_33 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Parameter'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Parameter'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_33 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Parameter'.'|'.0]", (path ? &lpath_33 : NULL));
            return false;
        }
    }
    if (must_count != 2)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <in> [.'$Parameter'.'|'.0]", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$Parameter'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Parameter (.'$Parameter')
static bool json_model_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Parameter'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$Parameter'.'|']", path);
    }
    if (res)
    {
        // .'$Parameter'.'|'.0
        res = _jm_obj_33(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Parameter'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Parameter'.'|'.1
            res = _jm_obj_31(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Parameter'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Parameter'.'|']", path);
        }
    }
    return res;
}

// object .'$RequestBody'.content
static bool _jm_obj_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RequestBody'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_36 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$RequestBody'.content.''
        res = json_model_20(pval, (path ? &lpath_36 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$RequestBody'.content.'']", (path ? &lpath_36 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$RequestBody'
static bool _jm_obj_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$RequestBody']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_35 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$RequestBody'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$RequestBody'.description]", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RequestBody'.description]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "content") == 0)
        {
            // handle may content property
            // .'$RequestBody'.content
            res = _jm_obj_36(pval, (path ? &lpath_35 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$RequestBody'.content]", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RequestBody'.content]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "required") == 0)
        {
            // handle may required property
            // .'$RequestBody'.required
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$RequestBody'.required]", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$RequestBody'.required]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$RequestBody'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$RequestBody'.'/^x\\\\-.*$/']", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$RequestBody']", (path ? &lpath_35 : NULL));
            return false;
        }
    }
    return true;
}

// check $RequestBody (.'$RequestBody')
static bool json_model_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$RequestBody'
    res = _jm_obj_35(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$RequestBody']", path);
    }
    return res;
}

// object .'$MediaType'.encoding
static bool _jm_obj_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$MediaType'.encoding]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_38 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$MediaType'.encoding.''
        res = json_model_21(pval, (path ? &lpath_38 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Encoding [.'$MediaType'.encoding.'']", (path ? &lpath_38 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_37_map_encoding (.'$MediaType'.encoding)
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$MediaType'.encoding
    res = _jm_obj_38(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$MediaType'.encoding]", path);
    }
    return res;
}

// check _jm_obj_37_map_example (.'$MediaType'.example)
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$MediaType'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$MediaType'.example]", path);
    }
    return res;
}

// object .'$MediaType'.examples
static bool _jm_obj_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$MediaType'.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_39 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$MediaType'.examples.''
        // .'$MediaType'.examples.''.'|'.0
        res = json_model_25(pval, (path ? &lpath_39 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$MediaType'.examples.''.'|'.0]", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            // .'$MediaType'.examples.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_39 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$MediaType'.examples.''.'|'.1]", (path ? &lpath_39 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$MediaType'.examples.''.'|']", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_37_map_examples (.'$MediaType'.examples)
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$MediaType'.examples
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$MediaType'.examples]", path);
    }
    return res;
}

// check _jm_obj_37_map_schema (.'$MediaType'.schema)
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$MediaType'.schema
    res = json_model_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$MediaType'.schema]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_37_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_37_map_tab, 4);
}

// object .'$MediaType'
static bool _jm_obj_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$MediaType']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_37 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_37_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_37 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$MediaType']", (path ? &lpath_37 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$MediaType'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$MediaType'.'/^x\\\\-.*$/']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$MediaType']", (path ? &lpath_37 : NULL));
            return false;
        }
    }
    return true;
}

// check $MediaType (.'$MediaType')
static bool json_model_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$MediaType'
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$MediaType']", path);
    }
    return res;
}

// check _jm_obj_40_map_allowReserved (.'$Encoding'.allowReserved)
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Encoding'.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_40_map_contentType (.'$Encoding'.contentType)
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'.contentType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Encoding'.contentType]", path);
    }
    return res;
}

// check _jm_obj_40_map_explode (.'$Encoding'.explode)
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Encoding'.explode]", path);
    }
    return res;
}

// object .'$Encoding'.headers
static bool _jm_obj_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Encoding'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_41 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Encoding'.headers.''
        // .'$Encoding'.headers.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_41 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$Encoding'.headers.''.'|'.0]", (path ? &lpath_41 : NULL));
        }
        if (! res)
        {
            // .'$Encoding'.headers.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_41 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Encoding'.headers.''.'|'.1]", (path ? &lpath_41 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Encoding'.headers.''.'|']", (path ? &lpath_41 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_40_map_headers (.'$Encoding'.headers)
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'.headers
    res = _jm_obj_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Encoding'.headers]", path);
    }
    return res;
}

// check _jm_obj_40_map_style (.'$Encoding'.style)
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'.style
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$Encoding'.style]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_40_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_40_map_tab, 5);
}

// object .'$Encoding'
static bool _jm_obj_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Encoding']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_40 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_40_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_40 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Encoding']", (path ? &lpath_40 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Encoding'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Encoding'.'/^x\\\\-.*$/']", (path ? &lpath_40 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Encoding']", (path ? &lpath_40 : NULL));
            return false;
        }
    }
    return true;
}

// check $Encoding (.'$Encoding')
static bool json_model_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Encoding'
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Encoding']", path);
    }
    return res;
}

static bool _jm_re_3(const char *s)
{
  int rc = pcre2_match(_jm_re_3_code, (PCRE2_SPTR) s, PCRE2_ZERO_TERMINATED,
                       0, 0, _jm_re_3_data, NULL);
  return rc >= 0;
}

// object .'$Responses'
static bool _jm_obj_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Responses']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_42 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "default") == 0)
        {
            // handle may default property
            // .'$Responses'.default
            // .'$Responses'.default.'|'.0
            res = json_model_23(pval, (path ? &lpath_42 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$Responses'.default.'|'.0]", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                // .'$Responses'.default.'|'.1
                res = json_model_30(pval, (path ? &lpath_42 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Responses'.default.'|'.1]", (path ? &lpath_42 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Responses'.default.'|']", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Responses'.default]", (path ? &lpath_42 : NULL));
                return false;
            }
        }
        else if (_jm_re_3(prop))
        {
            // handle 2 re props
            // .'$Responses'.'/^[1-5](\\d\\d|XX)$/'
            // .'$Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.0
            res = json_model_23(pval, (path ? &lpath_42 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Response [.'$Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.0]", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                // .'$Responses'.'/^[1-5](\\d\\d|XX)$/'.'|'.1
                res = json_model_30(pval, (path ? &lpath_42 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|'.1]", (path ? &lpath_42 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Responses'.'/^[1-5](\\\\d\\\\d|XX)$/'.'|']", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 2 re props
            // .'$Responses'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Responses'.'/^x\\\\-.*$/']", (path ? &lpath_42 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Responses']", (path ? &lpath_42 : NULL));
            return false;
        }
    }
    return true;
}

// check $Responses (.'$Responses')
static bool json_model_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Responses'
    res = _jm_obj_42(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Responses']", path);
    }
    return res;
}

// object .'$Response'.content
static bool _jm_obj_44(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Response'.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_44 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Response'.content.''
        res = json_model_20(pval, (path ? &lpath_44 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$Response'.content.'']", (path ? &lpath_44 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_43_map_content (.'$Response'.content)
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Response'.content
    res = _jm_obj_44(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Response'.content]", path);
    }
    return res;
}

// check _jm_obj_43_map_description (.'$Response'.description)
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Response'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Response'.description]", path);
    }
    return res;
}

// object .'$Response'.headers
static bool _jm_obj_45(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Response'.headers]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_45 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Response'.headers.''
        // .'$Response'.headers.''.'|'.0
        res = json_model_28(pval, (path ? &lpath_45 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Header [.'$Response'.headers.''.'|'.0]", (path ? &lpath_45 : NULL));
        }
        if (! res)
        {
            // .'$Response'.headers.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_45 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Response'.headers.''.'|'.1]", (path ? &lpath_45 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Response'.headers.''.'|']", (path ? &lpath_45 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_43_map_headers (.'$Response'.headers)
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Response'.headers
    res = _jm_obj_45(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Response'.headers]", path);
    }
    return res;
}

// object .'$Response'.links
static bool _jm_obj_46(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Response'.links]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_46 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Response'.links.''
        // .'$Response'.links.''.'|'.0
        res = json_model_27(pval, (path ? &lpath_46 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Link [.'$Response'.links.''.'|'.0]", (path ? &lpath_46 : NULL));
        }
        if (! res)
        {
            // .'$Response'.links.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_46 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Response'.links.''.'|'.1]", (path ? &lpath_46 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Response'.links.''.'|']", (path ? &lpath_46 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_43_map_links (.'$Response'.links)
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Response'.links
    res = _jm_obj_46(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Response'.links]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_43_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_43_map_tab, 4);
}

// object .'$Response'
static bool _jm_obj_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Response']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_43 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_43_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_43 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Response']", (path ? &lpath_43 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Response'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Response'.'/^x\\\\-.*$/']", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Response']", (path ? &lpath_43 : NULL));
            return false;
        }
    }
    return true;
}

// check $Response (.'$Response')
static bool json_model_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Response'
    res = _jm_obj_43(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Response']", path);
    }
    return res;
}

// object .'$Callback'
static bool _jm_obj_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Callback']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_47 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_check_fun_string(json_model_26, prop, (path ? &lpath_47 : NULL), rep))
        {
            // handle 1 key props
            // .'$Callback'.'$Expression'
            // .'$Callback'.'$Expression'.'|'.0
            res = json_model_10(pval, (path ? &lpath_47 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $PathItem [.'$Callback'.'$Expression'.'|'.0]", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                // .'$Callback'.'$Expression'.'|'.1
                res = json_model_30(pval, (path ? &lpath_47 : NULL), rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Callback'.'$Expression'.'|'.1]", (path ? &lpath_47 : NULL));
                }
            }
            if (res)
            {
                if (rep) jm_report_free_entries(rep);
            }
            else
            {
                if (rep) jm_report_add_entry(rep, "no model matched [.'$Callback'.'$Expression'.'|']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Callback'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Callback'.'/^x\\\\-.*$/']", (path ? &lpath_47 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Callback']", (path ? &lpath_47 : NULL));
            return false;
        }
    }
    return true;
}

// check $Callback (.'$Callback')
static bool json_model_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Callback'
    res = _jm_obj_47(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Callback']", path);
    }
    return res;
}

// check _jm_obj_48_map_description (.'$Example'.description)
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Example'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Example'.description]", path);
    }
    return res;
}

// check _jm_obj_48_map_externalValue (.'$Example'.externalValue)
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Example'.externalValue
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Example'.externalValue]", path);
    }
    return res;
}

// check _jm_obj_48_map_summary (.'$Example'.summary)
static bool _jm_f_92(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Example'.summary
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Example'.summary]", path);
    }
    return res;
}

// check _jm_obj_48_map_value (.'$Example'.value)
static bool _jm_f_93(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Example'.value
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Example'.value]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_48_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_48_map_tab, 4);
}

// object .'$Example'
static bool _jm_obj_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Example']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_48 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_48_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_48 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Example']", (path ? &lpath_48 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Example'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Example'.'/^x\\\\-.*$/']", (path ? &lpath_48 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Example']", (path ? &lpath_48 : NULL));
            return false;
        }
    }
    return true;
}

// check $Example (.'$Example')
static bool json_model_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Example'
    res = _jm_obj_48(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Example']", path);
    }
    return res;
}

// check $Expression (.'$Expression')
static bool json_model_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Expression'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Expression']", path);
    }
    return res;
}

// check _jm_obj_49_map_description (.'$Link'.'|'.1.description)
static bool _jm_f_94(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Link'.'|'.1.description]", path);
    }
    return res;
}

// object .'$Link'.'|'.1.parameters
static bool _jm_obj_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Link'.'|'.1.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_49_map_parameters (.'$Link'.'|'.1.parameters)
static bool _jm_f_95(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.1.parameters
    res = _jm_obj_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Link'.'|'.1.parameters]", path);
    }
    return res;
}

// check _jm_obj_49_map_requestBody (.'$Link'.'|'.1.requestBody)
static bool _jm_f_96(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.1.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Link'.'|'.1.requestBody]", path);
    }
    return res;
}

// check _jm_obj_49_map_server (.'$Link'.'|'.1.server)
static bool _jm_f_97(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.1.server
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$Link'.'|'.1.server]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_49_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_49_map_tab, 4);
}

// object .'$Link'.'|'.1
static bool _jm_obj_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Link'.'|'.1]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_49 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "operationId") == 0)
        {
            // handle must operationId property
            must_count += 1;
            // .'$Link'.'|'.1.operationId
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Link'.'|'.1.operationId]", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Link'.'|'.1.operationId]", (path ? &lpath_49 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_49_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_49 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Link'.'|'.1]", (path ? &lpath_49 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Link'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Link'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_49 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Link'.'|'.1]", (path ? &lpath_49 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "operationId") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <operationId> [.'$Link'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_51_map_description (.'$Link'.'|'.0.description)
static bool _jm_f_98(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Link'.'|'.0.description]", path);
    }
    return res;
}

// object .'$Link'.'|'.0.parameters
static bool _jm_obj_52(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Link'.'|'.0.parameters]", path);
        return false;
    }
    // accept any object
    return true;
}

// check _jm_obj_51_map_parameters (.'$Link'.'|'.0.parameters)
static bool _jm_f_99(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.0.parameters
    res = _jm_obj_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Link'.'|'.0.parameters]", path);
    }
    return res;
}

// check _jm_obj_51_map_requestBody (.'$Link'.'|'.0.requestBody)
static bool _jm_f_100(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.0.requestBody
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Link'.'|'.0.requestBody]", path);
    }
    return res;
}

// check _jm_obj_51_map_server (.'$Link'.'|'.0.server)
static bool _jm_f_101(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'.'|'.0.server
    res = json_model_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Server [.'$Link'.'|'.0.server]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_51_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_51_map_tab, 4);
}

// object .'$Link'.'|'.0
static bool _jm_obj_51(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Link'.'|'.0]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_50 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "operationRef") == 0)
        {
            // handle must operationRef property
            must_count += 1;
            // .'$Link'.'|'.0.operationRef
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Link'.'|'.0.operationRef]", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Link'.'|'.0.operationRef]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_51_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_50 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Link'.'|'.0]", (path ? &lpath_50 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Link'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Link'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_50 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Link'.'|'.0]", (path ? &lpath_50 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "operationRef") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <operationRef> [.'$Link'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $Link (.'$Link')
static bool json_model_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Link'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$Link'.'|']", path);
    }
    if (res)
    {
        // .'$Link'.'|'.0
        res = _jm_obj_51(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Link'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Link'.'|'.1
            res = _jm_obj_49(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Link'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Link'.'|']", path);
        }
    }
    return res;
}

// check _jm_obj_53_map_allowEmptyValue (.'$Header'.'|'.1.allowEmptyValue)
static bool _jm_f_102(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.1.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.1.allowEmptyValue]", path);
    }
    return res;
}

// object .'$Header'.'|'.1.content
static bool _jm_obj_54(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Header'.'|'.1.content]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_52 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Header'.'|'.1.content.''
        res = json_model_20(pval, (path ? &lpath_52 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $MediaType [.'$Header'.'|'.1.content.'']", (path ? &lpath_52 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_53_map_content (.'$Header'.'|'.1.content)
static bool _jm_f_103(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.1.content
    res = _jm_obj_54(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Header'.'|'.1.content]", path);
    }
    return res;
}

// check _jm_obj_53_map_deprecated (.'$Header'.'|'.1.deprecated)
static bool _jm_f_104(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.1.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.1.deprecated]", path);
    }
    return res;
}

// check _jm_obj_53_map_description (.'$Header'.'|'.1.description)
static bool _jm_f_105(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Header'.'|'.1.description]", path);
    }
    return res;
}

// check _jm_obj_53_map_required (.'$Header'.'|'.1.required)
static bool _jm_f_106(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.1.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.1.required]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_53_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_53_map_tab, 5);
}

// object .'$Header'.'|'.1
static bool _jm_obj_53(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Header'.'|'.1]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_51 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_53_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_51 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Header'.'|'.1]", (path ? &lpath_51 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Header'.'|'.1.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Header'.'|'.1.'/^x\\\\-.*$/']", (path ? &lpath_51 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Header'.'|'.1]", (path ? &lpath_51 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_55_map_allowEmptyValue (.'$Header'.'|'.0.allowEmptyValue)
static bool _jm_f_107(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.allowEmptyValue
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.0.allowEmptyValue]", path);
    }
    return res;
}

// check _jm_obj_55_map_allowReserved (.'$Header'.'|'.0.allowReserved)
static bool _jm_f_108(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.allowReserved
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.0.allowReserved]", path);
    }
    return res;
}

// check _jm_obj_55_map_deprecated (.'$Header'.'|'.0.deprecated)
static bool _jm_f_109(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.0.deprecated]", path);
    }
    return res;
}

// check _jm_obj_55_map_description (.'$Header'.'|'.0.description)
static bool _jm_f_110(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Header'.'|'.0.description]", path);
    }
    return res;
}

// check _jm_obj_55_map_example (.'$Header'.'|'.0.example)
static bool _jm_f_111(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Header'.'|'.0.example]", path);
    }
    return res;
}

// object .'$Header'.'|'.0.examples
static bool _jm_obj_56(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Header'.'|'.0.examples]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_54 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Header'.'|'.0.examples.''
        // .'$Header'.'|'.0.examples.''.'|'.0
        res = json_model_25(pval, (path ? &lpath_54 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Example [.'$Header'.'|'.0.examples.''.'|'.0]", (path ? &lpath_54 : NULL));
        }
        if (! res)
        {
            // .'$Header'.'|'.0.examples.''.'|'.1
            res = json_model_30(pval, (path ? &lpath_54 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Reference [.'$Header'.'|'.0.examples.''.'|'.1]", (path ? &lpath_54 : NULL));
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Header'.'|'.0.examples.''.'|']", (path ? &lpath_54 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_55_map_examples (.'$Header'.'|'.0.examples)
static bool _jm_f_112(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.examples
    res = _jm_obj_56(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Header'.'|'.0.examples]", path);
    }
    return res;
}

// check _jm_obj_55_map_explode (.'$Header'.'|'.0.explode)
static bool _jm_f_113(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.explode
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.0.explode]", path);
    }
    return res;
}

// check _jm_obj_55_map_required (.'$Header'.'|'.0.required)
static bool _jm_f_114(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.required
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Header'.'|'.0.required]", path);
    }
    return res;
}

// check _jm_obj_55_map_schema (.'$Header'.'|'.0.schema)
static bool _jm_f_115(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.schema
    res = json_model_32(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Header'.'|'.0.schema]", path);
    }
    return res;
}

// check _jm_obj_55_map_style (.'$Header'.'|'.0.style)
static bool _jm_f_116(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'.'|'.0.style
    res = json_model_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Style [.'$Header'.'|'.0.style]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_55_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_55_map_tab, 10);
}

// object .'$Header'.'|'.0
static bool _jm_obj_55(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Header'.'|'.0]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_53 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_55_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_53 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Header'.'|'.0]", (path ? &lpath_53 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Header'.'|'.0.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Header'.'|'.0.'/^x\\\\-.*$/']", (path ? &lpath_53 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Header'.'|'.0]", (path ? &lpath_53 : NULL));
            return false;
        }
    }
    return true;
}

// check $Header (.'$Header')
static bool json_model_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Header'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$Header'.'|']", path);
    }
    if (res)
    {
        // .'$Header'.'|'.0
        res = _jm_obj_55(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$Header'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$Header'.'|'.1
            res = _jm_obj_53(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Header'.'|'.1]", path);
            }
        }
        if (res)
        {
            if (rep) jm_report_free_entries(rep);
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "no model matched [.'$Header'.'|']", path);
        }
    }
    return res;
}

// object .'$Tag'
static bool _jm_obj_57(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Tag']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_55 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "name") == 0)
        {
            // handle must name property
            must_count += 1;
            // .'$Tag'.name
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Tag'.name]", (path ? &lpath_55 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Tag'.name]", (path ? &lpath_55 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$Tag'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Tag'.description]", (path ? &lpath_55 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Tag'.description]", (path ? &lpath_55 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "externalDocs") == 0)
        {
            // handle may externalDocs property
            // .'$Tag'.externalDocs
            res = json_model_12(pval, (path ? &lpath_55 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$Tag'.externalDocs]", (path ? &lpath_55 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Tag'.externalDocs]", (path ? &lpath_55 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Tag'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Tag'.'/^x\\\\-.*$/']", (path ? &lpath_55 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Tag']", (path ? &lpath_55 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$Tag']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Tag (.'$Tag')
static bool json_model_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Tag'
    res = _jm_obj_57(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Tag']", path);
    }
    return res;
}

// object .'$Reference'
static bool _jm_obj_58(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Reference']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_56 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "$ref") == 0)
        {
            // handle must $ref property
            must_count += 1;
            // .'$Reference'.'$ref'
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Reference'.'$ref']", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Reference'.'$ref']", (path ? &lpath_56 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "summary") == 0)
        {
            // handle may summary property
            // .'$Reference'.summary
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Reference'.summary]", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Reference'.summary]", (path ? &lpath_56 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$Reference'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Reference'.description]", (path ? &lpath_56 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Reference'.description]", (path ? &lpath_56 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Reference']", (path ? &lpath_56 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "$ref") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <$ref> [.'$Reference']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Reference (.'$Reference')
static bool json_model_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Reference'
    res = _jm_obj_58(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Reference']", path);
    }
    return res;
}

// check $schema (.'$schema')
static bool json_model_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema'
    // .'$schema'.'@'
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema'.'@']", path);
    }
    return res;
}

// check _jm_obj_59_map_$anchor (.'$Schema'.'$anchor')
static bool _jm_f_117(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$anchor'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#URI-REFERENCE [.'$Schema'.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_59_map_$comment (.'$Schema'.'$comment')
static bool _jm_f_118(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.'$comment']", path);
    }
    return res;
}

// object .'$Schema'.'$defs'
static bool _jm_obj_60(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_58 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Schema'.'$defs'.''
        res = json_model_55(pval, (path ? &lpath_58 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.'$defs'.'']", (path ? &lpath_58 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_$defs (.'$Schema'.'$defs')
static bool _jm_f_119(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$defs'
    res = _jm_obj_60(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_59_map_$dynamicAnchor (.'$Schema'.'$dynamicAnchor')
static bool _jm_f_120(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$dynamicAnchor'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#URI-REFERENCE [.'$Schema'.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_59_map_$dynamicRef (.'$Schema'.'$dynamicRef')
static bool _jm_f_121(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$dynamicRef'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#URI-REFERENCE [.'$Schema'.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_59_map_$id (.'$Schema'.'$id')
static bool _jm_f_122(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$id'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#URI-REFERENCE [.'$Schema'.'$id']", path);
    }
    return res;
}

// check _jm_obj_59_map_$ref (.'$Schema'.'$ref')
static bool _jm_f_123(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$ref'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#URI-REFERENCE [.'$Schema'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_59_map_$schema (.'$Schema'.'$schema')
static bool _jm_f_124(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$schema'
    res = json_is_string(val) && strcmp(json_string_value(val), "https://json-schema.org/draft/2020-12/schema") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _https://json-schema.org/draft/2020-12/schema [.'$Schema'.'$schema']", path);
    }
    return res;
}

// object .'$Schema'.'$vocabulary'
static bool _jm_obj_61(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_59 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$Schema'.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.'$vocabulary'.'$URI']", (path ? &lpath_59 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Schema'.'$vocabulary']", (path ? &lpath_59 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_$vocabulary (.'$Schema'.'$vocabulary')
static bool _jm_f_125(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.'$vocabulary'
    res = _jm_obj_61(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_59_map_additionalProperties (.'$Schema'.additionalProperties)
static bool _jm_f_126(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.additionalProperties
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_59_map_allOf (.'$Schema'.allOf)
static bool _jm_f_127(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.allOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#schemaArray [.'$Schema'.allOf]", path);
    }
    return res;
}

// check _jm_obj_59_map_anyOf (.'$Schema'.anyOf)
static bool _jm_f_128(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.anyOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#schemaArray [.'$Schema'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_59_map_const (.'$Schema'.const)
static bool _jm_f_129(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.const
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Schema'.const]", path);
    }
    return res;
}

// check _jm_obj_59_map_contains (.'$Schema'.contains)
static bool _jm_f_130(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.contains
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.contains]", path);
    }
    return res;
}

// check _jm_obj_59_map_contentEncoding (.'$Schema'.contentEncoding)
static bool _jm_f_131(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_59_map_contentMediaType (.'$Schema'.contentMediaType)
static bool _jm_f_132(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.contentMediaType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.contentMediaType]", path);
    }
    return res;
}

// check _jm_obj_59_map_contentSchema (.'$Schema'.contentSchema)
static bool _jm_f_133(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.contentSchema
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.contentSchema]", path);
    }
    return res;
}

// check _jm_obj_59_map_default (.'$Schema'.default)
static bool _jm_f_134(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Schema'.default]", path);
    }
    return res;
}

// object .'$Schema'.dependentRequired
static bool _jm_obj_62(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.dependentRequired]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_60 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Schema'.dependentRequired.''
        res = json_model_49(pval, (path ? &lpath_60 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schema#stringArray [.'$Schema'.dependentRequired.'']", (path ? &lpath_60 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_dependentRequired (.'$Schema'.dependentRequired)
static bool _jm_f_135(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.dependentRequired
    res = _jm_obj_62(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.dependentRequired]", path);
    }
    return res;
}

// object .'$Schema'.dependentSchemas
static bool _jm_obj_63(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.dependentSchemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_61 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Schema'.dependentSchemas.''
        res = json_model_55(pval, (path ? &lpath_61 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.dependentSchemas.'']", (path ? &lpath_61 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_dependentSchemas (.'$Schema'.dependentSchemas)
static bool _jm_f_136(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.dependentSchemas
    res = _jm_obj_63(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.dependentSchemas]", path);
    }
    return res;
}

// check _jm_obj_59_map_deprecated (.'$Schema'.deprecated)
static bool _jm_f_137(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_59_map_description (.'$Schema'.description)
static bool _jm_f_138(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.description]", path);
    }
    return res;
}

// check _jm_obj_59_map_discriminator (.'$Schema'.discriminator)
static bool _jm_f_139(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.discriminator
    res = json_model_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Discriminator [.'$Schema'.discriminator]", path);
    }
    return res;
}

// check _jm_obj_59_map_else (.'$Schema'.else)
static bool _jm_f_140(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.else
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.else]", path);
    }
    return res;
}

// check _jm_obj_59_map_enum (.'$Schema'.enum)
static bool _jm_f_141(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.enum
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Schema'.enum]", path);
    }
    return res;
}

// check _jm_obj_59_map_example (.'$Schema'.example)
static bool _jm_f_142(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.example
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Schema'.example]", path);
    }
    return res;
}

// check _jm_obj_59_map_examples (.'$Schema'.examples)
static bool _jm_f_143(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Schema'.examples]", path);
    }
    return res;
}

// check _jm_obj_59_map_exclusiveMaximum (.'$Schema'.exclusiveMaximum)
static bool _jm_f_144(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.exclusiveMaximum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Schema'.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_59_map_exclusiveMinimum (.'$Schema'.exclusiveMinimum)
static bool _jm_f_145(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.exclusiveMinimum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Schema'.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_59_map_externalDocs (.'$Schema'.externalDocs)
static bool _jm_f_146(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.externalDocs
    res = json_model_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ExternalDocumentation [.'$Schema'.externalDocs]", path);
    }
    return res;
}

// check _jm_obj_59_map_format (.'$Schema'.format)
static bool _jm_f_147(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.format]", path);
    }
    return res;
}

// check _jm_obj_59_map_if (.'$Schema'.if)
static bool _jm_f_148(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.if
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.if]", path);
    }
    return res;
}

// check _jm_obj_59_map_items (.'$Schema'.items)
static bool _jm_f_149(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.items
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.items]", path);
    }
    return res;
}

// check _jm_obj_59_map_maxContains (.'$Schema'.maxContains)
static bool _jm_f_150(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.maxContains
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.maxContains]", path);
    }
    return res;
}

// check _jm_obj_59_map_maxItems (.'$Schema'.maxItems)
static bool _jm_f_151(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.maxItems
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_59_map_maxLength (.'$Schema'.maxLength)
static bool _jm_f_152(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.maxLength
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_59_map_maxProperties (.'$Schema'.maxProperties)
static bool _jm_f_153(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.maxProperties
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_59_map_maximum (.'$Schema'.maximum)
static bool _jm_f_154(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.maximum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Schema'.maximum]", path);
    }
    return res;
}

// check _jm_obj_59_map_minContains (.'$Schema'.minContains)
static bool _jm_f_155(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.minContains
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.minContains]", path);
    }
    return res;
}

// check _jm_obj_59_map_minItems (.'$Schema'.minItems)
static bool _jm_f_156(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.minItems
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.minItems]", path);
    }
    return res;
}

// check _jm_obj_59_map_minLength (.'$Schema'.minLength)
static bool _jm_f_157(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.minLength
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.minLength]", path);
    }
    return res;
}

// check _jm_obj_59_map_minProperties (.'$Schema'.minProperties)
static bool _jm_f_158(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.minProperties
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#nonNegativeInteger [.'$Schema'.minProperties]", path);
    }
    return res;
}

// check _jm_obj_59_map_minimum (.'$Schema'.minimum)
static bool _jm_f_159(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.minimum
    res = json_is_real(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Schema'.minimum]", path);
    }
    return res;
}

// check _jm_obj_59_map_multipleOf (.'$Schema'.multipleOf)
static bool _jm_f_160(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.multipleOf
    res = json_is_real(val) && json_real_value(val) > 0.0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1.0 strict float [.'$Schema'.multipleOf]", path);
    }
    return res;
}

// check _jm_obj_59_map_not (.'$Schema'.not)
static bool _jm_f_161(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.not
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.not]", path);
    }
    return res;
}

// check _jm_obj_59_map_oneOf (.'$Schema'.oneOf)
static bool _jm_f_162(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.oneOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#schemaArray [.'$Schema'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_59_map_pattern (.'$Schema'.pattern)
static bool _jm_f_163(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.pattern
    res = jm_is_valid_regex(json_string_value(val), false);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$Schema'.pattern]", path);
    }
    return res;
}

// object .'$Schema'.patternProperties
static bool _jm_obj_64(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_62 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop, false))
        {
            // handle 1 key props
            // .'$Schema'.patternProperties.'$REGEX'
            res = json_model_55(pval, (path ? &lpath_62 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.patternProperties.'$REGEX']", (path ? &lpath_62 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Schema'.patternProperties]", (path ? &lpath_62 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_patternProperties (.'$Schema'.patternProperties)
static bool _jm_f_164(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.patternProperties
    res = _jm_obj_64(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.patternProperties]", path);
    }
    return res;
}

// check _jm_obj_59_map_prefixItems (.'$Schema'.prefixItems)
static bool _jm_f_165(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.prefixItems
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#schemaArray [.'$Schema'.prefixItems]", path);
    }
    return res;
}

// object .'$Schema'.properties
static bool _jm_obj_65(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_63 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Schema'.properties.''
        res = json_model_55(pval, (path ? &lpath_63 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.properties.'']", (path ? &lpath_63 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_59_map_properties (.'$Schema'.properties)
static bool _jm_f_166(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.properties
    res = _jm_obj_65(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema'.properties]", path);
    }
    return res;
}

// check _jm_obj_59_map_propertyNames (.'$Schema'.propertyNames)
static bool _jm_f_167(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.propertyNames
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_59_map_readOnly (.'$Schema'.readOnly)
static bool _jm_f_168(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.readOnly]", path);
    }
    return res;
}

// check _jm_obj_59_map_required (.'$Schema'.required)
static bool _jm_f_169(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.required
    res = json_model_49(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#stringArray [.'$Schema'.required]", path);
    }
    return res;
}

// check _jm_obj_59_map_then (.'$Schema'.then)
static bool _jm_f_170(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.then
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.then]", path);
    }
    return res;
}

// check _jm_obj_59_map_title (.'$Schema'.title)
static bool _jm_f_171(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$Schema'.title]", path);
    }
    return res;
}

// check _jm_obj_59_map_type (.'$Schema'.type)
static bool _jm_f_172(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.type
    // .'$Schema'.type.'|'.0
    res = json_model_47(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#simpleTypes [.'$Schema'.type.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Schema'.type.'|'.1
        res = json_model_48(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $schema#simpleTypesArray [.'$Schema'.type.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Schema'.type.'|']", path);
    }
    return res;
}

// check _jm_obj_59_map_unevaluatedItems (.'$Schema'.unevaluatedItems)
static bool _jm_f_173(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.unevaluatedItems
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.unevaluatedItems]", path);
    }
    return res;
}

// check _jm_obj_59_map_unevaluatedProperties (.'$Schema'.unevaluatedProperties)
static bool _jm_f_174(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.unevaluatedProperties
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schema#Schema [.'$Schema'.unevaluatedProperties]", path);
    }
    return res;
}

// check _jm_obj_59_map_uniqueItems (.'$Schema'.uniqueItems)
static bool _jm_f_175(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.uniqueItems]", path);
    }
    return res;
}

// check _jm_obj_59_map_writeOnly (.'$Schema'.writeOnly)
static bool _jm_f_176(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$Schema'.writeOnly]", path);
    }
    return res;
}

// check _jm_obj_59_map_xml (.'$Schema'.xml)
static bool _jm_f_177(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'.xml
    res = json_model_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $XML [.'$Schema'.xml]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_59_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_59_map_tab, 61);
}

// object .'$Schema'
static bool _jm_obj_59(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Schema']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_57 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_59_map(prop)))
        {
            // handle 61 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_57 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Schema']", (path ? &lpath_57 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Schema']", (path ? &lpath_57 : NULL));
            return false;
        }
    }
    return true;
}

// check $Schema (.'$Schema')
static bool json_model_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Schema'
    res = _jm_obj_59(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Schema']", path);
    }
    return res;
}

// object .'$Discriminator'.mapping
static bool _jm_obj_67(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Discriminator'.mapping]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_65 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Discriminator'.mapping.''
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$Discriminator'.mapping.'']", (path ? &lpath_65 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$Discriminator'
static bool _jm_obj_66(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Discriminator']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_64 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "propertyName") == 0)
        {
            // handle must propertyName property
            must_count += 1;
            // .'$Discriminator'.propertyName
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$Discriminator'.propertyName]", (path ? &lpath_64 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Discriminator'.propertyName]", (path ? &lpath_64 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "mapping") == 0)
        {
            // handle may mapping property
            // .'$Discriminator'.mapping
            res = _jm_obj_67(pval, (path ? &lpath_64 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$Discriminator'.mapping]", (path ? &lpath_64 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Discriminator'.mapping]", (path ? &lpath_64 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Discriminator'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Discriminator'.'/^x\\\\-.*$/']", (path ? &lpath_64 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Discriminator']", (path ? &lpath_64 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "propertyName") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <propertyName> [.'$Discriminator']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Discriminator (.'$Discriminator')
static bool json_model_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Discriminator'
    res = _jm_obj_66(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Discriminator']", path);
    }
    return res;
}

// check _jm_obj_68_map_attribute (.'$XML'.attribute)
static bool _jm_f_178(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'.attribute
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$XML'.attribute]", path);
    }
    return res;
}

// check _jm_obj_68_map_name (.'$XML'.name)
static bool _jm_f_179(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$XML'.name]", path);
    }
    return res;
}

// check _jm_obj_68_map_namespace (.'$XML'.namespace)
static bool _jm_f_180(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'.namespace
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$XML'.namespace]", path);
    }
    return res;
}

// check _jm_obj_68_map_prefix (.'$XML'.prefix)
static bool _jm_f_181(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'.prefix
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$XML'.prefix]", path);
    }
    return res;
}

// check _jm_obj_68_map_wrapped (.'$XML'.wrapped)
static bool _jm_f_182(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'.wrapped
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$XML'.wrapped]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_68_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_68_map_tab, 5);
}

// object .'$XML'
static bool _jm_obj_68(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$XML']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_66 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_68_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_66 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$XML']", (path ? &lpath_66 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$XML'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$XML'.'/^x\\\\-.*$/']", (path ? &lpath_66 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$XML']", (path ? &lpath_66 : NULL));
            return false;
        }
    }
    return true;
}

// check $XML (.'$XML')
static bool json_model_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$XML'
    res = _jm_obj_68(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$XML']", path);
    }
    return res;
}

// check _jm_obj_69_mup_flows (.'$SecurityScheme'.flows)
static bool _jm_f_183(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.flows
    res = json_model_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlows [.'$SecurityScheme'.flows]", path);
    }
    return res;
}


// check _jm_obj_69_mup_in (.'$SecurityScheme'.in)
static bool _jm_f_184(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.in
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_4, 3);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$SecurityScheme'.in.'|']", path);
    }
    return res;
}

// check _jm_obj_69_mup_name (.'$SecurityScheme'.name)
static bool _jm_f_185(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.name
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.name]", path);
    }
    return res;
}

// check _jm_obj_69_mup_openIdConnectUrl (.'$SecurityScheme'.openIdConnectUrl)
static bool _jm_f_186(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.openIdConnectUrl
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.openIdConnectUrl]", path);
    }
    return res;
}

// check _jm_obj_69_mup_scheme (.'$SecurityScheme'.scheme)
static bool _jm_f_187(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.scheme
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.scheme]", path);
    }
    return res;
}

// check _jm_obj_69_mup_type (.'$SecurityScheme'.type)
static bool _jm_f_188(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'.type
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.type]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_69_mup(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_69_mup_tab, 6);
}

// object .'$SecurityScheme'
static bool _jm_obj_69(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$SecurityScheme']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_67 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_69_mup(prop)))
        {
            // handle 6 mandatory props
            if (pfun != NULL)
            {
                must_count += 1;
                if (! pfun(pval, (path ? &lpath_67 : NULL), rep))
                {
                    if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$SecurityScheme']", (path ? &lpath_67 : NULL));
                    return false;
                }
            }
        }
        else if (strcmp(prop, "description") == 0)
        {
            // handle may description property
            // .'$SecurityScheme'.description
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.description]", (path ? &lpath_67 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$SecurityScheme'.description]", (path ? &lpath_67 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "bearerFormat") == 0)
        {
            // handle may bearerFormat property
            // .'$SecurityScheme'.bearerFormat
            res = json_is_string(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityScheme'.bearerFormat]", (path ? &lpath_67 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$SecurityScheme'.bearerFormat]", (path ? &lpath_67 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$SecurityScheme'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$SecurityScheme'.'/^x\\\\-.*$/']", (path ? &lpath_67 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$SecurityScheme']", (path ? &lpath_67 : NULL));
            return false;
        }
    }
    if (must_count != 6)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "flows") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <flows> [.'$SecurityScheme']", path);
            }
            if (! (json_object_get(val, "in") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <in> [.'$SecurityScheme']", path);
            }
            if (! (json_object_get(val, "name") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <name> [.'$SecurityScheme']", path);
            }
            if (! (json_object_get(val, "openIdConnectUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <openIdConnectUrl> [.'$SecurityScheme']", path);
            }
            if (! (json_object_get(val, "scheme") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <scheme> [.'$SecurityScheme']", path);
            }
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$SecurityScheme']", path);
            }
        }
        return false;
    }
    return true;
}

// check $SecurityScheme (.'$SecurityScheme')
static bool json_model_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityScheme'
    res = _jm_obj_69(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$SecurityScheme']", path);
    }
    return res;
}

// check _jm_obj_70_map_authorizationCode (.'$OAuthFlows'.authorizationCode)
static bool _jm_f_189(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlows'.authorizationCode
    res = json_model_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$OAuthFlows'.authorizationCode]", path);
    }
    return res;
}

// check _jm_obj_70_map_clientCredentials (.'$OAuthFlows'.clientCredentials)
static bool _jm_f_190(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlows'.clientCredentials
    res = json_model_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$OAuthFlows'.clientCredentials]", path);
    }
    return res;
}

// check _jm_obj_70_map_implicit (.'$OAuthFlows'.implicit)
static bool _jm_f_191(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlows'.implicit
    res = json_model_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$OAuthFlows'.implicit]", path);
    }
    return res;
}

// check _jm_obj_70_map_password (.'$OAuthFlows'.password)
static bool _jm_f_192(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlows'.password
    res = json_model_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OAuthFlow [.'$OAuthFlows'.password]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_70_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_70_map_tab, 4);
}

// object .'$OAuthFlows'
static bool _jm_obj_70(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OAuthFlows']", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_68 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_70_map(prop)))
        {
            // handle 4 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_68 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$OAuthFlows']", (path ? &lpath_68 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$OAuthFlows'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$OAuthFlows'.'/^x\\\\-.*$/']", (path ? &lpath_68 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$OAuthFlows']", (path ? &lpath_68 : NULL));
            return false;
        }
    }
    return true;
}

// check $OAuthFlows (.'$OAuthFlows')
static bool json_model_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlows'
    res = _jm_obj_70(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OAuthFlows']", path);
    }
    return res;
}

// object .'$OAuthFlow'.scopes
static bool _jm_obj_72(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OAuthFlow'.scopes]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_70 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$OAuthFlow'.scopes.''
        res = json_is_string(pval);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected string [.'$OAuthFlow'.scopes.'']", (path ? &lpath_70 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// object .'$OAuthFlow'
static bool _jm_obj_71(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$OAuthFlow']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_69 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "authorizationUrl") == 0)
        {
            // handle must authorizationUrl property
            must_count += 1;
            // .'$OAuthFlow'.authorizationUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$OAuthFlow'.authorizationUrl]", (path ? &lpath_69 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OAuthFlow'.authorizationUrl]", (path ? &lpath_69 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "tokenUrl") == 0)
        {
            // handle must tokenUrl property
            must_count += 1;
            // .'$OAuthFlow'.tokenUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$OAuthFlow'.tokenUrl]", (path ? &lpath_69 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OAuthFlow'.tokenUrl]", (path ? &lpath_69 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "scopes") == 0)
        {
            // handle must scopes property
            must_count += 1;
            // .'$OAuthFlow'.scopes
            res = _jm_obj_72(pval, (path ? &lpath_69 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$OAuthFlow'.scopes]", (path ? &lpath_69 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$OAuthFlow'.scopes]", (path ? &lpath_69 : NULL));
                return false;
            }
        }
        else if (strcmp(prop, "refreshUrl") == 0)
        {
            // handle may refreshUrl property
            // .'$OAuthFlow'.refreshUrl
            res = jm_is_valid_url(json_string_value(pval));
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $URL [.'$OAuthFlow'.refreshUrl]", (path ? &lpath_69 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$OAuthFlow'.refreshUrl]", (path ? &lpath_69 : NULL));
                return false;
            }
        }
        else if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$OAuthFlow'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$OAuthFlow'.'/^x\\\\-.*$/']", (path ? &lpath_69 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$OAuthFlow']", (path ? &lpath_69 : NULL));
            return false;
        }
    }
    if (must_count != 3)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "authorizationUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <authorizationUrl> [.'$OAuthFlow']", path);
            }
            if (! (json_object_get(val, "scopes") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <scopes> [.'$OAuthFlow']", path);
            }
            if (! (json_object_get(val, "tokenUrl") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <tokenUrl> [.'$OAuthFlow']", path);
            }
        }
        return false;
    }
    return true;
}

// check $OAuthFlow (.'$OAuthFlow')
static bool json_model_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$OAuthFlow'
    res = _jm_obj_71(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$OAuthFlow']", path);
    }
    return res;
}

// object .'$SecurityRequirement'
static bool _jm_obj_73(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$SecurityRequirement']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_71 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$SecurityRequirement'.''
        res = json_is_array(pval);
        if (res)
        {
            size_t arr_9_idx;
            json_t *arr_9_item;
            json_array_foreach(pval, arr_9_idx, arr_9_item)
            {
                jm_path_t arr_9_lpath = (jm_path_t) { NULL, arr_9_idx, (path ? &lpath_71 : NULL), NULL };
                // .'$SecurityRequirement'.''.0
                res = json_is_string(arr_9_item);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "unexpected string [.'$SecurityRequirement'.''.0]", ((path ? &lpath_71 : NULL) ? &arr_9_lpath : NULL));
                }
                if (! res)
                {
                    break;
                }
            }
        }
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$SecurityRequirement'.'']", (path ? &lpath_71 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check $SecurityRequirement (.'$SecurityRequirement')
static bool json_model_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$SecurityRequirement'
    res = _jm_obj_73(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$SecurityRequirement']", path);
    }
    return res;
}

// object .'$Extension'
static bool _jm_obj_74(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Extension']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_72 = (jm_path_t) { prop, 0, path, NULL };
        if (_jm_re_1(prop))
        {
            // handle 1 re props
            // .'$Extension'.'/^x\\-.*$/'
            res = true;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Extension'.'/^x\\\\-.*$/']", (path ? &lpath_72 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Extension']", (path ? &lpath_72 : NULL));
            return false;
        }
    }
    return true;
}

// check $Extension (.'$Extension')
static bool json_model_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Extension'
    res = _jm_obj_74(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Extension']", path);
    }
    return res;
}

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $OpenAPI [.]", path);
    }
    return res;
}

// check $schema#URI-REFERENCE (.'$schema#URI-REFERENCE')
static bool json_model_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#URI-REFERENCE'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#URI-REFERENCE']", path);
    }
    return res;
}


// check $schema#simpleTypes (.'$schema#simpleTypes')
static bool json_model_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#simpleTypes'
    res = jm_json_is_scalar(val) && json_is_string(val) && jm_search_cst(&(jm_constant_t) { cst_is_string, { .s = json_string_value(val) } }, _jm_cst_5, 7);;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "value not in enum [.'$schema#simpleTypes'.'|']", path);
    }
    return res;
}

// check $schema#simpleTypesArray (.'$schema#simpleTypesArray')
static bool json_model_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#simpleTypesArray'
    // .'$schema#simpleTypesArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_10_idx;
        json_t *arr_10_item;
        json_array_foreach(val, arr_10_idx, arr_10_item)
        {
            jm_path_t arr_10_lpath = (jm_path_t) { NULL, arr_10_idx, path, NULL };
            // .'$schema#simpleTypesArray'.'@'.0
            res = json_model_47(arr_10_item, (path ? &arr_10_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [.'$schema#simpleTypesArray'.'@'.0]", (path ? &arr_10_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#simpleTypesArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = jm_array_is_unique(val, path, rep) && ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#simpleTypesArray']", path);
    }
    return res;
}

// check $schema#stringArray (.'$schema#stringArray')
static bool json_model_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#stringArray'
    // .'$schema#stringArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_11_idx;
        json_t *arr_11_item;
        json_array_foreach(val, arr_11_idx, arr_11_item)
        {
            jm_path_t arr_11_lpath = (jm_path_t) { NULL, arr_11_idx, path, NULL };
            // .'$schema#stringArray'.'@'.0
            res = json_is_string(arr_11_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#stringArray'.'@'.0]", (path ? &arr_11_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#stringArray'.'@']", path);
    }
    if (res)
    {
        res = jm_array_is_unique(val, path, rep);
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#stringArray']", path);
    }
    return res;
}

// check $schema#nonNegativeInteger (.'$schema#nonNegativeInteger')
static bool json_model_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#nonNegativeInteger'
    res = ((json_is_integer(val) || (json_is_real(val) && json_real_value(val) == ((int64_t) json_real_value(val))))) && json_number_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 loose int [.'$schema#nonNegativeInteger']", path);
    }
    return res;
}

// check $schema#schemaArray (.'$schema#schemaArray')
static bool json_model_52(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#schemaArray'
    // .'$schema#schemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_12_idx;
        json_t *arr_12_item;
        json_array_foreach(val, arr_12_idx, arr_12_item)
        {
            jm_path_t arr_12_lpath = (jm_path_t) { NULL, arr_12_idx, path, NULL };
            // .'$schema#schemaArray'.'@'.0
            res = json_model_55(arr_12_item, (path ? &arr_12_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#schemaArray'.'@'.0]", (path ? &arr_12_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#schemaArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_1 = json_array_size(val);
        res = ival_1 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schema#schemaArray']", path);
    }
    return res;
}

// check $schema#Schema (.'$schema#Schema')
static bool json_model_55(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#Schema'
    // .'$schema#Schema'.'|'.0
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#Schema'.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema#Schema'.'|'.1
        res = json_model_54(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $ObjectSchema [.'$schema#Schema'.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema#Schema'.'|']", path);
    }
    return res;
}

// check _jm_obj_75_map_$anchor (.'$schema#ObjectSchema'.'$anchor')
static bool _jm_f_193(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$anchor'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$schema#ObjectSchema'.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_75_map_$comment (.'$schema#ObjectSchema'.'$comment')
static bool _jm_f_194(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.'$comment']", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.'$defs'
static bool _jm_obj_76(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_74 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema#ObjectSchema'.'$defs'.''
        res = json_model_55(pval, (path ? &lpath_74 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.'$defs'.'']", (path ? &lpath_74 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_$defs (.'$schema#ObjectSchema'.'$defs')
static bool _jm_f_195(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$defs'
    res = _jm_obj_76(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_75_map_$dynamicAnchor (.'$schema#ObjectSchema'.'$dynamicAnchor')
static bool _jm_f_196(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$dynamicAnchor'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$schema#ObjectSchema'.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_75_map_$dynamicRef (.'$schema#ObjectSchema'.'$dynamicRef')
static bool _jm_f_197(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$dynamicRef'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$schema#ObjectSchema'.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_75_map_$id (.'$schema#ObjectSchema'.'$id')
static bool _jm_f_198(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$id'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$schema#ObjectSchema'.'$id']", path);
    }
    return res;
}

// check _jm_obj_75_map_$ref (.'$schema#ObjectSchema'.'$ref')
static bool _jm_f_199(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$ref'
    res = json_model_41(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$schema#ObjectSchema'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_75_map_$schema (.'$schema#ObjectSchema'.'$schema')
static bool _jm_f_200(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$schema'
    res = json_is_string(val) && strcmp(json_string_value(val), "https://json-schema.org/draft/2020-12/schema") == 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected _https://json-schema.org/draft/2020-12/schema [.'$schema#ObjectSchema'.'$schema']", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.'$vocabulary'
static bool _jm_obj_77(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_75 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$schema#ObjectSchema'.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#ObjectSchema'.'$vocabulary'.'$URI']", (path ? &lpath_75 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$schema#ObjectSchema'.'$vocabulary']", (path ? &lpath_75 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_$vocabulary (.'$schema#ObjectSchema'.'$vocabulary')
static bool _jm_f_201(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.'$vocabulary'
    res = _jm_obj_77(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_75_map_additionalProperties (.'$schema#ObjectSchema'.additionalProperties)
static bool _jm_f_202(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.additionalProperties
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_75_map_allOf (.'$schema#ObjectSchema'.allOf)
static bool _jm_f_203(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.allOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema#ObjectSchema'.allOf]", path);
    }
    return res;
}

// check _jm_obj_75_map_anyOf (.'$schema#ObjectSchema'.anyOf)
static bool _jm_f_204(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.anyOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema#ObjectSchema'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_75_map_const (.'$schema#ObjectSchema'.const)
static bool _jm_f_205(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.const
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$schema#ObjectSchema'.const]", path);
    }
    return res;
}

// check _jm_obj_75_map_contains (.'$schema#ObjectSchema'.contains)
static bool _jm_f_206(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.contains
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.contains]", path);
    }
    return res;
}

// check _jm_obj_75_map_contentEncoding (.'$schema#ObjectSchema'.contentEncoding)
static bool _jm_f_207(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_75_map_contentMediaType (.'$schema#ObjectSchema'.contentMediaType)
static bool _jm_f_208(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.contentMediaType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.contentMediaType]", path);
    }
    return res;
}

// check _jm_obj_75_map_contentSchema (.'$schema#ObjectSchema'.contentSchema)
static bool _jm_f_209(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.contentSchema
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.contentSchema]", path);
    }
    return res;
}

// check _jm_obj_75_map_default (.'$schema#ObjectSchema'.default)
static bool _jm_f_210(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$schema#ObjectSchema'.default]", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.dependentRequired
static bool _jm_obj_78(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.dependentRequired]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_76 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema#ObjectSchema'.dependentRequired.''
        res = json_model_49(pval, (path ? &lpath_76 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema#ObjectSchema'.dependentRequired.'']", (path ? &lpath_76 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_dependentRequired (.'$schema#ObjectSchema'.dependentRequired)
static bool _jm_f_211(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.dependentRequired
    res = _jm_obj_78(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.dependentRequired]", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.dependentSchemas
static bool _jm_obj_79(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.dependentSchemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_77 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema#ObjectSchema'.dependentSchemas.''
        res = json_model_55(pval, (path ? &lpath_77 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.dependentSchemas.'']", (path ? &lpath_77 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_dependentSchemas (.'$schema#ObjectSchema'.dependentSchemas)
static bool _jm_f_212(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.dependentSchemas
    res = _jm_obj_79(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.dependentSchemas]", path);
    }
    return res;
}

// check _jm_obj_75_map_deprecated (.'$schema#ObjectSchema'.deprecated)
static bool _jm_f_213(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#ObjectSchema'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_75_map_description (.'$schema#ObjectSchema'.description)
static bool _jm_f_214(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.description]", path);
    }
    return res;
}

// check _jm_obj_75_map_else (.'$schema#ObjectSchema'.else)
static bool _jm_f_215(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.else
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.else]", path);
    }
    return res;
}

// check _jm_obj_75_map_enum (.'$schema#ObjectSchema'.enum)
static bool _jm_f_216(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.enum
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#ObjectSchema'.enum]", path);
    }
    return res;
}

// check _jm_obj_75_map_examples (.'$schema#ObjectSchema'.examples)
static bool _jm_f_217(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schema#ObjectSchema'.examples]", path);
    }
    return res;
}

// check _jm_obj_75_map_exclusiveMaximum (.'$schema#ObjectSchema'.exclusiveMaximum)
static bool _jm_f_218(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.exclusiveMaximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema#ObjectSchema'.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_75_map_exclusiveMinimum (.'$schema#ObjectSchema'.exclusiveMinimum)
static bool _jm_f_219(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.exclusiveMinimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema#ObjectSchema'.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_75_map_format (.'$schema#ObjectSchema'.format)
static bool _jm_f_220(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.format]", path);
    }
    return res;
}

// check _jm_obj_75_map_if (.'$schema#ObjectSchema'.if)
static bool _jm_f_221(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.if
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.if]", path);
    }
    return res;
}

// check _jm_obj_75_map_items (.'$schema#ObjectSchema'.items)
static bool _jm_f_222(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.items
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.items]", path);
    }
    return res;
}

// check _jm_obj_75_map_maxContains (.'$schema#ObjectSchema'.maxContains)
static bool _jm_f_223(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.maxContains
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.maxContains]", path);
    }
    return res;
}

// check _jm_obj_75_map_maxItems (.'$schema#ObjectSchema'.maxItems)
static bool _jm_f_224(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.maxItems
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.maxItems]", path);
    }
    return res;
}

// check _jm_obj_75_map_maxLength (.'$schema#ObjectSchema'.maxLength)
static bool _jm_f_225(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.maxLength
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.maxLength]", path);
    }
    return res;
}

// check _jm_obj_75_map_maxProperties (.'$schema#ObjectSchema'.maxProperties)
static bool _jm_f_226(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.maxProperties
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_75_map_maximum (.'$schema#ObjectSchema'.maximum)
static bool _jm_f_227(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.maximum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema#ObjectSchema'.maximum]", path);
    }
    return res;
}

// check _jm_obj_75_map_minContains (.'$schema#ObjectSchema'.minContains)
static bool _jm_f_228(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.minContains
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.minContains]", path);
    }
    return res;
}

// check _jm_obj_75_map_minItems (.'$schema#ObjectSchema'.minItems)
static bool _jm_f_229(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.minItems
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.minItems]", path);
    }
    return res;
}

// check _jm_obj_75_map_minLength (.'$schema#ObjectSchema'.minLength)
static bool _jm_f_230(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.minLength
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.minLength]", path);
    }
    return res;
}

// check _jm_obj_75_map_minProperties (.'$schema#ObjectSchema'.minProperties)
static bool _jm_f_231(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.minProperties
    res = json_model_50(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $nonNegativeInteger [.'$schema#ObjectSchema'.minProperties]", path);
    }
    return res;
}

// check _jm_obj_75_map_minimum (.'$schema#ObjectSchema'.minimum)
static bool _jm_f_232(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.minimum
    res = json_is_number(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1.0 loose float [.'$schema#ObjectSchema'.minimum]", path);
    }
    return res;
}

// check _jm_obj_75_map_multipleOf (.'$schema#ObjectSchema'.multipleOf)
static bool _jm_f_233(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.multipleOf
    res = json_is_number(val) && json_number_value(val) > 0.0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1.0 loose float [.'$schema#ObjectSchema'.multipleOf]", path);
    }
    return res;
}

// check _jm_obj_75_map_not (.'$schema#ObjectSchema'.not)
static bool _jm_f_234(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.not
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.not]", path);
    }
    return res;
}

// check _jm_obj_75_map_oneOf (.'$schema#ObjectSchema'.oneOf)
static bool _jm_f_235(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.oneOf
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema#ObjectSchema'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_75_map_pattern (.'$schema#ObjectSchema'.pattern)
static bool _jm_f_236(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.pattern
    res = jm_is_valid_regex(json_string_value(val), false);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$schema#ObjectSchema'.pattern]", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.patternProperties
static bool _jm_obj_80(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_78 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop, false))
        {
            // handle 1 key props
            // .'$schema#ObjectSchema'.patternProperties.'$REGEX'
            res = json_model_55(pval, (path ? &lpath_78 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.patternProperties.'$REGEX']", (path ? &lpath_78 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$schema#ObjectSchema'.patternProperties]", (path ? &lpath_78 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_patternProperties (.'$schema#ObjectSchema'.patternProperties)
static bool _jm_f_237(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.patternProperties
    res = _jm_obj_80(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.patternProperties]", path);
    }
    return res;
}

// check _jm_obj_75_map_prefixItems (.'$schema#ObjectSchema'.prefixItems)
static bool _jm_f_238(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.prefixItems
    res = json_model_52(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$schema#ObjectSchema'.prefixItems]", path);
    }
    return res;
}

// object .'$schema#ObjectSchema'.properties
static bool _jm_obj_81(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema'.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_79 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$schema#ObjectSchema'.properties.''
        res = json_model_55(pval, (path ? &lpath_79 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.properties.'']", (path ? &lpath_79 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_75_map_properties (.'$schema#ObjectSchema'.properties)
static bool _jm_f_239(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.properties
    res = _jm_obj_81(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema'.properties]", path);
    }
    return res;
}

// check _jm_obj_75_map_propertyNames (.'$schema#ObjectSchema'.propertyNames)
static bool _jm_f_240(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.propertyNames
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_75_map_readOnly (.'$schema#ObjectSchema'.readOnly)
static bool _jm_f_241(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#ObjectSchema'.readOnly]", path);
    }
    return res;
}

// check _jm_obj_75_map_required (.'$schema#ObjectSchema'.required)
static bool _jm_f_242(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.required
    res = json_model_49(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$schema#ObjectSchema'.required]", path);
    }
    return res;
}

// check _jm_obj_75_map_then (.'$schema#ObjectSchema'.then)
static bool _jm_f_243(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.then
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.then]", path);
    }
    return res;
}

// check _jm_obj_75_map_title (.'$schema#ObjectSchema'.title)
static bool _jm_f_244(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$schema#ObjectSchema'.title]", path);
    }
    return res;
}

// check _jm_obj_75_map_type (.'$schema#ObjectSchema'.type)
static bool _jm_f_245(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.type
    // .'$schema#ObjectSchema'.type.'|'.0
    res = json_model_47(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $simpleTypes [.'$schema#ObjectSchema'.type.'|'.0]", path);
    }
    if (! res)
    {
        // .'$schema#ObjectSchema'.type.'|'.1
        res = json_model_48(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $simpleTypesArray [.'$schema#ObjectSchema'.type.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$schema#ObjectSchema'.type.'|']", path);
    }
    return res;
}

// check _jm_obj_75_map_unevaluatedItems (.'$schema#ObjectSchema'.unevaluatedItems)
static bool _jm_f_246(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.unevaluatedItems
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.unevaluatedItems]", path);
    }
    return res;
}

// check _jm_obj_75_map_unevaluatedProperties (.'$schema#ObjectSchema'.unevaluatedProperties)
static bool _jm_f_247(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.unevaluatedProperties
    res = json_model_55(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schema#ObjectSchema'.unevaluatedProperties]", path);
    }
    return res;
}

// check _jm_obj_75_map_uniqueItems (.'$schema#ObjectSchema'.uniqueItems)
static bool _jm_f_248(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#ObjectSchema'.uniqueItems]", path);
    }
    return res;
}

// check _jm_obj_75_map_writeOnly (.'$schema#ObjectSchema'.writeOnly)
static bool _jm_f_249(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$schema#ObjectSchema'.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_75_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_75_map_tab, 57);
}

// object .'$schema#ObjectSchema'
static bool _jm_obj_75(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$schema#ObjectSchema']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_73 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_75_map(prop)))
        {
            // handle 57 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_73 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$schema#ObjectSchema']", (path ? &lpath_73 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$schema#ObjectSchema']", (path ? &lpath_73 : NULL));
            return false;
        }
    }
    return true;
}

// check $schema#ObjectSchema (.'$schema#ObjectSchema')
static bool json_model_54(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schema#ObjectSchema'
    res = _jm_obj_75(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$schema#ObjectSchema']", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 39);
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
        _jm_obj_0_map_tab[0] = (jm_propmap_t) { "component", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (jm_propmap_t) { "externalDocs", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (jm_propmap_t) { "jsonSchemaDialect", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (jm_propmap_t) { "paths", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (jm_propmap_t) { "security", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (jm_propmap_t) { "servers", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (jm_propmap_t) { "tags", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (jm_propmap_t) { "webhooks", _jm_f_7 };
        jm_sort_propmap(_jm_obj_0_map_tab, 8);
        _jm_re_1_code = pcre2_compile((PCRE2_SPTR) "^x\\-.*$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_1_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_1_data = pcre2_match_data_create_from_pattern(_jm_re_1_code, NULL);
        _jm_obj_2_map_tab[0] = (jm_propmap_t) { "contact", _jm_f_8 };
        _jm_obj_2_map_tab[1] = (jm_propmap_t) { "description", _jm_f_9 };
        _jm_obj_2_map_tab[2] = (jm_propmap_t) { "license", _jm_f_10 };
        _jm_obj_2_map_tab[3] = (jm_propmap_t) { "summary", _jm_f_11 };
        _jm_obj_2_map_tab[4] = (jm_propmap_t) { "termsOfService", _jm_f_12 };
        jm_sort_propmap(_jm_obj_2_map_tab, 5);
        _jm_obj_9_map_tab[0] = (jm_propmap_t) { "callbacks", _jm_f_13 };
        _jm_obj_9_map_tab[1] = (jm_propmap_t) { "examples", _jm_f_14 };
        _jm_obj_9_map_tab[2] = (jm_propmap_t) { "headers", _jm_f_15 };
        _jm_obj_9_map_tab[3] = (jm_propmap_t) { "links", _jm_f_16 };
        _jm_obj_9_map_tab[4] = (jm_propmap_t) { "parameters", _jm_f_17 };
        _jm_obj_9_map_tab[5] = (jm_propmap_t) { "pathItems", _jm_f_18 };
        _jm_obj_9_map_tab[6] = (jm_propmap_t) { "requestBodies", _jm_f_19 };
        _jm_obj_9_map_tab[7] = (jm_propmap_t) { "responses", _jm_f_20 };
        _jm_obj_9_map_tab[8] = (jm_propmap_t) { "schemas", _jm_f_21 };
        _jm_obj_9_map_tab[9] = (jm_propmap_t) { "securitySchemes", _jm_f_22 };
        jm_sort_propmap(_jm_obj_9_map_tab, 10);
        _jm_re_2_code = pcre2_compile((PCRE2_SPTR) "^/", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_2_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_2_data = pcre2_match_data_create_from_pattern(_jm_re_2_code, NULL);
        _jm_obj_21_map_tab[0] = (jm_propmap_t) { "$ref", _jm_f_23 };
        _jm_obj_21_map_tab[1] = (jm_propmap_t) { "delete", _jm_f_24 };
        _jm_obj_21_map_tab[2] = (jm_propmap_t) { "description", _jm_f_25 };
        _jm_obj_21_map_tab[3] = (jm_propmap_t) { "get", _jm_f_26 };
        _jm_obj_21_map_tab[4] = (jm_propmap_t) { "head", _jm_f_27 };
        _jm_obj_21_map_tab[5] = (jm_propmap_t) { "options", _jm_f_28 };
        _jm_obj_21_map_tab[6] = (jm_propmap_t) { "parameters", _jm_f_29 };
        _jm_obj_21_map_tab[7] = (jm_propmap_t) { "patch", _jm_f_30 };
        _jm_obj_21_map_tab[8] = (jm_propmap_t) { "post", _jm_f_31 };
        _jm_obj_21_map_tab[9] = (jm_propmap_t) { "put", _jm_f_32 };
        _jm_obj_21_map_tab[10] = (jm_propmap_t) { "servers", _jm_f_33 };
        _jm_obj_21_map_tab[11] = (jm_propmap_t) { "summary", _jm_f_34 };
        _jm_obj_21_map_tab[12] = (jm_propmap_t) { "trace", _jm_f_35 };
        jm_sort_propmap(_jm_obj_21_map_tab, 13);
        _jm_obj_22_map_tab[0] = (jm_propmap_t) { "callbacks", _jm_f_36 };
        _jm_obj_22_map_tab[1] = (jm_propmap_t) { "deprecated", _jm_f_37 };
        _jm_obj_22_map_tab[2] = (jm_propmap_t) { "description", _jm_f_38 };
        _jm_obj_22_map_tab[3] = (jm_propmap_t) { "externalDocs", _jm_f_39 };
        _jm_obj_22_map_tab[4] = (jm_propmap_t) { "operationId", _jm_f_40 };
        _jm_obj_22_map_tab[5] = (jm_propmap_t) { "parameters", _jm_f_41 };
        _jm_obj_22_map_tab[6] = (jm_propmap_t) { "requestBody", _jm_f_42 };
        _jm_obj_22_map_tab[7] = (jm_propmap_t) { "responses", _jm_f_43 };
        _jm_obj_22_map_tab[8] = (jm_propmap_t) { "security", _jm_f_44 };
        _jm_obj_22_map_tab[9] = (jm_propmap_t) { "servers", _jm_f_45 };
        _jm_obj_22_map_tab[10] = (jm_propmap_t) { "summary", _jm_f_46 };
        _jm_obj_22_map_tab[11] = (jm_propmap_t) { "tags", _jm_f_47 };
        jm_sort_propmap(_jm_obj_22_map_tab, 12);
        _jm_obj_25_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_48 };
        _jm_obj_25_map_tab[1] = (jm_propmap_t) { "deprecated", _jm_f_49 };
        _jm_obj_25_map_tab[2] = (jm_propmap_t) { "description", _jm_f_50 };
        _jm_obj_25_map_tab[3] = (jm_propmap_t) { "required", _jm_f_51 };
        jm_sort_propmap(_jm_obj_25_map_tab, 4);
        // initialize sorted set _jm_cst_0
        _jm_cst_0[0] = (jm_constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_0[1] = (jm_constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_0[2] = (jm_constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_0[3] = (jm_constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_0, 4);
        _jm_obj_26_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_52 };
        _jm_obj_26_map_tab[1] = (jm_propmap_t) { "deprecated", _jm_f_53 };
        _jm_obj_26_map_tab[2] = (jm_propmap_t) { "description", _jm_f_54 };
        _jm_obj_26_map_tab[3] = (jm_propmap_t) { "required", _jm_f_55 };
        jm_sort_propmap(_jm_obj_26_map_tab, 4);
        // initialize sorted set _jm_cst_1
        _jm_cst_1[0] = (jm_constant_t) { cst_is_string, { .s = "matrix" } };
        _jm_cst_1[1] = (jm_constant_t) { cst_is_string, { .s = "label" } };
        _jm_cst_1[2] = (jm_constant_t) { cst_is_string, { .s = "form" } };
        _jm_cst_1[3] = (jm_constant_t) { cst_is_string, { .s = "simple" } };
        _jm_cst_1[4] = (jm_constant_t) { cst_is_string, { .s = "spaceDelimited" } };
        _jm_cst_1[5] = (jm_constant_t) { cst_is_string, { .s = "pipeDelimited" } };
        _jm_cst_1[6] = (jm_constant_t) { cst_is_string, { .s = "deepObject" } };
        jm_sort_cst(_jm_cst_1, 7);
        _jm_obj_27_map_tab[0] = (jm_propmap_t) { "allowReserved", _jm_f_56 };
        _jm_obj_27_map_tab[1] = (jm_propmap_t) { "example", _jm_f_57 };
        _jm_obj_27_map_tab[2] = (jm_propmap_t) { "examples", _jm_f_58 };
        _jm_obj_27_map_tab[3] = (jm_propmap_t) { "explode", _jm_f_59 };
        _jm_obj_27_map_tab[4] = (jm_propmap_t) { "schema", _jm_f_60 };
        _jm_obj_27_map_tab[5] = (jm_propmap_t) { "style", _jm_f_61 };
        jm_sort_propmap(_jm_obj_27_map_tab, 6);
        // initialize sorted set _jm_cst_2
        _jm_cst_2[0] = (jm_constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_2[1] = (jm_constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_2[2] = (jm_constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_2[3] = (jm_constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_2, 4);
        _jm_obj_31_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_62 };
        _jm_obj_31_map_tab[1] = (jm_propmap_t) { "content", _jm_f_63 };
        _jm_obj_31_map_tab[2] = (jm_propmap_t) { "deprecated", _jm_f_64 };
        _jm_obj_31_map_tab[3] = (jm_propmap_t) { "description", _jm_f_65 };
        _jm_obj_31_map_tab[4] = (jm_propmap_t) { "required", _jm_f_66 };
        jm_sort_propmap(_jm_obj_31_map_tab, 5);
        // initialize sorted set _jm_cst_3
        _jm_cst_3[0] = (jm_constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_3[1] = (jm_constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_3[2] = (jm_constant_t) { cst_is_string, { .s = "path" } };
        _jm_cst_3[3] = (jm_constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_3, 4);
        _jm_obj_33_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_67 };
        _jm_obj_33_map_tab[1] = (jm_propmap_t) { "allowReserved", _jm_f_68 };
        _jm_obj_33_map_tab[2] = (jm_propmap_t) { "deprecated", _jm_f_69 };
        _jm_obj_33_map_tab[3] = (jm_propmap_t) { "description", _jm_f_70 };
        _jm_obj_33_map_tab[4] = (jm_propmap_t) { "example", _jm_f_71 };
        _jm_obj_33_map_tab[5] = (jm_propmap_t) { "examples", _jm_f_72 };
        _jm_obj_33_map_tab[6] = (jm_propmap_t) { "explode", _jm_f_73 };
        _jm_obj_33_map_tab[7] = (jm_propmap_t) { "required", _jm_f_74 };
        _jm_obj_33_map_tab[8] = (jm_propmap_t) { "schema", _jm_f_75 };
        _jm_obj_33_map_tab[9] = (jm_propmap_t) { "style", _jm_f_76 };
        jm_sort_propmap(_jm_obj_33_map_tab, 10);
        _jm_obj_37_map_tab[0] = (jm_propmap_t) { "encoding", _jm_f_77 };
        _jm_obj_37_map_tab[1] = (jm_propmap_t) { "example", _jm_f_78 };
        _jm_obj_37_map_tab[2] = (jm_propmap_t) { "examples", _jm_f_79 };
        _jm_obj_37_map_tab[3] = (jm_propmap_t) { "schema", _jm_f_80 };
        jm_sort_propmap(_jm_obj_37_map_tab, 4);
        _jm_obj_40_map_tab[0] = (jm_propmap_t) { "allowReserved", _jm_f_81 };
        _jm_obj_40_map_tab[1] = (jm_propmap_t) { "contentType", _jm_f_82 };
        _jm_obj_40_map_tab[2] = (jm_propmap_t) { "explode", _jm_f_83 };
        _jm_obj_40_map_tab[3] = (jm_propmap_t) { "headers", _jm_f_84 };
        _jm_obj_40_map_tab[4] = (jm_propmap_t) { "style", _jm_f_85 };
        jm_sort_propmap(_jm_obj_40_map_tab, 5);
        _jm_re_3_code = pcre2_compile((PCRE2_SPTR) "^[1-5](\\d\\d|XX)$", PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);
        if (_jm_re_3_code == NULL)
        {
            (void) pcre2_get_error_message(err_code, err_message, 1024);
            return (char *) err_message;
        }
        _jm_re_3_data = pcre2_match_data_create_from_pattern(_jm_re_3_code, NULL);
        _jm_obj_43_map_tab[0] = (jm_propmap_t) { "content", _jm_f_86 };
        _jm_obj_43_map_tab[1] = (jm_propmap_t) { "description", _jm_f_87 };
        _jm_obj_43_map_tab[2] = (jm_propmap_t) { "headers", _jm_f_88 };
        _jm_obj_43_map_tab[3] = (jm_propmap_t) { "links", _jm_f_89 };
        jm_sort_propmap(_jm_obj_43_map_tab, 4);
        _jm_obj_48_map_tab[0] = (jm_propmap_t) { "description", _jm_f_90 };
        _jm_obj_48_map_tab[1] = (jm_propmap_t) { "externalValue", _jm_f_91 };
        _jm_obj_48_map_tab[2] = (jm_propmap_t) { "summary", _jm_f_92 };
        _jm_obj_48_map_tab[3] = (jm_propmap_t) { "value", _jm_f_93 };
        jm_sort_propmap(_jm_obj_48_map_tab, 4);
        _jm_obj_49_map_tab[0] = (jm_propmap_t) { "description", _jm_f_94 };
        _jm_obj_49_map_tab[1] = (jm_propmap_t) { "parameters", _jm_f_95 };
        _jm_obj_49_map_tab[2] = (jm_propmap_t) { "requestBody", _jm_f_96 };
        _jm_obj_49_map_tab[3] = (jm_propmap_t) { "server", _jm_f_97 };
        jm_sort_propmap(_jm_obj_49_map_tab, 4);
        _jm_obj_51_map_tab[0] = (jm_propmap_t) { "description", _jm_f_98 };
        _jm_obj_51_map_tab[1] = (jm_propmap_t) { "parameters", _jm_f_99 };
        _jm_obj_51_map_tab[2] = (jm_propmap_t) { "requestBody", _jm_f_100 };
        _jm_obj_51_map_tab[3] = (jm_propmap_t) { "server", _jm_f_101 };
        jm_sort_propmap(_jm_obj_51_map_tab, 4);
        _jm_obj_53_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_102 };
        _jm_obj_53_map_tab[1] = (jm_propmap_t) { "content", _jm_f_103 };
        _jm_obj_53_map_tab[2] = (jm_propmap_t) { "deprecated", _jm_f_104 };
        _jm_obj_53_map_tab[3] = (jm_propmap_t) { "description", _jm_f_105 };
        _jm_obj_53_map_tab[4] = (jm_propmap_t) { "required", _jm_f_106 };
        jm_sort_propmap(_jm_obj_53_map_tab, 5);
        _jm_obj_55_map_tab[0] = (jm_propmap_t) { "allowEmptyValue", _jm_f_107 };
        _jm_obj_55_map_tab[1] = (jm_propmap_t) { "allowReserved", _jm_f_108 };
        _jm_obj_55_map_tab[2] = (jm_propmap_t) { "deprecated", _jm_f_109 };
        _jm_obj_55_map_tab[3] = (jm_propmap_t) { "description", _jm_f_110 };
        _jm_obj_55_map_tab[4] = (jm_propmap_t) { "example", _jm_f_111 };
        _jm_obj_55_map_tab[5] = (jm_propmap_t) { "examples", _jm_f_112 };
        _jm_obj_55_map_tab[6] = (jm_propmap_t) { "explode", _jm_f_113 };
        _jm_obj_55_map_tab[7] = (jm_propmap_t) { "required", _jm_f_114 };
        _jm_obj_55_map_tab[8] = (jm_propmap_t) { "schema", _jm_f_115 };
        _jm_obj_55_map_tab[9] = (jm_propmap_t) { "style", _jm_f_116 };
        jm_sort_propmap(_jm_obj_55_map_tab, 10);
        _jm_obj_59_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_117 };
        _jm_obj_59_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_118 };
        _jm_obj_59_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_119 };
        _jm_obj_59_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_120 };
        _jm_obj_59_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_121 };
        _jm_obj_59_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_122 };
        _jm_obj_59_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_123 };
        _jm_obj_59_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_124 };
        _jm_obj_59_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_125 };
        _jm_obj_59_map_tab[9] = (jm_propmap_t) { "additionalProperties", _jm_f_126 };
        _jm_obj_59_map_tab[10] = (jm_propmap_t) { "allOf", _jm_f_127 };
        _jm_obj_59_map_tab[11] = (jm_propmap_t) { "anyOf", _jm_f_128 };
        _jm_obj_59_map_tab[12] = (jm_propmap_t) { "const", _jm_f_129 };
        _jm_obj_59_map_tab[13] = (jm_propmap_t) { "contains", _jm_f_130 };
        _jm_obj_59_map_tab[14] = (jm_propmap_t) { "contentEncoding", _jm_f_131 };
        _jm_obj_59_map_tab[15] = (jm_propmap_t) { "contentMediaType", _jm_f_132 };
        _jm_obj_59_map_tab[16] = (jm_propmap_t) { "contentSchema", _jm_f_133 };
        _jm_obj_59_map_tab[17] = (jm_propmap_t) { "default", _jm_f_134 };
        _jm_obj_59_map_tab[18] = (jm_propmap_t) { "dependentRequired", _jm_f_135 };
        _jm_obj_59_map_tab[19] = (jm_propmap_t) { "dependentSchemas", _jm_f_136 };
        _jm_obj_59_map_tab[20] = (jm_propmap_t) { "deprecated", _jm_f_137 };
        _jm_obj_59_map_tab[21] = (jm_propmap_t) { "description", _jm_f_138 };
        _jm_obj_59_map_tab[22] = (jm_propmap_t) { "discriminator", _jm_f_139 };
        _jm_obj_59_map_tab[23] = (jm_propmap_t) { "else", _jm_f_140 };
        _jm_obj_59_map_tab[24] = (jm_propmap_t) { "enum", _jm_f_141 };
        _jm_obj_59_map_tab[25] = (jm_propmap_t) { "example", _jm_f_142 };
        _jm_obj_59_map_tab[26] = (jm_propmap_t) { "examples", _jm_f_143 };
        _jm_obj_59_map_tab[27] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_144 };
        _jm_obj_59_map_tab[28] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_145 };
        _jm_obj_59_map_tab[29] = (jm_propmap_t) { "externalDocs", _jm_f_146 };
        _jm_obj_59_map_tab[30] = (jm_propmap_t) { "format", _jm_f_147 };
        _jm_obj_59_map_tab[31] = (jm_propmap_t) { "if", _jm_f_148 };
        _jm_obj_59_map_tab[32] = (jm_propmap_t) { "items", _jm_f_149 };
        _jm_obj_59_map_tab[33] = (jm_propmap_t) { "maxContains", _jm_f_150 };
        _jm_obj_59_map_tab[34] = (jm_propmap_t) { "maxItems", _jm_f_151 };
        _jm_obj_59_map_tab[35] = (jm_propmap_t) { "maxLength", _jm_f_152 };
        _jm_obj_59_map_tab[36] = (jm_propmap_t) { "maxProperties", _jm_f_153 };
        _jm_obj_59_map_tab[37] = (jm_propmap_t) { "maximum", _jm_f_154 };
        _jm_obj_59_map_tab[38] = (jm_propmap_t) { "minContains", _jm_f_155 };
        _jm_obj_59_map_tab[39] = (jm_propmap_t) { "minItems", _jm_f_156 };
        _jm_obj_59_map_tab[40] = (jm_propmap_t) { "minLength", _jm_f_157 };
        _jm_obj_59_map_tab[41] = (jm_propmap_t) { "minProperties", _jm_f_158 };
        _jm_obj_59_map_tab[42] = (jm_propmap_t) { "minimum", _jm_f_159 };
        _jm_obj_59_map_tab[43] = (jm_propmap_t) { "multipleOf", _jm_f_160 };
        _jm_obj_59_map_tab[44] = (jm_propmap_t) { "not", _jm_f_161 };
        _jm_obj_59_map_tab[45] = (jm_propmap_t) { "oneOf", _jm_f_162 };
        _jm_obj_59_map_tab[46] = (jm_propmap_t) { "pattern", _jm_f_163 };
        _jm_obj_59_map_tab[47] = (jm_propmap_t) { "patternProperties", _jm_f_164 };
        _jm_obj_59_map_tab[48] = (jm_propmap_t) { "prefixItems", _jm_f_165 };
        _jm_obj_59_map_tab[49] = (jm_propmap_t) { "properties", _jm_f_166 };
        _jm_obj_59_map_tab[50] = (jm_propmap_t) { "propertyNames", _jm_f_167 };
        _jm_obj_59_map_tab[51] = (jm_propmap_t) { "readOnly", _jm_f_168 };
        _jm_obj_59_map_tab[52] = (jm_propmap_t) { "required", _jm_f_169 };
        _jm_obj_59_map_tab[53] = (jm_propmap_t) { "then", _jm_f_170 };
        _jm_obj_59_map_tab[54] = (jm_propmap_t) { "title", _jm_f_171 };
        _jm_obj_59_map_tab[55] = (jm_propmap_t) { "type", _jm_f_172 };
        _jm_obj_59_map_tab[56] = (jm_propmap_t) { "unevaluatedItems", _jm_f_173 };
        _jm_obj_59_map_tab[57] = (jm_propmap_t) { "unevaluatedProperties", _jm_f_174 };
        _jm_obj_59_map_tab[58] = (jm_propmap_t) { "uniqueItems", _jm_f_175 };
        _jm_obj_59_map_tab[59] = (jm_propmap_t) { "writeOnly", _jm_f_176 };
        _jm_obj_59_map_tab[60] = (jm_propmap_t) { "xml", _jm_f_177 };
        jm_sort_propmap(_jm_obj_59_map_tab, 61);
        _jm_obj_68_map_tab[0] = (jm_propmap_t) { "attribute", _jm_f_178 };
        _jm_obj_68_map_tab[1] = (jm_propmap_t) { "name", _jm_f_179 };
        _jm_obj_68_map_tab[2] = (jm_propmap_t) { "namespace", _jm_f_180 };
        _jm_obj_68_map_tab[3] = (jm_propmap_t) { "prefix", _jm_f_181 };
        _jm_obj_68_map_tab[4] = (jm_propmap_t) { "wrapped", _jm_f_182 };
        jm_sort_propmap(_jm_obj_68_map_tab, 5);
        // initialize sorted set _jm_cst_4
        _jm_cst_4[0] = (jm_constant_t) { cst_is_string, { .s = "query" } };
        _jm_cst_4[1] = (jm_constant_t) { cst_is_string, { .s = "header" } };
        _jm_cst_4[2] = (jm_constant_t) { cst_is_string, { .s = "cookie" } };
        jm_sort_cst(_jm_cst_4, 3);
        _jm_obj_69_mup_tab[0] = (jm_propmap_t) { "flows", _jm_f_183 };
        _jm_obj_69_mup_tab[1] = (jm_propmap_t) { "in", _jm_f_184 };
        _jm_obj_69_mup_tab[2] = (jm_propmap_t) { "name", _jm_f_185 };
        _jm_obj_69_mup_tab[3] = (jm_propmap_t) { "openIdConnectUrl", _jm_f_186 };
        _jm_obj_69_mup_tab[4] = (jm_propmap_t) { "scheme", _jm_f_187 };
        _jm_obj_69_mup_tab[5] = (jm_propmap_t) { "type", _jm_f_188 };
        jm_sort_propmap(_jm_obj_69_mup_tab, 6);
        _jm_obj_70_map_tab[0] = (jm_propmap_t) { "authorizationCode", _jm_f_189 };
        _jm_obj_70_map_tab[1] = (jm_propmap_t) { "clientCredentials", _jm_f_190 };
        _jm_obj_70_map_tab[2] = (jm_propmap_t) { "implicit", _jm_f_191 };
        _jm_obj_70_map_tab[3] = (jm_propmap_t) { "password", _jm_f_192 };
        jm_sort_propmap(_jm_obj_70_map_tab, 4);
        // initialize sorted set _jm_cst_5
        _jm_cst_5[0] = (jm_constant_t) { cst_is_string, { .s = "array" } };
        _jm_cst_5[1] = (jm_constant_t) { cst_is_string, { .s = "boolean" } };
        _jm_cst_5[2] = (jm_constant_t) { cst_is_string, { .s = "integer" } };
        _jm_cst_5[3] = (jm_constant_t) { cst_is_string, { .s = "null" } };
        _jm_cst_5[4] = (jm_constant_t) { cst_is_string, { .s = "number" } };
        _jm_cst_5[5] = (jm_constant_t) { cst_is_string, { .s = "object" } };
        _jm_cst_5[6] = (jm_constant_t) { cst_is_string, { .s = "string" } };
        jm_sort_cst(_jm_cst_5, 7);
        _jm_obj_75_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_193 };
        _jm_obj_75_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_194 };
        _jm_obj_75_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_195 };
        _jm_obj_75_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_196 };
        _jm_obj_75_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_197 };
        _jm_obj_75_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_198 };
        _jm_obj_75_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_199 };
        _jm_obj_75_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_200 };
        _jm_obj_75_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_201 };
        _jm_obj_75_map_tab[9] = (jm_propmap_t) { "additionalProperties", _jm_f_202 };
        _jm_obj_75_map_tab[10] = (jm_propmap_t) { "allOf", _jm_f_203 };
        _jm_obj_75_map_tab[11] = (jm_propmap_t) { "anyOf", _jm_f_204 };
        _jm_obj_75_map_tab[12] = (jm_propmap_t) { "const", _jm_f_205 };
        _jm_obj_75_map_tab[13] = (jm_propmap_t) { "contains", _jm_f_206 };
        _jm_obj_75_map_tab[14] = (jm_propmap_t) { "contentEncoding", _jm_f_207 };
        _jm_obj_75_map_tab[15] = (jm_propmap_t) { "contentMediaType", _jm_f_208 };
        _jm_obj_75_map_tab[16] = (jm_propmap_t) { "contentSchema", _jm_f_209 };
        _jm_obj_75_map_tab[17] = (jm_propmap_t) { "default", _jm_f_210 };
        _jm_obj_75_map_tab[18] = (jm_propmap_t) { "dependentRequired", _jm_f_211 };
        _jm_obj_75_map_tab[19] = (jm_propmap_t) { "dependentSchemas", _jm_f_212 };
        _jm_obj_75_map_tab[20] = (jm_propmap_t) { "deprecated", _jm_f_213 };
        _jm_obj_75_map_tab[21] = (jm_propmap_t) { "description", _jm_f_214 };
        _jm_obj_75_map_tab[22] = (jm_propmap_t) { "else", _jm_f_215 };
        _jm_obj_75_map_tab[23] = (jm_propmap_t) { "enum", _jm_f_216 };
        _jm_obj_75_map_tab[24] = (jm_propmap_t) { "examples", _jm_f_217 };
        _jm_obj_75_map_tab[25] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_218 };
        _jm_obj_75_map_tab[26] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_219 };
        _jm_obj_75_map_tab[27] = (jm_propmap_t) { "format", _jm_f_220 };
        _jm_obj_75_map_tab[28] = (jm_propmap_t) { "if", _jm_f_221 };
        _jm_obj_75_map_tab[29] = (jm_propmap_t) { "items", _jm_f_222 };
        _jm_obj_75_map_tab[30] = (jm_propmap_t) { "maxContains", _jm_f_223 };
        _jm_obj_75_map_tab[31] = (jm_propmap_t) { "maxItems", _jm_f_224 };
        _jm_obj_75_map_tab[32] = (jm_propmap_t) { "maxLength", _jm_f_225 };
        _jm_obj_75_map_tab[33] = (jm_propmap_t) { "maxProperties", _jm_f_226 };
        _jm_obj_75_map_tab[34] = (jm_propmap_t) { "maximum", _jm_f_227 };
        _jm_obj_75_map_tab[35] = (jm_propmap_t) { "minContains", _jm_f_228 };
        _jm_obj_75_map_tab[36] = (jm_propmap_t) { "minItems", _jm_f_229 };
        _jm_obj_75_map_tab[37] = (jm_propmap_t) { "minLength", _jm_f_230 };
        _jm_obj_75_map_tab[38] = (jm_propmap_t) { "minProperties", _jm_f_231 };
        _jm_obj_75_map_tab[39] = (jm_propmap_t) { "minimum", _jm_f_232 };
        _jm_obj_75_map_tab[40] = (jm_propmap_t) { "multipleOf", _jm_f_233 };
        _jm_obj_75_map_tab[41] = (jm_propmap_t) { "not", _jm_f_234 };
        _jm_obj_75_map_tab[42] = (jm_propmap_t) { "oneOf", _jm_f_235 };
        _jm_obj_75_map_tab[43] = (jm_propmap_t) { "pattern", _jm_f_236 };
        _jm_obj_75_map_tab[44] = (jm_propmap_t) { "patternProperties", _jm_f_237 };
        _jm_obj_75_map_tab[45] = (jm_propmap_t) { "prefixItems", _jm_f_238 };
        _jm_obj_75_map_tab[46] = (jm_propmap_t) { "properties", _jm_f_239 };
        _jm_obj_75_map_tab[47] = (jm_propmap_t) { "propertyNames", _jm_f_240 };
        _jm_obj_75_map_tab[48] = (jm_propmap_t) { "readOnly", _jm_f_241 };
        _jm_obj_75_map_tab[49] = (jm_propmap_t) { "required", _jm_f_242 };
        _jm_obj_75_map_tab[50] = (jm_propmap_t) { "then", _jm_f_243 };
        _jm_obj_75_map_tab[51] = (jm_propmap_t) { "title", _jm_f_244 };
        _jm_obj_75_map_tab[52] = (jm_propmap_t) { "type", _jm_f_245 };
        _jm_obj_75_map_tab[53] = (jm_propmap_t) { "unevaluatedItems", _jm_f_246 };
        _jm_obj_75_map_tab[54] = (jm_propmap_t) { "unevaluatedProperties", _jm_f_247 };
        _jm_obj_75_map_tab[55] = (jm_propmap_t) { "uniqueItems", _jm_f_248 };
        _jm_obj_75_map_tab[56] = (jm_propmap_t) { "writeOnly", _jm_f_249 };
        jm_sort_propmap(_jm_obj_75_map_tab, 57);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "OpenAPI", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "Info", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "Contact", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "License", json_model_5 };
        check_model_map_tab[5] = (jm_propmap_t) { "Server", json_model_6 };
        check_model_map_tab[6] = (jm_propmap_t) { "ServerVariable", json_model_7 };
        check_model_map_tab[7] = (jm_propmap_t) { "Components", json_model_8 };
        check_model_map_tab[8] = (jm_propmap_t) { "Paths", json_model_9 };
        check_model_map_tab[9] = (jm_propmap_t) { "PathItem", json_model_10 };
        check_model_map_tab[10] = (jm_propmap_t) { "Operation", json_model_11 };
        check_model_map_tab[11] = (jm_propmap_t) { "ExternalDocumentation", json_model_12 };
        check_model_map_tab[12] = (jm_propmap_t) { "parameterShare", json_model_13 };
        check_model_map_tab[13] = (jm_propmap_t) { "commonParameter", json_model_14 };
        check_model_map_tab[14] = (jm_propmap_t) { "Style", json_model_15 };
        check_model_map_tab[15] = (jm_propmap_t) { "parameterSchemaOnly", json_model_16 };
        check_model_map_tab[16] = (jm_propmap_t) { "parameterContentOnly", json_model_17 };
        check_model_map_tab[17] = (jm_propmap_t) { "Parameter", json_model_18 };
        check_model_map_tab[18] = (jm_propmap_t) { "RequestBody", json_model_19 };
        check_model_map_tab[19] = (jm_propmap_t) { "MediaType", json_model_20 };
        check_model_map_tab[20] = (jm_propmap_t) { "Encoding", json_model_21 };
        check_model_map_tab[21] = (jm_propmap_t) { "Responses", json_model_22 };
        check_model_map_tab[22] = (jm_propmap_t) { "Response", json_model_23 };
        check_model_map_tab[23] = (jm_propmap_t) { "Callback", json_model_24 };
        check_model_map_tab[24] = (jm_propmap_t) { "Example", json_model_25 };
        check_model_map_tab[25] = (jm_propmap_t) { "Expression", json_model_26 };
        check_model_map_tab[26] = (jm_propmap_t) { "Link", json_model_27 };
        check_model_map_tab[27] = (jm_propmap_t) { "Header", json_model_28 };
        check_model_map_tab[28] = (jm_propmap_t) { "Tag", json_model_29 };
        check_model_map_tab[29] = (jm_propmap_t) { "Reference", json_model_30 };
        check_model_map_tab[30] = (jm_propmap_t) { "schema", json_model_40 };
        check_model_map_tab[31] = (jm_propmap_t) { "Schema", json_model_32 };
        check_model_map_tab[32] = (jm_propmap_t) { "Discriminator", json_model_33 };
        check_model_map_tab[33] = (jm_propmap_t) { "XML", json_model_34 };
        check_model_map_tab[34] = (jm_propmap_t) { "SecurityScheme", json_model_35 };
        check_model_map_tab[35] = (jm_propmap_t) { "OAuthFlows", json_model_36 };
        check_model_map_tab[36] = (jm_propmap_t) { "OAuthFlow", json_model_37 };
        check_model_map_tab[37] = (jm_propmap_t) { "SecurityRequirement", json_model_38 };
        check_model_map_tab[38] = (jm_propmap_t) { "Extension", json_model_39 };
        jm_sort_propmap(check_model_map_tab, 39);
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
