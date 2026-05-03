# Improving performance

Investigation with `gprof`.

```bash
JMC_RUNTIME=$(jmc --runtime)
jsu-compile -o schema.c --fix --no-strict --no-reporting --no-format schema.json -- --cflags="-pg -g"
cc -I$JMC_RUNTIME/c -I/usr/local/linclude -DCHECK_FUNCTION_NAME=check_model -DREGEX_ENGINE_RE2 -Wall -Wno-address -Wno-c23-extensions -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-parentheses -Ofast -mtune=native -o cspell.out $JMC_RUNTIME/c/json-model.c schema.c $JMC_RUNTIME/c/main.c -L/usr/local/lib -ljansson -lcre2 -lpthread -lre2 -lm -lstdc++
schema.out --jsonl -T 10000
gprof schema.out > gprof.txt
gprof -l schema.out > gprof-l.txt
```

## Features

### Unique

Unique found in benchmark: 9/37 (24%)

Type of unique found: str 85%, obj 8%, int 7%.

- cspell: 2 string
- deno: 4 string
- draft04: 3 string, any (`enum`, most often strings?) ; `type` is always short
- jsconfig: 13 string, 1 object (open, one optional "path" prop)
- krakend: 9 string, 4 integer
- lazygit: 11 string, 2 object (with 1-3 mandatory props)
- stylecop: 4 string (in passing: 2 misplaced)
- ui5-mft: 1 object, 1 any (`enum`), 2 string
- unreal: 15 string, 2 object

TODO typical length of values found in benchmarks?
TODO missing unique? wrt number of arrays? (if the array represents a set, items should be unique)
TODO check enum item types in bench?
TODO check quality of schemas

## Cspell

Most of the time is spent checking that the `.words` array only contains strings.
The test values can contain dozens of items in this array (from 0 to 1311 (:973) 1326 (:612)).

Pseudo code in Python:

```python
res = is_array(val)
if res:
    for item in val:
        res = is_string(item)
        if not res:
            break
```

Suggestions: with the hypothesis that it validates, we can move the internal exit

```python
res = is_array(val)
if res:
    for item in val
        res &= is_string(item)
```

This seems to reduce the execution time by up to 15%.

## Helm

Very small schema/model with 2 must-only 3-properties objects checked for strings.

Maybe 5% improvement by removing breaks and using `res &= …`.

## Importmap

Very small schema/model with objects with optional properties, mostly string checks.

## Krakend

Large schema/model. Maybe get a few % by optimizing regex `^[xyzw]` (4 chars).

## Unreal

Medium schema/modal. Most of the time for checking item unicity in **object** arrays.

- [x] object array (`propval`) representation is built on each comparison,
  it could/should be kept for the duration of the unique check.
- [x] add a hash discriminator?
- [x] add a non-sorting n² implementation for small arrays?
- [ ] if object properties are stored in a reliable order, the sorting step could be skipped
  before merging?
- [ ] may be accelerated significantly if the JSON structure stores a hash for the object value?

Note about blaze unique implementation:

- it computes a type and slightly value dependent `fast_hash` (`uint64_t`) on each item
- then proceeds to do n² comparisons (`==`), first on the hash, then on the item if necessary

## Yamllint

Very small schema/model.
