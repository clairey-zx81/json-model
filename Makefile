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
clean: clean.dev
	$(RM) $~

.PHONY: clean.dev
clean.dev:
	$(RM) -r venv $(MODULE).egg-info $(MODULE)/__pycache__ build

.PHONY: check
check: check.flake8 check.ruff check.pyright check.pytest

IGNORE  = E227,E125

.PHONY: check.flake8
check.flake8:
	source venv/bin/activate
	flake8 --ignore=$(IGNORE) json_model

.PHONY: check.ruff
check.ruff:
	source venv/bin/activate
	ruff check json_model

.PHONY: check.pyright
check.pyright:
	source venv/bin/activate
	pyright check json_model

.PHONY: check.pytest
check.pytest:
	source venv/bin/activate
	$(MAKE) -C tests check.pytest
