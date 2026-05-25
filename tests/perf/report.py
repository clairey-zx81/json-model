#! /usr/bin/env python
#
# Generate a markdown report about a benchmark run
#

import sys
import argparse
import logging
import numpy as np
import pandas as pd
import warnings

# too many warning, uncomment to investigate
warnings.simplefilter(action='ignore', category=pd.errors.PerformanceWarning)

logging.basicConfig(level=logging.WARNING)
log = logging.getLogger("report")

# short column names
TOOL: dict[str, str] = {
    "blaze": "blaze",
    "jmc-c": "c",
    "jmc-js": "js",
    "jmc-java-gson": "jv1",
    "jmc-java-jackson": "jv2",
    "jmc-java-jsonp": "jv3",
    "jmc-py": "py",
    "jmc-pl": "pl",
}

# others are kept as-is
CASE: dict[str, str] = {
    "ansible-meta": "ansible",
    "clang-format": "clang-fmt",
    "cmake-presets": "cmake",
    "code-climate": "code-clim",
    "gitpod-configuration": "gitpod-cnf",
    "helm-chart-lock": "helm-chart",
    "pre-commit-hooks": "pre-ci",
    "semantic-release": "sem-rel",
    "ui5-manifest": "ui5-mfest",
    "unreal-engine-uproject": "unreal-ng",
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
- yamllint:{40,58,77,198,238,264,267,458,459,591,680,748,904,905,906,924,953,969} - unrelated raw strings

More values are rejected if formats are also checked, eg urls with are not urls.
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
- **changes**: number of source files changed
- **betters**: number of proven improved performance when _removing_ the optimization
- **sames**: number of similar performance
- **worses**: number of proven degraded performance (aka the optimization works!)
- **speed Δ**: percent performance impact of the optimization on speed
- **geo Δ**: percent performance impact of the optimization on performance geometrical average
- **summary**: symbolic evaluation
"""

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
    arg("--x2", type=str, default=None,
        help="perform a χ² analysis against this tool, default is none")
    arg("--alpha", type=float, default=0.05,
        help="alpha value for χ² test, default is 0.05")
    arg("--sort", default="bs", choices=["ab", "bs", "ls", "ga"],
        help="sort tools by criterion, default is \"bs\"")
    # verbosity control
    arg("--debug", dest="level", action="store_const", const=logging.DEBUG,
        default=logging.INFO, help="run in debug mode")
    arg("--quiet", dest="level", action="store_const", const=logging.WARNING,
        help="be quiet")
    # output
    arg("--standard", action="store_true",
        help="standard comparison report for \"json-model.org\" web site")
    arg("--hide", default=False, action="store_true",
        help="hide uneffective options from report")
    arg("--tools", nargs="*",
        help="restrict analysis to these tools, default is all available tools")
    arg("--unshift", action="store_true", default=False,
        help="unshift measure overhead estimation from reported measures")
    args = ap.parse_args()

    if args.hide and not args.x2:
        log.error("option --hide requires option --x2")
        sys.exit(0)

    log.setLevel(args.level)

    # get needed data
    log.info("loading data")

    resu_df = pd.read_csv(
        "result.csv",
        names=["case", "tool", "iter", "pass", "fail"],
        index_col=[0, 1]
    )

    # derive list of tools in "standard" order
    tools: list[str] = sorted(
        resu_df.index.get_level_values("tool").unique(),
        key=lambda n: "jmc-jas" if n == "jmc-js" else n
    )

    loaded_tools = tools
    if args.tools:
        # check availability and override, keeping the order
        assert set(args.tools) <= set(tools), f"expected tools are available ({tools})"
        assert len(set(args.tools)) == len(args.tools), "no tool repetition"
        tools = args.tools

    # provide some names for non standard reports
    for t in tools:
        if t not in TOOL:
            TOOL[t] = t

    if args.standard:
        assert tools == [
            "blaze", "jmc-c", "jmc-js",
            "jmc-java-gson", "jmc-java-jackson", "jmc-java-jsonp", "jmc-py"
        ], f"expect ordered standard benchmark tools ({tools})"

    # and list of cases
    cases: list[str] = sorted(
        resu_df.index.get_level_values("case").unique(),
        key=lambda n: "jmc-jas" if n == "jmc-js" else n
    )

    for c in cases:
        if c not in CASE:
            CASE[c] = c

    if args.standard:
        assert len(cases) == 37, f"check expected number of cases: {len(cases)}"

    # other data
    comp_df = pd.read_csv(
        "compile.csv",
        names=["case", "tool", "ran", "run"],
        index_col=[0, 1, 2]
    )
    case_df = pd.read_csv(
        "cases.csv",
        names=["case", "ssize", "nsize", "msize", "ntests"],
        index_col=[0]
    )
    vals_df = pd.read_csv(
        "casevalues.csv",
        names=["case", "line", "size", "lines"],
        index_col=[0, 1]
    )
    # very large
    perf_df = pd.read_csv(
        "perf.csv",
        names=["case", "tool", "iter", "line", "runavg", "runstd", "empty"],
        index_col=["case", "tool", "iter", "line"]
    )

    # remove unused values
    if loaded_tools != tools:
        log.info("removing unneeded data before analysis")
        for t in set(loaded_tools) - set(tools):
            for c in cases:
                perf_df.drop(index=(c, t), inplace=True)

    if args.unshift:
        perf_df["runavg"] += perf_df["empty"]

    log.info("analyzing data")

    # median performance for each case/tool/line
    perf_median = perf_df.groupby(["case", "tool", "line"])["runavg"].median()
    # total processing time for each case/tool
    perf_total = perf_median.groupby(["case", "tool"]).sum()
    # best performance for each case
    perf_best = perf_total.groupby("case").min()
    # relative time for each case/tool over all tests
    perf_rela = perf_total / perf_best
    # overall time for each tool over call cases and tests
    tool_perf = perf_total.groupby("tool").sum()

    # for each case, the best tool, and a count
    best_tool: dict[str, str] = {}
    nbest_tool: dict[str, int] = { t: 0 for t in tools }
    for c in cases:
        for t in tools:
            if perf_best[c] == perf_total[c, t]:
                best_tool[c] = t
                nbest_tool[t] += 1
                break

    perf_max = perf_rela.groupby("tool").max()
    # geometrical average over all cases
    perf_geo = np.exp(np.log(perf_rela).groupby("tool").mean())
    perf_min = perf_rela.groupby("tool").min()

    # compute speeds
    case_sizes = vals_df.groupby("case")["size"].sum()
    case_lines = vals_df.groupby("case")["lines"].sum()
    case_total_sizes = case_sizes.sum()
    case_total_lines = case_lines.sum()
    speed_size = case_total_sizes / tool_perf
    speed_lines = case_total_lines / tool_perf

    # results
    passed = resu_df.groupby(["case", "tool"])["pass"].min()
    failed = resu_df.groupby(["case", "tool"])["fail"].max()
    success_ratio = passed / (passed + failed)

    # for each tool, how many cases were failed
    # nfailed_tool: dict[str, int] = {
    #     t: sum(0 if success_ratio[c, t] == 1.0 else 1 for c in cases)
    #         for t in tools
    # }
    # print(case_df)
    # for each tool, how many cases ware not completed
    nerror_tool: dict[str, int] = {
        t: sum(1 if passed[c, t] + failed[c, t] != case_df.loc[c]["ntests"] else 0 for c in cases)
            for t in tools
    }

    if args.x2:

        assert args.x2 in tools, f"reference must be available: {args.x2}"

        srcs_df = pd.read_csv(
            "sources.csv",
            names=["file", "case", "tool", "lines", "bytes", "hash"],
            index_col=[1, 2]
        )

        # put worst first as it means that there is more effects
        FSORT = {
            "ab": lambda t: t,
            "bs": lambda t: speed_size[t],
            "ls": lambda t: speed_lines[t],
            "ga": lambda t: - perf_geo[t],
        }

        # move reference as first and sort other tools
        tools.remove(args.x2)
        tools = sorted(tools, key=FSORT[args.sort])
        tools.insert(0, args.x2)

        # tool -> [ list of hashes by case order ]
        tool_hashes = srcs_df.sort_values("case").groupby(["tool"])["hash"].apply(list)

        # only keep tools with an effect on some generated code
        if args.hide:
            assert tools[0] == args.x2
            ntools = tools[:1]
            for tool in tools[1:]:
                if tool_hashes[args.x2] != tool_hashes[tool]:
                    ntools.append(tool)
            if ntools != tools:
                log.info(f"hiding tools from report: {' '.join(sorted(set(tools) - set(ntools)))}")
            tools = ntools

    # data to be analyzed
    log.debug(f"tools = ({len(tools)}) {tools}")
    log.debug(f"cases = ({len(cases)}) {cases}")

    # generate markdown report
    log.info("generating report")
    print()
    print("## Tool Performance Summary")
    if args.standard: print(TOOL_SUMMARY, end="")

    print()
    print("|Summary|" + "|".join(TOOL[t] for t in tools) + "|")
    print("|:------|" + "".join("---:|" for t in tools))
    print("|best count|" + "".join(f"{nbest_tool[t]}|" for t in tools))
    if any(nerror_tool[t] != 0 for t in tools):
        print("|bad count|" + "".join(f"{nfailed_tool[t]}|" for t in tools))
    print("|speed B/µs|" + "".join(f"{speed_size[t]:.0f}|" for t in tools))
    print("|speed l/µs|" + "".join(f"{speed_lines[t]:.01f}|" for t in tools))
    print("|ratio max|" + "".join(f"{perf_max[t]:.02f}|" for t in tools))
    print("|ratio avg|" + "".join(f"{perf_geo[t]:.02f}|" for t in tools))
    print("|ratio min|" + "".join(f"{perf_min[t]:.02f}|" for t in tools))

    print()
    print("## Tool Performance Per Case")
    if args.standard: print(TOOL_CASES, end="")

    print()
    print("|#|name|cases|best µs| :1st_place_medal: |" + "|".join(TOOL[t] for t in tools) + "|")
    print("|---:|:------|---:|---:|:--:|" + "".join("---:|" for t in tools))
    for i, c in enumerate(cases):
        print(f"|{i+1}|{CASE[c]}|{case_df.loc[c]['ntests']}|"
              f"{perf_best[c]:.01f}|{TOOL[best_tool[c]]}|", end="")
        print("".join(f"{perf_rela[c, t]:.02f}|" for t in tools))

    if any(success_ratio[n, t] != 1.0 for t in tools for n in cases):

        print("\n## Result Success")

        if args.standard: print(RESULT_SUCCESS, end="")

        print()
        print("|#|name|" + "|".join(TOOL[t] for t in tools) + "|")
        print("|---:|:---|" + "".join("---:|" for t in tools))
        for i, c in enumerate(cases):
            if any(success_ratio[c, t] != 1.0 for t in tools):
                print(
                    f"|{i+1}|{CASE[c]}|" +
                    "".join(f"{100.0 * success_ratio[c, t]:.01f}|" for t in tools)
                )

        if args.standard: print(RESULT_COMMENT, end="")


    if args.standard:

        # compilation columns to display and associated labels
        comp_tool = {
            "blaze": "blaze",
            "jsu-model": "model",
            "jmc-c-out": "c",
            "jmc-js": "js",
            "jmc-java-class": "java",
            "jmc-py": "py",
        }

        print()
        print("## Compilation Times")

        if args.standard: print(COMP_CASES, end="")

        compilation = comp_df.groupby(["case", "tool"])["run"].median()
        comp_max = compilation.groupby("tool").max()
        comp_avg = compilation.groupby("tool").mean()
        comp_min = compilation.groupby("tool").min()

        print()
        print("|#|name|" + "".join(f"{comp_tool[t]}|" for t in comp_tool))
        print("|---:|:---|---:|---:|---:|---:|---:|---:|")
        print(f"|| _max_ |", "".join(f"{comp_max[t]:.01f}|" for t in comp_tool))
        print(f"|| _avg_ |", "".join(f"{comp_avg[t]:.01f}|" for t in comp_tool))
        print(f"|| _min_ |", "".join(f"{comp_min[t]:.01f}|" for t in comp_tool))

        for i, c in enumerate(cases):
            print(f"|{i+1}|{CASE[c]}|" +
                  "".join(f"{compilation[c,t]:.01f}|" for t in comp_tool))
    print()
    print("## Cases Data")
    if args.standard: print(CASE_DATA, end="")
    print()
    print(f"|#|name|schema|normal|model|nb|min (B)|avg (B)|max (B)|")
    print(f"|---:|:---|---:|---:|---:|---:|---:|---:|---:|")

    # aggregations
    sum_ss = case_df["ssize"].sum()
    sum_ns = case_df["nsize"].sum()
    sum_ms = case_df["msize"].sum()
    sum_nb = case_df["ntests"].sum()

    avg_ss = case_df["ssize"].mean()
    avg_ns = case_df["nsize"].mean()
    avg_ms = case_df["msize"].mean()
    avg_nb = case_df["ntests"].mean()

    min_vs = vals_df["size"].min()
    avg_vs = vals_df["size"].mean()
    max_vs = vals_df["size"].max()

    case_df["min"] = vals_df.groupby("case")["size"].min()
    case_df["avg"] = vals_df.groupby("case")["size"].mean()
    case_df["max"] = vals_df.groupby("case")["size"].max()

    print(f"|| _total_ | _{sum_ss}_ | _{sum_ns}_ | _{sum_ms}_ | _{sum_nb}_ ||||")
    print(f"|| _average_ | _{avg_ss:.0f}_ | _{avg_ns:.0f}_ | _{avg_ms:.0f}_ | _{avg_nb:.0f}_ ||||")
    # details
    for i, c in enumerate(cases):
        print(
            f"|{i+1}|{CASE[c]}|{case_df.loc[c]['ssize']:.0f}|"
            f"{case_df.loc[c]['nsize']:.0f}|{case_df.loc[c]['msize']:.0f}|{case_df.loc[c]['ntests']:.0f}|"
            f"{case_df.loc[c]['min']:.0f}|{case_df.loc[c]['avg']:.0f}|{case_df.loc[c]['max']:.0f}|"
        )
    print(f"|| _summary_ ||||| _{min_vs}_ | _{avg_vs:.0f}_ | _{max_vs}_ |")
    # force flush at end of main sections
    print(end="", flush=True)

    if args.x2:

        # NOTE this is quite slow
        log.info("testing statistical significance")

        titles = "".join(f"{TOOL[t]}|" for t in tools)
        print()
        print("## Tool Comparison")
        print()
        print(f"- **alpha:** {args.alpha} (p-value limit for statistical tests)")
        print()
        print("### Detailed Performance Impact")

        print(X2_DETAIL_COMMENT)

        print(f"|#|name|{titles}")
        print("|---:|:---|" + "".join(":---:|" for t in tools))

        from scipy.stats import chi2_contingency, barnard_exact

        # source to consider for a tool, default is identical
        tool_source = {
            "jmc-java-gson": "jmc-java",
            "jmc-java-jackson": "jmc-java",
            "jmc-java-jsonp": "jmc-java",
        }

        # how many changed source, improvements, nsame or worsening for a "tool"
        changes = { t: 0 for t in tools }
        betters = { t: 0 for t in tools }
        sames = { t: 0 for t in tools }
        worses = { t: 0 for t in tools }

        # cache matrix to whether it is independent
        INDEP: dict[str, bool] = {}

        # NOTE costly loop: over 35,000 tests for each tool
        for i, c in enumerate(cases):
            log.debug(f"considering {c} {i+1}/{len(cases)} ({case_df.loc[c]['ntests']} tests)")

            ref_runs = {
                line: runs.values
                    for line, runs in perf_df.loc[c, args.x2].groupby("line")["runavg"]
            }

            print(f"|{i+1}|{CASE[c]}|", end="")
            for tool in tools:
                # NOTE we compute a tool against itself for sanity checking
                # log.debug(f"name={name} tool={tool}")
                # if tool == args.x2:
                #     print("-|", end="")
                #     continue
                # same source was generated?
                try:
                    ref_src = tool_source.get(args.x2, args.x2)
                    cmp_src = tool_source.get(tool, tool)
                    src = "=" if (srcs_df.loc[c, ref_src] == srcs_df.loc[c, cmp_src]).all() else "!"
                except:
                    src = "?"
                if src == "!":
                    changes[tool] += 1

                # compute data
                cmp_runs = {
                    line: runs.values
                        for line, runs in perf_df.loc[c, tool].groupby("line")["runavg"]
                }

                # compare each test performance
                better, worse, same = 0, 0, 0
                for j in range(1, 1+int(case_df.loc[c]["ntests"])):

                    all_runs = pd.DataFrame(np.concatenate((ref_runs[j], cmp_runs[j])))

                    pivot = float(all_runs.median()[0])

                    ref_lower = (ref_runs[j] <= pivot).sum()
                    cmp_lower = (cmp_runs[j] <= pivot).sum()

                    matrix = [
                        [ ref_lower, len(ref_runs) - ref_lower ],
                        [ cmp_lower, len(cmp_runs) - cmp_lower ]
                    ]

                    matrix_key = str(matrix)

                    if matrix_key in INDEP:
                        pass
                    elif matrix[0] == matrix[1]:
                        # shortcut on identical rows
                        INDEP[matrix_key] = False
                    elif ref_lower in (0, len(ref_runs)) or cmp_lower in (0, len(cmp_runs)):
                        # Fisher? Barnard? Boschloo?
                        barnard_test = barnard_exact(matrix)
                        INDEP[matrix_key] = barnard_test.pvalue <= args.alpha
                    else:  # Chi2? same as previous?
                        chi2_test = chi2_contingency(matrix, correction=True)
                        INDEP[matrix_key] = chi2_test.pvalue <= args.alpha

                    # count confirmed better or worst or same than ref measures
                    if INDEP[matrix_key]
                        ref_perf = pd.DataFrame(ref_runs[j]).median()[0]
                        cmp_perf = pd.DataFrame(cmp_runs[j]).median()[0]
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
        print(f"| speed Δ |" +
              "".join(f"{100.0 * (speed_lines[args.x2] - speed_lines[t]) / speed_lines[t]:.01f}%|" for t in tools))
        print(f"| geo Δ |" +
              "".join(f"{100.0 * (perf_geo[t] / perf_geo[args.x2] - 1.0):.01f}%|" for t in tools))
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

        log.info("try: pandoc -s -o foo.html --title 'Great!' foo.md")

if __name__ == "__main__":
    report()
