from .language import Language, Code, Block, Inst, Var
from .language import BoolExpr, JsonExpr


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
