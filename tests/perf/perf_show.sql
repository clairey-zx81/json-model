--
-- SHOW
--

-- per case time
CREATE TABLE Comparison AS
  SELECT
    c.name AS name,
    tests AS cases,
    -- this generates a NULL if the run failed or the tool was not tested
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'blaze' and cp.name = c.name) AS blaze,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-c' and cp.name = c.name) AS c,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-js' and cp.name = c.name) AS js,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-gson' and cp.name = c.name) AS jv1,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-jackson' and cp.name = c.name) AS jv2,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-java-jsonp' and cp.name = c.name) AS jv3,
    (SELECT cp.run FROM CumulatedPerf AS cp WHERE cp.tool = 'jmc-py' and cp.name = c.name) AS py,
    (SELECT bc.run FROM BestCumulatedPerf AS bc WHERE bc.name = c.name) AS best,
    (SELECT bc.tool FROM BestCumulatedPerf AS bc WHERE bc.name = c.name) AS tool
  FROM Cases AS c
  ORDER BY 1;

-- execution time relative to the fastest, the lower the better
CREATE TABLE RelativeComparison AS
  SELECT
    name,
    cases,
    best,
    l.short AS tool,
    blaze / best AS blaze,
    c / best AS c,
    js / best AS js,
    jv1 / best AS jv1,
    jv2 / best AS jv2,
    jv3 / best AS jv3,
    py / best AS py
  FROM Comparison
  JOIN Labels AS l USING (tool);

-- compilation time per cases
CREATE TABLE CompilePerfCase AS
  SELECT
    c.name,
    (SELECT run FROM CompilePerf AS cp WHERE cp.name = c.name AND cp.tool = 'blaze') AS blaze,
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
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'blaze') AS blaze,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-c') AS c,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-js') AS js,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-java-gson') AS jv1,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jackson') AS jv2,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-java-jsonp') AS jv3,
    (SELECT pc FROM Result AS r WHERE r.name = c.name AND r.tool = 'jmc-py') AS py
  FROM Cases AS c
  ORDER BY 1;

-- case stats display
CREATE TABLE ShowCases AS WITH
  CaseInstances AS (
    SELECT
      RANK() OVER (ORDER BY name) AS rnk,
      name,
      COUNT(*) AS nb,
      MIN(bsize) AS minb,
      FORMAT('%.0f', AVG(bsize)) AS avgb,
      MAX(bsize) AS maxb
    FROM CaseValues
    GROUP BY 2
    UNION
    SELECT NULL, NULL, COUNT(*), MIN(bsize), FORMAT('%.0f', AVG(bsize)), MAX(bsize)
    FROM CaseValues
  ),
  CaseStats AS (
    SELECT
      name,
      ssize AS schema,
      nsize AS normal,
      msize AS model
    FROM Cases
    UNION
    SELECT
      NULL,
      FORMAT('%.0f', AVG(ssize)),
      FORMAT('%.0f', AVG(nsize)),
      FORMAT('%.0f', AVG(msize))
    FROM Cases
  )
  SELECT
    ci.rnk AS "#", cs.name, cs.schema, cs.normal, cs.model,
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
    SELECT tool, SUM(bsize) AS bsize, SUM(lsize) AS lsize
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
    SELECT tool, bsize / run AS bspeed, lsize / run AS lspeed
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
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'blaze')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-c')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-js')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-java-gson')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-java-jackson')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-java-jsonp')),
    FORMAT('%.0f', (SELECT bspeed FROM SpeedPerTool WHERE tool = 'jmc-py'))
  UNION
  SELECT
    4, 'speed l/µs',
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'blaze')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-c')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-js')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-java-gson')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-java-jackson')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-java-jsonp')),
    FORMAT('%.1f', (SELECT lspeed FROM SpeedPerTool WHERE tool = 'jmc-py'))
  UNION
  SELECT
    5, 'ratio max',
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
    6, 'ratio geo-avg',
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
    7, 'ratio min',
    FORMAT('%.02f', MIN(blaze)),
    FORMAT('%.02f', MIN(c)),
    FORMAT('%.02f', MIN(js)),
    FORMAT('%.02f', MIN(jv1)),
    FORMAT('%.02f', MIN(jv2)),
    FORMAT('%.02f', MIN(jv3)),
    FORMAT('%.02f', MIN(py))
  FROM RelativeComparison
  ORDER BY 1;

-- cleanup broken count row if empty
DELETE FROM ShowPerfSummary
WHERE ordre = 2
  AND blaze + c + js + jv1 + jv2 + jv3 + py = 0;

-- compile time per case
CREATE TABLE ShowCompilePerCase AS
  SELECT
    RANK() OVER (ORDER BY name) AS "#",
    name,
    ROUND(blaze, 1) AS blaze,
    ROUND(c,     1) AS c,
    ROUND(js,    1) AS js,
    ROUND(jv,    1) AS jv,
    ROUND(py,    1) AS py
  FROM CompilePerfCompare
  ORDER BY 1;

-- compile time summary for all cases
CREATE TABLE ShowCompileSummary AS
  SELECT
    3 AS ordre,
    'min compile time (s)' AS data,
    ROUND(MIN(blaze), 1) AS blaze,
    ROUND(MIN(c),     1) AS c,
    ROUND(MIN(js),    1) AS js,
    ROUND(MIN(jv),    1) AS jv,
    ROUND(MIN(py),    1) AS py
  FROM CompilePerfCompare
  UNION
  SELECT
    2,
    'avg compile time (s)',
    ROUND(AVG(blaze), 1),
    ROUND(AVG(c),     1),
    ROUND(AVG(js),    1),
    ROUND(AVG(jv),    1),
    ROUND(AVG(py),    1)
  FROM CompilePerfCompare
  UNION
  SELECT
    1,
    'max compile time (s)',
    ROUND(MAX(blaze), 1),
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
     OR jv2 <> 100.0 OR jv3 <> 100.0 OR py <> 100.0
;
