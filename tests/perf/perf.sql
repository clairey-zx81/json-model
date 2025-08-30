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

.print # overall cumulative perfs
SELECT name, tool,
  SUM(runavg) AS run,
  ROUND(AVG(empty), 3) AS empty,
  ROUND(AVG(runstd/runavg), 3) AS spread,
  COUNT(*) AS nb
FROM Run
GROUP BY 1, 2
ORDER BY 1, 2;

/*
.print # blaze vs jmc-c
SELECT name, line, b.runavg / c.runavg
FROM Run AS b
JOIN Run AS c USING (name, line)
WHERE b.tool = 'blaze'
  AND c.tool = 'jmc-c'
GROUP BY 1, 2
ORDER BY 1, 3;
*/
