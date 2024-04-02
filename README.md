# JSON Model Tools

JSON Model is a JSON syntax to describe JSON data structures.
It is presented in:

- JSON Model: a Lightweight Featureful Description Language for JSON Data Structures  
  Fabien Coelho and Claire Yannou-Medrala  
  Technical Report A/795/CRI, Mines Paris - PSL.

## Tool Installation

Proof-of-concept tools to test JSON Model are available as Python commands:

```shell
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

## Commands

- `c-check-model some.model.json files.json…`

   check whether the model matches the JSON data in files
   with the JSON Model Compiler.

- `v-check-model some.model.json files.json…`

   same thing with the *validator* (aka interpreter).

- `model2schema` convert a JSON Model to a JSON Schema.
- `schema2model` convert a JSON Schema (partial) to a JSON Model.
- `json-model-merge` JSON Model preprocessor
  - flatten operators `|` `^` and `&`
  - distribute `+` (merge operator occurences) over `|` (or operator).
  - compute merged objects definitions (removes `+` operators)
