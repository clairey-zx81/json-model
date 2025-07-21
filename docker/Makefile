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

.PHONY: cleaner.docker
cleaner.docker: clean
	docker image prune -f
	docker container prune -f
	docker image rm -f $$(docker image ls | grep '^<none>' | tr -s " " " " | cut -d' ' -f 3) jmc
	docker buildx prune -f

#
# DOCKER
#
.PHONY: docker.build
docker.build: .build

.build: Dockerfile ./in_docker_jmc.sh
	docker build -t zx80/jmc -f Dockerfile . && touch $@

.PHONY: docker.run
docker.run: .build
	@echo docker run -v .:/workspace -it --rm --entrypoint /bin/bash zx80/jmc

.PHONY: docker.status
docker.status:
	# docker volume ls
	docker system df
	docker container ps -a
	docker image ls -a
