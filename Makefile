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
	$(RM) $~ jmc.1 site/MODELS.md site/JMC.md
	$(RM) -r .pytest_cache/ .ruff_cache/ dist/
	find . -type d -name __pycache__ | xargs $(RM) -r
	$(MAKE) -C tests clean
	$(MAKE) -C json_model/runtime clean

.PHONY: clean.dev
clean.dev: clean
	$(RM) -r venv $(MODULE).egg-info build dist node_modules
	$(RM) package-lock.json

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
	npm publish --dry-run ./json_model/runtime/js
	echo npm publish ./json_model/runtime/js

#
# Docsify Web Site: https://json-model.org/
#
site/MODELS.md: Makefile models/
	{
	  echo "# JSON Model Examples"
	  echo
	  for model in models/*.model.json ; do
	    title=$$(jq -r '."#"' < $$model | sed 's/\s*.JSON_MODEL.*//')
	    doc=$$(jq -r '."#.doc"' < $$model)
	    if [ "$$doc" = "null" ] ; then doc="" ; else doc=" – $$doc" ; fi
	    echo "- [$$title]($$model ':ignore')$$doc"
	  done
	} > $@

site/JMC.md: json_model/data/jmc.pod
	pod2markdown $< > $@

jmc.1: json_model/data/jmc.pod dev
	source venv/bin/activate
	version=$$(jmc --version)
	year=$$(date +%Y)
	pod2man $< | sed "s/^\.TH JMC 1.*/.TH JMC 1 $$year \"v$$version\" \"User Documentation\"/" > $@

#
# PUBLICATION
#

.PHONY: build.site
build.site: site/MODELS.md site/JMC.md

.PHONY: publish.site
publish.site: build.site
	rsync -avL --progress ./site/. $(SITE):public_html/sw/json-model/.
	ssh $(SITE) chmod a+rx public_html/sw/json-model public_html/sw/json-model/models
	ssh $(SITE) chmod a+r public_html/sw/json-model/* public_html/sw/json-model/models/*

.PHONY: publish.py
publish.py: dev
	source venv/bin/activate
	python -m build
	twine check dist/*
	echo "# twine upload dist/*"

.PHONY: publish.docker
publish.docker:
	# $(MAKE) -C docker docker.push

RT.dir  = json_model/runtime

.PHONY: publish.sql
publish.sql:
	$(MAKE) -C $(RT.dir) json_model.tgz
	# upload to https://manager.pgxn.org/

.PHONY: publish.perl
publish.perl:
	perl $(RT.dir)/pl/Makefile.PL
	$(MAKE) -C $(RT.dir)/pl dist
	## cpan-upload -u ZXHZ $(RT.dir)/pl/JSON-JsonModel-<version>.tar.gz
	# web: https://pause.perl.org/ + ZXHZ auth + upload file
	# $(MAKE) -C $(RT.dir)/pl clean
	# $(RM) $(RT.dir)/pl/Makefile.old

.PHONY: publish.js
publish.js:
	cd $(RT.dir)/js
	npm publish --access public --tag latest

.PHONY: publish.java
publish.java:
	$(MAKE) -C $(RT.dir)/java zip
	# see https://central.sonatype.org/publish/requirements/
	# upload zip on https://central.sonatype.com/publishing as org.json-model:json-model:VERSION
