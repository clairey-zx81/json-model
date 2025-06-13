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

First, let us create a directory and install a Python virtual environment with the JSON Model
Compiler. In a Linux, MacOS or Windows with WSL terminal, type:

```sh
mkdir json-model-tutorial
cd json-model-tutorial
python -m venv venv
source venv/bin/activate
pip install git+https://github.com/clairey-zx81/json-model.git
```

Check that the `jmc` command is indeed available by checking its version:

```sh
jmc --version
```

## JSON – JavaScript Object Notation

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

A possible model simplistic model declaration for this data structure,
in file `Person-0.model.json`, is:

```json
{
  "name": "",
  "birth": "",
  "?friends": [ "" ]
}
```

The object properties are directly mapped to simple values: `""` stands for any string,
and `[ "" ]` an array of any number of strings, thanks to type inference.
The `?` sentinel character in the `"?friends"` property name indicates an _optional_ property,
other properties are _mandatory_ by default.

Let us check that our initial value matches the model by invoking the `jmc` command:

```sh
jmc Person-0.model.json hobbes.json
```

Should yield:

```
hobbes.json: PASS
```

Let us try a value which does not match because of a typo on a property name
(`friend` instead of `friends`), in file `moe.json`:

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
jmc -r Person-0.model.json moe.json
```
```
moe.json: FAIL (.: not an expected object [.]; .friend: unexpected prop [.])
```

The validation rejects the property at path `.friend` because it is not allowed
by the model, which yields to the conclusion that the object at the root `.` is unexpected.
The JSON path in square brackets `[.]` indicates where in the _model_ the
ruled was found whereas the path before the `:` indicates where in the _value_ it failed.

Note: for efficiency, the validation stops at the first encountered error which invalidates the
value: if a value includes several root errors, only one is reported.

## JSON Model with Constrained Strings

Our first model has no constraints on strings, thus also validates file `elysee.json`:

```json
{
  "name": "Élysée Palace, 55 rue du Faubourd Saint-Honoré, 75008 Paris, France.",
  "birth": "1722",
  "friends": [ "2", "3", "5", "7", "11" ]
}
```

We can improve it by constraining strings with regular expressions (between `/.../`)
and predefined types (`$...`), in file `Person-1.model.json`:

```json
{
  "name": "/^(\\w+ ?)+$/",
  "birth": "$DATE",
  "?friends": [ "/^(\\w+ ?)+$/" ]
}
```

Then the validation is strict enough to invalidate this value:

```sh
jmc Person-0.model.json elysee.json  # PASS
jmc Person-1.model.json elysee.json  # FAIL
```

## JSON Model with definitions

The previous model includes a regex which is hard to read and repeated twice.
We can use definitions to enhance readability and help reuse structures,
in file `Person-2.model.json`:

```json
{
  "#": "Definition of a Person",
  "$": {
    "Name": "/^(\\w+ ?)+$/",
    "Person": {
      "name": "$Name",
      "birth": "$DATE",
      "?friends": [ "$Name" ]
    },
    "PI": "=3.141592653589793238462643"
  },
  "@": "$Person"
}
```

This model defines 3 named models (in the `$` property), which can be referenced with `"$..."`
in definitions and as the root target type after ('@' property), and also includes a
comment (`#`). `"$DATE"` is predefined to only allow valid ISO-formatted date strings.

Special properties (`# $ @`) are used by JSON Model to extend models beyond simple
type inference. The choice of short symbols avoids confusion with word-based
property names used in typical JSON data structures.

Sentinel characters are used at the beginning of strings to embed special semantics,
such as regular expressions (`/`), references to named models (`$`) or scalar constants (`=`).

The `jmc` command allows to validate a value against a particular definition of a model,
for instance with file `pi.json`:

```json
3.141592653589793238462643
```

We can check that its content conforms to PI definition:

```sh
jmc --name PI Person-2.model.json pi.json
```
```
pi.json: PASS
```

## JSON Model with Loose Objects

People coming to JSON formatted data from strongly typed programming languages and relational
databases often like strict types to detect potential errors as soon as possible.
People coming to JSON from web application programming with weakly typed languages such as
JavaScript or PHP and loose document-based storage such as MongoDB might prefer loose data
structures which allow to add new properties silently.

There is no way to please everybody. Prioritizing data safety, JSON models are strict (closed)
by default, but can be easily extended to allow unknown properties with a special empty
string property, which is consistent with `""` representing _any_ string.

Hence, with file `Loose.model.json`:

```json
{
  "$": { "Name": "/^(\\w+ ?)+$/" },
  "name": "$Name",
  "birth": "$DATE",
  "?friends": [ "$Name" ],
  "": "$ANY"
}
```

The model is loosened thus accepts a person extended with unspecified properties having _any_ value.
However, this model silently ignores the property name typo in file `moe.json`
because it is covered by the catch-all property:

```json
jmc Loose.model.json moe.json
```
```
moe.json: PASS
```

This leads to ignoring typos on optional property names, which is seldom a good idea.

## JSON Model with alternatives

A frequent pattern is allow several kind of object as some point in the data structure.
This can be expressed with a model involving either the special `^` (xor, one-of) or `|`
(or, any-of) property with the list of objects.

Consider the model in file `Geom.model.json`, which defines a coordinate (`coord`) as
a pair of numbers, and use it for defining a point and a segment objects which are
allowed at the root of the model:

```json
{
  "$": { "coord": [ -1.0, -1.0 ] },
  "^": [
    {
      "type": "Point",
      "data": "$coord"
    },
    {
      "type": "Segment",
      "data": [ "$coord", "$coord" ]
    }
  ]
}
```

It matches both files `marseille.json` and `seoul-tokyo.json`:

```json
{
  "type": "Point",
  "data": [ 43.3, 5.4 ]
}
```

```json
{
  "type": "Segment",
  "data": [ [ 37.5, 127.0 ], [ 35.7, 139.7 ] ]
}
```

```sh
jmc Geom.model.json marseille.json seoul-tokyo.json
```
```
marseille.json: PASS
seoul-tokyo.json: PASS
```

When defining such unions, it is much better to include a discriminant property (here `type`)
with distinct constant value: it is detected by the JSON Model compiler and used to generate
efficient code which only checks for the relevant object.

## JSON Model with numbers

## JSON Model with object compositions

## JSON Model with constraints

## JSON Model transformations

## JSON Model examples

## JSON Model export to JSON Schema

## Conclusion
