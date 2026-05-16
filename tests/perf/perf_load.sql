--
-- LOAD
--

-- load raw data from benchmark generated files
.mode csv
.import perf.csv RawRun
.import compile.csv RawCompile
.import result.csv RawResult
.import casevalues.csv CaseValues
.import sources.csv Files

-- intermediate table to avoid warnings because of missing columns
CREATE TEMPORARY TABLE CasesTmp(
  name TEXT PRIMARY KEY,
  ssize INT NOT NULL,
  nsize INT NOT NULL,
  msize INT NOT NULL,
  tests INT NOT NULL
);

.import cases.csv CasesTmp

INSERT INTO Cases(name, ssize, nsize, msize, tests)
  SELECT * FROM CasesTmp
;

DROP TABLE CasesTmp;

.print loaded:
SELECT COUNT(*) AS "# run" FROM RawRun;
SELECT COUNT(*) AS "# compile" FROM RawCompile;
SELECT COUNT(*) AS "# result" FROM RawResult;
SELECT COUNT(*) AS "# cases" FROM Cases;
SELECT COUNT(*) AS "# tests" FROM CaseValues;
SELECT COUNT(*) AS "# files" FROM Files;
