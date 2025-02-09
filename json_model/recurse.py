# recurse on models in a JSON Model
from typing import Callable  # callable?
from .utils import ModelType

ModelPath = list[str|int]
ModelFilter = Callable[[ModelType, ModelPath], bool]
ModelRewrite = Callable[[ModelType, ModelPath], ModelType]

NO_MODEL_KEYWORDS = {"#", "%", "=", "!=", "<", "<=", ">", ">=", "!"}
MODEL_LIST_KEYWORDS = {"|", "&", "^", "+"}


def _recModel(
        model: ModelType,
        path: ModelPath,
        flt: ModelFilter,
        rwt: ModelRewrite
    ) -> ModelType:

    if not flt(model, path):
        return model

    # actual recursion
    if isinstance(model, list):
        return [_recModel(m, path + [i], flt, rwt)
                for i, m in enumerate(model)]
    elif isinstance(model, dict):
        for prop, val in model.items():
            if prop in NO_MODEL_KEYWORDS:
                if prop == "%":
                    assert len(path) == 1
                continue
            elif prop in MODEL_LIST_KEYWORDS:
                assert isinstance(val, list)  # sanity check in passing
                model[prop] = _recModel(val, path + [prop], flt, rwt)
            else:
                # assume properties or "@"
                assert len(prop) > 0
                pname = prop[1:] if prop[0] in ("_", "?", ":") else prop
                model[prop] = _recModel(val, path + [pname], flt, rwt)
    else:  # sanity check
        assert model is None or isinstance(model, (bool, int, float, str))

    return rwt(model, path)


def recModel(
        model: ModelType,
        flt: ModelFilter = lambda _m, _p: True,
        rwt: ModelRewrite = lambda m, _p: m
    ) -> ModelType:

    model = _recModel(model, ["$"], flt, rwt)

    return model
