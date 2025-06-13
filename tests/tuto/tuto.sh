#! /bin/bash

# installation
jmc --version

# person model
jmc Person-0.model.json hobbes.json
jmc -r Person-0.model.json moe.json

# constraining strings
jmc -r Person-1.model.json hobbes.json moe.json elysee.json

# using definitions
jmc -r Person-2.model.json hobbes.json moe.json elysee.json
jmc -n PI Person-2.model.json pi.json

# loosening objects
jmc Loose.model.json moe.json

# having alternatives
jmc Geom.model.json marseille.json seoul-tokyo.json

# numbers vs numbers
jmc Town.model.json beijing.json shanghai.json
jmc --loose-number Town.model.json beijing.json shanghai.json

# composing objects
# playing with constraints
# reusing definitions
# transforming models
# larger examples

# prefering yaml or js
jmc Person-0.model.yaml hobbes.json moe.json
jmc Person-0.model.js hobbes.json moe.json

# running with C, JS or Python

# exporting to JSON Schema
