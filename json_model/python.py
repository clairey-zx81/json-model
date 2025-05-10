from .language import Language, Code, Block, Inst, Var
from .language import BoolExpr


class Python(Language):
    """Python language support.

    Most Python code generation is actually inherited from Language.
    """

    def __init__(self, *, relib: str = "re2", debug: bool = False):

        super().__init__("Python", debug=debug, relib=relib)

        # locally defined predefs
        self._len_used = False
        self._url_used = False
        self._date_used = False
        self._regex_used = False

    def reset(self):
        self._len_used = False
        self._url_used = False
        self._date_used = False
        self._regex_used = False

    def predef(self, var: Var, name: str) -> BoolExpr:
        if name == "$URL":
            self._url_used = True
            return f"_is_valid_url({var}, path, rep)"
        elif name == "$DATE":
            self._date_used = True
            return f"_is_valid_date({var}, path, rep)"
        elif name == "$REGEX":
            self._regex_used = True
            return f"_is_valid_regex({var}, path, rep)"
        else:
            return super().predef(var, name)

    def file_header(self) -> Block:
        code: Block = super().file_header()
        code += [ f"import {self._relib} as re" ] + self.load_data("python_header.py")
        if self._url_used:
            code += [""] + self.load_data("python_url.py")
        if self._date_used:
            code += [""] + self.load_data("python_date.py")
        if self._regex_used:
            code += [""] + self.load_data("python_regex.py")
        if self._len_used:
            code += [""] + self.load_data("python_len.py")
        return code

    def file_footer(self) -> Block:
        return [""] + self.load_data("python_main.py")

    def gen_init(self, init: Block) -> Block:
        code: Block = self.load_data("python_init.py")
        body = self.indent(self.indent(init))
        bidx = code.index("INIT_BLOCK")
        assert bidx >= 0, "INIT_BLOCK marker found in file"
        code = [""] + code[:bidx] + body + code[bidx+1:]
        return code
