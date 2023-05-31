#! /usr/bin/env python

import json
import sys
from json_model.utils import merge_rewrite

for fn in sys.argv[1:]:
    with open(fn) as f:
        data = json.load(f)
        print(json.dumps(merge_rewrite(data), indent=2))
