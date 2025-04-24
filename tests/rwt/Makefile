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
F.DO    = $(F.root:%=%.DO.out)
F.dc    = $(F.root:%=%.dcheck.out)
F.gen   = $(F.UO) $(F.PO)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.gen)

.PHONY: gen
gen: $(F.gen)

%.UO.json: %.model.json
	$(JMC) -UO ./$< > $@

%.PO.json: %.model.json
	$(JMC) -PO ./$< > $@

%.DO.out: %.model.json
	$(JMC) -DO --dis ./$< > $@

%.dcheck.out: %.model.json
	shopt -s nullglob
	$(JMC) -v -DO ./$< $*.*.true.json $*.*.false.json > $@

.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.DO.out $*.dcheck.out
	$(MAKE) $*.UO.json $*.PO.json $*.DO.out $*.dcheck.out
