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
	$(RM) $~ jmc.1
	$(RM) -r .pytest_cache/ .ruff_cache/
	find . -type d -name __pycache__ | xargs $(RM) -r
	$(MAKE) -C tests clean

.PHONY: clean.dev
clean.dev: clean
	$(RM) -r venv $(MODULE).egg-info build dist node_modules
	$(RM) package-lock.json

jmc.1: jmc.md
	{
	  echo '.TH JMC "1" "July 2025" "JSON Model Compiler" "User Commands"'
	  pandoc -t man $< | sed -e '5s/^\.IP/.PP/'
	} > $@

.PHONY: check.src
check.src: check.ruff check.pyright

.PHONY: check
check: check.src check.tests

IGNORE  = E121,E125,E131,E227,E251,E302,W504,F841

.PHONY: check.flake8
check.flake8: dev
	source venv/bin/activate
	flake8 --ignore=$(IGNORE) --max-line-length=100 json_model

.PHONY: check.ruff
check.ruff: dev
	source venv/bin/activate
	ruff check json_model

.PHONY: check.pyright
check.pyright: dev
	source venv/bin/activate
	pyright json_model

.PHONY: check.tests
check.tests: dev
	source venv/bin/activate
	$(MAKE) -C tests check

.PHONY: publish.js
publish.js:
	npm publish --dry-run ./js_runtime
	echo npm publish ./js_runtime
