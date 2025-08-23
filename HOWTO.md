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

1. Add `JSON::JsonModel.pm` file to you Perl path (eg `PERLLIB` environment variable).

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
   use Model;          # your generated perl module
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

If you load a JSON file using specific Java classes (aka binding), your _do not_ really need
a model for checking your JSON: the JSON parser should check type constraints while creating
your class instances.

However, if you want to load a generic JSON file without having corresponding Java classes,
you can use JSON model for validating its contents.

1. add the [JSON Model Java runtime](https://central.sonatype.com/artifact/org.json-model/json-model),
   as a dependency to your project, for instance for Apache Maven:

   ```xml
   <dependency>
     <groupId>org.json-model</groupId>
     <artifactId>json-model</artifactId>
     <version>2.0b5</version>
   </dependency>
   ```

2. choose a Java JSON library! Currently 3 libraries are supported:

   - [GSON](https://central.sonatype.com/artifact/com.google.code.gson/gson)
   - [Jackson](https://central.sonatype.com/artifact/com.fasterxml.jackson.core/jackson-core)
   - [JSONP](https://central.sonatype.com/artifact/jakarta.json/jakarta.json-api)
     with an implementation such as
     [Johnzon](https://central.sonatype.com/artifact/org.apache.johnzon/johnzon) or
     [Joy](https://central.sonatype.com/artifact/org.leadpony.joy/joy).

3. generate the Java JSON validation class for your model, and put it somewhere in your project
   so that it is built with your source code:

   ```sh
   jmc -o StuffChecker.java Stuff
   ```

   Option `--package PACKAGE` allow to generate the checker for a particular package.

4. initialize the runtime:

   ```java
   import json_model.GSON;  // or Jackson or JSONP
   import json_model.ModelChecker;

   // where and when you need it
   ModelChecker checker = new StuffChecker();
   checker.init(new GSON())
   ```


5. call the checker on a `value` loaded by the library from some source, to check whether
   it conforms to `model` (the name of the model, empty string for the root model).

   ```java
   import json_model.Report;

   Report rep = new Report();  // or null if not needed
   boolean ok = checker.check(value, model, rep);
   // consult report for some hint on rejections
   ```

6. Sip some coffee!

## … get an Answer?

Feel free to [open an issue](https://github.com/clairey-zx81/json-model/issues) for any question.
