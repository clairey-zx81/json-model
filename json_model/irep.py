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
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals
from .runtime import Path, Report

def _j(o: str, **params) -> str:
    """Generate a JSON operation."""
    return json.dumps({"o": o, **params})

def _l(s: str) -> Jsonable:
    """Parse a JSON operation or something else."""
    # FIXME true/false/null handling is adhoc and can be wrong
    try:
        return json.loads(s) if isinstance(s, str) and s and (s[0] in '{["0123456789-' or s in ("null", "true", "false")) else s
    except:
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

# compute RW effects on boolean variables
type Sequence = list[Jsonable]
# read, write, true, false
type Effect = tuple[set[str], set[str], dict[str, bool]]
type Effects = list[Effect]


# NOTE there are quite a few implicit assumptions:
# - variables names are used once, without aliases or shadowing
# - early returns do not have an impact
def _getEffect(op: Jsonable, bool_vars: set[str], reporting: bool) -> Effect:

    read: set[str] = set()
    write: set[str] = set()
    value: dict[str, bool] = {}

    # direct boolean variable
    if isinstance(op, str) and op in bool_vars:
        read.add(op)
        return read, write, value

    # shortcut? error?
    if not isinstance(op, dict) or "o" not in op:
        return read, write, value

    # recursive computation
    # value: dict[str, bool] = {}
    # TODO interruption (return)
    # exit: bool

    NO_BOOL_EFFECT = {
        "co", "rep", "cst", "pl", "isa", "val", "iv", "i+", "hp", "isr", "cr",
        "brk", "apf", "id", "ss", "se", "pre", "no", "esc", "pvl", "scc", "jv",
        "gcm", "hpf", "gpf", "ol", "al", "sl", "nl", "cpv", "cont", "sh", "hv",
    }

    match op["o"]:
        # declaration/assignment
        case "bv":
            var = op["var"]
            bool_vars.add(var)
            op["val"] is not None and write.add(var)
            if isinstance(op["val"], bool):
                value[var] = op["val"]
            elif _isOp(op["val"], "pre"):
                predef = op["val"]["name"]
                if predef == "$ANY":
                    value[var] = True
                elif predef == "$NONE":
                    value[var] = False
            elif var in value:
                del value[var]
        # expressions
        case "ret":
            read, write, value = _getEffect(op["res"], bool_vars, reporting)
        case "not":
            read, write, value = _getEffect(op["e"], bool_vars, reporting)
        case "iv"|"cc"|"pv"|"fv"|"Fv"|"sv":
            read, write, value = _getEffect(op["val"], bool_vars, reporting)
        case "sc"|"nc":
            read, write, value = _getEffect(op["e1"], bool_vars, reporting)
            r, w, v = _getEffect(op["e2"], bool_vars, reporting)
            read |= r; write |= w; value.update(v)
        case "&"|"|":
            for e in op["exprs"]:
                r, w, v = _getEffect(e, bool_vars, reporting)
                read |= r; write |= w; value.update(v)
        # statements
        case "if":
            read, write, value = _getEffect(op["cond"], bool_vars, reporting)
            r, w, v = _optimSeq(op["true"], bool_vars, reporting)
            read |= r; write |= w
            r, w, v = _optimSeq(op["false"], bool_vars, reporting)
            read |= r; write |= w
            for var in write:
                if var in value:
                    del value[var]
        case "ifs":
            for tup in op["cond_true"]:
                cond, likely, true = tup
                r, w, v = _getEffect(cond, bool_vars, reporting)
                read |= r; write |= w
                r, w, v = _optimSeq(true, bool_vars, reporting)
                read |= r; write |= w
            r, w, v = _optimSeq(op["false"], bool_vars, reporting)
            read |= r; write |= w
        case "oL"|"aL"|"iL":
            read, write, value = _optimSeq(op["body"], bool_vars, reporting)
        case _:
            if not op["o"] in NO_BOOL_EFFECT:
                raise Exception(f"missing effect computation on operation {op['o']}")

    return read, write, value

def _isOp(op: Jsonable, o: str) -> bool:
    return isinstance(op, dict) and "o" in op and op["o"] == o

def _isOps(op: Jsonable, ops: set[str]) -> bool:
    return isinstance(op, dict) and "o" in op and op["o"] in ops

def _boolIf(op: Jsonable, bool_vars: set[str]) -> tuple[str, bool]|None:
    if not _isOp(op, "if"):
        return None
    cond = op["cond"]
    if isinstance(cond, str) and cond in bool_vars:
        return cond, True
    elif _isOp(cond, "not"):
        note = cond["e"]
        if isinstance(note, str) and note in bool_vars:
            return note, False
    return None

# direct operations without any effect, with or without reporting
IGN_REP = {"no", "co", "skip", "ign"}
IGN = IGN_REP | {"rep"}

def _noOp(op: Jsonable, reporting) -> bool:
    """Ignore this operation."""
    return _noOps(op["seq"], reporting) if _isOp(op, "seq") else _isOps(op, IGN_REP if reporting else IGN)

def _noOps(seq: list[Jsonable], reporting) -> bool:
    """Sequence without effect, only comments or nopes."""
    return all(map(lambda op: _noOp(op, reporting), seq))

def _returnCst(seq: list[Jsonable], reporting: bool = True) -> bool|None:
    result: bool|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "ret") and _isOp(op["res"], "cst"):
            assert isinstance(op["res"]["c"], bool)
            result = op["res"]["c"]
        else:
            # anything else is ignored
            return None
    return result

def _isRet(seq: list[Jsonable], reporting: bool) -> Jsonable:
    result = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "ret"):
            result = op["res"]
        else:
            return None
    return result

def _simpleRet(op: Jsonable, reporting: bool) -> bool:
    """Simplify if/return/return."""
    if _isOp(op, "if"):
        rest: bool|None
        resf: bool|None
        if ((rest := _returnCst(op["true"], reporting)) is not None) and \
           ((resf := _returnCst(op["false"], reporting)) is not None):
            if rest == resf:
                # quite unlikely…
                op.clear()
                op.update(o="ret", res={"o": "cst", "c": rest})
            else:
                cond = op["cond"]
                while _isOp(cond, "not"):
                    cond = cond["e"]
                    rest, resf = resf, rest
                op.clear()
                op.update(o="ret", res=cond if rest else {"o": "not", "e": cond})
            return True
    return False

def _isBoolAssign(seq: list[Jsonable], reporting: bool = True) -> Jsonable|None:
    """Return boolean assignment from sequence."""
    assign = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif not assign and _isOp(op, "bv") and op["val"] is not None:
            assign = op
        else:
            return None
    return assign

def _isBool(val: Jsonable) -> bool|None:
    if isinstance(val, bool):
        return val
    elif _isOp(val, "cst") and isinstance(val["c"], bool):
        return val["c"]
    else:
        return None

def _isFalse(val: Jsonable) -> bool:
    return _isBool(val) is False

def _isTrue(val: Jsonable) -> bool:
    return _isBool(val) is True

# NOTE despite the generality, the only occuring pattern is: "C ? E : F"
def _simpleBoolAssign(op: Jsonable, reporting: bool = True) -> bool:
    """Simplify conditional boolean assignment pattern."""
    if _isOp(op, "if"):
        tbv = _isBoolAssign(op["true"], reporting)
        fbv = _isBoolAssign(op["false"], reporting)
        # if tbv and fbv:
        #     log.warning(f"if: {op}")
        if tbv and fbv and tbv["var"] == fbv["var"]:
            vt = _isBool(tbv["val"])
            vf = _isBool(fbv["val"])
            if vt is None and vf is None:
                # this requires a ternary operator in the target language
                return False
            cond = op["cond"]
            op.clear()
            op.update({
                "o": "bv",
                "var": tbv["var"],
                "declare": False,
                "#": "IRO simple assign"
            })
            if vt is True and vf is True or vt is False and vf is False:
                # C ? V : V -> V
                op["val"] = {"o": "cst", "c": vt}
            elif vt is True and vf is False:
                # C ? T : F -> C
                op["val"] = cond
            elif vt is False and vf is True:
                # C ? F : T -> !C
                op["val"] = invertBool(cond)
            elif vf is False:
                # C ? E : F -> C && E
                op["val"] = {"o": "&", "exprs": [ cond, tbv["val"] ]}
            elif vt is True:
                # C ? T : E -> C || E
                op["val"] = {"o": "|", "exprs": [ cond, fbv["val"] ]}
            elif vf is True:
                # C ? E : T -> !C || E
                op["val"] = {"o": "|", "exprs": [ invertBool(cond), tbv["val"] ]}
            else:
                assert vt is False
                # C ? F : E -> !C && E
                op["val"] = {"o": "&", "exprs": [ invertBool(cond), fbv["val"] ]}
            return True
    return False

# comparison inversion
CMP_INV = {
    "=": "!=",
    "!=": "=",
    ">": "<=",
    ">=": "<",
    "<": ">=",
    "<=": ">",
}

def invertBool(op: Jsonable) -> Jsonable:
    """Invert boolean expression."""
    if isinstance(op, dict) and "o" in op:
        if op["o"] in ("sc", "nc"):
            op["op"] = CMP_INV[op["op"]]
        elif op["o"] == "cst":
            op["c"] = not op["c"]
        elif op["o"] == "not":
            op = op["e"]
        else:
            op = {"o": "not", "e": op}
        return op
    else:
        return {"o": "not", "e": op}

# FIXME full simplification should require several passes
def _optimSeq(seq: Sequence, bool_vars: set[str], reporting: bool) -> Effect:
    """Optimize instruction sequence if/then patterns on boolean variables in place."""

    effects: Effects = [ _getEffect(op, bool_vars, reporting) for op in seq ]
    assert len(effects) == len(seq)

    cum_read, cum_write, cum_value = set(), set(), {}

    # MERGE IF in sequence using effects with pattern:
    #
    # if [not] b:
    #     then_1  # no W on b
    #     else_1  # no W on b
    # (comments or nopes)
    # if [not] b:
    #     then_2
    #     else_2

    prev_var, prev_idx, prev_direct = None, 0, True

    for i, (op, (read, write, value)) in enumerate(list(zip(seq, effects))):

        # update cumulative analysis
        cum_read |= read; cum_write |= write
        for v in write:
            if v in value:
                cum_value[v] = value[v]
            else:  # erase current value
                if v in cum_value:
                    del cum_value[v]

        # skip comments and nope
        if _isOps(op, {"co", "no", "ign"}):
            continue

        cur_var, cur_idx, cur_direct = None, 0, True

        # NOT IN A IF
        # if prev_var and prev_var in write:
        #     prev_var = None

        if test := _boolIf(op, bool_vars):

            var, direct = test

            if var in cum_value:
                # drop if
                seq = op["true" if direct == cum_value[var] else "false"]
                op.clear()
                op.update(o="seq", seq=seq)
                op["#"] = "IRO dropped constant if"
                prev_var = None
                # NOTE could update effects?!
                continue

            if prev_var is None:
                if var not in write:
                    prev_var, prev_direct, prev_idx = var, direct, i
                continue

            # possibly merge
            cur_var, cur_direct, cur_idx = var, direct, i
            if prev_var == cur_var:  # merge!
                assert prev_idx != cur_idx
                # update sequence
                if cur_direct == prev_direct:
                    seq[prev_idx]["true"] += seq[cur_idx]["true"]
                    seq[prev_idx]["false"] += seq[cur_idx]["false"]
                else:
                    seq[prev_idx]["true"] += seq[cur_idx]["false"]
                    seq[prev_idx]["false"] += seq[cur_idx]["true"]
                # update corresponding effects
                effects[prev_idx][2].update(effects[cur_idx][2])
                effects[prev_idx] = (
                    effects[prev_idx][0] | effects[cur_idx][0],
                    effects[prev_idx][1] | effects[cur_idx][1],
                    # FIXME empty instead?
                    effects[prev_idx][2]
                )
                # stop merge on this if variable is written
                if prev_var in effects[prev_idx][1]:
                    prev_var = None
                # cleanup current instruction with a comment
                seq[cur_idx] = {"o": "no", "#": f"IRO if merged on {prev_idx}"}
                effects[cur_idx] = (set(), set(), {})

            elif var not in write:
                prev_var, prev_direct, prev_idx = var, direct, i
            else:
                prev_var = None

        else:  # whatever else is bad news for merging
            prev_var = None

    #
    # SIMPLER IF
    #

    assign: Jsonable|None = None
    for op in seq:

        if _noOp(op, reporting):
            continue

        # constant bool assignment
        if _isBoolAssign(op, reporting) and _isBool(op["val"]) is not None:
            assign = op
            continue

        # V = C ; if (!? V) ...
        if assign and _isOp(op, "if"):
            inverted = _isOp(op["cond"], "not")
            same_var = assign["var"] == (op["cond"]["e"] if inverted else op["cond"])
            vv = _isBool(assign["val"])  # ???
            if same_var and vv is not None:
                if vv and inverted or not vv and not inverted:
                    op["cond"] = {"o": "cst", "c": False}
                else:
                    op["cond"] = {"o": "cst", "c": True}
        assign = None

        # simplify "if (C) .../..."
        if _isOp(op, "if") and _isOp(op["cond"], "cst"):
            seq = op["true"] if op["cond"]["c"] else op["false"]
            op.clear()
            op.update(o="seq", seq=seq)

        # TODO flatten seq in seq?

        # simplify "if (!E) .../..."
        # remove "not" when "false" branch is not empty by exchanging true/false
        if _isOp(op, "if"):
            if _isOp(op["cond"], "not") and not _noOps(op["false"], reporting):
                op["cond"], op["true"], op["false"] = op["cond"]["e"], op["false"], op["true"]
                if isinstance(op["likely"], bool):
                    op["likely"] = not op["likely"]
                op["#"] = "IRO inverted not"
            elif (_isOp(op["cond"], "nc") or _isOp(op["cond"], "sc")) and \
                    _noOps(op["true"], reporting) and not _noOps(op["false"], reporting):
                assert "op" in op["cond"]
                op["#"] = "IRO inverted cmp"
                op["true"], op["false"] = op["false"], op["true"]
                op["cond"]["op"] = CMP_INV[op["cond"]["op"]]
                if isinstance(op["likely"], bool):
                    op["likely"] = not op["likely"]

        if _isOp(op, "if"):
            _simpleRet(op, reporting)         # simplify if/return/return
            _simpleBoolAssign(op, reporting)  # simplify if/assign/assign

        # simplify if / <empty> / ...
        if _isOp(op, "if") and _noOps(op["true"], reporting):
            if _noOps(op["false"], reporting):
                op.clear()
                op.update({"o": "no", "#": "IRO empty if removed"})
            else:
                op["cond"] = {"o": "not", "e": op["cond"], "#": "IRO empty true branch removed"}
                op["true"], op["false"] = op["false"], []
                if isinstance(op["likely"], bool):
                    op["likely"] = not op["likely"]

        # simplify "if (!? V) V = C
        if _isOp(op, "if") and (assign := _isBoolAssign(op["true"], reporting)) and \
                _noOps(op["false"], reporting):
            val = _isBool(assign["val"])
            inverted = _isOp(op["cond"], "not")
            same_var = assign["var"] == (op["cond"]["e"] if inverted else op["cond"])
            if same_var and val is not None:
                op.clear()
                if val and not inverted or not val and inverted:
                    # if (!V) V = F -> nope
                    # if (V) V = T -> nope
                    op.update({"o":"no", "#": "IRO removed useless conditional assignment"})
                else:
                    # if (!V) V = T -> V = T
                    # if (V) V = F -> V = F
                    op.update(assign)
                    op["#"] = "IRO simpler conditional assignment"

    # if (C) ret X ; ret Y
    ifop: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "if") and not op["false"] and _isRet(op["true"], reporting):
            ifop = op
        elif _isOp(op, "ret") and ifop is not None:
            true_result = _isRet(ifop["true"], reporting)
            assert true_result is not None  # sanity
            if _isOp(true_result, "cst"):
                if true_result["c"]:
                    if _isOp(op["res"], "cst"):
                        if op["res"]["c"]:
                            newop = {"o": "ret", "res": {"o": "cst", "c": True}}
                        else:
                            newop = {"o": "ret", "res": ifop["cond"]}
                    else:
                        newop = {"o": "ret", "res": {"o": "|", "exprs": [ifop["cond"], op["res"]]} }
                else:
                    if _isOp(op["res"], "cst"):
                        if op["res"]["c"]:
                            newop = {"o": "ret", "res": invertBool(ifop["cond"])}
                        else:
                            newop = {"o": "ret", "res": {"o": "cst", "c": False}}
                    else:
                        newop = {"o": "ret", "res": {"o": "&", "exprs": [invertBool(ifop["cond"]), op["res"]]} }
                # set return on latter instruction
                ifop.clear()
                ifop.update({"o": "ign", "#": "IRO if ret ret"})
                op.clear()
                op.update(newop)
            else:
                # NOTE it is unsure whether this can be triggered by the compiler
                # return true_result? X: Y
                log.info("TODO more if simplification")
        else:
            # reset previous if return
            ifop = None

    # simplify X = E1; X = E2;
    assign: Jsonable|None = None
    for op in seq:
        if _noOp(op, False):
            pass
        elif _isOp(op, "bv"):
            if assign and assign["var"] == op["var"]:
                op["declare"] = assign["declare"]
                assign.clear()
                assign.update(o="ign")
            assign = op
        else:
            assign = None

    # remove unused boolean declaration in a trivial case: bool v; ret X; -> ret X
    decl: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv") and op["val"] is None:
            decl = op
        elif _isOp(op, "ret") and decl is not None:
            decl.clear()
            decl.update({"o": "ign", "#": "IRO unused boolean declaration"})
            decl = None
        else:
            decl = None

    # move boolean declaration (usually res) with first usage if possible
    decl: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv"):
            if op["declare"] and op["val"] is None:
                decl = op
            elif not op["declare"] and decl is not None and op["var"] == decl["var"]:
                op["declare"] = True
                decl.clear()
                decl.update({"o": "ign", "#": "IRO moved boolean declaration"})
                decl = None
            else:  # safe
                decl = None
        else:  # safe
            decl = None

    # simplify "V = E1; if (!V) V = E2;" to "V = E1 || E2;"
    # simplify "V = E1; if (V) V = E2;" to "V = E1 && E2;"
    assign: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv"):
            assign = op
        elif (assign and _isOp(op, "if") and _noOps(op["false"], reporting)):
            is_not = _isOp(op["cond"], "not")
            same_var = assign["var"] == (op["cond"]["e"] if is_not else op["cond"])
            if same_var and (assign2 := _isBoolAssign(op["true"], reporting)) and assign2["var"] == assign["var"]:
                # ok, save comments and move expression forward
                newass = copy.copy(assign)
                newass["val"] = {
                    "o": "|" if is_not else "&",
                    "exprs": [assign["val"], assign2["val"]],
                    "#": f"IRO merge {'or' if is_not else 'and'}"
                }
                assign2.clear()
                assign2.update(o="ign")
                assign.clear()
                assign.update({"o": "seq", "seq": op["true"]})
                op.clear()
                op.update(newass)
                assign = op  # done
            else:
                assign = None
        else:  # safe
            assign = None

    # simplify "if (not V) V = E; ret V;" to "ret V || E;"
    if_not: Jsonable|None = None
    assign: Jsonable|None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "if") and _isOp(op["cond"], "not") and _noOps(op["false"], reporting):
            var = op["cond"]["e"]
            assign = _isBoolAssign(op["true"], reporting)
            if assign is not None and assign["var"] == var:
                if_not = op
            else:
                if_not, assign = None, None
        elif if_not is not None and _isOp(op, "ret") and op["res"] == assign["var"]:
            op["res"] = {
                "o": "|",
                "exprs": [{"o": "gv", "var": assign["var"], "tvar": "bool"}, assign["val"]]
            }
            # turn into a sequence to keep comments
            branch = if_not["true"]
            if_not.clear()
            if_not.update({
                "o": "seq",
                "seq": branch,
                "#": "# IRO simpler if assign / ret"
            })
            assign.clear()
            assign.update({"o": "ign"})
            if_not, assign = None, None
        else:
            if_not = None

    # simplify "V = E; ret V;" to "ret E;"
    prev: Jsonable|None = None
    for op in seq:
        if _noOp(op, False):
            pass
        elif _isOp(op, "bv") and op["val"] is not None:
            prev = op
        elif prev is not None and _isOp(op, "ret") and op["res"] == prev["var"]:
            op["res"] = prev["val"]
            prev.clear()
            prev.update({"o": "ign", "#": "IRO assignment moved to return"})
            prev = None
        else:
            prev = None

    # remove nopes (unless alone)
    rm, nco = [], 0
    for i, op in enumerate(seq):
        if _isOp(op, "co"):
            nco += 1
        elif _isOps(op, {"no", "ign"}):
            rm.append(i)
    if rm:
        if len(rm) + nco == len(seq):  # keep one op (FIXME should be a no)
            rm.pop()
        for i in reversed(rm):
            seq.pop(i)
            effects.pop(i)

    return cum_read, cum_write, cum_value

def _recIR(code: Jsonable, path: Path,
           flt: Callable[[Jsonable, Path], bool],
           rwt: Callable[[Jsonable, Path], Jsonable]) -> Jsonable:
    if flt(code, path):
        if isinstance(code, dict) and "o" in code:
            for k in list(code.keys()):
                code[k] = _recIR(code[k], path + [k], flt, rwt)
        elif isinstance(code, list):
            code = [ _recIR(c, path + [i], flt, rwt) for i, c in enumerate(code) ]
        code = rwt(code, path)
    return code

def recurseIR(code: Jsonable,
              flt: Callable[[Jsonable, Path], bool],
              rwt: Callable[[Jsonable, Path], Jsonable]):
    _recIR(code, [], flt, rwt)

def callShortcuts(code: Jsonable, shortcuts: dict[str, str]) -> int:
    """Update check function calls based on shortcuts."""

    # shortcut replacements
    if not shortcuts:
        return 0

    changes = 0

    def rep(fun: str) -> str:
        nonlocal changes
        if fun in shortcuts:
            changes += 1
            return shortcuts[fun]
        else:
            return fun

    def repRwt(code: Jsonable, _: Path) -> Jsonable:
        if isinstance(code, dict) and "o" in code:
            op = code["o"]
            if op in ("dcm", "scm", "icm", "rcm"):
                code["mapping"] = [ (c, rep(f)) for c, f in code["mapping"] ]
            elif op in ("dpm", "spm", "ipm", "rpm"):
                code["pmap"] = { p: rep(f) for p, f in code["pmap"].items() }
            elif op == "cc":
                code["name"] = rep(code["name"])
        return code

    recurseIR(code, lambda c, p: True, repRwt)

    return changes

SCALAR_TYPES = { "int", "float", "bool", "str" }

def partialEval(code: Jsonable, reporting: bool) -> int:
    changes = 0

    def peRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if not reporting:
            if _isOp(code, "rep"):
                code.clear()
                code.update({"o": "no", "#": "# IRO no reporting"})
                changes += 1
            elif _isOp(code, "isr"):
                code.clear()
                code.update(o="cst", c=False)
                changes += 1
            elif _isOp(code, "cr"):
                code.clear()
                code.update(o="ign")
                changes += 1
        if _isOp(code, "&"):
            ands = code["exprs"]
            assert isinstance(ands, list)
            if len(ands) < 2:
                pass
            elif (_isOp(ands[0], "is") and _isOp(ands[1], "isa") and
                  ands[0]["var"] == ands[1]["var"] and ands[1]["tval"] in SCALAR_TYPES):
                # NOTE no instance found
                # is_scalar(V) && is_a(V, scalar_type)
                ands[0].clear()
                ands[0]["o"] = "cst"
                ands[0]["c"] = True
                ands[0]["#"] = "# IRO simplified scalar test"
                ands.pop(0)
                changes += 1
            # NOTE too optimistic, see mv-01/enum_00
            # elif _isOp(ands[0], "is") and _isOp(ands[1], "incs"):
            #     # is_scalar(V) && in_cst(V, ...)
            #     ands[0].clear()
            #     ands[0]["o"] = "cst"
            #     ands[0]["c"] = True
            #     ands[0]["#"] = "# IRO simplified scalar test"
            #     ands.pop(0)
            #     changes += 1
        return code

    recurseIR(code, lambda c, p: True, peRwt)

    return changes

def elimCommonSub(code: Jsonable) -> int:
    """Common subexpression elimination in some cases."""
    changes: int = 0

    def cseFlt(code: Jsonable, _: Path) -> bool:
        nonlocal changes
        nchanges = changes
        if _isOps(code, {"|", "&"}):
            ope = code["o"]
            while True:
                if any(map(lambda e: _isOp(e, ope), code["exprs"])):
                    # flatten | in | or & in &
                    exprs = []
                    for e in code["exprs"]:
                        if _isOp(e, ope):
                            exprs += e["exprs"]
                        else:
                            exprs.append(e)
                    code["exprs"] = exprs
                    changes += 1
                if changes == nchanges:
                    break
                nchanges = changes
        return True

    def cseRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        # TODO improve generality with partial match
        if _isOp(code, "|"):
            factor: list[list[int]] = []
            common: Jsonable|None = None
            curidx: list[int] = []
            exprs = code["exprs"]
            for i, expr in enumerate(exprs):
                if _isOp(expr, "&"):
                    if common is None:
                        common = expr["exprs"][0]
                        curidx = [i]
                    elif common == expr["exprs"][0]:
                        curidx.append(i)
                        continue
                    else:
                        if len(curidx) > 1:
                            factor.append(curidx)
                        common = expr["exprs"][0]
                        curidx = [i]
                        break
                else:
                    if len(curidx) > 1:
                        factor.append(curidx)
                    common, curidx = None, []
            if len(curidx) > 1:
                factor.append(curidx)

            # rewrite factor sections
            for f in factor:
                # |(..., &(C, 1...), &(C, 2...), ...) -> |(..., &(C, |(&(1...), &(2...))), ...)
                assert len(f) > 1
                first, last = f[0], f[-1]

                common = exprs[first]["exprs"][0]

                # extract and drop the common part
                ands = copy.deepcopy(exprs[first: last+1])
                for e in ands:
                    e["exprs"] = e["exprs"][1:]

                # common expression
                exprs[first]["o"] = "&"
                exprs[first]["exprs"] = [ common, {"o": "|", "exprs": ands} ]
                # falsify other items
                for i in range(first+1, last+1):
                    exprs[i].clear()
                    exprs[i].update(o="cst", c=False)

                changes += 1

        if _isOps(code, {"&", "|"}):
            # remove True/False constants in passing
            keep_it = (lambda o: not _isTrue(o)) if code["o"] == "&" else (lambda o: not _isFalse(o))
            init_len = len(code["exprs"])
            code["exprs"] = list(filter(keep_it, code["exprs"]))
            changes += len(code["exprs"]) - init_len
            # partial eval
            if code["o"] == "&" and any(map(_isFalse, code["exprs"])):
                code.clear()
                code.update(o="cst", c=False)
            elif code["o"] == "|" and any(map(_isTrue, code["exprs"])):
                code.clear()
                code.update(o="cst", c=True)

        return code

    recurseIR(code, cseFlt, cseRwt)
    return changes

def elimDeadCode(code: Jsonable, reporting: bool) -> int:
    """Eliminate dead code in simple cases."""
    changes = 0

    def edcRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if isinstance(code, list):
            # sequence with a constant return and only assignments
            ret: Jsonable|None = None
            for op in code:
                if _noOp(op, reporting):
                    pass
                elif _isOps(op, {"bv", "iv"}):
                    pass
                elif _isOp(op, "seq") and _noOps(op["seq"], reporting):
                    pass
                elif _isOp(op, "ret") and _isBool(op["res"]) is not None:
                    ret = op
                    break
                else:
                    break
            if ret:
                # return comments and return
                changes += 1
                return list(filter(lambda o: _isOps(o, {"co", "ret", "seq"}), code))
        return code

    recurseIR(code, lambda _c, _p: True, edcRwt)
    return changes

def elimUnreachableCode(code: Jsonable) -> int:
    """Remove unreachable code after a return."""
    changes = 0

    def hasRet(op: Jsonable) -> bool:
        return isinstance(op, dict) and "o" in op and (
            op["o"] == "ret" or
            op["o"] == "seq" and any(map(hasRet, op["seq"])) or
            op["o"] == "if" and any(map(hasRet, op["true"])) and any(map(hasRet, op["false"]))
        )

    def eucRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if isinstance(code, list):
            returned = False
            for op in code:
                if _isOp(op, "co"):
                    pass
                elif returned:
                    if not _isOp(op, {"no", "ign"}):
                        changes += 1
                        op.clear()
                        op.update(o="ign")
                elif hasRet(op):
                    returned = True
        return code

    recurseIR(code, lambda _c, _p: True, eucRwt)
    return changes

def optimizeIR(code: list[Jsonable], *, shortcuts: dict[str, str], partial: bool = True,
               if_optim: bool = True, reporting: bool = True) -> Jsonable:
    """Optimize IR code."""

    if not if_optim and not shortcuts:
        return code

    optimized, calls = 0, 0

    for i, c in list(enumerate(code)):
        if c == "":
            continue
        changed: bool = False
        ins = json.loads(c)
        if isinstance(ins, dict) and "o" in ins and ins["o"] == "sfu":
            if partial:
                changes = partialEval(ins, reporting)
                changed |= changes > 0
            # if statement simplification
            if if_optim:
                optimized += 1
                _optimSeq(ins["body"], set(), reporting=reporting)
                changed = True  # maybe
        if shortcuts:  # call shortcuts
            changes = callShortcuts(ins, shortcuts)
            calls += changes
            changed |= changes > 0
        changed |= elimCommonSub(ins) > 0
        changed |= elimDeadCode(ins, reporting) > 0
        changed |= elimUnreachableCode(ins) > 0
        if changed:
            code[i] = json.dumps(ins)

    log.info(f"optimize ir: {optimized} functions processed, {calls} call shortcuts")

    return code


class IRep(Language):
    """Generate JSON intermediate representation of backend code.

    This class basically defer code generation calls using an intermediate JSON structure
    to hold the function and its parameters.

    NOTE this is currently pretty inefficient, with useless back and forth json encodings
    that artificially preserve the initial Block (list[str]) and Expr (str) typing.
    """

    def __init__(self, lang: Language|None, *, debug: bool = False, if_optim: bool = True):
        super().__init__("JSON", indent=",", debug=debug)
        self._lang = lang or self
        self._if_optim = if_optim
        self._byte_order = lang._byte_order if lang else "le"

    # langage dependent stuff
    def assign_expr(self) -> bool:
        return self._lang.assign_expr() if self._lang != self else True

    def assign_obj_prop(self) -> bool:
        return self._lang.assign_obj_prop() if self._lang != self else True

    def regroup(self, name: str, pattern: str = ".*") -> str:
        return self._lang.regroup(name, pattern) if self._lang != self else super().regroup(name, pattern)

    def indent(self, block: Block, sep: bool = True) -> Block:
        raise Exception("indentation not a IR operation")

    # generic code generation
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

    def esc(self, s: str) -> StrExpr:
        return _j("esc", s=s)

    def json_cst(self, j: Jsonable) -> JsonExpr:
        return _j("jc", json=j)

    def const(self, c: Jsonable) -> Expr:
        return _j("cst", c=c)

    def has_prop(self, obj: Var, prop: str) -> BoolExpr:
        return _j("hp", obj=_l(obj), prop=prop)

    def predef(self, var: Var, name: str, path: Var, is_str: bool = False) -> BoolExpr:
        return _j("pre", var=_l(var), name=name, path=_l(path), is_str=is_str)

    def value(self, var: Var, tvar: type) -> Expr:
        return _j("val", var=_l(var), tvar=tvar.__name__)

    def get_value(self, var: str, tvar: type) -> Expr:
        return _j("gv", var=var, tvar=tvar.__name__)

    def arr_item_val(self, arr: Var, idx: IntExpr) -> JsonExpr:
        return _j("aiv", arr=_l(arr), idx=_l(idx))

    def obj_prop_val(self, obj: Var, prop: str|StrExpr, is_var: bool = False) -> JsonExpr:
        return _j("opv", obj=_l(obj), prop=prop, is_var=is_var)

    def obj_has_prop_val(self, dst: Var, obj: Var, prop: str|StrExpr, is_var: bool = False) -> BoolExpr:
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

    def str_start(self, val: Var, start: str) -> BoolExpr:
        return _j("ss", val=_l(val), start=start)

    def str_end(self, val: Var, end: str) -> BoolExpr:
        return _j("se", val=_l(val), end=end)

    def str_check_call(self, name: str, val: StrExpr, path: Var) -> BoolExpr:
        return _j("scc", name=name, val=_l(val), path=_l(path))

    def check_call(self, name: str, val: Expr, path: Var, *,
                   is_ptr: bool = False, is_raw: bool = False) -> BoolExpr:
        return _j("cc", name=name, val=_l(val), path=_l(path), is_ptr=is_ptr, is_raw=is_raw)

    def check_unique(self, val: JsonExpr, path: Var) -> BoolExpr:
        return _j("cu", val=_l(val), path=_l(path))

    def check_constraint(self, op: str, vop: int|float|str, val: JsonExpr, path: Var) -> BoolExpr:
        return _j("ct", op=op, vop=vop, val=_l(val), path=_l(path))

    def str_cmp(self, e1: StrExpr, op: str, e2: StrExpr) -> BoolExpr:
        return _j("sc", e1=_l(e1), op=op, e2=_l(e2))

    def num_cmp(self, e1: NumExpr, op: str, e2: NumExpr, hexa: bool = False) -> BoolExpr:
        return _j("nc", e1=_l(e1), op=op, e2=_l(e2), hexa=hexa)

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
        return [ _j("rep", msg=msg, path=_l(path)) ]

    def clean_report(self) -> Block:
        return [ _j("cr") ]

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

    def if_stmt(self, cond: BoolExpr, true: Block, false: Block = [], likely: TestHint = None) -> Block:
        return [ _j("if", cond=_l(cond), true=_u(true), false=_u(false), likely=likely) ]

    def mif_stmt(self, cond_true: Conditionals, false: Block = []) -> Block:
        return [ _j("ifs", cond_true=[ (_l(c), k, _u(b)) for c, k, b in cond_true ], false=_u(false)) ]

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

    def match_val(self, mname: str, rname: str, sname: str, dname: str, declare: bool = False) -> Block:
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

    def get_cmap(self, name: str, tag: Var, ttag: type) -> Expr:
        return _j("gcm", name=name, tag=_l(tag), ttag=ttag.__name__)

    def gen_init(self, init: Block) -> Block:
        return [ _j("gi", init=_u(init)) ]

    def gen_free(self, free: Block) -> Block:
        return [ _j("gf", free=_u(free)) ]

    def gen_code(self, code: Block, entry: str, package: str|None, indent: bool = False) -> Block:
        return [ _j("gc", code=_u(code), entry=entry, package=package, indent=indent) ]

    def gen_full_code(self, defs: Block, inis: Block, dels: Block, subs: Block,
                      entry: str, package: str|None, exe: bool) -> Block:
        return [ _j("gfc", defs=_u(defs), inis=_u(inis), dels=_u(dels), subs=_u(subs),
                    entry=entry, package=package, exe=exe) ]

#
# target language reconstruction
#
def s2t(tname: str|None) -> type:
    """String to type reconversion."""
    match tname:
        case None: return None
        case "null": return None
        case "bool": return bool
        case "int": return int
        case "float": return float
        case "Number": return Number
        case "str": return str
        case "list": return list
        case "dict": return dict
        case "Path": return Path
        case "Report": return Report
        case _: raise Exception(f"unexpected type name: {tname}")

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
            case "co": return gen.lcom(text=jv["text"])
            case "fh": return gen.file_header(exe=jv["exe"])
            case "ff": return gen.file_footer(exe=jv["exe"])
            case "in": return gen.is_num(var=ev("var"))
            case "is": return gen.is_scalar(var=ev("var"))
            case "id": return gen.is_def(var=ev("var"))
            case "isa": return gen.is_a(var=ev("var"), tval=s2t(jv["tval"]), loose=jv["loose"])
            case "esc": return gen.esc(s=jv["s"])
            case "jc": return gen.json_cst(j=jv["j"])
            case "cst": return gen.const(c=jv["c"])
            case "hp": return gen.has_prop(obj=ev("obj"), prop=jv["prop"])
            case "pre": return gen.predef(var=ev("var"), name=jv["name"], path=ev("path"), is_str=jv["is_str"])
            case "val": return gen.value(var=ev("var"), tvar=s2t(jv["tvar"]))
            case "gv": return gen.get_value(var=jv["var"], tvar=s2t(jv["tvar"]))
            case "aiv": return gen.arr_item_val(arr=ev("arr"), idx=ev("idx"))
            case "opv": return gen.obj_prop_val(obj=ev("obj"), prop=jv["prop"], is_var=jv["is_var"])
            case "cpv": return gen.obj_has_prop_val(dst=ev("dst"), obj=ev("obj"), prop=jv["prop"], is_var=jv["is_var"])
            case "ol": return gen.obj_len(var=ev("var"))
            case "al": return gen.arr_len(var=ev("var"))
            case "sl": return gen.str_len(var=ev("var"))
            case "nl": return gen.any_len(var=ev("var"))
            case "sh": return gen.str_hash(val=ev("val"), size=jv["size"])
            case "apf": return gen.assign_prop_fun(fun=jv["fun"], prop=jv["prop"], mapname=jv["mapname"])
            case "hpf": return gen.has_prop_fun(prop=jv["prop"], mapname=jv["mapname"])
            case "gpf": return gen.get_prop_fun(prop=jv["prop"], mapname=jv["mapname"])
            case "ss": return gen.str_start(val=ev("val"), start=jv["start"])
            case "se": return gen.str_end(val=ev("val"), end=jv["end"])
            case "scc": return gen.str_check_call(name=jv["name"], val=ev("val"), path=ev("path"))
            case "cc": return gen.check_call(name=jv["name"], val=ev("val"), path=ev("path"), is_ptr=jv["is_ptr"], is_raw=jv["is_raw"])
            case "cu": return gen.check_unique(val=ev("val"), path=ev("path"))
            case "ct": return gen.check_constraint(op=jv["op"], vop=jv["vop"], val=ev("val"), path=ev("path"))
            case "sc": return gen.str_cmp(e1=ev("e1"), op=jv["op"], e2=ev("e2"))
            case "nc": return gen.num_cmp(e1=ev("e1"), op=jv["op"], e2=ev("e2"), hexa=jv["hexa"])
            case "()": return gen.paren(e=ev("e"))
            case "not": return gen.not_op(e=ev("e"))
            case "&": return gen.and_op(*[ _eval(e, gen) for e in jv["exprs"] ])
            case "|": return gen.or_op(*[ _eval(e, gen) for e in jv["exprs"] ])
            case "isr": return gen.is_reporting()
            case "pvl": return gen.path_val(pvar=ev("pvar"), pseg=jv["pseg"], is_prop=jv["is_prop"], is_var=jv["is_var"])
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
            case "aL": return gen.arr_loop(arr=ev("arr"), idx=ev("idx"), val=ev("val"), body=ev("body"))
            case "oL": return gen.obj_loop(obj=ev("obj"), key=ev("key"), val=ev("val"), body=ev("body"))
            case "iL": return gen.int_loop(idx=ev("idx"), start=ev("start"), end=ev("end"), body=ev("body"))
            case "if": return gen.if_stmt(cond=ev("cond"), true=ev("true"), false=ev("false"), likely=jv["likely"])
            case "ifs":
                ct = [ ( _eval(c, gen), k, _eval(b, gen) ) for c, k, b in jv["cond_true"] ]
                return gen.mif_stmt(cond_true=ct, false=ev("false"))
            case "seq": return gen.sequence(seq=ev("seq"))
            # regex
            case "dr": return gen.def_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "sr": return gen.sub_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "ir": return gen.ini_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "rr": return gen.del_re(name=jv["name"], regex=jv["regex"], opts=jv["opts"])
            case "mr": return gen.match_re(name=jv["name"], var=jv["var"], regex=jv["regex"], opts=jv["opts"])
            case "msv": return gen.match_str_var(rname=jv["rname"], var=jv["var"], val=jv["val"], declare=jv["declare"])
            case "mv": return gen.match_var(var=ev("var"), val=ev("val"), declare=jv["declare"])
            case "mvl": return gen.match_val(mname=jv["mname"], rname=jv["rname"], sname=jv["sname"], dname=jv["dname"], declare=jv["declare"])
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
            case "incs": return gen.in_cset(name=jv["name"], var=ev("var"), constants=jv["constants"])
            # fun
            case "dfu": return gen.def_fun(name=jv["name"])
            case "sfu": return gen.sub_fun(name=jv["name"], body=ev("body"), inline=jv["inline"])
            # constant map
            case "dcm": return gen.def_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "scm": return gen.sub_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "icm": return gen.ini_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "rcm": return gen.del_cmap(name=jv["name"], mapping=_json2cmap(jv["mapping"]))
            case "gcm": return gen.get_cmap(name=jv["name"], tag=ev("tag"), ttag=s2t(jv["ttag"]))
            # final generation
            case "gi": return gen.gen_init(init=ev("init"))
            case "gf": return gen.gen_free(free=ev("free"))
            case "gc": return gen.gen_code(code=ev("code"), entry=jv["entry"], package=jv["package"], indent=jv["indent"])
            case "gfc": return gen.gen_full_code(defs=ev("defs"), inis=ev("inis"), dels=ev("dels"), subs=ev("subs"),
                                                 entry=jv["entry"], package=jv["package"], exe=jv["exe"])
            case _: raise Exception(f"unexpected op code: {op}")
    elif isinstance(jv, list):
        # list of instructions (Block) fall here
        return functools.reduce(lambda x, i: x + _eval(i, gen), jv, [])
    elif isinstance(jv, str) and jv == "":
        return [ "" ]
    else:
        # probably a string, eg a variable name
        return jv

def evaluate(ir: Code, lang: Language) -> Code:
    code = Code(lang, ir._entry, ir._executable, ir._package)
    code._defs = _eval(_u(ir._defs), lang)
    code._subs = _eval(_u(ir._subs), lang)
    code._inis = _eval(_u(ir._inis), lang)
    code._dels = _eval(_u(ir._dels), lang)
    return code
