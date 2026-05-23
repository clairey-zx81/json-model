#! /usr/bin/env python
#
# extract result figures from run outputs
#

import sys
import re
import argparse
import logging
import math

logging.basicConfig(level=logging.INFO)
log = logging.getLogger("extract")

ap = argparse.ArgumentParser(description="extract measures")
ap.add_argument("--debug", "-d", action="store_true", default=False, help="set debug mode")
ap.add_argument("--unshift", "-u", action="store_true", default=False, help="unshift measures")
ap.add_argument("files", nargs="*", help="files to process")
args = ap.parse_args()

if args.debug:
    log.setLevel(level=logging.DEBUG)

for file in args.files:
    assert file.endswith(".out")
    name = file.split("/")[-1][:-4].replace("_", ",").lower()
    num = int(re.match(r".*/([0-9]+)/", file).group(1))
    npass, nfail = 0, 0
    with open(file) as f:
        for line in f:
            # /workspace/jsb/schemas/ansible-meta/instances.jsonl[236]: PASS 0.090 +- 0.007 us (0.017)
            # jsb/schemas/ansible-meta/instances.jsonl[1] nop PASS 0.322 ± 0.233 µs/check (0.021)
            matched = re.match(r"^.*/instances.jsonl\[(\d+)].*(?:PASS|FAIL) ([.0-9]+) [^ ]+ ([.0-9]+) [^ ]+ \(([.0-9]+)\)", line)
            if matched:
                g = matched.group
                linenb, avg, std, empty = int(g(1)), float(g(2)), float(g(3)), float(g(4))
                if args.unshift:
                    #
                    # shifted average:
                    #
                    # avg(r_i - e)
                    # = sum_n (r_i - e) / n
                    # = sum_n r_i / n - n e / n
                    # = avg(r_i) - e
                    #
                    avg = avg + empty
                    #
                    # shifted standard deviation: same, as painfully demonstrated here:
                    #
                    # stdev(r_i - e) = sqrt( sum_n (r_i - e)² / n - avg(r_i - e)² )
                    #
                    # sum_n (r_i - e)²
                    # = n (stdev(r_i - e)² + avg(r_i - e)²)
                    #
                    # = sum_n (r_i² - 2 e r_i + e²)
                    # = sum_n r_i² - 2 e sum_n r_i + n e²
                    # = sum_n r_i² - 2 e n * avg(r_i) + n e²
                    #
                    # sum_n r_i²
                    # = n (stdev(r_i - e)² + avg(r_i - e)²) + 2 n e avg(r_i) - n e²
                    # = n (stdev(r_i - e)² + avg(r_i - e)² + 2 e avg(r_i) - e²)
                    # = n (stdev(r_i - e)² + avg(r_i - e)² + e (2 avg(r_i) - e))
                    #
                    # sum_n r_i² / n
                    # = stdev(r_i - e)² + avg(r_i - e)² + e (2 avg(r_i) - 2 e + e)
                    # = stdev(r_i - e)² + avg(r_i - e)² + e (2 avg(r_i - e) + e)
                    # = stdev(r_i - e)² + avg(r_i - e)² + 2 e avg(r_i - e) + e²
                    # = stdev(r_i - e)² + (avg(r_i - e) + e)²
                    # = stdev(r_i - e)² + avg(r_i)²
                    #
                    # stdev(r_i)
                    # = sqrt( sum_n r_i² / n - avg(r_i)² )
                    # = sqrt( stdev(r_i - e)² + avg(r_i)² - avg(r_i)² )
                    # = stdev(r_i - e)
                    #
                print(f"{name},{num},{linenb},{avg},{std},{empty}")
            else:
                print(f"ERROR: {line}", file=sys.stderr)
                # sys.exit(1)
