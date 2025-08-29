#! /bin/bash
#
# Generate a markdown report about the compiler
#

version=$(jmc --version)
githash=$(git show --pretty=format:"%h" --no-patch)

cat <<EOF
# About JSON Model

JSON Model is an on-going [research project](PUBS.md).

The following statistics for version **$version** ($githash) show that the compiler,
code generator and runtimes are quite small, but still heavily tested:

## Compiler Source Code

This count includes model parsing and optimizations, compiler, exporter,
importer, \`jmc\` command script and miscellaneous utilities,
but excludes language-specific code generators.
EOF

cloc --md \
	json_model/analyze.py \
    json_model/convert.py \
    json_model/export.py \
    json_model/language.py \
    json_model/model.py \
    json_model/mtypes.py \
    json_model/objmerge.py \
    json_model/optim.py \
    json_model/recurse.py \
    json_model/resolver.py \
    json_model/script.py \
    json_model/url_cache.py \
    json_model/utils.py \
    json_model/xstatic.py \
    | sed -n -e '/^$/,$p' | head -4

cat <<EOF

## Per-Language Code Generators

Code generators for each target language are written in Python,
plus code snippets in the target language itself:

Language|files|blank|comment|code
:-------|-------:|-------:|-------:|-------:
EOF

cloc --md \
	json_model/python.py \
    json_model/data/*.py \
    | tail -1 | sed "s/SUM:/Python/"

cloc --md \
    json_model/clang.py \
    json_model/data/*.c \
    | tail -1 | sed "s/SUM:/C/"

cloc --md \
    json_model/javascript.py \
    json_model/data/*.js \
    | tail -1 | sed "s/SUM:/JavaScript/"

cloc --md \
    json_model/plpgsql.py \
    json_model/data/*.sql \
    | tail -1 | sed "s/SUM:/PL\/pgSQL/"

cloc --md \
    json_model/perl.py \
    json_model/data/*.pl \
    | tail -1 | sed "s/SUM:/Perl/"

cloc --md \
    json_model/java.py \
    json_model/data/*.java \
    | tail -1 | sed "s/SUM:/Java/"

cloc --md \
    json_model/python.py \
    json_model/data/*.py \
    json_model/clang.py \
    json_model/data/*.c \
    json_model/javascript.py \
    json_model/data/*.js \
    json_model/plpgsql.py \
    json_model/data/*.sql \
    json_model/perl.py \
    json_model/data/*.pl \
    json_model/java.py \
    json_model/data/*.java \
    | tail -1 | sed "s/SUM:/**Total**/;s/\([0-9][0-9]*\)/**\1**/g"

cat <<EOF

## Per-Language Runtimes

Each target language has a dedicated runtime to execute the generated codes:
EOF

cloc --md \
	--include-ext=c,h,sql,pm,pl,java,js,mjs,py \
    --force-lang=C,h \
    json_model/runtime \
    | sed -n -e '/SUM/s/\([0-9][0-9]*\)/**\1**/g;s/SUM:/**Total**/;/^$/,$p' | grep -v '^-[-|]*$'

cat <<EOF

Note that the generated code may also depend on third-party libraries.

## Test Models

Test models cover the various features of JSON Model.
Each model is tested for each target language (Python, C, JavaScript, PL/pgSQL, Perl, Java)
on a set of test vectors.

EOF

echo "- number of models: $(echo tests/*/*.model.json | wc -w)"
echo "- model JSON locs: $(cat tests/*/*.model.json | wc -l)"
echo "- number of test values: $(cat tests/*/*.values.json | egrep '(true|false)' | wc -l)"
