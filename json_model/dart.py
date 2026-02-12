import json
from .language import Language, Block, StrExpr, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals

_ESC_TABLE = { '"': r'\"', "\\": "\\\\", "$": r"\$" }

class Dart(Language):
    """Dart Code Generator."""

    def __init__(self, *,
                 debug: bool = False, relib: str = "re", with_predef: bool = True,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True):

        super().__init__(
            "Dart",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             with_predef=with_predef, not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="null", relib=relib,
             check_t="dynamic", json_t="dynamic", int_t="int", float_t="double",
             path_t="List<dynamic>?", str_t="String", match_t="bool",
             eoi=";", set_caps=(type(None), bool, int, float, str)) 

        self._json_esc_table = str.maketrans(_ESC_TABLE)

    # 
    # simple instructions
    # 
    def esc(self, s: str) -> StrExpr:
        """Escape string, with double quotes."""
        # log.warning(f"esc: {s}")
        if isinstance(s, bool):
            s = "true" if s else "false"
        s = str.translate(s, self._json_esc_table)
        return '"' + s + '"'

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code:Block = super().file_header(exe)
        code += self.file_load("dart_head.dart")
        code += [ f'const String JSON_MODEL_VERSION = "{self.version()}";' ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        code: Block = self.file_load("dart_foot.dart")
        if exe:
            code += [""] + self.file_load("dart_main.dart")
        return code

    #
    # inlined type test expressions about JSON data
    #
    def rep(self) -> str:
        return "rep" if self._with_report else "null"

    def path(self, p: str) -> str:
        return p if self._with_path else "null"

    def is_num(self, var: Var) -> BoolExpr:
        return f"({var} is num)"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"({var} == null || {var} is num || {var} is bool || {var} is String)"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != null"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"{var} == null"
        elif tval is bool:
            return f"({var} is bool)"
        elif tval is int:
            if loose : return f"({var} is int || ({var} is double && {var} == {var}.toInt()))"
            return f"({var} is int)"
        elif tval is float:
            if loose : return f"({var} is int || {var} is double)"
            return f"({var} is double)" 
        elif tval is Number:
            return f"({var} is num)"
        elif tval is str:
            return f"({var} is String)"
        elif tval is list:
            return f"({var} is List)"
        elif tval is dict:
            return f"({var} is Map)"
        else:
            raise Exception(f"unexpected type for json: {tval.__name__}")

    def _json_str(self, j) -> str:
        return '"' + json.dumps(j).translate(self._json_esc_table) + '"'

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"jsonDecode({self._json_str(j)})"

    def const(self, c: Jsonable) -> Expr:
        if isinstance(c, (list, dict)):
            return self.json_cst(c)
        else:
            return super().const(c)

    def obj_prop_val(self, obj: Var, prop: str, is_var: bool = False) -> JsonExpr:
        return f"{obj}[{prop}]" if is_var else f"{obj}[{self.esc(prop)}]" 

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"{obj}.containsKey({self.esc(prop)})"

    def assign_obj_prop(self) -> bool:
        return False

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        if not self._with_predef and self.str_content_predef(name):
            return self.true() if is_str else self.is_a(var, str)
        val = var
        if name == "$UUID":
            return f"runtime.jm_is_valid_uuid({val})"
        elif name == "$DATE":
            return f"runtime.jm_is_valid_date({val}, {self.path(path)}, {self.rep()})"
        elif name == "$TIME":
            return f"runtime.jm_is_valid_time({val}, {self.path(path)}, {self.rep()})"
        elif name == "$DATETIME":
            return f"runtime.jm_is_valid_datetime({val}, {self.path(path)}, {self.rep()})"
        elif name == "$REGEX":
            return f"runtime.jm_is_valid_regex({val}, false)"
        elif name == "$EXREG":
            return f"runtime.jm_is_valid_regex({val}, true)"
        elif name in ("$URL", "$URI"):
            return f"runtime.jm_is_valid_url({val})"
        elif name == "$EMAIL":
            return f"runtime.jm_is_valid_email({val})"
        elif name == "$JSON":
            return f"runtime.jm_is_valid_json({val})"
        else:
            return super().predef(var, name, path, is_str)
    
    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"{var}.length"

    def arr_len(self, var: Var) -> IntExpr:
        return f"{var}.length"

    def str_len(self, var: Var) -> IntExpr:
        return f"{var}.length"

    def any_len(self, var: Var) -> IntExpr:
        return f"runtime.jm_any_len({var})"

    #
    # misc expressions
    #
    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        """String comparison."""
        expr_str = f"{e1}.compareTo({e2})"
        return self.num_cmp(expr_str, op, 0)
    
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> JsonExpr:
        # Not checking if fun is null but generally followed by is_def checking  
        return f"({fun} = {mapname}[{prop}]) != null"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"{val}.startsWith({self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"{val}.endsWith({self.esc(end)})"

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"runtime.jm_array_is_unique({val}, {self.path(path)}, {self.rep()})"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return f"runtime.jm_check_constraint({val}, {self.esc(op)}, {self.const(vop)}, {self.path(path)}, {self.rep()})"

    def nope(self) -> Block:
        return []

    def _var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        assign = f" = {val}" if val else ""
        typevar = f"{tname} " if tname else ""
        return [ f"{typevar}{var}{assign}{self._eoi}" ]

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep != null"

    def report(self, msg: str, path: Var) -> Block:
        # Matches: rep?.add(["msg", path]);
        return ([ f"rep?.add([{self.esc(msg)}, {self.path(path)}]);" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ "rep?.clear();" ]

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        # Matches: (path != null ? [...path, prop] : null)
        sseg = pseg if is_var else self.esc(pseg) if is_prop else pseg
        if self._with_path:
             return f"({pvar} != null ? [...?{pvar}, {sseg}] : null)"
        return "null"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return f"({rvar} != null ? {lvar} : null)" if self._with_path else "null"

    #
    # blocks
    #
    def indent(self, block: Block, sep: bool = True) -> Block:
        indented = super().indent(block, sep)
        return ([ "{" ] + indented + [ "}" ]) if sep else indented

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"for (var {idx} = {start}; {idx} < {end}; {idx}++)"
        ] + self.indent(body)

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return self.int_loop(idx, "0", f"{arr}.length", [ f"var {val} = {arr}[{idx}];" ] + body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        # Matches: for (var entry in val.entries) { var prop = entry.key; ... }
        return [
            f"for (var entry in {obj}.entries)"
        ] + self.indent([f"var {key} = entry.key;", f"var {val} = entry.value;"] + body)

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        if true and false:
            return [ f"if ({cond})" ] + self.indent(true) + ["else"] + self.indent(false)
        elif true:
            return [ f"if ({cond})" ] + self.indent(true)
        else:
            return [ f"if (! ({cond}))" ] + self.indent(false)

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        code, op = [], "if"
        for cond, likely, true in cond_true:
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
    def def_re(self, name: str, regex: str, opts: str) -> Block:
        case_sensitive = "false" if "i" in opts else "true"
        multi_line = "true" if "m" in opts else "false"
        return [ f"final {name}_re = RegExp({self.esc(regex)}, caseSensitive: {case_sensitive}, multiLine: {multi_line});" ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        # second and thir agument not needed but mandatory to match function call 
        return [ f"bool {name}(String s, List<dynamic>? path, List<dynamic>? rep) => {name}_re.hasMatch(s);" ]

    def match_var(self, var: str, val: Expr|None = None, declare: bool = False) -> Block:
        return self._var(var, val, "RegExpMatch?")

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        return self._var(var, val, "String?")

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"{name}_re.firstMatch({var})"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        return [ f"{dname} = {mname}?.namedGroup({self.esc(sname)});" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ f"bool {name}(dynamic val, List<dynamic>? path, List<dynamic>? rep)" ] + self.indent(body)

    #
    # Property Map
    #
    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        # Matches: var check_model_map = <String, Function>{};
        return [ f"var {name} = <String, Function>{{}};" ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        # Matches: check_model_map[""] = json_model_1;
        return [ f"{name}[{self.esc(p)}] = {f};" for p, f in pmap.items() ]

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return []

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"var {name} = <dynamic>{{}};" ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        return []

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return f"{name}.contains({var})"

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"{name}.add({self.const(v)});" for v in constants ]

    def def_fun(self, name: str) -> Block:
        return []

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        # Note: Changed from 'void' to 'bool' to support validation return logic
        return [ f"bool {name}(dynamic val, List<dynamic>? path, List<dynamic>? rep)" ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"var {name} = Map();" ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"{name}[{self.const(k)}] = {m};" for k, m in mapping.items() ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}[{tag}]"

    def gen_init(self, init: Block) -> Block:
        # Injects code into jm_init
        return self.file_subs("dart_init.dart", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("dart_free.dart", free)