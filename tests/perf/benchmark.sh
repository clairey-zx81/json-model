#! /bin/bash
#
# run jmc benchmark
#

# performance run in parallel
PARALLEL=${1:-4}

# performance loop count
LOOP=${2:-1000}

# json model compiler
JMC=${3:-latest}

# jsonschema cli
JSC=${4:-latest}

function err()
{
    local status=$1
    shift 1
    echo "$@" >&2
    exit $status
}

#
# PARALLEL RUNS
#
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

#
# SANITY
#

echo "# sanity check"
for cmd in git docker sqlite3 jq id basename grep sed wc /bin/bash /usr/bin/time ; do
  type $cmd || err 1 "command $cmd not found"
done

for f in jmc jsb tmp perf.db ; do
  test -e $f && err 2 "unexpected $f"
done

#
# SETUP
#
echo "# docker images"
docker pull zx80/jmc:$JMC
docker pull ghcr.io/sourcemeta/jsonschema:$JSC

echo "# cloning repos"
git clone https://github.com/clairey-zx81/json-model.git jmc || err 3 "jmc clone failed"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 3 "jsb clone failed"

echo "# misc setup"
mkdir tmp || err 3 "mkdir tmp failed"
script_dir=$PWD/jmc/tests/perf
export PATH=$script_dir:$PATH

# check for scripts
for cmd in perf_run.sh jmc js-cli run-to-csv.sh compile-to-csv.sh res-to-csv.sh ; do
  type $cmd || err 4 "script $cmd not found"
done

#
# RUN
#
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

#
# DATA
#
echo "# extracts"
compile-to-csv.sh tmp/*_compile.csv > compile.csv
run-to-csv.sh tmp/*.out > perf.csv
res-to-csv.sh tmp/*.out > result.csv

for dir in jsb/schemas/* ; do
  [ -d "$dir" ] || continue
  name=$(basename $dir)
  ssize=$(jq < $dir | wc -l)
  msize=$(jq < tmp/${name}_model.json | wc -l)
  tests=$(wc -l < $dir/instances.jsonl)
  echo "$name,$ssize,$msize,$tests"
done > cases.csv

#
# ANALYSIS
#
echo "# create performance tables"
sqlite3 perf.db < $script_dir/perf.sql

#
# OUTPUT
#
echo "# versions"
echo "## jmc: $(jmc --version)"
echo "## js-cli: $(js-cli --version)"
echo "## statistics"
sqlite3 -box perf.db < $script_dir/show.sql
