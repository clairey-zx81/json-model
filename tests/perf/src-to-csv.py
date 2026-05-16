#! /usr/bin/env python
#
# Collect summary data about generated source files
#

import pathlib
import hashlib
import sys
import re

def hasher(data: str) -> str:
    return hashlib.sha3_256(data.encode("utf8")).hexdigest()

def wc(data: str) -> int:
    nlines = 0
    for c in data:
        if c == "\n":
            nlines += 1
    return nlines

# which tool produces a file
SUFFIX_TOOL = {
    ".c": "jmc-c",
    ".java": "jmc-java",
    ".js": "jmc-js",
    ".py": "jmc-py",
    ".pl": "jmc-pl",
    ".model.json": "jsu-model",
}

for filename in sys.argv[1:]:
    file = pathlib.Path(filename)
    src = file.read_text()
    name = file.stem.replace("_", "-")
    hs, nl, tool = hasher(src), wc(src), SUFFIX_TOOL["".join(file.suffixes)]
    print(f"{file.name},{name},{tool},{nl},{len(src)},sha3:{hs}")
