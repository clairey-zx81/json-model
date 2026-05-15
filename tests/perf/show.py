#! /usr/bin/env python
#
# Generate a markdown report about a benchmark run
#
# TODO consider pandas?

import argparse
import logging
import sqlite3

logging.basicConfig(level=logging.INFO)
log = logging.getLogger("show")

# very short column name
NAME: dict[str, str] = {
    "blaze": "blaze",
    "jmc-c": "c",
    "jmc-js": "js",
    "jmc-java-gson": "jv1",
    "jmc-java-jackson": "jv2",
    "jmc-java-jsonp": "jv3",
    "jmc-py": "py",
    "jmc-pl": "pl",
}

#
# standard section descriptions
#
TOOL_SUMMARY: str = """
For each tool: number of best performance, number of case failures (if any),
overall validation speed in bytes per µs and lines per µs,
maximum/geometrical average/minimum performance ratio.
"""

TOOL_CASES: str = """
For each case: number and name, number of test cases, best cumulated median performance (µs),
best tool, performance slowdown ratio for blaze and jmc variants
(java 1 is gson, 2 is jackson, 3 is jsonp/johnzon),
the lower the better, **1.00** is best, empty denotes a tool failure.
"""

RESULT_SUCCESS: str = """
For each tool and cases with a partial success rate, percent of test cases validated.
"""

RESULT_COMMENT: str = """
As of May 2026, the JMC results for `ansible-meta`, `cspell`, `cypress` and `yamllint`
are not 100.0% because validation checks are stricter and some
[values](https://github.com/sourcemeta-research/jsonschema-benchmark/pull/155)
are rightfully rejected.

- ansible-meta:105 - `.depedencies` (typo) unexpected prop (fixed misplaced `additionalProperties`)
- ansible-meta:{201,312} - `.argument_spec` unexpected prop (idem)
- cspell:75 - `.languageSettings[2].languageId[0]` is `yaml.ansible`, unexpected `.` in fixed regex
- cypress:8 - `.reporter` stricter check, file should end with `.js`
- yamllint:{40,58,77,198,238,264,267,458,459,591,680,748,904,905,906,924,953,969} - raw strings

More values are rejected if formats are also checked, eg urls with are not urls.
The `geoson` failure for Java/GSON is related to a corner case issue with GSON.
"""

COMP_CASES: str = """
For the 3 first lines, max/average/min compilation times in seconds,
then for each tool and case, compilation time (including both schema to model
conversion and model compilation) in second.
"""

CASE_DATA: str = """
For each case and a summary: the full schema, normalized schema and model sizes
(number of lines), number/min/average/max size of test values.
"""

def report():
    ap = argparse.ArgumentParser(description="Generate JMC benchmark report")
    arg = ap.add_argument
    # verbosity control
    arg("--debug", dest="level", action="store_const", const=logging.DEBUG, default=logging.INFO, help="run in debug mode")
    arg("--quiet", dest="level", action="store_const", const=logging.WARNING, help="be quiet")
    # output
    arg("--standard", action="store_true", help="Standard comparison report for web site")
    # input
    arg("database", nargs="?", default="perf.db", help="Use this SQLite database")
    args = ap.parse_args()

    log.setLevel(args.level)

    # get needed data
    conn = sqlite3.connect(args.database)

    tools: list[str] = sorted(
        (t[0] for t in conn.execute("SELECT tool FROM Tools")),
        key=lambda n: "jmc-jas" if n == "jmc-js" else n
    )
    log.debug(f"tools = {tools}")

    # provide some names for non standard reports
    for t in tools:
        if t not in NAME:
            NAME[t] = t

    if args.standard:
        assert tools == [
            "blaze", "jmc-c", "jmc-js",
            "jmc-java-gson", "jmc-java-jackson", "jmc-java-jsonp", "jmc-py"
        ], "expect standard benchmark tools"

    cases: list[str] = [
        t[0] for t in conn.execute("SELECT name FROM Cases ORDER BY 1")
    ]
    log.debug(f"cases = {cases}")

    if args.standard:
        assert len(cases) == 37, f"unexpected number of cases: {len(cases)}"

    case_data = {
        name: {"ss": ss, "ns": ns, "ms": ms, "nb": tests, "min": minsz, "avg": avgsz, "max": maxsz}
            for name, ss, ns, ms, tests, minsz, avgsz, maxsz in
                conn.execute("SELECT name, ssize, nsize, msize, tests, minsz, avgsz, maxsz FROM Cases")
    }

    summary = {
        tool: {"nb": nbest, "ko": nbroken, "bs": bspeed, "ls": lspeed, "max": rmax, "avg": ravg, "min": rmin}
            for tool, nbest, nbroken, bspeed, lspeed, rmax, ravg, rmin in 
                conn.execute("SELECT tool, nbest, nbroken, bspeed, lspeed, rmax, ravg, rmin FROM ToolSummaryPerf")
    }
    log.debug(f"summary = {summary}")

    best_perf = {
        name: {"run": run, "tool": tool}
            for name, run, tool in
                conn.execute("SELECT name, run, tool FROM CaseBestCumulatedPerf")
    }

    case_perf = {
        (name, tool): {"run": run, "rel": run / best_perf[name]["run"]}
            for name, tool, run in
                conn.execute("SELECT name, tool, run FROM CaseToolCumulatedPerf")
    }

    results = {
        (name, tool): {"rate": rate}
            for name, tool, rate in
                conn.execute("SELECT name, tool, rate FROM CaseToolResult")
    }

    compilation = {
        (name, tool): {"run": run}
            for name, tool, run in
                conn.execute("SELECT name, tool, run FROM CaseToolCompilePerf")
    }

    conn.close()

    # generate markdown report
    print("\n## Tool Performance Summary")
    if args.standard: print(TOOL_SUMMARY, end="")

    assert len(tools) == len(summary)
    print()
    print("|Summary|" + "|".join(NAME[t] for t in tools) + "|")
    print("|:------|" + "".join("---:|" for t in tools))
    print("|best count|" + "".join(f"{summary[t]['nb']}|" for t in tools))
    if any(summary[t]["ko"] != 0 for t in tools):
        print("|best count|" + "".join(f"{summary[t]['ko']}|" for t in tools))
    print("|speed B/µs|" + "".join(f"{summary[t]['bs']:.0f}|" for t in tools))
    print("|speed l/µs|" + "".join(f"{summary[t]['ls']:.01f}|" for t in tools))
    print("|ratio max|" + "".join(f"{summary[t]['max']:.02f}|" for t in tools))
    print("|ratio avg|" + "".join(f"{summary[t]['avg']:.02f}|" for t in tools))
    print("|ratio min|" + "".join(f"{summary[t]['min']:.02f}|" for t in tools))

    print("\n# Tool Performance Per Case")
    if args.standard: print(TOOL_CASES, end="")
    
    print()
    print("|#|name|cases|best µs| :1st_place_medal: |" + "|".join(NAME[t] for t in tools) + "|")
    print("|---:|:------|---:|---:|:--:|" + "".join("---:|" for t in tools))
    for i, name in enumerate(cases):
        print(f"|{i+1}|{name}|{case_data[name]['nb']}|"
              f"{best_perf[name]['run']:.01f}|{NAME[best_perf[name]['tool']]}|", end="")
        print("".join(f"{case_perf[(name,t)]['rel']:.02f}|" for t in tools))

    if any(results[(n, t)] != 1.0 for t in tools for n in cases):

        print("\n## Result Success")

        if args.standard: print(RESULT_SUCCESS, end="")

        print()
        print("|#|name|" + "|".join(NAME[t] for t in tools) + "|")
        print("|---:|:---|" + "".join("---:|" for t in tools))
        for i, name in enumerate(cases):
            if any(results[(name, t)]["rate"] != 1.0 for t in tools):
                print(
                    f"|{i+1}|{name}|" +
                    "".join(f"{100.0 * results[(name, t)]['rate']:.01f}|" for t in tools)
                )
                
        if args.standard: print(RESULT_COMMENT, end="")

    if args.standard:

        comp_tool = {
            "blaze": "blaze",
            "jsu-model": "model",
            "jmc-c-out": "c",
            "jmc-js": "js",
            "jmc-java-class": "java",
            "jmc-py": "py",
        }

        print("\n## Compilation Times")

        if args.standard: print(COMP_CASES, end="")

        print()
        print("|#|name|" + "".join(f"{comp_tool[t]}|" for t in comp_tool))
        print("|---:|:---|---:|---:|---:|---:|---:|---:|")
        print(f"|| _max_ |", end="") 
        for t in comp_tool:
            maxi = max(compilation[(n, t)]["run"] for n in cases)
            print(f"{maxi:.01f}|", end="")
        print()
        print(f"|| _avg_ |", end="") 
        for t in comp_tool:
            avg = sum(compilation[(n, t)]["run"] for n in cases) / len(cases)
            print(f"{avg:.01f}|", end="")
        print()
        print(f"|| _min_ |", end="") 
        for t in comp_tool:
            mini = min(compilation[(n, t)]["run"] for n in cases)
            print(f"{mini:.01f}|", end="")
        print()

        for i, name in enumerate(cases):
            print(f"|{i+1}|{name}|" +
                  "".join(f"{compilation[(name,t)]['run']:.01f}|" for t in comp_tool))

    print("\n## Cases Data")
    if args.standard: print(CASE_DATA, end="")
    print()
    print(f"|#|name|schema|normal|model|nb|min (B)|avg (B)|max (B)|")
    print(f"|---:|:---|---:|---:|---:|---:|---:|---:|---:|")
    print(f"|||{sum(case_data[name]['ss'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['ns'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['ms'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['nb'] for name in cases)}|"
          f"{min(case_data[name]['min'] for name in cases)}|"
          f"{sum(case_data[name]['avg'] for name in cases)/len(cases):.0f}|"
          f"{max(case_data[name]['max'] for name in cases)}|"
    )
    # TODO aggreg
    for i, name in enumerate(cases):
        print(
            f"|{i+1}|{name}|{case_data[name]['ss']}|"
            f"{case_data[name]['ns']}|{case_data[name]['ms']}|{case_data[name]['nb']}|"
            f"{case_data[name]['min']}|{case_data[name]['avg']:.0f}|{case_data[name]['max']}|"
        )

if __name__ == "__main__":
    report()
