SHELL   = /bin/bash
.ONESHELL:

BRANCH  = $(shell git branch --show-current)

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = $(BRANCH)
endif

.PHONY: clean
clean:
	$(RM) .docker-build.*

#
# DOCKER
#
.PHONY: docker.push
docker.push: docker.tag
	docker push -a zx80/jmc-bench

.PHONY: docker.tag
docker.tag: .docker-build.$(BRANCH)
	docker tag jmc-bench zx80/jmc-bench:$(TAG)
	docker tag jmc-bench zx80/jmc-bench:$$(JMC=$(TAG) ./jmc --version)
	docker tag jmc-bench zx80/jmc-bench:$$(git rev-parse --short HEAD)

.PHONY: docker.build
docker.build: .docker-build.$(BRANCH)

.docker-build.$(BRANCH):
	docker build -t jmc-bench -f Dockerfile .
	touch $@
