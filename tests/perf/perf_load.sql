--
-- LOAD
--

-- load raw data from generated files
.mode csv
.import perf.csv RawRun
.import compile.csv RawCompile
.import result.csv RawResult
.import cases.csv Cases
.import casevalues.csv CaseValues
