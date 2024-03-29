# common model utilities
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

# TODO maybe we should accept some simple type inclusions
def same_model(m1, m2) -> bool:
    """Compare models…"""
    # beware that True == 0
    return type(m1) == type(m2) and m1 == m2

def split_object(model: dict[str, any]) -> tuple[Object, Object, Object, Object, Object]:
    """Split properties in must/may/refs/regs/other cases."""

    if not isinstance(model, dict):
        raise ModelError(f"unexpected + model: {model}")

    if "@" in model or "|" in model or "^" in model or "+" in model or "&" in model:
        raise ModelError(f"unexpected + model: {model}")

    must, may, refs, regs, others = {}, {}, {}, {}, {"": model[""]} if "" in model else {}

    # put each property in the expected set
    for key, val in model.items():

        if not isinstance(key, str):
            raise ModelError(f"object proprety name must be a str: {type(key)}")

        # some (late) sanity check
        if key in ("$", "%", "#", ""):
            if key == "%" and not isinstance(val, dict):
                raise ModelError(f"{key} value must be an object: {type(key)}")
            if key == "#" and not isinstance(val, (str, dict)):
                raise ModelError(f"{key} value must be string or object: {type(key)}")
            if key == "$" and not isinstance(val, str):
                raise ModelError(f"{key} value must be string: {type(key)}")
            # ignore anyway
            continue

        c, name = key[0], key[1:]

        if c in ("_", "!", "?") and (name in must or name in may):
            raise ModelError(f"multiply defined property: {name}")

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
                raise ModelError(f"multiply defined property: {name}")
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

def _merge_object(i, j):
    if isinstance(i, dict) and "+" in i:
        d = copy.deepcopy(i)
        d["+"].append(copy.deepcopy(j))
    elif isinstance(j, dict) and "+" in j:
        d = copy.deepcopy(j)
        d["+"].append(copy.deepcopy(i))
    else:
        d = {"+": [i, j]}
    return d

def _merge(data, defs):

    if not isinstance(data, dict) or "+" not in data:
        return data

    assert isinstance(data["+"], list)
        
    merged = None
    for m in data["+"]:
        # resolve all references
        while isinstance(m, str) and m.startswith("$"):
            name = m[1:]
            assert name in defs
            m = defs[name]
        if not isinstance(m, dict):
            raise ModelError(f"invalid type for + item: {type(m)}")
        if isinstance(m, dict) and  "|" in m:
            models = m["|"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type of |: {type(models)}")
            tmerged = []
            if merged is None:
                merged = models
            else:
                for i in merged:
                    for j in models:
                        n = _merge_object(i, j)
                        n = _merge(n, defs)
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
            data["|"] = merged
        else:
            item = merged[0]
            if isinstance(item, dict) and "+" in item and len(item) == 1:
                data["+"]  = item["+"]
            else:
                data["@"] = merged
    else:
        pass
        # objet sans attribut
    return data

def merge_rewrite(data, defs: dict[str, any] = {}):
    """Rewrite model to handle "+"."""

    if data is None:
        return data
    elif isinstance(data, (bool, int, float, str)):
        return data
    elif isinstance(data, list):
        return [merge_rewrite(i, defs) for i in data]
    else:
        assert isinstance(data, dict)
        if "%" in data:
            ldefs = data["%"]
            if not isinstance(ldefs, dict):
                raise ModelError(f"invalid type for %: {type(ldefs)}")
            for k,v in ldefs.items():
                ldefs[k] = merge_rewrite(v, defs)
                # keep definitions to resolve references!
                defs[k] = ldefs[k]
        if "@" in data:
            data["@"] = merge_rewrite(data["@"], defs)
        if "|" in data:
            models = data["|"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for |: {type(models)}")
            data["|"] = merge_rewrite(models, defs)
        if "&" in data:
            models = data["&"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for &: {type(models)}")
            data["&"] = merge_rewrite(models, defs)
        if "^" in data:
            models = data["^"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for ^: {type(models)}")
            data["^"] = merge_rewrite(models, defs)
        if "+" in data:
            models = data["+"]
            if not isinstance(models, list):
                raise ModelError(f"invalid type for +: {type(models)}")
            data["+"] = merge_rewrite(models, defs)
            # Distribution des opérateurs avec le + et |
            # Resolve defs
            data = _merge(data, defs)
        return data

# TODO add path?
def merge_simple_models(models: list[any], defs) -> Object:
    """Merge a list of simple object models."""

    # sanity checks
    if not isinstance(models, (list, tuple)):
        raise ModelError(f"unexpected models to merge: {models} (type{models})")
    if len(models) == 0:
        # raise ModelError(f"empty models to merge")
        return "$NONE"

    # must follow references!
    dict_models = []
    for m in models:
        # log.debug(f"m 0: {m}")
        if isinstance(m, dict):
            if "+" in m:
                log.warning("+ in +")
                m = merge_simple_models(m["+"], defs)
            # log.debug(f"m 1: {m}")
            dict_models.append(m)
        elif isinstance(m, str) and len(m) >= 1 and m[0] == "$":  # reference
            log.warning("+ with references should be resolved before?")
            m2 = defs.model(m[1:])  # FIXME $x -> $y -> {} ?
            assert isinstance(m2, dict)
            # log.debug(f"m 2: {m2}")
            dict_models.append(m2)
        else:
            raise ModelError(f"unexpected model to merge: {m}")
    models = dict_models
    del dict_models

    if not all(map(lambda m: isinstance(m, dict), models)):
        raise ModelError(f"can only merge dicts")
    if any(map(is_constructed, models)):
        raise ModelError(f"can only merge simple objects")

    m0 = models[0]
    must, may, refs, regs, others = split_object(m0)

    for m in models[1:]:
        mu, ma, rf, rg, ot = split_object(m)
        # combine all properties
        # merge MUST
        for prop, mod in mu.items():
            if prop in must:
                if not same_model(mod, must[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: {m0} / {m}")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible must property {prop} while merging: {m0} / {m}")
                must[prop] = mod
                del may[prop]
            else:
                must[prop] = mod
        # merge MAY
        for prop, mod in ma.items():
            if prop in must:
                if not same_model(mod, must[prop]):  # ???
                    raise ModelError(f"incompatible may property {prop} while merging: {m0} / {m}")
                # else pass
            elif prop in may:
                if not same_model(mod, may[prop]):
                    raise ModelError(f"incompatible may property {prop} while merging: {m0} / {m}")
                # else pass
            else:
                may[prop] = mod
        # merge MAYBE
        for prop, mod in rf.items():
            # FIXME are the same $ available???
            if prop in refs:
                if not same_model(mod, refs[prop]):
                    raise ModelError(f"incompatible refs property {prop} while merging: {m0} / {m}")
                # else pass
            else:
                refs[prop] = mod
        for prop, mod in rg.items():
            # FIXME are the same $ available???
            if prop in regs:
                if not same_model(mod, regs[prop]):
                    raise ModelError(f"incompatible regs property {prop} while merging: {m0} / {m}")
                # else pass
            else:
                regs[prop] = mod
        # merge OTHERS
        if "" in ot:
            if "" in others:
                if not same_model(ot[""], others[""]):
                    raise ModelError(f"incompatible catchall while merging: {m0} / {m}")
                # else pass
            else:
                others = ot

    return unsplit_object(must, may, refs, regs, others)


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

    def set(self, name: str, model: ModelType|CheckFun, doc: str=None):
        """Add or override named JSON model."""
        if callable(model):
            m = Model(model, None, None, doc)
        else:
            # FIXME warn on redefinitions? forbid? scope?
            m = Model(self._compiler(model), model, json.dumps(model), doc)

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
            self._known.remove(self._jsons[name])

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

def json_metrics(data, skip_metadata=False, json_type=JsonType.DATA) -> \
    tuple[int, int, int, int, int, dict[str, int]]:
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
    depth = _json_metrics(data, counts, skip_metadata, json_type)
    metrics = (
        depth,
        counts["array"] + 2* counts["object"],
        counts["null"] + counts["boolean"] + counts["integer"] +  counts["number"] + counts["string"],
        sum(_COSTS[k] * counts[k] for k in _COSTS.keys()),
        len(json.dumps(data)),
    )
    return metrics + (counts, )

