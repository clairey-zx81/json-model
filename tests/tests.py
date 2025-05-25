import os
import re
import json
import pathlib
import logging
import pytest

from json_model.script import model_from_url, model_checker_from_url
from json_model.resolver import Resolver
from json_model.xstatic import xstatic_compile

logging.basicConfig()
log = logging.getLogger("test")
log.setLevel(logging.DEBUG)
# log.setLevel(logging.INFO)

#
# PER-DIRECTORY TEST EXPECTATIONS
#
EXPECT: dict[str, int] = {
    "modval:js2json": 8,
    "modval:yaml2json": 1,
    "modval:models": 116,
    "modval:preproc": 116,
    "modval:schema": 116,
    "modval:lang-c": 116,
    "modval:lang-py": 116,
    "modval:sta-c:tests": 116,
    "modval:sta-py:tests": 116,
    "modval:sta-c:values": 1195,
    "modval:sta-py:values": 1195,
    "basics:js2json": 4,
    "basics:models": 33,
    "basics:preproc": 33,
    "basics:schema": 33,
    "basics:lang-c": 33,
    "basics:lang-py": 33,
    "basics:sta-c:tests": 33,
    "basics:sta-py:tests": 33,
    "basics:sta-c:values": 245,
    "basics:sta-py:values": 245,
    "m2s:schema": 57,
    "m2s:models": 57,
    "rwt:preproc": 45,
    "rwt:models": 46,
    "rwt:schema": 45,
    "rwt:lang-c": 44,
    "rwt:lang-py": 44,
    "rwt:sta-c:tests": 44,
    "rwt:sta-py:tests": 44,
    "rwt:sta-c:values": 136,
    "rwt:sta-py:values": 136,
    "objs:preproc": 1,
    "objs:models": 1,
    "objs:schema": 1,
    "objs:lang-c": 1,
    "objs:lang-py": 1,
    "objs:sta-c:tests": 1,
    "objs:sta-py:tests": 1,
    "objs:sta-c:values": 12,
    "objs:sta-py:values": 12,
    "bads:models": 54,
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

#
# LOCAL FIXTURES
#
@pytest.fixture(params=["./modval", "./m2s", "./rwt", "./basics", "./objs"])
def directory(request):
    return pathlib.Path(request.param)


@pytest.fixture(params=["py", "c"])
def language(request):
    return request.param


@pytest.fixture(scope="session")
def clibjm():

    tmp_dir = "/dev/shm"
    jm_lib = f"{tmp_dir}/json-model.o"
    jm_main = f"{tmp_dir}/main.o"

    src_dir = "../json_model/runtime"
    src_lib = f"{src_dir}/json-model.c"
    src_main = f"{src_dir}/main.c"

    # compilation settings
    cc = os.environ.get("CC", "gcc")
    cppflags = os.environ.get("CPPFLAGS", f"-I{src_dir} -DCHECK_FUNCTION_NAME=check_model")
    cflags = os.environ.get("CFLAGS", "-Wall -Wno-address -O2")
    ldflags = os.environ.get("LDFLAGS", f"{jm_lib} -ljansson -lpcre2-8 {jm_main}")

    # compile library
    status = os.system(f"{cc} {cppflags} {cflags} {src_lib} -o {jm_lib} -c")
    assert status == 0, f"support library compilation"

    status = os.system(f"{cc} {cppflags} {cflags} {src_main} -o {jm_main} -c")
    assert status == 0, f"main frontend compilation"

    yield {
        "tmp": tmp_dir,
        "lib": jm_lib,
        "main": jm_main,
        "cc": cc,
        "cppflags": cppflags,
        "cflags": cflags,
        "ldflags": ldflags,
    }

    # FIXME cleanup
    # os.remove(jm_lib)
    # os.remove(jm_main)


@pytest.fixture(scope="session")
def jmchecker(clibjm):

    # compilation settings
    cc, cppflags, cflags, ldflags = \
        clibjm["cc"], clibjm["cppflags"], clibjm["cflags"], clibjm["ldflags"],
    # files
    tmp_dir, jm_lib, jm_main = clibjm["tmp"], clibjm["lib"], clibjm["main"]

    assert os.path.isfile(jm_lib), "available support lib"
    assert os.path.isfile(jm_main), "available support main"

    model_c = "rwt/json-model.x.c"
    fexec = f"{tmp_dir}/json_model_check"

    # NOTE with parallel runs the file may be generated several time despite the session scope
    if not os.path.exists(fexec):
        status = os.system(f"{cc} {cppflags} {cflags} {model_c} {ldflags} -o {fexec}")
        assert status == 0, f"{model_c} compilation success"

    yield fexec

    # FIXME cleanup
    # os.remove(fexec)

#
# GENERATED STUFF
#
def check_generated(directory: pathlib.Path, name: str, suffix: str,
                    generate, srcsuff: str = ".model.json"):

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

    assert ntests == EXPECT.get(f"{directory}:{name}", 0)


def test_2json(directory):

    """JavaScript and YaML conversion to JSON."""
    resolver = Resolver(None, dirmap(directory))

    def generate_json(fmodel: str):
        return resolver(fmodel, follow=True)

    check_generated(directory, "js2json", ".model.json", generate_json, ".model.js")
    check_generated(directory, "yaml2json", ".model.json", generate_json, ".model.yaml")


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
    suffix = f".x.{language}"

    def generate_language(fmodel: str):
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True)
        return str(xstatic_compile(jm, "check_model", lang=language))

    check_generated(directory, f"lang-{language}", f".x.{language}", generate_language)


#
# CHECK MODELS AGAINST VALUES
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

    assert ntests == EXPECT.get(f"{directory}:{name}:tests", 0)
    assert nvalues == EXPECT.get(f"{directory}:{name}:values", 0)


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
        
    check_values(directory, "sta-c", ".x.c", ".ccheck.out", generate_exec)


def test_sta_py(directory):
    """Check generated Python scripts with test value files."""
    check_values(directory, "sta-py", ".x.py", ".pcheck.out", lambda f: f)


# TODO use check_values?
@pytest.mark.skip(reason="wip")
def test_dyna_py(directory):
    """Check generated python with test values."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for fpath in sorted(directory.glob("*.model.json")):
        fname = f"./{fpath}"
        bname = fname.replace(".model.json", "")
        fin = bname.replace(f"{directory}/", "")
        log.debug(f"dyna-py[{directory}]: {fname} ({fpath})")

        checker = model_checker_from_url(fin, resolver=resolver, follow=True, debug=False)

        # true/false files
        for vpath in sorted(directory.glob(f"{bname}.*.*.json")):
            ntests += 1
            value = json.loads(vpath.read_text())
            assert ".true.json" in vpath or ".false.json" in vpath
            if ".true.json" in vpath:
                assert checker(value)
            else:
                assert not checker(value)

        # values file
        vfile = directory.joinpath(f"{bname}.values.json")
        if vfile.exists():
            values = json.loads(vfile.read_text())
            assert isinstance(values, list)
            for index, tvect in enumerate(values):
                if isinstance(tvect, str):
                    continue  # skip comments
                ntests += 1
                assert isinstance(expect, bool)
                if expect:
                    assert checker(value)
                else:
                    assert not checker(value)

    assert ntests == EXPECT.get(f"{directory}:dyna-py", 0)

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
    check_models(directory, "./rwt/json-model.x.py")

def test_models_jsm(directory):
    check_models(directory, "jsu-check --quiet json-model.schema.json")

def test_models_jsg(directory):
    check_models(directory, "jsu-check --quiet ./rwt/json-model.schema.json")

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
    check_bads("./rwt/json-model.x.py")

def test_bads_jsm():
    check_bads("jsu-check --quiet ./json-model.schema.json")

def test_bads_jsg():
    check_bads("jsu-check --quiet ./rwt/json-model.schema.json")

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

def test_draft3_fuzzy():
    # strict: fail on "definitions"
    # nesting: fail on "definitions"
    json_schema_test_suite("draft3", "../models/json-schema-draft-03-fuzzy.model.json")

def test_draft4_fuzzy():
    # strict: errors on "$comment"
    json_schema_test_suite("draft4", "../models/json-schema-draft-04-fuzzy.model.json")

def test_draft6_fuzzy():
    json_schema_test_suite("draft6", "../models/json-schema-draft-06-fuzzy.model.json")

def test_draft7_fuzzy():
    json_schema_test_suite("draft7", "../models/json-schema-draft-07-fuzzy.model.json")

def test_draft8_fuzzy():
    json_schema_test_suite("draft2019-09", "../models/json-schema-draft-2019-09-fuzzy.model.json")

def test_draft9_fuzzy():
    # strict: error on maxContains with number instead of integer
    json_schema_test_suite("draft2020-12", "../models/json-schema-draft-2020-12-fuzzy.model.json")

def test_draft_next_fuzzy():
    json_schema_test_suite("draft-next", "../models/json-schema-draft-next-fuzzy.model.json")
