#! /bin/bash

jmc --version

jmc Person-0.model.json hobbes.json
jmc -r Person-0.model.json moe.json
jmc -r Person-1.model.json hobbes.json moe.json elysee.json
jmc -r Person-2.model.json hobbes.json moe.json elysee.json
jmc -n PI Person-2.model.json pi.json
jmc Loose.model.json moe.json
jmc Geom.model.json marseille.json seoul-tokyo.json
