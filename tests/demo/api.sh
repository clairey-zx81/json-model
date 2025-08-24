#! /bin/bash

echo "# Python Static API"
jmc -o person.py --module Person
./api_python_static.py

echo "# Python Dynamic API"
./api_python_dynamic.py

echo "# JavaScript API"
jmc --loose -o person.mjs Person
./api_javascript.js

echo "# C API"
jmc -o person.c Person
# ...

echo "# PL/pgSQL API"
jmc --loose -o person.sql Person
createdb jm_test
psql -f person.sql jm_test

psql jm_test <<EOF
CREATE TABLE SomeOne(
  sid SERIAL8 PRIMARY KEY,
  data JSONB NOT NULL CHECK (check_model(data, '', NULL))
);
CREATE UNIQUE INDEX SomeOne_Name ON SomeOne ((data->>'name'));

INSERT INTO SomeOne(data) VALUES ('{"name": "Hobbes", "birth": "2020-07-29"}');
INSERT INTO SomeOne(data) VALUES ('{"name": "Pi", "birth": "1592-04-31"}');
EOF

dropdb jm_test

echo "# Perl API"
jmc --loose -o Person.pm Person
./api_perl.pl
