#
# Model Optimizations
#
from .mtypes import ModelPath, ModelType
from .utils import log, is_cst, _structurally_distinct_models, constant_value, same_model
from .recurse import recModel, allFlt, builtFlt
from .model import JsonModel
from .analyze import ultimate_type
from .runtime import ConstSet

def real_equal(i, j) -> bool:  # avoid True == 1 and 0.0 == 0…
    return type(i) is type(j) and i == j

def minl(model: ModelType, models: list[ModelType]) -> bool:
    return any(map(lambda m: real_equal(m, model), models))

# remove one occurence from list of models
def mdell(model: ModelType, models: list[ModelType]) -> bool:
    index = -1
    for i, m in enumerate(models):
        if real_equal(m, model):
            index = i
    if index != -1:
        del models[index]
    return index != -1

def normalizeModels(models: list[ModelType]) -> int:
    """Replace model predefs in the list with their canonic form."""
    IGNORE = object()
    changes = 0

    for idx, model in enumerate(models):
        nmodel = IGNORE
        if isinstance(model, str):
            if model == "$STRING":
                nmodel = ""
            elif model in ("$INT", "$INTEGER", "$I32", "$I64"):
                nmodel = -1
            elif model in ("$U32", "$U64"):
                nmodel = 0
            elif model in ("$FLOAT", "$F32", "$F64"):
                nmodel = -1.0
            elif model in ("$BOOL", "$BOOLEAN"):
                nmodel = True
            elif model in ("$NULL", "=null"):
                nmodel = None
        if nmodel != IGNORE:
            changes += 1
            models[idx] = nmodel  # type: ignore

    return changes

def xor_to_or(jm: JsonModel):
    """Change xor to less coslty or if possible."""

    changes = 0

    def x2oRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if isinstance(model, dict) and "^" in model:
            xor = model["^"]
            lpath = path + ["^"]
            assert isinstance(xor, list) and "|" not in model

            consts = [constant_value(m, lpath + [i]) for i, m in enumerate(xor)]

            # constant-only enum case
            if all(consts[i][0] for i in range(len(xor))):
                if len(ConstSet([consts[i][1] for i in range(len(xor))])) == len(xor):  # type: ignore
                    changes += 1
                    del model["^"]
                    model["|"] = xor
                # else some constants are repeated thus excluded by "^"
            elif _structurally_distinct_models(xor, jm._defs, lpath):  # pyright: ignore
                changes += 1
                del model["^"]
                model["|"] = xor

        return model

    jm._model = recModel(jm._model, builtFlt, x2oRwt)

    log.debug(f"{jm._id}: x2o {changes}")

    return changes > 0

def flatten(jm: JsonModel):
    """Flatten or, xor, and and merge operators."""

    changes = 0

    def flatRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        for op in ("|", "&", "^", "+"):
            if isinstance(model, dict) and op in model:
                models, updated = model[op], False
                assert isinstance(models, list)
                nmodels = []
                # NOTE empty lists are handled in eval
                if len(models) == 1:
                    changes += 1
                    return models[0]
                for m in models:
                    if isinstance(m, dict) and op in m:
                        changes += 1
                        updated = True
                        lm = m[op]
                        assert isinstance(lm, list)
                        nmodels.extend(lm)
                    else:
                        nmodels.append(m)
                if updated:
                    model[op] = nmodels
        return model

    jm._model = recModel(jm._model, builtFlt, flatRwt)

    log.debug(f"{jm._id}: flatten {changes}")

    return changes > 0

def const_prop(jm: JsonModel):
    """Propagate constants and predefs to their references."""

    changes = 0

    def cpRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if jm._isRef(model):
            jmp = jm.resolveRef(model, path)
            if jm._isPredef(jmp._model):
                changes += 1
                return jmp._model
            elif is_cst(jmp._model):
                changes += 1
                return jmp._model
        return model

    jm._model = recModel(jm._model, allFlt, cpRwt, True)

    log.debug(f"{jm._id}: constant propagation {changes}")

    return changes > 0

def partial_eval(jm: JsonModel):
    """Model partial evaluation."""

    changes = 0

    # helpers
    def empty_obj(o):
        return isinstance(o, dict) and (len(o) == 0 or len(o) == 1 and "#" in o)

    def deduplicate(lv):
        # return list(set(l))  # too easy: {True, 1} == {True}
        # TODO use an extended ConstSet?
        n = []
        for i in lv:
            if not any(map(lambda x: real_equal(x, i), n)):
                n.append(i)
        return n

    def evalRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if isinstance(model, str) and jm._isRef(model):
            jms = jm.resolveRef(model, path)
            if isinstance(jms._model, str) and jms._isPredef(jm._model):
                changes += 1
                return jms._model

        elif isinstance(model, dict):

            if "|" in model:  # optimize OR
                lor = model["|"]
                assert isinstance(lor, list)
                changes += normalizeModels(lor)

                # int type inclusions
                if minl(1, lor) and (minl(0, lor) or minl(-1, lor)):
                    changes += 1
                    mdell(1, lor)
                if minl(0, lor) and minl(-1, lor):
                    changes += 1
                    mdell(0, lor)

                # float type inclusions
                if minl(1.0, lor) and (minl(0.0, lor) or minl(-1.0, lor)):
                    changes += 1
                    mdell(1.0, lor)
                if minl(0.0, lor) and minl(-1.0, lor):
                    changes += 1
                    mdell(0.0, lor)
                if minl("", lor) and minl("$STRING", lor):
                    changes += 1
                    mdell("$STRING", lor)

                # others
                if len(lor) == 0:
                    changes += 1
                    return "$NONE"
                elif "$ANY" in lor:
                    changes += 1
                    return "$ANY"
                elif "$NONE" in lor:
                    changes += 1
                    model["|"] = lor = list(filter(lambda m: m != "$NONE", lor))
                elif len(lv := deduplicate(lor)) != len(lor):
                    changes += 1
                    model["|"] = lor = lv

                if len(lor) == 1:
                    changes += 1
                    return lor[0]

            elif "&" in model:  # optimize AND
                land = model["&"]
                assert isinstance(land, list)
                changes += normalizeModels(land)

                # manage simple type inclusions on ints
                if minl(-1, land) and (minl(0, land) or minl(1, land)):
                    mdell(-1, land)
                if minl(0, land) and minl(1, land):
                    mdell(0, land)

                # idem on floats
                if minl(-1.0, land) and (minl(0.0, land) or minl(1.0, land)):
                    mdell(-1.0, land)
                if minl(0.0, land) and minl(1.0, land):
                    mdell(0.0, land)

                # other optimizations
                if len(land) == 0:
                    changes += 1
                    return "$ANY"
                elif "$NONE" in land:
                    changes += 1
                    return "$NONE"
                elif len(lv := deduplicate(land)) != len(land):
                    changes += 1
                    model["&"] = land = lv
                if len(land) == 1:
                    changes += 1
                    return land[0]
                # if ultimates types are distinct, no value can match
                utypes = set(ultimate_type(jm, m) for m in land)
                if None not in utypes and len(utypes) > 1 or None in utypes and len(utypes) > 2:
                    return "$NONE"

            elif "^" in model:  # optimize XOR
                lxor = model["^"]
                assert isinstance(lxor, list)
                changes += normalizeModels(lxor)
                if len(lxor) == 2:
                    if same_model(lxor[0], lxor[1]):
                        return "$NONE"
                if len(lxor) == 0:
                    changes += 1
                    return "$NONE"
                elif len(lxor) == 1:
                    changes += 1
                    return lxor[0]
                elif "$NONE" in lxor:
                    changes += 1
                    model["^"] = list(filter(lambda m: m != "$NONE", lxor))
                elif len(list(filter(lambda m: m == "$ANY", lxor))) >= 2:
                    changes += 1
                    return "$NONE"
                # TODO more cleanups
                # ^(A A ...) = ^(...) ? not so, depends on inclusions?

            elif "+" in model:  # optimize MERGE
                plus = model["+"]
                assert isinstance(plus, list)
                if len(plus) == 0:  # {"+": []} == {}
                    changes += 1
                    del model["+"]
                elif len(plus) == 1:
                    changes += 1
                    return plus[0]
                elif any(map(empty_obj, plus)):
                    changes += 1
                    model["+"] = list(filter(lambda o: not empty_obj(o), plus))
                # TODO more cleanup? could I remove $NONE? $ANY?

            elif "@" in model:

                # "!": false is the default, so is not needed
                if "!" in model and not model["!"]:
                    changes += 1
                    del model["!"]
                # constraint without actual constraints
                if not (set(model.keys()) - {"#", "~", "$", "%", "@"}):
                    # keep directives
                    if path == [] and "#" in model:
                        assert isinstance(model["#"], str)
                        if "JSON_MODEL_" in model["#"]:
                            return model
                    changes += 1
                    return model["@"]
                # some non-feasable numerical cases
                lev, gev = None, None
                # add type information
                if isinstance(model["@"], float):
                    if model["@"] in (0.0, 1.0):
                        gev = 0.0
                elif isinstance(model["@"], int):
                    if model["@"] == 0:
                        gev = 0.0
                    elif model["@"] == 1:
                        gev = 1.0
                # map < and <= together for now
                if "<" in model:
                    if isinstance(model["<"], (int, float)):
                        lev = float(model["<"])
                if "<=" in model:
                    if isinstance(model["<="], (int, float)):
                        v = float(model["<="])
                        lev = v if lev is None else min(lev, v)
                # idem > and >=
                if ">" in model:
                    if isinstance(model[">"], (int, float)):
                        gev = float(model[">"])
                if ">=" in model:
                    if isinstance(model[">="], (int, float)):
                        v = float(model[">="])
                        gev = v if gev is None else max(gev, v)
                # map = to <= and >=
                if "=" in model:
                    if isinstance(model["="], (int, float)):
                        v = float(model["="])
                        lev = v if lev is None else min(lev, v)
                        gev = v if gev is None else max(gev, v)
                # conclude for < <= = > >=
                if gev is not None and lev is not None and gev > lev:
                    changes += 1
                    return "$NONE"
                # cleanup redundant !=
                if "!=" in model:
                    if isinstance(model["!="], (int, float)):
                        nev = float(model["!="])
                        if gev is not None and nev < gev or lev is not None and lev < nev:
                            changes += 1
                            del model["!="]
                # TODO could do other cases about str?
        return model

    jm._model = recModel(jm._model, allFlt, evalRwt)

    log.debug(f"{jm._id}: eval {changes}")

    return changes > 0

# FIXME probably some corner case issues
def simplify(jm: JsonModel):
    """Simplify properties and constraints in some cases."""

    changes: int = 0

    def simpRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if isinstance(model, dict):
            for old, new in [ ("//", ""), ("/^$/", "?")]:
                # FIXME in some corner case the simplification may be wrong…
                if old in model and new not in model:
                    model[new] = model[old]
                    del model[old]
            if "@" in model:
                # FIXME
                ultimate = ultimate_type(jm, model)
                if ultimate in (None, float):  # keep safe
                    return model
                # bool is an error?
                # else keep int, str, list, dict
                # str constraints? should be handled elsewhere?
                if ultimate in (None, bool, int, float, list, dict):
                    for op in ("<=", "<", "=", "!=", ">", ">="):
                        if op in model and isinstance(model[op], str):
                            # raise ModelError("str constraint for non str model")
                            log.warning(f"unexpected str constraint at {path}")
                            changes += 1
                            return "$NONE"
                # detect redundant or infeasible int constraints
                le = None if "<=" not in model or not isinstance(model["<="], (int, float)) else model["<="]
                lt = None if "<" not in model or not isinstance(model["<"], (int, float)) else model["<"]
                eq = None if "=" not in model or not isinstance(model["="], (int, float)) else model["="]
                ne = None if "!=" not in model or not isinstance(model["!="], (int, float)) else model["!="]
                ge = None if ">=" not in model or not isinstance(model[">="], (int, float)) else model[">="]
                gt = None if ">" not in model or not isinstance(model[">"], (int, float)) else model[">"]
                # handle floats for int constraints
                if isinstance(le, float):
                    le = int(le)
                if isinstance(lt, float):
                    lt = int(lt) if int(lt) == lt else int(lt + 1.0)
                if isinstance(ge, float):
                    ge = int(ge) if int(ge) == ge else int(ge + 1.0)
                if isinstance(gt, float):
                    gt = int(gt)
                if isinstance(eq, float):
                    if int(eq) != eq:  # infeasible constraint
                        changes += 1
                        return "$NONE"
                    else:
                        eq = int(eq)
                if isinstance(ne, float):
                    if int(ne) != ne:  # always feasible
                        changes += 1
                        ne = None
                        del model["ne"]
                    else:
                        ne = int(ne)
                # replace int gt/lt by int ge/le
                if lt is not None:
                    le = lt - 1 if le is None or le >= lt else le
                    lt = None
                    del model["<"]
                    changes += 1
                if gt is not None:
                    ge = gt + 1 if ge is None or ge <= gt else ge
                    gt = None
                    del model[">"]
                    changes += 1
                # boolean and null cannot have int comparisons
                if ultimate in (type(None), bool) and \
                        (ge is not None or le is not None or eq is not None or ne is not None):
                    changes += 1
                    return "$NONE"
                # ge/le consistency and simplification
                if ge is not None and le is not None:
                    if le < ge:
                        changes += 1
                        return "$NONE"
                    if le == ge:
                        changes += 1
                        eq, le, ge = le, None, None
                # eq consistency and redundancy
                if eq is not None:
                    if le is not None:
                        if eq > le:
                            changes += 1
                            return "$NONE"
                        le = None
                        del model["<="]
                        changes += 1
                    if ge is not None:
                        if eq < ge:
                            changes += 1
                            return "$NONE"
                        ge = None
                        del model[">="]
                        changes += 1
                    if ne is not None:
                        if eq == ne:
                            changes += 1
                            return "$NONE"
                        ne = None
                        del model["!="]
                        changes += 1
                # ne redundancy
                if ne is not None:
                    if le is not None:
                        if ne > le:  # type: ignore
                            changes += 1
                            ne = None
                            del model["!="]
                    if ge is not None:
                        if ne < ge:  # type: ignore
                            changes += 1
                            ne = None
                            del model["!="]
                # integer target
                # TODO set maxint?
                if isinstance(model["@"], str) and model["@"] in ("$INT", "$INTEGER", "$I32", "$I64"):
                    changes += 1
                    model["@"] = -1
                elif isinstance(model["@"], str) and model["@"] in ("$U32", "$U64"):
                    changes += 1
                    model["@"] = 0
                if isinstance(model["@"], int):
                    target = model["@"]
                    if eq is not None:
                        changes += 1
                        if eq < target:
                            return "$NONE"
                        else:
                            return f"={eq}"
                    if ge is not None:
                        if ge == 1 and target != 1:
                            changes += 1
                            model["@"] = 1
                            ge = None
                        elif ge == 0 and target == -1:
                            changes += 1
                            model["@"] = 0
                            ge = None
                    if le is not None:
                        if target >= 0 and target > le:
                            changes += 1
                            return "$NONE"
                # update possibly changed values
                if le is not None:
                    model["<="] = le
                elif "<=" in model and isinstance(model["<="], (int, float)):
                    del model["<="]
                if ge is not None:
                    model[">="] = ge
                elif ">=" in model and isinstance(model[">="], (int, float)):
                    del model[">="]
        return model

    jm._model = recModel(jm._model, allFlt, simpRwt)

    return changes > 0

def optimize(jm: JsonModel):
    changed = True
    while changed:
        changed = False
        changed |= const_prop(jm)
        changed |= simplify(jm)
        changed |= partial_eval(jm)
        changed |= flatten(jm)
        changed |= xor_to_or(jm)
