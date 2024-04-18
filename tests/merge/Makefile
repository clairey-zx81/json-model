F.json = $(filter-out %.merged.json, $(wildcard *.json))
F.mjson = $(F.json:%.json=%.merged.json)
F.py = $(F.json:%.json=%.py)

.PHONY: all
all: merged compiled

.PHONY: clean
clean:
	$(RM) $(F.mjson) $(F.py) *.out

.PHONY: merged
merged: $(F.mjson)

.PHONY: compiled
compiled: $(F.py)

%.merged.json: %.json
	jm-preprocessor $< > $@

%.py: %.json
	jm-compiler $< > $@
