-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION json_model_2(val JSONB, path TEXT[], rep jm_report_entry[])
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
      res := JSONB_TYPEOF(arr_0_item) = 'number' AND (arr_0_item)::INT8 = (arr_0_item)::FLOAT8 AND (arr_0_item)::INT8 >= 0;
      IF NOT res THEN
        EXIT;
      END IF;
    END LOOP;
  END IF;
  IF res THEN
    res := jm_array_is_unique(val, NULL, NULL);
  END IF;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_f_0(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN JSONB_TYPEOF(val) = 'boolean';
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_f_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN JSONB_TYPEOF(val) = 'boolean';
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION json_model_1_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"auto.diverse":"_jm_f_0","c":"json_model_2","dynpy":"json_model_2","java":"json_model_2","js":"json_model_2","pl":"json_model_2","py":"json_model_2","schema":"json_model_2","sql":"json_model_2","ts":"_jm_f_1"}';
BEGIN
  RETURN map->>name;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  pfun TEXT;
  prop TEXT;
  pval JSONB;
BEGIN
  IF NOT (JSONB_TYPEOF(val) = 'object') THEN
    RETURN FALSE;
  END IF;
  FOR prop, pval IN SELECT * FROM JSONB_EACH(val) LOOP
    IF json_model_1_map(prop) IS NOT NULL THEN
      pfun := json_model_1_map(prop);
      IF NOT jm_call(pfun, pval, NULL, NULL) THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    IF STARTS_WITH(prop, '#') THEN
      res := JSONB_TYPEOF(pval) = 'string';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    ELSE
      RETURN FALSE;
    END IF;
  END LOOP;
  RETURN TRUE;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION check_model_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"":"json_model_1","ErrorIndex":"json_model_2"}';
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
