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
    "modval:lang-py": 1,
    "modval:lang-c": 1,
    "m2s:2json": 0,
    "m2s:preproc": 0,
    "m2s:schema": 57,
    "m2s:lang-py": 0,
    "m2s:lang-c": 0,
    "rwt:2json": 0,
    "rwt:preproc": 44,
    "rwt:schema": 44,
    "rwt:lang-py": 0,
    "rwt:lang-c": 0,
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
    assert ntests == EXPECT[f"{directory}:2json"]

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
    assert ntests == EXPECT[f"{directory}:preproc"]

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
    assert ntests == EXPECT[f"{directory}:schema"]

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
        log.debug(f"lang {str(directory)} {language}: {fin}")
        ntests += 1
        jm = model_from_url(fin, resolver=resolver, auto=True, follow=True)
        code = xstatic_compile(jm, "check_model", lang=language)
        with open(fname) as fl:
            ref = fl.read()
        assert str(code) == ref
    assert ntests == EXPECT[f"{directory}:lang-{language}"]

@pytest.mark.skip(reason="not there yet…")
def test_dypy(directory):
    """Check generated python with test values."""
    resolver = Resolver(None, dirmap(directory))
    ntests = 0
    for fpath in sorted(directory.glob("*.model.json")):
        fname = f"./{fpath}"
        bname = fname.replace(".model.json", "")
        log.debug(f"dypy {str(directory)}: {fname} ({fpath})")
        checker = model_checker_from_url(fname, resolver=resolver, follow=False)
        for vpath in sorted(directory.glob(bname + ".*.*.json")):
            ntests += 1
            value = json.loads(vpath.read_text())
            assert ".true.json" in vpath or ".false.json" in vpath
            if ".true.json" in vpath:
                assert checker(value)
            else:
                assert not checker(value)
    assert ntests == EXPECT[f"{directory}:dypy"]

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
    assert ntests == EXPECT[f"{directory}:models"]
