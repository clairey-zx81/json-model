import json
from .language import Language, Block, Var, Inst, Block, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, FloatExpr, NumExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar
from .utils import UUID_RE

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class CLangJansson(Language):
    """Generate JSON value checker in C with Jansson and PCRE2.

    This implemebtation relies on inheritance for many methods, thanks to the root
    class heavy parameterization about operators, end-of-instruction and the like.
    """

    def __init__(self, *,
                 debug: bool = False,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 relib: str = "pcre2", int_t: str = "int64_t"):

        super().__init__(
            "C",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             not_op="!", and_op="&&", or_op="||", lcom="//",
             eoi=";", relib=relib, debug=debug,
             set_caps=[type(None), bool, int, float, str])

        assert relib == "pcre2", f"only pcre2 is supported for now, not {relib}"

        self._int: str = int_t
        self._json_esc_table: str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self: str) -> Block:
        return [
            r"#include <json-model.h>",
            f"#define JSON_MODEL_VERSION {self.esc(self._version)}"
        ]

    def file_footer(self) -> Block:
        return [""] + self.file_load("clang_entry.c")

    #
    # inlined type test expressions about JSON data
    #
    def is_obj(self, var: Var) -> BoolExpr:
        return f"json_is_object({var})"

    def is_arr(self, var: Var) -> BoolExpr:
        return f"json_is_array({var})"

    def is_str(self, var: Var) -> BoolExpr:
        return f"json_is_string({var})"

    def is_num(self, var: Var) -> BoolExpr:
        return f"json_is_number({var})"

    def is_flt(self, var: Var, loose: bool = False) -> BoolExpr:
        if loose:
            return self.is_num(var)
        else:
            return f"json_is_real({var})"

    def is_int(self, var: Var, loose: bool = False) -> BoolExpr:
        is_an_int = f"json_is_integer({var})"
        if loose:
            is_an_int = ("(" + is_an_int + " || " +
                               f"json_is_real({var}) && "
                               f"json_real_value({var}) == ((int) json_real_value({var})))")
        return is_an_int

    def is_bool(self, var: Var) -> BoolExpr:
        return f"json_is_boolean({var})"

    def is_null(self, var: Var) -> BoolExpr:
        return f"json_is_null({var})"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"_json_is_scalar({var})"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != NULL"

    def bool_cst(self, b: bool) -> BoolExpr:
        return "true" if b else "false"

    # FIXME path? reporting?
    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        val = var if is_str else f"json_string_value({var})"
        if name == "$UUID":
            return f"jm_is_valid_uuid({val})"
        elif name == "$DATE":
            return f"jm_is_valid_date({val})"
        elif name == "$REGEX":
            return f"jm_is_valid_regex({val})"
        elif name == "$URL":
            return f"jm_is_valid_url({val})"
        else:  # TODO $URL
            return super().predef(var, name, path, is_str)

    def _json_str(self, j) -> str:
        j = '"' + json.dumps(j).translate(self._json_esc_table) + '"'

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"json_loads({self._json_str(j)}, JSON_DECODE_ANY|JSON_ALLOW_NUL, NULL)"
    
    def bool_val(self, var: Var) -> BoolExpr:
        return f"json_boolean_value({var})"

    def int_val(self, var: Var) -> IntExpr:
        return f"json_integer_value({var})"

    def flt_val(self, var: Var) -> FloatExpr:
        return f"json_real_value({var})"

    def str_val(self, var: Var) -> StrExpr:
        return f"json_string_value({var})"

    def arr_item_val(self, arr: Var, idx: IntExpr) -> Expr:
        return f"json_array_get({arr}, {idx})"

    def obj_prop_val(self, obj: Var, prop: Var) -> Expr:
        return f"json_object_get({obj}, {prop})"

    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"json_object_size({var})"

    def arr_len(self, var: Var) -> IntExpr:
        return f"json_array_size({var})"

    def str_len(self, var: Var) -> IntExpr:
        return f"mbstowcs(NULL, {var}, 0)"

    def any_len(self, var: Var) -> IntExpr:
        return f"_any_len({var})"

    #
    # misc expressions
    #
    def ternary(self, cond: BoolExpr, true: Expr, false: Expr) -> Expr:
        return f"(({cond}) ? ({true}) : ({false}))"

    def prop_fun(self, fun: str, prop: str, name: str) -> Expr:
        return f"({fun} = {name}({prop}))"

    def check_call(self, fun: str, val: Expr, path: Var, is_str: bool = False) -> BoolExpr:
        if is_str:
            return f"jm_check_fun_string({fun}, {val}, {path}, rep)"
        else:
            return super().check_call(fun, val, path, is_str)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"jm_array_is_unique({val}, {path}, rep)"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        ...

    #
    # inline comparison expressions for strings
    # this is locale-unaware
    #
    def str_eq(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) == 0"

    def str_ne(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) != 0"

    def str_ge(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) >= 0"

    def str_gt(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) > 0"

    def str_le(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) <= 0"

    def str_lt(self, e1: StrExpr, e2: StrExpr) -> BoolExpr:
        return f"strcmp({e1}, {e2}) < 0"

    #
    # simple instructions
    #
    def nope(self) -> Inst:
        return None

    def  _var(self, var: Var, val: Expr|None, tname: str|None) -> Inst:
        assign = f" = {val}" if val else ""
        decl = f"{tname} " if tname else ""
        return f"{decl}{var}{assign}{self._eoi}"

    def fun_var(self, var: Var, val: BoolExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, "check_fun_t" if declare else None)

    def json_var(self, var: Var, val: JsonExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, "json_t *" if declare else None)

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, self._int if declare else None)

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"if (rep) jm_report_add_entry(rep, {self.esc(msg)}, {path});" ]
                if self._with_report else [])

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str, is_prop: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        if self._with_path:
            return (f"(Path) {{ {pseg}, 0, {pvar}, NULL }}" if is_prop else
                    f"(Path) {{ NULL, {pseg}, {pvar}, NULL }}")
        else:
            return None

    def path_var(self, pvar: Var, val: PathExpr|None = None, declare: bool = False) -> Inst:
        if self._with_path:
            assign = f" = {val}" if val else ""
            decl = "Path " if declare else ""
            return f"{decl}{pvar}{assign};"
        else:
            return None

    def path_lvar(self, lvar: Var, rvar: Var) -> Expr:
        return f"({rvar} ? &{lvar} : NULL)" if self._with_path else "NULL"

    #
    # blocks
    #
    def indent(self, block: Block, sep: bool = True) -> Block:
        indented = super().indent(block, sep)
        return ([ "{" ] + indented + [ "}" ]) if sep else indented

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [
            f"size_t {idx};",
            f"json_t *{val};",
            f"json_array_foreach({arr}, {idx}, {val})"
        ] + self.indent(body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [
            f"const char *{key};",
            f"json_t *{val};",
            f"json_object_foreach((json_t *) {obj}, {key}, {val})"
        ] + self.indent(body)

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = []) -> Block:
        if true and false:
            return [ f"if ({cond})" ] + self.indent(true) + ["else"] + self.indent(false)
        elif true:
            return [ f"if ({cond})" ] + self.indent(true)
        else:
            return [ f"if (!({cond}))" ] + self.indent(false)

    def mif_stmt(self, cond_true: list[tuple[BoolExpr, Block]], false: Block = []) -> Block:
        code, op = [], "if"
        for cond, true in cond_true:
            code += [ f"{op} ({cond})" ]
            code += self.indent(true)
            op = "else if"
        if false:
            if op != "if":
                code += [ "else" ]
                code += self.indent(false)
            else:
                code += false
        return code

    #
    # per-section/concept code generation
    #
    def def_re(self, name: str, regex: str) -> Block:
        return [
            f"static pcre2_code *{name}_code = NULL;",
            f"static pcre2_match_data *{name}_data = NULL;",
            f"static bool {name}(const char *s);"
        ]

    def sub_re(self, name: str, regex: str) -> Block:
        code = self.file_load("clang_pcre2_fun.c")
        return [ c.replace("FUNCTION_NAME", name) for c in code ]

    def ini_re(self, name: str, regex: str) -> Block:
        code = [] if self._re_used else [
            "int err_code;",
            "PCRE2_SIZE err_offset;",
            # FIXME strdup?
            "static PCRE2_UCHAR err_message[1024];",
        ]
        self._re_used = True
        code += [
            f"{name}_code = pcre2_compile((PCRE2_SPTR) {self.esc(regex)},"
             " PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);",
            f"if ({name}_code == NULL)",
            r"{",
            r"    (void) pcre2_get_error_message(err_code, err_message, 1024);",
            r"    return (char *) err_message;",
            r"}",
            f"{name}_data = pcre2_match_data_create_from_pattern({name}_code, NULL);"
        ]
        return code

    def del_re(self, name: str, regex: str) -> Block:
        return [
            f"pcre2_match_data_free({name}_data);",
            f"pcre2_code_free({name}_code);",
        ]

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        code = [ f"{'' if public else 'static '}propmap_t {name}_tab[{len(pmap)}];" ]
        if public:
            # add size accessor to public maps
            code += [ f"const size_t {name}_size = {len(pmap)};" ]
        return code

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        init = []
        for i, (p, f) in enumerate(pmap.items()):
            init += [ f"{name}_tab[{i}] = (propmap_t) {{ {self.esc(p)}, {f} }};" ]
        init += [ f"jm_sort_propmap({name}_tab, {len(pmap)});" ]
        return init

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [
            f"{'' if public else 'static '}check_fun_t {name}(const char *pname)",
            r"{",
            f"    return jm_search_propmap(pname, {name}_tab, {len(pmap)});",
            r"}",
        ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"static constant_t {name}[{len(constants)}];" ]

    def _var_cst(self, var: Var, vtype: type|None) -> Expr:
        if vtype is None or vtype == type(None):
            return "(constant_t) { cst_is_null, { .s = NULL } }"
        elif vtype is bool:
            return f"(constant_t) {{ cst_is_bool, {{ .b = {self.bool_val(var)} }} }}"
        elif vtype is int:
            return f"(constant_t) {{ cst_is_integer, {{ .i = {self.int_val(var)} }} }}"
        elif vtype is float:
            return f"(constant_t) {{ cst_is_float, {{ .f = {self.flt_val(var)} }} }}"
        elif vtype is str:
            return f"(constant_t) {{ cst_is_string, {{ .s = {self.str_val(var)} }} }}"
        else:
            raise NotImplementedError(f"type {vtype}")

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        """Tell whether JSON variable var value of potential types is in set name."""
        types = set(type(c) for c in constants)
        if len(types) != 1:
            raise NotImplementedError("multi type test")
        tcs = types.pop()
        val = self._var_cst(var, tcs)
        return f"{self.is_this_type(var, tcs)} && jm_search_cst(&{val}, {name}, {len(constants)});"

    def _cst(self, value: Jsonable) -> str:
        match value:
            case None:
                return "(constant_t) { cst_is_null, { .s = NULL } }"
            case bool(b):
                return f"(constant_t) {{ cst_is_bool, {{ .b = {self.bool_cst(b)} }} }}"
            case int(i):
                return f"(constant_t) {{ cst_is_integer, {{ .i = {i} }} }}"
            case float(f):
                return f"(constant_t) {{ cst_is_float, {{ .f = {f} }} }}"
            case str(s):
                return f"(constant_t) {{ cst_is_string, {{ .s = {self.esc(s)} }} }}"
            case _:
                raise Exception(f"unexpected constant value: {value}")

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        code = [ self.lcom("initialize sorted set {name}") ]
        for i, cst in enumerate(constants):
            code.append(f"{name}[{i}] = {self._cst(cst)};")
        code.append(f"jm_sort_cst({name}, {len(constants)});")
        return code

    def _fun(self, name: str) -> str:
        return  f"static bool {name}(const json_t* val, Path* path, Report* rep)"

    def def_fun(self, name: str) -> Block:
        return [ self._fun(name) + ";" ]

    def sub_fun(self, name: str, body: Block) -> Block:
        return [ self._fun(name) ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"static constmap_t {name}_tab[{len(mapping)}];" ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [
            f"static check_fun_t {name}(json_t *val)",
            r"{",
            r"    constant_t cst;",
            r"    jm_set_cst(&cst, val);",
            f"    return jm_search_constmap(&cst, {name}_tab, {len(mapping)});",
            r"}",
         ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        code = []
        for i, (k, v) in enumerate(list(mapping.items())):
            code += [ f"{name}_tab[{i}] = (constmap_t) {{ {self._cst(k)}, {v} }};" ]
        code += [ f"jm_sort_constmap({name}_tab, {len(mapping)});" ]
        return code

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}({tag})"

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("clang_init.c", ["jm_version_string = JSON_MODEL_VERSION;"] + init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("clang_free.c", free)
