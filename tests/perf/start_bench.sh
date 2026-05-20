#! /bin/bash
#
# start bench
#

export POD=${POD:-docker}
export POD_PULL=${POD_PULL:-1}
export POD_OPTS=

if [ $1 = "-h" -o $1 = "--help" ] ; then
  cat <<EOF

Standalone command to start the jmc benchmark with docker-in-docker or podman-in-podman
in a local directory.

Arguments:
- TAG: docker.io/zx80/jmc-bench-$POD docker tag, default is "latest"
- ID: bench id, name of new work directory, default is <date-number>, eg 2038011900
- others: passed to "benchmark.sh"

Environment:
- POD: container command, "docker" or "podman", default is "docker" ($POD)
- POD_PULL: (1/0) whether to pull container images before launch ($POD_PULL)
- JMC_BENCH_IMAGE: overide default docker.io/zx80/jmc-bench-$POD image for testing ($JMC_BENCH_IMAGE)
- JMC: docker.io/zx80/jmc container tag, default is "latest" ($JMC)
- JSC: ghcr.io/sourcemeta/jsonschema container tag, default is "latest" ($JSC)
- JMC_OPTS: options for jmc ($JMC_OPTS)
- JSB_DIR: JSON Schema Benchmark directory, default is to clone ($JSB_DIR)

Example:

  JMC_OPTS=--no-predef JMC=dev $0 dev -p 8 -l 1000 -r 3 -T bc

For further details: https://json-model.org/#/BENCH

EOF
  exit 0
fi

# err status some message to display…
function err()
{
  local status=$1
  shift
  echo "$@" >&2
  exit $status
}

# optional first argument container tag
if [[ "$1" != -* ]] ; then
  bench=$1
  shift
else
  bench=latest
fi

# optional second argument benchmark id
if [[ "$1" != -* ]] ; then
  bench_id=$1
  [ -e "$bench_id" ] && err 1 "cannot override $bench_id"
  shift
else
  bench_id=
fi

container_opts=(--hostname=$(hostname))
bench_opts=()

# default bench_id
if [ ! "$bench_id" ] ; then
  let count=0 now=$(date +%Y%m%d)
  while true ; do
    bench_id=$(printf "$now%02x" $count)
    [ ! -e $bench_id ] && break
    let count+=1
    [ $count -eq 1024 ] && err 2 "cannot find bench directory name"
  done
fi

mkdir $bench_id || err 3 "cannot create directory: $bench_id"
cd $bench_id || err 4 "cannot change directory: $bench_id"

# forward environment settings to container
if [ "$JMC_OPTS" ] ; then
  container_opts+=(-e "JMC_OPTS=$JMC_OPTS")
  bench_opts+=(--env JMC_OPTS)
fi

if [ "$JSB_DIR" ] ; then
  [ -d "$JSB_DIR" ] || err 6 "no such directory: $JSB_DIR"
  # this is for "benchmark.sh"
  container_opts+=(-v "$JSB_DIR:/workspace/jsb")
  # this is for "jmc"
  POD_OPTS="-v $JSB_DIR:/app/workspace/jsb"
fi

if [ "$JMC" ] ; then
  bench_opts+=(--jmc "$JMC")
fi

if [ "$JSC" ] ; then
  bench_opts+=(--jsc "$JSC")
fi

# hackish container-in-container
if [ "$POD" = "docker" ] ; then
  # docker-in-docker
  WORKDIR="$PWD"
  container_opts+=(-v /var/run/docker.sock:/var/run/docker.sock)
  container_opts+=(-v /etc/passwd:/etc/passwd:ro -v /etc/group:/etc/group:ro)
  # --user $(id -u):$(id -g)
elif [ "$POD" = "podman" ] ; then
  # podman-in-podman
  WORKDIR=.
  container_opts+=(-v $HOME/.local/share/containers:/home/podman/.local/share/containers)
  container_opts+=(--privileged --security-opt label=disable)
else
  err 5 "unexpected container command: $POD"
fi

image="${JMC_BENCH_IMAGE:-docker.io/zx80/jmc-bench-$POD}:$bench"

echo "# container options: ${container_opts[@]}"
echo "# benchmark options: --id=$bench_id ${bench_opts[@]} $@"

# possibly check for latest version
[ "$POD_PULL" = 1 ] && $POD pull $image

# start "benchmark.sh" container
exec $POD run \
  --rm \
  --name jmcbench_$bench_id \
  --pull=never \
  -v .:/workspace \
  -e WORKDIR="$WORKDIR" \
  -e POD="$POD" \
  -e POD_PULL="$POD_PULL" \
  -e POD_OPTS="$POD_OPTS" \
  "${container_opts[@]}" \
    "$image" \
      --id=$bench_id "${bench_opts[@]}" "$@" > $bench_id.output 2>&1
