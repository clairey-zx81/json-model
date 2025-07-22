#! /bin/bash
#
# JSON Model Tutorial inside Docker
#

docker pull zx80/jmc
docker run --user $UID:$GID --rm -v .:/app/workspace -it --entrypoint ./tuto.sh zx80/jmc
