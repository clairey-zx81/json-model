import re
import json
from .utils import log

#
# regex /^.{n,m}$/s
#
def str_len_bounds(regex: str, opts: str) -> tuple[int, int]|None:
    if "s" in opts and (repeat := re.match(r"^\^\.\{(\d+),(\d+)}\$$", regex)):
        return int(repeat.group(1)), int(repeat.group(2))
    return None

#
# regex: /^prefix[class]repetition$/
#

# FIXME move [:xxx:] to simpler_regex?
def norm_char_class(init: str) -> str:
    """Best effort character class normalization to help pattern matching."""
    cc = init
    if cc == "":
        return ""
    elif cc == r"\w":
        return r"[0-9A-Z_a-z]"
    elif cc in (r"\d", r"[0123456789]"):
        return r"[0-9]"
    elif cc[0] != "[" or cc[-1] != "]":
        return init
    # parse character class contents
    cc = cc[1:-1]
    assert cc and cc[0] != "^", f"not a complement: {init}"
    ncc: set[str] = set()
    while cc:
        # NOTE character class escapes are flavor-dependent
        # - PCRE: ^-]\
        # - POSIX BRE/ERE: none (aka clever placement)
        # - Python, RE2: \d and other escapes?
        if cc.startswith("\\d"):
            ncc.add("0-9")
            cc = cc[2:]
        elif cc.startswith("\\w"):
            ncc.update({"0-9", "a-z", "A-Z", "_"})
            cc = cc[2:]
        elif cc.startswith(r"\\"):
            # FIXME expected escapes? should it normalize to clever placement?
            ncc.add(r"\\")
            cc = cc[2:]
        elif cc.startswith("[:word:]"):
            ncc.update({"0-9", "a-z", "A-Z", "_"})
            cc = cc[8:]
        elif cc.startswith("\\s"):
            ncc.update({" ", "\n", "\t", "\f", "\r"})
            cc = cc[2:]
        elif cc.startswith("[:space:]"):
            ncc.update({" ", "\n", "\t", "\f", "\r"})
            cc = cc[9:]
        elif cc.startswith("[:alnum:]"):
            ncc.update({"0-9", "a-z", "A-Z"})
            cc = cc[9:]
        elif cc.startswith("[:alpha:]"):
            ncc.update({"a-z", "A-Z"})
            cc = cc[9:]
        elif cc.startswith("[:blank:]"):
            ncc.update({" ", "\t"})
            cc = cc[9:]
        elif cc.startswith("[:digit:]"):
            ncc.add("0-9")
            cc = cc[9:]
        elif cc.startswith("[:xdigit:]"):
            ncc.update({"0-9", "A-F", "a-f"})
            cc = cc[10:]
        elif cc.startswith("[:lower:]"):
            ncc.add("a-z")
            cc = cc[9:]
        elif cc.startswith("[:upper:]"):
            ncc.add("A-Z")
            cc = cc[9:]
        elif len(cc) >= 3 and cc[1] == "-":
            ncc.add(cc[:3])
            cc = cc[3:]
        elif cc.startswith("0123456789"):
            ncc.add("0-9")
            cc = cc[10:]
        elif cc.startswith("abcdefghijklmnopqrstuvwxyz"):
            ncc.add("a-z")
            cc = cc[26:]
        elif cc.startswith("ABCDEFGHIJKLMNOPQRSTUVWXYZ"):
            ncc.add("A-Z")
            cc = cc[26:]
        elif cc.startswith("abcdef"):
            ncc.add("a-f")
            cc = cc[6:]
        elif cc.startswith("ABCDEF"):
            ncc.add("A-F")
            cc = cc[6:]
        elif cc.startswith("[:") or cc == "\\":
            log.warning(f"cannot normalize character class: {init}")
            return init
        elif cc.startswith("\\"):
            # NOTE unterminated character set… we assume a useless escape
            ncc.add(cc[1])
            cc = cc[2:]
        else:
            ncc.add(cc[0])
            cc = cc[1:]
    # rebuild normalized character class with clever placement
    if "^" in ncc and "-" in ncc:
        ccend = "-^" if len(ncc) == 2 else "^-"
        ncc.remove("^")
        ncc.remove("-")
    elif "-" in ncc:
        ccend = "-"
        ncc.remove("-")
    elif "^" in ncc:  # NOTE cannot be alone? what if?
        ccend = "^"
        ncc.remove("^")
    else:
        ccend = ""
    if "]" in ncc:
        ccstart = "]"
        ncc.remove("]")
    else:
        ccstart = ""
    return "[" + ccstart + "".join(sorted(ncc)) + ccend + "]"

def get_re_segment(regex: str) -> tuple[str, str, str, str]|None:
    """Extract a simple compilable segment from regex."""
    prefix, chars, repeat = "", "", ""
    i = 0
    # extract prefix
    while i < len(regex):
        c = regex[i]
        if c in "(|?*+[.^${":
            break
        elif c == "\\":  # unescape
            i += 1
            cn = regex[i]
            if cn in "dw":  # special case
                chars = "[0-9]" if cn == "d" else "[0-9a-zA-Z_]"
                i += 1
                break
            elif cn in "DW":
                return None
            # NOTE only a subset of chars can really be escaped
            prefix += cn
        else:
            prefix += c
        i += 1
    # extract chars, unless done in the previous loop
    if chars == "" and i < len(regex) and regex[i] == "[":
        chars = "["
        i += 1
        if regex[i] == "]":
            chars += "]"
            i += 1
        while i < len(regex):
            c = regex[i]
            if c == "\\":
                # escape inside brackets?
                # whether they are really needed depend on the flavor, eg none for POSIX…
                # we just accept \] here?
                if regex[i+1] == "]":
                    chars += "\\]"
                    i += 1
                else:  # just add a "\" as-is
                    chars += c
            elif c == "]":
                chars += c
                i += 1
                break
            else:
                chars += c
            i += 1
    elif chars == "" and i < len(regex) and regex[i] == ".":
        chars = "."
        i += 1
    # TODO else accept "."?
    # extract repeat
    if i < len(regex) and regex[i] in "?+*{":
        repeat = regex[i]
        if repeat == "{":
            i += 1
            while i < len(regex):
                c = regex[i]
                repeat += c
                i += 1
                if c == "}":
                    break
        else:
            i += 1
    # adjust empty chars to last prefix char on repeat
    if repeat and chars == "":
        assert prefix, "no repeat on an empty char"
        prefix, chars = prefix[:-1], prefix[-1]
    # return if something was extracted
    if prefix or chars:
        assert i > 0
        return prefix, chars, repeat, regex[i:]
    else:
        return None

def char_class_name(chars: str, ic: bool) -> str|None:
    """Return the name of the macro or function to check for a char in this class."""
    chars = norm_char_class(chars)
    # log.warning(f"chars = {chars}")
    match chars:
        # standard classes
        case "[a-z]":
            test = "isalpha" if ic else "islower"
        case "[A-Z]":
            test = "isalpha" if ic else "isupper"
        case "[A-Za-z]":
            test = "isalpha"
        case "[0-9]":
            test = "isdigit"
        case "[0-9a-f]":
            test = "isxdigit" if ic else "jm_lowhexa"
        case "[0-9A-F]":
            test = "isxdigit" if ic else "jm_uphexa"
        case "[0-9A-Fa-f]":
            test = "isxdigit"
        case "[0-9a-z]":
            test = "isalnum" if ic else "jm_lownum"
        case "[0-9A-Z]":
            test = "isalnum" if ic else "jm_upnum"
        case "[0-9A-Za-z]":
            test = "isalnum"
        # extensions
        case "[0-9_a-z]":
            test = "jm_isident" if ic else "jm_lowident"
        case "[0-9A-Z_]":
            test = "jm_isident" if ic else "jm_upident"
        case "[0-9A-Z_a-z]":
            test = "jm_isident"
        case " "|"[ ]":
            test = "jm_isspace"
        case "[_a-z]":
            test = "jm_lowlow"
        case "[A-Z_]":
            test = "jm_uplow"
        case "[0-9A-Z\\-:_a-z]":
            test = "jm_ident_dc"
        case "[1-9]":
            test = "jm_nzdigit"
        case "[0-9_a-z-]"|"[0-9\\-_a-z]":
            test = "jm_ident_dash" if ic else "jm_lowident_dash"
        case "[0-9A-Z_-]"|"[0-9A-Z\\-_]":
            test = "jm_ident_dash" if ic else "jm_upident_dash"
        case "[0-9A-Z_a-z-]"|"[0-9A-Z\\-_a-z]":
            test = "jm_ident_dash"
        # how to process utf8?
        # case ".":
        #     test = "jm_dots" if sl else "jm_dot"
        case _:
            test = None
    return test

def simple_re(regex: str, opts: str) -> tuple[list[str, str, str], bool]|None:
    """Return whether the regex is simple and directly compilable."""
    ic = "i" in opts
    if regex == "" or regex[0] != "^":
        return None
    regex = regex[1:]
    eot = regex[-1] == "$"
    if eot:
        regex = regex[:-1]
    segments = []
    while extract := get_re_segment(regex):
        prefix, chars, repeat, regex = extract
        if chars.startswith("[^"):  # cannot handle complement (utf8)
            return None
        if prefix and ic and re.search(r"[a-zA-Z]", prefix):
            # cannot handle letters with simple equality under ignore case
            return None
        if segments:
            prevchars, prevrepeat = segments[-1][1], segments[-1][2]
            # check that this is a clearcut from previous segment
            if prefix and prevchars and re.search(f"^{prevchars}$", prefix[0]):
                return None
            if prefix == "" and prevrepeat != "":
                # TODO improve chars chars interaction
                return None
        # we do not know yet whether chars are okay
        segments.append((prefix, chars, repeat))
        if regex == "":
            # translate chars to their class names
            segments = [ (p, char_class_name(c, ic), r) for p, c, r in segments ]
            if any(seg[1] is None for seg in segments):
                return None
            return segments, eot
    return None

#
# compile /^(foo|bla|...)$/i
#
def is_plain_str(s: str) -> bool:
    # already split on |, not need to check
    return ("(" not in s and "[" not in s and "\\" not in s and "." not in s and
            "*" not in s and "+" not in s and "?" not in s and "{" not in s)

def ic_str_cmp_re(regex: str, opts: str, limit: int = 64) -> tuple[list[str], bool]|None:
    """Whether regex is a list of alternate strings."""
    ic = "i" in opts
    if ic:
        # we do not manage lowercasing any unicode string
        try:
            regex.encode("ascii")
        except UnicodeEncodeError:
            return None
    if regex.startswith("^(") and regex.endswith(")$"):
        # TODO improve with escape management
        alts = regex[2:-2].split("|")
        if all(is_plain_str(s) for s in alts) and len(alts) >= 1:
            if ic:
                alts = [s.lower() for s in alts]
            # remove duplicates
            alts = sorted(set(alts))
            if len(alts) <= limit:
                return alts, ic
    return None
