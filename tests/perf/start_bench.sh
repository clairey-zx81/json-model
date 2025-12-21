#! /bin/bash

if [ $1 = "-h" -o $1 = "--help" ] ; then
  cat <<EOF
Standalone command to start the jmc benchmark using docker-in-doocker.

Arguments:
- TAG: (zx80/jmc-bench docker tag, defaults to "latest")
- others: passed to "benchmark.sh"

Environment:
- JMC_OPTS: options for jmc
- JMC: zx80/jmc docker tag
- JSC: ghcr.io/sourcemeta/jsonschema docker tag

Example:

  JMC_OPTS=--no-predef JMC=dev $0 dev -p 8 -l 1000 -r 5

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

docker_opts=(--hostname=$(hostname))
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

if [ "$JMC_OPTS" ] ; then
  docker_opts+=(-e "JMC_OPTS=$JMC_OPTS")
  bench_opts+=(--env JMC_OPTS)
fi

if [ "$JMC" ] ; then
  bench_opts+=(--jmc "$JMC")
fi

if [ "$JSC" ] ; then
  bench_opts+=(--jsc "$JSC")
fi

if [[ "$1" != -* ]] ; then
  bench=$1
  shift
else
  bench=latest
fi

echo "# docker options: ${docker_opts[@]}"
echo "# benchmark options: --id=$bench_id ${bench_opts[@]} $@"

# check latest version
docker pull zx80/jmc-bench:$bench

# run
# -u $(id -u) -g $(id -g) -v /etc/passwd:/etc/passwd:ro -v /etc/group:/etc/group:ro
exec docker run --rm --name jmcbench_$bench_id \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v .:/workspace \
  --user $(id -u):$(id -g) \
  -v /etc/passwd:/etc/passwd:ro \
  -v /etc/group:/etc/group:ro \
  -e WORKDIR="$PWD" \
  "${docker_opts[@]}" \
    zx80/jmc-bench:$bench \
      --id=$bench_id "${bench_opts[@]}" "$@" > $bench_id.output 2>&1
