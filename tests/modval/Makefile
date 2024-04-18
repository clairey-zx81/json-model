M.json = $(wildcard *_m.json)
M.py    = $(M.json:%.json=%.py)

.PHONY: all
all: compiled

.PHONY: clean
clean:
	$(RM) $(M.py)

.PHONY: compile
compiled: $(M.py)

%.py: %.json
	jm-compiler $< > $@
