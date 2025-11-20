-- show results as tables
-- .width only works for "box" mode

.print
.print ## Tool Performance Summary
.print
.print For each tool: number of best performance, number of case failures, overall
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
.print 3 is jsonp/johnzon), the lower the better, **1.0** is best, empty denotes a tool failure.
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
.print ## Compilation Per Case
.print
.print For each tool and case, compilation time in second.
.print Tool `s2m` is initial schema-to-model conversion.
.print
.print <!-- RLRRRRRR -->
.width -2 16 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowCompilePerCase ORDER BY 1;

.print
.print ## Compilation Summary
.print
.print For each tool, average/max/min compilation time in seconds.
.print Tool `s2m` is initial schema-to-model conversion.
.print
.print <!-- LRRRRRR -->
.width 0 -5 -5 -5 -5 -5 -5
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
