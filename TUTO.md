# JSON Model Tutorial

JSON Model is a JSON language to describe JSON data structures.
Its objective is similar to [JSON Schema](https://json-schema.org/), but with
a user-friendly, compact and intuitive syntax which relies on type inference,
so that simple objects are typically described with example values.

This tutorial aims at learning briefly the JSON Model syntax and how to use
the `jmc` command for validating values directly.
For integrating JSON Model in a project, see [HowTo](HOWTO.md).

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

Add the different example values and models discussed below in this directory
so as to test the compiler.

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
of friend names, that you can put in file `hobbes.json` using your favorite text editor:

```json
{
  "name": "Hobbes",
  "birth": "2020-07-29",
  "friends": [ "Calvin", "Susie" ]
}
```

## A Person Model

A possible simplistic model declaration for this data structure,
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
  "birth": "2018-02-22",
  "friend": []
}
```

Then we can invoke the `jmc -r` command (the option triggers _reporting_ the reason for
validation failures) to validate this value with the person model:

```sh
jmc -r Person-0.model.json moe.json
```
```
moe.json: FAIL (.: unexpected object [.]; .friend: unexpected prop [.])
```

The validation rejects the property at path `.friend` because it is not allowed
by the model, which yields to the conclusion that the object at the root `.` is unexpected.
The JSON path in square brackets `[.]` indicates where in the _model_ the
ruled was found whereas the path before the `:` indicates where in the _value_ it failed.

:+1: For efficiency, the validation stops at the first encountered error which invalidates the
value: if a value includes several root errors, only one is reported, plus
cumulative failures along the path yielding to this error.

## Constraining Strings

Our first model has no constraints on strings, thus also validates file `elysee.json`
which does not represent a person:

```json
{
  "name": "Élysée Palace, 55 rue du Faubourd Saint-Honoré, 75008 Paris, France.",
  "birth": "1722",
  "friends": [ "2", "3", "5", "7", "11" ]
}
```

We can improve our model by constraining strings with regular expressions (between `/.../`)
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

## Using Definitions

The previous model includes a regex which is hard to read and repeated twice.
We can use definitions to enhance readability and reuse structures,
with file `Person-2.model.json`:

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

This model defines 3 named sub-models (in the `$` property), which can be referenced with `"$..."`
in definitions and as the root target type after (`@` property), and also includes a
comment (`#`). `"$DATE"` is predefined to only allow valid ISO-formatted date strings.

Special properties (`# $ @`) are used by JSON Model to extend models beyond simple
type inference. The choice of short symbols avoids confusion with word-based
property names used in typical JSON data structures.

Sentinel characters are used at the beginning of strings to embed special semantics,
such as regular expressions (`/`), references to named models (`$`) or scalar constants
(`_` for strings, `=` for other scalars).

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

## Loosening Objects

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

```sh
jmc Loose.model.json moe.json
```
```
moe.json: PASS
```

:warning: This leads to ignoring typos on optional property names, which is seldom a good idea.

## Having Alternatives

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
      "type": "_Point",
      "data": "$coord"
    },
    {
      "type": "_Segment",
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

## Numbers vs Numbers

JSON actually defines a loose _Number_ type which can hold any floatting point or integer number.
Internally, JavaScript uses `double` for everything.
However, most programming languages differentiate integers from floats.

JSON Model is not linked to the JavaScript ecosystem, thus supports actually distinguishing
integers from floats, but can also be configured to be more tolerant.

In the previous example, we used `-1.0` to represent a floatting point number in a coordinate.
JSON: This definition precludes validating against a strict integer, eg `5432` would be rejected.

Consider the model in file `Town.model.json`, which defines a town objects:

```json
{
  "name": "/^(\\w+ ?)+$/",
  "pop": 1,
  "coord": { "lat": -1.0, "lon": -1.0 }
}
```

The population _must_ be a positive integer, whereas `lat` and `long` coordinates _must_
be floating point numbers, thus for files `beijing.json` and `shanghai.json`:

```json
{ "name": "Beijing", "pop": 21893095, "coord": { "lat": 39.9, "lon": 116.3 } }
```
```json
{ "name": "Shanghai", "pop": 24874000.0, "coord": { "lat": 31, "lon": 121 } }
```

The first one is valid but the second is rejected:

```sh
jmc Town.model.json beijing.json shanghai.json
```
```
beijing.json: PASS
shanghai.json: FAIL (.: unexpected object [.]; .pop: invalid mandatory prop value [.pop]; .pop: not a 1 strict int [.pop])
```

This behavior can be loosen with option `--loose-number`, or by adding a special
`JSON_MODEL_LOOSE_NUMBER` at the root comment.

```sh
jmc --loose-number Town.model.json beijing.json shanghai.json
```
```
beijing.json: PASS
shanghai.json: PASS
```

## Composing Objects

## Playing with Constraints

## Reusing Definitions

## Transformating Models

## Larger Examples

## Preferring YaML or JS.

JSON is convenient for exchanging data between computer programs, especially across languages
and over networks. However, it is not a very friendly format for humans, thus actually typing
JSON models can be quite cumbersome.

In order to aleviate this drawback, this JSON Model implementation allows to use _YAML_  and
_JavaScript_ files, which drop some overheads such as double quotes, braces and commas, and
add comments:

```yaml
# a yaml representation of a person in Person-0.model.yaml
name: ""
birth: "$DATE"
?friends: [ "" ]
```

```js
// a javascript representation of a person in Person-0.model.js
{
  name: "",
  birth: "$DATE",
  "?friends": [ "" ]
}
```

Both these formats are converted to JSON and can be used as JSON Model:

```sh
jmc Person-0.model.yaml hobbes.json moe.json
jmc Person-0.model.js hobbes.json moe.json
```

## Running with C, JS or Python

The JSON Model compiler can generate C, JavaScript or Python validation code, ready to be
imported for checking values.

TODO

## Exporting to JSON Schema

## Importing from JSON Schema

## Conclusion
