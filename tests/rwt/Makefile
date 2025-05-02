# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC.opts    = --check --quiet
JMC = jmc $(JMC.opts) \
        -m "https://json-model.org/models ." \
        -m "https://json-model.org/tests ."

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

F.gen   = $(F.UO) $(F.PO) $(F.EO) $(F.DO) $(F.dc) $(F.SO) $(F.sc) $(F.json) $(F.js)

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
	$(JMC) -N ./$< > $@

%.model.json: %.model.yaml
	$(JMC) -N ./$< > $@

.PHONY: UO
UO: $(F.UO)
%.UO.json: %.model.json
	$(JMC) -UO ./$< > $@

.PHONY: PO
PO: $(F.PO)
%.PO.json: %.model.json
	$(JMC) -PO ./$< > $@

.PHONY: schema
schema: $(F.EO)
%.schema.json: %.model.json
	$(JMC) -EO ./$< > $@

.PHONY: DO
DO: $(F.DO)
%.DO.out: %.model.json
	$(JMC) -DO --code ./$< | sed -e 's/<code object .*>/<*>/' > $@

.PHONY: py
py: $(F.SO)
%.py: %.model.json
	$(JMC) -SO --code ./$< > $@

#
# Dynamic CHECKs
#
.PHONY: dcheck
dcheck: $(F.dc)
	egrep -v 'true.*True|false.*False' *.dcheck.out | egrep -v '^(json-model|l10n)'
	exit 0

# special case for the meta model
json-model.dcheck.out: json-model.model.json
	$(JMC) -v -DO --no-code --true ./$< $(F.model) ../bads/_*.model.json | sort > $@
	$(JMC) -v -DO --no-code --false ./$< $(F.bads) | sort >> $@

# special case for localizations
l10n.dcheck.out: l10n.model.json
	$(JMC) -v -DO --no-code --true ./$< english.model.json français.model.json > $@
	echo "# localized models" >> $@
	$(JMC) -v -DO --no-code --true ./english.model.json en_00.model.json >> $@
	$(JMC) -v -DO --no-code --true ./français.model.json fr_00.model.json >> $@

%.dcheck.out: %.model.json
	shopt -s nullglob
	$(JMC) -v -DO -nc ./$< $*.*.true.json $*.*.false.json | sort > $@

#
# Static CHECKs
#
.PHONY: scheck
scheck: $(F.sc)
	egrep -v 'true.*True|false.*False' *.scheck.out | egrep -v '^(json-model|l10n)'
	exit 0

# special case for the meta model
json-model.scheck.out: json-model.model.json
	$(JMC) -v -SO --no-code --true ./$< $(F.model) ../bads/_*.model.json | sort > $@
	$(JMC) -v -SO --no-code --false ./$< $(F.bads) | sort >> $@

# special case for localizations
l10n.scheck.out: l10n.model.json
	$(JMC) -v -SO --no-code --true ./$< english.model.json français.model.json > $@
	echo "# localized models" >> $@
	$(JMC) -v -SO --no-code --true ./english.model.json en_00.model.json >> $@
	$(JMC) -v -SO --no-code --true ./français.model.json fr_00.model.json >> $@

%.scheck.out: %.model.json
	shopt -s nullglob
	$(JMC) -v -SO -nc ./$< $*.*.true.json $*.*.false.json > $@

#
# JSON Schema Checks
#
# this is not perfect:
# - models distinguish between floats and ints, schema not really.
# - the json schema library used does not seem to implement "format" checks.
#
JS_CHECK    = jsu-check --quiet

.PHONY: jcheck
jcheck: $(F.js)
	egrep -v 'true.*PASS|false.*FAIL' *.jcheck.out | egrep -v '^(json-model|l10n)'
	exit 0

# special cases
json-model.jcheck.out: json-model.schema.json
	shopt -s nullglob
	$(JS_CHECK) $< *.model.json ../bads/*.model.json | sort > $@

l10n.jcheck.out: l10n.schema.json
	$(JS_CHECK) $< english.model.json français.model.json > $@
	# echo "# localized models" >> $@
	# $(JS_CHECK) english.schema.json en_00.model.json >> $@
	# $(JS_CHECK) français.schema.json fr_00.model.json >> $@

# external references are not supported
json-model-preprocessed.jcheck.out \
json-model-moschin.jcheck.out \
english.jcheck.out \
français.jcheck.out \
mrg_02.jcheck.out \
obj_03.jcheck.out \
obj_04.jcheck.out \
scope_1.jcheck.out \
hello2.jcheck.out \
hello3.jcheck.out \
scp_01.jcheck.out:
	touch $@

# default case
%.jcheck.out: %.schema.json
	shopt -s nullglob
	$(JS_CHECK) $< $*.*.true.json $*.*.false.json | sort > $@

#
# generate everything from a model
#
.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py $*.scheck.out
	$(MAKE) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py $*.scheck.out
