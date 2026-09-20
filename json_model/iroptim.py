#
# JSON Model IR Optimizations
#
from typing import Callable
import json
import copy

from .utils import log
from .language import Block
from .mtypes import Jsonable, JsonScalar, Number, TestHint, Conditionals, TopType, NullType
from .runtime import Path, Report

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
        case "gv":
            read |= {op["var"]}
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
            if op["o"] not in NO_BOOL_EFFECT:
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
    return _noOps(op["seq"], reporting) if _isOp(op, "seq") else \
        _isOps(op, IGN_REP if reporting else IGN)

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
                op["val"] = negate(cond)
            elif vf is False:
                # C ? E : F -> C && E
                op["val"] = {"o": "&", "exprs": [ cond, tbv["val"] ]}
            elif vt is True:
                # C ? T : E -> C || E
                op["val"] = {"o": "|", "exprs": [ cond, fbv["val"] ]}
            elif vf is True:
                # C ? E : T -> !C || E
                op["val"] = {"o": "|", "exprs": [ negate(cond), tbv["val"] ]}
            else:
                assert vt is False
                # C ? F : E -> !C && E
                op["val"] = {"o": "&", "exprs": [ negate(cond), fbv["val"] ]}
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

def negate(op: Jsonable) -> Jsonable:
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

def bvar_uses(op: Jsonable, var: str) -> int:
    """Count boolean variable occurrences in boolean expressions."""
    if op is None:
        return 0
    elif isinstance(op, str):
        return 1 if op == var else 0
    elif isinstance(op, dict) and "o" in op:
        match op["o"]:
            # simple boolean expressions
            case "gv":
                return 1 if op["var"] == var else 0
            case "|"|"&":
                return bvar_uses(op["exprs"], var)
            case "not"|"()":
                return bvar_uses(op["e"], var)
            # statements
            case "bv":
                return bvar_uses(op["val"], var)
            case "ret":
                return bvar_uses(op["res"], var)
            case "if":
                return (
                    bvar_uses(op["cond"], var) +
                    bvar_uses(op["true"], var) +
                    bvar_uses(op["false"], var)
                )
            case "ifs":
                return (
                    sum(map(
                        lambda x: bvar_uses(x[0], var) + bvar_uses(x[2], var),
                        op["cond_true"]
                    )) +
                    bvar_uses(op["false"], var)
                )
            case "aL"|"oL"|"iL"|"sfu":
                return bvar_uses(op["body"], var)
            case "seq":
                return bvar_uses(op["seq"], var)
            case _:  # is this safe?
                return 0
    elif isinstance(op, list):
        return sum(map(lambda s: bvar_uses(s, var), op))
    else:  # safe, probably dead code
        return 0

def bvar_subs(op: Jsonable, var: str, val: Jsonable) -> Jsonable:
    """Replace boolean variable reference by value in boolean expression."""
    if isinstance(op, str):  # maybe actual substitition
        return val if op == var else op
    elif isinstance(op, dict) and "o" in op:
        match op["o"]:
            case "|"|"&":
                op["exprs"] = [ bvar_subs(e, var, val) for e in op["exprs"] ]
            case "not"|"()":
                op["e"] = bvar_subs(op["e"], var, val)
            case "gv":  # substitute an explicit reference (get value)
                if op["var"] == var:
                    op.clear()
                    op.update(**val)
            case _:  # no propagation out of boolean expression
                pass
    return op

def bvar_is_used(op: Jsonable, var: str) -> bool:
    """Whether boolean variable is used in boolean expression."""
    # log.warning(f"used: var={var} op={op}")
    return bvar_uses(op, var) != 0

# FIXME full simplification should require several passes
def _optimSeq(seq: Sequence, bool_vars: set[str], reporting: bool) -> Effect:
    """Optimize instruction sequence if/then patterns on boolean variables in place."""

    effects: Effects = [ _getEffect(op, bool_vars, reporting) for op in seq ]
    assert len(effects) == len(seq)

    cum_read, cum_write, cum_value = set(), set(), {}

    if len(seq) == 0:
        return cum_read, cum_write, cum_value

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
        cum_read |= read
        cum_write |= write
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
                nseq = op["true" if direct == cum_value[var] else "false"]
                op.clear()
                op.update(o="seq", seq=nseq)
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
                    op.update({"o": "no", "#": "IRO removed useless conditional assignment"})
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
                            newop = {"o": "ret", "res": negate(ifop["cond"])}
                        else:
                            newop = {"o": "ret", "res": {"o": "cst", "c": False}}
                    else:
                        newop = {
                            "o": "ret",
                            "res": {"o": "&", "exprs": [negate(ifop["cond"]), op["res"]]}
                        }
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

    # simplify X = E1; X = E2 (no X!);
    assign: Jsonable|None = None
    for op in seq:
        if _noOp(op, False):
            pass
        elif _isOp(op, "bv"):
            if assign and assign["var"] == op["var"] and not bvar_is_used(op["val"], op["var"]):
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
            assert op["declare"]
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
            if same_var and (assign2 := _isBoolAssign(op["true"], reporting)) and \
                    assign2["var"] == assign["var"]:
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
        # FIXME reporting?
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

    # simplify "V = E; ret f(V where V appears once)" to "ret f(E)"
    val: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv") and op["val"] is not None:
            val = op
        elif val is not None and _isOp(op, "ret") and bvar_uses(op["res"], val["var"]) == 1:
            op["res"] = bvar_subs(op["res"], val["var"], val["val"])
            val.clear()
            val.update({"o": "ign", "#": "IRO subs boolean var in return"})
            val = None
        else:
            val = None

    # simplify "decl V = E; V' = f(V) where V appears once; no V uses" to "V' = f(E)"
    val1: Jsonable|None = None
    val2: Jsonable|None = None
    i = 0
    for op in seq:
        i += 1
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv") and op["val"] is not None and op["declare"]:
            val1 = op
        elif val1 is not None and _isOp(op, "bv") and val2 is None:
            uses = bvar_uses(op["val"], val1["var"])
            if uses == 0:
                pass
            elif uses == 1:
                val2 = op
            else:
                val1 = None
        elif val1 is not None and bvar_uses(op, val1["var"]) != 0:
            val1 = None
    if val1 is not None and val2 is not None:
        val2["val"] = bvar_subs(val2["val"], val1["var"], val1["val"])
        val1.clear()
        val1.update({"o": "ign", "#": "IRO subs boolean var in next assignment"})

    # move declaration to first assignment decl V; ... ; V = V';
    dec: Jsonable|None = None
    for op in seq:
        if _noOp(op, reporting):
            pass
        elif _isOp(op, "bv") and op["val"] is None and op["declare"]:
            dec = op
        elif dec is not None and _isOp(op, "bv") and op["var"] != dec["var"]:
            pass
        elif dec is not None and _isOp(op, "bv") and op["var"] == dec["var"]:
            # move declaration
            op["declare"] = True
            dec.clear()
            dec.update({"o": "ign", "#": "IRO move declaration to first assignment"})
            dec = None

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

def _goIR(code: Jsonable, path: Path) -> bool:
    return True

def _goStructIR(code: Jsonable, path: Path) -> bool:
    return isinstance(code, (dict, list))

def _nopeIR(code: Jsonable, path: Path) -> Jsonable:
    return code

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

#
# Actual IR optimizations
#

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

    recurseIR(code, _goStructIR, repRwt)

    log.debug(f"csc {changes}")
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

        return code

    recurseIR(code, _goStructIR, peRwt)

    log.debug(f"pev {changes}")
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
                ands = copy.deepcopy(exprs[first: last + 1])
                for e in ands:
                    e["exprs"] = e["exprs"][1:]

                # common expression
                exprs[first]["o"] = "&"
                exprs[first]["exprs"] = [ common, {"o": "|", "exprs": ands} ]
                # falsify other items
                for i in range(first + 1, last + 1):
                    exprs[i].clear()
                    exprs[i].update(o="cst", c=False)

                changes += 1

        if _isOps(code, {"&", "|"}):
            # remove True/False constants in passing
            keep_it = (lambda o: not _isTrue(o)) if code["o"] == "&" else \
                (lambda o: not _isFalse(o))
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

    log.debug(f"cse {changes}")
    return changes

def elimEmptySeq(code: Jsonable, reporting: bool) -> int:
    """Eliminate no-effect sequences with only new variables."""
    changes = 0

    def eecRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if isinstance(code, list):
            remove = True
            for op in code:
                if _noOp(op, reporting):
                    pass
                elif _isOps(op, {"pv", "iv", "bv", "jv"}) and op["declare"]:
                    # simple declarations
                    pass
                elif _isOp(op, "seq") and _noOps(op["seq"], reporting):
                    pass
                else:
                    remove = False
                    break
            if code and remove:
                changes += 1
                code = getComments(code) + [ {"o": "no"} ]
        return code

    recurseIR(code, _goIR, eecRwt)

    log.debug(f"ees {changes}")
    return changes


def getComments(code: Jsonable) -> list[dict[str, Jsonable]]:
    """Extract comments recursively."""

    comments = []

    def keepComments(code: Jsonable, _: Path) -> True:
        nonlocal comments
        if isinstance(code, dict):
            if _isOp(code, "co"):
                comments.append(copy.deepcopy(code))
                return False
            else:
                return True
        elif isinstance(code, list):
            return True
        else:
            return False

    recurseIR(code, keepComments, _nopeIR)
    return comments

def elimEmptyLoop(code: Jsonable, reporting: bool) -> int:
    """Eliminate empty lists in loops and sequences, but keep comments."""
    changes = 0

    def eelRwt(code: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if _isOps(code, {"oL", "aL", "iL"}) and _noOps(code["body"], reporting):
            changes += 1
            coms = getComments(code["body"])
            if coms:
                return {"o": "seq", "seq": coms}
            else:
                return {"o": "ign", "#": "empty loop body"}
        elif _isOp(code, "seq") and _noOps(code["seq"], reporting):
            if len(code["seq"]) == 0:
                return {"o": "ign", "#": "empty sequence"}
            if all(_isOp(o, "co") for o in code["seq"]):
                return code
            # else
            changes += 1
            coms = getComments(code["seq"])
            if coms:
                return {"o": "seq", "seq": coms}
            else:
                return {"o": "ign", "#": "empty sequence"}
        return code

    recurseIR(code, _goIR, eelRwt)

    log.debug(f"eel {changes}")
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
                changes += 1
                return list(filter(lambda o: _isOps(o, {"co", "ret", "seq", "ign"}), code))
        return code

    recurseIR(code, _goIR, edcRwt)

    log.debug(f"edc {changes}")
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

    recurseIR(code, _goStructIR, eucRwt)

    log.debug(f"euc {changes}")
    return changes

# TODO what about other variables?!
def elimUnusedBoolVars(code: Jsonable) -> int:
    """Bool variables may be set but unused."""

    # collect existing boolean variables
    bvars: dict[str, list[dict[str, Jsonable]]] = {}

    def _bvarRwt(op: Jsonable, path: Path) -> Jsonable:
        nonlocal bvars
        if _isOp(op, "bv"):
            var = op["var"]
            if var not in bvars:
                bvars[var] = []
            bvars[var].append(op)
        return op

    recurseIR(code, _goStructIR, _bvarRwt)

    # cleanup unused ones
    changes: int = 0

    for var, bops in bvars.items():
        if not bvar_is_used(code, var):
            for bop in bops:
                assert bop["o"] == "bv"
                changes += 1
                bop.clear()
                bop.update(o="ign")

    log.debug(f"eub {changes}")
    return changes

def mifToIf(code: Jsonable) -> int:
    """Turn multi-if in a simple if is possible."""

    changes: int = 0

    def mif2ifRwt(op: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if _isOp(op, "ifs") and len(op["cond_true"]) == 1:
            cond, likely, btrue = op["cond_true"][0]
            del op["cond_true"]
            op.update(o="if", cond=cond, true=btrue, likely=likely)
            changes += 1
        return op

    recurseIR(code, _goStructIR, mif2ifRwt)

    log.debug(f"m2i {changes}")
    return changes

def simplifySimpleIf(code: Jsonable, reporting: bool) -> int:
    """If with non effective or empty sequences."""

    changes: int = 0

    def sisifRwt(op: Jsonable, _: Path) -> Jsonable:
        nonlocal changes
        if _isOp(op, "if"):
            empty_true =  _noOps(op["true"], reporting)
            empty_false = _noOps(op["false"], reporting)
            if empty_true:
                changes += 1
                if empty_false:
                    op.clear()
                    op.update(o="ign")
                else:
                    op["true"] = op["false"]
                    op["false"] = []
                    op["cond"] = negate(op["cond"])
            elif empty_false and len(op["false"]) != 0:
                op["false"] = []
                changes += 1
        return op

    recurseIR(code, _goStructIR, sisifRwt)

    log.debug(f"ssi {changes}")
    return changes

def optimizeIR(
            code: Block, *,
            shortcuts: dict[str, str],
            partial: bool = True,
            if_optim: bool = True,
            reporting: bool = True
        ) -> Block:
    """Optimize IR code."""

    if not if_optim and not shortcuts:
        return code

    optimized, calls = 0, 0

    for i, c in list(enumerate(code)):
        if c is None or c == "":
            continue
        ins = json.loads(c)
        if not _isOp(ins, "sfu"):
            continue
        log.debug(f"IR optim considering function {ins['name']}")
        changed: bool = False
        changed |= mifToIf(ins) > 0
        if partial:
            changed |= partialEval(ins, reporting) > 0
        # sequence optimizations
        if if_optim:
            _optimSeq(ins["body"], set(), reporting=reporting)
            changed = True  # FIXME
        if shortcuts:  # call shortcuts
            changes = callShortcuts(ins, shortcuts)
            calls += changes
            changed |= changes > 0
        # FIXME should we iterate?
        changed |= elimCommonSub(ins) > 0
        changed |= elimDeadCode(ins, reporting) > 0
        changed |= elimUnreachableCode(ins) > 0
        changed |= elimUnusedBoolVars(ins) > 0
        changed |= simplifySimpleIf(ins, reporting) > 0
        changed |= elimEmptySeq(ins, reporting) > 0
        changed |= elimEmptyLoop(ins, reporting) > 0
        if changed:
            code[i] = json.dumps(ins)

    log.info(f"optimize ir: {len(code)} functions processed, {calls} call shortcuts")

    return code
