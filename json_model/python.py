from .language import Language, Block, Var, PropMap, ConstList
from .language import BoolExpr, JsonExpr, Expr, IntExpr, PathExpr, JsonScalar, StrExpr
from .mtypes import Number, TestHint, Conditionals
# from .utils import log


class Python(Language):
    """Python language Code Generator."""

    def __init__(self, *, relib: str = "re2",
                 debug: bool = False, with_report: bool = True, with_path: bool = True,
                 with_predef: bool = True):

        super().__init__("Python", relib=relib, debug=debug,
                         with_report=with_report, with_path=with_path, with_predef=with_predef)

        assert relib in ("re", "re2"), f"support for re and re2, not {relib}"

        # TODO check actual use to desactivate
        self._setmap_used = True

    def is_num(self, var: Var) -> BoolExpr:
        return f"isinstance({var}, (int, float)) and not isinstance({var}, bool)"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} != UNDEFINED"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"({var} is None or isinstance({var}, (bool, int, float, str)))"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"{var} is None"
        elif tval is int:
            is_an_int = f"isinstance({var}, int) and not isinstance({var}, bool)"
            if loose:
                is_an_int = f"({is_an_int} or isinstance({var}, float) and {var} == int({var}))"
            return is_an_int
        elif tval is float:
            return self.is_num(var) if loose else f"isinstance({var}, float)"
        elif tval is Number:
            return self.is_num(var)
        else:
            assert tval in (bool, str, list, dict)
            return f"isinstance({var}, {tval.__name__})"

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        if not self._with_predef and self.str_content_predef(name):
            return self.const(True) if is_str else self.is_a(var, str)
        if name in ("$URL", "$URI"):  # approximate
            return f"is_valid_url({var}, {path}, rep)"
        elif name == "$DATE":
            return f"is_valid_date({var}, {path}, rep)"
        elif name == "$TIME":
            return f"is_valid_time({var}, {path}, rep)"
        elif name == "$DATETIME":
            return f"is_valid_datetime({var}, {path}, rep)"
        elif name == "$REGEX":
            return f"is_valid_regex({var}, {path}, rep)"
        elif name == "$EXREG":
            return f"is_valid_exreg({var}, {path}, rep)"
        elif name == "$UUID":
            return f"is_valid_uuid({var}, {path}, rep)"
        elif name == "$EMAIL":
            return f"is_valid_email({var}, {path}, rep)"
        elif name == "$JSON":
            return f"is_valid_json({var}, {path}, rep)"
        else:
            return super().predef(var, name, path, is_str)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"is_unique_array({val}, {path}, rep)"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return f"check_constraint({val}, {self.esc(op)}, {self.const(vop)}, {path}, rep)"

    def regroup(self, name: str, pattern: str = ".*"):
        return f"(?P<{name}>{pattern})" if self._relib == "re" else super().regroup(name, pattern)

    def file_header(self, exe: bool = True) -> Block:
        code: Block = self.file_load("python_exe.py") if exe else []
        code += super().file_header(exe)
        code += [
            r"from typing import Callable",
            f"import {self._relib} as re",
            r"from json_model.runtime import *",
            f"__version__ = {self.esc(self.version())}",
            "",
        ]
        code += self.file_load("python_entry.py")  # too early?
        return code

    def file_footer(self, exe: bool = True) -> Block:
        return self.file_load("python_main.py") if exe else []

    def clean_report(self) -> Block:
        return [ "rep is None or rep.clear()" ]

    def nope(self) -> Block:
        return [ "pass" ]

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("python_init.py", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("python_free.py", free)

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return f"{obj}.get({prop}, UNDEFINED)" if is_var else \
               f"{obj}.get({self.esc(prop)}, UNDEFINED)"

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"{self.esc(prop)} in {obj}"

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        return f"({dst} := {self.obj_prop_val(obj, prop, is_var)}) != UNDEFINED"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"{val}.startswith({self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"{val}.endswith({self.esc(end)})"

    def any_len(self, var: Var) -> IntExpr:
        return f"len({var})"

    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"{fun} := {mapname}.get({prop})"

    def _var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        assign = f" = {val}" if val else ""
        decl = f": {tname}" if tname else ""
        return [ f"{var}{decl}{assign}{self._eoi}" ]

    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        # avoid nested if expressions
        pvar = f"({pvar})" if " if " in pvar else pvar
        sseg = pseg if is_var else self.esc(pseg) if is_prop else pseg
        return f"({pvar} + [ {sseg} ]) if {pvar} is not None else None" if self._with_path else "None"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        # avoid nested if expressions
        rvar = f"({rvar})" if " if " in rvar else rvar
        lvar = f"({lvar})" if " if " in lvar else lvar
        return f"{lvar} if {rvar} is not None else None" if self._with_path else "None"

    def is_reporting(self) -> BoolExpr:
        return "rep is not None"

    def report(self, msg: str, path: Var) -> Block:
        return [ f"rep is None or rep.append(({self.esc(msg)}, {path}))" ] \
            if self._with_report else []

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [ f"for {idx}, {val} in enumerate({arr}):" ] + self.indent(body)

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [ f"for {key}, {val} in {obj}.items():" ] + self.indent(body)

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [ f"for {idx} in range({start}, {end}):" ] + self.indent(body)

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        if true and false:
            return [ f"if {cond}:" ] + self.indent(true) + ["else:"] + self.indent(false)
        elif true:
            return [ f"if {cond}:" ] + self.indent(true)
        else:
            return [ f"if not ({cond}):" ] + self.indent(false)

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        code, op = [], "if"
        for cond, likely, true in cond_true:
            code += [ f"{op} {cond}:" ]
            code += self.indent(true)
            op = "elif"
        if false:
            if op != "if":
                code += [ "else:" ]
                code += self.indent(false)
            else:
                code += false
        return code

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [f"{name}: PropMap"]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [
            f"global {name}",
            f"{name} = {{" ] + [
                (self._indent + self.esc(p) + ": " + f + ",")
                    for p, f in pmap.items()
                ] + [ "}" ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ f"{name}: set[str]" ]

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        # generate a deterministic initialization
        dset = str(sorted(list(constants)))  # pyright: ignore
        dset = f"{{{dset[1:-1]}}}"
        return [ f"global {name}", f"{name} = {dset}" ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return f"{var} in {name}"

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [
            f"def {name}(val: Jsonable, path: Path, rep: Report) -> bool:"
        ] + self.indent(body)

    def def_strfun(self, name: str) -> Block:
        return [ f"{name}: RegexFun" ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [
            f"def {name}(val: str, path: Path, rep: Report) -> bool:",
        ] + self.indent(body)

    def def_re(self, name: str, regex: str, opts: str) -> Block:
        return [
            # NOTE re2 imported as re
            f"{name}_reco: object",
            f"{name}: RegexFun"
        ]

    def ini_re(self, name: str, regex: str, opts: str) -> Block:
        self._re_used = True
        sregex = self.esc((f"(?{opts})" if opts else "") + regex)
        return [
            f"global {name}_reco, {name}",
            # rex engine imported as re; may raise an exception
            f"{name}_reco = re.compile({sregex})",
            f"{name} = lambda s, p, r: {name}_reco.search(s) is not None"
        ]

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        return [
            f"global {name}_reco, {name}",
            f"{name}_reco = None",
            f"{name} = None"
        ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return f"{name}_reco.search({var})"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        decl = ": str" if declare else ""
        return [
            f"{dname}{decl} = {mname}.groupdict()[{self.esc(sname)}]"
        ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"{name}.get({self.value(tag, ttag)}, UNDEFINED)"

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        if self._str_map(mapping):
            return [ f"{name}: dict[str, str]" ]
        else:
            return [ f"{name}: ConstMap = ConstMap()" ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        icode = [ f"global {name}" ]
        if self._str_map(mapping):
            icode += [
                f"{name} = {{", ] + [
                f"    {self.const(v)}: {fun},"
                    for v, fun in mapping.items()
            ] + [ r"}" ]
        else:
            for v, fun in mapping.items():
                icode += [ f"{name}[{self.const(v)}] = {fun}" ]
        return icode
