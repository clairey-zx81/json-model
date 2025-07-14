-- psql -f test.sql < file.csv

\set QUIET 1
\set ON_ERROR_STOP
\t on
\a

\if :{?input}
\else
  \set input -
\endif

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

SELECT
  :'input' || '[' || jid || ']: ' ||
    CASE
       WHEN expect IS NOT NULL AND expect = checked AND checked THEN 'PASS'
       WHEN expect IS NOT NULL AND expect = checked AND NOT checked THEN 'FAIL'
       WHEN expect IS NOT NULL AND expect <> checked AND checked THEN 'ERROR unexpected PASS'
       WHEN expect IS NOT NULL AND expect <> checked AND NOT checked THEN 'ERROR unexpected FAIL'
       WHEN expect IS NULL AND checked THEN 'PASS'
       WHEN expect IS NULL AND NOT checked THEN 'FAIL'
       ELSE 'ERROR'
    END
FROM json_model_test
ORDER BY jid;
