#! /bin/bash
#
# run performance script from cron
#

# running script is a copy
PERF=$HOME/dev/json-model/tests/perf
WORK=$HOME/dev/cron-json-model
TARGET=$HOME/perf

#
# Environment overrides:
#
# - JMC: docker tag for jmc image (main)
# - JMC_BENCH: docker tag for jmc-bench image  (main)
# - SBC: docker tag for sourcemeta blaze cli (latest)
# - PARA: bench parallelism (12)
# - LOOP: bench iterations (1000)
# - RUNS: number of runs (11)
#
export JMC=${JMC:-main}
export JMC_BENCH=${JMC_BENCH:-main}
export SBC=${SBC:-latest}
export PARA=${PARA:-12}
export LOOP=${LOOP:-1000}
export RUNS=${RUNS:-11}

# setup standard run
export JMC_OPTS="--single-line-regex --cc=clang --precompiled --short-version"
# defaults are the next one with 2 exceptions
# export JSU_OPTS="--id --fix --no-strict"
# export JSU_OPTS="--id --no-fix --no-strict"
# export JSU_OPTS="--no-id --no-fix --no-strict"
export JSB_DIR="$TARGET/jsb_dir"
export POD_PULL=0  # do not pull images again!

function err()
{
  local status=$1
  shift 1
  echo "$@" >&2
  exit $status
}

function usage()
{
  cat <<EOF
Usage: $0 [ -c -f -p -i id ] [ -- benchmark options... ]
  -h: this help
  -c/-nc: check for new versions and run if any (yes)
  -f/-nf: force run (no)
  -p/-np: publish to git repos (yes)
  -i id/-ni: use existing benchmark id (auto)
EOF
}

# option management
check=1 run= publish= no_publish=

while [[ $1 == -* ]] ; do
  opt=$1
  shift
  case $opt in
    --help|-h) usage ; exit 0 ;;
    --check|-c) check=1 ;;
    --no-check|-nc) check= ;;
    --force|-f) run=1 ;;
    --no-force|-nf) run= ;;
    --publish|-p) publish=1 no_publish= ;;
    --no-publish|-np) no_publish=1 ;;
    --id|-i) bench_id=$1 ; shift ;;
    --id=*) bench_id=${opt#*=} ;;
    --no-id|-ni) bench_id= ;;
    --) break ;;
    -*) usage ; err 1 "unexpected option: $opt" ;;
  esac
done

#
# sanity checks
#
test -d $PERF || err 2 "missing source directory: $PERF"
test -x $PERF/start_bench.sh || err 3 "missing executable: $PERF/start_bench.sh"
test -d $TARGET || err 2 "missing target directory: $TARGET"
test -d $JSB_DIR || err 2 "missing json-schema benchmark directory: $JSB_DIR"

if [ "$publish" ] ; then
  test -d $WORK || err 2 "missing working directory: $WORK"
fi

for cmd in docker git ; do
  type $cmd > /dev/null 2>&1 || err 3 "missing command: $cmd"
done

#
# check for new versions
#
if [ "$check" ] ; then
  cd $TARGET || err 5 "cannot cd to: $TARGET"

  VERSION=$TARGET/.bench_version

  # docker images
  SBC_IMG=ghcr.io/sourcemeta/jsonschema:$SBC
  JMC_IMG=docker.io/zx80/jmc:$JMC
  BENCH_IMG=docker.io/zx80/jmc-bench-docker:$JMC_BENCH

  docker pull $SBC_IMG || err 6 "cannot docker pull: $SBC_IMG"
  docker pull $JMC_IMG || err 6 "cannot docker pull: $JMC_IMG"
  docker pull $BENCH_IMG || err 6 "cannot docker pull: $JMC_BENCH_IMG"

  docker run --rm --name sbc_version_$$ $SBC_IMG --version > $VERSION.sbc.tmp || err 7 "error getting version: $SBC_IMG"
  docker run --rm --name jmc_version_$$ --entrypoint jsu-compile $JMC_IMG --version > $VERSION.jmc.tmp || err 7 "error getting version: $JMC_IMG"
  git -C "$JSB_DIR" rev-parse HEAD > $VERSION.jsb.tmp || err 7 "error getting git version: $JSB_DIR"

  # run if versions differ
  for tool in sbc jmc jsb ; do
    cmp -s $VERSION.$tool $VERSION.$tool.tmp || run=1
  done
fi

#
# run bench if required
#
if [ "$run" ] ; then

  if [ ! "$bench_id" ] ; then
    # generate unique bench id
    let count=0 now=$(date +%Y%m%d)
    while true ; do
      bench_id=$(printf "$now%02x" $count)
      [ ! -e $bench_id ] && break
      let count+=1
      [ $count -eq 256 ] && err 8 "cannot find bench directory name"
    done
  else
    echo "using bench_id: $bench_id"
  fi

  PARA=${PARA:-12} LOOP=${LOOP:-1000} RUNS=${RUNS:-11}

  $PERF/calcutta.sh on
  $PERF/start_bench.sh $JMC_BENCH $bench_id -p $PARA -l $LOOP -r $RUNS -L -c "$@"
  $PERF/calcutta.sh off

  # test generated directory
  test -d $bench_id || err 9 "missing bench directory: $bench_id"
  for file in $bench_id/$bench_id.md $bench_id/$bench_id.json ; do
    test -f $file || err 9 "missing generated file: $file"
  done

  # check minimal sizes to ensure success
  msize=$(stat --format "%s" $bench_id/$bench_id.md)
  [ "$msize" -ge 8192 ] || err 9 "small generated file: $bench_id.md"

  jsize=$(stat --format "%s" $bench_id/$bench_id.json)
  [ "$jsize" -ge 4096 ] || err 9 "small generated file: $bench_id.json"

  # record benchmark version
  if [ "$check" ] ; then
    for tool in sbc jmc jsb ; do
      cp $VERSION.$tool.tmp $VERSION.$tool
      rm -f $VERSION.$tool.tmp
    done
  fi

  # switch publish unless disabled
  [ "$no_publish" ] || publish=1
fi

#
# publish (new) artifact
#
if [ "$publish" ] ; then

  [ "$bench_id" ] || err 12 "missing bench id for publish"

  cd $WORK || err 10 "cannot cd to: $WORK"

  # should be auth with a github PAT
  git checkout post || err 11 "cannot git checkout post"
  git pull || err 11 "cannot git pull"
  git submodule update || err 11 "cannot git submodule update"

  cp $TARGET/$bench_id/$bench_id.{json,md} $WORK/site/benchmarks/ || err 11 "cannot cp artifact files"
  git add site/benchmarks/$bench_id.* || err 11 "cannot git add artifacts"

  git commit -m "add artifact $bench_id from cron job" || err 11 "cannot git commit artifact"
  git push || err 11 "cannot git push"
fi
