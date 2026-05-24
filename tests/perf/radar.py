#! /usr/bin/env python
#
# Performance Radar
#

import sys
import json
import pandas as pd

perf = pd.read_csv(
    sys.argv[1] if len(sys.argv) > 1 else "perf.csv",
    names=["case", "tool", "iter", "line", "runavg", "runstd", "empty"],
    index_col=["case", "tool", "iter", "line"]
)

perf_median = perf.groupby(["case", "tool", "line"])["runavg"].median()
perf_total = perf_median.groupby(["case", "tool"]).sum()
perf_best = perf_total.groupby("case").min()
perf_speed = perf_best / perf_total

tools = perf.index.get_level_values("tool").unique()
# cases = perf.index.get_level_values("case").unique()

LABEL = {
    "blaze": "Blaze CLI",
    "jmc-c": "JMC C",
    "jmc-java-gson": "JMC Java GSON",
    "jmc-java-jackson": "JMC Java Jackson",
    "jmc-java-jsonp": "JMC Java JSONP/Johnzon",
    "jmc-js": "JMC JS",
    "jmc-py": "JMC Python",
    "jmc-pl": "JMC Perl",
}

radar = []
for t in sorted(tools, key=lambda t: "jmc-jas" if t == "jmc-js" else t):
    radar.append({
        "label": LABEL[t],
        "data": [ float(v) for v in perf_speed.groupby("tool").get_group(t).values ]
    })

print(json.dumps(radar, indent=2))
