# JSON Model Compiler Benchmark Artifacts

These artifacts compare
[JSON Model Compiler](https://github.com/clairey-zx81/json-model) generated code in
C, JS, Java (GSON, Jackson and JSONP using Johnzon) and Python with
[Sourcemeta Blaze CLI](https://github.com/sourcemeta/jsonschema) using test cases from
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).

## Recent Artifacts

- [2025112002](benchmarks/2025112002.md) clang, no predefs, jmc 2.0b36 vs jsc 12.6.0, 11 runs, 1000 iterations.
- [2025111900](benchmarks/2025111900.md) clang, no predefs, jmc 2.0b36 vs jsc 12.5.0, 3 runs, 1000 iterations.
- [2025111804](benchmarks/2025111804.md) clang, no predefs, jmc 2.0b36 vs jsc 12.3.0, 3 runs, 1000 iterations.
- [202511150e](benchmarks/202511150e.md) clang, no predefs, jmc 2.0b36 vs jsc 12.2.1, 3 runs, 1000 iterations.
- [2025110500](benchmarks/2025110500.md) clang, no predefs, jmc 2.0b36 vs jsc 12.2.0, 3 runs, 1000 iterations.
- [2025110100](benchmarks/2025110100.md) clang, no predefs, jmc 2.0b35 vs jsc 12.2.0, 3 runs, 1000 iterations.

## Benchmarking Script

The [benchmarking script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/benchmark.sh)
is provided as docker image [zx80/jmc-bench](https://hub.docker.com/repository/docker/zx80/jmc-bench).
It downloads the benchmark schemas and test values, and runs through docker-in-docker
[zx80/jmc](https://hub.docker.com/repository/docker/zx80/jmc) for JMC runs and
[sourcemeta/jsonschema](https://github.com/sourcemeta/jsonschema/pkgs/container/jsonschema)
for comparison using the Blaze CLI.

It is typically started on a large host with the
[`start_bench.sh` script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/start_bench.sh)
which will span the necessary dockers:

```sh
JMC=latest JMC_OPTS="--no-predef --cc=clang-20" \
  nohup ./start_bench.sh latest -p 16 -l 1000 -r 5 &
# in the generated directory, look for the summary markdown and radar json files.
```

The main script options are:

- `-p PARA` parallelism (a little less that the number of available cores, default is _8_)
- `-l LOOP` loop iterations for performance average (at least _1000_, the default)
- `-r RUNS` number of runs (odd number, default is _3_)
- `--no-cap-py` do _not_ reduce python iterations by a factor of 10 (default is to reduce)

## Benchmarking Conditions

JSON schemas for the benchmark are translated to models based on
[JSON Schema Utils](https://github.com/zx80/json-schema-utils).

Runs are performed in _fast_ mode: the rejection reasons are not collected, and
the run stops as soon as possible.

- To smooth out the wide range of collected performances (from 10 ns to
  over 300 µs for validating one value), a relative comparison ratio is shown.
- Compilation times are the _minimum_ encountered of over the runs.
  whereas performance times are the _median_ over the runs.
- The C backend also includes the _runtime_ compilation from sources.
- JSON Schema to JSON Model conversion times are recorded separately.

Note that performance figures **must** be taken with a pinch of salt, please consider
the following caveats, and others:

- test cases may or may not be representative of specific use cases,
  especially wrt schema/model and value sizes.
- the overall load on the host can impact measures.
- compilers, libraries and other design and updates can have dramatic effects:
  for faster parsing, a library may use linked-list for properties, which means
  that retrieving a given property value will cost more than a library which uses
  a hash table which is more costly to build.
- blaze does _not_ implement checking string values (eg dates, url…),
  so these checks may be disactivated (see `JMC_OPTS`) for fairness.
- blaze uses its own special-purpose JSON representation: if interfaced from another
  ecosystem, the cost of translating the JSON representation should be taken into account;
  jmc uses native JSON representation and generate validation code around it.
- due to intrinsic limitations of the underlying libraries and the quality of models or schemas,
  some results may differ, mostly for good reasons: regex incompatibilities, stricter
  model definitions compared to lax schemas…
- it is unclear whether JIT optimizations (Java and JS) may work around the
  benchmarking loops and report undue very fast performances, eg on the GeoJSON case.

## Other Artifacts

[Sourcemeta](https://sourcemeta.com)
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark)
also provides
[benchmark artifacts](https://github.com/sourcemeta-research/jsonschema-benchmark/actions)
which includes 15 JSON Schema validation tools and our JSON Model Compiler with
C, JS and Python backends.
Overall, JMC-C comes ahead of Blaze C++ on 2/3 of the test cases (as of 2025-11-18).

It should be noted that benchmarking conditions are quite different:

1. There is no loop to compute an average performance, but an initial _cold_ one-shot measure,
   a warming phase loop and a _hot_ one-shot measure: This may tend to mask effects from occasional
   GC runs.
2. The benchmark focuses on schema conformance, including (buggy) schemas which
   are mostly dead code: It rejects tools which do not validate all strictly conformant values,
   even if these values would be rejected by the target application.

This latest point explains the under 100% validation results displayed JMC for
_ansible-meta_, _cypress_ and _yamllint_ tests: the model translation or native models
are more accurate than the original schemas due to bug fixes or more rigorous descriptions.
