# Build and run JSON Model compiler benchmarking artifact

## DooD

```sh
# in tests/perf
docker build -t jmc-bench -f Dockerfile .
docker tag jmc-bench zx80/jmc-bench
docker push zx80/jmc-bench
# in an empty directory
docker run --rm --name imperial_jmcbench -v /var/run/docker.sock:/var/run/docker.sock \
    -e WORKDIR=$PWD -v .:/workspace zx80/jmc-bench:latest
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
