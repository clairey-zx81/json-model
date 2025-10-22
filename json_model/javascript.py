import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class JavaScript(Language):
    """JavaScript Code Generator."""

    def __init__(self, *,
                 debug: bool = False, relib: str = "re", with_predef: bool = True,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True):

        super().__init__(
            "JS",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             with_predef=with_predef, not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="null", relib=relib,
             check_t="object", json_t="object", int_t="Number", float_t="Number",
             path_t="?", str_t="String", match_t="bool",
             eoi=";", set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert self._relib in ("re", "re2"), f"unsupported regex engine: {self._relib}"

        self._json_esc_table = str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code: Block = self.file_load("javascript_exe.js") if exe else []
        code += super().file_header(exe)
        code += self.file_load("javascript_head.js")
        code += [ f"const JSON_MODEL_VERSION = {self.esc(self.version())};" ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        code: Block = self.file_load("javascript_foot.js")
        if exe:
            code += [""] + self.file_load("javascript_main.js")
        return code

    #
    # inlined type test expressions about JSON data
    #
    def rep(self) -> str:
        return "rep" if self._with_report else "null"

    def path(self, p: str) -> str:
        return p if self._with_path else "null"

    def is_num(self, var: Var) -> BoolExpr:
        # JS === BF
        # 12.5 instanceof Number === false
        # Number(12.5) instanceof Number === false  # YES!
        return f"(typeof {var} === 'number' || {var} instanceof Number)"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"({var} === null || {self.is_num(var)} || {self.is_a(var, bool)} || {self.is_a(var, str)})"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} !== undefined"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"{var} === null"
        elif tval is bool:
            return f"(typeof {var} === 'boolean' || {var} instanceof Boolean)"
        elif tval is int:
            return self.is_num(var) + f" && Number.isInteger({var})"  # type: ignore
        elif tval is float:
            return self.is_num(var)
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            # JS is a heavy contestant to BF.
            # c = "Calvin": typeof c === "string", c instanceof String === false
            # c = new String("Calvin"): typeof c === "object, c instanceof String === true
            return f"(typeof {var} === 'string' || {var} instanceof String)"
        elif tval is list:
            return f"Array.isArray({var})"
        elif tval is dict:
            # well, nearly everything is an object in JS, including null and arrays
            return f"Object.prototype.toString.call({var}) === '[object Object]'"
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

    def obj_prop_val(self, obj: Var, prop: Expr, is_var: bool = False) -> JsonExpr:
        return f"{obj}[{prop}]" if is_var else f"{obj}[{self.esc(prop)}]"  # type: ignore

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"{obj}.hasOwnProperty({self.esc(prop)})"

    def assign_obj_prop(self) -> bool:
        return False

    # FIXME path? reporting?
    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        if not self._with_predef and self.str_content_predef(name):
            return self.const(True) if is_str else self.is_a(var, str)
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
    def obj_len(self, var: Var) -> IntExpr:  # O(n) :-/
        return f"Object.keys({var}).length"

    def arr_len(self, var: Var) -> IntExpr:
        return f"{var}.length"

    def str_len(self, var: Var) -> IntExpr:
        return f"{var}.length"

    def any_len(self, var: Var) -> IntExpr:
        return f"_any_len({var})"
    #
    # misc expressions
    #
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> JsonExpr:
        return f"({fun} = {mapname}.get({prop}))"

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
        decl = "let " if tname else ""
        return [ f"{decl}{var}{assign}{self._eoi}" ]

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep !== null"

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"rep !== null && rep.push([{self.esc(msg)}, {self.path(path)}])" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ "if (rep !== null) rep.length = 0" ]

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        sseg = pseg if is_var else self.esc(pseg) if is_prop else pseg
        return f"{pvar} ? {pvar}.concat([{sseg}]) : null" if self._with_path else "null"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return f"({rvar} ? {lvar} : null)" if self._with_path else "null"

    #
    # blocks
    #
    def indent(self, block: Block, sep: bool = True) -> Block:
        indented = super().indent(block, sep)
        return ([ "{" ] + indented + [ "}" ]) if sep else indented

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"for (let {idx} = {start}; {idx} < {end}; {idx}++)"
        ] + self.indent(body)

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        # forEach: KO, cannot break
        return self.int_loop(idx, "0", f"{arr}.length", [ f"let {val} = {arr}[{idx}]" ] + body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [
            f"for (const [{key}, {val}] of Object.entries({obj}))"
        ] + self.indent(body)

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        if true and false:
            return [ f"if ({cond})" ] + self.indent(true) + ["else"] + self.indent(false)
        elif true:
            return [ f"if ({cond})" ] + self.indent(true)
        else:
            return [ f"if (!({cond}))" ] + self.indent(false)

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
        return [ f"const {name}_re = new runtime.RX({self.esc(regex)}, {self.esc(opts)})" ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        return [ f"const {name} = (s) => {name}_re.exec(s) !== null" ]

    def match_var(self, var: str, val: Expr|None = None, declare: bool = False) -> Block:
        return self._var(var, val, "Array")

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        return self._var(var, val, "String")

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"{name}_re.exec({var})"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        return [ f"{dname} = {mname}.groups[{self.esc(sname)}]" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ f"function {name}(val, path, rep)" ] + self.indent(body)

    #
    # Property Map
    #
    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"var {name} = new Map()" ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"{name}.set({self.esc(p)}, {f})" for p, f in pmap.items() ]

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return []

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"let {name} = new Set()" ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        return []

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return f"{name}.has({var})"

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"{name}.add({self.const(v)})" for v in constants ]

    def def_fun(self, name: str) -> Block:
        return []

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ f"function {name}(val, path, rep)" ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"let {name} = new Map()" ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"{name}.set({self.const(k)}, {m})" for k, m in mapping.items() ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}.get({tag})"

    def gen_init(self, init: Block) -> Block:
        code = [
            "runtime.jm_set_rx(require('re2'))" if self._relib == "re2" else "runtime.jm_set_rx(RegExp)"
        ] + init
        return self.file_subs("javascript_init.js", code)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("javascript_free.js", free)
