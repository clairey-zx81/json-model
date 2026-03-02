SHELL   = /bin/bash
.ONESHELL:

# relevant validation sub directories
D.subs  = $(wildcard mv-*) bads ref

D.check = $(D.subs:%=%.check)
D.clean = $(D.subs:%=%.clean)
D.gen = $(D.subs:%=%.gen)
D.java = $(D.subs:%=%.java)

.PHONY: clean
clean:
	$(MAKE) TARGET=clean $(D.clean)
	$(RM) -r __pycache__ .pytest_cache

LOGLEVEL = info
PYTEST  = pytest --log-level=$(LOGLEVEL) --capture=tee-sys --durations=5
PYTOPT	= -n auto

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

.PHONY: gen
gen:
	$(MAKE) TARGET=gen $(D.gen)

.PHONY: java
java:
	$(MAKE) TARGET=java $(D.java)

# show statistics about tests
.PHONY: stats
stats:
	@echo -n "- positive test cases: "
	ls mv-*/*.model.json ref/*.model.json | wc -l
	echo -n "- (basic) test values: "
	egrep '^  *\[ (true|false), ' mv-*/*.values.json ref/*.values.json | wc -l
	echo -n "- negative test cases: "
	ls bads/*.model.json | wc -l
