import re
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals
from .utils import log, __version__, load_data_file

# name
type Var = str

# typed expressions
type JsonExpr = str
type BoolExpr = str|bool
type IntExpr = str|int
type FloatExpr = str
type NumExpr = str|int
type StrExpr = str
type PathExpr = Var|str
# all value expressions
type Expr = JsonExpr|BoolExpr|IntExpr|FloatExpr|NumExpr|StrExpr

# actual code
type Block = list[str]

# must or may property name -> corresponding check function
type PropMap = dict[str, str]
type ConstList = list[None|bool|int|float|str]
type ConstMap = dict[JsonScalar, str]
type RegMap = dict[str, str]


class Language:
    """Dumb abstraction of an imperative language to manipulate JSON data.

    TODO reduce #funcs, eg var/val with type parameter.
    TODO move non generic methods to Python, to avoid generating python if unimplemented
    """

    def __init__(self,
            name: str, *,
            debug: bool = False,
            short_version: bool = False,
            # operators, separators, types…
            eq: str = "==", ne: str = "!=",
            ge: str = ">=", gt: str = ">", le: str = "<=", lt: str = "<",
            not_op: str = "not", and_op: str = "and", or_op: str = "or",
            eoi: str = "", isep: str = "\n", indent: str = "    ",
            lcom: str = "#", relib: str = "re2",
            true: str = "True", false: str = "False", null: str = "None",
            check_t: str = "CheckFun", json_t: str = "Jsonable", path_t: str = "Path",
            match_t: str|None = None, hash_t: str = "int",
            float_t: str = "float", int_t: str = "int", bool_t: str = "bool", str_t: str = "str",
            # options
            with_path: bool = True, with_report: bool = True, with_package: bool = False,
            with_predef: bool = True, with_comment: bool = True, with_hints: bool = True,
            set_caps: tuple[type] = (str,),
        ):

        # parameter consistency
        if with_path and not with_report:
            log.warning("path collection but no reporting, removing path")
            with_path = False

        # keep parameters
        self._name = name  # language name
        self._debug = debug
        self._short_version = short_version
        self._with_path = with_path and with_report
        self._with_report = with_report
        self._with_comment = with_comment
        self._with_package = with_package
        self._with_predef = with_predef
        self._with_hints = with_hints

        # comparison operators
        self._eq = eq
        self._ne = ne
        self._ge = ge
        self._gt = gt
        self._le = le
        self._lt = lt
        # logical operators
        self._not = not_op
        self._and = and_op
        self._or = or_op
        # instructions and blocks
        self._eoi = eoi
        self._isep = isep
        self._indent = indent
        self._lcom = lcom
        self._relib = relib
        # constants
        self._true = true
        self._false = false
        self._null = null
        self._check_t = check_t
        self._json_t = json_t
        self._path_t = path_t
        self._match_t = match_t
        self._bool_t = bool_t
        self._int_t = int_t
        self._float_t = float_t
        self._str_t = str_t
        self._hash_t = hash_t

        # other stuff
        self._version = __version__
        self._idcounts: dict[str, int] = {}  # per-prefix ident count for unicity
        self._re_used: bool = False          # whether regular expressions are used
        self._byte_order: str = "le"         # just in case

        self.set_caps = tuple(set_caps)      # constant types in a set
        self.reindent = False

    def version(self) -> str:
        """Version string in generated code."""
        return self._version.split(".", 1)[0] if self._short_version else self._version

    def ident(self, prefix: str) -> Var:
        """Return a new identifier using prefix."""
        if prefix not in self._idcounts:
            self._idcounts[prefix] = 0
        ident = prefix + "_" + str(self._idcounts[prefix])
        self._idcounts[prefix] += 1
        return ident

    def is_a_var(self, expr: Expr) -> bool:
        """Return whether expression is just a variable name."""
        return (expr != self._null and isinstance(expr, str) and
                re.search(r"^[_a-zA-Z]\w+$", expr) is not None)  # type: ignore

    #
    # SOURCE FILE MANAGEMENT
    #
    def file_load(self, fn: str) -> Block:
        """Load a source file."""
        code = load_data_file(fn).split("\n")
        # remove empty trailing lines
        while code and re.match(r"^\s*$", code[-1]):
            code = code[:-1]
        return code

    def file_subs(self, fname: str, block: Block) -> Block:
        """Load a file with a code block substitution."""
        code: Block = self.file_load(fname)
        body = self.indent(self.indent(block, False), False)
        bidx = code.index("CODE_BLOCK")
        assert bidx >= 0, "CODE_BLOCK marker found in file"
        code = code[:bidx] + body + code[bidx+1:]
        return code

    def file_header(self, exe: bool = True) -> Block:
        """File header."""
        return (
            self.lcom() +
            self.lcom(f"Generated by JSON Model Compiler version {self.version()}") +
            self.lcom("see https://github.com/clairey-zx81/json-model") +
            self.lcom()
        )

    def file_footer(self, exe: bool = True) -> Block:
        """File footer."""
        return []

    #
    # type tests
    #
    def is_num(self, var: Var) -> BoolExpr:
        """Is JSON variable a number?"""
        raise NotImplementedError("is_num")

    def is_def(self, var: Var) -> BoolExpr:
        """Is JSON variable defined?"""
        raise NotImplementedError("is_def")

    def is_scalar(self, var: Var) -> BoolExpr:
        """Is JSON variable a scalar?"""
        raise NotImplementedError("is_scalar")

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        """Is JSON variable of this type?"""
        raise NotImplementedError("is_a")

    def str_content_predef(self, name: str) -> bool:
        """Predef (probably costly) about string contents."""
        return name in ("$DATE", "$TIME", "$DATETIME",
            "$URL", "$REGEX", "$EXREG", "$UUID", "$URI", "$EMAIL", "$JSON")

    #
    # predefs
    #
    # FIXME loose vs strict
    #
    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        """Compile a predef."""
        # shortcut if the variable value is known to be a string
        if is_str:
            if name in { "$NULL", "$BOOL", "$BOOLEAN",
                         "$INT", "$INTEGER", "$I32", "$I64", "$U32", "$U64",
                         "$FLOAT", "$F32", "$F64", "$NUMBER" }:
                name = "$NONE"
            elif name == "$STRING":
                name = "$ANY"
        # else full type checks
        if name == "$ANY":
            return self.true()
        elif name == "$NONE":
            return self.false()
        elif name == "$NULL":
            return self.is_a(var, None)
        elif name in ("$BOOL", "$BOOLEAN"):
            return self.is_a(var, bool)
        elif name in ("$INT", "$INTEGER", "$I32", "$I64"):
            return self.is_a(var, int)
        elif name in ("$U32", "$U64"):
            return self.and_op(self.is_a(var, int),
                               self.num_cmp(self.value(var, int), ">=", self.const(0)))
        elif name in ("$FLOAT", "$F32", "$F64"):
            return self.is_a(var, float)
        elif name == "$NUMBER":
            return self.is_a(var, Number)  # type: ignore
        elif name == "$STRING":
            return self.is_a(var, str)
        elif str_content_predef(name):
            raise NotImplementedError(f"predef: {name}")
        else:
            raise NotImplementedError(f"unexpected predef {name}")

    #
    # constants
    #
    def const(self, c: Jsonable) -> Expr:
        """Build a constant expression for a value."""
        if c is None:
            return self._null
        elif isinstance(c, bool):
            return self._true if c else self._false
        elif isinstance(c, str):
            return self.esc(c)
        else:
            return str(c)

    def true(self) -> BoolExpr:
        return self.const(True)  # pyright: ignore

    def false(self) -> BoolExpr:
        return self.const(False)  # pyright: ignore

    #
    # inline json scalar value extraction
    #
    def value(self, var: Var, tvar: type) -> Expr:
        """Extract a type from JSON var."""
        if tvar in (bool, int, float, Number, str):
            return var
        else:
            raise Exception(f"unexpected type for value extraction: {tvar.__name__}")

    def get_value(self, var: str, tvar: type) -> Expr:
        """Extract a typed value from a variable of this type."""
        return var

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        """Get array item for an index."""
        return f"{arr}[{idx}]"

    def obj_prop_val(self, obj: Var, prop: Var, is_var: bool = False) -> JsonExpr:
        """Get object property value."""
        raise NotImplementedError("obj_prop_val")

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        """Tell whether an object as a property."""
        raise NotImplementedError("has_prop")

    def assign_obj_prop(self) -> bool:
        """Whether testing for a property can be combined with an assignment."""
        return True

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
        """Combined property test and value extraction, if assign_obj_prop."""
        raise NotImplementedError("obj_has_prop_val")

    #
    # inlined length computation
    #
    def any_len(self, var: Var) -> IntExpr:
        """Get length of variable."""
        raise NotImplementedError("any_len")

    def obj_len(self, var: Var) -> IntExpr:
        """Get number of properties of an object."""
        return self.any_len(var)

    def arr_len(self, var: Var) -> IntExpr:
        """Get number of items of an array."""
        return self.any_len(var)

    def str_len(self, var: Var) -> IntExpr:
        """Get length of a string."""
        return self.any_len(var)

    def str_start(self, val: Var, start: str) -> BoolExpr:
        raise NotImplementedError("str_start")

    def str_end(self, val: Var, end: str) -> BoolExpr:
        raise NotImplementedError("str_end")

    def str_hash(self, val: Var, size: int = 1) -> IntExpr:
        """Get hash for string partitioning purpose."""
        raise NotImplementedError("str_hash")

    def any_int_val(self, val: JsonExpr, tval: type) -> IntExpr:
        """Known type int extraction for constraints."""
        if tval is int:
            return self.value(val, int)
        elif tval is str:
            return self.str_len(self.value(val, str))  # type: ignore
        elif tval is list:
            return self.arr_len(val)
        elif tval is dict:
            return self.obj_len(val)
        else:
            raise Exception(f"unexpected type for any_int_val: {tval.__name__}")

    #
    # boolean expression
    #
    def rep(self) -> str:
        """Current report variable."""
        return "rep" if self._with_report else "None"

    def path(self, p: str) -> str:
        return p if self._with_path else "None"

    def str_check_call(self, name: str, val: StrExpr, path: Var) -> BoolExpr:
        """Model check call for a string value."""
        return f"{name}({val}, {self.path(path)}, {self.rep()})"

    def check_call(self, name: Var, val: JsonExpr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        """Model check call for a JSON value.

        is_ptr: the name is a function pointer, not a direct function
        is_raw: value is a raw (string) value, not a json
        """
        return f"{name}({val}, {self.path(path)}, {self.rep()})"

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        """Check uniqueness."""
        raise NotImplementedError("check_unique")

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        """Check constraint."""
        raise NotImplementedError("check_constraint")

    #
    # logical expressions
    #
    def not_op(self, e: BoolExpr) -> BoolExpr:
        """Not logical operator."""
        e = self.paren(e) if "=" in e or self._and in e or self._or in e else e  # type: ignore
        return f"{self._not} {e}"

    def and_op(self, *exprs: BoolExpr) -> BoolExpr:
        """And logical operator."""
        return f" {self._and} ".join(self.paren(e) if self._or in e else e  # type: ignore
                                        for e in exprs)

    def or_op(self, *exprs: BoolExpr) -> BoolExpr:
        """Or logical operator."""
        return f" {self._or} ".join(exprs)  # type: ignore

    def paren(self, e: Expr) -> Expr:
        """Parenthesize an expression."""
        return f"({e})"

    #
    # inline comparison expressions for numbers
    #
    def num_cmp(self, e1: NumExpr, op: str, e2: NumExpr, hexa: bool = False) -> BoolExpr:
        """Numerical comparison."""
        assert op in ("=", "!=", "<", "<=", ">=", ">")
        if hexa and isinstance(e2, int):
            e2 = hex(e2)
        if op == "=":
            return f"{e1} {self._eq} {e2}"
        elif op == "!=":
            return f"{e1} {self._ne} {e2}"
        elif op == "<":
            return f"{e1} {self._lt} {e2}"
        elif op == "<=":
            return f"{e1} {self._le} {e2}"
        elif op == ">=":
            return f"{e1} {self._ge} {e2}"
        elif op == ">":
            return f"{e1} {self._gt} {e2}"
        else:
            raise Exception(f"num_cmp unexpected op {op}")

    #
    # inline comparison expressions for strings
    #
    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        """String comparison."""
        return self.num_cmp(e1, op, e2)

    def assign_expr(self) -> bool:
        """Whether there is an assign expression in the language."""
        return True

    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        """Get check value fonction for a property and tell whether it got one."""
        raise NotImplementedError("prop_fun with assign expression")

    def has_prop_fun(self, prop: str, mapname: str) -> BoolExpr:
        """Whether property has a check function in the map."""
        raise NotImplementedError("has_prop_fun")

    def get_prop_fun(self, prop: str, mapname: str) -> Expr:
        """get check function for property."""
        raise NotImplementedError("has_prop_fun")

    #
    # for JSON values
    #
    def json_eq(self, e1: Expr, e2: Expr) -> BoolExpr:
        """Compare JSON values."""
        return f"{e1} {self._eq} {e2}"

    def json_ne(self, e1: Expr, e2: Expr) -> BoolExpr:
        """Compare JSON values."""
        return f"{e1} {self._ne} {e2}"

    #
    # simple instructions
    #
    def nope(self) -> Block:
        """Do nothing."""
        raise NotImplementedError("var")

    def lcom(self, text: str = "") -> Block:
        """Generate lines comment."""
        if self._with_comment:
            if text:
                return [ f"{self._lcom} {t}" for t in re.split(r"[\n\r\f]", text) ]
            else:
                return [ self._lcom ]
        else:
            return []

    def sequence(self, seq: Block) -> Block:
        """Block in block which may be created by IR optimizations."""
        return seq

    def _var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        """Declare and/or assign a variable with a type."""
        raise NotImplementedError("var")

    def json_var(self, var: Var, val: JsonExpr|None = None, declare: bool = False) -> Block:
        """Declare a JSON variable."""
        return self._var(var, val, self._json_t if declare else None)

    def bool_var(self, var: Var, val: BoolExpr|None = None, declare: bool = False) -> Block:
        """Declare a boolean variable."""
        return self._var(var, val, self._bool_t if declare else None)

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        """Declare and assign to int variable."""
        return self._var(var, val, self._int_t if declare else None)

    def str_var(self, var: Var, val: StrExpr|None = None, declare: bool = False) -> Block:
        """Declare and assign to str variable."""
        return self._var(var, val, self._str_t if declare else None)

    def flt_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        """Declare and assign to str variable."""
        return self._var(var, val, self._float_t if declare else None)

    def fun_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        """Declare a check function variable pointer."""
        # FIXME should guard for scalar?
        return self._var(var, val, self._check_t if declare else None)

    def path_var(self, pvar: Var, val: PathExpr|None = None, declare: bool = False) -> Block:
        """Assign and possibly declare a value to a path variable."""
        return self._var(pvar, val, self._path_t if declare else None) if self._with_path else []

    def match_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        """Assign and possibly declare a match result variable."""
        return self._var(var, val, self._match_t if declare else None)

    def hash_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        """Assign and possibly declare a value to a hash variable."""
        return self._var(var, val, self._hash_t if declare else None)

    def match_ko(self, var: Var) -> BoolExpr:
        return self.not_op(var)

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        """Declare a variable for a matching result extracted from val."""
        # the value is just as a length helper
        return self.str_var(var, None, declare)

    def iand_op(self, res: Var, e: BoolExpr) -> Block:
        """And-update boolean variable."""
        return [ "{var} &= {e}{self._eoi}" ]

    def inc_var(self, var: Var) -> Block:
        """Increment integer variable."""
        return [ f"{var} += 1{self._eoi}" ]

    def ret(self, res: BoolExpr) -> Block:
        """Return boolean result."""
        return [ f"return {res}{self._eoi}" ]

    def brk(self) -> Block:
        """Break from surrounding loop."""
        return [ f"break{self._eoi}" ]

    def cont(self) -> Block:
        """Skip to next loop interation."""
        return [ f"continue{self._eoi}" ]

    def esc(self, s: str) -> StrExpr:
        """Escape string, with double quotes."""
        # FIXME too late!
        # log.warning(f"esc: {s}")
        if isinstance(s, bool):
            s = "true" if s else "false"
        return '"' + s.replace("\\", "\\\\").replace('"', r'\"') + '"'

    def skip(self) -> Block:
        """Skip one line."""
        return [ "" ]

    def ignore(self) -> Block:
        """Ignore this line."""
        return []

    #
    # paths:
    #
    # fun(path: Path)
    # lpath: Path = path + [ segment ]  # if path is not None, else None !
    # checker(val, lpath, ...)
    #
    # fun(Path* path)
    # Path lpath = (Path) { ..., path }
    # checker(val, path ? &lpath : NULL, ...)
    #
    # TODO consider merging path_var and path_val?
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        """Append a segment variable/value to path."""
        raise NotImplementedError("see derived classes")

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        # avoid nested if expressions
        raise NotImplementedError("see derived classes")

    #
    # blocks
    #
    def is_reporting(self) -> BoolExpr:
        """Test whether run is generating a report."""
        raise NotImplementedError("see derived classes")

    def report(self, msg: str, path: Var) -> Block:
        """Add a a report entry."""
        raise NotImplementedError("see derived classes")

    def clean_report(self) -> Block:
        raise NotImplementedError("see derived classes")

    def indent(self, block: Block, sep: bool = True) -> Block:
        """Indent a block, but not empty lines though."""
        return [
            ((self._indent + line) if line else line)
                for line in filter(lambda s: s is not None, block)
        ]

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        """Loop over integers from start to end (excluded)."""
        raise NotImplementedError("int_loop")

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        """Loop over all items of an array."""
        raise NotImplementedError("arr_loop")

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        """Loop over all property-values pairs of an object."""
        raise NotImplementedError("obj_loop")

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        """Generate a if-then[-else] statement."""
        raise NotImplementedError("if_stmt")

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        """Generate a multi-if[-else] statement."""
        raise NotImplementedError("mif_stmt")

    #
    # PROPERTY MAPPING : property value (constant string) to check function
    #
    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        """Define a new (property) map."""
        return []

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        """Generate a subroutine for the property map."""
        return []

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        """Initialize a map."""
        return []

    def del_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        """Remove initial stuff for a property map."""
        return []

    #
    # CONSTANT SET FOR ENUM OPTIMIZATION
    #
    def def_cset(self, name: str, constants: ConstList) -> Block:
        """Declare a constant set."""
        return []

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        """Initialize a constant set with constants."""
        return []

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        """Test whether variable value belongs to constant set."""
        raise NotImplementedError("see derived classes")

    def del_cset(self, name: str, constants: ConstList) -> Block:
        """Remove stuff for constant set."""
        return []

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        """Generate support function for constant set check."""
        return []

    #
    # CHECK FUNCTION SIGNATURE
    #
    def def_fun(self, name: str) -> Block:
        """Define a function."""
        return []

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        """Generate a check function, with an inline request."""
        raise NotImplementedError("see derived classes")

    def def_strfun(self, name: str) -> Block:
        """Define a string check function."""
        return []

    def sub_strfun(self, name: str, body: Block) -> Block:
        raise NotImplementedError("see derived classes")

    #
    # REGULAR EXPRESSION PRECOMPILATION
    #
    def regroup(self, name: str, pattern: str = ".*") -> str:
        """Name a group in a regular expression."""
        return f"(?<{name}>{pattern})"

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        """Generate a regex check function."""
        return []

    def def_re(self, name: str, regex: str, opts: str) -> Block:
        """Define a new (static) regex."""
        return []

    def ini_re(self, name: str, regex: str, opts: str) -> Block:
        """Initialize a regex."""
        return []

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        """Free a regex."""
        return []

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        """Get a match result for string variable var value."""
        raise NotImplementedError("see derived classes")

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        """Assign match "name" to variable sname."""
        raise NotImplementedError("see derived classes")

    #
    # CONSTANT MAPPING FOR DISCRIMINANT OPTIMIZATION
    # constant value to check function
    #
    def _str_map(self, mapping: dict[JsonScalar, str]) -> bool:
        return all(isinstance(k, str) for k in mapping.keys())

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        """Return the function associated to the tag value if any."""
        raise NotImplementedError("see derived classes")

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        """Declare a new constant map."""
        return []

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        """Initialize constant mapping."""
        return []

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        """Generate support function for mapping."""
        return []

    def del_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        """Remove stuff for mapping."""
        return []

    #
    # FUNCTIONS
    #
    def gen_init(self, init: Block) -> Block:
        """Generate the initialization function."""
        raise NotImplementedError("gen_init")

    def gen_free(self, free: Block) -> Block:
        """Generate the deallocation function."""
        raise NotImplementedError("gen_free")

    def gen_code(self, code: Block, entry: str, package: str|None, indent: bool = False) -> Block:
        """Generate substituted code."""
        if indent:
            code = self.indent(code, False)
        return [
            line.replace("CHECK_FUNCTION_NAME", entry)
                .replace("CHECK_PACKAGE_NAME", package or "")
                    for line in code
        ]

    def gen_full_code(self,
                defs: Block, inis: Block, dels: Block, subs: Block,
                entry: str, package: str|None, exe: bool
            ) -> Block:
        """Generate final code block."""

        # FIXME TODO remove, this is a bad idea
        # compute init first as predefs may trigger more imports
        inis = self.gen_init(inis)
        dels = self.gen_free(dels)

        # reduce with empty lines between parts
        code: Block = self.gen_code(self.file_header(exe), entry, package)

        for block in (defs, subs, inis, dels):
            if code and block:
                code += self.skip()
            code += self.gen_code(block, entry, package, self.reindent)

        code += self.gen_code(self.file_footer(exe), entry, package)

        return code

    def code_to_str(self, code: Block) -> str:
        """Generate a final string for code display."""
        return self._isep.join(filter(lambda s: s is not None, code)) + "\n"

    def filter_code(self, code: Block) -> Block:
        """Textual optimizations: (late) backend-specific code filtering."""
        return code


class Code:
    """Hold generated source code for a model.

    - `language`: language generator
    - `entry`: name of the entry function
    - `executable`: generate a script or a module
    - `package`: generated name space
    """

    def __init__(self,
                lang: Language,
                entry: str = "check_model",
                executable: bool = True,
                package: str|None = None):
        self._lang = lang              # generated language abstraction
        self._entry = entry            # entry function name/prefix
        self._package = package        # generated name space
        self._executable = executable  # executable (shebang, main) vs module
        self._defs: Block = []         # definitions and declarations
        self._inis: Block = []         # initialization code
        self._dels: Block = []         # deallocation code
        self._subs: Block = []         # actual subroutines
        self._shortcuts = {}            # function shortcuts

    #
    # add blocks
    #
    def defs(self, b: Block|None = None):
        """Add lines to definitions."""
        self._defs += b if b is not None else self._lang.skip()

    def subs(self, b: Block|None = None):
        """Add lines to subroutines."""
        if self._subs:
            self._subs += self._lang.skip()
        self._subs += b if b is not None else self._lang.skip()

    def inis(self, b: Block|None = None):
        """Add lines to initialization code."""
        self._inis += b if b is not None else self._lang.skip()

    def dels(self, b: Block|None = None):
        """Add lines to cleanup code."""
        self._dels += b if b is not None else self._lang.skip()

    # TODO rename!
    def sub(self, name: str, body: Block, *, comment: str = "", inline: bool = False):
        """Add a function definition with a comment."""
        self.defs(self._lang.def_fun(name))
        fun = self._lang.lcom(comment) if comment else []
        fun += self._lang.sub_fun(name, body, inline=inline)
        self.subs(fun)

    def pmap(self, name: str, mapping: PropMap, public: bool = False):
        """Add a (property/name) mapping."""
        self.defs(self._lang.def_pmap(name, mapping, public))
        self.inis(self._lang.ini_pmap(name, mapping, public))
        self.dels(self._lang.del_pmap(name, mapping, public))
        self.subs(self._lang.sub_pmap(name, mapping, public))

    def cset(self, name: str, constants: ConstList):
        """Add a constant set."""
        self.defs(self._lang.def_cset(name, constants))
        self.inis(self._lang.ini_cset(name, constants))
        self.dels(self._lang.del_cset(name, constants))
        self.subs(self._lang.sub_cset(name, constants))

    def cmap(self, name: str, mapping: ConstMap):
        """Add a constant value mapping."""
        self.defs(self._lang.def_cmap(name, mapping))
        self.inis(self._lang.ini_cmap(name, mapping))
        self.dels(self._lang.del_cmap(name, mapping))
        self.subs(self._lang.sub_cmap(name, mapping))

    def regex(self, name: str, regex: str, opts: str):
        """Add a regex."""
        self.defs(self._lang.def_re(name, regex, opts))
        self.inis(self._lang.ini_re(name, regex, opts))
        self.dels(self._lang.del_re(name, regex, opts))
        self.subs(self._lang.sub_re(name, regex, opts))

    def strfun(self, name: str, body: Block):
        """Add a string function."""
        self.defs(self._lang.def_strfun(name))
        self.subs(self._lang.sub_strfun(name, body))

    def get_code(self):
        """Generate final code block."""
        return self._lang.filter_code(
            self._lang.gen_full_code(
                self._defs, self._inis, self._dels, self._subs,
                self._entry, self._package, self._executable
            )
        )

    def __str__(self):
        """Gather everything to generate the full source code."""
        return self._lang.code_to_str(self.get_code())
