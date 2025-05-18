import sys
import re
import json
import yaml
import logging
from importlib.metadata import version as pkg_version

from .mtypes import Jsonable, JsonSchema, ModelError
from .utils import log, tname
from .resolver import Resolver
from .model import JsonModel
from .dynamic import DynamicCompiler
from .static import static_compile
from .xstatic import xstatic_compile
from . import optim, analyze, objmerge
from .data.python_types import EntryCheckFun, Report


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
    arg("--auto", "-a", action="store_true", help="automatic mapping")
    # output options
    arg("--name", default="check_model", help="name of generated function")
    arg("--output", "-o", default="-", help="output file")
    arg("--sort", "-s", action="store_true", default=False, help="sorted JSON keys")
    arg("--no-sort", "-ns", dest="sort", action="store_false", help="unsorted JSON keys")
    arg("--indent", "-i", type=int, default=2, help="JSON indentation")
    arg("--code", action="store_true", default=None, help="show source code")
    arg("--no-code", "-nc", dest="code", action="store_false", help="do not show source code")
    arg("--format", "-F", choices=["json", "yaml", "py", "c", "cpp", "js", "ts", "rs", "go"],
        help="output format")
    # expected results on values
    arg("--none", "-n", dest="expect", action="store_const", const=None, default=None,
        help="no test expectations")
    arg("--true", "-t", dest="expect", action="store_const", const=True,
        help="test values for true")
    arg("--false", "-f", dest="expect", action="store_const", const=False,
        help="test values for false")
    # operations on model
    arg("--check", "-c", action="store_true", default=False, help="check model validity")
    arg("--optimize", "-O", action="store_true", help="optimize model")
    arg("--no-optimize", "-nO", dest="optimize", action="store_false", help="do not optimize model")
    operation = ap.add_mutually_exclusive_group()
    ope = operation.add_argument
    ope("--op", default="P", choices=["P", "U", "J", "N", "S", "D", "V", "E", "X"],
        help="select operation")
    ope("--preproc", "-P", dest="op", action="store_const", const="P",
        help="preprocess model")
    ope("--dump", "-U", dest="op", action="store_const", const="U",
        help="dump all models")
    ope("--jdump", "-J", dest="op", action="store_const", const="J",
        help="dump json IR")
    ope("--nope", "-N", dest="op", action="store_const", const="N",
        help="dump (retrieved) seldom processed json model input")
    ope("--static", "-S", dest="op", action="store_const", const="S",
        help="static compile model for Python")
    ope("--dynamic", "-D", dest="op", action="store_const", const="D",
        help="dynamic compile model for Python")
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

    # update op-dependent default
    if args.code is None:
        args.code = args.op in "DSX" and not args.values

    # option/parameter consistency and defaults
    if args.values and args.op not in "SDX":  # V?
        log.error(f"Testing JSON values requires -S, -D or -X: {args.op}")
        sys.exit(1)
    if args.code and args.op not in "DSX":
        log.error(f"Showing code requires -S, -D or -X: {args.op}")
        sys.exit(1)
    if args.op in "PUJNE":
        if args.format is None:
            args.format = "json"
        elif args.format not in ("json", "yaml"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    elif args.op in "DS":
        if args.format is None:
            args.format = "py"
        elif args.format != "py":
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    elif args.op == "X":
        if args.format is None:
            args.format = "py"
        elif args.format not in ("py", "c", "cpp", "js", "ts", "rs", "go"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    else:  # pragma: no cover
        log.error(f"unexpected operation {args.op}")
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

    # PREPROCESSING
    try:
        process_model(model, check=args.check, merge=args.op != "N",
                      optimize=args.optimize, debug=args.debug)
    except BaseException as e:
        log.error(e, exc_info=args.debug)
        sys.exit(3)

    # OUTPUT
    # TODO check overwrite?!
    output = open(args.output, "w") if args.output != "-" else sys.stdout
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
    elif args.op == "D":
        checker = DynamicCompiler(model)
        if args.code:
            import dis
            for jmid in sorted(checker._compiled.keys()):
                fun = checker._compiled[jmid]
                asm = re.sub(r"(?m)^\d+", lambda m: " " * len(m.group(0)), dis.Bytecode(fun).dis())
                print(f"#\n# json model {jmid}\n#", file=output)
                print(asm, file=output)
    elif args.op == "S":
        code = static_compile(model, "check_model", debug=args.debug, report=args.verbose)
        source = f"#! /bin/env python\n#\n# Model: {args.model}\n" + str(code)
        if args.code:
            print(source, file=output)
        env = {}
        exec(source, env)
        checker = env["check_model"]
    elif args.op == "X":
        assert args.format in ("py", "c", "cpp", "js", "ts", "rs", "go"), \
            f"valid output language {args.format}"
        code = xstatic_compile(model, args.name,
                               lang=args.format, debug=args.debug, report=args.verbose)
        source = str(code)
        if args.code:
            print(source, file=output, end="")
        if args.format == "py" and args.values:
            env = {}
            exec(source, env)
            env[args.name + "_init"]()
            def checker(v: Jsonable, s: str = "", rep: Report = None):
                return env[args.name](v, "", rep)
    elif args.op == "E":
        mm = model._init_md
        if isinstance(mm, dict) and "#" in mm and isinstance(comment := mm["#"], str):
            if not ("JSON_MODEL_LOOSE_INT" in comment and "JSON_MODEL_LOOSE_FLOAT" in comment):
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

    # values
    nerrors = 0
    for fn in args.values:
        assert checker
        with open(fn) as fh:
            try:
                value = json.load(fh)
                reasons = [[]] if args.verbose and args.op in "SX" else []
                okay = checker(value, "$", *reasons)
                sokay = "PASS" if okay else "FAIL"
                if args.expect is None or args.verbose:
                    msg = f"{fn}: {sokay}"
                    if not okay and args.verbose:
                        if args.op == "D":
                            msg += " " + str(checker._reasons)
                        elif args.op in ("S", "X"):
                            msg += " " + str(reasons[0])
                    print(msg, file=output)
                if args.expect is not None:
                    if okay == args.expect:
                        log.info(f"check value {fn}: {okay}")
                    elif okay != args.expect:
                        nerrors += 1
                        log.error(f"check value {fn}: {okay}")
            except Exception as e:
                log.debug(e, exc_info=args.verbose)
                print(f"{fn}: ERROR")

    sys.exit(4 if nerrors > 0 else 0)
