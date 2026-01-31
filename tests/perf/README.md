# Build and run JSON Model compiler benchmarking artifact

## Start Script

The `start_bench.sh` starts a benchmark into an empty subdirectory.

Arguments:

- `TAG`: `docker.io/zx80/jmc-bench-<container>` container tag, defaults to `latest`
- ...: all others arguments or options are passed to `benchmark.sh`

Environment:

- `POD`: "docker" or "podman" container command
- `JMC_OPTS`: options for jmc, for instance `--no-predef`
- `JMC`: `docker.io/zx80/jmc` container tag, default is latest
- `JSC`: `ghcr.io/sourcemeta/jsonschema` container tag, default is latest

Example usage:

```bash
JMC=dev JMC_OPTS=--no-predef \
  nohup \
    ./start_bench.sh dev -p 20 -l 1000 -r 5 --cap-py &
```

## DooD

```sh
pod=docker
# in tests/perf
$pod build -t jmc-bench-docker -f docker-file .
$pod tag jmc-bench-docker docker.io/zx80/jmc-bench-docker
$pod push docker.io/zx80/jmc-bench-docker
# in an empty directory
# possibly -e JMC_OPTS=$JMC_OPTS ## --env=JMC_OPTS
$pod run --rm --name imperial_jmcbench -v /var/run/docker.sock:/var/run/docker.sock \
    -e WORKDIR=$PWD -v .:/workspace docker.io/zx80/jmc-bench-docker:latest \
    -p 20 -l 10000 -r 5 --cap-py
```

## DinD

TODO make it work

```sh
# TODO simplify
docker network create dind-nw
docker run --privileged --name docker-daemon \
  -d --network dind-nw --network-alias docker \
  -e DOCKER_TLS_CERTDIR=/certs \
  -v daemon-certs-ca:/certs/ca \
  -v daemon-certs-client:/certs/client \
  docker:dind
docker run --rm -ti --network dind-nw \
  -e DOCKER_TLS_CERTDIR=/certs \
  -v daemon-certs-client:/certs/client:ro \
  docker sh
```
