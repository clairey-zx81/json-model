import json
from .language import Language, Block, Var, Inst, Block, PropMap
from .language import JsonExpr, BoolExpr, IntExpr, FloatExpr, NumExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable
from .utils import UUID_RE

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class CLangJansson(Language):
    """Generate JSON value checker in C with Jansson and PCRE2."""

    def __init__(self, *,
                 debug: bool = False,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 relib: str = "pcre2", int_t: str = "int64_t"):

        super().__init__("C",
                         with_path=with_path, with_report=with_report, with_comment=with_comment,
                         not_op="!", and_op="&&", or_op="||", lcom="//",
                         eoi=";", relib=relib, debug=debug)

        assert relib == "pcre2", f"only pcre2 is supported for now, not {relib}"

        self._int: str = int_t
        self._uuid_used: bool = False
        self._anylen_used: bool = False
        self._json_esc_table: str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self: str) -> Block:
        header = []
        if self._re_used:
            if self._relib == "pcre2":
                header += [ "#define PCRE2_CODE_UNIT_WIDTH 8" ]
            header += [ f"#include <{self._relib}.h>" ]
        header += [ f"#define JSON_MODEL_VERSION {self.esc(self._version)}" ]
        header += self.load_data("clang_header.c")
        if self._uuid_used:
            header += self.load_data("clang_uuid.c")
        if self._anylen_used:
            header += self.load_data("clang_anylen.c")
        return header

    def file_footer(self) -> Block:
        return ([""] + self.load_data("clang_entry.c") +
                [""] + self.load_data("clang_main.c"))

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

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != NULL"

    def bool_cst(self, b: bool) -> BoolExpr:
        return "true" if b else "false"

    # FIXME path
    def predef(self, var: Var, name: str, path: Var) -> BoolExpr:
        if name == "$UUID":
            self._uuid_used = True
            return f"_is_valid_uuid(json_string_value({var}))"
        # TODO $REGEX $DATE $URL
        else:
            return super().predef(name, path)

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
        self._anylen_used = True
        return f"_any_len({var})"

    #
    # ternary expression
    #
    def ternary(self, cond: BoolExpr, true: Expr, false: Expr) -> Expr:
        return f"(({cond}) ? ({true}) : ({false}))"

    def prop_fun(self, fun: str, prop: str, mapname: str, nprops: int) -> Expr:
        return f"({fun} = check_prop_find({prop}, {mapname}, {nprops}))"

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
        assign = f"= {val}" if val else ""
        decl = f"{tname} " if tname else ""
        return f"{decl}{var}{assign}{self._eoi}"

    def fun_var(self, var: Var, val: BoolExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, "check_fun_t" if declare else None)

    def json_var(self, var: Var, val: JsonExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, "json_t *" if declare else None)

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Inst:
        return self._var(var, val, self._int if declare else None)

    def report(self, msg: str, path: str) -> Block:
        return ([ f"if (rep) report_add_entry(rep, {self.esc(msg)}, {path});" ]
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
    def indent(self, block: Block) -> Block:
        return [ "{" ] + super().indent(block) + [ "}" ]

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

    def def_re(self, name: str, regex: str) -> Block:
        return [
            f"static pcre2_code *{name}_code = NULL;",
            f"static pcre2_match_data *{name}_data = NULL;",
            f"static bool {name}(const char *s);"
        ]

    def gen_re(self, name: str, regex: str) -> Block:
        code = self.load_data("clang_pcre2_fun.c")
        return [ c.replace("FUNCTION_NAME", name) for c in code ]

    def ini_re(self, name: str, regex: str) -> Block:
        code = [] if self._re_used else [
            "int err_code;",
            "PCRE2_SIZE err_offset;"
        ]
        self._re_used = True
        code += [
            f"{name}_code = pcre2_compile((PCRE2_SPTR) {self.esc(regex)},"
             " PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);",
            f"{name}_data = pcre2_match_data_create_from_pattern({name}_code, NULL);"
        ]
        return code

    def del_re(self, name: str, regex: str) -> Block:
        return [
            f"pcre2_match_data_free({name}_data);",
            f"pcre2_code_free({name}_code);",
        ]

    def def_map(self, name: str, size: int) -> Block:
        return [ f"static check_prop_t {name}[{size}];" ]

    def ini_map(self, name: str, pmap: PropMap) -> Block:
        init = []
        for i, pf in enumerate(pmap.items()):
            p, f = pf
            init += [ f"{name}[{i}] = (check_prop_t) {{ {self.esc(p)}, {f} }};" ]
        return init

    def _fun(self, name: str) -> str:
        return  f"static bool {name}(const json_t* val, Path* path, Report* rep)"

    def def_fun(self, name: str) -> Block:
        return [ self._fun(name) + ";" ]

    def gen_fun(self, name: str, body: Block) -> Block:
        return [ self._fun(name) ] + self.indent(body)

    # FIXME error reporting
    def gen_init(self, init: Block) -> Block:
        if self._uuid_used:
            init += self.init_re("_is_valid_uuid", UUID_RE)
        body = self.indent(self.if_stmt("!initialized", [ "initialized = true;" ] + init))
        return [ "void CHECK_FUNCTION_NAME_init(void)" ] + body

    def gen_free(self, free: Block) -> Block:
        body = self.indent(self.if_stmt("initialized", [ "initialized = false;" ] + free))
        return [ "void CHECK_FUNCTION_NAME_free(void)" ] + body
