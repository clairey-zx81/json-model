-- complain if script is sourced in psql, rather than via CREATE EXTENSION
-- \echo Use "CREATE EXTENSION json_model;" to load this file. \quit

DROP TYPE IF EXISTS jm_report_entry CASCADE;
CREATE TYPE jm_report_entry AS (message TEXT, path TEXT[]);
-- _jm_report_entry is jm_report_entry[]

CREATE OR REPLACE FUNCTION jm_call(fun TEXT, val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  res BOOLEAN;
BEGIN
  -- RAISE NOTICE 'jm_call: calling %', fun;
  EXECUTE FORMAT('SELECT %s($1, $2, $3)', fun)
    INTO res
    USING val, path, rep;
  RETURN res;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION jm_is_valid_date(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  PERFORM val::DATE;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION jm_is_valid_datetime(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  PERFORM val::TIMESTAMP;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION jm_is_valid_regex(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  PERFORM '' ~ val;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION jm_is_valid_uuid(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  PERFORM val::UUID;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION jm_is_valid_url(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  -- TODO improve checks! . -> \w?
  RETURN val ~ E'^((https?|file)://.*|\\.)';
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION
  jm_array_is_unique(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  previous JSONB := NULL;
  rec RECORD;
BEGIN
  IF jsonb_typeof(val) != 'array' THEN
    RETURN FALSE;
  END IF;
  FOR rec IN
    SELECT jv FROM JSONB_ARRAY_ELEMENTS(val) AS jv ORDER BY 1
  LOOP
    IF previous IS NOT NULL AND previous = rec.jv THEN
      RETURN FALSE;
    END IF;
    previous := rec.jv;
  END LOOP;
  RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE
  jm_report_free_entries(INOUT rep jm_report_entry[]) AS $$
BEGIN
    rep := ARRAY[];
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE PROCEDURE
  jm_report_add_entry(INOUT rep jm_report_entry[], message TEXT, path TEXT[]) AS $$
BEGIN
  rep := array_append(rep, ROW(message, path));
END;
$$ LANGUAGE plpgsql;
