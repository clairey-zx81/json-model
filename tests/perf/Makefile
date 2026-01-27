SHELL   = /bin/bash
.ONESHELL:

BRANCH  = $(shell git branch --show-current)
VERSION = $(shell grep '^version' ../../pyproject.toml | tr -cd '[0-9.ab]')

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = $(BRANCH)
endif

.PHONY: clean
clean:
	$(RM) .docker-build.* .podman-build.*

#
# CONTAINER
#

# POD   = podman
POD = docker
ZX80    = docker.io/zx80

.PHONY: pod.push
pod.push: pod.tag
	$(POD) push -a $(ZX80)/jmc-bench

.PHONY: pod.tag
pod.tag: .$(POD)-build.$(BRANCH)
	$(POD) tag jmc-bench $(ZX80)/jmc-bench:$(TAG)
	$(POD) tag jmc-bench $(ZX80)/jmc-bench:$(VERSION)
	$(POD) tag jmc-bench $(ZX80)/jmc-bench:$$(git rev-parse --short HEAD)

.PHONY: pod.build
pod.build: .$(POD)-build.$(BRANCH)

.$(POD)-build.$(BRANCH):
	$(POD) build -t jmc-bench -f Containerfile .
	touch $@
