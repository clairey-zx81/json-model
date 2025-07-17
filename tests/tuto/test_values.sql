CREATE TEMPORARY TABLE json_values(name TEXT PRIMARY KEY, data JSONB);
\copy json_values(name, data) FROM PSTDIN
SELECT
  name AS id,
  CASE WHEN check_model(data, '', NULL) THEN 'PASS' ELSE 'FAIL' END AS test
FROM json_values;
