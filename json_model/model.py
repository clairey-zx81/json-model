import copy
import re
import logging
import typing

from .utils import ModelError, Path, Jsonable, log
from .recurse import recModel
from .resolver import Resolver

JsonModel = typing.NewType("JsonModel", None)


class JsonModelCache:

    def __init__(self, resolver: Resolver):
        self._resolver = resolver
        self._cache: dict[str, JsonModel] = {}

    def set(self, url: str, jm: JsonModel):
        if url in self._cache:
            log.warning(f"overriding cached model for: {url}")
        self._cache[url] = jm

    def get(self, url: str, path: Path) -> JsonModel:
        if url not in self._cache:
            self.set(url, JsonModel(self._resolver(url, path), self._resolver))
        return self._cache[url]


class JsonModel:
    """JSON Model v2."""

    LIST_KW = ["|", "&", "^", "+"]
    ROOT_KW = ["$", "%"]
    SCAL_KW = ["@"]
    MISC_KW = ["!", "#", "<", "<=", ">", ">=", "=", "!="]
    TRAN_KW = ["+", "-", "~"]
    CONS_KW = MISC_KW + ["@"]
    KEYWORDS = LIST_KW + ROOT_KW + SCAL_KW + MISC_KW + TRAN_KW

    STR_SENTINELS = "_/$=."
    PROP_SENTINELS = "?!"
    SENTINELS = STR_SENTINELS + PROP_SENTINELS

    PREDEFS_MODELS: dict[str, Jsonable] = {
        "NONE": {"&": []},
        "ANY": {"|": []},
        "STRING": "",
        "BOOL": True,
        "INT": -1,
        "POS": 0,
        "FLOAT": -1.0,
        "NUMBER": {"|": [-1, -1.0]},
        "URL": r"/^\w+://.*/",
        "DATE": r"/^\d\d\d\d-\d\d?-\d\d?$/",  # FIXME
        # to be continued…
        "optBOOL": {"|": [None, "$BOOL"]},
        "optINT": {"|": [None, "$INT"]},
        "optPOS": {"|": [None, "$POS"]},
        "optFLOAT": {"|": [None, "$FLOAT"]},
        "optNUMBER": {"|": [None, "$NUMBER"]},
        "optSTRING": {"|": [None, "$STRING"]},
        "optURL": {"|": [None, "$URL"]},
        "optDATE": {"|": [None, "$DATE"]},
        # to be continued…
    }

    NMODELS = 0

    def __init__(self,
            model: Jsonable,
            resolver: Resolver,
            url: str = "",
        ):

        # FIXME thread safety
        self._id = JsonModel.NMODELS
        JsonModel.NMODELS += 1

        self._init_md = model
        self._url = url

        # NOTE **not** shared between models because it can be modified
        # However, if it is not, it could? optimization??
        # FIXME sharing semantics is not well defined yet!
        #
        # { "$": {
        #     "f": "$https://json-model.org/models/x",
        #     "g": "$https://json-model.org/models/x",
        #     "h": "$https://json-model.org/models/x#Foo",
        #     "i": "$https://json-model.org/models/x#Foo",
        # } }
        #
        # then f & g and h & i should be independent
        #
        self._jm_cache = JsonModelCache(resolver)

        # copy parameter which may be modified
        model = copy.deepcopy(model)

        # %: names and rewrites
        self._name: dict[str, str] = {}
        self._rewrite: dict[str, Jsonable] = {}
        self._init_pc: dict[str, Jsonable] = {}

        if isinstance(model, dict) and "%" in model:
            lpath = ["$", "%"]

            # checks
            if not isinstance(model["%"], dict):
                raise ModelError(f"expecting an object at {lpath}")
            bads = {
                name: kw
                    for name, kw in model["%"].items()
                        if (not isinstance(name, str) or name.startswith(".") and
                            isinstance(kw, str) and kw not in JsonModel.KEYWORDS)
            }
            if bads:
                raise ModelError(f"keyword renames must be json model keywords at {lpath}: {bads}")

            # keyword localization
            self._name = {
                name: kw
                    for name, kw in model["%"].items()
                        if isinstance(name, str) and name.startswith(".") and isinstance(kw, str)
            }

            # FIXME what is the scope of renamings, eg wrt references?
            model = self.rename(model, ["$"], True)

            # extract rewrites
            self._rewrite = {
                name: rw
                    for name, rw in model["%"].items()
                        if isinstance(name, str) and not name.startswith(".")
            }

            self._init_pc = model["%"]
            del model["%"]

        # definitions
        self._defs: dict[str, JsonModel] = {}
        self._init_dl: dict[str, Jsonable] = {}

        if isinstance(model, dict) and "$" in model:
            # extract actual definitions
            # TODO restrict names?
            self._defs = {
                n: JsonModel(m, resolver)
                    for n, m in model["$"].items()
                        if isinstance(n, str) and n not in ("#", "")
            }
            # extract model identifier if provided
            if u := model.get(""):
                if not self._isUrlRef(f"${u}"):
                    raise ModelError(f"model identifier should be a url: {u}")
                if self._url != "" and u != self._url:
                    log.warning(f"inconsistent url identifier: {u}")
                self._url = u
            self._init_dl = model["$"]
            del model["$"]

        self._model = model
        self._jm_cache.set(self._url, self)

        # TODO process references!
        # TODO apply rewrites!
        # TODO compute "+"

    def toJSON(self) -> Jsonable:
        """Convenient JsonModel display."""
        return {
            "id": self._id,
            "url": self._url,
            "model": self._model,
            "defs": {name: jm.toJSON() for name, jm in self._defs.items()},
            "rename": self._name,
            "rewrite": self._rewrite,
            "cached": list(self._jm_cache._cache.keys()),
        }

    # FIXME this is not very clean because $/% can appear inside defs
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model."""
        model = copy.deepcopy(self._model)
        if self._defs:
            assert isinstance(model, dict)
            assert "$" not in model
            model["$"] = {
                n: jm.toModel()
                    for n, jm in self._defs.items()
            } if deep else self._init_dl
        return model

    def _isRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and model and model[0] == "$"

    def _isUrlRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and re.match(r"\$(file://|https?://|\.|/)", model)

    def expandRefs(self):

        def expandRef(model: Jsonable, path: Path) -> Jsonable:
            if self._isRef(model):
                if self._isUrlRef(model):
                    return model
                elif model[1] == "#":
                    return self._url + model
                else:
                    return f"${self._url}#{model[1:]}"
            else:
                return model

        self._model = recModel(self._model, lambda _m, _p: True, expandRef)

    def resolveDef(self, name: str, path: Path) -> JsonModel:
        """Resolve $-definitions."""
        jm = self
        if "#" in name:
            name, others = name.split("#", 1)
        else:
            others = None
        if name not in jm._defs:
            raise ModelError(f"resolution error at {path}: {name}")
        jm = jm._defs[name]
        if others:  # None or ""
            return jm.resolveRef(f"${others}", path + ["$name"])
        else:
            return jm

    def resolveRef(self, model: Jsonable, path: Path) -> Jsonable:
        """Resolve $-references up to an actual model."""
        jm, initial, followed = self, model, []

        while jm._isRef(model):
            if jm._isUrlRef(model):
                if model in followed:
                    raise ModelError(f"cycle while resolving reference at {path}: {initial} ({followed})")
                followed.append(model)
                if "#" in model:
                    url, model = model[1:].split("#", 1)
                else:
                    url, model = model[1:], None  # will stop resolution loop
                jm = jm._jm_cache.get(url, path)
            else:
                jm = jm.resolveDef(model, path)
                model = jm._model

        return jm.toModel(False)
                

    # NOTE probably useless
    def resolveExtRef(self, resolver: Resolver):
        # FIXME keywords?
        """Resolve external references."""
        for jm in self._defs.values():
            jm.resolveExtRef(resolver)

        def resRef(model: Jsonable, path: Path) -> Jsonable:
            if self._isUrlRef(model):
                return resolver(model[1:], path)
            else:
                return model

        self._model = recModel(self._model, lambda _m, _p: True, rwtRef)

    def rename(self, model: Jsonable, path: Path = ["$"], root: bool = False):
        """Apply keyword renaming.

        NOTE we cannot simply use the recurse function because keywords
        are must be updated before proceeding.
        """
        # FIXME should check that all are ".…" are replaced?!
        if root and not self._name:
            return model
        if root and isinstance(model, dict):
            if "$" in model:
                defs = model["$"]
                model["$"] = {
                    n: self.rename(m, path + ["$", n])
                        for n, m in model["$"].items()
                            if n != "#"
                }
                if "#" in defs:
                    model["$"]["#"] = defs["#"]
            if "%" in model:
                # TODO
                ...
        else:  # not root sanity check
            if isinstance(model, dict) and ("$" in model or "%" in model):
                raise ModelError(f"'$' or '%' only at root, found at {path}")
        if model is None or isinstance(model, (bool, int, float, str)):
            return model
        elif isinstance(model, list):
            return [self.rename(m, path + [i]) for i, m in enumerate(model)]
        elif isinstance(model, dict):
            new: dict[str, Jsonable] = {}
            # rename
            for name, val in model.items():
                assert isinstance(name, str)
                repl = self._name[name] if name in self._name else name
                if repl in new:
                    raise ModelError(f"cannot rename {name} to {repl} at {path}")
                new[repl] = val
            assert len(new) == len(model)
            model, new = new, {}
            # recurse
            if "@" in model:
                allowed_kw = JsonModel.CONS_KW + JsonModel.ROOT_KW if root else []
                bads = [op for op in model.keys() if op not in allowed_kw]
                if bads:
                    raise ModelError(f"unexpected constraint keywords at {path}: {bads}")
                model["@"] = self.rename(val, path + ["@"])
            elif "|" in model or "&" in model or "^" in model or "+" in model:
                ops = [o for o in model.keys() if o not in ("#", "$", "%")]
                if len(ops) != 1:
                    raise ModelError(f"cannot mix list operators at {path}: {ops}")
                op, lpath = ops[0], path + ops
                if not isinstance(model[op], list):
                    raise ModelError(f"keyword {op} expects an array at {lpath}")
                model[op] = self.rename(model[op], lpath)
            else:  # simple Object
                for key, val in model.items():
                    lpath = path + [key]
                    k = self._name[key] if key in self._name else key
                    if k in new:
                        raise ModelError(f"rename collision at {lpath}: {k}")
                    new[k] = self.rename(val, lpath)
            return model
        else:  # pragma: no cover
            raise ModelError(f"unexpected model element while renaming: {type(model)}")


def test_script():

    logging.basicConfig()

    import json
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--debug", "-d", action="store_true", help="set debugging mode")
    ap.add_argument("--maps", "-m", action="append", default=[], help="URL mappings")
    ap.add_argument("urls", nargs="*", help="JSON Models to load")
    args = ap.parse_args()

    # debug
    if args.debug:
        log.setLevel(logging.DEBUG)

    # resolver
    maps: dict[str, str] = {}
    for m in args.maps:
        if " " not in m:
            raise Exception(f"invalid map: {m}")
        k, v = m.split(" ", 1)
        maps[k] = v
    resolver = Resolver(None, maps)

    for url in args.urls:
        print(f"# {url}")
        j = resolver(url, [])
        jm = JsonModel(j, resolver, url)
        print(json.dumps(jm.toJSON(), sort_keys=True, indent=2))
        # jm.resolveExtRef()
        jm.expandRefs()
        print(json.dumps(jm.toModel(True), sort_keys=True, indent=2))
