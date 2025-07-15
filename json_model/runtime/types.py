#
# type declarations for python jm runtime
#
from typing import Callable

type JsonScalar = None|bool|int|float|str
type Jsonable = JsonScalar|list[Jsonable]|dict[str, Jsonable]

type Path = list[int|str]|None
type Report = list[tuple[str, Path]]|None

type CheckFun = Callable[[Jsonable, Path, Report], bool]
type RegexFun = Callable[[str, Path, Report], bool]
type PropMap = dict[str, CheckFun]

type EntryCheckFun = Callable[[Jsonable, str, Report], bool]
