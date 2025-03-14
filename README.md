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

## Commands

- `jm-c-check-model awesome.model.json files.json…`

   check whether the model matches the JSON data in files
   with the JSON Model Dynamic Compiler.

- `jm-cs-check-model awesome.model.json files.json…`

   check whether the model matches the JSON data in files
   with the JSON Model Static Compiler.

- `jm-v-check-model awesome.model.json files.json…`

   same thing with the *validator* (aka interpreter).

- `jm-model2schema` convert a JSON Model to a JSON Schema.
- `jm-schema2model` convert a JSON Schema (partial) to a JSON Model.
- `jm-preprocessor` JSON Model preprocessor
  - flatten operators `|` `^` and `&`
  - distribute `+` (merge operator occurences) over `|` (or operator) and `^` (xor)
  - compute merged objects definitions (i.e. removes `+` operators)
  - partial evaluation
  - deduplication in `^ |`
  - xor to or convertion if possible (`^` → `|`)
- `jm-compiler awesome.model.json`

  static compiler, including some optimization:

  - detect object tags (discriminators)
  - optimize type checks in "&"
  - optimize homogeneous typed list in "&" and "|" 
  - subset of simple type constants

## TODO v2

- change `%` to `$` and remove `$` intra-model naming shortcut?
- readability and style: `:verbose` version of single char keywords!?
- clarify stuff inside the root `#`? or use `%` for specific purpose?
- check and document API entry points
- add doc and test CI
- provide a model to form proof-of-concept, possibly using some convenient form
  library, eg [FormBuilder](https://formbuilder.online/).
- think of extensions for variants, i.e. form in progress vs final form with more constraints?
- think of extensions to direct forms for instance?
  eg types, constraints, layout or not?
- think of extensions to direct relational mapping? (eg foreign key/primary key/unique)
  for the Python ecosystem, see `SQLAlchemy` and `Django`?
- think of extensions to direct object creation (Python pydantic, JS)?
- extensions could allow synonyms enabling JSON Model l10n?!
- name space?
- conditionals or not conditionals… eg for interfaces
  if not in the description language, it should be easy to express outside.
- declaration of the meta model?

  ```json
  {
    "#": {
      ":meta-model": "$URL"
    }
  }
  ```

  ```json
  {
    "%": "$URL"
  }
  ```

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
