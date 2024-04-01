#
# test merge operator
#

import sys
import json
from json_model.utils import merge_rewrite

def merge():
    for fn in sys.argv[1:]:
        with open(fn) as f:
            data = json.load(f)
            print(json.dumps(merge_rewrite(data, {}, ""), indent=2))
