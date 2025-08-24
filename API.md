# JSON Model APIs

Each JSON Model compiler language target presents a similar API to check whether
a JSON value validates against a model.

## APIs General Behavior

All generated functions, whatever the target language, are prefixed with `check_model`.
The prefix may be changed with compiler option `--entry`.
When appropriate, compiler option `--package` allows to generate a module inside
a particular namespace for the language.
Most language API have a initialization and cleanup function for managing internal data structures.

The following illustrations assume that the `jmc` compiler is available and a `Person.model.json`
file containing this model:

```json
{
  "#": "Model for a person",
  "$": {
    "Name": "/^\\w+([-' ]\\w+)*$/",
    "Person": {
      "name": "$Name",
      "birth": "$DATE",
      "?friends": [ "$Name" ]
    }
  },
  "@": "$Person"
}
```

## Python Static API

Model compilation to Python generates either a module or a python script,
which is the same as the module plus an added `main`.

### Functions

This generated module exposes 4 useful functions:

- `check_model_init()`: initialize internal model checking data structures,
  must be called **before** invoking `check_model`.
- `check_model(value, model, report) -> bool`:
  - check JSON _value_ (eg loaded with the `json` module) against model named _model_.
  - append rejection information to _report_, use _None_ for skipping reporting.
- `check_model_fun(model) -> CheckFun`:
  - return the lower level function to check the model named _model_.
  - its signature is `fun(value, path, report) -> bool`:
    the second argument is used for keeping track of the JSON path when walking through _value_;
    use _None_ for both path and report to skip reporting;
    use _[]_ for path and `report = []` for gathering the report.
  - the report is a list of tuples with the explanation for each rejections, and an associated path.
- `check_model_free()`: cleanup internal model checking data structures.

The generated functions depend on `json_model.runtime` which is part of the
[`json-model-compiler` Python package](https://pypi.org/project/json-model-compiler/).

### Example

Generate a Python module:

```sh
jmc -o person.py --module Person
```

Then use it from your code:

```python
import person  # adjust depending on where the generated module is stored

person.check_model_init()
print("hobbes is a person:", person.check_model({"name": "Hobbes", "birth": "2020-07-29"}))
person.check_model_free()
```

## Python Dynamic API

As the JSON Model compiler is written in Python, it can be invoked directly for generating
a validation function.

### Functions

Currently, two functions are available:

- `model_checker_from_json`: generate a model from a JSON value which must be a valid model.

  This function expects a Python JSON value, eg loaded with `json` module, as a first parameter.
- `model_checker_from_url`: generate a model from a JSON value loaded from a URL.

  This function expects a URL as a first parameter, which should dowload a JSON model possibly
  as JSON or YAML.

The following named parameters are available to both functions:

- `auto`: boolean, whether to automatically map url to local path, default is _False_;
  this feature is mostly for testing.
- `debug`: integer, debug level, default is _0_ for no debug.
- `resolver`: instance of Resolver class to load models from URLs.
- `loose_int`: boolean, whether integers a loose, eg `1.0` can be considered an int.
- `loose_float`: boolean, whether floats are loose, eg `42` can be considered a float.

To create a custom `Resolver` instance, use `json_model.resolver.Resolver` with the following arguments:

- `cache_dir`: string, where to store downloaded models, default is `$HOME/cache/json-model`.
- `maps`: dict, mapping urls to local directories, where to retrieve models, default is empty.
- `allow_duplicates`: boolean, whether to allow duplicated property names in an object.
- `cache_ignore`: boolean, whether not use a cache.

If not provided, a resolver is created based on defaults.

### Example

With the `json-model-compiler` Python package installed:

```python
import json_model as jm

is_person = jm.model_checker_from_url("./Person.model.json")
print("hobbes is a person:", is_person({"name": "Hobbes", "birth": "2020-07-29"}))
```

## JS API

Model compilation to JavaScript generates either a module (`.mjs`) or a node script (`.js`),
which is the same as the module plus an added `main`.

### Functions

This generated module exposes 3 useful functions:

- `check_model_init()`: initialize internal model checking data structures,
  must be called **before** invoking `check_model`.
- `check_model(value, model, report) -> bool`:
  - check JSON _value_ (eg loaded with the `json` module) against model named _model_.
  - append rejection information to _report_, use _null_ for skipping reporting.
- `check_model_free()`: cleanup internal model checking data structures.

The module also contains a `check_model_map` map of model names to check functions:

- its signature is `fun(value, path, report) -> bool`:
  the second argument is used for keeping track of the JSON path when walking through _value_;
  use _null_ for both path and report to skip reporting;
  use _[]_ for path and `report = []` for gathering the report.
- the report is a list of tuples with the explanation for each rejections, and an associated path.

The generated functions depend on
the [`json_model_runtime`](https://www.npmjs.com/package/json_model_runtime) npm package
which must be available in your js environment.

### Example

Generate a JavaScript module:

```sh
jmc --loose -o person.mjs Person
```

Then use it from your code, for instance with `node`:

```js
#! /bin/env node
import { check_model_init, check_model, check_model_free } from "./person.mjs"

check_model_init()
console.log(`hobbes is a person: ${check_model({"name": "Hobbes", "birth": "2020-07-29"}, '', null)}`)
check_model_free()
```

## C API

Model compilation to C generates source code (`.c`), an object file (`.o`) or
an executable (`.out`).

### Functions

This generated code exposes 4 useful functions:

```c
#include <json-model.h>
extern const char *check_model_init(void);
extern bool check_model(const json_t *, const char *, bool *, char **);
extern void check_model_free(void);
extern jm_check_fun_t check_model_map(const char *);
```

- `check_model_init`: initialize internal model checking data structures,
  must be called **before** invoking `check_model`.
  It returns an error string if the initialization failed (eg a bad regex).
- `check_model(value, model, error, msg)`:
  - check JSON _value_ against model named _model_.
  - tells whether there was some error (eg non existing name), and return a string for reporting.
  - if `msg` is _NULL_, there is no reporting.
- `check_model_free`: cleanup internal model checking data structures.
- `check_model_map`: returns the lower-level function to check a `json_t *` value for a model,
   with a `jm_path_t *` and `jm_report_t *` as additional parameters.
   This function returns `NULL` if the model name is unknown.

The generated functions depend on a specific C runtime library,
plus either `cre2` (re2 wrapper for C) or `pcre2` as a regex engine, and
Jansson for managing JSON values, which must be compiled and installed.

### Example

Generate a C object module:

```sh
jmc -o person.o Person
```

Then use it from your code:

```c
// see "json_model/runtime/c/main.c"
```

## PL/pgSQL API

:warning: :construction_worker: :construction:

## Perl API

:warning: :construction_worker: :construction:

## Java API

:warning: :construction_worker: :construction:

## Web API

:warning: :construction_worker: :construction:
