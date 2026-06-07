-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'n';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'null';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_1(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'b';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'boolean';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_2(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'i';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'number' AND (pval)::INT8 = (pval)::FLOAT8;
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_3(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'u';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'number' AND (pval)::INT8 = (pval)::FLOAT8 AND (pval)::INT8 >= 0;
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_4(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'f';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'number';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_5(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 's';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_6(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'a';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'array';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;

CREATE OR REPLACE FUNCTION _jm_obj_7(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'd' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'string' AND JSON_VALUE(pval, '$' RETURNING TEXT) = 'o';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'v' THEN
      must_count := must_count + 1;
      res := JSONB_TYPEOF(pval) = 'object';
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN must_count = 2;
END;
$$ LANGUAGE PLpgSQL;


CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  tag_0 JSONB;
  fun_0 TEXT;
BEGIN
  res := JSONB_TYPEOF(val) = 'object';
  IF res THEN
    IF val ? 'd' THEN
      tag_0 := val -> 'd';
      fun_0 := jm_cmap_get('_jm_map_0', tag_0);
      res := fun_0 IS NOT NULL AND jm_call(fun_0, val, NULL, NULL);
    ELSE
      res := FALSE;
    END IF;
  END IF;
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
INSERT INTO jm_constant_maps(mapname, tagval, value) VALUES
  ('_jm_map_0', JSONB '"n"', '_jm_obj_0'),
  ('_jm_map_0', JSONB '"b"', '_jm_obj_1'),
  ('_jm_map_0', JSONB '"i"', '_jm_obj_2'),
  ('_jm_map_0', JSONB '"u"', '_jm_obj_3'),
  ('_jm_map_0', JSONB '"f"', '_jm_obj_4'),
  ('_jm_map_0', JSONB '"s"', '_jm_obj_5'),
  ('_jm_map_0', JSONB '"a"', '_jm_obj_6'),
  ('_jm_map_0', JSONB '"o"', '_jm_obj_7')
;

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
