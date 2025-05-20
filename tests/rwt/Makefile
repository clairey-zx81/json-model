# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC = jmc
JMC.opts    = --check --quiet
JMC.cmd = \
	$(JMC) $(JMC.opts) \
        -m "https://json-model.org/models ../../models" \
        -m "https://json-model.org/tests ."

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
F.PO    = $(F.root:%=%.PO.json)
F.EO    = $(F.root:%=%.schema.json)
F.SO    = $(F.root:%=%.py)
F.sc    = $(F.root:%=%.scheck.out)
F.js    = $(F.root:%=%.jcheck.out)
F.sXc   = \
    schema.jcheck.out \
    schema.dcheck.out schema.dcheck2.out \
    schema.scheck.out schema.scheck2.out

# expermimental C and Python generation
F.xc    = $(F.root:%=%.x.c)
F.xpy   = $(F.root:%=%.x.py)
F.exe   = $(F.root:%=%.exe)
F.cc    = $(F.root:%=%.ccheck.out)
F.pc    = $(F.root:%=%.pcheck.out)

# all generated
F.gen   = $(F.UO) $(F.PO) $(F.EO) $(F.SO) $(F.sc) \
          $(F.json) $(F.js) $(F.sXc)

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
	$(RM) *.o *.exe

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

.PHONY: schema
schema: $(F.EO)
%.schema.json: %.model.json
	$(JMC.cmd) -EO -ns ./$< > $@

.PHONY: py
py: $(F.SO)
%.py: %.model.json
	$(JMC.cmd) -SO -v --code ./$< > $@
	chmod a+rx $@

#
# Experimental section
#

F.x     = $(F.xc) $(F.exe) $(F.cc) $(F.xpy) $(F.pc)

.PHONY: clean.x
clean.x:
	$(RM) $(F.x) json-model.o main.o

.PHONY: check.x
check.x: clean.x
	$(MAKE) $(F.x)

clean: clean.x

%.x.c: %.model.json
	$(JMC.cmd) -XO -v --format c ./$< > $@

CC        = gcc
CPPFLAGS  = -DCHECK_FUNCTION_NAME=check_model -I../../json_model/runtime
CFLAGS    = -Wall -Wno-address -O2
LDFLAGS   = json-model.o -ljansson -lpcre2-8 main.o

json-model.o: ../../json_model/runtime/json-model.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

main.o: ../../json_model/runtime/main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(F.exe): json-model.o main.o

%.exe: json-model.o main.o

%.exe: %.x.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) -o $@

%.ccheck.out: %.exe
	shopt -s nullglob
	set -o pipefail
	$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

%.x.py: %.model.json
	$(JMC.cmd) -XO -v --format py ./$< > $@
	chmod a+rx $@

%.pcheck.out: %.x.py
	shopt -s nullglob
	set -o pipefail
	./$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

.PHONY: %.x
%.x: %.model.json
	shopt -s nullglob
	$(RM) $*.x.c $*.exe $*.ccheck.out $*.x.py $*.pcheck.out
	$(MAKE) $*.x.c $*.exe $*.ccheck.out $*.x.py $*.pcheck.out

.PHONY: %.xALL
%.xALL:
	$(MAKE) $*.x $*.ALL
	$(MAKE) $*.jcheck.out
	for f in $*.?check.out ; do
	  echo "# $$f"
	  cat $$f
	done

#
# Static value checks
#
.PHONY: scheck
scheck: $(F.sc)
	egrep -v 'true.*PASS|false.*FAIL' *.scheck.out | egrep -v '^(json-model|l10n|schema|model)'
	exit 0

%.scheck.out: %.model.json
	shopt -s nullglob
	$(JMC.cmd) -v -SO -nc ./$< $*.*.true.json $*.*.false.json > $@

#
# Generated JSON Schema checks
#
.PHONY: check.schema
check.schema: $(F.sXc)

F.schema    = $(F.root:%=%.schema.json)

# NOTE some failures are expected because external refs are not handled.
schema.jcheck.out: $(F.schema)
	set -o pipefail
	for f in $(F.schema) ; do
	  if jsu-check --quiet $$f ; then
	    echo "$$f: PASS"
	  else
	    echo "$$f: FAIL"
	  fi
	done | sort > $@

schema.scheck.out: $(F.schema)
	set -o pipefail
	$(JMC) --auto --check --quiet -SO ../../models/json-schema-draft-2020-12.model.json $^ |
	  sort > $@

# FIXME json-schema-draft-tighter.model.json: KO, mandatory $schema

schema.scheck2.out: $(F.schema)
	set -o pipefail
	$(JMC) --auto --check --quiet -SO ../../models/json-schema-draft-2020-12-tight.model.json $^ |
	  sort > $@

#
# JSON model value checks with generated JSON schemas
#
# this is not perfect:
# - models distinguish between floats and ints, schema not really.
# - the json schema library used does not seem to implement "format" checks.
# - the implementation is _very_ slow.
#

.PHONY: jcheck
jcheck: $(F.js)
	egrep -v 'true.*PASS|false.*FAIL' *.jcheck.out |
	  egrep -v '^(json-model|l10n|schema|model|.*:json schema check skipped)'
	exit 0

# default case
%.jcheck.out: %.schema.json
	shopt -s nullglob
	set -o pipefail
	nrefs=$$(egrep '"\$$(\.|https:)' $*.model.json | wc -l)
	iserr=$$(grep '"ERROR": ' $< | wc -l)
	if [ $$nrefs == "0" -a $$iserr == "0" ] ; then
	  $(JSC) $< $*.*.true.json $*.*.false.json | sort > $@
	elif [ $$nrefs != "0" ] ; then
	  echo "json schema check skipped, $$nrefs external not supported" > $@
	elif [ $$iserr != "0" ] ; then
	  echo "json schema check skipped, ERROR reported in generated schema" > $@
	else
	  exit 1
	fi

#
# generate everything from a model
#
.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.schema.json $*.py $*.scheck.out
	$(MAKE) $*.UO.json $*.PO.json $*.schema.json $*.py $*.scheck.out
