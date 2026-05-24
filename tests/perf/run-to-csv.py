#! /usr/bin/env python
#
# extract result figures from run outputs
#

import sys
import re

# /workspace/jsb/schemas/ansible-meta/instances.jsonl[236]: PASS 0.090 +- 0.007 us (0.017)
# jsb/schemas/ansible-meta/instances.jsonl[1] nop PASS 0.322 ± 0.233 µs/check (0.021)
PERF_RE = r"^.*/instances.jsonl\[(\d+)].*(?:PASS|FAIL) ([.0-9]+) [^ ]+ ([.0-9]+) [^ ]+ \(([.0-9]+)\)"
perf_match = re.compile(PERF_RE).match

ITER_RE = r".*/([0-9]+)/"
iter_match = re.compile(ITER_RE).match

def get_iter(s: str) -> int:
    return int(iter_match(s).group(1))

for file in sys.argv[1:]:
    assert file.endswith(".out"), f"expecting output file: {file}"
    name = file.split("/")[-1][:-4].replace("_", ",").lower()
    num = get_iter(file)
    npass, nfail = 0, 0
    with open(file) as f:
        for line in f:
            if matched := perf_match(line):
                g = matched.group
                linenb, avg, std, empty = int(g(1)), float(g(2)), float(g(3)), float(g(4))
                print(f"{name},{num},{linenb},{avg},{std},{empty}")
            else:
                print(f"ERROR: {line}", file=sys.stderr)
