SHELL   = /bin/bash
.ONESHELL:

# relevant validation sub directories
D.subs  = $(wildcard mv-*) bads ref

# forwarding
D.check = $(D.subs:%=%.check)
D.valid = $(D.subs:%=%.ts.valid)
D.clean = $(D.subs:%=%.clean)
D.gen = $(D.subs:%=%.gen)
D.genone = $(D.subs:%=%.genone)
# per langage tasks
D.c = $(D.subs:%=%.c)
D.clean.c = $(D.subs:%=%.clean.c)
D.py = $(D.subs:%=%.py)
D.clean.py = $(D.subs:%=%.clean.py)
D.java = $(D.subs:%=%.java)
D.clean.java = $(D.subs:%=%.clean.java)
D.js = $(D.subs:%=%.js)
D.clean.js = $(D.subs:%=%.clean.js)
D.pl = $(D.subs:%=%.pl)
D.clean.pl = $(D.subs:%=%.clean.pl)
D.sql = $(D.subs:%=%.sql)
D.clean.sql = $(D.subs:%=%.clean.sql)
D.ts = $(D.subs:%=%.ts)
D.clean.ts = $(D.valid:%.ts.valid=%.clean.ts)
# schema
D.schema = $(D.subs:%=%.schema)
D.clean.schema = $(D.subs:%=%.clean.schema)

.PHONY: clean
clean:
	$(MAKE) TARGET=clean $(D.clean)
	$(RM) -r __pycache__ .pytest_cache

LOGLEVEL = info
PYTEST  = pytest --log-level=$(LOGLEVEL) --capture=tee-sys --durations=10
PYTOPT	= -n logical

.PHONY: check.pytest
check.pytest:
	$(PYTEST) $(PYTOPT) tests.py

# parallel forward trick
.PHONY: %.$(TARGET)
%.$(TARGET):
	$(MAKE) -C $* $(TARGET)

.PHONY: check
check: check.pytest

.PHONY: check.check
check.check:
	$(MAKE) TARGET=check $(D.check)
	$(MAKE) clean

# forwarding continued
.PHONY: gen
gen:
	$(MAKE) TARGET=gen $(D.gen)

.PHONY: genone
genone:
	$(MAKE) TARGET=genone GENONE=$(GENONE) $(D.genone)

.PHONY: c
c:
	$(MAKE) TARGET=c $(D.c)

.PHONY: clean.c
clean.c:
	$(MAKE) TARGET=clean.c $(D.clean.c)

.PHONY: py
py:
	$(MAKE) TARGET=py $(D.py)

.PHONY: clean.py
clean.py:
	$(MAKE) TARGET=clean.py $(D.clean.py)

.PHONY: java
java:
	$(MAKE) TARGET=java $(D.java)

.PHONY: clean.java
clean.java:
	$(MAKE) TARGET=clean.java $(D.clean.java)

.PHONY: js
js:
	$(MAKE) TARGET=js $(D.js)

.PHONY: clean.js
clean.js:
	$(MAKE) TARGET=clean.js $(D.clean.js)

.PHONY: pl
pl:
	$(MAKE) TARGET=pl $(D.pl)

.PHONY: clean.pl
clean.pl:
	$(MAKE) TARGET=clean.pl $(D.clean.pl)

.PHONY: sql
sql:
	$(MAKE) TARGET=sql $(D.sql)

.PHONY: clean.sql
clean.sql:
	$(MAKE) TARGET=clean.sql $(D.clean.sql)

.PHONY: ts
ts:
	$(MAKE) TARGET=ts $(D.ts)

.PHONY: clean.ts
clean.ts:
	$(MAKE) TARGET=clean.ts $(D.clean.ts)

.PHONY: schema
schema:
	$(MAKE) TARGET=schema $(D.schema)

.PHONY: clean.schema
clean.schema:
	$(MAKE) TARGET=clean.schema $(D.clean.schema)

# show statistics about tests
.PHONY: stats
stats:
	@echo -n "- positive test cases: "
	ls mv-*/*.model.json ref/*.model.json | wc -l
	echo -n "- (basic) test values: "
	egrep '^  *\[ (true|false), ' mv-*/*.values.json ref/*.values.json | wc -l
	echo -n "- negative test cases: "
	ls bads/*.model.json | wc -l
