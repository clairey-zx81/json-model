FROM alpinelinux/docker-cli:latest
LABEL description="JSON Model compiler benchmarking artifact"
RUN apk add git bash bash-completion sqlite jq
RUN mkdir /app /workspace
COPY . /app
ENV PATH=$PATH:/app
WORKDIR /workspace
ENTRYPOINT ["/app/benchmark.sh" ]
