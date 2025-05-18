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
    "modval:preproc": 139,
    "modval:schema": 139,
    "modval:lang-c": 19,
    "modval:lang-py": 19,
    "modval:stac:tests": 19,
    "modval:stapy:tests": 19,
    "modval:stac:values": 115,
    "modval:stapy:values": 115,
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
            log.debug(f"2json: {fname}")
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
        log.debug(f"preproc: {fin}")
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
        log.debug(f"schema: {fin}")
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
        log.debug(f"lang {directory} {language}: {fin}")
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
        log.debug(f"dypy {directory}: {fname} ({fpath})")
        checker = model_checker_from_url(fname, resolver=resolver, follow=False)
        for vpath in sorted(directory.glob(bname + ".*.*.json")):
            ntests += 1
            value = json.loads(vpath.read_text())
            assert ".true.json" in vpath or ".false.json" in vpath
            if ".true.json" in vpath:
                assert checker(value)
            else:
                assert not checker(value)
    assert ntests == EXPECT.get(f"{directory}:dypy", 0)

def test_stac(directory):
    """Check generated C code with test values."""
    ntests, nvalues = 0, 0
    # compilation settings
    cc = os.environ.get("CC", "gcc")
    cppflags = os.environ.get("CPPFLAGS", "-DWITH_MAIN")
    cflags = os.environ.get("CFLAGS", "-Wall -O2")
    ldflags = os.environ.get("LDFLAGS", "-ljansson -lpcre2-8")
    # try all sources
    for fpath in sorted(directory.glob("*.x.c")):
        fname = f"./{fpath}"
        bname = fname.replace(".x.c", "").split("/", -1)[-1]
        fexec = "/dev/shm/jm.out"
        log.debug(f"stac {directory}: {fname}")
        ntests += 1
        status = os.system(f"{cc} {cppflags} {cflags} {fname} {ldflags} -o {fexec}")
        assert status == 0, f"{fname} compilation success"
        values = list(directory.glob(f"{bname}.*.true.json")) + \
                 list(directory.glob(f"{bname}.*.false.json"))
        vfiles = sorted(str(f) for f in values)
        for line in os.popen(f"{fexec} {' '.join(vfiles)}"):
            nvalues += 1
            assert re.search(r"(\.true\.json: PASS|\.false\.json: FAIL)$", line) is not None, \
                f"result as expected: {line}"
    assert ntests == EXPECT.get(f"{directory}:stac:tests", 0)
    assert nvalues == EXPECT.get(f"{directory}:stac:values", 0)

def test_stapy(directory):
    """Check generated Python scripts with test values."""
    ntests, nvalues = 0, 0
    # try all sources
    for fpath in sorted(directory.glob("*.x.py")):
        fname = f"./{fpath}"
        bname = fname.replace(".x.py", "").split("/", -1)[-1]
        log.debug(f"stac {directory}: {fname}")
        ntests += 1
        values = list(directory.glob(f"{bname}.*.true.json")) + \
                 list(directory.glob(f"{bname}.*.false.json"))
        vfiles = sorted(str(f) for f in values)
        for line in os.popen(f"{fname} {' '.join(vfiles)}"):
            nvalues += 1
            assert re.search(r"(\.true\.json: PASS|\.false\.json: FAIL)$", line) is not None, \
                f"result as expected: {line}"
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
        log.debug(f"models {str(directory)}: {fname}")
        with open(fname) as f:
            model = json.load(f)
        report = []
        ntests += 1
        assert checker(model)  # no report
        assert checker(model, "", report)  # with report
    assert ntests == EXPECT.get(f"{directory}:models", 0)
