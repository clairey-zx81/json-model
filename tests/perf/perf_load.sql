--
-- LOAD
--

-- load raw data from benchmark generated files
.mode csv
.import perf.csv RawRun
.import compile.csv RawCompile
.import result.csv RawResult
.import cases.csv Cases
.import casevalues.csv CaseValues

.print loaded:
SELECT COUNT(*) AS "# run" FROM RawRun;
SELECT COUNT(*) AS "# compile" FROM RawCompile;
SELECT COUNT(*) AS "# result" FROM RawResult;
SELECT COUNT(*) AS "# cases" FROM Cases;
SELECT COUNT(*) AS "# tests" FROM CaseValues;
