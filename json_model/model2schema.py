#
# Generate a JSON Schema from a JSON Model
#

import json
import sys
import logging
from json_model.generate import model2schema

def model2schema_script():

    logging.basicConfig()
    log = logging.getLogger("m2s")

    for fn in sys.argv[1:]:
        with open(fn) as f:
            jmodel = f.read()
            model = json.loads(jmodel)
            schema = model2schema(model)
            jschema = json.dumps(schema, indent=2)
            # log.debug(f"schema: {}")
            # log.debug(f"model: {jmodel}")
            print(jschema)
