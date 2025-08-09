# JSON Model How To …

## … install the JSON Model Compiler ?

The `jmc` command can be install in a Python virtual environment from
[PyPI](https://pypi.org/project/json-model-compiler/) or from
[sources](https://github.com/clairey-zx81/json-model):

1. PyPI venv:

   ```sh
   python -m venv venv
   source venv/bin/activate
   pip install json-model-compiler
   jmc --version
   ```

2. Source venv:

   ```sh
   python -m venv venv
   source venv/bin/activate
   pip install git+https://github.com/clairey-zx81/json-model.git
   jmc --version
   ```

3. Docker install the [image](https://hub.docker.com/r/zx80/jmc) and its
   [convenient wrapper](https://github.com/clairey-zx81/json-model/blob/main/docker/jmc):

   ```sh
   docker pull zx80/jmc
   curl -o ./jmc https://raw.githubusercontent.com/clairey-zx81/json-model/refs/heads/main/docker/jmc
   chmod a+rx ./jmc
   ./jmc --version
   ```

## … use JSON Model in my _Python_ code (static)?

Assuming that the `jmc` command is available, which means that both the compiler and
runtime are in your Python environment.

1. Generate a Python script or module:

   ```sh
   jmc -o model.py model.json           # python script, run from shell
   jmc -o Model.py --module model.json  # python module to `import`
   ```

2. Example Python module usage, assuming that the generated `Model.py` is in your Python path:

   ```python
   import Model
   Model.check_model_init()
   hobbes = {"name": "Hobbes", "birth": "2020-07-29"}
   valid = Model.check_model(hobbes, "", None)
   Model.check_model_free()
   ```

## … use JSON Model in my _Python_ code (dynamic)?

:warning: :construction_worker: :construction:

## … use JSON Model in my _JavaScript_ code?

:warning: :construction_worker: :construction:

## … use JSON Model in my _Perl_ code?

Assuming that the `jmc` command is available:

1. Add the generated `JsonModel.pm` file to you Perl path (eg `PERLLIB` environment variable).

2. Generate a Perl script or module:

   ```sh
   jmc -o model.pl model.json   # perl script, run from shell
   jmc -o Model.pm model.json   # perl module to `use`
   ```

3. Example usage for Perl module, assuming that the generated `Model.pm` file
   is in your Perl path:

   ```perl
   #! /usr/bin/perl -w
   use JSON::MaybeXS;
   use Model;          # your pm file
   check_model_init();
   my $value = decode_json('{"hello": "world!"}');
   my $valid = check_model($value, "", undef);
   check_model_free();
   ```

## … use JSON Model in my _Postgres_ database?

Assuming that the `jmc` command is available:

1. Install the `json_model` Postgres extension, from source _or_
   from [pgxn](https://pgxn.org/dist/json_model/):

   ```sh
   sudo make -C json_model/runtime install
   sudo pgxn install json_model
   ```

2. Compile a model to PL/pgSQL:

   ```sh
   jmc -o stuff.sql Stuff.model.sql
   ```

3. Load the generated functions into your `stuff` database:

   ```sh
   psql -f stuff.sql stuff
   ```

4. Check the root model (empty name) against a `JSONB` value:

   ```sql
   SELECT check_model(JSONB '3.14', '', NULL);  # TRUE or FALSE…
   ```

## … use JSON Model in my _Java_ code?

:warning: :construction_worker: :construction:

## … get an Answer?

Feel free to [open an issue](https://github.com/clairey-zx81/json-model/issues) for any question.
