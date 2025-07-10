#! /usr/bin/env python

import sys
import json
import csv

with open(sys.argv[1]) as f:
    values = json.load(f)

#print(f"values = {values}")
def tojson(v):
    return json.dumps(v, separators=(",", ":"))

out = []
for v in values:
    if isinstance(v, str):
        continue
    assert isinstance(v, list)
    if len(v) == 2:
        out.append((v[0], '', tojson(v[1])))
    else:
        out.append((v[0], v[1], tojson(v[2])))

with open(sys.argv[2], "w") as f:
    csvw = csv.writer(f)
    for row in out:
        csvw.writerow(row)
