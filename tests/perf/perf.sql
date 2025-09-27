--
-- Performance summary queries
--

CREATE TABLE Run(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  line INTEGER NOT NULL,         -- test value line
  runavg DOUBLE NOT NULL,        -- average run time
  runstd DOUBLE NOT NULL,        -- standard deviation time
  empty DOUBLE NOT NULL,         -- estimated measure overhead
  PRIMARY KEY(name, tool, line)
);

CREATE TABLE Compile(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  ran TIMESTAMP NOT NULL,        -- compilation timestamp
  run DOUBLE NOT NULL,           -- compilation time
  PRIMARY KEY(name, tool, ran)
);

CREATE TABLE Result(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  pass INT NOT NULL,             -- number of passes
  fail INT NOT NULL,             -- number of fails
  PRIMARY KEY(name, tool)
);

CREATE TABLE Cases(
  name TEXT PRIMARY KEY,         -- test name
  ssize INT NOT NULL,            -- schema lines
  msize INT NOT NULL,            -- model lines
  tests INT NOT NULL             -- number of test values in test
);

CREATE TABLE CaseValues(
  name TEXT NOT NULL,            -- test name
  line INT NOT NULL,             -- value line number
  vsize INT NOT NULL,            -- value size in bytes
  PRIMARY KEY (name, line)
);

-- load raw data
.mode csv
.import perf.csv Run
.import compile.csv Compile
.import result.csv Result
.import cases.csv Cases
.import casevalues.csv CaseValues

-- shorten some names
UPDATE Run SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Compile SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Result SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Cases SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Run SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Compile SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Result SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Cases SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';

-- tools
CREATE TABLE Tools(tool TEXT PRIMARY KEY);
INSERT INTO Tools(tool)
  SELECT DISTINCT tool FROM Run ORDER BY 1;

-- all results
CREATE TABLE ResultRate AS
  SELECT
    c.name,
    t.tool,
    1.0 * COALESCE(r.pass + r.fail, 0.0) / c.tests AS executed,
    100.0 * COALESCE(r.pass, 0) / c.tests AS rate,
    NULL AS pc
  FROM Cases AS c
  CROSS JOIN Tools AS t
  LEFT JOIN Result AS r ON (c.name = r.name AND t.tool = r.tool);

-- show simple pc
UPDATE ResultRate
  SET pc = REPLACE(TRUNC(rate), '.0', '');

-- cumulated perf per case/tool
CREATE TABLE CumulatedPerf AS
  SELECT name, tool,
    SUM(runavg) AS run,
    ROUND(AVG(runstd/runavg), 3) AS spread,
    ROUND(AVG(empty), 3) AS empty,
    COUNT(*) AS nb
  FROM Run
  GROUP BY 1, 2
  ORDER BY 1, 2;

-- scratch measure if not all cases were executed
UPDATE CumulatedPerf AS cp
  SET run = NULL, spread = NULL, empty = NULL
  FROM ResultRate AS rr
  WHERE cp.name = rr.name AND cp.tool = rr.tool AND rr.executed <> 1.0;

-- but do not allow zero
UPDATE CumulatedPerf SET run = NULL WHERE run = 0.0;

-- per case time
CREATE TABLE Comparison AS
  SELECT
    c.name AS name,
    tests AS cases,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'blaze' and cp.name = c.name) AS blaze,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-c' and cp.name = c.name) AS c,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-js' and cp.name = c.name) AS js,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-gson' and cp.name = c.name) AS jv1,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-jackson' and cp.name = c.name) AS jv2,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-jsonp' and cp.name = c.name) AS jv3,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-py' and cp.name = c.name) AS py,
    -- (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-pl' and cp.name = c.name) AS pl,
    NULL AS best
  FROM Cases AS c
  ORDER BY 1;

UPDATE Comparison
  SET best = MIN(COALESCE(blaze, 1e999),
       	         COALESCE(c, 1e999),
       	         COALESCE(js, 1e999),
       	         COALESCE(jv1, 1e999),
       	         COALESCE(jv2, 1e999),
       	         COALESCE(jv3, 1e999),
       	         -- COALESCE(pl, 1e999),
       	         COALESCE(py, 1e999));

-- execution time relative to the fastest, the lower the better
CREATE TABLE RelativeComparison AS
  SELECT
    name,
    cases,
    best,
    blaze / best AS blaze,
    c / best AS c,
    js / best AS js,
    jv1 / best AS jv1,
    jv2 / best AS jv2,
    jv3 / best AS jv3,
    py / best AS py
  FROM Comparison;

-- compilation aggregation
CREATE TABLE CompilePerf AS
  SELECT name, tool, AVG(run) AS run, COUNT(*) AS nb
  FROM Compile
  GROUP BY 1, 2;

-- compilation time per cases
CREATE TABLE CompilePerfCase AS
  SELECT
    c.name,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'blaze') AS blaze,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jsu-simpler') AS jsu_s,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jsu-model') AS jsu_m,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-c-src') AS jmc_c,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-c-out') AS jmc_out,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-js') AS jmc_js,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-py') AS jmc_py,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-java-src') AS jmc_java,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'jmc-java-class') AS jmc_class
  FROM Cases AS c;

-- compilation time useful comparison
CREATE TABLE CompilePerfCompare AS
  SELECT
    name,
    blaze,
    jsu_s + jsu_m + jmc_out AS c,
    jsu_s + jsu_m + jmc_js AS js,
    jsu_s + jsu_m + jmc_py AS py,
    jsu_s + jsu_m + jmc_class AS jv
  FROM CompilePerfCase;

-- result summary
CREATE TABLE ResultComparison AS
  SELECT
    RANK() OVER (ORDER BY name) AS nb,
    c.name AS name,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'blaze') AS blaze,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-c') AS c,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-js') AS js,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-gson') AS jv1,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jackson') AS jv2,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jsonp') AS jv3,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-py') AS py
  FROM Cases AS c
  ORDER BY 1;

-- case stats
CREATE TABLE ShowCases AS
  SELECT
    name,
    COUNT(*) AS nb,
    MIN(vsize) AS "min (b)",
    ROUND(AVG(vsize), 1) AS "avg (b)",
    MAX(vsize) AS "max (b)"
  FROM CaseValues
  GROUP BY 1
UNION
  SELECT NULL, COUNT(*), MIN(vsize), ROUND(AVG(vsize), 1), MAX(vsize)
  FROM CaseValues
  ORDER BY 1;

-- relative execution time comparison per cases
CREATE TABLE ShowPerfPerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
    name,
    cases AS "cases",
    ROUND(best, 1) AS "best µs",
    ROUND(blaze, 1) AS blaze,
    ROUND(c, 1) AS c,
    ROUND(js, 1) AS js,
    ROUND(jv1, 1) AS jv1,
    ROUND(jv2, 1) AS jv2,
    ROUND(jv3, 1) AS jv3,
    ROUND(py, 1) AS py
  FROM RelativeComparison
  ORDER BY 1 ASC;

-- relative execution time summary
CREATE TABLE ShowPerfSummary AS
  SELECT
    1 AS ordre, 'Best' AS summary,
    COUNT(*) FILTER (WHERE blaze = 1.0) AS blaze,
    COUNT(*) FILTER (WHERE c = 1.0) AS c,
    COUNT(*) FILTER (WHERE js = 1.0) AS js,
    COUNT(*) FILTER (WHERE jv1 = 1.0) AS jv1,
    COUNT(*) FILTER (WHERE jv2 = 1.0) AS jv2,
    COUNT(*) FILTER (WHERE jv3 = 1.0) AS jv3,
    COUNT(*) FILTER (WHERE py = 1.0) AS py
  FROM RelativeComparison
  UNION
  SELECT
    2, 'KO',
    COUNT(*) FILTER (WHERE blaze IS NULL),
    COUNT(*) FILTER (WHERE c IS NULL),
    COUNT(*) FILTER (WHERE js IS NULL),
    COUNT(*) FILTER (WHERE jv1 IS NULL),
    COUNT(*) FILTER (WHERE jv2 IS NULL),
    COUNT(*) FILTER (WHERE jv3 IS NULL),
    COUNT(*) FILTER (WHERE py IS NULL)
  FROM RelativeComparison
  UNION
  SELECT
    3, 'max',
    ROUND(MAX(blaze), 1),
    ROUND(MAX(c), 1),
    ROUND(MAX(js), 1),
    ROUND(MAX(jv1), 1),
    ROUND(MAX(jv2), 1),
    ROUND(MAX(jv3), 1),
    ROUND(MAX(py), 1)
  FROM RelativeComparison
  UNION
  SELECT
    4, 'gav',
    ROUND(EXP(AVG(LN(blaze))), 1),
    ROUND(EXP(AVG(LN(c))), 1),
    ROUND(EXP(AVG(LN(js))), 1),
    ROUND(EXP(AVG(LN(jv1))), 1),
    ROUND(EXP(AVG(LN(jv2))), 1),
    ROUND(EXP(AVG(LN(jv3))), 1),
    ROUND(EXP(AVG(LN(py))), 1)
  FROM RelativeComparison
  UNION
  SELECT
    5, 'min',
    ROUND(MIN(blaze), 1),
    ROUND(MIN(c), 1),
    ROUND(MIN(js), 1),
    ROUND(MIN(jv1), 1),
    ROUND(MIN(jv2), 1),
    ROUND(MIN(jv3), 1),
    ROUND(MIN(py), 1)
  FROM RelativeComparison
  ORDER BY 1;
 
-- compile time per case
CREATE TABLE ShowCompilePerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
    name,
    ROUND(blaze, 1) AS blaze,
    ROUND(c, 1) AS c,
    ROUND(js, 1) AS js,
    ROUND(jv, 1) AS jv,
    ROUND(py, 1) AS py
  FROM CompilePerfCompare
  ORDER BY 1;

-- compile time summary for all cases
CREATE TABLE ShowCompileSummary AS
  SELECT
    'min compile time (s)' AS data,
    ROUND(MIN(blaze), 1) AS blaze,
    ROUND(MIN(c), 1) AS c,
    ROUND(MIN(js), 1) AS js,
    ROUND(MIN(jv), 1) AS jv,
    ROUND(MIN(py), 1) AS py
  FROM CompilePerfCompare
  UNION
  SELECT
    'avg compile time (s)',
    ROUND(AVG(blaze), 1),
    ROUND(AVG(c), 1),
    ROUND(AVG(js), 1),
    ROUND(AVG(jv), 1),
    ROUND(AVG(py), 1)
  FROM CompilePerfCompare
  UNION
  SELECT
    'max compile time (s)',
    ROUND(MAX(blaze), 1),
    ROUND(MAX(c), 1),
    ROUND(MAX(js), 1),
    ROUND(MAX(jv), 1),
    ROUND(MAX(py), 1)
  FROM CompilePerfCompare;

-- only bad results
CREATE TABLE ShowBadResults AS
  SELECT *
  FROM ResultComparison
  WHERE blaze <> '100' OR c <> '100' OR js <> '100' OR jv1 <> '100'
     OR jv2 <> '100' OR jv3 <> '100' OR py <> '100';
