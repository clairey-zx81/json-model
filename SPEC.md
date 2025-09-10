# JSON Model Specification v2

JSON Model aims at describing JSON data structures:
it is a cross-language JSON-specific type declaration written in JSON.
Some features go beyond the traditional _structural_ typing of programming language type
declarations, for instance by using constants and regular expressions.

## JSON Summary

[JSON (JavaScript Object Notation)](https://www.json.org/) is a limited-feature
text serialization format linked to the JavaScript ecosystem.
JSON values are built recursively from:

- symbols: `null`, `true`, `false`.
- numbers, mixing integers and floats: `-42`, `31.415927E-1`
- unicode text within `"`: `"Hello Susie!"`, with backslash escaping and special character such as `\n`.
- arrays of JSON values: `[ …, … ]`
- objects mapping string properties to JSON values: `{ "foo": …, "bla": … }`

For instance the following JSON object describe a comics character, his birth date and
list its friends:

```json
{
  "name": "Hobbes",
  "birth": "2020-07-29",
  "friends": [ "Calvin", "Susie" ]
}
```

It must be noted that:

- there are no comments/meta data.
- there are no cycles or references, a JSON value is only a tree.
- there is no limit set on integer or float precisions.
- there is no way to represent _NaN_ and _Infinity_ floats.

## JSON Model Syntax

This is a semi-formal specification of JSON Model.

The JSON Model syntax uses JSON to describe JSON.
It primilarily relies on type inference to express types, and
uses symbolic properties (`| ^ & + @ = != < <= > >= ! $ % ~`) and
string sentinel characters (`! ? = _ . $ /`) for advanced features.
Some symbols can _only_ appear at the root of a JSON model `~ $ %`.

JSON Model represents set of JSON values by providing a type declaration which
constraint the allowed values.
A model contains both JSON parts which must conform to the model syntax (the type declarations)
and JSON parts which may be values (eg examples of allowed values, as documentation illustrations
included in the model definition).

JSON model relies on type inference for typing, so that the simplest value typically stands
for all possible values for that type.

## Scalar Models

- **Scalar Type Inference**

  Relying on type inference, the following scalar models allow to declare scalar types:

  - `null`: JSON value _null_.
  - `true`: JSON values _true_ or _false_, a boolean.
  - `0`: a non-negative integer, eg _0_ or _42_.
  - `1`: a positive integer, eg _1_ or _42_.
  - `-1`: any integer, eg _-42_.
  - `0.0`: any non-negative float, eg _0.0_, _3.1415729_ or _1E100_.
  - `1.0`: any strictly positive float, eg _0.0000001_, _1E-100_, _42.0_.
  - `-1.0`: any float, eg _-42.5_.
  - `""`: any string.

  By default, JSON Model assumes a 64 bit size for integers and floats.

- **Scalar Constant Models**

  Non-string scalar constants are expressed with strings using sentinel `=`:

  - `"=null"`: the _null_ value.
  - `"=true"`: the _true_ boolean value.
  - `"=false"`: the _false_ boolean value.
  - `"=-5432"`: the _-5432_ integer value.
  - `"=3.1415927E0`: the approximated pi float value.

  Any other model strings starting with `=` must be treated as errors and rejected.

  String scalar constant are expressed with strings using sentinel `_`:

  - `"_XXX"`: the _XXX_ string constant, where _XXX_ can be anything.
    `"_"` is the empty string, `"_&"` is the ampersand character, `"_#"` is the sharp character.
  - as a convenience, `"XXX"`: the _XXX_ string constant **if** the first character
    is an identifier character, i.e. a letter of some sort.

- **Regular Expression String Models**

  Regular expression are specified in string with the `/` sentinel: `"/regex/options"`
  are the strings which match the _regex_ under the provided _options_.
  For instance, `"/^susie$/i"` matches ignore-case _Susie_ strings.

  - regular expressions should be restricted to efficient regex such as
    [RE2](https://github.com/google/re2).
    However, depending on the availibility of such regular expression engine on the target
    environment, other variant may be used which should support at least the RE2 subset.
    For portability, models should only rely on regex features available in the RE2 subset.

  - JSON Model regular expressions are extended with option `X` (capital letter x) to allow
    _references_ to string models with the following syntax: `($name:regex)`, where the regular
    expression after the `:` must match the named string model.
    Syntax `($name)` is a shortcut for `($name:.*)`.

- **Predefined Models**

  String models starting with a `$` reference using capitalized ASCII names are
  special **predefined** models, which may have any type:

  - `"$ANY"`: any JSON value (scalar or array or object).
  - `"$NONE"`: no JSON value.

  Simple scalar types:

  - `"$NULL"`: _null_ value.
  - `"$BOOL"` or `"$BOOLEAN"`: boolean values _true_ or _false_.
  - `"$INT"` or `"$INTEGER"`: JSON (unbounded) integer values.
  - `"$I8"`, `"$U8"`, `"$I16"`, `"$U16"`, `"$I32"`, `"$U32"`, `"$I64"`, `"$U64"`:
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
  - `"$REGEX"`: a valid regular expression, eg _^[a-z]+$_.
  - `"$EXREG"`: an extended regular expression.

  Any other all-capital ASCII character and digit names must be rejected as they
  are reserved for possible future predefs (eg URN, Luhn, ISBN, ISSN, EAN, DOI…).

  Model strings which do not start with `_` (constant), `/` (regex), `$` (reference),
  `=` (non-string scalar constants) or _identifier_ characters
  must be treated as errors and rejected.

  Note that the [symbol renaming feature](#symbol-names) may allow property names starting
  with a `.`, which must be translated into the regular symbol before proceeding.
  Extension to JSON Model which require new symbols should use a `.…` syntax for these,
  as other symbols are reserved for future standard uses.

## Array and Tuple Models

The model for an array or tuple is a JSON array.

- `[]`: empty array/tuple.
- `[…]`: an array of any number (possibly 0) of `…` JSON values.
- `[…, …, …]`:  a tuple composed of 3 items, each with a specified model.
- In a tuple or array specification, strings starting with `#` are comments and are ignored.

For example:

```json
[
  "# an array of non-negative integers",
  0
]
```

Is the same as JSON model `[ 0 ]`.

## Simple Object Model

- `{}`: empty object (no properties).
- `{"…": …, "…": …}`: an object with property specifications.

Property values are the models of the expected values associated to the property.

Property names are matched as follow:

- `"!XXX"`: mandatory properties directly provided after the `!`.
- as a convenience, string constants (eg `_XXX` or `Zzz` with the first character a letter)
  are also valid mandatory properties.
- `"?XXX"`: optional properties directly provided after the `?`.
- `"/.../"`: optional property names matching a regular expression:
  eg `{"/^a/": ""}` means property names starting with _a_ must have string values.
- `"$XXX"`: optional property reference to a **string** [definition](#definitions-and-scope).
- `""` catch all property: any property name matches.
  This is consistent with `""` standing for any string.
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
This allows to hint optimization by putting more likely properties ahead of the check.

## Model Comment Properties

In a model, property names starting with `#` are comments and **must** be ignored,
together with their arbitrary values.
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

## Composition Models

A model object with special properties `|`, `^`, `&` or `+` (only one of these) is
a composition object.
Comments (properties starting with `#`) are also allowed in a composition object,
plus `$ % ~` if it is the model root.
Any other property is an error and the model must be rejected.

- **Or Operator Model**

  Property `|` value must be an array of models.
  A value matches this model if it matches _any_ model in the list.
  If the list is empty, no value matches, thus it is equivalent to `"$NONE"`.

- **Xor Operator Model**

  Property `^` value must be an array of models.
  A value matches this model if it matches _one and only one_ model in the list.
  If the list is empty, no value matches.

- **And Operator Model**

  Property `&` value must be an array of models.
  A value matches this model if it matches _all_ models in the list.
  If the list is empty, any value matches, thus it is equivalent to `"$ANY"`.

- **Merge Operator Model**

  Property `+` value must be an array of **object** models, with some further constraints.
  A JSON object matches this model if it matches the object defined with the _combined_ properties
  of the list of models.

  Property combinations are preprocessed as follow:

  1. definitions are followed to substitute the corresponding simple objects and or/xor compositions
     of object models (recursively).
     If one definition is _not_ an object model, this is an error and must be rejected.
  2. the `+` operator is distributed over `|` and `^` lists, so that the resulting merge
     involves only or/xor of **simple** object models.
  3. object properties are merged with the following rules:
     - mandatory named properties take priority over optional named properties.
     - regular expression properties, left to right.
     - reference properties, left to right.
     - catch all property.
  4. the model values can be merge if and only if they are compatible:
     - they are _equal_ (ignoring comments and property ordering), or
     - one is the special `"$ANY"` model, in which case the other model is kept.

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

  Note that merge proprocessing conditions are stricter than the
  [typing lattice](#static-typing-lattice).

## Constraint Models

Constraint models are represented as an object with special property names:

- mandatory target model: `@`
- optional comparison constraints: `=`, `!=`, `<`, `<=`, `>`, `>=`
- optional unique constraint: `!`, the value of which must be a boolean.

A constraint model may or may not include optional constraints.
A constraint model without actual constraints (no optional constraint)
is called a _unconstrained constraint model_ or _unconstrained model_ for short.
Similarily, a constraint model with actual constraints is called a _constrained model_.

Unconstrained models are unrestricted, the `@` model indirection can just be seen as a
syntactic commodity for allowing comments, or definitions at the model root.

However, when a constrained object is used (i.e. with both `@` and any of the
special constraint properties), the target model **must** be
[statically type](#static-typing-lattice).
The interpretation of the constraint depend on the target type:

- **Null or Boolean Target**

  This is an error and must be rejected.

- **Number Target**

  Comparison constraints are allowed only with number values.
  The JSON value is valid if the comparisons are valid.

  Non number values are errors and must be rejected.

- **String Target**

  Comparison constraints are allowed with values either strings or numbers.

  - numbers apply to the _length_ of the string.
  - strings apply to the _value_ of the string.

  The comparison may be locale-dependent, depending on implementation settings.

- **Array Target**

  Comparison constraints are allowed with number values, which apply to
  the length of the array.

  The unique constraint is allowed, _true_ implies that all array elements
  must differ.

- **Tuple Target**

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

  The unique constraint does not apply to tuples and must be rejected if present.

- **Object Target**

  Comparison constraints are allowed with number values, which apply to
  the number of properties (size) of the object.

## Definitions and References

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
Names are restricted to simple identifiers (letters, numbers, underline, dash…).
Beware that all-capital ASCII identifiers are reserved for predefs.

The special empty string `""` property allows to declare the URL-identifier of the
model itself.

A reference is a string which begins with the `$` character.

- `"$name"` refers to a local definition named `name`, as discussed in the previous section.
- `"$some-url"` refers to the root of the external model retrieved at this url, which can be
  a local path.
  For instance, `"$https://json-model.org/models/json-model"` is JSON Model self-validating
  latest meta model; `"$./stuff"` is a JSON model file in the current directory.
  Loading an external model must take care of suffixes such as `.model.json` or `.json`.
- by extension, `"$#name"` refers to the local definition `name` within the current scope
  (empty name).
- `"$some-url#name` refers to the model named `name` inside the url-referenced model.
- `"$some-url#n1#n2"` allows to follow external definitions: inside the first target
  url, retrieve name `n1` model which is itself defined as another external definitions,
  then retrieve name `n2` into this secondary model.

Implementation should detect external reference cycles which are errors and should be rejected.

## (Experimental) Model Transformations

Symbol `%` at the root of the model defines a model transformation object, which
may include symbol renamings, model importations and model editions.

- **Symbol Names**

  Within the `%` object at the root, properties beginning with a `.` introduce new symbol names.
  The value is the symbol string which is replaced, in `# ~ $ % @ = != <= < >= > ! | ^ & + / *`.
  For instance:

  ```json
  {
    "%": { ".com": "#", ".or": "|", ".merge": "+" }
  }
  ```

  Declares property substitutions, which translate this model:

  ```json
  { ".merge": [ {"a": 0}, {".or": [ {"b": 0}, {"c": 0} ] } ] }
  ```

  Into:

  ```json
  { "+": [ {"a": 0}, {"|": [ {"b": 0}, {"c": 0} ] } ] }
  ```

  These substitutions can be carried out by a separate preprocessor which generates
  the resulting standard model without any renamed symbol.

  When declaring the model meta-model with `"~"` at the root, any renaming section specified
  in the meta-model **must** be applied to the current model before further processing.
  This feature allow the localization of the model syntax.

- **Importation**

  Special property `"<"` inside a transformation object expects a reference to an external
  model, or a list of such references, and imports all definitions of the targets into the
  local scope.

  While importing, homonymous definitions are invalid and must be rejected.

- **Model Addition and Edition**

  Model editions are specified with properties which are references possibly followed
  by a JSON path, allowing to point to a JSON element in the model, and either a value
  with special properties `/ *` to remove or add sub elements, or anything else
  taken as-is, but which must not be an object with any of the special properties.

  - Addition/replacement on a `"$External#name"` reference to a definition:
    - a non-existing definition is added to available definitions _in the target scope_.
    - an existing definition is replaced _in the target scope_.
  - Edition on a `"$External#name.foo.0"`: the target element **must** exist.
    The `.foo.0` path instructs to select the first element (index _0_) of
    the array value of property _foo_ inside definition _name_.

  The following edition rules apply, in order, depending on the type of the target element:

  - if the transformation value is an edition object (ie include at least one `/ *` property):
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
  - if the transformation value is a model (i.e. an object without any `/ *` property),
    the target value is _replaced_ by this value, in place.

  These additions and editions are performed _after_ property renamings and imports,
  and _before_ merge pre-processing.

What is the _right_ balance between features, syntax and ease-of-use for a type transformation
language is an on-going investigation: should it allow renaming, moving or copying attributes?
Should it allow to remove definitions? Should imports allow to define a namespace?

## Static Typing Lattice

In the above specification, there are several requirements for having _one_ known type
for a model:

- models referenced by extended regular expressions, which must be strings.
- properties defined using a reference which must be strings.
- merge (`+`) operands are simple objects or or/xor-op of objects (recursively).
- constrained model targets to allow interpreting the constraint.

```json
{
  "events": [ "/^($DATE:[-0-9]+): /" ],
  "$tagname": { "+": [ "$common", "$tagprops" ] },
  "authors": { "@": [ "" ], ">=": 1 }
}
```

The typing lattice is based on the following 3-level latice:

- ⊤ (top) is `"$ANY"`, i.e. any JSON is allowed, the type is unknown.
- 6 JSON types: `null`, `bool`, `number` (int or float), `string`, `array`, `object`.
- ⊥ (bottom) is `"$NONE"`, i.e. no JSON value.

All _model_ elements are typed with the following rules:

- _null_,  _"$NULL"_ and _"=null"_ are `null`.
- _true_, _"$BOOL"_, _"$BOOLEAN"_, _"=true"_ and _"=false"_ are `bool`.
- integer/number definitions, constants and predefs are `number`.
- _""_, _"/regex/"_, _"$STRING"_, string constants, other predefs are `string`.
- array and tuple models are `array`.
- simple object models are `object`.

They are then propagated along definitions and composition objects:

- references are typed as the corresponding definition
- or (`|`), xor (`^`) operators:
  - if the list of models is empty or only contains ⊥, the type is ⊥.
  - if all non-⊥ listed models have the same JSON type, the composition has this type,
  - otherwise the type is ⊤.
- and (`&`) operator:
  - if the list of models is empty or only contains ⊤, the type is ⊤.
  - if all non-⊤ models have the **same** type, the composition has this type,
  - otherwise the type is ⊥.
- merge (`+`) operators have type `object`, if merging succeeds.
- constraint objects (`@`) have the same type as their target.

Fixed point: in case of unresolved recursion, do not bother and assume ⊤,
i.e. the type is unknown.

:warning: Note that for a simplistic recursive descending implementation, care must be taken
to detect infinite reference loops.

:warning: Merge operands are managed in a preprocessing phase with specific rules.
Having them typed as `object` is not a sufficient to assume that the merge would succeed.

## Comments

- although there is no _not_ model operator, this can be semantically expressed with
  _xor_ of _any_ and some model, which matches only if the tested model does not match the
  xored model:

  ```json
  {
    "#": "this matches any JSON which is not a natural integer",
    "^": [ "$ANY", 0 ]
  }
  ```

- extensions relying on comment properties **must not** change the model semantics.
  New model semantics may be added through new keywords (preferably symbols) or predefs.
  The model transformation syntax allows to build a new meta-model for an extended syntax
  quite simply.

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
      "#.µ": "indirect fix point",
      "µ": { "|": [ "$µ", "" ] },
      "#.d": "direct unspecified fix point type",
      "d": "$d"
    }
  }
  ```

## Changes

- **Future directions**

  - discuss other transformations? mv/cp?
    eg promote an optional prop to mandatory, or the reverse?
  - expand constrained models?
  - what predefs should be relevant to typical use cases?

- **From JSON Model v1 to v2**

  - add `"%"` transformations.
  - add special `""` definition for providing the model URL.
  - require statically typed targets for constraints.
  - extend property comments to starting with `#`.
  - add array/tuple comments.

- **From JSON Model v0 to v1**

  - remove `"$"` property as a arbitrary naming anywhere in the model tree.
  - use `"$"` instead of `"%"` for definitions.
  - restrict definitions to be at the root of the model.

## References

JSON Model design is presented in [research papers and reports](PUBS#research-papers).
