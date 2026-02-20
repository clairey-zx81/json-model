#
# Manage docker/podman images for performance testing and reporting
#

SHELL   = /bin/bash
.ONESHELL:

#
# DOCKER/PODMAN IMAGE MANAGEMENT
#

# names
# docker or podman
POD     = docker
VARIANT = docker
ZX80    = docker.io/zx80

BRANCH  = $(shell git branch --show-current)
VERSION = $(shell grep '^version' ../../pyproject.toml | tr -cd '[0-9.ab]')
GITREV  = $(shell git rev-parse --short HEAD)

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = test
endif

.PHONY: clean
clean:
	$(RM) .*-*-build.*
	$(RM) -rf jsb/ tmp/

#
# CONTAINER
#

.PHONY: push
push: docker.push

.PHONY: docker.push
docker.push: docker.build
	$(MAKE) POD=docker VARIANT=docker tag
	docker push -a $(ZX80)/jmc-bench-docker
	$(MAKE) POD=docker VARIANT=podman tag
	docker push -a $(ZX80)/jmc-bench-podman

# .PHONY: podman.push
# podman.push:
# 	$(MAKE) POD=podman pod.tag
# 	for tag in $(BRANCH) $(TAG) $(VERSION) $(GITREV) ; do
# 	  podman push jmc-bench-$(POD):$$tag $(ZX80)/jmc-bench-$(VARIANT):$$tag
# 	  sleep 1
# 	done

.PHONY: pod.list
pod.list:
	$(POD) image ls

.PHONY: tag
tag: .$(POD)-$(VARIANT)-build.$(BRANCH)
	$(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(TAG)
	$(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(BRANCH)
	if [ "$(BRANCH)" = "main" ] ; then
	  $(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(VERSION)
	  # $(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(GITREV)
	fi
	$(POD) image ls

.PHONY: pod.build
pod.build: docker.build podman.build

.PHONY: build
build: .$(POD)-$(VARIANT)-build.$(BRANCH)

.$(POD)-$(VARIANT)-build.$(BRANCH): $(VARIANT)-file
	$(POD) build -t jmc-bench-$(VARIANT) -f $(VARIANT)-file . && date -Iseconds > $@

.PHONY: docker.build
docker.build:
	$(MAKE) POD=docker VARIANT=docker build
	$(MAKE) POD=docker VARIANT=podman build

.PHONY: podman.build
podman.build:
	$(MAKE) POD=podman VARIANT=podman build

#
# LOCAL SANITY TESTING
#
jsb:
	git clone git@github.com:sourcemeta-research/jsonschema-benchmark.git $@

tmp:
	mkdir $@

run: jsb tmp
	PATH=.:$$PATH
	./run.sh 1000 ./tmp/ all all ./jsb/schemas/ansible-meta
