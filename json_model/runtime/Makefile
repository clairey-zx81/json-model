#
# PostGres eXtenSion makefile
#

EXTENSION   = json_model
DATA    = json_model--2.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

# pgxn

clean: pgxn.clean
.PHONY: pgxn.clean
pgxn.clean:
	$(RM) json_model.tgz

pgxn: json_model.tgz
json_model.tgz:
	tar czf $@ json_model--2.0.sql json_model.control META.json Makefile
