#! /bin/bash

function err()
{
    local status=$1
    shift 1
    echo "$@" >&2
    exit $status
}

echo "# sanity check"
for cmd in git docker sqlite3 /usr/bin/time ; do
  type $cmd || err 1 "command $cmd not found"
done

echo "# cloning repos"
git clone https://github.com/clairey-zx81/json-model.git jmc
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb

script_dir=$PWD/jmc/tests/perf
export PATH=$script_dir:$PATH

echo "# compilation"
perf_run.sh 0 jsb/schemas/*
perf_run.sh 0 jsb/schemas/*
perf_run.sh 0 jsb/schemas/*
perf_run.sh 0 jsb/schemas/*

echo "# run"
perf_run.sh 1000 jsb/schemas/*

echo "# extract"
compile-to-csv.sh *_compile.csv > compile.csv
run-to-csv.sh *.out > perf.csv

echo "# performance tables"
sqlite3 < $script_dir/perf.sql
