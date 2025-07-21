#! /bin/bash

docker run -v .:/workspace --rm -it zx80/jmc $UID "$@"
