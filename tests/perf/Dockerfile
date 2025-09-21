#
# Example image run, try --help to see available options:
#
# docker run --rm --name imperial_jmcbench \
#   -v /var/run/docker.sock:/var/run/docker.sock \
#   -e WORKDIR=$PWD -v .:/workspace \
#     zx80/jmc-bench:latest -p 12 -l 10000 --cap-py
#
FROM alpinelinux/docker-cli:latest
LABEL description="JSON Model compiler benchmarking artifact"
RUN apk add git bash bash-completion sqlite jq lscpu
RUN mkdir /app /workspace
COPY . /app
ENV PATH=$PATH:/app
WORKDIR /workspace
ENTRYPOINT ["/app/benchmark.sh" ]
