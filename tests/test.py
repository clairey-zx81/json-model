import pytest
import pathlib
import logging

from json_model.script import create_model, process_model
from json_model.resolver import Resolver

logging.basicConfig()
log = logging.getLogger("test")
log.setLevel(logging.DEBUG)
# log.setLevel(logging.INFO)

@pytest.fixture(params=["./modval", "./m2s", "./rwt"])
def directory(request):
    return pathlib.Path(request.param)

EXPECT: dict[tuple[str, str], int] = {
    ("modval", "2json"): 13,
    ("modval", "preproc"): 139,
    ("modval", "schema"): 139,
    ("m2s", "2json"): 0,
    ("m2s", "preproc"): 0,
    ("m2s", "schema"): 57,
    ("rwt", "2json"): 0,
    ("rwt", "preproc"): 44,
    ("rwt", "schema"): 44,
}

def dirmap(dname) -> dict[str, str]:
    return {
        "https://json-model.org/models": "../models",
        "./": "./" + str(dname) + "/",
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
    assert ntests == EXPECT[(str(directory), "2json")]

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
        jm = create_model(fin, resolver, auto=True, follow=True)
        process_model(jm)
        out = jm.toModel(True)
        assert out == ref
    assert ntests == EXPECT[(str(directory), "preproc")]

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
        jm = create_model(fin, resolver, auto=True, follow=True)
        process_model(jm)
        try:
            out = jm.toSchema(True)
        except Exception as e:
            out = { "ERROR": str(e) }
        assert out == ref
    assert ntests == EXPECT[(str(directory), "schema")]
