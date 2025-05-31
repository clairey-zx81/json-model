# JSON Model Tools

JSON Model is a compact and intuitive JSON syntax to describe JSON data structures.

Version 2 is work-in-progress design, implementation and tests.

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

- main operations:
  - `-P`: preprocess model.
  - `-E`: export model to JSON Schema version draft 2020-12, if possible.
  - `-X`: generate python or C code.
  - `-U`: dump all models.
  - `-J`: dump json IR.
  - `-O`: optimize model: const prop, partial eval, xor to or, flatten…
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

- to _export_ this model as a JSON schema:

  ```sh
  jmc -EO -F yaml person.model.json
  ```

  Output in the YaML format (because of the `-F` option):

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

- to check sample JSON values against it:

  ```sh
  jmc -XO -v person.model.json hobbes.json unknown.json
  ```

  Output with an explanation (because of `-v` verbose option):

  ```
  hobbes.json: PASS
  unknown.json: FAIL [('missing must prop [$]', []), ('not an expected object at [$]', [])]
  ```

- to actually compile an executable for checking a model, and use it for validating values:

  ```sh
  jmc -XO -F out -o ./person.out person.model.json
  ./person.out -r hobbes.json unknown.json
  ```
  ```
  hobbes.json: PASS
  unknown.json: FAIL (.: not an expected object at [$]) (.: missing must prop [$])
  ```

## JSON Model Python API

The package provides functions to load and check models from Python:

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
bad_person = { "name": "Unknown" }
print(bad_person, "->", checker(bad_person))

# collect reasons
reasons: jm.Report = []
assert not checker(bad_person, "", reasons)
print("reasons:", reasons)
```

## References

JSON Model design is presented in:

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
