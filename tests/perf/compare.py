#! /usr/bin/env python
#
# Compare results
#
# Its fun in SQL, probably people would do that with pandas
#

import re
import sqlite3
import argparse
import logging

logging.basicConfig(level=logging.INFO)
log = logging.getLogger("cmp")

SETUP: str = """
CREATE TABLE Performances(
  name TEXT NOT NULL,
  tool TEXT NOT NULL,
  run DOUBLE NOT NULL,
  PRIMARY KEY(name, tool)
);
"""

POST_LOAD: str = """
CREATE TABLE Cases(
  name TEXT PRIMARY KEY
);

INSERT INTO Cases(name)
  SELECT DISTINCT name FROM Performances ORDER BY 1;

CREATE TABLE Tools(
  tool TEXT PRIMARY KEY
);

INSERT INTO Tools(tool)
  SELECT DISTINCT tool FROM Performances ORDER BY 1;
"""

def esc(raw: str) -> str:
    return "'" + raw.replace("'", "''") + "'"

def compare():

    # handle options and arguments
    parser = argparse.ArgumentParser(description="Compare Benchmark Results")
    arg = parser.add_argument
    arg("--tool", type=str, default="jmc-c", help="name of tool to import")
    arg("database", type=str, help="output database for merged results")
    arg("databases", nargs="+", help="input sqlite database files")
    args = parser.parse_args()

    # setup
    db = sqlite3.connect(args.database)

    def exe(sql: str):
        db.executescript(sql)
        db.commit()

    exe(SETUP)

    variants = []

    for fname in args.databases:
        log.info(f"loading file {fname}…")
        with sqlite3.connect(fname) as dbi:
            # assume .../directory/perf.db"
            name = fname.split("/")[-2]
            variants.append(name)
            data = dbi.execute("SELECT name, run FROM CumulatedPerf WHERE tool = ?", (args.tool, )).fetchall()
            db.executemany(f"INSERT INTO Performances(tool, name, run) VALUES({esc(name)}, ?, ?)", data)

    exe(POST_LOAD);

    # decide on column names
    cnames = {
        tool: tool if re.match(r"^[A-Za-z]\w+$", tool) else f"c{i}"
            for i, tool in enumerate(variants)
    }

    # build time comparison
    exe(f"""
        CREATE TABLE TimeComparison(
            name TEXT PRIMARY KEY,
            {"".join(f"  {cnames[tool]} DOUBLE,\n" for tool in variants)}
            best DOUBLE
        );
        INSERT INTO TimeComparison(name)
            SELECT name FROM Cases;
    """)
    
    for tool in variants:
        cname = cnames[tool]
        exe(f"""
            UPDATE TimeComparison AS c
            SET {cname} = p.run
            FROM Performances AS p
            WHERE c.name = p.name AND p.tool = {esc(tool)};
        """)

    exe(f"""
        UPDATE TimeComparison
            SET best = MIN({",".join(f"COALESCE({cnames[tool]}, 1e999)" for tool in variants)});
    """)

    # relative comparison
    exe(f"""
        CREATE TABLE RelComparison(
            name TEXT PRIMARY KEY,
            {"".join(f"  {cnames[tool]} DOUBLE,\n" for tool in variants)}
            tool TEXT
        );
        INSERT INTO RelComparison(name, {", ".join(cnames[tool] for tool in variants)})
            SELECT name, {", ".join(f"{cnames[tool]} / best" for tool in variants)}
            FROM TimeComparison
        ;
        UPDATE RelComparison SET tool = CASE 1.0
            {"".join(f" WHEN {cnames[tool]} THEN {esc(tool)}\n" for tool in variants)}
            END
        ;
    """)

    # summary
    exe(f"""
        CREATE TABLE PerfSummary AS
            SELECT 1 AS "#", 'max' AS summary,
                {", ".join(f"MAX({cnames[tool]}) AS {cnames[tool]}" for tool in variants)}
            FROM RelComparison
            UNION
            SELECT 2, 'geo avg' AS summary,
                {", ".join(f"EXP(AVG(LN({cnames[tool]}))) AS {cnames[tool]}" for tool in variants)}
            FROM RelComparison
            UNION
            SELECT 3, 'min' AS summary,
                {", ".join(f"MIN({cnames[tool]}) AS {cnames[tool]}" for tool in variants)}
            FROM RelComparison
        ;
    """)

    db.commit()
    db.close()

if __name__ == "__main__":
    compare()
