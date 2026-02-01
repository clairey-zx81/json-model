#! /bin/bash
#
# run jmc benchmark
#
# usage: $0 --help
# eg: $0 --par 12 --runs 5 --loop 1000 --jmc latest --jsc latest --env JMC_OPTS
#

# expected by jmc and js-cli wrappers
export POD=${POD:-docker}

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
PARA=8 LOOP=1000 RUNS=3 ID="benchmark" TASK="bcsvy" cap_py=1 debug=
export JMC=latest JSC=latest JMC_ENV=$JMC_ENV

# get options
while [[ "$1" == -* ]] ; do
  opt=$1
  shift
  case $opt in
    -h|--help)
      echo "$0 [-h] [-v] [-p 8] [-c 5] [-l 1000] [-T $TASK] [--jmc=latest] [--jsc=latest]"
      echo "Options and defaults:"
      echo " --help|-h: this help"
      echo " --debug|-d: set debugging messages"
      echo " --version|-v: show jmc version"
      echo " --id ID: benchmark identifier"
      echo " --container|-C POD: command (current is $POD)"
      echo " --parallel|-p N: benchmark parallelism, eg half available cores ($PARA)"
      echo " --loop|-l L: number of run iterations for performance figures ($LOOP)"
      echo " --runs|-r R: number of runs ($RUNS)"
      echo " --jmc=TAG: container tag for JSON Model Compiler container image ($JMC)"
      echo " --jsc=TAG: container tag for JSON Schema CLI (Blaze) container image ($JSC)"
      echo " --cap-py: reduce loop iterations for python (default)"
      echo " --no-cap-py: do not reduce loop iterations for python"
      echo " --env|-e VARS: environment variables to export to jmc container"
      echo " --task|-T TASK: comparisons to perform (b=blaze c=C s=JS v=Java y=Python)"
      exit 0
      ;;
    -v|--version)
      # NOTE depends on docker.io/zx80/jmc container image
      jmc --version
      exit 0
      ;;
    --id=*) ID=${opt#*=} ;;
    --id) ID=$1 ; shift ;;
    --container=*) POD=${opt#*=} ;;
    --container|-C) POD=$1 ; shift ;;
    -p|--para|--par|--parallel) PARA=$1 ; shift ;;
    --par=*|--para=*|--parallel=*) PARA=${opt#*=} ;;
    -l|--loop) LOOP=$1 ; shift ;;
    --loop=*) LOOP=${opt#*=} ;;
    -r|--runs) RUNS=$1 ; shift ;;
    --runs=*) RUNS=${opt#*=} ;;
    --jmc) JMC=$1 ; shift ;;
    --jmc=*) JMC=${opt#*=} ;;
    --jsc) JSC=$1 ; shift ;;
    --jsc=*) JSC=${opt#*=} ;;
    --env=*) JMC_ENV=${opt#*=} ;;
    -e|--env) JMC_ENV=$1 ; shift ;;
    --cap-py) cap_py=1 ;;
    --no-cap-py) cap_py= ;;
    -d|--debug) debug=1 ;;
    --task=*) TASK=${opt#*=} ;;
    --task|-T) TASK=$1 ; shift ;;
    --) break ;;
    *) err 1 "unexpected option: $opt" ;;
  esac
done

[ $# -ne 0 ] && err 1 "$0 - unexpected arguments: $@"

# check option integer values
[ $PARA -ge 1 ] || err 1 "unexpected parallel value, must be >= 1: $PARA"
[ $LOOP -ge 1 ] || err 1 "unexpected loop value, must be >= 1: $LOOP"
[ $RUNS -ge 3 -a $(( $RUNS % 2 )) -eq 1 ] || err 1 "unexpected runs value, must be >= 1 and odd: $RUNS"

echo "# $$ benchmarking pod=$POD parallel=$PARA loop=$LOOP runs=$RUNS jmc=$JMC jsc=$JSC env=$JMC_ENV"

#
# PARA RUNS
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

function do_status()
{
  echo "# $SECONDS status:" \
       "started=$started stopped=$stopped running=$running" \
       "processes=$processes"
}

trap do_status SIGUSR1

#
# SANITY COMMANDS END FILES
#
echo "# sanity check"
for cmd in git $POD sqlite3 jq id basename grep sed wc /bin/bash /usr/bin/time ; do
  type $cmd || err 2 "command not found: $cmd"
done

for f in jsb tmp perf.db ; do
  test -e $f && err 3 "unexpected dir/file: $f"
done

#
# SETUP
#
echo "# $POD images"
for img in docker.io/zx80/jmc:$JMC ghcr.io/sourcemeta/jsonschema:$JSC ; do
  $POD pull $img || err 4 "cannot $POD pull $img"
done

echo "# cloning repos"
git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 4 "git clone failed (jsb)"

echo "# directory setup"
# NOTE check that jmc CLASSPATH is consistent OR "java path/to/file.java"
mkdir tmp || err 4 "mkdir tmp failed"

let run=$RUNS
while let run-- ; do
  mkdir tmp/$run
done

echo "# script checks"

export JMC_BENCH_DEBUG=$debug
export PATH=$script_dir:$PATH

# check for scripts
for cmd in run.sh jmc js-cli run-to-csv.sh compile-to-csv.sh res-to-csv.sh mdalign.py ; do
  type $cmd || err 5 "script $cmd not found"
done

#
# RUN (189 parallel tasks with default settings)
#
# slowest first
tasks=""
[[ $TASK =~ y ]] && tasks+=" jmc-py"
[[ $TASK =~ v ]] && tasks+=" jmc-java"
[[ $TASK =~ s ]] && tasks+=" jmc-js"
[[ $TASK =~ b ]] && tasks+=" blaze"
[[ $TASK =~ c ]] && tasks+=" jmc-c"

echo "# validation runs (include at least one compilation each)"

for trg in $tasks ; do
  let run=$RUNS
  while let run-- ; do
    for dir in jsb/schemas/* ; do
      # time adjustment for slow runs
      if [ "$cap_py" -a $trg = "jmc-py" ] ; then
        loop=$(( $LOOP / 10 ))
      else
        loop=$LOOP
      fi
      do_start run.sh $loop tmp/$run/ all $trg $dir
      do_wait $PARA
    done
  done
done

while [ $running -gt 0 ] ; do
  do_wait 0
done

#
# DATA
#
echo "# extracts"
compile-to-csv.sh tmp/[0-9]*/*_compile.csv > compile.csv
run-to-csv.sh tmp/[0-9]*/*.out > perf.csv
res-to-csv.sh tmp/[0-9]*/*.out > result.csv

for dir in jsb/schemas/* ; do
  [ -d "$dir" ] || continue
  name=$(basename $dir)
  ssize=$(jq < $dir/schema.json | wc -l)
  msize=$(jq < tmp/0/${name}_model.json | wc -l)
  tests=$(wc -l < $dir/instances.jsonl)
  echo "$name,$ssize,$msize,$tests"

  # all cases stats
  let n=0
  while read value ; do
    let n++
    echo "$name,$n,${#value}"
  done < $dir/instances.jsonl >> casevalues.csv
done > cases.csv

#
# ANALYSIS
#
echo "# create performance tables"
sqlite3 perf.db < $script_dir/perf.sql

# cpu data
cpu_model=$(lscpu --extended=MODELNAME | sed -n 2p)
cpu_count=$(lscpu --extended=CPU | sed 1d | wc -l)

function pod_id()
{
  $POD inspect --format="{{.Id}}" "$1" | cut -d: -f2 | cut -c -8
}

#
# OUTPUT
#
cat <<EOF > "$ID.md"
# JSON Model Compiler Benchmark Run

For each test case, a radar of the relative speed performance of each tool,
the higher the better, **1.00** is best. Fully non working case(s) removed, if any.
Cases are sorted per decreasing performance of the fastest tools.
The radar is adjusted dynamically wrt the fastest _visible_ tool, click to select
or deselect tools for easier comparisons.

<div class="chart-container" style="position: relative; width: 70vw; height: 50vh;">
  <canvas id="PerformanceRadar"></canvas>
</div>
<script>showRadar("PerformanceRadar", "/benchmarks/$ID.json")</script>

## Summary

- **id:** $ID
- **now:** $(date)
- **host:** $(hostname)
- **cpu model:** $cpu_model
- **cpu cores:** $cpu_count
- **jmc version:** $(jmc --version)
- **jsonschema version:** $(js-cli --version)
- **jsonschema-benchmark version:** $(GIT_DIR=./jsb/.git git rev-parse --short=8 HEAD), $(cat jsb/schemas/*/instances.jsonl | sort -u | wc -l) unique tests
- **duration:** $SECONDS seconds

## Parameters

- **container command:** $POD
- **jmc container version:** $JMC ($(pod_id docker.io/zx80/jmc:$JMC))
- **jsc container version:** $JSC ($(pod_id ghcr.io/sourcemeta/jsonschema:$JSC))
- **benchmark parallelism:** $PARA
- **number of runs:** $RUNS
- **number of case iterations:** $LOOP
- **cap python:** $cap_py (whether to reduce iterations for python runs)
- **debug:** $debug
- **tasks:** $tasks
- **exported environment variables:** \`$JMC_ENV\`
$(for var in $JMC_ENV ; do echo "  - \`$var\`: \`${!var}\`" ; done)
EOF

# for markdown, including table alignment filter
sqlite3 -markdown perf.db < $script_dir/show.sql | mdalign.py >> "$ID.md"

# for latex
sqlite3 -csv perf.db < $script_dir/show.sql > "$ID.csv"

# for chart
sqlite3 perf.db < $script_dir/radar.sql | jq > "$ID.json"

#
# DONE
#
echo "# $$ benchmarking done after $SECONDS"
