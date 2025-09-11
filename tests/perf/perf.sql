CREATE TABLE Run(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  line INTEGER NOT NULL,
  runavg DOUBLE NOT NULL,
  runstd DOUBLE NOT NULL,
  empty DOUBLE NOT NULL,
  PRIMARY KEY(name, tool, line)
);

CREATE TABLE Compile(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  ran TIMESTAMP NOT NULL,
  run DOUBLE NOT NULL,
  PRIMARY KEY(name, tool, ran)
);

CREATE TABLE Result(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  pass INT NOT NULL,
  fail INT NOT NULL,
  PRIMARY KEY(name, tool)
);

CREATE TABLE Cases(
  name TEXT PRIMARY KEY,
  ssize INT NOT NULL,
  msize INT NOT NULL,
  tests INT NOT NULL
);

-- load raw data
.mode csv
.import perf.csv Run
.import compile.csv Compile
.import result.csv Result
.import cases.csv Cases

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

-- but do not allow zero
UPDATE CumulatedPerf SET run = NULL WHERE run = 0.0;

-- per case time
CREATE TABLE Comparison AS
  SELECT
    c.name AS name,
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
  SET best = MIN(COALESCE(blaze, 1000000.0),
       	         COALESCE(c, 1000000.0),
       	         COALESCE(js, 1000000.0),
       	         COALESCE(jv1, 1000000.0),
       	         COALESCE(jv2, 1000000.0),
       	         COALESCE(jv3, 1000000.0),
       	         -- COALESCE(pl, 1000000.0),
       	         COALESCE(py, 1000000.0));

-- execution time relative to the fastest, the lower the better
CREATE TABLE RelativeComparison AS
  SELECT
    name,
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
  SELECT c.name,
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

-- all results
CREATE TABLE ResultRate AS
  SELECT
    c.name,
    t.tool,
    100.0 * COALESCE(r.pass, 0) / c.tests AS rate,
    NULL AS pc
  FROM Cases AS c
  CROSS JOIN Tools AS t
  LEFT JOIN Result AS r ON (c.name = r.name AND t.tool = r.tool);

-- show simple pc
UPDATE ResultRate
  SET pc = REPLACE(TRUNC(rate), '.0', '');

-- result summary
CREATE TABLE ResultComparison AS
  SELECT
    c.name AS "name",
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'blaze') AS blaze,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-c') AS c,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-js') AS js,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-gson') AS jv1,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jackson') AS jv2,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jsonp') AS jv3,
    (SELECT pc FROM ResultRate AS r WHERE r.name = c.name AND r.tool = 'jmc-py') AS py
  FROM Cases AS c
  ORDER BY 1;

-- relative execution time comparison per cases
CREATE TABLE ShowPerfPerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
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
  SELECT 'Best' AS summary,
    COUNT(*) FILTER (WHERE blaze = 1.0) AS blaze,
    COUNT(*) FILTER (WHERE c = 1.0) AS c,
    COUNT(*) FILTER (WHERE js = 1.0) AS js,
    COUNT(*) FILTER (WHERE jv1 = 1.0) AS jv1,
    COUNT(*) FILTER (WHERE jv2 = 1.0) AS jv2,
    COUNT(*) FILTER (WHERE jv3 = 1.0) AS jv3,
    COUNT(*) FILTER (WHERE py = 1.0) AS py
  FROM RelativeComparison
  UNION
  SELECT 'KO',
    COUNT(*) FILTER (WHERE blaze IS NULL),
    COUNT(*) FILTER (WHERE c IS NULL),
    COUNT(*) FILTER (WHERE js IS NULL),
    COUNT(*) FILTER (WHERE jv1 IS NULL),
    COUNT(*) FILTER (WHERE jv2 IS NULL),
    COUNT(*) FILTER (WHERE jv3 IS NULL),
    COUNT(*) FILTER (WHERE py IS NULL)
  FROM RelativeComparison
  UNION
  SELECT 'min',
    ROUND(MIN(blaze), 1),
    ROUND(MIN(c), 1),
    ROUND(MIN(js), 1),
    ROUND(MIN(jv1), 1),
    ROUND(MIN(jv2), 1),
    ROUND(MIN(jv3), 1),
    ROUND(MIN(py), 1)
  FROM RelativeComparison
  UNION
  SELECT 'max',
    ROUND(MAX(blaze), 1),
    ROUND(MAX(c), 1),
    ROUND(MAX(js), 1),
    ROUND(MAX(jv1), 1),
    ROUND(MAX(jv2), 1),
    ROUND(MAX(jv3), 1),
    ROUND(MAX(py), 1)
  FROM RelativeComparison
  ORDER BY 1 ASC;
 
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
