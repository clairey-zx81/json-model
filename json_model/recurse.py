#
# Generic recursion on models in a JSON Model
#
# TODO multi recurse?
# TODO allow extending the parameterization
#
from .mtypes import ModelType, ModelPath, ModelFilter, ModelRewrite, ModelError
from .utils import log, is_obj_model

ROOT_KEYWORDS = {"~", "$", "%"}
# .mo and .in are extensions
ANYWHERE_KEYWORDS = {"#", ".schema"}
CONSTRAINT_KEYWORDS = {"=", "!=", "<", "<=", ">", ">=", "!", ".mo", ".in"}
NO_MODEL_KEYWORDS = ANYWHERE_KEYWORDS | CONSTRAINT_KEYWORDS | {"~", "/"}
MODEL_KEYWORD = {"@"}
# "/" expects a list, but we do not want to recurse there
MODEL_LIST_KEYWORDS = {"|", "&", "^", "+"}
MODEL_VALUE_KEYWORDS = {"$", "%", "*"}

ALL_KEYWORDS = NO_MODEL_KEYWORDS | MODEL_KEYWORD | MODEL_LIST_KEYWORDS | MODEL_VALUE_KEYWORDS

def _recModel(
        model: ModelType,
        path: ModelPath,
        flt: ModelFilter,
        rwt: ModelRewrite,
        keys: bool,
        root: bool,
    ) -> ModelType:

    if not flt(model, path):
        return model

    # actual recursion
    if isinstance(model, list):
        return rwt([_recModel(m, path + [i], flt, rwt, keys, False) for i, m in enumerate(model)], path)
    elif isinstance(model, dict):
        mkeys: list[str] = list(model.keys())
        for prop in mkeys:
            val = model[prop]
            lpath = path + [prop]
            assert isinstance(prop, str), f"properties are strings {lpath}"
            if prop in MODEL_KEYWORD:
                okprops = {prop} | ANYWHERE_KEYWORDS | CONSTRAINT_KEYWORDS
                if root:
                    okprops.update(ROOT_KEYWORDS)
                assert is_obj_model(model, okprops), f"@ restricts other keywords {lpath}"
                model[prop] = _recModel(val, lpath, flt, rwt, keys, False)
            elif prop in NO_MODEL_KEYWORDS:
                # some sanity checks in passing
                if prop == "#":
                    assert isinstance(val, str), f"# is a string {lpath}"
                elif prop == "~":
                    assert root and isinstance(val, str), f"~ is a string at root {lpath}"
                elif prop == "!":
                    assert isinstance(val, bool), f"! is a bool {lpath}"
                elif prop == "/":
                    assert isinstance(val, list), f"/ is a list {lpath}"
                continue
            elif prop in MODEL_LIST_KEYWORDS:
                assert isinstance(val, list), f"{prop} is a list {lpath}"
                model[prop] = _recModel(val, lpath, flt, rwt, keys, False)
                okprops = {prop, "#"}
                if root:
                    okprops.update(ROOT_KEYWORDS)
                assert is_obj_model(model, okprops), f"{prop} restricts other keywords {lpath}"
            elif prop == "%":  # renames and rewrites
                assert root and isinstance(val, dict), f"% transformations at root {lpath}"
                for k, v in val.items():
                    assert isinstance(k, str), f"% props are strings {lpath}"
                    if k == "#":
                        assert isinstance(v, str), f"# is a string {lpath}"
                    elif k == "<":
                        is_ref = lambda s: isinstance(s, str) and s and s[0] == "$"
                        assert is_ref(v) or isinstance(v, list) and all(map(is_ref, v)), \
                            "%.< is a reference or list of references"
                    elif k.startswith("."):  # rename
                        assert isinstance(v, str), f"rename to a string {lpath + [k]}"
                        assert v in ALL_KEYWORDS, f"rename to a valid keyword {lpath + [k]}"
                    else:  # rewrite
                        # FIXME recurse or not?
                        # model[k] = _recModel(v, path + ["%", k], flt, rwt)
                        continue
            elif prop in MODEL_VALUE_KEYWORDS:
                if prop == "$":
                    assert root and isinstance(val, dict), f"$ definitions at root {lpath}"
                model[prop] = _recModel(val, lpath, flt, rwt, keys, False)
            else:  # assume properties
                model[prop] = _recModel(val, lpath, flt, rwt, keys, False)
            if keys:  # possibly rewrite key references
                if prop != "" and prop[0] == "$":
                    log.debug(f"### considering key ref {prop}")
                    nprop = _recModel(prop, lpath, flt, rwt, keys, False)
                    log.debug(f"nprop={nprop}")
                    assert isinstance(nprop, str)
                    # substitution to an optional string
                    if nprop and nprop[0] not in ("$", "/", "="):
                        nprop = "?" + (nprop[1:] if nprop[0] == "_" else nprop)
                    if nprop != prop:
                        if nprop in model:
                            raise ModelError(f"cannot override key {prop}: {nprop} {lpath}")
                        model[nprop] = model[prop]
                        del model[prop]
    else:  # sanity check
        # FIXME could/should recurse on str?
        assert model is None or isinstance(model, (bool, int, float, str))

    return rwt(model, path)

def allFlt(_m: ModelType, _p: ModelPath) -> bool:
    return True

def builtFlt(m: ModelType, _p: ModelPath) -> bool:
    return isinstance(m, (list, dict))

def noRwt(m: ModelType, _p: ModelPath) -> ModelType:
    return m

def recModel(
        model: ModelType,
        flt: ModelFilter = lambda _m, _p: True,
        rwt: ModelRewrite = lambda m, _p: m,
        keys: bool = False,
        root: bool = True,
    ) -> ModelType:

    return _recModel(model, [], flt, rwt, keys, root)
