# JSON Model Specification

This is a semi-formal specification of JSON Model.

JSON Model aims at describying JSON data structures, so in that sense it is a cross-language
JSON-specific type declaration written in JSON or YAML.

Some features go beyond traditional _structural_ typing, for instance by using constants,
regular expressions.

## JSON Summary

[JSON (JavaScript Object Notation)](https://www.json.org/) is a limited-feature text serialization
format linked to the JavaScript ecosystem.
JSON values are built recursively from:

- symbols: `null`, `true`, `false`
- numbers, mixing integers and floats: _-42_, _3.1415927_
- unicode text: `"Hello World!"`
- arrays of values: `[ …, … ]`
- objects mapping string properties to JSON values: `{ "foo": …, "bla": … }`

There are no comments.
There are not cycles or references, a JSON data structure is only a tree.

## Type Inference

## Scalars

## Constraints

## Definitions and Scope

## References and Imports

## Model Transformations

## Self-Validating Meta-Model

## References
