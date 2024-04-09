# common model utilities
import sys
import enum
import json
import re
import copy
from typing import Callable  # why not callable?

import logging
log = logging.getLogger("utils")
# log.setLevel(logging.DEBUG)

class UnknownModel:
    pass

Object = dict[str, any]
ValueType = None|bool|int|float|str|list[any]|tuple[any]|Object
ModelType = ValueType|UnknownModel

# grrr… should be callable?
CheckFun = Callable[[any, str], bool]
KeyCheckFun = Callable[[str, any, str], bool|None]
Compiler = Callable[[ModelType], CheckFun|None]

class ModelError(BaseException):
    pass

#
# UTILITY FUNCTIONS
#

def is_regex(s: str) -> bool:
    if isinstance(s, str):
        try:
            re.compile(s)
            return True
        except Exception as e:
            # \c ControlLetter (ECMA 262 v13 - 22.2.1 p. 552)
            # \p{UnicodePropertyValueExpression} (same p. 553)
            good_anyway = re.search(r"\\[Pp]\{", s) or re.search(r"\\c[a-zA-Z]", s)
            if not good_anyway:
                log.warning(f"invalid /{s}/: {e}")
            return good_anyway
    else:
        return False

def distinct_values(val):
    try:
        if isinstance(val, (list, tuple, str)):
            return len(val) == len(set(val))
        else:
            return False
    except TypeError as e:
        # log.warning(f"ignoring error: {e}", exc_info=True)
        log.warning(f"ignoring error: {e}")
        # try slow iterative version which relies on ==
        seen = []
        for i in val:
            if i in seen:
                return False
            else:
                seen.append(i)
        return True

def one(l) -> bool:
    """Tell if only one from an iterable is True."""
    seen = False
    for b in l:
        if b:
            if seen:
                return False  # second
            seen = True   # first
    return seen

def model_eq(m1: ModelType, m2: ModelType) -> bool:
    """Recursively compare two models…"""
    # TODO resolve @ and $
    t1, t2 = type(m1), type(m2)
    if t1 != t2:
        return False
    elif t1 == type(None):
        return True
    elif t1 in (bool, int, float, str):
        return m1 == m2
    elif t1 == list:
        if len(m1) != len(m2):
            return False
        else:  # same size, recurse
            return all(model_eq(i1, i2) for i1, i2 in zip(m1, m2))
    elif t1 == dict:  # compare contents but # $ %
        # check m1 ⊂  m2
        for p in m1.keys():
            if p not in ("#", "%", "$"):
                if p not in m2:
                    return False
                if not model_eq(m1[p], m2[p]):
                    return False
        # check m2 ⊂  m1
        for p in m2.keys():
            if p not in ("#", "%", "$") and p not in m1:
                return False
        # m1 == m2
        return True
    else:
        raise ModelError(f"unexpected model element type ({t1.__name__})")

# TODO maybe we should accept some simple type inclusions
def same_model(m1: ModelType, m2: ModelType) -> bool:
    """Compare models…"""
    # beware that True == 1 and False == 0
    # return type(m1) == type(m2) and m1 == m2
    return model_eq(m1, m2)

def model_in_models(m: ModelType, l: list[ModelType]) -> bool:
    for i in l:
         if model_eq(i, m):
            return True
    return False

def split_object(model: dict[str, any], path: str) -> tuple[Object, Object, Object, Object, Object]:
    """Split properties in must/may/refs/regs/other cases."""

    if not isinstance(model, dict):
        raise ModelError(f"unexpected + model: {model} [{path}]")

    if "@" in model or "|" in model or "^" in model or "+" in model or "&" in model:
        raise ModelError(f"unexpected + model: {model} [{path}]")

    must, may, refs, regs, others = {}, {}, {}, {}, {"": model[""]} if "" in model else {}

    # put each property in the expected set
    for key, val in model.items():

        if not isinstance(key, str):
            raise ModelError(f"object proprety name must be a str: {type(key)} [{path}.{key}]")

        # some (late) sanity check
        if key in ("$", "%", "#", ""):
            if key == "%" and not isinstance(val, dict):
                raise ModelError(f"{key} value must be an object: {type(key)} [{path}.{key}]")
            if key == "#" and not isinstance(val, (str, dict)):
                raise ModelError(f"{key} value must be string or object: {type(key)} [{path}.{key}]")
            if key == "$" and not isinstance(val, str):
                raise ModelError(f"{key} value must be string: {type(key)} [{path}.{key}]")
            # ignore anyway
            continue

        c, name = key[0], key[1:]

        if c in ("_", "!", "?") and (name in must or name in may):
            raise ModelError(f"multiply defined property: {name} [{path}.{key}]")

        if c == "_" or c == "!":
            must[name] = val
        elif c == "?":
            may[name] = val
        elif c == "$":
            refs[name] = val
        elif c == "/":
            # FIXME /i support on keys
            assert key.endswith("/"), f"bad key: {key}"
            regs[name[:-1]] = val
        else:
            if key in must or key in may:
                raise ModelError(f"multiply defined property: {name} [{path}.{key}]")
            must[key] = val

    return must, may, refs, regs, others

def unsplit_object(must: Object, may: Object, refs: Object, regs: Object, others: Object) -> Object:
    """Regenerate an object from separated properties."""
    return {
        **{f"!{k}": v for k, v in must.items()},
        **{f"?{k}": v for k, v in may.items()},
        **{f"${k}": v for k, v in refs.items()},
        **{f"/{k}/": v for k, v in regs.items()},
        **others
    }


def is_constructed(model):
    """Tell whether model is constructed, i.e. uses some operator."""
    return isinstance(model, dict) and \
        ("|" in model or "&" in model or "^" in model or "+" in model or "@" in model)

# TODO add path?
def merge_simple_models(models: list[any], defs, path: str="") -> Object:
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

def actual_merge(data, defs, path):
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
                data["|"] = [actual_merge(m, defs, f"{lpath}[{i}]") if "+" in m else m for i, m in enumerate(models)]
            elif "^" in data:
                lpath += f"{path}.'^'"
                models = data["^"]
                assert isinstance(models, list)
                data["^"] = [actual_merge(m, defs, f"{lpath}[{i}]") if "+" in m else m for i, m in enumerate(models)]
            elif "+" in data:
                data = actual_merge(data, defs, f"{path}.'+'")
            # else let it be

        if "^" in data:
            lpath = f"{path}.'^'"
            models = data["^"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for ^: {type(models)} [{lpath}]")

            models = _merge_rewrite(models, defs, lpath)
            # ignore $NONE in models list
            models = list(filter(lambda m: m != "$NONE", models))

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
                # TODO possible optimization, turn ^ into | if distinct
                # { "^": [ 0, {} ] }  # structural
                # { "^": [ {"a": 0}, {"b": 0} ] }  # properties
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
                    while isinstance(m, str) and len(m) >= 2 and m[0] == "$":
                        log.debug(f"resolving {m}")
                        name = m[1:]
                        if name not in defs:
                            log.debug(f"{name} not found")
                            break
                        m = defs[name]
                    # NOTE no handling of "@"
                    # actual flattening
                    if isinstance(m, dict) and op in m:
                        if not isinstance(m[op], list):
                            raise ModelError(f"unexpected {op} value type: {type(m[op])} [{path}.'{op}']")
                        flat += m[op]
                    else:  # NOTE we keep the initial definition!
                        flat.append(model)
                data[op] = flat
        return data

    else:
        raise ModelError(f"unexpected type {type(data)} [{path}]")

def merge_rewrite(data, defs: dict[str, any], path: str=""):
    """Merge rewrite entry point.

    Remove all ``+`` (merge operator) from data:

    - flatten operators ``|``, ``^`` and ``&``.
    - distribute ``+`` over ``|``.
    - resolve definitions ``$something``.
    - actually merge object properties.

    TODO partial evaluation, propagation of $NONE and $ANY?
    """
    jdata = copy.deepcopy(data)
    jdata = flatten(jdata, defs, path)
    return _merge_rewrite(jdata, defs, path)

#
# DEFINITIONS
#

class Model:

    def __init__(self, check: CheckFun|None, model: ModelType|None, jsons: str|None, doc: str|None):
        self.check = check
        self.model = model
        self.jsons = jsons
        self.doc  = doc
        assert check is not None or model is not None

    def __repr__(self):
        return str(self.jsons)


class ModelDefs:
    """Hold current model definitions."""

    def __init__(self, compiler: Compiler=lambda _: None):
        self._compiler = compiler
        self._models: dict[str, Model] = {}

    def set(self, name: str, model: ModelType|CheckFun, mpath: str = "", doc: str=None):
        """Add or override named JSON model."""
        # FIXME forbid? scope?
        # log.debug(f"set {name} [{mpath}]")
        if name in self._models:
            log.warning(f"overriding definition for {name}")

        if callable(model):
            m = Model(model, None, None, doc)
        else:
            m = Model(self._compiler(model, mpath), model, json.dumps(model), doc)

        self._models[name] = m

    def get(self, name: str) -> CheckFun:
        """Get compiled or native checker function."""
        return self._models[name].check

    def model(self, name: str):
        """Return the JSON model of this name, if available."""
        return self._models[name].model if name in self._models else UnknownModel

    def delete(self, name):
        """Delete JSON model."""
        if name in self._models:
            del self._models[name]
            # self._known.remove(self._jsons[name])

    def __str__(self):
        return "models: " + " ".join(self._models.keys())

    def __repr__(self):
        return str(self)

    def __setitem__(self, key, val):
        self.set(key, val)

    def __contains__(self, key):
        return key in self._models

    def __getitem__(self, key):
        return self._models[key].check

    def __delitem__(self, key):
        self.delete(key)


class JsonType(enum.IntEnum):
    DATA = 0
    SCHEMA = 1
    MODEL = 2

_JSON_SCHEMA_METADATA = (
    "title", "description", "default", "examples", "deprecated", "readOnly",
    "writeOnly"
)

def _json_metrics(data, counts: dict[str, int], skip_metadata=False, json_type=JsonType.DATA):
    """Recursive internal computation of json data structure metrics."""
    tdata = type(data)
    if tdata == type(None):
        counts["null"] += 1
        return 0
    elif tdata == bool:
        counts["boolean"] += 1
        return 0
    elif tdata == int:
        counts["integer"] += 1
        return 0
    elif tdata == float:
        counts["number"] += 1
        return 0
    elif tdata == str:
        counts["string"] += 1
        counts["#length"] += len(data)
        return 0
    elif tdata in (list, tuple):
        counts["array"] += 1
        counts["#items"] += len(data)
        md = 0
        for m in data:
            md = max(md, _json_metrics(m, counts, skip_metadata, json_type))
        return 1 + md
    elif tdata == dict:
        counts["object"] += 1
        counts["#props"] += len(data)
        md = 0
        for k, v in data.items():
            assert isinstance(k, str)
            counts["string"] += 1
            counts["#length"] += len(k)
            if skip_metadata:
               if json_type == JsonType.MODEL and k == "#":
                   continue
               elif json_type == JsonType.SCHEMA and k in _JSON_SCHEMA_METADATA:
                   continue
               else:
                   pass
            md = max(md, _json_metrics(v, counts, skip_metadata, json_type))
        return 1 + md
    else:
        raise ModelError(f"unexpected data node type: {tdata}")

# normalized cost of JSON elements, for comparison purposes
_COSTS = {
    "null": 1,
    "boolean": 1,
    "integer": 4,
    "number": 8,
    "string": 10,
    "#length": 0,
    "array": 2,
    "#items": 1,
    "object": 2,
    "#props": 2,
}

def json_metrics_raw(data, skip_metadata=False, json_type=JsonType.DATA):
    """Compute metrics about a json data structure."""
    counts = {
        "null": 0,
        "boolean": 0,
        "integer": 0,
        "number": 0,
        "string": 0,
        "array": 0,
        "object": 0,
        "#items": 0,
        "#props": 0,
        "#length": 0,
    }
    counts["_depth"] = _json_metrics(data, counts, skip_metadata, json_type)
    counts["_length"] = len(json.dumps(data))
    return counts

def json_metrics(data, skip_metadata=False, json_type=JsonType.DATA) -> \
    tuple[int, int, int, int, int, dict[str, int]]:
    """Compute metrics about a json data structure."""
    counts = json_metrics_raw(data, skip_metadata, json_type)
    metrics = (
        counts["_depth"],
        counts["array"] + 2* counts["object"],
        counts["null"] + counts["boolean"] + counts["integer"] +  counts["number"] + counts["string"],
        sum(_COSTS[k] * counts[k] for k in _COSTS.keys() if k in counts),
        counts["_length"],
    )
    return metrics + (counts, )

def openfiles(args: list[str] = []):
    if not args:  # empty list is same as stdin
        args = ["-"]
    for fn in args:
        if fn == "-":
            yield fn, sys.stdin
        else:
            with open(fn) as fh:
                yield fn, fh
