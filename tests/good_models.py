import json

with open("../models/json-model.model.json") as model:
    JSON_MODEL = json.load(model)

with open("../models/draft-2020-12-tight.model.json") as model:
    JSON_SCHEMA_MODEL = json.load(model)

with open("./json-model.schema.json") as schema:
    JSON_MODEL_SCHEMA = json.load(schema)

# only existing dates
def valid_date(s: str, _: str = None):
    from datetime import date
    try:
        date.fromisoformat(s)
        return True
    except ValueError:
        return False

# manually checked structure
tup_2i = lambda v, _ = None: type(v) in (list, tuple) and len(v) == 2 and isinstance(v[0], int) and isinstance(v[1], int)
odd_int = lambda v, _ = None: isinstance(v, int) and v % 2 == 1

V_FOO_BLA = {"|": [{"v": "=1", "foo": ""}, {"v": "=2", "bla": 0}]}
V_FOO_BLA_STR = {"|": [{"v": "foo", "foo": ""}, {"v": "bla", "bla": 0}]}

STR_OR_INT = {"|": ["", 0]}
NULL_OR_INT = { "|": [None, 0]}

TUP_II_1 = [0, 0]
TUP_II_2 = {"(": [0, 0]}
TUP_II_3 = "$tup-2-ints"
LIST_F_1 = [0.0]
LIST_F_2 = {"@": [0.0]}

# recursive type
TOC_DEF = {"$": "toc", "toc": ["$toc"]}

TOC_VAL_1 = {"toc": []}
TOC_VAL_2 = {"toc": [{"toc": []}]}
TOC_VAL_3 = {"toc": [{"toc": []}, {"toc": []}]}
TOC_VAL_4 = {"toc": [{"toc": []}, {"toc": [{"toc": []}]}]}
TOC_VAL_5 = {"toc": [{"toc": [{"toc": []}]}, {"toc": [{"toc": []}]}]}

# list[int] with len in [2, 3]
SHORT_INT_LIST = {
  "#": {"title": "Short Integer List"},
  "@": [0], "<=": 3, ">=": 2
}

# MO_CENT = {"@": 0, "mo": 100}

LOCAL_DEFS = {
  "%": {
    "quarante-deux": {"@": 0, "=": 42},
    "dix": {"@": 0, "=": 10},
  },
  "|": ["$quarante-deux", "$dix"],
}

NO_PROPS = {
  "@": {"": 0},
  "=": 0
}

ONE_PROPS = {
  "@": {"": 0},
  "=": 1
}

TWO_PROPS = {
  "@": {"": "$ANY"},
  "=": 2
}

STR_LEN_3 = {
  "@": "",
  "=": 3
}

# constrained key
FOO_BLA_KEY = {
  "%": {
    "foo-bla-key": {"|": ["foo", "bla"]}
  },
  "$foo-bla-key": True
}
FBK_0_T = {}
FBK_1_T = {"foo": True}
FBK_2_T = {"bla": False}
FBK_3_T = {"foo": False, "bla": True}
FBK_0_F = None
FBK_1_F = {"fun": True}

# distinct list
INT_SET = {"@": [0], "!": True}
IS_0_T = []
IS_1_T = [1]
IS_2_T = [1, 2]
IS_3_T = [1, 2, 3]
IS_0_F = None
IS_1_F = 42
IS_2_F = [1, 2, 1]
IS_3_F = [0, 1, 2, 3, 4, 5, 6, 5, 5, 5, 4]

# multipleOf
# MO3 = {"@": 0, "mo": 3}
# MO3_0_T = 0
# MO3_1_T = 3
# MO3_2_T = -27
# MO3_0_F = 1
# MO3_1_F = 100
# MO3_2_F = -11

# MO5 = {"@": 0.0, "mo": 0.5}
# MO5_0_T = 0.0
# MO5_1_T = 0.5
# MO5_2_T = 1.0
# MO5_3_T = 42.0
# MO5_0_F = 0.1
# MO5_1_F = -0.1
# MO5_2_F = 1.49
# MO5_3_F = 5432.1

# length
L3_0 = {"@": {"|": ["", {"": "$ANY"}, ["$ANY"]]}, "=": 3}
L3_1 = {"@": {"|": ["", {"": "$ANY"}, ["$ANY"]]}, "<=": 3, ">=": 3}
L3_2 = {"@": {"|": ["", {"": "$ANY"}, ["$ANY"]]}, "<": 5, ">": 2, "!=": 4}
L3_0_T = "hel"
L3_1_T = [0, 1, 2]
L3_2_T = {"a":1, "b":2, "c":3}
L3_0_F = None
L3_1_F = 123
L3_2_F = "hello world!"
L3_3_F = []
L3_4_F = [0]
L3_5_F = [0, 1]
L3_6_F = [0, 1, 2, 3]
L3_7_F = {}
L3_8_F = {"a": 0}

# constraint on str *value*
STRCMP = {"@": "", ">=": "A", "<": "["}
SC_0_T = "Calvin"
SC_1_T = "Susie"
SC_2_T = "A234"
SC_0_F = "calvin"
SC_1_F = "5432"
SC_2_F = ""

# disjunction on int tag optimization
DIS3 = {
    "|": [
        {"tag": "=0", "firstname": "", "lastname": ""},
        {"tag": "=1", "prenom": "", "nom": ""},
        {"tag": "=2", "Vorname": "", "Name": ""}
    ]
}
DIS3_0_T = {"tag": 0, "firstname": "Calvin", "lastname": "Foo"}
DIS3_1_T = {"tag": 1, "prenom": "Calvin", "nom": "Foo"}
DIS3_2_T = {"tag": 2, "Vorname": "Calvin", "Name": "Foo"}
DIS3_0_F = {"tag": 4, "firstname": "Calvin", "lastname": "Foo"}
DIS3_1_F = {"tag": "0", "firstname": "Calvin", "lastname": "Foo"}
DIS3_2_F = {"tag": 2, "Vorname": "Calvin", "nom": "Foo"}
DIS3_3_F = {"tag": 2, "Vorname": "Calvin", "Name": "Foo", "nom": "Bla"}
DIS3_4_F = {"tag": 0}
DIS3_5_F = {}
DIS3_6_F = "tag=0, firstname=Calvin, lastname=Foo"
DIS3_7_F = 42

# disjunction on str tag optimization
DTWO = {
    "|": [
        {"what": "foo", "foo": 0},
        {"what": "bla", "bla": 0}
    ]
}
DTWO_0_T = {"what": "foo", "foo": 42}
DTWO_1_T = {"what": "bla", "bla": 42}
DTWO_0_F = {"what": "dul", "dul": 42}
DTWO_1_F = {"what": 42, "foo": 42}
DTWO_2_F = {"what": False, "foo": 42}
DTWO_3_F = {"what": "foo", "foo": "forty-two"}

# disjunction with 2 candidate properties
DBOO = {
    "|": [
        {"tag": "=0", "ok": "=true", "foo": ""},
        {"tag": "=1", "ok": "=false", "bla": ""}
    ]
}
DBOO_0_T = {"tag": 0, "ok": True, "foo": "Susie"}
DBOO_1_T = {"tag": 1, "ok": False, "bla": "Calvin"}
DBOO_0_F = {"tag": 0, "ok": False, "foo": "Susie"}
DBOO_1_F = {"tag": 1, "ok": True, "bla": "Calvin"}
DBOO_2_F = {"tag": 1, "ok": True, "foo": "Susie"}
DBOO_3_F = {"tag": 0, "ok": False, "bla": "Calvin"}
DBOO_4_F = {"tag": 0, "ok": True, "foo": "Hobbes", "bla": "Rosalyn"}
DBOO_5_F = {"tag": 0, "ok": True, "bla": "Susie"}
DBOO_6_F = {"tag": 1, "ok": False, "foo": "Calvin"}

# disjunction on bool
DBOOL = {
    "|": [
        {"flip": "=true", "flap": ""},
        {"flip": "=false", "flop": ""},
    ]
}
DBOOL_0_T = {"flip": True, "flap": "ok"}
DBOOL_1_T = {"flip": False, "flop": "ok"}
DBOOL_2_F = {"flip": 1, "flap": "ok"}
DBOOL_3_F = {"flip": "true", "flap": "ok"}
DBOOL_4_F = {"flap": "KO", "flop": "KO"}

# variable length tuple
VARTUP0 = {"@": [0, "", True], ">=": 2, "<=": 5}
VARTUP0_0_T = [42, "Calvin"]
VARTUP0_1_T = [42, "Susie", False]
VARTUP0_2_T = [42, "Hobbes", False, True]
VARTUP0_3_T = [42, "Calvin", False, True, False]
VARTUP0_0_F = []
VARTUP0_1_F = [42]
VARTUP0_2_F = [42, "Susie", "oops"]
VARTUP0_3_F = [42, "Calvin", False, True, False, True]
VARTUP0_4_F = "quarante-deux"

# contains
# CLINT = {"@": ["$ANY"], "in": 0, "=": 2}
# CLINT_0_T = [0, 1]
# CLINT_1_T = [False, "one", 2, {"foo": "bla"}, 3, [False, True]]
# CLINT_0_F = []
# CLINT_1_F = [1]
# CLINT_2_F = [2, 3, 4]
# CLINT_3_F = [True, False]

# and
AND0 = {"&": [0, {"@": 0, ">=": 41}, {"@": 0, "<=": 43}]}
AND0_0_T = 41
AND0_1_T = 42
AND0_2_T = 43
AND0_0_F = 40
AND0_1_F = 44
AND0_2_F = False
AND0_3_F = None
AND0_4_F = "42"
AND0_5_F = [1, 2, 3]
AND0_6_F = {"answer": 42}
AND0_7_F = 3.14159

# only one
ONE0 = {"^": [0, {"@": 0, "=": 1}]}
ONE0_0_T = 0
ONE0_1_T = 2
ONE0_0_F = 1
ONE0_1_F = None
ONE0_2_F = 0.0
ONE0_3_F = []

# additive: length-6 capitalized distinct-char string
AND1 = {
    "&": [
        {"@": "/^[A-Z]/"},
        {"@": "", "=": 6},
        {"@": "", "!": True}
    ]
}
AND1_0_T = "Calvin"
AND1_1_T = "Susie!"
AND1_0_F = "calvin"
AND1_1_F = "Calvi"
AND1_2_F = "Calvin!"
AND1_3_F = "Hobbes"

# ADD: error types; opt + mand = mand
ADD0a = {"+":[{"a": 0},{"b": 0}]}
ADD0b = {"+":[{"a": 0, "?b": 0},{"?a": 0, "b": 0}]}
ADD0_0_T = {"a": 29, "b": 7}
ADD0_0_F = {"a": 29}
ADD0_1_F = {"a": 29, "b": "sept"}
ADD0_2_F = {"a": 29, "c": 7}
ADD0_3_F = {"a": True, "c": 7}

# ADD: opt + opt = opt; opt + mand = mand
ADD1 = {"+":[{"?a": 0, "?b": 0},{"?a": 0, "b": 0}]}
ADD1_0_T = {"a": 29, "b": 7}
ADD1_1_T = {"b": 29}
ADD1_0_F = {"a": 29}

# ADD: catchall
ADD2 = {"+":[{"a": 0}, {"": 0}]}
ADD2_0_T = {"a": 29}
ADD2_1_T = {"a": 29, "b": 7}
ADD2_0_F = {}
ADD2_1_F = {"b": 7}
ADD2_2_F = {"a": "vingt-neuf"}
ADD2_3_F = {"a": False}
ADD2_4_F = {"a": 29, "b": False}
ADD2_5_F = {"a": 29, "b": "vingt-neuf"}

# ADD: catchall merged
ADD3 = {"+":[{"a": 0, "": ""}, {"b": "", "": ""}]}
ADD3_0_T = {"a": 29, "b": "sept", "c": "vingt"}
ADD3_1_T = {"a": 29, "b": "sept"}
ADD3_0_F = {"a": 29, "b": "sept", "c": 20}
ADD3_1_F = {"a": "vingt-neuf", "b": "sept", "c": "vingt"}
ADD3_2_F = {"a": 29, "b": True, "c": "vingt"}

# ADD with constraint key ($)
ADD4a = {
  "%": {
    "key-add": {"|": ["font", "paris"]}
  },
  "+": [
	{"$key-add": 0},
	{"a": 0}
  ]
}
ADD4b = {
  "%": {
    "key-add": {"|": ["font", "paris"]}
  },
  "+": [
	{"$key-add": 0, "a": 0},
	{"$key-add": 0}
  ]
}
ADD4_0_T = {"a": 29}
ADD4_1_T = {"a": 29, "font": 7}
ADD4_2_T = {"a": 29, "paris": 2020}
ADD4_3_T = {"a": 29, "font": 7, "paris": 2020}
ADD4_0_F = {}
ADD4_1_F = {"a": "vingt"}
ADD4_2_F = {"a": 29, "briare": 7}
ADD4_3_F = {"a": 29, "font": "sept"}
ADD4_4_F = {"a": 29, "font": False}
ADD4_5_F = {"b": 29, "font": 7}

SIMPLE_COMMENT = { "#": "this is a simple comment", "@": "$ANY" }

#
# ALL TESTS and their expectations
#
TEST_MODELS = [
    # None
    (None, None, True),
    ("", None, False),
    (0, None, False),
    (0.0, None, False),
    ({}, None, False),
    ([], None, False),
    (True, None, False),
    (False, None, False),
    # bools
    (True, True, True),
    (False, True, True),
    (None, True, False),
    ("calvin", True, False),
    (5432, True, False),
    (3.14, True, False),
    ([1], True, False),
    ({}, True, False),
    (None, "$bool", False),
    (True, "$bool", True),
    (False, "$bool", True),
    (5432, "$bool", False),
    (3.14159, "$bool", False),
    ("hello world", "$bool", False),
    ([True, False], "$bool", False),
    ((True, False), "$bool", False),
    ({"hello": "world"}, "$bool", False),
    # =true/=false
    (None, "=true", False),
    (True, "=true", True),
    (False, "=true", False),
    (True, "=false", False),
    (False, "=false", True),
    (0, "=true", False),
    (1, "=true", False),
    # simple strings
    ("hello world", "", True),
    ("", "_", True),
    ("non-empty", "_", False),
    ("hello", "_hello", True),
    ("world", "world", True),
    ("hello", "world", False),
    (True, "", False),
    (False, "", False),
    (None, "", False),
    # numbers
    (123, 0, True),
    ("", 0, False),
    ("one", 0, False),
    (1.2, 0.0, True),
    (1, 0.0, True),
    (None, 0, False),
    (None, 0.0, False),
    # objects
    ({"name": "Calvin", "age": 6}, {"name": "", "age": 0}, True),
    ({"nom": "Calvin", "age": 6}, {"name": "", "age": 0}, False),
    ({"name": "Calvin", "age": 6.6}, {"name": "", "age": 0}, False),
    ({"name": "Calvin", "age": 6}, {"name": "", "?age": 0}, True),
    ({"name": "Calvin"}, {"name": "", "?age": 0}, True),
    ({"name": "Calvin", "addr": "Home"}, {"name": ""}, False),
    ({"name": "Calvin", "addr": "Home"}, {"name": "", "": ""}, True),
    ({"v": 1, "foo": "42"}, V_FOO_BLA, True),
    ({"v": 2, "bla": 42}, V_FOO_BLA, True),
    ({"v": 3, "bad": "BAD"}, V_FOO_BLA, False),
    ({"v": 1, "bla": "42"}, V_FOO_BLA, False),
    ({"v": 2, "foo": 42}, V_FOO_BLA, False),
    ({"v": "foo", "foo": "bla"}, V_FOO_BLA_STR, True),
    ({"v": "bla", "bla": 42}, V_FOO_BLA_STR, True),
    ({"v": "xxx", "bad": "BAD"}, V_FOO_BLA_STR, False),
    ({"v": "foo", "bla": "42"}, V_FOO_BLA_STR, False),
    ({"v": "bla", "foo": 42}, V_FOO_BLA_STR, False),
    # list
    ([], [0], True),
    ([1, 2], [0], True),
    ([1, "two"], [0], False),
    ([None, None, None], [None], True),
    ([None, None, 0], [None], False),
    ([], LIST_F_1, True),
    ([1.0], LIST_F_1, True),
    ([1.0, 2.0], LIST_F_1, True),
    (["one"], LIST_F_1, False),
    (1, LIST_F_1, False),
    ([], LIST_F_2, True),
    ([1.0], LIST_F_2, True),
    ([1.0, 2.0], LIST_F_2, True),
    (["one"], LIST_F_2, False),
    (1, LIST_F_2, False),
    # disjunction
    ("hello", STR_OR_INT, True),
    (42, STR_OR_INT, True),
    (1.1, STR_OR_INT, False),
    (None, STR_OR_INT, False),
    ([], STR_OR_INT, False),
    ({}, STR_OR_INT, False),
    ("hello", NULL_OR_INT, False),
    (42, NULL_OR_INT, True),
    (1.1, NULL_OR_INT, False),
    (None, NULL_OR_INT, True),
    ([], NULL_OR_INT, False),
    ({}, NULL_OR_INT, False),
    # with int names
    ({"v": 1, "foo": "bla"}, "$foobla", True),
    ({"v": 2, "bla": 42}, "$foobla", True),
    ({"v": 3, "bad": "BAD"}, "$foobla", False),
    ({"v": 1, "bla": "42"}, "$foobla", False),
    ({"v": 2, "foo": 42}, "$foobla", False),
    # with str names
    ({"v": "foo", "foo": "bla"}, "$fooblas", True),
    ({"v": "bla", "bla": 42}, "$fooblas", True),
    ({"v": "xxx", "bad": "BAD"}, "$fooblas", False),
    ({"v": "foo", "bla": "42"}, "$fooblas", False),
    ({"v": "bla", "foo": 42}, "$fooblas", False),
    ("hello", "$strint", True),
    (42, "$strint", True),
    (1.1, "$strint", False),
    (None, "$strint", False),
    ([], "$strint", False),
    ({}, "$strint", False),
    ("hello", "$nullint", False),
    (42, "$nullint", True),
    (1.1, "$nullint", False),
    (None, "$nullint", True),
    ([], "$nullint", False),
    ({}, "$nullint", False),
    # simple comment
    (None, SIMPLE_COMMENT, True),
    (False, SIMPLE_COMMENT, True),
    (42, SIMPLE_COMMENT, True),
    (3.14159, SIMPLE_COMMENT, True),
    ("Calvin and Susie", SIMPLE_COMMENT, True),
    ([1, 2, 3], SIMPLE_COMMENT, True),
    ({"Calvin": "Susie"}, SIMPLE_COMMENT, True),
    # re
    ("Calvin", "/^[A-Z][a-z]*$/", True),
    ("1234", "/^[A-Z][a-z]*$/", False),
    ("1970-10-14", "$date", True),
    ("20 mars 1970", "$date", False),
    # whatever: does not check anything a tall
    ("oops", "$ANY", True),
    (None, "$ANY", True),
    (5432, "$ANY", True),
    (3.14159, "$ANY", True),
    (["oops", 1], "$ANY", True),
    ({"what": "ever"}, "$ANY", True),
    # stupid catchall
    (int, "$ANY", True),
    (print, "$ANY", True),
    # extension
    ([1, 2], "$tup-2-ints", True),
    ((3, 4), "$tup-2-ints", True),
    ([1, 2], TUP_II_1, True),
    ((3, 4), TUP_II_1, True),
    ((), "$tup-2-ints", False),
    ((5), "$tup-2-ints", False),
    ([6, 7, 8], "$tup-2-ints", False),
    ([6, "9"], "$tup-2-ints", False),
    ((), TUP_II_1, False),
    ((5), TUP_II_1, False),
    ([6, 7, 8], TUP_II_1, False),
    (1, "$odd-int", True),
    (191, "$odd-int", True),
    (222, "$odd-int", False),
    (0, "$odd-int", False),
    (1.3, "$odd-int", False),
    (False, "$odd-int", False),
    ("111", "$odd-int", False),
    ("2020-02-28", "$valid-date", True),
    ("2020-02-29", "$valid-date", True),
    ("2021-02-29", "$valid-date", False),
    ("2022-02-29", "$valid-date", False),
    ("2023-02-29", "$valid-date", False),
    ("0000-00-00", "$valid-date", False),
    # recursion
    (TOC_VAL_1, TOC_DEF, True),
    (TOC_VAL_2, TOC_DEF, True),
    (TOC_VAL_3, TOC_DEF, True),
    (TOC_VAL_4, TOC_DEF, True),
    (TOC_VAL_5, TOC_DEF, True),
    ({"toc": "plouf"}, TOC_DEF, False),
    (None, TOC_DEF, False),
    # object-constraints
    (None, SHORT_INT_LIST, False),
    (True, SHORT_INT_LIST, False),
    (123, SHORT_INT_LIST, False),
    (123.456E12, SHORT_INT_LIST, False),
    ("hello", SHORT_INT_LIST, False),
    ({}, SHORT_INT_LIST, False),
    ([], SHORT_INT_LIST, False),
    ([1], SHORT_INT_LIST, False),
    ([2,3], SHORT_INT_LIST, True),
    ([4,5,6], SHORT_INT_LIST, True),
    ([7,8,9,0], SHORT_INT_LIST, False),
    (None, "$short-list", False),
    (True, "$short-list", False),
    (123, "$short-list", False),
    (123.456E12, "$short-list", False),
    ("hello", "$short-list", False),
    ({}, "$short-list", False),
    ([], "$short-list", False),
    ([1], "$short-list", False),
    ([2,3], "$short-list", True),
    ([4,5,6], "$short-list", True),
    ([7,8,9,0], "$short-list", False),
    # MO
    # (None, MO_CENT, False),
    # ("hello", MO_CENT, False),
    # (0, MO_CENT, True),
    # (1, MO_CENT, False),
    # (100, MO_CENT, True),
    # (150, MO_CENT, False),
    # (-200, MO_CENT, True),
    # (MO3_0_T, MO3, True),
    # (MO3_1_T, MO3, True),
    # (MO3_2_T, MO3, True),
    # (MO3_0_F, MO3, False),
    # (MO3_1_F, MO3, False),
    # (MO3_2_F, MO3, False),
    # (MO5_0_T, MO5, True),
    # (MO5_1_T, MO5, True),
    # (MO5_2_T, MO5, True),
    # (MO5_3_T, MO5, True),
    # (MO5_0_F, MO5, False),
    # (MO5_1_F, MO5, False),
    # (MO5_2_F, MO5, False),
    # (MO5_3_F, MO5, False),
    # length three lengthy stuff
    (L3_0_T, L3_0, True),
    (L3_1_T, L3_0, True),
    (L3_2_T, L3_0, True),
    (L3_0_F, L3_0, False),
    (L3_1_F, L3_0, False),
    (L3_2_F, L3_0, False),
    (L3_3_F, L3_0, False),
    (L3_4_F, L3_0, False),
    (L3_5_F, L3_0, False),
    (L3_6_F, L3_0, False),
    (L3_7_F, L3_0, False),
    (L3_8_F, L3_0, False),
    (L3_0_T, L3_1, True),
    (L3_1_T, L3_1, True),
    (L3_2_T, L3_1, True),
    (L3_0_F, L3_1, False),
    (L3_1_F, L3_1, False),
    (L3_2_F, L3_1, False),
    (L3_3_F, L3_1, False),
    (L3_4_F, L3_1, False),
    (L3_5_F, L3_1, False),
    (L3_6_F, L3_1, False),
    (L3_7_F, L3_1, False),
    (L3_8_F, L3_1, False),
    (L3_0_T, L3_2, True),
    (L3_1_T, L3_2, True),
    (L3_2_T, L3_2, True),
    (L3_0_F, L3_2, False),
    (L3_1_F, L3_2, False),
    (L3_2_F, L3_2, False),
    (L3_3_F, L3_2, False),
    (L3_4_F, L3_2, False),
    (L3_5_F, L3_2, False),
    (L3_6_F, L3_2, False),
    (L3_7_F, L3_2, False),
    (L3_8_F, L3_2, False),
    # strcmp
    (SC_0_T, STRCMP, True),
    (SC_1_T, STRCMP, True),
    (SC_2_T, STRCMP, True),
    (SC_0_F, STRCMP, False),
    (SC_1_F, STRCMP, False),
    (SC_2_F, STRCMP, False),
    # maj
    # ("hello", MAJ_START, False),
    # ("Allô", MAJ_START, True),
    # ("Hello", MAJ_START, True),
    # ("Zélote", MAJ_START, True),
    # ("[…", MAJ_START, False),
    (None, LOCAL_DEFS, False),
    (18, LOCAL_DEFS, False),
    ("42", LOCAL_DEFS, False),
    ([10, 42], LOCAL_DEFS, False),
    (10, LOCAL_DEFS, True),
    (42, LOCAL_DEFS, True),
    # no props
    (None, NO_PROPS, False),
    (0, NO_PROPS, False),
    ("", NO_PROPS, False),
    ([], NO_PROPS, False),
    ({}, NO_PROPS, True),
    ({"x": 1}, NO_PROPS, False),
    # one props
    (None, ONE_PROPS, False),
    (0, ONE_PROPS, False),
    ("", ONE_PROPS, False),
    ([], ONE_PROPS, False),
    ({}, ONE_PROPS, False),
    ({"x": 1}, ONE_PROPS, True),
    ({"x": 1, "y": 2}, ONE_PROPS, False),
    # two props
    (None, TWO_PROPS, False),
    (True, TWO_PROPS, False),
    ("foo", TWO_PROPS, False),
    (2, TWO_PROPS, False),
    ([1, 2], TWO_PROPS, False),
    ({}, TWO_PROPS, False),
    ({"x": "1", "y": 2}, TWO_PROPS, True),
    ({"x": "1", "y": 2, "z": None}, TWO_PROPS, False),
    # str len 3
    (None, STR_LEN_3, False),
    (False, STR_LEN_3, False),
    (123, STR_LEN_3, False),
    (1.1, STR_LEN_3, False),
    ("", STR_LEN_3, False),
    ("1", STR_LEN_3, False),
    ("12", STR_LEN_3, False),
    ("123", STR_LEN_3, True),
    ("1234", STR_LEN_3, False),
    ([1,2,3], STR_LEN_3, False),
    ({"a":1,"b":2,"c":3}, STR_LEN_3, False),
    # constrained keys
    (FBK_0_T, FOO_BLA_KEY, True),
    (FBK_1_T, FOO_BLA_KEY, True),
    (FBK_2_T, FOO_BLA_KEY, True),
    (FBK_3_T, FOO_BLA_KEY, True),
    (FBK_0_F, FOO_BLA_KEY, False),
    (FBK_1_F, FOO_BLA_KEY, False),
    # distinct
    (IS_0_T, INT_SET, True),
    (IS_1_T, INT_SET, True),
    (IS_2_T, INT_SET, True),
    (IS_3_T, INT_SET, True),
    (IS_0_F, INT_SET, False),
    (IS_1_F, INT_SET, False),
    (IS_2_F, INT_SET, False),
    (IS_3_F, INT_SET, False),
    # disjunction
    (DIS3_0_T, DIS3, True),
    (DIS3_1_T, DIS3, True),
    (DIS3_2_T, DIS3, True),
    (DIS3_0_F, DIS3, False),
    (DIS3_1_F, DIS3, False),
    (DIS3_2_F, DIS3, False),
    (DIS3_3_F, DIS3, False),
    (DIS3_4_F, DIS3, False),
    (DIS3_5_F, DIS3, False),
    (DIS3_6_F, DIS3, False),
    (DIS3_7_F, DIS3, False),
    (DTWO_0_T, DTWO, True),
    (DTWO_1_T, DTWO, True),
    (DTWO_0_F, DTWO, False),
    (DTWO_1_F, DTWO, False),
    (DTWO_2_F, DTWO, False),
    (DTWO_3_F, DTWO, False),
    (DBOOL_0_T, DBOOL, True),
    (DBOOL_1_T, DBOOL, True),
    (DBOOL_2_F, DBOOL, False),
    (DBOOL_3_F, DBOOL, False),
    (DBOOL_4_F, DBOOL, False),
    (DBOO_0_T, DBOO, True),
    (DBOO_1_T, DBOO, True),
    (DBOO_0_F, DBOO, False),
    (DBOO_1_F, DBOO, False),
    (DBOO_2_F, DBOO, False),
    (DBOO_3_F, DBOO, False),
    (DBOO_4_F, DBOO, False),
    (DBOO_5_F, DBOO, False),
    (DBOO_6_F, DBOO, False),
    (None, DBOO, False),
    (5432, DBOO, False),
    ("debout", DBOO, False),
    ([0, 1, 2], DBOO, False),
    ({}, DBOO, False),
    # vartup
    (VARTUP0_0_T, VARTUP0, True),
    (VARTUP0_1_T, VARTUP0, True),
    (VARTUP0_2_T, VARTUP0, True),
    (VARTUP0_3_T, VARTUP0, True),
    (VARTUP0_0_F, VARTUP0, False),
    (VARTUP0_1_F, VARTUP0, False),
    (VARTUP0_2_F, VARTUP0, False),
    (VARTUP0_3_F, VARTUP0, False),
    (VARTUP0_4_F, VARTUP0, False),
    # contains
    # (CLINT_0_T, CLINT, True),
    # (CLINT_1_T, CLINT, True),
    # (CLINT_0_F, CLINT, False),
    # (CLINT_1_F, CLINT, False),
    # (CLINT_2_F, CLINT, False),
    # (CLINT_3_F, CLINT, False),
    # & = conjunctive
    (AND0_0_T, AND0, True),
    (AND0_1_T, AND0, True),
    (AND0_2_T, AND0, True),
    (AND0_0_F, AND0, False),
    (AND0_1_F, AND0, False),
    (AND0_2_F, AND0, False),
    (AND0_3_F, AND0, False),
    (AND0_4_F, AND0, False),
    (AND0_5_F, AND0, False),
    (AND0_6_F, AND0, False),
    (AND0_7_F, AND0, False),
    (AND1_0_T, AND1, True),
    (AND1_1_T, AND1, True),
    (AND1_0_F, AND1, False),
    (AND1_1_F, AND1, False),
    (AND1_2_F, AND1, False),
    (AND1_3_F, AND1, False),
    # ^ = exclusive
    (ONE0_0_T, ONE0, True),
    (ONE0_1_T, ONE0, True),
    (ONE0_0_F, ONE0, False),
    (ONE0_1_F, ONE0, False),
    (ONE0_2_F, ONE0, False),
    (ONE0_3_F, ONE0, False),
    # + = additive
    (ADD0_0_T, ADD0a, True),
    (ADD0_0_T, ADD0b, True),
    (ADD0_0_F, ADD0a, False),
    (ADD0_0_F, ADD0b, False),
    (ADD0_1_F, ADD0a, False),
    (ADD0_1_F, ADD0b, False),
    (ADD0_2_F, ADD0a, False),
    (ADD0_2_F, ADD0b, False),
    (ADD0_3_F, ADD0a, False),
    (ADD0_3_F, ADD0b, False),
    (ADD1_0_T, ADD1, True),
    (ADD1_1_T, ADD1, True),
    (ADD1_0_F, ADD1, False),
    (ADD2_0_T, ADD2, True),
    (ADD2_1_T, ADD2, True),
    (ADD2_0_F, ADD2, False),
    (ADD2_1_F, ADD2, False),
    (ADD2_2_F, ADD2, False),
    (ADD2_3_F, ADD2, False),
    (ADD2_4_F, ADD2, False),
    (ADD2_5_F, ADD2, False),
    (ADD3_0_T, ADD3, True),
    (ADD3_1_T, ADD3, True),
    (ADD3_0_F, ADD3, False),
    (ADD3_1_F, ADD3, False),
    (ADD3_2_F, ADD3, False),
    (ADD4_0_T, ADD4a, True),
    (ADD4_1_T, ADD4a, True),
    (ADD4_2_T, ADD4a, True),
    (ADD4_3_T, ADD4a, True),
    (ADD4_0_F, ADD4a, False),
    (ADD4_1_F, ADD4a, False),
    (ADD4_2_F, ADD4a, False),
    (ADD4_3_F, ADD4a, False),
    (ADD4_4_F, ADD4a, False),
    (ADD4_5_F, ADD4a, False),
    (ADD4_0_T, ADD4b, True),
    (ADD4_1_T, ADD4b, True),
    (ADD4_2_T, ADD4b, True),
    (ADD4_3_T, ADD4b, True),
    (ADD4_0_F, ADD4b, False),
    (ADD4_1_F, ADD4b, False),
    (ADD4_2_F, ADD4b, False),
    (ADD4_3_F, ADD4b, False),
    (ADD4_4_F, ADD4b, False),
    (ADD4_5_F, ADD4b, False),
    # ints
    (-42, -1, True),
    (0, -1, True),
    (42, -1, True),
    (True, -1, False),
    ("forty-two", -1, False),
    (-42, 0, False),
    (0, 0, True),
    (42, 0, True),
    (True, 0, False),
    ("forty-two", 0, False),
    (-42, 1, False),
    (0, 1, False),
    (42, 1, True),
    (True, 1, False),
    ("forty-two", 1, False),
    # self
    (JSON_MODEL, JSON_MODEL, True),
    (JSON_SCHEMA_MODEL, JSON_MODEL, True),
]

def init_data(define):
    define("foobla", V_FOO_BLA)
    define("fooblas", V_FOO_BLA_STR)
    define("strint", STR_OR_INT)
    define("nullint", NULL_OR_INT)
    # vaguely look like a date
    define("date", r"/^\d{4}-\d{2}-\d{2}$/")
    define("bool", True)
    define("lf1", LIST_F_1)
    define("lf2", LIST_F_2)
    define("odd-int", odd_int)
    define("short-list", SHORT_INT_LIST)
    # function calls
    define("tup-2-ints", tup_2i)
    define("valid-date", valid_date)
