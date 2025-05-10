from typing import Callable
import datetime
import urllib.parse

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]
type Path = list[int|str]|None
type Report = list[str]|None
type CheckFun = Callable[[Jsonable, Path, Report], bool]
type RegexFun = Callable[[str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# call initialize only once
initialized: bool = False

# extract type name
def _tname(value: Jsonable) -> str:
    return type(value).__name__

# maybe add message to report
def _rep(msg: str, rep: Report) -> bool:
    rep is None or rep.append(msg)
    return False

# generate path for display
# TODO add appropriate escaping…
def _path(path: Path) -> str:
    return ".".join(str(i) for i in path)
