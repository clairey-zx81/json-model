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

Medium schema/modal. Most of the time for checking item unicity in a object arrays.

This may be accelerated significantly if the JSON structure stores a hash for the object value?
If object properties are stored in a reliable order, the sorting step could be skipped
before merging?
The object array (`propval`) representation is built on each comparison, it could/should
be kept for the duration of the unique check.

## Yamllint

Very small schema/model.
