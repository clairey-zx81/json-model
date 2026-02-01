#! /bin/bash
#
# start bench
#

export POD=${POD:-docker}

if [ $1 = "-h" -o $1 = "--help" ] ; then
  cat <<EOF

Standalone command to start the jmc benchmark with docker-in-docker or podman-in-podman
in a local directory.

Arguments:
- TAG: (docker.io/zx80/jmc-bench-$POD docker tag, defaults to "latest")
- others: passed to "benchmark.sh"

Environment:
- POD: container command, "docker" or "podman"
- JMC_OPTS: options for jmc
- JMC: docker.io/zx80/jmc container tag, default is "latest"
- JSC: ghcr.io/sourcemeta/jsonschema container tag, default is "latest"

Example:

  JMC_OPTS=--no-predef JMC=dev $0 dev -p 8 -l 1000 -r 3 -T bc

For further details: https://json-model.org/#/BENCH

EOF
  exit 0
fi

function err()
{
  local status=$1
  shift
  echo "$@" >&2
  exit $status
}

container_opts=(--hostname=$(hostname))
bench_opts=()

let count=0 now=$(date +%Y%m%d)
while true ; do
  bench_id=$(printf "$now%02x" $count)
  [ ! -e $bench_id ] && break
  let count+=1
  [ $count -eq 1024 ] && err 1 "cannot find bench directory name"
done

mkdir $bench_id || err 2 "cannot create directory: $bench_id"
cd $bench_id || err 3 "cannot change directory: $bench_id"

# forward environment settings to container
if [ "$JMC_OPTS" ] ; then
  container_opts+=(-e "JMC_OPTS=$JMC_OPTS")
  bench_opts+=(--env JMC_OPTS)
fi

if [ "$JMC" ] ; then
  bench_opts+=(--jmc "$JMC")
fi

if [ "$JSC" ] ; then
  bench_opts+=(--jsc "$JSC")
fi

# optional first argument container tag
if [[ "$1" != -* ]] ; then
  bench=$1
  shift
else
  bench=latest
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
  err 4 "unexpected container command: $POD"
fi

image="docker.io/zx80/jmc-bench-$POD:$bench"

echo "# container options: ${container_opts[@]}"
echo "# benchmark options: --id=$bench_id ${bench_opts[@]} $@"

# check latest version
$POD pull $image

# start container
exec $POD run --rm --name jmcbench_$bench_id \
  -v .:/workspace \
  -e WORKDIR="$WORKDIR" \
  -e POD="$POD" \
  "${container_opts[@]}" \
    "$image" \
      --id=$bench_id "${bench_opts[@]}" "$@" > $bench_id.output 2>&1
