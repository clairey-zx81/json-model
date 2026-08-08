-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION json_model_2(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN JSONB_TYPEOF(val) = 'string' AND STARTS_WITH(JSON_VALUE(val, '$' RETURNING TEXT), '#');
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION json_model_3(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  res := JSONB_TYPEOF(val) = 'array' AND JSONB_ARRAY_LENGTH(val) = 2;
  IF res THEN
    res := JSONB_TYPEOF(val -> 0) = 'boolean';
    IF res THEN
      res := TRUE;
    END IF;
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- regex=^[-\w]*$ opts=s
CREATE OR REPLACE FUNCTION _jm_re_0(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^[-\w]*$', 's');
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION json_model_4(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  res := JSONB_TYPEOF(val) = 'array' AND JSONB_ARRAY_LENGTH(val) = 3;
  IF res THEN
    res := JSONB_TYPEOF(val -> 0) = 'boolean';
    IF res THEN
      res := JSONB_TYPEOF(val -> 1) = 'string' AND _jm_re_0(JSON_VALUE(val -> 1, '$' RETURNING TEXT), NULL, NULL);
      IF res THEN
        res := TRUE;
      END IF;
    END IF;
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION json_model_5(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN json_model_2(val, NULL, NULL) OR json_model_3(val, NULL, NULL) OR json_model_4(val, NULL, NULL);
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  arr_0_idx INT8;
  arr_0_item JSONB;
BEGIN
  res := JSONB_TYPEOF(val) = 'array';
  IF res THEN
    FOR arr_0_idx IN 0 .. JSONB_ARRAY_LENGTH(val) - 1 LOOP
      arr_0_item := val -> arr_0_idx;
      res := json_model_5(arr_0_item, NULL, NULL);
      IF NOT res THEN
        EXIT;
      END IF;
    END LOOP;
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION check_model_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"":"json_model_1","Comment":"json_model_2","Test2":"json_model_3","Test3":"json_model_4","Test":"json_model_5"}';
BEGIN
  RETURN map->>name;
END;
$$ LANGUAGE plpgsql;

--
-- constant maps initialization
--
TRUNCATE jm_constant_maps;

--
-- JSON Model checking entry point
--
-- TODO INOUT rep?
CREATE OR REPLACE FUNCTION check_model(val JSONB, name TEXT, rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  fun TEXT;
BEGIN
  fun := check_model_map(name);
  IF fun IS NULL THEN
    RAISE EXCEPTION 'model for % not found', name;
  END IF;
  RETURN jm_call(fun, val, NULL, rep);
END;
$$ LANGUAGE plpgsql;
