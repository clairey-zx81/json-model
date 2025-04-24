# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC.opts    = --check --quiet
JMC = jm-test $(JMC.opts) \
        -m "https://json-model.org/models ." \
        -m "https://json-model.org/tests ."

# inputs, skip _*
F.model = $(wildcard [a-zA-Z]*.model.json)
F.root  = $(F.model:%.model.json=%)

# derived
F.UO    = $(F.root:%=%.UO.json)
F.PO    = $(F.root:%=%.PO.json)
F.EO    = $(F.root:%=%.schema.json)
F.DO    = $(F.root:%=%.DO.out)
F.dc    = $(F.root:%=%.dcheck.out)

F.gen   = $(F.UO) $(F.PO) $(F.EO)

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
	$(JMC) -DO --dis ./$< > $@

json-model-v2.dcheck.out: json-model-v2.model.json
	# TODO ./bads/*.model.json
	$(JMC) -v -DO --true ./$< *.model.json > $@

.PHONY: dcheck
dcheck: $(F.dcheck)
%.dcheck.out: %.model.json
	shopt -s nullglob
	$(JMC) -v -DO ./$< $*.*.true.json $*.*.false.json > $@
	test -z $@ && $(RM) $@

.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.EO.json $*.DO.out $*.dcheck.out
	$(MAKE) $*.UO.json $*.PO.json $*.EO.json $*.DO.out $*.dcheck.out
