import re
import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals
from .utils import log, partition

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

#
# Attempt at optimizing string equality tests with chuncked comparisons,
# avoiding a function call and a loop. It is unclear whether it is a good idea.
# See runtime/c/json-model.h for the generated macro definitions.
#
# TODO add max chunks?
# TODO generate likely/unlikely hints? likely on must, unlikely on may??
#
def _str_cmp_chunk(s: str, chunk: bytes, size: int,
                   little: bool = True, eq: bool = True) -> BoolExpr:
    """Generate a chunck of byte string comparison."""
    cmp_fun = "jm_str_eq" if eq else "jm_str_ne"
    assert 1 <= size <= 8, "valid number of bytes"
    if size == 1:
        return f"{cmp_fun}_1({s}, {hex(chunk[0])})" if chunk else f"{cmp_fun}_0({s})"
    else:
        x: str = ""
        for b in chunk:
            if little:
                x = hex(b)[2:] + x
            else:
                x += hex(b)[2:]
        # adjust to 4/8 byte boundary
        zeros = "00" * ((8 if size > 4 else 4) - len(x) // 2)
        x = "0x" + ((zeros + x) if little else (x + zeros)) + ("LL" if size > 4 else "")
        return f"{cmp_fun}_{size}({s}, {x})"

def _str_cmp(s: str, cst: str, little: bool = True, eq: bool = True, start: bool = False) -> BoolExpr:
    """Generate a fast byte string comparison for known constants."""
    bcst = json.loads(cst).encode("UTF8")
    remain = len(bcst) + (0 if start else 1)  # add implicit null termination
    # filter out multiple array calls
    if remain > 8 and ("json_array_get(" in s or "json_string_value(" in s):
        assert not start
        cmp_fun = "jm_str_eq" if eq else "jm_str_ne"
        return f"{cmp_fun}({s}, {cst})"
    # generate chuncked comparison expression
    index = 0
    expr = ""
    while remain > 0:
        if remain >= 8:
            size = 8
        elif remain > 4:
            size = remain % 8
        elif remain == 4:
            size = 4
        else:
            size = remain % 4
        ptr = s if index == 0 else f"{s} + {index}"
        if expr:
            expr += " && " if eq else " || "
        expr += _str_cmp_chunk(ptr, bcst[index:index+size], size, little, eq)
        index += size
        remain -= size
    return expr

class CLangJansson(Language):
    """Generate JSON value checker in C with Jansson and PCRE2.

    This implementation relies on inheritance for many methods, thanks to the root
    class heavy parameterization about operators, end-of-instruction and the like.
    """

    def __init__(self, *,
             debug: bool = False,
             with_path: bool = True, with_report: bool = True, with_comment: bool = True,
             with_predef: bool = True, strcmp_opt: bool = True, byte_order: str = "le",
             inline: bool = True, with_hints: bool = True, max_strcmp_cset: int = 64,
             partition_threshold: int = 32, relib: str = "pcre2", int_t: str = "int64_t"
        ):

        super().__init__(
            "C",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="NULL", check_t="jm_check_fun_t", json_t="json_t *",
             path_t="jm_path_t", float_t="double", str_t="const char *", hash_t="uint32_t",
             match_t="bool" if relib == "pcre2" else "int", with_hints=with_hints,
             eoi=";", relib=relib, debug=debug, with_predef=with_predef,
             set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert byte_order in ("le", "be"), f"expecting little (le) or big (be) endian: {byte_order}"
        assert relib in ("pcre2", "re2"), f"regex engine {relib} is not supported, try: pcre2/re2"

        # we keep 2 ints: "int64_t" and "int"
        self._int: str = int_t
        self._json_esc_table = str.maketrans(_ESC_TABLE)
        self._inline = "INLINE " if inline else ""
        self._strcmp_opt = strcmp_opt
        self._max_strcmp_cset = max_strcmp_cset
        # NOTE not necessary equal to the one in CodeGenerator
        self._partition_threshold = partition_threshold
        self._byte_order = byte_order

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
    def rep(self) -> str:
        return "rep" if self._with_report else "NULL"

    def path(self, p: str) -> str:
        return p if self._with_path else "NULL"

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
        # no content checks
        if not self._with_predef and self.str_content_predef(name):
            return self.const(True) if is_str else self.is_a(var, str)
        if name == "$UUID":
            return f"jm_is_valid_uuid({val}, {self.path(path)}, {self.rep()})"
        elif name == "$DATE":
            return f"jm_is_valid_date({val}, {self.path(path)}, {self.rep()})"
        elif name == "$TIME":
            return f"jm_is_valid_time({val}, {self.path(path)}, {self.rep()})"
        elif name == "$DATETIME":
            return f"jm_is_valid_datetime({val}, {self.path(path)}, {self.rep()})"
        elif name == "$REGEX":
            return f"jm_is_valid_regex({val}, false, {self.path(path)}, {self.rep()})"
        elif name == "$EXREG":
            return f"jm_is_valid_regex({val}, true, {self.path(path)}, {self.rep()})"
        elif name in ("$URL", "$URI"):
            return f"jm_is_valid_url({val}, {self.path(path)}, {self.rep()})"
        elif name == "$EMAIL":
            return f"jm_is_valid_email({val}, {self.path(path)}, {self.rep()})"
        elif name == "$JSON":
            return f"jm_is_valid_json({val}, {self.path(path)}, {self.rep()})"
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

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        return f"({dst} = {self.obj_prop_val(obj, prop, is_var)}) != NULL"

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

    def str_hash(self, val: Var, size: int = 1) -> IntExpr:
        if size == 1:
            return f"{val}[0]"
        if self._byte_order == "le":
            mask = "0x" + "00" * (size - 4) + "ff" * size
        else:
            mask = "0x" + "ff" * size + "00" * (size - 4)
        expr = f"*((uint32_t *) ({val}))"
        if size != 4:
            expr = f"({expr}) & {mask}"
        return f"({expr}) >> {8 * (size-4)}" if size != 4 and self._byte_order == "be" else expr

    #
    # misc expressions
    #
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"({fun} = {mapname}({prop}))"

    def str_start(self, val: str, start: str) -> BoolExpr:
        if self._strcmp_opt:
            try:
                return _str_cmp(val, json.dumps(start), self._byte_order == "le", True, True)
            except:  # if rejected, proceed with generic solution
                pass
        return f"strncmp({val}, {self.esc(start)}, strlen({self.esc(start)})) == 0"

    def str_end(self, val: str, end: str) -> BoolExpr:
        sstr = self.esc(end)
        return f"strlen({val}) >= strlen({sstr}) && " \
               f"strcmp({val} + strlen({val}) - strlen({sstr}), {sstr}) == 0"

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        if is_raw:
            return f"jm_check_fun_string({name}, {val}, {self.path(path)}, {self.rep()})"
        else:
            return super().check_call(name, val, path, is_ptr=is_ptr, is_raw=is_raw)  # type: ignore

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"jm_array_is_unique({val}, {self.path(path)}, {self.rep()})"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        """Call inefficient type-unaware constraint check."""
        OPS = {
            "!=": "op_ne", "=": "op_eq",
            "<=": "op_le", "<": "op_lt",
            ">=": "op_ge", ">": "op_gt"
        }
        return f"jm_check_constraint({val}, {OPS[op]}, &{self._cst(vop)}, {self.path(path)}, {self.rep()})"

    #
    # inline comparison expressions for strings
    # this is locale-unaware
    #
    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        assert op in ("=", "!=", "<", "<=", ">=", ">")
        if op == "=":
            if self._strcmp_opt and len(e2) >= 2 and e2[0] == '"' and e2[-1] == '"':
                return _str_cmp(e1, e2, self._byte_order == "le", True)
            else:
                return f"strcmp({e1}, {e2}) == 0"
        elif op == "!=":
            if self._strcmp_opt and len(e2) >= 2 and e2[0] == '"' and e2[-1] == '"':
                return "(" + _str_cmp(e1, e2, self._byte_order == "le", False) + ")"
            else:
                return f"strcmp({e1}, {e2}) != 0"
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

    def _var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        assign = f" = {val}" if val else ""
        decl = f"{tname} " if tname else ""
        return [ f"{decl}{var}{assign}{self._eoi}" ]

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        return self._var(var, val, self._int if declare else None)

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep != NULL" if self._with_report else "false"

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"if (rep) jm_report_add_entry(rep, {self.esc(msg)}, {self.path(path)});" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ "if (rep) jm_report_free_entries(rep);" ] if self._with_report else []

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        if self._with_path:
            sseg = pseg if is_var else self.esc(pseg) if is_prop else pseg
            return (f"(jm_path_t) {{ {sseg}, 0, {pvar}, NULL }}" if is_prop else
                    f"(jm_path_t) {{ NULL, {sseg}, {pvar}, NULL }}")
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

    def _hint(self, e: str, likely: TestHint) -> str:
        if self._with_hints and likely is not None:
            return f"likely({e})" if likely else f"unlikely({e})"
        else:
            return e

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:

        # handle expectation hints

        if true and false:
            return [ f"if ({self._hint(cond, likely)})" ] + self.indent(true) + ["else"] + self.indent(false)
        elif true:
            return [ f"if ({self._hint(cond, likely)})" ] + self.indent(true)
        else:
            return [ f"if (!({self._hint(cond, likely)}))" ] + self.indent(false)

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        code, op = [], "if"
        for cond, likely, true in cond_true:
            code += [ f"{op} ({self._hint(cond, likely)})" ]
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
        declare = "" if public else "static "
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

    #
    # CONSTANT SETS
    #
    # TODO other constants
    # TODO generalize to other types
    def _str_cset_opt(self, constants: ConstList) -> bool:
        return (len(constants) < self._max_strcmp_cset and
                all(map(lambda c: type(c) is str, constants)))

    def _def_str_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"static {self._inline}bool {name}_str_test(const char *);" ]

    def _part_expr(self, var: Var, part_code: dict[int, str]) -> str:
        nparts = len(part_code)
        if nparts == 1:
            return list(part_code.values())[0]
        elif nparts == 2:
            first, second = min(part_code.keys()), max(part_code.keys())
            return (f"({self.num_cmp(var, '<=', first, True)}) "
                    f"? (\n           {part_code[first]}        ) : (\n           {part_code[second]}        )")
        else:
            limit = list(sorted(part_code.keys()))[nparts // 2 - 1]
            return (
                f"({self.num_cmp(var, '<=', limit, True)})"
                f" ? (\n        {self._part_expr(var, {p: s for p, s in part_code.items() if p <= limit})})"
                f" : (\n        {self._part_expr(var, {p: s for p, s in part_code.items() if p > limit})})"
            )

    def _sub_str_cset(self, name: str, constants: ConstList) -> Block:
        code = [
            f"static {self._inline}bool {name}_str_test(const char *s)",
            "{",
        ]

        names = set(constants)
        partitioning = partition(names, self._partition_threshold, self._byte_order)
        if partitioning is not None:
            hash_size, partitions = partitioning
            code.append(self._indent +
                        self.hash_var("hash", self.str_hash("s", hash_size), declare=True)[0])
        else:
            hash_size, partitions = 0, {0: names}

        part_code = {
            p: "        || ".join(
                (_str_cmp("s", json.dumps(s), self._byte_order, True) + f"  // {self.esc(s)}\n")
                    for s in sorted(strs, key=lambda s: (len(s), s)))
                        for p, strs in partitions.items()
        }

        code += [
            "    return",
            "           " + self._part_expr("hash", part_code),
            "    ;",
            "}"
        ]
        return code

    def _in_str_cset(self, name: str, var: str, constants: ConstList) -> BoolExpr:
        return f"{self.is_a(var, str)} && {name}_str_test(json_string_value({var}))"

    def def_cset(self, name: str, constants: ConstList) -> Block:
        if self._str_cset_opt(constants):
            return self._def_str_cset(name, constants)
        types = set(type(c) for c in constants)
        code = []
        if len(types) > 1:
            code += [ f"static bool {name}_test(const json_t *);" ]
        return  code + [ f"static jm_constant_t {name}[{len(constants)}];" ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        if self._str_cset_opt(constants):
            return self._sub_str_cset(name, constants)
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
            return f"(jm_constant_t) {{ strlen({self.value(var, str)}) + 1, {{ .s = {self.value(var, str)} }} }}"
        else:
            raise NotImplementedError(f"type {vtype}")

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        """Tell whether JSON variable var value of potential types is in set name."""
        if self._str_cset_opt(constants):
            return self._in_str_cset(name, var, constants)
        types = set(type(c) for c in constants)
        if len(types) == 1:
            tcs = types.pop()
            val = self._var_cst(var, tcs)
            return f"{self.is_a(var, tcs)} && jm_search_cst(&{val}, {name}, {len(constants)})"
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
                bs = s.encode("UTF-8")
                return f"(jm_constant_t) {{ {len(bs) + 1}, {{ .s = {self.esc(s)} }} }}"
            case _:
                raise Exception(f"unexpected constant value: {value}")

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        if self._str_cset_opt(constants):
            return []
        code = self.lcom(f"initialize sorted set {name}")
        for i, cst in enumerate(constants):
            code.append(f"{name}[{i}] = {self._cst(cst)};")
        code.append(f"jm_sort_cst({name}, {len(constants)});")
        return code

    def del_cset(self, name: str, constants: ConstList) -> Block:
        return []

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

    def filter_code(self, code: Block) -> Block:

        for i in range(len(code)):
            line = code[i]
            if line is None:
                continue
            # remove redundant checks generated in some cases
            if "jm_json_is_scalar" in line:
                line = re.sub(r" jm_json_is_scalar\((\w+)\) && json_is_string\(\1\)",
                              r" json_is_string(\1)", line)
                code[i] = line
            if "json_is_boolean" in line:
                line = re.sub(r" json_is_boolean\((\w+)\) && json_is_boolean\(\1\)",
                              r" json_is_boolean(\1)", line)
                code[i] = line
            # remove useless braces around one instruction in some safe cases
            if re.match(r"^ +\{$", line):
                ninst, n, opened = 0, 0, 1
                while True:
                    n += 1
                    nline = code[i+n]
                    if nline is None or re.match(r"^ *$", nline) or re.match(r"^ *//", nline):
                        continue
                    if re.match(r"^ +\{$", nline):
                        opened += 1
                    elif re.match(r"^ +\}$", nline):
                        opened -= 1
                        if opened == 0:
                            break
                    elif " if (" in nline:
                        # keep braces around nested ifs
                        ninst = -1
                        break
                    else:
                        # note this is intentionnaly pessimistic
                        ninst += 1
                if ninst == 1:
                    # log.warning(code[i:i+n+1])
                    code[i], code[i+n] = None, None

        return list(filter(lambda s: s is not None, code))
