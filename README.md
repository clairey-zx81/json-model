# JSON Model

JSON Model is a compact and intuitive JSON syntax to describe JSON data structures.

This reference implementation allows to generate code in Python, C, JavaScript,
PL/pgSQL, Perl and Java for checking a JSON value against a JSON model,
and to export models to JSON Schema or Pydantic.

It is dedicated to the _Public Domain_.

## JMC Command

JSON Model optimizing compiler (`jmc`) can be installed as a
[Python package](https://pypi.org/project/json-model-compiler/) or a
[Docker image](https://hub.docker.com/r/zx80/jmc), see
[Installation HOWTO](HOWTO.md#installing-json-model-compiler).

Command `jmc` options include:

- main operations (default depends on other options, final guess is preprocess):
  - `-P`: preprocess model.
  - `-C`: compile to Python, C, JS, PL/pgSQL, Perl, Java.
  - `-E`: export to JSON Schema version draft 2020-12 or Pydantic.
- `-O`: optimize model: constant propagation, partial evaluation, xor to or conversion, flattening…
  (this is the default, `-nO` to disable)
- `-o output`: file output instead of standard
- …

For instance, let's consider a JSON model in file `person.model.json`:

```json
{
  "#": "A person with a birth date",
  "name": "/^[a-z]+$/i",
  "born": "$DATE"
}
```

- to check directly sample JSON values against it (with the Python backend):

  ```sh
  jmc -r person.model.json hobbes.json oops.json
  ```
  ```
  hobbes.json: PASS
  oops.json: FAIL (.: not an expected object [.]; .: missing mandatory prop <born> [.])
  ```

- to compile an executable for checking a model (with the C backend),
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

See the [benchmark page](BENCH.md) for artifacts which compare various
[JSON Model Compiler](https://github.com/clairey-zx81/json-model) runs (C, JS, Java, Python) with
[Sourcemeta Blaze CLI](https://github.com/sourcemeta/jsonschema) as a baseline using test cases
from [JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).
Overall, JMC-C implementation fares over 50% faster than Blaze C++ and comes ahead 70% of the time
on the latest benchmarks tests, and JMC-JS and JMC-Java/GSON native implementations are on average
about 40% slower than Blaze C++, which given the intrinsic language capabilities is honorable.

## More Information

See the [JSON Model website](https://json-model.org),
which among many resources,
includes a [tutorial](TUTO.md) for a hands-on overview of JSON Model,
and links to [research papers](PAPERS.md) for explanations about the design.

## JSON Model Distribution

- [PYPI Package](https://pypi.org/project/json-model-compiler/)
- [Docker Image](https://hub.docker.com/r/zx80/jmc)
- [JS Runtime](https://www.npmjs.com/package/json_model_runtime)
- [Postgres Runtime](https://pgxn.org/dist/json_model/)
- [Perl Runtime](https://metacpan.org/pod/JSON::JsonModel)
- [Java Runtime](https://central.sonatype.com/artifact/org.json-model/json-model)
