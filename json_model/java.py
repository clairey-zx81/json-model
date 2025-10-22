import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class Java(Language):
    """Generate JSON value checker in Java with GSON or Jackson.
    """

    def __init__(self, *,
                 debug: bool = False, with_package: bool = False, with_predef: bool = True,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 relib: str = "re", int_t: str = "long"):

        super().__init__(
            "Java",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             with_package=with_package, with_predef=with_predef,
             not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="null", check_t="Checker", json_t="Object",
             path_t="Path", float_t="double", str_t="String", bool_t="boolean", int_t="long",
             match_t="boolean", eoi=";", relib=relib, debug=debug,
             set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert relib in ("re"), f"regex engine {relib} is not supported"

        self._json_esc_table = str.maketrans(_ESC_TABLE)
        self.reindent = True

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code: Block = super().file_header(exe)
        if self._with_package:
            code += [ "", "package CHECK_PACKAGE_NAME;" ]
        code += [
            "",
            "import json_model.*;",
            "import java.util.Map;",
            "import java.util.Set;",
            "import java.util.HashMap;",
            "import java.util.HashSet;",
            "import java.util.Iterator;",
            "import java.util.regex.Pattern;",
            "import java.util.regex.Matcher;",
            "",
            "@SuppressWarnings(\"unchecked\")",
            "public class CHECK_FUNCTION_NAME extends ModelChecker",
            "{",
            f"    static public final String VERSION = \"{self.version()}\";",
        ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        code = [
            "",
            "    public Checker get(String name)",
            "    {",
            "        return CHECK_FUNCTION_NAME_map_pmap.get(name);",
            "    }",
            "",
            "    public Set<String> models()",
            "    {",
            "        return CHECK_FUNCTION_NAME_map_pmap.keySet();",
            "    }",
        ]
        if exe:
            code += [
                "",
                "    static public void main(String[] args) throws Exception",
                "    {",
                "        ModelChecker checker = new CHECK_FUNCTION_NAME();",
                "        Main.main(\"CHECK_FUNCTION_NAME\", checker, VERSION, args);",
                "    }",
            ]
        return code + [ "}" ]

    #
    # inlined type test expressions about JSON data
    #
    def rep(self) -> str:
        return "rep" if self._with_report else "null"

    def path(self, p: str) -> str:
        return p if self._with_path else "null"

    def is_num(self, var: Var) -> BoolExpr:
        return f"json.isNumber({var})"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"json.isScalar({var})"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != null"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"json.isNull({var})"
        elif tval is bool:
            return f"json.isBoolean({var})"
        elif tval is int:
            is_an_int = f"json.isInteger({var})"
            if loose:
                is_an_int = (
                    "(" + is_an_int + " || " +
                    f"(json.isDouble({var}) && "
                        f"json.asDouble({var}) == ((long) json.asDouble({var}))))")
            return is_an_int
        elif tval is float:
            return self.is_num(var) if loose else f"json.isDouble({var})"
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            return f"json.isString({var})"
        elif tval is list:
            return f"json.isArray({var})"
        elif tval is dict:
            return f"json.isObject({var})"
        else:
            raise Exception(f"unexpected type for json: {tval.__name__}")

    def _json_str(self, j) -> str:
        return '"' + json.dumps(j).translate(self._json_esc_table) + '"'

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"json.safeJSON({self._json_str(j)})"

    def const(self, c: Jsonable) -> Expr:
        if isinstance(c, (list, dict)):
            return self.json_cst(c)
        else:
            return super().const(c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"json.objectHasProp({obj}, {self.esc(prop)})"

    # FIXME path? reporting?
    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        if not self._with_predef and self.str_content_predef(name):
            return self.const(True) if is_str else self.is_a(var, str)
        isstr, val = "", var
        if not is_str:
            isstr = self.is_a(var, str) + " && "  # type: ignore
            val = f"json.asString({var})"
        if name == "$UUID":
            return f"{isstr}rt.is_valid_uuid({val})"
        elif name == "$DATE":
            return f"{isstr}rt.is_valid_date({val})"
        elif name == "$TIME":
            return f"{isstr}rt.is_valid_time({val})"
        elif name == "$DATETIME":
            return f"{isstr}rt.is_valid_datetime({val})"
        elif name == "$REGEX":
            return f"{isstr}rt.is_valid_regex({val})"
        elif name == "$EXREG":
            return f"{isstr}rt.is_valid_exreg({val})"
        elif name in ("$URL", "$URI"):
            return f"{isstr}rt.is_valid_url({val})"
        elif name == "$EMAIL":
            return f"{isstr}rt.is_valid_email({val})"
        elif name == "$JSON":
            return f"{isstr}rt.is_valid_json({val})"
        else:
            return super().predef(var, name, path, is_str)

    def value(self, var: Var, tvar: type) -> Expr:
        """Known type value extraction."""
        if tvar is type(None):
            return "NULL"
        elif tvar is bool:
            return f"json.asBoolean({var})"
        elif tvar is int:
            return f"json.asLong({var})"
        elif tvar is float:
            return f"json.asDouble({var})"
        elif tvar is Number:  # NOTE this cast from int if necessary
            return f"json.asNumber({var})"
        elif tvar is str:
            return f"json.asString({var})"
        else:
            raise Exception(f"unexpected type for value extraction: {tvar.__name__}")

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return f"json.arrayItem({arr}, {idx})"

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return f"json.objectValue({obj}, {prop})" if is_var else \
               f"json.objectValue({obj}, {self.esc(prop)})"  # type: ignore

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        return f"({dst} = {self.obj_prop_val(obj, prop, is_var)}) != null"

    def check_call(self, name: Var, val: JsonExpr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        val = f"json.strToJSON({val})" if is_raw else val
        return f"{name}.call({val}, {self.path(path)}, {self.rep()})" if is_ptr else \
               f"{name}({val}, {self.path(path)}, {self.rep()})"

    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"json.objectSize({var})"

    def arr_len(self, var: Var) -> IntExpr:
        return f"json.arrayLength({var})"

    def str_len(self, var: Var) -> IntExpr:
        return f"{var}.length()"

    #
    # misc expressions
    #
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"({fun} = {mapname}_pmap.get({prop})) != null"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"{val}.startsWith({self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"{val}.endsWith({self.esc(end)})"

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"rt.array_is_unique({val}, {self.path(path)}, {self.rep()})"

    CMP_OPS = {
        "=": "json_model.Runtime.Operator.EQ",
        "!=": "json_model.Runtime.Operator.NE",
        "<=": "json_model.Runtime.Operator.LE",
        "<": "json_model.Runtime.Operator.LT",
        ">=": "json_model.Runtime.Operator.GE",
        ">": "json_model.Runtime.Operator.GT",
    }

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        """Call inefficient type-unaware constraint check."""
        return f"rt.check_constraint({val}, {self.CMP_OPS[op]}, {self.json_cst(vop)}, {self.path(path)}, {self.rep()})"

    #
    # inline comparison expressions for strings
    # this is locale-unaware
    #
    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        assert op in ("=", "!=", "<", "<=", ">=", ">")
        if op == "=":
            return f"{e1}.compareTo({e2}) == 0"
        elif op == "!=":
            return f"{e1}.compareTo({e2}) != 0"
        elif op == ">=":
            return f"{e1}.compareTo({e2}) >= 0"
        elif op == ">":
            return f"{e1}.compareTo({e2}) > 0"
        elif op == "<=":
            return f"{e1}.compareTo({e2}) <= 0"
        elif op == "<":
            return f"{e1}.compareTo({e2}) < 0"
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

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep != null"

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"if (rep != null) rep.addEntry({self.esc(msg)}, {self.path(path)});" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ "if (rep != null) rep.clearEntries();" ] if self._with_report else []

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        if self._with_path:
            sseg = pseg if is_var else self.esc(pseg) if is_prop else pseg
            return f"new Path({sseg}, {pvar})"
        else:
            return "null"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return f"({rvar} != null ? {lvar} : null)" if self._with_path else "null"

    #
    # blocks
    #
    def indent(self, block: Block, sep: bool = True) -> Block:
        indented = super().indent(block, sep)
        return ([ "{" ] + indented + [ "}" ]) if sep else indented

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [
            f"int {idx} = -1;",
            f"Iterator<{self._json_t}> {val}_loop = json.arrayIterator({arr});",
            f"while ({val}_loop.hasNext())",
        ] + self.indent([
            f"{idx}++;",
            f"{self._json_t} {val} = {val}_loop.next();"
        ] + body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [
            f"Iterator<String> {key}_loop = json.objectIterator({obj});",
            f"while ({key}_loop.hasNext())",
        ] + self.indent([
            f"String {key} = {key}_loop.next();",
            f"{self._json_t} {val} = json.objectValue({obj}, {key});",
        ] + body)

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"for (int {idx} = {start}; {idx} < {end}; {idx}++)"
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
        return [ f"public Pattern {name}_pat = null;" ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        return [
            f"public boolean {name}(String val, Path path, Report rep)",
            r"{",
            f"    return {name}_pat.matcher(val).find();",
            r"}",
        ]

    def ini_re(self, name: str, regex: str, opts: str) -> Block:
        sregex = self.esc((f"(?{opts})" if opts else "") + regex)
        return [ f"{name}_pat = Pattern.compile({sregex});" ]

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        return [ f"{name}_pat = null;" ]

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        assert declare
        return [ f"Matcher {rname}_match;" ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"({name}_match = {name}_pat.matcher({var})).find()"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        decl = "String " if declare else ""
        return [ f"{decl}{dname} = {rname}_match.group({self.esc(sname)});" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ f"public boolean {name}(String val, Path path, Report rep)" ] + \
                    self.indent(body)

    #
    # Property Map
    #
    def _checker(self, name: str) -> str:
        """Create a checker wrapper around a check function."""
        return f"new Checker() {{ public boolean call(Object o, Path p, Report r) {{ return {name}(o, p, r);}} }}"

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"{'public ' if public else ''}Map<String, Checker> {name}_pmap;" ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        code = [ f"{name}_pmap = new HashMap<String, Checker>();" ]
        for p, f in pmap.items():
            code += [ f"{name}_pmap.put({self.esc(p)}, {self._checker(f)});" ]
        return code

    def del_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"{name}_pmap = null;" ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"Set<Object> {name}_set;" ]

    def del_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"{name}_set = null;" ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return f"{name}_set.contains({var})"

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        code = [ f"{name}_set = new HashSet<Object>();" ]
        for cst in constants:
            code.append(f"{name}_set.add({self.json_cst(cst)});")
        return code

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ f"public boolean {name}(Object val, Path path, Report rep)" ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"Map<Object, Checker> {name}_cmap;" ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        code = [ f"{name}_cmap = new HashMap<Object, Checker>();" ]
        for k, v in mapping.items():
            code += [ f"{name}_cmap.put({self.json_cst(k)}, {self._checker(v)});" ]
        return code

    def del_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"{name}_cmap = null;" ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}_cmap.get({tag})"

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("java_init.java", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("java_free.java", free)
