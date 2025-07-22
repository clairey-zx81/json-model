# JSON Model Docker

This ubuntu-based docker provides the `jmc` (JSON Model Compiler) command.
It allows to preprocess, compile or export models through the `jmc` shell
script.

## Build

```sh
docker build -t jmc -f Dockerfile .
```

## Raw Run

```sh
docker run --user $UID:$GID -v .:/workspace --rm -it jmc …
```

## Convenient `jmc` Wrapper

Create a `jmc` executable file:

```sh
#! /bin/bash
#
# run jmc command in docker under current uid/gid
#
docker run --user $UID:$GID -v .:/workspace --rm -it jmc "$@"
```

:warning: Only run with relative downward path under the current directory
so that files are found through the virtual mount inside the docker:

```sh
jmc -o geo.out ./geo.model.json             # OK
jmc -o geo.out /home/calvin/geo.model.json  # KO, /home/calvin does not exist there
```

:warning: When generating files, beware that dynamic libraries and other runtime
dependencies must be available in the host to run it.
