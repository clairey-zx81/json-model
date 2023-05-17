#
# check some json files against a model
#
# usage: $0 model.json file.json …

import sys
import json
import logging
from json_model.compiler import compileModel

def c_check_model():

    assert len(sys.argv) >= 2 

    logging.basicConfig(level=logging.INFO)
    log = logging.getLogger("model")

    with open(sys.argv[1]) as f:
        checkModel = compileModel(json.load(f))

    for fn in sys.argv[2:]:
        valid = False
        try:
            with open(fn) as f:
                valid = checkModel(json.load(f))
                print(f"{fn}: {valid}")
                if not valid:
                    log.info(f"failures: {checkModel._reasons}")
        except Exception as e:
            print(f"{fn}: error")
            log.error(f"{fn}: {e}")
