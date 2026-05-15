--
-- COMPUTE
--

-- use simpler case names
UPDATE RawRun SET name = r.newname FROM Renames AS r WHERE name = r.oldname;
UPDATE RawCompile SET name = r.newname FROM Renames AS r WHERE name = r.oldname;
UPDATE RawResult SET name = r.newname FROM Renames AS r WHERE name = r.oldname;
UPDATE Cases SET name = r.newname FROM Renames AS r WHERE name = r.oldname;
UPDATE CaseValues SET name = r.newname FROM Renames AS r WHERE name = r.oldname;

-- keep MEDIAN values for each case (line)
-- NOTE MEDIAN requires sqlite 3.51
-- NOTE percent_rank() hack only works with odd numbers
WITH
  OrderedRawRun AS (
    SELECT
      percent_rank() OVER (PARTITION BY name, tool, line ORDER BY runavg) AS ordering,
      name, tool, line, runavg, runstd, empty
    FROM RawRun
  )
INSERT INTO Run(name, tool, line, runavg, runstd, empty)
  -- ensuire uniqueness
  SELECT name, tool, line, AVG(runavg), AVG(runstd), AVG(empty)
  FROM OrderedRawRun
  WHERE ordering = 0.5
  GROUP BY name, tool, line
;

-- all tested tools
INSERT INTO Tools(tool)
  SELECT DISTINCT tool FROM Run ORDER BY 1;

-- tools x cases
INSERT INTO ToolCase(name, tool)
  SELECT name, tool
  FROM Cases CROSS JOIN Tools
  ORDER BY 1, 2;

-- extract worse results
INSERT INTO Result(name, tool, pass, fail)
  SELECT name, tool, MIN(pass), MAX(fail)
  FROM RawResult
  GROUP BY 1, 2
;

-- fill in missings
INSERT INTO Result(name, tool)
  SELECT tc.name, tc.tool
  FROM ToolCase AS tc
  LEFT JOIN Result AS r USING (name, tool)
  WHERE r.pass IS NULL;

UPDATE Result AS r
  SET
    executed = 1.0 * (pass + fail) / c.tests,  -- usually 1.0
    rate = 1.0 * pass / c.tests                -- hopefully 1.0
  FROM Cases AS c
  WHERE c.name = r.name
;

UPDATE Result
  SET executed = 0.0
  WHERE executed IS NULL;

UPDATE Result
  SET rate = 0.0
  WHERE rate IS NULL; 

-- rounded pc
UPDATE Result
  SET pc = ROUND(100.0 * rate, 1);

-- get aggregated case performance
INSERT INTO CumulatedPerf(name, tool, run, spread, empty, nb)
  SELECT
    name, tool,
    SUM(runavg),
    AVG(runstd/runavg),
    AVG(empty),
    COUNT(runavg)
  FROM ToolCase
  LEFT JOIN Run USING (name, tool)
  GROUP BY 1, 2
  ORDER BY 1, 2
;

-- scratch measure if not all cases were executed
UPDATE CumulatedPerf AS cp
  SET run = NULL, spread = NULL, empty = NULL
  FROM Result AS rs
  WHERE cp.name = rs.name AND cp.tool = rs.tool AND rs.executed <> 1.0;

-- but do not allow zero
UPDATE CumulatedPerf SET run = NULL WHERE run = 0.0;

-- retrieve best performance for each case
-- best perrformance
INSERT INTO BestCumulatedPerf(name, run)
  SELECT name, MIN(run)
  FROM CumulatedPerf
  GROUP BY name;

-- retrieve corresponding best tool
UPDATE BestCumulatedPerf AS b
  SET tool = c.tool
  FROM CumulatedPerf AS c
  WHERE b.name = c.name
    AND b.run = c.run;

-- compilation MIN time aggregation? median??
INSERT INTO CompilePerf(name, tool, run, nb)
  SELECT name, tool, MIN(run), COUNT(*)
  FROM RawCompile
  GROUP BY 1, 2
;
