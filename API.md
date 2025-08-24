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

Example:

- generate a Python module:

  ```sh
  jmc -o person.py --module Person
  ```

- then use it from your code:

  ```python
  import person  # adjust depending on where the generated module is stored

  person.check_model_init()
  print("hobbes is a person:", person.check_model({"name": "Hobbes", "birth": "2020-07-29"}))
  person.check_model_free()
  ```

## Python Dynamic API

:warning: :construction_worker: :construction:

## JS API

:warning: :construction_worker: :construction:

## C API

:warning: :construction_worker: :construction:

## PL/pgSQL API

:warning: :construction_worker: :construction:

## Perl API

:warning: :construction_worker: :construction:

## Java API

:warning: :construction_worker: :construction:

## Web API

:warning: :construction_worker: :construction:
