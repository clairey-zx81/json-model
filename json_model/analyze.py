#
# Analyses
#
import re

from .mtypes import ModelPath, ModelType, ModelFilter
from .utils import log, CONST_RE, is_regex
from .recurse import recModel, allFlt, noRwt
from .model import JsonModel

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
            log.error(e, exc_info=jm._debug)
            is_valid = False
            if jm._debug:
                raise

    # TODO also check other instances?!

    return is_valid
