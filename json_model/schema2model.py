#
# Take a (simple) JSON Schema and generate a JSON Model
#

import json
import sys
import logging
import json_model.generate as gen
import json_model.utils as utils

def schema2model_script():

    logging.basicConfig()
    log = logging.getLogger("s2m")

    params = sys.argv[1:]
    if params and params[0] == "-e":
        params = params[1:]
        gen.EXPLICIT_TYPE = True

    for fn, fh in utils.openfiles(params):
        jschema = fh.read()
        schema = json.loads(jschema)
        model = gen.schema2model(schema)
        jmodel = json.dumps(model, indent=2)
        # log.debug(f"schema: {jschema}")
        # log.debug(f"model: {jmodel}")
        print(jmodel)
