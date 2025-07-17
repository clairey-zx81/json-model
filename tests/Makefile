SHELL   = /bin/bash
.ONESHELL:

# TODO only pytest driven tests?
D.subs  = $(wildcard mv-*) bads ref
D.check = $(D.subs:%=%.check)
D.clean = $(D.subs:%=%.clean)
D.gen = $(D.subs:%=%.gen)

.PHONY: clean
clean: $(D.clean)
	$(RM) -r __pycache__ .pytest_cache

PYTEST  = pytest --log-level=debug --capture=tee-sys --durations=5
PYTOPT	= -n auto

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py

.PHONY: check
check: check.pytest

.PHONY: %.check
%.check:
	$(MAKE) -C $* check

.PHONY: %.clean
%.clean:
	$(MAKE) -C $* clean

.PHONY: check.check
check.check: $(D.check)

.PHONY: gen
gen: $(D.gen)

.PHONY: %.gen
%.gen:
	$(MAKE) -C $* gen
