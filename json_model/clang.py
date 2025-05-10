import json
from .language import Language, Block, Var, Inst, Block
from .language import JsonExpr, BoolExpr, IntExpr, FloatExpr, NumExpr, StrExpr, Expr
from .mtypes import Jsonable

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class CLangJansson(Language):
    """Generate JSON value checker in C with Jansson."""

    def __init__(self, *, debug: bool = False, relib: str = "pcre2"):
        super().__init__("C", not_op="!", and_op="&&", or_op="||", relib=relib,
                         lcom="//", eoi=";", indent="  ", debug=debug)

        self._with_re: bool = False
        self._with_props: bool = False
        self._json_esc_table: str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self) -> Block:
        header = []
        if self._with_re:
            header += [ f"#include <{self._relib}.h>" ]
        header += self.load_data("clang_header.c")
        if self._with_props:
            header += [""] + self._load_data("clang_props.c")
        return header

    def file_footer(self) -> Block:
        return [""] + self.load_data("clang_main.c")

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

    def bool_cst(self, b: bool) -> BoolExpr:
        return "true" if b else "false"

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
        return f"mbstowcs({var}, NULL, 0)"

    def any_len(self, var: Var) -> IntExpr:
        return f"FIXME len({var})"

    #
    # ternary expression
    #
    def ternary(self, cond: BoolExpr, true: Expr, false: Expr) -> Expr:
        return f"(({cond}) ? ({true}) : ({false}))"

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
    def decl_json_var(self, var: Var) -> Inst:
        return f"json_t *{var};"

    def decl_bool_var(self, var: Var) -> Inst:
        return f"bool {var};"

    def decl_json_var_val(self, var: Var, expr: Expr) -> Inst:
        return f"json_t *{var} = {expr};"

    def decl_bool_var_val(self, var: Var, expr: BoolExpr) -> Inst:
        return f"bool {var} = {expr};"

    def report(self, msg: str) -> Block:
        return [ f"if (rep) /* {msg} */;" ]

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
            f"json_object_foreach({obj}, {key}, {val})"
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

    def _fun(self, name: str, local: bool = False) -> str:
        return  f"{'static ' if local else ''}bool {name}(json_t *val, Path *path, Report *rep)"

    def decl_fun(self, name: str, local: bool = False) -> Block:
        return [ self._fun(name, local) + ";" ]

    def gen_fun(self, name: str, body: Block, local: bool = False) -> Block:
        if not local:  # entry points must check for module initialization
            body = [ "initialize();" ] + body
        return [ self._fun(name, local) ] + self.indent(body)

    def gen_init(self, init: Block) -> Block:
        body = self.indent(self.if_stmt("!initialized", [ "initialized = true;" ] + init))
        return [ "static void initialize(void)" ] + body
