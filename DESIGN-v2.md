## Design of JSON Model v2

## Ambition

- an intuitive and compact JSON syntax to describe JSON data
- take advantage of type inference as much as possible
- relevant to a wide range of use cases
- allow adapting a existing model with import and transformation
- very fast implementations through compiler optimizations, dynamic and static
- export to other syntax, eg JSON Schema.

## WIP

- integration of json-model extensions?

  - could be a simplified version of JSON Schema vocabularies?
  - can also be loaded through a reference?
  - available characters
    - json characters to avoid (?) by decreasing frequency: `" : , {} [] - .`
    - used as keywords: `# $ @ ! = < > & | ^ +`…
    - used as sentinels: `$ _ ? ! = /`…
    - thus: `% ~ * / . ; ( ) ? `` -`…

  - examples

    ```json
    {
      "~": "https://json-model.org/models/json-model-v2",
      "$": {
        "": "https://json-model.org/models/json-model-v2-form"
        "Model": "$https://json-model.org/models/json-model-v2"
      },
      "%": {
        "$Model#Elem.+.0": {
          "*": { "?.readOnly": true }
        },
        "$Model#Or": {
          "*": { "?.selector": { "|": [ "checkbox", "menu", "whatever" ] } }
        }
      },
      "@": "$Model"
    }
    ```

    ```json
    {
      "$": {
        "modelv2": "$https://models.json-model.org/modelv2"
      },
      "%": {
        "#": "path to field to modify, change",
        "$model2#Object": {
          "*": { "?new-keyword": "$..." },
          "/": [ "props", "to", "remove", "in", "target" ]
        },
        "$model2#Common": "replacement_model"
      }
    }
    ```

- NOTE we decided to avoid reusing `+ ~` for `* /`.

- localization with prefixed keywords: `: ,` (too many?), `*` noizy and ugly, `.` discreet and rare enough?

  ```json
  {
    "%": { ".or": "|", ".unique": "!" }
  }
  ```

## Merge

- merge allow to merge something / ANY by keeping stricter one

## Usability use cases

- manage (related) models:
  - in files
  - in files in a directory
  - through a URL
  - inlined in source files
- tooling, file derivation
  - how to manage model changes and file derivations depending on the output
  - (easy) integration into the JS (npm) ecosystem?
  - (easy) integration into the Python (pip) ecosystem?
  - web development specific ecosystems: Flask, Django, express.js…
- derive/import JSON Model from an actual/existing data structure:
  - how to import and use such definitions?
- non JSON format:
  - yaml: for convenient data structure documentation
  - js/ts: for convenient data structure documentation (i.e. JSON with comments)
  - py: for convenient data structure documentation (?!)
  - ORM, tables, pydantic, dataclass, python types…
- extensions: derive models for distinct usages?

- rewrite: compare with dynamic reference JSON Schema use case.
