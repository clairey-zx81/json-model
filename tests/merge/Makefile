F.model = $(wildcard *.model.json)

# derived
F.merge = $(F.model:%.model.json=%.merged.json)
F.py    = $(F.model:%.model.json=%.py)

F.gen   = $(F.merge) $(F.py)

.PHONY: gen
gen: merged compiled

.PHONY: clean
clean:
	$(RM) $(F.merge) $(F.py) *.out

.PHONY: check
check:
	$(MAKE) clean
	$(MAKE) gen

.PHONY: merged
merged: $(F.merge)
%.merged.json: %.model.json
	jmc -PO $< > $@

.PHONY: compiled
compiled: $(F.py)
%.py: %.model.json
	jmc -SO $< > $@
