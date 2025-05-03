# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC.opts    = --check --quiet
JMC = jmc $(JMC.opts) \
        -m "https://json-model.org/models ../../models"

# inputs, skip _*
F.mjs   = $(wildcard [a-zA-Z]*.model.js)
F.myaml = $(wildcard *.model.yaml)
F.model = $(wildcard [a-zA-Z]*.model.json) \
          $(F.mjs:%.model.js=%.model.json) \
          $(F.myaml:%.model.yaml=%.model.json)

F.root  = $(F.model:%.model.json=%)

# derived
F.json = $(F.mjs:%.model.js=%.model.json) $(F.myaml:%.model.yaml=%.model.json)

F.gen   = bads.check.out

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

# test that --check rejects **all** bads
bads.check.out:
	shopt -s nullglob
	for bad in *.model.json ; do
	  $(JMC) --check -PO $$bad && exit 1
	done 2> $@
	exit 0
