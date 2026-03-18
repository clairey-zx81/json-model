#! /usr/bin/env python
#
# output stats about a jsonl file in CSV
#

import sys
import json

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} name file.jsonl")
    sys.exit(1)

name, file = sys.argv[1:3]

def not_closure(s: str) -> bool:
    """Whether the line is not the closure of a json structural element."""
    close = s[-2] if s[-1] == "," else s[-1]
    return close not in ("]", "}")

def jsonlines(j) -> int:
    """Count non-trivial lines in a JSON value."""
    return len(list(filter(not_closure, json.dumps(j, indent=2).split("\n"))))

with open(file) as jf:
    for n, line in enumerate(jf):
        size = len(line)  # bytes
        lines = jsonlines(json.loads(line))  # non-trivial lines
        print(f"{name},{n+1},{size},{lines}") 
