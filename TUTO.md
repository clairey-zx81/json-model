# JSON Model Tutorial

[JSON Model](https://json-model.org/) is a JSON language to describe JSON data
structures. Its objective is similar to [JSON Schema](https://json-schema.org/),
but with a user-friendly, compact and intuitive syntax which relies on type
inference, so that simple objects are typically described with sample values.

This tutorial aims at learning briefly the JSON Model syntax and how to use
the [`jmc` command](jmc.md) for validating values directly.
For integrating JSON Model in a project, see [HowTo](HOWTO.md).

## Installing JSON Model Compiler

First, let us create a directory for playing with the compiler:

```sh
mkdir json-model-tutorial
cd json-model-tutorial
```

Running the compiler to generate source code and validate values with the Python backend
only requires a Python virtual environment.
However, running other generated codes requires a few dependencies which are less easy
to install and may not be readily available on some platforms.

To simplify handling these dependencies, we provide an Ubuntu-based **Docker image**
(next subsection), but it is also possible to proceed with installing the
**Python venv** (following subsection) and possibly additional system packages when needed.

Both environments work for most of the tutorial sections below, so feel free to choose whichever
seems more familiar. The docker image include the necessary environment run directly generated
C, Python, JS, Perl and Java codes, which explains its size.
Running the PL/pgSQL code requires a working Postgres server, which is _not_ discussed here.

### Docker Image Installation

For the wary user, download and start the `zx80/jmc` docker image, from your docker
desktop client or from a terminal:

```sh
docker pull zx80/jmc:latest
docker run --name awesome_jmc --user $UID:$GID -v .:/app/workspace --rm -it --entrypoint /bin/bash zx80/jmc
```

This should give your a shell prompt open in the current directory with your permissions.
Check that the `jmc` command is available and works:

```sh
# inside the docker shell
jmc --version  # show version
jmc --man      # show manual page
```

Type `exit` when you want to stop playing with the application.

### Python Virtual Environment Installation

For the advanced user, create a Python virtual environment with the JSON Model Compiler
and JSON Schema Utils (for JSON Schema importations).
In a Linux, MacOS or Windows with WSL terminal, install the latest version with:

```sh
python -m venv venv
source venv/bin/activate
# released versions:
pip install json-model-compiler json-schema-utils
# OR from sources:
# pip install git+https://github.com/clairey-zx81/json-model.git
# pip install git+https://github.com/zx80/json-schema-utils.git
```

Check that the `jmc` command is available and works:

```sh
jmc --version  # show version
jmc --man      # show manual page
```

Add the example values and models discussed below in this directory for testing,
with the available terminal editor (`nano`, `vi`) in the Docker or with any available
editor on the host system.

## JSON – JavaScript Object Notation

[JSON](https://www.json.org/) is a simple text serialization format to represent structured
values involving scalars, arrays and objects.

- **scalars**: `null`, `true`, `false`, integers or floats (collectively named _number_ in JSON),
  and double-quoted utf-8 strings.
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

## Modelling a Person

A possible simplistic model declaration for this data structure,
in file `Person-0.model.json`, is:

```json
{
  "#": "Initial basic model for a person",
  "name": "",
  "birth": "",
  "?friends": [ "" ]
}
```

Object property names are directly mapped to simple values: `""` stands for any string
and `[ "" ]` an array of any number of strings, thanks to type inference.
The `?` sentinel character in the `"?friends"` property name indicates an _optional_ property,
whereas other properties are _mandatory_ by default.
Property `"#"` introduces a comment.

Let us check that our initial value matches the model by invoking the `jmc` command:

```sh
jmc Person-0.model.json hobbes.json
```
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

Let us invoke the `jmc -r` command (the option triggers _reporting_ the reason for
validation failures) to validate this value with the person model (the `.model.json` suffix
is added automatically):

```sh
jmc -r Person-0 moe.json
# moe.json: FAIL (.: unexpected object [.]; .friend: unexpected prop [.])
```

The validation rejects the property at path `.friend` because it is not allowed
by the model, which yields to the conclusion that the object at the root `.` is unexpected.
The JSON path in square brackets `[.]` indicates where in the _model_ the
rule was found whereas the path before the `:` indicates where in the _value_ it failed.

:+1: For efficiency, the validation stops at the first encountered error which invalidates the
value: if a value includes several errors, only one is reported, plus cumulative failures along
the path yielding to this error and invalidating the whole value.

## Constraining Strings

Our first model has no string constraints, thus also validates file `elysee.json`
which does not represent a person:

```json
{
  "name": "Élysée Palace, 55 rue du Faubourg Saint-Honoré, 75008 Paris, France.",
  "birth": "1722",
  "friends": [ "2", "3", "5", "7", "11" ]
}
```

We can improve our model by constraining strings with regular expressions (between `/.../`)
and predefined types (`$...`), in file `Person-1.model.json`:

```json
{
  "#": "Improved model for a person, with regex and predefs",
  "name": "/^\\w+([-' ]\\w+)*$/",
  "birth": "$DATE",
  "?friends": [ "/\\w+([-' ]\\w+)*$/" ]
}
```

The model is strict enough to invalidate this value:

```sh
jmc Person-0 elysee.json  # PASS
jmc Person-1 elysee.json  # FAIL
```

Note: the regex enthousiast may consider replacing `\w` with `\p{L}\p{M}*` (letters with marks).

## Using Definitions

The previous model includes a regex which is hard to read and repeated twice.
We can use definitions to enhance readability and reuse structures,
with file `Person-2.model.json`:

```json
{
  "#": "Model for a Person, with definitions and references",
  "$": {
    "Name": "/^\\w+([-' ]\\w+)*$/",
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

This model defines 3 named sub-models (as a map inside the `$` property value), which can be
referenced with `"$..."` in definitions and as the root target type after (`@` property), and also
includes a comment (`#`). `"$DATE"` is predefined to only allow valid ISO-formatted date strings.

Symbol properties (`# $ @`) are used by JSON Model to extend models beyond simple
type inference. The choice of short symbols avoids confusion with word-based
property names found in typical JSON data structures.

Sentinel characters are used at the beginning of strings to embed special semantics,
such as regular expressions (`/`), references to named models (`$`) or scalar constants
(`_` for strings, `=` for other scalars).

The `jmc` command allows to validate a value against a particular definition of a model,
for instance with file `pi.json`:

```json
3.141592653589793238462643
```

We can check that its content conforms to PI definition inside the `Person-2` model:

```sh
jmc --name PI Person-2 pi.json  # PASS
```

## Reusing Definitions

A common use case is to define some data structure and to reuse them in other
related settings, much like one would _import_ a module or _include_ a header file.
JSON Model allows definitions to be local or remote URLs so as to fetch and reuse
external models easily.

Let us write file `Class.model.json` which reuses `Person-2.model.json` by loading
it as a file (`$./Person-2`) for defining the class name and array of students:

```json
{
  "#": "Import Person to define a model for a class",
  "$": { "pv2": "$./Person-2" },
  "name": "$pv2#Name",
  "students": [ "$pv2#Person" ]
}
```

Then value file `cm1.json`:

```json
{
  "name": "Cours moyen un",
  "students": [
    { "name": "Susie", "birth": "2016-10-14" },
    { "name": "Calvin", "birth": "2016-03-20" }
  ]
}
```

Validates:

```sh
jmc Class cm1.json  # PASS
```

## Loosening Objects

People coming to JSON formatted data from strongly typed programming languages and relational
databases often like strict types to detect potential errors as soon as possible.
People coming to JSON from web application programming with weakly typed languages such as
JavaScript or PHP and loose document-based storage such as MongoDB may prefer loose data
structures which allow to add new properties silently.

There is no way to please everybody. Prioritizing data safety, JSON models are strict (closed)
by default, but can be easily extended to allow unknown properties with a special empty
string property, which is consistent with `""` representing _any_ string.
Hence, with file `Loose.model.json`:

```json
{
  "#": "Loosened model for a person",
  "$": { "Name": "/^\\w+([-' ]\\w+)*$/" },
  "name": "$Name",
  "birth": "$DATE",
  "?friends": [ "$Name" ],
  "": "$ANY"
}
```

The model is loosened to accept a person extended with unspecified properties having _any_ value.
However, this model silently ignores the property name typo in file `moe.json`
because it is covered by the catch-all property:

```sh
jmc Loose moe.json  # PASS
```

:warning: This leads to ignoring typos on optional property names, which is seldom a good idea.

## Having Alternatives

A common pattern is to allow several kind of object as some point in the data structure,
aka a _union_.
This can be expressed with a model involving either the special `^` (xor, one-of) or `|`
(or, any-of) property with an array of possible models.

Let us consider the model in file `Geom.model.json`, which defines a coordinate (`coord`) as
a pair of numbers, and use it for point and segment objects:

```json
{
  "#": "Geometrical Model",
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

In this model, the xor (`^`) alternative could be simplified to a or (`|`)
because the `type` discriminant ensure that there is no ambiguity.
The model matches both files `marseille.json` and `seoul-tokyo.json`:

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
jmc Geom marseille.json seoul-tokyo.json  # PASS, PASS
```

When defining such unions, it is much better to include a discriminant property (here `type`)
with distinct scalar constant values (here strings):
The JSON Model compiler uses this to generate efficient code which only checks
for the relevant object based on the discriminant.

## Numbers vs Numbers

JSON only defines a loose _Number_ type which can hold any floating point or integer value.
Internally, JavaScript uses `double` for everything.
However, most programming languages differentiate integers from floats.
JSON Model is not linked to the JavaScript ecosystem, thus supports actually distinguishing
integers from floats, but can also be configured to be more tolerant.

In the previous example, we used `-1.0` to represent a floating point number in a coordinate.
This definition precludes validating against a strict integer, eg `5432` would be rejected.
Let us consider the model in file `Town.model.json`, which defines a town objects:

```json
{
  "#": "Town Model",
  "name": "/^\\w+([-' ]\\w+)*$/",
  "pop": 1,
  "coord": { "lat": -1.0, "lon": -1.0 }
}
```

Attribute `pop` _must_ be a positive integer, whereas `lat` and `lon` coordinates _must_
be floating point numbers, thus for files `beijing.json` and `shanghai.json`:

```json
{ "name": "Beijing", "pop": 21893095, "coord": { "lat": 39.9, "lon": 116.3 } }
```
```json
{ "name": "Shanghai", "pop": 24874000.0, "coord": { "lat": 31, "lon": 121 } }
```

The first one is valid but the second is rejected:

```sh
jmc -r Town beijing.json shanghai.json
# beijing.json: PASS
# shanghai.json: FAIL (.: unexpected object [.]; .pop: invalid mandatory prop value [.pop]; .pop: not a 1 strict int [.pop])
```

This behavior can be loosen with option `--loose`, or by adding a special
`JSON_MODEL_LOOSE_NUMBER` at the root comment.

```sh
jmc --loose Town beijing.json shanghai.json  # PASS, PASS
```

## Composing Objects

When building large JSON data structures a common use case is to combine object definitions,
much like inheritance in programming languages.

Let us use the _merge_ (`+`) operator to compose objects with different set of properties,
in file `University.model.json`, with students and faculties which are both persons:

```json
{
  "#": "People at the University",
  "$": {
    "#": "Student and Faculty inherit properties from Person and add their own",
    "Person": { "name": "", "birth": "$DATE" },
    "Student": { "+": [ "$Person", { "class": 1 } ] },
    "Faculty": { "+": [ "$Person", { "domain": "" } ] }
  },
  "name": "",
  "students": [ "$Student" ],
  "faculties": [ "$Faculty" ]
}
```

And the JSON value in file `psl.json`:

```json
{
  "name": "PSL",
  "faculties": [
    { "name": "Susie", "birth": "1980-10-14", "domain": "CS" },
    { "name": "Calvin", "birth": "1980-03-20", "domain": "CS" }
  ],
  "students": [
    { "name": "Moe", "birth": "2001-01-01", "class": 42 },
    { "name": "Rosalyn", "birth": "2002-02-02", "class": 17 }
  ]
}
```

Which validates:

```sh
jmc University psl.json  # PASS
```

A special behavior of merging object is that the operator is distributive over `|` and
`^`, which allows to add common properties to list of objects.
Morover, the operator can be used with references which point to models defined in other files,
so that object models can be reused anywhere.

## Adding Constraints

A convenient use case is to add constaints about types such as the length of a string
the number of items of an array or the number of properties of an object.
Let us consider file `Tournament.model.json` where 4 distinct players must be listed:

```json
{
  "#": "Tournament Model to list participants",
  "@": [ "" ],
  "!": true,
  "=": 4
}
```

The target model (`@`) is an array of strings, which must be distinct (`!` is _true_), the
array length must be equal (`=`) to _4_.

Value files `musketeers.json` and `3_musketeers.json`:

```json
[ "Athos", "Porthos", "Aramis", "D'Artagnan" ]
```
```json
[ "Athos", "Porthos", "Aramis" ]
```

May or may not validate:

```sh
jmc -r Tournament musketeers.json 3_musketeers.json
# musketeers.json: PASS
# 3_musketeers.json: FAIL (.: constraints failed [.])
```

## Transforming Models

As pointed out in the previous _Reusing Definitions_ and _Composing Object_ sections,
models can be reused and even combined for merging properties into new objects.
However, it is sometimes convenient to transform a model when reusing it, for
instance to update a constraint or replace a part.

Let us reuse the person data model by adding a constraint so that the _friends_ array
must not be empty and must contain distinct people, in file `Person-3.model.json`:

```json
{
  "#": "Constrained Person",
  "$": {
    "p2": "$./Person-2"
  },
  "%": {
    "$p2#Person.?friends": {
      "@": [ "$Name" ],
      "!": true,
      ">": 0
    }
  },
  "@": "$p2#Person"
}
```

The rewrite section (inside `%`) overrides the `?friends` property initial definition with the
new one, which takes precedence.

```sh
jmc Person-3 hobbes.json bastille.json  # PASS, FAIL
```

With file `bastille.json` which repeats _Marat_ in the `friends` array:

```json
{
  "name": "Bastille Day",
  "birth": "1789-07-14",
  "friends": [ "Marat", "Robespierre", "Danton", "Marat" ]
}
```

## Preferring YaML or JS

JSON is convenient for exchanging data between computer programs, especially across languages
and over networks. However, it is not a very friendly format for humans, thus actually typing
a model can be quite cumbersome.

In order to alleviate this drawback, this JSON Model implementation allows to use _YAML_  and
_JavaScript_ files, which drop some overheads such as double quotes, braces and commas, and
add comments:

```yaml
# a yaml representation of a person
name: ""
birth: ""
?friends:
  - ""
```

```js
// a javascript representation of a person
{
  name: "",
  birth: "",
  "?friends": [ "" ]
}
```

Both these formats are converted to JSON and can be used as JSON Model and
would provide the same result:

```sh
jmc -r Person-0.model.json hobbes.json moe.json  # PASS, FAIL
jmc -r Person-0.model.yaml hobbes.json moe.json  # PASS, FAIL
jmc -r Person-0.model.js   hobbes.json moe.json  # PASS, FAIL
```

## Running with C, JS, Python, Perl or Java

The JSON Model compiler allows to create actual test executables or scripts for
direct validation or performance testing, including option `-T` to loop over
a value so as to compute the average and standard deviation times in µs.

- generate and execute a C executable (assuming that [cre2](https://github.com/marcomaggi/cre2)
  is available in `/usr/local`, which is the case with the Docker image):

  ```sh
  jmc -o person.out Person-2
  ./person.out -T 1000000 hobbes.json
  # hobbes.json: 0.152 ± 0.058 µs/check (0.152)
  # hobbes.json: PASS
  ```

- generate and execute a NodeJS script:

  First, let us install the needed in the current node environment
  [JS runtime](https://www.npmjs.com/package/json_model_runtime) with `npm`
  (this is not needed for the Docker image):

  ```
  npm install json_model_runtime
  ```

  Then we can compile and run the generated validation node executable
  (`--loose` avoids a warning):

  ```sh
  jmc --loose -o person.js Person-2
  ./person.js -T 1000000 hobbes.json
  # hobbes.json: 0.536 ± 0.962 µs (0.032)
  # hobbes.json: PASS
  ```

- generate and execute a Python script:

  ```sh
  jmc -o person.py Person-2
  ./person.py -T 1000000 hobbes.json
  # hobbes.json: 9.386 ± 0.972 µs/call (0.050)
  # hobbes.json: PASS
  ```

- generate and execute a Perl script:

  Assuming that the `JSON::JsonModel` Perl module is available in your `PERLLIB`,
  which is the case with the Docker image:

  ```sh
  jmc --loose -o person.pl Person-2
  ./person.pl -T 100000 hobbes.json
  # hobbes.json: 23.484 ± 2.648 µs/call (0.033)
  # hobbes.json: PASS
  ```

- Java VM code:

  Assuming that the required classes are available in your `CLASSPATH`,
  which is the case with the Docker image:

  ```sh
  jmc -o Person.java Person-2
  javac Person.java
  # OR jmc -o Person.class Person-2
  java Person -j GSON -T 100000 hobbes.json
  # hobbes.json: 1.556 ± 8.610 µs [0.035]
  # hobbes.json: PASS
  ```

  Three Java JSON libraries are currently supported:
  Jackson, JSONP (with Johnzon or Joy implementations) and GSON.

Some comments about these representative performance figures:
As JavaScript JIT and its underlying regex engine are quite good,
a typical JS-to-C performance ratio is 4:1.
Java-to-C ratio is 12:1, but can be much less for larger tests.
Python is _slow_, a typical ratio to compiled C is 25:1.
Perl is even slower, this backend is not well optimized.
Because the `-r` option is not used, there are no reporting overheads.
For JS standard deviation is quite high, which could be induced by
occasional garbage collection.

## Running from C, JS, Python, Perl, Java or PL/pgSQL

The JSON Model compiler can also generate C, JavaScript, Python or PL/pgSQL
validation code ready to be imported for checking values:

```sh
jmc -o person.o Person-2            # C object file
jmc -o person.mjs Person-2          # JavaScript Module
jmc -o person.py --module Person-2  # Python Module
jmc -o person.pm Person-2           # Perl Module
jmc -o Person.java Person-2         # Java class
jmc -o person.sql Person-2          # PL/pgSQL functions
```

Here is an example of checking JSONB values inside Postgres, by importing
JSON Model runtime and generated code:

```sh
sudo make -C json_model/runtime install  # install runtime
# OR: sudo pgxn install json_model
psql -f person.sql                       # load runtime and model checking functions
```

And then invoking `check_model` for name `''` (empty name is the root model):

```sh
cat > test_values.sql <<EOF
```
```sql
CREATE TEMPORARY TABLE json_values(name TEXT PRIMARY KEY, data JSONB);
\copy json_values(name, data) FROM PSTDIN
SELECT
  name AS id,
  CASE WHEN check_model(data, '', NULL) THEN 'PASS' ELSE 'FAIL' END AS test
FROM json_values;
```
```sh
EOF

for f in [a-z]*.json ; do
  echo -e "$f\t$(jq -c < $f)"
done | psql -f test_values.sql
```

| **id**      | **test** |
|:---         |       ---:|
| hobbes.json |      PASS |
| moe.json    |      FAIL |

## Exporting to Pydantic

In the Python ecosystem, [pydantic](https://pydantic.dev/) allows to create typed data
classes very simply using type hints.

Let us export a model to pydantic with the `-E` export task:

```sh
jmc -E -F PersonModels.py -n Root Person-2
```

The generated file provide predeclared classes and types based on all named
definitions, plus the root model if appropriate:

```python
import datetime
import pydantic

type Name = str

class Person(pydantic.BaseModel):
    name: Name
    birth: datetime.date
    friends: list[Name]|None = None

PI: float = 3.141592653589793238462643

type Root = Person
```

Note that not all constraints and types are implemented.

## Exporting to and Importing from JSON Schema

Because of its simple structure, most models can be mapped simply to equivalent schemas.
The conversion currently does not handle external references, though.
The only features which cannot be translated are arbitrary property name references and
regular expression `X` extension.

Let us use `-E` to _export_ a model as a schema, displayed here in the yaml format to
save some space:

```sh
jmc -E -F yaml Person-2
```
```yaml
$comment: JSON Schema generated by JSON Model Compiler
$schema: https://json-schema.org/draft/2020-12/schema
$defs:
  Name:
    type: string
    pattern: ^\w+([-' ]\w+)*$
  Person:
    type: object
    properties:
      name:
        $ref: '#/$defs/Name'
      birth:
        type: string
        format: date
      friends:
        type: array
        items:
          $ref: '#/$defs/Name'
    required:
    - name
    - birth
    additionalProperties: false
  PI:
    const: 3.141592653589793
$ref: '#/$defs/Person'
```

A schema can also be converted to a model, although its lack of structural constraint makes it
harder. A partial converter which work with well-structured cases and support common schema
keywords is available with [json-schema-util](https://github.com/zx80/json-schema-utils):

```sh
jmc -E Person-2 | jsu-model
```
```json
{
  "#": "JSON Model generated from a JSON Schema with json-schema-utils",
  "$": {
    "Name": "/^\\w+( \\w+)*$/",
    "PI": "=3.141592653589793",
    "Person": {
      "?friends": [ "$Name" ],
      "_birth": "$DATE",
      "_name": "$Name"
    }
  },
  "@": "$Person"
}
```

## Empowering Developers

JSON Model is a compact and intuitive syntax for describing JSON data structures used
extensively to exchange data over networks, across programming languages and storage.
Its `jmc` implementation offers high performance validation for C, JS and Python.

The power of JSON Model is illustrated with this
[OpenAPI 3.1.1](https://github.com/clairey-zx81/json-model/blob/main/models/openapi-311.model.json)
model:

- it describes deeply nested objects with mostly optional properties.
- it reuses and extends the
  [JSON Schema model](https://github.com/clairey-zx81/json-model/blob/main/models/json-schema-draft-2020-12.model.json),
  see `schema` and `Schema` definitions.

This model is reused for defining an new OpenAPI standard where _models_ replace _schemas_,
with a short (32 lines) transformation model, see
[OpenAPI 3.1.1 with models](https://github.com/clairey-zx81/json-model/blob/main/models/openapi-311-models.model.json).

- it add new definitions to import JSON Model model
- replaces instances of schemas with instances of models where appropriate.

## References

- [JSON Model official web site](https://json-model.org/) with many resources!
- [JSON Model on GitHub](https://github.com/clairey-zx81/json-model) with all sources!
