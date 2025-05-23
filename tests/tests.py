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

@pytest.fixture(params=["./modval", "./m2s", "./rwt"])
def directory(request):
    return pathlib.Path(request.param)

# test expectations
EXPECT: dict[str, int] = {
    "modval:2json": 13,
    "modval:preproc": 147,
    "modval:schema": 147,
    "modval:lang-c": 130,
    "modval:lang-py": 130,
    "modval:stac:tests": 130,
    "modval:stapy:tests": 130,
    "modval:stac:values": 1172,
    "modval:stapy:values": 1172,
    "m2s:schema": 57,
    "rwt:preproc": 44,
    "rwt:schema": 44,
}

def dirmap(dname) -> dict[str, str]:
    return {
        "https://json-model.org/models/": "../models/",
        "./": f"./{dname}/",
    }

def test_2json(directory):
    """JavaScript and YaML conversion to JSON."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for suffix in (".model.js", ".model.yaml"):
        for fpath in sorted(directory.glob("*" + suffix)):
            ntests += 1
            fname = str(fpath)
            log.debug(f"2json[{directory}]: {fname}")
            j = resolver(fname, follow=False)
            ref = resolver(fname.replace(suffix, ""), follow=False)
            assert j == ref
    assert ntests == EXPECT.get(f"{directory}:2json", 0)

def test_preproc(directory):
    """Preprocessing optimizations."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for fpath in sorted(directory.glob("*.PO.json")):
        fname = "./" + str(fpath)
        fin = fname.replace(".PO.json", "").replace(f"./{str(directory)}/", "./")
        log.debug(f"preproc[{directory}]: {fin}")
        ntests += 1
        ref = resolver(fname, follow=False)
        jm = model_from_url(fin, resolver=resolver, auto=True, follow=True)
        out = jm.toModel(True)
        assert out == ref
    assert ntests == EXPECT.get(f"{directory}:preproc", 0)

def test_schema(directory):
    """Model to Schema conversion."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for fpath in sorted(directory.glob("*.schema.json")):
        fname = "./" + str(fpath)
        sname = fname.replace(".schema.json", ".model.json")
        fin = fname.replace(".schema.json", "").replace(f"./{str(directory)}/", "./")
        log.debug(f"schema[{directory}]: {fin}")
        if not fpath.stat().st_size:
            log.warning(f"skipping empty schema file: {fname}")
            continue
        if not pathlib.Path(sname).exists():
            log.warning(f"skipping missing model file: {sname}")
            continue
        ntests += 1
        ref = resolver(fname, follow=False)
        jm = model_from_url(fin, resolver=resolver, auto=True, follow=True)
        try:
            out = jm.toSchema(True)
        except Exception as e:
            out = { "ERROR": str(e) }
        assert out == ref
    assert ntests == EXPECT.get(f"{directory}:schema", 0)

@pytest.fixture(params=["py", "c"])
def language(request):
    return request.param

def test_lang(directory, language):
    """Check compiled sources."""
    resolver = Resolver(None, dirmap(directory))
    suffix = f".x.{language}"
    ntests = 0
    for fpath in sorted(directory.glob(f"*{suffix}")):
        fname = "./" + str(fpath)
        fin = fname.replace(suffix, "").replace(f"./{str(directory)}/", "./")
        log.debug(f"lang[{directory},{language}]: {fin}")
        ntests += 1
        jm = model_from_url(fin, resolver=resolver, auto=True, follow=True)
        code = xstatic_compile(jm, "check_model", lang=language)
        with open(fname) as fl:
            ref = fl.read()
        assert str(code) == ref
    assert ntests == EXPECT.get(f"{directory}:lang-{language}", 0)

@pytest.mark.skip(reason="not there yet…")
def test_dypy(directory):
    """Check generated python with test values."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for fpath in sorted(directory.glob("*.model.json")):
        fname = f"./{fpath}"
        bname = fname.replace(".model.json", "")
        log.debug(f"dypy[{directory}]: {fname} ({fpath})")

        checker = model_checker_from_url(fname, resolver=resolver, follow=False)

        # true/false files
        for vpath in sorted(directory.glob(bname + ".*.*.json")):
            ntests += 1
            value = json.loads(vpath.read_text())
            assert ".true.json" in vpath or ".false.json" in vpath
            if ".true.json" in vpath:
                assert checker(value)
            else:
                assert not checker(value)

        # values file
        vfile = directory.joinpath(bname + ".values.json")
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

    assert ntests == EXPECT.get(f"{directory}:dypy", 0)

def path2file(fname: str) -> str:
    return fname.replace("/", "_").replace(".", "_")

@pytest.fixture
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

    # os.remove(jm_lib)
    # os.remove(jm_main)


def test_stac(directory, clibjm):
    """Check generated C code with test value files."""
    ntests, nvalues = 0, 0

    # compilation settings
    cc, cppflags, cflags, ldflags = \
        clibjm["cc"], clibjm["cppflags"], clibjm["cflags"], clibjm["ldflags"],
    # files
    tmp_dir, jm_lib, jm_main = clibjm["tmp"], clibjm["lib"], clibjm["main"]

    assert os.path.isfile(jm_lib), "available support lib"
    assert os.path.isfile(jm_main), "available support main"

    # try all sources
    for fpath in sorted(directory.glob("*.x.c")):
        fname = f"./{fpath}"
        bname = fname.replace(".x.c", "").split("/", -1)[-1]
        fexec = f"{tmp_dir}/{path2file(fname)}.out"
        log.debug(f"stac[{directory}]: {fname} ({fexec})")
        ntests += 1

        # compile
        status = os.system(f"{cc} {cppflags} {cflags} {fname} {ldflags} -o {fexec}")
        assert status == 0, f"{fname} compilation success"

        # run on all validations
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
        cfile = fname.replace(".x.c", ".ccheck.out")
        with open(cfile) as r:
            ref = r.read()
        assert out == ref
        # cleanup
        os.remove(fexec)

    assert ntests == EXPECT.get(f"{directory}:stac:tests", 0)
    assert nvalues == EXPECT.get(f"{directory}:stac:values", 0)

def test_stapy(directory):
    """Check generated Python scripts with test value files."""
    ntests, nvalues = 0, 0

    # try all sources
    for fpath in sorted(directory.glob("*.x.py")):
        fname = f"./{fpath}"
        bname = fname.replace(".x.py", "").split("/", -1)[-1]
        log.debug(f"stac[{directory}]: {fname}")
        ntests += 1

        # run on all validations
        values = list(directory.glob(f"{bname}.*.true.json")) + \
                 list(directory.glob(f"{bname}.*.false.json"))
        vfiles = " ".join(sorted(str(f) for f in values))
        for line in os.popen(f"{fname} {vfiles}"):
            nvalues += 1
            assert re.search(r"(\.true\.json: PASS|\.false\.json: FAIL)$", line) is not None, \
                f"result as expected: {line}"

        vfile = directory.joinpath(bname + ".values.json")
        if vfile.exists():
            for line in os.popen(f"{fname} -t {vfile}"):
                nvalues += 1
                assert ": ERROR" not in line and (": PASS" in line or ": FAIL" in line)

        # run script with reporting
        with os.popen(f"{fname} -r {vfiles} | cut -d/ -f2-") as p:
            out = p.read()
        if vfile.exists():
            with os.popen(f"{fname} -tr {vfile} | cut -d/ -f2-") as p:
                out += p.read()
        pfile = fname.replace(".x.py", ".pcheck.out")
        with open(pfile) as r:
            ref = r.read()
        assert out == ref

    assert ntests == EXPECT.get(f"{directory}:stapy:tests", 0)
    assert nvalues == EXPECT.get(f"{directory}:stapy:values", 0)


# TODO no report option
# TODO check wrt json model official schema
# TODO check wrt json model generated schema
@pytest.mark.skip(reason="not there yet…")
def test_models(directory):
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
