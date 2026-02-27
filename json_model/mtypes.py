import typing

# JSON types
type Number = int|float
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
type ModelTrafo = ModelType
type ModelRename = dict[str, str]
type ModelFilter = typing.Callable[[ModelType, ModelPath], bool]
type ModelRewrite = typing.Callable[[ModelType, ModelPath], ModelType]

type CheckFun = typing.Callable[[ValueType, str], bool]
type KeyCheckFun = typing.Callable[[str, ValueType, str], bool|None]
# FIXME remove None
type Compiler = typing.Callable[[ModelType, str], CheckFun|None]

type ModelCheckFun = typing.Callable[[ValueType, JsonPath], bool]

JsonModel = typing.NewType("JsonModel", None)
type Symbols = typing.MutableMapping[str, JsonModel]
type JsonSchema = bool|dict[str, Jsonable]
type TestHint = bool|None

# name
type Var = str

# typed expressions
type JsonExpr = str
type BoolExpr = str|bool
type IntExpr = str|int
type FloatExpr = str
type NumExpr = str|int
type StrExpr = str
type PathExpr = Var|str
type Expr = JsonExpr|BoolExpr|IntExpr|FloatExpr|NumExpr|StrExpr

type Block = list[str]

type Conditionals = list[tuple[BoolExpr, TestHint, Block]]
# del JsonModel

class ModelError(BaseException):
    pass


# remove if not needed!
class UnknownModel:
    pass
