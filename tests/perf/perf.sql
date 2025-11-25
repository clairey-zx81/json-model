--
-- Performance summary queries
--

CREATE TABLE RawRun(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  iter INT NOT NULL,             -- iteration
  line INT NOT NULL,             -- test value line
  runavg DOUBLE NOT NULL,        -- average run time
  runstd DOUBLE NOT NULL,        -- standard deviation time
  empty DOUBLE NOT NULL,         -- estimated measure overhead
  PRIMARY KEY(name, tool, iter, line)
);

CREATE TABLE RawCompile(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  ran TIMESTAMP NOT NULL,        -- compilation timestamp
  run DOUBLE NOT NULL,           -- compilation time
  PRIMARY KEY(name, tool, ran)
);

CREATE TABLE RawResult(
  name TEXT NOT NULL,            -- test name
  tool TEXT NOT NULL,            -- tool name
  iter INT NOT NULL,             -- iteration
  pass INT NOT NULL,             -- number of passes
  fail INT NOT NULL,             -- number of fails
  PRIMARY KEY(name, tool, iter)
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

CREATE TABLE Labels(
  tool TEXT PRIMARY KEY,
  label TEXT UNIQUE NOT NULL
);

INSERT INTO Labels(tool, label) VALUES
  ('blaze', 'Blaze CLI'),
  ('jmc-c', 'JMC C'),
  ('jmc-js', 'JMC JS'),
  ('jmc-java-gson', 'JMC Java GSON'),
  ('jmc-java-jackson', 'JMC Java Jackson'),
  ('jmc-java-jsonp', 'JMC Java JSONP/Johnzon'),
  ('jmc-py', 'JMC Python')
;

-- load raw data
.mode csv
.import perf.csv RawRun
.import compile.csv RawCompile
.import result.csv RawResult
.import cases.csv Cases
.import casevalues.csv CaseValues

-- shorten some names to improve display
UPDATE RawRun SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE RawRun SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE RawCompile SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE RawCompile SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE RawResult SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE RawResult SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';
UPDATE Cases SET name = 'gitpod' WHERE name = 'gitpod-configuration';
UPDATE Cases SET name = 'unreal-engine' WHERE name = 'unreal-engine-uproject';

-- keep MEDIAN values for each case (line)
CREATE TABLE Run AS
  WITH OrderedRawRun AS (
    SELECT
      percent_rank() OVER (PARTITION BY name, tool, line ORDER BY runavg) AS ordering,
      name, tool, line, runavg, runstd, empty
    FROM RawRun
  )
  SELECT name, tool, line, runavg, runstd, empty
  FROM OrderedRawRun
  WHERE ordering = 0.5
;

-- all tested tools
CREATE TABLE Tools(tool TEXT PRIMARY KEY);

INSERT INTO Tools(tool)
  SELECT DISTINCT tool FROM Run ORDER BY 1;

-- tools x cases
CREATE TABLE ToolCase AS
  SELECT name, tool
  FROM Cases CROSS JOIN Tools
  ORDER BY 1, 2;

-- results selection, keep MIN pass
CREATE TABLE Result AS
  WITH OrderedRawResult AS (
    SELECT
      RANK() OVER (PARTITION BY name, tool ORDER BY pass) AS ordering,
      name, tool, pass, fail
    FROM RawResult
  )
  SELECT name, tool, pass, fail
  FROM OrderedRawResult
  WHERE ordering = 1;

-- all results, set to 0 if missing
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

-- show rounded pc
UPDATE ResultRate
  SET pc = ROUND(rate, 1);

-- cumulated perf per case/tool
CREATE TABLE CumulatedPerf AS
  SELECT name, tool,
    SUM(runavg) AS run,
    AVG(runstd/runavg) AS spread,
    AVG(empty) AS empty,
    COUNT(runavg) AS nb
  FROM Run
  RIGHT JOIN ToolCase USING (name, tool)
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
    NULL AS best
  FROM Cases AS c
  ORDER BY 1;

-- set best execution time is used as a reference, 1E999 is Infinity
UPDATE Comparison
  SET best = MIN(COALESCE(blaze, 1e999),
       	         COALESCE(c, 1e999),
       	         COALESCE(js, 1e999),
       	         COALESCE(jv1, 1e999),
       	         COALESCE(jv2, 1e999),
       	         COALESCE(jv3, 1e999),
       	         COALESCE(py, 1e999));

-- execution time relative to the fastest, the lower the better
CREATE TABLE RelativeComparison AS
  SELECT
    name,
    cases,
    best,
    CASE best
      WHEN blaze THEN 'blaze'
      WHEN c THEN 'c'
      WHEN js THEN 'js'
      WHEN jv1 THEN 'jv1'
      WHEN jv2 THEN 'jv2'
      WHEN jv3 THEN 'jv3'
      WHEN py THEN 'py'
    END as tool,
    blaze / best AS blaze,
    c / best AS c,
    js / best AS js,
    jv1 / best AS jv1,
    jv2 / best AS jv2,
    jv3 / best AS jv3,
    py / best AS py
  FROM Comparison;

-- compilation MIN time aggregation
CREATE TABLE CompilePerf AS
  SELECT name, tool, MIN(run) AS run, COUNT(*) AS nb
  FROM RawCompile
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

-- compilation time with separate schema to model conversion
CREATE TABLE CompilePerfCompare AS
  SELECT
    name,
    blaze,
    jsu_s + jsu_m AS s2m,
    jmc_out AS c,
    jmc_js AS js,
    jmc_py AS py,
    jmc_class AS jv
  FROM CompilePerfCase;

-- result summary
CREATE TABLE ResultComparison AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
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

-- case stats display
CREATE TABLE ShowCases AS WITH
  CaseInstances AS (
    SELECT
      RANK() OVER (ORDER BY name) AS rnk,
      name,
      COUNT(*) AS nb,
      MIN(vsize) AS minb,
      FORMAT('%.0f', AVG(vsize)) AS avgb,
      MAX(vsize) AS maxb
    FROM CaseValues
    GROUP BY 2
    UNION
    SELECT NULL, NULL, COUNT(*), MIN(vsize), FORMAT('%.0f', AVG(vsize)), MAX(vsize)
    FROM CaseValues
  ),
  CaseStats AS (
    SELECT
      name,
      ssize AS schema,
      msize AS model
    FROM Cases
    UNION
    SELECT NULL, FORMAT('%.0f', AVG(ssize)), FORMAT('%.0f', AVG(msize))
    FROM Cases
  )
  SELECT
    ci.rnk AS "#", cs.name, cs.schema, cs.model,
    ci.nb, ci.minb AS "min (b)", ci.avgb AS "avg (b)", ci.maxb AS "max (b)"
  FROM CaseInstances AS ci
  JOIN CaseStats AS cs ON (ci.name IS NULL AND cs.name IS NULL OR ci.name = cs.name)
  ORDER BY 1;

-- relative execution time comparison per cases
-- display nothing on failures
CREATE TABLE ShowPerfPerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
    name,
    cases AS "cases",
    ROUND(best, 1) AS "best µs",
    tool AS ":1st_place_medal:",
    CASE WHEN blaze <> 0.0 THEN FORMAT('%.02f', blaze) ELSE NULL END AS blaze,
    CASE WHEN c     <> 0.0 THEN FORMAT('%.02f', c)     ELSE NULL END AS c,
    CASE WHEN js    <> 0.0 THEN FORMAT('%.02f', js)    ELSE NULL END AS js,
    CASE WHEN jv1   <> 0.0 THEN FORMAT('%.02f', jv1)   ELSE NULL END AS jv1,
    CASE WHEN jv2   <> 0.0 THEN FORMAT('%.02f', jv2)   ELSE NULL END AS jv2,
    CASE WHEN jv3   <> 0.0 THEN FORMAT('%.02f', jv3)   ELSE NULL END AS jv3,
    CASE WHEN py    <> 0.0 THEN FORMAT('%.02f', py)    ELSE NULL END AS py
  FROM RelativeComparison
  ORDER BY 1 ASC;

-- relative execution time summary
CREATE TABLE ShowPerfSummary AS WITH
  TotalCaseSize AS (
    SELECT tool, SUM(vsize) AS tsize
    FROM CaseValues
    JOIN CumulatedPerf USING (name)
    WHERE run != 0.0
    GROUP BY 1
  ),
  TotalToolTime AS (
    SELECT tool, SUM(run) AS run
    FROM CumulatedPerf
    GROUP BY 1
  ),
  SpeedPerTool AS (
    SELECT tool, tsize / run AS speed
    FROM TotalToolTime
    JOIN TotalCaseSize USING (tool)
  )
  SELECT
    1 AS ordre, 'best count' AS summary,
    COUNT(*) FILTER (WHERE blaze = 1.0) AS blaze,
    COUNT(*) FILTER (WHERE c     = 1.0) AS c,
    COUNT(*) FILTER (WHERE js    = 1.0) AS js,
    COUNT(*) FILTER (WHERE jv1   = 1.0) AS jv1,
    COUNT(*) FILTER (WHERE jv2   = 1.0) AS jv2,
    COUNT(*) FILTER (WHERE jv3   = 1.0) AS jv3,
    COUNT(*) FILTER (WHERE py    = 1.0) AS py
  FROM RelativeComparison
  UNION
  SELECT
    2, 'broken count',
    COUNT(*) FILTER (WHERE blaze IS NULL),
    COUNT(*) FILTER (WHERE c     IS NULL),
    COUNT(*) FILTER (WHERE js    IS NULL),
    COUNT(*) FILTER (WHERE jv1   IS NULL),
    COUNT(*) FILTER (WHERE jv2   IS NULL),
    COUNT(*) FILTER (WHERE jv3   IS NULL),
    COUNT(*) FILTER (WHERE py    IS NULL)
  FROM RelativeComparison
  UNION
  SELECT
    3, 'speed B/µs',
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'blaze')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-c')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-js')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-java-gson')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-java-jackson')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-java-jsonp')),
    FORMAT('%.0f', (SELECT speed FROM SpeedPerTool WHERE tool = 'jmc-py'))
  UNION
  SELECT
    4, 'ratio max',
    FORMAT('%.02f', MAX(blaze)),
    FORMAT('%.02f', MAX(c)),
    FORMAT('%.02f', MAX(js)),
    FORMAT('%.02f', MAX(jv1)),
    FORMAT('%.02f', MAX(jv2)),
    FORMAT('%.02f', MAX(jv3)),
    FORMAT('%.02f', MAX(py))
  FROM RelativeComparison
  UNION
  SELECT
    5, 'ratio geo-avg',
    FORMAT('%.02f', EXP(AVG(LN(blaze)))),
    FORMAT('%.02f', EXP(AVG(LN(c)))),
    FORMAT('%.02f', EXP(AVG(LN(js)))),
    FORMAT('%.02f', EXP(AVG(LN(jv1)))),
    FORMAT('%.02f', EXP(AVG(LN(jv2)))),
    FORMAT('%.02f', EXP(AVG(LN(jv3)))),
    FORMAT('%.02f', EXP(AVG(LN(py))))
  FROM RelativeComparison
  UNION
  SELECT
    6, 'ratio min',
    FORMAT('%.02f', MIN(blaze)),
    FORMAT('%.02f', MIN(c)),
    FORMAT('%.02f', MIN(js)),
    FORMAT('%.02f', MIN(jv1)),
    FORMAT('%.02f', MIN(jv2)),
    FORMAT('%.02f', MIN(jv3)),
    FORMAT('%.02f', MIN(py))
  FROM RelativeComparison
  ORDER BY 1;

-- compile time per case
CREATE TABLE ShowCompilePerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
    name,
    ROUND(blaze, 1) AS blaze,
    ROUND(s2m,   1) AS s2m,
    ROUND(c,     1) AS c,
    ROUND(js,    1) AS js,
    ROUND(jv,    1) AS jv,
    ROUND(py,    1) AS py
  FROM CompilePerfCompare
  ORDER BY 1;

-- compile time summary for all cases
CREATE TABLE ShowCompileSummary AS
  SELECT
    'min compile time (s)' AS data,
    ROUND(MIN(blaze), 1) AS blaze,
    ROUND(MIN(s2m),   1) AS s2m,
    ROUND(MIN(c),     1) AS c,
    ROUND(MIN(js),    1) AS js,
    ROUND(MIN(jv),    1) AS jv,
    ROUND(MIN(py),    1) AS py
  FROM CompilePerfCompare
  UNION
  SELECT
    'avg compile time (s)',
    ROUND(AVG(blaze), 1),
    ROUND(AVG(s2m),   1),
    ROUND(AVG(c),     1),
    ROUND(AVG(js),    1),
    ROUND(AVG(jv),    1),
    ROUND(AVG(py),    1)
  FROM CompilePerfCompare
  UNION
  SELECT
    'max compile time (s)',
    ROUND(MAX(blaze), 1),
    ROUND(MAX(s2m),   1),
    ROUND(MAX(c),     1),
    ROUND(MAX(js),    1),
    ROUND(MAX(jv),    1),
    ROUND(MAX(py),    1)
  FROM CompilePerfCompare;

-- show only bad results
CREATE TABLE ShowBadResults AS
  SELECT *
  FROM ResultComparison
  WHERE blaze <> 100.0 OR c <> 100.0 OR js <> 100.0 OR jv1 <> 100.0
     OR jv2 <> 100.0 OR jv3 <> 100.0 OR py <> 100.0;
