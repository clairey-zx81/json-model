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
	$(RM) .build.base .build.jmc

.PHONY: pod.clean
pod.clean: clean
	$(POD) system prune -f
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
# consider: --no-cache
JMC.opts  =
BASE.pots =

JMC     = $(BRANCH)
JSU     = $(BRANCH)  # for consistency use same branch as JMC

#
# global commands
#
.PHONY: pod.build
pod.build:
	$(MAKE) .build.base
	$(MAKE) .build.jmc

.PHONY: pod.status
pod.status:
	# $(POD) volume ls
	$(POD) system df
	$(POD) container ps -a
	$(POD) image ls -a

IMG = $(ZX80)/jmc

.PHONY: any.run
any.run:
	@GID=$$(id -g)
	echo $(POD) run --user $$UID:$$GID -v .:/workspace -it --rm --entrypoint /bin/bash $(IMG)

.PHONY: versions
versions:
	@ \
	echo " - tag: $(TAG)"; \
	echo " - branch: $(BRANCH)"; \
	echo " - gitvers: $(GITVERS)"; \
	echo " - version: $(VERSION)"

#
# build
#
.build.base: base.container
	$(POD) build $(BASE.opts) -t jmc-base -f $< . && date -Iseconds > $@
	$(POD) tag jmc-base $(ZX80)/jmc-base:latest
	$(POD) tag jmc-base $(ZX80)/jmc-base:26.04

.build.jmc: jmc.container
	$(POD) build $(JMC.opts) --build-arg JMC=$(JMC) --build-arg JSU=$(JSU) \
	    -t jmc -f $< . && date -Iseconds > $@

.PHONY: base.build
base.build: .build.base

.PHONY: jmc.tag
jmc.tag: .build.jmc
	export POD=$(POD)
	$(POD) tag jmc $(ZX80)/jmc:$(TAG)
	$(POD) tag jmc $(ZX80)/jmc:$(BRANCH)
	$(POD) tag jmc $(ZX80)/jmc:$$(JMC=$(BRANCH) ./jmc --version)

.PHONY: jmc.push
jmc.push: jmc.tag
	# if needed: docker login
	$(POD) push -a $(ZX80)/jmc

.PHONY: base.push
base.push: .build.base
	$(POD) push $(ZX80)/jmc-base:latest
	$(POD) push $(ZX80)/jmc-base:26.04

.PHONY: quick-jmc.push
quick-jmc.push: jmc.tag
	$(POD) push $(ZX80)/jmc:$(BRANCH)
	$(POD) push $(ZX80)/jmc:$(TAG)

#
# run
#

.PHONY: jmc.run
jmc.run: .build.jmc
	$(MAKE) any.run

.PHONY: base.run
base.run: .build.base
	$(MAKE) IMG=$(ZX80)/jmc-base any.run
