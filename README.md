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

- [x] move schema to model conversion to json-schema-utils.
- [x] change `%` to `$` and remove `$` intra-model naming shortcut.
- [x] name space decision, there is only one name space per file. trafo path are exceptions?
- [~] readability and style: `:verbose` version of single char keywords!? (see extensions)
- [x] clarify stuff inside the root `#`? or use `%` for specific purpose?
- [x] extenstion for preprocessed (merged and trafo).
- [x] dynamic python compiler
- [x] static python compiler
- [x] think of extensions for variants, i.e. form in progress vs final form with more constraints?
- [x] extensions could allow synonyms enabling JSON Model l10n?
- [x] declaration of the meta model?
- [ ] static python: generate separate `check_model` root function and simplify code.
- [ ] recheck existing tests in rwt
- [ ] move/add more tests to rwt
- [ ] refactor all tests
- [ ] test schemas with jsu?
- [ ] add doc and test CI
- [ ] improve `-P` to have a re-intrant model
- [ ] prettyprint rejection reasons?
- [ ] direct validator
- [ ] static js/ts compiler
- [ ] check and document API entry points
- [ ] think of extensions to direct forms for instance, eg types, constraints, layout?
      see [FormBuilder](https://formbuilder.online/).
- [ ] think of extensions to direct relational mapping? (eg foreign key/primary key/unique)
- [ ] think of extensions to direct object creation (Python pydantic, JS)?
- [ ] think of extensions for ORM, eg in the Python ecosystem, see `SQLAlchemy` and `Django`?
- [ ] think of extensions for accepting any extension?! eg opened objects?
- [ ] conditionals or not conditionals… eg for interfaces
      if not in the description language, it should be easy to express outside.
- [ ] create a clean documentation, following Diátaxis (tuto | howto / explain | reference).
- [ ] model tutorial which mimics [json schema](https://tour.json-schema.org/).

  ```json
  {
    "~": "$URL"
  }
  ```

- [ ] integration of json-model extensions?

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
    "$": {
      "model": "$https://json-model.org/model-v2"
    },
    "%": {
      "$model#Elem.+.0": {
        "+": { "?readOnly": true }
      },
      "$model#Or": {
        "+": { "?selector": { "|": [ "checkbox", "menu", "whatever" ] } }
      }
    },
    "@": "$model#Root"
  }
  ```

- localization with prefixed keywords? `:` (too many?), `*` too noizy, `.` discreet enough?

  ```json
  {
    "%": { "*or": "|" }
  }
  ```
