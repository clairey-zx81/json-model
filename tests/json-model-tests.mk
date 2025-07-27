# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC = jmc
JMC.opts    = --check --quiet
JMC.cmd = \
	$(JMC) $(JMC.opts) \
        -m "https://json-model.org/models/ ../../models/" \
        -m "https://json-model.org/tests/ ./"

# JSON Schema Checker
JSC = jsu-check --quiet

# inputs, skip _*
F.mjs   = $(wildcard [a-zA-Z]*.model.js)
F.myaml = $(wildcard *.model.yaml)
F.model = $(wildcard [a-zA-Z]*.model.json) \
          $(F.mjs:%.model.js=%.model.json) \
          $(F.myaml:%.model.yaml=%.model.json)
F.bads  = $(wildcard ../bads/[a-zA-Z]*.model.json)

F.root  = $(F.model:%.model.json=%)

# derived
F.json = $(F.mjs:%.model.js=%.model.json) $(F.myaml:%.model.yaml=%.model.json)
F.UO    = $(F.root:%=%.UO.json)
F.JO    = $(F.root:%=%.JO.json)
F.PO    = $(F.root:%=%.PO.json)
F.EO    = $(F.root:%=%.schema.json)

# code generation
F.c     = $(F.root:%=%.c)
F.py    = $(F.root:%=%.py)
F.js    = $(F.root:%=%.js)
F.out   = $(F.root:%=%.out)
F.sql   = $(F.root:%=%.sql)
F.pl    = $(F.root:%=%.pl)
# test results
F.cc    = $(F.root:%=%.c.check)
F.pyc   = $(F.root:%=%.py.check)
F.jsc   = $(F.root:%=%.js.check)
F.sqlc  = $(F.root:%=%.sql.check)
F.plc   = $(F.root:%=%.pl.check)

# all generated
F.gen   = \
    $(F.json) $(F.UO) $(F.PO) $(F.EO) \
    $(F.c) $(F.py) $(F.cc) $(F.sql) $(F.pl) \
    $(F.pyc) $(F.js) $(F.jsc) $(F.sqlc) $(F.plc)

.PHONY: all
all: $(F.gen)

.PHONY: js clean.js
js: $(F.js) $(F.jsc)

clean.js:
	$(RM) $(F.js) $(F.jsc)

.PHONY: pl clean.pl
pl: $(F.pl) $(F.plc)

clean.pl:
	$(RM) $(F.pl) $(F.plc)

-include local.mk

.PHONY: clean.gen
clean.gen:
	$(RM) $(F.gen)

.PHONY: gen
gen: $(F.gen)

.PHONY: check
check:
	$(MAKE) clean.gen
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) *.o *.out *.mjs *.mpy

.PHONY: sql clean.sql
sql: $(F.sql) $(F.sqlc)

clean.sql:
	$(RM) *.sql *.sql.check *.values.csv

.PHONY: json
json: $(F.json)

%.model.json: %.model.js
	$(JMC.cmd) -N ./$< > $@

%.model.json: %.model.yaml
	$(JMC.cmd) -N ./$< > $@

.PHONY: UO
UO: $(F.UO)
%.UO.json: %.model.json
	$(JMC.cmd) -UO ./$< > $@

.PHONY: PO
PO: $(F.PO)
%.PO.json: %.model.json
	$(JMC.cmd) -PO ./$* > $@

# dump internal JSON IR
%.JO.json: %.model.json
	$(JMC.cmd) -JO ./$* > $@

.PHONY: schema
schema: $(F.EO)
%.schema.json: %.model.json
	$(JMC.cmd) -EO -ns ./$< > $@

# regular expression library for C generated code
RELIB    = re2

%.c: %.model.json
	$(JMC.cmd) -re $(RELIB) -o $@ ./$<

CC        = gcc
CPPFLAGS  = -DCHECK_FUNCTION_NAME=check_model -I../../json_model/runtime
CFLAGS    = -Wall -Wno-address -Wno-c23-extensions -Wno-unused-variable -Wno-unused-function -Ofast

ifeq ($(RELIB), pcre2)
CPPFLAGS  += -DREGEX_ENGINE_PCRE2
LDFLAGS   = json-model.o -ljansson -lpcre2-8 main.o -lm
else
CPPFLAGS  += -I/usr/local/include -DREGEX_ENGINE_RE2
LDFLAGS   = -L/usr/local/lib json-model.o -ljansson -lcre2 -lpthread -lre2 main.o -lm
endif

#
# C Backend
#
json-model.o: ../../json_model/runtime/json-model.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

main.o: ../../json_model/runtime/main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(F.out): json-model.o main.o

%.out: json-model.o main.o

%.out: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) -o $@

%.c.check: %.out
	shopt -s nullglob
	set -o pipefail
	$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

#
# Python Backend
#
%.py: %.model.json
	$(JMC.cmd) -v -o $@ ./$<
	chmod a+rx $@

%.py.check: %.py
	shopt -s nullglob
	set -o pipefail
	./$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

#
# JavaScript Backend
#
%.js: %.model.json
	$(JMC.cmd) -v -o $@ $<
	chmod a+rx $@

%.js.check: %.js
	shopt -s nullglob
	set -o pipefail
	./$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

#
# PL/pgSQL Backend
#
%.sql: %.model.json
	$(JMC.cmd) --no-reporting -o $@ $<

%.values.csv: %.values.json
	../values2csv.py $< $@

%.sql.check: %.sql %.values.json ../test_sql_csv.sql ../test_sql.sh
	shopt -s nullglob
	../test_sql.sh $< $*.*.true.json $*.*.false.json $*.values.json > $@
	status=$$?
	# TODO check for errors to ignore

#
# Perl Backend
#
%.pl: %.model.json
	$(JMC.cmd) --no-reporting -o $@ $<

# NOTE no -r for now
# TODO check for specific pl error
%.pl.check: %.pl %.values.json
	shopt -s nullglob
	set -o pipefail
	./$< $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -t $*.values.json >> $@
	    status=$$?
	fi
	if [ $$status -ne 0 ] ; then
	    test -f $*.errors.json && status=0
	fi
	exit $$status

#
# Generated JSON Schema checks
#
F.schema    = $(F.root:%=%.schema.json)

.PHONY: check.schema
check.schema: $(F.sXc)

# helpers
%.ALL:
	$(MAKE) $*.model.json $*.schema.json \
	    $*.c $*.c.check \
	    $*.py $*.py.check \
	    $*.js $*.js.check \
	    $*.sql $*.sql.check \
	    $*.pl $*.pl.check

%.CLEAN:
	$(RM) $*.schema.json \
	    $*.c $*.c.check \
	    $*.py $*.py.check \
	    $*.js $*.js.check \
	    $*.sql $*.sql.check \
	    $*.pl $*.pl.check

# TODO JSON Schema checks on test values?
