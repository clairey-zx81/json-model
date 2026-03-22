-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
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
    IF prop = 'host' THEN
      res := JSONB_TYPEOF(pval) = 'string' AND jm_is_host(JSON_VALUE(pval, '$' RETURNING TEXT), NULL, NULL) AND LENGTH(JSON_VALUE(pval, '$' RETURNING TEXT)) <= 255;
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'ipv4' THEN
      res := JSONB_TYPEOF(pval) = 'string' AND jm_is_ip4(JSON_VALUE(pval, '$' RETURNING TEXT), NULL, NULL);
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    ELSEIF prop = 'ipv6' THEN
      res := JSONB_TYPEOF(pval) = 'string' AND jm_is_ip6(JSON_VALUE(pval, '$' RETURNING TEXT), NULL, NULL);
      IF NOT res THEN
        RETURN FALSE;
      END IF;
      CONTINUE;
    END IF;
    RETURN FALSE;
  END LOOP;
  RETURN TRUE;
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

-- regex=^([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*$ opts=ni
CREATE OR REPLACE FUNCTION jm_is_host(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*$', 'ni');
END;
$$ LANGUAGE plpgsql;

-- regex=^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$ opts=n
CREATE OR REPLACE FUNCTION jm_is_ip4(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$', 'n');
END;
$$ LANGUAGE plpgsql;

-- regex=^[a-f0-9:]+$ opts=ni
CREATE OR REPLACE FUNCTION jm_is_ip6(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^[a-f0-9:]+$', 'ni');
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
