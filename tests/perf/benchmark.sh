#! /bin/bash
#
# run jmc benchmark
#
# usage: $0 --par 8 --comp 5 --loop 1000 --jmc latest --jsc latest
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
PARALLEL=8 LOOP=1000 COMP=5 JMC=latest JSC=latest

# get options
while [[ "$1" == -* ]] ; do
    opt=$1
    shift
    case $opt in
        -h|--help)
            echo "$0 [-h] [-v] [-p 8] [-c 5] [-l 1000] [--jmc=latest] [--jsc=latest]"
            echo "Options and defaults:"
            echo " --help|-h: this help"
            echo " --version|-v: show jmc version"
            echo " --parallel|-p N: benchmark parallelism, eg half available cores ($PARALLEL)"
            echo " --compile|-c C: number of compilation iterations for performance ($COMP)"
            echo " --loop|-l L: number of run iterations for performance figures ($LOOP)"
            echo " --jmc=TAG: docker tag for JSON Model Compiler docker image ($JMC)"
            echo " --jsc=TAG: docker tag for JSON Schema CLI (Blaze) docker image ($JSC)"
            exit 0
            ;;
        -v|--version)
            # NOTE depends on zx80/jmc docker image
            jmc --version
            exit 0
            ;;
        -p|--par|--parallel) PARALLEL=$1 ; shift ;;
        --par=*|--parallel=*) PARALLEL=${opt#*} ;;
        -l|--loop) LOOP=$1 ; shift ;;
        --loop=*) LOOP=${opt#*=} ;;
        -c|--compile) COMP=$1 ; shift ;;
        --comp=*|--compile=*) COMP=${opt#*=} ;;
        --jmc) JMC=$1 ; shift ;;
        --jmc=*) JMC=${opt#*=} ;;
        --jsc) JSC=$1 ; shift ;;
        --jsc=*) JSC=${opt#*=} ;;
        --) break ;;
        *) err 1 "unexpected option: $opt" ;;
    esac
done

[ $# -ne 0 ] && err 1 "$0 - unexpected arguments: $@"

# check option integer values
[ $PARALLEL -ge 1 ] || err 1 "unexpected parallel value, must be >= 1: $PARALLEL"
[ $LOOP -ge 0 ] || err 1 "unexpected loop value, must be >= 0: $LOOP"
[ $COMP -ge 1 ] || err 1 "unexpected comp value, must be >= 1: $COMP"

echo "# $$ benchmarking parallel=$PARALLEL loop=$LOOP comp=$COMP jmc=$JMC jsc=$JSC"

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
# SANITY COMMANDS END FILES
#
echo "# sanity check"
for cmd in git docker sqlite3 jq id basename grep sed wc /bin/bash /usr/bin/time ; do
  type $cmd || err 2 "command not found: $cmd"
done

for f in jsb tmp perf.db ; do
  test -e $f && err 3 "unexpected dir/file: $f"
done

#
# SETUP
#
echo "# docker images"
for img in zx80/jmc:$JMC ghcr.io/sourcemeta/jsonschema:$JSC ; do
  docker pull $img || err 4 "cannot docker pull $img"
done

echo "# cloning repos"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 4 "git clone failed (jsb)"

echo "# misc setup"
# NOTE check that jmc CLASSPATH is consistent
mkdir tmp || err 4 "mkdir tmp failed"

export PATH=$script_dir:$PATH

# check for scripts
for cmd in run.sh jmc js-cli run-to-csv.sh compile-to-csv.sh res-to-csv.sh ; do
  type $cmd || err 5 "script $cmd not found"
done

#
# RUN (189 parallel tasks with default settings)
#
# slowest first
tasks="jmc-py jmc-java jmc-js jmc-c blaze"

echo "# compilation runs"
let nc=$(( $COMP - 1 ))
while let nc-- ; do
  do_start run.sh 0 tmp/C${nc}_ cmp all jsb/schemas/*
  do_wait $PARALLEL
done

echo "# validation runs (include one compilation)"
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
  echo "## jsb uniq tests: $(cat jsb/schemas/*/instances.jsonl | sort -u | wc -l)"
  echo "# statistics"
  sqlite3 -box perf.db < $script_dir/show.sql
} > benchmark.output

sqlite3 -csv perf.db < $script_dir/show.sql > benchmark.csv

#
# DONE
#
echo "# $$ benchmarking done after $SECONDS"
