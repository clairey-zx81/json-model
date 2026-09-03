#! /bin/bash
#
# Remove test vectors from *.values.json files when the same value is already
# covered by the matching generated *.auto.json, and renumber the vector
# indexes held in the matching *.errors.json files.
#
# Run "make auto" first, the *.auto.json files are not committed.
#
# usage: [VERBOSE=1] strip-auto-values.sh [-w] [file-or-directory ...]
#
#   -w   apply the changes, the default is to only report them
#
# the default target is the directory holding this script
#

write=

while [ $# -gt 0 ] ; do
    case "$1" in
        -w|--write) write=1 ; shift ;;
        -h|--help) sed -n '2,14p' "$0" ; exit 0 ;;
        --) shift ; break ;;
        -*) echo "unexpected option: $1" >&2 ; exit 1 ;;
        *) break ;;
    esac
done

targets=("$@")
[ ${#targets[@]} -eq 0 ] && targets=("$(dirname "$0")")

WRITE="$write" python3 - "${targets[@]}" <<'PY'
import json
import os
import sys

WRITE = bool(os.environ.get("WRITE"))
VERBOSE = bool(os.environ.get("VERBOSE"))
SUFFIX = ".values.json"

def collect(targets):
    """List the values files held by the given files or directories."""
    out = set()
    for target in targets:
        if os.path.isdir(target):
            for root, _, names in os.walk(target, followlinks=True):
                for name in names:
                    if name.endswith(SUFFIX):
                        out.add(os.path.join(root, name))
        elif os.path.isfile(target):
            out.add(target)
        else:
            print(f"no such file or directory: {target}", file=sys.stderr)
    return sorted(out)

def key(value):
    """Comparison key of a test vector value."""
    return json.dumps(value, sort_keys=True)

def elements(text):
    """List (value, start, end) triples for the items of a JSON array source."""
    dec, out = json.JSONDecoder(), []
    i, n = text.index("[") + 1, len(text)
    while i < n:
        while i < n and text[i].isspace():
            i += 1
        if i >= n or text[i] == "]":
            break
        value, end = dec.raw_decode(text, i)
        out.append((value, i, end))
        i = end
        while i < n and text[i].isspace():
            i += 1
        if i < n and text[i] == ",":
            i += 1
    return out

def members(text):
    """List (name, value, start, end) tuples for the members of a JSON object source."""
    dec, out = json.JSONDecoder(), []
    i, n = text.index("{") + 1, len(text)
    while i < n:
        while i < n and text[i].isspace():
            i += 1
        if i >= n or text[i] == "}":
            break
        name, i = dec.raw_decode(text, i)
        while i < n and text[i].isspace():
            i += 1
        i += 1
        while i < n and text[i].isspace():
            i += 1
        value, end = dec.raw_decode(text, i)
        out.append((name, value, i, end))
        i = end
        while i < n and text[i].isspace():
            i += 1
        if i < n and text[i] == ",":
            i += 1
    return out

def splice(text, elems, dropped):
    """Rebuild an array source without the dropped item indexes."""
    kept = [i for i in range(len(elems)) if i not in dropped]
    if not kept:
        return text[:text.index("[")] + "[]" + text[text.rindex("]") + 1:]
    parts = [text[:elems[0][1]]]
    for pos, i in enumerate(kept):
        parts.append(text[elems[i][1]:elems[i][2]])
        if pos + 1 < len(kept):
            parts.append(text[elems[i][2]:elems[i + 1][1]])
    parts.append(text[elems[-1][2]:])
    return "".join(parts)

def auto_values(path):
    """Map the value key of each generated vector to its expected validity."""
    with open(path) as f:
        data = json.load(f)
    flags = {}
    for item in data:
        if isinstance(item, list) and len(item) == 2:
            flags.setdefault(key(item[1]), item[0])
    return flags

def dead_comments(elems, dropped):
    """Comment indexes whose whole section of vectors was dropped."""
    dead, comment, seen, gone = set(), None, 0, 0
    for i, (value, _, _) in enumerate(elems):
        if isinstance(value, str):
            if comment is not None and seen > 0 and seen == gone:
                dead.add(comment)
            comment, seen, gone = i, 0, 0
        elif isinstance(value, list):
            seen += 1
            if i in dropped:
                gone += 1
    if comment is not None and seen > 0 and seen == gone:
        dead.add(comment)
    return dead

def render(source, indexes):
    """Render an index list following the bracket spacing of its source."""
    if not indexes:
        return "[]"
    inner = ", ".join(str(i) for i in indexes)
    return f"[ {inner} ]" if source.startswith("[ ") else f"[{inner}]"

def renumber(path, shift, report):
    """Rewrite the vector indexes of an errors file, return its new source."""
    with open(path) as f:
        text = f.read()
    edits = []
    for name, value, start, end in members(text):
        if name.startswith("#") or not isinstance(value, list):
            continue
        if not all(isinstance(i, int) and not isinstance(i, bool) for i in value):
            continue
        for i in value:
            if i not in shift:
                report.append(f"{path} [{name}]: dropped index {i}, vector removed")
        kept = [shift[i] for i in value if i in shift]
        if kept != value:
            edits.append((start, end, render(text[start:end], kept)))
    for start, end, new in reversed(edits):
        text = text[:start] + new + text[end:]
    return text if edits else None

def strip(vfile, report):
    """Remove the already generated vectors of one values file."""
    base = vfile[:-len(SUFFIX)]
    afile = f"{base}.auto.json"
    if not os.path.exists(afile):
        return None
    try:
        flags = auto_values(afile)
    except Exception as e:
        report.append(f"{afile}: unreadable, {e}")
        return None
    with open(vfile) as f:
        text = f.read()
    elems = elements(text)

    dropped, order, ordinal = set(), {}, 0
    for i, (value, start, end) in enumerate(elems):
        if not isinstance(value, list) or len(value) not in (2, 3):
            continue
        order[i] = ordinal
        ordinal += 1
        if len(value) == 3:
            continue
        k = key(value[1])
        if k not in flags:
            continue
        if flags[k] != value[0]:
            report.append(
                f"MISMATCH {vfile}[{order[i]}]: {k} "
                f"expects {json.dumps(value[0])}, auto says {json.dumps(flags[k])}")
            continue
        dropped.add(i)
        if VERBOSE:
            report.append(f"{vfile}[{order[i]}]: drop {text[start:end]}")

    if not dropped:
        return None

    comments = dead_comments(elems, dropped)
    shift, new = {}, 0
    for i in sorted(order):
        if i in dropped:
            continue
        shift[order[i]] = new
        new += 1

    efile = f"{base}.errors.json"
    errors = renumber(efile, shift, report) if os.path.exists(efile) else None
    return (splice(text, elems, dropped | comments),
            len(dropped), len(comments), efile, errors, new)

def main():
    files = collect(sys.argv[1:])
    report = []
    scanned = noauto = changed = vectors = comments = renumbered = emptied = 0

    for vfile in files:
        scanned += 1
        try:
            done = strip(vfile, report)
        except Exception as e:
            report.append(f"{vfile}: failed, {e}")
            continue
        if done is None:
            if not os.path.exists(f"{vfile[:-len(SUFFIX)]}.auto.json"):
                noauto += 1
            continue
        text, nvec, ncom, efile, errors, left = done
        changed += 1
        vectors += nvec
        comments += ncom
        suffix = f", {ncom} comment(s)" if ncom else ""
        if left == 0:
            emptied += 1
            suffix += ", now empty"
        print(f"{vfile}: -{nvec} vector(s){suffix}")
        if errors is not None:
            renumbered += 1
            print(f"{efile}: renumbered")
        if WRITE:
            with open(vfile, "w") as f:
                f.write(text)
            if errors is not None:
                with open(efile, "w") as f:
                    f.write(errors)

    for line in report:
        print(line, file=sys.stderr)

    print(f"# {scanned} values file(s), {noauto} without a generated auto file")
    print(f"# {changed} file(s) with {vectors} redundant vector(s) "
          f"and {comments} orphan comment(s), {renumbered} errors file(s) renumbered")
    if emptied:
        print(f"# {emptied} file(s) reduced to an empty vector list")
    if not WRITE and changed:
        print("# dry run, use -w to apply")

main()
PY
