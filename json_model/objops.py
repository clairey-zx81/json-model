#
# Merging (+ operator)
#
import copy

from .mtypes import ModelType, ModelPath, ModelObject, OperatorError
from .predefs import MODEL_PREDEFS
from .utils import log, tname, merge_objects, model_type, constant_value, simple_object, is_base_model
from .recurse import recModel, allFlt, builtFlt, noRwt
from .model import JsonModel
from . import analyze

# - inline defs inside +
# - distribute + over | and ^
# - merge objects, removing all +
#
def _mergeInlining(jm: JsonModel):

    changes = 0

    def miFlt(model: ModelType, path: ModelPath) -> bool:

        def inline(m: ModelType, p: ModelPath):
            nonlocal changes
            if isinstance(m, str):  # actual inlining
                assert m and m[0] == "$"
                if jm._isPredef(m):
                    return m
                changes += 1
                jmr, mo, seen = jm, m, set()
                while isinstance(mo, str):
                    jmr = jmr.resolveRef(mo, p)
                    # loop guard, really needed?
                    if jmr._id in seen:
                        raise Exception(f"cycle while resolving {m}")
                    seen.add(jmr._id)
                    mo = jmr._model
                mo = copy.deepcopy(jmr._model)
                log.debug(f"{jm._id} inline from {jmr._id}")
                assert isinstance(mo, dict)
                if jm._defs._id != jmr._defs._id:  # if not in same name space
                    if jm._loose_int != jmr._loose_int or jm._loose_float != jmr._loose_float:
                        log.warning("should not combine models with distinct int/float looseness: "
                                    f"{jm._url} and {jmr._url}")

                    # substitute local references
                    def subRefRwt(m, p):
                        return jmr._defs.gget(m) if jmr._isRef(m) else m
                    return recModel(mo, allFlt, subRefRwt, True)
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

    jm._model = recModel(jm._model, miFlt, noRwt, True)

    log.debug(f"{jm._id}: merge inline {changes}")

    return changes > 0

def _mergeDistribute(jm: JsonModel):

    changes = 0

    def isAlt(m: ModelType) -> bool:
        return isinstance(m, dict) and ("|" in m or "^" in m)

    def mdFlt(model: ModelType, path: ModelPath) -> bool:
        # +( |(A B) C ) -> |( +(A C) +(B C) )
        nonlocal changes

        dive = builtFlt(model, path)

        if not isinstance(model, dict) or "+" not in model:  # no merge here
            return dive

        plus, is_xor = model["+"], False
        assert isinstance(plus, list), f"+ type: {tname(plus)}"

        if not any(map(isAlt, plus)):  # nothing to distribute
            return dive

        # actual distribution
        changes += 1

        lmodels: list[list[ModelType]] = [[]]
        for m in plus:
            assert isinstance(m, dict), f"unexpected model in +: {m}"
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

    jm._model = recModel(jm._model, mdFlt, noRwt)

    log.debug(f"{jm._id}: merge distribute {changes}")

    return changes > 0

def _mergeObjects(jm: JsonModel):
    """Actually compute and remove operator "+"."""

    changes = 0

    def moRwt(model: ModelType, path: ModelPath) -> ModelType:
        nonlocal changes
        if not isinstance(model, dict) or "+" not in model:
            return model
        changes += 1
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

    jm._model = recModel(jm._model, builtFlt, moRwt)

    log.debug(f"{jm._id}: merge objects {changes}")

    return changes > 0

def merge(jm: JsonModel):

    # NOTE after distribution, more inlining may be required
    # +( |( $A, {.1.} ), {.2.} ) -> |( +( $A, {.2.} ), +( {.1.}, {.2.} ) )

    updated = True
    while updated:
        _mergeInlining(jm)
        updated = _mergeDistribute(jm)

    if jm._debug:  # check merge precondition

        def is_object(m: ModelType) -> bool:  # NOTE "+" is allowed
            return isinstance(m, dict) and not ("@" in m or "|" in m or "^" in m or "&" in m)

        def merge_on_objects(model: ModelType, path: ModelPath) -> bool:
            if isinstance(model, dict) and "+" in model:
                assert isinstance(plus := model["+"], list)  # sanity
                return all(map(is_object, plus))
            return True

        assert analyze.check(jm, merge_on_objects, "only objects under +")

    _mergeObjects(jm)

    if jm._debug:
        assert analyze.check(jm, lambda m, _: not isinstance(m, dict) or "+" not in m)

def _get_prop_spec(prop: str, model: ModelObject) -> str|None:
    """Return actual property specification in object model."""
    assert not prop or prop[0] == "_", f"property name: {prop}"
    name = prop[1:]
    for p in (prop, "?" + name, "!" + name, name):
        if p in model:
            return p
    raise OperatorError(f"cannot find property {prop}")

def _regex_prefix(regex: str) -> str:
    """Extract a regular expression string prefix from regex.

    This objective is to be able to prove that regex match distinct strings.
    """
    assert regex and regex[0] == "/", f"is a regex: {regex}"
    prefix, regex = "", regex.rsplit("/", 1)[0]
    if regex.startswith("/^"):
        i = 2
        while i < len(regex):
            if regex[i] == "\\":
                i += 1
                prefix += regex[i]
            elif regex[i] not in "^$([*+?.{":
                prefix += regex[i]
            else:
                break
            i += 1
    return prefix

def _prefixes_and_strings(props: list[str]) -> tuple[list[str], list[str], list[str]]:
    """Separate regex prefixes and property names for further comparisons."""
    prefixes, regexes, names = [], [], []
    for prop in props:
        if prop == "":
            pass
        elif prop[0] == "_":
            names.append(prop[1:])
        elif prop[0] == "/":
            prefixes.append(_regex_prefix(prop))
            regexes.append(prop)
        else:
            raise ModelError(f"unexpected property name: {prop}")
    return prefixes, regexes, names

def _prefix_of(p: str, ls: list[str]) -> bool:
    """Whether prefix p appears in ls."""
    return any(s.startswith(p) for s in ls)

def _prefix_in(lp: list[str]) -> bool:
    """Whether prefixes overlap."""
    # log.debug(f"_prefix_in: {lp}")
    for i, p in enumerate(lp):
        for j, q in enumerate(lp):
            if i != j:
                if p.startswith(q) or q.startswith(p):
                    return True
    return False

def _intersectable(lp1: list[str], lp2: list[str]) -> bool:
    """Whether properties can be intersected, i.e. no cross interactions."""
    p1, r1, n1 = _prefixes_and_strings(lp1)
    p2, r2, n2 = _prefixes_and_strings(lp2)
    if not p1 and not p2:
        return True
    log.debug(f"intersectable: p1={p1} n1={n1}")
    log.debug(f"intersectable: p2={p2} n2={n2}")
    # interactions with names
    # TODO use the regex instead of the prefix?
    if any(_prefix_of(p, n2) for p in p1) or any(_prefix_of(p, n1) for p in p2):
        return False
    # interactions between prefixes for distinct regex
    # TODO regex normalization?
    if (any(r1[i] not in r2 and _prefix_of(p, p2) for i, p in enumerate(p1)) or
        any(r2[i] not in r1 and _prefix_of(p, p1) for i, p in enumerate(p2))):
        return False
    # interactions within prefixes
    if _prefix_in(p1) or _prefix_in(p2):
        return False
    # no interaction found!
    return True

def _and(m1: ModelType, m2: ModelType) -> ModelType:
    land = []
    if isinstance(m1, dict) and "&" in m1:
        land += m1["@"]
    else:
        land.append(m1)
    if isinstance(m2, dict) and "&" in m2:
        land += m2["@"]
    else:
        land.append(m2)
    return { "&": land }

def _is_prop(p: str) -> bool:
    """Whether p is about properties, not a special key."""
    return (p == "" or p[0] in "?_!/" or
            p not in ("#", "$", "~", "@", "%", "&", "|", "+", "^") and p[0] not in "!<>=")

# NOTE this is partially redundant with other operators
def intersect(
            jm: JsonModel,
            m1: ModelType, m2: ModelType,
            path1: ModelPath, path2: ModelPath,
            strict: bool = True,
        ) -> ModelType:
    """Create a model/object intersection, if possible: &(m1, m2).

    Raise an exception if this cannot be done.

    It could always return &(m1, m2), but that is not the point.
    """
    log.debug(f"AC in: m1={m1} m2={m2}")
    # resolve reference, which leads to inlining if property merging proceeds
    if isinstance(m1, str) and m1 and m1[0] == "$" and m1 not in MODEL_PREDEFS:
        m1 = jm.resolveRef(m1, path1)._model
    if isinstance(m2, str) and m2 and m2[0] == "$" and m2 not in MODEL_PREDEFS:
        m2 = jm.resolveRef(m2, path2)._model
    # various shortcuts
    if m1 == m2:
        return m1
    if m1 in ("$NONE", "$ANY"):
        return m2 if m1 == "$ANY" else m1
    if m2 in ("$NONE", "$ANY"):
        return m1 if m2 == "$ANY" else m2
    # final type compatibility
    t1, t1t = model_type(m1, path1)
    t2, t2t = model_type(m2, path2)
    if t1 and t2:
        if t1t is not t2t:
            return "$NONE"
        # else same final type
    elif strict:
        raise OperatorError("cannot intersect models: unknown final type")
    else:
        # FIXME extracts side stuff
        return _and(m1, m2)
    # same type, simplify on base models
    if is_base_model(m1):
        return m2
    elif is_base_model(m2):
        return m1
    # type strict inclusions
    # TODO loose ints/floats?
    if t1t is int:
        mm, mM = min(m1, m2), max(m1, m2)
        if mm == -1 and mM in (0, 1):
            return mM
        elif mm == 0 and mM == 1:
            return 1
    if t1t is float:
        mm, mM = min(m1, m2), max(m1, m2)
        if mm == -1.0 and mM in (0.0, 1.0):
            return mM
        elif mm == 0.0 and mM == 1.0:
            return 1.0
    # TODO str? others?
    # constants compatibility
    if t1t in (None, int, bool, float, str):
        c1, c1v = constant_value(m1, path1)
        c2, c2v = constant_value(m2, path2)
        if c1 and c2:
            return m1 if c1v == c2v else "$NONE"
        elif c1 and is_base_model(m2):
            return m1
        elif c2 and is_base_model(m1):
            return m2
        # else cannot conclude simply on constants
        # TODO $NONE for &("=-42", 0)
        # TODO investigate further, eg constant is compatible or not with constraints…
    if type(m1) is not type(m2):
        raise OperatorError("cannot intersect models: distinct base types")
    # recurse on list or tuple
    if isinstance(m1, list) and len(m1) == len(m2):
        return [
            intersect(jm, m1[i], m2[i], path1 + [ i ], path2 + [i], strict)
                for i in range(len(m1))
        ]
    # object
    if not isinstance(m1, dict):
        if strict:
            raise OperatorError("cannot intersect models: not an object")
        return _and(m1, m2)
    # probably useless explicit close cleanup
    if m1.get("", "") == "$NONE":
        del m1[""]
    if m2.get("", "") == "$NONE":
        del m2[""]
    m1_open, m2_open = "" in m1, "" in m2
    # for now, we can only handle open or close objects
    if m1_open and m1[""] != "$ANY" or m2_open and m2[""] != "$ANY":
        # special case if no other props
        m1_props, m2_props = list(filter(_is_prop, m1)), list(filter(_is_prop, m2))
        if m1_open and m1[""] != "$ANY" and len(m1_props) == 1:
            target, is_m1 = m1[""], True
        elif m2_open and m2[""] != "$ANY" and len(m2_props) == 1:
            target, is_m1 = m2[""], False
        else:
            target, is_m1 = None, None
        if target is not None:
            # apply restriction to all models
            m = copy.deepcopy(m2 if is_m1 else m1)
            props = m2_props if is_m1 else m1_props
            path, path0 = path2 if is_m1 else path1, path1 if is_m1 else path2
            for p in props:
                m[p] = intersect(jm, target, m[p], path0 + [""], path + [p], False)
            return m
        # else we give up
        # TODO handle more cases
        if strict:
            raise OperatorError("cannot intersect models: constrained default prop")
        return _and(m1, m2)
    # get properties
    o1, o2 = simple_object(m1, jm, path1), simple_object(m2, jm, path2)
    if o1 is None or o2 is None:
        if strict:
            raise OperatorError("cannot intersect models: not simple objects")
        return _and(m1, m2)
    if not _intersectable(o1, o2):
        if strict:
            raise OperatorError("cannot intersect models: regex props")
        return _and(m1, m2)
    # has regex prop
    r1 = any(s.startswith("/") for s in o1)
    r2 = any(s.startswith("/") for s in o2)
    # actual property merge
    inter = {}
    # open/close object?
    both_closed = not m1_open and not m2_open
    # {"a": 1, "?b": 1, "": "$ANY"} & {"?a": "$ANY", "c": 1, "?d": 1}
    # actual property combinations, that we know are **distinguishable**
    for p1 in o1:
        if p1 == "":
            continue
        if p1[0] == "/":
            if p1 in m2:  # same regex on both sides
                inter[p1] = intersect(jm, m1[p1], m2[p1], path1 + [p1], path2 + [p1], False)
            elif both_closed or m1_open and not m2_open:
                pass
            else:  # both open
                inter[p1] = m1[p1]
            continue
        # else process a name
        rp1 = _get_prop_spec(p1, m1)
        if p1 in o2:
            # name appears on both side
            rp2 = _get_prop_spec(p1, m2)
            if rp1[0] == "?" and rp2[0] == "?":  # keep optional
                inter[rp1] = intersect(jm, m1[rp1], m2[rp2], path1 + [rp1], path2 + [rp2], False)
            else:  # all mandatory
                inter[p1] = intersect(jm, m1[rp1], m2[rp2], path1 + [rp1], path2 + [rp2], False)
        else:
            if rp1[0] == "?":  # optional
                if m2_open:
                    inter[rp1] = m1[rp1]
                # else drop
            else:  # mandatory
                if m2_open:
                    inter[rp1] = m1[rp1]
                else:  # mandatory prop cannot fit in m2
                    return "$NONE"
    for p2 in o2:
        if p2 == "":
            continue
        if p2[0] == "/":
            if both_closed or m2_open and not m1_open:
                pass
            else:  # m1 is open
                inter[p2] = m2[p2]
            continue
        rp2 = _get_prop_spec(p2, m2)
        if p2 in o1:
            # already processed in previous book
            pass
        else:
            if rp2[0] == "?":  # optional
                if m1_open:
                    inter[rp2] = m2[rp2]
                # else drop
            else:  # mandatory
                if m1_open:
                    inter[rp2] = m2[rp2]
                else:  # mandatory prop cannot fit in m1
                    return "$NONE"
    # add default in the end
    if m1_open and m2_open:
        inter[""] = "$ANY"
    return inter
