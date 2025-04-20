# convenient Makefile for testing

# JSON Model Compiler
JMC = jm-test --check

# inputs, skip _*
F.model = $(wildcard [a-zA-Z]*.model.json)
F.root  = $(F.model:%.model.json=%)

# derived
F.test  = $(F.root:%=%.test.json)
F.pp   = $(F.root:%=%.pp.json)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.test) $(F.pp)

.PHONY: gen
gen: $(F.test) $(F.pp)

%.test.json: %.model.json
	$(JMC) -m "https://json-model.org/models ." -T -O ./$< > $@

%.pp.json: %.model.json
	$(JMC) -m "https://json-model.org/models ." -E -O ./$< > $@
