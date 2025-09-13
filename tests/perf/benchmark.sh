#! /bin/bash
#
# run jmc benchmark
#
# usage: $0 --par 4 --loop 1000 --jmc latest --jsc latest
#

# error handling
function err()
{
    local status=$1
    shift 1
    echo "$@" >&2
    exit $status
}

# script directory
script_dir=$(dirname $0)

# defaults
PARALLEL=8 LOOP=1000 JMC=latest JSC=latest

# get options
while [[ "$1" == -* ]] ; do
    opt=$1
    shift
    case $opt in
        -h|--help)
            echo "$0 [-p 8] [-l 1000] --jmc=latest --jsc=latest"
            exit 0
            ;;
        -p|--par|--parallel) PARALLEL=$1 ; shift ;;
        --par=*|--parallel=*) PARALLEL=${opt#*} ;;
        -l|--loop) LOOP=$1 ; shift ;;
        --loop=*) LOOP=${opt#*=} ;;
        --jmc) JMC=$1 ; shift ;;
        --jmc=*) JMC=${opt#*=} ;;
        --jsc) JSC=$1 ; shift ;;
        --jsc=*) JSC=${opt#*=} ;;
        --) break ;;
        *) err 1 "unexpected option: $opt" ;;
    esac
done

[ $# -ne 0 ] && err 1 "$0 - unexpected arguments: $@"

echo "# benchmarking parallel=$PARALLEL loop=$LOOP jmc=$JMC jsc=$JSC"

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
      # NOTE ps counting does not seem very reliable
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
  type $cmd || err 2 "command $cmd not found"
done

for f in jsb tmp perf.db ; do
  test -e $f && err 3 "unexpected $f"
done

#
# SETUP
#
echo "# docker images"
docker pull zx80/jmc:$JMC
docker pull ghcr.io/sourcemeta/jsonschema:$JSC

echo "# cloning repos"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 3 "jsb clone failed"

echo "# misc setup"
# NOTE check that jmc CLASSPATH is consistent
mkdir tmp || err 4 "mkdir tmp failed"

export PATH=$script_dir:$PATH

# check for scripts
for cmd in run.sh jmc js-cli run-to-csv.sh compile-to-csv.sh res-to-csv.sh ; do
  type $cmd || err 5 "script $cmd not found"
done

#
# RUN
#
# slowest first
tasks="jmc-py jmc-java jmc-js jmc-c blaze"

echo "# compilation runs"
for i in A B C D ; do
  do_start run.sh 0 tmp/${i}_ cmp all jsb/schemas/*
  do_wait $PARALLEL
done

echo "# validation runs"
for trg in $tasks ; do
  for dir in jsb/schemas/* ; do
    do_start run.sh $LOOP tmp/ all $trg $dir
    do_wait $PARALLEL
  done
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
  ssize=$(jq < $dir/schema.json | wc -l)
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
{
  echo "# versions"
  echo "## jmc: $(jmc --version)"
  echo "## js-cli: $(js-cli --version)"
  echo "# statistics"
  sqlite3 -box perf.db < $script_dir/show.sql
} > benchmark.output

sqlite3 -csv perf.db < $script_dir/show.sql > benchmark.csv
