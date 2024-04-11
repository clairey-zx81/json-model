#
# check some json files against a model
#
# usage: $0 model.json file.json …

import sys
import json
import logging
from .validator import DSV
from .utils import openfiles

def v_check_model():

    assert len(sys.argv) >= 2 

    logging.basicConfig(level=logging.INFO)
    log = logging.getLogger("model")

    with open(sys.argv[1]) as f:
        model = json.load(f)

    validator = DSV()

    for fn, fh in openfiles(sys.argv[2:]):
        valid = False
        try:
            m = json.load(fh)
            valid = validator.check(m, model)
            print(f"{fn}: {valid}")
        except Exception as e:
            log.error(f"{fn}: {e}")
