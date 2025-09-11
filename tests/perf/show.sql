.print # cases statistics
SELECT COUNT(*) AS ncases, SUM(tests) AS ntests FROM Cases;

.print # tool performance per case
SELECT * FROM ShowPerfPerCase ORDER BY 1;

.print # tool performance summary
SELECT * FROM ShowPerfSummary ORDER BY 1;

.print # tool compile per case
SELECT * FROM ShowCompilePerCase ORDER BY 1;

.print # tool compile summary
SELECT * FROM ShowCompileSummary ORDER BY 1;

.print # result summary
SELECT * FROM ShowBadResults ORDER BY 1;
