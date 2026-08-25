import typing
import os
import pathlib
import re
import json
import subprocess
import logging
import filelock
import pytest
from functools import reduce

from json_model.script import model_from_url, model_checker_from_url
from json_model.resolver import Resolver
from json_model.xstatic import xstatic_compile, ir_compile

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
    "ref:values": 114,
    "ref:verrors:schema": 59,
    "ref:models:errors-jsm": 2,
    # chunk 00
    "mv-00:cmp-opts": {"report": False, "comment": False, "relib": "re"},
    "mv-00:models": 10,
    "mv-00:values": 95,
    # chunk 01
    "mv-01:models": 11,
    "mv-01:values": 116,
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
    "mv-09:verrors:schema": 2,
    # chunk 0A
    "mv-0a:models": 10,
    "mv-0a:values": 131,
    "mv-0a:verrors:schema": 1,
    # chunk 0B
    "mv-0b:models": 7,
    "mv-0b:values": 82,
    # chunk 0C
    "mv-0c:models": 5,
    "mv-0c:values": 50,
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
    "mv-13:verrors:schema": 1,
    # chunk 14
    "mv-14:models": 12,
    "mv-14:values": 84,
    "mv-14:verrors:schema": 6,
    # chunk 15
    "mv-15:js2json": 2,
    "mv-15:models": 12,
    "mv-15:values": 133,
    "mv-15:verrors:schema": 2,
    # chunk 16
    "mv-16:models": 11,
    "mv-16:values": 100,
    "mv-16:verrors:schema": 1,
    # chunk 17
    "mv-17:models": 12,
    "mv-17:values": 146,
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
    "mv-1a:verrors:schema": 3,
    # chunk 1B
    "mv-1b:models": 10,
    "mv-1b:values": 68,
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
    "mv-1e:values": 153,
    "mv-1e:verrors:schema": 16,
    "mv-1e:verrors:dynpy": 1,
    "mv-1e:verrors:ir": 1,
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
    "mv-22:values": 725,
    "mv-22:verrors:schema": 27,
    # mv-23
    "mv-23:models": 4,
    "mv-23:values": 83,
    # mv-24
    "mv-24:cmp-opts": {"report": False},
    "mv-24:models": 5,
    "mv-24:values": 127,
    # mv-25
    "mv-25:cmp-opts": {"report": False},
    "mv-25:models": 8,
    "mv-25:values": 134,
    "mv-25:verrors:schema": 4,
    # mv-26
    "mv-26:cmp-opts": {"strcmp": True},
    "mv-26:models": 7,
    "mv-26:values": 109,
    # mv-27
    "mv-27:cmp-opts": {"strcmp": True, "report": False, "must_only_threshold": 2},
    "mv-27:models": 7,
    "mv-27:values": 105,
    # mv-28
    "mv-28:cmp-opts": {"strcmp": True, "report": False, "strcmp_cset_partition_threshold": 32},
    "mv-28:models": 7,
    "mv-28:values": 159,
    # mv-29: extensions
    "mv-29:models": 8,
    "mv-29:values": 129,
    "mv-29:mod-opts": {"extend": True},
    "mv-29:models:errors-jsm": 5,
    "mv-29:models:errors": 5,
    "mv-29:verrors:schema": 3,
    # mv-2a
    "mv-2a:models": 7,
    "mv-2a:values": 145,
    # mv-2b
    "mv-2b:cmp-opts": {"report": False, "comment": False},
    "mv-2b:models": 8,
    "mv-2b:values": 108,
    # mv-2c
    "mv-2c:cmp-opts": {"report": False, "comment": False},
    "mv-2c:models": 9,
    "mv-2c:values": 268,
    "mv-2c:verrors:schema": 47,
    # mv-2d
    "mv-2d:cmp-opts": {"report": False, "comment": False},
    "mv-2d:models": 10,
    "mv-2d:values": 164,
    # mv-2e
    "mv-2e:cmp-opts": {"report": False, "comment": False, "max_strcmp_cset": 64},
    "mv-2e:models": 10,
    "mv-2e:values": 179,
    # mv-2f
    "mv-2f:cmp-opts": {"report": False, "comment": False},
    "mv-2f:models": 11,
    "mv-2f:values": 160,
    # mv-30
    "mv-30:models": 10,
    "mv-30:values": 134,
    # mv-31
    "mv-31:models": 8,
    "mv-31:values": 237,
    # mv-32
    "mv-32:verrors:schema": 1,  # sre_0d.values [16]
    "mv-32:cmp-opts": {"report": False, "comment": False, "mark": "hello world"},
    "mv-32:mod-opts": {"single_line": True},
    "mv-32:models": 10,
    "mv-32:models:errors": 1,
    "mv-32:values": 194,
    # mv-33
    "mv-33:models": 10,
    "mv-33:values": 163,
    "mv-33:verrors:schema": 1,
    # mv-34
    "mv-34:cmp-opts": {"report": False, "comment": False},
    "mv-34:mod-opts": {"single_line": True},
    "mv-34:models": 8,
    "mv-34:values": 131,
    "mv-34:verrors:schema": 2,
    "mv-34:verrors:dynpy": 1,
    "mv-34:verrors:ir": 1,
    # mv-35
    "mv-35:cmp-opts": {"report": False, "comment": False},
    "mv-35:mod-opts": {"single_line": True},
    "mv-35:models": 7,
    "mv-35:values": 176,
    "mv-35:verrors:schema": 1,
    # mv-36
    "mv-36:models": 5,
    "mv-36:values": 89,
    "mv-36:verrors:schema": 1,
    # miscellaneous tests
    "bads:models": 58,
    "jsts-files": 309,
    # tests json models of json schema versions
    "draft3:jsts": 104,
    "draft4:jsts": 160,
    "draft6:jsts": 232,
    "draft7:jsts": 257,
    "draft2019-09:jsts": 372,
    "draft2020-12:jsts": 383,
    "draft-next:jsts": 369,
}

#
# LOCAL TEST UTILS
#
def path2file(fname: str) -> str:
    return fname.replace("/", "_").replace(".", "_")


def dirmap(dname) -> dict[str, str]:
    return {
        # map JM canonical url to local directory
        "https://json-model.org/models/": "../models/",
        # map current to tested directory
        "./": f"./{dname}/",
    }

def file_is_newer(f1: str, f2: str) -> bool:
    return os.path.getmtime(f1) > os.path.getmtime(f2)

def has_exec(program: str) -> bool:
    return os.system(f"type {program}") == 0

DIR_WITH_EXTENSIONS: set[str] = { "mv-29" }

#
# LOCAL FIXTURES
#
# test sub directories
MODEL_DIRS: list[pathlib.Path] = [ pathlib.Path("./ref") ] + sorted(pathlib.Path(".").glob("mv-*"))

MODEL_FILES: list[pathlib.Path] = reduce(
    lambda l1, l2: l1 + l2,
    (sorted(d.glob("*.model.json")) for d in MODEL_DIRS),
    []
)

MODEL_NAMES: list[str] = [ str(p)[:-11] for p in MODEL_FILES ]

@pytest.fixture(params=MODEL_DIRS)
def directory(request):
    return request.param

@pytest.fixture(params=MODEL_NAMES)
def model_name(request):
    return request.param

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


# TODO allow to restrict to a subset
@pytest.fixture(params=["py", "c", "js", "sql", "pl", "java"])
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
    cppflags += " -DREGEX_ENGINE_RE2 -DURL_PARSER_CCA"
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

    # use lax model
    model_c = "ref/json-model-moschin.c"
    fexec = f"{tmp_dir}/json_model_moschin_check"

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
    mod_opts = dict(EXPECT.get(f"{directory}:mod-opts", {}))
    cmp_opts = dict(EXPECT.get(f"{directory}:cmp-opts", {}))
    suffix = f".{language}"

    # defaults are different for PL/pgSQL
    if "report" not in cmp_opts:
        cmp_opts["report"] = language != "sql"

    def generate_language(fmodel: str):
        assert fmodel.startswith("./")
        entry = "check_model" if language != "java" else fmodel[2:].replace("-", "_")
        jm = model_from_url(fmodel, resolver=resolver, auto=True, follow=True, **mod_opts)
        code = xstatic_compile(jm, entry, lang=language, short_version=True, **cmp_opts)
        return str(code)

    check_generated(directory, f"lang-{language}", f".{language}", generate_language)

TSC = "../node_modules/.bin/tsc"
#
# STATIC CHECK MODELS AGAINST VALUES
#

@pytest.mark.ts
@pytest.mark.skipif(not os.path.exists(TSC), reason="missing tsc (npm install)")
def test_ts(directory, tmp_dir):
    from json_model.ts_export import model2tsinterface

    resolver = Resolver(None, dirmap(directory))
    mod_opts = EXPECT.get(f"{directory}:mod-opts", {})
    ntests = 0

    for fpath in sorted(directory.glob("*.model.json")):
        fname = "./" + str(fpath)
        fin = fname.replace(".model.json", "").replace(f"./{directory}/", "./")
        bname = fpath.name.replace(".model.json", "")
        ntests += 1
        declared = expected_errors(directory, bname).get("ts", False)

        try:
            jm = model_from_url(fin, resolver=resolver, auto=True, follow=True, **mod_opts)
            generated = "\n".join([
                "// Typescript interface generated by JSON Model Compiler",
                f"// for {fin}",
                "// see https://json-model.org/",
                "",
            ] + model2tsinterface(jm, root="RootModel")) + "\n"
        except Exception as e:
            assert declared, f"{directory}/{bname}: undeclared ts generation error: {e}"
            continue

        tsref = fname.replace(".model.json", ".ts")
        with open(tsref) as f:
            assert generated == f.read(), f"generated TS differs from committed {tsref}"

        tsfile = f"{tmp_dir}/{path2file(fname)}.ts"
        with open(tsfile, "w") as f:
            f.write(generated)

        proc = subprocess.run(
            [TSC, "--noEmit", "--strict", "--skipLibCheck", "--lib", "es2020", tsfile],
            capture_output=True, text=True
        )

        failed = proc.returncode != 0

        assert failed == declared, \
            f"{directory}/{bname}.errors.json [ts]: " + (
                f"undeclared tsc failure:\n{proc.stdout}{proc.stderr}" if failed else
                "declared as failing, but tsc accepts it"
            )

    assert ntests == EXPECT.get(f"{directory}:models", 0)

def expected_errors(directory: pathlib.Path, model: str) -> dict[str, list[int]]:
    """Expected errors for a model"""
    efile = directory.joinpath(f"{model}.errors.json")
    if not efile.exists():
        return {}
    with open(efile) as ef:
        return { k: v for k, v in json.load(ef).items() if not k.startswith("#") }

def check_errors(directory: pathlib.Path, model: str, key: str, observed: set[int]):
    """Compare observed checker errors to expectations"""
    expected = set(expected_errors(directory, model).get(key) or [])

    missing, extra = expected - observed, observed - expected
    assert not missing and not extra, \
        f"{directory}/{model}.values.json [{key}]: " \
        f"missing={sorted(missing)} extra={sorted(extra)}"

def check_values(
            tname: str,    # test model, eg "./mv-00/foo"
            name: str,     # test name, eg "sta-c"
            suffix: str,   # source suffix, eg ".c"
            refsuff: str,  # result suffix, eg ".c.check"
            generate: typing.Callable[[str], str],
            opts: str = ""
        ):
    """Generic value testing for one model."""

    nvalues = 0
    out = ""

    fname = f"{tname}{suffix}"
    fexec = generate(fname)
    log.debug(f"{name}: {fname} ({fexec})")

    bname = tname.split("/", -2)[-1]
    dname = tname.split("/", -2)[-2]

    directory = pathlib.Path(dname)

    # run on all validations
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

        ref_file = fname.replace(suffix, refsuff)
        with open(ref_file) as r:
            ref = r.read()

        if ref.strip() == "skipped":
            # just count and proceed to the next
            with open(vfile) as vf:
                values = json.load(vf)
            nvalues += len(list(filter(lambda t: isinstance(t, list), values)))
            return

        with os.popen(f"{fexec} {opts} -t {vfile} | cut -d/ -f2-") as p:
            result = p.read()
        out += result

        lang = suffix[1:]
        observed: set[int] = set()

        for line in result.split("\n")[:-1]:
            nvalues += 1
            m = re.search(r"\.values\.json\[(\d+)\]: (\w+)", line)
            assert m is not None, f"unexpected output in {directory}/{bname}:{line}"

            idx, verdict = int(m.group(1)), m.group(2)
            if verdict == "ERROR":
                observed.add(idx)

        assert result, f"no output from {fexec} on {vfile}"
        check_errors(directory, bname, lang, observed)
        assert out == ref

    # cleanup
    if suffix.endswith(".c"):
        os.remove(fexec)

@pytest.mark.c
def test_sta_c(model_name, clibjm):
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

    check_values(model_name, "sta-c", ".c", ".c.check", gen_exec, "-r")

@pytest.mark.py
def test_sta_py(model_name):
    """Check generated Python scripts with test value files."""
    check_values(model_name, "sta-py", ".py", ".py.check", lambda f: f, "-r")

@pytest.mark.js
@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_sta_js(model_name):
    """Check generated JS scripts with test value files."""
    check_values(model_name, "sta-js", ".js", ".js.check", lambda f: f, "-r")

@pytest.mark.sql
@pytest.mark.skipif(not has_exec("psql"), reason="missing psql")
def test_sta_sql(model_name):
    """Check generated SQL scripts with test value files."""
    check_values(model_name, "sta-sql", ".sql", ".sql.check",
                 lambda f: f"./test_sql.sh {f}")

@pytest.mark.pl
@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_sta_pl(model_name):
    """Check generated Perl scripts with test value files."""
    check_values(model_name, "sta-pl", ".pl", ".pl.check", lambda f: f, "-r")

@pytest.mark.java
@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_sta_java(model_name, tmp_dir):
    """Check generated Java programs with test value files."""
    check_values(model_name, "sta-java", ".java", ".java.check",
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
                assert isinstance(tvect, list)
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

    assert nfiles == EXPECT.get(f"{directory}:models")
    assert ntests == EXPECT.get(f"{directory}:values")
    assert nmerrors == EXPECT.get(f"{directory}:merrors:{name}", 0)
    assert nverrors == EXPECT.get(f"{directory}:verrors:{name}", 0)

@pytest.mark.py
def test_dyn_py(directory: pathlib.Path):

    resolver = Resolver(None, dirmap(directory))
    options = EXPECT.get(f"{directory}:mod-opts", {})

    def gen_py_checker(fmodel: str):
        assert fmodel.endswith(".model.json")
        model = fmodel.replace(".model.json", "").replace(f"{directory}/", "")
        return model_checker_from_url(model, resolver=resolver, follow=True, debug=False, **options)

    run_dyn(directory, gen_py_checker, "dynpy")

@pytest.mark.py
@pytest.mark.ir
def test_dyn_ir(directory: pathlib.Path):
    """Test IR re-entrance: compile to the JSON IR, then back to Python."""

    resolver = Resolver(None, dirmap(directory))
    options = EXPECT.get(f"{directory}:mod-opts", {})

    def gen_ir_checker(fmodel: str):
        assert fmodel.endswith(".model.json")
        model = fmodel.replace(".model.json", "").replace(f"{directory}/", "")
        jm = model_from_url(model, resolver=resolver, follow=True, debug=False, **options)
        ir = json.loads(str(xstatic_compile(jm, lang="json")))
        env = {}
        exec(ir_compile(ir, lang="py"), env)
        env[ir["entry"] + "_init"]()
        return env[ir["entry"]]

    run_dyn(directory, gen_ir_checker, "ir")

@pytest.mark.schema
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
            log.error(f"{str(dir)}[{ntests}] failed: {line}")
    assert ntests == EXPECT.get(f"{directory}:models", 0)
    assert nerrors == errors

@pytest.mark.c
@pytest.mark.skipif(not has_exec("cc"), reason="missing cc")
def test_models_c(directory, jmchecker):
    check_models(directory, jmchecker, EXPECT.get(f"{directory}:models:errors-c", 0))

@pytest.mark.py
def test_models_py(directory):
    check_models(directory, "./ref/json-model-moschin.py", EXPECT.get(f"{directory}:models:errors-py", 0))

@pytest.mark.js
@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_models_js(directory):
    check_models(directory, "./ref/json-model-moschin.js", EXPECT.get(f"{directory}:models:errors-js", 0))

@pytest.mark.pl
@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_models_pl(directory):
    check_models(directory, "./ref/json-model-moschin.pl", EXPECT.get(f"{directory}:models:errors-pl", 0))

@pytest.mark.java
@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_models_java(directory):
    check_models(directory, "./test_java.sh ./ref/json-model-moschin.java",
                 EXPECT.get(f"{directory}:models:errors-java", 0))

@pytest.mark.sql
@pytest.mark.skipif(not has_exec("psql"), reason="missing psql")
def test_models_sql(directory):
    # TODO add custom error
    if str(directory) == "mv-2a":
        pytest.skip("model with incompatible nul character")
    check_models(directory, "./test_sql.sh ./ref/json-model-moschin.sql",
                 EXPECT.get(f"{directory}:models:errors-sql", 0))

# NOTE moschin schema does not work
@pytest.mark.schema
def test_models_jsm(directory):
    if str(directory) in DIR_WITH_EXTENSIONS:
        pytest.skip("model extensions not supported")
    check_models(directory, "jsu-check --quiet --engine jsonschema json-model.schema.json",
                 EXPECT.get(f"{directory}:models:errors-jsm", 0))

@pytest.mark.schema
def test_models_jsg(directory):
    if str(directory) in DIR_WITH_EXTENSIONS:
        pytest.skip("model extensions not supported")
    check_models(directory, "jsu-check -e jschon --quiet ./ref/json-model.schema.json",
                 EXPECT.get(f"{directory}:models:errors-jsg", 0))

def check_directory_models(
        directory: pathlib.Path, url: str, suffix: str,
        generate: typing.Callable[[str], typing.Any], count: int,
    ):
    """Check a model against directory/*.suffix, expecting count tests."""
    resolver = Resolver(None, dirmap(directory))
    checker = model_checker_from_url(url, resolver=resolver, follow=True)
    ntests, nokay = 0, 0

    for fpath in sorted(directory.glob(f"*{suffix}")):
        log.debug(f"considering {fpath}")
        ntests += 1
        value = generate(fpath)
        report = []
        if checker(value, "", report):
            nokay += 1
        else:
            log.error(f"{fpath}: {report} ## {json.dumps(value)[:100]}")

    assert ntests == nokay
    if count == -1:
        pass
    elif count == -2:
        assert ntests > 0
    else:
        assert ntests == count

@pytest.mark.ir
def test_ir(directory):
    """Model IR conformity to IR model."""

    resolver = Resolver(None, dirmap(directory))
    mod_opts = EXPECT.get(f"{directory}:mod-opts", {})
    cmp_opts = dict(EXPECT.get(f"{directory}:cmp-opts", {}))

    def generate_ir(fmodel: str|pathlib.Path):
        fname = str(fmodel).replace(f"{str(directory)}/", "./")
        jm = model_from_url(fname, resolver=resolver, auto=True, follow=True, **mod_opts)
        code = xstatic_compile(jm, "check_model", lang="json", short_version=True, **cmp_opts)
        return json.loads(str(code))

    check_directory_models(
        directory,
        "https://json-model.org/models/jmc-ir",
        ".model.json",
        generate_ir,
        EXPECT.get(f"{directory}:models"),
    )

def get_json_file(fpath: str|pathlib.Path):
    fname = "./" + str(fpath)
    with open(fname) as f:
        return json.load(f)


def test_model_json(directory):
    """Check test model conformity to JSON Model meta model."""

    model_url = "https://json-model.org/models/json-model"
    if str(directory) in DIR_WITH_EXTENSIONS:
        model_url += "-moschin"

    check_directory_models(
        directory,
        model_url,
        ".model.json",
        get_json_file,
        EXPECT.get(f"{directory}:models"),
    )

def test_values_json(directory):
    """Check *.values.json files in directory."""

    check_directory_models(
        directory,
        "https://json-model.org/models/jmc-tests",
        ".values.json",
        get_json_file,
        EXPECT.get(f"{directory}:models"),
    )

def test_errors_json(directory):
    """Check *.errors.json files in directory against the jmc-errors meta model."""

    check_directory_models(
        directory,
        "https://json-model.org/models/jmc-errors",
        ".errors.json",
        get_json_file,
        -1,
    )

    # TODO check that model file exists
    # model = fname.replace(".errors.json", ".model.json")
    # assert os.path.exists(model), f"{fname}: no corresponding {model}"

def test_bench_json():

    check_directory_models(
        pathlib.Path("../site/benchmarks"),
        "https://json-model.org/models/jmc-bench",
        ".json",
        get_json_file,
        -2,
    )

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

@pytest.mark.c
@pytest.mark.skipif(not has_exec("cc"), reason="missing cc")
def test_bads_c(jmchecker):
    check_bads(jmchecker)

@pytest.mark.py
def test_bads_py():
    check_bads("./ref/json-model.py")

@pytest.mark.js
@pytest.mark.skipif(not has_exec("node"), reason="missing node")
def test_bads_js():
    check_bads("./ref/json-model.js")

@pytest.mark.pl
@pytest.mark.skipif(not has_exec("perl"), reason="missing perl")
def test_bads_pl():
    check_bads("./ref/json-model.js")

@pytest.mark.java
@pytest.mark.skipif(not has_exec("javac"), reason="missing javac")
def test_bads_java():
    check_bads("./test_java.sh ./ref/json-model.java")

@pytest.mark.schema
def test_bads_jsm():
    check_bads("jsu-check -e jsonschema --quiet ./json-model.schema.json")

@pytest.mark.schema
def test_bads_jsg():
    check_bads("jsu-check -e jschon --quiet ./ref/json-model.schema.json")

#
# JSON SCHEMA DRAFT TESTS
#

@pytest.mark.schema
def test_schema_suite_tests():
    ntests = 0
    checker = model_checker_from_url("../models/test-schema.model.json")
    path = pathlib.Path("./JSON-Schema-Test-Suite/tests/")
    if not path.is_dir():
        pytest.skip(f"missing test suite directory: {path}")
    for tfile in path.glob("*/*.json"):
        with open(tfile) as f:
            value = json.load(f)
            assert isinstance(value, list)
            ntests += 1
            reasons = []
            okay = checker(value, "", reasons)
            assert okay, f"{tfile} matches its model"
    assert ntests == EXPECT.get("jsts-files", 0)

def json_schema_test_suite(version, fmodel):
    ntests = 0
    # load model
    checker = model_checker_from_url(fmodel, auto=True)
    # run all tests
    path = pathlib.Path(f"./JSON-Schema-Test-Suite/tests/{version}")
    if not path.is_dir():
        pytest.skip(f"missing test suite directory: {path}")
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

@pytest.mark.schema
def test_draft3():
    # strict: fails on infinite-loop-detection.json[0]
    # nesting: fails on ref.json[7]
    json_schema_test_suite("draft3", "../models/json-schema-draft-03-fuzzy.model.json")

@pytest.mark.schema
def test_draft4():
    # strict/nesting: fails on infinite-loop-detection.json[0]
    json_schema_test_suite("draft4", "../models/json-schema-draft-04-fuzzy.model.json")

@pytest.mark.schema
def test_draft6():
    # strict: fails on ref.json[6]
    json_schema_test_suite("draft6", "../models/json-schema-draft-06-fuzzy.model.json")

@pytest.mark.schema
def test_draft7():
    json_schema_test_suite("draft7", "../models/json-schema-draft-07.model.json")

@pytest.mark.schema
def test_draft8():
    # strict: fails on vocabulary.json[0] (meta schema url)
    json_schema_test_suite("draft2019-09", "../models/json-schema-draft-2019-09-fuzzy.model.json")

@pytest.mark.schema
def test_draft9():
    # strict: fails on vocabulary.json[0] (meta schema url)
    json_schema_test_suite("draft2020-12", "../models/json-schema-draft-2020-12-fuzzy.model.json")

@pytest.mark.schema
def test_draft_next():
    json_schema_test_suite("draft-next", "../models/json-schema-draft-next.model.json")

# file consistency
SUFFIXES: list[str] = [
    "model.json", "values.json", "PO.json", "UO.json", "schema.json", "schema.check"
]

for lang in [ "c", "py", "js", "sql", "pl", "java" ]:
    SUFFIXES.extend([ lang, f"{lang}.check" ])

def test_sanity(directory):
    assert len(SUFFIXES) == 18
    files: dict[str, list[pathlib.Path]] = {}
    for suffix in SUFFIXES:
        files[suffix] = sorted(str(fn) for fn in directory.glob(f"*.{suffix}"))
    # avoid *.model.js
    files["js"] = [ fn for fn in files["js"] if not fn.endswith(".model.js") ]
    # number of mandatory files
    nfiles = len(files["c"])
    assert nfiles > 0, "no empty directory"
    for suffix in SUFFIXES:
        assert len(files[suffix]) == nfiles, f"expected number of {suffix} files"
    # name of files
    names = [ fn[:-2] for fn in files["c"] ]
    for name in names:
        for suffix in SUFFIXES:
            fn = f"{name}.{suffix}"
            assert pathlib.Path(fn).exists(), f"expecting file: {fn}"
    # some values
    for fn in files["values.json"]:
        with open(fn) as f:
            values = json.load(f)
        assert isinstance(values, list)
        assert len(list(filter(lambda i: isinstance(i, list), values))) > 2, f"enough values: {fn}"
