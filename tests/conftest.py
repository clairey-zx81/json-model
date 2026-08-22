#
# xdist-resistant assert counter
#
# count assert through a file to work around xdist multiprocess machinery
# what hook can be used to remove the generated files is unclear
#
# FIXME is this reliable?
#

import pytest
import os
import glob

COUNTER = ".counter"
cnt: int = 0

def pytest_assertion_pass(item, lineno, orig, expl):
    global cnt
    cnt += 1

def pytest_unconfigure(config):
    worker_id = os.environ.get("PYTEST_XDIST_WORKER", "root")
    counter_file = f"{COUNTER}.{worker_id}"
    with open(counter_file, "w") as cf:
        print(cnt, file=cf)

def pytest_terminal_summary(terminalreporter, exitstatus, config):
    n_asserts: int = 0
    files = glob.glob(f"{COUNTER}.*")
    for cf in files:
        with open(cf) as f:
            n_asserts += int(f.read())
    terminalreporter.rewrite(f"\nTotal number of asserts: {n_asserts} (over {len(files)})\n")
