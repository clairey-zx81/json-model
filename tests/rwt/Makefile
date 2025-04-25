# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC.opts    = --check --quiet
JMC = jmc $(JMC.opts) \
        -m "https://json-model.org/models ." \
        -m "https://json-model.org/tests ."

# inputs, skip _*
F.model = $(wildcard [a-zA-Z]*.model.json)
F.bads  = $(wildcard bads/[a-zA-Z]*.model.json)
F.root  = $(F.model:%.model.json=%)

# derived
F.UO    = $(F.root:%=%.UO.json)
F.PO    = $(F.root:%=%.PO.json)
F.EO    = $(F.root:%=%.schema.json)
F.DO    = $(F.root:%=%.DO.out)
F.SO    = $(F.root:%=%.py)
F.dc    = $(F.root:%=%.dcheck.out)

F.gen   = $(F.UO) $(F.PO) $(F.EO) $(F.DO) $(F.dc) bads.check.out

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.gen)

.PHONY: gen
gen: $(F.gen)

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
	$(JMC) -DO --dis ./$< | sed -e 's/<code object .*>/<*>/' > $@

.PHONY: py
py: $(F.SO)
%.py: %.model.json
	$(JMC) -SO ./$< > $@

# test that --check rejects **all** bads
bads.check.out:
	for bad in bads/*.model.json ; do
	  $(JMC) --check -PO $$bad && exit 1
	done 2> $@
	exit 0

# TODO scheck

# special case for the meta model
json-model-v2.dcheck.out: json-model-v2.model.json
	# TODO ./bads/*.model.json
	$(JMC) -v -DO --true ./$< $(F.model) > $@
	$(JMC) -v -DO --false ./$< $(F.bads) >> $@

# special case for localizations
l10n.dcheck.out: l10n.model.json
	$(JMC) -v -DO --true ./$< english.model.json français.model.json > $@
	echo "# localized models" >> $@
	$(JMC) -v -DO --true ./english.model.json en_00.model.json >> $@
	$(JMC) -v -DO --true ./français.model.json fr_00.model.json >> $@

.PHONY: dcheck
dcheck: $(F.dcheck)
%.dcheck.out: %.model.json
	shopt -s nullglob
	$(JMC) -v -DO ./$< $*.*.true.json $*.*.false.json > $@

.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py
	$(MAKE) $*.UO.json $*.PO.json $*.schema.json $*.DO.out $*.dcheck.out $*.py
