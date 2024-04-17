F.json = $(filter-out %.merged.json, $(wildcard *.json))
F.mjson = $(F.json:%.json=%.merged.json)

# .PHONY: clean
# clean:
# 	$(RM) $(F.mjson)

.PHONY: merged
merged: $(F.mjson)

%.merged.json: %.json
	jm-preprocessor $< > $@
