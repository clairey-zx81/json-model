# Build and run JSON Model compiler benchmarking artifact

## Start Script

The `start_bench.sh` starts a benchmark into an empty subdirectory.

Arguments:

- TAG: `zx80/jmc-bench` docker tag, defaults to `latest`
- ...: all others arguments passed to `benchmark.sh`

Environment:

- `JMC_OPTS`: options for jmc, for instance `--no-predef`
- `JMC`: `zx80/jmc` docker tag
- `JSC`: `ghcr.io/sourcemeta/jsonschema` docker tag

Example usage:

```bash
JMC=dev JMC_OPTS=--no-predef \
  nohup \
    ./start_bench.sh dev -p 20 -l 1000 -r 5 --cap-py &
```

## DooD

```sh
# in tests/perf
docker build -t jmc-bench -f Dockerfile .
docker tag jmc-bench zx80/jmc-bench
docker push zx80/jmc-bench
# in an empty directory
# possibly -e JMC_OPTS=$JMC_OPTS ## --env=JMC_OPTS
docker run --rm --name imperial_jmcbench -v /var/run/docker.sock:/var/run/docker.sock \
    -e WORKDIR=$PWD -v .:/workspace zx80/jmc-bench:latest -p 20 -l 10000 -r 5 --cap-py
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
