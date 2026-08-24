#! /bin/bash
#
# run performance script from cron
#

# take scripts from jmc source?
PERF=$HOME/dev/json-model/tests/perf
WORK=$HOME/dev/cron-json-model
TARGET=$HOME/perf

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
Usage: $0 [ -c -f -p -i id ]
  -h: this help
  -c: check for new versions and run if any (yes)
  -f: force run (no)
  -p: publish to git repos (yes)
  -i id: use existing benchmark id (auto)
EOF
}

# option management
check=1 force= publish=1

while [[ $1 == -* ]] ; do
  opt=$1
  shift
  case $opt in
    --help|-h) usage ; exit 0 ;;
    --check|-c) check=1 ;;
    --no-check|-nc) check= ;;
    --force|-f) force=1 ;;
    --no-force|-nf) force= ;;
    --publish|-p) publish=1 ;;
    --no-publish|-np) publish= ;;
    --id|-i) bench_id=$1 ; shift ;;
    --id=*) bench_id=${opt#*=} ;;
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
test -d $TARGET/jsb_dir || err 2 "missing json-schema benchmark directory: $TARGET/jsb_dir"

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

  # TODO also check jmc-bench image?
  SBC=ghcr.io/sourcemeta/jsonschema:latest
  JMC=docker.io/zx80/jmc:latest

  docker pull $SBC || err 6 "cannot docker pull: $SBC"
  docker pull $JMC || err 6 "cannot docker pull: $JMC"

  docker run --rm --name sbc_version_$$ $SBC --version > $VERSION.sbc.tmp || err 7 "error getting version: $SBC"
  docker run --rm --name jmc_version_$$ --entrypoint jsu-compile $JMC --version > $VERSION.jmc.tmp || err 7 "error getting version: $JMC"

  # run if versions differ
  for tool in sbc jmc ; do
    cmp -s $VERSION.$tool $VERSION.$tool.tmp || run=1
  done
fi

#
# run bench if required
#
if [ "$run" -o "$force" ] ; then
  # setup standard run

  export JMC=main
  export JMC_OPTS="--single-line-regex --cc=clang --precompiled --short-version"
  # defaults are the next with 2 exceptions
  # export JSU_OPTS="--id --fix --no-strict"
  # export JSU_OPTS="--id --no-fix --no-strict"
  # export JSU_OPTS="--no-id --no-fix --no-strict"
  export JSB_DIR="$HOME/perf/jsb_dir"
  export POD_PULL=0
  export JMC_BENCH=${JMC_BENCH:-main}

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

  PARA=12 LOOP=1000 RUNS=11

  $PERF/calcutta.sh on
  $PERF/start_bench.sh $JMC_BENCH $bench_id -p $PARA -l $LOOP -r $RUNS -L -c "$@"
  $PERF/calcutta.sh off

  # test generated directory
  test -d $bench_id || err 9 "missing bench directory: $bench_id"
  for file in $bench_id/$bench_id.md $bench_id/$bench_id.json ; do
    test -f $file || err 9 "missing generated file: $file"
  done

  # TODO improve run checks?!

  # record benchmark version
  if [ "$check" ] ; then
    cp $VERSION.sbc.tmp $VERSION.sbc
    cp $VERSION.jmc.tmp $VERSION.jmc
    rm -f $VERSION.sbc.tmp $VERSION.jmc.tmp
  fi
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

  cp $TARGET/$bench_id/$bench_id.{json,md} $WORK/site/benchmarks/
  git add site/benchmarks/$bench_id.* || err 11 "cannot git add artifacts"

  git commit -m "add artifact $bench_id from cron job" || err 11 "cannot git commit artifacts"
  git push || err 11 "cannot git push"
fi
