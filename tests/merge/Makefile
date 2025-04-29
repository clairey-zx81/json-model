F.model = $(wildcard *.model.json)

# derived
F.merge = $(F.model:%.model.json=%.merged.json)
F.py = $(F.model:%.model.json=%.py)

.PHONY: all
all: merged compiled

.PHONY: clean
clean:
	$(RM) $(F.merge) $(F.py) *.out

.PHONY: merged
merged: $(F.merge)

.PHONY: compiled
compiled: $(F.py)

%.merged.json: %.model.json
	jmc -PO $< > $@

%.py: %.model.json
	jmc -SO $< > $@
