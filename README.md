# JSON Model Tools

JSON Model is a JSON syntax to describe JSON data structures.
It is presented in:

- JSON Model: a Lightweight Featureful DSL for JSON.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/817/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-817.pdf), Mines Paris - PSL, April 2024

  JSON Model version 1.
  
- An Analysis of Defects in Public JSON Schemas.
  Claire Yannou-Medrala and Fabien Coelho.  
  In BDA 2023, 39eme conférence sur la gestion de données - Principes, technologies et applications.
  Also TR [A/794/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-794.pdf), Mines Paris - PSL, October 2023

  Very brief introduction to version 0 at the end of the paper.

- JSON Model: a Lightweight Featureful Description Language for JSON Data Structures.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/795/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-795.pdf), Mines Paris - PSL, May 2023

  JSON Model version 0 (work in progress).

## Tool Installation

Proof-of-concept tools to test JSON Model are available as Python commands:

```shell
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

## Command

Command `jmc` (JSON Model Compiler) options:

- `--optimize` or `-O`: optimize (const prop, partial eval, xor to or, flatten)
- `-P -D -S -E -U`: operation (preprocess, dynamic and static compile, JSON Schema export, dump)
- `-o output`: output file instead of standard
- …

## TODO v2

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
- [x] python: pyright
- [x] python: ruff
- [x] python: flake8
- [ ] python: coverage
- [ ] dynamic: fix output instability
- [ ] static: remove spurious newlines
- [ ] static: detect and remove duplicate functions!
- [ ] static: do not inline unused support function (`is_valid_*`)
- [ ] tests: move/add more tests to rwt
- [ ] tests: refactor all tests
- [ ] tests: test schemas with jsu?
- [ ] output: improve `-P` to have a re-intrant model
- [ ] output: prettyprint rejection reasons?
- [ ] python: refactor and cleanup
- [ ] feature: direct validator
- [ ] feature: static js/ts compiler
- [ ] feature: integrate or remove `stats`?
- [ ] feature: --yaml show yaml instead of json
- [ ] feature: simplify lib usage wrt script-like features with some functions
- [ ] doc: add doc
- [ ] tests: add github CI
- [ ] feature: think about code integration in a realistic project? doc and usability?
- [ ] doc: check and document API entry points
- [ ] extend: direct forms for instance, eg types, constraints, layout?
      see [FormBuilder](https://formbuilder.online/).
- [ ] extend: direct relational mapping? (eg foreign key/primary key/unique)
- [ ] extend: direct object creation (Python pydantic, JS)?
- [ ] extend: ORM support, eg in the Python ecosystem, see `SQLAlchemy` and `Django`?
- [ ] extend: accepting any extension?! eg opened objects?
- [ ] feature: conditionals or not conditionals… eg for interfaces
      if not in the description language, it should be easy to express outside.
- [ ] doc: create a clean documentation, following Diátaxis (tuto | howto / explain | reference).
- [ ] doc: tutorial which mimics [json schema](https://tour.json-schema.org/)?

## WIP

- integration of json-model extensions?

  This could be a simplified version of JSON Schema vocabularies?

  - declare extensions with some meta?!

    ```json
    {
      "$": {
        "modelv2": "$https://models.json-model.org/modelv2"
      },
      "%": {
        "#": "path to field to modify",
        "$model2#Object": {
          "+": { "?new-keyword": "$..." }
        }
      }
    }
    ```

  - contextualized? model context? semantics ?!

    ```json
    {
      "$": {
        "modelv2": "$https://models.json-model.org/modelv2"
      },
      "%": {
        "#": "path to model to modify (remove, replace, add)",
        "$model2#Object": {
          "@": { "_@": "$ANY" },
          "-": { "old-kw": null },
          "~": { "some-kw": "$..." },
          "+": { "new-kw": "$..." }
        }
      }
    }
    ```

    What about allowing several contexts and targets with alternative `|`?

    Context semantics may be quite specific? Should it be open by default?
    Should it be direct or meta? Should it be a structural match?

  - can also be loaded through a reference?

  - use something other than `#`? `%`?
    - used sentinels and keywords: `# $ _ ? ! = @ & | ^ + / ops`…
    - possibly available or reusable keywords: `~ * . : ; , ( ) [ ] { } ops`…

- example

  ```json
  {
    "~": "https://json-model.org/models/json-model-v2-form"
    "$": {
      "model": "$https://json-model.org/models/json-model-v2"
    },
    "%": {
      "$model#Elem.+.0": {
        "*": { "?.readOnly": true }
      },
      "$model#Or": {
        "*": { "?.selector": { "|": [ "checkbox", "menu", "whatever" ] } }
      }
    },
    "@": "$model"
  }
  ```

- localization with prefixed keywords: `: ,` (too many?), `*` too noizy, `.` discreet and rare enough?

  ```json
  {
    "%": { ".or": "|" }
  }
  ```
