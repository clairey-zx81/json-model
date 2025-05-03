F.model = $(wildcard *.model.json)

F.schema = $(F.model:%.model.json=%.schema.json)

F.gen   = $(F.schema)

.PHONY: gen
gen: $(F.gen)

.PHONY: schema
schema: $(F.schema)
%.schema.json: %.model.json
	jmc -EO -ns $< > $@

.PHONY: clean
clean:
	$(RM) $(F.gen)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen
