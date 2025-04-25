from typing import Any, Mapping, MutableMapping
import re
import json
from .types import CheckFun, ModelType, UnknownModel, Compiler, JsonModel
from .utils import log


class Model:

    def __init__(self, check: CheckFun|None, model: ModelType|None, jsons: str|None, doc: str|None):
        self.check = check
        self.model = model
        self.jsons = jsons
        self.doc = doc

    def __repr__(self):
        return str(self.jsons)


class ReadOnlyDefs(Mapping[str, Model]):

    def __init__(self, md):
        self._md = md

    def __getitem__(self, key):
        model = self._md._models[key].model
        # FIXME what about "null" model?
        return model if model is not None else f"${key}"

    def __iter__(self):
        return self._md.__iter__()

    def __len__(self):
        return self._md.__len__()

    def __contains__(self, key):
        return key in self._md._models


# TODO remove compiler ?!
class ModelDefs(MutableMapping[str, Model]):
    """Hold current model definitions and possibly compiled versions."""

    def __init__(self, compiler: Compiler = lambda _m, _s: None):
        self._compiler = compiler
        self._models: dict[str, Model] = {}
        self.defs = ReadOnlyDefs(self)

    def set(self, name: str, model: ModelType|CheckFun, mpath: str = "", doc: str|None = None):
        """Add or override named JSON model."""
        # FIXME forbid? scope?
        log.debug(f"set {name} [{mpath}]")

        if name in self._models:
            log.warning(f"overriding definition for {name}")

        if callable(model):
            # direct function?!
            m = Model(model, f"${name}", None, doc)
        else:
            m = Model(self._compiler(model, mpath), model, json.dumps(model), doc)

        self._models[name] = m

    def get(self, name: str) -> CheckFun:
        """Get compiled or native checker function."""
        assert self._models[name].check is not None
        log.debug(f"returning check fun for {name}")
        return self._models[name].check  # type: ignore

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
        return self.delete(key)

    def __iter__(self):
        return self._models.__iter__()

    def __len__(self):
        return self._models.__len__()


_UTYPE = {
    "$NULL": None,
    "$BOOL": bool,
    "$I32": int, "$U32": int, "$I64": int, "$U64": int, "$INTEGER": int,
    "$F32": float, "$F64": float, "$NUMBER": float,
    "$STRING": str,
}

# model predef to standard model
_UMODEL = {
    "$BOOL": True, "$NULL": None,
    "$I32": -1, "$U32": 0, "$I64": -1, "$U64": 0, "$INTEGER": -1,
    "$F32": -1.0, "$F64": -1.0, "$NUMBER": -1.0,
    "$STRING": "",
    # stop recursion on some predefs
    "$URI": "$URI",
    "$REGEX": "$REGEX",
    "$DATE": "$DATE",
    "$UUID": "$UUID",
    # to be continued…
}


class Validator:

    def __init__(self, compiler: Compiler = lambda _m, _p: None):
        self._defs = ModelDefs(compiler)

    def _ultimate_type(self, jm: JsonModel, model: ModelType) -> type:
        """Get the utimate type by following definitions."""
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return tmodel
        elif tmodel is str:
            assert isinstance(model, str)  # useless pyright hint
            if model == "" or model[0] not in ("$", "="):
                return tmodel
            elif model[0] == "=":  # constants
                return (type(None) if model == "=null" else 
                        bool if model in ("=true", "=false") else
                        float if "." in model else
                        int)
            else:  # $... follow definition if possible
                if model in _UTYPE:
                    return _UTYPE[model]
                elif model in self._defs:
                    m = self._defs.model[model]
                    return self._ultimate_type(jm, m) if m != UnknownModel else m  # type: ignore
                else:
                    m = jm.resolveRef(model, ["<?>"])
                    return self._ultimate_type(m, m._model)
        elif tmodel is dict:
            assert isinstance(model, dict)
            if "@" in model:
                return self._ultimate_type(jm, model["@"])
            elif "|" in model:
                assert isinstance(model["|"], (list, tuple))
                types = set(self._ultimate_type(jm, i) for i in model["|"])
                if len(types) == 1:
                    return types.pop()
                else:
                    return UnknownModel
            else:
                return tmodel

    def _ultimate_model(self, jm: JsonModel, model: ModelType, constrained=True, strict=False) -> ModelType:
        """Look for the real model, beyond references."""
        # FIXME stop infinite recursion?!
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return model
        elif tmodel is str:
            assert isinstance(model, str)  # useless pyright hint
            if model == "" or model[0] not in ("$", "="):
                return model
            elif model[0] == "=":
                return model
            else:  # follow definition if possible
                assert model[0] == "$"
                name = model[1:]
                m = self._defs.model(name)
                # handle some predefs
                if isinstance(m, str) and m in _UMODEL:
                    return _UMODEL[m]
                # else try recursing
                return self._ultimate_model(jm, m) if m != UnknownModel else m  # type: ignore
        elif tmodel is dict:
            assert isinstance(model, dict)  # useless pyright hint
            if "@" in model:
                if strict:
                    if set(model.keys()).issubset(["@", "#", "%", "%"]):
                        return self._ultimate_model(jm, model["@"])
                    else:
                        return UnknownModel  # type: ignore
                else:
                    if constrained:
                        return self._ultimate_model(jm, model["@"])
                    else:
                        return UnknownModel  # type: ignore
            elif "|" in model:
                return UnknownModel  # type: ignore
            else:
                return model

    def _constant(self, jm: JsonModel, model: ModelType):
        """Tell an ultimate model value has a constant."""
        # FIXME should it detect @ eq?
        v = self. _ultimate_model(jm, model)
        if v == UnknownModel:
            # FIXME ?!
            return None
        tv = type(v)
        if tv is str:
            assert isinstance(v, str)  # useless pyright hint
            if v == "":
                return None
            elif v == "=null":
                return None
            elif re.search(r"^=(true|false)$", v) is not None:
                return True if v == "=true" else False
            elif re.search(r"^=-?\d+$", v) is not None:
                return int(v[1:])
            elif re.search(r"^=", v) is not None:
                return float(v[1:])
            elif v[0] == "_":
                return v[1:]
            else:
                return v
        else:
            return None

    def _disjunct_analyse(self, jm: JsonModel, model: ModelType, mpath: str) -> tuple[str, Any, list, list]|None:
        """Return the optimized check function if possible."""
        # FIXME if there is a ^, the preprocessor will have detected the discriminant
        # and turned it into a |.
        assert isinstance(model, dict) and "|" in model
        # first filter out
        utype = self._ultimate_type(jm, model)
        if utype is not dict:
            log.debug(f"ultimate type not a dict: {utype}")
            return None
        # get models
        models = [self._ultimate_model(jm, m) for m in model["|"]]
        # should not happen, just in case
        if len(models) < 2:
            log.debug("not enough models for a disjunction")
            return None
        # we may have some doubts yet (eg | in |)
        if any(filter(lambda m: not isinstance(m, dict), models)):
            log.debug("some models are not objects")
            return None
        # only objects: collect their direct mandatory properties
        all_props: list[set[str]] = [
            set(k for k in m.keys() if k and k[0] not in ("$", "?", "/"))
            for m in models if isinstance(m, dict)
        ]
        # get cleaned props and their constant values
        all_const_props: list[dict[str, Any]] = []
        for props, model in zip(all_props, models):
            consts: dict[str, Any] = {}
            assert isinstance(model, dict)
            for prop in props:
                val = self._constant(jm, model[prop])
                if val is not None:
                    key = prop[1:] if prop[0] in ("_", "!") else prop
                    consts[key] = val
            all_const_props.append(consts)
        # tag candidates must:
        # - appear in all alternate models
        candidates: set[str] = set(all_const_props[0].keys())
        for props in all_const_props[1:]:
            candidates.intersection_update(props.keys())
        if not candidates:
            log.debug("no property with constant values")
            return None
        # - have the same type
        candidates_typed: set[str] = set()
        for prop in candidates:
            if len(set(type(consts[prop]) for consts in all_const_props)) == 1:
                candidates_typed.add(prop)
        if not candidates_typed:
            log.debug("no proprety with same type constants")
            return None
        # - have distinct constant values
        candidates_distinct: set[str] = set()
        for prop in candidates_typed:
            if len(set(consts[prop] for consts in all_const_props)) == len(all_const_props):
                candidates_distinct.add(prop)
        if not candidates_distinct:
            log.debug("no property with distinct values")
            return None
        if len(candidates_distinct) > 1:
            log.warning(f"several disjunctive properties: {candidates_distinct}")
        # one tag with one type and only constants found!
        tag_name = candidates_distinct.pop()
        tag_type = self._ultimate_type(jm, all_const_props[0][tag_name])
        assert tag_type in (bool, int, float, str)

        return tag_name, tag_type, models, all_const_props
