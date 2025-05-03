# JSON Model Tools

JSON Model is a JSON syntax to describe JSON data structures.
It is presented in:

- JSON Model: a Lightweight Featureful DSL for JSON.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/817/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-817.pdf),
  Mines Paris - PSL, April 2024

  JSON Model version 1.

- An Analysis of Defects in Public JSON Schemas.
  Claire Yannou-Medrala and Fabien Coelho.  
  In BDA 2023, 39eme conférence sur la gestion de données - Principes, technologies et applications.
  Also TR [A/794/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-794.pdf),
  Mines Paris - PSL, October 2023

  Very brief introduction to version 0 at the end of the paper.

- JSON Model: a Lightweight Featureful Description Language for JSON Data Structures.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/795/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-795.pdf),
  Mines Paris - PSL, May 2023

  JSON Model version 0 (work in progress).

## Tool Installation

Proof-of-concept compiler to test JSON Model is available as Python a command:

```shell
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

## Command

Command `jmc` (JSON Model Compiler) options:

- `--optimize` or `-O`: optimize (const prop, partial eval, xor to or, flatten)
- `-P -D -S -E -U`: operation (preprocess, dynamic and static compile, JSON Schema export, dump)
- `-o output`: file output instead of standard
- …

## Backlog v2

- [x] refactor: move schema to model conversion to json-schema-utils.
- [x] design: change `%` to `$` and remove `$` intra-model naming shortcut.
- [x] design: name space decision, there is only one name space per file. trafo path are exceptions?
- [~] design: readability and style: `:verbose` version of single char keywords!? (see extensions)
- [x] design: clarify stuff inside the root `#`? or use `%` for specific purpose?
- [x] design: extension for preprocessed (merged and trafo).
- [x] dynamic: python compiler
- [x] static: python compiler
- [x] design: variants, i.e. form in progress vs final form with more constraints?
- [x] design: extensions could allow synonyms enabling JSON Model l10n?
- [x] tests: declaration of the meta model?
- [x] feature: accept js suffix as input, possibly removing comments.
- [x] feature: add `--auto` option to automatically extract url mappings
- [x] static: generate separate `check_model` root function and simplify code.
- [x] tests: recheck existing tests in rwt
- [x] static: deterministic set output
- [x] dynamic: fix output instability
- [x] python: pyright
- [x] python: ruff
- [x] python: flake8
- [x] refactor: move basic script pre processing as functions
- [x] tests: test schemas and values with jsu
- [x] extend: `.schema` extension to add JSON Schema specific stuff, and `.mo` and `.in`
- [x] tests: rename without explicit `-v2`
- [x] python: remove global list in Symbols
- [x] tests: move bads up
- [x] tests: move bads data to bads directory
- [x] feature: use `-` for standard input and output
- [x] feature: yaml file input
- [x] tests: working `make check`
- [x] tests: make check for bads
- [x] tests: add malformed bad models
- [x] tests: with an actual url! (hello2)
- [x] python: rename `types.py` which is a pain
- [x] feature: yaml url input
- [x] tests: True/False -> PASS/FAIL
- [~] feature: how to remove a definition? nope, must be nullified (eg `$NONE`) because refs
- [x] tests: upgrade all models in `models/` and check them as well
- [x] tests: add expected "$schema" value to schema models
- [x] static: do not inline unused support function (`is_valid_*` and possibly others)
- [x] schema: control keyword sorting to put type-related stuff on top (-ns)
- [x] static: use mandatory keyword parameters where appropriate
- [x] feature: clarify and implement options management `JSON_MODEL_…`
- [x] feature: allow scalar value for `/`
- [x] schema: test output json schema (strict) conformity
- [x] command: use exclusive options where appropriate
- [x] tests: check all models wrt to the meta model, once
- [x] static: remove pyright asserts from generated code
- [ ] static: add a `_` to the default prefix to separate exports
- [ ] static: update path
- [ ] static: fast vs slow with path and reasons?
- [ ] static: detect and remove duplicate functions!
- [ ] static: add option to report where it fails (aka reasons)
- [ ] static: generate pyright compatible code…
- [ ] tests: remove unstable DO output? remove empty lines?
- [ ] static: fix `modval/_untyped*` with `value_len` when type is unknown
- [ ] design: handle `.` and `/` references as relative url
- [ ] design: namespace, only some defs exported, and cannot have multi-level refs `$r#N#xxx`?
- [ ] python: use mandatory keyword parameters where appropriate
- [ ] python: extract optimizations in another file
- [ ] design: convention for local vs exported definitions? capital?
- [ ] optim: remove unused local (not exported) definitions
- [ ] feature: make (static/dynamic) compiled exported defs accessible… which implies fname control
- [ ] static: separate compilation of included models
- [ ] command: add option to control name of generated function
- [ ] command: add option to do/skip check of `~` model
- [ ] feature: control url caching, change dir location or disable
- [ ] feature: cache expiration?
- [ ] feature: improve error messages, eg missing "$" on a URL reference
- [ ] feature: restrict definitions as proper identifiers
- [ ] tests: re-check some results of json schema analysis paper
- [ ] feature: self trafo example, eg create a variant between local defs
- [ ] python: remove global list in JsonModel
- [ ] python: remove all globals in Symbols?
- [ ] python: remove all globals in JsonModel?
- [ ] python: measure coverage
- [ ] feature: simplify lib usage wrt script-like features with some functions
- [ ] feature: full inline of externals to generate a working model without includes
- [ ] feature: check/forbid/allow url references with an anchor
- [ ] python: refactor and cleanup
- [ ] static: remove spurious newlines
- [ ] tests: move/add more tests to rwt, modval, bads
- [ ] tests: what if a trafo adds/replaces an external reference, is it resolved?
- [ ] tests: fix tests in `bads/wip`?
- [ ] tests: refactor all tests, keep or drop `pytest`
- [ ] tests: use ref instead of git?
- [ ] tests: add github CI
- [ ] tests: raise coverage, possibly to 100%?
- [ ] output: improve `-P` to have a re-intrant model (see also: inline)
- [ ] output: prettyprint rejection reasons?
- [ ] feature: direct validator
- [ ] feature: static/dynamic js/ts compiler?
- [ ] feature: (limited) pydantic export?
- [ ] feature: integrate or remove `stats`?
- [ ] feature: --yaml show yaml instead of json
- [ ] feature: think about code integration in a realistic project? usability? doc?
- [ ] design: (online) extension register?
- [ ] design: official (meta) model url:
      `https://models.json-model.org/...` vs `https://json-model.org/models/...`?
- [ ] doc: check and document API entry points
- [ ] extend: direct forms for instance, eg types, constraints, layout? see [FormBuilder](https://formbuilder.online/).
- [ ] extend: direct relational mapping? (eg foreign key/primary key/unique)
- [ ] extend: direct object creation (Python pydantic, JS)?
- [ ] extend: ORM support, eg in the Python ecosystem, see `SQLAlchemy` and `Django`?
- [ ] extend: data structure _documentation_
- [ ] extend: accepting any extension?! eg opened objects?
- [ ] extend: variants, see `models/json-schema-*`
- [ ] design: conditionals or not conditionals… eg for interfaces?
      if not in the description language, it should be easy to express outside.
- [ ] doc: create a clean documentation, following Diátaxis (tuto | howto / explain | reference).
- [ ] doc: setup mkdocs
- [ ] doc: tutorial which mimics [json schema](https://tour.json-schema.org/)?
- [ ] research: paper themes? extensions, compilation (CGO), ...?
- [ ] feature: use actual JSON path spec for transformations with a filter for applying changes
- [ ] pr: register `json-model.org`? use `github.io`?
- [ ] pr: article submission about data structure trafo? CGO (end of may)?
- [ ] schema: handle includes? inline?!
- [ ] static: abstract imperative language code generation with intermediate code?
      see JSON Schema C++ Blaze, RUST boon?
- [ ] static: prioritize ts/js for usability, c for speed.
- [ ] c-backend: see [jansson](https://jansson.readthedocs.io/en/latest/), avoid cJSON.
- [ ] rust-backend: see [json crate](https://docs.rs/json/latest/json/).
- [ ] java-backend: see [jackson](https://github.com/FasterXML/jackson).
- [ ] kotlin-backend: see [serialization](https://kotlinlang.org/docs/serialization.html).
- [ ] feature: add model predef for URI-REF

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

- usability use cases:

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
