# JSON Model Docker

This ubuntu-based [docker image](https://hub.docker.com/r/zx80/jmc)
provides the `jmc` (JSON Model Compiler) command.
It allows to preprocess, compile, export and execute models through
the `jmc` convenient shell wrapper.

## Pull or Build

```sh
docker pull zx80/jmc
docker build -t zx80/jmc .
```

## Convenient `jmc` Wrapper

Copy this [script](https://raw.githubusercontent.com/clairey-zx81/json-model/refs/heads/main/docker/jmc)
somewhere in your path with executable permissions:

```sh
curl -o ./jmc https://raw.githubusercontent.com/clairey-zx81/json-model/refs/heads/main/docker/jmc
chmod a+rx ./jmc
```

:warning: Review the script before executing it!

The wrapper script allows 4 modes:

- :cherries: **compiler**: execute the `jmc` command inside the current directory:

  ```sh
  ./jmc model.json hobbes.json                  # PASS or FAIL…
  ./jmc -o model.out model.json                 # generate executable from C
  ./jmc --loose-number -o model.js model.json   # generate javascript script
  ./jmc -o model.py model.json                  # generate python script
  ./jmc -o model.pl model.json                  # generate perl script
  ```

  :warning: Only run with relative downward path under the current directory
  so that files are found through the virtual mount inside the docker:

  :warning: note that generated executable and scripts require dependencies (dynamic libraries,
  Python, JS or Perl packages…) that may or may not be available on the host.

  :+1: invoking the compilation is also triggered with `run`: `./jmc run model.json hobbes.json`

- :arrow_forward: **execution**: execute generated code in the docker environment,
  where dependencies are readily available:

  ```sh
  ./jmc exec ./model.out hobbes.json
  ./jmc exec ./model.js hobbes.json
  ./jmc exec ./model.py hobbes.json
  ./jmc exec ./model.pl hobbes.json
  ```

  :warning: you must use an **explicit** relative path to the executable.

  :+1: the generated executable have various options available for performance testing.
  Try `-T 1000` to repeat validation _1000_ times on a value and collect average and standard
  deviation µs. Try `--help` to check for available options.

- :shell: **shell**: enjoy a shell with `jmc` and `jsu-*` commands available in the local directory
  under your current id.

  ```sh
  ./jmc shell
  jsu-model schema.json > model.json
  jmc -o model.out model.json
  ./model.out -T 1000 hobbes.json
  # ...
  exit
  ```

- :computer: **root**: start a shell in the docker with root permissions.

## Direct Docker Commands

The `jmc` wrapper runs the following commands:

- **compiler** (default entry point):

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it jmc -o model.out model.json
  ```

- **execution**:

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it --entrypoint ./model.out jmc hobbes.json
  ```

- **shell**:

  ```sh
  docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it --entrypoint /bin/bash jmc
  jmc -o model.out model.json
  ./model.out hobbes.json
  ```
