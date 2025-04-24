#
# Generic recursion on models in a JSON Model
#
# TODO multi recurse?
#
from .types import ModelType, ModelPath, ModelFilter, ModelRewrite

ROOT_KEYWORDS = {"~", "$", "%"}
CONSTRAINT_KEYWORDS = {"=", "!=", "<", "<=", ">", ">=", "!"}
NO_MODEL_KEYWORDS = {"#", "~", "/"} | CONSTRAINT_KEYWORDS
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
        return [_recModel(m, path + [i], flt, rwt, keys, False) for i, m in enumerate(model)]
    elif isinstance(model, dict):
        keys = list(model.keys())
        for prop in keys:
            val = model[prop]
            assert isinstance(prop, str)
            if prop in MODEL_KEYWORD:
                okprops = {prop, "#"} | CONSTRAINT_KEYWORDS
                if root:
                    okprops.update(ROOT_KEYWORDS)
                assert not (set(keys) - okprops), "@ restricts other keywords"
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys, False)
            elif prop in NO_MODEL_KEYWORDS:
                # some sanity checks in passing
                if prop == "#":
                    assert isinstance(val, str), "# is a string"
                elif prop == "~":
                    assert root and isinstance(val, str), "~ is a string at root"
                elif prop == "!":
                    assert isinstance(val, bool), "! is a bool"
                elif prop == "/":
                    assert isinstance(val, list), "/ is a list"
                continue
            elif prop in MODEL_LIST_KEYWORDS:
                assert isinstance(val, list)  # sanity check in passing
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys, False)
                okprops = {prop, "#"}
                if root:
                    okprops.update(ROOT_KEYWORDS)
                assert not (set(keys) - okprops), f"{prop} restricts other keywords"
            elif prop == "%":  # renames and rewrites
                assert root and isinstance(val, dict), "% transformations at root"
                for k, v in val.items():
                    assert isinstance(k, str), "props are strings"
                    if k == "#":
                        assert isinstance(v, str), "# is a string"
                    elif k.startswith("."):  # rename
                        assert isinstance(v, str), "rename to a string"
                        assert v in ALL_KEYWORDS, "rename to a valid keyword"
                    else:  # rewrite
                        # FIXME recurse or not?
                        # model[k] = _recModel(v, path + ["%", k], flt, rwt)
                        continue
            elif prop in MODEL_VALUE_KEYWORDS:
                if prop == "$":
                    assert root and isinstance(val, dict), "$ definitions at root"
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys, False)
            else:  # assume properties
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys, False)
            if keys:  # possibly rewrite key references
                if prop != "" and prop[0] == "$":
                    nprop = _recModel(prop, path + [prop], flt, rwt, keys, False)
                    if nprop != prop:
                        if nprop in model:
                            raise ModelError(f"cannot override rewritten key {prop}: {nprop}")
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
