#
# Analyses
#
import functools
import re
import json

from .mtypes import UnknownModel, ModelPath, ModelType, ModelFilter, ModelObject, ModelArray, NullType, TopType
from .utils import log, is_regex, is_a_simple_object
from .predefs import CONST_RE, STR_MODEL_PREDEFS, BOOL_MODEL_PREDEFS, INT_MODEL_PREDEFS, FLOAT_MODEL_PREDEFS
from .recurse import recModel, allFlt, noRwt
from .model import JsonModel
from .runtime import ConstSet
from .runtime.support import _path as json_path

# JsonModel = typing.NewType("JsonModel", None)
type Constants = bool|int|float|str|list[int|float|str]
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
def valid(jm: JsonModel, path: ModelPath = [], root: bool = True, extend: bool = False) -> bool:
    """Check JSON Model structural (and slightly more) validity."""

    is_valid = True

    # allowed keywords
    ROOT_KW = {"$", "%", "~"}
    DIV_KW = {"@", "#"}
    CMP_KW = {"<", "<=", ">", ">="}
    NEQ_KW = {"=", "!="}
    ARR_KW = {"!"}
    OP_KW = {"@", "|", "&", "^", "+"}

    if extend:  # multiple-of: number, contains: model
        CMP_KW |= {".mo"}
        ARR_KW |= {".in"}

    NUM_KW = NEQ_KW | CMP_KW
    ANY_KW = DIV_KW | NUM_KW | ARR_KW
    if root:
        ANY_KW |= ROOT_KW

    def finiteRef(model: str) -> bool:
        ref, recref, recid, ljm = model, [], [], jm
        smodel = json.dumps(model)
        while isinstance(ref, str) and jm._isRef(ref) and ref not in recref:
            ljm = ljm.resolveRef(ref, path + recref)
            recref.append(ref)
            recid.append(ljm._id)
            ref = ljm._model
        finite = not jm._isRef(ref) or ref == "$#"  # Hmmm…
        if not finite:
            log.debug(f"infinite recursion on {smodel}: {recref} ({recid})")
        return finite

    def validFlt(model: ModelType, path: ModelPath) -> bool:
        spath, smodel = json_path(path), json.dumps(model)
        match model:
            case None:
                pass
            case bool():
                assert model, f"boolean model must be true at {spath}"
            case int():
                assert model in (-1, 0, 1), f"int model values at {spath}"
            case float():
                assert model in (-1.0, 0.0, 1.0), f"float model values at {spath}"
            case str():
                if model == "" or model[0] == "_":
                    pass
                elif model[0] == "=":
                    assert re.match(CONST_RE, model) is not None, f"constant model {smodel} at {spath}"
                elif model[0] == "/":
                    assert "/" in model[1:], f"regex model {smodel} has closing marker at {spath}"
                    pattern, ropts = model[1:].rsplit("/", 1)
                    assert (ropts == "" or ropts.isalpha()) and is_regex(pattern), f"regex model {smodel} at {spath}"
                elif model[0] == "$":
                    # reject predef extensions
                    if not extend and model.startswith("$__EXTENSION_"):
                        assert False, f"model extensions are enabled at {spath}"
                else:  # TODO more checks?
                    pass
            case list():
                pass
            case dict():
                assert len(model.keys() & OP_KW) <= 1, f"no operator mix at {spath}"
                if "#" in model:
                    assert isinstance(model["#"], str), f"model object comment is a string at {spath}"
                if "@" in model:
                    if "!" in model:
                        assert isinstance(model["!"], bool), f"unique (!) is a boolean at {spath}"
                    if ".mo" in model:
                        assert isinstance(model[".mo"], (int, float)), f"multiple-of extension is a number at {spath}"
                    # @ and comparison consistency
                    aro_type = ultimate_type(jm, model["@"])
                    if aro_type in (int, float):
                        assert all(isinstance(model[op], (int, float)) for op in NUM_KW & model.keys()), \
                            f"number model has number constraints at {spath}"
                    elif aro_type is str:
                        assert all(isinstance(model[op], (int, str)) for op in NUM_KW & model.keys()), \
                            f"string model has number or string constraints at {spath}"
                    elif aro_type in (list, dict):
                        assert all(isinstance(model[op], int) for op in NUM_KW & model.keys()), \
                            f"array or object model has integer constraints at {spath}"
                    elif aro_type is bool:
                        assert len(model.keys() & CMP_KW) == 0, f"boolean model has no comparison constraints at {spath}"
                        assert all(isinstance(model[op], bool) for op in NEQ_KW & model.keys()), \
                            f"boolean model has boolean eq/neq constraints at {spath}"
                    elif aro_type is NullType:
                        assert len(model.keys() & CMP_KW) == 0, f"null model has no comparison constraints at {spath}"
                        assert all(isinstance(model[op], NullType) for op in NEQ_KW & model.keys()), \
                            f"null model has null eq/neq constraints at {spath}"
                    elif aro_type is TopType:
                        assert len(model.keys() & (NUM_KW | ARR_KW)) == 0, \
                            f"multi typed model has no constraints at {spath}"
                    elif aro_type is None:
                        assert len(model.keys() & (NUM_KW | ARR_KW)) == 0, \
                            f"no type model has no constraints at {spath}"
                    else:
                        assert False, f"unexpected model type {aro_type} at {spath}"
                    # only comments
                    assert all(prop.startswith("#") for prop in model.keys() - ANY_KW), \
                        f"miscellaneous keywords are comments at {spath}"
                    # lattice consistency
                    if model.keys() & ARR_KW:
                        assert aro_type is list, f"array model for array constraints at {spath}"
                elif "|" in model:
                    assert isinstance(model["|"], list), f"or model is an array at {spath}"
                elif "^" in model:
                    assert isinstance(model["^"], list), f"xor model is an array at {spath}"
                elif "&" in model:
                    assert isinstance(model["&"], list), f"and model is an array at {spath}"
                elif "+" in model:
                    assert isinstance(model["+"], list), f"merge model is an array at {spath}"
                else:  # check object
                    props = set()  # check property name collisions
                    for p, m in model.items():
                        if p == "#":
                            continue
                        assert isinstance(p, str), f"property name {p} is a string at {spath}"
                        if p and p[0] not in ("$", "/"):
                            name = p[1:] if p[0] in ("?", "_", "!") else p
                            assert name not in props, f"no property name collison at {spath}"
                            props.add(name)
                        # more checks on p if p[0] == "$"
            case _:
                assert False, f"unexpected model base type at {spath}"
        return True

    try:
        for name, jmr in jm._defs.items():
            assert finiteRef("$" + name), f"finite recursion on ${name}"
        check(jm, validFlt, "JSON Model Structural Validity")
        is_valid = True
    except AssertionError as e:
        is_valid = False
        if jm._debug > 0:
            log.error(e, exc_info=True)
        else:
            log.warning(e)
        if jm._debug:
            raise

    return is_valid

# ultimate type of predefs
_UTYPE = {
    "$ANY": TopType,
    "$NULL": NullType,
    "$NONE": None,  # bottom for infeasible
}

for predef in BOOL_MODEL_PREDEFS:
    _UTYPE[predef] = bool
for predef in INT_MODEL_PREDEFS:
    _UTYPE[predef] = int
for predef in FLOAT_MODEL_PREDEFS:
    _UTYPE[predef] = float
for predef in STR_MODEL_PREDEFS:
    _UTYPE[predef] = str

def _ultimate_type(jm: JsonModel, model: ModelType, names: set[str]) -> type|None:
    if model is None:
        return NullType
    match model:
        case str():
            if model == "" or model[0] not in ("$", "="):
                # cover strings, regex...
                return type(model)
            elif model[0] == "=":  # constants
                return (
                    NullType if model == "=null" else
                    bool if model in ("=true", "=false") else
                    float if "." in model else
                    int
                )
            elif model in _UTYPE:  # predefs
                return _UTYPE[model]
            else:  # reference "$..."
                # stop detected recursion
                if model in names:
                    return None
                m = jm.resolveRef(model, ["<?>"])  # type: ignore
                return _ultimate_type(m, m._model, names | {model})
        case dict():
            if "@" in model:
                return _ultimate_type(jm, model["@"], names)
            elif "|" in model:
                assert isinstance(models := model["|"], list)
                types = set(_ultimate_type(jm, m, names) for m in models)
                if len(types) == 1:
                    return types.pop()
                elif len(types) == 0:  # |() == $NONE
                    return None
                else:
                    return TopType
            elif "^" in model:
                assert isinstance(models := model["^"], list)
                types = set(_ultimate_type(jm, m, names) for m in models)
                if len(types) == 1:
                    return types.pop()
                elif len(types) == 0:
                    return None
                else:
                    return TopType
            elif "&" in model:
                assert isinstance(models := model["&"], list)
                types = set(_ultimate_type(jm, m, names) for m in models)
                if len(types) == 1:
                    return types.pop()
                elif len(types) == 0:  # &() == $ANY
                    return TopType
                else:
                    # possibly not feasible
                    return None
            elif "+" in model:
                return dict
            else:
                return type(model)  # dict
        case _:  # bool, int, float, list
            return type(model)

def ultimate_type(jm: JsonModel, model: ModelType) -> type|None:
    """Get the utimate JSON type by following definitions.

    Return _None_ if unknown, eg several are possible.
    Note: this is also returned iff the type system is not feasible, eg "&(int, str)"
    """
    return _ultimate_type(jm, model, set())


# model predef to standard model
_UMODEL = {
    "$BOOL": True, "$NULL": None,
    "$I32": -1, "$U32": 0, "$I64": -1, "$U64": 0, "$INTEGER": -1,
    "$F32": -1.0, "$F64": -1.0, "$NUMBER": -1.0,
    "$STRING": "",
    "$ANY": "$ANY",
    "$NONE": "$NONE",
}

# str content predefs are their own standard model
for predef in STR_MODEL_PREDEFS:
    if predef not in _UMODEL:
        _UMODEL[predef] = predef

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
                    # FIXME generic comments!
                    if set(model.keys()).issubset(["@", "#", "~", "%", "$"]):
                        return ultimate_model(jm, model["@"])
                    else:
                        return UnknownModel  # type: ignore
                elif constrained:
                    return ultimate_model(jm, model["@"])
                else:
                    return UnknownModel  # type: ignore
            else:  # include | ^ &
                return model
        case _:
            return model

# this seems partially redundant with constant_values?
def evalModel(jm: JsonModel, model: ModelType, lists: bool = False) -> list|None:
    """Tell if an ultimate model value has a constant."""
    # FIXME should it detect @ eq?
    v = ultimate_model(jm, model)
    log.debug(f"model={model} v={v}")
    if v == UnknownModel:
        # FIXME ?!
        return None
    tv = type(v)
    if tv is str:
        assert isinstance(v, str)  # useless pyright hint
        if v == "":
            return None  # FIXME
        elif v == "=null" or v == "$NULL":
            return [ None ]
        elif re.search(r"^=(true|false)$", v) is not None:
            return [ True if v == "=true" else False ]
        elif re.search(r"^=-?\d+$", v) is not None:
            return [ int(v[1:]) ]
        elif re.search(r"^=", v) is not None:
            return [ float(v[1:]) ]
        elif v[0] == "_":
            return [ v[1:] ]
        elif v[0] in ("$", "/"):
            # TODO improve on $?
            return None
        else:
            return [ v ]
    elif lists and tv is dict and ("|" in v or "^" in v):
        op = "|" if "|" in v else "^"
        orcst = [ evalModel(jm, m, False) for m in v[op] ]
        if any(map(lambda c: c is None, orcst)) or not orcst:
            return None
        else:
            return functools.reduce(lambda v, e: v + e, orcst, [])
    else:
        return None

def disjunct_analyse(jm: JsonModel, model: ModelType, mpath: ModelPath, lists: bool = False) -> \
        tuple[list[tuple[str, type, list[int]]],
              dict[int, dict[str, ConstSet]],
              list[int]]|None:
    """Return optimized discriminators for code generation.

    Return struct:
    - list of tag tests: tag name, tag type, list of models index in the or-list
    - mapping from or-list model index to mapping from prop name to constant values
    - rejected or-list indexes
    """
    # FIXME if there is a ^, the preprocessor will have detected the discriminant
    # and turned it into a |.
    # TODO ensure determinism at all stages
    assert isinstance(model, dict) and "|" in model
    # get models
    orl = model["|"]
    log.debug(f"disjunct_analyze on {orl}")
    # sanity checks
    assert isinstance(orl, list)
    if len(orl) < 2:
        log.debug(f"not enough models for disjunction ({len(orl)}")
        return None
    # kept and rejected _initial_ models by or index
    kept: dict[int, ModelType] = { i: m for i, m in enumerate(orl) }
    rejected: dict[int, ModelType] = {}
    # get models, possibly following references and jumping over constraints?
    models: dict[int, ModelType] = { i: ultimate_model(jm, m) for i, m in kept.items() }
    log.debug(f"models: {models}")
    # only keep objects
    reject: list[int] = []
    for i, m in models.items():
        if not isinstance(m, dict) or "|" in m or "^" in m or "&" in m or "@" in m or "+" in m:
            log.debug(f"rejecting m: {m}")
            reject.append(i)
    for i in reject:
        del models[i]
        rejected[i] = kept[i]
        del kept[i]
    if len(models) <= 1:
        log.debug(f"not enough object models for disjunction ({len(models)})")
        return None
    # collect direct mandatory properties
    all_props: dict[int, set[str]] = {}
    for i, m in models.items():
        all_props[i] = {
            (k[1:] if k[0] in ("_", "!") else k)
                for k in m.keys() if k and k[0] not in ("$", "?", "/", "#")
        }
    # only objects with some mandatory properties
    for i in [ i for i, m in all_props.items() if not m ]:
        del all_props[i]
        rejected[i] = kept[i]
        del kept[i]
    if len(all_props) <= 1:
        log.debug("not enough objects with mandatory props for disjunction")
        return None
    # get cleaned props and their constant values
    all_const_props: dict[int, dict[str, ConstSet]] = {}
    for i, props in all_props.items():
        consts: dict[str, ConstSet] = {}
        for p in props:
            # mandatory props should be normalized…
            prop = f"_{p}" if f"_{p}" in models[i] else f"!{p}" if f"!{p}" in models[i] else p
            val = evalModel(jm, models[i][prop], lists)
            # log.debug(f"cst [{i}].{p} {models[i][prop]}: {val}")
            if val is not None:
                consts[p] = ConstSet(val)
            else:
                log.debug(f"no constants on alt [{i}].{p}")
        if len(consts) > 0:
            all_const_props[i] = consts
        else:
            log.debug(f"no constant props in {i}")
            rejected[i] = kept[i]
            del kept[i]
    log.debug(f"all_const_props: {all_const_props}")
    if len(all_const_props) <= 1:
        log.debug("not enough object with mandatory constant props for disjunction")
        return None
    # build tag candidates, for each prop which models indexes are ok, and all values
    # property name -> set of models that contain the property with a constant
    tag_to_model: dict[str, set[int]] = {}
    # cumulated constants
    tag_to_csts: dict[str, ConstSet] = {}
    # NOTE there is a subtility: if a tag can appear in rejected objects,
    # we must keep an external "or" with rejected models
    for i, p2c in all_const_props.items():
        for p, csts in p2c.items():
            if len(csts) == 0:
                # FIXME should not happen?
                continue
            if p not in tag_to_model:
                tag_to_model[p] = set()
                tag_to_csts[p] = ConstSet()
            if csts & tag_to_csts[p]:
                # skip if some common values
                pass
            else:
                # handling null as a special case may be necessary for some benches
                tag_to_model[p].add(i)
                tag_to_csts[p] |= csts
    # remove props which do not offer choices
    for p in list(tag_to_model):
        if len(tag_to_model[p]) <= 1:
            del tag_to_model[p]
            del tag_to_csts[p]
    # FIXME for now we required homogeneous types
    for p in list(tag_to_csts):
        if len(tag_to_csts[p].ctypes()) > 1:
            log.debug(f"removing multi type constant prop {p} from disjunction")
            del tag_to_model[p]
            del tag_to_csts[p]
    if not tag_to_model:
        log.debug("not any discriminant tag candidate for disjunction")
        return None
    # TODO there is a nice optimization problem here, for now just skip to a basic heuristic
    extracted: list[tuple[str, set[int]]] = []
    ex_models: set[int] = set()
    while tag_to_model:
        best: str|None = None
        for p, ms in tag_to_model.items():
            if best is None:
                best = p
            else:  # max models min property
                nb, np = len(tag_to_model[best]), len(tag_to_model[p])
                if nb < np or nb == np and p < best:
                    best = p
        if best is None:
            break
        else:
            tested: set[int] = tag_to_model[best]
            ex_models |= tested
            extracted.append((best, tag_to_model[best]))
            # cleanup for next round
            del tag_to_model[best]
            for p, ms in list(tag_to_model.items()):
                ms -= tested
                # drop props without enough disjunct models
                if len(ms) <= 1:
                    del tag_to_model[p]
    # there must be one if tag_to_model is not empty
    assert extracted
    log.debug(f"disjunction: {extracted}")
    # update kept/rejected dicts
    for i in list(kept):
        if i not in ex_models:
            rejected[i] = kept[i]
            del kept[i]
    # now build returned structure
    disjuncts = []
    for prop, smi in extracted:
        lmi = list(sorted(smi))
        assert len(lmi) > 1, f"discriminating discriminant on {prop}"
        ctype = all_const_props[lmi[0]][prop].ctypes().pop()
        disjuncts.append((prop, ctype, lmi))
    # final result
    return disjuncts, all_const_props, list(rejected)

def incompatible_prop(prop: str, obj: ModelObject) -> bool:
    """Is this property incompatible with the object model?"""
    for p, m in obj.items():
        if p == "":
            if m != "$NONE":  # default object
                return False
        elif p[0] == "#":
            pass
        elif p[0] in ("_", "!", "?"):
            if p[1:] == prop:
                return False
        elif p[0] == "/":
            # TODO check regex!
            return False
        elif p[0] == "$":
            # TODO check reference?
            return False
        elif p == prop:
            return False
        else:
            pass
    return True

# TODO partial: not all objets? shared prop names?
def distinct_prop_objects(jm, models: ModelArray) -> list[str|None]:
    """Return distinct mandatory props to shorten/split or/xor object checks."""
    if len(models) <= 1:
        return [None] * len(models)
    objs = [ultimate_model(jm, m) for m in models]
    counts: list[dict[str, int]] = []
    for idx, obj in enumerate(objs):
        counts.append({})
        if is_a_simple_object(obj):
            for prop in obj.keys():
                if not prop or prop[0] in "#?/$":
                    continue
                # else mandatory property name
                pname = prop[1:] if prop[0] in "!_" else prop
                counts[idx][pname] = 0
                for i, o in enumerate(objs):
                    if i != idx and incompatible_prop(pname, o):
                        counts[idx][pname] += 1
    # keep the most selective property on each model
    distinct_prop: list[str|None] = []
    for uses in counts:
        best = max(uses.values()) if uses else None
        if best:
            for prop, count in uses.items():
                if count == best:
                    distinct_prop.append((prop, best == len(models) - 1))
                    break
        else:
            distinct_prop.append(None)
    assert len(distinct_prop) == len(models)
    return distinct_prop
