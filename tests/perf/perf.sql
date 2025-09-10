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
  run DOUBLE NOT NULL,
  PRIMARY KEY(name, tool)
);

.mode csv
.import perf.csv Run
.import compile.csv Compile

CREATE TABLE Cases(name TEXT PRIMARY KEY);
  INSERT INTO Cases(name)
    SELECT DISTINCT name FROM Run ORDER BY 1;

-- .printf "# cases"
-- SELECT COUNT(*) FROM Cases;
-- SELECT * FROM Cases;

CREATE TABLE Tools(name TEXT PRIMARY KEY);
  INSERT INTO Tools(name)
    SELECT DISTINCT tool FROM Run ORDER BY 1;

.print # compute overall cumulative perfs
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
UPDATE CumulatedPerf
  SET run = NULL WHERE run = 0.0;

.print # build comparison table
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
    NULL AS best
  FROM Cases AS c
  ORDER BY 1;

-- best time
UPDATE Comparison
  SET best = MIN(COALESCE(blaze, 1000000.0),
                 COALESCE(c, 1000000.0),
                 COALESCE(js, 1000000.0),
                 COALESCE(jv1, 1000000.0),
                 COALESCE(jv2, 1000000.0),
                 COALESCE(jv3, 1000000.0),
                 COALESCE(py, 1000000.0));

-- relative comparison table
CREATE TABLE RelativeComparison AS
  SELECT name,
    ROUND(blaze / best, 2) AS "blaze",
    ROUND(c / best, 2) AS "c",
    ROUND(js / best, 2) AS "js",
    ROUND(jv1 / best, 2) AS "jv1",
    ROUND(jv2 / best, 2) AS "jv2",
    ROUND(jv3 / best, 2) AS "jv3"
  FROM Comparison;

-- OUTPUT
.mode box

.print # Relative Comparison
SELECT *
FROM RelativeComparison
ORDER BY 1 ASC;

.print # Relative Comparison Summary
SELECT 'min' AS summary,
  MIN(blaze) AS blaze,
  MIN(c) AS c,
  MIN(js) AS js,
  MIN(jv1) AS jv1,
  MIN(jv2) AS jv2,
  MIN(jv3) AS jv3
FROM RelativeComparison
UNION
SELECT 'max',
  MAX(blaze), MAX(c), MAX(js), MAX(jv1), MAX(jv2), MAX(jv3)
FROM RelativeComparison
UNION
SELECT 'best',
  COUNT(*) FILTER (WHERE blaze = 1.0),
  COUNT(*) FILTER (WHERE c = 1.0),
  COUNT(*) FILTER (WHERE js = 1.0),
  COUNT(*) FILTER (WHERE jv1 = 1.0),
  COUNT(*) FILTER (WHERE jv2 = 1.0),
  COUNT(*) FILTER (WHERE jv3 = 1.0)
FROM RelativeComparison
UNION
SELECT 'KO',
  COUNT(*) FILTER (WHERE blaze IS NULL),
  COUNT(*) FILTER (WHERE c IS NULL),
  COUNT(*) FILTER (WHERE js IS NULL),
  COUNT(*) FILTER (WHERE jv1 IS NULL),
  COUNT(*) FILTER (WHERE jv2 IS NULL),
  COUNT(*) FILTER (WHERE jv3 IS NULL)
FROM RelativeComparison
ORDER BY 1 ASC;

-- TODO compilation time
-- CREATE TABLE CompilationTimes
