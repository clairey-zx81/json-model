SHELL   = /bin/bash
.ONESHELL:

D.subs  = rwt modval merge
D.check = $(D.subs:%=%.check)

.PHONY: clean
clean:
	$(RM) -r __pycache__

PYTEST  = pytest --log-level=debug --capture=tee-sys
PYTOPT	= -vv

# TODO reinstante some pytest tests
# .PHONY: check.pytest
# check.pytest:
# 	$(PYTEST) $(PYTOPT) tests.py

.PHONY: check
check: $(D.check)

.PHONY: $(D.check)
%.check:
	$(MAKE) -C $* check
