-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION json_model;" to load this file. \quit

-- DROP TYPE IF EXISTS jm_report_entry CASCADE;
-- DROP TABLE IF EXISTS jm_constant_maps;

CREATE TYPE jm_report_entry AS (message TEXT, path TEXT[]);
-- _jm_report_entry is jm_report_entry[]

--
-- constant maps for object tags
--
CREATE TABLE jm_constant_maps(
  mapname TEXT NOT NULL,
  tagval JSONB NOT NULL,
  value TEXT NOT NULL,
  PRIMARY KEY(mapname, tagval)
);

CREATE OR REPLACE FUNCTION
  jm_cmap_get(TEXT, JSONB)
RETURNS TEXT STRICT STABLE PARALLEL SAFE AS $$
  SELECT value
  FROM jm_constant_maps
  WHERE mapname = $1 AND tagval = $2;
$$ LANGUAGE sql;

--
-- dynamically call a function by name
--
CREATE OR REPLACE FUNCTION
  jm_call(fun TEXT, val JSONB, path TEXT[], rep jm_report_entry[])
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

--
-- JSON Model predef validations
--
-- $DATE
CREATE OR REPLACE FUNCTION
  jm_is_valid_date(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM val::DATE;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $DATETIME
CREATE OR REPLACE FUNCTION
  jm_is_valid_datetime(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM val::TIMESTAMP;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $TIME
CREATE OR REPLACE FUNCTION
  jm_is_valid_time(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM val::TIME;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $REGEX
CREATE OR REPLACE FUNCTION
  jm_is_valid_regex(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM '' ~ val;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $EXTREG
CREATE OR REPLACE FUNCTION
  jm_is_valid_extreg(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
  SELECT jm_is_valid_regex(val, path, rep);
$$ LANGUAGE sql;

-- $UUID
CREATE OR REPLACE FUNCTION
  jm_is_valid_uuid(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM val::UUID;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $JSON
CREATE OR REPLACE FUNCTION
  jm_is_valid_json(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  IF val IS NULL THEN
    RETURN FALSE;
  END IF;
  PERFORM val::JSON;
  RETURN TRUE;
EXCEPTION
  WHEN data_exception THEN
    RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

-- $URL (loose)
CREATE OR REPLACE FUNCTION
  jm_is_valid_url(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN val IS NOT NULL AND val ~ '^((https?|file)://|\.)\S*$';
END;
$$ LANGUAGE plpgsql;

-- $EMAIL
CREATE OR REPLACE FUNCTION
  jm_is_valid_email(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN val IS NOT NULL AND val ~ '^[_A-Za-z0-9_.]+@[_A-Za-z0-9_.]+$';
END;
$$ LANGUAGE plpgsql;

--
-- array uniqueness by sorting and adjacent item comparison
--
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

-- WTF
CREATE OR REPLACE FUNCTION
  jm_object_size(val JSONB)
RETURNS INT STRICT IMMUTABLE PARALLEL SAFE AS $$
  SELECT COUNT(*) FROM JSONB_EACH(val);
$$ LANGUAGE sql;

--
-- (slow) dynamic value to constant comparison
--
CREATE OR REPLACE FUNCTION
  jm_check_constraint(val JSONB, op TEXT, cst ANYELEMENT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
DECLARE
  cval JSONB := val;
  vt TEXT := JSONB_TYPEOF(val);
  ct TEXT := pg_typeof(cst);
  const JSONB;
BEGIN
  -- filter on types
  IF vt IN ('null', 'boolean') THEN
    RETURN FALSE;
  END IF;

  IF ct = 'unknown' THEN
    const := TO_JSONB(cst::TEXT);
  ELSEIF ct IN ('integer', 'numeric', 'double precision') THEN
    const := TO_JSONB(cst);
  ELSE
    RAISE EXCEPTION 'unexpected constant type %', ct;
  END IF;

  -- get an integer in some cases
  IF ct = 'integer' THEN
    IF vt = 'number' THEN
      NULL;
    ELSEIF vt = 'string' THEN
      cval := TO_JSONB(LENGTH(JSON_VALUE(val, '$' RETURNING TEXT)));
    ELSEIF vt = 'array' THEN
      cval := TO_JSONB(JSONB_ARRAY_LENGTH(val));
    ELSEIF vt = 'object' THEN
      cval := TO_JSONB(jm_object_size(val));
    ELSE
      RAISE NOTICE 'unexpected value type for integer comparison: %', vt;
    END IF;
  END IF;

  -- actual comparison, which may fail depending on types
  IF op = '=' THEN
    RETURN cval = const;
  ELSEIF op = '!=' THEN
    RETURN cval <> const;
  ELSEIF op = '<' THEN
    RETURN cval < const;
  ELSEIF op = '<=' THEN
    RETURN cval <= const;
  ELSEIF op = '>' THEN
    RETURN cval < const;
  ELSEIF op = '>=' THEN
    RETURN cval >= const;
  ELSE
    RAISE EXCEPTION 'unexpected comparison operator %', op;
  END IF;
END;
$$ LANGUAGE plpgsql;

--
-- FIXME REPORTING
--
-- clear current report
CREATE OR REPLACE PROCEDURE
  jm_report_free_entries(INOUT rep jm_report_entry[]) AS $$
BEGIN
  rep := ARRAY[];
END;
$$ LANGUAGE plpgsql;

-- TODO INOUT
CREATE OR REPLACE PROCEDURE
  jm_report_add_entry(INOUT rep jm_report_entry[], message TEXT, path TEXT[]) AS $$
BEGIN
  rep := array_append(rep, ROW(message, path));
END;
$$ LANGUAGE plpgsql;
