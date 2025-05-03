SHELL   = /bin/bash
.ONESHELL:

# sources
F.model = $(wildcard *.model.json)

# derived
F.schema = $(F.model:%.model.json=%.schema.json)
F.sXc = schema.jcheck.out \
    schema.dcheck.out schema.scheck.out \
    schema.dcheck2.out schema.scheck2.out

# generated
F.gen   = $(F.schema) $(F.sXc)

.PHONY: gen
gen: $(F.gen)

.PHONY: schema
schema: $(F.schema)
%.schema.json: %.model.json
	jmc -EO -ns $< > $@

.PHONY: check.schema
check.schema: $(F.sXc)

schema.jcheck.out: $(F.schema)
	for f in $(F.schema) ; do
	  if jsu-check $$f ; then
	    echo "$$f: PASS"
	  else
	    echo "$$f: FAIL"
	  fi
	done | sort > $@

schema.dcheck.out: $(F.schema)
	jmc --auto --check --quiet -DO ../../models/json-schema-draft-2020-12.model.json $^ |
	  sort > $@

schema.scheck.out: $(F.schema)
	jmc --auto --check --quiet -SO ../../models/json-schema-draft-2020-12.model.json $^ |
	  sort > $@

# FIXME json-schema-draft-tighter.model.json: KO, mandatory $schema

schema.dcheck2.out: $(F.schema)
	jmc --auto --check --verbose -DO ../../models/json-schema-draft-2020-12-tight.model.json $^ |
	  sort > $@

schema.scheck2.out: $(F.schema)
	jmc --auto --check --quiet -SO ../../models/json-schema-draft-2020-12-tight.model.json $^ |
	  sort > $@

.PHONY: clean
clean:
	$(RM) $(F.gen)

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen
