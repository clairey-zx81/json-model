from typing import Callable
import datetime
import urllib.parse

type Jsonable = None|bool|int|float|str|list[Jsonable]|dict[str, Jsonable]

# NOTE path and report are None if no information is collected
type Path = list[int|str]|None
type Report = list[str]|None

type CheckFun = Callable[[Jsonable, Path, Report], bool]
type RegexFun = Callable[[str], bool]
type PropMap = dict[str, CheckFun]
type TagMap = dict[None|bool|float|int|str, CheckFun]

# call initialize only once
initialized: bool = False

# map model names to check functions
_check_model_map_size: int
_check_model_map: PropMap

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

def CHECK_FUNCTION_NAME_fun(name: str) -> CheckFun:
    """Return check function for JSON model name."""
    return _check_model_map[name]

# entry point for generated checkers
def CHECK_FUNCTION_NAME(val: Jsonable, name: str = "", rep: Report = None) -> bool:
    """Check val validity agains JSON Model name."""
    if name not in _check_model_map:
        raise Exception(f"unexpected model name: {name}")
    checker = _check_model_map[name]
    return checker(val, [], rep)
