--
-- Generated by JSON Model Compiler version 2.0b1
-- see https://github.com/clairey-zx81/json-model
--
-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

-- check $ex5 (.'$ex5')
CREATE OR REPLACE FUNCTION json_model_4(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .'$ex5'
  -- .'$ex5'.'|'.0
  res := json_model_5(val, path, rep);
  IF NOT res THEN
    -- .'$ex5'.'|'.1
    res := json_model_6(val, path, rep);
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- check $EX06 (.'$EX06')
CREATE OR REPLACE FUNCTION json_model_3(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .'$EX06'
  res := JSONB_TYPEOF(val) = 'boolean';
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- check $ (.)
CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .
  res := JSONB_TYPEOF(val) = 'array' AND JSONB_ARRAY_LENGTH(val) = 3;
  IF res THEN
    -- .0
    res := json_model_5(val -> 0, NULL, rep);
    IF res THEN
      -- .1
      res := json_model_6(val -> 1, NULL, rep);
      IF res THEN
        -- .2
        res := json_model_3(val -> 2, NULL, rep);
      END IF;
    END IF;
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- check $ex5#EX05a (.'$ex5#EX05a')
CREATE OR REPLACE FUNCTION json_model_5(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .'$ex5#EX05a'
  res := JSONB_TYPEOF(val) = 'number' AND (val)::INT8 = (val)::FLOAT8 AND (val)::INT8 >= 0;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- check $ex5#EX05b (.'$ex5#EX05b')
CREATE OR REPLACE FUNCTION json_model_6(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .'$ex5#EX05b'
  res := JSONB_TYPEOF(val) = 'string';
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION check_model_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"":"json_model_1","ex5":"json_model_4","EX06":"json_model_3"}';
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
