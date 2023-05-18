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
	pip install -e .

.PHONY: clean
clean: clean.venv

.PHONY: clean.venv
clean.venv:
	$(RM) -r venv $(MODULE).egg-info $(MODULE)/__pycache__ build
