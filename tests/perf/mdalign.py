#! /usr/bin/env python
#
# filter markdown to fix table alignments depending on hints
#

import re
import fileinput

fmt: str|None = None

for line in fileinput.input(encoding="utf-8"):
    if re.match(r"^[CLR]+$", line):
        fmt = line
    elif fmt and re.match(r"^\|([- ]+\|)+$", line):
        align = line.split(r"|")
        for i, f in enumerate(fmt):
            if f == "R":
                align[i+1] = " ---: "
            elif f == "C":
                align[i+1] = " :--: "
            elif f == "L":
                align[i+1] = " :--- "
        print("|".join(align), end="")
    else:
        print(line)
