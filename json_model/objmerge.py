#
# Merging
#
import copy

from .mtypes import ModelType, ModelPath
from .utils import log, tname, merge_objects
from .recurse import recModel, allFlt, builtFlt, noRwt
from .model import JsonModel
from . import analyze

# - inline defs inside +
# - distribute + over | and ^
# - merge objects, removing all +
#
def _mergeInlining(jm: JsonModel):

    changes = 0

    def miFlt(model: ModelType, path: ModelPath) -> bool:

        def inline(m: ModelType, p: ModelPath):
            nonlocal changes
            if isinstance(m, str):  # actual inlining
                assert m and m[0] == "$"
                if jm._isPredef(m):
                    return m
                changes += 1
                jmr, mo, seen  = jm, m, set()
                while isinstance(mo, str):
                    jmr = jmr.resolveRef(mo, p)
                    # loop guard, really needed?
                    if jmr._id in seen:
                        raise Exception(f"cycle while resolving {m}")
                    seen.add(jmr._id)
                    mo = jmr._model
                mo = copy.deepcopy(jmr._model)
                log.debug(f"{jm._id} inline from {jmr._id}")
                assert isinstance(mo, dict)
                if jm._defs._id != jmr._defs._id:  # if not in same name space
                    if jm._loose_int != jmr._loose_int or jm._loose_float != jmr._loose_float:
                        log.warning("should not combine models with distinct int/float looseness: "
                                    f"{jm._url} and {jmr._url}")
                    # substitute local references
                    def subRefRwt(m, p):
                        return jmr._defs.gget(m) if jmr._isRef(m) else m
                    return recModel(mo, allFlt, subRefRwt, True)
                else:  # keep as is
                    return mo
            else:
                assert isinstance(m, dict)
            return m

        if isinstance(model, dict) and "+" in model:
            plus = model["+"]
            assert isinstance(plus, list)  # pyright hint
            model["+"] = [inline(n, path + ["+", i]) for i, n in enumerate(plus)]

        return True

    jm._model = recModel(jm._model, miFlt, noRwt, True)

    log.debug(f"{jm._id}: merge inline {changes}")

    return changes > 0

def _mergeDistribute(jm: JsonModel):

    changes = 0

    def isAlt(m: ModelType) -> bool:
        return isinstance(m, dict) and ("|" in m or "^" in m)

    def mdFlt(model: ModelType, path: ModelPath) -> bool:
        # +( |(A B) C ) -> |( +(A C) +(B C) )
        nonlocal changes

        dive = builtFlt(model, path)

        if not isinstance(model, dict) or "+" not in model:  # no merge here
            return dive

        plus, is_xor = model["+"], False
        assert isinstance(plus, list), f"+ type: {tname(plus)}"

        if not any(map(isAlt, plus)):  # nothing to distribute
            return dive

        # actual distribution
        changes += 1

        lmodels: list[list[ModelType]] = [[]]
        for m in plus:
            assert isinstance(m, dict), f"unexpected model in +: {m}"
            if isAlt(m):
                alts = m["|"] if "|" in m else m["^"]
                is_xor |= "^" in m
                assert isinstance(alts, list)
                lmodels = [
                    copy.deepcopy(lm) + [n]
                        for lm in lmodels
                            for n in alts
                ]
            else:
                for lm in lmodels:
                    lm.append(m)

        # substitute + by ^ or | in place
        model["^" if is_xor else "|"] = [{"+": lo} for lo in lmodels]
        del model["+"]

        return dive

    jm._model = recModel(jm._model, mdFlt, noRwt)

    log.debug(f"{jm._id}: merge distribute {changes}")

    return changes > 0

def _mergeObjects(jm: JsonModel):
    """Actually compute and remove operator "+"."""

    changes = 0

    def moRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if not isinstance(model, dict) or "+" not in model:
            return model
        changes += 1
        plus = model["+"]
        assert isinstance(plus, list)  # pyright hint
        merged = merge_objects(plus, path + ["+"])  # pyright: ignore
        del model["+"]
        if len(model) > 0:
            model["@"] = merged
        else:
            assert isinstance(merged, dict)  # pyright hint
            model.update(merged)
        return model

    jm._model = recModel(jm._model, builtFlt, moRwt)

    log.debug(f"{jm._id}: merge objects {changes}")

    return changes > 0

def merge(jm: JsonModel):

    # NOTE after distribution, more inlining may be required
    # +( |( $A, {.1.} ), {.2.} ) -> |( +( $A, {.2.} ), +( {.1.}, {.2.} ) )

    updated = True
    while updated:
        _mergeInlining(jm)
        updated = _mergeDistribute(jm)

    if jm._debug:  # check merge precondition

        def is_object(m: ModelType) -> bool:  # NOTE "+" is allowed
            return isinstance(m, dict) and not ("@" in m or "|" in m or "^" in m or "&" in m)

        def merge_on_objects(model: ModelType, path: ModelPath) -> bool:
            if isinstance(model, dict) and "+" in model:
                assert isinstance(plus := model["+"], list)  # sanity
                return all(map(is_object, plus))
            return True

        assert analyze.check(jm, merge_on_objects, "only objects under +")

    _mergeObjects(jm)

    if jm._debug:
        assert analyze.check(jm, lambda m, _: not isinstance(m, dict) or "+" not in m)
