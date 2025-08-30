from collections.abc import MutableMapping, MutableSet
import datetime
import time
import validators
import json
import re  # FIXME re2?
import math

from json_model.runtime.types import Jsonable, JsonScalar, Report, Path, CheckFun

# special undefined value
def UNDEFINED(v, p, r):
    raise Exception("must not be called")

# extract type name
def _tname(value: Jsonable) -> str:
    return type(value).__name__

# maybe add message to report
def _rep(msg: str, rep: Report) -> bool:
    _ = rep is None or rep.append((msg, []))
    return False

# generate path for display
def _path(path: Path) -> str:
    """Show path as a JSON Path (RFC9535), with proper escaping when necessary."""
    if path is None:
        return ""

    def esc(item: str|int) -> str:
        if isinstance(item, int):
            return str(item)
        elif item.isidentifier():
            return item
        else:
            items = item.split("'")
            return "'" + "\\'".join(i.replace("\\", "\\\\") for i in items) + "'"

    return "." + ".".join(map(esc, path))

#
# TYPED VALUES MANAGEMENT
#
def typed_eq(v1: Jsonable, v2: Jsonable):
    if type(v1) is not type(v2):
        return False
    if v1 is None:
        return True
    elif isinstance(v1, (bool, int, float, str)):
        return v1 == v2
    elif isinstance(v1, list):
        return len(v1) == len(v2) and all(typed_eq(i1, i2) for i1, i2 in zip(v1, v2))  # pyright: ignore
    else:
        assert isinstance(v1, dict)
        if len(v1) != len(v2) or set(v1.keys()) != set(v2.keys()):  # type: ignore
            return False
        # same props, compare values
        return all(typed_eq(v1[p], v2[p]) for p in v1)  # pyright: ignore


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
        return map(lambda i: i._val, self._set)

    def __contains__(self, item):
        return Const(item) in self._set

    def add(self, value):
        self._set.add(Const(value))

    def discard(self, value):
        self._set.discard(Const(value))


class ConstMap(MutableMapping[JsonScalar, CheckFun]):
    """A mapping of constants to check functions."""

    def __init__(self):
        self._map: dict[Const, CheckFun] = {}

    def __setitem__(self, key, val):
        self._map[Const(key)] = val

    def __getitem__(self, key):
        if isinstance(key, (list, dict)):
            return UNDEFINED  # pyright: ignore
        else:
            return self._map[Const(key)]

    def __delitem__(self, key):
        del self._map[Const(key)]

    def __iter__(self):
        return map(lambda k: k._val, self._map)

    def __len__(self):
        return self._map.__len__()

#
# PREDEFS HELPERS
#

def is_valid_date(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            datetime.date.fromisoformat(value)
            return True
        except Exception as e:
            _ = rep is None or rep.append((f"invalid date {value} ({e})", path))
            return False
    _ = rep is None or rep.append((f"incompatible type {_tname(value)} for date", path))
    return False


def is_valid_time(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            datetime.time.fromisoformat(value)
            return True
        except Exception as e:
            _ = rep is None or rep.append((f"invalid time {value} ({e})", path))
            return False
    _ = rep is None or rep.append((f"incompatible type {_tname(value)} for time", path))
    return False


def is_valid_datetime(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            datetime.datetime.fromisoformat(value)
            return True
        except Exception as e:
            _ = rep is None or rep.append((f"invalid datetime {value} ({e})", path))
            return False
    _ = rep is None or rep.append((f"incompatible type {_tname(value)} for datetime", path))
    return False


def value_len(value: Jsonable, path: Path) -> None|bool|int|float:
    match value:
        case str()|list()|dict():
            return len(value)
        case _:
            # FIXME should error out on None|bool?
            return value


_UUID_RE = r"(?i)^[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}$"
_UUID_SEARCH = re.compile(_UUID_RE).search

def is_valid_uuid(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        if _UUID_SEARCH(value) is not None:
            return True
        else:
            _ = rep is None or rep.append((f"str not an uuid {value}", path))
            return False
    else:
        _ = rep is None or rep.append((f"incompatible type {_tname(value)} for uuid", path))
        return False


def is_valid_url(value: Jsonable, path: Path, rep: Report = None) -> bool:
    # NOTE urllib.parse accepts any garbage…
    # NOTE simple_host required to accept "localhost"
    # FIXME file:// is not a url…
    valid = isinstance(value, str) and validators.url(value, simple_host=True) is True
    if not valid:
        _ = rep is None or rep.append((f"invalid url {value}", path))
    return valid


def is_valid_email(value: Jsonable, path: Path, rep: Report = None) -> bool:
    valid = isinstance(value, str) and validators.email(value) is True
    if not valid:
        _ = rep is None or rep.append((f"invalid email {value}", path))
    return valid


def is_valid_json(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            json.loads(value)
            return True
        except Exception:
            _ = rep is None or rep.append(("invalid json string", path))
            return False
    _ = rep is None or rep.append((f"incompatible type for json: {_tname(value)}", path))
    return False


# quite inefficient but safe
def is_valid_regex(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        try:
            re.compile(value)
            return True
        except Exception as e:
            _ = rep is None or rep.append((f"regex {value} compile error ({e})", path))
            return False
    # other types cannot be valid regex
    _ = rep is None or rep.append((f"incompatible type for regex: {_tname(value)}", path))
    return False


# extension: accept inlined reference syntax ($FOO:...)
def is_valid_exreg(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, str):
        # remplace references with named subpattern
        count = 0
        def repl(_):
            nonlocal count
            count += 1
            return f"(P<x{count}>"
        value = re.sub(r"\(\$\w+", repl, value)
    return is_valid_regex(value, path, rep)


def is_unique_array(value: Jsonable, path: Path, rep: Report = None) -> bool:
    if isinstance(value, list):
        # that costs but works in all cases…
        unique = len(set(json.dumps(i, sort_keys=True) for i in value)) == len(value)
        if not unique:
            _ = rep is None or rep.append(("non unique array", path))
        return unique
    # other types cannot be unique
    _ = rep is None or rep.append(("non array for unique", path))
    return False

def check_constraint(value: Jsonable, op: str, cst: int|float|str, path: Path, rep: Report) -> bool:
    if value is None or isinstance(value, bool):
        _ = rep is None or \
            rep.append((f"unexpected type {_tname(value)} for {op} constraint", path))
    # get comparison value depending on constant cst type
    if isinstance(cst, int):
        if isinstance(value, (str, list, dict)):
            cval = len(value)
        elif isinstance(value, (int, float)):
            cval = value
        else:
            _ = rep is None or \
                rep.append((f"unexpected type {_tname(value)} for {op} int constraint", path))
            return False
    elif isinstance(cst, float):
        if isinstance(value, (int, float)):
            cval = value
        else:  # list, dict, str
            _ = rep is None or \
                rep.append((f"unexpected type {_tname(value)} for {op} float constraint", path))
            return False
    else:
        assert isinstance(cst, str)
        if isinstance(value, str):
            cval = value
        else:  # dict, list, int, float
            _ = rep is None or \
                rep.append((f"unexpected type {_tname(value)} for {op} str constraint", path))
            return False
    # actual comparison
    if op == "=":
        cmp = cval == cst
    elif op == "!=":
        cmp = cval != cst
    elif op == "<=":
        cmp = cval <= cst  # pyright: ignore
    elif op == "<":
        cmp = cval < cst  # pyright: ignore
    elif op == ">=":
        cmp = cval >= cst  # pyright: ignore
    elif op == ">":
        cmp = cval > cst  # pyright: ignore
    else:
        assert False, f"unexpected operator: {op}"
    if not cmp and rep is not None:
        rep.append((f"invalid {op} {cst} constraint", path))
    return cmp


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
    ap.add_argument("--name", "-n", default="",
                    help="select model by name, default is empty for root model")
    ap.add_argument("--list", "-l", action="store_true", help="show available model names and exit")
    ap.add_argument("--version", "-v", action="store_true", help="show JSON Model compiler version")
    ap.add_argument("--report", "-r", default=False, action="store_true",
                    help="show error locations on failure")
    ap.add_argument("--no-report", dest="report", action="store_false",
                    help="no not show error locations on failure")
    ap.add_argument("--time", "-T", type=int, default=1, help="report performance measures")
    ap.add_argument("--test", "-t", action="store_true", help="assume test vector JSON files")
    ap.add_argument("--jsonl", "-L", action="store_true", default=False, help="assume JSONL files")
    ap.add_argument("--jsonschema-benchmark", action="store_true", default=False,
                    help="specific JSON Schema Benchmark run")
    ap.add_argument("values", nargs="*", help="JSON files")
    args = ap.parse_args()

    log.setLevel(logging.DEBUG if args.debug else logging.INFO)

    if args.list:
        print(f"JSON Models (empty for root):{' '.join(sorted(jm_map.keys()))}")
        sys.exit(0)
    if args.version:
        print(f"Python from JSON Model compiler version {jmc_version}")
        sys.exit(0)
    if args.jsonschema_benchmark:
        args.jsonl = True

    errors = 0

    for fn in args.values:

        try:
            # load json data
            if args.jsonl:
                with open(fn) as f:
                    values = [json.loads(r) for r in f]
            else:
                with open(fn) as f:
                    value = json.load(f)
                values = value if args.test else [ [ None, value ] ]

            # benckmarking
            if args.jsonschema_benchmark:

                checker = jm_fun(args.name)

                # cold run in µs
                cold_start = time.clock_gettime(time.CLOCK_REALTIME)
                for v in values:
                    if not checker(v, None, None):
                        errors += 1
                cold_delay = 1_000_000.0 * (time.clock_gettime(time.CLOCK_REALTIME) - cold_start)

                # more runs to trigger a potential JIT?
                # NOTE probaly useless: JIT should be triggered by previous loop
                for _ in range(min(20, int(10_000_000.0 / cold_delay))):
                    for v in values:
                        checker(v, None, None)

                # warm run in µs
                sum1, sum2 = 0.0, 0.0
                for _ in range(args.time):
                    start = time.clock_gettime(time.CLOCK_REALTIME)
                    for j in values:
                        checker(j, None, None)
                    delay = 1_000_000.0 * (time.clock_gettime(time.CLOCK_REALTIME) - start)
                    sum1 += delay
                    sum2 += delay * delay

                # result
                avg = sum1 / args.time
                stdev = math.sqrt( sum2 / args.time - avg * avg)
                print(f"py validation: pass={len(values)-errors} fail={errors} "
                      f"{avg:.03f} ± {stdev:.03f} µs", file=sys.stderr)

                # cold-run-ns,warm-run-ns
                print(f"{int(1000 * cold_delay)},{int(1000 * avg)}")
                sys.exit(1 if errors else 0)

            # else usual runs

            if args.jsonl:
                values = [[None, j] for j in values]

            index, item = 0, -1
            for tvect in values:
                item += 1

                if isinstance(tvect, str):  # ignore strings as comments
                    continue

                if not isinstance(tvect, list) or len(tvect) not in (2, 3):
                    log.error(f"unexpected test vector: {tvect}")
                    print("{fn}[{item}]: ERROR bad test vector")
                    errors += 1
                    continue

                if len(tvect) == 2:
                    expect, val = tvect
                    name = args.name
                else:
                    expect, name, val = tvect

                info = f"[{index+1}]" if args.jsonl else f"[{index}]" if args.test else ""

                try:
                    checker: CheckFun = jm_fun(name)
                except Exception as e:
                    log.debug(e, exc_info=args.debug)
                    log.error(f"no such model \"{name}\": {e}")
                    print(f"{fn}{info}: ERROR unexpected name {name}")
                    errors += 1
                    continue

                valid: bool
                empty, sum1, sum2 = 0.0, 0.0, 0.0
                mode = "rep" if args.report else "nop"

                if args.time > 1:

                    # evaluate average overhead
                    for _ in range(args.time - 1):
                        start = time.clock_gettime(0)
                        end = time.clock_gettime(0)
                        empty += 1000000.0 * (end - start)
                    empty /= args.time

                    # evaluate validation time
                    if args.report:
                        for _ in range(args.time):
                            start = time.clock_gettime(0)
                            reasons, path = [], []
                            valid = checker(val, path, reasons)
                            del reasons
                            del path
                            end = time.clock_gettime(0)
                            delay = 1000000.0 * (end - start) - empty
                            sum1 += delay
                            sum2 += delay * delay
                    else:
                        for _ in range(args.time):
                            start = time.clock_gettime(0)
                            valid = checker(val, None, None)
                            end = time.clock_gettime(0)
                            delay = 1000000.0 * (end - start) - empty
                            sum1 += delay
                            sum2 += delay * delay

                    avg = sum1 / args.time
                    stdev = math.sqrt(sum2 / args.time - avg * avg)

                    result = "PASS" if valid else "FAIL"

                    print(f"{fn}{info} {mode} {result} "
                          f"{avg:.03f} ± {stdev:.03f} µs/call ({empty:.03f})",
                          file=sys.stderr)

                # collect results for actual display
                if args.report:
                    reasons, path = [], []
                    valid = checker(val, path, reasons)
                else:
                    reasons, path = None, None
                    valid = checker(val, None, None)

                result = "PASS" if valid else "FAIL"

                if expect is not None and valid != expect:
                    print(f"{fn}{info}: ERROR unexpected {result}")
                    errors += 1
                elif valid:
                    print(f"{fn}{info}: PASS")
                elif reasons:
                    msg = "; ".join(f"{_path(p)}: {m}" for m, p in reversed(reasons))
                    print(f"{fn}{info}: FAIL ({msg})")
                else:
                    print(f"{fn}{info}: FAIL")

                index += 1

        except Exception as e:
            log.debug(e, exc_info=args.debug)
            print(f"{fn}: ERROR ({e})")
            errors += 1

    sys.exit(1 if errors else 0)
