import pathlib
import re
import json
import copy
import pytest

import logging
logging.basicConfig()
log = logging.getLogger("tests")
log.setLevel(logging.INFO)
# log.setLevel(logging.DEBUG)

import json_model.generate as generate
from json_model.preproc import model_preprocessor

def test_s2m():
    s2m = pathlib.Path("./s2m")
    for fs in s2m.glob("*.schema.json"):
        log.info(f"schema to model: {fs}")
        with open(fs) as f:
            js = json.load(f)
        # reset schema2 model global
        generate._definitions = 0
        jm = generate.schema2model(js)
        fm = str(fs).replace(".schema.json", ".model.json")
        with open(fm) as f:
            jmr = json.load(f)
        assert jm == jmr, f"{fs} generated model is ok"

def test_m2s():
    m2s = pathlib.Path("./m2s")
    for fm in m2s.glob("*.model.json"):
        log.info(f"model to schema: {fm}")
        with open(fm) as f:
            jm = json.load(f)
        js = generate.model2schema(jm)
        fs = str(fm).replace(".model.json", ".schema.json")
        with open(fs) as f:
            jsr = json.load(f)
        assert js == jsr, f"{fm} generated schema is ok"

from json_model.utils import ModelError
from json_model.validator import DSV
import json_model.compiler as compiler

from good_models import (
    TEST_MODELS, JSON_MODEL, JSON_SCHEMA_MODEL, JSON_MODEL_SCHEMA,
    init_data
)

# FIXME jschon tests are pretty slow…

def test_jschon_m2s():
    jschon = pytest.importorskip("jschon")
    jschon.create_catalog("2020-12")
    model_schema = jschon.JSONSchema(JSON_MODEL_SCHEMA)
    m2s = pathlib.Path("./m2s")
    for fm in m2s.glob("*.model.json"):
        log.info(f"model evaluation: {fm}")
        with open(fm) as f:
            jm = json.load(f)
        res = model_schema.evaluate(jschon.JSON(jm))
        if not res.passed:
            log.error(f"model: {jm}")
            log.error(json.dumps(res.output('basic'), indent=2))
        assert res.passed, f"model seems okay"

def test_jschon_goods():
    jschon = pytest.importorskip("jschon")
    import jschon
    jschon.create_catalog("2020-12")
    model_schema = jschon.JSONSchema(JSON_MODEL_SCHEMA)
    for _v, model, _e in TEST_MODELS:
        if isinstance(model, str) and model.startswith("$"):
            continue
        log.info(f"model: {model}")
        res = model_schema.evaluate(jschon.JSON(model))
        if not res.passed:
            log.error(f"model: {model}")
            log.error(json.dumps(res.output('basic'), indent=2))
        assert res.passed, f"model seems okay"

def test_jschon_bads():
    jschon = pytest.importorskip("jschon")
    import jschon
    jschon.create_catalog("2020-12")
    model_schema = jschon.JSONSchema(JSON_MODEL_SCHEMA)
    for _i, valid, _c, model in BADS:
        if valid:
            continue
        if isinstance(model, str) and model.startswith("$"):
            continue
        log.info(f"model: {model}")
        try:
            res = model_schema.evaluate(jschon.JSON(model))
        except TypeError as error:
            log.error(f"on {model}: {error}")
            continue
        if res.passed:
            log.error(f"model: {model}")
            log.error(json.dumps(res.output('basic'), indent=2))
        assert not res.passed, f"model is invalid"

def test_merge():
    merge = pathlib.Path("./merge")
    for fm in merge.glob("*.merged.json"):
        fi = str(fm).replace(".merged.", ".")
        with open(fi) as f:
            mi = json.load(f)
        with open(fm) as f:
            mm = json.load(f)
        mmg = model_preprocessor(mi, {})
        assert mmg == mm

def test_v_checked_json_model():
    """Check that test models validate the meta model."""
    validator = DSV()
    for _v, model, _e in TEST_MODELS:
        assert validator.check(model, JSON_MODEL), f"v-valid model: {model}"

def test_c_checked_json_model():
    """Check that test models match the meta model."""
    checker = compiler.compileModel(JSON_MODEL)
    for _v, model, _e in TEST_MODELS:
        log.info(f"model: {model}")
        assert checker(model), f"c-valid model: {model}"

def test_v_checked_json_schema():
    validator = DSV()
    s2m = pathlib.Path("./s2m")
    for fs in s2m.glob("*.schema.json"):
        log.info(f"schema to model: {fs}")
        with open(fs) as f:
            schema = json.load(f)
        assert validator.check(schema, JSON_SCHEMA_MODEL), f"v-checked schema: {js}"

def test_c_checked_json_schema():
    """Check that s2m schemas are tight."""
    schema_is_tight = compiler.compileModel(JSON_SCHEMA_MODEL)
    s2m = pathlib.Path("./s2m")
    for fs in s2m.glob("*.schema.json"):
        log.info(f"schema validation: {fs}")
        with open(fs) as f:
            schema = json.load(f)
        assert schema_is_tight(schema), f"c-checked schema: {fs}"

def test_v_checked_json_model_values():
    validator = DSV()
    init_data(validator.set)
    for value, model, expect in TEST_MODELS:
        log.info(f"model: {model}")
        log.debug(f"expecting {expect} for {value}")
        assert validator.check(value, model) == expect, \
            f"v-checked model value: {value} ~ {model} = {expect}"

def test_c_checked_json_model_values():
    # init_data(compiler._DEFS.set)
    for value, model, expect in TEST_MODELS:
        log.info(f"model: {model}")
        log.debug(f"expecting {expect} for {value}")
        checker = compiler.compileModel(model)
        init_data(checker._defs.set)
        assert checker(value) == expect, f"c-checked model value: {value} ~ {model} = {expect}"

def test_c_checked_json_model_files():
    modval = pathlib.Path("./modval")
    model_suffix = "_m.json"
    mcount = 0
    for mf in modval.glob("*" + model_suffix):
        mcount += 1
        vtrue, vfalse = 0, 0
        prefix = mf.name[:-len(model_suffix)]
        model = json.load(open(mf))
        log.info(f"model: {model}")
        checker = compiler.compileModel(model)
        init_data(checker._defs.set)
        for vf in modval.glob(f"{prefix}_*_t.json"):
            log.debug("true value file: {vf}")
            vtrue += 1
            value = json.load(open(vf))
            assert checker(value), f"c-checked model value: {value} ~ {model}"
        for vf in modval.glob(f"{prefix}_*_f.json"):
            log.debug("false value file: {vf}")
            vfalse += 1
            value = json.load(open(vf))
            assert not checker(value), f"c-checked model value: {value} !~ {model}"
        assert vtrue >= 1 or vfalse >= 1
    assert mcount > 5

@pytest.mark.skip("some issues")
def test_v_checked_json_model_files():
    validator = DSV()
    init_data(validator.set)
    modval = pathlib.Path("./modval")
    model_suffix = "_m.json"
    mcount = 0
    for mf in modval.glob("*" + model_suffix):
        mcount += 1
        vtrue, vfalse = 0, 0
        prefix = mf.name[:-len(model_suffix)]
        model = json.load(open(mf))
        log.info(f"model: {model}")
        for vf in modval.glob(f"{prefix}_*_t.json"):
            log.debug("true value file: {vf}")
            vtrue += 1
            value = json.load(open(vf))
            assert validator.check(model, value), f"v-checked model value: {value} ~ {model}"
        for vf in modval.glob(f"{prefix}_*_f.json"):
            log.debug("false value file: {vf}")
            vfalse += 1
            value = json.load(open(vf))
            assert not validator.check(model, value), f"v-checked model value: {value} !~ {model}"
        assert vtrue >= 1 or vfalse >= 1
    assert mcount > 5

def test_json_model_compilation():
    for _v, model, _e in TEST_MODELS:
        log.info(f"model: {model}")
        try:
            checker = compiler.compileModel(model)
            assert checker is not None, f"model compilation: {model}"
        except ModelError as e:
            assert False, f"model compilation failed: {model}"

from bad_models import BADS

def test_bad_json_model_v_checked():
    validator = DSV()
    for _i, expect, _c, model in BADS:
        log.info(f"model: {model}")
        assert validator.check(model, JSON_MODEL) == expect, f"v-checked bad model: {model}"

def test_bad_json_model_c_checked():
    checker = compiler.compileModel(JSON_MODEL)
    for _i, expect, _c, model in BADS:
        log.info(f"model: {model}")
        assert checker(model) == expect, f"c-checked bad model: {model}"

def test_bad_json_models_compilation():
    for _i, _e, compiles, model in BADS:
        log.info(f"model: {model}")
        try:
            checker = compiler.compileModel(model)
            compiled = True
        except ModelError:
            compiled = False
        assert compiled == compiles, f"bad model compilation: {model} ({compiles})"

def json_schema_test_suite(version, fmodel):
    # load model
    with open(fmodel) as f:
        checker = compiler.compileModel(json.load(f))
    # get all tests
    path = pathlib.Path(f"./JSON-Schema-Test-Suite/tests/{version}")
    for jstest in path.glob("*.json"):
        log.info(f"considering file {jstest}")
        with open(jstest) as f:
            tests = json.load(f)
            assert isinstance(tests, list)
            for test in tests:
                schema = test["schema"]
                assert checker(schema), f"{jstest}/{test['description']} is valid for {fmodel} ({checker._reasons}) {str(checker)}"

def test_draft3_fuzzy():
    # strict: fail on "definitions"
    # nesting: fail on "definitions"
    json_schema_test_suite("draft3", "../models/draft-03-fuzzy.model.json")

def test_draft4_fuzzy():
    # strict: errors on "$comment"
    json_schema_test_suite("draft4", "../models/draft-04-fuzzy.model.json")

def test_draft6_fuzzy():
    json_schema_test_suite("draft6", "../models/draft-06-fuzzy.model.json")

def test_draft7_fuzzy():
    json_schema_test_suite("draft7", "../models/draft-07-fuzzy.model.json")

def test_draft8_fuzzy():
    json_schema_test_suite("draft2019-09", "../models/draft-2019-09-fuzzy.model.json")

def test_draft9_fuzzy():
    # strict: error on maxContains with number instead of integer
    json_schema_test_suite("draft2020-12", "../models/draft-2020-12-fuzzy.model.json")

def test_draft_next_fuzzy():
    json_schema_test_suite("draft-next", "../models/draft-next-fuzzy.model.json")
