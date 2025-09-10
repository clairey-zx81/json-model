#! /bin/bash

function err()
{
    local status=$1
    shift 1
    echo "$@" >&2
    exit $status
}

# sanity check
for cmd in git docker sqlite3 ; do
  type $cmd || err 1 "command $cmd not found"
done

echo "# cloning benchmark"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb

echo "# compilation"
./perf_run.sh 0 jsb/schemas/*
./perf_run.sh 0 jsb/schemas/*
./perf_run.sh 0 jsb/schemas/*
./perf_run.sh 0 jsb/schemas/*

echo "# run"
./perf_run.sh 1000 jsb/schemas/*

echo "# extract"
./compile-to-csv.sh *_compile.csv > compile.csv
./run-to-csv.sh *.out > perf.csv

echo "# performance tables"
sqlite3 < perf.sql
