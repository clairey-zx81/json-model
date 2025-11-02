import re

from .language import Language, Block, Var, PropMap, ConstList
from .language import BoolExpr, JsonExpr, Expr, IntExpr, PathExpr, JsonScalar, StrExpr, NumExpr
from .mtypes import Number, Jsonable, TestHint, Conditionals


class Perl(Language):
    """Perl language Code Generator."""

    def __init__(self, *, relib: str = "re2", with_package: bool = False, with_predef: bool = True,
                 debug: bool = False, with_report: bool = True, with_path: bool = True):

        super().__init__("Perl",
            debug=debug, relib=relib, with_report=with_report, with_path=with_path,
            with_package=with_package, with_predef=with_predef,
            not_op="!", and_op="&&", or_op="||", lcom="#",
            true="1", false="0", null="undef", check_t="", json_t="",
            path_t="", float_t="", str_t="", match_t="", eoi=";", set_caps=(str,)
        )

        assert relib in ("re", "re2"), f"support for re and re2, not {relib}"

        # TODO check actual use to desactivate
        self._setmap_used = True

    def esc(self, s: str) -> StrExpr:
        return "'" + s.replace("'", r"\'") + "'"

    def rep(self) -> str:
        return "$rep" if self._with_report else "undef"

    def path(self, p: str) -> str:
        return p if self._with_path else "undef"

    def is_num(self, var: Var) -> BoolExpr:
        var = f"${var}" if self.is_a_var(var) else var
        return f"jm_is_numeric({var})"

    def is_def(self, var: Var) -> BoolExpr:
        var = f"${var}" if self.is_a_var(var) else var
        return f"defined({var})"

    def is_scalar(self, var: Var) -> BoolExpr:
        var = f"${var}" if self.is_a_var(var) else var
        return f"jm_is_scalar({var})"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        var = f"${var}" if self.is_a_var(var) else var
        if tval is None or tval is type(None):
            return f"!{self.is_def(var)}"
        elif tval is int:
            return f"jm_is_integer({var})"
        elif tval is float:
            return self.is_num(var)
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            return f"jm_is_string({var})"
        elif tval is bool:
            return f"jm_is_boolean({var})"
        elif tval is list:
            return f"jm_is_array({var})"
        elif tval is dict:
            return f"jm_is_object({var})"
        else:
            raise Exception("unexpected type: {tval}")

    def _val(self, expr: Expr) -> Expr:
        return f"${expr}" if self.is_a_var(expr) else expr

    def value(self, var: Var, tvar: type) -> Expr:
        return self._val(var)

    def get_value(self, var: Var, tvar: type) -> Expr:
        return self._val(var)

    def num_cmp(self, e1: NumExpr, op: str, e2: NumExpr, hexa: bool = False) -> BoolExpr:
        return super().num_cmp(self._val(e1), op, e2, hexa)

    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        e1 = self._val(e1)  # type: ignore
        if op == "=":
            return f"{e1} eq {e2}"
        elif op == "!=":
            return f"{e1} ne {e2}"
        elif op == "<=":
            return f"{e1} le {e2}"
        elif op == "<":
            return f"{e1} lt {e2}"
        elif op == ">=":
            return f"{e1} ge {e2}"
        elif op == ">":
            return f"{e1} gt {e2}"
        else:
            raise Exception(f"unexpected string comparison operator: {op}")

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        if not self._with_predef and self.str_content_predef(name):
            return self.const(True) if is_str else self.is_a(var, str)
        is_str_and  = self.is_a(var, str) + " && "  # type: ignore
        var, path = self._val(var), self._val(path)  # type: ignore
        if name in ("$URL", "$URI"):  # approximate
            return is_str_and + f"jm_is_valid_url({var}, {self.path(path)}, {self.rep()})"
        elif name == "$DATE":
            return is_str_and + f"jm_is_valid_date({var}, {self.path(path)}, {self.rep()})"
        elif name == "$TIME":
            return is_str_and + f"jm_is_valid_time({var}, {self.path(path)}, {self.rep()})"
        elif name == "$DATETIME":
            return is_str_and + f"jm_is_valid_datetime({var}, {self.path(path)}, {self.rep()})"
        elif name == "$REGEX":
            return is_str_and + f"jm_is_valid_regex({var}, {self.path(path)}, {self.rep()})"
        elif name == "$EXREG":
            return is_str_and + f"jm_is_valid_exreg({var}, {self.path(path)}, {self.rep()})"
        elif name == "$UUID":
            return is_str_and + f"jm_is_valid_uuid({var}, {self.path(path)}, {self.rep()})"
        elif name == "$EMAIL":
            return is_str_and + f"jm_is_valid_email({var}, {self.path(path)}, {self.rep()})"
        elif name == "$JSON":
            return is_str_and + f"jm_is_valid_json({var}, {self.path(path)}, {self.rep()})"
        else:
            return super().predef(var, name, path, is_str)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        path = self.path(self._val(path))
        return f"jm_is_unique_array(${val}, {path}, {self.rep()})"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        path = self.path(self._val(path))
        return f"jm_check_constraint({self._val(val)}, {self.esc(op)}, {self.const(vop)}, {path}, {self.rep()})"

    def file_header(self, exe: bool = True) -> Block:
        code: Block = self.file_load("perl_exe.pl") if exe else []
        code += super().file_header(exe)
        code += [ "use strict;", "use warnings;", 'no warnings "uninitialized";' ]
        if self._relib == "re2":
            code.append("use re::engine::RE2;")
        if not exe:
            code += self.file_load("perl_pkg.pl")
        code += [
            r"use JSON::JsonModel;",
            f"use constant JMC_VERSION => {self.esc(self.version())};",
            "",
        ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        code: Block = [ "" ] + self.file_load("perl_entry.pl") + [ "" ]
        code += self.file_load("perl_main.pl") if exe else [ "1;" ]
        return code

    def clean_report(self) -> Block:
        return [ "defined $rep && $rep = [];" ] if self._with_report else []

    def nope(self) -> Block:
        return [ ";" ]

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("perl_init.pl", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("perl_free.pl", free)

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return f"$${obj}{{${prop}}}" if is_var else \
               f"$${obj}{{{self.esc(prop)}}}"

    # TODO FIXME mv-18/dis_04.pl.check
    def assign_obj_prop(self) -> bool:
        return False

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        return f"defined(${dst} = {self.obj_prop_val(obj, prop, is_var)})"

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        idx = f"${idx}" if isinstance(idx, str) and self.is_a_var(idx) else str(idx)
        return f"${self._val(arr)}[{idx}]"

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"exists $${obj}{{{self.esc(prop)}}}"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"jm_starts_with({self._val(val)}, {self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"jm_ends_with({self._val(val)}, {self.esc(end)})"

    def any_len(self, var: Var) -> IntExpr:
        return f"jm_any_len({self._val(var)})"

    def arr_len(self, var: Var) -> IntExpr:
        return f"scalar @${var}"

    def str_len(self, var: Var) -> IntExpr:
        return f"length {self._val(var)}"

    def obj_len(self, var: Var) -> IntExpr:
        return f"jm_obj_size(${var})"

    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"(${fun} = ${mapname}{{{self._val(prop)}}})"

    def const(self, c: Jsonable) -> Expr:
        if c is None:
            return "undef"
        elif isinstance(c, bool):
            return "1" if c else "0"
        elif isinstance(c, int):
            return str(c)
        elif isinstance(c, float):
            return str(c)
        elif isinstance(c, str):
            return self.esc(c)
        else:
            raise Exception("not implemented yet for list and dict")

    def _var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        assign = f" = {val}" if val else ""
        decl = "my " if tname is not None else ""
        return [ f"{decl}${var}{assign};" ]

    # FIXME broken
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        seg = "${pseg}" if is_var else self.esc(pseg) if is_prop else str(pseg)
        pvar = f"${pvar}" if self.is_a_var(pvar) else pvar
        pvar = f"({pvar})" if " " in pvar else pvar
        return f"defined {pvar} ? [@{{{pvar}}}, {seg}] : undef" if self._with_path else "undef"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        rvar = f"${rvar}" if self.is_a_var(rvar) else rvar
        rvar = f"({rvar})" if " " in rvar else rvar
        lvar = f"${lvar}" if self.is_a_var(lvar) else lvar
        return f"defined {rvar} ? {lvar} : undef" if self._with_path else "undef"

    def check_call(self, name: Var, val: JsonExpr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        # FIXME is_ptr, is_raw
        val = f"${val}" if self.is_a_var(val) else val
        path = self.path(f"${path}" if self.is_a_var(path) else path)
        name = f"&${name}" if is_ptr else name
        return f"{name}({val}, {path}, {self.rep()})"

    def str_check_call(self, name: str, val: StrExpr, path: Var) -> BoolExpr:
        return self.check_call(name, val, path)

    def is_reporting(self) -> BoolExpr:
        return "defined $rep" if self._with_report else "0"

    def report(self, msg: str, path: Var) -> Block:
        # FIXME probably need to copy path
        path = self.path(f"${path}" if self.is_a_var(path) else path)
        return [ f"push @$rep, [{self.esc(msg)}, {path}] if defined $rep;" ] \
            if self._with_report else []

    def inc_var(self, var: Var) -> Block:
        assert self.is_a_var(var), "can only increment a simple variable"
        return [ f"${var}++;" ]

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        # NOTE "each" does not work properly if the list contains 'undef'
        isref = "$" in arr
        alen = f"(scalar @{{{arr}}} - 1)" if isref else f"$#${arr}"
        aref = f"{arr}" if isref else f"$${arr}"
        return [ f"for my ${idx} (0 .. {alen})" ] + \
            self.indent([f"my ${val} = {aref}[${idx}];"] + body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [ f"scalar keys %${obj};", f"while (my (${key}, ${val}) = each %${obj})" ] + \
            self.indent(body)

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        if isinstance(end, int):
            end -= 1
        else:
            end = self._val(end) + " - 1"  # type: ignore
        return [ f"for my ${idx} ({start} .. {end})" ] + self.indent(body)

    def brk(self) -> Block:
        return [ "last;" ]

    def cont(self) -> Block:
        return [ "next;" ]

    def ret(self, res: BoolExpr) -> Block:
        return super().ret(f"${res}" if self.is_a_var(res) else res)

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        cond = f"${cond}" if self.is_a_var(cond) else cond
        if true and false:
            return [ f"if ({cond})" ] + self.indent(true) + ["else"] + self.indent(false)
        elif true:
            return [ f"if ({cond})" ] + self.indent(true)
        else:
            return [ f"if (!({cond}))" ] + self.indent(false)

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        code, op = [], "if"
        for cond, likely, true in cond_true:
            cond = f"${cond}" if self.is_a_var(cond) else cond
            code += [ f"{op} ({cond})" ]
            code += self.indent(true)
            op = "elsif"
        if false:
            if op != "if":
                code += [ "else" ]
                code += self.indent(false)
            else:
                code += false
        return code

    def not_op(self, e: BoolExpr) -> BoolExpr:
        return super().not_op(self._val(e))  # type: ignore

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [f"my %{name};"]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [
            f"%{name} = (" ] + [
                f"{self._indent}{self.esc(p)} => \\&{f}," for p, f in pmap.items() ] + [
            ");"
        ]

    def del_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ f"%{name} = ();" ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"my %{name};" ]

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        # generate a deterministic initialization
        return [
            f"%{name} = (" ] + [
                f"{self._indent}{self.const(c)} => 1," for c in constants ] + [
            ");"
        ]

    def del_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"%{name} = ();" ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        # NOTE sets (hash) keys must be strings
        return f"jm_is_string(${var}) && exists ${name}{{${var}}}"

    def _fun(self, name: str) -> str:
        return f"sub {name}($$$)"

    def def_fun(self, name: str) -> Block:
        return [ self._fun(name) + ";" ]

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ self._fun(name) ] + self.indent([ "my ($val, $path, $rep) = @_;" ] + body)

    def def_strfun(self, name: str) -> Block:
        return self.def_fun(name)

    def sub_strfun(self, name: str, body: Block) -> Block:
        return self.sub_fun(name, body)

    def _escRegEx(self, regex: str) -> str:
        # we do not want an open / in the regex
        # FIXME repeated for //
        regex = re.sub(r"([^\\])/", r"\1\\/", regex)
        regex = re.sub(r"([^\\])/", r"\1\\/", regex)
        # $ followed by a name is interpreted as a variable in a regex, we must backslash some…
        regex = re.sub(r"(\$(\w+|%|]|@))", r"\\\1", regex)
        return regex

    # EMPTY: def_re ini_re del_re
    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        match = self.match_re(name, "val", regex, opts)
        return self.sub_fun(name, [
            f"my $res = {match};",
            r"return $res;",
        ])

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"${var} =~ /{self._escRegEx(regex)}/{opts}"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        return [ f"${dname} = $+{{{self.esc(sname)}}};" ]

    # constants map
    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"${name}{{{self.value(tag, ttag)}}}"

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"my %{name};" ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"%{name} = (" ] + [
                f"{self._indent}{self.const(v)} => \\&{f}," for v, f in mapping.items()
            ] + [ ");" ]

    def del_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ f"%{name} = ();" ]

    def indent(self, block: Block, sep: bool = True) -> Block:
        indented =  super().indent(block)
        return (["{"] + indented + ["}"]) if sep else indented

    def filter_code(self, code: Block) -> Block:

        for i in range(len(code)):
            line = code[i]
            if line is None:
                continue
            if " && 1" in line:
                line = re.sub(r" && 1", "", line)
                code[i] = line
            # remove redundant scalar check
            if "jm_is_scalar" in line:
                code[i] = re.sub(r" jm_is_scalar\((\$\w+)\) && jm_is_string\(\1\)",
                                 r" jm_is_string(\1)", line)

        return list(filter(lambda line: line is not None, code))
