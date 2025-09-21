SHELL   = /bin/bash
.ONESHELL:

.PHONY: push
push: build
	docker push -a zx80/jmc-bench

BRANCH  = $(shell git branch --show-current)

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = $(BRANCH)
endif

.PHONY: build
build:
	docker build -t jmc-bench -f Dockerfile .
	docker tag jmc-bench zx80/jmc-bench:$(TAG)
	docker tag jmc-bench zx80/jmc-bench:$$(JMC=$(TAG) ./jmc --version)
	docker tag jmc-bench zx80/jmc-bench:$$(git rev-parse --short HEAD)
