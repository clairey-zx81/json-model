-- psql -v csvfile=file.csv -f test.sql

\set ON_ERROR_STOP

CREATE TEMPORARY TABLE json_model_test(
    jid SERIAL PRIMARY KEY,
    expect BOOLEAN,
    name TEXT NOT NULL,
    jval JSONB NOT NULL
);

\copy json_model_test(expect, name, jval) FROM './dst_03.values.csv' WITH (FORMAT csv, NULL '\\n')

SELECT
  COUNT(*) FILTER (WHERE expect = check_model(jval, name, NULL)) AS ok,
  COUNT(*) AS total
FROM json_model_test;
