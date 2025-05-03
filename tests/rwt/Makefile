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
F.DO    = $(F.root:%=%.DO.out)
F.SO    = $(F.root:%=%.py)
F.dc    = $(F.root:%=%.dcheck.out)
F.sc    = $(F.root:%=%.scheck.out)
F.js    = $(F.root:%=%.jcheck.out)
F.sXc   = schema.jcheck.out \
    schema.dcheck.out schema.scheck.out \
    schema.dcheck2.out schema.scheck2.out

# all generated
F.gen   = $(F.UO) $(F.PO) $(F.EO) $(F.DO) $(F.dc) $(F.SO) $(F.sc) $(F.json) $(F.js) $(F.sXc)

-include local.mk

.PHONY: gen
gen: $(F.gen)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.gen)

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
	$(JMC.cmd) -PO ./$< > $@

.PHONY: schema
schema: $(F.EO)
%.schema.json: %.model.json
	$(JMC.cmd) -EO -ns ./$< > $@

.PHONY: DO
DO: $(F.DO)
%.DO.out: %.model.json
	$(JMC.cmd) -DO --code ./$< | sed -e 's/<code object .*>/<*>/' > $@

.PHONY: py
py: $(F.SO)
%.py: %.model.json
	$(JMC.cmd) -SO --code ./$< > $@

#
# Dynamic value checks
#
.PHONY: dcheck
dcheck: $(F.dc)
	egrep -v 'true.*PASS|false.*FAIL' *.dcheck.out | egrep -v '^(json-model|l10n|schema)'
	exit 0

%.dcheck.out: %.model.json
	shopt -s nullglob
	$(JMC.cmd) -v -DO -nc ./$< $*.*.true.json $*.*.false.json | sort > $@

#
# Static value checks
#
.PHONY: scheck
scheck: $(F.sc)
	egrep -v 'true.*PASS|false.*FAIL' *.scheck.out | egrep -v '^(json-model|l10n|schema)'
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
	for f in $(F.schema) ; do
	  if jsu-check --quiet $$f ; then
	    echo "$$f: PASS"
	  else
	    echo "$$f: FAIL"
	  fi
	done | sort > $@

schema.dcheck.out: $(F.schema)
	$(JMC) --auto --check --quiet -DO ../../models/json-schema-draft-2020-12.model.json $^ |
	  sort > $@

schema.scheck.out: $(F.schema)
	$(JMC) --auto --check --quiet -SO ../../models/json-schema-draft-2020-12.model.json $^ |
	  sort > $@

# FIXME json-schema-draft-tighter.model.json: KO, mandatory $schema

schema.dcheck2.out: $(F.schema)
	$(JMC) --auto --check --verbose -DO ../../models/json-schema-draft-2020-12-tight.model.json $^ |
	  sort > $@

schema.scheck2.out: $(F.schema)
	$(JMC) --auto --check --quiet -SO ../../models/json-schema-draft-2020-12-tight.model.json $^ |
	  sort > $@

#
# JSON model value checks with generated JSON schemas
#
# this is not perfect:
# - models distinguish between floats and ints, schema not really.
# - the json schema library used does not seem to implement "format" checks.
#

.PHONY: jcheck
jcheck: $(F.js)
	egrep -v 'true.*PASS|false.*FAIL' *.jcheck.out | egrep -v '^(json-model|l10n|schema)'
	exit 0

# default case
%.jcheck.out: %.schema.json
	shopt -s nullglob
	$(JSC) $< $*.*.true.json $*.*.false.json | sort > $@

#
# generate everything from a model
#
.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py $*.scheck.out
	$(MAKE) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py $*.scheck.out
