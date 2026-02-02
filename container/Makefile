#
# Convenient Makefile
#

SHELL   = /bin/bash
.ONESHELL:

# POD = podman
POD = docker
ZX80    = docker.io/zx80

# settings, build for current branch
BRANCH  = $(shell git branch --show-current)
GITVERS = $(shell git rev-parse --short=8 HEAD)
VERSION = $(shell ./jmc --version)

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = test
endif

# for jmc wrapper
export JMC = $(BRANCH)

#
# CLEAN
#
.PHONY: clean
clean:
	$(RM) .build

.PHONY: pod.clean
pod.clean: clean
	$(POD) image prune -f
	$(POD) container prune -f
	$(POD) image rm -f $$($(POD) image ls | grep '^<none>' | tr -s " " " " | cut -d' ' -f 3) jmc
	$(POD) buildx prune -f

.PHONY: pod.cleaner
pod.cleaner:
	$(POD) image rm -f $$($(POD) image ls | grep ^zx80/jmc | tr -s " " " " | cut -d' ' -f 3)

#
# POD (docker ou podman)
#
NOCACHE = --no-cache
JMC     = $(BRANCH)
JSU     = main

.PHONY: pod.build
pod.build: .build

.build: Containerfile jmc
	$(POD) build $(NOCACHE) --build-arg JMC=$(JMC) --build-arg JSU=$(JSU) \
	    -t jmc -f Containerfile . && touch $@

.PHONY: pod.run
pod.run: .build
	@echo $(POD) run --user $$UID:$$GID -v .:/workspace -it --rm --entrypoint /bin/bash jmc

.PHONY: pod.status
pod.status:
	# $(POD) volume ls
	$(POD) system df
	$(POD) container ps -a
	$(POD) image ls -a

.PHONY: versions
versions:
	@ \
	echo " - tag: $(TAG)"; \
	echo " - branch: $(BRANCH)"; \
	echo " - gitvers: $(GITVERS)"; \
	echo " - version: $(VERSION)"

.PHONY: pod.tag
pod.tag: .build
	export POD=$(POD)
	$(POD) tag jmc $(ZX80)/jmc:$(TAG)
	$(POD) tag jmc $(ZX80)/jmc:$(BRANCH)
	$(POD) tag jmc $(ZX80)/jmc:$(GITVERS)
	$(POD) tag jmc $(ZX80)/jmc:$$(JMC=$(BRANCH) ./jmc --version)

.PHONY: pod.push
pod.push: pod.tag
	# if needed: docker login
	$(POD) push -a $(ZX80)/jmc
