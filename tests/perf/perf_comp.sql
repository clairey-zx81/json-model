--
-- COMPUTE
--

-- use simpler case names
UPDATE RawRun SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE RawCompile SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE RawResult SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE Cases SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE CaseValues SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;

-- compute test stats
WITH
  case_stats(name, minsz, avgsz, maxsz) AS (
    SELECT name, MIN(bsize), AVG(bsize), MAX(bsize)
    FROM CaseValues
    GROUP BY 1
  )
UPDATE CaseValues AS cv
  SET
    minsz = cs.minsz,
    avgsz = cs.avgsz,
    maxsz = cs.maxsz
  FROM case_stats AS cs
  WHERE cs.name = cv.name
;

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
INSERT INTO CaseToolRun(name, tool, line, runavg, runstd, empty)
  -- ensuire uniqueness
  SELECT name, tool, line, AVG(runavg), AVG(runstd), AVG(empty)
  FROM OrderedRawRun
  WHERE ordering = 0.5
  GROUP BY name, tool, line
;

-- all actually tested tools
INSERT INTO Tools(tool)
  SELECT DISTINCT tool FROM CaseToolRun ORDER BY 1;

-- tools x cases
INSERT INTO CaseTool(name, tool)
  SELECT name, tool
  FROM Cases CROSS JOIN Tools
  ORDER BY 1, 2;

-- extract worse results
INSERT INTO CaseToolResult(name, tool, pass, fail)
  SELECT name, tool, MIN(pass), MAX(fail)
  FROM RawResult
  GROUP BY 1, 2
;

-- fill in missings
INSERT INTO CaseToolResult(name, tool)
  SELECT tc.name, tc.tool
  FROM CaseTool AS tc
  LEFT JOIN CaseToolResult AS r USING (name, tool)
  WHERE r.pass IS NULL;

UPDATE CaseToolResult AS r
  SET
    executed = 1.0 * (pass + fail) / c.tests,  -- usually 1.0
    rate = 1.0 * pass / c.tests                -- hopefully 1.0
  FROM Cases AS c
  WHERE c.name = r.name
;

UPDATE CaseToolResult
  SET executed = 0.0
  WHERE executed IS NULL;

UPDATE CaseToolResult
  SET rate = 0.0
  WHERE rate IS NULL; 

-- rounded pc
UPDATE CaseToolResult
  SET pc = ROUND(100.0 * rate, 1);

-- get aggregated case performance
INSERT INTO CaseToolCumulatedPerf(name, tool, run, spread, empty, nb)
  SELECT
    name, tool,
    -- may be null
    SUM(runavg),
    AVG(runstd/runavg),
    AVG(empty),
    -- may be 0
    COUNT(runavg)
  FROM CaseTool
  LEFT JOIN CaseToolRun USING (name, tool)
  GROUP BY 1, 2
  ORDER BY 1, 2
;

-- scratch measure if not all cases were executed!
UPDATE CaseToolCumulatedPerf AS cp
  SET run = NULL, spread = NULL, empty = NULL
  FROM CaseToolResult AS rs
  WHERE cp.name = rs.name AND cp.tool = rs.tool AND rs.executed <> 1.0;

-- and do not allow zero
UPDATE CaseToolCumulatedPerf
  SET run = NULL WHERE run = 0.0;

-- retrieve best performance for each case
-- best perrformance
INSERT INTO CaseBestCumulatedPerf(name, run)
  SELECT name, MIN(run)
  FROM CaseToolCumulatedPerf
  GROUP BY name;

-- retrieve corresponding best tool
UPDATE CaseBestCumulatedPerf AS b
  SET tool = c.tool
  FROM CaseToolCumulatedPerf AS c
  WHERE b.name = c.name
    AND b.run = c.run;

-- summary of tool performance
INSERT INTO ToolSummaryPerf(tool, nbest)
  SELECT tool, COUNT(*) FILTER (WHERE run IS NOT NULL)
  FROM Tools
  LEFT JOIN CaseBestCumulatedPerf USING (tool)
  GROUP BY 1
;

-- update broken count
WITH
  tool_broken(tool, nbfail) AS (
    SELECT tool, COUNT(*) FILTER (WHERE executed <> 1.0)
    FROM CaseToolResult
    GROUP BY 1
  )
UPDATE ToolSummaryPerf AS ts
  SET nbroken = tb.nbfail
  FROM tool_broken AS tb
  WHERE tb.tool = ts.tool
;

WITH
  perf_ratio(name, tool, ratio) AS (
    SELECT cp.name, cp.tool, cp.run / bc.run
    FROM CaseToolCumulatedPerf AS cp
    JOIN CaseBestCumulatedPerf AS bc USING (name)
  ),
  tool_perf(tool, rel_max, rel_avg, rel_min) AS (
    SELECT tool, MAX(ratio), EXP(AVG(LN(ratio))), MIN(ratio)
    FROM perf_ratio
    GROUP BY 1
  )
UPDATE ToolSummaryPerf AS cp
  SET
    rel_max = pr.rel_max,
    rel_avg = pr.rel_avg,
    rel_min = pr.rel_min
  FROM tool_perf AS pr
  WHERE cp.tool = pr.tool
;

-- compilation MIN time aggregation? median??
INSERT INTO CaseToolCompilePerf(name, tool, run, nb)
  SELECT name, tool, MIN(run), COUNT(*)
  FROM RawCompile
  GROUP BY 1, 2
;
