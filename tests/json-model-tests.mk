# convenient Makefile for testing
SHELL	= /bin/bash
.ONESHELL:

# JSON Model Compiler
JMC = jmc
JMC.opts    = --check --quiet
JMC.cmd = \
	$(JMC) $(JMC.opts) \
        -m "https://json-model.org/models ../../models" \
        -m "https://json-model.org/tests ."

# JSON Schema Checker
JSC = jsu-check --quiet

# inputs, skip _*
F.mjs   = $(wildcard [a-zA-Z]*.model.js)
F.myaml = $(wildcard *.model.yaml)
F.model = $(wildcard [a-zA-Z]*.model.json) \
          $(F.mjs:%.model.js=%.model.json) \
          $(F.myaml:%.model.yaml=%.model.json)
F.bads  = $(wildcard ../bads/[a-zA-Z]*.model.json)

F.root  = $(F.model:%.model.json=%)

# derived
F.json = $(F.mjs:%.model.js=%.model.json) $(F.myaml:%.model.yaml=%.model.json)
F.UO    = $(F.root:%=%.UO.json)
F.JO    = $(F.root:%=%.JO.json)
F.PO    = $(F.root:%=%.PO.json)
F.EO    = $(F.root:%=%.schema.json)

# C and Python generation
F.c     = $(F.root:%=%.c)
F.py    = $(F.root:%=%.py)
F.exe   = $(F.root:%=%.exe)
F.cc    = $(F.root:%=%.c-check.out)
F.pyc   = $(F.root:%=%.py-check.out)

# all generated
F.gen   = $(F.UO) $(F.PO) $(F.EO) $(F.json) $(F.js) $(F.sXc) $(F.c) $(F.py) $(F.cc) $(F.pyc)

-include local.mk

.PHONY: clean.gen
clean.gen:
	$(RM) $(F.gen)

.PHONY: gen
gen: $(F.gen)

.PHONY: check
check:
	$(MAKE) clean.gen
	$(MAKE) gen

.PHONY: clean
clean:
	$(RM) *.o *.exe

.PHONY: json
json: $(F.json)

%.model.json: %.model.js
	$(JMC.cmd) -N ./$< > $@

%.model.json: %.model.yaml
	$(JMC.cmd) -N ./$< > $@

.PHONY: UO
UO: $(F.UO)
%.UO.json: %.model.json
	$(JMC.cmd) -UO ./$< > $@

.PHONY: PO
PO: $(F.PO)
%.PO.json: %.model.json
	$(JMC.cmd) -PO ./$* > $@

# dump internal JSON IR
%.JO.json: %.model.json
	$(JMC.cmd) -JO ./$* > $@

.PHONY: schema
schema: $(F.EO)
%.schema.json: %.model.json
	$(JMC.cmd) -EO -ns ./$< > $@

# code execution
F.x     = $(F.c) $(F.exe) $(F.cc) $(F.py) $(F.pyc)

.PHONY: clean.x
clean.x:
	$(RM) $(F.x) json-model.o main.o

.PHONY: check.x
check.x: clean.x
	$(MAKE) $(F.x)

%.c: %.model.json
	$(JMC.cmd) -XO -v --format c ./$< > $@

CC        = gcc
CPPFLAGS  = -DCHECK_FUNCTION_NAME=check_model -I../../json_model/runtime
CFLAGS    = -Wall -Wno-address -Wno-c23-extensions -Wno-unused-variable -Wno-unused-function -Ofast
LDFLAGS   = json-model.o -ljansson -lpcre2-8 main.o -lm

json-model.o: ../../json_model/runtime/json-model.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

main.o: ../../json_model/runtime/main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(F.exe): json-model.o main.o

%.exe: json-model.o main.o

%.exe: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) -o $@

%.c-check.out: %.exe
	shopt -s nullglob
	set -o pipefail
	$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

%.py: %.model.json
	$(JMC.cmd) -XO -v --format py ./$< > $@
	chmod a+rx $@

%.py-check.out: %.py
	shopt -s nullglob
	set -o pipefail
	./$< -r $*.*.{true,false}.json | sort > $@
	if [ -f $*.values.json ] ; then
	    $< -tr $*.values.json >> $@
	fi

.PHONY: %.x
%.x: %.model.json
	shopt -s nullglob
	$(RM) $*.c $*.exe $*.c-check.out $*.py $*.py-check.out
	$(MAKE) $*.c $*.exe $*.c-check.out $*.py $*.py-check.out

.PHONY: %.xALL
%.xALL:
	$(MAKE) $*.x $*.ALL
	for f in $*.*check.out ; do
	  echo "# $$f"
	  cat $$f
	done

#
# Generated JSON Schema checks
#
.PHONY: check.schema
check.schema: $(F.sXc)

F.schema    = $(F.root:%=%.schema.json)

#
# JSON model value checks with generated JSON schemas
#
# this is not perfect:
# - models distinguish between floats and ints, schema not really.
# - the json schema library used does not seem to implement "format" checks.
# - the implementation is _very_ slow.
#

# default case
# %.jcheck.out: %.schema.json
# 	shopt -s nullglob
# 	set -o pipefail
# 	nrefs=$$(egrep '"\$$(\.|https:)' $*.model.json | wc -l)
# 	iserr=$$(grep '"ERROR": ' $< | wc -l)
# 	if [ $$nrefs == "0" -a $$iserr == "0" ] ; then
# 	  $(JSC) $< $*.*.true.json $*.*.false.json | sort > $@
# 	elif [ $$nrefs != "0" ] ; then
# 	  echo "json schema check skipped, $$nrefs external not supported" > $@
# 	elif [ $$iserr != "0" ] ; then
# 	  echo "json schema check skipped, ERROR reported in generated schema" > $@
# 	else
# 	  exit 1
# 	fi

#
# generate everything from a model
#
.PHONY: %.ALL
%.ALL: %.model.json
	$(RM) $*.UO.json $*.PO.json $*.schema.json
	$(MAKE) $*.UO.json $*.PO.json $*.schema.json
