#! /bin/bash

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
jmc University psl.json

# playing with constraints
jmc -r Tournament musketeers.json 3_musketeers.json

# transforming models
jmc Person-3 hobbes.json bastille.json

# prefering yaml or js
jmc -r Person-0.model.json hobbes.json moe.json
jmc -r Person-0.model.yaml hobbes.json moe.json
jmc -r Person-0.model.js hobbes.json moe.json

# running with C, JS, Python, Perl, Java
echo "# C exec"
jmc -o person.out Person-2
./person.out -T 1000000 hobbes.json

echo "# JS script"
jmc -o person.js Person-2
./person.js -T 1000000 hobbes.json

echo "# Python script"
jmc -o person.py Person-2
./person.py -T 100000 hobbes.json

echo "# Perl script"
jmc -o person.pl Person-2
[ "$PERLLIB" ] && ./person.pl -T 10000 hobbes.json

echo "# Java run"
jmc -o Person.java Person-2  # Java
if [ "$CLASSPATH" ] ; then
  javac Person.java
  java Person -T 100000 hobbes.json
fi

# using from C, JS, Python, Perl or PL/pgSQL
jmc -o person.o Person-2
jmc -o person.mjs Person-2
jmc -o Person.py --module Person-2
./test_python_module.py
jmc -o PersonModels.py -E -n Root Person-2  # pydantic

jmc -o person.pm Person-2
[ "$PERLLIB" ] && PERLLIB=$PERLLIB:. ./test_perl_module.pl

jmc -o person.sql Person-2
psql -f person.sql

for f in [a-z]*.json ; do
  echo -e "$f\t$(jq -c < $f)"
done | psql -f test_values.sql

# exporting to, importing from JSON Schema
jmc -E -F yaml Person-2
jmc -E Person-2 | jsu-model
