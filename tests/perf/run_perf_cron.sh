#! /bin/bash
#
# run performance script from cron
#
 
function err()
{ 
  local status=$1
  shift 1
  echo "$@" >&2
  exit $status
}

# option management
force=

while [[ $1 == -* ]] ; do
  opt=$1
  shift 1
  case $opt in
    --force|-f) force=1 ;;
    --no-force|-nf) force= ;;
    --) break ;;
    -*) err 1 "unexpected option: $opt" ;;
  esac
done

# take scripts from jmc source
PERF=$HOME/dev/json-model/tests/perf
TARGET=$HOME/perf

test -d $PERF || err 1 "missing source directory: $PERF"
test -x $PERF/start_bench.sh || err 2 "missing executable: $PERF/start_bench.sh"
test -d $TARGET || err 3 "missing target directory: $TARGET"
test -d $TARGET/jsb_dir || err 4 "missing json-schema benchmark directory: $TARGET/jsb_dir"

cd $TARGET || err 5 "cannot cd to: $TARGET"

VERSION=$TARGET/.bench_version

# TODO also check jmc-bench image?
SBC=ghcr.io/sourcemeta/jsonschema:latest
JMC=docker.io/zx80/jmc:latest

docker pull $SBC || err 6 "cannot docker pull: $SBC"
docker pull $JMC || err 6 "cannot docker pull: $JMC"

docker run --rm $SBC --version > $VERSION.sbc.tmp || err 7 "error getting version: $SBC"
docker run --rm --entrypoint jsu-compile $JMC --version > $VERSION.jmc.tmp || err 7 "error getting version: $JMC"

# run if versions differ
for tool in sbc jmc ; do
  cmp -s $VERSION.$tool $VERSION.$tool.tmp || run=1
done

[ "$run" -o "$force" ] || err 0 "no new version, no force: skipping benchmark run"

# setup standard run
export JMC=main
export JMC_OPTS="--single-line-regex --cc=clang --precompiled --short-version"
# defaults are the next with 2 exceptions
# export JSU_OPTS="--id --fix --no-strict"
# export JSU_OPTS="--id --no-fix --no-strict"
# export JSU_OPTS="--no-id --no-fix --no-strict"
export JSB_DIR="$HOME/perf/jsb_dir"
export POD_PULL=0

jmc_bench=main

# generate unique bench id
let count=0 now=$(date +%Y%m%d)
while true ; do
  bench_id=$(printf "$now%02x" $count)
  [ ! -e $bench_id ] && break
  let count+=1
  [ $count -eq 256 ] && err 8 "cannot find bench directory name"
done

PARA=12 LOOP=1000 RUNS=11

$PERF/calcutta.sh on
$PERF/start_bench.sh $jmc_bench $bench_id -p $PARA -l $LOOP -r $RUNS -L -c "$@"
$PERF/calcutta.sh off

# test generated directory
test -d $bench_id || err 9 "missing bench directory: $bench_id"
for file in $bench_id/$bench_id.md $bench_id/$bench_id.json ; do
  test -f $file || err 10 "missing generated file: $file"
done

# TODO improve checks?!

# record benchmark version
cp $VERSION.sbc.tmp $VERSION.sbc
cp $VERSION.jmc.tmp $VERSION.jmc
rm -f $VERSION.sbc.tmp $VERSION.jmc.tmp

# TODO
# auto commit? pat on https clone
# auto deploy? cron public https clone on branch post on cristalina + rsync
# add a copy on github.io through a deployment script + project conf
