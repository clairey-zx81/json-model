# convenient Makefile for testing

# JSON Model Compiler
JMC = jm-test --check --quiet \
        -m "https://json-model.org/models ." \
        -m "https://json-model.org/tests ."

# inputs, skip _*
F.model = $(wildcard [a-zA-Z]*.model.json)
F.root  = $(F.model:%.model.json=%)

# derived
F.TO    = $(F.root:%=%.TO.json)
F.EO    = $(F.root:%=%.EO.json)
F.gen   = $(F.TO) $(F.EO)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.gen)

.PHONY: gen
gen: $(F.gen)

%.TO.json: %.model.json
	$(JMC) -TO ./$< > $@

%.EO.json: %.model.json
	$(JMC) -EO ./$< > $@
