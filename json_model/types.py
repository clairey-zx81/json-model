from typing import Callable  # why not callable?

# JSON types
type JsonScalar = None|bool|int|float|str
type Jsonable = JsonScalar|list[Jsonable]|dict[str, Jsonable]
type JsonObject = dict[str, Jsonable]
type JsonArray = list[Jsonable]
type JsonPath = list[int|str]

type ValueType = Jsonable

# JSON Model Types
type ModelType = Jsonable
type ModelArray = JsonArray
type ModelObject = JsonObject
type ModelPath = JsonPath
type ModelDefs = dict[str, ModelType]
type ModelTrafo = dict[str, Jsonable]
type ModelRename = dict[str, str]
type ModelFilter = Callable[[ModelType, ModelPath], bool]
type ModelRewrite = Callable[[ModelType, ModelPath], ModelType]

type CheckFun = Callable[[ValueType, str], bool]
type KeyCheckFun = Callable[[str, ValueType, str], bool|None]
# FIXME remove None
type Compiler = Callable[[ModelType, str], CheckFun|None]

type ModelCheckFun = Callable[[ValueType, JsonPath], bool]

type JsonModel = typing.NewType("JsonModel", None)
type Symbols = dict[str, JsonModel]

class ModelError(BaseException):
    pass


# remove if not needed!
class UnknownModel:
    pass
