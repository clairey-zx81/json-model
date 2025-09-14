.print # cases statistics
SELECT COUNT(*) AS ncases, SUM(tests) AS ntests FROM Cases;

.print # tool performance per case
.width -2 16 -5 -7 -6 -6 -6 -6 -6 -6 -6
SELECT * FROM ShowPerfPerCase ORDER BY 1;

.print # tool performance summary
.width 0 -5 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowPerfSummary ORDER BY 1;

.print # tool compile per case
.width -2 16 -5 -5 -5 -5 -5
SELECT * FROM ShowCompilePerCase ORDER BY 1;

.print # tool compile summary
.width 0 -5 -5 -5 -5 -5
SELECT * FROM ShowCompileSummary ORDER BY 1;

.print # result summary
.width -2 16 -5 -5 -5 -5 -5 -5 -5
SELECT * FROM ShowBadResults ORDER BY 1;
