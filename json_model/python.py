from .language import Language, Code, Block, Inst, Var
from .language import BoolExpr


class Python(Language):
    """Python language support.

    Most Python code generation is actually inherited from Language,
    so this class in minimal.
    """

    def __init__(self, *, relib: str = "re2", debug: bool = False):

        super().__init__("Python", debug=debug, relib=relib)

        assert relib in ("re", "re2"), f"support for re and re2, not {relib}"

        # locally defined predefs
        self._len_used = False
        self._url_used = False
        self._date_used = False
        self._regex_used = False
        self._uuid_used = False
        # TODO check actual use to desactivate
        self._setmap_used = True

    def predef(self, var: Var, name: str, path: Var) -> BoolExpr:
        if name == "$URL":
            self._url_used = True
            return f"_is_valid_url({var}, {path}, rep)"
        elif name == "$DATE":
            self._date_used = True
            return f"_is_valid_date({var}, {path}, rep)"
        elif name == "$REGEX":
            self._regex_used = True
            return f"_is_valid_regex({var}, {path}, rep)"
        elif name == "$UUID":
            self._uuid_used = True
            self._re_used = True
            return f"_is_valid_uuid({var}, {path}, rep)"
        else:
            return super().predef(var, name, path)

    def file_header(self) -> Block:
        code: Block = super().file_header()
        code += [ f"__version__ = {self.esc(self._version)}" ]
        if self._re_used:
            code += [ f"import {self._relib} as re" ]
        code += self.file_load("python_types.py")
        code += self.file_load("python_header.py")
        if self._setmap_used:
            code += [""] + self.file_load("python_setmap.py")
        if self._url_used:
            code += [""] + self.file_load("python_url.py")
        if self._date_used:
            code += [""] + self.file_load("python_date.py")
        if self._regex_used:
            code += [""] + self.file_load("python_regex.py")
        if self._uuid_used:
            code += [""] + self.file_load("python_uuid.py")
        if self._len_used:
            code += [""] + self.file_load("python_len.py")
        return code

    def file_footer(self) -> Block:
        return [""] + self.file_load("python_main.py")

    def gen_init(self, init: Block) -> Block:
        return self.file_subs("python_init.py", init)

    def gen_free(self, free: Block) -> Block:
        return self.file_subs("python_free.py", free)
