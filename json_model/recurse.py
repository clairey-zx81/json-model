#
# Generic recursion on models in a JSON Model
#
# TODO options about re?
#
from .types import ModelType, ModelPath, ModelFilter, ModelRewrite

NO_MODEL_KEYWORDS = {"#", "~", "=", "!=", "<", "<=", ">", ">=", "!", "/"}
MODEL_KEYWORDS = {"@"}
# "/" expects a list, but we do not want to recurse there
MODEL_LIST_KEYWORDS = {"|", "&", "^", "+"}
MODEL_VALUE_KEYWORDS = {"$", "%", "*"}

def _recModel(
        model: ModelType,
        path: ModelPath,
        flt: ModelFilter,
        rwt: ModelRewrite,
        keys: bool,
    ) -> ModelType:

    if not flt(model, path):
        return model

    # actual recursion
    if isinstance(model, list):
        return [_recModel(m, path + [i], flt, rwt, keys) for i, m in enumerate(model)]
    elif isinstance(model, dict):
        for prop in list(model.keys()):
            val = model[prop]
            assert isinstance(prop, str)
            if prop in NO_MODEL_KEYWORDS:
                # sanity checks in passing
                if prop in ("#", "~"):
                    assert isinstance(val, str)
                elif prop in ("!"):
                    assert isinstance(val, bool)
                elif prop in ("/"):
                    assert isinstance(val, list)
                continue
            elif prop in MODEL_LIST_KEYWORDS:
                assert isinstance(val, list)  # sanity check in passing
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys)
            elif prop == "%":  # renames and rewrites
                assert isinstance(val, dict)
                for k, v in val.items():
                    assert isinstance(k, str)
                    if k == "#":
                        assert isinstance(v, str)
                        continue
                    elif k.startswith("."):  # rename
                        assert isinstance(v, str)
                        continue
                    else:  # rewrite
                        # FIXME recurse or not?
                        # model[k] = _recModel(v, path + ["%", k], flt, rwt)
                        continue
            elif prop in MODEL_VALUE_KEYWORDS:
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys)
            else:  # assume properties
                model[prop] = _recModel(val, path + [prop], flt, rwt, keys)
            if keys:  # possibly rewrite key references
                if prop != "" and prop[0] == "$":
                    nprop = _recModel(prop, path + [prop], flt, rwt, keys)
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
    ) -> ModelType:

    return _recModel(model, [], flt, rwt, keys)
