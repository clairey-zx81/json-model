from .language import Language, Code, Block, Inst, Var
from .language import BoolExpr, JsonExpr, Expr, IntExpr
from .mtypes import Number


class Python(Language):
    """Python language support.

    Most Python code generation is actually inherited from Language,
    so this class in minimal.
    """

    def __init__(self, *, relib: str = "re2", debug: bool = False, with_report: bool = True):

        super().__init__("Python", debug=debug, relib=relib, with_report=with_report)

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
        if tval is None or tval == type(None):
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
        if name == "$URL":
            return f"is_valid_url({var}, {path}, rep)"
        elif name == "$DATE":
            return f"is_valid_date({var}, {path}, rep)"
        elif name == "$REGEX":
            return f"is_valid_regex({var}, {path}, rep)"
        elif name == "$UUID":
            return f"is_valid_uuid({var}, {path}, rep)"
        else:
            return super().predef(var, name, path, is_str)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"is_unique_array({val}, {path}, rep)"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return f"check_constraint({val}, {self.esc(op)}, {self.const(vop)}, {path}, rep)"

    def regroup(self, name: str):
        return f"(?P<{name}>)" if self._relib == "re" else super().regroup(name)

    def file_header(self) -> Block:
        code: Block = [
            "#! /bin/env python",
        ]
        code += super().file_header()
        code += [
            r"from typing import Callable",
            f"import {self._relib} as re",
            f"from json_model.runtime import *",
            f"__version__ = {self.esc(self._version)}",
            "",
        ] + self.file_load("python_entry.py")
        return code

    def file_footer(self) -> Block:
        return [""] + self.file_load("python_main.py")

    def clean_report(self) -> Block:
        return [ "rep is None or rep.clear()" ]

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("python_init.py", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("python_free.py", free)

    def obj_prop_val(self, obj: Var, prop: Var) -> Expr:
        return f"{obj}.get({prop}, UNDEFINED)"

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"{self.esc(prop)} in {obj}"

    def any_len(self, var: Var) -> IntExpr:
        return f"len({var})"

    def ternary(self, cond: BoolExpr, true: BoolExpr, false: BoolExpr) -> BoolExpr:
        return f"{true} if {cond} else {false}"

    def prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return f"{fun} := {mapname}.get({prop})"

    def var(self, var: Var, val: Expr|None, tname: str|None) -> Inst:
        assign = f" = {val}" if val else ""
        decl = f": {tname}" if tname else ""
        return f"{var}{decl}{assign}{self._eoi}"
