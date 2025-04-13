from typing import Any, Callable  # why not callable?

# JSON types
type JsonScalar = None|bool|int|float|str
type Jsonable = JsonScalar|list[Jsonable]|dict[str, Jsonable]
type JsonObject = dict[str, Jsonable]
type JsonArray = list[Jsonable]
type JsonPath = list[int|str]

type ValueType = Jsonable

# JSON Model Types
type ModelType = Jsonable
type ModelPath = JsonPath
type ModelDefs = dict[str, ModelType]
type ModelTrafo = dict[str, Jsonable]
type ModelRename = dict[str, str]
type ModelFilter = Callable[[ModelType, ModelPath], bool]
type ModelRewrite = Callable[[ModelType, ModelPath], ModelType]

type CheckFun = Callable[[Any, str], bool]
type KeyCheckFun = Callable[[str, Any, str], bool|None]
type Compiler = Callable[[ModelType, str], CheckFun|None]


class ModelError(BaseException):
    pass


# remove if not needed!
class UnknownModel:
    pass
