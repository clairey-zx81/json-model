#! /bin/bash
#
# run jmc benchmark
#
# usage: $0 --help
#
# eg: $0 --par 12 --runs 5 --loop 1000 --jmc latest --jsc latest --env JMC_OPTS
#

START=$SECONDS

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
PARA=8 LOOP=1000 RUNS=3 ID="benchmark" TASK="bcsvy" cap=1 debug= show_opt=--standard unshift=
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
      echo " --cap: reduce loop iterations for slow scripts (default)"
      echo " --no-cap: do not reduce loop iterations for slow scripts"
      echo " --env|-e VARS: environment variables to export to jmc container"
      echo " --task|-T TASK: comparisons to perform (b=blaze c=C s=JS v=Java y=Python l=Perl)"
      echo " --unshift|-u: unshift overhead estimation from measures"
      exit 0
      ;;
    -v|--version)
      # NOTE expects "jmc" wrapper, depends on docker.io/zx80/jmc container image
      jmc --version
      jmc exec jsu-compile --version
      jmc exec cc --version | head -1
      jmc exec clang --version | head -1
      jmc exec python --version | head -1
      jmc exec node --version | head -1
      jmc exec javac --version | head -1
      jmc exec perl -e 'print "Perl $^V\n"' | head -1
      version=$(dirname $0)/.version
      if [ -f "$version" ] ; then
        echo "$0 version: $(cat "$version")"
      else
        echo "$0 version: unknown"
      fi
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
    --cap) cap=1 ;;
    --no-cap) cap= ;;
    -d|--debug) debug=1 ;;
    --task=*) TASK=${opt#*=} ;;
    --task|-T) TASK=$1 ; shift ;;
    --unshift|-u) unshift="--unshift" ;;
    --) break ;;
    *) err 1 "unexpected option: $opt" ;;
  esac
done

[ $# -ne 0 ] && err 1 "$0 - unexpected arguments: $@"

# check option integer values
[ $PARA -ge 1 ] || err 1 "unexpected parallel value, must be >= 1: $PARA"
[ $LOOP -ge 1 ] || err 1 "unexpected loop value, must be >= 1: $LOOP"
[ $RUNS -ge 3 -a $(( $RUNS % 2 )) -eq 1 ] || err 1 "unexpected runs value, must be >= 1 and odd: $RUNS"

# non standard run
[ "$TASK" != "bcsvy" ] && show_opt=

echo "# $$ benchmarking pod=$POD parallel=$PARA loop=$LOOP runs=$RUNS jmc=$JMC jsc=$JSC env=$JMC_ENV task=$TASK"

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
# SANITY COMMANDS, SCRIPTS AND FILES
#
echo "# sanity check"
for cmd in git $POD jq id basename grep egrep sed wc gron /bin/bash /usr/bin/time ; do
  type $cmd || err 2 "command not found: $cmd"
done

for f in tmp perf.db ; do
  test -e $f && err 3 "unexpected dir/file: $f"
done

export JMC_BENCH_DEBUG=$debug
export PATH=$script_dir:$PATH

for cmd in run.sh jmc js-cli run-to-csv.py compile-to-csv.sh res-to-csv.py src-to-csv.py report.py radar.py ; do
  type $cmd || err 5 "script $cmd not found"
done

if [ "$debug" ] ; then
  echo "## raw docker commands"
  jmc echo --version
  js-cli echo --version
fi

echo "## started $(( $SECONDS - $START ))"
START=$SECONDS

#
# SETUP
#

if [ "$POD_PULL" = "1" ] ; then
  echo "# pulling $POD images"
  for img in docker.io/zx80/jmc:$JMC ghcr.io/sourcemeta/jsonschema:$JSC ; do
    $POD pull $img || err 4 "cannot $POD pull $img"
  done
else
  echo "# using $POD images"
fi

if [ -d jsb ] ; then
  echo "# reusing existing jsb directory"
  echo "## jmc forwarding: $JMC_POD_OPTS"
  echo "## js-cli forwarding: $JSC_POD_OPTS"
else
  echo "# cloning jsb repos"
  git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git jsb || err 4 "git clone failed (jsb)"
fi

echo "# directory setup"
# NOTE check that jmc CLASSPATH is consistent OR "java path/to/file.java"
mkdir tmp || err 4 "mkdir tmp failed"

let run=$RUNS
while let run-- ; do
  mkdir tmp/$run || err 4 "mkdir tmp/$run failed"
done

#
# RUN (hundreds of parallel tasks with default settings)
#
# slowest first
# TODO add sql?
# TODO control java json lib variants?
tasks=""
[[ $TASK =~ l ]] && tasks+=" jmc-pl"
[[ $TASK =~ y ]] && tasks+=" jmc-py"
[[ $TASK =~ v ]] && tasks+=" jmc-java"
[[ $TASK =~ s ]] && tasks+=" jmc-js"
[[ $TASK =~ b ]] && tasks+=" blaze"
[[ $TASK =~ c ]] && tasks+=" jmc-c"

echo "## setup done $(( $SECONDS - $START ))"
START=$SECONDS

echo "# validation runs (include at least one compilation each)"

for trg in $tasks ; do
  let run=$RUNS
  while let run-- ; do
    for dir in jsb/schemas/* ; do
      # time adjustment for slow runs
      if [[ "$cap" && $trg = jmc-p? ]] ; then
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

echo "## validation done $(( $SECONDS - $START ))"

#
# DATA
#
echo "# extracting data..."

START=$SECONDS
compile-to-csv.sh tmp/[0-9]*/*_compile.csv > compile.csv
echo "## compilation times $(( $SECONDS - $START ))"

START=$SECONDS
run-to-csv.py tmp/[0-9]*/*.out > perf.csv
echo "## run times $(( $SECONDS - $START ))"

START=$SECONDS
res-to-csv.py tmp/[0-9]*/*.out > result.csv
echo "## result counts $(( $SECONDS - $START ))"

START=$SECONDS
shopt -s nullglob
src-to-csv.py tmp/0/*.{c,java,js,pl,py,model.json} > sources.csv
echo "## source summary $(( $SECONDS - $START ))"

START=$SECONDS

for dir in jsb/schemas/* ; do
  [ -d "$dir" ] || continue
  name=$(basename $dir)
  # full schema locs
  ssize=$(jq < $dir/schema.json | wc -l)
  # locs without documentation stuff, may be approximated
  nsize=$(
    gron $dir/schema.json |
    egrep -v '(\$comment|description|title|default|deprecated|readOnly|writeOnly|examples) = ' |
    wc -l
  )
  msize=$(jq < tmp/0/${name}.model.json | wc -l)
  tests=$(wc -l < $dir/instances.jsonl)
  echo "$name,$ssize,$nsize,$msize,$tests"

  # all cases stats
  jsonl2csv.py $name $dir/instances.jsonl >> casevalues.csv
done > cases.csv

echo "## case stats $(( $SECONDS - $START ))"

#
# CPU DATA
#
START=$SECONDS

# collect cpu data
cpu_model=$(lscpu --extended=MODELNAME | sed -n 2p)
cpu_count=$(lscpu --extended=CPU | sed 1d | wc -l)

cpu=/sys/devices/system/cpu
read cur_freq < $cpu/cpu0/cpufreq/scaling_cur_freq
read min_freq < $cpu/cpu0/cpufreq/scaling_min_freq
read max_freq < $cpu/cpu0/cpufreq/scaling_max_freq
read hyper_threading < $cpu/smt/active

# show convenient unit for data in K
function unit()
{
  local perf=${1%?????}  # in 100M
  local giga=${perf%?}
  local frac=${perf#$giga}
  echo "${giga}.${frac}G"
}

# frequency display depends on current conditions
if [ $min_freq -eq $max_freq ] ; then
  # TODO check that $cur_freq is indeed set as expected
  frequency="$(unit $min_freq)Hz (HT=$hyper_threading)"
else
  frequency="$(unit $cur_freq)Hz ($(unit $min_freq)Hz-$(unit $max_freq)Hz, HT=$hyper_threading)"
fi

#
# REPORT
#
REPORT_START=$SECONDS

function pod_id()
{
  $POD inspect --format="{{.Id}}" "$1" | cut -d: -f2 | cut -c -8
}

version_file=$(dirname $0)/.version
if [ -f "$version_file" ] ; then
  read version < "$version_file"
else
  version="unknown"
fi

overhead="removed"
[ "$unshift" ] && overhead="kept"

debug_status="no"
[ "$debug" ] && debug_status="yes"

cat <<EOF > "$ID.md"
# JSON Model Compiler Benchmark Run

For each test case, a radar of the **relative speed** performance of each tool,
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
- **cpu freq:** $frequency
- **jmc version:** $(jmc --version)
- **jsu version:** $(jmc exec jsu-compile --version)
- **benchmarking script:** $version
- **jsonschema-cli version:** $(js-cli --version)
- **jsonschema-benchmark version:** $(GIT_DIR=./jsb/.git git rev-parse --short=8 HEAD), $(cat jsb/schemas/*/instances.jsonl | sort -u | wc -l) unique tests
- **cc version:** $(jmc exec cc --version|head -1)
- **clang version:** $(jmc exec clang --version|head -1)
- **python version:** $(jmc exec python --version|head -1)
- **node version:** $(jmc exec node --version|head -1)
- **javac version:** $(jmc exec javac --version|head -1)
- **perl version:** $(jmc exec perl -e 'print "$^V\n"'|head -1)
- **duration:** $SECONDS seconds

## Parameters

- **container command:** $POD
- **jmc container version:** $JMC ($(pod_id docker.io/zx80/jmc:$JMC))
- **jsc container version:** $JSC ($(pod_id ghcr.io/sourcemeta/jsonschema:$JSC))
- **benchmark parallelism:** $PARA
- **number of runs:** $RUNS
- **number of case iterations:** $LOOP
- **cap:** $cap (whether to reduce iterations for slow script runs)
- **overhead:** $overhead (measure overhead estimations may be removed from execution times)
- **debug:** $debug_status
- **tasks:** $tasks
- **exported environment variables:** \`$JMC_ENV\`
$(for var in $JMC_ENV ; do echo "  - \`$var\`: \`${!var}\`" ; done)
EOF

echo "## report head $(( $SECONDS - $REPORT_START ))"

# generate markdown tables
START=$SECONDS
report.py $show_opt $unshift >> "$ID.md"
echo "## report tables $(( $SECONDS - $START ))"
echo "## report generation $(( $SECONDS - $REPORT_START ))"

# generate radar chart data
START=$SECONDS
radar.py > "$ID.json"
echo "## radar generation $(( $SECONDS - $START ))"

#
# DONE
#
echo "# $$ benchmarking done after $SECONDS"
