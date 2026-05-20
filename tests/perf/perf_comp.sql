--
-- COMPUTE
--

-- use simpler case names
UPDATE RawRun SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE RawCompile SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE RawResult SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE Cases SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE CaseValues SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;
UPDATE Files SET name = r.newname FROM CaseRenames AS r WHERE name = r.oldname;

-- compute test stats
WITH
  case_stats(name, minsz, avgsz, maxsz, bsize, lsize) AS (
    SELECT name, MIN(bsize), AVG(bsize), MAX(bsize), SUM(bsize), SUM(lsize)
    FROM CaseValues
    GROUP BY 1
  )
UPDATE Cases AS cv
  SET
    minsz = cs.minsz,
    avgsz = cs.avgsz,
    maxsz = cs.maxsz,
    bsize = cs.bsize,
    lsize = cs.lsize
  FROM case_stats AS cs
  WHERE cs.name = cv.name
;

-- keep MEDIAN values for each case (line)
-- NOTE MEDIAN requires sqlite 3.51
-- NOTE percent_rank() hack only works with odd numbers and distinct values…
WITH
  OrderedRawRun AS (
    SELECT
      percent_rank() OVER (PARTITION BY name, tool, line ORDER BY runavg) AS ordering,
      name, tool, line, runavg, runstd, empty
    FROM RawRun
  )
INSERT INTO CaseToolRun(name, tool, line, runavg, runstd, empty)
  -- ensuxire uniqueness
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

-- summary data with geometric average for the slowdown ratio
WITH
  perf_ratio(name, tool, ratio) AS (
    SELECT cp.name, cp.tool, cp.run / bc.run
    FROM CaseToolCumulatedPerf AS cp
    JOIN CaseBestCumulatedPerf AS bc USING (name)
  ),
  tool_perf(tool, rmax, ravg, rmin) AS (
    SELECT tool, MAX(ratio), EXP(AVG(LN(ratio))), MIN(ratio)
    FROM perf_ratio
    GROUP BY 1
  )
UPDATE ToolSummaryPerf AS cp
  SET
    rmax = pr.rmax,
    ravg = pr.ravg,
    rmin = pr.rmin
  FROM tool_perf AS pr
  WHERE cp.tool = pr.tool
;

-- compute byte and line speeds
-- NOTE byte makes more sense if the values are also checked, ie with predefs
WITH
  -- total value size in bytes and lines
  all_sizes(bsize, lsize) AS (
    SELECT SUM(bsize), SUM(lsize)
    FROM CaseValues
  ),
  -- for each tool, total time to process all values
  all_times(tool, trun) AS (
    SELECT tool, SUM(run)
    FROM CaseToolCumulatedPerf
    GROUP BY 1
  )
UPDATE ToolSummaryPerf AS cp
  SET
    bspeed = az.bsize / at.trun,
    lspeed = az.lsize / at.trun
  FROM all_sizes AS az
  CROSS JOIN all_times AS at
  WHERE cp.tool = at.tool
;

-- medial compilation time
-- NOTE some effort to compute the median reliably
WITH
  -- rank and count run times
  ranked_compile_time(name, tool, run, ordering, nb) AS (
    SELECT DISTINCT name, tool, run,
      PERCENT_RANK() OVER (PARTITION BY name, tool ORDER BY run),
      COUNT(*) OVER (PARTITION BY name, tool, run)
    FROM RawCompile
  ),
  -- re-rank lower than 0.5
  smaller_run(name, tool, ordering, run, nb, closer) AS (
    SELECT name, tool, ordering, run, nb,
      PERCENT_RANK() OVER (partition BY name, tool ORDER BY ordering DESC)
    FROM ranked_compile_time
    WHERE ordering <= 0.5
  ),
  -- re-rank greater than 0.5
  larger_run(name, tool, ordering, run, nb, closer) AS (
    SELECT name, tool, ordering, run, nb,
      PERCENT_RANK() OVER (partition BY name, tool ORDER BY ordering ASC)
    FROM ranked_compile_time
    WHERE ordering >= 0.5
  ),
  -- compute weighted average of the closest above and below 0.5
  -- NOTE it may be the same
  median_run(name, tool, run) AS (
    SELECT name, tool, (s.nb * s.run + l.nb * l.run) / (s.nb + l.nb)
    FROM smaller_run AS s
    JOIN larger_run AS l USING (name, tool)
    WHERE s.closer = 0.0 AND l.closer = 0.0
  ),
  -- also collect counts
  counts(name, tool, nb) AS (
    SELECT name, tool, COUNT(*)
    FROM RawCompile
    GROUP BY 1, 2
  )
  -- final result
  INSERT INTO CaseToolCompilePerf(name, tool, run, nb)
    SELECT name, tool, m.run, c.nb
    FROM median_run AS m
    JOIN counts AS c USING (name, tool)
;
