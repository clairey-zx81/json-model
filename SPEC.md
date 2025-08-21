# JSON Model Specification v2

JSON Model aims at describying JSON data structures, so in that sense it is a cross-language
JSON-specific type declaration written in JSON or YAML.

Some features go beyond the traditional _structural_ typing of programming language type
declarations, for instance by using constants and regular expressions.

This is a semi-formal specification of JSON Model.

The JSON Model syntax primarily relies on type inference to express types, and
uses symbolic properties (`| ^ & + @ = != < <= > >= ! $ % ~`) and
string sentinel characters (`_ ! ? = . $ /`) for advanced features.

## JSON Summary

[JSON (JavaScript Object Notation)](https://www.json.org/) is a limited-feature
text serialization format linked to the JavaScript ecosystem.
JSON values are built recursively from:

- symbols: `null`, `true`, `false`.
- numbers, mixing integers and floats: _-42_, _3.1415927E00_
- unicode text: `"Hello Susie!"`, with backslash escaping and special character such as `\n`.
- arrays of JSON values: `[ …, … ]`
- objects mapping string properties to JSON values: `{ "foo": …, "bla": … }`

It must be noted that:

- there are no comments.
- there are no cycles or references, a JSON value is only a tree.
- there is no limit set on integer or float precision.
- there is no way to represent _NaN_ and _Infinity_ floats.

By default, JSON Model assumes a 64 bit size for integers and floats.

## Static Type Inference

In a JSON model, the simplest value typically stands for all possible values for that type.

### Scalars

- `null`: JSON value _null_.
- `true`: JSON values _true_ or _false_, a boolean.
- `0`: a non-negative integer, eg _0_ or _42_.
- `1`: a positive integer, eg _1_ or _42_.
- `-1`: any integer, eg _-42_.
- `0.0`: any non-negative float, eg _0.0_, _3.1415729_ or _1E100_.
- `1.0`: any strictly positive float, eg _0.0000001_, _1E-100_, _42.0_.
- `-1.0`: any float, eg _-42.5_.
- `""`: any string.

Moreover, strings can also be specified with a regex:

- `"/regex/options"`: a string matching the regex with some options,
  eg _/^susie$/i_ for an ignore-case _Susie_ string.

And a model can be defined with a name and referenced with `"$name"`.

### Arrays

- `[]`: empty array/tuple.
- `[…]`: an array of any number (possibly 0) of `…` JSON values.
- `[…, …, …]`:  a tuple composed of 3 items, each with a specified type.
   in a tuple or array specification, string starting with `#` are comments and are ignored.

For example:

```json
[
  "# an array of non-negative integers",
  0
]
```

Is the same as JSON model `[ 0 ]`.

### Objects

- `{}`: empty object (no properties).
- `{"…": …, "…": …}`: an object with property specifications.

Property values are the models of the expected associated values.

Property names are matched as follow:

- `"!XXX"`: mandatory properties directly provided after the `!`.
  String constants are _also_ valid mandatory properties.
- `"?XXX"`: optional properties directly provided after the `?`.
- `"/.../"`: optional property names matching a regular expression:
  eg `{"/^a/": ""}` means property names starting with _a_ must have string values.
- `"$XXX"`: optional property reference to a **string** definition.
- `""` catch all property: any property name matches.
- property names starting with other characters are reserved for future uses and must be rejected.

:warning: Named properties **must** be distinct one from the other,
any name collision is an error and must be rejected, eg with
`{ "!a": 0, "_a": 0, "a": 0, "?a": 0}` all 4 property specifications describe
the same `a` property, only one is allowed.

For objects, the evaluation order prioritizes property checks, only the first match is used:
property specifications are **not** cumulative.

1. mandatory/optional properties.
2. regular expression properties.
3. reference properties.
4. catch all property.

The matching search **should** follow the specification order within these classes
if the language JSON representation allows it.
However, a model **should nots** rely on the fact that the specification order is preserved
for its expected semantics.
This allows to direct optimization by putting more likely properties ahead of the check.

### Comment Properties

Property names starting with `#` are comments and **must** be ignored,
together with their arbitrary values (bar type constraints).
They may appear within simple, composition, constraint, definition and transformation
objects eg:

```json
{
  "#": "Return status of an HTTP request",
  "status": 1,
  "message": "",
  "#.eg": [
    { "status": 200, "message": "Ok" },
    { "status": 418, "message": "I'm a teapot" },
    { "status": 451, "message": "Unavailable for Legal Reasons." }
  ],
  "#.md": "# Status Object\n\nUse this for `HTTP` request status."
}
```

Is equivalent to:

```json
{
  "status": 1,
  "message": ""
}
```

The `"#"` single sharp character comment is the _main_ comment, to be interpreted
as the title of the model or submodel. It **must** be a string.
Other comment values are not restricted.

Comments may be interpreted by tools to generate documentations,
and these tools may add further restrictions to their value.
For instance, `"#.md"` may be required to be a valid markdown document,
or `"#.eg"` may be required to be an array of JSON values which _do_ match the model.

## Scalar Constants

Scalar constants are expressed as special strings with a `=` or `_` sentinel character:

### Non-String Scalar Constants

Non-string scalar constants are expressed within strings starting with a `=`:

- `"=null"`: the _null_ value.
- `"=true"`: the _true_ boolean value.
- `"=false"`: the _false_ boolean value.
- `"=-5432"`: the _-5432_ integer value.
- `"=3.1415927E0`: the approximated pi float value.

Any other model string starting with `=` must be treated as errors and rejected.

### String Scalars

- `"_XXX"`: the _XXX_ string constant, where _XXX_ can be anything.
  `"_"` is the empty string, `"_&"` is the ampersand character.
- `"XXX"`: the _XXX_ string constant **if** the first character
  is an identifier character (letter, underline).

Model strings which do not start with `_` (constant), `/` (regex), `$` (reference),
`=` (non-string scalar constants) or _identifier_ characters
must be treated as errors and rejected.

Note that the symbol renaming feature may allow property names starting with a `.`,
which must be translated into the regular symbol before processing.

## Predefined Models

String models with a `$` reference with a capitalized ASCII name are special **predefined** models:

- `"$ANY"`: any JSON value.
- `"$NONE"`: no JSON value.

Simple scalar types:

- `"$NULL"`: _null_ value.
- `"$BOOL"` or `"$BOOLEAN"`: boolean values _true_ or _false_.
- `"$INT"` or `"$INTEGER"`: JSON (unbounded) integer values.
- `"$I8"`, `"$U8"`, `"$I16"`, `"$U16"`, `"$I32"`, `"$U32"`, `"$U32"`, `"$U64$"`:
  signed/unsigned 8/16/32/64-bit integers.
- `"$FLOAT"` or `"$NUMBER"`: JSON (unbounded) float values.
- `"$F16"`, `"$F32"`, `"$F64"`: 16/32/64 bit precision
  [IEEE 754](https://standards.ieee.org/ieee/754/6210/) floats.
- "`$STRING"`: a string.

In addition, the following string predefs are defined:

- `"$URL"` `"$URI"`: a URL or URI
  ([RFC 3986](https://datatracker.ietf.org/doc/html/rfc3986)), eg _https://json-model.org/_.
- `"$UUID"`: a UUID (Universally Unique IDentifier -
  [RFC 9562](https://www.rfc-editor.org/rfc/rfc9562)).
- `"$DATE"`, `"$TIME"` or `"$DATETIME"`:
  a date, time or timestamp ([RFC 3339](https://datatracker.ietf.org/doc/html/rfc3339)).
- `"$EMAIL"`: an email address, eg _susie@json-model.org_.
- `"$JSON"`: a valid JSON value, eg _123_ or _{"Susie": "Derkins"}_.
- `"$REGEX"`: a valid _re2_ regular expression, eg _^[a-z]+$_.
- `"$EXREG"`: an extended regular expression, see below.

Any other all-capital ASCII character (and digit) definition names must be rejected
as they are reserved for possible future predefs (eg Luhn, ISBN, EAI…).

## Composition

An object with special properties `|`, `^`, `&` or `+` (only one of these) is
a composition object.
Comments (properties starting with `#`) are also allowed in a composition object,
plus `$ % ~` if it is the model root.
Any other property is an error and the model must be rejected.

### Or Operator

Property `|` value must be an array of models.
A value matches this model if it matches _any_ model in the list.
If the list is empty, no value matches, thus it is equivalent to `"$NONE"`

### Xor Operator

Property `^` value must be an array of models.
A value matches this model if it matches _one and only one_ model in the list.
If the list is empty, no value matches.

### And Operator

Property `&` value must be an array of models.
A value matches this model if it matches _all_ models in the list.
If the list is empty, any value matches, this it is equivalent to `"$ANY"`

### Merge Operator

Property `+` value must be an array of **object** models, with some further constraints.
A JSON object matches this model if it matches the object defined with the _combined_ properties
of the list of models.

Property combinations are preprocessed as follow:

1. definitions are followed to substitute the corresponding objects and or/xor compositions of
   object models. If one definition is _not_ an object model, this is an error and the model
   is rejected.
2. the `+` operator is distributed over `|` and `^` lists, so that the resulting merge
   involves only or/xor of simple object models.
3. object properties are merged with the following rules:
   - mandatory named properties take priority over optional named properties.
   - regular expression properties, left to right.
   - reference properties, left to right.
   - catch all property.
4. the model values can be merge if and only if they are compatible:
   - they are strictly _equal_ (ignoring comments).
   - or one is the special `"$ANY"` model, in which case the most restrictive is kept.

Incompatible property value models must be treated as errors and rejected.

A merge composition with an empty object list is equivalent to an empty object.

The merge operator can be handled by a preprocessor which outputs a model without merges.

Example:

```json
{ "+": [ {"a": 0}, { "|": [ {"?a": 0}, {"b": true} ] } ] }
```

Is distributed as:

```json
{
  "|": [
    { "+": [ {"a": 0}, {"?a": 0} ] },
    { "+": [ {"a": 0}, {"b": true} ] }
  ]
}
```

Which is merged as:

```json
{ "|": [ {"a": 0} , {"a": 0, "b": true} ] }
```

## Constraints

Constrained models are represented with an object with special propertie names:

- target model: `@`
- comparison constraints: `=`, `!=`, `<`, `<=`, `>`, `>=`
- unique constraint: `!`, the value of which must be a boolean, the target model must be an array.

:warning: when a constrained object is used (i.e. with both `@` and any of the
special constraint properties), the target model **must** be statically type, see
[Static Typing Lattice](#static-typing-lattice) below.

### Null or Boolean Target Model

This is an error and must be rejected.

### Number (integer or float) Target Model

Comparison constraints are allowed only with number values.
The JSON value is valid if the comparisons are valid.

Non number values are errors and must be rejected.

### String Target Model

Comparison constraints are allowed with values either strings or numbers.

- numbers apply to the _length_ of the string.
- strings apply to the _value_ of the string.

The comparison may be locale-dependent, depending on implementation settings.

### Array Target Model

Comparison constraints are allowed with number values, which apply to
the length of the array.

The unique constraint is allowed, _true_ implies that all array elements
must differ.

### Tuple Target Model

If the target model is a tuple (array of several models) with any comparison
constraint, the constraints apply to the length of the tuple which becomes
open-ended, with any number of items of the last model of the array at the
end of the tuple.

For instance:

```json
{
  "@": [ "", true, 0 ],
  ">=": 3,
  "<=": 9
}
```

Corresponds to a tuple with a string as the first element, a boolean
as the second element, followed by 1 to 7 integers.

The unique constraint does not apply to tuple and must be rejected if present.

### Object Target Model

Comparison constraints are allowed with number values, which apply to
the number of properties (size) of the object.

### Target Model Type

- **top**: if the target model is not statically typed, this is an error and must be rejected.
- **bottom**: if the target model is not feasible, constraints are ignored and
  the implementation must report to the user that the submodel is unfeasible.

Implementations may choose to manage constraints dynamically, but the static typing constraints
applies.

## Root Special Keywords

Additional one-letter symbols can _only_ appear at the root of a JSON model:

- `~`: introduces a URL to the meta-model of this model.
- `$`: introduces new definitions in the file scope, as an object.
- `%`: introduces an object with model transformations.

These 3 symbols can only appear in the root model.

## Definitions and Scope

A `"$"` property at the root of the model allow to define named models and their
associated values. These definition are available for this model, but may be referenced
from other models, see next section.

For instance:

```json
{
  "$": { "entier": -1, "mot": "/^\\w+$/" }
}
```

defines `"$entier"` as a synonym for integers, and `"$mot"` as a string matching the regex.

Definitions allow recursivity.
Names are restricted to simple identifiers (letters, numbers, underline, dash).

The special empty string `""` name allows to declare the URL-identifier of the model itself.

Beware that all-capital ASCII identifiers are reserved for predefs.

## References and Imports

A reference is a string which begins with the `$` character.

- `"$name"` refers to a local definition named `name`, as discussed in the previous section.
- `"$some-url"` refers to the root of the external model retrieved at this url, which can be
  a local path.
  For instance, `"$https://json-model.org/models/json-model"` is JSON Model self-validating
  meta model.
- by extension, `"$#name"` refers to the local definition `name` within the current scope
  (empty name).
- `"$some-url#name` refers to the model named `name` inside the url-reference model.
- `"$some-url#n1#n2" allows to follow external definitions: inside the first target
  url, retrieve name `n1` model which is itself defined as another external definitions,
  then retrieve name `n2` into this secondary model.

## Regular Expressions

### RE2

Regular expressions should be restricted to efficient regex such as `re2`.
However, depending on the availibility of such regular expression engine on the target
language, other variant may be used which should support at least the re2 subset.

### Extended Regular Expressions

Regular expressions are extended with option `X` (capital letter x) to allow references
to string models with the following syntax: `($name:regex)`, where the regular expression
after the `:` must match the named string model. `($name)` is a shortcut for `($name:.\*).

## Model Transformations

Symbol `%` at the root of the model defines a model transformation object, which
may include symbol renamings, model importations and model editions.

### Symbol Names

Within the `%` object at the root,
properties begining with a `.` introduce new symbol names.
The value is the symbol string which is replaced.
For instance:

```json
{
  "%": { ".or": "|", ".merge": "+" }
}
```

Declares property substitutions, which translate this model:

```json
{ ".merge" [ ".or": [ {"a": 0}, {"b": 0} ] }
```

Into:

```json
{ "+" [ "|": [ {"a": 0}, {"b": 0} ] }
```

These substitutions can be carried out by a separate preprocessor which generates
the resulting standard model without any `".xxx"` symbols.

When declaring the model meta-model with `"~"` at the root, any renaming specified
in the meta-model **must** be applied to the current model before further processing.

### Importation

Special property "<" inside a transformation object expect an external reference string value,
or a list of such references, and imports all definitions of the targets into the local
scope.

While importing, homonymous definitions are invalid and must be rejected.

### Model Addition and Edition

Model editions are specified with properties which are references possibly followed
by a JSON path, allowing to point to a JSON element in the model, and either a value
with special properties `/ *` to remove or add sub elements, or anything else
taken as-is, but which must not be an object with any of the special properties.

- Addition/replacement on a `"$External#name"` reference to a definition:
  - a non-existing definition is added to available definitions _in the target scope_.
  - an existing definition is replaced _in the target scope_.
- Edition on a `"$External#name.foo.0"`: the target element **must** exist.
  The `.foo.0` path instructs to select in first element of the array value of property foo
  inside definition `name`.

The following edition rules apply, in order, depending on the type of the target element:

- if the transformation value is an edition object (ie include at least one `/ ~ *` property):
  - if the target is a JSON object (not necessarily a model for an object):
    - `/` value may be a string or a list of strings.
      All properties of these names are removed.
      If a property does not exist, this is an error and must be rejected.
    - `*` value must be a object, which is merged into the target object.
      If a property already exists, this is an error and must be rejected.
  - if the target is a JSON array (not necessarily a model for an array):
    - `/`: may be value or a list of values.
      Array items equal to these values are removed.
      If a value is not found, this is an error and must be rejected.
    - `*`: if the value is an array, append its items to the target array.
      if the value is something else, appends this to the array.
  - if the target is a JSON scalar: this is an error and must be rejected.
- if the transformation value is a model (i.e. an object without any `/ ~ *` property),
  the target value is _replaced_ by this value, in place.

For instance,

```json
{
  "$": {
    "#": "the root model of JSON Model meta-model",
    "Model": "$https://json-model.org/models/json-model"
  },
  "%": {
    "#": "add or replace Comments definition in the target model",
    "$Model#Comments": { "?#": "", "/^#.+/": "$ANY" }
  }
}
```

These additions and editions are performed _after_ property renamings and imports,
and _before_ merge pre-processing.

## Static Typing Lattice

In the above specification, there are several requirements for having _one_ known type
for a model:

- merge operands are simple objects or or/xor-op of objects (recursively).
- properties defined using a reference must be strings.
- constrained targets must have a known type.

This typing lattice is based on the following 3-level latice:

- $\top$ (top) is `"$ANY"`
- defined types are: `null`, `bool`, `number` (int or float), `string`, `array`, `object`.
- $\perp$ (bottom) is `"$NONE"`, i.e. no possible value.

All model elements are typed with the following rules:

- _null_,  _"$NULL"_ and _"=null"_ are `null`.
- _true_, _"$BOOL"_, _"$BOOLEAN"_, _"=true"_ and _"=false"_ are `bool`.
- integer/number definitions, constants and predefs are `number`.
- _""_, _"/regex/"_, _"$STRING"_, string constants, other predefs are `string`.
- array and tuple models are `array`.
- simple object models are `object`.

They are then propagated along definitions and composition objects:

- definitions are typed as their values,
  and references are typed as the corresponding definition
- or (`|`), xor (`^`) operators:
  - if all listed models have the **same** type, the composition has this type.
  - if composed models have different types, the type is _top_.
  - if the list of models is empty, the type is _bottom_.
- and (`&`) operator:
  - if all models have the **same** type, the composition has this type.
  - if composed models have different types, the type is _bottom_.
  - if the list is empty, the type is _top_.
- merge (`+`) operator has type `object`.
- constraint with a target (`@`) are types as the target.

Fixed point: in case of unresolved recursion, assume _top_.

## Comments

- not.
- ...

## Self-Validating Meta-Model

JSON Model meta-model is available [here](https://json-model.org/models/json-model).

## Unfeasible models

- statically unfeasible constraints

  ```json
  {
    "#": "a JSON value cannot be both a string and an integer",
    "&": [ "", 0 ]
  }
  ```

- dynamically unfeasible constraints (without knowledge of regex semantics)"

  ```json
  {
    "#": "a string cannot both starts with `a` and `b`",
    "&": [ "/^a/", "/^b/" ]
  }
  ```

- feasible vs unfeasible recursions

  ```json
  {
    "$": {
      "#.x": "this is feasible because the array may be empty",
      "x": [ "$x" ],
      "#.y": "this is feasible because the property is optional",
      "y": { "?y": "$y" },
      "#.z": "the mandatory prop means that no finite value can satisfy this model",
      "z": { "!z": "$z" },
    }
  }
  ```

## Changes

### Future directions

- discuss other transformations? mv/cp?
- expand constrained models?

### From JSON Model v1 to v2.

- add `"%"` transformations.
- add special `""` definition for providing the model URL.
- require statically typed targets for constraints.
- extend property comments to starting with `#`.
- add array/tuple comments.

### From JSON Model v0 to v1.

- remove `"$"` property as a arbitrary naming anywhere in the model tree.
- use `"$"` instead of `"%"` for definitions.
- restrict definitions to be at the root of the model.

## References

JSON Model design is presented in research papers and reports:

- JSON Model: a Lightweight Featureful DSL for JSON.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/817/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-817.pdf),
  Mines Paris - PSL, April 2024

  JSON Model version 1.

- An Analysis of Defects in Public JSON Schemas.
  Claire Yannou-Medrala and Fabien Coelho.  
  In BDA 2023, 39ème conférence sur la gestion de données - Principes, technologies et applications.
  Also TR [A/794/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-794.pdf),
  Mines Paris - PSL, October 2023

  Brief introduction to version 0 at the end of the paper.

- JSON Model: a Lightweight Featureful Description Language for JSON Data Structures.
  Fabien Coelho and Claire Yannou-Medrala.  
  Technical Report [A/795/CRI](https://www.cri.minesparis.psl.eu/classement/doc/A-795.pdf),
  Mines Paris - PSL, May 2023

  JSON Model version 0.
