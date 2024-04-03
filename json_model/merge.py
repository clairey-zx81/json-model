#
# test merge operator
#

import sys
import json
from json_model.utils import merge_rewrite, openfiles

def merge():
    for fn, fh in openfiles(sys.argv[1:]):
        data = json.load(fh)
        print(json.dumps(merge_rewrite(data, {}, ""), indent=2))
