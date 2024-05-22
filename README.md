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

- `jm-c-check-model some_model.json files.json…`

   check whether the model matches the JSON data in files
   with the JSON Model Dynamic Compiler.

- `jm-cs-check-model some_model.json files.json…`

   check whether the model matches the JSON data in files
   with the JSON Model Static Compiler.

- `jm-v-check-model some_model.json files.json…`

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
- `jm-compiler some_model.json`
  static compiler, including some optimization:
  - detect object tags
  - optimize type checks in "&"

