import copy
import json
import logging
import re
from pathlib import Path

import pytest

from json_model.model import JsonModel
from json_model.resolver import Resolver
from json_model.script import model_checker_from_json, jmc_script
from json_model.values import (simplest, bounds, optionals, branches, violations,
                               vectors, UnsupportedValue, Vacuous,
                               _PREDEFS, _PREDEF_VIOLATIONS, _matches, _verify, _compile,
                               _outranking, _names, _PREDEF_NAMES, _NO_NAME_PREDEFS, _rejected,
                               _mistyped, _ultimate, _ROOT_TYPES, _TYPE_VIOLATIONS,
                               _sites, _defs, _document, _unclaimed, _EXTRA_NAMES,
                               _mandatory, _object_sites, _measured, _breaks,
                               _violations_constrained, _justified, _rejects,
                               _refuses, _anything, _recheck)

CONSTRAINT_OPS = {"=", "!=", "<", "<=", ">", ">=", "!"}
_LAST_STEP_RE = re.compile(r"\.'([^']*)'$|\.([^.\[\]'\s]+)$|\[(\d+)\]$")

def last_step(pointer):
    """Last step of a model path expression."""
    match = _LAST_STEP_RE.search(pointer)
    if match is None:
        return ""
    quoted, name, index = match.groups()
    return quoted if quoted is not None else name or index

def constrained(model):
    """Violations of an explicit constraint, leaving type violations out."""
    return {p: v for p, v in violations(model).items()
            if last_step(p) in CONSTRAINT_OPS}

def below_root(found):
    """Violations of a mapping which do not replace the whole document."""
    return {p: v for p, v in found.items() if not p.endswith(" root invalid")}

def roots(model):
    """Violations which replace the whole document with a value of another type."""
    return {p: v for p, v in violations(model).items() if p.endswith(" root invalid")}

def nested(model):
    """Violations which alter one position of the document, root types left out."""
    return below_root(violations(model))

def unrooted(tests):
    """Test vectors with the root type violations left out."""
    kept, skip = [], False
    for entry in tests:
        if isinstance(entry, str):
            skip = entry.endswith(" root invalid") or " root invalid DUPLICATE" in entry
        if not skip:
            kept.append(entry)
    return kept

def test_null_model_gives_null():
    assert simplest(None) is None

def test_bool_model_gives_a_bool():
    assert simplest(True) is False

def test_false_is_not_a_bool_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest(False)

def test_non_negative_int_model_gives_zero():
    v = simplest(0)
    assert v == 0 and type(v) is int

def test_positive_int_model_gives_one():
    v = simplest(1)
    assert v == 1 and type(v) is int

def test_any_int_model_gives_zero():
    v = simplest(-1)
    assert v == 0 and type(v) is int

def test_other_int_is_not_a_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest(42)

def test_non_negative_float_model_gives_zero():
    v = simplest(0.0)
    assert v == 0.0 and type(v) is float

def test_positive_float_model_gives_a_positive_float():
    v = simplest(1.0)
    assert v > 0.0 and type(v) is float

def test_any_float_model_gives_zero():
    v = simplest(-1.0)
    assert v == 0.0 and type(v) is float

def test_negative_zero_float_model_is_accepted():
    v = simplest(-0.0)
    assert v == 0.0 and type(v) is float

def test_other_float_is_not_a_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest(2.0)

def test_any_string_model_gives_empty_string():
    assert simplest("") == ""



def test_unknown_reference_is_an_invalid_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("$Foo")

VAL_MODELS = [ None, True, 0, 1, -1, 0.0, 1.0, -1.0 ]

@pytest.mark.parametrize("model", VAL_MODELS)
def test_all_non_string_scalar_models_are_supported(model):
    simplest(model)

SCALAR_MODELS = VAL_MODELS + [ "" ]

@pytest.mark.parametrize("model", SCALAR_MODELS)
def test_simplest_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_escaped_string_constant():
    assert simplest("_XXX") == "XXX"

def test_empty_string_constant():
    assert simplest("_") == ""

def test_bare_string_constant():
    assert simplest("XXX") == "XXX"

def test_bare_string_constant_starting_with_a_digit():
    assert simplest("9abc") == "9abc"

def test_bare_string_constant_with_a_space():
    assert simplest("a b") == "a b"

def test_escaped_string_constant_starting_with_underscore():
    assert simplest("__foo") == "_foo"

def test_escaped_string_constant_hiding_a_predef():
    assert simplest("_$INT") == "$INT"

def test_escaped_string_constant_hiding_a_scalar_constant():
    assert simplest("_=null") == "=null"

def test_escaped_string_constant_hiding_a_regex():
    assert simplest("_/a/") == "/a/"

def test_literal_regex():
    assert simplest("/^x-/") == "x-"

def test_anchors_are_dropped():
    assert simplest("/^abc$/") == "abc"

def test_any_char_gives_one_char():
    v = simplest("/./")
    assert type(v) is str and len(v) == 1

def test_star_gives_nothing():
    assert simplest("/^[a-z]*$/") == ""

def test_plus_gives_one():
    assert simplest("/^ab+c$/") == "abc"

def test_counted_repeat_is_repeated():
    assert simplest("/^\\d{4}$/") == "0000"

def test_bounded_repeat_takes_the_minimum():
    assert simplest("/^a{2,5}$/") == "aa"

def test_char_class_takes_the_first_char():
    assert simplest("/^[a-z][0-9]$/") == "a0"

def test_char_class_literal_before_range():
    assert simplest("/^[-a-z]$/") == "-"

def test_word_category():
    assert simplest("/^\\w+$/") == "a"

def test_space_category():
    assert simplest("/^\\s$/") == " "

def test_branch_takes_the_first_alternative():
    assert simplest("/^(<=|>=|<|>)$/") == "<="

def test_group_is_transparent():
    assert simplest("/^(ab)+$/") == "ab"

def test_optional_group_is_dropped():
    assert simplest("/^3\\.1\\.\\d+(-.+)?$/") == "3.1.0"

def test_regex_options_are_kept():
    assert simplest("/bearer/i") == "bearer"

def test_regex_containing_a_slash():
    assert simplest("/^//") == "/"

def test_negated_class_is_not_supported_yet():
    with pytest.raises(UnsupportedValue):
        simplest("/^[^a]$/")

def test_backref_is_not_supported_yet():
    with pytest.raises(UnsupportedValue):
        simplest("/(ab)+\\1/")

def test_extended_regex_is_not_supported_yet():
    with pytest.raises(UnsupportedValue, match="extended"):
        simplest("/^/($REGEX)/[a-z]*$/X")

def test_invalid_regex_is_rejected():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("/^(a$/")

REGEX_MODELS = [ "/^x-/", "/^abc$/", "/./", "/^[a-z]*$/", "/^ab+c$/", "/^\\d{4}$/", "/^a{2,5}$/",
                 "/^[a-z][0-9]$/", "/^[-a-z]$/", "/^\\w+$/", "/^\\s$/", "/^(<=|>=|<|>)$/",
                 "/^(ab)+$/", "/^3\\.1\\.\\d+(-.+)?$/", "/bearer/i", "/^//", "/^#[0-9a-fA-F]{6}$/",
                 "/^[a-z][-a-z0-9_]+$/", "/^[1-5](\\d\\d|XX)$/", "/^\\d{7}-\\d{3}[A-Z]$/" ]

@pytest.mark.parametrize("model", REGEX_MODELS)
def test_regex_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

STR_CONST_MODELS = [ "_XXX", "_", "XXX", "9abc", "a b", "__foo", "_$INT", "_=null", "_/a/" ]

@pytest.mark.parametrize("model", STR_CONST_MODELS)
def test_string_constant_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_null_constant():
    assert simplest("=null") is None

def test_true_constant():
    assert simplest("=true") is True

def test_false_constant():
    assert simplest("=false") is False

def test_zero_int_constant():
    v = simplest("=0")
    assert v == 0 and type(v) is int

def test_negative_int_constant():
    v = simplest("=-5432")
    assert v == -5432 and type(v) is int

def test_float_constant():
    v = simplest("=3.14159")
    assert v == 3.14159 and type(v) is float

def test_exponent_constant_is_a_float():
    v = simplest("=1E5")
    assert v == 100000.0 and type(v) is float

def test_negative_exponent_constant():
    v = simplest("=1e-3")
    assert v == 0.001 and type(v) is float

def test_zero_float_constant():
    v = simplest("=0.0")
    assert v == 0.0 and type(v) is float

def test_leading_plus_constant_is_rejected():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("=+5")

def test_trailing_dot_constant_is_rejected():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("=1.")

def test_bad_constant_is_rejected():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("=oops")

def test_leading_zero_int_constant():
    v = simplest("=01")
    assert v == 1 and type(v) is int

def test_leading_zeros_float_constant():
    v = simplest("=-00.5")
    assert v == -0.5 and type(v) is float

CONST_MODELS = [ "=null", "=true", "=false", "=0", "=1", "=-5432", "=3.14159", "=1E5", "=1e-3", "=0.0",
                 "=01", "=007", "=00", "=-00.5" ]

@pytest.mark.parametrize("model", CONST_MODELS)
def test_scalar_constant_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_null_predef():
    assert simplest("$NULL") is None

def test_any_predef_gives_null():
    assert simplest("$ANY") == {}

def test_bool_predef():
    assert simplest("$BOOL") is False

def test_int_predef():
    v = simplest("$INT")
    assert v == 0 and type(v) is int

def test_unsigned_predef():
    v = simplest("$U32")
    assert v == 0 and type(v) is int

def test_float_predef():
    v = simplest("$FLOAT")
    assert v == 0.0 and type(v) is float

def test_number_predef_accepts_an_int():
    v = simplest("$NUMBER")
    assert v == 0 and type(v) is int

def test_string_predef():
    assert simplest("$STRING") == ""

def test_regex_predef_is_an_empty_regex():
    assert simplest("$REGEX") == ""

def test_date_predef():
    assert simplest("$DATE") == "1970-01-01"

def test_uuid_predef():
    assert simplest("$UUID") == "00000000-0000-0000-0000-000000000000"

def test_none_predef_has_no_value():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest("$NONE")

def test_extension_predef_is_not_supported():
    with pytest.raises(UnsupportedValue):
        simplest("$__EXTENSION_COLOR")

PREDEF_MODELS = [ "$ANY", "$NULL", "$BOOL", "$BOOLEAN", "$INT", "$INTEGER", "$I32", "$I64",
                  "$U32", "$U64", "$FLOAT", "$F32", "$F64", "$NUMBER", "$STRING", "$REGEX",
                  "$EXREG", "$JSONPT", "$DATE", "$TIME", "$TIMETZ", "$DATETIME", "$DURATION",
                  "$UUID", "$CARD", "$IP4", "$IP6", "$HOST", "$ETH", "$URL", "$URI", "$URL_REL",
                  "$EMAIL", "$JSON", "$SEMVER" ]

@pytest.mark.parametrize("model", PREDEF_MODELS)
def test_predef_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_every_predef_is_covered_or_knowingly_skipped():
    from json_model.predefs import MODEL_PREDEFS
    skipped = { "$NONE", "$__EXTENSION_COLOR", "$__EXTENSION_REL_JSONPT" }
    assert MODEL_PREDEFS - set(PREDEF_MODELS) - skipped == set()

@pytest.mark.parametrize("model", sorted(_PREDEF_VIOLATIONS))
def test_predef_violation_breaks_only_the_format(model):
    """Hard coded bad values keep the JSON type of the predef and are rejected."""
    bad, good = _PREDEF_VIOLATIONS[model], _PREDEFS[model]
    assert isinstance(bad, type(good)) and isinstance(good, type(bad))
    assert model_checker_from_json(model)(bad, "", None) is False

def test_every_broken_predef_is_a_known_predef():
    assert set(_PREDEF_VIOLATIONS) <= set(PREDEF_MODELS)

def test_predef_property_is_broken_by_format():
    assert violations({"d": "$DATE"})[".d bad"] == {"d": "1970-13-45"}

def test_constrained_predef_is_broken_by_format():
    assert violations({"@": "$DATE", ">=": 4})['.@ bad'] == "1970-13-45"

def test_predef_with_no_bad_value_is_only_broken_by_type():
    assert nested("$STRING") == {}

def test_empty_array_model():
    assert simplest([]) == []

def test_homogeneous_array_model_is_empty():
    assert simplest([0]) == []

def test_tuple_model_has_every_item():
    assert simplest([0, ""]) == [0, ""]

def test_tuple_model_recurses_into_items():
    assert simplest([True, "=null", "$INT", "/^ab+$/"]) == [False, None, 0, "ab"]

def test_comment_is_ignored():
    assert simplest(["# a comment", 0]) == []

def test_comment_inside_a_tuple_is_ignored():
    assert simplest([0, "# a comment", ""]) == [0, ""]

def test_only_comments_gives_an_empty_array():
    assert simplest(["# a comment"]) == []

def test_nested_array_model():
    assert simplest([[0]]) == []

def test_tuple_of_arrays():
    assert simplest([[0], []]) == [[], []]

def test_unknown_reference_in_a_tuple_is_invalid():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest([0, "$Foo"])

ARRAY_MODELS = [ [], [0], [0, ""], [True, "=null", "$INT", "/^ab+$/"], ["# a comment", 0],
                 [0, "# a comment", ""], ["# a comment"], [[0]], [[0], []], [[[0]]],
                 ["$STRING", "$UUID"], [{"|": [0, ""]}] ]

@pytest.mark.parametrize("model", ARRAY_MODELS)
def test_array_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_empty_object_model():
    assert simplest({}) == {}

def test_mandatory_property_is_kept():
    assert simplest({"!a": 0}) == {"a": 0}

def test_bare_name_is_mandatory():
    assert simplest({"a": 0}) == {"a": 0}

def test_escaped_name_is_mandatory():
    assert simplest({"_a": 0}) == {"a": 0}

def test_escaped_name_keeps_its_sentinel():
    assert simplest({"_?a": 0}) == {"?a": 0}

def test_optional_property_is_dropped():
    assert simplest({"?a": 0}) == {}

def test_regex_property_is_dropped():
    assert simplest({"/^a/": ""}) == {}

def test_reference_property_is_dropped():
    assert simplest({"$": {"Name": "/^a/"}, "$Name": 0}) == {}

def test_catch_all_property_is_dropped():
    assert simplest({"": 0}) == {}

def test_comment_property_is_dropped():
    assert simplest({"#": "note", "!a": 0}) == {"a": 0}

def test_dotted_comment_property_is_dropped():
    assert simplest({"#.doc": "note", "!a": 0}) == {"a": 0}

def test_mandatory_and_optional_mixed():
    assert simplest({"!a": 0, "?b": ""}) == {"a": 0}

def test_property_values_recurse():
    assert simplest({"!a": "$UUID", "!b": [0], "!c": "=null"}) == \
        {"a": "00000000-0000-0000-0000-000000000000", "b": [], "c": None}

def test_nested_objects():
    assert simplest({"!a": {"!b": {"?c": 0}}}) == {"a": {"b": {}}}

def test_object_inside_a_tuple():
    assert simplest([{"!a": 0}, []]) == [{"a": 0}, []]

def test_union_takes_the_first_alternative():
    assert simplest({"|": [0, ""]}) == 0

def test_union_order_matters():
    assert simplest({"|": ["", 0]}) == ""

def test_single_alternative_union():
    assert simplest({"|": [""]}) == ""

def test_union_skips_comments():
    assert simplest({"|": ["# a comment", "", 0]}) == ""

def test_nested_union():
    assert simplest({"|": [{"|": [0, ""]}, "=null"]}) == 0

def test_union_falls_back_to_a_usable_alternative():
    assert simplest({"$": {"X": {"|": [{"!a": "$X"}, ""]}}, "@": "$X"}) == ""

def test_recursive_union_uses_its_base_case():
    assert simplest({"$": {"X": {"|": [{"!a": "$X"}, 0]}}, "@": "$X"}) == 0

def test_union_with_no_usable_alternative_is_refused():
    with pytest.raises(UnsupportedValue, match="no alternative"):
        simplest({"$": {"X": {"|": [{"!a": "$X"}, {"!b": "$X"}]}}, "@": "$X"})

def test_union_inside_an_object():
    assert simplest({"!a": {"|": [0, ""]}}) == {"a": 0}

def test_union_inside_an_array_element():
    assert simplest({"@": [{"|": ["", 0]}], ">=": 2}) == ["", ""]

UNION_MODELS = [ {"|": [0, ""]}, {"|": ["", 0]}, {"|": [""]}, {"|": ["# a comment", "", 0]},
                 {"|": [{"|": [0, ""]}, "=null"]},
                 {"$": {"X": {"|": [{"!a": "$X"}, ""]}}, "@": "$X"},
                 {"$": {"X": {"|": [{"!a": "$X"}, 0]}}, "@": "$X"},
                 {"!a": {"|": [0, ""]}}, {"@": [{"|": ["", 0]}], ">=": 2},
                 {"|": ["$UUID", "$INT"]}, {"|": [[0], {"!a": 0}]} ]

@pytest.mark.parametrize("model", UNION_MODELS)
def test_union_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_xor_of_disjoint_scalar_types():
    assert simplest({"^": [True, -1]}) is False

def test_xor_of_null_and_bool():
    assert simplest({"^": [None, True]}) is None

def test_xor_of_int_and_float():
    assert simplest({"^": [-1, 1.0]}) == 0

def test_xor_with_any_avoids_the_other_branch():
    assert simplest({"^": ["$ANY", 0]}) == {}

def test_xor_of_overlapping_int_models_looks_past_the_branch_values():
    """Both branches yield 0, which the xor refuses: a violation of one branch does not."""
    value = simplest({"^": [-1, 0]})
    assert isinstance(value, int) and not isinstance(value, bool) and value < 0

def test_xor_of_overlapping_int_models_is_no_longer_contradicted():
    assert "# . simplest" in vectors({"^": [-1, 0]})

def test_xor_keeps_a_branch_value_when_it_is_the_only_one_accepted():
    """A value one branch builds and every other certainly rejects satisfies the xor."""
    assert simplest({"^": [{"a": 0}, {"b": ""}]}) == {"a": 0}

def test_xor_overlap_is_a_proven_violation():
    """Two branches yielding the same value make the xor certainly refuse it."""
    assert violations({"^": [-1, 0]})[".'^' overlap"] == 0

def test_xor_overlap_vector_is_unmarked():
    """The overlap violation is proven by construction, so no verdict is attached."""
    tests = vectors({"^": [-1, 0]})
    assert "# .'^' overlap" in tests
    assert [False, 0] == tests[tests.index("# .'^' overlap") + 1]

def test_xor_of_repeated_branches_has_no_overlap_violation():
    """The optimizer removes alternatives repeated word for word, so the oracle abstains."""
    assert not [k for k in violations({"^": ["", ""]}) if k.endswith(" overlap")]

def test_xor_of_disjoint_branches_has_no_overlap_violation():
    """Branches yielding different values overlap on nothing the generator can show."""
    assert not [k for k in violations({"^": [True, -1]}) if k.endswith(" overlap")]

def test_xor_of_identical_branches_is_empty():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"^": ["", ""]})

def test_xor_beside_other_properties_is_not_a_valid_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest({"^": [True, -1], "!a": 0})

XOR_MODELS = [ {"^": [True, -1]}, {"^": [None, True]}, {"^": [-1, 1.0]}, {"^": ["$ANY", 0]} ]

@pytest.mark.parametrize("model", XOR_MODELS)
def test_xor_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_and_with_any_uses_the_narrower_branch():
    assert simplest({"&": ["$ANY", 0]}) == 0

def test_and_of_nested_int_models():
    assert simplest({"&": [-1, 0]}) == 0

def test_and_of_object_and_catch_all():
    assert simplest({"&": [{"!a": 0}, {"": "$ANY"}]}) == {"a": 0}

def test_and_of_disjoint_types_is_empty():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"&": [0, ""]})

def test_and_of_objects_with_distinct_mandatory_properties_is_empty():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"&": [{"!a": 0}, {"!b": ""}]})

def test_empty_and_matches_any_value():
    assert simplest({"&": []}) == {}

AND_MODELS = [ {"&": ["$ANY", 0]}, {"&": [-1, 0]}, {"&": [{"!a": 0}, {"": "$ANY"}]} ]

@pytest.mark.parametrize("model", AND_MODELS)
def test_and_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_unique_array_of_non_negative_ints():
    assert simplest({"@": [0], ">=": 3, "!": True}) == [0, 1, 2]

def test_unique_array_of_any_ints():
    assert simplest({"@": [-1], ">=": 3, "!": True}) == [0, 1, -1]

def test_unique_array_of_floats():
    assert simplest({"@": [0.0], ">=": 3, "!": True}) == [0.0, 1.0, 2.0]

def test_unique_array_of_any_floats():
    assert simplest({"@": [-1.0], ">=": 3, "!": True}) == [0.0, 1.0, -1.0]

def test_unique_array_with_an_exact_length():
    assert simplest({"@": [0], "=": 2, "!": True}) == [0, 1]

def test_unique_array_of_positive_ints_is_empty():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"@": [1], ">=": 3, "!": True})

def test_unique_array_of_strings():
    assert simplest({"@": [""], ">=": 3, "!": True}) == ["", "a", "aa"]

def test_unique_array_of_strings_with_an_exact_length():
    assert simplest({"@": [""], "=": 2, "!": True}) == ["", "a"]

def test_unique_array_of_strings_grows_by_one_character():
    assert simplest({"@": [""], ">=": 4, "!": True}) == ["", "a", "aa", "aaa"]

def test_a_constrained_tuple_repeats_its_last_model():
    assert simplest({"@": [-1, "", True], ">=": 5}) == [0, "", False, False, False]

def test_a_constrained_tuple_repeats_a_catch_all_last_model():
    assert simplest({"@": ["", "$ANY"], ">=": 3}) == ["", {}, {}]

def test_a_constrained_tuple_repeats_its_last_model_for_an_exact_length():
    assert simplest({"@": ["", True, 0], "=": 5}) == ["", False, 0, 0, 0]

def test_a_constrained_tuple_may_be_shorter_than_its_models():
    assert simplest({"@": ["", True, 0], "<=": 2}) == []

def test_a_tuple_that_already_fits_is_kept():
    assert simplest({"@": ["", True, 0], ">=": 1}) == ["", False, 0]

def test_a_unique_constrained_tuple_keeps_its_prefix():
    assert simplest({"@": ["", 0], ">=": 4, "!": True}) == ["", 0, 1, 2]

def test_a_unique_tuple_with_a_bool_tail_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="unique constraint needs"):
        simplest({"@": [-1, "", True], ">=": 5, "!": True})

def test_an_empty_array_model_cannot_be_resized():
    with pytest.raises(UnsupportedValue, match="cannot resize array model"):
        simplest({"@": [], ">=": 2})

VARLEN_MODELS = [
    {"@": [-1, "", True], ">=": 5},
    {"@": ["", "$ANY"], ">=": 3},
    {"@": ["", True, 0], "=": 5},
    {"@": ["", True, 0], "<=": 2},
    {"@": ["", True, 0], ">=": 3, "<=": 9},
    {"@": [0, ""], ">": 3},
    {"@": ["", [0]], ">=": 4},
    {"@": ["", 0], ">=": 4, "!": True},
]

@pytest.mark.parametrize("model", VARLEN_MODELS)
def test_a_constrained_tuple_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    assert check(simplest(json.loads(json.dumps(model))), "", None) is True

def test_unique_array_of_regex_strings_is_not_supported_yet():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["/^a/"], ">=": 2, "!": True})

def test_unique_array_of_a_constant_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["_x"], ">=": 2, "!": True})

def test_unique_array_of_booleans_uses_the_whole_domain():
    assert simplest({"@": [True], "=": 2, "!": True}) == [False, True]

def test_unique_array_of_booleans_beyond_the_domain_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"@": [True], ">=": 3, "!": True})

def test_unique_array_of_nulls_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"@": [None], ">=": 2, "!": True})

def test_unique_array_of_a_numeric_constant_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["=5"], ">=": 2, "!": True})

def test_unique_array_of_an_enum():
    assert simplest({"@": [{"|": ["_a", "_b", "_c"]}], ">=": 3, "!": True}) == ["a", "b", "c"]

def test_unique_array_of_a_union_exhausts_every_branch():
    assert simplest({"@": [{"|": [None, True]}], ">=": 3, "!": True}) == [None, False, True]

def test_unique_array_of_a_short_enum_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": [{"|": ["_a", "_b"]}], ">=": 3, "!": True})

def test_unique_array_does_not_confuse_zero_with_false():
    assert simplest({"@": [{"|": ["=0", True]}], ">=": 3, "!": True}) == [0, False, True]

def test_unique_array_of_any():
    assert simplest({"@": ["$ANY"], ">=": 3, "!": True}) == [{}, None, False]

def test_unique_array_of_an_int_predef():
    assert simplest({"@": ["$INT"], ">=": 3, "!": True}) == [0, 1, -1]

def test_unique_array_of_a_string_predef():
    assert simplest({"@": ["$STRING"], ">=": 3, "!": True}) == ["", "a", "aa"]

def test_unique_array_of_an_unsigned_predef():
    assert simplest({"@": ["$U32"], ">=": 3, "!": True}) == [0, 1, 2]

def test_unique_array_of_a_bool_predef_is_unsatisfiable():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["$BOOL"], ">=": 3, "!": True})

def test_unique_array_of_a_regex_predef_is_not_supported_yet():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["$UUID"], ">=": 2, "!": True})

def test_unique_array_through_a_reference():
    model = {"$": {"C": {"|": ["_a", "_b", "_c"]}},
             "@": {"@": ["$C"], ">=": 3, "!": True}}
    assert simplest(model) == ["a", "b", "c"]

def test_unique_array_of_a_recursive_reference_is_refused():
    model = {"$": {"R": {"!a": "$R"}}, "@": {"@": ["$R"], ">=": 2, "!": True}}
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest(model)

def test_unique_array_of_none_predef_is_refused():
    with pytest.raises(UnsupportedValue, match="unique"):
        simplest({"@": ["$NONE"], ">=": 2, "!": True})

UNIQUE_MODELS = [ {"@": [0], ">=": 3, "!": True}, {"@": [-1], ">=": 3, "!": True},
                  {"@": [0.0], ">=": 3, "!": True}, {"@": [-1.0], ">=": 3, "!": True},
                  {"@": [0], "=": 2, "!": True}, {"@": [0], ">": 1, "!": True},
                  {"@": [""], ">=": 3, "!": True}, {"@": [""], "=": 2, "!": True},
                  {"@": [""], ">=": 4, "!": True}, {"@": [True], "=": 2, "!": True},
                  {"@": [True], ">=": 2, "!": True},
                  {"@": [{"|": ["_a", "_b", "_c"]}], ">=": 3, "!": True},
                  {"@": [{"|": [None, True]}], ">=": 3, "!": True},
                  {"@": [{"|": ["=0", True]}], ">=": 3, "!": True},
                  {"@": ["$ANY"], ">=": 3, "!": True}, {"@": ["$INT"], ">=": 3, "!": True},
                  {"@": ["$STRING"], ">=": 3, "!": True}, {"@": ["$U32"], ">=": 3, "!": True},
                  {"$": {"C": {"|": ["_a", "_b", "_c"]}},
                   "@": {"@": ["$C"], ">=": 3, "!": True}} ]

@pytest.mark.parametrize("model", UNIQUE_MODELS)
def test_unique_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_bare_target_model_is_transparent():
    v = simplest({"@": 0})
    assert v == 0 and type(v) is int

def test_bare_target_with_a_comment():
    assert simplest({"@": "", "#": "note"}) == ""

def test_bare_target_with_a_reference():
    assert simplest({"$": {"A": ""}, "@": "$A"}) == ""

def test_bare_target_with_an_object():
    assert simplest({"@": {"!a": 0}}) == {"a": 0}


def test_unknown_reference_in_a_property_is_invalid():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest({"!a": "$Foo"})

OBJECT_MODELS = [ {}, {"!a": 0}, {"a": 0}, {"_a": 0}, {"_?a": 0}, {"?a": 0}, {"/^a/": ""},
                  {"": 0}, {"#": "note", "!a": 0}, {"#.doc": "note", "!a": 0}, {"!a": 0, "?b": ""},
                  {"!a": "$UUID", "!b": [0], "!c": "=null"}, {"!a": {"!b": {"?c": 0}}},
                  {"!a": [{"!b": ""}]}, {"?a": 0, "?b": 0, "": ""} ]

@pytest.mark.parametrize("model", OBJECT_MODELS)
def test_object_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_definitions_do_not_reach_the_object_walk():
    assert simplest({"$": {"A": 0}, "!a": 0}) == {"a": 0}

def test_reference_resolves_to_its_definition():
    assert simplest({"$": {"A": 0}, "!a": "$A"}) == {"a": 0}

def test_reference_chain_is_followed():
    assert simplest({"$": {"A": "$B", "B": "$C", "C": ""}, "!a": "$A"}) == {"a": ""}

def test_reference_to_an_object():
    assert simplest({"$": {"P": {"!x": 0}}, "!a": "$P"}) == {"a": {"x": 0}}

def test_reference_to_an_array():
    assert simplest({"$": {"P": [0]}, "!a": "$P"}) == {"a": []}

def test_reference_used_twice():
    assert simplest({"$": {"A": 0}, "!a": "$A", "!b": "$A"}) == {"a": 0, "b": 0}

def test_recursion_through_an_optional_property():
    assert simplest({"$": {"X": {"?a": "$X"}}, "!r": "$X"}) == {"r": {}}

def test_recursion_through_an_array():
    assert simplest({"$": {"X": {"!a": ["$X"]}}, "!r": "$X"}) == {"r": {"a": []}}

def test_recursion_through_a_mandatory_property_has_no_value():
    with pytest.raises(UnsupportedValue, match="no finite value"):
        simplest({"$": {"X": {"!a": "$X"}}, "!r": "$X"})

def test_mutual_recursion_has_no_value():
    with pytest.raises(UnsupportedValue, match="no finite value"):
        simplest({"$": {"X": {"!a": "$Y"}, "Y": {"!b": "$X"}}, "!r": "$X"})

def test_unproductive_definition_that_is_never_used_is_ignored():
    assert simplest({"$": {"X": {"!a": "$X"}, "A": 0}, "!r": "$A"}) == {"r": 0}

def test_unsupported_predef_does_not_reach_the_resolver():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest("$__EXTENSION_COLOR")

REF_MODELS = [ {"$": {"A": 0}, "!a": "$A"},
               {"$": {"A": "$B", "B": "$C", "C": ""}, "!a": "$A"},
               {"$": {"P": {"!x": 0}}, "!a": "$P"},
               {"$": {"P": [0]}, "!a": "$P"},
               {"$": {"A": 0}, "!a": "$A", "!b": "$A"},
               {"$": {"X": {"?a": "$X"}}, "!r": "$X"},
               {"$": {"X": {"!a": ["$X"]}}, "!r": "$X"},
               {"$": {"X": {"!a": "$X"}, "A": 0}, "!r": "$A"},
               {"$": {"S": "/^ab+$/", "N": "$UUID"}, "!s": "$S", "!n": "$N"} ]

@pytest.mark.parametrize("model", REF_MODELS)
def test_reference_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_model_that_fails_to_build_is_reported_as_unsupported():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest({"%": {"Val": "$A"}, "$": {"A": 0}, "!a": "$A"})

TARGET_MODELS = [ {"@": 0}, {"@": "", "#": "note"}, {"$": {"A": ""}, "@": "$A"},
                  {"@": {"!a": 0}}, {"@": [0]}, {"@": "$UUID"},
                  {"$": {"X": {"?a": "$X"}}, "@": "$X"} ]

@pytest.mark.parametrize("model", TARGET_MODELS)
def test_target_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_greater_than_on_an_int():
    assert simplest({"@": 0, ">": 5}) == 6

def test_greater_or_equal_on_an_int():
    assert simplest({"@": 0, ">=": 5}) == 5

def test_less_than_keeps_the_simplest():
    assert simplest({"@": 0, "<": 5}) == 0

def test_less_than_forces_a_negative_when_allowed():
    assert simplest({"@": -1, "<": 0}) == -1

def test_equal_constraint():
    assert simplest({"@": 0, "=": 7}) == 7

def test_not_equal_moves_up():
    assert simplest({"@": 0, "!=": 0}) == 1

def test_two_sided_range():
    assert simplest({"@": 0, ">": 2, "<": 9}) == 3

def test_float_constraint_stays_a_float():
    v = simplest({"@": 0.0, ">": 1.5})
    assert v > 1.5 and type(v) is float

def test_float_upper_bound():
    v = simplest({"@": 0.0, "<=": 1.0})
    assert v == 0.0 and type(v) is float

def test_empty_range_is_empty():
    with pytest.raises(UnsupportedValue, match="no value exists"):
        simplest({"@": 0, "<": 0})

def test_string_length_constraint():
    assert simplest({"@": "", ">=": 4}) == "aaaa"

def test_string_exact_length():
    assert simplest({"@": "", "=": 2}) == "aa"

def test_array_length_constraint():
    assert simplest({"@": [0], ">=": 2}) == [0, 0]

def test_non_empty_unique_array():
    assert simplest({"@": ["$ANY"], ">=": 1, "!": True}) == [{}]

def test_unique_alone_allows_the_empty_array():
    assert simplest({"@": [0], "!": True}) == []

def test_value_that_already_fits_is_kept():
    assert simplest({"@": "$UUID", ">=": 4}) == "00000000-0000-0000-0000-000000000000"

def test_unique_with_repetition_yields_distinct_values():
    assert simplest({"@": [0], ">=": 2, "!": True}) == [0, 1]

def test_a_predefined_string_target_is_resizable():
    assert simplest({"@": "$STRING", ">=": 3}) == "aaa"

def test_a_predefined_string_target_with_an_exact_length():
    assert simplest({"@": "$STRING", "=": 2}) == "aa"

def test_a_referenced_string_target_is_resizable():
    assert simplest({"$": {"S": ""}, "@": {"@": "$S", ">=": 3}}) == "aaa"

def test_a_referenced_array_target_is_resizable():
    assert simplest({"$": {"L": [""]}, "@": {"@": "$L", ">=": 2}}) == ["", ""]

def test_a_referenced_object_target_is_growable():
    assert simplest({"$": {"O": {"": "$ANY"}}, "@": {"@": "$O", ">=": 2}}) == {"a": {}, "aa": {}}

def test_a_fixed_format_predefined_target_is_still_refused():
    with pytest.raises(UnsupportedValue, match="cannot resize string model"):
        simplest({"@": "$DATE", ">=": 30})

RESOLVED_TARGET_MODELS = [
    {"@": "$STRING", ">=": 3},
    {"@": "$STRING", "=": 2},
    {"$": {"S": ""}, "@": {"@": "$S", ">=": 3}},
    {"$": {"L": [""]}, "@": {"@": "$L", ">=": 2}},
    {"$": {"O": {"": "$ANY"}}, "@": {"@": "$O", ">=": 2}},
    {"$": {"L": [""]}, "@": {"@": "$L", ">=": 3, "!": True}},
]

@pytest.mark.parametrize("model", RESOLVED_TARGET_MODELS)
def test_a_resolved_target_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    assert check(simplest(json.loads(json.dumps(model))), "", None) is True

def test_string_comparison_is_not_supported_yet():
    with pytest.raises(UnsupportedValue, match="string comparison"):
        simplest({"@": "", ">": "abc"})

def test_a_non_numeric_comparison_bound_is_refused():
    """A bad bound must not reach the comparisons, even when validation is skipped."""
    for bound in ([], {}, None, True):
        jm = JsonModel({"@": 0, "=": bound}, Resolver())
        with pytest.raises(UnsupportedValue, match="unsupported comparison constraint"):
            simplest(jm._model, jm)

def test_a_constrained_object_grows_with_free_names():
    assert simplest({"@": {"": "$ANY"}, ">=": 2, "<=": 3}) == {"a": {}, "aa": {}}

def test_a_constrained_object_grows_with_pattern_names():
    assert simplest({"@": {"/^a/": ""}, ">=": 2}) == {"a": "", "aa": ""}

def test_a_constrained_object_prefers_its_optional_properties():
    assert simplest({"@": {"?a": 0, "?b": ""}, ">=": 2}) == {"a": 0, "b": ""}

def test_a_constrained_object_keeps_its_mandatory_properties():
    assert simplest({"@": {"!a": 0, "": "$ANY"}, ">=": 3}) == {"a": 0, "aa": {}, "aaa": {}}

def test_a_constrained_object_uses_optionals_before_free_names():
    assert simplest({"@": {"!a": 0, "?b": ""}, ">=": 2}) == {"a": 0, "b": ""}

def test_an_object_that_already_fits_is_kept():
    assert simplest({"@": {"!a": 0}, ">=": 1}) == {"a": 0}

def test_a_constrained_object_cannot_shrink():
    """The optimizer proves this empty, so reach the guard without validation."""
    jm = JsonModel({"@": {"!a": 0, "!b": ""}, "<=": 1}, Resolver())
    with pytest.raises(UnsupportedValue, match="cannot shrink object model"):
        simplest(jm._model, jm)

def test_an_object_without_free_names_cannot_grow():
    with pytest.raises(UnsupportedValue, match="properties"):
        simplest({"@": {"!a": 0}, ">=": 2})

def test_an_anchored_pattern_yields_a_single_name():
    with pytest.raises(UnsupportedValue, match="properties"):
        simplest({"@": {"/^a$/": ""}, ">=": 2})

def test_a_unique_constraint_on_an_object_is_refused():
    with pytest.raises(UnsupportedValue, match="unique constraint on a non-array"):
        simplest({"@": {"": "$ANY"}, ">=": 2, "!": True})

OBJECT_COUNT_MODELS = [
    {"@": {"": "$ANY"}, ">=": 2, "<=": 3},
    {"@": {"": 0}, ">=": 2},
    {"@": {"/^a/": ""}, ">=": 2},
    {"@": {"/^a/": ""}, ">": 0, "<=": 2},
    {"@": {"?a": 0, "?b": ""}, ">=": 2},
    {"@": {"!a": 0, "": "$ANY"}, ">=": 3},
    {"@": {"!a": 0, "?b": ""}, ">=": 2},
    {"@": {"": "$ANY"}, "=": 1},
]

@pytest.mark.parametrize("model", OBJECT_COUNT_MODELS)
def test_a_constrained_object_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    assert check(simplest(json.loads(json.dumps(model))), "", None) is True

def test_multiple_of_is_not_supported_yet():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest({"@": 0, ".mo": 3})

CONSTRAINT_MODELS = [ {"@": 0, ">": 5}, {"@": 0, ">=": 5}, {"@": 0, "<": 5}, {"@": -1, "<": 0},
                      {"@": 0, "=": 7}, {"@": 0, "!=": 0}, {"@": 0, ">": 2, "<": 9},
                      {"@": 0.0, ">": 1.5}, {"@": 0.0, "<=": 1.0}, {"@": "", ">=": 4},
                      {"@": "", "=": 2}, {"@": [0], ">=": 2}, {"@": ["$ANY"], ">=": 1, "!": True},
                      {"@": [0], "!": True}, {"@": "$UUID", ">=": 4}, {"@": [""], ">=": 1, "!": True},
                      {"@": [0, ""], ">=": 2} ]

@pytest.mark.parametrize("model", CONSTRAINT_MODELS)
def test_constrained_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def test_merge_collects_mandatory_properties():
    assert simplest({"+": [{"!a": 0}, {"!b": ""}]}) == {"a": 0, "b": ""}

def test_merge_drops_optional_properties():
    assert simplest({"+": [{"!a": 0}, {"?b": ""}]}) == {"a": 0}

def test_merge_with_a_catch_all():
    assert simplest({"+": [{"!a": 0}, {"": "$ANY"}]}) == {"a": 0}

def test_empty_merge_yields_an_empty_object():
    assert simplest({"+": []}) == {}

def test_merge_skips_comments():
    assert simplest({"+": ["# a comment", {"!a": 0}]}) == {"a": 0}

def test_merge_of_identical_properties():
    assert simplest({"+": [{"!a": 0}, {"!a": 0}]}) == {"a": 0}

def test_merge_through_a_reference():
    assert simplest({"$": {"A": {"!a": 0}}, "+": ["$A", {"!b": ""}]}) == {"a": 0, "b": ""}

def test_merge_inside_a_union():
    assert simplest({"|": [{"+": [{"!a": 0}, {"!b": ""}]}, 0]}) == {"a": 0, "b": ""}

def test_merge_nested_in_a_property():
    assert simplest({"!x": {"+": [{"!a": 0}, {"!b": ""}]}}) == {"x": {"a": 0, "b": ""}}

def test_merge_prefers_the_specific_model_over_any():
    assert simplest({"+": [{"!a": 0}, {"!a": "$ANY"}]}) == {"a": 0}

def test_merge_prefers_the_specific_model_whatever_the_order():
    assert simplest({"+": [{"!a": "$ANY"}, {"!a": 0}]}) == {"a": 0}

MERGE_MODELS = [ {"+": [{"!a": 0}, {"!a": "$ANY"}]}, {"+": [{"!a": "$ANY"}, {"!a": 0}]},
                 {"+": [{"!a": 0}, {"!b": ""}]}, {"+": [{"!a": 0}, {"?b": ""}]},
                 {"+": [{"!a": 0}, {"": "$ANY"}]}, {"+": ["# a comment", {"!a": 0}]},
                 {"+": [{"!a": 0}, {"!a": 0}]},
                 {"$": {"A": {"!a": 0}}, "+": ["$A", {"!b": ""}]},
                 {"|": [{"+": [{"!a": 0}, {"!b": ""}]}, 0]},
                 {"!x": {"+": [{"!a": 0}, {"!b": ""}]}},
                 {"+": [{"!a": [0]}, {"!b": {"?c": 0}}]} ]

@pytest.mark.parametrize("model", MERGE_MODELS)
def test_merge_value_validates_against_its_model(model):
    check = model_checker_from_json(model)
    assert check(simplest(model), "", None)

def _model_file(tmp_path, model):
    """Write a model to a temporary file and return its path."""
    path = tmp_path / "m.model.json"
    path.write_text(json.dumps(model))
    return str(path)

def test_cli_rejects_a_non_json_format(tmp_path):
    assert jmc_script(["--auto-values", "--format", "py",
                       _model_file(tmp_path, {"!a": 0})]) == 1

def test_a_constraint_the_optimizer_would_fold_is_kept():
    """The generator works on the model as written, not on its optimized form."""
    assert below_root(violations({"@": 0, "=": 2})) == {".'='": 3, '.@ invalid': None}

def test_violating_a_minimum_length_gives_one_char_less():
    assert constrained({"@": "", ">=": 3}) == {".'>='": "aa"}

def test_violating_a_maximum_length_gives_one_char_more():
    assert constrained({"@": "", "<=": 2}) == {".'<='": "aaa"}

def test_violating_a_strict_minimum_gives_the_bound():
    assert constrained({"@": "", ">": 2}) == {".'>'": "aa"}

def test_violating_a_strict_maximum_gives_the_bound():
    assert constrained({"@": "", "<": 3}) == {".'<'": "aaa"}

def test_violating_an_exact_length_gives_one_more():
    assert constrained({"@": "", "=": 2}) == {".'='": "aaa"}

def test_violating_a_forbidden_length_gives_that_length():
    assert constrained({"@": "", "!=": 2}) == {".'!='": "aa"}

def test_each_of_two_bounds_is_violated_separately():
    assert constrained({"@": "", ">=": 2, "<=": 4}) == {".'>='": "a", ".'<='": "aaaaa"}

def test_violating_an_array_minimum_length():
    assert constrained({"@": [0], ">=": 2}) == {".'>='": [0]}

def test_violating_an_array_maximum_length():
    assert constrained({"@": [0], "<=": 1}) == {".'<='": [0, 0]}

def test_violating_a_unique_array_keeps_distinct_items():
    assert constrained({"@": [""], ">=": 3, "!": True}) == {".'>='": ["", "a"], ".'!'": ["", "", ""]}

def test_nothing_violates_a_non_negative_minimum_length():
    assert constrained({"@": "", ">=": 0}) == {}

def test_an_unconstrained_object_has_no_constraint_to_violate():
    assert constrained({"!a": 0}) == {}

def test_a_scalar_has_no_constraint():
    assert constrained(0) == {}

def test_a_bare_target_has_no_constraint():
    assert constrained({"@": ""}) == {}

def test_a_string_comparison_constraint_gives_no_violation():
    assert constrained({"@": "", ">=": "$INT"}) == {}

def test_a_string_comparison_constraint_is_refused():
    with pytest.raises(UnsupportedValue, match="unsupported string comparison"):
        simplest({"@": "", ">=": "$INT"})

def test_a_float_maximum_is_snapped_up_to_an_integer_length():
    assert constrained({"@": "", "<=": 3.14159}) == {".'<='": "aaaa"}

def test_a_float_minimum_is_snapped_down_to_an_integer_length():
    assert constrained({"@": "", ">=": 3.14159}) == {".'>='": "aaa"}

def test_a_fractional_forbidden_length_is_refused():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        violations({"@": "", "!=": 3.14159})

def test_a_model_the_optimizer_cannot_handle_is_refused():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        simplest({"@": "", "!=": 3.14159})

def test_violating_a_numeric_minimum():
    assert constrained({"@": 0, ">=": 3}) == {".'>='": 2}

def test_violating_a_numeric_maximum():
    assert constrained({"@": 0, "<=": 2}) == {".'<='": 3}

def test_violating_a_strict_numeric_minimum_gives_the_bound():
    assert constrained({"@": 0, ">": 2}) == {".'>'": 2}

def test_violating_a_strict_numeric_maximum_gives_the_bound():
    assert constrained({"@": 0, "<": 3}) == {".'<'": 3}

def test_violating_an_exact_number_gives_one_more():
    assert constrained({"@": 0, "=": 2}) == {".'='": 3}

def test_violating_a_forbidden_number_gives_that_number():
    assert constrained({"@": 0, "!=": 2}) == {".'!='": 2}

def test_violating_a_zero_minimum_on_any_int_goes_negative():
    assert constrained({"@": -1, ">=": 0}) == {".'>='": -1}

def test_a_non_negative_int_model_cannot_go_below_zero():
    assert constrained({"@": 0, ">=": 0}) == {}

def test_each_of_two_numeric_bounds_is_violated_separately():
    assert constrained({"@": -1, ">=": 2, "<=": 4}) == {".'>='": 1, ".'<='": 5}

def test_violating_a_float_minimum_keeps_a_float():
    v = constrained({"@": -1.0, ">=": 3.0})
    assert v == {".'>='": 2.0} and type(v[".'>='"]) is float

def test_violating_a_float_maximum_keeps_a_float():
    v = constrained({"@": -1.0, "<=": 2.0})
    assert v == {".'<='": 3.0} and type(v[".'<='"]) is float

def test_an_integer_bound_on_a_float_model_gives_a_float():
    v = constrained({"@": -1.0, "!=": 2})
    assert v == {".'!='": 2.0} and type(v[".'!='"]) is float

def test_a_fractional_bound_on_an_int_model_snaps_to_an_int():
    assert constrained({"@": -1, ">=": 3.5}) == {".'>='": 3}

def test_a_fractional_forbidden_number_is_refused():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        violations({"@": -1, "!=": 3.5})

def test_a_bool_model_has_no_numeric_violation():
    assert constrained({"@": True, ">=": 1}) == {}

def test_violating_a_unique_array_gives_a_duplicate():
    assert constrained({"@": [""], "!": True}) == {".'!'": ["", ""]}

def test_violating_uniqueness_respects_a_minimum_length():
    assert constrained({"@": [0], "!": True, ">=": 4}) == {".'!'": [0, 0, 0, 0], ".'>='": [0, 1, 2]}

def test_a_unique_array_of_exactly_one_item_cannot_hold_a_duplicate():
    assert constrained({"@": [0], "!": True, "=": 1}) == {".'='": [0, 1]}

def test_a_unique_string_model_has_no_value():
    with pytest.raises(UnsupportedValue, match="unique constraint on a non-array"):
        simplest({"@": "", "!": True})

def test_a_unique_string_model_has_nothing_to_violate():
    assert constrained({"@": "", "!": True, ">=": 3}) == {}

def test_a_unique_number_model_has_no_value():
    with pytest.raises(UnsupportedValue, match="unique constraint on a non-array"):
        simplest({"@": 0, "!": True, ">=": 3})

VIOLATION_MODELS = [ {"@": "", ">=": 3}, {"@": "", "<=": 2}, {"@": "", ">": 2},
                     {"@": "", "<": 3}, {"@": "", "=": 2}, {"@": "", "!=": 2},
                     {"@": "", ">=": 2, "<=": 4}, {"@": [0], ">=": 2},
                     {"@": [0], "<=": 1}, {"@": [""], ">=": 3, "!": True},
                     {"@": ["$INT"], ">": 1, "<": 4},
                     {"@": "", "<=": 3.14159}, {"@": "", ">=": 3.14159}, {"@": "", ">": 3.14159},
                     {"@": 0, ">=": 3}, {"@": 0, "<=": 2}, {"@": 0, ">": 2},
                     {"@": 0, "<": 3}, {"@": 0, "=": 2}, {"@": 0, "!=": 2},
                     {"@": -1, ">=": 0}, {"@": -1, ">=": 2, "<=": 4},
                     {"@": -1.0, ">=": 3.0}, {"@": -1.0, "<=": 2.0},
                     {"@": -1.0, "!=": 2}, {"@": -1, ">=": 3.5},
                     {"@": "$U32", ">=": 3}, {"@": 1, "<=": 4},
                     {"@": [""], "!": True}, {"@": [0], "!": True, ">=": 4},
                     {"@": [0], "!": True, "=": 1} ]

@pytest.mark.parametrize("model", VIOLATION_MODELS)
def test_each_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

@pytest.mark.parametrize("model", VIOLATION_MODELS)
def test_each_violation_is_accepted_without_its_constraint(model):
    for pointer, value in constrained(model).items():
        op = last_step(pointer)
        check = model_checker_from_json({p: m for p, m in model.items() if p != op})
        assert check(value, "", None)

def test_violating_a_constraint_inside_a_property():
    assert constrained({"!a": {"@": "", ">=": 3}, "!b": 0}) == {".!a.'>='": {"a": "aa", "b": 0}}

def test_violating_a_constraint_inside_an_optional_property():
    assert constrained({"!a": 0, "?b": {"@": "", ">=": 3}}) == {".?b.'>='": {"a": 0, "b": "aa"}}

def test_violating_a_constraint_two_levels_down():
    assert constrained({"!a": {"!b": {"@": [0], ">=": 2}}}) == {".!a.!b.'>='": {"a": {"b": [0]}}}

def test_two_nested_constraints_are_violated_separately():
    assert constrained({"!a": {"@": "", ">=": 2}, "!b": {"@": "", ">=": 3}}) == {
        ".!a.'>='": {"a": "a", "b": "aaa"}, ".!b.'>='": {"a": "aa", "b": "aa"}}

def test_violating_a_constraint_inside_a_tuple():
    assert constrained(["", {"@": [0], ">=": 2}]) == {".[1].'>='": ["", [0]]}

def test_a_constraint_inside_a_union_is_reached():
    assert constrained({"|": [{"@": "", ">=": 3}, 0]}) == {".'|'[0].'>='": "aa"}

def test_a_constraint_inside_a_homogeneous_array_is_reached():
    assert constrained([{"@": "", ">=": 3}]) == {".[0].'>='": ["aa"]}

def test_a_nested_constraint_inside_a_constrained_object_is_reached():
    assert constrained({"@": {"!a": {"@": "", ">=": 3}}, ">=": 1}) == {".@.!a.'>='": {"a": "aa"}}

NESTED_MODELS = [ {"!a": {"@": "", ">=": 3}, "!b": 0}, {"!a": 0, "?b": {"@": "", ">=": 3}},
                  {"!a": {"!b": {"@": [0], ">=": 2}}},
                  {"!a": {"@": "", ">=": 2}, "!b": {"@": "", ">=": 3}},
                  ["", {"@": [0], ">=": 2}],
                  {"!a": {"@": [""], "!": True, ">=": 2}, "?c": {"@": 0, "<=": 5}} ]

@pytest.mark.parametrize("model", NESTED_MODELS)
def test_each_nested_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

def test_violating_a_constraint_in_a_definition():
    assert constrained({"$": {"Name": {"@": "", ">=": 3}}, "!a": "$Name"}) == {
        ".$Name.'>='": {"a": "aa"}}

def test_a_definition_used_twice_yields_one_vector():
    assert constrained({"$": {"N": {"@": "", ">=": 3}}, "!a": "$N", "!b": "$N"}) == {
        ".$N.'>='": {"a": "aa", "b": "aaa"}}

def test_violating_a_constraint_in_a_definition_of_a_definition():
    assert constrained({"$": {"A": {"!x": "$B"}, "B": {"@": [0], ">=": 2}}, "@": "$A"}) == {
        ".$B.'>='": {"x": [0]}}

def test_violating_a_definition_used_as_the_root_model():
    assert constrained({"$": {"S": {"@": "", ">=": 3}}, "@": "$S"}) == {".$S.'>='": "aa"}

def test_two_definitions_are_violated_separately():
    assert constrained({"$": {"A": {"@": "", ">=": 2}, "B": {"@": "", ">=": 3}},
                       "!a": "$A", "!b": "$B"}) == {
        ".$A.'>='": {"a": "a", "b": "aaa"}, ".$B.'>='": {"a": "aa", "b": "aa"}}

def test_a_recursive_definition_does_not_loop():
    assert constrained({"$": {"a": {"?next": "$a"}}, "@": "$a"}) == {}

def test_a_constraint_below_a_recursive_definition_is_still_found():
    assert constrained({"$": {"a": {"!n": {"@": "", ">=": 3}, "?next": "$a"}}, "@": "$a"}) == {
        ".$a.!n.'>='": {"n": "aa"}}

DEFS_MODELS = [ {"$": {"Name": {"@": "", ">=": 3}}, "!a": "$Name"},
                {"$": {"N": {"@": "", ">=": 3}}, "!a": "$N", "!b": "$N"},
                {"$": {"A": {"!x": "$B"}, "B": {"@": [0], ">=": 2}}, "@": "$A"},
                {"$": {"S": {"@": "", ">=": 3}}, "@": "$S"},
                {"$": {"A": {"@": "", ">=": 2}, "B": {"@": "", ">=": 3}},
                 "!a": "$A", "!b": "$B"},
                {"$": {"U": {"@": [""], "!": True, ">=": 2}}, "!u": "$U"} ]

@pytest.mark.parametrize("model", DEFS_MODELS)
def test_each_definition_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

def test_a_fixed_format_target_falls_back_to_its_natural_value():
    assert constrained({"@": "$DATE", "<=": 5}) == {".'<='": "1970-01-01"}

def test_a_string_constant_target_falls_back_to_its_natural_value():
    assert constrained({"@": "_abc", "=": 5}) == {".'='": "abc"}

def test_a_regex_target_falls_back_to_its_natural_value():
    assert constrained({"@": "/^ab$/", ">=": 5}) == {".'>='": "ab"}

def test_a_tuple_target_falls_back_to_its_natural_value():
    assert constrained({"@": [-1, "", True], ">=": 5}) == {".'>='": [0, "", False]}

def test_an_object_size_constraint_falls_back_to_the_empty_object():
    assert constrained({"@": {"": "$ANY"}, ">=": 2, "<=": 3}) == {".'>='": {}}

def test_a_fractional_float_bound_falls_back_to_zero():
    assert constrained({"@": 0.0, ">=": 0.5}) == {".'>='": 0.0}

def test_the_boundary_value_is_preferred_over_the_natural_value():
    assert constrained({"@": "", ">=": 3}) == {".'>='": "aa"}

def test_an_unusable_target_leaves_only_a_type_violation():
    assert nested({"@": True, ">=": 1}) == {'.@ invalid': None}

FALLBACK_MODELS = [ {"@": "$DATE", "<=": 5}, {"@": "_abc", "=": 5},
                    {"@": "/^ab$/", ">=": 5}, {"@": [-1, "", True], ">=": 5},
                    {"@": {"": "$ANY"}, ">=": 2, "<=": 3}, {"@": 0.0, ">=": 0.5},
                    {"@": "$UUID", "<": 10} ]

@pytest.mark.parametrize("model", FALLBACK_MODELS)
def test_each_fallback_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

@pytest.mark.parametrize("model", FALLBACK_MODELS)
def test_each_fallback_violation_is_accepted_without_its_constraint(model):
    for pointer, value in constrained(model).items():
        op = last_step(pointer)
        check = model_checker_from_json({p: m for p, m in model.items() if p != op})
        assert check(value, "", None)

def test_a_failing_property_is_named_in_the_error():
    with pytest.raises(UnsupportedValue, match=r"!b: .*no value exists"):
        simplest({"!a": 0, "!b": {"|": []}})

def test_a_failing_nested_property_gives_a_path():
    with pytest.raises(UnsupportedValue, match=r"!x: !b: "):
        simplest({"!x": {"!b": {"|": []}}})

def test_a_failing_tuple_item_is_numbered():
    with pytest.raises(UnsupportedValue, match=r"\b1: .*no value exists"):
        simplest(["", {"|": []}])

def test_a_tuple_item_index_follows_the_preprocessed_model():
    with pytest.raises(UnsupportedValue, match=r"\b1: "):
        simplest(["# a comment", "", {"|": []}])

def test_a_document_that_cannot_be_built_leaves_only_the_root_type():
    assert nested({"!a": {"@": "", ">=": 3}, "!b": {"|": []}}) == {}

def test_violating_a_constraint_in_a_top_level_union_branch():
    assert constrained({"|": [0, {"@": "", ">=": 3}]}) == {".'|'[1].'>='": "aa"}

def test_violating_a_constraint_inside_a_union_branch():
    assert constrained({"!a": {"|": [0, {"@": "", ">=": 3}]}}) == {".!a.'|'[1].'>='": {"a": "aa"}}

def test_violating_a_constraint_in_an_xor_branch():
    assert constrained({"^": [0, {"@": "", ">=": 3}]}) == {".'^'[1].'>='": "aa"}

def test_violating_a_constraint_in_a_union_inside_a_definition():
    assert constrained({"$": {"S": {"|": [0, {"@": "", ">=": 3}]}}, "!a": "$S"}) == {
        ".$S.'|'[1].'>='": {"a": "aa"}}

def test_union_branch_indexes_follow_the_preprocessed_model():
    assert constrained({"|": ["# a comment", 0, {"@": "", ">=": 3}]}) == {".'|'[1].'>='": "aa"}

def test_a_union_branch_deeper_than_the_document_is_rebuilt():
    assert constrained({"!a": {"|": [0, {"!x": {"@": "", ">=": 3}}]}}) == {
        ".!a.'|'[1].!x.'>='": {"a": {"x": "aa"}}}

def test_a_top_level_union_branch_is_rebuilt():
    assert constrained({"|": [0, {"!x": {"@": "", ">=": 3}}]}) == {".'|'[1].!x.'>='": {"x": "aa"}}

def test_a_union_branch_through_a_definition_is_rebuilt():
    assert constrained({"$": {"O": {"!x": {"@": "", ">=": 3}}},
                       "@": {"|": [0, "$O"]}}) == {".$O.!x.'>='": {"x": "aa"}}

def test_nested_union_branches_are_rebuilt():
    assert constrained({"|": [0, {"!x": {"|": [True, {"@": "", ">=": 3}]}}]}) == {
        ".'|'[1].!x.'|'[1].'>='": {"x": "aa"}}

OPERATOR_MODELS = [ {"|": [0, {"@": "", ">=": 3}]},
                    {"!a": {"|": [0, {"@": "", ">=": 3}]}},
                    {"^": [0, {"@": "", ">=": 3}]},
                    {"$": {"S": {"|": [0, {"@": "", ">=": 3}]}}, "!a": "$S"},
                    {"|": ["# a comment", 0, {"@": "", ">=": 3}]},
                    {"|": [{"@": [0], ">=": 2}, ""]} ]

@pytest.mark.parametrize("model", OPERATOR_MODELS)
def test_each_operator_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

def test_a_constraint_under_a_nested_optional_property_is_reached():
    assert constrained({"?a": {"?b": {"@": "", ">=": 3}}}) == {".?a.?b.'>='": {"a": {"b": "aa"}}}

def test_an_optional_property_is_rebuilt_with_its_mandatory_fields():
    assert constrained({"?a": {"!x": 0, "!y": {"@": "", ">=": 3}}}) == {
        ".?a.!y.'>='": {"a": {"x": 0, "y": "aa"}}}

def test_a_constraint_three_optional_levels_down():
    assert constrained({"?a": {"?b": {"?c": {"@": [0], ">=": 2}}}}) == {
        ".?a.?b.?c.'>='": {"a": {"b": {"c": [0]}}}}

def test_an_optional_property_beside_a_mandatory_one():
    assert constrained({"!m": 0, "?a": {"!y": {"@": "", ">=": 3}}}) == {
        ".?a.!y.'>='": {"m": 0, "a": {"y": "aa"}}}

OPTIONAL_MODELS = [ {"?a": {"?b": {"@": "", ">=": 3}}},
                    {"?a": {"!x": 0, "!y": {"@": "", ">=": 3}}},
                    {"?a": {"?b": {"?c": {"@": [0], ">=": 2}}}},
                    {"!m": 0, "?a": {"!y": {"@": "", ">=": 3}}},
                    {"?a": {"|": [0, {"!x": {"@": "", ">=": 3}}]}} ]

@pytest.mark.parametrize("model", OPTIONAL_MODELS)
def test_each_optional_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

def test_a_scalar_model_is_violated_by_another_type():
    assert roots(0)[".null root invalid"] is None

def test_a_null_model_is_violated_by_a_bool():
    assert roots(None)[".true root invalid"] is True

def test_a_bool_model_is_violated_by_null():
    assert roots(True)[".null root invalid"] is None

def test_a_predef_model_is_violated_by_a_bad_value():
    assert nested("$DATE") == {"bad": "1970-13-45"}

def test_a_constant_model_is_violated_by_another_type():
    assert ".'abc' root invalid" not in roots("_abc")

def test_a_regex_model_is_violated_by_another_type():
    assert roots("/^a+$/")[".'' root invalid"] == ""

def test_every_type_the_root_rejects_is_generated():
    assert roots(True) == {
        ".null root invalid": None, ".-42 root invalid": -42, ".3.14159 root invalid": 3.14159,
        ".'' root invalid": "", ".'abc' root invalid": "abc",
        ".[] root invalid": [], ".[1] root invalid": [1], ".{} root invalid": {}}

def test_a_root_type_the_model_accepts_is_left_out():
    assert ".-42 root invalid" not in roots(-1)

def test_a_root_type_the_model_rejects_is_kept_next_to_it():
    assert roots(-1)[".3.14159 root invalid"] == 3.14159

def test_a_root_value_already_used_by_a_constraint_is_left_out():
    assert ".-42 root invalid" not in violations({"@": -1, ">": -42})

def test_a_root_violation_never_reaches_a_nested_position():
    assert nested({"a": True}) == {
        ".a invalid": {"a": None}, ".a missing": {},
        '.no-such-prop extra': {"a": False, "no-such-prop": None}}

def test_a_root_violation_is_a_fresh_value():
    first, second = roots(True), roots(True)
    first[".[1] root invalid"].append(2)
    assert second[".[1] root invalid"] == [1]

ROOT_MODELS = [ 0, None, True, "", "$DATE", "$UUID", "_abc", "/^a+$/", "=3", -1,
                {"a": True}, ["", 0], [""], {"|": [0, ""]}, {"@": "", ">=": 3},
                {"$": {"S": ""}, "!a": "$S"}, {"@": {"": "$ANY"}, ">=": 2} ]

@pytest.mark.parametrize("model", ROOT_MODELS)
def test_each_root_type_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in roots(model).values():
        assert not check(value, "", None)

def test_vectors_label_a_root_type_violation_without_its_value():
    """The comment does not repeat the value shown by the test vector below it."""
    tests = vectors(True)
    assert tests[tests.index([False, None]) - 1] == "# . root invalid"

def test_each_property_type_is_violated_separately():
    assert nested({"?a": 0, "?b": ""}) == {
        '.?a invalid': {"a": None}, '.?b invalid': {"b": None},
        '.no-such-prop extra': {"no-such-prop": None}}

def test_each_tuple_item_type_is_violated_separately():
    assert nested(["", 0]) == {".[0] invalid": [None, 0], ".[1] invalid": ["", None]}

def test_a_nested_object_type_is_violated():
    assert nested({"?a": {"?b": 0}}) == {
        '.?a invalid': {"a": None}, '.?a.?b invalid': {"a": {"b": None}},
        '.no-such-prop extra': {"no-such-prop": None}, '.?a.no-such-prop extra': {"a": {"no-such-prop": None}}}

def test_a_type_in_a_definition_is_violated_once():
    assert nested({"$": {"S": ""}, "!a": "$S"}) == {
        '.$S invalid': {"a": None}, '.!a missing': {},
        '.no-such-prop extra': {"a": "", "no-such-prop": None}}

def test_a_union_type_is_violated_once():
    assert nested({"|": [0, ""]}) == {".'|'[0] invalid": None}

def test_a_nested_union_type_is_violated_at_the_union():
    assert nested({"!a": {"|": [0, ""]}}) == {
        '.!a invalid': {"a": None}, '.!a missing': {},
        '.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_an_optional_property_type_is_violated():
    assert nested({"?a": {"@": "", ">=": 3}}) == {
        ".?a.'>='": {"a": "aa"}, '.?a.@ invalid': {"a": None},
        '.no-such-prop extra': {"no-such-prop": None}}

def test_a_constrained_target_type_is_violated():
    assert nested({"@": "", ">=": 3}) == {".'>='": "aa", '.@ invalid': None}

def test_an_item_type_inside_a_homogeneous_array_is_reached():
    assert nested([""]) == {".[0] invalid": [None]}

def test_an_object_inside_a_homogeneous_array_is_reached():
    assert nested([{"!a": 0}]) == {
        ".[0] invalid": [None], '.[0].!a invalid': [{"a": None}],
        '.[0].!a missing': [{}], '.[0].no-such-prop extra': [{"a": 0, "no-such-prop": None}]}

def test_a_reference_inside_an_extended_regex_is_kept():
    model = {"$": {"character": {"|": ["Susie", "Calvin", "Hobbes"]}},
             "@": "/'($character:\\w+)'.*'($character:\\w+)'/X"}
    assert '.@ invalid' in violations(model)

def test_a_model_accepting_anything_has_no_type_to_violate():
    with pytest.raises(UnsupportedValue, match="every value matches the model"):
        violations("$ANY")

def test_a_model_whose_checker_never_terminates_is_survived():
    assert nested({"$": {"root": "$#"}, "?foo": {"|": ["$root", ["$root"]]}}) == {
        ".?foo.'|'[1] invalid": {"foo": None}, '.no-such-prop extra': {"no-such-prop": None}}

def test_a_missing_required_property_is_generated():
    assert nested({"!a": 0, "!b": ""}) == {
        '.!a invalid': {"a": None, "b": ""}, '.!b invalid': {"a": 0, "b": None},
        '.!a missing': {"b": ""}, '.!b missing': {"a": 0},
        '.no-such-prop extra': {"a": 0, "b": "", "no-such-prop": None}}

def test_the_only_required_property_leaves_an_empty_object():
    assert nested({"!a": 0}) == {
        '.!a invalid': {"a": None}, '.!a missing': {},
        '.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_an_optional_property_is_never_reported_as_missing():
    assert nested({"!a": 0, "?b": ""}) == {
        '.!a invalid': {"a": None}, '.?b invalid': {"a": 0, "b": None},
        '.!a missing': {}, '.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_a_bare_property_name_is_mandatory_too():
    assert nested({"a": 0}) == {
        ".a invalid": {"a": None}, ".a missing": {},
        '.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_a_missing_property_is_found_two_levels_down():
    assert nested({"!a": {"!b": 0}}) == {
        '.!a invalid': {"a": None}, '.!a.!b invalid': {"a": {"b": None}},
        '.!a missing': {}, '.!a.!b missing': {"a": {}},
        '.no-such-prop extra': {"a": {"b": 0}, "no-such-prop": None},
        '.!a.no-such-prop extra': {"a": {"b": 0, "no-such-prop": None}}}

def test_a_missing_property_inside_a_union_branch():
    assert nested({"|": [{"!a": 0}, ""]}) == {
        ".'|'[0] invalid": None, ".'|'[0].!a invalid": {"a": None},
        ".'|'[0].!a missing": {}, ".'|'[0].no-such-prop extra": {"a": 0, "no-such-prop": None}}

def test_a_merged_xor_is_verified_against_the_optimized_model():
    model = {"$": {"Aa": {"^": [{"a": 0}, {"b": 0}]},
                   "Bb": {"^": [{"a": 0}, {"c": 0}]},
                   "Cc": {"^": [{"b": 0}, {"c": 0}]}},
             "+": ["$Aa", "$Bb", "$Cc"]}
    check = model_checker_from_json(model)
    for pointer, value in violations(model).items():
        assert not check(value, "", None), pointer

MISSING_MODELS = [ {"!a": 0, "!b": ""}, {"!a": 0}, {"!a": 0, "?b": ""}, {"a": 0},
                   {"!a": {"!b": 0}}, {"|": [{"!a": 0}, ""]},
                   {"?a": {"!x": 0, "!y": ""}}, {"@": {"!a": 0, "!b": ""}, ">=": 2} ]

@pytest.mark.parametrize("model", MISSING_MODELS)
def test_each_missing_property_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

MANDATORY_MODELS = [ {"a": 0}, {"!a": 0, "?b": ""}, {"_a": 0}, {"a": 0, "b": ""},
                     {"a": {"b": 0}}, {"a": 0, "": "$ANY"}, {"a": 0, "/^x-/": ""},
                     {"?a": {"!x": 0}}, [{"a": 0}], {"&": [{"a": 0}, {"?b": ""}]},
                     {"|": [{"a": 0, "b": ""}, {"a": 0}]},
                     {"$": {"S": {"!a": 0}}, "@": "$S"} ]

@pytest.mark.parametrize("model", MANDATORY_MODELS)
def test_an_unbranched_missing_property_breaks_the_document(model):
    """Outside a union or xor, dropping a declared name invalidates the document."""
    jm, compiled = _compile(model, False, None, "", False)
    vjm, vmodel = _compile(model, True, None, "", False)
    try:
        doc = simplest(compiled, jm, frozenset())
    except UnsupportedValue:
        doc = None
    sites = list(_sites(compiled, [], [], [], jm, frozenset()))
    for mpath, vpath, frames, node, disjunction in _object_sites(sites):
        if disjunction is not None:
            continue
        try:
            built = simplest(node, jm, frozenset())
        except UnsupportedValue:
            continue
        for prop, name in _mandatory(node):
            if name not in built:
                continue
            sub = {p: v for p, v in built.items() if p != name}
            value = _document(sub, vpath, frames, doc, jm, frozenset())
            assert _verify(value, vmodel, vjm) is False, (mpath, name, value)

def test_a_missing_property_under_a_union_is_noted():
    """Dropping b leaves a document which the second alternative still matches."""
    model = {"|": [{"a": 0, "b": ""}, {"a": 0}]}
    assert model_checker_from_json(model)({"a": 0}, "", None) is True
    assert "# .'|'[0].b missing BAD PASS" in vectors(model)

def test_a_missing_mandatory_property_needs_no_compiler():
    """The name is declared, nothing else supplies it, and the site is not branched."""
    assert unrooted(vectors({"!a": 0})) == [
        "# . simplest", [True, {"a": 0}], "# .!a invalid", [False, {"a": None}],
        "# .!a missing", [False, {}],
        "# .no-such-prop extra", [False, {"a": 0, "no-such-prop": None}]]

def test_a_catch_all_key_matches_every_name():
    assert _matches("anything", "") is True

def test_a_pattern_key_matches_by_regex():
    assert _matches("abc", "/^ab/") is True
    assert _matches("xab", "/^ab/") is False

def test_a_pattern_key_searches_rather_than_anchors():
    assert _matches("xabcx", "/abc/") is True

def test_a_pattern_key_honours_its_flags():
    assert _matches("ABC", "/^abc$/i") is True
    assert _matches("ABC", "/^abc$/") is False

def test_a_pattern_key_keeps_regex_escapes():
    assert _matches("a.b", "/^a\\.b$/") is True
    assert _matches("axb", "/^a\\.b$/") is False

@pytest.mark.parametrize("key", ["/^a/X", "/[/", "/a", "$Ref", "$", "$EMAIL", "$URL"])
def test_an_undecidable_key_abstains(key):
    assert _matches("x", key) is None

PREDEF_NAMES_POOL = [
    "", " ", "a", "abc", "0", "null", "{", "1970-01-01", "20240101", "1970-13-45",
    "2024-02-29", "2023-02-29", "00:00:00", "25:00:00", "23:59:60", "00:00:60",
    "00:00:00+00:00", "1970-01-01T00:00:00", "1970-01-01T25:00:00",
    "0.0.0.0", "256.0.0.1", "1.2.3", "01.2.3.4", "::", "::1", "xyz::", "fe80::1%eth0",
    "00000000-0000-0000-0000-000000000000", "{00000000-0000-0000-0000-000000000000}",
    "00:00:00:00:00:00", "00:00:00:00:00", "1.0.0", "1.0.0-rc.1", "v1.0.0",
    "4111111111111111", "411111111111111", "P", "PT0S", "P1Y2M3DT4H5M6S",
    "/", "/a/b", "/a~0b", "/a~2b", "[", "a*", "\\p{L}+",
]

@pytest.mark.parametrize("predef", sorted(_PREDEF_NAMES))
def test_the_predef_oracle_agrees_with_the_compiler(predef):
    """Every predefined property key, decided without asking the compiler."""
    check = model_checker_from_json({predef: 0})
    for name in PREDEF_NAMES_POOL:
        assert _matches(name, predef) == check({name: 0}, "", None), (predef, name)

@pytest.mark.parametrize("predef", sorted(_NO_NAME_PREDEFS))
def test_a_non_string_predef_key_matches_no_name(predef):
    check = model_checker_from_json({predef: 0})
    for name in ["a", "1", "", "true", "null"]:
        assert _matches(name, predef) is False
        assert check({name: 0}, "", None) is False

@pytest.mark.parametrize("kinds,value,expect", [
    ({int}, None, True), ({int}, True, True), ({int}, 3.14159, True), ({int}, "", True),
    ({int}, -42, False), ({bool}, True, False), ({bool}, -42, True),
    ({str}, "abc", False), ({str}, -42, True), ({type(None)}, None, False),
    ({list}, [], False), ({dict}, {}, False), ({dict}, [], True),
    ({int, str}, -42, False), ({int, str}, "abc", False), ({int, str}, 3.14159, True),
    (set(), -42, True), (set(), None, True),
])
def test_a_value_of_another_type_cannot_match(kinds, value, expect):
    assert _mistyped(value, kinds) is expect

def test_a_float_type_rejects_an_int_unless_the_model_is_loose():
    """$FLOAT excludes ints, $NUMBER admits them, and loose float widens $FLOAT."""
    assert _mistyped(-42, {float}) is True
    assert _mistyped(-42, {int, float}) is False

def test_an_unknown_ultimate_type_decides_nothing():
    assert all(_mistyped(v, None) is False for v in _ROOT_TYPES)

@pytest.mark.parametrize("model,expect", [
    ("$INT", {int}), ("$FLOAT", {float}), ("$NUMBER", {int, float}),
    ("$STRING", {str}), ("$BOOL", {bool}), ("$NULL", {type(None)}),
    ("$ANY", None), ("$NONE", set()), ("Susie", {str}), ("=null", {type(None)}),
    ({"a": 0}, {dict}), (["$INT"], {list}),
    ({"|": ["$INT", "$STRING"]}, {int, str}),
    ({"^": ["$INT", "$STRING"]}, {int, str}),
    ({"&": ["$INT", "$NUMBER"]}, {int}),
    ({"#": "JSON_MODEL_LOOSE_FLOAT", "@": -1.0}, {int, float}),
    ({"#": "JSON_MODEL_LOOSE_INT", "@": -1}, {int, float}),
    ("=1E3", {float}), ("=1.0", {float}), ("=-5432", {int}),
])
def test_the_types_a_model_accepts_are_enumerated(model, expect):
    jm, compiled = _compile(model, True, None, "", False)
    assert _ultimate(jm, compiled) == expect

def test_a_recursive_reference_still_enumerates_types():
    """The reference to the whole model resolves, and the fixpoint closes the cycle."""
    model = {"$": {"root": "$#"}, "?foo": {"|": ["$root", ["$root"]]}}
    jm, compiled = _compile(model, False, None, "", False)
    assert _ultimate(jm, compiled["?foo"]) == {dict, list}

@pytest.mark.parametrize("model", ["$INT", "$FLOAT", "$NUMBER", "$STRING", "$BOOL",
                                  "$NULL", "$NONE", {"|": ["$INT", "$STRING"]},
                                  {"^": ["$INT", "$STRING"]}, {"a": 0}, ["$INT"],
                                  {"#": "JSON_MODEL_LOOSE_FLOAT", "@": -1.0}])
def test_the_type_set_never_contradicts_the_compiler(model):
    """Every root value the type set rules out must be rejected by the compiler."""
    jm, compiled = _compile(model, True, None, "", False)
    kinds = _ultimate(jm, compiled)
    for value in _ROOT_TYPES:
        if _mistyped(value, kinds):
            assert _verify(value, compiled, jm) is not True, (model, value)

ROOT_ORACLE_MODELS = ["$INT", "$FLOAT", "$NUMBER", "$STRING", "$BOOL", "$NULL", "$ANY",
                      {"@": "$INT", ">=": 10}, {"a": 0}, ["$INT"], "Susie", "=null",
                      {"|": ["$INT", "$STRING"]}, {"|": ["$INT", "$I32"]}]

@pytest.mark.parametrize("model", ROOT_ORACLE_MODELS)
def test_the_root_type_oracle_never_contradicts_the_compiler(model):
    """Where the oracle rules a root value out, the compiler must agree."""
    jm, compiled = _compile(model, False, None, "", False)
    utype = _ultimate(jm, compiled)
    for value in _ROOT_TYPES:
        if _mistyped(value, utype):
            assert _verify(value, compiled, jm) is False, (model, value)

TYPE_ORACLE_MODELS = [{"a": 0}, {"!a": ""}, {"?x": "$DATE"}, ["$INT"], {"a": {"b": 0}},
                      {"a": "$STRING", "b": "$BOOL"}, {"|": [{"a": 0}, {"b": ""}]},
                      {"a": {"@": "$INT", ">=": 10}}, {"a": "$ANY"}]

@pytest.mark.parametrize("model", TYPE_ORACLE_MODELS)
def test_the_type_oracle_never_contradicts_the_compiler_at_a_site(model):
    """Where the oracle rules a type out for a sub-model, the compiler must agree."""
    jm, compiled = _compile(model, False, None, "", False)
    defs = _defs(jm)
    for mpath, vpath, frames, props, disjunction in _sites(compiled, [], [], [], jm, frozenset()):
        if not mpath or set(props) - {"@"}:
            continue
        target = _ultimate(jm, props["@"])
        for candidate in _TYPE_VIOLATIONS:
            if _mistyped(candidate, target):
                assert _verify(candidate, props["@"], jm, defs) is False, (mpath, candidate)

def notes(tests, warn):
    """Comments of a test vector file which end with a warning."""
    return [t for t in tests if isinstance(t, str) and t.endswith(f" {warn}")]

def test_nothing_is_marked_when_every_oracle_decides():
    """Nine root types go by type, 9 and -42 by the bound, "abc" by the date format."""
    assert notes(vectors({"@": "$INT", ">=": 10}), "AGREES") == []
    assert notes(vectors("$DATE"), "AGREES") == []

@pytest.mark.parametrize("model", ["Susie", "_x", "=1", "/^a+$/", "$U32", 0, 1,
                                   {"|": ["a", "b"]},
                                   {"|": [{"a": "$INT"}, {"b": "$INT"}]},
                                   {"a": 0, "$REGEX": "$INT"}])
def test_no_violation_needs_the_compiler(model):
    """Constants, patterns, signs, string bounds and unions are all decided."""
    marks = notes(vectors(model), "BAD")
    assert all(m.endswith((" branch BAD", " present BAD")) for m in marks), marks

def test_an_unsigned_predef_violation_is_proven_by_its_sign():
    """The negative value breaking $U32 is not a string the format checkers can decide."""
    assert notes(vectors("$U32"), "AGREES") == []
    assert [False, -1] in vectors("$U32")

@pytest.mark.parametrize("model", ["$INT", {"@": "$INT", ">=": 10}, {"!a": 0}, ["$INT"]])
def test_every_unmarked_vector_is_decided_without_the_compiler(model):
    """Whatever stays unmarked must be right, since nothing checked it."""
    check = model_checker_from_json(model)
    label = None
    for entry in vectors(model):
        if isinstance(entry, str):
            label = entry
            continue
        if label and label.endswith(" BAD"):
            continue
        expect, value = entry
        assert check(value, "", None) is expect, (label, entry)

def test_cli_keeps_marked_values(tmp_path, capsys):
    path = _model_file(tmp_path, {"|": [{"a": "$INT"}, {"a": "$NULL"}]})
    assert jmc_script(["--auto-values", path]) == 0
    out = json.loads(capsys.readouterr().out)
    assert "# .'|'[1] branch BAD" in out
    assert "# .'|'[0].a invalid SKIPPED: valid for the model" in out

CHECK_BACK_MODELS = [{"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 5}]},
                     {"|": [{"a": 0, "b": ""}, {"a": 0}]},
                     {"|": [{"a": "$INT"}, {"a": "$ANY"}]}]

def paired(tests, comment):
    """Test vector which follows a comment in a test vector file."""
    return tests[tests.index(comment) + 1]

def test_a_value_no_oracle_proves_is_settled_when_the_validator_agrees():
    """No oracle relates the two bounds, so the validator agreeing is what settles 5."""
    tests = vectors(CHECK_BACK_MODELS[0])
    assert "# .'|'[1].'>=' bound" in tests
    assert paired(tests, "# .'|'[1].'>=' bound") == [True, 5]

def test_a_value_the_validator_leaves_unchecked_expects_nothing():
    """$ANY accepts the branch value, so nothing proves the document is valid."""
    tests = vectors(CHECK_BACK_MODELS[2])
    assert paired(tests, "# .'|'[1] branch BAD") == [None, {"a": {}}]

def test_a_value_the_validator_refutes_expects_nothing():
    """The second alternative takes the shrunk object the generator meant to break."""
    tests = vectors(CHECK_BACK_MODELS[1])
    assert paired(tests, "# .'|'[0].b missing BAD PASS") == [None, {"a": 0}]

@pytest.mark.parametrize("model", CHECK_BACK_MODELS)
def test_no_verdict_is_stated_without_a_proof(model):
    """Only a mark the validator did not settle leaves the expected result unset."""
    label = None
    for entry in vectors(model):
        if isinstance(entry, str):
            label = entry
        elif entry[0] is None:
            assert label.rstrip().split()[-1] in ("BAD", "PASS", "FAIL"), label

def test_a_value_the_validator_refutes_is_flagged(monkeypatch):
    """A verdict the validator contradicts is renamed and dropped, whichever way they disagree."""
    entries = [(1, ".a", ["# .a invalid AGREES", [False, {"a": "x"}]]),
               (0, ".b", ["# .b bound AGREES", [True, {"a": "yy"}]])]
    monkeypatch.setattr("json_model.values._verify", lambda value, *args: value == {"a": "x"})
    _recheck(entries, {"a": "$STRING"}, None, "", False)
    assert [entry for *_, entry in entries] == [
        ["# .a invalid BAD PASS", [None, {"a": "x"}]],
        ["# .b bound BAD FAIL", [None, {"a": "yy"}]]]

def test_a_nested_union_supplies_the_value_its_alternative_hides():
    """Both alternatives build "hello", but the inner union also offers "world"."""
    assert simplest({"^": [{"|": ["_hello", "_world"]}, "_hello"]}) == "world"

def test_a_base_value_which_cannot_exist_is_named():
    """The model has no value at all, which is a fact about it, not a failure."""
    tests = vectors({"!a": 0, "!b": {"|": []}})
    assert "# . simplest SKIPPED: !b: no value exists for model: $NONE" in tests

def test_a_base_value_the_generator_cannot_build_gives_its_reason():
    """The generator gave up here, so the file names what it could not do."""
    tests = vectors({"$": {"R": {"a": "$R"}}, "@": "$R"})
    assert "# . simplest FAILED: a: no finite value for recursive model: $R" in tests

def test_a_refused_base_value_is_called_out():
    """No alternative of the and yields a value the compiler takes, so say it once."""
    tests = vectors({"&": ["/[a-z]/", "/[0-9]/"]})
    assert "# . simplest" in tests and "# . simplest BAD" not in tests
    assert [False, "a"] in tests
    assert any(t.startswith("# base values FAILED") for t in tests if isinstance(t, str))

def test_a_base_value_the_validator_cannot_judge_is_not_called_out():
    """Silence is not a refusal, so an unverifiable base keeps the file quiet."""
    tests = vectors({"|": [{"a": "$INT"}, {"a": "$ANY"}]})
    assert "# . simplest" in tests
    assert not any(t.startswith("# base values FAILED") for t in tests if isinstance(t, str))

def test_a_violation_no_oracle_proves_is_settled_by_the_validator(monkeypatch):
    """The validator refusing a value the generator meant to break confirms the violation."""
    entries = [(1, ".a", ["# .a invalid AGREES", [False, {"a": "x"}]])]
    monkeypatch.setattr("json_model.values._verify", lambda *args: False)
    _recheck(entries, {"a": "$STRING"}, None, "", False)
    assert [entry for *_, entry in entries] == [
        ["# .a invalid", [False, {"a": "x"}]]]

def test_a_validator_which_answers_nothing_leaves_unchecked(monkeypatch):
    """Silence is never read as a confirmation, whatever keeps the validator from answering."""
    entries = [(0, ".a", ["# .a invalid AGREES", [False, {"a": "x"}]]),
               (0, ".b", ["# .b bound AGREES", [True, {"a": "yy"}]]),
               (1, ".c", ["# .c missing SKIPPED: valid for the model"])]
    monkeypatch.setattr("json_model.values._verify", lambda *args: None)
    _recheck(entries, {"a": "$STRING"}, None, "", False)
    assert [entry for *_, entry in entries] == [
        ["# .a invalid BAD", [None, {"a": "x"}]],
        ["# .b bound BAD", [None, {"a": "yy"}]],
        ["# .c missing SKIPPED: valid for the model"]]

@pytest.mark.parametrize("model", CHECK_BACK_MODELS)
def test_the_check_back_pass_never_changes_a_value(model, monkeypatch):
    """Comments move and an unconfirmed verdict is dropped, no test vector value is lost."""
    checked = vectors(model)
    monkeypatch.setattr("json_model.values._recheck", lambda *args: None)
    kept = vectors(model)
    assert [t[1] for t in checked if isinstance(t, list)] == \
           [t[1] for t in kept if isinstance(t, list)]
    assert len(checked) - len(kept) == len(
        [t for t in checked if isinstance(t, str) and t.startswith("# base values FAILED")])

KEY_MODEL = {"$": {"Key": "$URL", "map": {"$Key": "$INT"},
                   "E": {"|": ["$map", "$Key"]}}, "@": "$E"}

def test_the_validator_reads_the_definitions_a_model_carries():
    """A model holding its own definitions is not nested inside the checked wrapper."""
    jm, _ = _compile(KEY_MODEL, True, None, "", False)
    defs = _defs(jm)
    assert _verify({"https://json-model.org/": 0}, KEY_MODEL, jm, defs) is True
    assert _verify({"https://json model.org/": 0}, KEY_MODEL, jm, defs) is False

def test_a_violation_under_a_union_is_kept_and_noted():
    """No structural oracle refuses the key here, so the validator is what settles it."""
    tests = vectors(KEY_MODEL)
    assert "# .$Key bad" in tests
    assert paired(tests, "# .$Key bad") == [False, "https://json model.org/"]

def test_the_violation_api_claims_nothing_no_oracle_proves():
    """Without a caller to check them back, unproven violations are left out."""
    assert ".$Key bad" not in violations(KEY_MODEL)

PROPAGATION_MODELS = [
    {"a": 0}, {"a": {"b": 0}}, ["$INT"], {"!a": "", "?b": 0},
    {"^": [{"a": 0}, {"b": ""}]}, {"|": [{"a": 0}, {"b": ""}]},
    {"&": [{"a": "$INT"}, {"a": "$INT", "?b": ""}]},
    {"$": {"g": {"a": 0}}, "^": ["$g", {"b": ""}]},
    {"?x": {"|": [{"c": 0}, {"d": ""}]}},
]

@pytest.mark.parametrize("model", PROPAGATION_MODELS)
def test_an_unbranched_type_violation_breaks_the_document(model):
    """Outside a union or xor, a mistyped fragment invalidates the whole document."""
    jm, compiled = _compile(model, False, None, "", False)
    vjm, vmodel = _compile(model, True, None, "", False)
    try:
        doc = simplest(compiled, jm, frozenset())
    except UnsupportedValue:
        doc = None
    for mpath, vpath, frames, props, disjunction in _sites(compiled, [], [], [], jm, frozenset()):
        if not mpath or set(props) - {"@"} or disjunction is not None:
            continue
        target = _ultimate(jm, props["@"])
        for candidate in _TYPE_VIOLATIONS:
            if not _mistyped(candidate, target):
                continue
            try:
                value = _document(copy.deepcopy(candidate), vpath, frames, doc,
                                  jm, frozenset())
            except UnsupportedValue:
                break
            assert _verify(value, vmodel, vjm) is False, (mpath, candidate, value)
            break

SHADOWED_PATTERN_MODELS = [{"/^a/": "$ANY", "/^ab/": ""}, {"/^a/": 0, "/^ab/": ""},
                           {"a": "$ANY", "/^a/": ""}]

@pytest.mark.parametrize("model", SHADOWED_PATTERN_MODELS)
def test_a_pattern_site_uses_a_name_no_other_key_claims(model):
    """A shadowed pattern must not yield a site under a name an earlier key owns."""
    jm, compiled = _compile(model, False, None, "", False)
    for mpath, vpath, frames, props, disjunction in _sites(compiled, [], [], [], jm, frozenset()):
        if not vpath or not isinstance(vpath[-1], str):
            continue
        prop = mpath[-1] if mpath else ""
        if not isinstance(prop, str) or not prop.startswith("/"):
            continue
        for other in _outranking(compiled, prop):
            assert _matches(vpath[-1], other) is not True, (prop, vpath, other)

def test_a_conjunction_does_not_branch():
    """An & alternative still has to hold, unlike a | or ^ one."""
    found = {}
    for op in ("&", "|", "^"):
        model = {op: [{"a": "$INT"}, {"a": "$INT", "?b": ""}]}
        jm, compiled = _compile(model, False, None, "", False)
        found[op] = [d for _, _, _, _, d in _sites(compiled, [], [], [], jm, frozenset())]
    assert all(d is None for d in found["&"])
    assert any(d is not None for d in found["|"])
    assert any(d is not None for d in found["^"])

def test_a_site_carries_the_outermost_disjunction():
    """A nested union is covered by failing every alternative of the outer one."""
    model = {"|": [{"a": {"|": ["$INT", "$U32"]}}, {"a": "$INT"}]}
    jm, compiled = _compile(model, False, None, "", False)
    found = [d for _, _, _, _, d in _sites(compiled, [], [], [], jm, frozenset())
             if d is not None]
    assert found and all(path == [] and set(node) == {"|"} and len(node["|"]) == 2
                         for path, node in found)

REJECTS_CASES = [
    ({"a": "$INT"}, ["a"], None, True), ({"a": "$INT"}, ["a"], 0, False),
    ({"!a": "$INT"}, ["a"], None, True), ({"?a": "$INT"}, ["a"], None, True),
    ({"a": {"b": "$INT"}}, ["a", "b"], None, True),
    ({"@": {"a": "$INT"}, ">=": 1}, ["a"], None, True),
    ({"": "$INT"}, ["a"], None, True), ({"/^a/": "$INT"}, ["a"], None, True),
    ({"$STRING": "$INT"}, ["a"], None, True), ({"$DATE": "$INT"}, ["a"], None, False),
    ({"b": "$ANY", "/^a/": "$INT"}, ["a"], None, True),
    ({"|": [{"a": "$INT"}, {"a": "$U32"}]}, ["a"], None, True),
    ({"|": [{"a": "$INT"}, {"a": "$NULL"}]}, ["a"], None, False),
    ({"^": [{"a": "$INT"}, {"a": "$STRING"}]}, ["a"], None, True),
    ({"&": [{"a": "$ANY"}, {"a": "$INT"}]}, ["a"], None, True),
    ({"&": [{"a": "$ANY"}, {"a": "$NULL"}]}, ["a"], None, False),
    ({"a": {"|": ["$INT", "$U32"]}}, ["a"], None, True),
    ({"a": {"^": ["$INT", "$U32"]}}, ["a"], None, True),
    ({"a": {"&": ["$ANY", "$INT"]}}, ["a"], None, True),
    ({"/^a/X": "$INT"}, ["a"], None, False), ({"$Ref": "$INT"}, ["a"], None, False),
    ({"|": []}, ["a"], None, False),
    (["$INT"], [0], None, True), (["$INT"], [7], None, True),
    (["$INT", "$STRING"], [1], None, True), (["$INT", "$STRING"], [2], None, True),
    ({"@": ["$INT", "$STRING"], ">=": 2}, [2], "", False),
    ({"@": ["$INT", "$STRING"], ">=": 2}, [2], None, True),
    ("$INT", [], None, True), ("$ANY", [], None, False), ("$INT", ["a"], None, False),
    ({"a": "$INT"}, ["b"], None, False), ({"a": "$INT"}, [0], None, False),
]

@pytest.mark.parametrize("model,path,value,expect", REJECTS_CASES)
def test_a_position_of_a_model_certainly_refuses_a_value(model, path, value, expect):
    """Keys resolve by precedence, operators combine, and anything else abstains."""
    jm, _ = _compile({"a": 0}, False, None, "", False)
    assert _rejects(jm, model, path, value, frozenset()) is expect

REFUSES_CASES = [
    ("$INT", None, True), ("$INT", 0, False), ("$ANY", None, False),
    ("$DATE", "1970-13-45", True), ("$DATE", "1970-01-01", False),
    ("$UUID", "abc", True), ("$Ref", None, False), ("$EMAIL", "not an address", False),
    ({"a": "$INT"}, {}, True), ({"a": "$INT"}, {"a": 0}, False),
    ({"?a": "$INT"}, {}, False), ({"!a": "$INT"}, {"b": 0}, True),
    ({"a": "$INT"}, {"a": 0, "x": 1}, True),
    ({"a": "$INT", "": "$ANY"}, {"a": 0, "x": 1}, False),
    ({"a": "$INT", "/^x/": ""}, {"a": 0, "x1": ""}, False),
    ({"a": "$INT", "/^x/X": ""}, {"a": 0, "y": 1}, False),
    ({"a": "$INT"}, [], True), ({"a": "$INT"}, 0, True),
    ({"a": {"b": "$INT"}}, {"a": {"b": None}}, True),
    ({"a": {"b": "$INT"}}, {"a": {"b": 0}}, False),
    ({"": "$INT"}, {"x": None}, True), ({"": "$INT"}, {"x": 0}, False),
    ("Susie", "abc", True), ("Susie", "Susie", False),
    ("_x", "y", True), ("_x", "x", False), ("_", "", False),
    ("=1", 2, True), ("=1", 1, False), ("=true", False, True), ("=null", None, False),
    ("/^a+$/", "b", True), ("/^a+$/", "aa", False), ("/^abc$/i", "ABC", False),
    ("/^a+$/X", "b", False), ("", "anything", False),
    ("$U64", -1, True), ("$U64", 0, False), ("$U32", -42, True),
    (0, -1, True), (0, 0, False), (1, 0, True), (1, 1, False),
    (0.0, -1.0, True), (1.0, 0.0, True), (1.0, 0.5, False), (-1, -42, False),
    (["$INT"], ["x"], True), (["$INT"], [0], False),
    (["$INT", "$STRING"], [0], True), (["$INT", "$STRING"], [0, ""], False),
    (["$INT", "$STRING"], [0, "", 1], True), ([], [], False), ([], [0], True),
]

@pytest.mark.parametrize("model,value,expect", REFUSES_CASES)
def test_a_model_certainly_refuses_a_value(model, value, expect):
    """The leaf also knows string formats, missing properties and unclaimed names."""
    jm, _ = _compile({"a": 0}, False, None, "", False)
    assert _refuses(jm, model, value) is expect

REJECTS_LEAF_CASES = [
    ({"@": "", ">=": 3}, [], "aa", True), ({"@": "", ">=": 3}, [], "aaa", False),
    ({"@": [0], "!": True}, [], [1, 1], True), ({"@": [0], "!": True}, [], [1, 2], False),
    ({"a": {"@": "$INT", ">=": 10}}, ["a"], 9, True),
    ({"|": [{"a": "$INT", "b": ""}, {"a": "$INT", "b": "$STRING"}]}, [], {"a": 0}, True),
    ({"|": [{"a": "$INT", "b": ""}, {"a": "$INT", "?b": ""}]}, [], {"a": 0}, False),
    ({"|": [{"a": "$INT"}, {"a": "$INT", "?c": ""}]}, [],
     {"a": 0, "no-such-prop": None}, True),
    ({"|": [{"a": "$INT"}, {"a": "$INT", "": "$ANY"}]}, [],
     {"a": 0, "no-such-prop": None}, False),
    ({"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 20}]}, [], 9, True),
    ({"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 5}]}, [], 9, False),
    ({"&": [{"@": "$INT", ">=": 10}, "$ANY"]}, [], 9, True),
]

@pytest.mark.parametrize("model,path,value,expect", REJECTS_LEAF_CASES)
def test_a_position_refuses_a_value_by_format_or_structure(model, path, value, expect):
    """Constraints and object structure now travel into every alternative."""
    jm, _ = _compile({"a": 0}, False, None, "", False)
    assert _rejects(jm, model, path, value) is expect

@pytest.mark.parametrize("model,expect", [
    ("$ANY", True), ({"@": "$ANY"}, True), ({"|": ["$ANY", "$INT"]}, True),
    ({"@": "$ANY", ">=": 1}, False), ({"^": ["$ANY", "$INT"]}, False),
    ({"&": ["$ANY"]}, False), ("$INT", False), ({"a": "$INT"}, False),
    ("$Ref", False), (["$ANY"], False),
])
def test_a_model_which_accepts_every_value_is_recognised(model, expect):
    """Only a certain yes, so a xor or a constraint keeps the answer negative."""
    jm, _ = _compile({"a": 0}, False, None, "", False)
    assert _anything(jm, model) is expect

def test_a_definition_of_anything_is_followed():
    jm, _ = _compile({"$": {"S": "$ANY"}, "@": "$S"}, False, None, "", False)
    assert _anything(jm, "$S") is True

def test_a_model_which_accepts_every_value_has_no_root_violation():
    """An empty conjunction is $ANY, so no root candidate can be claimed invalid."""
    assert not [t for t in vectors({"&": []})
                if isinstance(t, str) and "root invalid" in t]
    assert not [t for t in vectors({"|": ["$ANY", "$INT"]})
                if isinstance(t, str) and "root invalid" in t]

@pytest.mark.parametrize("model,label", [
    ({"|": [{"a": "$INT", "b": ""}, {"a": "$INT", "b": "$STRING"}]}, "# .'|'[0].b missing"),
    ({"|": [{"a": "$INT"}, {"a": "$INT", "?c": ""}]}, "# .'|'[0].no-such-prop extra"),
    ({"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 20}]}, "# .'|'[0].'>='"),
])
def test_a_structural_violation_every_alternative_refuses(model, label):
    """A required property, an unclaimed name or a broken bound, in every alternative."""
    assert label in vectors(model)

@pytest.mark.parametrize("model,label", [
    ({"|": [{"a": "$INT", "b": ""}, {"a": "$INT", "?b": ""}]},
     "# .'|'[0].b missing BAD"),
    ({"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 5}]}, "# .'|'[0].'>=' BAD PASS"),
])
def test_a_structural_violation_one_alternative_still_allows(model, label):
    """The other alternative makes it optional, holds the name, or allows the value."""
    assert label in vectors(model)

def test_a_reference_is_followed_into_its_definition():
    model = {"$": {"S": {"?a": "$S", "b": "$INT"}}, "@": "$S"}
    jm, _ = _compile(model, False, None, "", False)
    assert _rejects(jm, "$S", ["b"], None) is True
    assert _rejects(jm, "$S", ["a", "b"], None) is False

def _placed(doc, path, value):
    """Copy of a document with one position set to a value."""
    node = copy.deepcopy(doc)
    here = node
    for step in path[:-1]:
        here = here[step]
    here[path[-1]] = value
    return node

COMPILER_REJECTS = [
    ({"a": "$INT"}, {"a": 0}, ["a"], None),
    ({"": "$STRING"}, {"a": ""}, ["a"], None),
    ({"/^a/": "$STRING"}, {"a": ""}, ["a"], 0),
    ({"$STRING": "$INT"}, {"a": 0}, ["a"], ""),
    ({"a": "$INT", "/^b/": "$STRING"}, {"a": 0}, ["b1"], 0),
    ({"a": {"b": "$INT"}}, {"a": {"b": 0}}, ["a", "b"], None),
    ({"@": {"a": "$INT"}, ">=": 1}, {"a": 0}, ["a"], None),
    ({"&": [{"a": "$INT"}, {"?b": ""}]}, {"a": 0}, ["a"], None),
    (["$INT"], [0, 0], [1], ""),
    ({"a": ["$INT"]}, {"a": [0]}, ["a", 0], ""),
]

@pytest.mark.parametrize("model,doc,path,value", COMPILER_REJECTS)
def test_the_compiler_never_contradicts_the_position_oracle(model, doc, path, value):
    """Where the oracle rules a position out, the compiler must reject the document."""
    jm, compiled = _compile(copy.deepcopy(model), False, None, "", False)
    assert _rejects(jm, compiled, path, value) is True
    check = model_checker_from_json(copy.deepcopy(model))
    assert check(_placed(doc, path, value), "", None) is False

DISJUNCTION_MODELS = [ {"^": [{"a": "$INT"}, {"a": "$U32"}]},
                       {"^": [{"a": "$INT"}, {"a": "$STRING"}]},
                       {"^": [{"a": "$INT"}, {"a": "$NULL"}]},
                       {"^": [{"a": {"b": "$INT"}}, {"a": {"b": "$STRING"}}]},
                       {"|": [{"a": "$INT"}, "$STRING"]},
                       {"|": [{"a": "$INT"}, ["$INT"]]},
                       {"|": [["$INT"], ["$STRING"]]},
                       {"?x": {"^": [{"a": "$INT"}, {"a": "$U32"}]}} ]

@pytest.mark.parametrize("model", DISJUNCTION_MODELS)
def test_a_violation_rejected_by_every_alternative_breaks_the_document(model):
    """Matching no alternative of the outermost disjunction fails the document."""
    jm, compiled = _compile(model, False, None, "", False)
    vjm, vmodel = _compile(model, True, None, "", False)
    try:
        doc = simplest(compiled, jm, frozenset())
    except (UnsupportedValue, Vacuous):
        doc = None
    for mpath, vpath, frames, props, disjunction in _sites(compiled, [], [], [], jm,
                                                           frozenset()):
        if not mpath or set(props) - {"@"} or disjunction is None:
            continue
        target = _ultimate(jm, props["@"])
        for candidate in _justified(target):
            if not (_mistyped(candidate, target) and _rejects(
                    jm, disjunction[1], vpath[len(disjunction[0]):], candidate)):
                continue
            try:
                value = _document(copy.deepcopy(candidate), vpath, frames, doc,
                                  jm, frozenset())
            except UnsupportedValue:
                continue
            assert _verify(value, vmodel, vjm) is False, (mpath, candidate, value)

@pytest.mark.parametrize("model,label", [
    ({"|": [{"a": "$INT"}, {"a": "$U32"}]}, "# .'|'[0].a invalid"),
    ({"|": [{"a": "$INT"}, {"a": "$STRING"}]}, "# .'|'[0].a invalid"),
    ({"^": [{"a": "$INT"}, {"a": "$U32"}]}, "# .'^'[0].a invalid"),
    ({"|": [{"a": {"|": ["$INT", "$U32"]}}, {"a": "$INT"}]}, "# .'|'[0].a invalid"),
])
def test_a_union_every_alternative_refuses_needs_no_compiler(model, label):
    """The nested union is covered by the outermost one, which no alternative accepts."""
    assert label in vectors(model)

@pytest.mark.parametrize("model", [{"|": [{"a": "$INT"}, {"b": "$INT"}]},
                                   {"|": [{"a": "$INT"}, ["$INT"]]},
                                   {"|": [{"a": "$INT"}, {"b": "$INT", "?a": "$ANY"}]}])
def test_an_alternative_which_refuses_the_whole_document_decides(model):
    """The other alternative says nothing about that position, yet refuses the document."""
    assert "# .'|'[0].a invalid" in vectors(model)

@pytest.mark.parametrize("model,label", [
    ({"|": [{"a": "$INT"}, {"": "$STRING"}]}, "# .'|'[0].a invalid"),
    ({"|": [{"a": "$INT"}, {"/^a/": "$STRING"}]}, "# .'|'[0].a invalid"),
    ({"|": [{"a": "$INT"}, {"$STRING": "$U32"}]}, "# .'|'[0].a invalid"),
    ({"|": [{"a": {"b": "$INT"}}, {"a": {"|": [{"b": "$U32"}, {"b": "$STRING"}]}}]},
     "# .'|'[0].a.b invalid"),
])
def test_a_key_which_is_not_a_literal_still_decides_the_position(model, label):
    """A catch-all, a pattern, a predef key or a nested union no longer blocks the proof."""
    assert label in vectors(model)

def test_alternatives_which_disagree_are_proven_by_the_candidate():
    """$INT and $STRING disagree, yet neither accepts the null the generator picks."""
    tests = vectors({"|": [{"a": "$INT"}, {"a": "$STRING"}]})
    assert "# .'|'[0].a invalid" in tests and [False, {"a": None}] in tests

@pytest.mark.parametrize("model", PROPAGATION_MODELS)
def test_every_unmarked_vector_survives_the_compiler(model):
    """Whatever the generator leaves unmarked was decided here, so it must be right."""
    check = model_checker_from_json(model)
    label = None
    for entry in vectors(model):
        if isinstance(entry, str):
            label = entry
            continue
        if label and label.endswith(" BAD"):
            continue
        expect, value = entry
        assert check(value, "", None) is expect, (label, entry)

@pytest.mark.parametrize("target", sorted(set(_PREDEF_NAMES) & set(_PREDEF_VIOLATIONS)))
def test_the_hand_written_violation_is_rejected_by_its_predef(target):
    """The table says the value is bad, and the checkers must say so too."""
    assert _rejected(target, _PREDEF_VIOLATIONS[target]) is True

@pytest.mark.parametrize("target", ["$EMAIL", "$URL", "$URI", "$HOST", "$U32"])
def test_a_predef_without_a_checker_stays_undecided(target):
    assert _rejected(target, _PREDEF_VIOLATIONS[target]) is False

@pytest.mark.parametrize("target", sorted(set(_PREDEF_NAMES) & set(_PREDEF_VIOLATIONS)))
def test_a_rejected_violation_breaks_the_model(target):
    """Where the checker rules the value out, the compiler must reject it too."""
    check = model_checker_from_json(target)
    assert check(_PREDEF_VIOLATIONS[target], "", None) is False
    assert check(_PREDEFS[target], "", None) is True

@pytest.mark.parametrize("value,expect", [
    (0, 0), (-42, -42), (3.14159, 3.14159), ("", 0), ("abc", 3), ([], 0), ([1, 2], 2),
    ({}, 0), ({"a": 0, "b": 1}, 2), (True, None), (False, None), (None, None),
])
def test_a_constraint_measures_a_number_or_a_length(value, expect):
    assert _measured(value) == expect

@pytest.mark.parametrize("op,bound,value,expect", [
    (">=", 10, 9, True), (">=", 10, 10, False), (">", 10, 10, True),
    ("<=", 3, 4, True), ("<=", 3, 3, False), ("<", 3, 3, True), ("<", 3, 2, False),
    ("=", 2, 3, True), ("=", 2, 2, False), ("!=", 2, 2, True), ("!=", 2, 3, False),
    (">=", 10, 3.0, True), ("<=", 2.5, 3, True), ("<=", 2.5, 2, False),
    (">=", 3, "aa", True), (">=", 3, "aaa", False), ("<=", 2, "abc", True),
    (">=", 2, [0], True), ("<=", 1, [0, 1], True), (">=", 2, [0, 1], False),
    (">=", 2, {"a": 0}, True), ("<=", 2, {"a": 0, "b": 1}, False),
    ("!", True, [0, 0], True), ("!", True, [0, 1], False), ("!", True, [[1], [1]], True),
    ("!", True, "aa", False), ("!", False, [0, 0], False),
    (">=", 10, True, False), (">=", 10, None, False), (">=", True, 0, False),
    ("<=", "$INT", "abc", True), ("?", 1, 0, False),
    (">=", "abc", "aaa", True), (">=", "abc", "abc", False), ("<=", "abc", "zzz", True),
    ("=", "abc", "abc", False), ("=", "abc", "abd", True), ("!=", "abc", "abc", True),
    (">=", "abc", 5, True), (">=", "abc", None, True),
])
def test_a_broken_constraint_is_decided_without_the_compiler(op, bound, value, expect):
    assert _breaks(op, bound, value) is expect

BREAK_MODELS = [ {"@": "$INT", ">=": 10}, {"@": 0, "<=": 3}, {"@": 0, "=": 2},
                 {"@": 0, "!=": 2}, {"@": "", ">=": 3}, {"@": "", "<=": 2},
                 {"@": [0], ">=": 2}, {"@": [0], "!": True, ">=": 4},
                 {"@": {"": "$ANY"}, ">=": 2, "<=": 3}, {"@": -1, "<=": 3.5},
                 {"!a": {"@": "", ">=": 3}, "!b": 0},
                 {"|": [{"@": "$INT", ">=": 10}, "$STRING"]} ]

@pytest.mark.parametrize("model", BREAK_MODELS)
def test_the_constraint_oracle_never_contradicts_the_compiler(model):
    """Where the oracle rules a value out, the constrained model must reject it."""
    jm, compiled = _compile(model, False, None, "", False)
    defs = _defs(jm)
    for mpath, vpath, frames, props, disjunction in _sites(compiled, [], [], [], jm, frozenset()):
        if not set(props) - {"@"}:
            continue
        try:
            subs = _violations_constrained(props, jm, frozenset())
        except UnsupportedValue:
            continue
        for op, sub in subs.items():
            if _breaks(op, props[op], sub):
                assert _verify(sub, props, jm, defs) is False, (mpath, op, sub)

@pytest.mark.parametrize("model", [{"|": [{"@": "$INT", ">=": 10}, "$INT"]},
                                   {"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 5}]}])
def test_a_constraint_under_a_union_is_noted(model):
    """The other alternative accepts the value, so the validator contradicts the vector."""
    assert "# .'|'[0].'>=' BAD PASS" in vectors(model)

def test_a_constraint_broken_in_a_union_branch_can_stay_valid():
    """The second alternative accepts 9, which is why the branched site is marked."""
    assert model_checker_from_json({"|": [{"@": "$INT", ">=": 10}, "$INT"]})(9, "", None) is True

def test_a_predef_key_outranks_patterns_and_the_catch_all():
    assert _outranking({"$DATE": 0, "": ""}, "") == ["$DATE"]
    assert _outranking({"a": 0, "$DATE": 1, "/^x/": 2}, "/^x/") == ["a", "$DATE"]

@pytest.mark.parametrize("name", ["x", "#note", "# abc"])
def test_a_comment_key_declares_no_property(name):
    """The preprocessor drops it, so a value carrying that name is rejected."""
    assert _matches(name, "# abc") is False

def test_a_comment_key_is_dropped_by_the_compiler():
    check = model_checker_from_json({"# abc": 1, "b": ""})
    assert check({"b": "x"}, "", None) is True
    assert check({"b": "x", "# abc": 1}, "", None) is False

@pytest.mark.parametrize("node,prop,expect", [
    ({"/^a/": 0, "/^ab/": ""}, "/^ab/", ["/^a/"]),
    ({"/^a/": 0, "/^ab/": ""}, "/^a/", []),
    ({"": "$ANY", "/^a/": 0}, "", ["/^a/"]),
    ({"a": 0, "/^a/": ""}, "/^a/", ["a"]),
    ({"!a": 0, "?b": 1, "/^x/": ""}, "/^x/", ["!a", "?b"]),
    ({"#c": 1, "/^a/": 0}, "/^a/", []),
    ({"a": 0}, "a", []),
])
def test_a_key_is_outranked_by_names_and_earlier_patterns(node, prop, expect):
    assert _outranking(node, prop) == expect

def test_a_catch_all_tries_further_letters_when_outranked():
    """Every name starting with 'a' belongs to the pattern, so fall back on 'b'."""
    node = {"/^a/": True, "": 1}
    assert _names("", 1, set(), _outranking(node, "")) == ["b"]
    check = model_checker_from_json(node)
    assert check({"b": 1}, "", None) is True

def test_a_catch_all_keeps_its_first_letter_when_free():
    assert _names("", 2, set(), []) == ["a", "aa"]

def test_a_shadowed_pattern_yields_no_name():
    """Every name matching /^ab/ also matches the earlier /^a/, so none is free."""
    node = {"/^a/": 0, "/^ab/": ""}
    assert _names("/^ab/", 1, set(), _outranking(node, "/^ab/")) == []
    assert _names("/^a/", 1, set(), _outranking(node, "/^a/")) == ["a"]

OVERLAP_MODELS = [{"/^a/": 0, "/^ab/": ""}, {"/^ab/": "", "/^a/": 0},
                  {"": "$ANY", "/^a/": 0}, {"a": 0, "/^a/": ""}, {"!a": 0, "/^a/": ""}]

@pytest.mark.parametrize("model", OVERLAP_MODELS)
def test_a_generated_name_belongs_to_its_own_key(model):
    """Overlapping keys resolve by precedence, so the compiler must accept each value."""
    check = model_checker_from_json(model)
    for key, value in optionals(model)[0].items():
        assert check(value, "", None) is True, (key, value)

@pytest.mark.parametrize("key,name", [("_#foo", "#foo"), ("_!x", "!x"), ("_?y", "?y")])
def test_an_escaped_key_declares_the_stripped_name(key, name):
    """The oracle and the compiler must agree on which name the key declares."""
    assert _matches(name, key) is True and _matches(key, key) is False
    check = model_checker_from_json({key: 0})
    assert check({name: 1}, "", None) is True
    assert check({key: 1}, "", None) is False

@pytest.mark.parametrize("key", ["$ANY", "$STRING"])
def test_an_unconstrained_key_matches_every_name(key):
    assert _matches("anything", key) is True

@pytest.mark.parametrize("key", ["foo", "!foo", "?foo", "_foo"])
def test_a_literal_key_matches_its_own_name(key):
    assert _matches("foo", key) is True
    assert _matches("bar", key) is False

def test_a_literal_key_compares_the_stripped_name():
    assert _matches("!foo", "!foo") is False

@pytest.mark.parametrize("target,name,expect", [
    ("/^x/", "xa", True), ("/^x/", "ya", False),
    ("Susie", "Susie", True), ("Susie", "other", False),
    ("", "anything", True), ("$STRING", "anything", True),
    ("$DATE", "1970-01-01", True), ("$DATE", "2023-02-29", False),
    ("$URL", "https://json-model.org/", None),
    ({"@": "", ">=": 3}, "abcd", None),
])
def test_a_reference_key_resolves_to_its_string_definition(target, name, expect):
    """A key naming a definition decides like the string model behind it."""
    jm, model = _compile({"$": {"Name": target}, "@": {"$Name": 0}}, False, None, "", False)
    assert _matches(name, "$Name") is None
    assert _matches(name, "$Name", jm) is expect
    if expect is not None:
        assert _verify({name: 0}, model, jm) is expect

def test_a_reference_key_stops_at_a_chain_which_leads_nowhere():
    jm, _ = _compile({"$": {"Name": "$Other", "Other": "/^x/"}, "@": {"$Name": 0}},
                     False, None, "", False)
    assert _matches("xa", "$Name", jm) is True
    assert _matches("xa", "$Nope", jm) is None

OPTIMIZED_PATTERNS = {
    "/.*$/": ["", "x", "abc"], "/^.*/": ["", "x", "abc"], "/.+/s": ["", "x"],
    "/^.{3}$/s": ["", "ab", "abc", "abcd"], "/^.{2,}$/s": ["a", "ab", "abcd"],
    "/^.{0,4}$/s": ["", "abcd", "abcde"], "/^.{2,4}$/s": ["a", "ab", "abcd", "abcde"],
    "/^abc/": ["abc", "abcd", "xabc", "ab"], "/abc$/": ["abc", "xabc", "abcd"],
    "/^abc$/": ["abc", "abcd", "xabc"], "/^a\\.b/": ["a.b", "axb", "a.bc"],
    "/^ab|cd$/": ["ab", "cd", "xy"], "/^[a-c]+$/": ["abc", "abd", ""],
}

@pytest.mark.parametrize("pattern", sorted(OPTIMIZED_PATTERNS))
def test_the_name_oracle_agrees_with_the_compiler(pattern):
    """Each shape the compiler rewrites into a non-regex operation."""
    jm, model = _compile(pattern, False, None, "", False)
    for name in OPTIMIZED_PATTERNS[pattern]:
        assert _matches(name, pattern) == _verify(name, model, jm), (pattern, name)

def test_a_pattern_property_is_entered():
    assert extras({"/^x-/": {"a": 0}}) == {
        '.no-such-prop extra': {"no-such-prop": None},
        './^x-/.no-such-prop extra': {"x-": {"a": 0, "no-such-prop": None}}}

def test_a_pattern_property_name_avoids_a_named_property():
    assert extras({"a": 0, "/^a/": {"b": 0}}) == {
        '.no-such-prop extra': {"a": 0, "no-such-prop": None},
        './^a/.no-such-prop extra': {"a": 0, "a0": {"b": 0, "no-such-prop": None}}}

def test_a_pattern_property_the_sampler_cannot_handle_is_skipped():
    assert extras({"?p": {"/[^a]/": {"b": 0}}}) == {'.no-such-prop extra': {"no-such-prop": None}}

def _imported_model(tmp_path):
    """Write a model importing definitions from another file, return its path."""
    lib = tmp_path / "lib.model.json"
    lib.write_text(json.dumps({"$": {"Name": {"first": "", "last": ""}}, "@": "$Name"}))
    main = tmp_path / "main.model.json"
    main.write_text(json.dumps({"$": {"lib": "$" + str(lib)},
                                "@": {"who": "$lib#Name", "n": 0}}))
    return str(main)

def test_a_definition_imported_from_another_file_is_violated(tmp_path):
    path = _imported_model(tmp_path)
    model = json.loads(open(path).read())
    check = model_checker_from_json(model, resolver=Resolver())
    found = violations(model, url=path)
    assert set(below_root(found)) == {'.@ invalid', '.@.n invalid', '.@.who missing',
                                      '.@.n missing', '.@.no-such-prop extra'}
    for pointer, value in found.items():
        assert not check(value, "", None), pointer

def extras(model):
    """Violations which add a property the model does not define."""
    return {p: v for p, v in violations(model).items() if p.endswith(" extra")}

EXTRA_MODELS = [ {"a": 0}, {"!a": 0, "!b": ""}, {"?a": ""}, {"a": {"b": 0}},
                 {"a": 0, "": "$NONE"}, {"a": 0, "/^e/": 0},
                 {"|": [{"!a": 0}, ""]}, [{"a": 0}, {"b": 0}],
                 {"$": {"S": ""}, "!a": "$S"}, {"@": {"!a": 0}, ">=": 1} ]

@pytest.mark.parametrize("model", EXTRA_MODELS)
def test_each_extra_property_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in extras(model).values():
        assert not check(value, "", None)

def test_an_extra_property_is_checked_at_every_object_level():
    assert extras({"a": {"b": {"c": 0}}}) == {
        '.no-such-prop extra': {"a": {"b": {"c": 0}}, "no-such-prop": None},
        '.a.no-such-prop extra': {"a": {"b": {"c": 0}, "no-such-prop": None}},
        '.a.b.no-such-prop extra': {"a": {"b": {"c": 0, "no-such-prop": None}}}}

def test_an_open_object_has_no_extra_property_violation():
    assert extras({"a": 0, "": 0}) == {}

def test_an_explicitly_closed_object_has_an_extra_property_violation():
    assert extras({"a": 0, "": "$NONE"}) == {'.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_an_extra_property_avoids_a_pattern_property_name():
    assert extras({"a": 0, "/^no-such-prop$/": 0}) == {
        '.no-such-property extra': {"a": 0, "no-such-property": None}}

def test_a_reference_property_behaves_like_a_pattern():
    assert extras({"$": {"S": "/^s/"}, "a": 0, "$S": 0}) == {
        '.no-such-prop extra': {"a": 0, "no-such-prop": None}}

def test_an_extra_property_grows_an_optional_object():
    assert extras({"?a": {"!x": 0}}) == {
        '.no-such-prop extra': {"no-such-prop": None},
        '.?a.no-such-prop extra': {"a": {"x": 0, "no-such-prop": None}}}

def test_an_extra_property_in_each_tuple_item():
    assert extras([{"a": 0}, {"b": 0}]) == {
        '.[0].no-such-prop extra': [{"a": 0, "no-such-prop": None}, {"b": 0}],
        '.[1].no-such-prop extra': [{"a": 0}, {"b": 0, "no-such-prop": None}]}

def test_an_open_object_nested_in_a_closed_one_is_skipped():
    assert extras({"a": {"b": 0, "": "$ANY"}}) == {
        '.no-such-prop extra': {"a": {"b": 0}, "no-such-prop": None}}

UNCLAIMED_MODELS = [ {"a": 0}, {}, {"!a": 0, "?b": ""}, {"a": 0, "/^x-/": ""},
                     {"a": 0, "$DATE": 0}, {"# note": 1, "a": 0}, {"_!a": 0},
                     {"a": 0, "": "$ANY"}, {"$STRING": 0}, {"/^no/": 0} ]

UNCLAIMED_NAMES = _EXTRA_NAMES + ["a", "b", "x-1", "1970-01-01", "no", "!a", ""]

@pytest.mark.parametrize("node", UNCLAIMED_MODELS)
def test_the_extra_name_oracle_never_contradicts_the_compiler(node):
    """Where no key can hold a name, adding it must break the object model."""
    check = model_checker_from_json(node)
    built = simplest(node)
    for name in UNCLAIMED_NAMES:
        if name in built or not _unclaimed(node, name):
            continue
        assert check({**built, name: None}, "", None) is False, (node, name)

@pytest.mark.parametrize("node", [{"a": 0, "": "$ANY"}, {"a": 0, "": "$NONE"},
                                  {"$STRING": 0}, {"$ANY": 0}, {"/^no/": 0},
                                  {"$Ref": 0}, {"/^no/X": 0}])
def test_a_key_which_may_hold_the_name_defeats_the_proof(node):
    """A catch-all, a string predef, a matching pattern, or an undecided key."""
    assert _unclaimed(node, "no-such-prop") is False

def test_an_unclaimed_extra_property_needs_no_compiler():
    """No key can hold the name and the site is not branched, so the claim holds."""
    assert unrooted(vectors({"?a": 0})) == [
        "# . simplest", [True, {}], "# .?a present BAD", [None, {"a": 0}],
        "# .?a invalid", [False, {"a": None}],
        "# .no-such-prop extra", [False, {"no-such-prop": None}]]

TYPE_MODELS = [ 0, None, True, "", "$DATE", "$UUID", "_abc", "/^a+$/", "=3",
                {"!a": 0, "!b": ""}, ["", 0], {"!a": {"!b": 0}}, [""],
                {"$": {"S": ""}, "!a": "$S"}, {"|": [0, ""]}, {"^": [0, ""]},
                {"!a": {"|": [0, ""]}}, {"?a": {"@": "", ">=": 3}},
                {"@": "", ">=": 3}, {"@": {"": "$ANY"}, ">=": 2}, {"!a": "$INT"} ]

@pytest.mark.parametrize("model", TYPE_MODELS)
def test_each_type_violation_is_rejected_by_its_model(model):
    check = model_checker_from_json(model)
    for value in violations(model).values():
        assert not check(value, "", None)

def test_a_maximum_bound_is_the_largest_accepted_number():
    assert bounds({"@": 0, "<=": 3}) == {".'<='": 3}

def test_a_minimum_bound_is_the_smallest_accepted_number():
    assert bounds({"@": 0, ">=": 3}) == {".'>='": 3}

def test_a_strict_maximum_bound_stops_one_before():
    assert bounds({"@": 0, "<": 3}) == {".'<'": 2}

def test_a_strict_minimum_bound_starts_one_after():
    assert bounds({"@": 0, ">": 3}) == {".'>'": 4}

def test_an_exact_bound_is_the_value_itself():
    assert bounds({"@": 0, "=": 2}) == {".'='": 2}

def test_a_forbidden_number_bound_is_its_neighbour():
    assert bounds({"@": 0, "!=": 2}) == {".'!='": 3}

def test_a_forbidden_number_bound_moves_down_when_blocked():
    assert bounds({"@": 0, "!=": 2, "<=": 2}) == {".'!='": 1}

def test_each_of_two_bounds_is_reached_separately():
    assert bounds({"@": 0, ">=": 2, "<=": 4}) == {".'>='": 2, ".'<='": 4}

def test_a_fractional_bound_on_an_int_model_snaps_inwards():
    assert bounds({"@": -1, "<=": 3.5}) == {".'<='": 3}

def test_a_float_bound_keeps_the_bound_value():
    v = bounds({"@": 0.0, ">=": 1.5})
    assert v == {".'>='": 1.5} and type(v[".'>='"]) is float

def test_a_strict_float_bound_has_no_exact_value():
    with pytest.raises(UnsupportedValue, match="no constraint bound"):
        bounds({"@": 0.0, ">": 1.5})

def test_a_maximum_string_length_bound():
    assert bounds({"@": "", "<=": 2}) == {".'<='": "aa"}

def test_a_minimum_string_length_bound():
    assert bounds({"@": "", ">=": 3}) == {".'>='": "aaa"}

def test_a_float_length_bound_snaps_to_an_integer_length():
    assert bounds({"@": "", "<=": 3.14159}) == {".'<='": "aaa"}

def test_an_array_length_bound():
    assert bounds({"@": [0], "<=": 2}) == {".'<='": [0, 0]}

def test_a_unique_array_length_bound_keeps_distinct_items():
    assert bounds({"@": [0], ">=": 2, "!": True}) == {".'>='": [0, 1]}

def test_an_object_size_bound_grows_to_each_limit():
    assert bounds({"@": {"": "$ANY"}, ">=": 2, "<=": 3}) == {
        ".'>='": {"a": {}, "aa": {}}, ".'<='": {"a": {}, "aa": {}, "aaa": {}}}

def test_a_predefined_string_target_has_a_bound():
    assert bounds({"@": "$STRING", "<=": 3}) == {".'<='": "aaa"}

def test_a_unique_constraint_has_no_bound():
    with pytest.raises(UnsupportedValue, match="no constraint bound"):
        bounds({"@": [0], "!": True})

def test_a_model_without_a_constraint_has_no_bound():
    with pytest.raises(UnsupportedValue, match="no constraint in model"):
        bounds({"!a": 0})

def test_a_string_comparison_bound_is_refused():
    with pytest.raises(UnsupportedValue, match="unsupported comparison constraint"):
        bounds({"@": "", ">=": "$INT"})

def test_a_bound_inside_a_property():
    assert bounds({"!a": {"@": "", ">=": 3}, "!b": 0}) == {".!a.'>='": {"a": "aaa", "b": 0}}

def test_a_bound_inside_an_optional_property():
    assert bounds({"?a": {"@": "", "<=": 2}}) == {".?a.'<='": {"a": "aa"}}

def test_a_bound_inside_a_tuple():
    assert bounds(["", {"@": [0], ">=": 2}]) == {".[1].'>='": ["", [0, 0]]}

def test_a_bound_in_a_definition():
    assert bounds({"$": {"S": {"@": "", ">=": 3}}, "!a": "$S"}) == {".$S.'>='": {"a": "aaa"}}

def test_a_bound_in_a_union_branch():
    assert bounds({"|": [0, {"@": "", ">=": 3}]}) == {".'|'[1].'>='": "aaa"}

def test_a_bound_broken_by_the_whole_document_is_marked():
    """No oracle relates the two branches, so the bound is kept for the validator."""
    marks: set[str] = set()
    found = bounds({"^": [{"@": 0, "<=": 5}, {"@": 0, ">=": 5, "<=": 9}]}, marks=marks)
    assert set(found) == marks

BOUND_MODELS = [ {"@": 0, "<=": 3}, {"@": 0, ">=": 3}, {"@": 0, "<": 3}, {"@": 0, ">": 3},
                 {"@": 0, "=": 2}, {"@": 0, "!=": 2}, {"@": 0, "!=": 2, "<=": 2},
                 {"@": 0, ">=": 2, "<=": 4}, {"@": -1, "<=": 3.5}, {"@": 0.0, ">=": 1.5},
                 {"@": 0.0, "<=": 2.0}, {"@": "", "<=": 2}, {"@": "", ">=": 3},
                 {"@": "", "<=": 3.14159}, {"@": [0], "<=": 2}, {"@": [0], ">=": 2, "!": True},
                 {"@": {"": "$ANY"}, ">=": 2, "<=": 3}, {"@": "$STRING", "<=": 3},
                 {"@": "$U32", ">=": 3}, {"!a": {"@": "", ">=": 3}, "!b": 0},
                 {"$": {"S": {"@": "", ">=": 3}}, "!a": "$S"},
                 {"|": [0, {"@": "", ">=": 3}]}, {"?a": {"@": "", "<=": 2}},
                 ["", {"@": [0], ">=": 2}] ]

@pytest.mark.parametrize("model", BOUND_MODELS)
def test_each_bound_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    for value in bounds(json.loads(json.dumps(model))).values():
        assert check(value, "", None) is True

@pytest.mark.parametrize("model", BOUND_MODELS)
def test_a_bound_and_its_violation_fall_on_either_side(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    broken = violations(json.loads(json.dumps(model)))
    for pointer, value in bounds(json.loads(json.dumps(model))).items():
        if pointer in broken:
            assert check(value, "", None) is True, pointer
            assert check(broken[pointer], "", None) is False, pointer

def test_vectors_pair_a_valid_value_with_each_violation():
    assert unrooted(vectors({"!a": 0})) == [
        "# . simplest", [True, {"a": 0}],
        '# .!a invalid', [False, {"a": None}], '# .!a missing', [False, {}],
        '# .no-such-prop extra', [False, {"a": 0, "no-such-prop": None}]]

def test_vectors_put_each_bound_before_the_violations():
    assert unrooted(vectors({"@": 0, "<=": 3})) == [
        "# . simplest", [True, 0], "# .'<=' bound", [True, 3], "# .'<='", [False, 4],
        '# .@ invalid', [False, None]]

def test_vectors_skip_a_bound_equal_to_the_valid_value():
    assert unrooted(vectors({"@": "", ">=": 3})) == [
        "# . simplest", [True, "aaa"],
        "# .'abc' root SKIPPED: valid for the model",
        "# .'>='", [False, "aa"], '# .@ invalid', [False, None]]

def test_vectors_without_a_violation_keep_the_valid_value():
    """Nothing can break $ANY, and the file says so instead of staying quiet."""
    assert vectors("$ANY") == [
        "# . simplest", [True, {}],
        "# violation values SKIPPED: every value matches the model: '$ANY'"]

def test_vectors_without_a_valid_value_keep_the_violations():
    tests = vectors("$NONE")
    assert tests[tests.index([False, None]) - 1] == "# . root invalid"
    assert all(entry[0] is False for entry in tests if isinstance(entry, list))

def test_vectors_are_refused_for_an_invalid_model():
    with pytest.raises(UnsupportedValue, match="unsupported model"):
        vectors(False)

VECTOR_MODELS = [ {"!a": 0}, {"!a": {"@": "", ">=": 3}, "!b": 0}, ["", 0],
                  {"|": [0, {"@": "", ">=": 3}]}, {"$": {"S": {"@": "", ">=": 2}}, "!a": "$S"},
                  {"?a": {"!x": 0}}, "$DATE", {"@": [0], "!": True, ">=": 4},
                  {"@": 0, ">=": 2, "<=": 4},
                  {"@": {"": "$ANY"}, ">=": 2, "<=": 3} ]

@pytest.mark.parametrize("model", VECTOR_MODELS)
def test_each_vector_matches_its_expectation(model):
    check = model_checker_from_json(model)
    for entry in vectors(model):
        if isinstance(entry, str):
            continue
        expect, value = entry
        assert check(value, "", None) is expect, entry

def test_cli_generates_test_vectors(tmp_path, capsys):
    assert jmc_script(["--auto-values", _model_file(tmp_path, {"!a": 0})]) == 0
    out = json.loads(capsys.readouterr().out)
    assert out[0].startswith("# generated from") and unrooted(out[1:]) == [
        "# . simplest", [True, {"a": 0}],
        '# .!a invalid', [False, {"a": None}], '# .!a missing', [False, {}],
        '# .no-such-prop extra', [False, {"a": 0, "no-such-prop": None}]]

def test_cli_generates_a_bound_vector(tmp_path, capsys):
    assert jmc_script(["--auto-values", _model_file(tmp_path, {"@": 0, "<=": 3})]) == 0
    out = json.loads(capsys.readouterr().out)
    assert out[0].startswith("# generated from") and unrooted(out[1:]) == [
        "# . simplest", [True, 0], "# .'<=' bound", [True, 3], "# .'<='", [False, 4],
        '# .@ invalid', [False, None]]

def test_cli_reports_a_model_with_no_vector(tmp_path, capsys):
    assert jmc_script(["--auto-values", _model_file(tmp_path, False)]) == 0
    out = json.loads(capsys.readouterr().out)
    assert len(out) == 1 and out[0].startswith("# generated from")
    assert "no test vector" in out[0]

def test_each_optional_property_is_added_on_its_own():
    assert optionals({"a": True, "?b": 0, "?c": 1})[0] == {
        '.?b present': {"a": False, "b": 0},
        '.?c present': {"a": False, "c": 1}}

def test_an_optional_property_is_reached_two_levels_down():
    assert optionals({"a": True, "?b": {"?c": 0}})[0] == {
        '.?b present': {"a": False, "b": {}},
        '.?b.?c present': {"a": False, "b": {"c": 0}}}

def test_a_catch_all_property_gets_a_free_name():
    assert optionals({"a": True, "": 0})[0] == {".'' present": {"a": False, "aa": 0}}

def test_a_pattern_property_is_added():
    assert optionals({"a": True, "/^x/": ""})[0] == {
        './^x/ present': {"a": False, "x": ""}}

def test_a_reference_property_is_added():
    assert optionals({"$": {"K": "/^k/"}, "@": {"a": True, "$K": 0}})[0] == {
        '.$K present': {"a": False, "k": 0}}

def test_an_optional_property_of_a_union_branch_is_added():
    assert optionals({"|": [{"a": 0, "?b": 0}, {"c": True, "?d": ""}]})[0] == {
        ".'|'[0].?b present": {"a": 0, "b": 0},
        ".'|'[1].?d present": {"c": False, "d": ""}}

def test_a_property_which_must_be_absent_is_not_a_failure():
    with pytest.raises(Vacuous, match="no optional property"):
        optionals({"a": True, "?b": "$NONE"})

def test_an_optional_property_a_size_constraint_forbids_is_dropped():
    with pytest.raises(Vacuous, match="no optional property"):
        optionals({"@": {"a": True, "?b": 0}, "<=": 1})

def test_a_mandatory_only_object_has_no_optional_property():
    with pytest.raises(Vacuous, match="no optional property"):
        optionals({"!a": 0})

def test_an_optional_property_which_breaks_an_xor_is_marked():
    """No oracle rules the added property out, so it is kept for the validator."""
    marks: set[str] = set()
    values, *_ = optionals({"^": [{"a": 0, "?b": 0}, {"b": 0, "?a": 0}]}, marks=marks)
    assert values == {".'^'[0].?b present": {"a": 0, "b": 0}}
    assert marks == {".'^'[0].?b present"}

def test_an_optional_property_is_kept_beside_the_document_mandatory_ones():
    model = {"$": {"O": {"|": [{"?i": 0, "": "$ANY"}, {"t": "_s", "": "$ANY"}]}},
             "@": {"&": [{"s": "", "": "$ANY"}, "$O"]}}
    assert optionals(json.loads(json.dumps(model)))[0][".$O.'|'[0].?i present"] \
        == {"s": "", "i": 0}

def test_each_union_alternative_gives_a_value():
    assert branches({"|": ["Calvin", "Susie", "Hobbes"]})[0] == {
        ".'|'[1] branch": "Susie", ".'|'[2] branch": "Hobbes"}

def test_a_union_alternative_is_reached_inside_a_property():
    assert branches({"a": {"|": ["_x", "_y"]}})[0] == {".a.'|'[1] branch": {"a": "y"}}

def test_an_empty_object_model_holds_no_union():
    with pytest.raises(Vacuous, match="no union alternative"):
        branches({})

def test_a_scalar_model_holds_no_union():
    with pytest.raises(Vacuous, match="no union alternative"):
        branches(True)

def test_a_null_alternative_is_a_value_of_its_own():
    assert branches({"|": ["=200", None, "=3.14159"]})[0] == {
        ".'|'[1] branch": None, ".'|'[2] branch": 3.14159}

def test_a_null_optional_property_is_added():
    assert optionals({"a": True, "?b": None})[0] == {
        '.?b present': {"a": False, "b": None}}

def test_a_commented_union_alternative_is_skipped():
    assert branches({"|": ["_a", "#comment", "_b"]})[0] == {".'|'[1] branch": "b"}

VALID_MODELS = [ {"a": True, "?b": 0, "?c": 1}, {"a": True, "?b": {"?c": 0}},
                 {"a": True, "": 0}, {"a": True, "/^x/": ""},
                 {"$": {"K": "/^k/"}, "@": {"a": True, "$K": 0}},
                 {"|": [{"a": 0, "?b": 0}, {"c": True, "?d": ""}]},
                 {"?a": {"?b": 0}}, [{"?a": 0, "b": 1}],
                 {"|": ["Calvin", "Susie", "Hobbes"]}, {"a": {"|": ["_x", "_y"]}},
                 {"|": [0, "", [0]]}, {"@": {"a": True, "?b": 0}, ">=": 1} ]

@pytest.mark.parametrize("model", VALID_MODELS)
def test_each_optional_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    try:
        found, *_ = optionals(json.loads(json.dumps(model)))
    except Vacuous:
        found = {}
    for key, value in found.items():
        assert check(value, "", None) is True, key

@pytest.mark.parametrize("model", VALID_MODELS)
def test_each_branch_value_is_accepted_by_its_model(model):
    check = model_checker_from_json(json.loads(json.dumps(model)))
    try:
        found, *_ = branches(json.loads(json.dumps(model)))
    except Vacuous:
        found = {}
    for key, value in found.items():
        assert check(value, "", None) is True, key

def test_vectors_add_a_true_value_per_optional_property():
    assert unrooted(vectors({"a": True, "?b": 0}))[:5] == [
        "# . simplest", [True, {"a": False}], '# .?b present',
        [True, {"a": False, "b": 0}], '# .?b invalid']

def test_vectors_add_a_true_value_per_union_alternative():
    assert unrooted(vectors({"|": ["_x", "_y"]}))[:4] == [
        "# . simplest", [True, "x"], "# .'|'[1] branch", [True, "y"]]

def test_vectors_comment_an_optional_property_which_cannot_be_added():
    tests = vectors({"^": [{"a": 0, "?b": 0}, {"b": 0, "?a": 0}]})
    assert ["# .'^'[0].?b present FAILED: adding b is not valid",
            "# .'^'[1].?a present FAILED: adding a is not valid"] == \
        [t for t in tests if isinstance(t, str) and " present FAILED:" in t]

MARKED_MODEL = {"|": [{"a": "$INT"}, {"a": "$NULL"}]}

def test_cli_keeps_a_marked_value_it_cannot_settle(tmp_path, capsys):
    assert jmc_script(["--auto-values", _model_file(tmp_path, MARKED_MODEL)]) == 0
    assert "# .'|'[1] branch BAD" in json.loads(capsys.readouterr().out)

def test_cli_generates_test_vectors_for_an_auto_json_output(tmp_path):
    out = tmp_path / "m.auto.json"
    assert jmc_script(["-o", str(out), _model_file(tmp_path, MARKED_MODEL)]) == 0
    assert "# .'|'[1] branch BAD" in json.loads(out.read_text())

def test_cli_prefers_an_explicit_operation_to_the_auto_json_output(tmp_path):
    out = tmp_path / "m.auto.json"
    assert jmc_script(["-P", "-o", str(out), _model_file(tmp_path, MARKED_MODEL)]) == 0
    assert isinstance(json.loads(out.read_text()), dict)

def _values_file(tmp_path, text):
    """Write a test values file and return its path."""
    path = tmp_path / "m.values.json"
    path.write_text(text)
    return str(path)

def _auto(tmp_path, *options, model=MARKED_MODEL):
    """Generated test vectors of a model, as the CLI writes them to a file."""
    out = tmp_path / "m.auto.json"
    assert jmc_script([*options, "-o", str(out), _model_file(tmp_path, model)]) == 0
    return json.loads(out.read_text())

BAD_VALUE = {"a": None}
GOOD_VALUE = {"a": 0}

def test_cli_moves_a_bad_value_to_the_values_file(tmp_path, caplog):
    path = _values_file(tmp_path, '[\n  [ false, "x" ]\n]')
    with caplog.at_level(logging.WARNING):
        auto = _auto(tmp_path, "--values", path)
    assert [None, BAD_VALUE] not in auto
    assert not [t for t in auto if isinstance(t, str) and t.endswith(" BAD")]
    assert json.loads(Path(path).read_text()) == [[False, "x"], [None, BAD_VALUE]]
    assert any("1 value" in r.message for r in caplog.records)

def test_cli_drops_a_bad_value_the_values_file_already_holds(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, BAD_VALUE]]))
    auto = _auto(tmp_path, "--values", path)
    assert [None, BAD_VALUE] not in auto
    assert not [t for t in auto if isinstance(t, str) and " branch BAD" in t]
    assert json.loads(Path(path).read_text()) == [[True, BAD_VALUE]]

def test_cli_generates_a_settled_value_missing_from_the_values_file(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"]]))
    auto = _auto(tmp_path, "--values", path)
    assert [True, GOOD_VALUE] in auto
    assert [True, GOOD_VALUE] not in json.loads(Path(path).read_text())

def test_cli_removes_a_settled_value_from_the_values_file(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE]]))
    with caplog.at_level(logging.WARNING):
        auto = _auto(tmp_path, "--values", path)
    assert [True, GOOD_VALUE] in auto
    assert json.loads(Path(path).read_text()) == [[False, "x"], [None, BAD_VALUE]]
    assert any("removed, now generated: [1]" in r.message for r in caplog.records)

def test_cli_removes_a_settled_value_from_the_middle_of_the_values_file(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE], [False, "y"]]))
    _auto(tmp_path, "--values", path)
    assert json.loads(Path(path).read_text()) == \
        [[False, "x"], [False, "y"], [None, BAD_VALUE]]

def _errors_file(tmp_path, text):
    """Write an expected errors file beside the temporary model and return its path."""
    path = tmp_path / "m.errors.json"
    path.write_text(text)
    return path

def test_cli_renumbers_the_errors_file_of_a_removed_value(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE], [False, "y"]]))
    errors = _errors_file(tmp_path, '{ "values": { "py": [ 0, 2 ], "js": [ 2 ] } }')
    with caplog.at_level(logging.WARNING):
        _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text())["values"] == {"py": [0, 1], "js": [1]}
    assert any("m.errors.json" in r.message for r in caplog.records)

def test_cli_keeps_the_layout_of_the_errors_file_it_renumbers(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE], [False, "y"]]))
    errors = _errors_file(
        tmp_path, '{\n  "#py": "a note",\n  "values": { "py": [ 1 ] },\n  "ts": true\n}\n')
    _auto(tmp_path, "--values", path)
    assert errors.read_text() == \
        '{\n  "#py": "a note",\n  "values": { "py": [ 0 ] },\n  "ts": true\n}\n'

def test_cli_moves_the_errors_of_a_generated_value_to_the_auto_member(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE]]))
    errors = _errors_file(tmp_path, json.dumps({"values": {"py": [0, 1]}, "auto": {"py": [3]}}))
    _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text()) == {"values": {"py": [0]}, "auto": {"py": [0, 3]}}

def test_cli_creates_the_auto_member_of_the_errors_of_a_generated_value(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE]]))
    errors = _errors_file(tmp_path, '{\n  "values": { "py": [ 0, 1 ], "js": [ 1 ] }\n}\n')
    _auto(tmp_path, "--values", path)
    assert errors.read_text() == \
        '{\n  "values": { "py": [ 0 ], "js": [] },\n' \
        '  "auto": { "py": [ 0 ], "js": [ 0 ] }\n}\n'

def test_cli_creates_the_auto_backend_of_the_errors_of_a_generated_value(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE]]))
    errors = _errors_file(tmp_path, '{ "values": { "py": [ 1 ] }, "auto": { "js": [ 2 ] } }')
    _auto(tmp_path, "--values", path)
    assert errors.read_text() == \
        '{ "values": { "py": [] }, "auto": { "js": [ 2 ], "py": [ 0 ] } }'

def test_cli_drops_an_errors_index_pointing_at_no_test_vector(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[False, "x"], [True, GOOD_VALUE]]))
    errors = _errors_file(tmp_path, json.dumps({"values": {"py": [0, 42]}}))
    with caplog.at_level(logging.WARNING):
        _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text()) == {"values": {"py": [0]}}
    assert any("index 42" in r.message for r in caplog.records)

def _previous_auto(tmp_path, vectors):
    """Write the generated vector file a previous run would have left behind."""
    path = tmp_path / "m.auto.json"
    path.write_text(json.dumps(vectors))
    return path

def test_cli_renumbers_the_auto_member_against_the_previous_vectors(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[False, "x"]]))
    _previous_auto(tmp_path, ["# gone", [False, "zzz"], [True, GOOD_VALUE]])
    errors = _errors_file(tmp_path, json.dumps({"auto": {"py": [0, 1]}}))
    with caplog.at_level(logging.WARNING):
        _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text()) == {"auto": {"py": [0]}}
    assert any("index 0" in r.message for r in caplog.records)

def test_cli_keeps_the_auto_member_without_previous_vectors(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"]]))
    errors = _errors_file(tmp_path, json.dumps({"auto": {"py": [7]}}))
    _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text()) == {"auto": {"py": [7]}}

def test_cli_keeps_the_auto_member_when_writing_the_vectors_to_stdout(tmp_path, capsys):
    path = _values_file(tmp_path, json.dumps([[False, "x"]]))
    _previous_auto(tmp_path, [[True, GOOD_VALUE]])
    errors = _errors_file(tmp_path, json.dumps({"auto": {"py": [0]}}))
    assert jmc_script(["--values", path, _model_file(tmp_path, MARKED_MODEL)]) == 0
    assert isinstance(json.loads(capsys.readouterr().out), list)
    assert json.loads(errors.read_text()) == {"auto": {"py": [0]}}

def test_cli_leaves_the_errors_file_alone_without_a_removal(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, "x"]]))
    errors = _errors_file(tmp_path, json.dumps({"values": {"py": [0]}}))
    _auto(tmp_path, "--values", path)
    assert json.loads(errors.read_text()) == {"values": {"py": [0]}}

def test_cli_renumbers_no_errors_file_beside_the_values_file(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE]]))
    _auto(tmp_path, "--values", path)
    assert not (tmp_path / "m.errors.json").exists()

def test_cli_keeps_a_settled_value_the_values_file_disagrees_about(tmp_path):
    path = _values_file(tmp_path, json.dumps([[False, GOOD_VALUE]]))
    auto = _auto(tmp_path, "--values", path)
    assert [True, GOOD_VALUE] in auto
    assert [False, GOOD_VALUE] in json.loads(Path(path).read_text())

def test_cli_keeps_a_named_case_of_the_values_file(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, "some-case", GOOD_VALUE]]))
    _auto(tmp_path, "--values", path)
    assert [True, "some-case", GOOD_VALUE] in json.loads(Path(path).read_text())

def test_cli_removes_the_comment_of_a_section_it_empties(tmp_path):
    path = _values_file(tmp_path, json.dumps(["# kept", [False, "x"], "# gone", [True, GOOD_VALUE]]))
    _auto(tmp_path, "--values", path)
    assert json.loads(Path(path).read_text()) == ["# kept", [False, "x"], [None, BAD_VALUE]]

def test_cli_keeps_the_layout_of_the_values_file_it_removes_from(tmp_path):
    path = _values_file(tmp_path, '[\n  [ false,  "x" ],\n  [ true,   {"a": 0} ]\n]\n')
    _auto(tmp_path, "--values", path)
    assert Path(path).read_text() == \
        '[\n  [ false,  "x" ],\n  [ null, {"a": null} ]\n]\n'

def test_cli_empties_a_values_file_holding_only_generated_values(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE]]))
    _auto(tmp_path, "--values", path)
    assert json.loads(Path(path).read_text()) == [[None, BAD_VALUE]]

def test_cli_keeps_the_layout_of_the_values_file_it_adds_to(tmp_path):
    path = _values_file(tmp_path, '[\n  [ false,  "x" ]\n]\n')
    _auto(tmp_path, "--values", path)
    assert Path(path).read_text() == \
        '[\n  [ false,  "x" ],\n  [ null, {"a": null} ]\n]\n'

def test_cli_adds_to_an_empty_values_file(tmp_path):
    path = _values_file(tmp_path, "[]\n")
    _auto(tmp_path, "--values", path)
    assert json.loads(Path(path).read_text()) == [[None, BAD_VALUE]]

def test_cli_generates_test_vectors_for_a_values_file(tmp_path):
    path = _values_file(tmp_path, "[]")
    out = tmp_path / "m.out.json"
    assert jmc_script(["--values", path, "-o", str(out),
                       _model_file(tmp_path, MARKED_MODEL)]) == 0
    assert isinstance(json.loads(out.read_text()), list)

def test_cli_rejects_writing_the_generated_vectors_over_the_values_file(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE]]))
    with caplog.at_level(logging.ERROR):
        assert jmc_script(["--values", path, "-o", path,
                           _model_file(tmp_path, MARKED_MODEL)]) == 1
    assert json.loads(Path(path).read_text()) == [[True, GOOD_VALUE]]
    assert any("--values" in r.message for r in caplog.records)

def test_cli_ignores_an_errors_file_which_is_not_an_object(tmp_path, caplog):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE]]))
    errors = _errors_file(tmp_path, "[ 1, 2 ]")
    with caplog.at_level(logging.ERROR):
        _auto(tmp_path, "--values", path)
    assert errors.read_text() == "[ 1, 2 ]"
    assert json.loads(Path(path).read_text()) == [[None, BAD_VALUE]]
    assert any("m.errors.json" in r.message for r in caplog.records)

def test_cli_keeps_the_line_endings_of_the_values_file(tmp_path):
    path = tmp_path / "m.values.json"
    path.write_bytes(b'[\r\n  [ false, "x" ]\r\n]\r\n')
    _auto(tmp_path, "--values", str(path))
    assert path.read_bytes() == b'[\r\n  [ false, "x" ],\r\n  [ null, {"a": null} ]\r\n]\r\n'

def test_cli_keeps_the_line_endings_of_the_errors_file(tmp_path):
    path = _values_file(tmp_path, json.dumps([[True, GOOD_VALUE], [False, "x"]]))
    errors = tmp_path / "m.errors.json"
    errors.write_bytes(b'{\r\n  "values": { "py": [ 1 ] }\r\n}\r\n')
    _auto(tmp_path, "--values", path)
    assert errors.read_bytes() == b'{\r\n  "values": { "py": [ 0 ] }\r\n}\r\n'

def test_cli_rejects_a_missing_values_file(tmp_path, caplog):
    with caplog.at_level(logging.ERROR):
        assert jmc_script(["--values", str(tmp_path / "nope.values.json"),
                           _model_file(tmp_path, MARKED_MODEL)]) == 1
    assert any("nope.values.json" in r.message for r in caplog.records)

def test_cli_rejects_a_values_file_which_is_not_an_array(tmp_path, caplog):
    path = _values_file(tmp_path, "{}")
    with caplog.at_level(logging.ERROR):
        assert jmc_script(["--values", path, _model_file(tmp_path, MARKED_MODEL)]) == 1
    assert any("not an array" in r.message for r in caplog.records)

def test_cli_rejects_a_values_file_with_another_operation(tmp_path, caplog):
    path = _values_file(tmp_path, "[]")
    with caplog.at_level(logging.ERROR):
        assert jmc_script(["-P", "--values", path,
                           _model_file(tmp_path, MARKED_MODEL)]) == 1
    assert any("--values" in r.message for r in caplog.records)

DENIED_MODEL = {"@": {"|": [1, "$STRING"]}, ">=": 10}
OVERLAP_MODEL = {"^": [-1, 0]}

def test_vectors_settle_a_marked_value_the_model_certainly_rejects():
    tests = vectors(copy.deepcopy(DENIED_MODEL))
    assert "# .@.'|'[0] branch" in tests
    assert "# .@.'|'[0] branch BAD" not in tests
    assert [False, 1] in tests
    assert [None, 1] not in tests

def test_vectors_comment_a_marked_value_the_file_already_settles():
    tests = vectors(copy.deepcopy(OVERLAP_MODEL))
    assert "# .'^'[0] branch DUPLICATE BAD" in tests
    assert "# .'^'[0] branch BAD" not in tests
    assert [None, 0] not in tests
    assert [False, 0] in tests

def test_vectors_keep_a_marked_value_no_oracle_settles():
    tests = vectors(copy.deepcopy(MARKED_MODEL))
    assert "# .'|'[1] branch BAD" in tests
    assert [None, {"a": None}] in tests

CONFIRMED_MODEL = {"$": {"rec": {"|": [True, {"": "$rec"}]}}, "@": "$rec"}
REFUSED_MODEL = {"^": ["$ANY", "/^[a-z]+$/i"]}
ACCEPTED_MODEL = {"+": [{"a": 0}, {"|": [{"b": 1}, {"|": [{}]}]}]}

def test_vectors_keep_a_marked_value_the_validator_confirms():
    tests = vectors(copy.deepcopy(CONFIRMED_MODEL))
    assert "# .$rec.'|'[1].'' present" in tests
    assert "# .$rec.'|'[1].'' present BAD" not in tests
    assert [True, {"a": False}] in tests

def test_vectors_report_a_marked_value_the_validator_refuses():
    tests = vectors(copy.deepcopy(REFUSED_MODEL))
    assert "# .'^'[1] branch BAD FAIL" in tests
    assert paired(tests, "# .'^'[1] branch BAD FAIL") == [None, "a"]

def test_vectors_report_a_marked_violation_the_validator_accepts():
    tests = vectors(copy.deepcopy(ACCEPTED_MODEL))
    assert "# .'|'[0].b missing BAD PASS" in tests
    assert paired(tests, "# .'|'[0].b missing BAD PASS") == [None, {"a": 0}]

def test_vectors_keep_a_marked_value_the_validator_says_nothing_about():
    tests = vectors(copy.deepcopy(MARKED_MODEL))
    assert "# .'|'[1] branch BAD" in tests
    assert [None, {"a": None}] in tests

RULE_CASES = [
    ("validator agrees on a value", {"|": [{"@": "$INT", ">=": 10}, {"@": "$INT", ">=": 5}]},
     "# .'|'[1].'>=' bound", [True, 5]),
    ("validator agrees on a violation", "$EMAIL",
     "# . bad", [False, "susie@@json-model.org"]),
    ("module proves the model refuses", {"@": {"|": [1, "$STRING"]}, ">=": 10},
     "# .@.'|'[0] branch", [False, 1]),
    ("validator takes what was meant to break", {"+": [{"a": 0}, {"|": [{"b": 1}, {"|": [{}]}]}]},
     "# .'|'[0].b missing BAD PASS", [None, {"a": 0}]),
    ("validator refuses what was meant to hold", {"^": ["$ANY", "/^[a-z]+$/i"]},
     "# .'^'[1] branch BAD FAIL", [None, "a"]),
    ("the file already settles the value", {"^": [-1, 0]},
     "# .'^'[0] branch DUPLICATE BAD", None),
    ("no oracle says anything", {"|": [{"a": "$INT"}, {"a": "$NULL"}]},
     "# .'|'[1] branch BAD", [None, {"a": None}]),
]

@pytest.mark.parametrize("rule,model,comment,vector", RULE_CASES,
                         ids=[case[0] for case in RULE_CASES])
def test_every_check_back_rule_reaches_the_file(rule, model, comment, vector):
    """One minimal model per rule, from a settled verdict down to a bare mark."""
    tests = vectors(copy.deepcopy(model))
    assert comment in tests, rule
    if vector is None:
        assert isinstance(paired(tests, comment), str), rule
    else:
        assert paired(tests, comment) == vector, rule
