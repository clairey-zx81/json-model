#! /bin/bash

# installation
python -m venv venv
source venv/bin/activate
pip install \
    git+https://github.com/clairey-zx81/json-model.git \
    git+https://github.com/zx89/json-schema-utils.git

# run
./tuto.sh
