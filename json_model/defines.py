import sys
import re
import json
from typing import Any
from .utils import log, CheckFun, ModelType, UnknownModel, Compiler

class Model:

    def __init__(self, check: CheckFun|None, model: ModelType|None, jsons: str|None, doc: str|None):
        self.check = check
        self.model = model
        self.jsons = jsons
        self.doc  = doc
        # FIXME too optimistic, None is a valid model!
        # assert check is not None or model is not None

    def __repr__(self):
        return str(self.jsons)

class ReadOnlyDefs:

    def __init__(self, md):
        self._md = md

    def __getitem__(self, key):
        model = self._md._models[key].model
        # FIXME what about "null" model?
        return model if model is not None else f"${key}"

    def __contains__(self, key):
        return key in self._md._models


class ModelDefs:
    """Hold current model definitions and possibly compiled versions."""

    def __init__(self, compiler: Compiler=lambda _: None):
        self._compiler = compiler
        self._models: dict[str, Model] = {}
        self.defs = ReadOnlyDefs(self)

    def set(self, name: str, model: ModelType|CheckFun, mpath: str = "", doc: str=None):
        """Add or override named JSON model."""
        # FIXME forbid? scope?
        # log.debug(f"set {name} [{mpath}]")
        if name in self._models:
            log.warning(f"overriding definition for {name}")

        if callable(model):
            # direct function
            m = Model(model, f"${name}", None, doc)
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

_UTYPE = {
    "$NULL": None,
    "$BOOL": bool,
    "$I32": int, "$U32": int, "$I64": int, "$U64": int,
    "$F32": float, "$F64": float,
    "$STRING": str,
}

_UMODEL = { 
    "BOOL": True, "NULL": None,
    "I32": -1, "U32": 0, "I64": -1, "U64": 0,
    "F32": -1.0, "F64": -1.0,
    "STRING": ""
}

class Validator:

    def __init__(self, compiler: Compiler = lambda _m, _p: None):
        self._defs = ModelDefs(compiler)

    def _ultimate_type(self, model: ModelType) -> Any:
        """Get the utimate type by following definitions."""
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return tmodel
        elif tmodel is str:
            if model == "" or model[0] != "$":
                return tmodel
            else:  # follow definition if possible
                if model in _UTYPE:
                    return _UTYPE[model]
                m = self._defs.model(model[1:])
                return self._ultimate_type(m) if m != UnknownModel else m
        elif tmodel is dict:
            if "@" in model:
                return self._ultimate_type(model["@"])
            elif "|" in model:
                assert isinstance(model["|"], (list, tuple))
                types = set(self._ultimate_type(i) for i in model["|"])
                if len(types) == 1:
                    return types.pop()
                else:
                    return UnknownModel
            else:
                return tmodel

    def _ultimate_model(self, model: ModelType, constrained=True, strict=False) -> ModelType:
        """Look for the real model, beyond references."""
        # FIXME stop infinite recursion?!
        tmodel = type(model)
        if tmodel in (type(None), bool, int, float, list, tuple):
            return model
        elif tmodel is str:
            if model == "" or model[0] not in ("$", "="):
                return model
            elif model[0] == "=":
                return model
            else:  # follow definition if possible
                m = self._defs.model(model[1:])
                # handle some predefs
                if isinstance(m, str) and m and m[0] == "$" and m[1:] in _UMODEL:
                    return _UMODEL[m[1:]]
                # else try recursing
                return self._ultimate_model(m) if m != UnknownModel else m
        elif tmodel is dict: 
            if "@" in model:
                if strict:
                    if set(model.keys()).issubset(["@", "#", "%", "%"]):
                        return self._ultimate_model(model["@"])
                    else:
                        return UnknownModel
                # else
                return self._ultimate_model(model["@"]) if constrained else UnknownModel
            elif "|" in model:
                return UnknownModel
            else:
                return model

    def _constant(self, model: ModelType):
        """Tell an ultimate model value has a constant."""
        # FIXME should it detect @ eq?
        v = self. _ultimate_model(model)
        if v == UnknownModel:
            return None
        tv = type(v)
        if tv == str:
            if v == "":
                return None
            elif v == "=null":
                return None
            elif re.search(r"^=(true|false)$", v):
                return True if v == "=true" else False
            elif re.search(r"^=-?\d+$", v):
                return int(v[1:])
            elif re.search(r"^=", v):
                return float(v[1:])
            elif v[0] == "_":
                return v[1:]
            else:
                return v
        else:
            return None
