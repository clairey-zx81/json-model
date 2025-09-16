import copy
import re
import typing
from collections.abc import MutableMapping
import json

from .mtypes import ModelPath, ModelTrafo, ModelRename, ModelDefs, ModelType
from .mtypes import ModelError, Jsonable, JsonSchema, JsonObject
from .utils import log, tname, PREDEF_RE, UUID_RE
from .recurse import recModel, allFlt, noRwt, _recModel
from .resolver import Resolver

# FIXME
JsonModel = typing.NewType("JsonModel", None)  # pyright: ignore

type SymTable = dict[str, JsonModel]
type Globals = dict[str, str]
type ModelRef = list[str]  # $stuff#name#inside

def json_dump(j: Jsonable):
    return json.dumps(j, indent=2, sort_keys=False)


class Symbols(MutableMapping[str, JsonModel]):
    """JSON Model Symbol Table.

    This associate models to names, which may be global or local.
    """

    def __init__(self, mid):

        self._id = mid
        # symbol definitions
        self._syms: SymTable = {}
        # local names to global names
        self._gmap: Globals = {}

    def toJSON(self, rec: bool = False):
        """Display as JSON."""
        if rec:
            data = {}
            data["#"] = f"Symbols {self._id}"
            data["__gmap__"] = self._gmap
            data.update({n: jm.toJSON(rec) for n, jm in self.items()})
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
    """Represent a JSON Model v2.

    There are 3 kinds of JSON Models:

    1. The head json model with all its dependent models, which is the first
       root model, holds the global symbol table and a list of all
       its related models from internal definitions or external references.
    2. Root models which represent distinct loaded files,
       and define an associated naming scope possibly shared with local defs.
    3. Local models created for the internal definitions of a root model,
       and share their naming scope with their parent.

    When providing a master model with ~, these models are loaded independently,
    i.e. they are considered a head model.
    """

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
        "URL": r"/^\w+://.*$/",  # FIXME relative URL?
        "DATE": r"/^\d\d\d\d-\d?\d-\d?\d$/",  # FIXME
        "TIME": r"/^[T ]?\d\d:\d\d:\d\d(\.\d\d\d)?(Z|[-+]\d\d(:?\d\d)?$/",  # FIXME
        "DATETIME": "",  # FIXME
        "UUID": "/^" + UUID_RE + "$/",
        "REGEX": "",  # FIXME
        "EXREG": "",
        "URI": r"^\w+:.*$/",  # TODO improve
        "EMAIL": r"^(?i)[a-z0-9_.]+@[a-z0-9_.]+$",
        "JSON": "",
        # to be continued…
        # o = optional
        "oBOOL": {"|": [None, "$BOOL"]},
        "oINT": {"|": [None, "$INT"]},
        "oFLOAT": {"|": [None, "$FLOAT"]},
        "oNUMBER": {"|": [None, "$NUMBER"]},
        "oSTRING": {"|": [None, "$STRING"]},
        "oURL": {"|": [None, "$URL"]},
        "oDATE": {"|": [None, "$DATE"]},
        "oUUID": {"|": [None, "$UUID"]},
        "oREGEX": {"|": [None, "$REGEX"]},
        # to be continued…
    }

    # OFFICIAL VERSION URLS
    VERSION_URLS = {
        "https://json-model.org/models/json-model",  # latest
        "https://json-model.org/models/json-model-v2",
    }

    def __init__(self,
                 model: ModelType,
                 resolver: Resolver|None,
                 *,
                 url: str = "",
                 head: JsonModel|None = None,
                 scope: Symbols|None = None,
                 debug: int = 0,
                 loose_int: bool|None = None,
                 loose_float: bool|None = None,
                 dname: str|None = None,
            ):

        # the root model cannot share a scope
        assert head is not None or head is None and scope is None

        if head is None:  # this is a (new) root model
            # self._lock = threading.RLock()
            self._is_head = True
            self._head = self
            self._id = 1
            self._models = {1: self}
            self._nmodels = 1
            self._globs = Symbols(0)
            self._is_root = True
            self._defs = Symbols(1)
            self._externs = []
        else:  # set root model this model belongs to
            # self._lock = None
            self._is_head = False
            self._head = head
            self._nmodels = None
            self._models = None
            # with head._lock:
            assert isinstance(head._nmodels, int) and isinstance(head._models, dict)
            head._nmodels += 1
            self._id = head._nmodels
            head._models[self._id] = self
            self._globs = head._globs
            if scope is None:
                self._is_root = True
                self._defs = Symbols(self._id)
                self._externs = []
            else:
                self._is_root = False
                self._defs = scope
                self._externs = None

        # unmodified parameters
        self._init_md = model
        self._resolver = resolver or Resolver()
        self._url = url
        self._dname = dname
        self._debug = debug

        # copy parameter which may be modified
        model = self.noComment(copy.deepcopy(model))

        # %: names and rewrites
        self._init_pc: dict[str, ModelType] = {}
        self._name: ModelRename = {}
        self._rewrite: dict[str, ModelTrafo] = {}
        self._imports: list[str] = []

        if debug:
            log.debug(f"{self._id}: model for {url} "
                      f"{head._id if head else '-'} {scope._id if scope else '-'}")

        # set loose/strict int/float
        if isinstance(model, dict) and "#" in model:
            meta = model["#"]
            if isinstance(meta, str):
                # default value from parameters
                li: bool|None = loose_int
                lf: bool|None = loose_float
                # local overrides
                if "JSON_MODEL_LOOSE_NUMBER" in meta:
                    li = True
                    lf = True
                elif "JSON_MODEL_STRICT_NUMBER" in meta:
                    li = False
                    lf = False
                if "JSON_MODEL_LOOSE_INT" in meta:
                    li = True
                elif "JSON_MODEL_STRICT_INT" in meta:
                    li = False
                if "JSON_MODEL_LOOSE_FLOAT" in meta:
                    lf = True
                elif "JSON_MODEL_STRICT_FLOAT" in meta:
                    lf = False
                self._loose_int = False if li is None else li
                self._loose_float = False if lf is None else lf
            else:
                self._loose_int = loose_int if loose_int is not None else False
                self._loose_float = loose_float if loose_float is not None else False
        else:
            self._loose_int = loose_int if loose_int is not None else False
            self._loose_float = loose_float if loose_float is not None else False

        # root models can have % $ ~ keywords
        if isinstance(model, dict) and "%" in model:
            assert self._is_root
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

            # reference imports
            if "<" in model_pc:
                imports = model_pc["<"]
                if isinstance(imports, str):
                    imports = [imports]
                else:
                    assert (isinstance(imports, list) and
                            all(map(lambda i: isinstance(i, str), imports)))
                self._imports = imports  # type: ignore

            # extract rewrites
            # TODO check name syntax? $Path#To#Def.path.to.prop
            self._rewrite = {
                name: rw
                    for name, rw in model_pc.items()
                        if isinstance(name, str) and
                            not name.startswith(".") and
                            name not in ("#", "<") and
                            not name.startswith("#")
            }

            # log.warning(f"rewrite={self._rewrite}")

            # save initial definition
            self._init_pc = model_pc

        if isinstance(model, dict) and "$" in model:
            assert self._is_root, f"{self._id}: {self._is_head}/{self._is_root} with $"
            dollar = model["$"]
            del model["$"]
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
                n: JsonModel(m, resolver, url=self._url + "#" + n,
                             head=self._head, scope=self._defs, debug=self._debug,
                             loose_int=self._loose_int, loose_float=self._loose_float, dname=n)
                    for n, m in dollar.items()
                        if isinstance(n, str) and n not in ("#", "")
            })
            # warn about possibly missing $
            for name, value in self._defs.items():
                m = value._model
                if isinstance(m, str) and re.search("^((https?|file)://|\\.)", m):
                    log.warning(f"url-looking {name}: "
                                "add missing $ or prefix with _ for string constants")
            # keep initial definitions
            self._init_dl = dollar
        else:
            self._init_dl = None

        if isinstance(model, dict) and "~" in model:
            assert self._is_root
            version = model["~"]
            del model["~"]
            # FIXME should accept a *model*, not just a URL? or not?
            if not isinstance(version, str):
                raise ModelError(f"invalid model version type: {tname(version)}")
            log.debug(f"url={url} version={version}")
            # FIXME prevent all recursion cycles!?
            if version != self._url:  # prevent direct recursion
                # FIXME ~ should be a head model
                self._spec = self.load(version, ["~"], True)
            else:
                self._spec = self
            log.info(f"renaming {self._id} from ~")
            model = self._spec.rename(model, [], True)
        else:
            # FIXME add a default?
            self._spec = None

        self._model = model

        # import definitions
        if self._imports:
            log.info(f"importing model definitions from {self._imports}")
            assert isinstance(self._imports, list) and \
                all(isinstance(s, str) and s and s[0] == "$" for s in self._imports), \
                "imports must be an array of references"
            for i, ref in enumerate(self._imports):
                jsub = self.resolveRef(ref, ["%", "~", i], False)
                if len(jsub._defs) > 0:
                    for name, jm in jsub._defs.items():
                        if name in self._defs:
                            raise ModelError(f"cannot override definition {name} in {self._url} from {ref}")
                        self._defs[name] = jm
                else:
                    log.warning(f"no definition to import from {ref}")

        if self._is_root:
            # loading twice, rewriting may add references…
            self.allLoads()
            self.rewrite()

        if self._is_head:
            # hmmm… the above rewriting may have changed external dependencies,
            # probably it would be enough to rewrite only the changed externals,
            # but which one were changed is not visible from here so we load again
            # everything, just in case.
            for mid in reversed(list(self._head._models.keys())):  # pyright: ignore
                jm = self._head._models[mid]  # pyright: ignore
                if jm._is_root:
                    jm.allLoads()
            self.scope(self._globs, [], set(), {})
            # _ = self._debug and log.debug(f"globs = {self._globs}")
            self.unload()

    def load(self, url: str, path: ModelPath, is_head: bool = False) -> JsonModel:
        """Retrieve external JSON Model for a URL."""
        log.debug(f"{self._id}: getting {url} at {path}")
        # get raw json, may be cached
        j = self._resolver(url, path=path)
        # build a *new* model: distinct refs to the same url are treated independently
        # because each may be rewritten independently.
        # If you want to share, add an explicit definition to a url and use it afterwards.
        return JsonModel(j, self._resolver, url=url, head=None if is_head else self._head,
                         scope=None, debug=self._debug,
                         loose_int=self._loose_int, loose_float=self._loose_float)

    def allLoads(self):
        """Load externals, switch un-named externals to local definitions."""

        assert self._is_root
        log.debug(f"{self._id}: IN allLoads on {self._url}")

        def follow(model: str, path: ModelPath) -> JsonModel:
            """Follow a simple URL model till the end of the world."""

            assert isinstance(model, str) and self._isUrlRef(model)
            followed, jm = set(), None
            current: Jsonable = model

            while self._isUrlRef(current):
                assert isinstance(current, str)  # pyright hint
                if self._debug >= 2:
                    log.debug(f"{self._id}: following {current} at {path}")

                # NOTE the first url does not have a fragment, but subsequent urls may have
                if "#" in model:
                    url, frag = current[1:].split("#", 1)
                else:
                    url, frag = current[1:], None

                if url in followed:
                    raise ModelError(f"infinite recursion when loading {url} at {path}")

                log.debug(f"{self._id}: loading {url}")
                followed.add(url)
                jm = self.load(url, path)
                log.debug(f"{self._id}: head models: "
                          f"{[mid for mid in sorted(self._head._models.keys())]}")  # pyright: ignore

                # handle sequence of fragments
                while frag:
                    if "#" in frag:
                        name, frag = frag.split("#", 1)
                    else:
                        name, frag = frag, None
                    jm = jm._defs[name]

                current = jm._model

            assert jm is not None  # pyright hint
            return jm

        # substitute $<URL>#... with $__external_X#...
        def ldRwt(model: ModelType, path: ModelPath) -> ModelType:

            if isinstance(model, str) and self._isUrlRef(model):
                log.debug(f"{self._id}: ldRwt at {path} with {model}")
                assert self._externs is not None  # pyright hint
                if "#" in model:
                    model, frag = model.split("#", 1)
                else:
                    frag = None
                ext = follow(model, path)
                name = f"__external_{len(self._externs)}"
                self._defs[name] = ext
                self._externs.append(ext)
                log.debug(f"swith: {name} {model}")
                return "$" + name + (("#" + frag) if frag else "")

            return model

        # log.debug(f"{self._id}: root url")
        if self._isUrlRef(self._model):
            # if the root schema is a string, there was no definitions nor rewrites!
            # ??? assert len(self._defs) == 0 and isinstance(self._model, str)
            assert isinstance(self._model, str)  # pyright helper
            self.override(follow(self._model, []))

        names = list(self._defs.keys())
        for name in names:
            # log.debug(f"{self._id}: {name} url")
            model = self._defs[name]._model
            if self._isUrlRef(model):
                assert isinstance(model, str)  # pyright hint
                self._defs[name] = follow(model, [name])

            # look for other external references in the model definitions
            _recModel(self._defs[name]._model, [name], allFlt, ldRwt, True, False)

        # look for external references in the main model
        _recModel(self._model, [], allFlt, ldRwt, True, True)

        log.debug(f"{self._id}: OUT allLoads on {self._url}")

    def override(self, jm: JsonModel):
        """Self replace model with another model, for handling $<url>."""
        # NO _is_root, init_*
        log.debug(f"overriding {self._id} with {jm._id}")
        assert self._is_root and jm._is_root
        assert self._globs._id == jm._globs._id
        self._id = jm._id
        self._defs = jm._defs
        self._name = jm._name
        self._rewrite = jm._rewrite
        self._externs = jm._externs
        self._model = jm._model
        self._loose_int = jm._loose_int
        self._loose_float = jm._loose_float

    def unload(self):
        """Delete unused models."""
        assert self._is_head and isinstance(self._models, dict)
        todo, keep = {self._id}, set()

        # transitive closure
        while todo:
            ntodo = set()
            keep.update(todo)
            for mid in sorted(todo):
                model = self._models[mid]
                if not model._is_root:
                    continue
                for _, jm in model._defs.items():
                    if jm._id not in keep:
                        ntodo.add(jm._id)
            todo = ntodo

        # cleanup
        total = len(self._models)
        for mid in list(self._models.keys()):
            if mid not in keep:
                del self._models[mid]

        # debug summary
        if self._debug:
            kept = " ".join(str(mid) for mid in sorted(keep))
            log.debug(f"{self._id}: unload {len(self._models)}/{total} models kept ({kept})")

    def noComment(self, model: ModelType):
        """Remove non trivial comments."""

        def rmComments(m: ModelType, p: ModelPath):
            if isinstance(m, list):
                return list(filter(lambda i: not isinstance(i, str) or not i.startswith("#"), m))
            elif isinstance(m, dict):
                for prop in list(m):
                    if prop != "#" and prop.startswith("#"):
                        del m[prop]
                return m
            else:
                return m

        return recModel(model, allFlt, rmComments)

    #
    # Display
    #
    def toJSON(self, recurse: bool = True, verbose: bool = False) -> Jsonable:
        """Convenient JsonModel debug display."""
        data = {
            "type": "head" if self._is_head else "root" if self._is_root else "local",
            "id": self._id,
            "url": self._url,
            "model": self._model,
            "int": "loose" if self._loose_int else "strict",
            "float": "loose" if self._loose_float else "strict",
        }
        if verbose:
            data["init"] = self._init_md
        if self._is_head:
            assert self._models is not None and isinstance(self._models, dict)  # pyright hint
            data["dependents"] = {
                mid: self._head._models[mid]._url  # pyright: ignore
                    for mid in sorted(self._head._models)  # pyright: ignore
            }
            if recurse:
                data["globals"] = {
                    name: jm._id  # f"Model {jm._id}"
                        for name, jm in self._globs.items()
                }
            else:
                data["globals"] = f"Symbols {self._globs._id}"
            # externals?
        if self._is_root and recurse:
            data.update({
                "defs": self._defs.toJSON(recurse),  # False?
                "rename": self._name,
                "rewrite": self._rewrite,
            })
        if "defs" not in data:
            data["defs"] = f"Symbols {self._defs._id}"
        return data

    # FIXME this is **not** very clean YET, should be a valid model?!
    def toModel(self, deep: bool = False) -> Jsonable:
        """Return JSON Model (more or less) for display."""
        model = copy.deepcopy(self._model)
        if isinstance(model, dict):
            if "#" in model:
                del model["#"]
            li = "JSON_MODEL_LOOSE_INT" if self._loose_int else ""
            lf = "JSON_MODEL_LOOSE_FLOAT" if self._loose_float else ""
            loose = f" ({li} {lf})" if self._loose_float and self._loose_int else f" ({li}{lf})"
            model["#"] = \
                f"JsonModel {self._id}{loose if self._loose_float or self._loose_int else ''}"
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

    def toSchema(self, recurse: bool = True, path: ModelPath|None = None,
                 version: bool|None = False) -> JsonSchema:
        from . import convert
        schema: JsonSchema
        model = copy.deepcopy(self._model)
        changed = False
        if path is None:
            path = []

        # try to replace some key references
        def keyFlt(model: ModelType, path: ModelPath) -> bool:
            nonlocal changed
            if isinstance(model, dict):
                for key in list(model.keys()):
                    lpath = path + [key]
                    if self._isRef(key):
                        jm = self.resolveRef(key, lpath)
                        if isinstance(jm._model, str):
                            m = jm._model
                        else:
                            log.info(f"string re for prop ref {key} at {lpath}")
                            pattern = convert.propRefRegex(jm, jm._model, lpath)  # type: ignore
                            if pattern is not None:
                                if pattern == "":  # special case
                                    m = pattern
                                else:
                                    m = r"/" + pattern + r"/"
                            else:
                                log.warning(f"cannot replace {key} at {lpath}, rough approximation")
                                # this may lead to an invalid schema
                                m = "/^.*$/s"
                    else:
                        m = key
                    if m == "":
                        pass
                    elif m in PREDEF_RE:
                        m = r"/^" + PREDEF_RE[m] + "$/"
                    elif m[0] == "_":
                        m = "!" + m[1:]
                    elif m[0] not in ("/", "$", "="):
                        m = "?" + m
                    if m != key and (m == "" or m[0] == "/"):
                        changed = True
                        log.info(f"replacing {key} with {m} at {lpath}")
                        assert m not in model, f"cannot overwrite key {m} at {lpath}"
                        model[m] = model[key]
                        del model[key]
            return isinstance(model, (list, dict))

        model = recModel(model, keyFlt, noRwt)

        if changed:
            log.debug(f"filtered model={model}")

        # convert root model
        schema = convert.model2schema(model, path, self._defs)  # type: ignore

        # root specific, only when there are defs though
        if recurse and (self._defs or version):
            # ensure that schema is an object
            if isinstance(schema, bool):  # we need an object to store defs
                schema = {} if schema else {"not": True}
                # possibly salvage root comment
                if isinstance(self._model, dict) and "#" in self._model:
                    schema["description"] = self._model["#"]
            # build root object, in order
            root: JsonObject = {}
            root["$comment"] = "JSON Schema generated by JSON Model Compiler"
            if version is None or version:
                root["$schema"] = "https://json-schema.org/draft/2020-12/schema"
            # Hmmm… not really?!
            # if self._url:
            #     root["$id"] = self._url
            if "description" in schema:  # move description ahead
                root["description"] = schema["description"]
                del schema["description"]
            if self._defs:
                root["$defs"] = {  # type: ignore
                    name: jm.toSchema(False, ["$", name])
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

        if self._debug >= 3:
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
                if self._debug:
                    log.debug(f"{self._id}: ref={ref} model={self._model} defs={list(self._defs.keys())}")
                raise ModelError(f"{self._id}: cannot find definition for \"{name}\" ({path})")
            # creation only allowed while rewriting, as new defs may be added _after_ a reference
            log.info(f"{self._id}: creating empty definition \"{name}\"")
            self._defs[name] = JsonModel(None, self._resolver, url=self._url + "#" + name,
                                         head=self._head, scope=self._defs, debug=self._debug,
                                         loose_int=self._loose_int, loose_float=self._loose_float)
            return self._defs[name]

    def resolveRef(self, model: Jsonable, path: ModelPath, create: bool = False) -> JsonModel:
        """Resolve references up to an actual model, maybe."""
        jm, initial, followed = self, model, []

        if self._debug >= 2:
            log.debug(f"{self._id}: RR {model} at {path}")

        # no jm for predefs
        assert not self._isPredef(model), f"no resolution for {model}"

        # shortcut with global scoping
        if isinstance(model, str) and self._isRef(model) and self._defs.ghas(model):
            if self._debug >= 3:
                log.debug(f"{self._id}: gmap shortcut {self._defs._gmap}")
                log.debug(f"{self._id}: globs = {self._globs}")
            return self._globs[self._defs.gget(model)]

        # NOTE after a merge, some references may be global
        if isinstance(model, str) and self._isRef(model) and model in self._globs:
            if self._debug >= 3:
                log.debug(f"{self._id}: direct globs shortcut for {model}")
            return self._globs[model]

        # actual resolution
        while jm._isRef(model):
            jm_id = jm._id  # entry id
            assert isinstance(model, str)  # pyright hint
            if self._debug >= 3:
                log.debug(f"{self._id}: [{jm._id}] RR ref loop on {model}")
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
                jm = jm.load(url, path)
            else:  # reference to a definition
                if self._debug >= 3:
                    log.debug(f"{self._id}: [{jm._id}] RR to RD for {model} at {path}")
                jm = jm.resolveDef(model, path, create)
                # if self._debug >= 3:
                #     log.debug(f"{self._id}: [{jm._id}] after RD")

                # special case for "$#" which leads to a direct recursion
                if jm._id == jm_id and model == jm._model:
                    if model == "$#":
                        break
                    else:
                        raise ModelError(f"{self._id}: (jm={jm._id}) resolution cycle on {model}")
                model = jm._model

            if self._debug >= 3:
                log.debug(f"{self._id}: RR next {model} in {jm._id}")

        if self._debug >= 2:
            log.debug(f"{self._id}: RR resolved {initial} to {jm._id}")

        return jm

    #
    # Build global symbol table
    # Build mapping of local references to global references
    #
    def scope(self, symbols: Symbols, root: ModelRef,
              visited: set[tuple[str, int]], references: dict[int, str]):
        """Move all local references to the root scope."""
        if self._debug >= 2:
            log.debug(f"{self._id}: scoping {root} ({visited} / {references})")
            if self._debug >= 3:
                log.debug(f"{self._id}: scope in symbols: {symbols}")

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

        # override URLs with their target?!
        if self.isUrlRef():
            jm = self.resolveRef(self._model, [])
            symbols[root_ref] = jm
            jm.scope(symbols, root, visited, references)

        # handle models's symbol table if not done yet
        sid = ("s", self._defs._id)
        if sid not in visited:
            visited.add(sid)
            # two phase ensure that maps are okay for resolveRef
            # names = list(self._defs.keys())
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
            if self._debug >= 3:
                log.debug(f"{self._id}: gmap={self._defs._gmap}")
            for name, jm in self._defs.items():
                jm.scope(symbols, root + [name], visited, references)

        # update map of local references to global references
        def globRwt(m: ModelType, p: ModelPath) -> ModelType:
            if isinstance(m, str):
                if self._isSimpleRef(m):
                    jm = self.resolveRef(m, p + [m])
                    if jm._id in references:
                        gref = references[jm._id]
                    else:
                        # assert False  # FIXME ?!
                        gref = root_ref + "#" + m[1:]
                        if gref not in symbols:
                            symbols[gref] = jm
                            jm.scope(symbols, root + [m[1:]], visited, references)
                        references[jm._id] = gref
                    # log.debug(f"{self._id}: glob rwt m={m} jm={jm._id} gref={gref}")
                    if not self._defs.ghas(m):
                        # log.debug(f"{self._id}: glob rwt gmap {m} -> {gref} for {self._defs._id}")
                        self._defs.gset(m, gref)
                    # if not jm._defs.ghas(gref):  # also accept global references?
                    #     jm._defs.gset(gref, gref)
                elif self._isUrlRef(m):
                    if m not in symbols:
                        symbols[m] = self.resolveRef(m, p + [m])
                    if not self._defs.ghas(m):
                        self._defs.gset(m, m)
            return m

        self._model = recModel(self._model, allFlt, globRwt, True)

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
        assert tpath and tpath[0] == "$", f"tpath must be a reference: {tpath}"
        if "." in tpath:
            name, jpath = tpath.split(".", 1)
            if jpath == "":
                raise ModelError(f"bad transformation path at {path}: {tpath}")
            xpath = [int(i) if re.match(r"\d+$", i) else i for i in jpath.split(".")]
        else:
            name, xpath = tpath, []
        log.debug(f"{self._id}: parsePath name={name} xpath={xpath}")
        jm = self.resolveRef(name, path, True)
        return (jm, xpath)

    def _isTrafo(self, trafo: ModelTrafo):
        return isinstance(trafo, dict) and set(trafo.keys()).issubset({"#", "/", "*"})

    def _applyTrafo(self, j: Jsonable, trafo: ModelTrafo, path: ModelPath):
        """Apply this transformation on j."""

        if not isinstance(trafo, dict) or "/" not in trafo and "*" not in trafo:
            return trafo
        assert self._isTrafo(trafo)
        assert isinstance(trafo, dict)  # pyright hint
        if self._debug:
            log.debug(f"{self._id}: applyTrafo trafo={trafo} on j={j} [{path}]")

        if "/" in trafo:
            sub = trafo["/"]
            # handle scalars
            if sub is None or isinstance(sub, (bool, int, float, str)):
                sub = [sub]
            if isinstance(sub, list):
                if isinstance(j, list):
                    for i in sub:
                        if i not in j:
                            raise ModelError(f"cannot remove item {i} from list at {path}")
                        j.remove(i)
                elif isinstance(j, dict):
                    for i in sub:
                        if i not in j:
                            raise ModelError(f"cannot remove item {i} from object at {path}")
                        del j[i]
                else:
                    raise ModelError(f"cannot remove list from {tname(j)} at {path}")
            else:
                raise ModelError(f"expecting a remove list at {path}")

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
                            # raise ModelError(f"cannot overwrite property {k} at {path}, remove first")
                            log.warning(f"overwriting property {k} at {path}")
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
                log.debug(f"{jm._id}: applying on p={p} in j={j} trafo={trafo}")
                j[p] = self._applyTrafo(j[p], trafo, path)  # type: ignore
                if self._debug >= 3:
                    log.debug(f"{self._id}: after trafo j[p] = {j[p]}")  # pyright: ignore
            else:  # move forward
                log.debug(f"{jm._id}: moving forward on p={p}")
                j = j[p]  # type: ignore
        if not tpath:
            log.debug(f"{jm._id}: empty tpath on {jm._model}")
            jm._model = self._applyTrafo(jm._model, trafo, path)

    def rewrite(self):
        """Apply model rewriting to current JSON Model."""

        # NOTE transformation specs may be empty
        for tpath, trafo in self._rewrite.items():
            lpath = ["$", "%", tpath]  # FIXME
            # typing issue, cannot assign list[str] to list[str|int] !?
            jm, path = self._parsePath(tpath, lpath)  # type: ignore
            self._applyTrafoAtPath(jm, path, trafo, lpath)  # type: ignore
