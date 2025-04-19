# common model utilities

from typing import Any
import re
import copy
import json
import logging
import argparse
from .types import JsonObject, ModelType, ModelError, ModelDefs, ModelPath
from .utils import (
    same_model, model_in_models, split_object, unsplit_object, is_constructed,
    resolve_model, openfiles, constant_value
)

from .utils import log
from .recurse import recModel

# preprocessor-specific debug
log = logging.getLogger("preproc")
# log.setLevel(logging.DEBUG)


def _dedup_models(models: list[ModelType]) -> list[ModelType]:
    dedups = []
    for m in models:
        if not model_in_models(m, dedups):
            dedups.append(m)
    return dedups


# FIXME consistency with _structurally_distinct_models…
def _distinct_models(m1: ModelType, m2: ModelType, defs: ModelDefs, mpath: ModelPath) -> bool:
    """Whether m1 and m2 are provably distinct, i.e. do not have values in common."""
    m1, m2 = resolve_model(m1, defs), resolve_model(m2, defs)
    # log.warning(f"m1={m1} m2={m2}")
    # type
    if isinstance(m1, str) and m1 and m1[0] == "$":  # unresolved reference
        return m1 == "$NONE"  # special case for none which interact with nothing
    if isinstance(m2, str) and m2 and m2[0] == "$":  # unresolved reference
        return m2 == "$NONE"
    if is_constructed(m1) or is_constructed(m2):
        return False
    if type(m1) is not type(m2):
        # log.warning("distinct!")
        return True
    # else same type… try value
    c1, v1 = constant_value(m1, mpath)
    c2, v2 = constant_value(m2, mpath)
    # log.warning(f"{c1} {v1} / {c2} {v2}")
    if c1 and c2 and (type(v1) is not type(v2) or v1 != v2):
        return True
    return False


class _Object:
    """Internal representation of an object model."""

    def __init__(self, model: ModelType, gdefs: ModelDefs, mpath: ModelPath):
        assert isinstance(model, dict)
        must, may, defs, regs, oth = split_object(model, mpath)
        self._must = must
        self._may = may
        self._defs = defs
        self._regs = regs
        self._oth = oth
        self._global_defs = gdefs
        self._mpath = mpath

    def __contains__(self, o):
        """Whether o may be included in self (safe).

        That is all mandatory properties of o may be accepted by self.
        We could do a better job by checking model target incompatibility.
        """
        if not isinstance(o, _Object):
            raise ModelError("Only objects can be compared")
        if self._defs:
            # FIXME improve?
            log.debug("$-reference keys are not handled")
            return True
        # we look for mandatory one property in o which allows to discriminate
        for p, m in o._must.items():
            if p in self._must:
                if _distinct_models(m, self._must[p], self._global_defs, self._mpath):
                    return False
                # o.p does not discriminate with self
                continue
            elif p in self._may:
                if _distinct_models(m, self._may[p], self._global_defs, self._mpath):
                    return False
                continue
            for reg, model in self._regs.items():
                if re.search(reg, p):
                    # TODO catch more $NONE cases?
                    if model == "$NONE":
                        return False
                    # else try model resolution… this may depend on the execution order?
                    resolved = resolve_model(model, self._global_defs)
                    if resolved == "$NONE":
                        return False
                    if _distinct_models(m, model, self._global_defs, self._mpath):
                        return False
                    # else o.p does not discrimate
                    continue
            if "" in self._oth:
                if _distinct_models(m, self._oth[""], self._global_defs, self._mpath):
                    return False
                # self is open so would accept p
                continue
            # else: p is not must nor may nor re nor others!
            return False
        # we did not found any sure discrimination on this way
        return True


def merge_objects(models: list[ModelType], path: ModelPath) -> JsonObject|str:
    """Merge a list of simple object models."""

    assert isinstance(models, list) and len(models) > 0

    m0 = models[0]
    must, may, refs, regs, others = split_object(m0, path + [0])

    for i, m in enumerate(models[1:]):
        lpath = path + [i + 1]
        mu, ma, rf, rg, ot = split_object(m, lpath)
        # combine all properties
        # merge MUST
        for prop, mod in mu.items():
            lppath = path + [prop]
            if prop in must:
                if not same_model(mod, must[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                must[prop] = mod
                del may[prop]
            else:
                must[prop] = mod
        # merge MAY
        for prop, mod in ma.items():
            lppath = path + [prop]
            if prop in must:
                if not same_model(mod, must[prop]):  # ???
                    raise ModelError(f"incompatible may property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible may property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else pass
            else:
                may[prop] = mod
        # merge MAYBE
        for prop, mod in rf.items():
            lppath = path + [prop]
            # FIXME are the same $ available???
            if prop in refs:
                if not same_model(mod, refs[prop]):
                    raise ModelError(f"incompatible refs property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else pass
            else:
                refs[prop] = mod
        for prop, mod in rg.items():
            lppath = path + [prop]
            # FIXME are the same $ available???
            if prop in regs:
                if not same_model(mod, regs[prop]):
                    raise ModelError(f"incompatible regs property {prop} while merging: "
                                     f"{m0} / {m} {lppath}")
                # else pass
            else:
                regs[prop] = mod
        # merge OTHERS
        if "" in ot:
            if "" in others:
                if not same_model(ot[""], others[""]):
                    raise ModelError("incompatible catchall while merging: "
                                     f"{m0} / {m} [{lpath}.'']")
                # else pass
            else:
                others = ot

    return unsplit_object(must, may, refs, regs, others)


def _structurally_distinct_models(lm: list[ModelType], defs: ModelDefs, mpath: ModelPath) -> bool:
    """Whether all models are structurally distinct.

    This ensures that values in these are distinct.
    """
    log.debug(f"distinct on {lm}")
    # TODO add other constant values?
    types, objects, strings = set(), [], set()
    for m in lm:
        m = resolve_model(m, defs)
        mt = type(m)
        # special str preprocessing
        if isinstance(m, str):
            if m.startswith("$"):  # unresolved reference
                log.debug("- unresolved $-reference")
                return False
            elif m.startswith("="):
                c, v = constant_value(m, mpath)
                assert c
                m, mt = v, type(v)
            # else: empty or re or str constant

        if mt in (type(None), bool, int, float, list):
            if mt in types:
                log.debug(f"- multiple type {mt.__name__}")
                return False
            types.add(mt)
        elif isinstance(m, str):
            if m == "" or m[0] == "/":  # generic string
                if str in types or strings:
                    log.debug("- multiple strings")
                    return False
                types.add(str)
            else:  # constant string
                if str in types:
                    log.debug("- constant strings")
                    return False
                if m[0] == "_":
                    m = m[1:]
                # ???
                if m in strings:
                    log.warning(f"repeated constant: {m} {mpath}")
                    log.debug("- repeated constant strings")
                    return False
                strings.add(m)
        elif isinstance(m, dict):
            assert "@" not in m  # should have been resolved!
            assert "+" not in m  # should have been merged!
            if is_constructed(m):
                log.debug(f"- constructed model: {m}")
                return False
            # else dict is a model for an object
            obj = _Object(m, defs, mpath)
            # distinguishable objects?
            # - each object has a mandatory prop which cannot exists in others objects
            #   possibly with one exception
            if not objects:  # first encounted object
                objects.append(obj)
            else:
                for o in objects:
                    if o in obj and obj in o:
                        log.debug("- conflicting objects")
                        return False
                objects.append(obj)
        else:
            raise ModelError(f"unexpected model type ({mt.__name__}) {mpath}")
    return True
