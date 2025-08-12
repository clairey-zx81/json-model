#! /bin/bash

echo "# jmc version"
jmc --version

echo "# person model v0"
jmc Person-0 hobbes.json
jmc -r Person-0 moe.json

echo "# person model v1, constraining strings"
jmc -r Person-1 hobbes.json moe.json elysee.json

echo "# person model v2, using definitions"
jmc -r Person-2 hobbes.json moe.json elysee.json
jmc -n PI Person-2 pi.json

echo "# reusing definitions"
jmc Class cm1.json

echo "# loosening objects"
jmc Loose moe.json

echo "# having alternatives"
jmc Geom marseille.json seoul-tokyo.json

echo "# numbers vs numbers"
jmc -r Town beijing.json shanghai.json
jmc --loose-number Town beijing.json shanghai.json

echo "# composing objects"
jmc University psl.json

echo "# playing with constraints"
jmc -r Tournament musketeers.json 3_musketeers.json

echo "# transforming models"
jmc Person-3 hobbes.json bastille.json

echo "# prefering yaml or js"
jmc -r Person-0.model.json hobbes.json moe.json
jmc -r Person-0.model.yaml hobbes.json moe.json
jmc -r Person-0.model.js hobbes.json moe.json

echo "# running with C, JS, Python, Perl, Java"
echo "## C exec"
jmc -o person.out Person-2
./person.out -T 1000000 hobbes.json

echo "## JS script"
jmc -o person.js Person-2
./person.js -T 1000000 hobbes.json

echo "## Python script"
jmc -o person.py Person-2
./person.py -T 100000 hobbes.json

echo "## Perl script"
jmc -o person.pl Person-2
[ "$PERLLIB" ] && ./person.pl -T 10000 hobbes.json

echo "## Java run"
jmc --loose -o Person.java Person-2  # Java
if [ "$CLASSPATH" ] ; then
  javac Person.java
  java Person -T 100000 hobbes.json
fi

# using from C, JS, Python, Perl or PL/pgSQL
echo "# using ..."
jmc -o person.o Person-2
jmc -o person.mjs Person-2
jmc -o Person.py --module Person-2
./test_python_module.py

jmc -o PersonModels.py -E -n Root Person-2  # pydantic

jmc -o person.pm Person-2
[ "$PERLLIB" ] && PERLLIB=$PERLLIB:. ./test_perl_module.pl

echo "## SQL"
jmc -o person.sql Person-2
type psql > /dev/null 2>&1 && {
    psql -f person.sql

    for f in [a-z]*.json ; do
      echo -e "$f\t$(jq -c < $f)"
    done | psql -f test_values.sql
}

echo "# exporting to, importing from JSON Schema"
jmc --loose -E -F yaml Person-2
jmc -E Person-2 | jsu-model
