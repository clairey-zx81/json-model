-- show results as tables
-- .width only works for "box" mode

.print
.print ## Tool Performance Summary
.print
.print For each tool: number of best performance, number of case failures (if any), overall
.print validation speed in bytes per µs, maximum/geometrical average/minimum performance ratio.
.print
.print <!-- LRRRRRRR -->
.width 0 -5 -5 -5 -5 -5 -5 -5
SELECT summary, blaze, c, js, jv1, jv2, jv3, py
FROM ShowPerfSummary ORDER BY ordre;

.print
.print ## Tool Performance Per Case
.print
.print For each case: number and name, number of test cases, best cumulated median performance (µs),
.print best tool, performance slowdown ratio for blaze and jmc variants (java 1 is gson, 2 is jackson,
.print 3 is jsonp/johnzon), the lower the better, **1.00** is best, empty denotes a tool failure.
.print
.print <!-- RLRRCRRRRRRR -->
.width -2 16 -5 -7 17 -6 -6 -6 -6 -6 -6 -6
SELECT * FROM ShowPerfPerCase ORDER BY 1;

.print
.print ## Result Success
.print
.print For each tool and cases with a partial success rate, percent of test cases validated.
.print
.print <!-- RLRRRRRRR -->
.width -2 16 -5 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowBadResults ORDER BY 1;
.print
.print As of November 2025, the JMC results for `ansible-meta`, `cypress` and `yamllint` are
.print not 100.0% because validation checks are stricter and some
.print [malformed values](https://github.com/sourcemeta-research/jsonschema-benchmark/pull/155)
.print are rightfully rejected.
.print The `geoson` failure for Java/GSON is related to a corner case issue with GSON.

.print
.print ## Compilation Per Case
.print
.print For each tool and case, compilation time (including both schema to model
.print conversion and model compilation) in second.
.print
.print <!-- RLRRRRR -->
.width -2 16 -5 -5 -5 -5 -5
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
.print For each case and a summary: the schema and model sizes (number of lines, model size 1
.print denotes a reference to a predefined model), number/min/average/max size of test values.
.print
.print <!-- RLRRRRRR -->
.width -2, 0 -6, -6, -5 -8 -8 -8
SELECT * FROM ShowCases ORDER BY 1;
