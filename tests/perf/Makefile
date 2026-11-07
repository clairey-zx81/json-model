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
VERSION = $(shell jmc --version)
GITREV  = $(shell git rev-parse --short HEAD)

ifeq ($(BRANCH), main)
TAG = latest
else
TAG = test
endif

.PHONY: clean
clean:
	$(RM) .*.build .*.tag .version .{ajv,corvus}.* {ajv,corvus}/.jmc_version
	$(RM) -rf jsb/ tmp/

#
# JMC BENCH CONTAINER
#

.PHONY: docker-docker.push
docker-docker.push: docker-docker.tag
	# docker push -a $(ZX80)/jmc-bench-docker
	docker push $(ZX80)/jmc-bench-docker:$(BRANCH)
	docker push $(ZX80)/jmc-bench-docker:$(TAG)
	[ "$(BRANCH)" = "main" ] && docker push $(ZX80)/jmc-bench-docker:$(VERSION)

.PHONY: docker-podman.push
docker-podman.push: docker-podman.tag
	# docker push -a $(ZX80)/jmc-bench-podman
	docker push $(ZX80)/jmc-bench-podman:$(BRANCH)
	docker push $(ZX80)/jmc-bench-podman:$(TAG)
	[ "$(BRANCH)" = "main" ] && docker push $(ZX80)/jmc-bench-podman:$(VERSION)

.PHONY: pod.list
pod.list:
	$(POD) image ls

.PHONY: push
push: docker-docker.push

.PHONY: tag
tag: .$(POD)-$(VARIANT)-$(BRANCH).tag

.PHONY: build
build: .$(POD)-$(VARIANT)-$(BRANCH).build

# actual building and tagging
POD.opts    = --no-cache

.$(POD)-$(VARIANT)-$(BRANCH).build: perf.$(VARIANT)
	jmc --version > .version || exit 1
	$(POD) build $(POD.opts) -t jmc-bench-$(VARIANT) -f perf.$(VARIANT) . && date -Iseconds > $@

.$(POD)-$(VARIANT)-$(BRANCH).tag: .$(POD)-$(VARIANT)-$(BRANCH).build
	$(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(TAG)
	$(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(BRANCH)
	$(POD) tag jmc-bench-$(VARIANT) $(ZX80)/jmc-bench-$(VARIANT):$(VERSION)
	touch $@

.PHONY: pod.build
pod.build: docker-docker.build docker-podman.build podman-podman.build

.PHONY: docker-docker.build
docker-docker.build:
	$(MAKE) POD=docker VARIANT=docker build

.PHONY: docker-docker.tag
docker-docker.tag:
	$(MAKE) POD=docker VARIANT=docker tag

# does this one make sense?
.PHONY: docker-podman.build
docker-podman.build:
	$(MAKE) POD=docker VARIANT=podman build

.PHONY: docker-podman.tag
docker-podman.tag:
	$(MAKE) POD=docker VARIANT=podman tag

.PHONY: podman-podman.build
podman-podman.build:
	$(MAKE) POD=podman VARIANT=podman build

.PHONY: podman-podman.tag
podman-podman.tag:
	$(MAKE) POD=podman VARIANT=podman tag

.PHONY: current
current:
	$(POD) run --rm $(ZX80)/jmc-bench-$(VARIANT):$(TAG) --version

#
# EXTERNAL TOOLS
#
# SUB = corvus
# SUB = ajv

.$(SUB).build: $(SUB)/$(SUB).docker $(SUB)/wrapper.sh
	echo $(VERSION) > $(SUB)/.jmc_version
	$(POD) build --no-cache -t $(SUB)-cli:latest -f $(SUB)/$(SUB).docker $(SUB)/. && \
	  $(POD) tag $(SUB)-cli:latest $(ZX80)/$(SUB)-cli:latest && \
	  touch $@

.$(SUB).push: .$(SUB).build
	$(POD) push $(ZX80)/$(SUB)-cli:latest
	touch $@

ajv.%:
	$(MAKE) SUB=ajv .$@

corvus.%:
	$(MAKE) SUB=corvus .$@

%.version:
	docker run --rm $*-cli:latest --version

# additional dependencies
.corvus.build: corvus/Program.cs corvus/CorvusBench.csproj

#
# LOCAL SANITY TESTING
#
jsb:
	git clone git@github.com:sourcemeta-research/jsonschema-benchmark.git $@

tmp:
	mkdir $@

TASK    = all
TARGET  = jmc-c
RUN.d   = $(wildcard ./jsb/schemas/*)

.PHONY: run.params
run.params: jsb
	@# show run parameters
	echo "# JMC=$(JMC)"
	echo "# TASK=$(TASK)"
	echo "# TARGET=$(TARGET)"
	echo "# RUN.d=$(RUN.d)"

.PHONY: run.clean
run.clean:
	$(RM) -r tmp

.PHONY: run
run: jsb tmp
	# test setup
	dir=./tmp/$$(date +%Y%m%d%H%M%S)
	mkdir $$dir
	echo "# running in $$dir"
	$(MAKE) run.params
	# use local jmc wrapper
	export PATH=.:$$PATH
	./run.sh 1000 $$dir/ $(TASK) $(TARGET) $(RUN.d) > $$dir/run.output 2>&1
	# extract data
	./run-to-csv.sh $$dir/*.out > $$dir/perf.csv
	./res-to-csv.sh $$dir/*.out > $$dir/result.csv
	./compile-to-csv.sh $$dir/*_compile.csv > $$dir/compile.csv
