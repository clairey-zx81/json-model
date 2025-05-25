SHELL   = /bin/bash
.ONESHELL:

# TODO only pytest driven tests?
D.subs  = bads rwt modval merge m2s
D.check = $(D.subs:%=%.check)

.PHONY: clean
clean:
	$(RM) -r __pycache__

PYTEST  = pytest --log-level=debug --capture=tee-sys --durations=5
PYTOPT	= -v -n auto

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py

.PHONY: check
check: $(D.check)

%.check:
	$(MAKE) -C $* check
