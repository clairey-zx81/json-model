-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

-- regex=y opts=n
CREATE OR REPLACE FUNCTION _jm_re_0(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, 'y', 'n');
END;
$$ LANGUAGE plpgsql;

-- regex=x opts=n
CREATE OR REPLACE FUNCTION _jm_re_1(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, 'x', 'n');
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res bool;
  arr_1_idx INT8;
  arr_1_item JSONB;
  arr_0_idx INT8;
  arr_0_item JSONB;
BEGIN
  res := JSONB_TYPEOF(val) = 'array';
  IF res THEN
    FOR arr_1_idx IN 0 .. JSONB_ARRAY_LENGTH(val) - 1 LOOP
      arr_1_item := val -> arr_1_idx;
      res := JSONB_TYPEOF(arr_1_item) = 'string' AND _jm_re_1(JSON_VALUE(arr_1_item, '$' RETURNING TEXT), NULL, NULL);
      IF NOT res THEN
        EXIT;
      END IF;
    END LOOP;
    IF res THEN
      FOR arr_0_idx IN 0 .. JSONB_ARRAY_LENGTH(val) - 1 LOOP
        arr_0_item := val -> arr_0_idx;
        res := JSONB_TYPEOF(arr_0_item) = 'string' AND _jm_re_0(JSON_VALUE(arr_0_item, '$' RETURNING TEXT), NULL, NULL);
        IF NOT res THEN
          EXIT;
        END IF;
      END LOOP;
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
