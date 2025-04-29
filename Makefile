SHELL   = /bin/bash
.ONESHELL:

MODULE  = json_model

ifndef PYTHON
PYTHON  = python
endif

venv:
	$(PYTHON) -m venv venv
	source venv/bin/activate
	pip install -U pip
	pip install -e .[dev]

.PHONY: dev
dev: venv

.PHONY: clean
clean:
	$(RM) $~

.PHONY: clean.dev
clean.dev: clean
	$(RM) -r venv $(MODULE).egg-info $(MODULE)/__pycache__ build

.PHONY: check
check: check.flake8 check.ruff check.pyright check.pytest

IGNORE  = E121,E125,E131,E227,E251,E302,W504,F841

.PHONY: check.flake8
check.flake8:
	source venv/bin/activate
	flake8 --ignore=$(IGNORE) --max-line-length=100 json_model

.PHONY: check.ruff
check.ruff:
	source venv/bin/activate
	ruff check json_model

.PHONY: check.pyright
check.pyright:
	source venv/bin/activate
	pyright json_model

.PHONY: check.pytest
check.pytest:
	source venv/bin/activate
	$(MAKE) -C tests check.pytest
