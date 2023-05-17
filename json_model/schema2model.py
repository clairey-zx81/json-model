#
# Take a (simple) JSON Schema and generate a JSON Model
#

import json
import sys
import logging
from json_model.generate import schema2model

def schema2model_script():

    logging.basicConfig()
    log = logging.getLogger("s2m")

    for fn in sys.argv[1:]:
        with open(fn) as f:
            jschema = f.read()
            schema = json.loads(jschema)
            model = schema2model(schema)
            jmodel = json.dumps(model, indent=2)
            log.debug(f"schema: {jschema}")
            # log.debug(f"model: {jmodel}")
            print(jmodel)
