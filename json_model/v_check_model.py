#
# check some json files against a model
#
# usage: $0 model.json file.json …

import sys
import json
import logging
from json_model.validator import DSV

def v_check_model():

    assert len(sys.argv) >= 2 

    logging.basicConfig(level=logging.INFO)
    log = logging.getLogger("model")

    with open(sys.argv[1]) as f:
        model = json.load(f)

    validator = DSV()

    for fn in sys.argv[2:]:
        valid = False
        try:
            with open(fn) as f:
                schema = json.load(f)
                valid = validator.check(schema, model)
                print(f"{fn}: {valid}")
                # if not valid:
                #    log.info(f"failures: {checkModel._reasons}")
        except Exception as e:
            print(f"{fn}: error")
            log.error(f"{fn}: {e}")
