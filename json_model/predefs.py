#
# predefs management
#

from .mtypes import ModelType

STR_MODEL_PREDEFS = {
    "$STRING",
    "$DATE", "$TIME", "$DATETIME", "$DURATION",
    "$REGEX", "$EXREG",
    "$UUID", "$CARD",
    "$URL", "$URI", "$EMAIL", "$IP4", "$IP6", "$HOST", "$ETH",
    "$JSON", "$JSONPT",
    "$__EXTENSION_COLOR",
}

BOOL_MODEL_PREDEFS = {
    "$BOOL", "$BOOLEAN",
}

INT_MODEL_PREDEFS = {
    "$INT", "$INTEGER", "$I32", "$I64", "$U32", "$U64",
}

FLOAT_MODEL_PREDEFS = {
    "$FLOAT", "$F32", "$F64", "$NUMBER",
}

MODEL_PREDEFS = {
    "$ANY", "$NONE", "$NULL",
} | INT_MODEL_PREDEFS | FLOAT_MODEL_PREDEFS | STR_MODEL_PREDEFS | BOOL_MODEL_PREDEFS

#
# network
#
# regex helpers
_DB = r"([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])"  # byte in decimal
_HS = r"([a-z0-9][-a-z0-9]{0,62})"  # ascii host segment, eg localhost json-model org
# length is max 255
_HOST = f"{_HS}(\\.{_HS})*"
# !#$%&'*+-/=?^_`{|}~
_NS = r"([-+!#$%&'`*/=?^{}|~_a-z0-9]+)"  # ascii name segment, eg jean-baptiste_poquelin1622
_NAME = f"{_NS}(\\.{_NS})*"  # email ascii name, eg jean-baptiste.poquelin
# no commented (...) nor quoted "..." forms; .. is forbidden
# max size of local part is 64 characters
_EMAIL = f"{_NAME}@{_HOST}"  # full ascii email, eg jean-baptiste.poquelin@comedie-francaise.fr
# json number
_IP4 = f"({_DB}\\.){{3}}{_DB}"
# ipv6 non-empty segment
_IP6S = "[0-9a-f]{1,4}"
# NOTE no zone id (%...)
_IP6 = (
    r"("
    f"({_IP6S}:){{7}}{_IP6S}|"               # _:_:_:_:_:_:_:_
    f"({_IP6S}:){{1,7}}:|"                   # *::
    f"({_IP6S}:){{1,6}}(:{_IP6S}){{1}}|"     # *::_
    f"({_IP6S}:){{1,5}}(:{_IP6S}){{1,2}}|"   # *::_:_
    f"({_IP6S}:){{1,4}}(:{_IP6S}){{1,3}}|"   # *::_:_:_
    f"({_IP6S}:){{1,3}}(:{_IP6S}){{1,4}}|"   # *::_:_:_:_
    f"({_IP6S}:){{1,2}}(:{_IP6S}){{1,5}}|"   # *::_:_:_:_:_
    f"{_IP6S}:(:{_IP6S}){{1,6}}|"            # *::_:_:_:_:_:_
    f":(:{_IP6S}){{1,7}}|"                   # ::*
    r"::)"                                   # ::
)
# ethernet/mac address
_ETH = "([0-9a-f]{2}:){5}[0-9a-f]{2}"  # i

# FIXME TODO improve!
_URL = r"((https?|file)://.*|\..*)"
# RFC3986 https://datatracker.ietf.org/doc/html/rfc3986
_URI = f"({_URL}|urn:.*)"

#
# date time and duration
#
# RFC3339 (not RFC9557) ; ISO8601
_DATE = r"\d{4}-(0?[1-9]|1[012])-([0-2]?\d|3[01])"  # 2020-07-29
_TIME = r"([01]\d|2[0-3]):[0-5]\d:([0-5]\d|60)(\.\d{0,9})?"  # 12:34:56.123456
# optional timezone with some leaway
_optTZ = r"(Z|[-+]\d\d(:?\d\d)?)?"
_DATETIME = f"{_DATE}T{_TIME}{_optTZ}"
# RFC3339 durations (down to seconds)
_DUR_s = "[0-9]+S"
_DUR_m = f"[0-9]+M({_DUR_s})?"
_DUR_h = f"[0-9]+H({_DUR_m})?"
_DUR_TIME = f"T({_DUR_h}|{_DUR_m}|{_DUR_s})"
_DUR_D = "[0-9]+D"
_DUR_W = "[0-9]+W"
_DUR_M = f"[0-9]+M({_DUR_D})?"
_DUR_Y = f"[0-9]+Y({_DUR_M})?"
_DUR_DATE = f"({_DUR_D}|{_DUR_M}|{_DUR_Y})({_DUR_TIME})?"
_DURATION = f"P({_DUR_DATE}|{_DUR_TIME}|{_DUR_W})"

#
# misc
#

_UUID = r"[0-9a-f]{4}([0-9a-f]{4}-){4}[0-9a-f]{12}"  # i
# unckeched LUHN algorithm
_CARD = r"[0-9]{16}"

_NUM = r"[-+]?\d+(\.\d*)?([Ee][-+]?\d+)?"
_JSON = f"\\s*(\\{{.*\\}}|\\[.*\\]|null|true|false|\".*\"|{_NUM})\\s*",  # s
_JSONPT = "(/([^~]|~0|~1)*)*"  # escapes: "~0" = "~" and "~1" = "/"

# CSS colors: simple and short list (not the 150)
_COLOR_HEXA = "#([0-9A-F]{6}|[0-9A-F]{3})"
# 16 CSS1 names, aliases and specials
_COLOR_NAMES = (
    "(black|silver|white|maroon|red|purple|fuchsia|green|lime|olive"
    "|yellow|navy|blue|teal|aqua|transparent|current[cC]olor|orange"
    "|cyan|magenta|((dark|light)?(slate)?|dim)gr[ae]y|rebeccapurple)"
)
_COLOR = f"({_COLOR_HEXA}|{_COLOR_NAMES})"

# model constants
CONST_RE = r"^=(null|true|false|-?\d+(\.\d+)?([eE]-?\d+)?)$"

# approximate backup regex for unimplemented predefs
PREDEF_RE: dict[str, tuple[str, str, str]] = {
    "$IP4": ("jm_is_ip4", f"^{_IP4}$", ""),
    "$IP6": ("jm_is_ip6", f"^{_IP6}$", "i"),
    "$HOST": ("jm_is_host", f"^{_HOST}$", "i"),
    "$EMAIL": ("jm_is_email", f"^{_EMAIL}$", "i"),
    "$ETH": ("jm_is_eth", f"^{_ETH}$", "i"),
    "$URL": ("jm_is_url", f"^{_URL}$", ""),
    "$URI": ("jm_is_uri", f"^{_URI}$", ""),
    "$DATE": ("jm_is_date", f"^{_DATE}$", ""),
    "$TIME": ("jm_is_time", f"^{_TIME}$", ""),
    "$DATETIME": ("jm_is_datetime", f"^{_DATETIME}$", "i"),
    "$DURATION": ("jm_is_duration", f"^{_DURATION}$", ""),
    "$UUID": ("jm_is_uuid", f"^{_UUID}$", "i"),
    "$JSON": ("jm_is_json", f"^{_JSON}$", "s"),
    "$JSONPT": ("jm_is_jsonpt", f"^{_JSONPT}$", "s"),
    "$CARD": ("jm_is_card", f"^{_CARD}$", ""),
    "$REGEX": ("jm_is_regex", "^.*$", "s"),
    # some extensions for JSU backend
    "$__EXTENSION_COLOR": ("jm_is_color", f"^{_COLOR}$", ""),  # v3
}

# some predefs models
PREDEFS: dict[str, ModelType] = {
    # specials
    "ANY": {"&": []},
    "NONE": {"|": []},
    # type inference
    "NULL": None,
    "BOOL": True,
    "BOOLEAN": True,
    "INT": -1,
    "INTEGER": -1,
    "I32": -1,  # min/max?
    "I64": -1,  # min/max?
    "U32": 0,  # max?
    "U64": 0,  # max?
    "FLOAT": -1.0,
    "F32": -1.0,
    "F64": -1.0,
    "NUMBER": {"|": [-1, -1.0]},
    "STRING": "",
    "REGEX": "",
    "EXREG": "",
    # o = optional
    "oBOOL": {"|": [None, "$BOOL"]},
    "oINT": {"|": [None, "$INT"]},
    "oFLOAT": {"|": [None, "$FLOAT"]},
    "oNUMBER": {"|": [None, "$NUMBER"]},
    "oSTRING": {"|": [None, "$STRING"]},
    "oURL": {"|": [None, "$URL"]},
    "oDATE": {"|": [None, "$DATE"]},
    "oUUID": {"|": [None, "$UUID"]},
    "oREGEX": {"|": [None, "$REGEX"]},
    # to be continued…
}

for pname, spec in PREDEF_RE.items():
    _, regex, opt = spec
    PREDEFS[pname[1:]] = f"/{regex}/{opt}"
