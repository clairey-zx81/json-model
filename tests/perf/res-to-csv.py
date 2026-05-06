#! /bin/env python3
#
# extract result figures from run outputs
#

import sys
import re

for file in sys.argv[1:]:
    assert file.endswith(".out")
    name = file.split("/")[-1][:-4].replace("_", ",")
    num = int(re.match(r".*/([0-9]+)/", file).group(1))
    npass, nfail = 0, 0
    with open(file) as f:
        for line in f:
            if "PASS" in line:
                npass += 1
            if "FAIL" in line:
                nfail += 1
    print(f"{name},{num},{npass},{nfail}")
