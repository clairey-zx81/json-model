# JSON Model Docker

This ubuntu-based docker provides the `jmc` (JSON Model Compiler) command.
It allows to preprocess, compile, export and execute models through
the `jmc` convenient shell wrapper.

## Pull or Build

```sh
docker pull zx80/jmc
docker build -t zx80/jmc .
```

## Convenient `jmc` Wrapper

Copy this [`jmc` executable script](./jmc) somewhere in your path.
The wrapper script allows 3 modes:

- compiler run: execute the `jmc` command inside the current directory:

  ```sh
  ./jmc model.json hobbes.json                  # PASS or FAIL…
  ./jmc -o model.out model.json                 # generate executable from C
  ./jmc --loose-number -o model.js model.json   # generate javascript script
  ./jmc -o model.py model.json                  # generate python script
  ```

- execution run: execute generated code in the docker environment, with dependencies:

  ```sh
  ./jmc exec ./model.out -T 1000 hobbes.json
  ./jmc exec ./model.js -T 1000 hobbes.json
  ./jmc exec ./model.py -T 1000 hobbes.json
  ```

  :warning: you must use an **explicit** relative path to the executable.

- shell run: enjoy a shell with `jmc` and `jsu-*` commands available in the local directory:

  ```sh
  ./jmc shell
  ```

:warning: Only run with relative downward path under the current directory
so that files are found through the virtual mount inside the docker:

```sh
./jmc -o geo.out ./geo.model.json             # OK
./jmc -o geo.out /home/calvin/geo.model.json  # KO, /home/calvin does not exist there
```

:warning: When generating files, beware that dynamic libraries and other runtime
dependencies must be available in the host to run it.
Alternatively, these libraries are available inside the docker image.

## Direct Docker Commands

The `jmc` wrapper runs the following commands:

- compiler run (default entry point)

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it jmc -o model.out model.json
  ```

- execution run

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it ./model.out hobbes.json
  ```

- shell run

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it --entrypoint /bin/bash jmc
  jmc -o model.out model.json
  ./model.out hobbes.json
  ```
