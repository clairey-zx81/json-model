# JSON Model Tutorial

JSON Model is a JSON language to describe JSON data structures.
Its objective is similar to [JSON Schema](https://json-schema.org/), but with
a user-friendly, compact and intuitive syntax which relies on type inference,
so that objects are typically described with example values.

This tutorial aims at learning briefly the JSON Model syntax and how to use
the `jmc` command for validating values directly.
It does not address the integration of JSON Model in a project, which
would depend on the specific framework used, as discussed in [How To…](HOWTO.md).

## Installation

First, create a directory and install a Python virtual environment with the JSON Model
Compiler. In a Linux, MacOS or Windows with WSL terminal, type:

```sh
mkdir json-model-tutorial
cd json-model-tutorial
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

Check that the `jmc` command is avalaible by checking its version.

```sh
jmc --version
```

## JSON (JavaScript Object Notation)

[JSON](https://www.json.org/) is a simple text serialization format to represent structured
values involving scalars, arrays and objects.

- **scalars**: `null`, `true`, `false`, integers or floats (collectively named `number` in JSON),
  and utf-8 strings in double quotes.
- **arrays**: a possibly empty list of JSON elements between square brackets (`[` and `]`)
  with comma `,` as a separator.
- **objects**: a mapping of property names (strings) to JSON values between curly braces 
  (`{` and `}`) with colons `:` and commas `,` as separators.

For instance, the following object can represent a person with their name, birth date and array
of friend names, that you can put in File `hobbes.json` using your favorite text editor:

```json
{
  "name": "Hobbes",
  "birth": "2020-07-29",
  "friends": [ "Calvin", "Susie" ]
}
```

## JSON Model for a Person

A possible model for this data structure, in file `person.model.json`, is:

```json
{
  "name": "",
  "birth": "$DATE",
  "?friends": [ "" ]
}
```

The object properties are directly mapped to simple values: `""` stands for any string, `"$DATE"`
for a predefined which must match a valid date, `[ "" ]` an array of any number of strings.
The `?` sentinel character in the `"?friends"` property name indicates an optional property.

Check that the value matches the model:

```sh
jmc person.model.json hobbes.json
```

Should yield:

```
hobbes.json: PASS
```

Let us try a value which does not match because of a typo (proprety `friend` instead of `friends`),
in file `moe.json`:

```json
{
  "name": "Moe",
  "birth": "2022-02-22",
  "friend": []
}
```

Then we can invoke the `jmc -r` command (the option triggers reporting the reason for
validation failures) to validate this value with the person model:

```sh
jmc -r person.model.json moe.json
```
```
moe.json: FAIL (.: not an expected object [.]; .friend: unexpected prop [.])
```

The validation has rejected the property at path `.friend` because it is not allowed
by the model, which yields to the conclusion that the object at the root `.` is unexpected.
The JSON path in square brackets `[.]` indicates where in the _model_ the
ruled was found whereas the path before the `:` indicates the where in the _value_ it failed.

## JSON Model with numbers

## JSON Model with loose objects

## JSON Model with alternatives

## JSON Model with definitions

## JSON Model with object compositions

## JSON Model with constraints

## JSON Model transformations

## JSON Model export to JSON Schema

## Conclusion
