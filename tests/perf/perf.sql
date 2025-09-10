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

-- load raw data
.mode csv
.import perf.csv Run
.import compile.csv Compile
.import result.csv Result

-- shorten some names
UPDATE Run SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Compile SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Result SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Run SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Compile SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Result SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';

CREATE TABLE Cases(name TEXT PRIMARY KEY);
INSERT INTO Cases(name)
  SELECT DISTINCT name FROM Run ORDER BY 1;

.print # cases
SELECT COUNT(*) FROM Cases;

CREATE TABLE Tools(name TEXT PRIMARY KEY);
  INSERT INTO Tools(name)
    SELECT DISTINCT tool FROM Run ORDER BY 1;

CREATE TABLE CumulatedPerf AS
  SELECT name, tool,
    SUM(runavg) AS run,
    ROUND(AVG(runstd/runavg), 3) AS spread,
    ROUND(AVG(empty), 3) AS empty,
    COUNT(*) AS nb
  FROM Run
  GROUP BY 1, 2
  ORDER BY 1, 2;

-- do not allow zero
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
    ROUND(blaze / best, 2) AS "blaze",
    ROUND(c / best, 2) AS "c",
    ROUND(js / best, 2) AS "js",
    ROUND(jv1 / best, 2) AS "jv1",
    ROUND(jv2 / best, 2) AS "jv2",
    ROUND(jv3 / best, 2) AS "jv3",
    ROUND(py / best, 2) AS "py"
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
    ROUND(blaze, 2) AS blaze,
    ROUND(jsu_s + jsu_m + jmc_out, 2) AS c,
    ROUND(jsu_s + jsu_m + jmc_js, 2) AS js,
    ROUND(jsu_s + jsu_m + jmc_py, 2) AS py,
    ROUND(jsu_s + jsu_m + jmc_class, 2) AS jv
  FROM CompilePerfCase;

-- SHOW
.mode box
.print # relative execution time comparison per cases
SELECT
  RANK() OVER (ORDER BY name) AS "#",
  *
FROM RelativeComparison
ORDER BY 1 ASC;

.print # relative execution time summary
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
  MIN(blaze),
  MIN(c),
  MIN(js),
  MIN(jv1),
  MIN(jv2),
  MIN(jv3),
  MIN(py)
FROM RelativeComparison
UNION
SELECT 'max',
  MAX(blaze), MAX(c), MAX(js), MAX(jv1), MAX(jv2), MAX(jv3), MAX(py)
FROM RelativeComparison
ORDER BY 1 ASC;
 
.print # compile time per case
SELECT
  RANK() OVER (ORDER BY name) AS "#",
  *
FROM CompilePerfCompare
ORDER BY 1;

.print # compile time summary for all cases
SELECT
  'min compile time (s)' AS data,
  MIN(blaze) AS blaze,
  MIN(c) AS c,
  MIN(js) AS js,
  MIN(py) AS py,
  MIN(jv) AS jv
FROM CompilePerfCompare
UNION
SELECT
  'avg compile time (s)',
  ROUND(AVG(blaze), 2),
  ROUND(AVG(c), 2),
  ROUND(AVG(js), 2),
  ROUND(AVG(py), 2),
  ROUND(AVG(jv), 2)
FROM CompilePerfCompare
UNION
SELECT
  'max compile time (s)',
  MAX(blaze),
  MAX(c),
  MAX(js),
  MAX(py),
  MAX(jv)
FROM CompilePerfCompare;
/*
UNION
SELECT
  'std compile time (s)' AS data,
  ROUND(STDEV(blaze), 1) AS blaze,
  ROUND(STDEV(c), 1) AS c,
  ROUND(STDEV(js), 1) AS js,
  ROUND(STDEV(py), 1) AS py,
  ROUND(STDEV(jv), 1) AS jv
FROM CompilePerfCompare
*/
;
