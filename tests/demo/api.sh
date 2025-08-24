#! /bin/bash

echo "# Python Static API"
jmc -o person.py --module Person
./api_python_static.py

echo "# Python Dynamic API"
./api_python_dynamic.py

echo "# JavaScript API"
jmc --loose -o person.mjs Person
./api_javascript.js
