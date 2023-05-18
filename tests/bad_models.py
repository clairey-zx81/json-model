#
# test bad models
#
BADS = [
    # "$" value is str
    ("name 0", False, False, {"$": None}),
    ("name 1", False, False, {"$": False}),
    ("name 2", False, False, {"$": 42}),
    ("name 3", False, False, {"$": {}}),
    # "#" value is dict or str
    ("meta 0", False, False, {"#": None}),
    ("meta 1", False, False, {"#": 42}),
    ("meta 2", False, False, {"#": False}),
    ("meta 3", False, False, {"#": []}),
    # ("meta 4", False, False, {"#": {"$$": True, }}),
    # "%" value is a dict
    ("defs 0", False, False, {"%": None}),
    ("defs 1", False, False, {"%": 42}),
    ("defs 2", False, False, {"%": "oops"}),
    ("defs 3", False, False, {"%": []}),
    # exclusives
    ("@|", False, False, {"@": "", "|": [0, ""]}),
    ("@&", False, False, {"@": "", "&": [0, ""]}),
    ("@^", False, False, {"@": "", "^": [0, ""]}),
    ("@+", False, False, {"@": "", "+": [0, ""]}),
    ("@i", False, False, {"@": "", "i": True}),
    ("i|", False, False, {"i": "", "|": [0, ""]}),
    ("i&", False, False, {"i": "", "&": [0, ""]}),
    ("i^", False, False, {"i": "", "^": [0, ""]}),
    ("i+", False, False, {"i": "", "+": [0, ""]}),
    ("|s", False, False, {"|": "bad"}),
    ("^s", False, False, {"^": "bad"}),
    ("&s", False, False, {"&": "bad"}),
    ("+s", False, False, {"+": "bad"}),
    # FIXME @ restriction could be detected
    # ("@in", True, False, {"@": True, "in": ""}),
    ("@eq", False, False, {"@": [0], "eq": [0, 0]}),
    # bad types
    ("@ type 0", False, False, {"@": "", "le": True}),
    # ("@ type 1", False, False, {"@": "", "prop": 0}),
    # ("@ type 2", False, False, {"@": "", "mo": "hello"}),
    # ("@ type 3", False, False, {"@": "", "mo": False}),
    # multi def props
    ("{x,x}", True, False, {"a": 0, "_a": 0}),
    ("{x,x}", True, False, {"a": 0, "?a": 0}),
    ("{x,x}", True, False, {"_a": 0, "?a": 0}),
    # unexpected constraint
    ("@what", False, False, {"@": "", "whatever": 0}),
    # bad key
    ("42", False, False, {42:42}),
    # TODO implement!
    # TODO exemples pour tester les incompatibilités…
    ("+", True, False, {"+": []}),
    ("+", True, False, {"+": [{"a": 0}, 0]}),
    ("+", True, False, {"+":[{"a": 0}, {"a": False}]}),
    ("+", True, False, {"+":[{"a": 0}, {"?a": ""}]}),
    ("+", True, False, {"+":[{"@": 0, "le": 2}, {"a": 0, "b": 0, "c": ""}]}),
    # #
    # detect infinite recursion?
    # FIXME compilation should fail?
    ("recursion", True, True, {"%": {"oops": "$oops"}, "foo": "$oops"}),
    # TO BE CONTINUED…
]
