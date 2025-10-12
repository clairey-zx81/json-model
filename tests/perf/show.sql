-- show results as tables
-- .width only works for "box" mode

.print
.print ### cases statistics
.print
.print LRRRRRR
.width 0 -6, -6, -5 -8 -8 -8
SELECT * FROM ShowCases ORDER BY 1;

.print
.print ### tool performance per case
.print
.print RLRRRRRRRRR
.width -2 16 -5 -7 -6 -6 -6 -6 -6 -6 -6
SELECT * FROM ShowPerfPerCase ORDER BY 1;

.print
.print ### tool performance summary
.print
.print LRRRRRRR
.width 0 -5 -5 -5 -5 -5 -5 -5
SELECT summary, blaze, c, js, jv1, jv2, jv3, py
FROM ShowPerfSummary ORDER BY ordre;

.print
.print ### tool compile per case
.print
.print RLRRRRR
.width -2 16 -5 -5 -5 -5 -5
SELECT * FROM ShowCompilePerCase ORDER BY 1;

.print
.print ### tool compile summary
.print
.print LRRRRR
.width 0 -5 -5 -5 -5 -5
SELECT * FROM ShowCompileSummary ORDER BY 1;

.print
.print ### result summary
.print
.print RLRRRRRRR
.width -2 16 -5 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowBadResults ORDER BY 1;
