from typing import Callable
from collections.abc import MutableMapping, MutableSet
import datetime
import urllib.parse
import re  # FIXME re2?

from json_model.runtime.types import Jsonable, JsonScalar, Report, Path, CheckFun

# special undefined value
UNDEFINED: object = object()

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


#
# TYPED VALUES MANAGEMENT
#

class Const:
    """A constant holder suitable for set/dict, with a stricly typed comparison.

    The point is to avoid 1 == 1.0 == True, 0 == 0.0 == False, n == n.0
    """

    def __init__(self, val: JsonScalar):
        self._val = val

    def __hash__(self):
        return hash(self._val)

    def __eq__(self, val):
        return (
            isinstance(val, Const) and
            type(self._val) is type(val._val) and
            self._val == val._val
        )


class ConstSet(MutableSet[JsonScalar]):
    """A set of constants, with strictly typed comparisons."""

    def __init__(self, init: list[JsonScalar]|str|None = None):
        self._set: set[Const] = set()
        if init:
            for item in init:
                self.add(item)

    def __len__(self):
        return len(self._set)

    def __iter__(self):
        return [ item._val for item in self._set ]

    def __contains__(self, item):
        return Const(item) in self._set

    def add(self, item):
        self._set.add(Const(item))

    def discard(self, item):
        self._set.discard(Const(item))


class ConstMap(MutableMapping[JsonScalar, CheckFun]):
    """A mapping of constants to check functions."""

    def __init__(self):
        self._map: dict[Const, CheckFun] = {}

    def __setitem__(self, key, val):
        self._map[Const(key)] = val

    def __getitem__(self, key):
        if isinstance(key, (list, dict)):
            return UNDEFINED
        else:
            return self._map[Const(key)]

    def __delitem__(self, key):
        del self._map[Const(key)]

    def __iter__(self):
        return [ (k._val, v) for k, v in self._map.items() ]

    def __len__(self):
        return self._map.__len__()

#
# PREDEFS HELPERS
#

def is_valid_date(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            datetime.date.fromisoformat(value)
            return True
        except Exception as e:
            rep is None or rep.append(f"invalid date at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for date at {path}: {_tname(value)}")
    return False


def value_len(value: Jsonable, path: str) -> None|bool|int|float:
    match value:
        case str()|list()|dict():
            return len(value)
        case _:
            # FIXME should error out on None|bool?
            return value


_UUID_RE = r"(?i)^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"
_UUID_SEARCH = re.compile(_UUID_RE).search

def is_valid_uuid(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        if _UUID_SEARCH(value) is not None:
            return True
        else:
            rep is None or rep.append(f"str not an uuid at {path}")
            return False
    else:
        rep is None or rep.append(f"incompatible type for uuid at {path}: {_tname(value)}")
        return False


def is_valid_url(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            urllib.parse.urlparse(value)
            return True
        except Exception as e:
            rep is None or rep.append(f"invalid url at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for url at {path}: {_tname(value)}")
    return False


def is_valid_regex(value: Jsonable, path: str, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            re.compile(value)
            return True
        except Exception as e:
            rep is None or rep.append(f"regex compile error at {path}: {value} ({e})")
            return False
    rep is None or rep.append(f"incompatible type for regex at {path}: {_tname(value)}")
    return False


def main(jm_fun, jm_map, jmc_version):
    """Possibly run as a script: $0 values..."""

    import json
    import sys
    import argparse
    import logging

    logging.basicConfig()
    log = logging.getLogger("checker")

    ap = argparse.ArgumentParser()
    ap.add_argument("--debug", "-d", action="store_true", help="set verbose mode")
    ap.add_argument("--name", "-n", default="", help="select model by name")
    ap.add_argument("--list", "-l", action="store_true", help="show available model names and exit")
    ap.add_argument("--version", "-v", action="store_true", help="show JSON Model compiler version")
    ap.add_argument("--report", "-r", action="store_true", help="show error locations on failure")
    ap.add_argument("--test", "-t", action="store_true", help="assume test vector JSON files")
    ap.add_argument("values", nargs="*", help="JSON files")
    args = ap.parse_args()

    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    if args.list:
        print(f"JSON Models (empty for root):{' '.join(sorted(jm_map.keys()))}")
        sys.exit(0)
    if args.version:
        print(f"Python from JSON Model compiler version {jmc_version}")
        sys.exit(0)

    try:
        checker: CheckFun = jm_fun(args.name)
    except Exception as e:
        log.debug(e, exc_info=args.debug)
        log.error(f"error on model for {args.name}: {e}")
        sys.exit(1)

    for fn in args.values:
        try:
            with open(fn) as f:
                value = json.load(f)
            values = value if args.test else [ [ None, value ] ]
            for i, (expect, val) in enumerate(values):
                info = "" if expect is None else f"[{i}]"
                reasons = [] if args.report else None
                path = [] if args.report else None
                valid = checker(val, path, reasons)
                if expect is not None and valid != expect:
                    print(f"{fn}{info}: ERROR unexpected {'PASS' if expect else 'FAIL'}")
                elif valid:
                    print(f"{fn}{info}: PASS")
                elif reasons:
                    print(f"{fn}{info}: FAIL {reasons}")
                else:
                    print(f"{fn}{info}: FAIL")
        except Exception as e:
            log.debug(e, exc_info=args.debug)
            print(f"{fn}: ERROR ({e})")
