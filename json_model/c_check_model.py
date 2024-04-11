#
# check some json files against a model
#
# usage: $0 model.json file.json …

import sys
import json
import logging
import argparse
from . import compiler, utils

def c_check_model():

    logging.basicConfig(level=logging.INFO)
    log = logging.getLogger("model")

    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--debug", action="store_true")
    ap.add_argument("-D", "--dis", action="store_true")
    ap.add_argument("model", type=str)
    ap.add_argument("jsons", nargs="*")
    args = ap.parse_args()

    if args.debug:
        compiler._debug = True
        compiler.log.setLevel(logging.DEBUG)

    # load model
    with open(args.model) as f:
        checkModel = compiler.compileModel(json.load(f))

    if args.dis:
        import dis
        print(dis.dis(checkModel))

    # process other files
    for fn, fh in utils.openfiles(args.jsons):
        valid = False
        try:
            valid = checkModel(json.load(fh))
            print(f"{fn}: {valid}")
            if not valid:
                log.info(f"failures: {checkModel._reasons}")
                print(f"failures: {checkModel._reasons}")
        except Exception as e:
            print(f"{fn}: error")
            log.error(f"{fn}: {e}")
