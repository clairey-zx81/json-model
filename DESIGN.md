## Design of JSON Model v2

## Ambition

- an intuitive and compact JSON syntax to describe JSON data
- take advantage of type inference as much as possible
- relevant to a wide range of use cases
- allow adapting a existing model with import and transformation
- very fast implementations through compiler static optimizations
- export to other syntax, eg JSON Schema, pydantic
- extensions? see moshi

## Usability use cases

- def only models are ok
- manage (related) models:
  - in files
  - in files in a directory
  - through a URL
  - inlined in source files
- tooling, file derivation
  - how to manage model changes and file derivations depending on the output
  - (easy) integration into the JS (npm) ecosystem?
  - (easy) integration into the Python (pip) ecosystem?
  - web development specific ecosystems: Flask, Django, express.js, Spring…
- derive/import JSON Model from an actual/existing data structure:
  - how to import and use such definitions?
- non JSON format:
  - yaml: for convenient data structure documentation
  - js/ts: for convenient data structure documentation (i.e. JSON with comments)
  - py: for convenient data structure documentation (?!)
  - ORM, tables, pydantic, dataclass, python types…
- extensions: derive models for distinct usages?
- provide with default values for initialization
- rewrite: compare with dynamic reference JSON Schema use case.
