#
# JSON backend intermediate representation
#
import functools
import json

from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number

def _j(op: str, **params) -> str:
    """Generate a JSON operation."""
    return json.dumps({"o": op, **params})

def _l(s: str) -> Jsonable:
    return json.loads(s) if s is not None and s and s[0] == "{" else s

def _u(block: Block) -> list[Jsonable]:
    return [ _l(l) for l in filter(lambda s: s is not None and s != "", block) ]


class IRep(Language):
    """Generate JSON intermediate representation of backend code."""

    def __init__(self, debug: bool = False):
        super().__init__("JSON", indent=",", debug=debug)

    def lcom(self, text: str = "") -> Block:
        return [ _j("co", text=text) ]

    def file_header(self, exe: bool = True) -> Block:
        return [ _j("fh", exe=exe, version=self.version()) ]

    def file_footer(self, exe: bool = True) -> Block:
        return [ _j("ff", exe=exe) ]

    def is_num(self, var: Var) -> BoolExpr:
        return _j("in", var=_l(var))

    def is_scalar(self, var: Var) -> BoolExpr:
        return _j("is", var=_l(var))

    def is_def(self, var: Var) -> BoolExpr:
        return _j("id", var=_l(var))

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        return _j("isa", var=_l(var), tval=tval if not tval else tval.__name__, loose=loose)

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return _j("jc", json=j)

    def const(self, c: Jsonable) -> Expr:
        return _j("cst", cst=c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return _j("hp", obj=_l(obj), prop=prop)

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        return _j("pre", var=_l(var), name=name, path=_l(path), is_str=is_str)
    
    def value(self, var: Var, tvar: type) -> Expr:
        return _j("val", var=_l(var), tvar=tvar.__name__)

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return _j("aiv", arr=_l(arr), idx=_l(idx))

    def obj_prop_val(self, obj: Var, prop: Expr, is_var: bool = False) -> JsonExpr:
        return _j("opv", obj=_l(obj), prop=_l(prop), is_var=is_var)

    def obj_len(self, var: Var) -> IntExpr:
        return _j("ol", var=_l(var))

    def arr_len(self, var: Var) -> IntExpr:
        return _j("al", var=_l(var))

    def str_len(self, var: Var) -> IntExpr:
        return _j("sl", var=_l(var))

    def any_len(self, var: Var) -> IntExpr:
        return _j("nl", var=_l(var))

    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return _j("apf", fun=fun, prop=prop, mapname=mapname)

    def str_start(self, val: str, start: str) -> BoolExpr:
        return _j("ss", val=val, start=start)

    def str_end(self, val: str, end: str) -> BoolExpr:
        return _j("se", val=val, end=end)

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        return _j("cc", name=name, val=_l(val), path=_l(path), is_ptr=is_ptr, is_raw=is_raw)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return _j("cu", val=_l(val), path=_l(path))

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return _j("cc", op=op, vop=vop, val=_l(val), path=_l(path))

    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        return _j("sc", e1=_l(e1), op=op, e2=_l(e2))

    def nope(self) -> Block:
        return [ _j("no") ]

    def var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        return [ _j("v", var=_l(val), val=_l(val), tname=tname) ]

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        return [ _j("iv", var=_l(var), val=_l(val), declare=declare) ]

    def brk(self) -> Block:
        return [ _j("brk") ]

    def inc_var(self, var: Var) -> Block:
        return [ _j("iv", var=_l(var)) ]

    def ret(self, res: BoolExpr) -> Block:
        return [ _j("ret", res=_l(res)) ]

    def not_op(self, e: BoolExpr) -> BoolExpr:
        return _j("not", e=_l(e))

    def and_op(self, *exprs: BoolExpr) -> BoolExpr:
        return _j("and", exprs=_u(exprs))

    def iand_op(self, res: Var, e: BoolExpr) -> Block:
        return [ _j("iand", res=_l(res), e=_l(e)) ]

    def or_op(self, *exprs: BoolExpr) -> BoolExpr:
        return _j("or", exprs=_u(exprs))

    def paren(self, e: Expr) -> Expr:
        return _j("()", e=_l(e))

    def is_reporting(self) -> BoolExpr:
        return _j("isr")

    def report(self, msg: str, path: Var) -> Block:
        return [ _j("rep", msg=msg, path=_l(path)) ]

    def clean_report(self) -> Block:
        return [ _j("cr") ]

    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool) -> PathExpr:
        return _j("pv", pvar=_l(pvar), pseg=pseg, is_prop=is_prop)

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return _j("pl", lvar=_l(lvar), rvar=_l(rvar))

    def indent(self, block: Block, sep: bool = True) -> Block:
        raise Exception("indentation not a IR operation")

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [ _j("al", arr=_l(arr), idx=_l(idx), val=_l(val), body=_u(body)) ]

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [ _j("ol", obj=_l(obj), key=_l(key), val=_l(val), body=_u(body)) ]

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [ _j("il", idx=_l(idx), start=_l(start), end=_l(end), body=_u(body)) ]

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = []) -> Block:
        return [ _j("if", cond=_l(cond), true=_u(true), false=_u(false)) ]

    def mif_stmt(self, cond_true: list[tuple[BoolExpr, Block]], false: Block = []) -> Block:
        return [ _j("ifs", cond_true=[ (_l(c), _u(b)) for c, b in cond_true ], false=_u(false)) ]

    # FIXME language dependent internal regex operations
    def regroup(self, name: str, pattern: str = ".*") -> str:
        return f"(?P<{name}>{pattern})" if self._relib == "re2" else super().regroup(name, pattern)

    def def_re(self, name: str, regex: str, opts: str) -> Block:
        return [ _j("dr", name=name, regex=regex, opts=opts) ]

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        return [ _j("sr", name=name, regex=regex, opts=opts) ]

    def ini_re(self, name: str, regex: str, opts: str) -> Block:
        return [ _j("ir", name=name, regex=regex, opts=opts) ]

    def del_re(self, name: str, regex: str, opts: str) -> Block:
        return [ _j("rr", name=name, regex=regex, opts=opts) ]

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = False) -> Block:
        return [ _j("msv", rname=rname, var=var, val=val, declare=declare) ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        return _j("mr", name=name, var=var, regex=regex, opts=opts)

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        return [ _j("mv", mname=mname, rname=rname, sname=sname, dname=dname, declare=declare) ]

    def def_strfun(self, name: str) -> Block:
        return [ _j("ds", name=name) ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ _j("ssf", name=name, body=_u(body)) ]

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("dpm", name=name, pmap=pmap, public=public) ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("ipm", name=name, pmap=pmap, public=public) ]

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("spm", name=name, pmap=pmap, public=public) ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("dcs", name=name, constants=constants) ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("scs", name=name, constants=constants) ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return _j("incs", name=name, var=var, constants=constants)

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("ics", name=name, var=var, constants=constants) ]

    def def_fun(self, name: str) -> Block:
        return [ _j("dfu", name=name) ]

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ _j("sfu", name=name, body=_u(body), inline=inline) ]

    # FIXME dict key
    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("dcm", name=name, mapping=mapping) ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("scm", name=name, mapping=mapping) ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("icm", name=name, mapping=mapping) ]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return _j("gcm", name=name, tag=_l(tag), ttag=ttag.__name__)

    def gen_init(self, init: Block) -> Block:
        return [ _j("gi", init=_u(init)) ]

    def gen_free(self, free: Block) -> Block:
        return [ _j("gf", free=_u(free)) ]

    def gen_code(self, code: Block, entry: str, package: str|None, indent: bool = False) -> Block:
        return [ _j("c", code=_u(code), entry=entry, package=package, indent=indent) ]

    def gen_full_code(self, defs: Block, inis: Block, dels: Block, subs: Block,
                      entry: str, package: str|None, exe: bool) -> Block:
        return [ _j("fc", defs=_u(defs), inis=_u(inis), dels=_u(dels), subs=_u(subs),
                    entry=entry, package=package, exe=exe) ]

    def code_to_str(self, code: Block) -> str:
        if len(code) == 0:
            return ""
        elif len(code) == 1:
            return code[0]
        else:
            return json.dumps([ _l(l) for l in code ])

    def _str2type(self, tname: str|None) -> type:
        match tname:
            case None: return None
            case "null": return None
            case "bool": return bool
            case "int": return int
            case "float": return float
            case "str": return str
            case "Path": return Path
            case "Report": return Report
            case _: raise Exception(f"unexpected type name: {tname}")

    def evaluate(self, code: Jsonable, lang: Language) -> Block|Expr:
        """Evaluate IR for a target a language."""

        # convenient recursion shortcut
        def ev(v: Jsonable):
            return self.evaluate(v, lang)

        if code is None:
            raise Exception("cannot evaluate null")
        elif isinstance(code, dict) and "o" in code:
            op = code["o"]
            match op:
                case "co": return lang.lcom(text=code["text"])
                case "fh": return lang.file_header(exe=code["exe"])
                case "dfu": return lang.def_fun(name=code["name"])
                case _: raise Exception(f"unexpected op code: {op}")
        elif isinstance(code, list):
            return [ ev(i) for i in code ]
        elif isinstance(code, str) and code == "":
            return [ "" ]
        else:  # optimistic!
            return code
