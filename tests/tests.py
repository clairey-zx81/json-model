import typing
import os
import pathlib
import re
import json
import logging
import filelock
import pytest

from json_model.script import model_from_url, model_checker_from_url
from json_model.resolver import Resolver
from json_model.xstatic import xstatic_compile

logging.basicConfig()
log = logging.getLogger("test")
# log.setLevel(logging.DEBUG)
log.setLevel(logging.INFO)

#
# PER-DIRECTORY TEST EXPECTATIONS, IN SMALL CHUNKS FOR XDIST
#
EXPECT: dict[str, int] = {
    # reference
    "ref:models": 9,
    "ref:values": 111,
    "ref:verrors:schema": 56,
    # chunk 00
    "mv-00:models": 10,
    "mv-00:values": 95,
    # chunk 01
    "mv-01:models": 10,
    "mv-01:values": 100,
    "mv-01:errors.js": 2,
    "mv-01:errors.sql": 2,
    "mv-01:errors.pl": 2,
    "mv-01:verrors:schema": 14,
    # chunk 02
    "mv-02:js2json": 1,
    "mv-02:models": 10,
    "mv-02:values": 122,
    "mv-02:verrors:schema": 46,
    # chunk 03
    "mv-03:js2json": 1,
    "mv-03:models": 10,
    "mv-03:models:errors-jsg": 2,
    "mv-03:values": 78,
    "mv-03:verrors:schema": 26,
    # chunk 04
    "mv-04:js2json": 2,
    "mv-04:models": 8,
    "mv-04:values": 98,
    "mv-04:verrors:schema": 15,
    # chunk 05
    "mv-05:models": 9,
    "mv-05:values": 81,
    # chunk 06
    # FIXME schema missing Schema
    "mv-06:models": 9,
    "mv-06:values": 89,
    "mv-06:verrors:schema": 24,
    # chunk 07
    # FIXME schema missing Schema
    "mv-07:models": 5,
    "mv-07:values": 45,
    "mv-07:verrors:schema": 18,
    # chunk 08
    "mv-08:models": 9,
    "mv-08:values": 129,
    "mv-08:verrors:schema": 43,
    "mv-08:models:errors-jsg": 2,
    # chunk 09
    "mv-09:models": 10,
    "mv-09:values": 141,
    "mv-09:errors.js": 2,
    "mv-09:errors.sql": 2,
    "mv-09:errors.pl": 2,
    "mv-09:verrors:schema": 2,
    # chunk 0A
    "mv-0a:models": 10,
    "mv-0a:values": 131,
    "mv-0a:errors.js": 1,
    "mv-0a:errors.sql": 1,
    "mv-0a:errors.pl": 1,
    "mv-0a:verrors:schema": 1,
    # chunk 0B
    "mv-0b:models": 7,
    "mv-0b:values": 82,
    # chunk 0C
    "mv-0c:models": 5,
    "mv-0c:values": 50,
    "mv-0c:errors.js": 1,
    "mv-0c:errors.sql": 1,
    "mv-0c:errors.pl": 1,
    "mv-0c:verrors:schema": 1,
    # chunk 0D
    "mv-0d:models": 10,
    "mv-0d:values": 112,
    # chunk 0E
    "mv-0e:models": 9,
    "mv-0e:values": 121,
    # chunk 0F
    "mv-0f:models": 9,
    "mv-0f:values": 107,
    # chunk 10
    "mv-10:js2json": 1,
    "mv-10:models": 9,
    "mv-10:values": 120,
    # chunk 11
    "mv-11:models": 8,
    "mv-11:values": 140,
    "mv-11:verrors:schema": 27,
    # chunk 12
    "mv-12:models": 10,
    "mv-12:values": 124,
    # chunk 13
    "mv-13:js2json": 2,
    "mv-13:models": 12,
    "mv-13:values": 91,
    "mv-13:errors.js": 1,
    "mv-13:errors.sql": 1,
    "mv-13:errors.pl": 1,
    "mv-13:verrors:schema": 1,
    # chunk 14
    "mv-14:models": 12,
    "mv-14:values": 84,
    "mv-14:errors.js": 6,
    "mv-14:errors.sql": 6,
    "mv-14:errors.pl": 6,
    "mv-14:verrors:schema": 6,
    # chunk 15
    "mv-15:js2json": 2,
    "mv-15:models": 12,
    "mv-15:values": 133,
    "mv-15:errors.js": 1,
    "mv-15:errors.sql": 1,
    "mv-15:errors.pl": 1,
    "mv-15:verrors:schema": 9,
    # chunk 16
    "mv-16:models": 11,
    "mv-16:values": 100,
    "mv-16:errors.js": 1,
    "mv-16:errors.sql": 1,
    "mv-16:errors.pl": 1,
    "mv-16:verrors:schema": 1,
    # chunk 17
    "mv-17:models": 12,
    "mv-17:values": 145,
    "mv-17:errors.js": 2,
    "mv-17:errors.sql": 2,
    "mv-17:errors.pl": 2,
    "mv-17:verrors:schema": 2,
    # chunk 18
    "mv-18:js2json": 3,
    "mv-18:yaml2json": 1,
    "mv-18:models": 10,
    "mv-18:values": 93,
    # chunk 19
    "mv-19:models": 9,
    "mv-19:values": 110,
    # chunk 1A
    "mv-1a:models": 10,
    "mv-1a:values": 132,
    "mv-1a:errors.js": 2,
    "mv-1a:errors.sql": 2,
    "mv-1a:errors.pl": 2,
    "mv-1a:verrors:schema": 3,
    # chunk 1B
    "mv-1b:models": 10,
    "mv-1b:values": 68,
    "mv-1b:errors.js": 13,
    "mv-1b:errors.sql": 13,
    "mv-1b:errors.pl": 13,
    "mv-1b:verrors:schema": 13,
    # chunk 1C
    "mv-1c:models": 6,
    "mv-1c:models:errors-jsg": 4,
    "mv-1c:values": 77,
    "mv-1c:verrors:schema": 32,
    # chunk 1D
    # FIXME schema missing Schema
    "mv-1d:models": 5,
    "mv-1d:values": 45,
    "mv-1d:verrors:schema": 9,
    # chunk 1E
    "mv-1e:models": 10,
    "mv-1e:values": 151,
    "mv-1e:errors.js": 1,
    "mv-1e:errors.sql": 2,
    "mv-1e:errors.pl": 1,
    "mv-1e:errors.java": 2,
    "mv-1e:verrors:schema": 15,
    # chunk 1F
    "mv-1f:models": 9,
    "mv-1f:values": 137,
    "mv-1f:verrors:schema": 43,
    # chunk 20
    "mv-20:models": 9,
    "mv-20:values": 112,
    "mv-20:verrors:schema": 17,
    # check 21
    "mv-21:models": 8,
    "mv-21:values": 192,
    "mv-21:verrors:schema": 88,
    # mv-22
    "mv-22:models": 6,
    "mv-22:values": 709,
    "mv-22:verrors:schema": 36,
    # mv-23
    "mv-23:models": 4,
    "mv-23:values": 83,
    # mv-24
    "mv-24:cmp-opts": {"report": False},
    "mv-24:models": 5,
    "mv-24:values": 127,
    # mv-25
    "mv-25:cmp-opts": {"report": False},
    "mv-25:models": 4,
    "mv-25:values": 59,
    # miscellaneous tests
    "bads:models": 58,
    # tests json models of json schema versions
    "draft3:jsts": 105,
    "draft4:jsts": 159,
    "draft6:jsts": 231,
    "draft7:jsts": 254,
    "draft2019-09:jsts": 361,
    "draft2020-12:jsts": 368,
    "draft-next:jsts": 365,
}


#
# LOCAL TEST UTILS
#
def path2file(fname: str) -> str:
    return fname.replace("/", "_").replace(".", "_")


def dirmap(dname) -> dict[str, str]:
    return {
        "https://json-model.org/models/": "../models/",
        "./": f"./{dname}/",
    }

def file_is_newer(f1: str, f2: str) -> bool:
    return os.path.getmtime(f1) > os.path.getmtime(f2)

def has_exec(program: str) -> bool:
    return os.system(f"type {program}") == 0

#
# LOCAL FIXTURES
#
@pytest.fixture(
    # all test directories
    params=[
        "./ref",
        "./mv-00", "./mv-01", "./mv-02", "./mv-03", "./mv-04",
        "./mv-05", "./mv-06", "./mv-07", "./mv-08", "./mv-09",
        "./mv-0a", "./mv-0b", "./mv-0c", "./mv-0d", "./mv-0e",
        "./mv-0f", "./mv-10", "./mv-11", "./mv-12", "./mv-13",
        "./mv-14", "./mv-15", "./mv-16", "./mv-17", "./mv-18",
        "./mv-19", "./mv-1a", "./mv-1b", "./mv-1c", "./mv-1d",
        "./mv-1e", "./mv-1f", "./mv-20", "./mv-21", "./mv-22",
        "./mv-23", "./mv-24", "./mv-25",
    ]
)
def directory(request):
    return pathlib.Path(request.param)


@pytest.fixture(scope="session")
def tmp_dir():
    tmp = os.environ.get("TMPDIR", "/dev/shm")
    user = os.environ.get("USER", "hobbes")
    tmp_dir = f"{tmp}/{user}"
    # if there is a little race it probably does not matter
    if not os.path.exists(tmp_dir):
        try:
            os.mkdir(tmp_dir)
            os.chmod(tmp_dir, 0o700)
        except Exception as e:
            log.warning(f"tmp_dir: {e}")
    yield tmp_dir
    # could cleanup


@pytest.fixture(params=["py", "c", "js", "sql"])
def language(request):
    return request.param


@pytest.fixture(scope="session")
def clibjm(tmp_dir):
    """Compile JSON Model C runtime library."""

    jm_lock = f"{tmp_dir}/clibjm.lock"
    jm_lib = f"{tmp_dir}/json-model.o"
    jm_main = f"{tmp_dir}/main.o"

    src_dir = "../json_model/runtime/c"
    src_lib = f"{src_dir}/json-model.c"
    src_main = f"{src_dir}/main.c"

    from json_model.script import (
        DEFAULT_CC, DEFAULT_CFLAGS, DEFAULT_LDFLAGS_CRE2 as DEFAULT_LDFLAGS
    )

    # compilation settings with re2
    cc = os.environ.get("CC", DEFAULT_CC)
    cppflags = os.environ.get("CPPFLAGS", f"-I{src_dir} -DCHECK_FUNCTION_NAME=check_model")
    cppflags += " -DREGEX_ENGINE_RE2"
    cflags = os.environ.get("CFLAGS", DEFAULT_CFLAGS)
    ldflags = os.environ.get("LDFLAGS", f"{jm_main} {jm_lib} " + DEFAULT_LDFLAGS)


    # compile library once
    with filelock.FileLock(jm_lock):
        if not os.path.exists(jm_lib) or file_is_newer(src_lib, jm_lib):
            status = os.system(f"{cc} {cppflags} {cflags} {src_lib} -o {jm_lib} -c")
            assert status == 0, f"support library compilation"

        if not os.path.exists(jm_main) or file_is_newer(src_main, jm_main):
            status = os.system(f"{cc} {cppflags} {cflags} {src_main} -o {jm_main} -c")
            assert status == 0, f"main frontend compilation"

    yield {
        "tmp": tmp_dir,
        "lock": jm_lock,
        "lib": jm_lib,
        "main": jm_main,
        "cc": cc,
        "cppflags": cppflags,
        "cflags": cflags,
        "ldflags": ldflags,
    }

    # FIXME cleanup is broken because of parallel runs
    # os.remove(jm_lib)
    # os.remove(jm_main)


@pytest.fixture(scope="session")
def jmchecker(clibjm):
    """Compile JSON Model C checker."""

    # compilation settings
    cc, cppflags, cflags, ldflags = \
        clibjm["cc"], clibjm["cppflags"], clibjm["cflags"], clibjm["ldflags"],
    # files
    tmp_dir, lock_file, jm_lib, jm_main = \
        clibjm["tmp"], clibjm["lock"], clibjm["lib"], clibjm["main"]

    assert os.path.isfile(jm_lib), "available support lib"
    assert os.path.isfile(jm_main), "available support main"

    model_c = "ref/json-model.c"
    fexec = f"{tmp_dir}/json_model_check"

    with filelock.FileLock(lock_file):
        if not os.path.exists(fexec) or file_is_newer(model_c, fexec):
            status = os.system(f"{cc} {cppflags} {cflags} {model_c} {ldflags} -o {fexec}")
            assert status == 0, f"{model_c} compilation success"

    yield fexec

    # FIXME cleanup
    # os.remove(fexec)

#
# GENERATED STUFF
#
def check_generated(directory: pathlib.Path, name: str, suffix: str,
                    generate, srcsuff: str = ".model.json", expect: int|None = None):

    """Generic test against generated stuff."""

    assert callable(generate)
    ntests = 0

    for fpath in sorted(directory.glob(f"*{suffix}")):
        fname = "./" + str(fpath)
        mname = fname.replace(suffix, srcsuff)
        fin = fname.replace(suffix, "").replace(f"./{str(directory)}/", "./")
        log.debug(f"{name}[{directory}]: {fin}")

        if not fpath.stat().st_size:
            log.warning(f"skipping empty generated file: {fname}")
            continue
        if not pathlib.Path(mname).exists():
            log.warning(f"skipping missing model file: {mname}")
            continue
        ntests += 1
        try:
            with open(fname) as f:
                ref = f.read()
                if fname.endswith(".json"):
                    ref = json.loads(ref)
            out = generate(fin)
        except Exception as e:
            out = { "ERROR": str(e) }
        assert out == ref

    expected = expect if expect is not None else EXPECT.get(f"{directory}:models", 0)
    assert ntests == expected 


def test_2json(directory):

    """JavaScript and YaML conversion to JSON."""
    resolver = Resolver(None, dirmap(directory))

    def generate_json(fmodel: str):
        return resolver(fmodel, follow=True)

    check_generated(directory, "js2json", ".model.json", generate_json, ".model.js",
                    EXPECT.get(f"{directory}:js2json", 0))
    check_generated(directory, "yaml2json", ".model.json", generate_json, ".model.yaml",
                    EXPECT.get(f"{directory}:yaml2json", 0))


def test_preproc(directory):
    """Preprocessing optimizations."""

    resolver = Resolver(None, dirmap(directory))
    options = EXPECT.get(f"{directory}:mod-opts", {})

    def generate_preproc(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True, **options)
        return jm.toModel(True)

    check_generated(directory, "preproc", ".PO.json", generate_preproc)


def test_schema(directory):
    """Model to Schema conversion."""

    resolver = Resolver(None, dirmap(directory))
    options = EXPECT.get(f"{directory}:mod-opts", {})

    def generate_schema(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True, **options)
        return jm.toSchema(True, version=None)

    check_generated(directory, "schema", ".schema.json", generate_schema)


def test_lang(directory, language):
    """Check compiled sources."""
    resolver = Resolver(None, dirmap(directory))
    mod_opts = EXPECT.get(f"{directory}:mod-opts", {})
    cmp_opts = EXPECT.get(f"{directory}:cmp-opts", {})
    suffix = f".{language}"

    # default are different for PL/pgSQL
    if "report" not in cmp_opts:
        cmp_opts["report"] = True if language != "sql" else False

    def generate_language(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True, **mod_opts)
        code = xstatic_compile(jm, "check_model", lang=language,
            map_threshold=5, short_version=True, **cmp_opts)
        return str(code)

    check_generated(directory, f"lang-{language}", f".{language}", generate_language)


#
# STATIC CHECK MODELS AGAINST VALUES
#

def check_values(directory: pathlib.Path, name: str, suffix: str, refsuff: str,
                 generate: typing.Callable[[str], str], opts: str = ""):
    """Generic value testing."""
    ntests, nvalues, nerrors = 0, 0, 0

    # try all sources
    for fpath in sorted(directory.glob(f"*{suffix}")):
        out = ""
        fname = f"./{fpath}"

        # skip *.model.js
        if fname.endswith(".model.js"):
            continue
        fexec = generate(fname)
        log.debug(f"{name}[{directory}]: {fname} ({fexec})")
        ntests += 1

        # run on all validations
        bname = fname.replace(suffix, "").split("/", -1)[-1]

        # true/false value files
        values = list(directory.glob(f"{bname}.*.true.json")) + \
                 list(directory.glob(f"{bname}.*.false.json"))
        vfiles = " ".join(sorted(str(f) for f in values))

        if values:

            for line in os.popen(f"{fexec} {opts} --no-report {vfiles}"):
                nvalues += 1
                assert re.search(r"(\.true\.json(\[\d+])?: PASS|\.false\.json(\[\d+])?: FAIL)$", line) is not None, \
                    f"result as expected: {line}"

            with os.popen(f"{fexec} {opts} {vfiles} | cut -d/ -f2-") as p:
                out = p.read()

        # values file
        vfile = directory.joinpath(bname + ".values.json")

        if vfile.exists():

            with os.popen(f"{fexec} {opts} -t {vfile} | cut -d/ -f2-") as p:
                result = p.read()
            out += result

            for line in result.split("\n")[:-1]:
                nvalues += 1
                if ": ERROR" not in line and (": PASS" in line or ": FAIL" in line):
                    assert True, "PASS/FAIL expectation ok"
                else:
                    log.error(f"error in {directory}: {line}")
                    nerrors += 1

            ref_file = fname.replace(suffix, refsuff)
            with open(ref_file) as r:
                ref = r.read()

            assert out == ref

        # cleanup
        if suffix.endswith(".c"):
            os.remove(fexec)

    assert ntests == EXPECT.get(f"{directory}:models", 0)
    assert nvalues == EXPECT.get(f"{directory}:values", 0)
    assert nerrors == EXPECT.get(f"{directory}:errors{suffix}", 0)


def test_sta_c(directory, clibjm):
    """Check generated C code with test value files."""

    # compilation settings
    cc, cppflags, cflags, ldflags = \
        clibjm["cc"], clibjm["cppflags"], clibjm["cflags"], clibjm["ldflags"],
    # files
    tmp_dir, jm_lib, jm_main = clibjm["tmp"], clibjm["lib"], clibjm["main"]

    assert os.path.isfile(jm_lib), "available support lib"
    assert os.path.isfile(jm_main), "available support main"

    def gen_exec(fname: str):
        fexec = f"{tmp_dir}/{path2file(fname)}.out"
        status = os.system(f"{cc} {cppflags} {cflags} {fname} {ldflags} -o {fexec}")
        assert status == 0, f"{fname} compilation success"
        return fexec

    check_values(directory, "sta-c", ".c", ".c.check", gen_exec, "-r")

def test_sta_py(directory):
    """Check generated Python scripts with test value files."""
    check_values(directory, "sta-py", ".py", ".py.check", lambda f: f, "-r")

@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_sta_js(directory):
    """Check generated JS scripts with test value files."""
    check_values(directory, "sta-js", ".js", ".js.check", lambda f: f, "-r")

@pytest.mark.skipif(not has_exec("psql"), reason="missing psql")
def test_sta_sql(directory):
    """Check generated SQL scripts with test value files."""
    check_values(directory, "sta-sql", ".sql", ".sql.check",
                 lambda f: f"./test_sql.sh {f}")

@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_sta_pl(directory):
    """Check generated Perl scripts with test value files."""
    check_values(directory, "sta-pl", ".pl", ".pl.check", lambda f: f)

@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_sta_java(directory, tmp_dir):
    """Check generated Java programs with test value files."""
    check_values(directory, "sta-java", ".java", ".java.check",
                 lambda f: f"./test_java.sh {f}", "-r")

#
# DYNAMIC CHECKS AGAINST VALUES
#
class NotSupportedError(BaseException):
    pass

type GenChecker = typing.Callable[[str], typing.Callable[[typing.Any, str], bool]]

def run_dyn(directory: pathlib.Path, gen_checker: GenChecker, name: str):
    """Check dynamic checker with test values."""

    nfiles, ntests, nmerrors, nverrors = 0, 0, 0, 0

    for fpath in sorted(directory.glob("*.model.json")):
        nfiles += 1

        fmodel = f"./{fpath}"
        model = fmodel.replace(f"{directory}/", "").replace(".model.json", "")
        log.debug(f"dyn[{directory}]: {model} ({fpath})")

        checker = gen_checker(f"./{fpath}")
        if checker is None:
            log.error(f"{name}: cannot generate checker for {fpath}")
            nmerrors += 1

        # process true/false files
        for vpath in sorted(directory.glob(f"{model}.*.*.json")):
            spath = str(vpath)
            assert spath.endswith(".true.json") or spath.endswith(".false.json")
            ntests += 1
            if checker is None:
                nverrors += 1
                continue
            value = json.loads(vpath.read_text())
            if spath.endswith(".true.json"):
                assert checker(value)
            else:
                assert not checker(value)

        # process values file
        vfile = directory.joinpath(f"{model}.values.json")
        if vfile.exists():
            values = json.loads(vfile.read_text())
            assert isinstance(values, list)

            for index, tvect in enumerate(values):
                if isinstance(tvect, str):
                    continue  # skip comments
                ntests += 1
                if checker is None:
                    nverrors += 1
                    continue

                log.debug(f"{model}.values.json[{index}]")
                assert len(tvect) in (2, 3)
                if len(tvect) == 3:
                    expect, case, value = tvect
                else:
                    expect, value = tvect
                    case = ""
                assert isinstance(expect, bool) and isinstance(case, str)

                try:
                    if expect:
                        assert checker(value, case)
                    else:
                        assert not checker(value, case)
                except NotSupportedError as e:
                    log.error(f"{name} not supported error on {model}.values.json[{index}]")
                    nverrors += 1
                except AssertionError as e:
                    log.error(f"{name} assert error on {model}.values.json[{index}]")
                    nverrors += 1
                except Exception as e:
                    log.error(f"{name} internal checker error on {model}.values.json[{index}]")
                    nverrors += 1

    assert nfiles == EXPECT.get(f"{directory}:models", 0)
    assert ntests == EXPECT.get(f"{directory}:values", 0)
    assert nmerrors == EXPECT.get(f"{directory}:merrors:{name}", 0)
    assert nverrors == EXPECT.get(f"{directory}:verrors:{name}", 0)


def test_dyn_py(directory: pathlib.Path):

    resolver = Resolver(None, dirmap(directory))
    options = EXPECT.get(f"{directory}:mod-opts", {})

    def gen_py_checker(fmodel: str):
        assert fmodel.endswith(".model.json")
        model = fmodel.replace(".model.json", "").replace(f"{directory}/", "")
        return model_checker_from_url(model, resolver=resolver, follow=True, debug=False, **options)

    run_dyn(directory, gen_py_checker, "dynpy")

def test_dyn_json_schema(directory: pathlib.Path):
    """Test generated JSON Schema with test value files."""

    # Some test cases cannot validate because:
    # 1. they require strict int/float (feature)
    # 2. there is no direct schema for a model (missing feature)
    # 3. the model contains external references (untranslated, should be inlined?)
    # 4. the schema is plain wrong (bug)
    # for now, just skip the corresponding directories

    import jsonschema

    def gen_jschema_checker(fmodel: str):
        assert fmodel.endswith(".model.json")

        # load schema
        fschema = fmodel.replace(".model.json", ".schema.json")
        with open(fschema) as f:
            js = json.loads(f.read())

        if isinstance(js, dict) and "ERROR" in js:
            log.info(f"skipping error {fschema}")
            return None

        # set version just in case
        if isinstance(js, dict) and "$schema" not in js:
            js["$schema"] = "https://json-schema.org/draft/2020-12/schema"

        # native checker
        try:
            jsc = jsonschema.Draft202012Validator(js, format_checker=jsonschema.FormatChecker())
        except Exception:
            log.error(f"cannot compile schema {fschema}")
            return None

        def checker(val, name: str = ""):
            if name == "":
                return jsc.is_valid(val)
            raise NotSupportedError("cannot check sub-model with a schema")

        return checker

    run_dyn(directory, gen_jschema_checker, "schema")

#
# CHECK MODELS AGAINST META MODEL(S)
#

def check_models(directory, jmchecker: str, errors: int = 0):
    ntests, nerrors = 0, 0
    models = " ".join(map(str, sorted(directory.glob(f"*.model.json"))))
    log.error(f"{jmchecker} {models}")
    for line in os.popen(f"{jmchecker} {models}"):
        ntests += 1
        if ": PASS" not in line:
            nerrors += 1
    assert ntests == EXPECT.get(f"{directory}:models", 0)
    assert nerrors == errors

@pytest.mark.skipif(not has_exec("cc"), reason="missing cc")
def test_models_c(directory, jmchecker):
    check_models(directory, jmchecker)

def test_models_py(directory):
    check_models(directory, "./ref/json-model.py")

@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_models_js(directory):
    check_models(directory, "./ref/json-model.js")

@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_models_pl(directory):
    check_models(directory, "./ref/json-model.pl")

@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_models_java(directory):
    check_models(directory, "./test_java.sh ./ref/json-model.java")

def test_models_jsm(directory):
    check_models(directory, "jsu-check --quiet json-model.schema.json")

def test_models_jsg(directory):
    check_models(directory, "jsu-check -e jschon --quiet ./ref/json-model.schema.json",
                 EXPECT.get(f"{directory}:models:errors-jsg", 0))

def test_models_dpy(directory):
    """Check test model conformity to JSON Model meta model."""
    resolver = Resolver(None, dirmap(directory))
    checker = model_checker_from_url("https://json-model.org/models/json-model", resolver=resolver)
    ntests = 0

    for fpath in sorted(directory.glob(f"*.model.json")):
        fname = "./" + str(fpath)
        log.debug(f"models[{directory}]: {fname}")
        with open(fname) as f:
            model = json.load(f)
        report = []
        ntests += 1
        assert checker(model)  # no report
        assert checker(model, "", report)  # with report

    assert ntests == EXPECT.get(f"{directory}:models", 0)


#
# BAD MODELS
#

def check_bads(jmchecker: str):
    ntests = 0
    bads_dir = pathlib.Path("./bads")
    nbad_models = " ".join(map(str, sorted(bads_dir.glob(f"[a-z]*.model.json"))))
    for line in os.popen(f"{jmchecker} {nbad_models}"):
        ntests += 1
        assert ": FAIL" in line
    _bad_models = " ".join(map(str, sorted(bads_dir.glob(f"_*.model.json"))))
    for line in os.popen(f"{jmchecker} {_bad_models}"):
        ntests += 1
        assert ": PASS" in line
    xbad_models = " ".join(map(str, sorted(bads_dir.glob(f"X*.model.json"))))
    for line in os.popen(f"{jmchecker} {xbad_models}"):
        ntests += 1
        assert ": ERROR" in line
    assert ntests == EXPECT.get(f"bads:models", 0)

@pytest.mark.skipif(not has_exec("cc"), reason="missing cc")
def test_bads_c(jmchecker):
    check_bads(jmchecker)

def test_bads_py():
    check_bads("./ref/json-model.py")

@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_bads_js():
    check_bads("./ref/json-model.js")

@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_bads_pl():
    check_bads("./ref/json-model.js")

@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_bads_java():
    check_bads("./test_java.sh ./ref/json-model.java")

def test_bads_jsm():
    check_bads("jsu-check --quiet ./json-model.schema.json")

def test_bads_jsg():
    check_bads("jsu-check -e jschon --quiet ./ref/json-model.schema.json")

#
# JSON SCHEMA DRAFT TESTS
#
def json_schema_test_suite(version, fmodel):
    ntests = 0
    # load model
    checker = model_checker_from_url(fmodel, auto=True)
    # run all tests
    path = pathlib.Path(f"./JSON-Schema-Test-Suite/tests/{version}")
    if not path.is_dir():
        pytest.skip("missing test suite directory")
    for jstest in path.glob("*.json"):
        log.info(f"considering file {jstest}")
        with open(jstest) as f:
            tests = json.load(f)
            assert isinstance(tests, list)
            for idx, test in enumerate(tests):
                description, schema = test["description"], test["schema"]
                log.debug(f"checking {jstest}[{idx}] {description}")
                ntests += 1
                reasons = []
                okay = checker(schema, "", reasons)
                assert okay, f"{jstest}[{idx}] is valid for {fmodel} ({reasons})"
    assert ntests == EXPECT.get(f"{version}:jsts", 0)

def test_draft3():
    # strict: fails on infinite-loop-detection.json[0]
    # nesting: fails on ref.json[7]
    json_schema_test_suite("draft3", "../models/json-schema-draft-03-fuzzy.model.json")

def test_draft4():
    # strict/nesting: fails on infinite-loop-detection.json[0]
    json_schema_test_suite("draft4", "../models/json-schema-draft-04-fuzzy.model.json")

def test_draft6():
    # strict: fails on ref.json[6]
    json_schema_test_suite("draft6", "../models/json-schema-draft-06-fuzzy.model.json")

def test_draft7():
    json_schema_test_suite("draft7", "../models/json-schema-draft-07.model.json")

def test_draft8():
    # strict: fails on vocabulary.json[0] (meta schema url)
    json_schema_test_suite("draft2019-09", "../models/json-schema-draft-2019-09-fuzzy.model.json")

def test_draft9():
    # strict: fails on vocabulary.json[0] (meta schema url)
    json_schema_test_suite("draft2020-12", "../models/json-schema-draft-2020-12-fuzzy.model.json")

def test_draft_next():
    json_schema_test_suite("draft-next", "../models/json-schema-draft-next.model.json")
