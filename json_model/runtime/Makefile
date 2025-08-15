#
# PostGres eXtenSion makefile
#
SHELL   = /bin/bash
.ONESHELL:

#
# cleanup
#
clean: sql.clean clean.local java.clean pl.clean js.clean c.clean

%.clean:
	test -f $*/Makefile && $(MAKE) -C $* clean
	exit 0

clean.local:
	$(RM) -r __pycache__
