#! /bin/bash

# installation
python -m venv venv
source venv/bin/activate
pip install json-model-compiler json-schema-utils
# direct from sources:
# pip install git+https://github.com/clairey-zx81/json-model.git
# pip install git+https://github.com/zx89/json-schema-utils.git
# deactivate

./tuto.sh
