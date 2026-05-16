#! /usr/bin/env python
#
# Generate a markdown report about a benchmark run
#
# TODO consider pandas?

import sys
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

X2_DETAIL_COMMENT: str = """
For each case and tool, the impact on the source and performance on all tests.

- `=` if generated source is the same, `!` if it differs.
- _b/e/w_ when the optimization is **removed**,
  number of proven improved, similar (unproven) or proven degraded performance.
  Use _0_ if there is no proven improvement nor degradation on any test.
"""

X2_SUMMARY_COMMENT: str = """
- **changes**: number of source file changed
- **betters**: number of proven improved performance when _removing_ the optimization
- **sames**: number of similar performance
- **worses**: number of proven degraded performance (aka the optimization works!)
- **delta**: percent performance impact of the optimization
- **summary**: symbolic evaluation
"""

def median(data: list[float]) -> float:
    sdata, middle = sorted(data), len(data) // 2
    if len(data) % 2 == 1:
        return sdata[middle]
    else:
        return 0.5 * (sdata[middle-1] + sdata[middle])

assert median([0.0, 10.0, 15.0]) == 10.0
assert median([0.0, 10.0, 15.0, 0.0, 10.0, 15.0]) == 10.0
assert median([0.0, 10.0, 20.0, 21.0]) == 15.0

def nlower(pivot: float, data: list[float]) -> int:
    n = 0
    for v in data:
        if v <= pivot:
            n += 1
    return n

def report():
    ap = argparse.ArgumentParser(description="Generate JMC benchmark report")
    arg = ap.add_argument
    # analysis
    arg("--x2", type=str, default=None, help="perform a χ² analysis against this tool")
    arg("--alpha", type=float, default=0.05, help="alpha value for χ² test, default is 0.05")
    arg("--sort", default="bs", choices=["ab", "bs", "ls", "geo"], help="sort tools by criterion")
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
    log.info("loading data")
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
        ], "expect ordered standard benchmark tools"

    cases: list[str] = [
        t[0] for t in conn.execute("SELECT name FROM Cases ORDER BY 1")
    ]
    log.debug(f"cases = {cases}")

    if args.standard:
        assert len(cases) == 37, f"check expected number of cases: {len(cases)}"

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
    # log.debug(f"summary = {summary}")

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

    if args.x2:
        assert args.x2 in tools, f"reference must be available: {args.x2}"

        # put worst first as it means that there is more effects
        FSORT = {
            "ab": lambda t: t,
            "bs": lambda t: summary[t]["bs"],
            "ls": lambda t: summary[t]["ls"],
            "geo": lambda t: -summary[t]["avg"],
        }

        # move reference as first and sort other tools
        tools.remove(args.x2)
        tools = sorted(tools, key=FSORT[args.sort])
        tools.insert(0, args.x2)

        # (name X tool) -> line-1 -> [ runs ]
        runs: dict[tuple[str, str], list[list[float]]] = {
            (name, tool): [ [] for i in range(case_data[name]["nb"]) ]
                for name in cases
                    for tool in tools
        }

        for name, tool, line, run in conn.execute("SELECT name, tool, line, runavg FROM RawRun ORDER BY 1, 2, 3, 4"):
            runs[(name, tool)][line-1].append(run)

        files: dict[tuple[str, str], str] = {
            (name, tool): fhash
                for name, tool, fhash in conn.execute("SELECT name, tool, hash FROM Files")
        }

    conn.close()

    # generate markdown report
    log.info("generating report")
    print("\n## Tool Performance Summary")
    if args.standard: print(TOOL_SUMMARY, end="")

    assert len(tools) == len(summary)
    print()
    print("|Summary|" + "|".join(NAME[t] for t in tools) + "|")
    print("|:------|" + "".join("---:|" for t in tools))
    print("|best count|" + "".join(f"{summary[t]['nb']}|" for t in tools))
    if any(summary[t]["ko"] != 0 for t in tools):
        print("|bad count|" + "".join(f"{summary[t]['ko']}|" for t in tools))
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
    # aggregations
    print(f"|||{sum(case_data[name]['ss'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['ns'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['ms'] for name in cases)/len(cases):.0f}|"
          f"{sum(case_data[name]['nb'] for name in cases)}|"
          f"{min(case_data[name]['min'] for name in cases)}|"
          f"{sum(case_data[name]['avg'] for name in cases)/len(cases):.0f}|"
          f"{max(case_data[name]['max'] for name in cases)}|"
    )
    # details
    for i, name in enumerate(cases):
        print(
            f"|{i+1}|{name}|{case_data[name]['ss']}|"
            f"{case_data[name]['ns']}|{case_data[name]['ms']}|{case_data[name]['nb']}|"
            f"{case_data[name]['min']}|{case_data[name]['avg']:.0f}|{case_data[name]['max']}|"
        )
    # force flush at end of main sections
    print(end="", flush=True)

    if args.x2:
        # NOTE this is quite slow
        log.info("testing with chi-square")
        print("\n## Tool Comparison Per Case χ² Test")
        from scipy.stats import chi2_contingency

        print()
        print(f"- **alpha:** {args.alpha} (χ² test)")
        print()
        print("### Detailed Performance Impact")
        print(X2_DETAIL_COMMENT)
        titles = "".join(f"{NAME[t]}|" for t in tools)
        print(f"|#|name|{titles}")
        print("|---:|:---|" + "".join(":---:|" for t in tools))

        # how many changed source, improvements, nsame or worsening for a "tool"
        changes = { t: 0 for t in tools }
        betters = { t: 0 for t in tools }
        sames = { t: 0 for t in tools }
        worses = { t: 0 for t in tools }

        # NOTE costly loop: over 35,000 tests for each tool
        for i, name in enumerate(cases):
            log.debug(f"considering {name} {i+1}/{len(cases)}")
            print(f"|{i+1}|{name}|", end="")
            for tool in tools:
                # NOTE we compute a tool against itself for sanity checking
                # log.debug(f"name={name} tool={tool}")
                # if tool == args.x2:
                #     print("-|", end="")
                #     continue
                # same source was generated?
                src = "=" if files[(name, args.x2)] == files[(name, tool)] else "!"
                if src == "!":
                    changes[tool] += 1
                # compare each test performance
                better, worse, same = 0, 0, 0
                for j in range(case_data[name]["nb"]):  # beware, shifted
                    ref_runs, cmp_runs = runs[(name, args.x2)][j], runs[(name, tool)][j]
                    ref_perf, cmp_perf = median(ref_runs), median(cmp_runs)
                    # log.debug(f"{args.x2} {j} runs {ref_perf} {sorted(ref_runs)}")
                    # log.debug(f"{tool} {j} runs {cmp_perf} {sorted(cmp_runs)}")
                    # is the delta significant?
                    pivot = median(ref_runs + cmp_runs)
                    # log.debug(f"pivot {j}: {pivot}")
                    ref_lower, cmp_lower = nlower(pivot, ref_runs), nlower(pivot, cmp_runs)
                    matrix = [
                        [ ref_lower, len(ref_runs) - ref_lower ],
                        [ cmp_lower, len(cmp_runs) - cmp_lower ]
                    ]
                    chi2_test = chi2_contingency(matrix, correction=True)
                    # log.debug(f"matrix[{j}] = {matrix} chi2={chi2_test} alpha={args.alpha}")
                    indep = chi2_test.pvalue <= args.alpha
                    # count confirmed better or worst or same than ref measures
                    if indep:
                        if ref_perf < cmp_perf:
                            worse += 1
                        else:
                            better += 1
                    else:
                        same += 1
                if better + worse == 0:
                    result = f"{src} 0"
                else:
                    # NOTE showing same is not very useful
                    result = f"{src} {better}/{same}/{worse}"
                print(f"{result}|", end="")
                assert args.x2 != tool or (src == "=" and better == 0 and worse == 0)
                betters[tool] += better
                sames[tool] += same
                worses[tool] += worse
            # flush on each line, which is quite slow to produce
            print(flush=True)

        # summary counts below details
        print()
        print("### Summary Performance Impact")
        print(X2_SUMMARY_COMMENT)
        print(f"|data|{titles}")
        print("|:---|" + "".join("---:|" for t in tools))
        print(f"| changes |" + "".join(f"{changes[t]}|" for t in tools))
        print(f"| betters |" + "".join(f"{betters[t]}|" for t in tools))
        print(f"| sames |" + "".join(f"{sames[t]}|" for t in tools))
        print(f"| worses |" + "".join(f"{worses[t]}|" for t in tools))
        # show relative speed delta (inverted because the feature is removed in the test)
        print(f"| delta |" +
              "".join(f"{100.0 * (summary[args.x2]['ls'] - summary[t]['ls']) / summary[t]['ls']:.01f}%|" for t in tools))
        # effectiveness summary
        print(f"|**summary**|", end="")
        for t in tools:
            if t == args.x2:
                summary = "="
            else:
                ntests = sames[t] + betters[t] + worses[t]
                thresholds = [f * ntests for f in [0.01, 0.02, 0.04, 0.08, 0.16, 1.0]]
                deltat = worses[t] - betters[t]
                sign = "+" if deltat > 0 else "-"
                for delta, threshold in enumerate(thresholds):
                    if abs(deltat) <= threshold:
                        break
                summary = (sign * delta) if delta else "~"
            print(summary + "|", end="")
        print(flush=True)

if __name__ == "__main__":
    report()
