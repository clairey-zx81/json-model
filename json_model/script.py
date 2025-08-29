import os
import sys
import re
import json
import yaml
import logging
from pathlib import Path
from importlib.metadata import version as pkg_version
from importlib.resources import files
import subprocess
import tempfile

from .mtypes import Jsonable, JsonSchema, ModelError
from .utils import log, tname, json_loads, load_data_file
from .resolver import Resolver
from .model import JsonModel
from .xstatic import xstatic_compile
from . import optim, analyze, objmerge
from .runtime.types import EntryCheckFun, Report
from .runtime.support import _path as json_path
from .export import model2python

LANG = {
  "py": "Python",
  "c": "C",
  "js": "JavaScript",
  "plpgsql": "PL/pgSQL",
  "pl": "Perl",
  "java": "Java",
}

def process_model(model: JsonModel, *,
                  check: bool = True, merge: bool = True, optimize: bool = True,
                  debug: int = 0):
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
        debug: int = 0, murl: str = "",
        check: bool = True, merge: bool = True, optimize: bool = True,
        loose_int: bool|None = None, loose_float: bool|None = None,
        resolver: Resolver|None = None) -> JsonModel:
    """JsonModel instanciation from JSON data."""

    if resolver is None:
        resolver = Resolver()

    # possibly add resolver mapping rule
    if auto and (isinstance(mjson, dict) and "$" in mjson and \
            isinstance(mjson["$"], dict) and "" in mjson["$"]):
        url = mjson["$"][""]
        assert isinstance(url, str), ".\"$\"." f" expects a string: {tname(url)}"
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

    jm = JsonModel(mjson, resolver, url=murl, debug=debug,
                   loose_int=loose_int, loose_float=loose_float)

    if check or merge or optimize:
        process_model(jm, check=check, merge=merge, optimize=optimize, debug=debug)

    return jm


def model_from_url(murl: str, *, auto: bool = False, debug: int = 0,
                   check: bool = True, merge: bool = True, optimize: bool = True,
                   loose_int: bool|None = None, loose_float: bool|None = None,
                   resolver: Resolver|None = None, follow: bool = True) -> JsonModel:
    """JsonModel instanciation from a URL."""

    if resolver is None:
        resolver = Resolver()

    mjson = resolver(murl, follow=follow)

    return model_from_json(mjson, murl=murl, auto=auto, debug=debug, resolver=resolver,
                           loose_int=loose_int, loose_float=loose_float,
                           check=check, merge=merge, optimize=optimize)


def model_from_str(mstring: str, *, auto: bool = False,
                   check: bool = True, merge: bool = True, optimize: bool = True,
                   loose_int: bool|None = None, loose_float: bool|None = None,
                   debug: int = 0, murl: str = "", allow_duplicates: bool = False) -> JsonModel:
    """JsonModel instanciation from a string."""

    return model_from_json(json_loads(mstring, allow_duplicates=allow_duplicates),
                           auto=auto, debug=debug, murl=murl,
                           loose_int=loose_int, loose_float=loose_float,
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
            mjson: Jsonable, *, auto: bool = False, debug: int = 0,
            resolver: Resolver|None = None,
            loose_int: bool|None = None, loose_float: bool|None = None,
        ) -> EntryCheckFun:
    """Return an executable model checker from a URL."""
    jm = model_from_json(mjson, auto=auto, debug=debug, resolver=resolver,
                         loose_int=loose_int, loose_float=loose_float)
    return model_checker(jm, debug=debug > 0)


def model_checker_from_url(
            murl: str, *, auto: bool = False, debug: int = 0,
            resolver: Resolver|None = None, follow: bool = True,
            loose_int: bool|None = None, loose_float: bool|None = None
        ) -> EntryCheckFun:
    """Return an executable model checker from a URL."""
    jm = model_from_url(murl, auto=auto, debug=debug, resolver=resolver, follow=follow,
                        loose_int=loose_int, loose_float=loose_float)
    return model_checker(jm, debug=debug > 0)


def create_model(murl: str, resolver: Resolver, *,
                 auto: bool = False, follow: bool = True, debug: int = 0,
                 check: bool = True, merge: bool = True, optimize: bool = True,
                 loose_int: bool|None = None, loose_float: bool|None = None) -> JsonModel:
    """JsonModel instanciation without preprocessing."""
    return model_from_url(murl, auto=auto, follow=follow, debug=debug, resolver=resolver,
                          loose_int=loose_int, loose_float=loose_float,
                          check=check, merge=merge, optimize=optimize)

DEFAULT_CC = "cc"
DEFAULT_CFLAGS = "-Wall -Wno-address -Wno-c23-extensions -Wno-unused-variable -Wno-unused-function -Ofast"
DEFAULT_LDFLAGS_PCRE2 = "-ljansson -lpcre2-8 -lm"
# pkgconf --libs cre2
DEFAULT_LDFLAGS_CRE2 = "-L/usr/local/lib -ljansson -lcre2 -lpthread -lre2 -lm -lstdc++"

def clang_compile(c_code: str, args):
    """Generate an actual executable or object file."""

    tmp_dir = os.environ.get("TMPDIR", "/dev/shm")

    # source files
    rt_dir = files("json_model.runtime")
    lib = rt_dir.joinpath("c/json-model.c")
    main = rt_dir.joinpath("c/main.c")

    # compiler setings
    env = os.environ.get
    cc = args.cc or env("CC", DEFAULT_CC)
    cflags = args.cflags or env("CFLAGS", DEFAULT_CFLAGS)
    d_engine = "-DREGEX_ENGINE_PCRE2" if args.regex_engine == "pcre2" else "-DREGEX_ENGINE_RE2"
    cppflags = args.cppflags or \
        f"-I{rt_dir}/c -I/usr/local/linclude -DCHECK_FUNCTION_NAME=check_model {d_engine}"
    if args.define:
        cppflags = " ".join(f"-D{d}" for d in args.define) + " " + cppflags
    if args.include:
        cppflags = " ".join(f"-I{i}" for i in args.include) + " " + cppflags
    ldflags = args.ldflags or \
        (DEFAULT_LDFLAGS_PCRE2 if args.regex_engine == "pcre2" else DEFAULT_LDFLAGS_CRE2)
    if args.library:
        ldflags = " -L".join([""] + args.library) + " " + ldflags
    if args.static:
        ldflags += " --static"

    output = "a.out" if args.output == "-" else args.output

    with tempfile.NamedTemporaryFile(dir=tmp_dir, suffix=".c") as tmp:
        tmp.write(c_code.encode("UTF-8"))
        tmp.flush()
        if args.gen == "exec":
            command = f"{cc} {cppflags} {cflags} -o {output} {lib} {tmp.name} {main} {ldflags}"
        else:
            command = f"{cc} {cppflags} {cflags} -o {output} -c {tmp.name}"
        if args.verbose:
            log.info(f"C compilation: {command}")
        status = os.system(command)
        assert status == 0, f"C compilation succeeded: {command}"

def java_compile(java_code: str, args):
    """Compile java source."""
    tmp_dir = os.environ.get("TMPDIR", "/dev/shm")
    output = Path(args.output or "XXX.java")
    out_dir = Path(output).parent

    # CAUTION java files must be named after their class name
    java_file = (Path(tmp_dir) / output.stem).with_suffix(".java")
    with open(java_file, "w") as f:
        f.write(java_code)

    javac = args.javac or "javac"
    jflags = args.jflags or ""
    command = f"{javac} -d {out_dir} {jflags} {java_file}"
    if args.verbose:
        log.info(f"Java compilation: {command}")
    status = os.system(command)

    # cleanup and check
    java_file.unlink()
    assert status == 0, f"Java compilation succeeded: {command}"

def jmc_script():

    import argparse

    logging.basicConfig()

    ap = argparse.ArgumentParser(
        prog="jmc",
        description="""JSON Model is a compact and intuitive JSON syntax to describe JSON data
            structures. This JSON Model Compiler command allows to derive codes or schemas from
            a model. See https://github.com/clairey-zx81/json-model for details.""",
        epilog="This code is Public Domain."
    )
    arg = ap.add_argument

    # documentation
    arg("--doc", choices=["pod", "syn", "help", "man"], default=None,
        help="show documentation and exit")
    arg("--man", dest="doc", action="store_const", const="man", help="show man page")

    # verbosity and checks
    arg("--version", action="store_true", help="show current version and exit")
    arg("--debug", "-d", default=0, action="count", help="increase debugging verbosity")
    arg("--verbose", "-v", action="store_true", help="more verbose")
    arg("--quiet", "-q", dest="verbose", action="store_false", help="less verbose")

    # input options about JM
    arg("--allow-duplicates", "-ad", action="store_true", default=False,
        help="allow duplicated properties in parsed model, probably a bad idea.""")
    arg("--maps", "-m", action="append", default=[], help="URL mappings")
    arg("--auto", "-a", action="store_true", help="automatic URL mapping")

    arg("--loose-int", "-li", action="store_true", default=None,
        help="use loose integers")
    arg("--strict-int", "-si", dest="loose_int", action="store_false", default=None,
        help="use strict integers (default)")
    arg("--loose-float", "-lf", action="store_true", default=None,
        help="use loose floats")
    arg("--strict-float", "-sf", dest="loose_float", action="store_false",
        help="use strict floats (default)")
    arg("--loose-number", "--loose", "-ln", action="store_true", default=None,
        help="use loose integer and float numbers")
    arg("--strict-number", "--strict", "-sn", dest="loose_number", action="store_false",
        help="use strict integer and float numbers (default)")

    # output options
    arg("--output", "-o", default="-", help="output file")
    arg("--package", "-p", default=None, help="generated module name, if appropriate")
    arg("--entry", "-e", help="name prefix of generated functions")
    arg("--regex-engine", "-re", default=None, choices=["re", "re2", "pcre2"],
        help="select regular expression engine (default depends on target language)")
    arg("--sort", "-s", action="store_true", default=False, help="sorted JSON keys")
    arg("--no-sort", "-ns", dest="sort", action="store_false", help="unsorted JSON keys")
    arg("--indent", "-i", type=int, default=2, help="JSON indentation")
    arg("--reporting", action="store_true", default=None,
        help="add reporting capabilities (default)")
    arg("--no-reporting", dest="reporting", action="store_false",
        help="remove reporting capabilities")
    arg("--short-version", action="store_true", default=False,
        help="generate a short version in output code")

    generate = ap.add_mutually_exclusive_group()
    gen = generate.add_argument
    gen("--generate", "--gen", dest="gen", choices=["exec", "module", "source", "none"],
        help="select what to generate")
    gen("--exec", "--executable", dest="gen", action="store_const", const="exec", default=None,
        help="generate an executable")
    gen("--module", dest="gen", action="store_const", const="module", help="generate a module")
    gen("--code", dest="gen", action="store_const", const="code", help="generate source code")
    gen("--no-gen", "-ng", dest="gen", action="store_const", const="none",
        help="do not generate anything")

    # TODO cpp ts rs go…
    arg("--format", "-F", choices=["json", "yaml", "py", "c", "js", "plpgsql", "pl", "java"],
        default=None, help="output language")

    # C-specific options
    arg("--cc", type=str, help="override default C language compiler")
    arg("--cflags", type=str, help="override C compiler flags")
    arg("--cppflags", type=str, help="override C pre-processor flags")
    arg("--ldflags", type=str, help="override C linker flags for executable")
    arg("--static", action="store_true", default=False, help="trigger static link")
    arg("--include", "-I", nargs="*", default=[], help="add include directory")
    arg("--library", "-L", nargs="*", default=[], help="add library directory")
    arg("--define", "-D", nargs="*", default=[], help="add cpp definitions")
    arg("--inline", default=True, action="store_true", help="enable function inlining")
    arg("--no-inline", dest="inline", action="store_false", help="disable function inlining")

    # TODO java-specific options
    arg("--javac", type=str, help="override default Java language compiler")
    arg("--jflags", type=str, help="add Java compiler flags")

    # testing mode, expected results on values
    arg("--name", "-n", default="", help="name of validation submodel, default is \"\" (root)")
    arg("--none", dest="expect", action="store_const", const=None, default=None,
        help="no test expectations")
    arg("--true", "-t", dest="expect", action="store_const", const=True,
        help="test values for true")
    arg("--false", "-f", dest="expect", action="store_const", const=False,
        help="test values for false")
    arg("--test-vector", "-tv", action="store_true", default=False,
        help="read values from a test vector file")
    arg("--jsonl", "-j", action="store_true", default=False,
        help="accept value file in JSONL format")
    arg("--report", "-r", action="store_true", default=False, help="report reasons on fail")
    arg("--no-report", "-nr", dest="report", action="store_false",
        help="fast mode, do not give reasons")

    # operations on model
    arg("--check", "-c", action="store_true", default=False, help="check model validity")
    arg("--optimize", "-O", action="store_true", default=True, help="optimize model")
    arg("--no-optimize", "-nO", dest="optimize", action="store_false", help="do not optimize model")
    arg("--map-threshold", "-mt", default=5, type=int, help="property map threshold, default 5")
    arg("--map-share", "-ms", default=False, action="store_true", help="property map sharing")

    operation = ap.add_mutually_exclusive_group()
    ope = operation.add_argument
    ope("--op", choices=["P", "U", "J", "N", "E", "C"], default=None,
        help="select operation")
    ope("--preproc", "-P", dest="op", action="store_const", const="P",
        help="preprocess model")
    ope("--dump", "-U", dest="op", action="store_const", const="U",
        help="dump all models")
    ope("--jdump", "-J", dest="op", action="store_const", const="J",
        help="dump json IR")
    ope("--nope", "-N", dest="op", action="store_const", const="N",
        help="dump (retrieved) seldom processed json model input")
    ope("--export", "-E", dest="op", action="store_const", const="E",
        help="export as JSON Schema")
    ope("--compile", "-C", dest="op", action="store_const", const="C",
        help="code generation")

    # url cache management
    arg("--cache-dir", default=None, help="set cache directory")
    arg("--cache-ignore", default=False, action="store_true", help="ignore cache contents")
    arg("--cache-clear", default=False, action="store_true", help="cleanup cache contents and exit")

    # parameters
    arg("model", default="-", nargs="?", help="JSON model source (file or url or \"-\" for stdin)")
    arg("values", nargs="*", help="JSON values to testing")
    args = ap.parse_args()

    if args.version:
        print(pkg_version("json_model_compiler"))
        sys.exit(0)

    # POD - Plain Old Documentation
    if args.doc:
        # Python does not provide any help to write man pages for the user
        pod = load_data_file("jmc.pod")
        if args.doc == "pod":
            print(pod)
        else:
            v = "2" if args.doc == "man" else "1" if args.doc == "help" else "0"
            f = "Pod::Text::Termcap" if args.doc == "man" else "Pod::Text"
            subprocess.run(["pod2usage", "-v", v, "-formatter", f], input=pod.encode("utf8"))
        sys.exit(0)

    # format/operation/gen guessing
    if args.output != "-":
        if args.output.endswith(".c"):
            args.format = args.format or "c"
            args.op = args.op or "C"
            args.gen = args.gen or "source"
        if args.output.endswith(".o"):
            args.format = args.format or "c"
            args.op = args.op or "C"
            args.gen = args.gen or "module"
        elif args.output.endswith(".out"):
            args.format = args.format or "c"
            args.op = args.op or "C"
            args.gen = args.gen or "exec"
        elif args.output.endswith(".py"):
            args.format = args.format or "py"
            args.op = args.op or "C"
            args.gen = args.gen or "exec"
        elif args.output.endswith(".mpy"):
            args.format = args.format or "py"
            args.op = args.op or "C"
            args.gen = args.gen or "module"
        elif args.output.endswith(".js"):
            args.format = args.format or "js"
            args.op = args.op or "C"
            args.gen = args.gen or "exec"
        elif args.output.endswith(".mjs"):
            args.format = args.format or "js"
            args.op = args.op or "C"
            args.gen = args.gen or "module"
        elif args.output.endswith(".sql"):
            args.format = args.format or "plpgsql"
            args.op = args.op or "C"
            args.gen = args.gen or "module"
        elif args.output.endswith(".pl"):
            args.format = args.format or "pl"
            args.op = args.op or "C"
            args.gen = args.gen or "exec"
        elif args.output.endswith(".pm"):
            args.format = args.format or "pl"
            args.op = args.op or "C"
            args.gen = args.gen or "module"
            args.package = args.package or Path(args.output).stem
        elif args.output.endswith(".java"):
            args.format = args.format or "java"
            args.op = args.op or "C"
            args.gen = args.gen or "source"
            args.entry = args.entry or Path(args.output).stem.replace("-", "_")
        elif args.output.endswith(".class"):
            args.format = args.format or "java"
            args.op = args.op or "C"
            args.gen = args.gen or "exec"
            stem = Path(args.output).stem
            if "-" in stem:
                log.error(f"java class files cannot contain '-': {args.output}")
                sys.exit(1)
            args.entry = args.entry or Path(args.output).stem.replace("-", "_")
        elif args.output.endswith(".schema.json"):
            args.format = args.format or "json"
            args.op = args.op or "E"
        elif args.output.endswith(".model.json"):
            args.format = args.format or "json"
            args.op = args.op or "P"

    args.entry = args.entry or "check_model"

    if args.values:
        args.op = args.op or "C"
        args.format = args.format or "py"
        args.gen = args.gen or "none"

    if args.reporting is None:
        args.reporting = False if args.format == "plpgsql" else True

    if args.op is None:
        args.op = "P"

    # update op-dependent default
    if args.gen is None:
        args.gen = "source" if args.op in "C" and not args.values else "module"

    # option/parameter consistency and defaults
    if args.op in "PUJN":
        args.format = args.format or "json"
        if args.format not in ("json", "yaml"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    elif args.op == "E":
        args.format = args.format or "json"
        if args.format not in ("json", "yaml", "py"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    elif args.op == "C":
        args.format = args.format or "py"
        if args.format not in ("py", "c", "js", "plpgsql", "pl", "java"):
            log.error(f"unexpected format {args.format} for operation {args.op}")
            sys.exit(1)
    else:  # pragma: no cover
        log.error(f"unexpected operation {args.op}")
        sys.exit(1)

    if args.values and (args.op != "C" or args.format != "py"):
        log.error(f"Testing JSON values requires -C for Python: {args.op} {args.format}")
        sys.exit(1)
    if args.gen == "source" and (args.op != "C" or args.format not in ("py", "c", "js", "plpgsql", "pl", "java")):
        log.error(f"Showing code requires -C for C, Java, JavaScript, Perl, Python and PL/pgSQL: {args.op} {args.format}")
        sys.exit(1)

    # strict/loose numbers
    if args.loose_number is not None:
        if args.loose_int is None:
            args.loose_int = args.loose_number
        else:
            log.warning("keeping integer strictness as already set")
        if args.loose_float is None:
            args.loose_float = args.loose_number
        else:
            log.warning("keeping float strictness as already set")

    with_main = args.gen == "exec" or args.gen == "source" and args.format == "java"

    # debug
    log.setLevel(logging.DEBUG if args.debug else logging.INFO if args.verbose else logging.WARNING)

    # resolver
    maps: dict[str, str] = {}
    for m in args.maps:
        assert " " in m, f"valid map require a space: {m}"
        k, v = m.split(" ", 1)
        maps[k] = v
    resolver = Resolver(args.cache_dir, maps, allow_duplicates=args.allow_duplicates,
                        cache_ignore=args.cache_ignore)
    if args.cache_clear:
        resolver.clear()
        sys.exit(0)

    log.info(f"processing {args.model}")

    # CREATE FROM FILE OR URL
    try:
        model = create_model(args.model, resolver, auto=args.auto, debug=args.debug,
                             loose_int=args.loose_int, loose_float=args.loose_float,
                             check=args.check, merge=args.op != "N", optimize=args.optimize,
                             follow=False)
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
    checker = None  # pyright: ignore

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
    elif args.op == "C":
        assert args.format in ("py", "c", "js", "plpgsql", "pl", "java"), \
            f"valid output language {args.format}"

        # FIXME PL/pgSQL?
        if args.format in ("plpgsql", "js", "pl") and \
                (not model._loose_int or not model._loose_float):
            log.warning(f"{args.model}: {LANG[args.format]} backend does not support strict numbers")

        # compile to source
        code = xstatic_compile(model, args.entry, lang=args.format, execute=with_main,
                               map_threshold=args.map_threshold, map_share=args.map_share,
                               debug=args.debug, report=args.reporting, relib=args.regex_engine,
                               short_version=args.short_version, package=args.package,
                               inline=args.inline)
        source = str(code)

        # source to executable for C and java
        if args.format == "c" and args.gen in ("exec", "module"):
            clang_compile(source, args)
        elif args.format == "java" and args.gen in ("exec", "module"):
            java_compile(source, args)
        elif args.gen != "none":
            print(source, file=output, end="", flush=True)
            if args.output != "-" and args.gen == "exec":
                os.chmod(args.output, 0o755)

        # import for checks
        if args.format == "py" and args.values:
            env = {}
            exec(source, env)
            env[args.entry + "_init"]()

            def checker(v: Jsonable, model: str, rep: Report = None) -> bool:
                return env[args.entry](v, model, rep)

    elif args.op == "E":
        if args.format in ("json", "yaml"):
            if not model._loose_int or not model._loose_float:
                log.warning(f"{args.model}: JSON Schema does not support strict integer/float")
            schema: JsonSchema
            try:
                schema = model.toSchema()
            except Exception as e:
                log.error(e, exc_info=args.debug)
                schema = {"ERROR": str(e)}
            print(json2str(schema), file=output)
        elif args.format == "py":
            code = [
                "# Pydantic classes generated by JSON Model Compiler",
                f"# for {args.model}",
                "# see https://json-model.org/",
            ] + model2python(model, root=args.name or "RootModel")
            print("\n".join(code), file=output)
    else:
        raise Exception(f"operation not implemented yet: {args.op}")

    def _process(checker, model: str, value: Jsonable, fid: str, expect: bool|None, output) -> bool:
        """Process a value and report to output depending on args, return if as expected."""
        reasons = [] if args.report else None
        okay = checker(value, model, reasons)
        sokay = "PASS" if okay else "FAIL"
        if expect is None or args.verbose or fid[-1] == "]":
            msg = f"{fid}: {sokay}"
            if not okay and args.report and reasons:
                msg += " (" + "; ".join(f"{json_path(p)}: {m}" for m, p in reversed(reasons)) + ")"
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
                contents = fh.read()
                # parse JSON
                if args.jsonl:
                    lines = contents.split("\n")[:-1]
                    value = [ [ None, json_loads(line, allow_duplicates=args.allow_duplicates) ]
                                for line in lines ]
                else:
                    value = json_loads(contents, allow_duplicates=args.allow_duplicates)
                # process values
                if args.test_vector or args.jsonl:
                    assert isinstance(value, list), "array test vector"
                    for idx, test in enumerate(value):

                        assert isinstance(test, list) and len(test) in (2, 3), "2 or 3 tuple test"

                        if len(test) == 2:
                            expect, val = test
                            model = args.name
                        else:
                            assert len(test) == 3
                            expect, model, val = test
                        assert expect is None or isinstance(expect, bool), "expect is null or bool"
                        assert isinstance(model, str), "model name is a string"

                        if not _process(checker, model, val, f"{fn}[{idx}]", expect, output):
                            nerrors += 1

                else:  # direct value testing
                    if not _process(checker, args.name, value, fn, args.expect, output):  # type: ignore
                        nerrors += 1
            except Exception as e:
                nerrors += 1
                log.debug(e, exc_info=args.verbose)
                print(f"{fn}: ERROR")

    sys.exit(4 if nerrors > 0 else 0)
