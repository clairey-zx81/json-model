import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class CLangJansson(Language):
    """Generate JSON value checker in C with Jansson and PCRE2.

    This implementation relies on inheritance for many methods, thanks to the root
    class heavy parameterization about operators, end-of-instruction and the like.
    """

    def __init__(self, *,
                 debug: bool = False,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 inline: bool = True, relib: str = "pcre2", int_t: str = "int64_t"):

        super().__init__(
            "C",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="NULL", check_t="jm_check_fun_t", json_t="json_t *",
             path_t="jm_path_t", float_t="double", str_t="char *",
             match_t="bool" if relib == "pcre2" else "int",
             eoi=";", relib=relib, debug=debug,
             set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert relib in ("pcre2", "re2"), f"regex engine {relib} is not supported, try: pcre2/re2"

        # we keep 2 ints: "int64_t" and "int"
        self._int: str = int_t
        self._json_esc_table = str.maketrans(_ESC_TABLE)
        self._inline = "INLINE " if inline else ""

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code: Block = super().file_header(exe)
        code += [ "", "// regular expression engine" ]
        if self._relib == "pcre2":
            code += [
                "#define PCRE2_CODE_UNIT_WIDTH 8",
                "#include <pcre2.h>",
            ]
        else:
            code += [
                "#include <stddef.h>",
                "#include <cre2.h>",
            ]
        code += [
            "",
            r"#include <json-model.h>",
            f"#define JSON_MODEL_VERSION {self.esc(self.version())}"
        ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        return [""] + self.file_load("clang_entry.c")

    #
    # inlined type test expressions about JSON data
    #
    def is_num(self, var: Var) -> BoolExpr:
        return f"json_is_number({var})"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"jm_json_is_scalar({var})"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != NULL"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"json_is_null({var})"
        elif tval is bool:
            return f"json_is_boolean({var})"
        elif tval is int:
            is_an_int = f"json_is_integer({var})"
            if loose:
                is_an_int = (
                    "(" + is_an_int + " || " +
                    f"(json_is_real({var}) && "
                        f"json_real_value({var}) == (({self._int}) json_real_value({var}))))")
            return is_an_int
        elif tval is float:
            return self.is_num(var) if loose else f"json_is_real({var})"
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            return f"json_is_string({var})"
        elif tval is list:
            return f"json_is_array({var})"
        elif tval is dict:
            return f"json_is_object({var})"
        else:
            raise Exception(f"unexpected type for json: {tval.__name__}")

    def _json_str(self, j) -> str:
        return '"' + json.dumps(j).translate(self._json_esc_table) + '"'

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"json_loads({self._json_str(j)}, JSON_DECODE_ANY|JSON_ALLOW_NUL, NULL)"

    def const(self, c: Jsonable) -> Expr:
        if isinstance(c, (list, dict)):
            return self.json_cst(c)
        else:
            return super().const(c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"json_object_get({obj}, {self.esc(prop)}) != NULL"

    # FIXME path? reporting?
    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        val = var if is_str else f"json_string_value({var})"
        if name == "$UUID":
            return f"jm_is_valid_uuid({val}, {path}, rep)"
        elif name == "$DATE":
            return f"jm_is_valid_date({val}, {path}, rep)"
        elif name == "$TIME":
            return f"jm_is_valid_time({val}, {path}, rep)"
        elif name == "$DATETIME":
            return f"jm_is_valid_datetime({val}, {path}, rep)"
        elif name == "$REGEX":
            return f"jm_is_valid_regex({val}, false, {path}, rep)"
        elif name == "$EXREG":
            return f"jm_is_valid_regex({val}, true, {path}, rep)"
        elif name in ("$URL", "$URI"):
            return f"jm_is_valid_url({val}, {path}, rep)"
        elif name == "$EMAIL":
            return f"jm_is_valid_email({val}, {path}, rep)"
        elif name == "$JSON":
            return f"jm_is_valid_json({val}, {path}, rep)"
        else:
            return super().predef(var, name, path, is_str)
    
    def value(self, var: Var, tvar: type) -> Expr:
        """Known type value extraction."""
        if tvar is type(None):
            return "NULL"
        elif tvar is bool:
            return f"json_boolean_value({var})"
        elif tvar is int:
            return f"json_integer_value({var})"
        elif tvar is float:
            return f"json_real_value({var})"
        elif tvar is Number:  # NOTE this cast from int if necessary
            return f"json_number_value({var})"
        elif tvar is str:
            return f"json_string_value({var})"
        else:
            raise Exception(f"unexpected type for value extraction: {tvar.__name__}")

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return f"json_array_get({arr}, {idx})"

    def obj_prop_val(self, obj: Var, prop: Expr, is_var: bool = False) -> JsonExpr:
        return f"json_object_get({obj}, {prop})" if is_var else \
               f"json_object_get({obj}, {self.esc(prop)})"  # type: ignore

    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"json_object_size({var})"

    def arr_len(self, var: Var) -> IntExpr:
        return f"json_array_size({var})"

    def str_len(self, var: Var) -> IntExpr:
        return f"jm_str_len({var})"

    def any_len(self, var: Var) -> IntExpr:
        return f"_any_len({var})"

    #
    # misc expressions
    #
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"({fun} = {mapname}({prop}))"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"strncmp({val}, {self.esc(start)}, strlen({self.esc(start)})) == 0"

    def str_end(self, val: str, end: str) -> BoolExpr:
        sstr = self.esc(end)
        return f"strlen({val}) >= strlen({sstr}) && " \
               f"strcmp({val} + strlen({val}) - strlen({sstr}), {sstr}) == 0"

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        if is_raw:
            return f"jm_check_fun_string({name}, {val}, {path}, rep)"
        else:
            return super().check_call(name, val, path, is_ptr=is_ptr, is_raw=is_raw)  # type: ignore

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"jm_array_is_unique({val}, {path}, rep)"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        """Call inefficient type-unaware constraint check."""
        OPS = {
            "!=": "op_ne", "=": "op_eq",
            "<=": "op_le", "<": "op_lt",
            ">=": "op_ge", ">": "op_gt"
        }
        return f"jm_check_constraint({val}, {OPS[op]}, &{self._cst(vop)}, {path}, rep)"

    #
    # inline comparison expressions for strings
    # this is locale-unaware
    #
    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        assert op in ("=", "!=", "<", "<=", ">=", ">")
        if op == "=":
            return f"strcmp({e1}, {e2}) == 0"
        elif op == "!=":
            return f"strcmp({e1}, {e2}) != 0"
        elif op == ">=":
            return f"strcmp({e1}, {e2}) >= 0"
        elif op == ">":
            return f"strcmp({e1}, {e2}) > 0"
        elif op == "<=":
            return f"strcmp({e1}, {e2}) <= 0"
        elif op == "<":
            return f"strcmp({e1}, {e2}) < 0"
        else:
            raise Exception(f"str_cmp unexpected operator {op}")

    #
    # simple instructions
    #
    def nope(self) -> Block:
        return []

    def var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        assign = f" = {val}" if val else ""
        decl = f"{tname} " if tname else ""
        return [ f"{decl}{var}{assign}{self._eoi}" ]

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        return self.var(var, val, self._int if declare else None)

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep != NULL"

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"if (rep) jm_report_add_entry(rep, {self.esc(msg)}, {path});" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ "if (rep) jm_report_free_entries(rep);" ] if self._with_report else []

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        if self._with_path:
            return (f"(jm_path_t) {{ {pseg}, 0, {pvar}, NULL }}" if is_prop else
                    f"(jm_path_t) {{ NULL, {pseg}, {pvar}, NULL }}")
        else:
            return "NULL"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
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

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"for ({self._int} {idx} = {start}; {idx} < {end}; {idx}++)"
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
    # (Extended) Regular Expressions
    #
    def regroup(self, name: str, pattern: str = ".*") -> str:
        return f"(?P<{name}>{pattern})" if self._relib == "re2" else super().regroup(name, pattern)

    def def_re(self, name: str, regex: str, opts: str) -> Block:
        if self._relib == "pcre2":
            return [
                f"static pcre2_code *{name}_code = NULL;",
                f"static pcre2_match_data *{name}_data = NULL;",
                f"static bool {name}(const char *s, jm_path_t *path, jm_report_t *rep);",
            ]
        else:
            return [
                f"static cre2_regexp_t *{name}_re2 = NULL;",
                f"static int {name}_nn = 0;",
                f"static bool {name}(const char *s, jm_path_t *path, jm_report_t *rep);",
            ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        code = self.file_load(f"clang_{self._relib}_fun.c")
        return [ c.replace("FUNCTION_NAME", name) for c in code ]

    def ini_re(self, name: str, regex: str, opts: str) -> Block:
        # declare once
        code = [] if self._re_used or self._relib != "pcre2" else [
            "int err_code;",
            "PCRE2_SIZE err_offset;",
            "static PCRE2_UCHAR err_message[1024];",
        ]
        self._re_used = True
        sregex = self.esc((f"(?{opts})" if opts else "") + regex)
        if self._relib == "pcre2":
            code += [
                f"{name}_code = pcre2_compile((PCRE2_SPTR) {sregex},"
                 " PCRE2_ZERO_TERMINATED, PCRE2_UCP|PCRE2_UTF, &err_code, &err_offset, NULL);",
                f"if ({name}_code == NULL)",
                r"{",
                r"    (void) pcre2_get_error_message(err_code, err_message, 1024);",
                r"    return (const char *) err_message;",
                r"}",
                f"{name}_data = pcre2_match_data_create_from_pattern({name}_code, NULL);"
            ]
        else:
            code += [
                f"{name}_re2 = cre2_new({sregex}, strlen({sregex}), NULL);",
                f"if (cre2_error_code({name}_re2))",
                f"    return cre2_error_string({name}_re2);",
                f"{name}_nn = cre2_num_capturing_groups({name}_re2) + 1;",  # why?
            ]
        return code

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        if self._relib == "pcre2":
            return [
                f"pcre2_match_data_free({name}_data);",
                f"pcre2_code_free({name}_code);",
            ]
        else:
            return [
                f"cre2_delete({name}_re2);",
                f"{name}_re2 = NULL;",
                f"{name}_nn = 0;",
            ]

    # TODO add rname
    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        assert declare
        if self._relib == "pcre2":
            return [
                f"const PCRE2_SIZE {var}_size = strlen({val});",
                f"char {var}[{var}_size];",
                f"PCRE2_SIZE {var}_len;",
                r"int rc;"
            ]
        else:  # var is dname
            return [
                f"size_t {var}_size = strlen({val}) + 1;",
                f"char {var}[{var}_size];",
                r"int match_index;",
                f"cre2_string_t matches[{rname}_nn];",
            ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        if self._relib == "pcre2":
            return f"pcre2_match({name}_code, (PCRE2_SPTR) {var}, PCRE2_ZERO_TERMINATED," \
                   f" 0, 0, {name}_data, NULL) != 0"
        else:
            return f"cre2_match({name}_re2, {var}, strlen({var}), 0, strlen({var}), " \
                   f"CRE2_UNANCHORED, matches, {name}_nn) != 0"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        if self._relib == "pcre2":
            return [
                f"{dname}_len = {dname}_size;",
                f"rc = pcre2_substring_copy_byname({rname}_data, (PCRE2_SPTR) {self.esc(sname)}," \
                f" (PCRE2_UCHAR *) {dname}, &{dname}_len);",
                r"if (rc != 0)",
                r"    return false;",
            ]
        else:
            return [
                f"match_index = cre2_find_named_capturing_groups({rname}_re2, {self.esc(sname)});",
                f"strncpy({dname}, matches[match_index].data, matches[match_index].length);",
                f"{dname}[matches[match_index].length] = '\\0';",
            ]

    def def_strfun(self, name: str) -> Block:
        return [ f"static {self._inline}bool {name}(const char *, jm_path_t *, jm_report_t *);" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ f"static {self._inline}bool {name}(const char *val, jm_path_t *path, jm_report_t *rep)" ] + \
                    self.indent(body)

    #
    # Property Map
    #
    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        declare = "" if public else f"static "
        code = [ f"{declare}jm_propmap_t {name}_tab[{len(pmap)}];" ]
        if public:
            # add size accessor to public maps
            code += [ f"const size_t {name}_size = {len(pmap)};" ]
        return code

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        init = []
        for i, (p, f) in enumerate(pmap.items()):
            init += [ f"{name}_tab[{i}] = (jm_propmap_t) {{ {self.esc(p)}, {f} }};" ]
        init += [ f"jm_sort_propmap({name}_tab, {len(pmap)});" ]
        return init

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        declare = "" if public else f"static {self._inline}"
        return [
            f"{declare}jm_check_fun_t {name}(const char *pname)",
            r"{",
            f"    return jm_search_propmap(pname, {name}_tab, {len(pmap)});",
            r"}",
        ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        types = set(type(c) for c in constants)
        code = []
        if len(types) > 1:
            code += [ f"static bool {name}_test(const json_t *);" ]
        return  code + [ f"static jm_constant_t {name}[{len(constants)}];" ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        types = set(type(c) for c in constants)
        code = []
        if len(types) > 1:
            code += [
                f"static {self._inline}bool {name}_test(const json_t *val)",
                r"{",
                r"  jm_constant_t cst;",
                r"  jm_set_cst(&cst, val);",
                f"  return jm_search_cst(&cst, {name}, {len(constants)});",
                r"}"
            ]
        return code

    def _var_cst(self, var: Var, vtype: type|None) -> Expr:
        if vtype is None or vtype is type(None):
            return "(jm_constant_t) { cst_is_null, { .s = NULL } }"
        elif vtype is bool:
            return f"(jm_constant_t) {{ cst_is_bool, {{ .b = {self.value(var, bool)} }} }}"
        elif vtype is int:
            return f"(jm_constant_t) {{ cst_is_integer, {{ .i = {self.value(var, int)} }} }}"
        elif vtype is float:
            return f"(jm_constant_t) {{ cst_is_float, {{ .f = {self.value(var, float)} }} }}"
        elif vtype is str:
            return f"(jm_constant_t) {{ cst_is_string, {{ .s = {self.value(var, str)} }} }}"
        else:
            raise NotImplementedError(f"type {vtype}")

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        """Tell whether JSON variable var value of potential types is in set name."""
        types = set(type(c) for c in constants)
        if len(types) == 1:
            tcs = types.pop()
            val = self._var_cst(var, tcs)
            return f"{self.is_a(var, tcs)} && jm_search_cst(&{val}, {name}, {len(constants)});"
        else:  # multi type managed in a generated function
            return f"{name}_test({var})"

    def _cst(self, value: Jsonable) -> str:
        match value:
            case None:
                return "(jm_constant_t) { cst_is_null, { .s = NULL } }"
            case bool(b):
                return f"(jm_constant_t) {{ cst_is_bool, {{ .b = {self.const(b)} }} }}"
            case int(i):
                return f"(jm_constant_t) {{ cst_is_integer, {{ .i = {i} }} }}"
            case float(f):
                return f"(jm_constant_t) {{ cst_is_float, {{ .f = {f} }} }}"
            case str(s):
                return f"(jm_constant_t) {{ cst_is_string, {{ .s = {self.esc(s)} }} }}"
            case _:
                raise Exception(f"unexpected constant value: {value}")

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        code = self.lcom(f"initialize sorted set {name}")
        for i, cst in enumerate(constants):
            code.append(f"{name}[{i}] = {self._cst(cst)};")
        code.append(f"jm_sort_cst({name}, {len(constants)});")
        return code

    def _fun(self, name: str, inline: bool = False) -> str:
        declare = f"static {self._inline}" if inline else "static "
        return  f"{declare}bool {name}(const json_t *val, jm_path_t *path, jm_report_t *rep)"

    def def_fun(self, name: str) -> Block:
        return [ self._fun(name, False) + ";" ]

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ self._fun(name, inline) ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"static jm_constmap_t {name}_tab[{len(mapping)}];" ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [
            f"static {self._inline}jm_check_fun_t {name}(json_t *val)",
            r"{",
            r"    jm_constant_t cst;",
            r"    jm_set_cst(&cst, val);",
            f"    return jm_search_constmap(&cst, {name}_tab, {len(mapping)});",
            r"}",
         ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        code = []
        for i, (k, v) in enumerate(list(mapping.items())):
            code += [ f"{name}_tab[{i}] = (jm_constmap_t) {{ {self._cst(k)}, {v} }};" ]
        code += [ f"jm_sort_constmap({name}_tab, {len(mapping)});" ]
        return code

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}({tag})"

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("clang_init.c", ["jm_version_string = JSON_MODEL_VERSION;"] + init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("clang_free.c", free)
