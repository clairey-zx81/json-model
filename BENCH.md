# JSON Model Compiler Benchmark Artifacts

The purpose of this benchmark is to compare JSON value validation performance for
the same constraints, independently of the syntax used to express these constraints.

These artifacts compare
[JSON Model Compiler (jmc)](https://github.com/clairey-zx81/json-model) generated code using the
[JSON Schema Utils (jsu)](https://hub.docker.com/repository/docker/zx80/json-schema-utils)
schema to model converter in C, JS, Java (GSON, Jackson and JSONP using Johnzon) and Python with
[Sourcemeta Blaze CLI (sbc)](https://github.com/sourcemeta/jsonschema) using test cases and values
from [JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).

## Recent Artifacts

Overall, depending on the chosen metrics, JMC with the C backend is 50-100% faster
than Blaze on average to validate JSON values in these artifacts.

- [2026080700](benchmarks/2026080700.md) jsu 0.9.17/jmc 2.0.56 vs sbc 16.7.0, content, fix.
- [2026080800](benchmarks/2026080800.md) jsu 0.9.17/jmc 2.0.56 vs sbc 16.7.0, content, no fix.
- [2026080900](benchmarks/2026080900.md) jsu 0.9.17/jmc 2.0.56 vs sbc 16.7.0, content, no id, no fix.
- [2026080600](benchmarks/2026080600.md) jsu 0.9.17/jmc 2.0.55 vs sbc 16.7.0, content, fix.
- [2026080501](benchmarks/2026080501.md) jsu 0.9.17/jmc 2.0.55 vs sbc 16.6.0, content, fix.
- [2026080500](benchmarks/2026080500.md) jsu 0.9.17/jmc 2.0.55 vs sbc 16.5.0, content, fix.
- [2026080400](benchmarks/2026080400.md) jsu 0.9.16/jmc 2.0.55 vs sbc 16.5.0, content, fix.
- [2026080300](benchmarks/2026080300.md) jsu 0.9.16/jmc 2.0.55 vs sbc 16.4.0, content, fix.
- [2026080100](benchmarks/2026080100.md) jsu 0.9.16/jmc 2.0.55 vs sbc 16.3.0, content, no fix.

Options: _content_ validate string contents (format/predef), _fix_ improved models (bug fixes) or strictly schema compatible native models.

## Benchmarking Script

The [benchmarking script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/benchmark.sh)
is provided as docker [docker.io/zx80/jmc-bench-docker](https://hub.docker.com/repository/docker/zx80/jmc-bench-docker)
or podman [docker.io/zx80/jmc-bench-podman](https://hub.docker.com/repository/docker/zx80/jmc-bench-podman) image.
It downloads the benchmark, and runs through docker-in-docker or podman-in-podman
[docker.io/zx80/jmc](https://hub.docker.com/repository/docker/zx80/jmc) for JMC runs and
[ghcr.io/sourcemeta/jsonschema](https://github.com/sourcemeta/jsonschema/pkgs/container/jsonschema)
for comparison using the Blaze CLI.

It is typically started on a large host with the
[`start_bench.sh` script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/start_bench.sh)
which will spawn the necessary containers:

```sh
JMC=latest JMC_OPTS="--predef --cc=clang" JSU_OPTS="--id --fix --no-strict" \
  nohup ./start_bench.sh latest -p 12 -l 1000 -r 5 -c &
# in the generated directory, look for the summary markdown and radar json files.
```

The main script options are:

- `-p PARA` parallelism (less that the number of available cores, default is _8_)
- `-l LOOP` loop iterations for performance average (at least _1000_, the default)
- `-r RUNS` number of runs (odd number, default is _3_)
- `-c` validate contents (default is _not_)

## Benchmarking Conditions

JSON schemas for the benchmark are translated to models based on `jsu-compile`
from [JSON Schema Utils](https://github.com/zx80/json-schema-utils).
This is mostly an automatic conversion of the test schema to a model, but
for a few cases have a _native_ model which is used instead.
Depending on the selected options, the model may be stricter/more accurate than
the corresponding schema (eg automatic schema fixes such as missing types,
misplaced keywords or bad regex, or better native models), and induce small
differences in the validated results, in which case they are manually
validated and discussed.

Runs are performed in _fast_ mode: the rejection reasons are not collected, and
the run stops as soon as possible.

- To smooth out the wide range of collected performances (from 10 ns to
  over 300 µs for validating one value), a relative comparison ratio is shown.
- Compilation times and performance times are the _median_ encountered over the runs.

Note that performance figures **must** be taken with a pinch of salt, please consider
the following caveats, and others:

- do you value latency or throuput or resource consumption? the answer is not so obvious,
  probably you should prefer a high throuput _if_ the latency is good enough, but these
  benchmark actually measure raw latency.
- test cases may or may not be representative of specific use cases,
  especially wrt schema/model and value sizes.
- the overall load on the test host can impact measures, as well as power control
  features which adjust the cpu frequency in real time, thus the frequency may be set
  explicitely, and effort are made to cap the load to limit its impact on measures.
- Relying on hyper-threading can reduce performance for simple one thread tasks,
  so it is often disabled.
- the measure overhead is estimated and deduced from the performance figures by default,
  which leads to potentially fuzzy results when testing very small values.
- compilers, libraries and other design and updates can have dramatic effects:
  for faster parsing, a library may use linked-list for properties, which means
  that retrieving a given property value will cost more than a library which uses
  a hash table which is more costly to build.
- before version _16.0_, blaze does _not_ implement checking string values (eg dates, url…),
  so these checks may be disactivated (see _Contents_ in _Parameters_) for fairness,
  reducing the results significance.
- blaze uses its own special-purpose JSON representation which include a precomputed
  custom hash for string comparisons, aleviating the need to actually compare strings
  in most cases.
- blaze is a C++ library, if interfaced from another language, the cost of translating
  the JSON representation to this library should be taken into account;
  in contrast, jmc uses native JSON representations in the target ecosystem and generate
  validation code around it.
- due to intrinsic limitations of the underlying libraries and the quality of models or schemas,
  some results may differ, mostly for good reasons: regex incompatibilities, stricter
  model definitions compared to lax schemas…
- it is unclear whether JIT optimizations (eg Java and JS) may work around the
  benchmarking loops and report undue very fast performances, eg on the GeoJSON case.
- some execution environment (eg Java) take advantage of parallelism with threads (possibly
  for the garbage collector and JIT), which may or may not be a blessing: it can reduce
  the apparent latency (eg the gc runs in another thread) but have a detrimental overall
  effect on throughput and costs as more cpu ressources are spent on the same task.
- test values are mostly valid, which is representative of a typical use case, but
  the tool accuracy should be asserted elsewhere with failing cases.

## Other Artifacts

[Sourcemeta](https://sourcemeta.com)
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark)
also provides
[benchmark artifacts](https://github.com/sourcemeta-research/jsonschema-benchmark/actions)
which includes 16 JSON Schema validation tools including our compiler with
C, JS and Python backends, using the `jsu-compile` command only.

It should be noted that benchmarking conditions are quite different compared to our own:

1. There is no loop to compute an average performance, but an initial _cold_ one-shot measure,
   a warming phase loop (up to 1000 rounds, kept under 10 seconds) and a _hot_ one-shot measure:
   This may tend to mask effects from occasional GC runs.
2. The benchmark focuses on schema conformance, including (buggy) schemas which
   are mostly dead code: It rejects tools which do not validate all strictly conformant
   values, even if these values would be rejected by the target application.
   The model used are strictly converted from schemas, native models are not used
   even if available and schemas are not fixed for typical errors (eg misplaced keywords).
3. Three schemas (`krakend`, `stale` and `yamllint`) in the test suites have been
   [edited](https://github.com/sourcemeta-research/jsonschema-benchmark/commit/ad109eb210c0939bd8393da28d8212f75c1c2d92),
   especially to deal corner cases issues with `$ref` under version 7 and prior,
   thus do not conform to the initial official schemas.
4. The benchmark _removes_ format assertions before testing schemas.
