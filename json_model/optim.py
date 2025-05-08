#
# Model Optimizations
#
from .mtypes import ModelPath, ModelType
from .utils import log, is_cst, _structurally_distinct_models
from .recurse import recModel, allFlt, builtFlt
from .model import JsonModel

def xor_to_or(jm: JsonModel):
    """Change xor to less coslty or if possible."""

    changes = 0

    def x2oRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if isinstance(model, dict) and "^" in model:
            xor = model["^"]
            assert isinstance(xor, list) and "|" not in model
            # TODO handle distinct constants, eg "=1", "=2"…
            if _structurally_distinct_models(xor, jm._defs, path + ["^"]):  # pyright: ignore
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

    def real_equal(i, j) -> bool:  # avoid True == 1 and 0.0 == 0…
        return type(i) is type(j) and i == j

    def deduplicate(lv):
        # return list(set(l))  # too easy: {True, 1} == {True}
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
            if "|" in model:
                lor = model["|"]
                assert isinstance(lor, list)
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
            elif "&" in model:
                land = model["&"]
                assert isinstance(land, list)
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
            elif "^" in model:
                lxor = model["^"]
                assert isinstance(lxor, list)
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
            elif "+" in model:
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
                    del model["!"]
                # constraint without actual constraints
                if not (set(model.keys()) - {"#", "~", "$", "%", "@"}):
                    if path == [] and "#" in model:
                        assert isinstance(model["#"], str)
                        if "JSON_MODEL_" in model["#"]:
                            return model
                    return model["@"]
        return model

    jm._model = recModel(jm._model, allFlt, evalRwt)

    log.debug(f"{jm._id}: eval {changes}")

    return changes > 0

def optimize(jm: JsonModel):
    changed = True
    while changed:
        changed = False
        changed |= const_prop(jm)
        changed |= partial_eval(jm)
        changed |= flatten(jm)
        changed |= xor_to_or(jm)
