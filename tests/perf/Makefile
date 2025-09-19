SHELL   = /bin/bash
.ONESHELL:

.PHONY: push
push: build
	docker push -a zx80/jmc-bench

TAG = latest

.PHONY: build
build:
	docker build -t jmc-bench -f Dockerfile .
	docker tag jmc-bench zx80/jmc-bench:$(TAG)
	docker tag jmc-bench zx80/jmc-bench:$$(jmc --version)
	docker tag jmc-bench zx80/jmc-bench:$$(git rev-parse --short HEAD)
