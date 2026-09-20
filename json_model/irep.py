#
# JSON backend intermediate representation
#
from typing import Callable
import functools
import json
import copy

from .utils import log
from .language import Language, Block, Var, PropMap, ConstList, Code
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, NumExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals, TopType, NullType
from .runtime import Path, Report

#
# build intermediate representation
#

def _j(o: str, **params) -> str:
    """Generate a JSON operation."""
    return json.dumps({"o": o, **params})

def _l(s: str) -> Jsonable:
    """Parse a JSON operation or something else."""
    # FIXME true/false/null handling is adhoc and can be wrong
    try:
        if (isinstance(s, str) and s and
                (s[0] in '{["0123456789-' or s in ("null", "true", "false"))):
            return json.loads(s)
        else:
            return s
    except Exception:
        # FIXME triggered on strange property names, eg "[a-z]"
        log.warning(f"shamefully ignoring json oops on {s}")
        return s

def _u(block: Block) -> list[Jsonable]:
    """Parse a JSON code block."""
    return [ _l(i) for i in filter(lambda s: s is not None and s != "", block) ]

# constant map to json and reverse
def _cmap2json(mapping: dict[JsonScalar, str]) -> list[tuple[JsonScalar, str]]:
    return [ ( c, s ) for c, s in mapping.items() ]

def _json2cmap(mapping: list[tuple[JsonScalar, str]]) -> dict[JsonScalar, str]:
    return { c: s for c, s in mapping }

def _t2s(tvar: type|None) -> str:
    """Type to IR type name conversion."""
    if tvar is None:
        return "none"
    elif tvar is NullType:
        return "null"
    elif tvar is bool:
        return "bool"
    elif tvar is int:
        return "integer"
    elif tvar is float:
        return "number"
    elif tvar is str:
        return "string"
    elif tvar is list:
        return "array"
    elif tvar is dict:
        return "object"
    elif tvar is Number:
        return "Number"
    elif tvar is Path:
        return "Path"
    elif tvar is Report:
        return "Report"
    elif tvar is TopType:
        return "any"
    raise Exception(f"unexpected type: {tvar}")

class IRep(Language):
    """Generate JSON intermediate representation of backend code.

    This class basically defer code generation calls using an intermediate JSON structure
    to hold the function and its parameters.

    NOTE this is currently pretty inefficient, with useless back and forth json encodings
    that artificially preserve the initial Block (list[str]) and Expr (str) typing.
    """

    def __init__(
                self, lang: Language|None, *,
                debug: bool = False, if_optim: bool = True,
                with_comment: bool = True, with_report: bool = True,
            ):
        super().__init__(
            "JSON", indent=",",
            debug=debug, with_comment=with_comment, with_report=with_report
        )
        self._lang = lang or self
        self._if_optim = if_optim
        self._byte_order = lang._byte_order if lang else "le"

    # language dependent stuff is forwarded to the underlying language if any
    def fast_strlen(self) -> bool:
        return self._lang._fast_strlen

    def assign_expr(self) -> bool:
        return self._lang.assign_expr() if self._lang != self else True

    def assign_obj_prop(self) -> bool:
        return self._lang.assign_obj_prop() if self._lang != self else True

    def regroup(self, name: str, pattern: str = ".*") -> str:
        return self._lang.regroup(name, pattern) if self._lang != self else \
            super().regroup(name, pattern)

    def indent(self, block: Block, sep: bool = True) -> Block:
        raise Exception("indentation not a IR operation")

    # generic code generation
    def lcom(self, text: str = "", force: bool = False) -> Block:
        return [ _j("co", text=text, force=force) ] if self._with_comment or force else []

    def file_header(self, exe: bool = True, mark: str|None = None) -> Block:
        return [ _j("fh", exe=exe, mark=mark, version=self.version()) ]

    def file_footer(self, exe: bool = True) -> Block:
        return [ _j("ff", exe=exe) ]

    def is_num(self, var: Var) -> BoolExpr:
        return _j("in", var=_l(var))

    def is_scalar(self, var: Var) -> BoolExpr:
        return _j("is", var=_l(var))

    def is_def(self, var: Var) -> BoolExpr:
        return _j("id", var=_l(var))

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        return _j("isa", var=_l(var), tval=_t2s(tval), loose=loose)

    def esc(self, s: str) -> StrExpr:
        return _j("esc", s=s)

    def esc_msg(self, s: str) -> StrExpr:
        return Language.esc(self, s)

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return _j("jc", j=j)

    def const(self, c: Jsonable) -> Expr:
        return _j("cst", c=c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return _j("hp", obj=_l(obj), prop=prop)

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False, is_val: bool = False) -> BoolExpr:
        return _j("pre", var=_l(var), name=name, path=_l(path), is_str=is_str, is_val=is_val)

    def value(self, var: Var, tvar: type, loose: bool = False) -> Expr:
        return _j("val", var=_l(var), tvar=_t2s(tvar), loose=loose)

    def get_value(self, var: str, tvar: type) -> Expr:
        return _j("gv", var=var, tvar=_t2s(tvar))

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return _j("aiv", arr=_l(arr), idx=_l(idx))

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return _j("opv", obj=_l(obj), prop=prop, is_var=is_var)

    def obj_has_prop_val(
            self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False
        ) -> BoolExpr:
        return _j("cpv", dst=_l(dst), obj=_l(obj), prop=prop, is_var=is_var)

    def obj_len(self, var: Var) -> IntExpr:
        return _j("ol", var=_l(var))

    def arr_len(self, var: Var) -> IntExpr:
        return _j("al", var=_l(var))

    def str_len(self, var: Var) -> IntExpr:
        return _j("sl", var=_l(var))

    def any_len(self, var: Var) -> IntExpr:
        return _j("nl", var=_l(var))

    def str_hash(self, val: Var, size: int = 1) -> IntExpr:
        return _j("sh", val=_l(val), size=size)

    def assign_prop_fun(self, fun: str, prop: str, mapname: str) -> BoolExpr:
        return _j("apf", fun=fun, prop=prop, mapname=mapname)

    def has_prop_fun(self, prop: str, mapname: str) -> BoolExpr:
        return _j("hpf", prop=prop, mapname=mapname)

    def get_prop_fun(self, prop: str, mapname: str) -> BoolExpr:
        return _j("gpf", prop=prop, mapname=mapname)

    def str_start(self, val: Var, start: StrExpr) -> BoolExpr:
        return _j("ss", val=_l(val), start=_l(start))

    def str_end(self, val: Var, end: StrExpr) -> BoolExpr:
        return _j("se", val=_l(val), end=_l(end))

    def str_check_call(self, name: str, val: StrExpr, path: Var) -> BoolExpr:
        return _j("scc", name=name, val=_l(val), path=_l(path))

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        return _j("cc", name=name, val=_l(val), path=_l(path), is_ptr=is_ptr, is_raw=is_raw)

    def check_unique(self, val: JsonExpr, titem: type|None, path: Var) -> BoolExpr:
        return _j("cu", val=_l(val), titem=_t2s(titem), path=_l(path))

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return _j("ct", op=op, vop=vop, val=_l(val), path=_l(path))

    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        return _j("sc", e1=_l(e1), op=op, e2=_l(e2))

    def num_cmp(
            self, e1: NumExpr, op: str, e2: NumExpr, hexa: bool = False, is_int: bool = True
        ) -> BoolExpr:
        return _j("nc", e1=_l(e1), op=op, e2=_l(e2), hexa=hexa, is_int=is_int)

    def nope(self) -> Block:
        return [ _j("no") ]

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        return [ _j("iv", var=_l(var), val=_l(val), declare=declare) ]

    def bool_var(self, var: Var, val: BoolExpr|None = None, declare: bool = False) -> Block:
        return [ _j("bv", var=_l(var), val=_l(val), declare=declare) ]

    def path_var(self, pvar: Var, val: PathExpr|None = None, declare: bool = False) -> Block:
        return [ _j("pv", pvar=_l(pvar), val=_l(val), declare=declare) ]

    def json_var(self, var: Var, val: JsonExpr|None = None, declare: bool = False) -> Block:
        return [ _j("jv", var=_l(var), val=_l(val), declare=declare) ]

    def str_var(self, var: Var, val: StrExpr|None = None, declare: bool = False) -> Block:
        return [ _j("sv", var=_l(var), val=_l(val), declare=declare) ]

    def hash_var(self, var: Var, val: StrExpr|None = None, declare: bool = False) -> Block:
        return [ _j("hv", var=_l(var), val=_l(val), declare=declare) ]

    def flt_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        return [ _j("fv", var=_l(var), val=_l(val), declare=declare) ]

    def fun_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        return [ _j("Fv", var=_l(var), val=_l(val), declare=declare) ]

    def brk(self) -> Block:
        return [ _j("brk") ]

    def cont(self) -> Block:
        return [ _j("cont") ]

    def skip(self) -> Block:
        return [ _j("skip") ]

    def ignore(self) -> Block:
        return [ _j("ign") ]

    def inc_var(self, var: Var) -> Block:
        return [ _j("i+", var=_l(var)) ]

    def ret(self, res: BoolExpr) -> Block:
        return [ _j("ret", res=_l(res)) ]

    def not_op(self, e: BoolExpr) -> BoolExpr:
        return _j("not", e=_l(e))

    def and_op(self, *exprs: BoolExpr) -> BoolExpr:
        return _j("&", exprs=_u(exprs))

    def iand_op(self, res: Var, e: BoolExpr) -> Block:
        return [ _j("i&", res=_l(res), e=_l(e)) ]

    def or_op(self, *exprs: BoolExpr) -> BoolExpr:
        return _j("|", exprs=_u(exprs))

    def paren(self, e: Expr) -> Expr:
        return _j("()", e=_l(e))

    def is_reporting(self) -> BoolExpr:
        return _j("isr")

    def report(self, msg: str, path: Var) -> Block:
        return [ _j("rep", msg=msg, path=_l(path)) ] if self._with_report else []

    def clean_report(self) -> Block:
        return [ _j("cr") ] if self._with_report else []

    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool, is_var: bool) -> PathExpr:
        return _j("pvl", pvar=_l(pvar), pseg=pseg, is_prop=is_prop, is_var=is_var)

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return _j("pl", lvar=_l(lvar), rvar=_l(rvar))

    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [ _j("aL", arr=_l(arr), idx=_l(idx), val=_l(val), body=_u(body)) ]

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [ _j("oL", obj=_l(obj), key=_l(key), val=_l(val), body=_u(body)) ]

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [ _j("iL", idx=_l(idx), start=_l(start), end=_l(end), body=_u(body)) ]

    def if_stmt(
            self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None
        ) -> Block:
        return [ _j("if", cond=_l(cond), true=_u(true), false=_u(false), likely=likely) ]

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        return [
            _j("ifs", cond_true=[ (_l(c), k, _u(b)) for c, k, b in cond_true ], false=_u(false))
        ]

    def sequence(self, seq: Block) -> Block:
        return [ _j("seq", seq=_u(seq)) ]

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

    def match_var(self, var: Var, val: Expr|None = None, declare: bool = False) -> Block:
        return [ _j("mv", var=_l(var), val=_l(val), declare=declare) ]

    def match_val(
            self, mname: str, rname: str, sname: str, dname: str, declare: bool = False
        ) -> Block:
        return [ _j("mvl", mname=mname, rname=rname, sname=sname, dname=dname, declare=declare) ]

    def match_ko(self, var: Var) -> BoolExpr:
        return _j("mko", var=_l(var))

    def def_strfun(self, name: str) -> Block:
        return [ _j("dsf", name=name) ]

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [ _j("ssf", name=name, body=_u(body)) ]

    def def_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("dpm", name=name, pmap=pmap, public=public) ]

    def ini_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("ipm", name=name, pmap=pmap, public=public) ]

    def del_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("rpm", name=name, pmap=pmap, public=public) ]

    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [ _j("spm", name=name, pmap=pmap, public=public) ]

    def def_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("dcs", name=name, constants=constants) ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("scs", name=name, constants=constants) ]

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        return _j("incs", name=name, var=_l(var), constants=constants)

    def ini_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("ics", name=name, constants=constants) ]

    def del_cset(self, name: str, constants: ConstList) -> Block:
        return [ _j("rcs", name=name, constants=constants) ]

    def def_fun(self, name: str) -> Block:
        return [ _j("dfu", name=name) ]

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [ _j("sfu", name=name, body=_u(body), inline=inline) ]

    def def_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("dcm", name=name, mapping=_cmap2json(mapping)) ]

    def sub_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("scm", name=name, mapping=_cmap2json(mapping)) ]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("icm", name=name, mapping=_cmap2json(mapping)) ]

    def del_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        return [ _j("rcm", name=name, mapping=_cmap2json(mapping)) ]

    def get_cmap(self, name: str, mapping: dict[JsonScalar, str], tag: Var, ttag: type) -> Expr:
        return _j("gcm", name=name, mapping=_cmap2json(mapping), tag=_l(tag), ttag=_t2s(ttag))

    def gen_init(self, init: Block) -> Block:
        return [ _j("gi", init=_u(init)) ]

    def gen_free(self, free: Block) -> Block:
        return [ _j("gf", free=_u(free)) ]

    def gen_code(self, code: Block, entry: str, package: str|None, indent: bool = False) -> Block:
        return [ _j("gc", code=_u(code), entry=entry, package=package, indent=indent) ]

    def gen_full_code(self, defs: Block, inis: Block, dels: Block, subs: Block,
                      entry: str, package: str|None, exe: bool, mark: bool) -> Block:
        return [ _j("gfc", defs=_u(defs), inis=_u(inis), dels=_u(dels), subs=_u(subs),
                    entry=entry, package=package, exe=exe, mark=mark) ]

#
# target language reconstruction
#

def _s2t(tname: str|None) -> type:
    """String to type reconversion."""
    match tname:
        case "none": return None
        case "null": return NullType
        case "bool": return bool
        case "int"|"integer": return int
        case "float"|"number": return float
        case "Number": return Number
        case "str"|"string": return str
        case "list"|"array": return list
        case "dict"|"object": return dict
        case "Path": return Path
        case "Report": return Report
        case "any": return TopType
    raise Exception(f"unexpected type name: {tname}")

def _eval(jv: Jsonable, gen: Language) -> Block|Expr:
    """Recursive IR evaluation for the target a language."""

    # convenient recursion shortcut
    def ev(tag: str):
        # log.warning(f"{tag} -> {jv[tag]}")
        return _eval(jv[tag], gen)

    if isinstance(jv, dict) and "o" in jv:
        # introspection? generation? with a decorator?
        op = jv["o"]
        match op:
            case "co": return gen.lcom(text=jv["text"], force=jv["force"])
            case "fh": return gen.file_header(exe=jv["exe"], mark=jv["mark"])
            case "ff": return gen.file_footer(exe=jv["exe"])
            case "in": return gen.is_num(var=ev("var"))
            case "is": return gen.is_scalar(var=ev("var"))
            case "id": return gen.is_def(var=ev("var"))
            case "isa": return gen.is_a(var=ev("var"), tval=_s2t(jv["tval"]), loose=jv["loose"])
            case "esc": return gen.esc(s=jv["s"])
            case "jc": return gen.json_cst(j=jv["j"])
            case "cst": return gen.const(c=jv["c"])
            case "hp": return gen.has_prop(obj=ev("obj"), prop=jv["prop"])
            case "pre": return gen.predef(
                var=ev("var"), name=jv["name"], path=ev("path"), is_str=jv["is_str"], is_val=jv["is_val"]
            )
            case "val": return gen.value(var=ev("var"), tvar=_s2t(jv["tvar"]), loose=jv["loose"])
            case "gv": return gen.get_value(var=jv["var"], tvar=_s2t(jv["tvar"]))
            case "aiv": return gen.arr_item_val(arr=ev("arr"), idx=ev("idx"))
            case "opv": return gen.obj_prop_val(obj=ev("obj"), prop=jv["prop"], is_var=jv["is_var"])
            case "cpv": return gen.obj_has_prop_val(
                dst=ev("dst"), obj=ev("obj"), prop=jv["prop"], is_var=jv["is_var"]
            )
            case "ol": return gen.obj_len(var=ev("var"))
            case "al": return gen.arr_len(var=ev("var"))
            case "sl": return gen.str_len(var=ev("var"))
            case "nl": return gen.any_len(var=ev("var"))
            case "sh": return gen.str_hash(val=ev("val"), size=jv["size"])
            case "apf": return gen.assign_prop_fun(
                fun=jv["fun"], prop=jv["prop"], mapname=jv["mapname"]
            )
            case "hpf": return gen.has_prop_fun(prop=jv["prop"], mapname=jv["mapname"])
            case "gpf": return gen.get_prop_fun(prop=jv["prop"], mapname=jv["mapname"])
            case "ss": return gen.str_start(val=ev("val"), start=ev("start"))
            case "se": return gen.str_end(val=ev("val"), end=ev("end"))
            case "scc": return gen.str_check_call(name=jv["name"], val=ev("val"), path=ev("path"))
            case "cc": return gen.check_call(
                name=jv["name"], val=ev("val"), path=ev("path"),
                is_ptr=jv["is_ptr"], is_raw=jv["is_raw"]
            )
            case "cu": return gen.check_unique(val=ev("val"), titem=_s2t(jv["titem"]), path=ev("path"))
            case "ct": return gen.check_constraint(
                op=jv["op"], vop=jv["vop"], val=ev("val"), path=ev("path")
            )
            case "sc": return gen.str_cmp(e1=ev("e1"), op=jv["op"], e2=ev("e2"))
            case "nc": return gen.num_cmp(
                e1=ev("e1"), op=jv["op"], e2=ev("e2"), hexa=jv["hexa"], is_int=jv["is_int"]
            )
            case "()": return gen.paren(e=ev("e"))
            case "not": return gen.not_op(e=ev("e"))
            case "&": return gen.and_op(*[ _eval(e, gen) for e in jv["exprs"] ])
            case "|": return gen.or_op(*[ _eval(e, gen) for e in jv["exprs"] ])
            case "isr": return gen.is_reporting()
            case "pvl": return gen.path_val(
                pvar=ev("pvar"), pseg=jv["pseg"], is_prop=jv["is_prop"], is_var=jv["is_var"]
            )
            case "pl": return gen.path_lvar(lvar=ev("lvar"), rvar=ev("rvar"))
            # variable declarations
            case "iv": return gen.int_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "bv": return gen.bool_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "sv": return gen.str_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "hv": return gen.hash_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "jv": return gen.json_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "fv": return gen.flt_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "Fv": return gen.fun_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "pv": return gen.path_var(pvar=ev("pvar"), val=ev("val"), declare=jv["declare"])
            # simple instructions
            case "no": return gen.nope()
            case "brk": return gen.brk()
            case "cont": return gen.cont()
            case "skip": return gen.skip()
            case "ign": return gen.ignore()
            case "cr": return gen.clean_report()
            case "i+": return gen.inc_var(var=ev("var"))
            case "i&": return gen.iand_op(res=ev("res"), e=ev("e"))
            case "ret": return gen.ret(res=ev("res"))
            case "rep": return gen.report(msg=jv["msg"], path=ev("path"))
            # control
            case "aL": return gen.arr_loop(
                arr=ev("arr"), idx=ev("idx"), val=ev("val"), body=ev("body")
            )
            case "oL": return gen.obj_loop(
                obj=ev("obj"), key=ev("key"), val=ev("val"), body=ev("body")
            )
            case "iL": return gen.int_loop(
                idx=ev("idx"), start=ev("start"), end=ev("end"), body=ev("body")
            )
            case "if": return gen.if_stmt(
                cond=ev("cond"), true=ev("true"), false=ev("false"), likely=jv["likely"]
            )
            case "ifs":
                ct = [ ( _eval(c, gen), k, _eval(b, gen) ) for c, k, b in jv["cond_true"] ]
                return gen.mif_stmt(cond_true=ct, false=ev("false"))
            case "seq": return gen.sequence(seq=ev("seq"))
            # regex
            case "dr": return gen.def_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "sr": return gen.sub_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "ir": return gen.ini_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "rr": return gen.del_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "mr": return gen.match_re(
                name=jv["name"], var=jv["var"], regex=jv["regex"], opts=jv["opts"]
            )
            case "msv": return gen.match_str_var(
                rname=jv["rname"], var=jv["var"], val=jv["val"], declare=jv["declare"]
            )
            case "mv": return gen.match_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "mvl": return gen.match_val(
                mname=jv["mname"], rname=jv["rname"], sname=jv["sname"], dname=jv["dname"],
                declare=jv["declare"]
            )
            case "mko": return gen.match_ko(var=ev("var"))
            # str fun
            case "dsf": return gen.def_strfun(name=jv["name"])
            case "ssf": return gen.sub_strfun(name=jv["name"], body=ev("body"))
            # property map
            case "dpm": return gen.def_pmap(name=jv["name"], pmap=jv["pmap"], public=jv["public"])
            case "ipm": return gen.ini_pmap(name=jv["name"], pmap=jv["pmap"], public=jv["public"])
            case "spm": return gen.sub_pmap(name=jv["name"], pmap=jv["pmap"], public=jv["public"])
            case "rpm": return gen.del_pmap(name=jv["name"], pmap=jv["pmap"], public=jv["public"])
            # constant set
            case "dcs": return gen.def_cset(name=jv["name"], constants=jv["constants"])
            case "scs": return gen.sub_cset(name=jv["name"], constants=jv["constants"])
            case "ics": return gen.ini_cset(name=jv["name"], constants=jv["constants"])
            case "rcs": return gen.del_cset(name=jv["name"], constants=jv["constants"])
            case "incs": return gen.in_cset(
                name=jv["name"], var=ev("var"), constants=jv["constants"]
            )
            # fun
            case "dfu": return gen.def_fun(name=jv["name"])
            case "sfu": return gen.sub_fun(name=jv["name"], body=ev("body"), inline=jv["inline"])
            # constant map
            case "dcm": return gen.def_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "scm": return gen.sub_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "icm": return gen.ini_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "rcm": return gen.del_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "gcm": return gen.get_cmap(
                name=jv["name"], mapping=_json2cmap(jv["mapping"]), tag=ev("tag"), ttag=_s2t(jv["ttag"])
            )
            # final generation
            case "gi": return gen.gen_init(init=ev("init"))
            case "gf": return gen.gen_free(free=ev("free"))
            case "gc": return gen.gen_code(
                code=ev("code"), entry=jv["entry"], package=jv["package"], indent=jv["indent"]
            )
            case "gfc": return gen.gen_full_code(
                defs=ev("defs"), inis=ev("inis"), dels=ev("dels"), subs=ev("subs"),
                entry=jv["entry"], package=jv["package"], exe=jv["exe"], mark=jv["mark"],
            )
            case _: raise Exception(f"unexpected op code: {op}")
    elif isinstance(jv, list):
        # list of instructions (Block) fall here
        return functools.reduce(lambda x, i: x + _eval(i, gen), jv, [])
    elif isinstance(jv, str) and jv == "":
        return [ "" ]
    else:
        # probably a string, eg a variable name
        return jv

def ir_evaluate(ir: Jsonable, lang: Language) -> str:
    """Generate the target language source code from a full code JSON IR."""
    code = _eval(ir, lang)
    assert isinstance(code, list), "full code JSON IR"
    return lang.code_to_str(lang.filter_code(code))

def evaluate(ir: Code, lang: Language) -> Code:
    code = Code(lang, ir._entry, ir._executable, ir._package, ir._mark)
    code._predefs = ir._predefs
    code._defs = _eval(_u(ir._defs), lang)
    code._subs = _eval(_u(ir._subs), lang)
    code._inis = _eval(_u(ir._inis), lang)
    code._dels = _eval(_u(ir._dels), lang)
    return code
