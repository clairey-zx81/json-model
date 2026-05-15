--
-- Performance Summary SQLite infrastructure
--

--
-- imported data
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
  nsize INT NOT NULL,            -- normalized schema lines (no doc)
  msize INT NOT NULL,            -- model lines (may be a reference)
  tests INT NOT NULL,            -- number of test values in test
  minsz INT DEFAULT NULL,        -- min value size in bytes
  avgsz INT DEFAULT NULL,        -- avg value size in bytes
  maxsz INT DEFAULT NULL,        -- max value size in bytes
  bsize INT DEFAULT NULL,        -- total size of values in bytes
  lsize INT DEFAULT NULL         -- total size of values in lines
);

CREATE TABLE CaseValues(
  name TEXT NOT NULL,            -- test name
  line INT NOT NULL,             -- value line number (from 1)
  bsize INT NOT NULL,            -- value size in bytes
  lsize INT NOT NULL,            -- value size in lines
  PRIMARY KEY (name, line)
);

-- tool descriptions
CREATE TABLE ToolLabels(
  ord INT NOT NULL,              -- prefered order of appearence
  tool TEXT PRIMARY KEY,         -- tool name as imported
  label TEXT UNIQUE NOT NULL,    -- pretty descriptive label
  short TEXT UNIQUE NOT NULL     -- short descriptive label for column names
);

INSERT INTO ToolLabels(ord, tool, label, short) VALUES
  (1, 'blaze', 'Blaze CLI', 'blaze'),
  (2, 'jmc-c', 'JMC C', 'jmc c'),
  (3, 'jmc-js', 'JMC JS', 'jmc js'),
  (4, 'jmc-java-gson', 'JMC Java GSON', 'jmc jv1'),
  (5, 'jmc-java-jackson', 'JMC Java Jackson', 'jmc jv2'),
  (6, 'jmc-java-jsonp', 'JMC Java JSONP/Johnzon', 'jmc jv3'),
  (7, 'jmc-py', 'JMC Python', 'jmc py')
;

-- shorten long names to improve display
CREATE TABLE CaseRenames(
  oldname TEXT PRIMARY KEY,
  newname TEXT UNIQUE NOT NULL
);

INSERT INTO CaseRenames(oldname, newname) VALUES
  ('unreal-engine-uproject', 'unreal-ng'),
  ('gitpod-configuration', 'gitpod-cnf'),
  ('pre-commit-hooks', 'pre-ci'),
  ('semantic-release', 'sem-rel'),
  ('helm-chart-lock', 'helm-chart'),
  ('cmake-presets', 'cmake'),
  ('code-climate', 'code-clim'),
  ('ansible-meta', 'ansible'),
  ('clang-format', 'clang-fmt'),
  ('ui5-manifest', 'ui5-mfest')
;

-- one performance point for a test (tool on name:line), kept from RawRun
CREATE TABLE CaseToolRun(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  line INT NOT NULL,
  runavg DOUBLE,
  runstd DOUBLE,
  empty DOUBLE,
  PRIMARY KEY(name, tool, line)
);

-- actually used tools
CREATE TABLE Tools(
  tool TEXT PRIMARY KEY
);

-- all case and tools
CREATE TABLE CaseTool(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  PRIMARY KEY(name, tool)
);

-- results summary per case/tool
CREATE TABLE CaseToolResult(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  pass INT,
  fail INT,
  -- NOTE these are derived data for convenience
  -- fraction of executed tests
  executed DOUBLE CHECK(executed IS NULL OR executed BETWEEN 0.0 AND 1.0),
  -- success rate achieved
  rate DOUBLE CHECK(rate IS NULL OR rate BETWEEN 0.0 AND 1.0),
  PRIMARY KEY(name, tool)
);

-- cumulated perf, aggregated per case/tool
CREATE TABLE CaseToolCumulatedPerf(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  run DOUBLE,
  spread DOUBLE,
  empty DOUBLE,
  nb INT,
  PRIMARY KEY(name, tool)
);

-- case winner
CREATE TABLE CaseBestCumulatedPerf(
  name TEXT PRIMARY KEY,
  tool TEXT,
  run DOUBLE
);

-- tool perf over all cases
CREATE TABLE ToolSummaryPerf(
  tool TEXT PRIMARY KEY,
  nbest INT NOT NULL,
  nbroken INT,
  -- speeds
  bspeed DOUBLE,
  lspeed DOUBLE,
  -- relative time ratio aggregations
  rmax DOUBLE,
  ravg DOUBLE,  -- geometric
  rmin DOUBLE
);

-- compilation times
CREATE TABLE CaseToolCompilePerf(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  run DOUBLE NOT NULL,
  nb INT NOT NULL,
  PRIMARY KEY(name, tool)
);
