#
# Analyses
#
import re
from .mtypes import UnknownModel, ModelPath, ModelType, ModelFilter
from .utils import log, CONST_RE, is_regex
from .recurse import recModel, allFlt, noRwt
from .model import JsonModel

# JsonModel = typing.NewType("JsonModel", None)
type Constants = bool|int|float|str
type ModelRef = list[str]

def references(jm: JsonModel) -> dict[str, set[int]]:
    """Get direct references between models.

    local name in model -> set of model ids that are referenced
    """
    assert jm._is_root

    def directRefs(model: ModelType) -> set[int]:
        """Recursive collect references."""

        refs: set[int] = set()

        def drRwt(m: ModelType, p: ModelPath) -> ModelType:
            if isinstance(m, str) and jm._isRef(m):
                target = jm.resolveRef(m, p)
                refs.add(target._id)
            return m

        recModel(model, allFlt, drRwt, True)

        return refs

    contains = {}

    for name, model in jm._defs.items():
        contains[name] = directRefs(model._model)

    contains[""] = directRefs(jm._model)

    return contains

# def reachable(self):
#     """Build reachable defs."""
#
#     # should consider **all** loaded models!?
#     contains = self.references()
#     reached = copy.deepcopy(contains)
#
#     # simplistic transitive closure computation
#     changed = True
#     while changed:
#         changed = False
#         for ref, refs in reached.items():
#             for r in refs:
#                 if r in reached and not reached[r].issubset(refs):
#                     changed = True
#                     refs.update(reached[r])
#
#     return reached

def check(jm: JsonModel, assertion: ModelFilter, what: str = "?", short: bool = False) -> bool:
    """Check an arbitrary local assertion on a model."""

    okay = True

    def checkFlt(model: ModelType, path: ModelPath) -> bool:
        nonlocal okay
        if not assertion(model, path):
            log.debug(f"{jm._id}: check {what} failed at {path}")
            okay = False
        return okay if short else True

    recModel(jm._model, checkFlt, noRwt, True)

    return okay

# FIXME must tell why it is unhappy!
def valid(jm: JsonModel, path: ModelPath = [], root: bool = True) -> bool:
    """Check JSON Model structural (and slightly more) validity."""

    is_valid = True

    def finiteRef(model: str) -> bool:
        ref, recref, recid, ljm = model, [], [], jm
        while isinstance(ref, str) and jm._isRef(ref) and ref not in recref:
            ljm = ljm.resolveRef(ref, path + recref)
            recref.append(ref)
            recid.append(ljm._id)
            ref = ljm._model
        finite = not jm._isRef(ref) or ref == "$#"  # Hmmm…
        if not finite:
            log.debug(f"infinite recursion on {model}: {recref} ({recid})")
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
                    if "!" in model:
                        is_valid &= isinstance(model["!"], bool)
                    for op in ("=", "!=", "<", "<=", ">", ">="):
                        if op in model:
                            is_valid &= isinstance(model[op], (int, float, str))
                    # TODO reject any other props! TODO allow .mo and other extensions?
                    for k in model.keys():
                        is_valid &= \
                            k in ("@", "!", "=", "!=", "<", "<=", ">=", ">", "#", "$", "%", "~")
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
                    props = set()  # property name collisions
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

    if is_valid and jm._defs:
        for name, jmr in jm._defs.items():
            is_valid &= finiteRef("$" + name)

    if is_valid:
        try:
            check(jm, validFlt, "JSON Model Structural Validity")
        except AssertionError as e:
            log.error(e, exc_info=jm._debug > 0)
            is_valid = False
            if jm._debug:
                raise

    # TODO also check other instances?!

    return is_valid



# ultimate type of predefs
_UTYPE = {
    "$ANY": None, "$NONE": None,
    "$NULL": type(None),
    "$BOOL": bool, "$BOOLEAN": bool,
    "$I32": int, "$U32": int, "$I64": int, "$U64": int, "$INT": int, "$INTEGER": int,
    "$F32": float, "$F64": float, "$FLOAT": float, "$NUMBER": float,
    "$STRING": str,
    "$URL": str, "$URI": str, "$EMAIL": str,
    "$REGEX": str, "$EXREG": str,
    "$DATE": str, "$TIME": str, "$DATETIME": str,
    "$UUID": str, "$JSON": str,
}


# TODO return a set of types?
def ultimate_type(jm: JsonModel, model: ModelType) -> type|None:
    """Get the utimate type by following definitions.

    Return _None_ if unknown, eg several are possible.
    Note: this is also return of the type system is not feasible, eg "&(int, str)"

    FIXME recursion
    """
    match model:
        case str():
            if model == "" or model[0] not in ("$", "="):
                return type(model)
            elif model[0] == "=":  # constants
                return (type(None) if model == "=null" else
                        bool if model in ("=true", "=false") else
                        float if "." in model else
                        int)
            elif model in _UTYPE:
                return _UTYPE[model]
            else:
                m = jm.resolveRef(model, ["<?>"])  # type: ignore
                return ultimate_type(m, m._model)
        case dict():
            if "@" in model:
                return ultimate_type(jm, model["@"])
            elif "|" in model:
                assert isinstance(models := model["|"], list)
                types = set(ultimate_type(jm, m) for m in models)
                if len(types) == 1:
                    return types.pop()
                else:
                    return None
            elif "^" in model:
                assert isinstance(models := model["^"], list)
                types = set(ultimate_type(jm, m) for m in models)
                if len(types) == 1:
                    return types.pop()
                else:
                    return None
            elif "&" in model:
                assert isinstance(models := model["&"], list)
                types = set(ultimate_type(jm, m) for m in models)
                if len(types) == 1:
                    return types.pop()
                else:
                    # possibly not feasible
                    return None
            else:
                return type(model)  # dict
        case _:  # None, bool, int, float, list
            return type(model)


# model predef to standard model
_UMODEL = {
    "$BOOL": True, "$NULL": None,
    "$I32": -1, "$U32": 0, "$I64": -1, "$U64": 0, "$INTEGER": -1,
    "$F32": -1.0, "$F64": -1.0, "$NUMBER": -1.0,
    "$STRING": "",
    # stop recursion on (some) predefs
    "$ANY": "$ANY",
    "$NONE": "$NONE",
    "$URL": "$URL",
    "$REGEX": "$REGEX",
    "$EXREG": "$EXREG",
    "$DATE": "$DATE",
    "$TIME": "$TIME",
    "$DATETIME": "$DATETIME",
    "$UUID": "$UUID",
    "$URI": "$URI",
    "$EMAIL": "$EMAIL",
    "$JSON": "$JSON",
    # to be continued…
}

def ultimate_model(jm: JsonModel, model: ModelType, constrained=True, strict=False) -> ModelType:
    """Look for the real model, beyond references."""
    log.debug(f"ultimate_model on {model}")
    match model:
        case str():
            if model == "" or model[0] not in ("$", "="):  # / returns as is
                return model
            elif model[0] == "=":
                return model
            else:  # follow definition if possible
                assert model[0] == "$"
                if model in _UMODEL:
                    m = _UMODEL[model]
                else:
                    m = jm.resolveRef(model, [])._model
                # handle some predefs (again)
                if isinstance(m, str) and m in _UMODEL:
                    return _UMODEL[m]
                # else try recursing
                return ultimate_model(jm, m) if m != UnknownModel else m  # type: ignore
        case dict():
            if "@" in model:
                if strict:
                    if set(model.keys()).issubset(["@", "#", "~", "%", "$"]):
                        return ultimate_model(jm, model["@"])
                    else:
                        return UnknownModel  # type: ignore
                elif constrained:
                    return ultimate_model(jm, model["@"])
                else:
                    return UnknownModel  # type: ignore
            elif "|" in model:
                return UnknownModel  # type: ignore
            else:
                return model
        case _:
            return model

def evalModel(jm: JsonModel, model: ModelType):
    """Tell if an ultimate model value has a constant."""
    # FIXME should it detect @ eq?
    v = ultimate_model(jm, model)
    if v == UnknownModel:
        # FIXME ?!
        return None
    tv = type(v)
    if tv is str:
        assert isinstance(v, str)  # useless pyright hint
        if v == "":
            return None  # FIXME
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

def disjunct_analyse(jm: JsonModel, model: ModelType, mpath: ModelPath) -> \
        tuple[str, type, list, list]|None:
    """Return the optimized check function if possible."""
    # FIXME if there is a ^, the preprocessor will have detected the discriminant
    # and turned it into a |.
    assert isinstance(model, dict) and "|" in model
    # first filter out
    utype = ultimate_type(jm, model)
    if utype is not dict:
        log.debug(f"ultimate type not a dict: {utype}")
        return None
    # get models
    assert isinstance(models := model["|"], list)
    models = [ultimate_model(jm, m) for m in models]
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
    all_const_props: list[dict[str, Constants]] = []
    for props, model in zip(all_props, models):
        consts: dict[str, Constants] = {}
        assert isinstance(model, dict)
        for prop in props:
            val = evalModel(jm, model[prop])
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
    tag_type = ultimate_type(jm, all_const_props[0][tag_name])
    assert tag_type in (bool, int, float, str)

    return tag_name, tag_type, models, all_const_props
