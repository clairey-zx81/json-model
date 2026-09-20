#! /usr/bin/env python
#
# Performance Radar
#

import sys
import json
import numpy as np
import pandas as pd
import logging

logging.basicConfig()
log = logging.getLogger("radar")
log.setLevel(logging.INFO)

perf = pd.read_csv(
    sys.argv[1] if len(sys.argv) > 1 else "perf.csv",
    names=["case", "tool", "iter", "line", "runavg", "runstd", "empty", "pass"],
    index_col=["case", "tool", "iter", "line"]
)

tools = sorted(perf.index.get_level_values("tool").unique())
cases = sorted(perf.index.get_level_values("case").unique())

# ensure a consistent ordering? The default is ab, which suit us
# tools_order = { k: i for i, k in enumerate(tools) }
# perf = perf.sort_index(level="tool", key=lambda idx: idx.map(tools_order))
# cases_order = { k: i for i, k in enumerate(cases) }
# perf = perf.sort_index(level="case", key=lambda idx: idx.map(cases_order))

# compute performance
perf_median = perf.groupby(["case", "tool", "line"])["runavg"].median()
perf_total = perf_median.groupby(["case", "tool"]).sum()
perf_best = perf_total.groupby("case").min()
perf_speed = perf_best / perf_total  # relative speed

# cleanup missings
missings: set[tuple[str, str]] = set()
for c in cases:
    for t in tools:
        try:
            _ = perf_speed[c, t]
        except KeyError:
            missings.add((c, t))
            perf_speed[c, t] = 0.0

if missings:
    log.info(f"missings: {missings}")

# TODO bad results

perf_geo = np.exp(- np.log(perf_speed).groupby("tool").mean())

LABEL = {
    "blaze": "Blaze CLI C++",
    "ajv": "AJV CLI JS",
    "jmc-c": "JMC C",
    "jmc-java-gson": "JMC Java GSON",
    "jmc-java-jackson": "JMC Java Jackson",
    "jmc-java-jsonp": "JMC Java JSONP/Johnzon",
    "jmc-js": "JMC JS",
    "jmc-py": "JMC Python",
    "jmc-pl": "JMC Perl",
}

perf_per_tool = perf_speed.groupby("tool")

radar = []
for t in sorted(tools):
    radar.append({
        "label": LABEL[t],
        "speed": perf_geo["blaze"] / perf_geo[t],
        "data": [ float(v) for v in perf_per_tool.get_group(t).values ]
    })

print(json.dumps({"labels": cases, "datasets": radar}, indent=2))
