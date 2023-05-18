SHELL   = /bin/bash
.ONESHELL:

.PHONY: clean
clean:
	$(RM) -r __pycache__

PYTEST  = pytest --log-level=debug --capture=tee-sys
PYTOPT	=

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py
