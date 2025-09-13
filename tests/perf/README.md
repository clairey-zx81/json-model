# Build and run JSON Model compiler benchmarking artifact

```sh
# in tests/perf
docker build -t jmc-bench -f Dockerfile .
# in an empty directory
docker run --rm --name imperial_jmcbench -e WORKDIR=$PWD -v /var/run/docker.sock:/var/run/docker.sock -v .:/workspace jmc-bench:latest 
```
