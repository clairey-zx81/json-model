#
# xdist-resistant assert counter
#

import pytest
import os

# count assert through a file to work around xdist
# probably something better can be done
COUNTER = ".counter"
counter = open(COUNTER, "a")

def pytest_sessionstart(session):
    global counter

def pytest_assertion_pass(item, lineno, orig, expl):
    # FIXME it is unclear whether data loss is possible
    counter.write("x")
    counter.flush()

def pytest_terminal_summary(terminalreporter, exitstatus, config):
    n_passed_asserts = os.path.getsize(COUNTER)
    terminalreporter.rewrite(f"\nTotal number of asserts: {n_passed_asserts}\n")
