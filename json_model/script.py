import os
import sys
import re
import json
import yaml
import logging
from importlib.metadata import version as pkg_version
from importlib.resources import files
import tempfile

from .mtypes import Jsonable, JsonSchema, ModelError
from .utils import log, tname
from .resolver import Resolver
from .model import JsonModel
from .xstatic import xstatic_compile
from . import optim, analyze, objmerge
from .runtime.types import EntryCheckFun, Report
from .runtime.support import _path as json_path


def process_model(model: JsonModel, *,
                  check: bool = True, merge: bool = True, optimize: bool = True,
                  debug: bool = False):
    """Apply necessary preprocessing to JsonModel."""

    # initial sanity check
    assert model._is_head and model._is_root and model._models

    all_models = list(sorted(model._models.values(), key=lambda m: m._id))

    if debug or check:
        for m in all_models:
            if not analyze.valid(m):
                raise ModelError(f"invalid initial model {m._id}")

    # simplify before merging
    if optimize:
        for m in all_models:
            optim.optimize(m)

    # check after initial optimize
    if debug or check:
        # log.debug(json.dumps(model.toJSON(), sort_keys=True, indent=2))
        for m in all_models:
            if not analyze.valid(m):
                raise ModelError(f"invalid optimized model {m._id}")

    # merge in reverse order to move alts up before inlining?!
    if merge:
        for m in reversed(all_models):
            objmerge.merge(m)

    # optimize again?
    if optimize:
        for m in all_models:
            optim.optimize(m)

    # check after merge & optimize
    if debug or check:
        for m in all_models:
            if not analyze.valid(m):
                raise ModelError(f"invalid merged model {m._id}")


def model_from_json(
        mjson: Jsonable, *, auto: bool = False,
        debug: bool = False, murl: str|None = None,
        check: bool = True, merge: bool = True, optimize: bool = True,
        resolver: Resolver|None = None) -> JsonModel:
    """JsonModel instanciation from JSON data."""

    if resolver is None:
        resolver = Resolver()

    # possibly add resolver mapping rule
    if auto and (isinstance(mjson, dict) and "$" in mjson and \
            isinstance(mjson["$"], dict) and "" in mjson["$"]):
        url = mjson["$"][""]
        assert isinstance(url, str), f".\"$\"."" expects a string: {tname(url)}"
        fn = re.sub(r"(\.model)?(\.js(on)?|\.yaml)?$", "", murl)  # drop suffix
        if debug:
            log.debug(f"url={url} fn={fn}")
        file = fn if "/" in fn else ("./" + fn)
        if fn != url and file != url and "/" in url:
            upref, uend = url.rsplit("/", 1)
            fpref, fend = file.rsplit("/", 1)
            if upref not in resolver._maps and uend == fend:
                log.info(f"auto adding url map: {upref} -> {fpref}")
                resolver._maps[upref] = fpref

    jm = JsonModel(mjson, resolver, murl, debug=debug)

    if check or merge or optimize:
        process_model(jm, check=check, merge=merge, optimize=optimize, debug=debug)

    return jm


def model_from_url(murl: str, *, auto: bool = False, debug: bool = False,
                   check: bool = True, merge: bool = True, optimize: bool = True,
                   resolver: Resolver|None = None, follow: bool = True) -> JsonModel:
    """JsonModel instanciation from a URL."""

    if resolver is None:
        resolver = Resolver()

    mjson = resolver(murl, follow=follow)

    return model_from_json(mjson, murl=murl, auto=auto, debug=debug, resolver=resolver)


def model_from_str(mstring: str, *, auto: bool = False,
                   check: bool = True, merge: bool = True, optimize: bool = True,
                   debug: bool = False, murl: str|None = None) -> JsonModel:
    """JsonModel instanciation from a string."""

    return model_from_json(json.loads(mstring), auto=auto, debug=debug, murl=murl,
                           check=check, merge=merge, optimize=optimize)


# it is unclear if this tricks actually works
def _model_checker(jm: JsonModel, *, debug: bool = False):
    code = xstatic_compile(jm, lang="py", debug=debug)
    env = {}
    exec(str(code), env)
    env["check_model_init"]()
    yield env["check_model"]
    env["check_model_free"]()


def model_checker(jm: JsonModel, *, debug: bool = False) -> EntryCheckFun:
    """Return an executable model checker from a JsonModel."""
    return next(_model_checker(jm, debug=debug))


def model_checker_from_json(
            mjson: Jsonable, *, auto: bool = False, debug: bool = False,
            resolver: Resolver|None = None,
        ) -> EntryCheckFun:
    """Return an executable model checker from a URL."""
    jm = model_from_json(mjson, auto=auto, debug=debug, resolver=resolver)
    return model_checker(jm, debug=debug)


def model_checker_from_url(
            murl: str, *, auto: bool = False, debug: bool = False,
            resolver: Resolver|None = None, follow: bool = True,
        ) -> EntryCheckFun:
    """Return an executable model checker from a URL."""
    jm = model_from_url(murl, auto=auto, debug=debug, resolver=resolver, follow=follow)
    return model_checker(jm, debug=debug)


def create_model(murl: str, resolver: Resolver, *,
                 auto: bool = False, follow: bool = True, debug: bool = False) -> JsonModel:
    """JsonModel instanciation without preprocessing."""
    return model_from_url(murl, auto=auto, follow=follow, debug=debug, resolver=resolver,
                          check=False, merge=False, optimize=False)

DEFAULT_CC = "cc"
DEFAULT_CFLAGS = "-Wall -Wno-address -Wno-c23-extensions -Wno-unused-variable -Wno-unused-function -Ofast"
DEFAULT_LDFLAGS = "-ljansson -lpcre2-8 -lm"

def clang_compile(c_code: str, args):
    """Generate an actual executable."""

    tmp_dir = os.environ.get("TMPDIR", "/dev/shm")

    # source files
    rt_dir = files("json_model.runtime")
    lib = rt_dir.joinpath("json-model.c")
    main = rt_dir.joinpath("main.c")

    # compiler setings
    env = os.environ.get
    cc = args.cc or env("CC", DEFAULT_CC)
    cflags = args.cflags or env("CFLAGS", DEFAULT_CFLAGS)
    cppflags = args.cppflags or f"-I{rt_dir} -DCHECK_FUNCTION_NAME=check_model"
    ldflags = args.ldflags or DEFAULT_LDFLAGS

    output = "a.out" if args.output == "-" else args.output

    with tempfile.NamedTemporaryFile(dir=tmp_dir, suffix=".c") as tmp:
        tmp.write(c_code.encode("UTF-8"))
        tmp.flush()
        status = os.system(f"{cc} {cppflags} {cflags} -o {output} {main} {lib} {tmp.name} {ldflags}")
        assert status == 0, "C compilation succeeded"

def jmc_script():

    import argparse

    logging.basicConfig()

    ap = argparse.ArgumentParser()
    arg = ap.add_argument

    # verbosity and checks
    arg("--version", action="store_true", help="show current version and exit")
    arg("--debug", "-d", action="store_true", help="set debugging mode")
    arg("--verbose", "-v", action="store_true", help="more verbose")
    arg("--quiet", "-q", dest="verbose", action="store_false", help="less verbose")

    # input options
    arg("--maps", "-m", action="append", default=[], help="URL mappings")
    arg("--auto", "-a", action="store_true", help="automatic URL mapping")

    # output options
    arg("--name", default="check_model", help="name of generated function")
    arg("--output", "-o", default="-", help="output file")
    arg("--sort", "-s", action="store_true", default=False, help="sorted JSON keys")
    arg("--no-sort", "-ns", dest="sort", action="store_false", help="unsorted JSON keys")
    arg("--indent", "-i", type=int, default=2, help="JSON indentation")
    arg("--code", action="store_true", default=None, help="show source code")
    arg("--no-code", "-nc", dest="code", action="store_false", help="do not show source code")
    arg("--no-reporting", dest="reporting", action="store_false", default=True,
        help="remove reporting capabilities")

    # TODO js cpp ts rs go…
    arg("--format", "-F", choices=["json", "yaml", "py", "c", "js", "out"],
        help="output format")

    arg("--cc", type=str, help="override default C language compiler")
    arg("--cflags", type=str, help="override C compiler flags")
    arg("--cppflags", type=str, help="override C pre-processor flags")
    arg("--ldflags", type=str, help="override C linker flags")

    # testing mode, expected results on values
    arg("--none", "-n", dest="expect", action="store_const", const=None, default=None,
        help="no test expectations")
    arg("--true", "-t", dest="expect", action="store_const", const=True,
        help="test values for true")
    arg("--false", "-f", dest="expect", action="store_const", const=False,
        help="test values for false")
    arg("--test-vector", "-tv", action="store_true", default=False,
        help="read values from a test vector file")
    arg("--report", "-r", action="store_true", default=False, help="report reasons on fail")
    arg("--no-report", "-nr", dest="report", action="store_false",
        help="fast mode, do not give reasons")

    # operations on model
    arg("--check", "-c", action="store_true", default=False, help="check model validity")
    arg("--optimize", "-O", action="store_true", default=True, help="optimize model")
    arg("--no-optimize", "-nO", dest="optimize", action="store_false", help="do not optimize model")
    arg("--map-threshold", "-mt", default=3, type=int, help="property map threshold")
    arg("--map-share", "-ms", default=False, action="store_true", help="property map sharing")

    operation = ap.add_mutually_exclusive_group()
    ope = operation.add_argument
    ope("--op", choices=["P", "U", "J", "N", "V", "E", "X"],
        help="select operation")
    ope("--preproc", "-P", dest="op", action="store_const", const="P",
        help="preprocess model")
    ope("--dump", "-U", dest="op", action="store_const", const="U",
        help="dump all models")
    ope("--jdump", "-J", dest="op", action="store_const", const="J",
        help="dump json IR")
    ope("--nope", "-N", dest="op", action="store_const", const="N",
        help="dump (retrieved) seldom processed json model input")
    ope("--validate", "-V", dest="op", action="store_const", const="V",
        help="interpreted model validation")
    ope("--export", "-E", dest="op", action="store_const", const="E",
        help="export as JSON Schema")
    ope("--experimental", "-X", dest="op", action="store_const", const="X",
        help="experimental code generation")

    # parameters
    arg("model", default="-", nargs="?", help="JSON model source (file or url or \"-\" for stdin)")
    arg("values", nargs="*", help="JSON values to testing")
    args = ap.parse_args()

    if args.version:
        print(pkg_version("json-model"))
        sys.exit(0)

    # format/operation guessing
    if args.output != "-" and args.op is None and args.format is None:
        if args.output.endswith(".c"):
            args.format, args.op = "c", "X"
        elif args.output.endswith(".out"):
            args.format, args.op = "out", "X"
        elif args.output.endswith(".py"):
            args.format, args.op = "py", "X"
        elif args.output.endswith(".js"):
            args.format, args.op = "js", "X"
        elif args.output.endswith(".schema.json"):
            args.format, args.op = "json", "E"
        elif args.output.endswith(".model.json"):
            args.format, args.op = "json", "P"
    elif args.values:
        if args.op is None:
            args.op = "X"
        if args.format is None:
            args.format = "py"

    if args.op is None:
        args.op = "P"

    # update op-dependent default
    if args.code is None:
        args.code = args.op in "X" and not args.values and args.format != "out"

    # option/parameter consistency and defaults
    if args.op in "PUJNE":
        if args.format is None:
            args.format = "json"
        elif args.format not in ("json", "yaml"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    elif args.op == "X":
        if args.format is None:
            args.format = "py"
        elif args.format not in ("py", "c", "js", "out"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    else:  # pragma: no cover
        log.error(f"unexpected operation {args.op}")
        sys.exit(1)

    if args.values and (args.op not in "X" or args.format != "py"):
        log.error(f"Testing JSON values requires -X for Python: {args.op} {args.format}")
        sys.exit(1)
    if args.code and (args.op not in "X" or args.format not in ("py", "c", "js")):
        log.error(f"Showing code requires -X for Python or C: {args.op} {args.format}")
        sys.exit(1)
    if args.format == "out" and args.op not in "X":
        log.error(f"generating executable requires -X: {args.op}")
        sys.exit(1)

    # debug
    log.setLevel(logging.DEBUG if args.debug else logging.INFO if args.verbose else logging.WARNING)

    # resolver
    maps: dict[str, str] = {}
    for m in args.maps:
        assert " " in m, f"valid map require a space: {m}"
        k, v = m.split(" ", 1)
        maps[k] = v
    resolver = Resolver(None, maps)

    log.info(f"processing {args.model}")

    # CREATE FROM FILE OR URL
    try:
        model = create_model(args.model, resolver, auto=args.auto, debug=args.debug, follow=False)
    except BaseException as e:
        log.error(e)
        if args.debug:
            raise
        else:
            log.error(f"invalid model {args.model}")
            sys.exit(2)

    # NOTE preprocessing already done in create_model
    # TODO check why iterating changes things (eg ref to predefs substitions)
    # process_model(model, check=args.check, merge=args.op != "N",
    #               optimize=args.optimize, debug=args.debug)

    # OUTPUT
    # TODO check overwrite?!
    output = open(args.output, "w") if args.output != "-" and args.format != "out" else sys.stdout
    checker = None

    # convert json to a string using prettyprint options
    def json2str(j: Jsonable) -> str:
        if args.format == "json":
            return json.dumps(j, sort_keys=args.sort, indent=args.indent)
        else:
            return yaml.dump(j, sort_keys=args.sort, indent=args.indent)

    # actual output
    if args.op == "J":  # json dump
        verbose = True if args.verbose is None else args.verbose
        show = model.toJSON(verbose=verbose, recurse=verbose)
        # show = [ model._models[mid].toJSON(verbose=args.verbose)
        #             for mid in sorted(model._models.keys()) ]
        print(json2str(show), file=output)
    elif args.op == "U":  # model dump
        assert model._models
        show = []
        for mid in sorted(model._models.keys()):
            m = model._models[mid]
            j = m.toModel(m._is_root)
            if isinstance(j, dict) or model._is_root:
                show.append(j)
        print(json2str(show), file=output)
    elif args.op == "N":  # no operation
        print(json2str(model._init_md), file=output)
    elif args.op == "P":  # preprocessed model
        show = model.toModel(True)
        print(json2str(show), file=output)
    elif args.op == "X":
        assert args.format in ("py", "c", "js", "out"), f"valid output language {args.format}"
        sfmt = "c" if args.format == "out" else args.format

        code = xstatic_compile(model, args.name, lang=sfmt,
                               map_threshold=args.map_threshold, map_share=args.map_share,
                               debug=args.debug, report=args.reporting)
        source = str(code)

        if args.format == "out":
            clang_compile(source, args)
        elif args.code:
            print(source, file=output, end="", flush=True)
            if args.format in ("py", "js") and args.output != "-":
                os.chmod(args.output, 0o755)

        if args.format == "py" and args.values:
            env = {}
            exec(source, env)
            env[args.name + "_init"]()

            def checker(v: Jsonable, model: str, rep: Report = None):
                return env[args.name](v, model, rep)

    elif args.op == "E":
        mm = model._init_md
        if isinstance(mm, dict) and "#" in mm and isinstance(comment := mm["#"], str):
            if "JSON_MODEL_LOOSE" not in comment:
                log.warning(f"{args.model}: JSON Schema does not support strict integer/float")
        schema: JsonSchema
        try:
            schema = model.toSchema()
        except Exception as e:
            log.error(e, exc_info=args.debug)
            schema = {"ERROR": str(e)}
        print(json2str(schema), file=output)
    else:
        raise Exception(f"operation not implemented yet: {args.op}")

    def _process(checker, model: str, value: Jsonable, fid: str, expect: bool|None, output) -> bool:
        """Process a value and report to output depending on args, return if as expected."""
        collect = args.report and args.op in "X"
        reasons = [] if collect else None
        okay = checker(value, model, reasons)
        sokay = "PASS" if okay else "FAIL"
        if expect is None or args.verbose or fid[-1] == "]":
            msg = f"{fid}: {sokay}"
            if not okay and args.report and reasons:
                msg += " (" + "; ".join(f"{json_path(p)}: {m}" for m, p in reasons) + ")"
            print(msg, file=output)
        if expect is not None:
            if okay == expect:
                log.info(f"check value {fid}: {okay}")
            elif okay != expect:
                log.error(f"check value {fid}: {okay}")
                return False
        return True

    # values
    nerrors = 0
    for fn in args.values:
        assert checker
        with open(fn) as fh:
            try:
                value = json.load(fh)
                if args.test_vector:
                    assert isinstance(value, list), "array test vector"
                    for idx, test in enumerate(value):

                        assert isinstance(test, list) and len(test) in (2, 3), "2 or 3 tuple test"

                        if len(test) == 2:
                            expect, val = test
                            model = ""
                        else:
                            assert len(test) == 3
                            expect, model, val = test
                        assert isinstance(expect, bool) and isinstance(model, str), "test format"

                        if not _process(checker, model, val, f"{fn}[{idx}]", expect, output):
                            nerrors += 1

                else:  # direct value testing
                    if not _process(checker, "", value, fn, args.expect, output):
                        nerrors += 1
            except Exception as e:
                nerrors += 1
                log.debug(e, exc_info=args.verbose)
                print(f"{fn}: ERROR")

    sys.exit(4 if nerrors > 0 else 0)
