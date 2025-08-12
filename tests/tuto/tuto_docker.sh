#! /bin/bash
#
# JSON Model Tutorial inside Docker
#

docker image inspect zx80/jmc > /dev/null 2>&1 || docker pull zx80/jmc
docker run --name awesome_jmc --user $UID:$GID --rm -v .:/app/workspace -it --entrypoint ./tuto.sh zx80/jmc
