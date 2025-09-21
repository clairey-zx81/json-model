#
# Convenient Makefile
#

SHELL   = /bin/bash
.ONESHELL:

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

.PHONY: docker.clean
docker.clean: clean
	docker image prune -f
	docker container prune -f
	docker image rm -f $$(docker image ls | grep '^<none>' | tr -s " " " " | cut -d' ' -f 3) jmc
	docker buildx prune -f

.PHONY: docker.cleaner
docker.cleaner:
	docker image rm -f $$(docker image ls | grep ^zx80/jmc | tr -s " " " " | cut -d' ' -f 3)

#
# DOCKER
#
NOCACHE = --no-cache
JMC     = $(BRANCH)
JSU     = main

.PHONY: docker.build
docker.build: .build

.build: Dockerfile jmc
	docker build $(NOCACHE) --build-arg JMC=$(JMC) --build-arg JSU=$(JSU) \
	    -t jmc -f Dockerfile . && touch $@

.PHONY: docker.run
docker.run: .build
	@echo docker run --user $$UID:$$GID -v .:/workspace -it --rm --entrypoint /bin/bash jmc

.PHONY: docker.status
docker.status:
	# docker volume ls
	docker system df
	docker container ps -a
	docker image ls -a

.PHONY: versions
versions:
	@ \
	echo " - tag: $(TAG)"; \
	echo " - branch: $(BRANCH)"; \
	echo " - gitvers: $(GITVERS)"; \
	echo " - version: $(VERSION)"

.PHONY: docker.tag
docker.tag: .build
	docker tag jmc zx80/jmc:$(TAG)
	docker tag jmc zx80/jmc:$(BRANCH)
	docker tag jmc zx80/jmc:$(GITVERS)
	docker tag jmc zx80/jmc:$$(JMC=$(BRANCH) ./jmc --version)

.PHONY: docker.push
docker.push: docker.tag
	# if needed: docker login
	docker push -a zx80/jmc
