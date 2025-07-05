# JSON Model Tools

JSON Model is a compact and intuitive JSON syntax to describe JSON data structures.

Version 2 is work-in-progress design, implementation and tests.

This implementation is given to the _Public Domain_.

## Tool Installation

Proof-of-concept compiler to test JSON Model is available as Python a command
which can be installed with `pip` directly from GitHub:

```shell
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

## JSON Model Compiler

Command `jmc` options include:

- main operations (default depends on other options, final guess is preprocess):
  - `-P`: preprocess model.
  - `-E`: export model to JSON Schema version draft 2020-12, if possible.
  - `-C`: compile to Python, C or JS.
  - `-U`: dump all models.
  - `-J`: dump json IR.
- `-O`: optimize model: const prop, partial eval, xor to or, flatten…
  (this is the default, `-nO` to disable)
- `-o output`: file output instead of standard
- `-F format`: select `json` or `yaml` for output
- …

For instance, let's consider a JSON model in file `person.model.json`:

```json
{
  "#": "A person with a birth date",
  "name": "/^[a-z]+$/i",
  "born": "$DATE"
}
```

- to _export_ this model as a JSON schema in the YaML format:

  ```sh
  jmc -E -F yaml person.model.json
  ```
  ```yaml
  description: A person with a birth date
  type: object
  properties:
    name:
      type: string
      pattern: (?i)^[a-z]+$
    born:
      type: string
      format: date
  required:
  - name
  - born
  additionalProperties: false
  ```

- to check directly sample JSON values against it (with the Python backend):

  ```sh
  jmc -r person.model.json hobbes.json oops.json
  ```
  ```
  hobbes.json: PASS
  oops.json: FAIL (.: not an expected object [.]; .: missing mandatory prop <born> [.])
  ```

- to actually compile an executable for checking a model (with the C backend),
  and use it for validating values:

  ```sh
  jmc -o ./person.out person.model.json
  ./person.out -r hobbes.json oops.json
  ```
  ```
  hobbes.json: PASS
  oops.json: FAIL (.: not an expected object [.]; .: missing mandatory prop <born> [.])
  ```

  The generated executable allow to collect validation performance figures (average and
  standard deviation) over a loop, with or without reporting:

  ```sh
  ./person.out -r -T 100000 hobbes.json
  ```
  ```
  hobbes.json.[0] nop PASS 0.056 ± 0.423 µs/check (0.174)
  hobbes.json.[0] rep PASS 0.071 ± 0.443 µs/check (0.174)
  hobbes.json: PASS
  ```

## JSON Model Python API

The package provides functions to create and check models from Python:

```python
import json_model as jm

# direct model definition with 2 mandatory properties
person_model: jm.Jsonable = {
  "name": "/^[a-z]+$/i",
  "born": "$DATE"
}

# create a dynamically compiled checker function for the model
checker = jm.model_checker_from_json(person_model)

# check valid data
good_person = { "name": "Hobbes", "born": "2020-07-29" }
print(good_person, "->", checker(good_person))

# check invalid data
bad_person = { "name": "Oops" }
print(bad_person, "->", checker(bad_person))

# collect reasons
reasons: jm.Report = []
assert not checker(bad_person, "", reasons)
print("reasons:", reasons)
```

## JSON Model Validation Performance

Preliminary performance tests below compare validation times for a _large_ 500 KB JSON OpenAPI
description using JSON Model in C, JS and Python and JSON Schema Blaze 9.6.1 implementation,
with an average collected on one thousand runs, in _fast_ (no reporting) mode, including
format validations, on a laptop:

- JSON Model C: _204_ µs/check (about ⅕ ms)
- JSON Model JS: _791_ µs/check (under 1 ms)
- JSON Schema C++ Blaze: _1252_ µs/check (over 1 ms)
- JSON Model Python: _4,433_ µs/check (over 4 ms)

On this benchmark, JSON Model Compiler outperforms the fastest JSON Schema library 6:1,
and the JavaScript model validation is faster than the C++ schema validation.

## More Information

See the [JSON Model Tutorial](./TUTO.md) for a hands-on overview of JSON Model.

JSON Model design is presented in research papers and reports:

- JSON Model: a Lightweight Featureful DSL for JSON.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/817/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-817.pdf),
  Mines Paris - PSL, April 2024

  JSON Model version 1.

- An Analysis of Defects in Public JSON Schemas.
  Claire Yannou-Medrala and Fabien Coelho.  
  In BDA 2023, 39ème conférence sur la gestion de données - Principes, technologies et applications.
  Also TR [A/794/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-794.pdf),
  Mines Paris - PSL, October 2023

  Brief introduction to version 0 at the end of the paper.

- JSON Model: a Lightweight Featureful Description Language for JSON Data Structures.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/795/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-795.pdf),
  Mines Paris - PSL, May 2023

  JSON Model version 0.
