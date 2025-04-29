F.model = $(wildcard *.model.json)
F.schema = $(F.model:%.model.json=%.schema.json)

.PHONY: default
default: $(F.schema)

%.schema.json: %.model.json
	jmc -EO $< > $@
