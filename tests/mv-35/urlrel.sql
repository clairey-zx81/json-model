-- JSON_MODEL_VERSION is 2
CREATE EXTENSION IF NOT EXISTS json_model;

CREATE OR REPLACE FUNCTION json_model_1(val JSONB, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN JSONB_TYPEOF(val) = 'string' AND jm_is_url_rel(JSON_VALUE(val, '$' RETURNING TEXT), NULL, NULL);
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

-- regex=^(((https?|s?ftp|rtsps?|s3|cm|oci)://([\w.-]+(:[^@\s]*@)?([-\w.]*|\[[a-fA-F0-9:.]+\])(:\d+)?)?(/[^/?#\s]*)*(\?[^#\s]*)?(#\S*)?|file:([^?#\s:/<>{}()!=*]+)?(/[^?#\s/]*)*(\?[^#\s]*)?(#\S*)?|(ssh|telnet|mailto):([-+!#$%&'`*/=?^{}|~_a-z0-9]+)(\.([-+!#$%&'`*/=?^{}|~_a-z0-9]+))*@([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*|urn:[\w.:-]+)|([^?#\s:/<>{}()!=*]+)?(/[^?#\s/]*)*(\?[^#\s]*)?(#\S*)?)$ opts=n
CREATE OR REPLACE FUNCTION jm_is_url_rel(val TEXT, path TEXT[], rep jm_report_entry[])
RETURNS BOOLEAN CALLED ON NULL INPUT IMMUTABLE PARALLEL SAFE AS $$
BEGIN
  RETURN regexp_like(val, '^(((https?|s?ftp|rtsps?|s3|cm|oci)://([\w.-]+(:[^@\s]*@)?([-\w.]*|\[[a-fA-F0-9:.]+\])(:\d+)?)?(/[^/?#\s]*)*(\?[^#\s]*)?(#\S*)?|file:([^?#\s:/<>{}()!=*]+)?(/[^?#\s/]*)*(\?[^#\s]*)?(#\S*)?|(ssh|telnet|mailto):([-+!#$%&''`*/=?^{}|~_a-z0-9]+)(\.([-+!#$%&''`*/=?^{}|~_a-z0-9]+))*@([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*|urn:[\w.:-]+)|([^?#\s:/<>{}()!=*]+)?(/[^?#\s/]*)*(\?[^#\s]*)?(#\S*)?)$', 'n');
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
