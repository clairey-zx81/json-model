import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals

_ESC_TABLE = { '"': r'\"', "\\": "\\\\" }

class Cpp(Language):
    """Generate JSON value checker in C++ with nlohmann and regex.
    """

    def __init__(self, *,
                 debug: bool = False,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 with_predef: bool = True,
                 relib: str = "regex"):

        super().__init__(
            "C++",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             with_predef=with_predef,
             not_op="!", and_op="&&", or_op="||", lcom="//",
             true="true", false="false", null="nullptr", check_t="", json_t="json",
             path_t="Path", report_t="Report", float_t="double", str_t="string", bool_t="bool", int_t="int64_t",
             match_t="bool" if relib == "regex" else "int", eoi=";", relib=relib, debug=debug,
             set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert relib in ("regex"), f"regex engine {relib} is not supported"

        self._json_esc_table = str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code: Block = super().file_header(exe)
        if self._relib == "regex":
            code += [ "#include <regex>" ]
        code += [
            "#include <cstdint>",
            "#include <string>",
            "#include <nlohmann/json.hpp>",
            "",
            "#include \"path.hpp\"",
            "#include \"report.hpp\"",
            "#include \"misc.hpp\"",
            "",
            "using std::int64_t;",
            "using std::string;",
            "using std::unordered_map;",
            "using json = nlohmann::json;",
        ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        return [ "" ]

    #
    # inlined type test expressions about JSON data
    #
    def rep(self) -> str:
        return "rep" if self._with_report else self._null

    def path(self, p: str) -> str:
        return p if self._with_path else self._null

    def is_num(self, var: Var) -> BoolExpr:
        return f"{var}.is_number()"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"is_scalar({var})"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != {self._null}"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"{var}.is_null()"
        elif tval is bool:
            return f"{var}.is_boolean()"
        elif tval is int:
            is_an_int = f"{var}.is_number_integer()"
            if loose:
                is_an_int = (
                    "(" + is_an_int + " || " +
                    f"({var}.is_number_float() && "
                        f"{var}.get<{self._float_t}>() == (({self._int_t}) {var}.get<{self._float_t}>())))")
            return is_an_int
        elif tval is float:
            return self.is_num(var) if loose else f"{var}.is_number_float()"
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            return f"{var}.is_string()"
        elif tval is list:
            return f"{var}.is_array()"
        elif tval is dict:
            return f"{var}.is_object()"
        else:
            raise Exception(f"unexpected type for json: {tval.__name__}")

    def _json_str(self, j) -> str:
        return '"' + json.dumps(j).translate(self._json_esc_table) + '"'

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"json::parse({self._json_str(j)})"

    def const(self, c: Jsonable) -> Expr:
        if isinstance(c, (list, dict)):
            return self.json_cst(c)
        else:
            return super().const(c)

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        val = var if is_str else f"to_string({var})"
        # no content checks
        if not self._with_predef and self.str_content_predef(name):
            return "true" if is_str else self.is_a(var, str)
        if name == "$UUID":
            return f"isValid::isValidUUID({val}, {self.path(path)}, {self.rep()})"
        elif name == "$DATE":
            return f"isValid::isValidDate({val}, {self.path(path)}, {self.rep()})"
        elif name == "$TIME":
            return f"isValid::isValidTime({val}, {self.path(path)}, {self.rep()})"
        elif name == "$DATETIME":
            return f"isValid::isValidDateTime({val}, {self.path(path)}, {self.rep()})"
        elif name in ("$REGEX", "$EXREG"):
            return f"isValid::isValidRegex({val}, {self.path(path)}, {self.rep()})"
        elif name in ("$URL", "$URI"):
            return f"jisValid::isValidURL({val}, {self.path(path)}, {self.rep()})"
        elif name == "$EMAIL":
            return f"isValid::isValidEmail({val}, {self.path(path)}, {self.rep()})"
        elif name == "$JSON":
            return f"isValid::isValidJSON({val}, {self.path(path)}, {self.rep()})"
        else:
            return super().predef(var, name, path, is_str)
        raise NotImplementedError() # runtime

    def value(self, var: Var, tvar: type) -> Expr:
        """Known type value extraction."""
        if tvar is type(None):
            return self._null
        elif tvar is bool:
            return f"{var}.get<{self._bool_t}>()"
        elif tvar is int:
            return f"{var}.get<{self._int_t}>()"
        elif tvar is float:
            return f"{var}.get<{self._float_t}>()"
        elif tvar is Number:  # NOTE this cast from int if necessary
            return f"{var}.get<{self._int_t}>()"
        elif tvar is str:
            return f"{var}.get<{self._str_t}>()"
        else:
            raise Exception(f"unexpected type for value extraction: {tvar.__name__}")

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return f"{arr}[{idx}]"

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return f"{obj}[{prop})" if is_var else \
               f"{obj}[{self.esc(prop)}]"  # type: ignore

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        return f"({dst} = {self.obj_prop_val(obj, prop, is_var)}) != {self._null}"

    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"{var}.size()"

    def arr_len(self, var: Var) -> IntExpr:
        return f"{var}.size()"

    def str_len(self, var: Var) -> IntExpr:
        return f"{var}.length()"

    #
    # misc expressions
    #
    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        # return f"({fun} = {mapname}_pmap.get({prop})) != null"
        raise NotImplementedError()

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"{val}.starts_with({self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"{val}.ends_with({self.esc(end)})"

    def check_call(self, name: Var, val: JsonExpr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        # val = f"json.strToJSON({val})" if is_raw else val
        # return f"{name}.call({val}, {self.path(path)}, {self.rep()})" if is_ptr else \
        #        f"{name}({val}, {self.path(path)}, {self.rep()})"
        raise NotImplementedError()


    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        # return f"rt.array_is_unique({val}, {self.path(path)}, {self.rep()})"
        raise NotImplementedError()

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
        # return f"rt.check_constraint({val}, {self.CMP_OPS[op]}, {self.json_cst(vop)}, {self.path(path)}, {self.rep()})"
        raise NotImplementedError()


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
        return f"rep != {self._null}" if self._with_report else "false"

    def report(self, msg: str, path: Var) -> Block:
        return ([ f"if (rep != {self._null}) rep->addEntry({self.esc(msg)}, {self.path(path)});" ]
                if self._with_report else [])

    def clean_report(self) -> Block:
        return [ f"if (rep != {self._null}) rep->clear()" ] if self._with_report else []

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        if self._with_path:
            sseg = pseg if is_var else self.esc(str(pseg)) if is_prop else pseg
            return (f"{self._path_t}({pvar}, {sseg})")
        else:
            return self._null

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return f"({rvar} != {self._null} ? {lvar} : {self._null})" if self._with_path else self._null

    #
    # blocks
    #
    def indent(self, block: Block, sep: bool = True) -> Block:
        indented = super().indent(block, sep)
        return ([ "{" ] + indented + [ "}" ]) if sep else indented

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [
            f"for (size_t {idx}=0; {idx} < {arr}.size(); {idx}++)",
        ] + self.indent([
            f"{self._json_t} {val} = {arr}[{idx}];"
        ] + body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [
            f"for (auto item = {obj}.begin(); item != {obj}.end(); ++item)",
        ] + self.indent([
            f"{self._str_t} {key} = item.key();",
            f"{self._json_t} {val} = item.value();",
        ] + body)

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"for ({self._int_t} {idx} = {start}; {idx} < {end}; {idx}++)"
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
        return [ f"const regex {name}_pat;" ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        return [
            f"{self._bool_t} {name}({self._str_t} val, {self._path_t}* path, {self._report_t}* rep)",
            r"{",
            f"    return regex_match(val, {name}_pat);",
            r"}",
        ]

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        return [ f"{name}_pat = {self._null};" ]

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        assert declare
        return [ f"Matcher {rname}_match;" ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"({name}_match = {name}_pat.matcher({var})).find()"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        decl = "String " if declare else ""
        return [ f"{decl}{dname} = {rname}_match.group({self.esc(sname)});" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ f"{self._bool_t} {name}(String val, {self._path_t}* path, {self._report_t}* rep)" ] + \
                    self.indent(body)

    #
    # Property Map
    #
    def _checker(self, name: str) -> str:
        """Create a checker wrapper around a check function."""
        return f"Checker() {{ {self._bool_t} call(json& o, {self._path_t}* p, {self._report_t}* r) {{ return {name}(o, p, r);}} }}"

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"unordered_map<string, Checker> {name}_pmap;" ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        code = [ f"{name}_pmap = unordered_map<string, Checker>();" ]
        for p, f in pmap.items():
            code += [ f"{name}_pmap.insert(\"\", static_cast<Checker>({f}));" ]
        return code

    def del_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"{name}_pmap.clear();" ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"Set<Object> {name}_set;" ]

    def del_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"{name}_set = {self._null};" ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return f"{name}_set.contains({var})"

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        code = [ f"{name}_set = HashSet<Object>();" ]
        for cst in constants:
            code.append(f"{name}_set.add({self.json_cst(cst)});")
        return code

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ f"{self._bool_t} {name}(json& val, {self._path_t}* path, {self._report_t}* rep)" ] + self.indent(body)

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"unordered_map<json&, Checker> {name}_cmap;" ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        code = [ f"{name}_cmap = unordered_map<json&, Checker>();" ]
        for k, v in mapping.items():
            code += [ f"{name}_cmap.put({self.json_cst(k)}, {self._checker(v)});" ]
        return code

    def del_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"{name}_cmap = {self._null};" ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}_cmap.get({tag})"

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("cpp_init.java", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("cpp_free.java", free)
