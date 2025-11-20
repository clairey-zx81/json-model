#! /usr/bin/env python
#
# filter markdown to fix table alignments depending on hints
#

import re
import fileinput

fmt: str|None = None

for line in fileinput.input(encoding="utf-8"):
    if re.match(r"^<!-- [CLR]+ -->$", line):
        # intercept html comment table alignment hint
        fmt = line[5:-4]
    elif fmt and re.match(r"^\|([- ]+\|)+$", line):
        # ensure table alignment
        align = line.split(r"|")
        for i, f in enumerate(fmt):
            if f == "R":  # right
                align[i+1] = " ---: "
            elif f == "C":  # center
                align[i+1] = " :--: "
            elif f == "L":  # left
                align[i+1] = " :--- "
        print("|".join(align), end="")
    else:
        # reset current format on empty line
        if line == "":
            fmt = None
        print(line, end="")
