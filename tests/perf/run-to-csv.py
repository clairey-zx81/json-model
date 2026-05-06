#! /usr/bin/env python
#
# extract result figures from run outputs
#

import sys
import re

for file in sys.argv[1:]:
    assert file.endswith(".out")
    name = file.split("/")[-1][:-4].replace("_", ",")
    num = int(re.match(r".*/([0-9]+)/", file).group(1))
    npass, nfail = 0, 0
    with open(file) as f:
        for line in f:
            # /workspace/jsb/schemas/ansible-meta/instances.jsonl[236]: PASS 0.090 +- 0.007 us (0.017)
            # jsb/schemas/ansible-meta/instances.jsonl[1] nop PASS 0.322 ± 0.233 µs/check (0.021)
            matched = re.match(r"^.*/instances.jsonl\[(\d+)].*(?:PASS|FAIL) ([.0-9]+) [^ ]+ ([.0-9]+) [^ ]+ \(([.0-9]+)\)", line)
            if matched:
                g = matched.group
                print(f"{name},{num},{g(1)},{g(2)},{g(3)},{g(4)}")
            else:
                print(f"ERROR: {line}", file=sys.stderr)
                # sys.exit(1)
