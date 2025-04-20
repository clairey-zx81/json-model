# convenient Makefile for testing

# JSON Model Compiler
JMC = jm-test

# inputs
F.model = $(wildcard [a-zA-Z]*.model.json)
F.root  = $(F.model:%.model.json=%)

# derived
F.out   = $(F.root:%=%.out.json)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) $(F.out)

.PHONY: gen
gen: $(F.out)

%.out.json: %.model.json
	$(JMC) -m "https://json-model.org/models ." -O ./$< > $@
