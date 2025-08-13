#
# PostGres eXtenSion makefile
#
SHELL   = /bin/bash
.ONESHELL:

EXTENSION   = json_model
DATA    = json_model--2.0.sql

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

#
# cleanup
#
clean: clean.pgxn clean.local java.clean pl.clean js.clean

%.clean:
	test -f $*/Makefile && $(MAKE) -C $* clean
	exit 0

clean.local:
	$(RM) -r __pycache__

#
# Postgres
#
.PHONY: clean.pgxn
clean.pgxn:
	$(RM) json_model.tgz

.PHONY: pgxn
pgxn: json_model.tgz

json_model.tgz:
	tar czf $@ json_model--2.0.sql json_model.control META.json Makefile
