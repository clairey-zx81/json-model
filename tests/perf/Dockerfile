#
# Example run:
#   docker run --rm --name imperial_jmcbench \
#     -v /var/run/docker.sock:/var/run/docker.sock \
#     -e WORKDIR=$PWD -v .:/workspace \
#       zx80/jmc-bench:latest -p 12 -l 10000
#
FROM alpinelinux/docker-cli:latest
LABEL description="JSON Model compiler benchmarking artifact"
RUN apk add git bash bash-completion sqlite jq
RUN mkdir /app /workspace
COPY . /app
ENV PATH=$PATH:/app
WORKDIR /workspace
ENTRYPOINT ["/app/benchmark.sh" ]
