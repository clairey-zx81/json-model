import sys
import re
import json
import logging
from importlib.metadata import version as pkg_version

from .types import Jsonable, JsonSchema, ModelError
from .utils import log, tname
from .resolver import Resolver
from .model import JsonModel
from .dynamic import DynamicCompiler
from .static import static_compile

def create_model(murl: str, resolver: Resolver,
                 auto: bool = False, debug: bool = False) -> JsonModel:

    # load JSON
    j = resolver(murl, [])

    # handle automatic URL mapping
    if auto and (isinstance(j, dict) and "$" in j and isinstance(j["$"], dict) and "" in j["$"]):
        url = j["$"][""]
        assert isinstance(url, str), f"$ expects a string: {tname(url)}"
        fn = re.sub(r"(\.model)?(\.js(on))?$", "", murl)  # drop suffix
        log.debug(f"url={url} fn={fn}")
        file = fn if "/" in fn else ("./" + fn)
        if fn != url and file != url and "/" in url:
            upref, uend = url.rsplit("/", 1)
            fpref, fend = file.rsplit("/", 1)
            log.debug(f"upref={upref} fpref={fpref}")
            if upref not in resolver._maps and uend == fend:
                log.info(f"auto adding url map: {upref} -> {fpref}")
                resolver._maps[upref] = fpref

    # build model
    return JsonModel(j, resolver, None, None, murl, True, debug)

def process_model(model: JsonModel, check: bool = True,
                  merge: bool = True, optimize: bool = True, debug: bool = False):

    # initial sanity check
    if debug or check:
        for m in JsonModel.MODELS:
            if not m.valid():
                raise ModelError(f"invalid initial model {model._url}[{model._id}]")

    # simplify before merging
    if optimize:
        for m in JsonModel.MODELS:
            m.optimize()

    # check after initial optimize
    if debug or check:
        # log.debug(json.dumps(model.toJSON(), sort_keys=True, indent=2))
        for m in JsonModel.MODELS:
            if not m.valid():
                raise ModelError(f"invalid optimized model {model._url}[{model._id}]")

    # merge in reverse order to move alts up before inlining?!
    if merge:
        for m in reversed(JsonModel.MODELS):
            m.merge()

    # optimize again?
    if optimize:
        for m in JsonModel.MODELS:
            m.optimize()

    # check after merge & optimize
    if debug or check:
        # log.debug(json.dumps(model.toJSON(), sort_keys=True, indent=2))
        for m in JsonModel.MODELS:
            # assert m.valid()
            if not m.valid():
                raise ModelError(f"invalid merged model {model._url}[{model._id}]")

def jmc_script():

    import argparse

    logging.basicConfig()

    ap = argparse.ArgumentParser()
    arg = ap.add_argument
    # verbosity and checks
    arg("--version", action="store_true", help="show current version and exit")
    arg("--debug", "-d", action="store_true", help="set debugging mode")
    arg("--verbose", "-v", action="store_true", help="set verbose mode")
    arg("--quiet", "-q", dest="verbose", action="store_false", help="reduce verbosity")
    # input options
    arg("--maps", "-m", action="append", default=[], help="URL mappings")
    arg("--auto", "-a", action="store_true", help="automatic mapping")
    # output options
    arg("--output", "-o", default="-", help="output file")
    arg("--sort", "-s", action="store_true", default=True, help="sorted JSON keys")
    arg("--no-sort", "-ns", dest="sort", action="store_false", help="unsorted JSON keys")
    arg("--indent", "-i", type=int, default=2, help="JSON indentation")
    arg("--code", action="store_true", default=None, help="show source code")
    arg("--no-code", "-nc", dest="code", action="store_false", help="do not show source code")
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
    arg("--dump", "-U", dest="op", action="store_const", const="U", default="U", help="dump model")
    arg("--nope", "-N", dest="op", action="store_const", const="N",
        help="dump (retrieved) json input")
    arg("--preproc", "-P", dest="op", action="store_const", const="P", help="preprocess model")
    arg("--static", "-S", dest="op", action="store_const", const="S", help="static compile model")
    arg("--dynamic", "-D", dest="op", action="store_const", const="D", help="dynamic compile model")
    arg("--validate", "-V", dest="op", action="store_const", const="V", help="direct validation")
    arg("--export", "-E", dest="op", action="store_const", const="E", help="export as JSON Schema")
    # parameters
    arg("model", default="-", nargs="?", help="JSON model source (file or url or \"-\" for stdin)")
    arg("values", nargs="*", help="JSON values to testing")
    args = ap.parse_args()

    if args.version:
        print(pkg_version("json-model"))
        sys.exit(0)

    # update op-dependent default
    if args.code is None:
        args.code = args.op in ("D", "S") and not args.values

    # option/parameter consistency
    if args.values and args.op not in ("S", "D", "V"):
        log.error(f"Testing JSON values requires -S, -D or -V: {args.op}")
        sys.exit(1)
    if args.code and args.op not in ("D", "S"):
        log.error(f"Showing code requires -S or -D: {args.op}")
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
        model = create_model(args.model, resolver, args.auto, args.debug)
        assert model._isolated
    except BaseException as e:
        log.error(e)
        if args.debug:
            raise
        else:
            log.error(f"invalid model {args.model}")
            sys.exit(2)

    # PREPROCESSING
    try:
        process_model(model, args.check, args.op != "N", args.optimize, args.debug)
    except BaseException as e:
        log.error(e, exc_info=args.debug)
        sys.exit(3)

    # OUTPUT
    # TODO check overwrite?!
    output = open(args.output, "w") if args.output != "-" else sys.stdout
    checker = None

    # convert json to a string using prettyprint options
    def json2str(j: Jsonable) -> str:
        return json.dumps(j, sort_keys=args.sort, indent=args.indent)

    # actual output
    if args.op == "U":  # test output
        show, symbols = [], set()
        for m in JsonModel.MODELS:
            j = m.toModel(m._defs._id not in symbols)
            symbols.add(m._defs._id)
            if isinstance(j, dict) or model._isolated:
                show.append(j)
        print(json2str(show), file=output)
    elif args.op == "N":  # no operation
        print(json2str(model._init_md), file=output)
    elif args.op == "P":  # preprocessed model
        show = model.toModel(True)
        print(json2str(show), file=output)
    elif args.op == "D":
        checker = DynamicCompiler(model)
        if args.debug or args.code:
            import dis
            for jmid in sorted(checker._compiled.keys()):
                fun = checker._compiled[jmid]
                asm = re.sub(r"(?m)^\d+", lambda m: " " * len(m.group(0)), dis.Bytecode(fun).dis())
                print(f"#\n# json model {jmid}\n#", file=output)
                print(asm, file=output)
    elif args.op == "S":
        code = static_compile(model, "check_model", debug=args.debug)
        source_code = f"# Generated for model: {args.model}\n" + str(code)
        if args.debug or args.code:
            print(source_code, file=output)
        env = {}
        exec(source_code, env)
        checker = env["check_model"]
    elif args.op == "E":
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
                okay = checker(value)
                if args.expect is None or args.verbose:
                    msg = f"{fn}: {okay}"
                    if not okay and args.verbose and args.op == "D":
                        msg += " " + str(checker._reasons)
                    print(msg, file=output)
                if args.expect is not None:
                    if okay == args.expect:
                        log.info(f"check value {fn}: {okay}")
                    elif okay != args.expect:
                        nerrors += 1
                        log.error(f"check value {fn}: {okay}")
            except Exception as e:
                log.debug(e, exc_info=args.verbose)
                print(f"{fn}: Error")

    sys.exit(4 if nerrors > 0 else 0)
