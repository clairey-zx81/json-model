# TODO sharing until transformed?

import copy
import re
import logging
import typing
from collections.abc import MutableMapping
import threading

from .types import ModelError, ModelPath, ModelTrafo, ModelRename, ModelDefs, ModelType, Jsonable
from .utils import log, tname
from .recurse import recModel, allFlt, builtFlt, noRwt
from .resolver import Resolver
from .optim import _structurally_distinct_models

# forward declaration
type JsonModel = typing.NewType("JsonModel", None)

# class?
type Symbols = dict[str, JsonModel]

class Symbols(MutableMapping):

    # keep track of allocated symbol tables
    lock = threading.RLock()
    SYMBOLS: list[Symbols] = []

    def __init__(self):

        with Symbols.lock:
            self._id = len(Symbols.SYMBOLS)
            Symbols.SYMBOLS.append(self)

        self._syms: dict[str, JsonModel] = {}

    def toJSON(self, rec: bool = False):
        data = {}
        data["#"] = f"symbol: {self._id}"
        # data[""] = self._url
        if rec:
            data.update(**{n: jm.toJSON(rec) for n, jm in self.items()})
        return data

    def __setitem__(self, k, v):
        return self._syms.__setitem__(k, v)

    def __getitem__(self, k):
        return self._syms.__getitem__(k)

    def __delitem__(self, k):
        return self._syms.__delitem__(k)

    def __len__(self):
        return self._syms.__len__()

    def __iter__(self):
        return self._syms.__iter__()

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
    MODELS: list[JsonModel] = []

    def __init__(self,
            model: ModelType,
            resolver: Resolver,
            scope: Symbols|None = None,
            url: str = "",
            root: bool = True,
            debug: bool = False,
        ):

        with JsonModel.lock:
            self._id = len(JsonModel.MODELS)
            JsonModel.MODELS.append(self)

        # unmodified parameters
        self._init_md = model
        self._resolver = resolver
        self._url = url
        self._root = root
        self._debug = debug

        # processing (is it useful?)
        self._self_renamed = False
        self._renamed = False
        self._rewritten = False
        self._preprocessed = False
        # validation?
        self._static_compiled = False
        self._dynamic_compiled = False

        # ???
        self._cache: dict[str, JsonModel] = {}

        # copy parameter which may be modified
        model = copy.deepcopy(model)

        # %: names and rewrites
        self._init_pc: dict[str, ModelType] = {}
        self._name: ModelRename = {}
        self._rewrite: ModelTrafo = {}

        if isinstance(model, dict) and "%" in model:
            lpath = ["%"]

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

        # definitions, possibly shared
        assert root and scope is None or not root and scope is not None
        self._init_dl: dict[str, ModelType] = {}
        self._defs = Symbols() if root else scope

        if isinstance(model, dict) and "$" in model:
            assert root  # $ only at root
            dollar = model["$"]
            assert isinstance(dollar, dict)
            # check that keys are str
            assert all(map(lambda k: isinstance(k, str), dollar.keys()))
            # extract current model identifier if provided
            if u := dollar.get(""):
                if not self._isUrlRef(f"${u}"):
                    raise ModelError(f"model identifier should be a url: {u}")
                if self._url != "" and u != self._url:
                    log.warning(f"inconsistent url identifier: {u}")
                self._url = u  # override
            # TODO restrict names?
            # extract actual definitions
            self._defs.update({
                n: JsonModel(m, resolver, self._defs, self._url + "#" + n, False, debug)
                    for n, m in dollar.items()
                        if isinstance(n, str) and n not in ("#", "")
            })
            # keep initial definitions
            self._init_dl = dollar
            del model["$"]

        if isinstance(model, dict) and "~" in model:
            version = model["~"]
            # FIXME should accept a *model*, not just a URL?
            if not isinstance(version, str):
                raise ModelError(f"invalid model version type: {tname(version)}")
            self._spec = self.get(version, ["~"])
            del model["~"]
        else:
            # FIXME add a default?
            self._spec = None

        if self._spec:
            log.info(f"renaming {self._id} from ~")
            model = self._spec.rename(model, [], True)

        self._model = model
        self.set(self._url, self)

        # TODO process references?
        self.rewrite()

        if root:
            self._global = Symbols()
            self.rootScope(self._global, "", set())
        else:
            self._global = None

        # TODO compute "+" and other preprocessing
        # TODO allow skipping?
        # self.merge()

    #
    # Analyses
    #
    def references(self) -> dict[str, set[str]]:
        """Get direct references."""

        def direcRefs(model: ModelType) -> set[str]:

            refs: set[str] = set()

            def dr_rwt(m: ModelType, p) -> bool:
                nonlocal refs
                if isinstance(m, str) and m and m[0] == "$":
                    refs.add(m)
                return m

            recModel(model, allFlt, dr_rwt, True)

            return refs

        contains = {}

        for name, model in self._defs.items():
            # FIXME model._url or name?
            contains["$" + name] = directRefs(model._model)
        contains[""] = directRefs(model._model)

        return contains

    def reachable(self):
        """Build reachable defs."""

        # should consider **all** loaded models!?
        contains = self.references()
        reached = copy.deepcopy(contains)

        # simplistic transitive closure computation
        changed = True
        while changed:
            changed = False
            for ref, refs in reached.items():
                for r in refs:
                    if r in reached and not reached[r].issubset(refs):
                        changed = True
                        refs.update(reached[r])

        return reached

    #
    # Optimizations
    #
    def xor_to_or(self):
        """Change xor to less coslty or if possible."""

        changed = False

        def x2o_rwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changed
            if isinstance(model, dict) and "^" in model:
                xor = model["^"]
                assert isinstance(xor, list) and "|" not in model
                # TODO handle distinct constants, eg "=1", "=2"…
                if _structurally_distinct_models(xor, self._defs, path + ["^"]):
                    changed = True
                    del model["^"]
                    model["|"] = xor
            return model

        self._model = recModel(self._model, builtFlt, x2o_rwt)

        return changed

    def flatten(self):
        """Flatten or, xor, and and merge operators."""

        changed = False

        def flatten_rwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changed
            for op in ("|", "&", "^", "+"):
                if isinstance(model, dict) and op in model:
                    models = model[op]
                    assert isinstance(models, list)
                    nmodels = []
                    # NOTE empty lists are handled in eval
                    if len(models) == 1:
                        changed = True
                        return models[0]
                    for m in models:
                        if isinstance(m, dict) and op in m:
                            changed = True
                            nmodels.extend(m[op])
                        else:
                            nmodels.append(m)
                    if changed:
                        model[op] = nmodels
            return model

        self._model = recModel(self._model, builtFlt, flatten_rwt)

        return changed

    # TODO inline defs
    def inline(self):

        return False

    def eval(self):
        """Model partial evaluation."""

        changed = False

        # helpers
        def empty_obj(o):
            return isinstance(o, dict) and (len(o) == 0 or len(o) == 1 and "#" in o)

        def real_equal(i, j) -> bool:  # avoid True == 1 and 0.0 == 0…
            return type(i) == type(j) and i == j

        def deduplicate(l):
            # return list(set(l))
            n = []
            for i in l:
                if not any(map(lambda x: real_equal(x, i), n)):
                    n.append(i)
            return n

        def eval_rwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changed
            if isinstance(model, dict):
                if "|" in model:
                    lor = model["|"]
                    if len(lor) == 0:
                        changed = True
                        return "$NONE"
                    elif "$ANY" in lor:
                        changed = True
                        return "$ANY"
                    elif len(l := deduplicate(lor)) != len(lor):
                        changed = True
                        model["|"] = lor = l
                    if len(lor) == 1:
                        changed = True
                        return lor[0]
                    # TODO remove duplicates
                elif "&" in model:
                    land = model["&"]
                    if len(land) == 0:
                        changed = True
                        return "$ANY"
                    elif "$NONE" in land:
                        changed = True
                        return "$NONE"
                    elif len(l := deduplicate(land)) != len(land):
                        changed = True
                        model["&"] = land = l
                    if len(land) == 1:
                        changed = True
                        return land[0]
                elif "^" in model:
                    lxor = model["^"]
                    if len(lxor) == 0:
                        changed = True
                        return "$NONE"
                    elif len(lxor) == 1:
                        changed = True
                        return lxor[0]
                    elif "$NONE" in lxor:
                        changed = True
                        model["^"] = list(filter(lambda m: m != "$NONE", lxor))
                    elif len(list(filter(lambda m: m == "$ANY", lxor))) >= 2:
                        changed = True
                        return "$NONE"
                    # TODO more cleanups
                    # ^(A A ...) = ^(...) ? not so, depends on inclusions?
                elif "+" in model:
                    lplus = model["+"]
                    if len(lplus) == 0:  # {"+": []} == {}
                        changed = True
                        del model["+"]
                    elif len(lplus) == 1:
                        changed = True
                        return lplus[0]
                    elif any(map(empty_obj, lplus)):
                        changed = True
                        model["+"] = list(filter(lambda o: not empty_obj(o), lplus))
            return model

        self._model = recModel(self._model, builtFlt, eval_rwt)

        return changed

    def optimize(self):
        self.inline()
        changed = True
        while changed:
            changed = False
            changed |= self.eval()
            changed |= self.flatten()
            changed |= self.xor_to_or()

    #
    # Display
    #
    def toJSON(self, recurse: bool = True) -> Jsonable:
        """Convenient JsonModel debug display."""
        data = {
            "id": self._id,
            "url": self._url,
            "model": self._model,
            "init": self._init_md,
            "rename": self._name,
            "rewrite": self._rewrite,
            "cached": sorted(self._cache.keys()),
        }
        if self.isUrlRef():
            data["external"] = self.get(self._model[1:], []).toJSON()
        if recurse:
            data["defs"] = {
                name: jm.toJSON(False) for name, jm in self._defs.items()
            }
        else:
            data["defs"] = self._defs._id
        if self._global:
            data["global"] = {
                name: f"Symbol {jm._id}" for name, jm in self._global.items()
            }
        return data

    # FIXME this is **not** very clean because $/% can appear inside defs
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model for display."""
        # log.debug(f"toModel on {self._model}")
        model = copy.deepcopy(self._model)
        if isinstance(model, dict):
            if "#" in model:
                del model["#"]
            model["#"] = f"JsonModel {self._id}"
        if self._defs:
            # log.info(f"defs: {self._defs}")
            defs = {
                n: jm.toModel() if isinstance(jm, JsonModel) else jm
                    for n, jm in self._defs.items()
            } if deep else self._init_dl
            if "" not in defs:
                defs[""] = self._url
            if isinstance(model, dict):
                assert "$" not in model
                model["$"] = defs
            elif self._debug:
                model = {
                    "#": f"Debug JsonModel {self._id}",
                    "$": defs,
                    "@": model,
                }
        return model

    #
    # Resolution
    #
    # @staticmethod?
    def _isPredef(self, s: str) -> bool:
        return s and s[0] == "$" and s[1:] in JsonModel.PREDEFS

    # @staticmethod?
    def _isRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and model and model[0] == "$" and not self._isPredef(model)

    # @staticmethod?
    def _isUrlRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and re.match(r"\$(file://|https?://|\.|/)", model)

    # @staticmethod?
    def _isSimpleRef(self, model: Jsonable) -> bool:
        return self._isRef(model) and not self._isUrlRef(model)

    def isRef(self) -> bool:
        return self._isRef(self._model)

    def isUrlRef(self) -> bool:
        return self._isUrlRef(self._model)

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
            if name == "":  # self!
                name, others = others.split("#", 1)
        else:
            others = None

        jm = self
        # log.debug(f"isRef on {jm._id}: {jm.isRef()} / {jm._model}")
        if jm.isRef():
            if self._debug:
                log.debug(f"{self._id}: following model ref {self._model}")
            path.append(self._model)
            jm = jm.resolveRef(self._model, path)

        log.debug(f"{jm._id}: name=\"{name}\" defs={list(jm._defs.keys())}")

        if name not in jm._defs:
            raise ModelError(f"{self._id}: cannot find definition for \"{name}\" ({path})")
            # log.info(f"{self._id}: creating empty definition \"{name}\"")
            # jm._defs[name] = JsonModel(None, self._resolver, jm._defs, jm._url + "#" + name, False, jm._debug)

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

        # shortcut for globals?!
        if self._global and self._isRef(model) and model in self._global:
            return self._global[model]

        # actual resolution
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

    #
    # Compute the root symbol table.
    # Move all references to the root scope.
    #
    def rootScope(self, symbols: Symbols, root: str, visited: set[tuple[str, int]]):
        """Move all local references to the root scope."""
        log.debug(f"scoping {self._defs._id}: {root}")

        assert root == "" or root[0] != "$"

        #  prevent recursion
        mid = ("m", self._id)
        if mid in visited:
            return
        visited.add(mid)

        root_ref = "$" + root
        symbols[root_ref] = self

        # handle models's symbol table if not done yet
        sid = ("s", self._defs._id)
        if sid not in visited:
            visited.add(sid)
            for name, jm in self._defs.items():
                jm.rootScope(symbols, root + "#" + name, visited)

        # substitute local references for global references
        def rootRwt(m: ModelType, p: ModelPath) -> ModelType:
            if self._isSimpleRef(m):
                ref = root_ref + "#" + m[1:]
                if ref not in symbols:
                    jm = self.resolveRef(m, p + [m])
                    symbols[ref] = jm
                    jm.rootScope(symbols, ref[1:], visited)
                return ref
            elif self._isUrlRef(m):
                if m not in symbols:
                    symbols[m] = self.resolveRef(m, p + [m])
                return m
            else:
                return m

        self._model = recModel(self._model, allFlt, rootRwt, True)

    #
    # URL Model Memoization
    #
    def set(self, url: str, jm: JsonModel):
        """Store JSON Model for URL in cache."""
        log.debug(f"{self._id}: setting {url}")
        if url in self._cache:
            raise ModelError(f"cannot override cached model for: {url}")
        self._cache[url] = jm

    def get(self, url: str, path: ModelPath) -> JsonModel:
        """Retrieve JSON Model for a URL."""
        log.debug(f"{self._id}: getting {url}")
        assert self._isUrlRef("$" + url)
        if url not in self._cache:
            j = self._resolver(url, path)
            jm = JsonModel(j, self._resolver, None, url, True, self._debug)
            self.set(url, jm)
        return self._cache[url]

    #
    # Merging
    #
    # - inline defs inside +
    # - distribute + over | and ^
    # - merge objects, removing all +
    #
    def mergeInlining(self):

        def mi_flt(model: ModelType, path: ModelPath) -> bool:

            updated = False

            def inline(m: model, p: path):
                nonlocal updated
                if isinstance(m, str):
                    updated = True
                    assert m and m[0] == "$"
                    # FIXME DOES NOT WORK! resolution scope is lost!
                    return copy.deepcopy(self.resolveRef(m, p)._model)
                else:
                    assert isinstance(m, dict)
                    return m

            if isinstance(model, dict) and "+" in model:
                model["+"] = [inline(n, path + ["+", i]) for i, n in enumerate(model["+"])]

            return True

        self._model = recModel(self._model, mi_flt, noRwt)

    def mergeDistribute(self):

        def distrib_flt(model: ModelType, path: ModelPath) -> ModelType:
            # +( |(A B) |(C D) ) -> |( +(A C) +(A D) +(B C) +(B D) )

            def has_orxor(m: ModelType) -> bool:
                if isinstance(m, str) and m and m[0] == "$":
                    m = self.resolveRef(m, path)._model
                return isinstance(m, dict) and ("|" in m or "^" in m)

            if isinstance(model, dict) and "+" in model:
                lplus = model["+"]
                if any(map(has_orxor, lplus)):
                    ...

            return model

        self._model = _recModel(self._model, distrib_flt, noRwt)

    def mergeObjects(self):
        ...

    def merge(self):
        self.mergeInlining()
        # self.mergeDistribute()
        # self.mergeObjects()

    #
    # Rename and Rewrite Transformations
    #
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
                    raise ModelError(f"cannot remove list from {tname(j)}")
            else:
                raise ModelError(f"expecting a remove list")
        if "*" in trafo:
            add = trafo["*"]
            if isinstance(add, list):
                if isinstance(j, list):
                    j.extend(add)
                else:
                    raise ModelError(f"cannot add list to {tname(j)} at {path}")
            elif isinstance(add, dict):
                if isinstance(j, dict):
                    for k, v in add.items():
                        if k in j:
                            raise ModelError(f"cannot overwrite property at {path}, remove first")
                        j[k] = v
                else:
                    raise ModelError(f"cannot add object to {tname(j)} at {path}")
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
    ap.add_argument("--optimize", "-O", action="store_true", help="optimize model")
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
    # TODO update maps using file path?
    jm = JsonModel(j, resolver, None, args.model, True, args.debug)
    if args.optimize:
        for m in JsonModel.MODELS:
            m.optimize()
    if args.debug:
        log.debug(json.dumps(jm.toJSON(), sort_keys=True, indent=2))
    show = [JsonModel.MODELS[0].toModel(True)] + \
            list(filter(lambda j: isinstance(j, dict),
                 [jm.toModel(True) for jm in JsonModel.MODELS[1:]]))
    print(json.dumps(show, sort_keys=True, indent=2))

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

# FIXME this imply not sharing, which is not desirable! use prefix with $$?
# possibly we want to distinguish different models
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
