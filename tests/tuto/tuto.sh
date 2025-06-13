#! /bin/bash

# installation
jmc --version

# person model
jmc Person-0 hobbes.json
jmc -r Person-0 moe.json

# constraining strings
jmc -r Person-1 hobbes.json moe.json elysee.json

# using definitions
jmc -r Person-2 hobbes.json moe.json elysee.json
jmc -n PI Person-2 pi.json

# reusing definitions
jmc Class cm1.json

# loosening objects
jmc Loose moe.json

# having alternatives
jmc Geom marseille.json seoul-tokyo.json

# numbers vs numbers
jmc -r Town beijing.json shanghai.json
jmc --loose-number Town beijing.json shanghai.json

# composing objects
# playing with constraints
# transforming models
# larger examples

# prefering yaml or js
jmc -r Person-0.model.json hobbes.json moe.json
jmc -r Person-0.model.yaml hobbes.json moe.json
jmc -r Person-0.model.js hobbes.json moe.json

# running with C, JS or Python

# exporting to JSON Schema
