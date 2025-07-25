# JSON Model How To …

## How to install the JSON Model Compiler ?

The `jmc` command can be install in a Python virtual environment from
[PyPI](https://pypi.org/project/json-model-compiler/) or from
[sources](https://github.com/clairey-zx81/json-model):

1. PyPI venv:

   ```sh
   python -m venv venv
   source venv/bin/activate
   pip install json-model-compiler
   ```

2. Source venv:

   ```sh
   python -m venv venv
   source venv/bin/activate
   pip install git+https://github.com/clairey-zx81/json-model.git
   ```

3. Docker install the [image](https://hub.docker.com/r/zx80/jmc) and its
   [convenient wrapper](https://github.com/clairey-zx81/json-model/blob/main/docker/jmc):

   ```
   docker pull zx80/jmc
   curl -o ./jmc https://raw.githubusercontent.com/clairey-zx81/json-model/refs/heads/main/docker/jmc
   chmod a+rx ./jmc
   ```

## How to use JSON Model in my _Python_ project?

## How to use JSON Model in my _JavaScript_ project?

## How to use JSON Model in my _Postgres_ database?

Assuming that the `jmc` command is available:

1. install the `json_model` Postgres extension, from source _or_
   from [pgxn](https://pgxn.org/dist/json_model/):

   ```sh
   sudo make -C json_model/runtime install
   sudo pgxn install json_model
   ```

2. compile a model to PL/pgSQL:

   ```sh
   jmc -o stuff.sql Stuff.model.sql
   ```

3. load the generated functions into your `stuff` database:

   ```sh
   psql -f stuff.sql stuff
   ```

4. check the root model (empty name) against a `JSONB` value:

   ```sql
   SELECT check_model(JSONB '3.14', '', NULL);  # TRUE or FALSE…
   ```

## How to … ?

