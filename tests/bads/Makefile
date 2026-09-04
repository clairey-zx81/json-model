# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC.opts    = --quiet
JMC = jmc $(JMC.opts) \
        -m "https://json-model.org/models ../../models"

# inputs, skip _*
F.model = $(wildcard *.model.json)
F.root  = $(F.model:%.model.json=%)
F.check = $(F.root:%=%.check)

F.gen   = $(F.check)

.PHONY: gen
gen: $(F.gen)

.PHONY: genone
	# skip

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.gen)

%.check: %.model.json
	$(JMC) --check -PO $< > $@ 2>&1 && exit 1 || exit 0

# catchall to ignore anything else
%:
	# skip

clean.%:
	# skip
