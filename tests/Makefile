SHELL   = /bin/bash
.ONESHELL:

# TODO only pytest driven tests?
D.subs  = $(wildcard mv-*) bads ref
D.check = $(D.subs:%=%.check)
D.clean = $(D.subs:%=%.clean)

.PHONY: clean
clean: $(D.clean)
	$(RM) -r __pycache__

PYTEST  = pytest --log-level=debug --capture=tee-sys --durations=5
PYTOPT	= -v -n auto

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py

.PHONY: check
check: check.pytest

.PHONY: check.gen
check.gen: $(D.check)

.PHONY: %.check
%.check:
	$(MAKE) -C $* check

.PHONY: %.clean
%.clean:
	$(MAKE) -C $* clean
