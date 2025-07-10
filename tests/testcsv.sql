-- psql -v csvfile=file.csv -f test.sql

\set ON_ERROR_STOP

CREATE TEMPORARY TABLE json_model_test(
    jid SERIAL PRIMARY KEY,
    expect BOOLEAN,
    name TEXT NOT NULL,
    jval JSONB NOT NULL,
    checked BOOLEAN DEFAULT NULL
);

\copy json_model_test(expect, name, jval) FROM PSTDIN WITH (FORMAT csv, NULL '\\n')

UPDATE json_model_test
SET
  jid = jid - 1,
  checked = check_model(jval, name, NULL);

\echo # count working tests
SELECT
  COUNT(*) FILTER (WHERE expect = checked) AS success,
  COUNT(*) AS total
FROM json_model_test;

-- any errors?
SELECT COUNT(*) = 0 AS okay
FROM json_model_test
WHERE checked IS NULL OR expect <> checked \gset

\if :okay
\echo # OK
\else
\echo # bad tests
SELECT jid, checked
FROM json_model_test
WHERE checked IS NULL OR expect <> checked;

\echo # all results
SELECT jid, expect, checked
FROM json_model_test;

SELECT JSONB_AGG(TO_JSONB(jid) ORDER BY jid) AS failed
FROM json_model_test
WHERE checked IS NULL OR expect <> checked \gset

\echo # KO :failed
\endif
