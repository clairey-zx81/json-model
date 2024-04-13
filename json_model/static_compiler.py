# Static JSON Model Compiler

import sys
import json
import logging
from .utils import openfiles
from .compiler_gen import static_compile

logging.basicConfig()
log = logging.getLogger("compiler")

def static_compiler():
    for fn, fh in openfiles(sys.argv[1:]):
        try:
            model = json.load(fh)
            print(static_compile(model))
        except Exception as e:
            log.error(f"{fn}: {e}")        
            log.error(e, exc_info=True)
