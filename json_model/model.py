import copy
import re
import typing
from collections.abc import MutableMapping
import threading

from .mtypes import ModelPath, ModelTrafo, ModelRename, ModelDefs, ModelType, ModelFilter
from .mtypes import ModelError, Jsonable, JsonSchema, JsonObject
from .utils import log, tname, is_cst, _structurally_distinct_models, merge_objects
from .utils import WEAK_DATE_RE, CONST_RE, is_regex
from .recurse import recModel, allFlt, builtFlt, noRwt
from .resolver import Resolver

# FIXME
JsonModel = typing.NewType("JsonModel", None)  # pyright: ignore
# Symbols = typing.NewType("Symbols", None)  # pyright: ignore

type SymTable = dict[str, JsonModel]
type Globals = dict[str, str]
type ModelRef = list[str]  # $stuff#name#inside


class Symbols(MutableMapping[str, JsonModel]):
    """JSON Model Symbol Table."""

    # debug identification helper
    lock = threading.RLock()
    NSYMBOLS = 0

    def __init__(self):

        with Symbols.lock:
            self._id = Symbols.NSYMBOLS
            Symbols.NSYMBOLS += 1

        self._syms: SymTable = {}
        self._gmap: Globals = {}

    def toJSON(self, rec: bool = False):
        """Display as JSON."""
        if rec:
            data = {}
            data["#"] = f"Symbols {self._id}"
            data["~"] = self._gmap
            data.update({n: jm.toJSON(False) for n, jm in self.items()})
        else:
            data = f"Symbols {self._id}"
        return data

    def __str__(self):
        return str({n: m._id for n, m in self.items()})

    # local to global symbol
    def gset(self, ref: str, gref: str):
        self._gmap[ref] = gref

    def gget(self, ref: str):
        return self._gmap[ref]

    def ghas(self, ref: str):
        return ref in self._gmap

    # local to model
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
        "URL": r"/^\w+://.*/",  # FIXME relative URL?
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

    # OFFICIAL VERSION URLS
    VERSION_URLS = {
        "https://json-model.org/models/json-model",  # latest
        "https://json-model.org/models/json-model-v2",
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
                 debug: bool = False):

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

        # copy parameter which may be modified
        model = copy.deepcopy(model)

        # %: names and rewrites
        self._init_pc: dict[str, ModelType] = {}
        self._name: ModelRename = {}
        self._rewrite: dict[str, ModelTrafo] = {}

        if isinstance(model, dict) and "%" in model:

            lpath = ["%"]
            model_pc = model["%"]
            del model["%"]
            assert isinstance(model_pc, dict), "% expects an object"

            bads = {
                name: kw
                    for name, kw in model_pc.items()
                        if (not isinstance(name, str) or name.startswith(".") and
                            isinstance(kw, str) and kw not in JsonModel.KEYWORDS)
            }
            if bads:
                raise ModelError(f"keyword renames must be json model keywords at {lpath}: {bads}")

            # keyword localization
            self._name = {
                name: kw
                    for name, kw in model_pc.items()
                        if isinstance(name, str) and name.startswith(".") and isinstance(kw, str)
            }

            # FIXME what is the scope of renamings, eg wrt references?
            model = self.rename(model, [], True)
            assert isinstance(model, dict)
            self._self_renamed = True

            # extract rewrites
            # TODO check name syntax? $Path#To#Def.path.to.prop
            self._rewrite = {
                name: rw
                    for name, rw in model_pc.items()
                        if isinstance(name, str) and not name.startswith(".") and not name == "#"
            }

            # save initial definition
            self._init_pc = model_pc

        # definitions, possibly shared
        assert root and scope is None or not root and scope is not None
        self._init_dl: dict[str, ModelType] = {}
        self._defs: Symbols
        if root:
            self._defs = Symbols()
        else:
            assert scope is not None
            self._defs = scope

        if isinstance(model, dict) and "$" in model:
            assert root  # $ only at root
            dollar = model["$"]
            assert isinstance(dollar, dict), "$ expects an object"
            # check that keys are str
            assert all(map(lambda k: isinstance(k, str), dollar.keys())), "$ keys must be str"
            # extract current model identifier if provided
            if u := dollar.get(""):
                assert isinstance(u, str)
                if not self._isUrlRef(f"${u}"):
                    raise ModelError(f"model identifier should be a url: {u}")
                if self._url != "" and u != self._url:
                    log.info(f"inconsistent url identifier: {u}")
                self._url = u  # override
            # TODO restrict names?
            # extract actual definitions
            self._defs.update({
                n: JsonModel(m, resolver, self._globs, self._defs,
                             self._url + "#" + n, False, debug)
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

        # NOTE references are loaded as a side effect
        self.rewrite()

        if globs is None:
            self.scope(self._globs, [""], set(), {})
            log.debug(f"globs = {self._globs}")

    #
    # Analyses
    #
    def references(self) -> dict[str, set[str]]:
        """Get direct references."""

        def directRefs(model: ModelType) -> set[str]:

            refs: set[str] = set()

            def drRwt(m: ModelType, p: ModelPath) -> ModelType:
                if isinstance(m, str) and m != "" and m[0] == "$":
                    refs.add(m)
                return m

            recModel(model, allFlt, drRwt, True)

            return refs

        contains = {}

        for name, model in self._defs.items():
            # FIXME model._url or name?
            contains["$" + name] = directRefs(model._model)

        contains[""] = directRefs(self._model)

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

        def finiteRef(model: str) -> bool:
            ref, rec, jm = model, [], self
            while isinstance(ref, str) and self._isRef(ref) and ref not in rec:
                jm = jm.resolveRef(ref, path + rec)
                rec.append(ref)
                ref = jm._model
            finite = not self._isRef(ref)
            if not finite:
                log.debug(f"infinite recursion on {model}: {rec}")
            return finite

        def validFlt(model: ModelType, path: ModelPath) -> bool:
            nonlocal is_valid
            match model:
                case None:
                    pass
                case bool():
                    is_valid &= model
                case int():
                    is_valid &= model in (-1, 0, 1)
                case float():
                    is_valid &= model in (-1.0, 0.0, 1.0)
                case str():
                    if model == "":
                        pass
                    elif model[0] == "=":
                        is_valid &= re.match(CONST_RE, model) is not None
                    elif model[0] == "/":
                        try:
                            pattern, ropts = model[1:].rsplit("/", 1)
                            is_valid &= (ropts == "" or ropts.isalpha()) and is_regex(pattern)
                        except Exception:
                            is_valid = False
                    elif model[0] == "$":
                        pass
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
                    assert isinstance(defs, dict)  # redundant pyright hint
                    for p, m in defs.items():
                        is_valid &= isinstance(p, str)
                        if p in ("", "#"):
                            is_valid &= isinstance(m, str)
                            # TODO "" expects an URL
                        else:  # recursion!
                            jm = self._defs[p]
                            is_valid &= jm.valid(["$", p], False)
            if "%" in self._model:
                is_valid &= isinstance(trafo := self._model["%"], dict)
                if is_valid:
                    assert isinstance(trafo, dict)  # redundant pyright hint
                    for p, t in trafo.items():
                        is_valid &= isinstance(p, str)
                        if p == "#":
                            is_valid &= isinstance(t, str)
                        else:
                            is_valid &= isinstance(t, dict)
                            # TODO more checks on t

        if is_valid and self._defs:
            for name, jm in self._defs.items():
                is_valid &= finiteRef("$" + name)

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
                if _structurally_distinct_models(xor, self._defs, path + ["^"]):  # pyright: ignore
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
                            lm = m[op]
                            assert isinstance(lm, list)
                            nmodels.extend(lm)
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

        self._model = recModel(self._model, allFlt, cpRwt, True)

        log.debug(f"{self._id}: constant propagation {changes}")

        return changes > 0

    def eval(self):
        """Model partial evaluation."""

        changes = 0

        # helpers
        def empty_obj(o):
            return isinstance(o, dict) and (len(o) == 0 or len(o) == 1 and "#" in o)

        def real_equal(i, j) -> bool:  # avoid True == 1 and 0.0 == 0…
            return type(i) is type(j) and i == j

        def deduplicate(lv):
            # return list(set(l))  # too easy: {True, 1} == {True}
            n = []
            for i in lv:
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
                    assert isinstance(lor, list)
                    if len(lor) == 0:
                        changes += 1
                        return "$NONE"
                    elif "$ANY" in lor:
                        changes += 1
                        return "$ANY"
                    elif "$NONE" in lor:
                        changes += 1
                        model["|"] = lor = list(filter(lambda m: m != "$NONE", lor))
                    elif len(lv := deduplicate(lor)) != len(lor):
                        changes += 1
                        model["|"] = lor = lv
                    if len(lor) == 1:
                        changes += 1
                        return lor[0]
                elif "&" in model:
                    land = model["&"]
                    assert isinstance(land, list)
                    if len(land) == 0:
                        changes += 1
                        return "$ANY"
                    elif "$NONE" in land:
                        changes += 1
                        return "$NONE"
                    elif len(lv := deduplicate(land)) != len(land):
                        changes += 1
                        model["&"] = land = lv
                    if len(land) == 1:
                        changes += 1
                        return land[0]
                elif "^" in model:
                    lxor = model["^"]
                    assert isinstance(lxor, list)
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
                    plus = model["+"]
                    assert isinstance(plus, list)
                    if len(plus) == 0:  # {"+": []} == {}
                        changes += 1
                        del model["+"]
                    elif len(plus) == 1:
                        changes += 1
                        return plus[0]
                    elif any(map(empty_obj, plus)):
                        changes += 1
                        model["+"] = list(filter(lambda o: not empty_obj(o), plus))
                    # TODO more cleanup? could I remove $NONE? $ANY?
                elif "@" in model:
                    # "!": false is the default, so is not needed
                    if "!" in model and not model["!"]:
                        del model["!"]
                    # constraint without actual constraints
                    if not (set(model.keys()) - {"#", "~", "$", "%", "@"}):
                        if path == [] and "#" in model:
                            assert isinstance(model["#"], str)
                            if "JSON_MODEL_" in model["#"]:
                                return model
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
            "defs": self._defs.toJSON(recurse),
        }
        if isinstance(self._model, str) and self.isUrlRef():
            data["external"] = self.get(self._model[1:], []).toJSON()
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

    def toSchema(self, recurse: bool = True) -> JsonSchema:
        from . import convert
        schema: JsonSchema
        model = copy.deepcopy(self._model)

        # try to replace key references
        def keyFlt(model: ModelType, path: ModelPath) -> bool:
            if isinstance(model, dict):
                for key in list(model.keys()):
                    lpath = path + [key]
                    if self._isRef(key):
                        jm = self.resolveRef(key, lpath)
                        if isinstance(jm._model, str):
                            m = jm._model
                        else:  # give up, will fail later anyway
                            raise Exception(f"cannot replace {key} at {lpath}")
                    else:
                        m = key
                    match m:
                        case ""|"$STRING":
                            m = ""
                        case "$URL":
                            log.warning(f"approximating $URL key at {lpath}")
                            m = r"/[:/#]/"  # hmmm…
                        case "$REGEX":
                            log.warning(f"approximating $REGEX key at {lpath}")
                            m = ""
                        case "$DATE":
                            log.warning(f"approximating $DATE key at {lpath}")
                            m = "/" + WEAK_DATE_RE + "/"
                        case _:
                            if m[0] == "_":
                                m = "?" + m[1:]
                            elif m[0] not in ("/", "$"):
                                m = "?" + m
                    if m != key and (m == "" or m[0] == "/"):
                        assert m not in model, f"cannot overwrite key {m} at {lpath}"
                        model[m] = model[key]
                        del model[key]
            return isinstance(model, (list, dict))

        model = recModel(model, keyFlt, noRwt)

        # convert root model
        schema = convert.model2schema(model)

        # root specific, only when there are defs though
        if recurse and self._defs:
            # ensure that schema is an object
            if isinstance(schema, bool):  # we need an object to store defs
                schema = {} if schema else {"not": True}
                # possibly salvage root comment
                if isinstance(self._model, dict) and "#" in self._model:
                    schema["description"] = self._model["#"]
            # build root object, in order
            root: JsonObject = {}
            root["$comment"] = "JSON Schema generated by JSON Model Compiler"
            root["$schema"] = "https://json-schema.org/draft/2020-12/schema"
            # Hmmm… not really?!
            # if self._url:
            #     root["$id"] = self._url
            if "description" in schema:  # move description ahead
                root["description"] = schema["description"]
                del schema["description"]
            root["$defs"] = {  # type: ignore
                name: jm.toSchema(False)
                    for name, jm in self._defs.items()
            }
            root.update(schema)
            schema = root
        return schema  # type: ignore

    #
    # Resolution
    #
    # @staticmethod?
    def _isPredef(self, s: Jsonable) -> bool:
        return isinstance(s, str) and s != "" and s[0] == "$" and s[1:] in JsonModel.PREDEFS

    # @staticmethod?
    def _isRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and (
            model != "" and model[0] == "$" and not self._isPredef(model))

    # @staticmethod?
    def _isUrlRef(self, model: Jsonable) -> bool:
        return isinstance(model, str) and re.match(r"\$(file://|https?://|\.|/)", model) is not None

    # @staticmethod?
    def _isSimpleRef(self, model: Jsonable) -> bool:
        return self._isRef(model) and not self._isUrlRef(model)

    def isRef(self) -> bool:
        return self._isRef(self._model)

    def isUrlRef(self) -> bool:
        return self._isUrlRef(self._model)

    def resolveDef(self, ref: str, path: ModelPath, create: bool = False) -> JsonModel:
        """Resolve a definition in the current Model context.

        format: /\\$($URL#)*name/
        """

        if self._debug:
            log.debug(f"{self._id}: RD {ref} at {path} (defs: {list(self._defs.keys())})")

        assert ref and ref[0] == "$" and len(ref) > 1
        name = ref[1:]

        # extract first name, will have to recurse
        if "#" in name:
            name, others = name.split("#", 1)
            while name == "" and "#" in others:  # self!
                name, others = others.split("#", 1)
            if name == "" and others == "":
                return self
        else:
            others = None

        # name resolution
        if name in self._defs:
            log.debug(f"{self._id}: ref={ref} model={self._model} namedef={self._defs[name]._id}")
            jm = self._defs[name]
            if isinstance(jm._model, str) and jm.isRef():
                log.debug(f"{self._id}: following {ref} in {jm._model}")
                model = jm._model
                if others:
                    model += "#" + others
                return jm.resolveRef(model, path + [name, jm._model], create)
            else:
                return jm.resolveRef("$" + others, path + [name], create) if others else jm
        else:
            if not create:
                raise ModelError(f"{self._id}: cannot find definition for \"{name}\" ({path})")
            # creation only allowed while rewriting, as new defs may be added _after_ a reference
            log.info(f"{self._id}: creating empty definition \"{name}\"")
            self._defs[name] = JsonModel(None, self._resolver, self._globs, self._defs,
                                         self._url + "#" + name, False, self._debug)
            return self._defs[name]

    def resolveRef(self, model: Jsonable, path: ModelPath, create: bool = False) -> JsonModel:
        """Resolve references up to an actual model, maybe."""
        jm, initial, followed = self, model, []

        if self._debug:
            log.debug(f"{self._id}: RR {model} at {path}")

        # no jm for predefs
        assert not self._isPredef(model), f"no resolution for {model}"

        # shortcut with global scoping
        if isinstance(model, str) and self._isRef(model) and self._defs.ghas(model):
            if self._debug:
                log.debug(f"{self._id}: gmap shortcut {self._defs._gmap}")
                log.debug(f"{self._id}: globs = {self._globs}")
            return self._globs[self._defs.gget(model)]

        # actual resolution
        while jm._isRef(model):
            assert isinstance(model, str)  # pyright hint
            log.debug(f"{self._id}: RR {model} in {jm._id}")
            if jm._isUrlRef(model):
                # detect recursion
                if model in followed:
                    raise ModelError(f"cycle while resolving ref at {path}: {initial} ({followed})")
                # change scope
                followed.append(model)
                if "#" in model:
                    url, model = model[1:].split("#", 1)
                    model = "$" + model
                else:
                    url, model = model[1:], None  # will stop resolution loop
                jm = jm.get(url, path)
            else:
                jm = jm.resolveDef(model, path, create)
                # special case for "$#"
                if model == jm._model:
                    if model == "$#":
                        break
                    else:
                        raise ModelError(f"resolution cycle on {model}")
                model = jm._model
            log.debug(f"{self._id}: RR next {model} in {jm._id}")

        log.debug(f"{self._id}: RR resolved {initial} to {jm._id}")
        return jm

    #
    # Build global symbol table
    # Build mapping of local references to global references
    #
    def scope(self, symbols: Symbols, root: ModelRef,
              visited: set[tuple[str, int]], references: dict[int, str]):
        """Move all local references to the root scope."""
        log.debug(f"{self._id}: scoping {self._defs._id} at {root} ({visited} / {references})")
        log.debug(f" - symbols: {symbols}")

        # prevent infinite recursion
        mid = ("m", self._id)
        if mid in visited:
            return
        visited.add(mid)

        root_ref = "$" + "#".join(root)

        if root_ref not in symbols:
            symbols[root_ref] = self

        if root_ref == "$":  # also add "$#" for the root model
            if "$#" not in symbols:
                symbols["$#"] = self

        if self._id not in references:
            references[self._id] = root_ref

        # override URLs with their target
        if self.isUrlRef():
            jm = self.resolveRef(self._model, [])
            symbols[root_ref] = jm
            jm.scope(symbols, root, visited, references)

        # handle models's symbol table if not done yet
        sid = ("s", self._defs._id)
        if sid not in visited:
            visited.add(sid)
            # two phase ensure that maps are okay for resolveRef
            for name, jm in self._defs.items():
                if jm._id not in references:
                    gref = "$" + "#".join(root + [name])
                    references[jm._id] = gref
                    self._defs.gset("$" + name, gref)
                    # FIXME should also but "$#" + name?
                    # NOTE for $#, we put the root jm directly
                    # FIXME this kludge avoids bad recursions later…
                    if isinstance(jm._model, str) and jm._model == "$#":
                        symbols[gref] = self
                    else:
                        symbols[gref] = jm
            log.debug(f"{self._id}: gmap={self._defs._gmap}")
            for name, jm in self._defs.items():
                jm.scope(symbols, root + [name], visited, references)

        # update map of local references to global references
        def rootRwt(m: ModelType, p: ModelPath) -> ModelType:
            if isinstance(m, str):
                if self._isSimpleRef(m):
                    jm = self.resolveRef(m, p + [m])
                    if jm._id in references:
                        gref = references[jm._id]
                    else:
                        assert False
                        gref = root_ref + "#" + m[1:]
                        if gref not in symbols:
                            symbols[gref] = jm
                            jm.scope(symbols, root + [m[1:]], visited, references)
                        references[jm._id] = gref
                    log.debug(f"### {self._id}: m={m} jm={jm._id} gref={gref}")
                    if not self._defs.ghas(m):
                        log.debug(f"{self._id}: gmap {m} -> {gref} for {self._defs._id}")
                        self._defs.gset(m, gref)
                    # if not jm._defs.ghas(gref):  # also accept global references?
                    #     jm._defs.gset(gref, gref)
                elif self._isUrlRef(m):
                    if m not in symbols:
                        symbols[m] = self.resolveRef(m, p + [m])
                    if not self._defs.ghas(m):
                        self._defs.gset(m, m)
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

            def inline(m: ModelType, p: ModelPath):
                nonlocal updated
                if isinstance(m, str):  # actual inlining
                    assert m and m[0] == "$"
                    if self._isPredef(m):
                        return m
                    updated = True
                    jm = self.resolveRef(m, p)
                    mo = copy.deepcopy(jm._model)
                    if self._defs._id != jm._defs._id:  # if not in same name space
                        # substitute local references
                        def subRefRwt(m, p):
                            return jm._defs.gget(m) if jm._isRef(m) else m
                        return recModel(mo, allFlt, subRefRwt)
                    else:  # keep as is
                        return mo
                else:
                    assert isinstance(m, dict)
                return m

            if isinstance(model, dict) and "+" in model:
                plus = model["+"]
                assert isinstance(plus, list)  # pyright hint
                model["+"] = [inline(n, path + ["+", i]) for i, n in enumerate(plus)]

            return True

        self._model = recModel(self._model, miFlt, noRwt)

        return updated

    def mergeDistribute(self):

        updated = False

        def isAlt(m: ModelType) -> bool:
            return isinstance(m, dict) and ("|" in m or "^" in m)

        def mdFlt(model: ModelType, path: ModelPath) -> bool:
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
                assert isinstance(m, dict)  # pyright hint
                if isAlt(m):
                    alts = m["|"] if "|" in m else m["^"]
                    is_xor |= "^" in m
                    assert isinstance(alts, list)
                    lmodels = [
                        copy.deepcopy(lm) + [n]
                            for lm in lmodels
                                for n in alts
                    ]
                else:
                    for lm in lmodels:
                        lm.append(m)

            # substitute + by ^ or | in place
            model["^" if is_xor else "|"] = [{"+": lo} for lo in lmodels]
            del model["+"]

            return dive

        self._model = recModel(self._model, mdFlt, noRwt)

        return updated

    def mergeObjects(self):
        """Actually compute and remove operator "+"."""

        updated = False

        def moRwt(model: ModelType, path: ModelPath) -> ModelType:
            nonlocal updated
            if not isinstance(model, dict) or "+" not in model:
                return model
            updated = True
            plus = model["+"]
            assert isinstance(plus, list)  # pyright hint
            merged = merge_objects(plus, path + ["+"])  # pyright: ignore
            del model["+"]
            if len(model) > 0:
                model["@"] = merged
            else:
                assert isinstance(merged, dict)  # pyright hint
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
    def rename(self, model: ModelType, path: ModelPath = [], root: bool = False) -> ModelType:
        """Apply keyword renaming."""
        # FIXME should check that all are ".…" are replaced?!
        if root and not self._name:
            return model

        def rnFlt(m: ModelType, path: ModelPath) -> bool:
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

        return recModel(model, rnFlt, noRwt)

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
        log.debug(f"name={name} xpath={xpath}")
        return (self.resolveRef(name, path, True), xpath)

    def _isTrafo(self, trafo: ModelTrafo):
        return isinstance(trafo, dict) and set(trafo.keys()).issubset({"#", "/", "*"})

    def _applyTrafo(self, j: Jsonable, trafo: ModelTrafo, path: ModelPath):
        """Apply this transformation on j."""
        if not isinstance(trafo, dict) or "/" not in trafo and "*" not in trafo:
            return trafo
        assert self._isTrafo(trafo)
        assert isinstance(trafo, dict)  # pyright hint
        if self._debug:
            log.debug(f"trafo={trafo} on j={j}")
        if "/" in trafo:
            sub = trafo["/"]
            # handle scalars
            if sub is None or isinstance(sub, (bool, int, float, str)):
                sub = [sub]
            if isinstance(sub, list):
                if isinstance(j, list):
                    for i in sub:
                        if i not in j:
                            raise ModelError(f"cannot remove item {i} from object at {path}")
                        j.remove(i)
                elif isinstance(j, dict):
                    for i in sub:
                        if i not in j:
                            raise ModelError(f"cannot remove item {i} from object at {path}")
                        del j[i]
                else:
                    raise ModelError(f"cannot remove list from {tname(j)}")
            else:
                raise ModelError("expecting a remove list")
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

    def _applyTrafoAtPath(self, jm: JsonModel, tpath: ModelPath,
                          trafo: ModelTrafo, path: ModelPath):
        """Apply a transformation into a JSON Model."""

        if self._debug:
            log.debug(f"{jm._id}: trafo at {path}: {tpath}")

        j = jm._model

        # if tpath == ["$"]:
        #     log.warning("TODO add/remove definitions ?!")
        #     if "/" in trafo:
        #         assert isinstance(trafo["/"], list)
        #         for name in trafo["/"]:
        #             assert isinstance(name, str)
        #             if name in jm._defs:
        #                 del jm._defs[name]
        #             else:
        #                 log.warning(f"cannot remove definition for {name}")
        #     assert "*" not in trafo, f"not implemented yet"
        #     return

        # follow the JSON path
        for i, p in enumerate(tpath):
            assert isinstance(j, (list, dict))
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
            if last:  # apply!
                log.debug(f"applying on p={p} in j={j}")
                j[p] = self._applyTrafo(j[p], trafo, path)  # type: ignore
            else:  # move forward
                log.debug(f"moving forward on p={p}")
                j = j[p]  # type: ignore
        if not tpath:
            log.debug(f"empty tpath on {jm._model}")
            jm._model = self._applyTrafo(jm._model, trafo, path)

    def rewrite(self):
        """Apply model rewriting to current JSON Model."""

        # NOTE transformation specs may be empty
        for tpath, trafo in self._rewrite.items():
            lpath = ["$", "%", tpath]  # FIXME
            # typing issue, cannot assign list[str] to list[str|int] !?
            jm, path = self._parsePath(tpath, lpath)  # type: ignore
            self._applyTrafoAtPath(jm, path, trafo, lpath)  # type: ignore
        self._rewritten = True
