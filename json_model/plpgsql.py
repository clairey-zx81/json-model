import re
import json
from .language import Language, Block, Var, PropMap, ConstList
from .language import JsonExpr, BoolExpr, IntExpr, StrExpr, PathExpr, Expr
from .mtypes import Jsonable, JsonScalar, Number

_DECL = "%PL_DECL% "
_ESC_TABLE = { "'": "''" }

class PLpgSQL(Language):
    """PL/pgSQL Code Generator."""

    def __init__(self, *,
                 debug: bool = False,
                 with_path: bool = True, with_report: bool = True, with_comment: bool = True,
                 with_package: bool = False, relib: str = "re", int_t: str = "INT8"):

        super().__init__(
            "PLpgSQL",
             with_path=with_path, with_report=with_report, with_comment=with_comment,
             with_package=with_package, eq="=", ne="<>", indent="  ",
             not_op="NOT", and_op="AND", or_op="OR", lcom="--",
             true="TRUE", false="FALSE", null="NULL",
             check_t="TEXT", json_t="JSONB",
             path_t="TEXT[]", float_t="FLOAT8", str_t="TEXT", match_t="TEXT[]",
             eoi=";", relib=relib, debug=debug,
             set_caps=(type(None), bool, int, float, str))  # type: ignore

        assert relib in ("re"), f"regex engine {relib} is not supported, try: re"

        self._json_esc_table = str.maketrans(_ESC_TABLE)

    #
    # file
    #
    def file_header(self, exe: bool = True) -> Block:
        code: Block = super().file_header(exe)
        code += [
            f"-- JSON_MODEL_VERSION is {self.version()}",
            r"CREATE EXTENSION IF NOT EXISTS json_model;",
        ]
        if self._with_package:
            code += [
                "",
                "CREATE SCHEMA IF NOT EXISTS CHECK_PACKAGE_NAME;",
                "SET search_path TO CHECK_PACKAGE_NAME, \"$user\", public;",
            ]
        return code

    def file_footer(self, exe: bool = True) -> Block:
        return [""] + self.file_load("plpgsql_entry.sql")

    #
    # inlined type test expressions about JSON data
    #
    def is_num(self, var: Var) -> BoolExpr:
        return f"JSONB_TYPEOF({var}) = 'number'"

    def is_scalar(self, var: Var) -> BoolExpr:
        return f"JSONB_TYPEOF({var}) IN ('null', 'boolean', 'number', 'string')"

    def is_def(self, var: Var) -> BoolExpr:
        return f"{var} IS NOT NULL"

    def is_a(self, var: Var, tval: type|None, loose: bool|None = None) -> BoolExpr:
        assert loose is None or tval in (int, float, Number)
        if tval is None or tval is type(None):
            return f"JSONB_TYPEOF({var}) = 'null'"
        elif tval is bool:
            return f"JSONB_TYPEOF({var}) = 'boolean'"
        elif tval is int:
            return self.is_num(var) + f" AND ({var})::INT8 = ({var})::FLOAT8"  # pyright: ignore
        elif tval is float:
            return self.is_num(var)
        elif tval is Number:
            return self.is_num(var)
        elif tval is str:
            return f"JSONB_TYPEOF({var}) = 'string'"
        elif tval is list:
            return f"JSONB_TYPEOF({var}) = 'array'"
        elif tval is dict:
            return f"JSONB_TYPEOF({var}) = 'object'"
        else:
            raise Exception(f"unexpected tval: {tval.__name__}")

    def esc(self, s: str) -> StrExpr:
        return "'" + s.translate(self._json_esc_table) + "'"

    def _json_str(self, j) -> str:
        return self.esc(json.dumps(j))

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return f"JSONB '{json.dumps(j, separators=(',', ':')).translate(self._json_esc_table)}'"

    def const(self, c: Jsonable) -> Expr:
        if isinstance(c, (list, dict)):
            return self.json_cst(c)
        else:
            return super().const(c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return f"{obj} ? {self.esc(prop)}"

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        val = var if is_str else f"JSON_VALUE({var}, '$' RETURNING TEXT)"
        cktype = "" if is_str else (self.is_a(var, str) + " AND ")  # pyright: ignore
        if name == "$UUID":
            return cktype + f"jm_is_valid_uuid({val}, {path}, rep)"
        elif name == "$DATE":
            return cktype + f"jm_is_valid_date({val}, {path}, rep)"
        elif name == "$TIME":
            return cktype + f"jm_is_valid_time({val}, {path}, rep)"
        elif name == "$DATETIME":
            return cktype + f"jm_is_valid_datetime({val}, {path}, rep)"
        elif name == "$REGEX":
            return cktype + f"jm_is_valid_regex({val}, {path}, rep)"
        elif name == "$EXREG":
            return cktype + f"jm_is_valid_extreg({val}, {path}, rep)"
        elif name in ("$URL", "$URI"):
            return cktype + f"jm_is_valid_url({val}, {path}, rep)"
        elif name == "$EMAIL":
            return cktype + f"jm_is_valid_email({val}, {path}, rep)"
        elif name == "$JSON":
            return cktype + f"jm_is_valid_json({val}, {path}, rep)"
        else:
            return super().predef(var, name, path, is_str)
    
    def value(self, var: Var, tvar: type) -> Expr:
        """Known type value extraction."""
        if tvar is type(None):
            return "NULL"
        elif tvar is bool:
            return f"({var})::BOOL"
        elif tvar is int:
            return f"({var})::INT8"
        elif tvar is float:
            return f"({var})::FLOAT8"
        elif tvar is Number:
            return f"({var})::FLOAT8"
        elif tvar is str:
            return f"JSON_VALUE({var}, '$' RETURNING TEXT)"  # WTF?
        else:
            raise Exception(f"unexpected type for value extraction: {tvar.__name__}")

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return f"{arr} -> {idx}"

    def obj_prop_val(self, obj: Var, prop: str|Var, is_var: bool = False) -> JsonExpr:
        return f"{obj} -> {prop}" if is_var else f"{obj} -> {self.esc(prop)}"
    #
    # inlined length computation
    #
    def obj_len(self, var: Var) -> IntExpr:
        return f"jm_object_size({var})"

    def arr_len(self, var: Var) -> IntExpr:
        return f"JSONB_ARRAY_LENGTH({var})"

    def str_len(self, var: Var) -> IntExpr:
        return f"LENGTH({var})"

    def any_len(self, var: Var) -> IntExpr:
        return f"jm_any_length({var})"

    #
    # misc expressions
    #
    def assign_expr(self) -> bool:
        return False

    def has_prop_fun(self, prop: str, mapname: str) -> BoolExpr:
        return f"{mapname}({prop}) IS NOT NULL"

    def get_prop_fun(self, prop: str, mapname: str) -> Expr:
        return f"{mapname}({prop})"

    def str_start(self, val: str, start: str) -> BoolExpr:
        return f"STARTS_WITH({val}, {self.esc(start)})"

    def str_end(self, val: str, end: str) -> BoolExpr:
        return f"RIGHT({val}, {len(end)}) = {self.esc(end)}"

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        if is_raw:
            val = f"TO_JSONB({val})"
        return f"jm_call({name}, {val}, {path}, rep)" if is_ptr else \
               f"{name}({val}, {path}, rep)"

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return f"jm_array_is_unique({val}, {path}, rep)"

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        """Call inefficient type-unaware constraint check."""
        return f"jm_check_constraint({val}, '{op}', {self._cst(vop)}, {path}, rep)"

    #
    # simple instructions
    #
    def ret(self, res: Expr) -> Block:
        return [ f"RETURN {res};"]

    def brk(self) -> Block:
        return [ "EXIT;" ]

    def nope(self) -> Block:
        return [ "NULL;" ]

    def var(self, var: Var, val: Expr|None, tname: str|None) -> Block:
        code = []
        if tname:
            code.append(f"{_DECL}{var} {tname};")
        if val:
            code.append(f"{var} := {val};")
        return code

    def int_var(self, var: Var, val: IntExpr|None = None, declare: bool = False) -> Block:
        return self.var(var, val, self._int_t if declare else None)

    def inc_var(self, var: Var) -> Block:
        return [f"{var} := {var} + 1;"]

    #
    # reporting
    #
    def is_reporting(self) -> BoolExpr:
        return "rep IS NOT NULL"

    def report(self, msg: str, path: Var) -> Block:
        return [
            r"IF rep IS NOT NULL THEN",
            f"  CALL jm_report_add_entry(rep, {self.esc(msg)}, {path});",
            r"END IF;"
        ] if self._with_report else []

    def clean_report(self) -> Block:
        return [
            r"IF rep IS NOT NULL THEN",
            r"  CALL jm_report_free_entries(rep);",
            r"END IF;"
        ] if self._with_report else []

    #
    # path management
    #
    def path_val(self, pvar: Var, pseg: str|int, is_prop: bool) -> PathExpr:
        # note: segment is a variable name for a prop or an integer
        return f"array_append({pvar}, {pseg})" if self._with_path else "NULL"

    def path_lvar(self, lvar: Var, rvar: Var) -> PathExpr:
        return f"(CASE WHEN {rvar} IS NOT NULL THEN {lvar} ELSE NULL END)" if self._with_path else "NULL"

    #
    # blocks
    #
    def arr_loop(self, arr: Var, idx: Var, val: Var, body: Block) -> Block:
        return [
            f"{_DECL}{idx} INT8;",
            f"{_DECL}{val} JSONB;",
            f"FOR {idx} IN 0 .. JSONB_ARRAY_LENGTH({arr}) - 1 LOOP",
        ] + self.indent([f"{val} := {arr} -> {idx};" ] + body) + [ "END LOOP;" ]

    def obj_loop(self, obj: Var, key: Var, val: Var, body: Block) -> Block:
        return [
            f"{_DECL}{key} TEXT;",
            f"{_DECL}{val} JSONB;",
            f"FOR {key}, {val} IN SELECT * FROM JSONB_EACH({obj}) LOOP",
        ] + self.indent(body) + [ "END LOOP;" ]

    def int_loop(self, idx: Var, start: IntExpr, end: IntExpr, body: Block) -> Block:
        return [
            f"{_DECL}{idx} INT8;",
            f"FOR {idx} IN {start} .. {end}-1 LOOP",
        ] + self.indent(body) + [ "END LOOP;" ]

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = []) -> Block:
        if true and false:
            return [ f"IF {cond} THEN" ] + self.indent(true) + ["ELSE"] + self.indent(false) + ["END IF;"]
        elif true:
            return [ f"IF {cond} THEN" ] + self.indent(true) + ["END IF;"]
        else:
            return [ f"IF NOT ({cond}) THEN" ] + self.indent(false) + ["END IF;"]

    def mif_stmt(self, cond_true: list[tuple[BoolExpr, Block]], false: Block = []) -> Block:
        code, op = [], "IF"
        for cond, true in cond_true:
            code += [ f"{op} {cond} THEN" ]
            code += self.indent(true)
            op = "ELSEIF"
        if false:
            if cond_true:
                code += ["ELSE"] + self.indent(false) + ["END IF;"]
            else:
                code += false
        else:
            code += ["END IF;"]
        return code

    #
    # (Extended) Regular Expressions
    #
    def regroup(self, name: str, pattern: str = ".*") -> str:
        return f"({pattern})"

    def _regex(self, regex: str) -> str:
        # character classes are not supported by Postgres?
        return re.sub(r"\\p\{L\}", r"\\w", regex)

    def sub_re(self, name: str, regex: str, opts: str) -> Block:
        # trigger _usual_ newline sensitive matching which is not the default with pg
        regex = self._regex(regex)
        if "s" not in opts:
            opts = "n" + opts
        return [
            f"-- regex={regex} opts={opts}",
            f"CREATE OR REPLACE FUNCTION {name}(val TEXT, path TEXT[], rep jm_report_entry[])",
            r"RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$",
            r"BEGIN",
            f"  RETURN regexp_like(val, {self.esc(regex)}, {self.esc(opts)});",
            r"END;",
            r"$$ LANGUAGE plpgsql;",
        ]

    def match_str_var(self, rname: str, var: str, val: str, declare: bool = True) -> Block:
        return [ f"{_DECL}{var} TEXT;" ]

    def match_re(self, name: str, var: str, regex: str, opts: str) -> BoolExpr:
        regex = self._regex(regex)
        if "s" not in opts:
            opts = "n" + opts
        return f"regexp_match({var}, {self.esc(regex)}, {self.esc(opts)})"

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
        return [ f"{dname} := {mname}[{sname[1:]}];" ]

    def match_ko(self, var: str) -> BoolExpr:
        return f"{var} IS NULL"

    def _plbody(self, body: Block) -> Block:
        """Generate a full DECLARE/BEGIN/END; PL/pgSQL function body."""
        # separate declarations from code
        decls, code = [], []
        for line in body:
            if _DECL in line:
                decls.append(line.split(_DECL)[1])
            else:
                code.append(line)
        # generate full code
        code = ["BEGIN"] + self.indent(code) + ["END;"]
        if decls:
            code = ["DECLARE"] + self.indent(decls) + code
        return code

    def sub_strfun(self, name: str, body: Block) -> Block:
        return [
            f"CREATE OR REPLACE FUNCTION {name}(val TEXT, path TEXT[], rep jm_report_entry[])",
            r"RETURNS BOOL CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$",
        ] + self._plbody(body) + [ "$$ LANGUAGE PLpgSQL;"]


    #
    # Property Map
    #
    def sub_pmap(self, name: str, pmap: PropMap, public: bool) -> Block:
        return [
            f"CREATE OR REPLACE FUNCTION {name}(name TEXT)",
            r"RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$",
            r"DECLARE",
            f"  map JSONB := {self.json_cst(pmap)};",  # pyright: ignore
            r"BEGIN",
            r"  RETURN map->>name;",
            r"END;",
            r"$$ LANGUAGE plpgsql;",
        ]

    def sub_cset(self, name: str, constants: ConstList) -> Block:
        return [
            f"CREATE OR REPLACE FUNCTION {name}(value JSONB)",
            r"RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$",
            r"DECLARE",
            f"  constants JSONB = {self.json_cst(constants)};",  # pyright: ignore
            r"BEGIN",
            r"  RETURN constants @> value;",
            r"END;",
            r"$$ LANGUAGE plpgsql;"
        ]

    def _var_cst(self, var: Var, vtype: type|None) -> Expr:
        return var

    def in_cset(self, name: str, var: Var, constants: ConstList) -> BoolExpr:
        """Tell whether JSON variable var value of potential types is in set name."""
        return f"{name}({var})"

    def _cst(self, value: Jsonable) -> str:
        match value:
            case None:
                return "NULL"
            case bool():
                return "true" if value else "false"
            case int()|float():
                return str(value)
            case str():
                return self.esc(value)
            case _:
                raise Exception(f"unexpected constant value: {value}")

    # def def_fun(self, name: str) -> Block:
    #     return []

    def sub_fun(self, name: str, body: Block, inline: bool = False) -> Block:
        return [
            f"CREATE OR REPLACE FUNCTION {name}(val JSONB, path TEXT[], rep jm_report_entry[])",
            "RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$",
        ] + self._plbody(body) + ["$$ LANGUAGE PLpgSQL;"]

    def ini_cmap(self, name: str, mapping: dict[JsonScalar, str]) -> Block:
        sname = self.esc(name)
        code = [ f"  ({sname}, {self.json_cst(tv)}, {self.esc(val)})"
                    for tv, val in mapping.items() ]
        for i in range(len(code) - 1):
            code[i] += ","
        return [ "INSERT INTO jm_constant_maps(mapname, tagval, value) VALUES" ] + code + [";"]

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return f"jm_cmap_get({self.esc(name)}, {tag})"

    def gen_init(self, init: Block) -> Block:
        return [
            "--",
            "-- constant maps initialization",
            "--",
            "TRUNCATE jm_constant_maps;",
        ] + init

    def gen_free(self, free: Block) -> Block:
        return []
