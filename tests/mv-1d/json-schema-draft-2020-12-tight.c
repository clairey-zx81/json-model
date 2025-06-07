#include <json-model.h>
#define JSON_MODEL_VERSION "2.0a0"

static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_0_map_tab[9];
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_3_map_tab[7];
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_6_map_tab[5];
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_7_map_tab[5];
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_8_map_tab[7];
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_38(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_39(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_40(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_41(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_9_map_tab[9];
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep);
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
static jm_propmap_t _jm_obj_10_map_tab[10];
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_15_map_tab[9];
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep);
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
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_16_map_tab[25];
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep);
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
static jm_propmap_t _jm_obj_19_map_tab[26];
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
static jm_propmap_t _jm_obj_26_map_tab[25];
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
static jm_propmap_t _jm_obj_29_map_tab[23];
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
static bool _jm_f_178(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_179(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_180(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_32_map_tab[21];
static bool _jm_f_181(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_182(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_183(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_184(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_185(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_186(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_187(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_188(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_189(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_190(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_191(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_192(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_193(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_194(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_195(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_196(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_197(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_198(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_199(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_200(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool _jm_f_201(const json_t *val, jm_path_t *path, jm_report_t *rep);
static jm_propmap_t _jm_obj_35_map_tab[21];
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
static jm_propmap_t _jm_obj_38_map_tab[16];
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
static jm_propmap_t _jm_obj_41_map_tab[16];
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep);
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep);
jm_propmap_t check_model_map_tab[16];
const size_t check_model_map_size = 16;

// check $URI-REFERENCE (.'$URI-REFERENCE')
static bool json_model_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$URI-REFERENCE'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$URI-REFERENCE']", path);
    }
    return res;
}

// check _jm_obj_0_map_$anchor (.'$core'.'$anchor')
static bool _jm_f_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$core'.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_0_map_$comment (.'$core'.'$comment')
static bool _jm_f_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$core'.'$comment']", path);
    }
    return res;
}

// object .'$core'.'$defs'
static bool _jm_obj_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$core'.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_1 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$core'.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_1 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$core'.'$defs'.'']", (path ? &lpath_1 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_$defs (.'$core'.'$defs')
static bool _jm_f_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$defs'
    res = _jm_obj_1(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$core'.'$defs']", path);
    }
    return res;
}

// check _jm_obj_0_map_$dynamicAnchor (.'$core'.'$dynamicAnchor')
static bool _jm_f_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$core'.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_0_map_$dynamicRef (.'$core'.'$dynamicRef')
static bool _jm_f_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$core'.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_0_map_$id (.'$core'.'$id')
static bool _jm_f_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$core'.'$id']", path);
    }
    return res;
}

// check _jm_obj_0_map_$ref (.'$core'.'$ref')
static bool _jm_f_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$core'.'$ref']", path);
    }
    return res;
}

// check _jm_obj_0_map_$schema (.'$core'.'$schema')
static bool _jm_f_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$core'.'$schema']", path);
    }
    return res;
}

// object .'$core'.'$vocabulary'
static bool _jm_obj_2(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$core'.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_2 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$core'.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$core'.'$vocabulary'.'$URI']", (path ? &lpath_2 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$core'.'$vocabulary']", (path ? &lpath_2 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_0_map_$vocabulary (.'$core'.'$vocabulary')
static bool _jm_f_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'.'$vocabulary'
    res = _jm_obj_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$core'.'$vocabulary']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_0_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_0_map_tab, 9);
}

// object .'$core'
static bool _jm_obj_0(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$core']", path);
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
            // handle 9 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_0 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$core']", (path ? &lpath_0 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$core']", (path ? &lpath_0 : NULL));
            return false;
        }
    }
    return true;
}

// check $core (.'$core')
static bool json_model_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$core'
    res = _jm_obj_0(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$core']", path);
    }
    return res;
}

// check _jm_obj_3_map_default (.'$meta'.default)
static bool _jm_f_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$meta'.default]", path);
    }
    return res;
}

// check _jm_obj_3_map_deprecated (.'$meta'.deprecated)
static bool _jm_f_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$meta'.deprecated]", path);
    }
    return res;
}

// check _jm_obj_3_map_description (.'$meta'.description)
static bool _jm_f_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$meta'.description]", path);
    }
    return res;
}

// check _jm_obj_3_map_examples (.'$meta'.examples)
static bool _jm_f_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$meta'.examples]", path);
    }
    return res;
}

// check _jm_obj_3_map_readOnly (.'$meta'.readOnly)
static bool _jm_f_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$meta'.readOnly]", path);
    }
    return res;
}

// check _jm_obj_3_map_title (.'$meta'.title)
static bool _jm_f_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$meta'.title]", path);
    }
    return res;
}

// check _jm_obj_3_map_writeOnly (.'$meta'.writeOnly)
static bool _jm_f_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$meta'.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_3_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_3_map_tab, 7);
}

// object .'$meta'
static bool _jm_obj_3(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$meta']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_3 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_3_map(prop)))
        {
            // handle 7 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_3 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$meta']", (path ? &lpath_3 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$meta']", (path ? &lpath_3 : NULL));
            return false;
        }
    }
    return true;
}

// check $meta (.'$meta')
static bool json_model_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$meta'
    res = _jm_obj_3(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$meta']", path);
    }
    return res;
}

// object .'$Null'
static bool _jm_obj_4(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Null']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_4 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Null'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "null") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _null [.'$Null'.type]", (path ? &lpath_4 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Null'.type]", (path ? &lpath_4 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Null']", (path ? &lpath_4 : NULL));
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
static bool json_model_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Null'
    res = _jm_obj_4(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Null']", path);
    }
    return res;
}

// object .'$Boolean'
static bool _jm_obj_5(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Boolean']", path);
        return false;
    }
    bool res;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_5 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Boolean'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "boolean") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _boolean [.'$Boolean'.type]", (path ? &lpath_5 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Boolean'.type]", (path ? &lpath_5 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Boolean']", (path ? &lpath_5 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$Boolean']", path);
            }
        }
        return false;
    }
    return true;
}

// check $Boolean (.'$Boolean')
static bool json_model_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Boolean'
    res = _jm_obj_5(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Boolean']", path);
    }
    return res;
}

// check _jm_obj_6_map_exclusiveMaximum (.'$Number'.exclusiveMaximum)
static bool _jm_f_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.exclusiveMaximum
    // .'$Number'.exclusiveMaximum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Number'.exclusiveMaximum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Number'.exclusiveMaximum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.exclusiveMaximum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Number'.exclusiveMaximum.'|']", path);
    }
    return res;
}

// check _jm_obj_6_map_exclusiveMinimum (.'$Number'.exclusiveMinimum)
static bool _jm_f_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.exclusiveMinimum
    // .'$Number'.exclusiveMinimum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Number'.exclusiveMinimum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Number'.exclusiveMinimum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.exclusiveMinimum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Number'.exclusiveMinimum.'|']", path);
    }
    return res;
}

// check _jm_obj_6_map_maximum (.'$Number'.maximum)
static bool _jm_f_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.maximum
    // .'$Number'.maximum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Number'.maximum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Number'.maximum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.maximum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Number'.maximum.'|']", path);
    }
    return res;
}

// check _jm_obj_6_map_minimum (.'$Number'.minimum)
static bool _jm_f_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.minimum
    // .'$Number'.minimum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Number'.minimum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Number'.minimum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$Number'.minimum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Number'.minimum.'|']", path);
    }
    return res;
}

// check _jm_obj_6_map_multipleOf (.'$Number'.multipleOf)
static bool _jm_f_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'.multipleOf
    // .'$Number'.multipleOf.'|'.0
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 strict int [.'$Number'.multipleOf.'|'.0]", path);
    }
    if (! res)
    {
        // .'$Number'.multipleOf.'|'.1
        res = json_is_real(val) && json_real_value(val) > 0.0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 1.0 strict float [.'$Number'.multipleOf.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$Number'.multipleOf.'|']", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_6_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_6_map_tab, 5);
}

// object .'$Number'
static bool _jm_obj_6(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_6 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Number'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _number [.'$Number'.type]", (path ? &lpath_6 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Number'.type]", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_6_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_6 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Number']", (path ? &lpath_6 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Number']", (path ? &lpath_6 : NULL));
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
static bool json_model_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Number'
    res = _jm_obj_6(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Number']", path);
    }
    return res;
}

// check _jm_obj_7_map_exclusiveMaximum (.'$Integer'.exclusiveMaximum)
static bool _jm_f_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.exclusiveMaximum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Integer'.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_7_map_exclusiveMinimum (.'$Integer'.exclusiveMinimum)
static bool _jm_f_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.exclusiveMinimum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Integer'.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_7_map_maximum (.'$Integer'.maximum)
static bool _jm_f_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.maximum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Integer'.maximum]", path);
    }
    return res;
}

// check _jm_obj_7_map_minimum (.'$Integer'.minimum)
static bool _jm_f_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.minimum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$Integer'.minimum]", path);
    }
    return res;
}

// check _jm_obj_7_map_multipleOf (.'$Integer'.multipleOf)
static bool _jm_f_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'.multipleOf
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 strict int [.'$Integer'.multipleOf]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_7_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_7_map_tab, 5);
}

// object .'$Integer'
static bool _jm_obj_7(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_7 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Integer'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _integer [.'$Integer'.type]", (path ? &lpath_7 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Integer'.type]", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_7_map(prop)))
        {
            // handle 5 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_7 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Integer']", (path ? &lpath_7 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Integer']", (path ? &lpath_7 : NULL));
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
static bool json_model_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Integer'
    res = _jm_obj_7(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Integer']", path);
    }
    return res;
}

// check _jm_obj_8_map_contentEncoding (.'$String'.contentEncoding)
static bool _jm_f_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_8_map_contentMediaType (.'$String'.contentMediaType)
static bool _jm_f_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.contentMediaType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.contentMediaType]", path);
    }
    return res;
}

// check _jm_obj_8_map_contentSchema (.'$String'.contentSchema)
static bool _jm_f_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.contentSchema
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$String'.contentSchema]", path);
    }
    return res;
}

// check _jm_obj_8_map_format (.'$String'.format)
static bool _jm_f_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$String'.format]", path);
    }
    return res;
}

// check _jm_obj_8_map_maxLength (.'$String'.maxLength)
static bool _jm_f_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
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

// check _jm_obj_8_map_minLength (.'$String'.minLength)
static bool _jm_f_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
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

// check _jm_obj_8_map_pattern (.'$String'.pattern)
static bool _jm_f_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'.pattern
    res = jm_is_valid_regex(json_string_value(val), false);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$String'.pattern]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_8_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_8_map_tab, 7);
}

// object .'$String'
static bool _jm_obj_8(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_8 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$String'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _string [.'$String'.type]", (path ? &lpath_8 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$String'.type]", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_8_map(prop)))
        {
            // handle 7 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_8 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$String']", (path ? &lpath_8 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$String']", (path ? &lpath_8 : NULL));
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
static bool json_model_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$String'
    res = _jm_obj_8(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$String']", path);
    }
    return res;
}

// check $stringArray (.'$stringArray')
static bool json_model_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$stringArray'
    // .'$stringArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_0_idx;
        json_t *arr_0_item;
        json_array_foreach(val, arr_0_idx, arr_0_item)
        {
            jm_path_t arr_0_lpath = (jm_path_t) { NULL, arr_0_idx, path, NULL };
            // .'$stringArray'.'@'.0
            res = json_is_string(arr_0_item);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected string [.'$stringArray'.'@'.0]", (path ? &arr_0_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$stringArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_0 = json_array_size(val);
        res = ival_0 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$stringArray']", path);
    }
    return res;
}

// check $schemaArray (.'$schemaArray')
static bool json_model_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$schemaArray'
    // .'$schemaArray'.'@'
    res = json_is_array(val);
    if (res)
    {
        size_t arr_1_idx;
        json_t *arr_1_item;
        json_array_foreach(val, arr_1_idx, arr_1_item)
        {
            jm_path_t arr_1_lpath = (jm_path_t) { NULL, arr_1_idx, path, NULL };
            // .'$schemaArray'.'@'.0
            res = json_model_16(arr_1_item, (path ? &arr_1_lpath : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$schemaArray'.'@'.0]", (path ? &arr_1_lpath : NULL));
            }
            if (! res)
            {
                break;
            }
        }
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$schemaArray'.'@']", path);
    }
    if (res)
    {
        int64_t ival_1 = json_array_size(val);
        res = ival_1 >= 1;
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "constraints failed [.'$schemaArray']", path);
    }
    return res;
}

// check _jm_obj_9_map_contains (.'$Array'.contains)
static bool _jm_f_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.contains
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.contains]", path);
    }
    return res;
}

// check _jm_obj_9_map_items (.'$Array'.items)
static bool _jm_f_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.items
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.items]", path);
    }
    return res;
}

// check _jm_obj_9_map_maxContains (.'$Array'.maxContains)
static bool _jm_f_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.maxContains
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.maxContains]", path);
    }
    return res;
}

// check _jm_obj_9_map_maxItems (.'$Array'.maxItems)
static bool _jm_f_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
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

// check _jm_obj_9_map_minContains (.'$Array'.minContains)
static bool _jm_f_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.minContains
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Array'.minContains]", path);
    }
    return res;
}

// check _jm_obj_9_map_minItems (.'$Array'.minItems)
static bool _jm_f_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
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

// check _jm_obj_9_map_prefixItems (.'$Array'.prefixItems)
static bool _jm_f_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.prefixItems
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Array'.prefixItems]", path);
    }
    return res;
}

// check _jm_obj_9_map_unevaluatedItems (.'$Array'.unevaluatedItems)
static bool _jm_f_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'.unevaluatedItems
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Array'.unevaluatedItems]", path);
    }
    return res;
}

// check _jm_obj_9_map_uniqueItems (.'$Array'.uniqueItems)
static bool _jm_f_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
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

static jm_check_fun_t _jm_obj_9_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_9_map_tab, 9);
}

// object .'$Array'
static bool _jm_obj_9(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_9 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Array'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "array") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _array [.'$Array'.type]", (path ? &lpath_9 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Array'.type]", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_9_map(prop)))
        {
            // handle 9 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_9 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Array']", (path ? &lpath_9 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Array']", (path ? &lpath_9 : NULL));
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
static bool json_model_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Array'
    res = _jm_obj_9(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Array']", path);
    }
    return res;
}

// check _jm_obj_10_map_additionalProperties (.'$Object'.additionalProperties)
static bool _jm_f_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.additionalProperties
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.additionalProperties]", path);
    }
    return res;
}

// object .'$Object'.dependentRequired
static bool _jm_obj_11(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.dependentRequired]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_11 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.dependentRequired.''
        res = json_model_10(pval, (path ? &lpath_11 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$Object'.dependentRequired.'']", (path ? &lpath_11 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_dependentRequired (.'$Object'.dependentRequired)
static bool _jm_f_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.dependentRequired
    res = _jm_obj_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.dependentRequired]", path);
    }
    return res;
}

// object .'$Object'.dependentSchemas
static bool _jm_obj_12(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Object'.dependentSchemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_12 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.dependentSchemas.''
        res = json_model_16(pval, (path ? &lpath_12 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.dependentSchemas.'']", (path ? &lpath_12 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_dependentSchemas (.'$Object'.dependentSchemas)
static bool _jm_f_44(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.dependentSchemas
    res = _jm_obj_12(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.dependentSchemas]", path);
    }
    return res;
}

// check _jm_obj_10_map_maxProperties (.'$Object'.maxProperties)
static bool _jm_f_45(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.maxProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Object'.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_10_map_minProperties (.'$Object'.minProperties)
static bool _jm_f_46(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.minProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$Object'.minProperties]", path);
    }
    return res;
}

// object .'$Object'.patternProperties
static bool _jm_obj_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_13 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop, false))
        {
            // handle 1 key props
            // .'$Object'.patternProperties.'$REGEX'
            res = json_model_16(pval, (path ? &lpath_13 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.patternProperties.'$REGEX']", (path ? &lpath_13 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Object'.patternProperties]", (path ? &lpath_13 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_patternProperties (.'$Object'.patternProperties)
static bool _jm_f_47(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.patternProperties
    res = _jm_obj_13(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.patternProperties]", path);
    }
    return res;
}

// object .'$Object'.properties
static bool _jm_obj_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_14 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$Object'.properties.''
        res = json_model_16(pval, (path ? &lpath_14 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.properties.'']", (path ? &lpath_14 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_10_map_properties (.'$Object'.properties)
static bool _jm_f_48(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.properties
    res = _jm_obj_14(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object'.properties]", path);
    }
    return res;
}

// check _jm_obj_10_map_propertyNames (.'$Object'.propertyNames)
static bool _jm_f_49(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.propertyNames
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_10_map_required (.'$Object'.required)
static bool _jm_f_50(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.required
    res = json_model_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$Object'.required]", path);
    }
    return res;
}

// check _jm_obj_10_map_unevaluatedProperties (.'$Object'.unevaluatedProperties)
static bool _jm_f_51(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'.unevaluatedProperties
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Object'.unevaluatedProperties]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_10_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_10_map_tab, 10);
}

// object .'$Object'
static bool _jm_obj_10(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        jm_path_t lpath_10 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$Object'.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "object") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _object [.'$Object'.type]", (path ? &lpath_10 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$Object'.type]", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_10_map(prop)))
        {
            // handle 10 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_10 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Object']", (path ? &lpath_10 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Object']", (path ? &lpath_10 : NULL));
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
static bool json_model_13(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Object'
    res = _jm_obj_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Object']", path);
    }
    return res;
}

// check _jm_obj_15_map_allOf (.'$Misc'.allOf)
static bool _jm_f_52(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.allOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Misc'.allOf]", path);
    }
    return res;
}

// check _jm_obj_15_map_anyOf (.'$Misc'.anyOf)
static bool _jm_f_53(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.anyOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Misc'.anyOf]", path);
    }
    return res;
}

// check _jm_obj_15_map_const (.'$Misc'.const)
static bool _jm_f_54(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.const
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$Misc'.const]", path);
    }
    return res;
}

// check _jm_obj_15_map_else (.'$Misc'.else)
static bool _jm_f_55(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.else
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Misc'.else]", path);
    }
    return res;
}

// check _jm_obj_15_map_enum (.'$Misc'.enum)
static bool _jm_f_56(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.enum
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$Misc'.enum]", path);
    }
    return res;
}

// check _jm_obj_15_map_if (.'$Misc'.if)
static bool _jm_f_57(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.if
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Misc'.if]", path);
    }
    return res;
}

// check _jm_obj_15_map_not (.'$Misc'.not)
static bool _jm_f_58(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.not
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Misc'.not]", path);
    }
    return res;
}

// check _jm_obj_15_map_oneOf (.'$Misc'.oneOf)
static bool _jm_f_59(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.oneOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$Misc'.oneOf]", path);
    }
    return res;
}

// check _jm_obj_15_map_then (.'$Misc'.then)
static bool _jm_f_60(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'.then
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$Misc'.then]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_15_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_15_map_tab, 9);
}

// object .'$Misc'
static bool _jm_obj_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$Misc']", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_15 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_15_map(prop)))
        {
            // handle 9 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_15 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$Misc']", (path ? &lpath_15 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$Misc']", (path ? &lpath_15 : NULL));
            return false;
        }
    }
    return true;
}

// check $Misc (.'$Misc')
static bool json_model_14(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$Misc'
    res = _jm_obj_15(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$Misc']", path);
    }
    return res;
}

// check _jm_obj_16_map_$anchor (.'$TightSchema'.'|'.7.'$anchor')
static bool _jm_f_61(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.7.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_16_map_$comment (.'$TightSchema'.'|'.7.'$comment')
static bool _jm_f_62(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.7.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.7.'$defs'
static bool _jm_obj_17(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.7.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_17 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.7.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_17 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.7.'$defs'.'']", (path ? &lpath_17 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_16_map_$defs (.'$TightSchema'.'|'.7.'$defs')
static bool _jm_f_63(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$defs'
    res = _jm_obj_17(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.7.'$defs']", path);
    }
    return res;
}

// check _jm_obj_16_map_$dynamicAnchor (.'$TightSchema'.'|'.7.'$dynamicAnchor')
static bool _jm_f_64(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.7.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_16_map_$dynamicRef (.'$TightSchema'.'|'.7.'$dynamicRef')
static bool _jm_f_65(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.7.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_16_map_$id (.'$TightSchema'.'|'.7.'$id')
static bool _jm_f_66(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.7.'$id']", path);
    }
    return res;
}

// check _jm_obj_16_map_$ref (.'$TightSchema'.'|'.7.'$ref')
static bool _jm_f_67(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.7.'$ref']", path);
    }
    return res;
}

// check _jm_obj_16_map_$schema (.'$TightSchema'.'|'.7.'$schema')
static bool _jm_f_68(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.7.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.7.'$vocabulary'
static bool _jm_obj_18(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.7.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_18 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.7.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.7.'$vocabulary'.'$URI']", (path ? &lpath_18 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.7.'$vocabulary']", (path ? &lpath_18 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_16_map_$vocabulary (.'$TightSchema'.'|'.7.'$vocabulary')
static bool _jm_f_69(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.'$vocabulary'
    res = _jm_obj_18(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.7.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_16_map_allOf (.'$TightSchema'.'|'.7.allOf)
static bool _jm_f_70(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.allOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$TightSchema'.'|'.7.allOf]", path);
    }
    return res;
}

// check _jm_obj_16_map_anyOf (.'$TightSchema'.'|'.7.anyOf)
static bool _jm_f_71(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.anyOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$TightSchema'.'|'.7.anyOf]", path);
    }
    return res;
}

// check _jm_obj_16_map_const (.'$TightSchema'.'|'.7.const)
static bool _jm_f_72(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.const
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.7.const]", path);
    }
    return res;
}

// check _jm_obj_16_map_default (.'$TightSchema'.'|'.7.default)
static bool _jm_f_73(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.7.default]", path);
    }
    return res;
}

// check _jm_obj_16_map_deprecated (.'$TightSchema'.'|'.7.deprecated)
static bool _jm_f_74(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.7.deprecated]", path);
    }
    return res;
}

// check _jm_obj_16_map_description (.'$TightSchema'.'|'.7.description)
static bool _jm_f_75(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.7.description]", path);
    }
    return res;
}

// check _jm_obj_16_map_else (.'$TightSchema'.'|'.7.else)
static bool _jm_f_76(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.else
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.7.else]", path);
    }
    return res;
}

// check _jm_obj_16_map_enum (.'$TightSchema'.'|'.7.enum)
static bool _jm_f_77(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.enum
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.7.enum]", path);
    }
    return res;
}

// check _jm_obj_16_map_examples (.'$TightSchema'.'|'.7.examples)
static bool _jm_f_78(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.7.examples]", path);
    }
    return res;
}

// check _jm_obj_16_map_if (.'$TightSchema'.'|'.7.if)
static bool _jm_f_79(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.if
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.7.if]", path);
    }
    return res;
}

// check _jm_obj_16_map_not (.'$TightSchema'.'|'.7.not)
static bool _jm_f_80(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.not
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.7.not]", path);
    }
    return res;
}

// check _jm_obj_16_map_oneOf (.'$TightSchema'.'|'.7.oneOf)
static bool _jm_f_81(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.oneOf
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$TightSchema'.'|'.7.oneOf]", path);
    }
    return res;
}

// check _jm_obj_16_map_readOnly (.'$TightSchema'.'|'.7.readOnly)
static bool _jm_f_82(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.7.readOnly]", path);
    }
    return res;
}

// check _jm_obj_16_map_then (.'$TightSchema'.'|'.7.then)
static bool _jm_f_83(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.then
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.7.then]", path);
    }
    return res;
}

// check _jm_obj_16_map_title (.'$TightSchema'.'|'.7.title)
static bool _jm_f_84(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.7.title]", path);
    }
    return res;
}

// check _jm_obj_16_map_writeOnly (.'$TightSchema'.'|'.7.writeOnly)
static bool _jm_f_85(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.7.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.7.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_16_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_16_map_tab, 25);
}

// object .'$TightSchema'.'|'.7
static bool _jm_obj_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.7]", path);
        return false;
    }
    jm_check_fun_t pfun;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_16 = (jm_path_t) { prop, 0, path, NULL };
        if ((pfun = _jm_obj_16_map(prop)))
        {
            // handle 25 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_16 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.7]", (path ? &lpath_16 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.7]", (path ? &lpath_16 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_$anchor (.'$TightSchema'.'|'.6.'$anchor')
static bool _jm_f_86(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.6.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_19_map_$comment (.'$TightSchema'.'|'.6.'$comment')
static bool _jm_f_87(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.6.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.'$defs'
static bool _jm_obj_20(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_20 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.6.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_20 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.'$defs'.'']", (path ? &lpath_20 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_$defs (.'$TightSchema'.'|'.6.'$defs')
static bool _jm_f_88(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$defs'
    res = _jm_obj_20(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.'$defs']", path);
    }
    return res;
}

// check _jm_obj_19_map_$dynamicAnchor (.'$TightSchema'.'|'.6.'$dynamicAnchor')
static bool _jm_f_89(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.6.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_19_map_$dynamicRef (.'$TightSchema'.'|'.6.'$dynamicRef')
static bool _jm_f_90(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.6.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_19_map_$id (.'$TightSchema'.'|'.6.'$id')
static bool _jm_f_91(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.6.'$id']", path);
    }
    return res;
}

// check _jm_obj_19_map_$ref (.'$TightSchema'.'|'.6.'$ref')
static bool _jm_f_92(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.6.'$ref']", path);
    }
    return res;
}

// check _jm_obj_19_map_$schema (.'$TightSchema'.'|'.6.'$schema')
static bool _jm_f_93(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.6.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.'$vocabulary'
static bool _jm_obj_21(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_21 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.6.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.6.'$vocabulary'.'$URI']", (path ? &lpath_21 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.6.'$vocabulary']", (path ? &lpath_21 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_$vocabulary (.'$TightSchema'.'|'.6.'$vocabulary')
static bool _jm_f_94(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.'$vocabulary'
    res = _jm_obj_21(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_19_map_additionalProperties (.'$TightSchema'.'|'.6.additionalProperties)
static bool _jm_f_95(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.additionalProperties
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.additionalProperties]", path);
    }
    return res;
}

// check _jm_obj_19_map_default (.'$TightSchema'.'|'.6.default)
static bool _jm_f_96(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.6.default]", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.dependentRequired
static bool _jm_obj_22(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.dependentRequired]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_22 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.6.dependentRequired.''
        res = json_model_10(pval, (path ? &lpath_22 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$TightSchema'.'|'.6.dependentRequired.'']", (path ? &lpath_22 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_dependentRequired (.'$TightSchema'.'|'.6.dependentRequired)
static bool _jm_f_97(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.dependentRequired
    res = _jm_obj_22(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.dependentRequired]", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.dependentSchemas
static bool _jm_obj_23(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.dependentSchemas]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_23 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.6.dependentSchemas.''
        res = json_model_16(pval, (path ? &lpath_23 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.dependentSchemas.'']", (path ? &lpath_23 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_dependentSchemas (.'$TightSchema'.'|'.6.dependentSchemas)
static bool _jm_f_98(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.dependentSchemas
    res = _jm_obj_23(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.dependentSchemas]", path);
    }
    return res;
}

// check _jm_obj_19_map_deprecated (.'$TightSchema'.'|'.6.deprecated)
static bool _jm_f_99(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.6.deprecated]", path);
    }
    return res;
}

// check _jm_obj_19_map_description (.'$TightSchema'.'|'.6.description)
static bool _jm_f_100(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.6.description]", path);
    }
    return res;
}

// check _jm_obj_19_map_examples (.'$TightSchema'.'|'.6.examples)
static bool _jm_f_101(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.6.examples]", path);
    }
    return res;
}

// check _jm_obj_19_map_maxProperties (.'$TightSchema'.'|'.6.maxProperties)
static bool _jm_f_102(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.maxProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.6.maxProperties]", path);
    }
    return res;
}

// check _jm_obj_19_map_minProperties (.'$TightSchema'.'|'.6.minProperties)
static bool _jm_f_103(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.minProperties
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.6.minProperties]", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.patternProperties
static bool _jm_obj_24(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.patternProperties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_24 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_regex(prop, false))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.6.patternProperties.'$REGEX'
            res = json_model_16(pval, (path ? &lpath_24 : NULL), rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.patternProperties.'$REGEX']", (path ? &lpath_24 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.6.patternProperties]", (path ? &lpath_24 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_patternProperties (.'$TightSchema'.'|'.6.patternProperties)
static bool _jm_f_104(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.patternProperties
    res = _jm_obj_24(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.patternProperties]", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.6.properties
static bool _jm_obj_25(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6.properties]", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_25 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.6.properties.''
        res = json_model_16(pval, (path ? &lpath_25 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.properties.'']", (path ? &lpath_25 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_19_map_properties (.'$TightSchema'.'|'.6.properties)
static bool _jm_f_105(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.properties
    res = _jm_obj_25(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6.properties]", path);
    }
    return res;
}

// check _jm_obj_19_map_propertyNames (.'$TightSchema'.'|'.6.propertyNames)
static bool _jm_f_106(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.propertyNames
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.propertyNames]", path);
    }
    return res;
}

// check _jm_obj_19_map_readOnly (.'$TightSchema'.'|'.6.readOnly)
static bool _jm_f_107(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.6.readOnly]", path);
    }
    return res;
}

// check _jm_obj_19_map_required (.'$TightSchema'.'|'.6.required)
static bool _jm_f_108(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.required
    res = json_model_10(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $stringArray [.'$TightSchema'.'|'.6.required]", path);
    }
    return res;
}

// check _jm_obj_19_map_title (.'$TightSchema'.'|'.6.title)
static bool _jm_f_109(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.6.title]", path);
    }
    return res;
}

// check _jm_obj_19_map_unevaluatedProperties (.'$TightSchema'.'|'.6.unevaluatedProperties)
static bool _jm_f_110(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.unevaluatedProperties
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.6.unevaluatedProperties]", path);
    }
    return res;
}

// check _jm_obj_19_map_writeOnly (.'$TightSchema'.'|'.6.writeOnly)
static bool _jm_f_111(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.6.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.6.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_19_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_19_map_tab, 26);
}

// object .'$TightSchema'.'|'.6
static bool _jm_obj_19(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.6]", path);
        return false;
    }
    bool res;
    jm_check_fun_t pfun;
    int64_t must_count = 0;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_19 = (jm_path_t) { prop, 0, path, NULL };
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$TightSchema'.'|'.6.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "object") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _object [.'$TightSchema'.'|'.6.type]", (path ? &lpath_19 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.6.type]", (path ? &lpath_19 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_19_map(prop)))
        {
            // handle 26 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_19 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.6]", (path ? &lpath_19 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.6]", (path ? &lpath_19 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.6]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_26_map_$anchor (.'$TightSchema'.'|'.5.'$anchor')
static bool _jm_f_112(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.5.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_26_map_$comment (.'$TightSchema'.'|'.5.'$comment')
static bool _jm_f_113(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.5.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.5.'$defs'
static bool _jm_obj_27(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.5.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_27 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.5.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_27 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.5.'$defs'.'']", (path ? &lpath_27 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_$defs (.'$TightSchema'.'|'.5.'$defs')
static bool _jm_f_114(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$defs'
    res = _jm_obj_27(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.5.'$defs']", path);
    }
    return res;
}

// check _jm_obj_26_map_$dynamicAnchor (.'$TightSchema'.'|'.5.'$dynamicAnchor')
static bool _jm_f_115(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.5.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_26_map_$dynamicRef (.'$TightSchema'.'|'.5.'$dynamicRef')
static bool _jm_f_116(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.5.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_26_map_$id (.'$TightSchema'.'|'.5.'$id')
static bool _jm_f_117(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.5.'$id']", path);
    }
    return res;
}

// check _jm_obj_26_map_$ref (.'$TightSchema'.'|'.5.'$ref')
static bool _jm_f_118(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.5.'$ref']", path);
    }
    return res;
}

// check _jm_obj_26_map_$schema (.'$TightSchema'.'|'.5.'$schema')
static bool _jm_f_119(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.5.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.5.'$vocabulary'
static bool _jm_obj_28(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.5.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_28 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.5.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.5.'$vocabulary'.'$URI']", (path ? &lpath_28 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.5.'$vocabulary']", (path ? &lpath_28 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_26_map_$vocabulary (.'$TightSchema'.'|'.5.'$vocabulary')
static bool _jm_f_120(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.'$vocabulary'
    res = _jm_obj_28(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.5.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_26_map_contains (.'$TightSchema'.'|'.5.contains)
static bool _jm_f_121(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.contains
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.5.contains]", path);
    }
    return res;
}

// check _jm_obj_26_map_default (.'$TightSchema'.'|'.5.default)
static bool _jm_f_122(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.5.default]", path);
    }
    return res;
}

// check _jm_obj_26_map_deprecated (.'$TightSchema'.'|'.5.deprecated)
static bool _jm_f_123(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.5.deprecated]", path);
    }
    return res;
}

// check _jm_obj_26_map_description (.'$TightSchema'.'|'.5.description)
static bool _jm_f_124(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.5.description]", path);
    }
    return res;
}

// check _jm_obj_26_map_examples (.'$TightSchema'.'|'.5.examples)
static bool _jm_f_125(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.5.examples]", path);
    }
    return res;
}

// check _jm_obj_26_map_items (.'$TightSchema'.'|'.5.items)
static bool _jm_f_126(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.items
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.5.items]", path);
    }
    return res;
}

// check _jm_obj_26_map_maxContains (.'$TightSchema'.'|'.5.maxContains)
static bool _jm_f_127(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.maxContains
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.5.maxContains]", path);
    }
    return res;
}

// check _jm_obj_26_map_maxItems (.'$TightSchema'.'|'.5.maxItems)
static bool _jm_f_128(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.maxItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.5.maxItems]", path);
    }
    return res;
}

// check _jm_obj_26_map_minContains (.'$TightSchema'.'|'.5.minContains)
static bool _jm_f_129(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.minContains
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.5.minContains]", path);
    }
    return res;
}

// check _jm_obj_26_map_minItems (.'$TightSchema'.'|'.5.minItems)
static bool _jm_f_130(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.minItems
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.5.minItems]", path);
    }
    return res;
}

// check _jm_obj_26_map_prefixItems (.'$TightSchema'.'|'.5.prefixItems)
static bool _jm_f_131(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.prefixItems
    res = json_model_11(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $schemaArray [.'$TightSchema'.'|'.5.prefixItems]", path);
    }
    return res;
}

// check _jm_obj_26_map_readOnly (.'$TightSchema'.'|'.5.readOnly)
static bool _jm_f_132(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.5.readOnly]", path);
    }
    return res;
}

// check _jm_obj_26_map_title (.'$TightSchema'.'|'.5.title)
static bool _jm_f_133(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.5.title]", path);
    }
    return res;
}

// check _jm_obj_26_map_unevaluatedItems (.'$TightSchema'.'|'.5.unevaluatedItems)
static bool _jm_f_134(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.unevaluatedItems
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.5.unevaluatedItems]", path);
    }
    return res;
}

// check _jm_obj_26_map_uniqueItems (.'$TightSchema'.'|'.5.uniqueItems)
static bool _jm_f_135(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.uniqueItems
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.5.uniqueItems]", path);
    }
    return res;
}

// check _jm_obj_26_map_writeOnly (.'$TightSchema'.'|'.5.writeOnly)
static bool _jm_f_136(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.5.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.5.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_26_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_26_map_tab, 25);
}

// object .'$TightSchema'.'|'.5
static bool _jm_obj_26(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.5]", path);
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
            // .'$TightSchema'.'|'.5.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "array") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _array [.'$TightSchema'.'|'.5.type]", (path ? &lpath_26 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.5.type]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_26_map(prop)))
        {
            // handle 25 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_26 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.5]", (path ? &lpath_26 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.5]", (path ? &lpath_26 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.5]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_29_map_$anchor (.'$TightSchema'.'|'.4.'$anchor')
static bool _jm_f_137(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.4.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_29_map_$comment (.'$TightSchema'.'|'.4.'$comment')
static bool _jm_f_138(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.4.'$defs'
static bool _jm_obj_30(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.4.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_30 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.4.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_30 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.4.'$defs'.'']", (path ? &lpath_30 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_$defs (.'$TightSchema'.'|'.4.'$defs')
static bool _jm_f_139(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$defs'
    res = _jm_obj_30(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.4.'$defs']", path);
    }
    return res;
}

// check _jm_obj_29_map_$dynamicAnchor (.'$TightSchema'.'|'.4.'$dynamicAnchor')
static bool _jm_f_140(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.4.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_29_map_$dynamicRef (.'$TightSchema'.'|'.4.'$dynamicRef')
static bool _jm_f_141(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.4.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_29_map_$id (.'$TightSchema'.'|'.4.'$id')
static bool _jm_f_142(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.4.'$id']", path);
    }
    return res;
}

// check _jm_obj_29_map_$ref (.'$TightSchema'.'|'.4.'$ref')
static bool _jm_f_143(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.4.'$ref']", path);
    }
    return res;
}

// check _jm_obj_29_map_$schema (.'$TightSchema'.'|'.4.'$schema')
static bool _jm_f_144(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.4.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.4.'$vocabulary'
static bool _jm_obj_31(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.4.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_31 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.4.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.4.'$vocabulary'.'$URI']", (path ? &lpath_31 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.4.'$vocabulary']", (path ? &lpath_31 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_29_map_$vocabulary (.'$TightSchema'.'|'.4.'$vocabulary')
static bool _jm_f_145(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.'$vocabulary'
    res = _jm_obj_31(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.4.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_29_map_contentEncoding (.'$TightSchema'.'|'.4.contentEncoding)
static bool _jm_f_146(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.contentEncoding
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.contentEncoding]", path);
    }
    return res;
}

// check _jm_obj_29_map_contentMediaType (.'$TightSchema'.'|'.4.contentMediaType)
static bool _jm_f_147(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.contentMediaType
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.contentMediaType]", path);
    }
    return res;
}

// check _jm_obj_29_map_contentSchema (.'$TightSchema'.'|'.4.contentSchema)
static bool _jm_f_148(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.contentSchema
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.4.contentSchema]", path);
    }
    return res;
}

// check _jm_obj_29_map_default (.'$TightSchema'.'|'.4.default)
static bool _jm_f_149(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.4.default]", path);
    }
    return res;
}

// check _jm_obj_29_map_deprecated (.'$TightSchema'.'|'.4.deprecated)
static bool _jm_f_150(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.4.deprecated]", path);
    }
    return res;
}

// check _jm_obj_29_map_description (.'$TightSchema'.'|'.4.description)
static bool _jm_f_151(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.description]", path);
    }
    return res;
}

// check _jm_obj_29_map_examples (.'$TightSchema'.'|'.4.examples)
static bool _jm_f_152(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.4.examples]", path);
    }
    return res;
}

// check _jm_obj_29_map_format (.'$TightSchema'.'|'.4.format)
static bool _jm_f_153(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.format
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.format]", path);
    }
    return res;
}

// check _jm_obj_29_map_maxLength (.'$TightSchema'.'|'.4.maxLength)
static bool _jm_f_154(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.maxLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.4.maxLength]", path);
    }
    return res;
}

// check _jm_obj_29_map_minLength (.'$TightSchema'.'|'.4.minLength)
static bool _jm_f_155(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.minLength
    res = json_is_integer(val) && json_integer_value(val) >= 0;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 0 strict int [.'$TightSchema'.'|'.4.minLength]", path);
    }
    return res;
}

// check _jm_obj_29_map_pattern (.'$TightSchema'.'|'.4.pattern)
static bool _jm_f_156(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.pattern
    res = jm_is_valid_regex(json_string_value(val), false);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $REGEX [.'$TightSchema'.'|'.4.pattern]", path);
    }
    return res;
}

// check _jm_obj_29_map_readOnly (.'$TightSchema'.'|'.4.readOnly)
static bool _jm_f_157(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.4.readOnly]", path);
    }
    return res;
}

// check _jm_obj_29_map_title (.'$TightSchema'.'|'.4.title)
static bool _jm_f_158(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.4.title]", path);
    }
    return res;
}

// check _jm_obj_29_map_writeOnly (.'$TightSchema'.'|'.4.writeOnly)
static bool _jm_f_159(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.4.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.4.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_29_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_29_map_tab, 23);
}

// object .'$TightSchema'.'|'.4
static bool _jm_obj_29(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.4]", path);
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
            // .'$TightSchema'.'|'.4.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "string") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _string [.'$TightSchema'.'|'.4.type]", (path ? &lpath_29 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.4.type]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_29_map(prop)))
        {
            // handle 23 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_29 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.4]", (path ? &lpath_29 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.4]", (path ? &lpath_29 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.4]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_32_map_$anchor (.'$TightSchema'.'|'.3.'$anchor')
static bool _jm_f_160(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.3.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_32_map_$comment (.'$TightSchema'.'|'.3.'$comment')
static bool _jm_f_161(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.3.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.3.'$defs'
static bool _jm_obj_33(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.3.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_33 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.3.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_33 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.3.'$defs'.'']", (path ? &lpath_33 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_$defs (.'$TightSchema'.'|'.3.'$defs')
static bool _jm_f_162(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$defs'
    res = _jm_obj_33(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.3.'$defs']", path);
    }
    return res;
}

// check _jm_obj_32_map_$dynamicAnchor (.'$TightSchema'.'|'.3.'$dynamicAnchor')
static bool _jm_f_163(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.3.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_32_map_$dynamicRef (.'$TightSchema'.'|'.3.'$dynamicRef')
static bool _jm_f_164(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.3.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_32_map_$id (.'$TightSchema'.'|'.3.'$id')
static bool _jm_f_165(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.3.'$id']", path);
    }
    return res;
}

// check _jm_obj_32_map_$ref (.'$TightSchema'.'|'.3.'$ref')
static bool _jm_f_166(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.3.'$ref']", path);
    }
    return res;
}

// check _jm_obj_32_map_$schema (.'$TightSchema'.'|'.3.'$schema')
static bool _jm_f_167(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.3.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.3.'$vocabulary'
static bool _jm_obj_34(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.3.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_34 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.3.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.3.'$vocabulary'.'$URI']", (path ? &lpath_34 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.3.'$vocabulary']", (path ? &lpath_34 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_32_map_$vocabulary (.'$TightSchema'.'|'.3.'$vocabulary')
static bool _jm_f_168(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.'$vocabulary'
    res = _jm_obj_34(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.3.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_32_map_default (.'$TightSchema'.'|'.3.default)
static bool _jm_f_169(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.3.default]", path);
    }
    return res;
}

// check _jm_obj_32_map_deprecated (.'$TightSchema'.'|'.3.deprecated)
static bool _jm_f_170(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.3.deprecated]", path);
    }
    return res;
}

// check _jm_obj_32_map_description (.'$TightSchema'.'|'.3.description)
static bool _jm_f_171(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.3.description]", path);
    }
    return res;
}

// check _jm_obj_32_map_examples (.'$TightSchema'.'|'.3.examples)
static bool _jm_f_172(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.3.examples]", path);
    }
    return res;
}

// check _jm_obj_32_map_exclusiveMaximum (.'$TightSchema'.'|'.3.exclusiveMaximum)
static bool _jm_f_173(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.exclusiveMaximum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.3.exclusiveMaximum]", path);
    }
    return res;
}

// check _jm_obj_32_map_exclusiveMinimum (.'$TightSchema'.'|'.3.exclusiveMinimum)
static bool _jm_f_174(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.exclusiveMinimum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.3.exclusiveMinimum]", path);
    }
    return res;
}

// check _jm_obj_32_map_maximum (.'$TightSchema'.'|'.3.maximum)
static bool _jm_f_175(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.maximum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.3.maximum]", path);
    }
    return res;
}

// check _jm_obj_32_map_minimum (.'$TightSchema'.'|'.3.minimum)
static bool _jm_f_176(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.minimum
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.3.minimum]", path);
    }
    return res;
}

// check _jm_obj_32_map_multipleOf (.'$TightSchema'.'|'.3.multipleOf)
static bool _jm_f_177(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.multipleOf
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 strict int [.'$TightSchema'.'|'.3.multipleOf]", path);
    }
    return res;
}

// check _jm_obj_32_map_readOnly (.'$TightSchema'.'|'.3.readOnly)
static bool _jm_f_178(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.3.readOnly]", path);
    }
    return res;
}

// check _jm_obj_32_map_title (.'$TightSchema'.'|'.3.title)
static bool _jm_f_179(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.3.title]", path);
    }
    return res;
}

// check _jm_obj_32_map_writeOnly (.'$TightSchema'.'|'.3.writeOnly)
static bool _jm_f_180(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.3.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.3.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_32_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_32_map_tab, 21);
}

// object .'$TightSchema'.'|'.3
static bool _jm_obj_32(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.3]", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$TightSchema'.'|'.3.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "integer") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _integer [.'$TightSchema'.'|'.3.type]", (path ? &lpath_32 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.3.type]", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_32_map(prop)))
        {
            // handle 21 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_32 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.3]", (path ? &lpath_32 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.3]", (path ? &lpath_32 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.3]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_35_map_$anchor (.'$TightSchema'.'|'.2.'$anchor')
static bool _jm_f_181(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.2.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_35_map_$comment (.'$TightSchema'.'|'.2.'$comment')
static bool _jm_f_182(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.2.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.2.'$defs'
static bool _jm_obj_36(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.2.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_36 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.2.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_36 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.2.'$defs'.'']", (path ? &lpath_36 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_$defs (.'$TightSchema'.'|'.2.'$defs')
static bool _jm_f_183(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$defs'
    res = _jm_obj_36(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.2.'$defs']", path);
    }
    return res;
}

// check _jm_obj_35_map_$dynamicAnchor (.'$TightSchema'.'|'.2.'$dynamicAnchor')
static bool _jm_f_184(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.2.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_35_map_$dynamicRef (.'$TightSchema'.'|'.2.'$dynamicRef')
static bool _jm_f_185(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.2.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_35_map_$id (.'$TightSchema'.'|'.2.'$id')
static bool _jm_f_186(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.2.'$id']", path);
    }
    return res;
}

// check _jm_obj_35_map_$ref (.'$TightSchema'.'|'.2.'$ref')
static bool _jm_f_187(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.2.'$ref']", path);
    }
    return res;
}

// check _jm_obj_35_map_$schema (.'$TightSchema'.'|'.2.'$schema')
static bool _jm_f_188(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.2.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.2.'$vocabulary'
static bool _jm_obj_37(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.2.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_37 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.2.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.2.'$vocabulary'.'$URI']", (path ? &lpath_37 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.2.'$vocabulary']", (path ? &lpath_37 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_35_map_$vocabulary (.'$TightSchema'.'|'.2.'$vocabulary')
static bool _jm_f_189(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.'$vocabulary'
    res = _jm_obj_37(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.2.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_35_map_default (.'$TightSchema'.'|'.2.default)
static bool _jm_f_190(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.2.default]", path);
    }
    return res;
}

// check _jm_obj_35_map_deprecated (.'$TightSchema'.'|'.2.deprecated)
static bool _jm_f_191(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.2.deprecated]", path);
    }
    return res;
}

// check _jm_obj_35_map_description (.'$TightSchema'.'|'.2.description)
static bool _jm_f_192(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.2.description]", path);
    }
    return res;
}

// check _jm_obj_35_map_examples (.'$TightSchema'.'|'.2.examples)
static bool _jm_f_193(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.2.examples]", path);
    }
    return res;
}

// check _jm_obj_35_map_exclusiveMaximum (.'$TightSchema'.'|'.2.exclusiveMaximum)
static bool _jm_f_194(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.exclusiveMaximum
    // .'$TightSchema'.'|'.2.exclusiveMaximum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.2.exclusiveMaximum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$TightSchema'.'|'.2.exclusiveMaximum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$TightSchema'.'|'.2.exclusiveMaximum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|'.2.exclusiveMaximum.'|']", path);
    }
    return res;
}

// check _jm_obj_35_map_exclusiveMinimum (.'$TightSchema'.'|'.2.exclusiveMinimum)
static bool _jm_f_195(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.exclusiveMinimum
    // .'$TightSchema'.'|'.2.exclusiveMinimum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.2.exclusiveMinimum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$TightSchema'.'|'.2.exclusiveMinimum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$TightSchema'.'|'.2.exclusiveMinimum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|'.2.exclusiveMinimum.'|']", path);
    }
    return res;
}

// check _jm_obj_35_map_maximum (.'$TightSchema'.'|'.2.maximum)
static bool _jm_f_196(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.maximum
    // .'$TightSchema'.'|'.2.maximum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.2.maximum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$TightSchema'.'|'.2.maximum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$TightSchema'.'|'.2.maximum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|'.2.maximum.'|']", path);
    }
    return res;
}

// check _jm_obj_35_map_minimum (.'$TightSchema'.'|'.2.minimum)
static bool _jm_f_197(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.minimum
    // .'$TightSchema'.'|'.2.minimum.'|'.0
    res = json_is_integer(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a -1 strict int [.'$TightSchema'.'|'.2.minimum.'|'.0]", path);
    }
    if (! res)
    {
        // .'$TightSchema'.'|'.2.minimum.'|'.1
        res = json_is_real(val);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a -1.0 strict float [.'$TightSchema'.'|'.2.minimum.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|'.2.minimum.'|']", path);
    }
    return res;
}

// check _jm_obj_35_map_multipleOf (.'$TightSchema'.'|'.2.multipleOf)
static bool _jm_f_198(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.multipleOf
    // .'$TightSchema'.'|'.2.multipleOf.'|'.0
    res = json_is_integer(val) && json_integer_value(val) >= 1;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a 1 strict int [.'$TightSchema'.'|'.2.multipleOf.'|'.0]", path);
    }
    if (! res)
    {
        // .'$TightSchema'.'|'.2.multipleOf.'|'.1
        res = json_is_real(val) && json_real_value(val) > 0.0;
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not a 1.0 strict float [.'$TightSchema'.'|'.2.multipleOf.'|'.1]", path);
        }
    }
    if (res)
    {
        if (rep) jm_report_free_entries(rep);
    }
    else
    {
        if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|'.2.multipleOf.'|']", path);
    }
    return res;
}

// check _jm_obj_35_map_readOnly (.'$TightSchema'.'|'.2.readOnly)
static bool _jm_f_199(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.2.readOnly]", path);
    }
    return res;
}

// check _jm_obj_35_map_title (.'$TightSchema'.'|'.2.title)
static bool _jm_f_200(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.2.title]", path);
    }
    return res;
}

// check _jm_obj_35_map_writeOnly (.'$TightSchema'.'|'.2.writeOnly)
static bool _jm_f_201(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.2.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.2.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_35_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_35_map_tab, 21);
}

// object .'$TightSchema'.'|'.2
static bool _jm_obj_35(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.2]", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$TightSchema'.'|'.2.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "number") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _number [.'$TightSchema'.'|'.2.type]", (path ? &lpath_35 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.2.type]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_35_map(prop)))
        {
            // handle 21 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_35 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.2]", (path ? &lpath_35 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.2]", (path ? &lpath_35 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.2]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_38_map_$anchor (.'$TightSchema'.'|'.1.'$anchor')
static bool _jm_f_202(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.1.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_38_map_$comment (.'$TightSchema'.'|'.1.'$comment')
static bool _jm_f_203(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.1.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.1.'$defs'
static bool _jm_obj_39(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.1.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_39 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.1.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_39 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.1.'$defs'.'']", (path ? &lpath_39 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_$defs (.'$TightSchema'.'|'.1.'$defs')
static bool _jm_f_204(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$defs'
    res = _jm_obj_39(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.1.'$defs']", path);
    }
    return res;
}

// check _jm_obj_38_map_$dynamicAnchor (.'$TightSchema'.'|'.1.'$dynamicAnchor')
static bool _jm_f_205(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.1.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_38_map_$dynamicRef (.'$TightSchema'.'|'.1.'$dynamicRef')
static bool _jm_f_206(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.1.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_38_map_$id (.'$TightSchema'.'|'.1.'$id')
static bool _jm_f_207(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.1.'$id']", path);
    }
    return res;
}

// check _jm_obj_38_map_$ref (.'$TightSchema'.'|'.1.'$ref')
static bool _jm_f_208(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.1.'$ref']", path);
    }
    return res;
}

// check _jm_obj_38_map_$schema (.'$TightSchema'.'|'.1.'$schema')
static bool _jm_f_209(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.1.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.1.'$vocabulary'
static bool _jm_obj_40(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.1.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_40 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.1.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.1.'$vocabulary'.'$URI']", (path ? &lpath_40 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.1.'$vocabulary']", (path ? &lpath_40 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_38_map_$vocabulary (.'$TightSchema'.'|'.1.'$vocabulary')
static bool _jm_f_210(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.'$vocabulary'
    res = _jm_obj_40(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.1.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_38_map_default (.'$TightSchema'.'|'.1.default)
static bool _jm_f_211(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.1.default]", path);
    }
    return res;
}

// check _jm_obj_38_map_deprecated (.'$TightSchema'.'|'.1.deprecated)
static bool _jm_f_212(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.1.deprecated]", path);
    }
    return res;
}

// check _jm_obj_38_map_description (.'$TightSchema'.'|'.1.description)
static bool _jm_f_213(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.1.description]", path);
    }
    return res;
}

// check _jm_obj_38_map_examples (.'$TightSchema'.'|'.1.examples)
static bool _jm_f_214(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.1.examples]", path);
    }
    return res;
}

// check _jm_obj_38_map_readOnly (.'$TightSchema'.'|'.1.readOnly)
static bool _jm_f_215(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.1.readOnly]", path);
    }
    return res;
}

// check _jm_obj_38_map_title (.'$TightSchema'.'|'.1.title)
static bool _jm_f_216(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.1.title]", path);
    }
    return res;
}

// check _jm_obj_38_map_writeOnly (.'$TightSchema'.'|'.1.writeOnly)
static bool _jm_f_217(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.1.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.1.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_38_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_38_map_tab, 16);
}

// object .'$TightSchema'.'|'.1
static bool _jm_obj_38(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.1]", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$TightSchema'.'|'.1.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "boolean") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _boolean [.'$TightSchema'.'|'.1.type]", (path ? &lpath_38 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.1.type]", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_38_map(prop)))
        {
            // handle 16 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_38 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.1]", (path ? &lpath_38 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.1]", (path ? &lpath_38 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.1]", path);
            }
        }
        return false;
    }
    return true;
}

// check _jm_obj_41_map_$anchor (.'$TightSchema'.'|'.0.'$anchor')
static bool _jm_f_218(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$anchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.0.'$anchor']", path);
    }
    return res;
}

// check _jm_obj_41_map_$comment (.'$TightSchema'.'|'.0.'$comment')
static bool _jm_f_219(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$comment'
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.0.'$comment']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.0.'$defs'
static bool _jm_obj_42(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.0.'$defs']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_42 = (jm_path_t) { prop, 0, path, NULL };
        // handle other props
        // .'$TightSchema'.'|'.0.'$defs'.''
        res = json_model_16(pval, (path ? &lpath_42 : NULL), rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $Schema [.'$TightSchema'.'|'.0.'$defs'.'']", (path ? &lpath_42 : NULL));
        }
        if (! res)
        {
            return false;
        }
    }
    return true;
}

// check _jm_obj_41_map_$defs (.'$TightSchema'.'|'.0.'$defs')
static bool _jm_f_220(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$defs'
    res = _jm_obj_42(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.0.'$defs']", path);
    }
    return res;
}

// check _jm_obj_41_map_$dynamicAnchor (.'$TightSchema'.'|'.0.'$dynamicAnchor')
static bool _jm_f_221(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$dynamicAnchor'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.0.'$dynamicAnchor']", path);
    }
    return res;
}

// check _jm_obj_41_map_$dynamicRef (.'$TightSchema'.'|'.0.'$dynamicRef')
static bool _jm_f_222(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$dynamicRef'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.0.'$dynamicRef']", path);
    }
    return res;
}

// check _jm_obj_41_map_$id (.'$TightSchema'.'|'.0.'$id')
static bool _jm_f_223(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$id'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.0.'$id']", path);
    }
    return res;
}

// check _jm_obj_41_map_$ref (.'$TightSchema'.'|'.0.'$ref')
static bool _jm_f_224(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$ref'
    res = json_model_2(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI-REFERENCE [.'$TightSchema'.'|'.0.'$ref']", path);
    }
    return res;
}

// check _jm_obj_41_map_$schema (.'$TightSchema'.'|'.0.'$schema')
static bool _jm_f_225(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$schema'
    res = jm_is_valid_url(json_string_value(val));
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $URI [.'$TightSchema'.'|'.0.'$schema']", path);
    }
    return res;
}

// object .'$TightSchema'.'|'.0.'$vocabulary'
static bool _jm_obj_43(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.0.'$vocabulary']", path);
        return false;
    }
    bool res;
    const char *prop;
    json_t *pval;
    json_object_foreach((json_t *) val, prop, pval)
    {
        jm_path_t lpath_43 = (jm_path_t) { prop, 0, path, NULL };
        if (jm_is_valid_url(prop))
        {
            // handle 1 key props
            // .'$TightSchema'.'|'.0.'$vocabulary'.'$URI'
            res = json_is_boolean(pval);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.0.'$vocabulary'.'$URI']", (path ? &lpath_43 : NULL));
            }
            if (! res)
            {
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.0.'$vocabulary']", (path ? &lpath_43 : NULL));
            return false;
        }
    }
    return true;
}

// check _jm_obj_41_map_$vocabulary (.'$TightSchema'.'|'.0.'$vocabulary')
static bool _jm_f_226(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.'$vocabulary'
    res = _jm_obj_43(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.0.'$vocabulary']", path);
    }
    return res;
}

// check _jm_obj_41_map_default (.'$TightSchema'.'|'.0.default)
static bool _jm_f_227(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.default
    res = true;
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $ANY [.'$TightSchema'.'|'.0.default]", path);
    }
    return res;
}

// check _jm_obj_41_map_deprecated (.'$TightSchema'.'|'.0.deprecated)
static bool _jm_f_228(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.deprecated
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.0.deprecated]", path);
    }
    return res;
}

// check _jm_obj_41_map_description (.'$TightSchema'.'|'.0.description)
static bool _jm_f_229(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.description
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.0.description]", path);
    }
    return res;
}

// check _jm_obj_41_map_examples (.'$TightSchema'.'|'.0.examples)
static bool _jm_f_230(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.examples
    res = json_is_array(val);
    if (res)
    {
        // accept any array
    }
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not array or unexpected array [.'$TightSchema'.'|'.0.examples]", path);
    }
    return res;
}

// check _jm_obj_41_map_readOnly (.'$TightSchema'.'|'.0.readOnly)
static bool _jm_f_231(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.readOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.0.readOnly]", path);
    }
    return res;
}

// check _jm_obj_41_map_title (.'$TightSchema'.'|'.0.title)
static bool _jm_f_232(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.title
    res = json_is_string(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected string [.'$TightSchema'.'|'.0.title]", path);
    }
    return res;
}

// check _jm_obj_41_map_writeOnly (.'$TightSchema'.'|'.0.writeOnly)
static bool _jm_f_233(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'.'|'.0.writeOnly
    res = json_is_boolean(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "not a bool [.'$TightSchema'.'|'.0.writeOnly]", path);
    }
    return res;
}

static jm_check_fun_t _jm_obj_41_map(const char *pname)
{
    return jm_search_propmap(pname, _jm_obj_41_map_tab, 16);
}

// object .'$TightSchema'.'|'.0
static bool _jm_obj_41(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    if (! json_is_object(val))
    {
        if (rep) jm_report_add_entry(rep, "not an object [.'$TightSchema'.'|'.0]", path);
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
        if (strcmp(prop, "type") == 0)
        {
            // handle must type property
            must_count += 1;
            // .'$TightSchema'.'|'.0.type
            res = json_is_string(pval) && strcmp(json_string_value(pval), "null") == 0;
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "unexpected _null [.'$TightSchema'.'|'.0.type]", (path ? &lpath_41 : NULL));
            }
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "invalid mandatory prop value [.'$TightSchema'.'|'.0.type]", (path ? &lpath_41 : NULL));
                return false;
            }
        }
        else if ((pfun = _jm_obj_41_map(prop)))
        {
            // handle 16 may props
            if (pfun != NULL && ! pfun(pval, (path ? &lpath_41 : NULL), rep))
            {
                if (rep) jm_report_add_entry(rep, "invalid optional prop value [.'$TightSchema'.'|'.0]", (path ? &lpath_41 : NULL));
                return false;
            }
        }
        else
        {
            if (rep) jm_report_add_entry(rep, "unexpected prop [.'$TightSchema'.'|'.0]", (path ? &lpath_41 : NULL));
            return false;
        }
    }
    if (must_count != 1)
    {
        if (rep != NULL)
        {
            if (! (json_object_get(val, "type") != NULL))
            {
                if (rep) jm_report_add_entry(rep, "missing mandatory prop <type> [.'$TightSchema'.'|'.0]", path);
            }
        }
        return false;
    }
    return true;
}

// check $TightSchema (.'$TightSchema')
static bool json_model_15(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .'$TightSchema'
    res = json_is_object(val);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected type [.'$TightSchema'.'|']", path);
    }
    if (res)
    {
        // .'$TightSchema'.'|'.0
        res = _jm_obj_41(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.0]", path);
        }
        if (! res)
        {
            // .'$TightSchema'.'|'.1
            res = _jm_obj_38(val, path, rep);
            if (! res)
            {
                if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.1]", path);
            }
            if (! res)
            {
                // .'$TightSchema'.'|'.2
                res = _jm_obj_35(val, path, rep);
                if (! res)
                {
                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.2]", path);
                }
                if (! res)
                {
                    // .'$TightSchema'.'|'.3
                    res = _jm_obj_32(val, path, rep);
                    if (! res)
                    {
                        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.3]", path);
                    }
                    if (! res)
                    {
                        // .'$TightSchema'.'|'.4
                        res = _jm_obj_29(val, path, rep);
                        if (! res)
                        {
                            if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.4]", path);
                        }
                        if (! res)
                        {
                            // .'$TightSchema'.'|'.5
                            res = _jm_obj_26(val, path, rep);
                            if (! res)
                            {
                                if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.5]", path);
                            }
                            if (! res)
                            {
                                // .'$TightSchema'.'|'.6
                                res = _jm_obj_19(val, path, rep);
                                if (! res)
                                {
                                    if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.6]", path);
                                }
                                if (! res)
                                {
                                    // .'$TightSchema'.'|'.7
                                    res = _jm_obj_16(val, path, rep);
                                    if (! res)
                                    {
                                        if (rep) jm_report_add_entry(rep, "not an expected object [.'$TightSchema'.'|'.7]", path);
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
            if (rep) jm_report_add_entry(rep, "no model matched [.'$TightSchema'.'|']", path);
        }
    }
    return res;
}

// check $Schema (.'$Schema')
static bool json_model_16(const json_t *val, jm_path_t *path, jm_report_t *rep)
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
        res = json_model_15(val, path, rep);
        if (! res)
        {
            if (rep) jm_report_add_entry(rep, "unexpected $TightSchema [.'$Schema'.'|'.1]", path);
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

// check $ (.)
static bool json_model_1(const json_t *val, jm_path_t *path, jm_report_t *rep)
{
    bool res;
    // .
    res = json_model_16(val, path, rep);
    if (! res)
    {
        if (rep) jm_report_add_entry(rep, "unexpected $Schema [.]", path);
    }
    return res;
}

jm_check_fun_t check_model_map(const char *pname)
{
    return jm_search_propmap(pname, check_model_map_tab, 16);
}

static bool initialized = false;

char *CHECK_init(void)
{
    if (!initialized)
    {
        initialized = true;
        jm_version_string = JSON_MODEL_VERSION;
        _jm_obj_0_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_0 };
        _jm_obj_0_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_1 };
        _jm_obj_0_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_2 };
        _jm_obj_0_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_3 };
        _jm_obj_0_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_4 };
        _jm_obj_0_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_5 };
        _jm_obj_0_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_6 };
        _jm_obj_0_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_7 };
        _jm_obj_0_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_8 };
        jm_sort_propmap(_jm_obj_0_map_tab, 9);
        _jm_obj_3_map_tab[0] = (jm_propmap_t) { "default", _jm_f_9 };
        _jm_obj_3_map_tab[1] = (jm_propmap_t) { "deprecated", _jm_f_10 };
        _jm_obj_3_map_tab[2] = (jm_propmap_t) { "description", _jm_f_11 };
        _jm_obj_3_map_tab[3] = (jm_propmap_t) { "examples", _jm_f_12 };
        _jm_obj_3_map_tab[4] = (jm_propmap_t) { "readOnly", _jm_f_13 };
        _jm_obj_3_map_tab[5] = (jm_propmap_t) { "title", _jm_f_14 };
        _jm_obj_3_map_tab[6] = (jm_propmap_t) { "writeOnly", _jm_f_15 };
        jm_sort_propmap(_jm_obj_3_map_tab, 7);
        _jm_obj_6_map_tab[0] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_16 };
        _jm_obj_6_map_tab[1] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_17 };
        _jm_obj_6_map_tab[2] = (jm_propmap_t) { "maximum", _jm_f_18 };
        _jm_obj_6_map_tab[3] = (jm_propmap_t) { "minimum", _jm_f_19 };
        _jm_obj_6_map_tab[4] = (jm_propmap_t) { "multipleOf", _jm_f_20 };
        jm_sort_propmap(_jm_obj_6_map_tab, 5);
        _jm_obj_7_map_tab[0] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_21 };
        _jm_obj_7_map_tab[1] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_22 };
        _jm_obj_7_map_tab[2] = (jm_propmap_t) { "maximum", _jm_f_23 };
        _jm_obj_7_map_tab[3] = (jm_propmap_t) { "minimum", _jm_f_24 };
        _jm_obj_7_map_tab[4] = (jm_propmap_t) { "multipleOf", _jm_f_25 };
        jm_sort_propmap(_jm_obj_7_map_tab, 5);
        _jm_obj_8_map_tab[0] = (jm_propmap_t) { "contentEncoding", _jm_f_26 };
        _jm_obj_8_map_tab[1] = (jm_propmap_t) { "contentMediaType", _jm_f_27 };
        _jm_obj_8_map_tab[2] = (jm_propmap_t) { "contentSchema", _jm_f_28 };
        _jm_obj_8_map_tab[3] = (jm_propmap_t) { "format", _jm_f_29 };
        _jm_obj_8_map_tab[4] = (jm_propmap_t) { "maxLength", _jm_f_30 };
        _jm_obj_8_map_tab[5] = (jm_propmap_t) { "minLength", _jm_f_31 };
        _jm_obj_8_map_tab[6] = (jm_propmap_t) { "pattern", _jm_f_32 };
        jm_sort_propmap(_jm_obj_8_map_tab, 7);
        _jm_obj_9_map_tab[0] = (jm_propmap_t) { "contains", _jm_f_33 };
        _jm_obj_9_map_tab[1] = (jm_propmap_t) { "items", _jm_f_34 };
        _jm_obj_9_map_tab[2] = (jm_propmap_t) { "maxContains", _jm_f_35 };
        _jm_obj_9_map_tab[3] = (jm_propmap_t) { "maxItems", _jm_f_36 };
        _jm_obj_9_map_tab[4] = (jm_propmap_t) { "minContains", _jm_f_37 };
        _jm_obj_9_map_tab[5] = (jm_propmap_t) { "minItems", _jm_f_38 };
        _jm_obj_9_map_tab[6] = (jm_propmap_t) { "prefixItems", _jm_f_39 };
        _jm_obj_9_map_tab[7] = (jm_propmap_t) { "unevaluatedItems", _jm_f_40 };
        _jm_obj_9_map_tab[8] = (jm_propmap_t) { "uniqueItems", _jm_f_41 };
        jm_sort_propmap(_jm_obj_9_map_tab, 9);
        _jm_obj_10_map_tab[0] = (jm_propmap_t) { "additionalProperties", _jm_f_42 };
        _jm_obj_10_map_tab[1] = (jm_propmap_t) { "dependentRequired", _jm_f_43 };
        _jm_obj_10_map_tab[2] = (jm_propmap_t) { "dependentSchemas", _jm_f_44 };
        _jm_obj_10_map_tab[3] = (jm_propmap_t) { "maxProperties", _jm_f_45 };
        _jm_obj_10_map_tab[4] = (jm_propmap_t) { "minProperties", _jm_f_46 };
        _jm_obj_10_map_tab[5] = (jm_propmap_t) { "patternProperties", _jm_f_47 };
        _jm_obj_10_map_tab[6] = (jm_propmap_t) { "properties", _jm_f_48 };
        _jm_obj_10_map_tab[7] = (jm_propmap_t) { "propertyNames", _jm_f_49 };
        _jm_obj_10_map_tab[8] = (jm_propmap_t) { "required", _jm_f_50 };
        _jm_obj_10_map_tab[9] = (jm_propmap_t) { "unevaluatedProperties", _jm_f_51 };
        jm_sort_propmap(_jm_obj_10_map_tab, 10);
        _jm_obj_15_map_tab[0] = (jm_propmap_t) { "allOf", _jm_f_52 };
        _jm_obj_15_map_tab[1] = (jm_propmap_t) { "anyOf", _jm_f_53 };
        _jm_obj_15_map_tab[2] = (jm_propmap_t) { "const", _jm_f_54 };
        _jm_obj_15_map_tab[3] = (jm_propmap_t) { "else", _jm_f_55 };
        _jm_obj_15_map_tab[4] = (jm_propmap_t) { "enum", _jm_f_56 };
        _jm_obj_15_map_tab[5] = (jm_propmap_t) { "if", _jm_f_57 };
        _jm_obj_15_map_tab[6] = (jm_propmap_t) { "not", _jm_f_58 };
        _jm_obj_15_map_tab[7] = (jm_propmap_t) { "oneOf", _jm_f_59 };
        _jm_obj_15_map_tab[8] = (jm_propmap_t) { "then", _jm_f_60 };
        jm_sort_propmap(_jm_obj_15_map_tab, 9);
        _jm_obj_16_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_61 };
        _jm_obj_16_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_62 };
        _jm_obj_16_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_63 };
        _jm_obj_16_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_64 };
        _jm_obj_16_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_65 };
        _jm_obj_16_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_66 };
        _jm_obj_16_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_67 };
        _jm_obj_16_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_68 };
        _jm_obj_16_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_69 };
        _jm_obj_16_map_tab[9] = (jm_propmap_t) { "allOf", _jm_f_70 };
        _jm_obj_16_map_tab[10] = (jm_propmap_t) { "anyOf", _jm_f_71 };
        _jm_obj_16_map_tab[11] = (jm_propmap_t) { "const", _jm_f_72 };
        _jm_obj_16_map_tab[12] = (jm_propmap_t) { "default", _jm_f_73 };
        _jm_obj_16_map_tab[13] = (jm_propmap_t) { "deprecated", _jm_f_74 };
        _jm_obj_16_map_tab[14] = (jm_propmap_t) { "description", _jm_f_75 };
        _jm_obj_16_map_tab[15] = (jm_propmap_t) { "else", _jm_f_76 };
        _jm_obj_16_map_tab[16] = (jm_propmap_t) { "enum", _jm_f_77 };
        _jm_obj_16_map_tab[17] = (jm_propmap_t) { "examples", _jm_f_78 };
        _jm_obj_16_map_tab[18] = (jm_propmap_t) { "if", _jm_f_79 };
        _jm_obj_16_map_tab[19] = (jm_propmap_t) { "not", _jm_f_80 };
        _jm_obj_16_map_tab[20] = (jm_propmap_t) { "oneOf", _jm_f_81 };
        _jm_obj_16_map_tab[21] = (jm_propmap_t) { "readOnly", _jm_f_82 };
        _jm_obj_16_map_tab[22] = (jm_propmap_t) { "then", _jm_f_83 };
        _jm_obj_16_map_tab[23] = (jm_propmap_t) { "title", _jm_f_84 };
        _jm_obj_16_map_tab[24] = (jm_propmap_t) { "writeOnly", _jm_f_85 };
        jm_sort_propmap(_jm_obj_16_map_tab, 25);
        _jm_obj_19_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_86 };
        _jm_obj_19_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_87 };
        _jm_obj_19_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_88 };
        _jm_obj_19_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_89 };
        _jm_obj_19_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_90 };
        _jm_obj_19_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_91 };
        _jm_obj_19_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_92 };
        _jm_obj_19_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_93 };
        _jm_obj_19_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_94 };
        _jm_obj_19_map_tab[9] = (jm_propmap_t) { "additionalProperties", _jm_f_95 };
        _jm_obj_19_map_tab[10] = (jm_propmap_t) { "default", _jm_f_96 };
        _jm_obj_19_map_tab[11] = (jm_propmap_t) { "dependentRequired", _jm_f_97 };
        _jm_obj_19_map_tab[12] = (jm_propmap_t) { "dependentSchemas", _jm_f_98 };
        _jm_obj_19_map_tab[13] = (jm_propmap_t) { "deprecated", _jm_f_99 };
        _jm_obj_19_map_tab[14] = (jm_propmap_t) { "description", _jm_f_100 };
        _jm_obj_19_map_tab[15] = (jm_propmap_t) { "examples", _jm_f_101 };
        _jm_obj_19_map_tab[16] = (jm_propmap_t) { "maxProperties", _jm_f_102 };
        _jm_obj_19_map_tab[17] = (jm_propmap_t) { "minProperties", _jm_f_103 };
        _jm_obj_19_map_tab[18] = (jm_propmap_t) { "patternProperties", _jm_f_104 };
        _jm_obj_19_map_tab[19] = (jm_propmap_t) { "properties", _jm_f_105 };
        _jm_obj_19_map_tab[20] = (jm_propmap_t) { "propertyNames", _jm_f_106 };
        _jm_obj_19_map_tab[21] = (jm_propmap_t) { "readOnly", _jm_f_107 };
        _jm_obj_19_map_tab[22] = (jm_propmap_t) { "required", _jm_f_108 };
        _jm_obj_19_map_tab[23] = (jm_propmap_t) { "title", _jm_f_109 };
        _jm_obj_19_map_tab[24] = (jm_propmap_t) { "unevaluatedProperties", _jm_f_110 };
        _jm_obj_19_map_tab[25] = (jm_propmap_t) { "writeOnly", _jm_f_111 };
        jm_sort_propmap(_jm_obj_19_map_tab, 26);
        _jm_obj_26_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_112 };
        _jm_obj_26_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_113 };
        _jm_obj_26_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_114 };
        _jm_obj_26_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_115 };
        _jm_obj_26_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_116 };
        _jm_obj_26_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_117 };
        _jm_obj_26_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_118 };
        _jm_obj_26_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_119 };
        _jm_obj_26_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_120 };
        _jm_obj_26_map_tab[9] = (jm_propmap_t) { "contains", _jm_f_121 };
        _jm_obj_26_map_tab[10] = (jm_propmap_t) { "default", _jm_f_122 };
        _jm_obj_26_map_tab[11] = (jm_propmap_t) { "deprecated", _jm_f_123 };
        _jm_obj_26_map_tab[12] = (jm_propmap_t) { "description", _jm_f_124 };
        _jm_obj_26_map_tab[13] = (jm_propmap_t) { "examples", _jm_f_125 };
        _jm_obj_26_map_tab[14] = (jm_propmap_t) { "items", _jm_f_126 };
        _jm_obj_26_map_tab[15] = (jm_propmap_t) { "maxContains", _jm_f_127 };
        _jm_obj_26_map_tab[16] = (jm_propmap_t) { "maxItems", _jm_f_128 };
        _jm_obj_26_map_tab[17] = (jm_propmap_t) { "minContains", _jm_f_129 };
        _jm_obj_26_map_tab[18] = (jm_propmap_t) { "minItems", _jm_f_130 };
        _jm_obj_26_map_tab[19] = (jm_propmap_t) { "prefixItems", _jm_f_131 };
        _jm_obj_26_map_tab[20] = (jm_propmap_t) { "readOnly", _jm_f_132 };
        _jm_obj_26_map_tab[21] = (jm_propmap_t) { "title", _jm_f_133 };
        _jm_obj_26_map_tab[22] = (jm_propmap_t) { "unevaluatedItems", _jm_f_134 };
        _jm_obj_26_map_tab[23] = (jm_propmap_t) { "uniqueItems", _jm_f_135 };
        _jm_obj_26_map_tab[24] = (jm_propmap_t) { "writeOnly", _jm_f_136 };
        jm_sort_propmap(_jm_obj_26_map_tab, 25);
        _jm_obj_29_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_137 };
        _jm_obj_29_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_138 };
        _jm_obj_29_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_139 };
        _jm_obj_29_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_140 };
        _jm_obj_29_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_141 };
        _jm_obj_29_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_142 };
        _jm_obj_29_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_143 };
        _jm_obj_29_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_144 };
        _jm_obj_29_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_145 };
        _jm_obj_29_map_tab[9] = (jm_propmap_t) { "contentEncoding", _jm_f_146 };
        _jm_obj_29_map_tab[10] = (jm_propmap_t) { "contentMediaType", _jm_f_147 };
        _jm_obj_29_map_tab[11] = (jm_propmap_t) { "contentSchema", _jm_f_148 };
        _jm_obj_29_map_tab[12] = (jm_propmap_t) { "default", _jm_f_149 };
        _jm_obj_29_map_tab[13] = (jm_propmap_t) { "deprecated", _jm_f_150 };
        _jm_obj_29_map_tab[14] = (jm_propmap_t) { "description", _jm_f_151 };
        _jm_obj_29_map_tab[15] = (jm_propmap_t) { "examples", _jm_f_152 };
        _jm_obj_29_map_tab[16] = (jm_propmap_t) { "format", _jm_f_153 };
        _jm_obj_29_map_tab[17] = (jm_propmap_t) { "maxLength", _jm_f_154 };
        _jm_obj_29_map_tab[18] = (jm_propmap_t) { "minLength", _jm_f_155 };
        _jm_obj_29_map_tab[19] = (jm_propmap_t) { "pattern", _jm_f_156 };
        _jm_obj_29_map_tab[20] = (jm_propmap_t) { "readOnly", _jm_f_157 };
        _jm_obj_29_map_tab[21] = (jm_propmap_t) { "title", _jm_f_158 };
        _jm_obj_29_map_tab[22] = (jm_propmap_t) { "writeOnly", _jm_f_159 };
        jm_sort_propmap(_jm_obj_29_map_tab, 23);
        _jm_obj_32_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_160 };
        _jm_obj_32_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_161 };
        _jm_obj_32_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_162 };
        _jm_obj_32_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_163 };
        _jm_obj_32_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_164 };
        _jm_obj_32_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_165 };
        _jm_obj_32_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_166 };
        _jm_obj_32_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_167 };
        _jm_obj_32_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_168 };
        _jm_obj_32_map_tab[9] = (jm_propmap_t) { "default", _jm_f_169 };
        _jm_obj_32_map_tab[10] = (jm_propmap_t) { "deprecated", _jm_f_170 };
        _jm_obj_32_map_tab[11] = (jm_propmap_t) { "description", _jm_f_171 };
        _jm_obj_32_map_tab[12] = (jm_propmap_t) { "examples", _jm_f_172 };
        _jm_obj_32_map_tab[13] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_173 };
        _jm_obj_32_map_tab[14] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_174 };
        _jm_obj_32_map_tab[15] = (jm_propmap_t) { "maximum", _jm_f_175 };
        _jm_obj_32_map_tab[16] = (jm_propmap_t) { "minimum", _jm_f_176 };
        _jm_obj_32_map_tab[17] = (jm_propmap_t) { "multipleOf", _jm_f_177 };
        _jm_obj_32_map_tab[18] = (jm_propmap_t) { "readOnly", _jm_f_178 };
        _jm_obj_32_map_tab[19] = (jm_propmap_t) { "title", _jm_f_179 };
        _jm_obj_32_map_tab[20] = (jm_propmap_t) { "writeOnly", _jm_f_180 };
        jm_sort_propmap(_jm_obj_32_map_tab, 21);
        _jm_obj_35_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_181 };
        _jm_obj_35_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_182 };
        _jm_obj_35_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_183 };
        _jm_obj_35_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_184 };
        _jm_obj_35_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_185 };
        _jm_obj_35_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_186 };
        _jm_obj_35_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_187 };
        _jm_obj_35_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_188 };
        _jm_obj_35_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_189 };
        _jm_obj_35_map_tab[9] = (jm_propmap_t) { "default", _jm_f_190 };
        _jm_obj_35_map_tab[10] = (jm_propmap_t) { "deprecated", _jm_f_191 };
        _jm_obj_35_map_tab[11] = (jm_propmap_t) { "description", _jm_f_192 };
        _jm_obj_35_map_tab[12] = (jm_propmap_t) { "examples", _jm_f_193 };
        _jm_obj_35_map_tab[13] = (jm_propmap_t) { "exclusiveMaximum", _jm_f_194 };
        _jm_obj_35_map_tab[14] = (jm_propmap_t) { "exclusiveMinimum", _jm_f_195 };
        _jm_obj_35_map_tab[15] = (jm_propmap_t) { "maximum", _jm_f_196 };
        _jm_obj_35_map_tab[16] = (jm_propmap_t) { "minimum", _jm_f_197 };
        _jm_obj_35_map_tab[17] = (jm_propmap_t) { "multipleOf", _jm_f_198 };
        _jm_obj_35_map_tab[18] = (jm_propmap_t) { "readOnly", _jm_f_199 };
        _jm_obj_35_map_tab[19] = (jm_propmap_t) { "title", _jm_f_200 };
        _jm_obj_35_map_tab[20] = (jm_propmap_t) { "writeOnly", _jm_f_201 };
        jm_sort_propmap(_jm_obj_35_map_tab, 21);
        _jm_obj_38_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_202 };
        _jm_obj_38_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_203 };
        _jm_obj_38_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_204 };
        _jm_obj_38_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_205 };
        _jm_obj_38_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_206 };
        _jm_obj_38_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_207 };
        _jm_obj_38_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_208 };
        _jm_obj_38_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_209 };
        _jm_obj_38_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_210 };
        _jm_obj_38_map_tab[9] = (jm_propmap_t) { "default", _jm_f_211 };
        _jm_obj_38_map_tab[10] = (jm_propmap_t) { "deprecated", _jm_f_212 };
        _jm_obj_38_map_tab[11] = (jm_propmap_t) { "description", _jm_f_213 };
        _jm_obj_38_map_tab[12] = (jm_propmap_t) { "examples", _jm_f_214 };
        _jm_obj_38_map_tab[13] = (jm_propmap_t) { "readOnly", _jm_f_215 };
        _jm_obj_38_map_tab[14] = (jm_propmap_t) { "title", _jm_f_216 };
        _jm_obj_38_map_tab[15] = (jm_propmap_t) { "writeOnly", _jm_f_217 };
        jm_sort_propmap(_jm_obj_38_map_tab, 16);
        _jm_obj_41_map_tab[0] = (jm_propmap_t) { "$anchor", _jm_f_218 };
        _jm_obj_41_map_tab[1] = (jm_propmap_t) { "$comment", _jm_f_219 };
        _jm_obj_41_map_tab[2] = (jm_propmap_t) { "$defs", _jm_f_220 };
        _jm_obj_41_map_tab[3] = (jm_propmap_t) { "$dynamicAnchor", _jm_f_221 };
        _jm_obj_41_map_tab[4] = (jm_propmap_t) { "$dynamicRef", _jm_f_222 };
        _jm_obj_41_map_tab[5] = (jm_propmap_t) { "$id", _jm_f_223 };
        _jm_obj_41_map_tab[6] = (jm_propmap_t) { "$ref", _jm_f_224 };
        _jm_obj_41_map_tab[7] = (jm_propmap_t) { "$schema", _jm_f_225 };
        _jm_obj_41_map_tab[8] = (jm_propmap_t) { "$vocabulary", _jm_f_226 };
        _jm_obj_41_map_tab[9] = (jm_propmap_t) { "default", _jm_f_227 };
        _jm_obj_41_map_tab[10] = (jm_propmap_t) { "deprecated", _jm_f_228 };
        _jm_obj_41_map_tab[11] = (jm_propmap_t) { "description", _jm_f_229 };
        _jm_obj_41_map_tab[12] = (jm_propmap_t) { "examples", _jm_f_230 };
        _jm_obj_41_map_tab[13] = (jm_propmap_t) { "readOnly", _jm_f_231 };
        _jm_obj_41_map_tab[14] = (jm_propmap_t) { "title", _jm_f_232 };
        _jm_obj_41_map_tab[15] = (jm_propmap_t) { "writeOnly", _jm_f_233 };
        jm_sort_propmap(_jm_obj_41_map_tab, 16);
        check_model_map_tab[0] = (jm_propmap_t) { "", json_model_1 };
        check_model_map_tab[1] = (jm_propmap_t) { "URI-REFERENCE", json_model_2 };
        check_model_map_tab[2] = (jm_propmap_t) { "core", json_model_3 };
        check_model_map_tab[3] = (jm_propmap_t) { "meta", json_model_4 };
        check_model_map_tab[4] = (jm_propmap_t) { "Null", json_model_5 };
        check_model_map_tab[5] = (jm_propmap_t) { "Boolean", json_model_6 };
        check_model_map_tab[6] = (jm_propmap_t) { "Number", json_model_7 };
        check_model_map_tab[7] = (jm_propmap_t) { "Integer", json_model_8 };
        check_model_map_tab[8] = (jm_propmap_t) { "String", json_model_9 };
        check_model_map_tab[9] = (jm_propmap_t) { "stringArray", json_model_10 };
        check_model_map_tab[10] = (jm_propmap_t) { "schemaArray", json_model_11 };
        check_model_map_tab[11] = (jm_propmap_t) { "Array", json_model_12 };
        check_model_map_tab[12] = (jm_propmap_t) { "Object", json_model_13 };
        check_model_map_tab[13] = (jm_propmap_t) { "Misc", json_model_14 };
        check_model_map_tab[14] = (jm_propmap_t) { "TightSchema", json_model_15 };
        check_model_map_tab[15] = (jm_propmap_t) { "Schema", json_model_16 };
        jm_sort_propmap(check_model_map_tab, 16);
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
