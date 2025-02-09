# common model utilities

import json
import re
import copy
from typing import Any
import logging
import argparse
from .utils import Object, ModelType, ModelError
from .utils import same_model, model_in_models, split_object, unsplit_object, is_constructed, resolve_model, openfiles, constant_value

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
def _distinct_models(m1: ModelType, m2: ModelType, defs: dict[str, Any], mpath: str) -> bool:
    """Whether m1 and m2 are provably distinct, i.e. do not have values in common."""
    m1, m2 = resolve_model(m1, defs), resolve_model(m2, defs)
    tm1, tm2 = type(m1), type(m2)
    # log.warning(f"m1={m1} m2={m2}")
    # type
    if tm1 is str and m1 and m1[0] == "$":  # unresolved reference
        return m1 == "$NONE"  # special case for none which interact with nothing
    if tm2 is str and m2 and m2[0] == "$":  # unresolved reference
        return m2 == "$NONE"
    if is_constructed(m1) or is_constructed(m2):
        return False
    if tm1 is not tm2:
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

    def __init__(self, model: ModelType, gdefs: dict[str, Any], mpath: str):
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

def merge_simple_models(models: list[Any], defs, path: str="") -> Object:
    """Merge a list of simple object models."""

    # sanity checks
    if not isinstance(models, (list, tuple)):
        raise ModelError(f"unexpected models to merge: {models} (type{models}) [{path}]")
    if len(models) == 0:
        # raise ModelError(f"empty models to merge")
        return "$NONE"

    # must follow references!
    dict_models = []
    for i, m in enumerate(models):
        # log.debug(f"m {i}: {m}")
        lpath = f"{path}[{i}]"
        if isinstance(m, dict):
            if "+" in m:
                log.warning("+ in +")
                m = merge_simple_models(m["+"], defs, lpath)
            # log.debug(f"m 1: {m}")
            dict_models.append(m)
        elif isinstance(m, str) and len(m) >= 1 and m[0] == "$":  # reference
            log.warning("+ with references should be resolved before?")
            m2 = defs.model(m[1:])  # FIXME $x -> $y -> {} ?
            assert isinstance(m2, dict)
            # log.debug(f"m 2: {m2}")
            dict_models.append(m2)
        else:
            raise ModelError(f"unexpected model to merge: {m} [{lpath}]")
    models = dict_models
    del dict_models

    if not all(map(lambda m: isinstance(m, dict), models)):
        raise ModelError(f"can only merge dicts [{path}]")
    if any(map(is_constructed, models)):
        raise ModelError(f"can only merge simple objects [{path}]")

    m0 = models[0]
    must, may, refs, regs, others = split_object(m0, f"{path}[0]")

    for i, m in enumerate(models[1:]):
        lpath = f"{path}[{i+1}]"
        mu, ma, rf, rg, ot = split_object(m, lpath)
        # combine all properties
        # merge MUST
        for prop, mod in mu.items():
            if prop in must:
                if not same_model(mod, must[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                must[prop] = mod
                del may[prop]
            else:
                must[prop] = mod
        # merge MAY
        for prop, mod in ma.items():
            if prop in must:
                if not same_model(mod, must[prop]):  # ???
                    raise ModelError(f"incompatible may property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible may property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                # else pass
            else:
                may[prop] = mod
        # merge MAYBE
        for prop, mod in rf.items():
            # FIXME are the same $ available???
            if prop in refs:
                if not same_model(mod, refs[prop]):
                    raise ModelError(f"incompatible refs property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                # else pass
            else:
                refs[prop] = mod
        for prop, mod in rg.items():
            # FIXME are the same $ available???
            if prop in regs:
                if not same_model(mod, regs[prop]):
                    raise ModelError(f"incompatible regs property {prop} while merging: {m0} / {m} [{lpath}.{prop}]")
                # else pass
            else:
                regs[prop] = mod
        # merge OTHERS
        if "" in ot:
            if "" in others:
                if not same_model(ot[""], others[""]):
                    raise ModelError(f"incompatible catchall while merging: {m0} / {m} [{lpath}.'']")
                # else pass
            else:
                others = ot

    return unsplit_object(must, may, refs, regs, others)

def _merge_object(i, j):
    """Merge two objects.

    - +(A), B -> +(A, B)
    - A, +(B) -> +(A, B)
    - A, B    -> +(A, B)
    """
    if isinstance(i, dict) and "+" in i:
        d = copy.deepcopy(i)
        d["+"].append(copy.deepcopy(j))
    elif isinstance(j, dict) and "+" in j:
        d = copy.deepcopy(j)
        d["+"].append(copy.deepcopy(i))
    else:
        d = {"+": [i, j]}
    return d

def _merge(data: any, defs: dict[str, any], path: str):
    """Handle merge (+) operator on data."""

    if not isinstance(data, dict) or "+" not in data:
        return data

    assert isinstance(data["+"], list)
    n_merge = len(data["+"])

    if n_merge == 0:
        # not "$NONE"?
        return {}
    elif n_merge == 1:
        return data["+"][0]
    # else: something to handle

    merged, is_xor = None, False
    for i, m in enumerate(data["+"]):
        lpath = f"{path}[{i}]"
        # resolve direct references
        while isinstance(m, str) and m.startswith("$"):
            name = m[1:]
            assert name in defs
            m = defs[name]
        if not isinstance(m, dict):
            raise ModelError(f"invalid type for + item: {type(m)} [{lpath}]")
        # distribute + over |
        if isinstance(m, dict) and  "|" in m:
            models = m["|"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type of |: {type(models)} [{lpath}]")
            tmerged = []
            if merged is None:
                merged = models
            else:
                for i in merged:
                    for j in models:
                        n = _merge_object(i, j)
                        n = _merge(n, defs, lpath)
                        tmerged.append(n)
                merged = tmerged
        elif isinstance(m, dict) and  "^" in m:
            models = m["^"]
            is_xor = True
            if not isinstance(models, list):
                raise ModelError(f"invalid type of ^: {type(models)} [{lpath}]")
            tmerged = []
            if merged is None:
                merged = models
            else:
                for i in merged:
                    for j in models:
                        n = _merge_object(i, j)
                        n = _merge(n, defs, lpath)
                        tmerged.append(n)
                merged = tmerged
        else:
            if merged is None:
                merged = [m]
            else:
                merged = [ _merge_object(i, m) for i in merged ]


    del data["+"]
    if merged:
        if len(merged) > 1:
            data["^" if is_xor else "|"] = merged
        else:
            item = merged[0]
            if isinstance(item, dict) and "+" in item and len(item) == 1:
                data["+"]  = item["+"]
            else:
                data["@"] = merged
    else:  # objet sans attribut
        pass
    return data

def _actual_merge(data, defs, path):
    assert "+" in data
    models = data["+"]
    del data["+"]
    assert isinstance(models, list)
    obj = merge_simple_models(models, defs, f"{path}.'+'")
    assert isinstance(obj, dict)
    if len(data) == 0:
        data = obj
    else:  # keep metadata
        data["@"] = obj
    return data

def _structurally_distinct_models(lm: list[ModelType], defs: dict[str, any], mpath: str) -> bool:
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
        if mt is str:
            if m.startswith("$"):  # unresolved reference
                log.debug("- unresolved $-reference")
                return False
            elif m.startswith("="):
                c, v = constant_value(m, defs)
                assert c
                m, mt = v, type(v)
            # else: empty or re or str constant
        if mt in (type(None), bool, int, float, list):
            if mt in types:
                log.debug(f"- multiple type {mt.__name__}")
                return False
            types.add(mt)
        elif mt is str:
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
                    log.warning(f"repeated constant: {m} [{mpath}]")
                    log.debug("- repeated constant strings")
                    return False
                strings.add(m)
        elif mt is dict:
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
            raise ModelError(f"unexpected model type ({mt.__name__}) [{mpath}]")
    return True

def _merge_rewrite(data, defs: dict[str, any], path: str):
    """Rewrite model to handle "+"."""

    if data is None:
        return data
    elif isinstance(data, (bool, int, float, str)):
        return data
    elif isinstance(data, list):
        return [_merge_rewrite(m, defs, f"{path}[{i}]") for i, m in enumerate(data)]
    else:
        assert isinstance(data, dict)
        if "%" in data:
            lpath = f"{path}.'%'"
            # FIXME only at root?
            ldefs = data["%"]
            if not isinstance(ldefs, dict):
                raise ModelError(f"invalid type for %: {type(ldefs)} [{lpath}]")
            for k, v in ldefs.items():
                ldefs[k] = _merge_rewrite(v, defs, f"{lpath}.{k}")
                # keep definitions to resolve references!
                # FIXME should warn on overwrite?
                defs[k] = ldefs[k]

        if "@" in data:
            data["@"] = _merge_rewrite(data["@"], defs, f"{path}.'@'")
            # NOTE no further recursion
            return data

        if "+" in data:
            lpath = f"{path}.'+'"
            models = data["+"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for +: {type(models)} [{lpath}]")

            data["+"] = _merge_rewrite(models, defs, lpath)

            # Distribution des opérateurs avec le + et |
            # Resolve defs
            data = _merge(data, defs, lpath)
            assert isinstance(data, dict)

            # catch merging
            if "|" in data:
                lpath += f"{path}.'|'"
                models = data["|"]
                assert isinstance(models, list)
                data["|"] = [_actual_merge(m, defs, f"{lpath}[{i}]") if "+" in m else m for i, m in enumerate(models)]
            elif "^" in data:
                lpath += f"{path}.'^'"
                models = data["^"]
                assert isinstance(models, list)
                data["^"] = [_actual_merge(m, defs, f"{lpath}[{i}]") if "+" in m else m for i, m in enumerate(models)]
            elif "+" in data:
                data = _actual_merge(data, defs, f"{path}.'+'")
            # else let it be

            # NOTE must have been merged!
            assert "+" not in data

            # NOTE may have been regenerated by the merge
            if "@" in data:
                return data

        if "^" in data:
            lpath = f"{path}.'^'"
            models = data["^"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for ^: {type(models)} [{lpath}]")

            models = _merge_rewrite(models, defs, lpath)

            # ignore $NONE in models list
            models = list(filter(lambda m: m != "$NONE", models))

            log.debug(f"^: {models}")

            # partial eval
            if len(models) == 0:
                return "$NONE"
            elif len(models) == 1:
                if "%" in data:
                    data["@"] = models[0]
                    del data["^"]
                    return data
                else:
                    return models[0]
            else:
                data["^"] = models

        if "|" in data:
            lpath = f"{path}.'|'"
            models = data["|"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for |: {type(models)} [{lpath}]")

            models = _merge_rewrite(models, defs, lpath)

            # remove duplicate model
            if len(models) >= 2:
                # detect duplicated (strictly equal) models
                newmodels = []
                for m in models:
                    if not model_in_models(m, newmodels) and m != "$NONE":
                        newmodels.append(m)
                models = newmodels

            # partial eval
            if len(models) == 0:
                return "$NONE"  # no model
            elif len(models) == 1:
                if "%" in data:
                    data["@"] = models[0]
                    del data["|"]
                    return data
                else:
                    return models[0]
            elif "$ANY" in models:
                return "$ANY"
            else:
                data["|"] = models

        if "&" in data:
            lpath = f"{path}.'&'"
            models = data["&"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for &: {type(models)} [{lpath}]")

            models = _merge_rewrite(models, defs, lpath)

            # remove duplicate model
            if len(models) >= 2:
                # detect duplicated (strictly equal) models
                newmodels = []
                for m in models:
                    if not model_in_models(m, newmodels) and m != "$ANY":
                        newmodels.append(m)
                models = newmodels

            # partial eval
            if len(models) == 0:
                return "$ANY"  # All models
            elif len(models) == 1:
                if "%" in data:
                    data["@"] = models[0]
                    del data["&"]
                    return data
                else:
                    return models[0]
            elif "$NONE" in models:
                return "$NONE"
            else:
                data["&"] = models

        if not is_constructed(data):

            # handle standard object
            for prop, model in data.items():
                if prop == "#":
                    continue
                # else recurse on model values
                data[prop] = _merge_rewrite(model, defs, f"{path}.{prop}")

        return data

def flatten(data, defs, path):
    """Simplistic flattening."""
    if data is None:
        return data
    elif isinstance(data, (bool, int, float, str)):
        return data
    elif isinstance(data, list):
        return [flatten(m, defs, f"{path}[{i}]") for i, m in enumerate(data)]
    elif isinstance(data, dict):

        # recursions
        if "%" in data:
            ldefs = data["%"]
            if not isinstance(ldefs, dict):
                raise ModelError(f"unexpected '%' value type: {type(ldefs)}")
            for prop, model in ldefs.items():
                log.debug(f"handling defs {prop}")
                ldefs[prop] = flatten(model, defs, f"{path}.{prop}")
                defs[prop] = ldefs[prop]
        if "$" in data:
            name = data["$"]
            if not isinstance(name, str) or len(name) == 0:
                raise ModelError(f"unexpected name {name} ({type(name)})")
            defs[name] = data
        if "@" in data:
            data["@"] = flatten(data["@"], defs, f"{path}.'@'")
            # ignore constraints
        else:
            for prop, val in data.items():
                if prop not in ("%", "$", "#", "@"):
                    data[prop] = flatten(val, defs, f"{path}.{prop}")

        # actual flattening for this level
        for op in ("|", "^", "&"):
            if op in data:
                models = data[op]
                flat = []
                if not isinstance(models, list):
                    raise ModelError(f"unexpected {op} value type: {type(models)} [{path}.'{op}']")
                for model in models:
                    m = model
                    # primitive resolution of names
                    resolved = set()
                    while isinstance(m, str) and len(m) >= 2 and m[0] == "$":
                        log.debug(f"resolving {m}")
                        name = m[1:]
                        if name not in defs:
                            log.debug(f"{name} not found")
                            break
                        if name in resolved:
                            log.debug(f"ignoring recursion on ${name}")
                            break
                        resolved.add(name)
                        m = defs[name]
                    # NOTE no handling of "@"
                    # actual flattening
                    if isinstance(m, dict) and op in m:
                        if not isinstance(m[op], list):
                            raise ModelError(f"unexpected {op} value type: {type(m[op])} [{path}.'{op}']")
                        flat += m[op]
                    else:  # NOTE we keep the initial definition!
                        flat.append(model)
                if op in ("|", "&"):
                    flat = _dedup_models(flat)
                data[op] = flat
        return data

    else:
        raise ModelError(f"unexpected type {type(data)} [{path}]")

def xor_to_or(data, defs: dict[str, Any], path: str = ""):
    """Change ^ to | if provably distinct."""
    if data is None:
        pass
    elif isinstance(data, (bool, int, float, str)):
        pass
    elif isinstance(data, list):
        data = [ xor_to_or(m, defs, f"{path}[{i}]") for i, m in enumerate(data) ]
    elif isinstance(data, dict):

        # definitions
        if "%" in data:
            defines = data["%"]
            assert isinstance(defines, dict)
            defines = { p: xor_to_or(m, defs, f"{path}.%.{p}") for p, m in defines.items() }
        if "+" in data:
            raise ModelError("+ must be preprocessed")
        # constraints
        if "@" in data:
            data["@"] = xor_to_or(data["@"], defs, f"{path}.@")
            # ignore other props…
        # combinators
        elif "|" in data:
            data["|"] = xor_to_or(data["|"], defs, f"{path}.|")
        elif "&" in data:
            data["&"] = xor_to_or(data["&"], defs, f"{path}.&")
        elif "^" in data:
            models = xor_to_or(data["^"], defs, f"{path}.^")
            if not isinstance(models, list):
                raise ModelError("^ expects an array")
            if _structurally_distinct_models(models, defs, path):
                del data["^"]
                data["|"] = models
            else:
                data["^"] = models
        else:  # object
            data2 = {}
            for p, m in data.items():
                if p in ("%", "$", "#"):
                    data2[p] = m
                else:
                    data2[p] = xor_to_or(m, defs, f"{path}.{p}")
            data = data2
    return data

def model_preprocessor(data, defs: dict[str, Any], path: str = ""):
    """Preprocessor entry point entry point.

    Remove all ``+`` (merge operator) from data:

    - flatten operators ``|``, ``^`` and ``&``.
    - distribute ``+`` over ``|`` and ``^``.
    - resolve definitions ``$something``.
    - actually merge object properties.
    - switch ``^`` to less costly ``|`` when possible.
    - optimize empty and one model lists on combinators.
    - some partial evaluation about $NONE and $ANY.
    """
    log.debug(f"defs={defs}")
    jdata = copy.deepcopy(data)
    # only later?
    fdata = flatten(jdata, defs, path)
    rdata = _merge_rewrite(fdata, defs, path)
    fdata = flatten(rdata, defs, path)
    odata = xor_to_or(fdata, defs, path)
    log.debug(f"odata={odata}")
    return rdata

def preprocessor():
    """Shell command entry point."""

    # handle script options and arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--debug", action="store_true")
    ap.add_argument("models", nargs="*")
    args = ap.parse_args()

    if args.debug:
        log.setLevel(logging.DEBUG)

    for fn, fh in openfiles(args.models):
        data = json.load(fh)
        print(json.dumps(model_preprocessor(data, {}, ""), indent=2))
