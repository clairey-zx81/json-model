#
# type declarations for python jm runtime
#
type JsonScalar = None|bool|int|float|str
type Jsonable = JsonScalar|list[Jsonable]|dict[str, Jsonable]

type Path = list[int|str]|None
type Report = list[str]|None

type CheckFun = Callable[[Jsonable, Path, Report], bool]
type RegexFun = Callable[[str], bool]
type PropMap = dict[str, CheckFun]
