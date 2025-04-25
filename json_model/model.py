import copy
import re
import sys
import logging
import typing
import json
from collections.abc import MutableMapping
import threading

from .types import ModelError, ModelPath, ModelTrafo, ModelRename, ModelDefs, ModelType, ModelFilter
from .types import Jsonable, JsonModel
from .utils import log, tname, is_cst
from .recurse import recModel, allFlt, builtFlt, noRwt
from .resolver import Resolver
from .dynamic import DynamicCompiler
from .static import static_compile

# FIXME misnomer
from .optim import _structurally_distinct_models, merge_objects

# forward declaration
type Symbols = dict[str, JsonModel]
type ModelRef = list[str]  # $stuff#name#inside

class Symbols(MutableMapping[str, JsonModel]):
    """JSON Model Symbol Table."""

    # TODO move to JsonModel instances
    # keep track of allocated symbol tables
    lock = threading.RLock()
    SYMBOLS: list[Symbols] = []

    def __init__(self):

        with Symbols.lock:
            self._id = len(Symbols.SYMBOLS)
            Symbols.SYMBOLS.append(self)

        self._syms: dict[str, JsonModel] = {}

    def toJSON(self, rec: bool = False):
        """Display as JSON."""
        if rec:
            data = {}
            data["#"] = f"Symbols {self._id}"
            data.update({n: jm.toJSON(rec) for n, jm in self.items()})
        else:
            data = f"Symbols {self._id}"
        return data

    def __str__(self):
        return str({n: m._id for n, m in self.items()})

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
        "NULL": None,
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
        # o = optional
        "oBOOL": {"|": [None, "$BOOL"]},
        "oINT": {"|": [None, "$INT"]},
        "oFLOAT": {"|": [None, "$FLOAT"]},
        "oNUMBER": {"|": [None, "$NUMBER"]},
        "oSTRING": {"|": [None, "$STRING"]},
        "oURL": {"|": [None, "$URL"]},
        "oDATE": {"|": [None, "$DATE"]},
        "oREGEX": {"|": [None, "$REGEX"]},
        # to be continued…
    }

    # TODO move to instances
    # store models
    lock = threading.RLock()
    MODELS: list[JsonModel] = []

    def __init__(self,
            model: ModelType,
            resolver: Resolver,
            globs: Symbols|None = None,
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
        self._isolated = globs is None
        self._globs = Symbols() if globs is None else globs
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

        # local to global references
        self._gmap: dict[str, str] = {}

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
                n: JsonModel(m, resolver, self._globs, self._defs, self._url + "#" + n, False, debug)
                    for n, m in dollar.items()
                        if isinstance(n, str) and n not in ("#", "")
            })
            # keep initial definitions
            self._init_dl = dollar
            del model["$"]

        if isinstance(model, dict) and "~" in model:
            version = model["~"]
            del model["~"]
            # FIXME should accept a *model*, not just a URL? or not?
            if not isinstance(version, str):
                raise ModelError(f"invalid model version type: {tname(version)}")
            log.debug(f"url={url} version={version}")
            # FIXME prevent all recursions!
            if version != self._url:  # prevent direct recursion
                self._spec = self.get(version, ["~"], True)
            else:
                self._spec = self
        else:
            # FIXME add a default?
            self._spec = None

        if self._spec:
            log.info(f"renaming {self._id} from ~")
            model = self._spec.rename(model, [], True)

        self._model = model
        self.set(self._url, self)

        self.rewrite()

        if globs is None:
            self.scope(self._globs, [""], set(), {})
            log.debug(f"globs = {self._globs}")

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

    def check(self, assertion: ModelFilter, what: str = "?", short: bool = False) -> bool:
        """Check an arbitrary local assertion on a model."""

        okay = True

        def checkFlt(model: ModelType, path: ModelPath) -> bool:
            nonlocal okay
            if not assertion(model, path):
                log.info(f"{self._id}: check {what} failed at {path}")
                okay = False
            return okay if short else True

        recModel(self._model, checkFlt, noRwt, True)

        return okay

    # FIXME must tell why it is unhappy!
    def valid(self, path: ModelPath = [], root: bool = True) -> bool:
        """Check JSON Model structural (and slightly more) validity."""

        is_valid = True

        def validFlt(model: ModelType, path: ModelPath) -> bool:
            nonlocal is_valid
            match model:
                case None:
                    pass
                case bool():
                    is_valid &= model == True
                case int():
                    is_valid &= model in (-1, 0, 1)
                case float():
                    is_valid &= model in (-1.0, 0.0, 1.0)
                case str():
                    if model == "":
                        pass
                    elif model[0] == "=":
                        is_valid &= re.match(r"=(true|false|null|-?\d+(\.\d+)?([eE]-?\d+)?)$", model) is not None
                    elif model[0] == "/":
                        is_valid &= model.endswith("/") or model.endswith("/i")
                        # TODO check re validity
                    else:  # TODO more checks
                        pass
                case list():
                    pass
                case dict():
                    if "#" in model:
                        is_valid &= isinstance(model["#"], str)
                    if "@" in model:
                        pass  # contraint keys in recurse
                    elif "|" in model:
                        is_valid &= isinstance(model["|"], list)
                        # no other keys in recurse
                    elif "^" in model:
                        is_valid &= isinstance(model["^"], list)
                        # no other keys in recurse
                    elif "&" in model:
                        is_valid &= isinstance(model["&"], list)
                        # no other keys in recurse
                    elif "+" in model:
                        is_valid &= isinstance(model["+"], list)
                        # no other keys in recurse
                    else:  # check object
                        props = set()
                        for p, m in model.items():
                            if p == "#":
                                continue
                            is_valid &= isinstance(p, str)
                            if p and p[0] not in ("$", "/"):
                                name = p[1:] if p[0] in ("?", "_", "!") else p
                                is_valid &= name not in props
                                props.add(name) 
                            # more checks on p if p[0] == "$"
                case _:
                    is_valid = False
            return True

        # check root-specific keywords
        if root and isinstance(self._model, dict):
            if "~" in self._model:
                is_valid &= isinstance(self._model["~"], str)  # and url
            if "$" in self._model:
                is_valid &= isinstance(defs := self._model["$"], dict)
                if is_valid:
                    for p, m in defs.items():
                        is_valid &= isinstance(p, str)
                        if p in ("", "#"):
                            is_valid &= isinstance(m, str)
                            # TODO "" expects an URL
                        else:  # recursion!
                            is_valid &= self.valid(m, ["$", p], False)
            if "%" in self._model:
                is_valid &= isinstance(trafo := self._model["%"], dict)
                if is_valid:
                    for p, t in trafo.items():
                        is_valid &= isinstance(p, str)
                        if p == "#":
                            is_valid &= isinstance(t, str)
                        else:
                            is_valid &= isinstance(t, dict)
                            # TODO more checks on t

        if is_valid:
            try:
                self.check(validFlt, "JSON Model Structural Validity")
            except AssertionError as e:
                log.error(e)
                is_valid = False
                if self._debug:
                    raise

        # TODO also check other instances?!

        return is_valid

    #
    # Optimizations
    #
    def xor_to_or(self):
        """Change xor to less coslty or if possible."""

        changes = 0

        def x2oRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changes
            if isinstance(model, dict) and "^" in model:
                xor = model["^"]
                assert isinstance(xor, list) and "|" not in model
                # TODO handle distinct constants, eg "=1", "=2"…
                if _structurally_distinct_models(xor, self._defs, path + ["^"]):
                    changes += 1
                    del model["^"]
                    model["|"] = xor
            return model

        self._model = recModel(self._model, builtFlt, x2oRwt)

        log.debug(f"{self._id}: x2o {changes}")

        return changes > 0

    def flatten(self):
        """Flatten or, xor, and and merge operators."""

        changes = 0

        def flatRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changes
            for op in ("|", "&", "^", "+"):
                if isinstance(model, dict) and op in model:
                    models, updated = model[op], False
                    assert isinstance(models, list)
                    nmodels = []
                    # NOTE empty lists are handled in eval
                    if len(models) == 1:
                        changes += 1
                        return models[0]
                    for m in models:
                        if isinstance(m, dict) and op in m:
                            changes += 1
                            updated = True
                            nmodels.extend(m[op])
                        else:
                            nmodels.append(m)
                    if updated:
                        model[op] = nmodels
            return model

        self._model = recModel(self._model, builtFlt, flatRwt)

        log.debug(f"{self._id}: flatten {changes}")

        return changes > 0

    def const_prop(self):
        """Propagate constants and predefs to their references."""

        changes = 0

        def cpRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changes
            if self._isRef(model):
                jm = self.resolveRef(model, path)
                if self._isPredef(jm._model):
                    changes += 1
                    return jm._model
                elif is_cst(jm._model):
                    changes += 1
                    return jm._model
            return model

        self._model = recModel(self._model, allFlt, cpRwt)

        log.debug(f"{self._id}: constant propagation {changes}")

        return changes > 0

    def eval(self):
        """Model partial evaluation."""

        changes = 0

        # helpers
        def empty_obj(o):
            return isinstance(o, dict) and (len(o) == 0 or len(o) == 1 and "#" in o)

        def real_equal(i, j) -> bool:  # avoid True == 1 and 0.0 == 0…
            return type(i) == type(j) and i == j

        def deduplicate(l):
            # return list(set(l))  # too easy: {True, 1} == {True}
            n = []
            for i in l:
                if not any(map(lambda x: real_equal(x, i), n)):
                    n.append(i)
            return n

        def evalRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal changes
            if isinstance(model, str) and self._isRef(model):
                jm = self.resolveRef(model, path)
                if isinstance(jm._model, str) and self._isPredef(jm._model):
                    changes += 1
                    return jm._model
            elif isinstance(model, dict):
                if "|" in model:
                    lor = model["|"]
                    if len(lor) == 0:
                        changes += 1
                        return "$NONE"
                    elif "$ANY" in lor:
                        changes += 1
                        return "$ANY"
                    elif len(l := deduplicate(lor)) != len(lor):
                        changes += 1
                        model["|"] = lor = l
                    if len(lor) == 1:
                        changes += 1
                        return lor[0]
                elif "&" in model:
                    land = model["&"]
                    if len(land) == 0:
                        changes += 1
                        return "$ANY"
                    elif "$NONE" in land:
                        changes += 1
                        return "$NONE"
                    elif len(l := deduplicate(land)) != len(land):
                        changes += 1
                        model["&"] = land = l
                    if len(land) == 1:
                        changes += 1
                        return land[0]
                elif "^" in model:
                    lxor = model["^"]
                    if len(lxor) == 0:
                        changes += 1
                        return "$NONE"
                    elif len(lxor) == 1:
                        changes += 1
                        return lxor[0]
                    elif "$NONE" in lxor:
                        changes += 1
                        model["^"] = list(filter(lambda m: m != "$NONE", lxor))
                    elif len(list(filter(lambda m: m == "$ANY", lxor))) >= 2:
                        changes += 1
                        return "$NONE"
                    # TODO more cleanups
                    # ^(A A ...) = ^(...) ? not so, depends on inclusions?
                elif "+" in model:
                    lplus = model["+"]
                    if len(lplus) == 0:  # {"+": []} == {}
                        changes += 1
                        del model["+"]
                    elif len(lplus) == 1:
                        changes += 1
                        return lplus[0]
                    elif any(map(empty_obj, lplus)):
                        changes += 1
                        model["+"] = list(filter(lambda o: not empty_obj(o), lplus))
                elif "@" in model:
                    # constraint without actual constraints
                    if not(set(model.keys()) - {"#", "~", "$", "%", "@"}):
                        return model["@"]
            return model

        self._model = recModel(self._model, allFlt, evalRwt)

        log.debug(f"{self._id}: eval {changes}")

        return changes > 0

    def optimize(self):
        # self.inline()
        changed = True
        while changed:
            changed = False
            changed |= self.const_prop()
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
            "gmap": self._gmap,
        }
        if self.isUrlRef():
            data["external"] = self.get(self._model[1:], []).toJSON()
        if recurse:
            data["defs"] = {
                name: jm.toJSON(False) for name, jm in self._defs.items()
            }
        else:
            data["defs"] = self._defs._id
        if self._isolated:
            log.debug(f"len(globals) = {len(self._globs)}")
            data["globals"] = {
                name: f"Symbol {jm._id}" for name, jm in self._globs.items()
            }
        return data

    # FIXME this is **not** very clean, should be a valid model?!
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model (more or less) for display."""
        model = copy.deepcopy(self._model)
        if isinstance(model, dict):
            if "#" in model:
                del model["#"]
            model["#"] = f"JsonModel {self._id}"
        if len(self._defs):
            defs = {
                n: jm.toModel() if isinstance(jm, JsonModel) else jm
                    for n, jm in self._defs.items()
            } if deep else self._init_dl
            if defs:
                if "" not in defs:
                    defs["#"] = f"Symbol {self._defs._id}"
                    defs[""] = self._url
                if isinstance(model, dict):
                    assert "$" not in model
                    model["$"] = defs
                else:
                    model = {
                        "#": f"JsonModel {self._id} with defs",
                        "$": defs if deep else f"Symbol {self._defs._id}",
                        "@": model,
                    }
        if self._spec and isinstance(model, dict):
            model["~"] = self._spec._url
        return model

    def toSchema(self, recurse: bool = True) -> Jsonable:
        from . import convert
        schema = convert.model2schema(self._model)
        if recurse and self._defs:
            if isinstance(schema, bool):  # we need an object to store defs
                schema = {} if schema else {"not": True}
                # possibly salvage comment
                if isinstance(self._model, dict) and "#" in self._model:
                    schema["description"] = self._model["#"]
            schema["$defs"] = {
                name: jm.toSchema(False)
                    for name, jm in self._defs.items()
            }
        return schema

    #
    # Resolution
    #
    # @staticmethod?
    def _isPredef(self, s: Jsonable) -> bool:
        return isinstance(s, str) and s and s[0] == "$" and s[1:] in JsonModel.PREDEFS

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

    def resolveDef(self, ref: str, path: ModelPath, create: bool = False) -> JsonModel:
        """Resolve a definition in the current Model.

        format: /\\$($URL#)?name/
        """

        if self._debug:
            log.debug(f"{self._id}: resolveDef {ref} at {path} (defs: {list(self._defs.keys())})")

        assert ref and ref[0] == "$"
        name = ref[1:]

        if "#" in name:
            name, others = name.split("#", 1)
            if name == "":  # self!
                name, others = others.split("#", 1)
        else:
            others = None

        log.debug(f"{self._id}: isRef for {ref}: {self.isRef()} / {self._model}")

        if name in self._defs:
            log.debug(f"{self._id}: {ref} / {self._model} / {self._defs[name]._id} / {self._defs[name]._model}")

        if name in self._defs:
            jm = self._defs[name]
            path.append(name)
        else:
            jm = self

        if jm.isRef():
            if self._debug:
                log.debug(f"{self._id}: following model ref {self._model}")
            if path:
                assert path[-1] != jm._model, f"path={path} ref={ref}"
            path.append(jm._model)
            jm = jm.resolveRef(self._model, path, create)

        log.debug(f"{jm._id}: name=\"{name}\" defs={list(jm._defs.keys())}")

        if name not in jm._defs:
            if not create:
                raise ModelError(f"{self._id}: cannot find definition for \"{name}\" ({path})")
            # creation is only allowed while rewriting
            log.info(f"{self._id}: creating empty definition \"{name}\"")
            jm._defs[name] = JsonModel(None, self._resolver, jm._globs, jm._defs, jm._url + "#" + name, False, jm._debug)

        path.append("$" + name)
        jm = jm._defs[name]

        if others:  # not None or ""
            return jm.resolveRef(f"${others}", path, create)
        else:
            return jm

    def resolveRef(self, model: Jsonable, path: ModelPath, create: bool = False) -> JsonModel:
        """Resolve references up to an actual model, maybe."""
        jm, initial, followed = self, model, []

        if self._debug:
            log.debug(f"{self._id}: resolveRef {model} at {path}")

        # shortcut
        if self._isRef(model) and model in self._gmap:
            log.debug(f"{self._id}: globs = {self._globs}")
            return self._globs[self._gmap[model]]

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
                jm = jm.resolveDef(model, path, create)
                model = jm._model

        return jm

    #
    # Build global symbol table
    # Build mapping of local references to global references: self._gmap
    #
    def scope(self, symbols: Symbols, root: ModelRef,
              visited: set[tuple[str, int]], references: dict[int, str]):
        """Move all local references to the root scope."""
        log.debug(f"scoping {self._id} at {root} ({visited}/{references})")

        # prevent infinite recursion
        mid = ("m", self._id)
        if mid in visited:
            return
        visited.add(mid)

        root_ref = "$" + "#".join(root)

        if root_ref not in symbols:
            symbols[root_ref] = self

        if self._id not in references:
            references[self._id] = root_ref

        # override URLs with their target
        if is_url := self.isUrlRef():
            jm = self.resolveRef(self._model, [])
            symbols[root_ref] = jm
            jm.scope(symbols, root, visited, references)

        # handle models's symbol table if not done yet
        sid = ("s", self._defs._id)
        if sid not in visited:
            visited.add(sid)
            for name, jm in self._defs.items():
                assert jm._id not in references
                gref = "$" + "#".join(root + [name])
                references[jm._id] = gref
                self._gmap["$" + name] = gref
                symbols[gref] = jm
            for name, jm in self._defs.items():
                jm.scope(symbols, root + [name], visited, references)

        # update map of local references to global references
        def rootRwt(m: ModelType, p: ModelPath) -> ModelType:
            if self._isSimpleRef(m):
                jm = self.resolveRef(m, p + [m])
                if jm._id in references:
                    ref = references[jm._id]
                else:
                    ref = root_ref + "#" + m[1:]
                    if ref not in symbols:
                        symbols[ref] = jm
                        jm.scope(symbols, root + [m[1:]], visited, references)
                    references[jm._id] = ref
                if m not in self._gmap:
                    self._gmap[m] = ref
                if ref not in self._gmap:  # also accept global references
                    self._gmap[ref] = ref
            elif self._isUrlRef(m):
                if m not in symbols:
                    symbols[m] = self.resolveRef(m, p + [m])
                if m not in self._gmap:
                    self._gmap[m] = m
            return m

        self._model = recModel(self._model, allFlt, rootRwt, True)

    #
    # URL Model Memoization (??)
    #
    def set(self, url: str, jm: JsonModel):
        """Store JSON Model for URL in cache."""
        log.debug(f"{self._id}: setting {url}")
        if url in self._cache:
            raise ModelError(f"cannot override cached model for: {url}")
        self._cache[url] = jm

    def get(self, url: str, path: ModelPath, isolated: bool = False) -> JsonModel:
        """Retrieve JSON Model for a URL."""
        log.debug(f"{self._id}: getting {url}")
        if self._debug and not self._isUrlRef("$" + url):
            log.debug(f"loading non explicit url: {url}")
        if url not in self._cache:
            j = self._resolver(url, path)
            jm = JsonModel(j, self._resolver, None if isolated else self._globs,
                           None, url, True, self._debug)
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

        updated = False

        def miFlt(model: ModelType, path: ModelPath) -> bool:

            def inline(m: model, p: path):
                nonlocal updated
                if isinstance(m, str):  # actual inlining
                    updated = True
                    assert m and m[0] == "$"
                    jm = self.resolveRef(m, p)
                    mo = copy.deepcopy(jm._model)
                    if self._defs._id != jm._defs._id:  # if not in same name space
                        # substitute local references
                        def subRefRwt(m, p):
                            return jm._gmap[m] if jm._isRef(m) else m
                        return recModel(mo, allFlt, subRefRwt)
                    else:  # keep as is
                        return mo
                else:
                    assert isinstance(m, dict)
                return m

            if isinstance(model, dict) and "+" in model:
                model["+"] = [inline(n, path + ["+", i]) for i, n in enumerate(model["+"])]

            return True

        self._model = recModel(self._model, miFlt, noRwt)

        return updated

    def mergeDistribute(self):

        updated = False

        def isAlt(m: ModelType) -> bool:
            return isinstance(m, dict) and ("|" in m or "^" in m)

        def mdFlt(model: ModelType, path: ModelPath) -> ModelType:
            # +( |(A B) C ) -> |( +(A C) +(B C) )
            nonlocal updated

            dive = builtFlt(model, path)

            if not isinstance(model, dict) or "+" not in model:  # no merge here
                return dive

            plus, is_xor = model["+"], False
            assert isinstance(plus, list), f"+ type: {tname(plus)}"

            if not any(map(isAlt, plus)):  # nothing to distribute
                return dive

            # actual distribution
            updated = True

            lmodels: list[list[ModelType]] = [[]]
            for m in plus:
                if isAlt(m):
                    alts = m["|"] if "|" in m else m["^"]
                    is_xor |= "^" in m
                    assert isinstance(alts, list)
                    lmodels = [
                        copy.deepcopy(l) + [n]
                            for l in lmodels
                                for n in alts
                    ]
                else:
                    for l in lmodels:
                        l.append(m)

            # substitute + by ^ or | in place
            model["^" if is_xor else "|"] = [{"+": l} for l in lmodels]
            del model["+"]

            return dive

        self._model = recModel(self._model, mdFlt, noRwt)

        return updated

    def mergeObjects(self):
        """Actually compute and remove operator "+"."""

        updated = False

        def moRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal updated
            if not isinstance(model, dict) or not "+" in model:
                return model
            updated = True
            merged = merge_objects(model["+"], path + ["+"])
            del model["+"]
            if len(model) > 0:
                model["@"] = merged
            else:
                model.update(merged)
            return model

        self._model = recModel(self._model, builtFlt, moRwt)

        return updated

    def merge(self):

        # NOTE after distribution, more inlining may be required
        # +( |( $A, {.1.} ), {.2.} ) -> |( +( $A, {.2.} ), +( {.1.}, {.2.} ) )
        updated = True
        while updated:
            self.mergeInlining()
            updated = self.mergeDistribute()

        if self._debug:  # check merge precondition

            def is_object(m: ModelType) -> bool:  # NOTE "+" is allowed
                return isinstance(m, dict) and not ("@" in m or "|" in m or "^" in m or "&" in m)

            def merge_on_objects(model: ModelType, path: ModelPath) -> bool:
                if isinstance(model, dict) and "+" in model:
                    assert isinstance(plus := model["+"], list)  # sanity
                    return all(map(is_object, plus))
                return True

            assert self.check(merge_on_objects, "only objects under +")

        self.mergeObjects()

        if self._debug:
            assert self.check(lambda m, _: not isinstance(m, dict) or "+" not in m)

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
        return (self.resolveRef(name, path, True), xpath)

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

def jmc_script():

    import argparse

    logging.basicConfig()

    ap = argparse.ArgumentParser()
    arg = ap.add_argument
    # verbosity and checks
    arg("--debug", "-d", action="store_true", help="set debugging mode")
    arg("--verbose", "-v", action="store_true", help="set verbose mode")
    arg("--quiet", "-q", dest="verbose", action="store_false", help="reduce verbosity")
    arg("--check", "-c", action="store_true", help="check model validity")
    # input options
    arg("--maps", "-m", action="append", default=[], help="URL mappings")
    # output options
    arg("--output", "-o", default=None, help="output file")
    arg("--sort", "-s", action="store_true", default=True, help="sorted JSON keys")
    arg("--no-sort", "-ns", dest="sort", action="store_false", help="unsorted JSON keys")
    arg("--indent", "-i", type=int, default=2, help="JSON indentation")
    arg("--code", action="store_true", help="show source code")
    # expected results on values
    arg("--none", "-n", dest="expect", action="store_const", const=None, default=None, help="no test expectations")
    arg("--true", "-t", dest="expect", action="store_const", const=True, help="test values for true")
    arg("--false", "-f", dest="expect", action="store_const", const=False, help="test values for false")
    # operations on model
    arg("--optimize", "-O", action="store_true", help="optimize model")
    arg("--no-optimize", "-nO", dest="optimize", action="store_false", help="do not optimize model")
    arg("--dump", "-U", dest="op", action="store_const", const="U", default="U", help="dump model")
    arg("--preproc", "-P", dest="op", action="store_const", const="P", help="preprocess model")
    arg("--static", "-S", dest="op", action="store_const", const="S", help="static compile model")
    arg("--dynamic", "-D", dest="op", action="store_const", const="D", help="dynamic compile model")
    arg("--validate", "-V", dest="op", action="store_const", const="V", help="direct validation")
    arg("--export", "-E", dest="op", action="store_const", const="E", help="export as JSON Schema")
    # parameters
    arg("model", help="JSON model")
    arg("values", nargs="*", help="JSON values to testing")
    args = ap.parse_args()

    # option/parameter consistency
    if args.values and args.op not in ("S", "D", "V"):
        log.error(f"Testing JSON values requires -S, -D or -V: {args.op}")
        sys.exit(1)
    if args.code and args.op not in ("D", "S"):
        log.error("Code only available for -D and -S: {args.op}")
        sys.exit(1)

    # debug
    log.setLevel(logging.DEBUG if args.debug else logging.INFO if args.verbose else logging.WARNING)

    # resolver
    maps: dict[str, str] = {}
    for m in args.maps:
        assert " " in m, f"valid map require a space: {m}"
        k, v = m.split(" ", 1)
        maps[k] = v
    resolver = Resolver(None, maps)

    log.info(f"processing {args.model}")
    try:
        # TODO update maps using file path? and declared url
        j = resolver(args.model, [])
        model = JsonModel(j, resolver, None, None, args.model, True, args.debug)
        assert model._isolated
    except BaseException as e:
        log.error(e)
        if args.debug:
            raise
        else:
            log.error(f"invalid model {args.model}")
            sys.exit(2)

    # initial sanity check
    if args.debug or args.check:
        for m in JsonModel.MODELS:
            # assert m.valid()
            if not m.valid():
                log.error(f"invalid initial model {args.model}[{m._id}]")
                sys.exit(3)

    # simplify before merging
    if args.optimize:
        for m in JsonModel.MODELS:
            m.optimize()

    # check after initial optimize
    if args.debug or args.check:
        log.debug(json.dumps(model.toJSON(), sort_keys=True, indent=2))
        for m in JsonModel.MODELS:
            if not m.valid():
                log.error(f"invalid optimized model {args.model}[{m._id}]")
                sys.exit(3)

    # merge in reverse order to move alts up before inlining?!
    for m in reversed(JsonModel.MODELS):
        m.merge()

    # optimize again?
    if args.optimize:
        for m in JsonModel.MODELS:
            m.optimize()

    # check after merge & optimize
    if args.debug or args.check:
        log.debug(json.dumps(model.toJSON(), sort_keys=True, indent=2))
        for m in JsonModel.MODELS:
            # assert m.valid()
            if not m.valid():
                log.error(f"invalid merged model {args.model}[{m._id}]")
                sys.exit(3)

    # TODO check overwrite?!
    output = file(args.output, "w") if args.output else sys.stdout
    checker = None

    # actual output
    if args.op == "U":  # test output
        show, symbols = [], set()
        for m in JsonModel.MODELS:
            j = m.toModel(m._defs._id not in symbols)
            symbols.add(m._defs._id)
            if isinstance(j, dict) or model._isolated:
                show.append(j)
        print(json.dumps(show, sort_keys=args.sort, indent=args.indent), file=output)
    elif args.op == "P":  # preprocessed model
        show = JsonModel.MODELS[0].toModel()
        print(json.dumps(show, sort_keys=args.sort, indent=args.indent), file=output)
    elif args.op == "D":
        checker = DynamicCompiler(m)
        if args.debug or args.code:
            import dis
            print(dis.dis(checker), file=output)
    elif args.op == "S":
        code = static_compile(m, "check_model")
        source_code = f"# generated from model: {args.model}\n" + str(code)
        if args.debug or args.code:
            print(source_code, file=output)
        env = {}
        exec(source_code, env)
        checker = env["check_model"]
    elif args.op == "E":
        try:
            schema = model.toSchema()
        except Exception as e:
            log.error(e, exc_info=args.debug)
            schema = {"ERROR": str(e)}
        print(json.dumps(schema, sort_keys=args.sort, indent=args.indent), file=output)
    else:
        raise Exception(f"operation not implemented yet: {args.op}")

    # values
    nerrors = 0
    for fn in args.values:
        assert checker
        with open(fn) as fh:
            value = json.load(fh)
            okay = checker(value)
            if args.expect is None or args.verbose:
                msg = f"{fn}: {okay}"
                if not okay and args.verbose and args.op == "D":
                    msg += " " + str(checker._reasons)
                print(msg, file=output)
            if args.expect is not None:
                if okay == args.expect:
                    log.info(f"check value {fn}: {okay}")
                elif okay != args.expect:
                    nerrors += 1
                    log.error(f"check value {fn}: {okay}")

    sys.exit(4 if nerrors > 0 else 0)
