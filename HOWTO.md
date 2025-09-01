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
   jmc --man
   ```

2. Source venv:

   ```sh
   python -m venv venv
   source venv/bin/activate
   pip install git+https://github.com/clairey-zx81/json-model.git
   jmc --version
   jmc --man
   ```

3. Docker install the [image](https://hub.docker.com/r/zx80/jmc) and its
   [convenient wrapper](https://github.com/clairey-zx81/json-model/blob/main/docker/jmc):

   ```sh
   docker pull zx80/jmc
   curl -o ./jmc https://raw.githubusercontent.com/clairey-zx81/json-model/refs/heads/main/docker/jmc
   chmod a+rx ./jmc
   ./jmc --version
   ./jmc --man
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

See [Python Static API](API#python-static-api) for further details.

## … use JSON Model in my _Python_ code (dynamic)?

As the compiler is written in Python, in can be invoked directly from Python code
and the generated validation function can be used from there:

1. [Install](#install-the-json-model-compiler) the
   [JSON Model Compiler](https://pypi.org/project/json-model-compiler/) Python package.

2. Generate and use model checker functions in
   [`howto_python_dyn.py`](https://github.com/clairey-zx81/json-model/blob/main/tests/tuto/howto_python_dyn.py):

   ```python
   #! /usr/bin/env python
   import json_model as jm

   # model and value
   person = { "name": "/^\\w+$/", "born": "$DATE" }
   hobbes = { "name": "Hobbes", "born": "2020-07-29" }

   # direct model
   is_person = jm.model_checker_from_json(person)

   # from a URL
   is_model = jm.model_checker_from_url("https://json-model.org/models/json-model")

   # use model checkers on JSON values
   print("hobbes is a person:", is_person(hobbes))
   print("hobbes is a model:", is_model(hobbes))
   print("person is a person:", is_person(person))
   print("person is a model:", is_model(person))
   ```

3. Enjoy!

   ```sh
   time ./howto_python_dyn.py
   ```
   ```
   hobbes is a person: True
   hobbes is a model: True    # indeed, as a model it only matches itself
   person is a person: False
   person is a model: True

   real    0m0,134s
   ```

   The reported time include compiling the _person_ model and
   JSON Model [meta model](https://json-model.org/models/json-model).

See [Python Dynamic API](API#python-dynamic-api) for further details.

## … use JSON Model in my _JavaScript_ code?

Assuming that the `jmc` command is available:

1. Add the JSON Model JavaScript runtime `json_model_runtime` to your js environment,
   for instance:

   ```sh
   npm install json_model_runtime
   ```

2. Generate a JS script or module:

   ```sh
   jmc --loose -o model.mjs model.json
   jmc --loose -o model.js model.json
   ```

3. Exemple usage for a JS module:

   ```js
   import { check_model_init, check_model, check_model_free } from "./model.mjs"

   function foo() {
     check_model_init()
     hobbes = { name: "Hobbes", birth: "2020-07-29" }
     console.log(`hobbes: ${check_model(hobbes, "", null)}`)
   }
   ```

For a web frontend, it makes sense to add model checks when extracting JSON
data from a `fetch` or `axios` request, and before it is used or stored by
`SWR` or `Redux`.

See [JavaScript API](API#javascript-api) for further details.

## … use JSON Model in my _Perl_ code?

Assuming that the `jmc` command is available:

1. Add the JSON Model Perl runtime `JSON::JsonModel` to your Perl environment,
   for instance by adjusting your `PERLLIB` path or with `cpan`:

   ```sh
   cpan JSON::JsonModel
   ```

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

See [Perl API](API#perl-api) for further details.

## … use JSON Model in my _Postgres_ database?

Assuming that the `jmc` command is available:

1. Install the `json_model` Postgres extension, from source _or_
   from [pgxn](https://pgxn.org/dist/json_model/):

   ```sh
   sudo pgxn install json_model                 # from pgxn
   sudo make -C json_model/runtime/sql install  # manually from sources
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

See [PL/pgSQL API](API#plpgsql-api) for further details about the API.

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

See [Java API](API#java-api) for further details about the API.

## … use JSON Model in my _C_ code?

First, you need to install dependencies, in particular:

- JSON library: Jansson. 
- Regex engine: cre2 (C wrapper for re2) and re2 or pcre2.

You must link the generated object file with your own program and call the generated functions
to check values.

See [C API](API#c-api) for further details about the API.

See
[main source code](https://github.com/clairey-zx81/json-model/blob/main/json_model/runtime/c/main.c)
for a working example involving parameter handling, reading JSON files, and so on.

## … get an Answer?

Feel free to [open an issue](https://github.com/clairey-zx81/json-model/issues) for any question.
