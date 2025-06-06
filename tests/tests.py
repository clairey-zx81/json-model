import os
import re
import json
import pathlib
import logging
import pytest
import filelock

from json_model.script import model_from_url, model_checker_from_url
from json_model.resolver import Resolver
from json_model.xstatic import xstatic_compile

logging.basicConfig()
log = logging.getLogger("test")
log.setLevel(logging.DEBUG)
# log.setLevel(logging.INFO)

#
# PER-DIRECTORY TEST EXPECTATIONS, IN SMALL CHUNKS FOR XDIST
#
EXPECT: dict[str, int] = {
    # reference
    "ref:models": 9,
    "ref:values": 31,
    # chunk 00
    "mv-00:models": 10,
    "mv-00:values": 95,
    # chunk 01
    "mv-01:models": 10,
    "mv-01:values": 100,
    # chunk 02
    "mv-02:js2json": 1,
    "mv-02:models": 10,
    "mv-02:values": 122,
    # chunk 03
    "mv-03:js2json": 1,
    "mv-03:models": 10,
    "mv-03:values": 78,
    # chunk 04
    "mv-04:js2json": 2,
    "mv-04:models": 8,
    "mv-04:values": 98,
    # chunk 05
    "mv-05:models": 9,
    "mv-05:values": 0,
    # chunk 06
    "mv-06:models": 8,
    "mv-06:values": 0,
    # chunk 07
    "mv-07:models": 5,
    "mv-07:values": 0,
    # chunk 08
    "mv-08:models": 9,
    "mv-08:values": 116,
    # chunk 09
    "mv-09:models": 10,
    "mv-09:values": 45,
    # chunk 0A
    "mv-0a:models": 10,
    "mv-0a:values": 74,
    # chunk 0B
    "mv-0b:models": 9,
    "mv-0b:values": 0,
    # chunk 0C
    "mv-0c:models": 10,
    "mv-0c:values": 0,
    # chunk 0D
    "mv-0d:models": 10,
    "mv-0d:values": 0,
    # chunk 0E
    "mv-0e:models": 9,
    "mv-0e:values": 20,
    # chunk 0F
    "mv-0f:models": 9,
    "mv-0f:values": 0,
    # chunk 10
    "mv-10:js2json": 1,
    "mv-10:models": 9,
    "mv-10:values": 53,
    # chunk 11
    "mv-11:models": 9,
    "mv-11:values": 0,
    # chunk 12
    "mv-12:models": 10,
    "mv-12:values": 0,
    # chunk 13
    "mv-13:js2json": 2,
    "mv-13:models": 12,
    "mv-13:values": 81,
    # chunk 14
    "mv-14:models": 12,
    "mv-14:values": 84,
    # chunk 15
    "mv-15:js2json": 2,
    "mv-15:models": 12,
    "mv-15:values": 102,
    # chunk 16
    "mv-16:models": 11,
    "mv-16:values": 100,
    # chunk 17
    "mv-17:models": 12,
    "mv-17:values": 136,
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
    # chunk 1B
    "mv-1b:models": 10,
    "mv-1b:values": 68,
    # chunk 1C
    "mv-1c:models": 6,
    "mv-1c:values": 64,
    # chunk 1D
    "mv-1d:models": 5,
    "mv-1d:values": 0,
    # chunk 1E
    "mv-1e:models": 7,
    "mv-1e:values": 91,
    # miscellaneous tests
    # miscellaneous tests
    "bads:models": 54,
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

#
# LOCAL FIXTURES
#
@pytest.fixture(
    params=[
        "./ref",
        "./mv-00", "./mv-01", "./mv-02", "./mv-03",
        "./mv-04", "./mv-05", "./mv-06", "./mv-07",
        "./mv-08", "./mv-09", "./mv-0a", "./mv-0b",
        "./mv-0c", "./mv-0d", "./mv-0e", "./mv-0f",
        "./mv-10", "./mv-11", "./mv-12", "./mv-13",
        "./mv-14", "./mv-15", "./mv-16", "./mv-17",
        "./mv-18", "./mv-19", "./mv-1a", "./mv-1b",
        "./mv-1c", "./mv-1d", "./mv-1e", # "./mv-1f",
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


@pytest.fixture(params=["py", "c"])
def language(request):
    return request.param


@pytest.fixture(scope="session")
def clibjm(tmp_dir):
    """Compile JSON Model C runtime library."""

    jm_lock = f"{tmp_dir}/clibjm.lock"
    jm_lib = f"{tmp_dir}/json-model.o"
    jm_main = f"{tmp_dir}/main.o"

    src_dir = "../json_model/runtime"
    src_lib = f"{src_dir}/json-model.c"
    src_main = f"{src_dir}/main.c"

    from json_model.script import DEFAULT_CC, DEFAULT_CFLAGS, DEFAULT_LDFLAGS

    # compilation settings
    cc = os.environ.get("CC", DEFAULT_CC)
    cppflags = os.environ.get("CPPFLAGS", f"-I{src_dir} -DCHECK_FUNCTION_NAME=check_model")
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

    def generate_preproc(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True)
        return jm.toModel(True)

    check_generated(directory, "preproc", ".PO.json", generate_preproc)


def test_schema(directory):
    """Model to Schema conversion."""

    resolver = Resolver(None, dirmap(directory))

    def generate_schema(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True)
        return jm.toSchema(True)

    check_generated(directory, "schema", ".schema.json", generate_schema)


def test_lang(directory, language):
    """Check compiled sources."""
    resolver = Resolver(None, dirmap(directory))
    suffix = f".{language}"

    def generate_language(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True)
        return str(xstatic_compile(jm, "check_model", lang=language))

    check_generated(directory, f"lang-{language}", f".{language}", generate_language)


#
# STATIC CHECK MODELS AGAINST VALUES
#

def check_values(directory: pathlib.Path, name: str, suffix: str, refsuff: str, generate):
    """Generic value testing."""
    ntests, nvalues = 0, 0

    # try all sources
    for fpath in sorted(directory.glob(f"*{suffix}")):
        fname = f"./{fpath}"
        fexec = generate(fname)
        log.debug(f"{name}[{directory}]: {fname} ({fexec})")
        ntests += 1

        # run on all validations
        bname = fname.replace(suffix, "").split("/", -1)[-1]

        values = list(directory.glob(f"{bname}.*.true.json")) + \
                 list(directory.glob(f"{bname}.*.false.json"))
        vfiles = " ".join(sorted(str(f) for f in values))

        for line in os.popen(f"{fexec} {vfiles}"):
            nvalues += 1
            assert re.search(r"(\.true\.json: PASS|\.false\.json: FAIL)$", line) is not None, \
                f"result as expected: {line}"

        vfile = directory.joinpath(bname + ".values.json")
        if vfile.exists():
            for line in os.popen(f"{fexec} -t {vfile}"):
                nvalues += 1
                assert ": ERROR" not in line and (": PASS" in line or ": FAIL" in line)

        # run again with reporting
        with os.popen(f"{fexec} -r {vfiles} | cut -d/ -f2-") as p:
            out = p.read()

        if vfile.exists():
            with os.popen(f"{fexec} -tr {vfile} | cut -d/ -f2-") as p:
                out += p.read()

        ref_file = fname.replace(suffix, refsuff)
        with open(ref_file) as r:
            ref = r.read()

        assert out == ref

        # cleanup
        if suffix.endswith(".c"):
            os.remove(fexec)

    assert ntests == EXPECT.get(f"{directory}:models", 0)
    assert nvalues == EXPECT.get(f"{directory}:values", 0)


def test_sta_c(directory, clibjm):
    """Check generated C code with test value files."""

    # compilation settings
    cc, cppflags, cflags, ldflags = \
        clibjm["cc"], clibjm["cppflags"], clibjm["cflags"], clibjm["ldflags"],
    # files
    tmp_dir, jm_lib, jm_main = clibjm["tmp"], clibjm["lib"], clibjm["main"]

    assert os.path.isfile(jm_lib), "available support lib"
    assert os.path.isfile(jm_main), "available support main"

    def generate_exec(fname: str):
        fexec = f"{tmp_dir}/{path2file(fname)}.out"
        status = os.system(f"{cc} {cppflags} {cflags} {fname} {ldflags} -o {fexec}")
        assert status == 0, f"{fname} compilation success"
        return fexec

    check_values(directory, "sta-c", ".c", ".c-check.out", generate_exec)


def test_sta_py(directory):
    """Check generated Python scripts with test value files."""
    check_values(directory, "sta-py", ".py", ".py-check.out", lambda f: f)


#
# DYNAMIC CHECKS AGAINST VALUES
#
class NotSupportedError(BaseException):
    pass


def run_dyn(directory, gen_checker):
    """Check dynamic checker with test values."""
    nfiles, ntests = 0, 0
    for fpath in sorted(directory.glob("*.model.json")):
        nfiles += 1

        fmodel = f"./{fpath}"
        model = fmodel.replace(f"{directory}/", "").replace(".model.json", "")

        log.debug(f"dyn[{directory}]: {model} ({fpath})")

        checker = gen_checker(f"./{fpath}")

        # true/false files
        for vpath in sorted(directory.glob(f"{model}.*.*.json")):
            spath = str(vpath)
            assert spath.endswith(".true.json") or spath.endswith(".false.json")
            ntests += 1
            value = json.loads(vpath.read_text())
            if spath.endswith(".true.json"):
                assert checker(value)
            else:
                assert not checker(value)

        # values file
        vfile = directory.joinpath(f"{model}.values.json")
        if vfile.exists():
            values = json.loads(vfile.read_text())
            assert isinstance(values, list)
            for index, tvect in enumerate(values):
                if isinstance(tvect, str):
                    continue  # skip comments
                ntests += 1
                log.debug(f"{model}.values.json[{index}]")
                assert len(tvect) in (2, 3)
                if len(tvect) == 3:
                    expect, case, value = tvect
                else:
                    expect, value = tvect
                    case = ""
                assert isinstance(expect, bool)
                try:
                    if expect:
                        assert checker(value, case)
                    else:
                        assert not checker(value, case)
                except NotSupportedError as e:
                    # simply ignore
                    pass

    assert nfiles == EXPECT.get(f"{directory}:models", 0)
    assert ntests == EXPECT.get(f"{directory}:values", 0)


def test_dyn_py(directory):

    resolver = Resolver(None, dirmap(directory))

    def gen_py_checker(fmodel: str):
        assert fmodel.endswith(".model.json")
        model = fmodel.replace(".model.json", "").replace(f"{directory}/", "")
        return model_checker_from_url(model, resolver=resolver, follow=True, debug=False)

    run_dyn(directory, gen_py_checker)


def test_dyn_js(directory):
    """Test generated JSON Schema with test value files."""

    # Some test cases cannot validate because:
    # 1. they require strict int/float (feature)
    # 2. there is no direct schema for a model (feature)
    # 3. the schema is wrong (bug)
    # for now, just skip the corresponding directories
    log.debug(f"directory: {str(directory)}")
    if str(directory) in {
                "mv-00", "mv-01", "mv-03", "mv-04",
                "mv-08", "mv-09", "mv-0a", "mv-13", "mv-14",
                "mv-15", "mv-16", "mv-17", "mv-19", "mv-1a",
                "mv-1b", "mv-1c", "mv-1e", "ref",
            }:
        pytest.mark.skip(reason="wip")
        return

    import jsonschema

    def gen_js_checker(fmodel: str):
        assert fmodel.endswith(".model.json")

        # load schema
        fschema = fmodel.replace(".model.json", ".schema.json")
        with open(fschema) as f:
            js = json.loads(f.read())

        # set version just in case
        if isinstance(js, dict) and "$schema" not in js:
            js["$schema"] = "https://json-schema.org/draft/2020-12/schema"

        # native checker
        jsc = jsonschema.Draft202012Validator(js, format_checker=jsonschema.FormatChecker())

        def checker(val, name: str = ""):
            if name == "":
                return jsc.is_valid(val)
            raise NotSupportedError("cannot check sub-model with a schema")

        return checker

    run_dyn(directory, gen_js_checker)

#
# CHECK MODELS AGAINST META MODEL(S)
#

def check_models(directory, jmchecker: str):
    ntests = 0
    models = " ".join(map(str, sorted(directory.glob(f"*.model.json"))))
    for line in os.popen(f"{jmchecker} {models}"):
        ntests += 1
        assert ": PASS" in line
    assert ntests == EXPECT.get(f"{directory}:models", 0)

def test_models_c(directory, jmchecker):
    check_models(directory, jmchecker)

def test_models_py(directory):
    check_models(directory, "./ref/json-model.py")

def test_models_jsm(directory):
    check_models(directory, "jsu-check --quiet json-model.schema.json")

def test_models_jsg(directory):
    check_models(directory, "jsu-check --quiet ./ref/json-model.schema.json")

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
    xbad_models = " ".join(map(str, sorted(bads_dir.glob(f"X*.model.json"))))
    _bad_models = " ".join(map(str, sorted(bads_dir.glob(f"_*.model.json"))))
    for line in os.popen(f"{jmchecker} {nbad_models}"):
        ntests += 1
        assert ": FAIL" in line
    for line in os.popen(f"{jmchecker} {_bad_models}"):
        ntests += 1
        assert ": PASS" in line
    for line in os.popen(f"{jmchecker} {xbad_models}"):
        ntests += 1
        assert ": ERROR" in line
    assert ntests == EXPECT.get(f"bads:models", 0)

def test_bads_c(jmchecker):
    check_bads(jmchecker)

def test_bads_py():
    check_bads("./ref/json-model.py")

def test_bads_jsm():
    check_bads("jsu-check --quiet ./json-model.schema.json")

def test_bads_jsg():
    check_bads("jsu-check --quiet ./ref/json-model.schema.json")

#
# JSON SCHEMA DRAFT TESTS
#
def json_schema_test_suite(version, fmodel):
    ntests = 0
    # load model
    checker = model_checker_from_url(fmodel, auto=True)
    # run all tests
    path = pathlib.Path(f"./JSON-Schema-Test-Suite/tests/{version}")
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
