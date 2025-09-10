#! /bin/bash

# performance run in parallel
PARALLEL=${1:-4}

# performance loop count
LOOP=${2:-1000}

function err()
{
    local status=$1
    shift 1
    echo "$@" >&2
    exit $status
}

# parallelism management
started=0 running=0 stopped=0 processes=""

function do_start()
{
    echo "# starting: $@"
    "$@" &
    processes="$processes $! "
    echo "# started: $!"
    let started+=1 running+=1
}

function do_wait()
{
    local loaded=${1:-0}
    if [ $running -ge $loaded ] ; then
      echo "# waiting on $processes"
      wait -n -p stopped_pid
      echo "# stopped: $stopped_pid"
      processes=${processes/ $stopped_pid /}
      let running-=1 stopped+=1
    fi
}

echo "# sanity check"
for cmd in git docker sqlite3 /usr/bin/time ; do
  type $cmd || err 1 "command $cmd not found"
done

for dir in jmc jsb tmp ; do
  test -d $dir && err 2 "unexpected directory $dir"
done

echo "# cloning repos"
git clone https://github.com/clairey-zx81/json-model.git jmc || err 3 "jmc clone failed"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 3 "jsb clone failed"
mkdir tmp || err 3 "mkdir tmp failed"

script_dir=$PWD/jmc/tests/perf
export PATH=$script_dir:$PATH

echo "# compilation runs"
for i in 1 2 3 4 ; do
  do_start perf_run.sh 0 tmp/${i}_ jsb/schemas/*
  do_wait $PARALLEL
done

echo "# validation runs"
for dir in jsb/schemas/* ; do
  do_start perf_run.sh $LOOP tmp/ $dir
  do_wait $PARALLEL
done

while [ $running -gt 0 ] ; do
  do_wait 0
done

echo "# extracts"
compile-to-csv.sh tmp/*_compile.csv > compile.csv
run-to-csv.sh tmp/*.out > perf.csv
res-to-csv.sh tmp/*.out > result.csv

echo "# statistics"
echo "## number of schemas: $(echo jsb/schemas/* | wc -l)"
echo "## number of values: $(cat jsb/schemas/*/instances.jsonl | wc -l)"
# TODO more stats

echo "# performance tables"
sqlite3 < $script_dir/perf.sql
