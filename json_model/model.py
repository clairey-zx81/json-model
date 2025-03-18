# TODO sharing until transformed?

import copy
import re
import logging
import typing

from .utils import ModelError, Path, Jsonable, log
from .recurse import recModel
from .resolver import Resolver

type JsonModel = typing.NewType("JsonModel", None)
type Trafo = dict[str, Jsonable]


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

    PREDEFS: dict[str, Jsonable] = {
        "NONE": {"&": []},
        "ANY": {"|": []},
        "STRING": "",
        "BOOL": True,
        "BOOLEAN": True,
        "INT": -1,
        "INTEGER": -1,
        "FLOAT": -1.0,
        "NUMBER": {"|": [-1, -1.0]},
        "I32": -1,
        "I64": -1,
        "U32": 0,
        "U64": 0,
        "F32": -1.0,
        "F64": -1.0,
        "URL": r"/^\w+://.*/",
        "DATE": r"/^\d\d\d\d-\d\d?-\d\d?$/",  # FIXME
        # to be continued…
        "optBOOL": {"|": [None, "$BOOL"]},
        "optINT": {"|": [None, "$INT"]},
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
            debug: bool = False,
        ):

        # FIXME thread safety
        self._id = JsonModel.NMODELS
        JsonModel.NMODELS += 1

        self._init_md = model
        self._url = url
        self._debug = debug

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
        self._name: dict[str, str] = {}
        self._rewrite: Trafo = {}
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
            # TODO check name syntax? $Path#To#Def.path.to.prop
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
            # extract model identifier if provided
            if u := model.get(""):
                if not self._isUrlRef(f"${u}"):
                    raise ModelError(f"model identifier should be a url: {u}")
                if self._url != "" and u != self._url:
                    log.warning(f"inconsistent url identifier: {u}")
                self._url = u
            # TODO add model for current model?!
            # extract actual definitions
            # TODO restrict names?
            self._defs = {
                n: JsonModel(m, resolver, self._url + "#" + n, debug)
                    for n, m in model["$"].items()
                        if isinstance(n, str) and n not in ("#", "")
            }
            self._init_dl = model["$"]
            del model["$"]

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

    def get(self, url: str, path: Path) -> JsonModel:
        """Retrieve JSON Model for a URL."""
        log.debug(f"{self._id}: getting {url}")
        if url not in self._cache:
            j = self._resolver(url, path)
            jm = JsonModel(j, self._resolver, "", self._debug)
            self.set(url, jm)
        return self._cache[url]

    def toJSON(self) -> Jsonable:
        """Convenient JsonModel display."""
        data = {
            "id": self._id,
            "url": self._url,
            "model": self._model,
            "defs": {name: jm.toJSON() for name, jm in self._defs.items()},
            "rename": self._name,
            "rewrite": self._rewrite,
            "cached": sorted(self._cache.keys()),
        }
        if self.isUrlRef():
            data["external"] = self.get(self._model[1:], []).toJSON()
        return data

    # FIXME this is not very clean because $/% can appear inside defs
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model."""
        # log.info(f"toModel on {self._model}")
        model = copy.deepcopy(self._model)
        if self._defs:
            # log.info(f"defs: {self._defs}")
            assert isinstance(model, dict)
            assert "$" not in model
            model["$"] = {
                n: jm.toModel()
                    for n, jm in self._defs.items()
            } if deep else self._init_dl
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
    #     def expandRef(model: Jsonable, path: Path) -> Jsonable:
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

    def resolveDef(self, name: str, path: Path) -> JsonModel:
        """Resolve a definition in the current Model."""

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

        path.append(f"${name}")
        jm = jm._defs[name]

        if others:  # None or ""
            return jm.resolveRef(f"${others}", path)
        else:
            return jm

    def resolveRef(self, model: Jsonable, path: Path) -> JsonModel:
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
    #     def resRef(model: Jsonable, path: Path) -> Jsonable:
    #         if self._isUrlRef(model):
    #             return resolver(model[1:], path)
    #         else:
    #             return model
    #     self._model = recModel(self._model, lambda _m, _p: True, rwtRef)

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

    # FIXME parsing should conform to JSON Path
    # TODO think transformation path spec
    def _parsePath(self, tpath: str, path: Path) -> tuple[JsonModel, Path]:
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

    def _applyTrafo(self, j: Jsonable, trafo: Trafo, path: Path):
        # TODO handle $ANY
        if "~" in trafo:
            assert "-" not in trafo and "+" not in trafo, f"cannot mix ~ with + or - at {path}"
            return trafo["~"]
        if "-" in trafo:
            sub = trafo["-"]
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
        if "+" in trafo:
            add = trafo["+"]
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
    

    def _applyTrafoAtPath(self, jm: JsonModel, tpath: Path, trafo: Trafo, path: Path):
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
            lpath = ["$", "$", tpath]
            if tpath == "#":  # skip comment
                continue
            else:
                jm, path = self._parsePath(tpath, lpath)
                self._applyTrafoAtPath(jm, path, trafo, lpath)

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
    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

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
        # TODO update maps using file path
        jm = JsonModel(j, resolver, url, args.debug)
        print(json.dumps(jm.toJSON(), sort_keys=True, indent=2))
        # jm.resolveExtRef()
        # jm.expandRefs()
        print(json.dumps(jm.toModel(True), sort_keys=True, indent=2))
