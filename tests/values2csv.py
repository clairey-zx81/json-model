#! /usr/bin/env python

import sys
import json
import csv

type Json = None|bool|int|float|list[Json]|dict[str, Json]

if len(sys.argv) >= 2 and sys.argv[1] != "-":
    with open(sys.argv[1]) as f:
        values = json.load(f)
else:
    values = json.load(sys.stdin)

def tojson(v: Json):
    """Convert value to a JSON string."""
    return json.dumps(v, separators=(",", ":"))

out = []
for v in values:
    if isinstance(v, str):
        continue
    assert isinstance(v, list)
    if len(v) == 2:
        out.append((v[0], "", tojson(v[1])))
    else:
        out.append((v[0], v[1], tojson(v[2])))

if len(sys.argv) >= 3 and sys.argv[2] != "-":
    fout = open(sys.argv[2], "w")
else:
    fout = sys.stdout

csvw = csv.writer(fout)
for row in out:
    csvw.writerow(row)

fout.close()
