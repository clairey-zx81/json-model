# TODO sharing until transformed?

import copy
import re
import logging
import typing
import threading

from .types import ModelError, ModelPath, ModelTrafo, ModelRename, ModelDefs, ModelType, Jsonable
from .utils import log
from .recurse import recModel
from .resolver import Resolver

# forward declaration
type JsonModel = typing.NewType("JsonModel", None)


class JsonModel:
    """JSON Model v2."""

    # keyword characters
    LIST_KW = ["|", "&", "^", "+"]
    ROOT_KW = ["$", "%", "~"]
    SCAL_KW = ["@"]
    CONS_KW = ["!", "#", "<", "<=", ">", ">=", "=", "!="]
    TRAN_KW = ["*", "/"]
    KEYWORDS = LIST_KW + ROOT_KW + SCAL_KW + CONS_KW + TRAN_KW

    # sentinel characters
    # $: reference
    # /: regular expression
    # _: escape character for string
    # =: scalar (not string) constants
    # .: keyword names
    STR_SENTINELS = "/$_=."
    PROP_SENTINELS = "?!"
    SENTINELS = STR_SENTINELS + PROP_SENTINELS

    PREDEFS: ModelDefs = {
        # specials
        "ANY": {"&": []},
        "NONE": {"|": []},
        # type inference
        "BOOL": True,
        "BOOLEAN": True,
        "INT": -1,
        "INTEGER": -1,
        "I32": -1,  # min/max?
        "I64": -1,  # min/max?
        "U32": 0,  # max?
        "U64": 0,  # max?
        "FLOAT": -1.0,
        "F32": -1.0,
        "F64": -1.0,
        "NUMBER": {"|": [-1, -1.0]},
        "STRING": "",
        "URL": r"/^\w+://.*/",  # relative URL?
        "DATE": r"/^\d\d\d\d-\d?\d-\d?\d$/",  # FIXME
        "REGEX": "",  # FIXME
        # to be continued…
        "optBOOL": {"|": [None, "$BOOL"]},
        "optINT": {"|": [None, "$INT"]},
        "optFLOAT": {"|": [None, "$FLOAT"]},
        "optNUMBER": {"|": [None, "$NUMBER"]},
        "optSTRING": {"|": [None, "$STRING"]},
        "optURL": {"|": [None, "$URL"]},
        "optDATE": {"|": [None, "$DATE"]},
        "optREGEX": {"|": [None, "$REGEX"]},
        # to be continued…
    }

    # store models
    lock = threading.RLock()
    MODELS: list[ModelType] = []

    def __init__(self,
            model: ModelType,
            resolver: Resolver,
            url: str = "",
            debug: bool = False,
        ):

        with JsonModel.lock:
            self._id = len(JsonModel.MODELS)
            JsonModel.MODELS.append(self)

        self._init_md = model
        self._url = url
        self._debug = debug

        # processing
        self._self_renamed = False
        self._renamed = False
        self._rewritten = False
        self._preprocessed = False
        # validation?
        self._static_compiled = False
        self._dynamic_compiled = False

        # NOTE **not** shared between models because it can be modified
        # However, if it is not, it could? optimization??
        #
        # WARN sharing semantics is not well defined yet!?
        #
        # { "$": {
        #     "f": "$https://json-model.org/models/x",
        #     "g": "$https://json-model.org/models/x",
        # } }
        #
        # then f & g should be independent, whereas
        #
        # { "$": {
        #     "f": "$https://json-model.org/models/x",
        #     "g": "$f"
        # } }
        #
        # then f & g are shared, so that if "$f#Foo" is changed, "$g#Foo" as well
        self._resolver = resolver
        self._cache: dict[str, JsonModel] = {}

        # copy parameter which may be modified
        model = copy.deepcopy(model)

        # %: names and rewrites
        self._init_pc: dict[str, ModelType] = {}
        self._name: ModelRename = {}
        self._rewrite: ModelTrafo = {}

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
            model = self.rename(model, [], True)
            self._self_renamed = True

            # extract rewrites
            # TODO check name syntax? $Path#To#Def.path.to.prop
            self._rewrite = {
                name: rw
                    for name, rw in model["%"].items()
                        if isinstance(name, str) and not name.startswith(".") and not name == "#"
            }

            # save initial definition
            self._init_pc = model["%"]
            del model["%"]

        # definitions
        self._defs: dict[str, JsonModel] = {}
        self._init_dl: dict[str, ModelType] = {}

        if isinstance(model, dict) and "$" in model:
            # check that keys are str
            assert all(map(lambda k: isinstance(k, str), model["$"].keys()))
            # extract current model identifier if provided
            if u := model.get(""):
                if not self._isUrlRef(f"${u}"):
                    raise ModelError(f"model identifier should be a url: {u}")
                if self._url != "" and u != self._url:
                    log.warning(f"inconsistent url identifier: {u}")
                self._url = u
            # extract actual definitions
            # TODO restrict names?
            self._defs = {
                n: JsonModel(m, resolver, self._url + "#" + n, debug)
                    for n, m in model["$"].items()
                        if isinstance(n, str) and n not in ("#", "")
            }
            # keep initial definitions
            self._init_dl = model["$"]
            del model["$"]

        if isinstance(model, dict) and "~" in model:
            version = model["~"]
            if not isinstance(version, str):
                raise ModelError(f"invalid model version type: {type(version).__name__}")
            self._spec = self.get(version, ["~"])
            del model["~"]
        else:
            # self._version = "https://json-model.org/json-model/latest"
            self._spec = None

        if self._spec:
            log.info(f"renaming {self._id} from ~")
            model = self._spec.rename(model, [], True)

        self._model = model
        self.set(self._url, self)

        # TODO process references?
        self.rewrite()
        # TODO compute "+" and other preprocessing

    def set(self, url: str, jm: JsonModel):
        """Store JSON Model for URL in cache."""
        log.debug(f"{self._id}: setting {url}")
        if url in self._cache:
            log.warning(f"overriding cached model for: {url}")
        self._cache[url] = jm

    def get(self, url: str, path: ModelPath) -> JsonModel:
        """Retrieve JSON Model for a URL."""
        log.debug(f"{self._id}: getting {url}")
        if url not in self._cache:
            j = self._resolver(url, path)
            jm = JsonModel(j, self._resolver, url, self._debug)
            self.set(url, jm)
        return self._cache[url]

    def toJSON(self) -> Jsonable:
        """Convenient JsonModel display."""
        data = {
            "id": self._id,
            "version": self._version,
            "url": self._url,
            "model": self._model,
            "init": self._init_md,
            "defs": {name: jm.toJSON() for name, jm in self._defs.items()},
            "rename": self._name,
            "rewrite": self._rewrite,
            "cached": sorted(self._cache.keys()),
        }
        if self.isUrlRef():
            data["external"] = self.get(self._model[1:], []).toJSON()
        return data

    # FIXME this is **not** very clean because $/% can appear inside defs
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model."""
        # log.debug(f"toModel on {self._model}")
        model = copy.deepcopy(self._model)
        if isinstance(model, dict):
            if "#" in model:
                del model["#"]
            model["#"] = f"JsonModel {self._id}"
        if self._defs:
            # log.info(f"defs: {self._defs}")
            assert isinstance(model, dict)
            assert "$" not in model
            defs = {
                n: jm.toModel()
                    for n, jm in self._defs.items()
            } if deep else self._init_dl
            if "" not in defs:
                defs[""] = self._url
            model["$"] = defs
        return model

    # @staticmethod?
    def _isPredef(self, s: str) -> bool:
        return s and s[0] == "$" and s[1:] in JsonModel.PREDEFS

    # @staticmethod?
    def _isRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and model and model[0] == "$" and not self._isPredef(model)

    # @staticmethod?
    def _isUrlRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and re.match(r"\$(file://|https?://|\.|/)", model)

    def isRef(self) -> bool:
        return self._isRef(self._model)

    def isUrlRef(self) -> bool:
        return self._isUrlRef(self._model)

    # FIXME this imply not sharing, which is not desirable! use prefix with $$?
    # NOTE do we want that?
    # def expandRefs(self):
    #     """Replace short references by absolute references."""
    #     def expandRef(model: Jsonable, path: ModelPath) -> Jsonable:
    #         if self._isRef(model):
    #             if self._isUrlRef(model):
    #                 return model
    #             elif model[1] == "#":
    #                 return self._url + model
    #             else:
    #                 return f"${self._url}#{model[1:]}"
    #         else:
    #             return model
    #     self._model = recModel(self._model, lambda _m, _p: True, expandRef)

    def resolveDef(self, name: str, path: ModelPath) -> JsonModel:
        """Resolve a definition in the current Model.

        format: /\\$($URL#)?name/
        """

        if self._debug:
            log.debug(f"{self._id}: resolveDef {name} at {path} (defs: {list(self._defs.keys())})")

        assert name and name[0] == "$"
        name = name[1:]

        if "#" in name:
            name, others = name.split("#", 1)
        else:
            others = None

        jm = self
        # log.debug(f"isRef on {jm._id}: {jm.isRef()} / {jm._model}")
        if jm.isRef():
            path.append(self._model)
            if self._debug:
                log.debug(f"{self._id}: following model ref {self._model}")
            jm = jm.resolveRef(self._model, path)

        log.debug(f"{jm._id}: name={name} defs={list(jm._defs.keys())}")

        if name not in jm._defs:
            log.info(f"{self._id}: creating empty definition {name}")
            jm._defs[name] = JsonModel(None, self._resolver, jm._url + "#" + name, jm._debug)

        path.append("$" + name)
        jm = jm._defs[name]

        if others:  # None or ""
            return jm.resolveRef(f"${others}", path)
        else:
            return jm

    def resolveRef(self, model: Jsonable, path: ModelPath) -> JsonModel:
        """Resolve references up to an actual model, maybe."""
        jm, initial, followed = self, model, []

        if self._debug:
            log.debug(f"{self._id}: resolveRef {model} at {path}")

        while jm._isRef(model):
            if jm._isUrlRef(model):
                if model in followed:
                    raise ModelError(f"cycle while resolving reference at {path}: {initial} ({followed})")
                followed.append(model)
                if "#" in model:
                    url, model = model[1:].split("#", 1)
                else:
                    url, model = model[1:], None  # will stop resolution loop
                jm = jm.get(url, path)
            else:
                jm = jm.resolveDef(model, path)
                model = jm._model

        return jm

    # NOTE probably useless
    # def resolveExtRef(self, resolver: Resolver):
    #     # FIXME keywords?
    #     """Resolve external references."""
    #     for jm in self._defs.values():
    #         jm.resolveExtRef(resolver)
    #     def resRef(model: Jsonable, path: ModelPath) -> Jsonable:
    #         if self._isUrlRef(model):
    #             return resolver(model[1:], path)
    #         else:
    #             return model
    #     self._model = recModel(self._model, lambda _m, _p: True, rwtRef)

    def rename(self, model: ModelType, path: ModelPath = [], root: bool = False):
        """Apply keyword renaming."""
        # FIXME should check that all are ".…" are replaced?!
        if root and not self._name:
            return model

        def flt(m: ModelType, path: ModelPath) -> bool:
            if isinstance(m, dict):
                remove, added = set(), {}
                for k, v in m.items():
                    assert isinstance(k, str)
                    if k in self._name:
                        added[self._name[k]] = v
                        remove.add(k)
                for k in remove:
                    del m[k]
                for k in added.keys():
                    if k in m:
                        raise ModelError(f"rename cannot overwrite existing {k}")
                m.update(**added)
            return True

        return recModel(model, flt, lambda m, _p: m)

    # FIXME parsing should conform to JSON Path
    # TODO think transformation path spec
    def _parsePath(self, tpath: str, path: ModelPath) -> tuple[JsonModel, ModelPath]:
        """Parse "$Foo.foo.0.bla" reference and simple json path."""
        if self._debug:
            log.debug(f"{self._id}: parsePath at {path}: {tpath}")
        assert tpath and tpath[0] == "$"
        if "." in tpath:
            name, jpath = tpath.split(".", 1)
            if jpath == "":
                raise ModelError(f"bad transformation path at {path}: {tpath}")
            xpath = [int(i) if re.match(r"\d+$", i) else i for i in jpath.split(".")]
        else:
            name, xpath = tpath, []
        return (self.resolveRef(name, path), xpath)

    def _isTrafo(self, trafo: ModelTrafo):
        return isinstance(trafo, dict) and set(trafo.keys()).issubset({"#", "/", "*"})

    def _applyTrafo(self, j: Jsonable, trafo: ModelTrafo, path: ModelPath):
        if not isinstance(trafo, dict) or not "/" in trafo and not "*" in trafo:
            # $ANY
            return trafo
        assert self._isTrafo(trafo)
        if "/" in trafo:
            sub = trafo["/"]
            if isinstance(sub, list):
                if isinstance(j, list):
                    for i in sub:
                        j.remove(i)
                elif isinstance(j, dict):
                    for i in sub:
                        if i not in j:
                            raise ModelError(f"cannot remove item {i} from object at {path}")
                        del j[i]
                else:
                    raise ModelError(f"cannot remove list from {type(j)}")
            else:
                raise ModelError(f"expecting a remove list")
        if "*" in trafo:
            add = trafo["*"]
            if isinstance(add, list):
                if isinstance(j, list):
                    j.extend(add)
                else:
                    raise ModelError(f"cannot add list to {type(j)} at {path}")
            elif isinstance(add, dict):
                if isinstance(j, dict):
                    for k, v in add.items():
                        if k in j:
                            raise ModelError(f"cannot overwrite property at {path}, remove first")
                        j[k] = v
                else:
                    raise ModelError(f"cannot add object to {type(j)} at {path}")
            else:
                raise ModelError(f"unexpected add type at {path}")
        return j

    def _applyTrafoAtPath(self, jm: JsonModel, tpath: ModelPath, trafo: ModelTrafo, path: ModelPath):
        """Apply a transformation into a JSON Model."""

        if self._debug:
            log.debug(f"{jm._id}: trafo at {path}: {tpath}")

        j = jm._model

        for i, p in enumerate(tpath):
            last = i == len(tpath) - 1
            if isinstance(p, str):
                if not isinstance(j, dict):
                    raise ModelError(f"invalid transformation path at {path}: {tpath}")
                if p not in j:
                    raise ModelError(f"cannot find at {path}: {p} in {tpath}")
            else:
                assert isinstance(p, int)
                if not isinstance(j, list):
                    raise ModelError(f"invalid transformation path at {path}: {tpath}")
                if not 0 <= p < len(j):
                    raise ModelError(f"invalid index at {path}: {p} in {tpath}")
            if last:
                j[p] = self._applyTrafo(j[p], trafo) 
            else:
                j = j[p]
        else:
            jm._model = self._applyTrafo(jm._model, trafo, path)

    def rewrite(self):
        """Apply model rewriting to current JSON Model."""

        # NOTE transformation specs may be empty
        for tpath, trafo in self._rewrite.items():
            lpath = ["$", "$", tpath]  # FIXME
            jm, path = self._parsePath(tpath, lpath)
            self._applyTrafoAtPath(jm, path, trafo, lpath)
        self._rewritten = True

def test_script():

    logging.basicConfig()

    import json
    import argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("--debug", "-d", action="store_true", help="set debugging mode")
    ap.add_argument("--maps", "-m", action="append", default=[], help="URL mappings")
    ap.add_argument("model", help="JSON models to load")
    ap.add_argument("files", nargs="*", help="JSON values to test")
    args = ap.parse_args()

    # debug
    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    # resolver
    maps: dict[str, str] = {}
    for m in args.maps:
        if " " not in m:
            raise Exception(f"invalid map: {m}")
        k, v = m.split(" ", 1)
        maps[k] = v
    resolver = Resolver(None, maps)

    log.info(f"processing {args.model}")
    j = resolver(args.model, [])
    # TODO update maps using file path
    jm = JsonModel(j, resolver, args.model, args.debug)
    if args.debug:
        log.debug(json.dumps(jm.toJSON(), sort_keys=True, indent=2))
    show = list(filter(lambda j: isinstance(j, dict), [jm.toModel(True) for jm in JsonModel.MODELS]))
    print(json.dumps(show, sort_keys=True, indent=2))
