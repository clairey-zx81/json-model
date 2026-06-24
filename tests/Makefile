SHELL   = /bin/bash
.ONESHELL:

# relevant validation sub directories
D.subs  = $(wildcard mv-*) bads ref

# forwarding
D.check = $(D.subs:%=%.check)
D.clean = $(D.subs:%=%.clean)
D.gen = $(D.subs:%=%.gen)
D.java = $(D.subs:%=%.java)
D.clean.java = $(D.subs:%=%.clean.java)
D.js = $(D.subs:%=%.js)
D.clean.js = $(D.subs:%=%.clean.js)
D.pl = $(D.subs:%=%.pl)
D.clean.pl = $(D.subs:%=%.clean.pl)

.PHONY: clean
clean:
	$(MAKE) TARGET=clean $(D.clean)
	$(RM) -r __pycache__ .pytest_cache

LOGLEVEL = info
PYTEST  = pytest --log-level=$(LOGLEVEL) --capture=tee-sys --durations=5
PYTOPT	= -n logical

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py

.PHONY: %.$(TARGET)
%.$(TARGET):
	$(MAKE) -C $* $(TARGET)

.PHONY: check
check: check.pytest

.PHONY: check.check
check.check:
	$(MAKE) TARGET=check $(D.check)
	$(MAKE) clean

# forwarding continued
.PHONY: gen
gen:
	$(MAKE) TARGET=gen $(D.gen)

.PHONY: java
java:
	$(MAKE) TARGET=java $(D.java)

.PHONY: clean.java
clean.java:
	$(MAKE) TARGET=clean.java $(D.clean.java)

.PHONY: js
js:
	$(MAKE) TARGET=js $(D.js)

.PHONY: clean.js
clean.js:
	$(MAKE) TARGET=clean.js $(D.clean.js)

.PHONY: pl
pl:
	$(MAKE) TARGET=pl $(D.pl)

.PHONY: clean.pl
clean.pl:
	$(MAKE) TARGET=clean.pl $(D.clean.pl)

# show statistics about tests
.PHONY: stats
stats:
	@echo -n "- positive test cases: "
	ls mv-*/*.model.json ref/*.model.json | wc -l
	echo -n "- (basic) test values: "
	egrep '^  *\[ (true|false), ' mv-*/*.values.json ref/*.values.json | wc -l
	echo -n "- negative test cases: "
	ls bads/*.model.json | wc -l
