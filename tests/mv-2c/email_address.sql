-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN JSONB_TYPEOF(val) = 'string' AND jm_is_email(JSON_VALUE(val, '$' RETURNING TEXT), NULL, NULL);
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

-- regex=^([-+!#$%&'`*/=?^{}|~_a-z0-9]+)(\.([-+!#$%&'`*/=?^{}|~_a-z0-9]+))*@([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*$ opts=ni
CREATE OR REPLACE FUNCTION jm_is_email(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^([-+!#$%&''`*/=?^{}|~_a-z0-9]+)(\.([-+!#$%&''`*/=?^{}|~_a-z0-9]+))*@([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*$', 'ni');
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
