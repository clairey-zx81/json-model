-- show results as markdown tables
-- .width only works for "box" mode

.print
.print ## Tool Performance Summary
.print
.print For each tool: number of best performance, number of case failures (if any), overall
.print validation speed in bytes per µs and lines per µs,
.print maximum/geometrical average/minimum performance ratio.
.print
.print <!-- LRRRRRRR -->
-- NOTE last column made larger to account for python slowness
.width 0 -5 -5 -5 -5 -5 -5 -6
SELECT summary, blaze, c, js, jv1, jv2, jv3, py
FROM ShowPerfSummary ORDER BY ordre;

.print
.print ## Tool Performance Per Case
.print
.print For each case: number and name, number of test cases, best cumulated median performance (µs),
.print best tool, performance slowdown ratio for blaze and jmc variants
.print (java 1 is gson, 2 is jackson, 3 is jsonp/johnzon),
.print the lower the better, **1.00** is best, empty denotes a tool failure.
.print
.print <!-- RLRRCRRRRRRR -->
.width -2 0 -5 -7 17 -6 -6 -6 -6 -6 -6 -6
SELECT * FROM ShowPerfPerCase ORDER BY 1;

.print
.print ## Result Success
.print
.print For each tool and cases with a partial success rate, percent of test cases validated.
.print
.print <!-- RLRRRRRRR -->
.width -2 0 -5 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowBadResults ORDER BY 1;
.print
-- ansible-meta[105]: ".depedencies" unexpected prop (fixed misplaced additionalProperties)
-- ansible-meta[201,312]: ".argument_spec" unexpected prop (idem)
-- cspell[75]: ".languageSettings[2].languageId[0]" is "yaml.ansible": unexpected . in fixed regex
-- cypress[8]: ".reporter" stricter check, file should end with ".js"; .baseUrl is not a URL;
-- yamllint[40,58,77,198,238,264,267,458,459,591,680,748,904,905,906,924,953,969]: raw strings
.print As of April 2026, the JMC results for `ansible-meta`, `cspell`, `cypress` and `yamllint`
.print are not 100.0% because validation checks are stricter and some
.print [values](https://github.com/sourcemeta-research/jsonschema-benchmark/pull/155)
.print are rightfully rejected.
.print More values are rejected if formats are also checked.
.print The `geoson` failure for Java/GSON is related to a corner case issue with GSON.

.print
.print ## Compilation Per Case
.print
.print For each tool and case, compilation time (including both schema to model
.print conversion and model compilation) in second.
.print
.print <!-- RLRRRRR -->
.width -2 0 -5 -5 -5 -5 -5
SELECT * FROM ShowCompilePerCase ORDER BY 1;

.print
.print ## Compilation Summary
.print
.print For each tool, average/max/min compilation time in seconds.
.print
.print <!-- LRRRRR -->
.width 0 -5 -5 -5 -5 -5
SELECT * FROM ShowCompileSummary ORDER BY 1;

.print
.print ## Cases Statistics
.print
.print For each case and a summary: the full schema, normalized schema and model sizes
.print (number of lines), number/min/average/max size of test values.
.print
.print <!-- RLRRRRRRR -->
.width -2, 0 -6, -6, -6, -5 -8 -8 -8
SELECT * FROM ShowCases ORDER BY 1;
