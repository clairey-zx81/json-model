#
# Convenient Makefile
#

SHELL   = /bin/bash
.ONESHELL:

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
.PHONY: docker.build
docker.build: .build
.build: Dockerfile
	docker build $(NOCACHE) -t jmc -f Dockerfile . && touch $@

.PHONY: docker.run
docker.run: .build
	@echo docker run --user $$UID:$$GID -v .:/workspace -it --rm --entrypoint /bin/bash jmc

.PHONY: docker.status
docker.status:
	# docker volume ls
	docker system df
	docker container ps -a
	docker image ls -a

docker.tag: .build
	# tag latest
	docker tag jmc zx80/jmc:latest
	# tag package version
	gitvers=$$(git rev-parse --short=8 HEAD)
	docker tag jmc zx80/jmc:$$gitvers
	# git commit
	version=$$(./jmc --version| tr -d '\012\015')
	docker tag jmc zx80/jmc:$$version

.PHONY: docker.push
docker.push: docker.tag
	# if needed: docker login
	docker push zx80/jmc:latest
	version=$$(./jmc --version| tr -d '\012\015')
	docker push zx80/jmc:$$version
