--
-- Generated by JSON Model Compiler version 2.0b1
-- see https://github.com/clairey-zx81/json-model
--
-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

-- regex=a opts=n
CREATE OR REPLACE FUNCTION _jm_re_0(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, 'a', 'n');
END;
$$ LANGUAGE plpgsql;

-- object .'^'.0
CREATE OR REPLACE FUNCTION _jm_obj_0(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  prop TEXT;
  pval JSONB;
BEGIN
  IF NOT (JSONB_TYPEOF(val) = 'object') THEN
    RETURN FALSE;
  END IF;
  FOR prop, pval IN SELECT * FROM JSONB_EACH(val) LOOP
    IF _jm_re_0(prop, path, rep) THEN
      -- handle 1 re props
      -- .'^'.0.'/a/'
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

-- object .'^'.1
CREATE OR REPLACE FUNCTION _jm_obj_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  prop TEXT;
  pval JSONB;
BEGIN
  IF NOT (JSONB_TYPEOF(val) = 'object') THEN
    RETURN FALSE;
  END IF;
  FOR prop, pval IN SELECT * FROM JSONB_EACH(val) LOOP
    IF prop = 'a' THEN
      -- handle may a property
      -- .'^'.1.a
      res := JSONB_TYPEOF(pval) = 'null';
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

-- check $ (.)
CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  xc_0 int;
  xr_0 bool;
BEGIN
  -- NOT ^ to | because both empty objects are ok
  -- .
  -- generic xor list
  xc_0 := 0;
  -- .'^'.0
  xr_0 := _jm_obj_0(val, path, rep);
  IF xr_0 THEN
    xc_0 := xc_0 + 1;
  END IF;
  -- .'^'.1
  xr_0 := _jm_obj_1(val, path, rep);
  IF xr_0 THEN
    xc_0 := xc_0 + 1;
  END IF;
  res := xc_0 = 1;
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION check_model_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"":"json_model_1"}';
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
