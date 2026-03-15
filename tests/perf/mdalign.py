#! /usr/bin/env python
#
# filter markdown to fix table alignments depending on hints
#

import re
import fileinput

fmt: str|None = None

ALIGN = {
    "R": " ---: ",
    "C": " :--: ",
    "L": " :--- ",
}

for line in fileinput.input(encoding="utf-8"):
    if re.match(r"^<!-- [CLR]+ -->$", line):
        # intercept html comment table alignment hint
        fmt = line[5:-4]
    elif fmt and re.match(r"^\|([- ]+\|)+$", line):
        # ensure table alignment
        align = line.split(r"|")
        for i, f in enumerate(fmt):
            align[i+1] = ALIGN[f]
        print("|".join(align), end="")
    else:
        # reset current format on empty line
        if line == "":
            fmt = None
        print(line, end="")
