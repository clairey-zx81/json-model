--
-- Generated by JSON Model Compiler version 2.0b1
-- see https://github.com/clairey-zx81/json-model
--
-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION _jm_cst_0(value JSONB)
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  constants JSONB = JSONB '["X","XX","XXX"]';
BEGIN
  RETURN constants @> value;
END;
$$ LANGUAGE plpgsql;

-- check $XXX (.'$XXX')
CREATE OR REPLACE FUNCTION json_model_2(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- .'$XXX'
  res := JSONB_TYPEOF(val) IN ('null', 'boolean', 'number', 'string') AND _jm_cst_0(val);
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

-- regex=^[0-9]+$ opts=n
CREATE OR REPLACE FUNCTION _jm_re_0(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^[0-9]+$', 'n');
END;
$$ LANGUAGE plpgsql;

-- object .
CREATE OR REPLACE FUNCTION _jm_obj_0(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  must_count int;
  prop TEXT;
  pval JSONB;
BEGIN
  IF NOT (JSONB_TYPEOF(val) = 'object') THEN
    RETURN FALSE;
  END IF;
  must_count := 0;
  FOR prop, pval IN SELECT * FROM JSONB_EACH(val) LOOP
    IF prop = 'foo' THEN
      -- handle must foo property
      must_count := must_count + 1;
      -- .foo
      res := JSONB_TYPEOF(pval) = 'string' AND jm_is_valid_date(JSON_VALUE(pval, '$' RETURNING TEXT), NULL, rep);
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    ELSEIF prop = 'bla' THEN
      -- handle may bla property
      -- .bla
      res := JSONB_TYPEOF(pval) = 'boolean';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    ELSEIF json_model_2(TO_JSONB(prop), NULL, rep) THEN
      -- handle 1 key props
      -- .'$XXX'
      res := JSONB_TYPEOF(pval) = 'number' AND (pval)::FLOAT8 >= 0.0;
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    ELSEIF _jm_re_0(prop, path, rep) THEN
      -- handle 1 re props
      -- .'/^[0-9]+$/'
      res := JSONB_TYPEOF(pval) = 'number' AND (pval)::INT8 = (pval)::FLOAT8 AND (pval)::INT8 >= 0;
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    ELSE
      -- handle other props
      -- .''
      res := JSONB_TYPEOF(pval) = 'null';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
    END IF;
  END LOOP;
  IF must_count <> 1 THEN
    RETURN FALSE;
  END IF;
  RETURN TRUE;
END;
$$ LANGUAGE PLpgSQL;

-- check $ (.)
CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
BEGIN
  -- object with must/may/regex/ref/others
  -- .
  res := _jm_obj_0(val, path, rep);
  RETURN res;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION check_model_map(name TEXT)
RETURNS TEXT STRICT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  map JSONB := JSONB '{"":"json_model_1","XXX":"json_model_2"}';
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
