# JSON Model Compiler Benchmark Artifacts

These artifacts compare
[JSON Model Compiler (jmc)](https://github.com/clairey-zx81/json-model) generated code using the
[JSON Schema Utils (jsu)](https://hub.docker.com/repository/docker/zx80/json-schema-utils)
schema to model converter in C, JS, Java (GSON, Jackson and JSONP using Johnzon) and Python with
[Sourcemeta Blaze CLI (sbc)](https://github.com/sourcemeta/jsonschema) using test cases from
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).

## Recent Artifacts

- [2026050900](benchmarks/2026050900.md) clang, no predefs, jsu 0.9.8/jmc 2.0b48 vs sbc 15.6.0, 11 runs, 1000 iterations.
- [2026050800](benchmarks/2026050800.md) clang, no predefs, jsu 0.9.8/jmc 2.0b48 vs sbc 15.5.0, 11 runs, 1000 iterations.
- [2026050703](benchmarks/2026050703.md) clang, no predefs, jsu 0.9.8/jmc 2.0b48 vs sbc 15.4.0, 11 runs, 1000 iterations.
- [2026050700](benchmarks/2026050700.md) clang, no predefs, jsu 0.9.6/jmc 2.0b46 vs sbc 15.4.0, 11 runs, 1000 iterations.
- [2026050304](benchmarks/2026050304.md) clang, no predefs, jsu 0.9.6/jmc 2.0b46 vs sbc 15.2.0, 11 runs, 1000 iterations.
- [2026042800](benchmarks/2026042800.md) clang, no predefs, jsu 0.9.6/jmc 2.0b45 vs sbc 15.2.0, 11 runs, 1000 iterations.
- [2026042700](benchmarks/2026042700.md) clang, no predefs, jsu 0.9.6/jmc 2.0b45 vs sbc 15.1.0, 11 runs, 1000 iterations.
- [2026042503](benchmarks/2026042503.md) clang, no predefs, jsu 0.9.6/jmc 2.0b45 vs sbc 15.0.0, 11 runs, 1000 iterations.
- [2026042500](benchmarks/2026042500.md) clang, no predefs, jsu 0.9.5/jmc 2.0b44 vs sbc 15.0.0, 11 runs, 1000 iterations.
- [2026042400](benchmarks/2026042400.md) clang, no predefs, jsu 0.9.4/jmc 2.0b43 vs sbc 15.0.0, 11 runs, 1000 iterations.
- [2026042001](benchmarks/2026042001.md) clang, no predefs, jsu 0.9.3/jmc 2.0b42 vs sbc 14.20.2, 11 runs, 1000 iterations.
- [2026040700](benchmarks/2026040700.md) clang, no predefs, jsu 0.9.2/jmc 2.0b41 vs sbc 14.20.2, 11 runs, 1000 iterations.
- [2026040400](benchmarks/2026040400.md) clang, no predefs, jsu 0.9.2/jmc 2.0b41 vs sbc 14.19.0, 11 runs, 1000 iterations.
- [2026040300](benchmarks/2026040300.md) clang, no predefs, jsu 0.9.2/jmc 2.0b41 vs sbc 14.18.0, 11 runs, 1000 iterations.
- [2026040200](benchmarks/2026040200.md) clang, no predefs, jsu 0.9.2/jmc 2.0b41 vs sbc 14.17.1, 11 runs, 1000 iterations.

## Benchmarking Script

The [benchmarking script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/benchmark.sh)
is provided as docker [docker.io/zx80/jmc-bench-docker](https://hub.docker.com/repository/docker/zx80/jmc-bench-docker)
or podman [docker.io/zx80/jmc-bench-podman](https://hub.docker.com/repository/docker/zx80/jmc-bench-podman) image.
It downloads the benchmark schemas and test values, and runs through docker-in-docker or podman-in-podman
[docker.io/zx80/jmc](https://hub.docker.com/repository/docker/zx80/jmc) for JMC runs and
[ghcr.io/sourcemeta/jsonschema](https://github.com/sourcemeta/jsonschema/pkgs/container/jsonschema)
for comparison using the Blaze CLI.

It is typically started on a large host with the
[`start_bench.sh` script](https://github.com/clairey-zx81/json-model/blob/main/tests/perf/start_bench.sh)
which will spawn the necessary containers:

```sh
JMC=latest JMC_OPTS="--no-predef --cc=clang" \
  nohup ./start_bench.sh latest -p 16 -l 1000 -r 5 &
# in the generated directory, look for the summary markdown and radar json files.
```

The main script options are:

- `-p PARA` parallelism (a little less that the number of available cores, default is _8_)
- `-l LOOP` loop iterations for performance average (at least _1000_, the default)
- `-r RUNS` number of runs (odd number, default is _3_)

## Benchmarking Conditions

JSON schemas for the benchmark are translated to models based on `jsu-compile`
from [JSON Schema Utils](https://github.com/zx80/json-schema-utils).
This is mostly an automatic conversion of the test schema to a model, but
for a few cases have a _native_ model which is used instead.

Runs are performed in _fast_ mode: the rejection reasons are not collected, and
the run stops as soon as possible.

- To smooth out the wide range of collected performances (from 10 ns to
  over 300 µs for validating one value), a relative comparison ratio is shown.
- Compilation times are the _minimum_ encountered over the runs.
  whereas performance times are the _median_ over the runs.

Note that performance figures **must** be taken with a pinch of salt, please consider
the following caveats, and others:

- do you value latency or throuput or resource consumption? the answer is not so obvious,
  probably you should prefer a high throuput _if_ the latency is good enough, but these
  benchmark actually measure raw latency.
- test cases may or may not be representative of specific use cases,
  especially wrt schema/model and value sizes.
- the overall load on the test host can impact measures.
- the measure overhead is estimated and deduced from the performance figures,
  which leads to potentially fuzzy results on very small data and schemas.
- compilers, libraries and other design and updates can have dramatic effects:
  for faster parsing, a library may use linked-list for properties, which means
  that retrieving a given property value will cost more than a library which uses
  a hash table which is more costly to build.
- blaze does _not_ implement checking string values (eg dates, url…),
  so these checks may be disactivated (see `JMC_OPTS`) for fairness,
  reducing the results significance.
- blaze uses its own special-purpose JSON representation which include a precomputed
  custom hash for string comparisons.
- blaze is a C++ library, if interfaced from another language, the cost of translating
  the JSON representation to this library should be taken into account;
  in contrast, jmc uses native JSON representations in the target ecosystem and generate
  validation code around it.
- due to intrinsic limitations of the underlying libraries and the quality of models or schemas,
  some results may differ, mostly for good reasons: regex incompatibilities, stricter
  model definitions compared to lax schemas…
- it is unclear whether JIT optimizations (eg Java and JS) may work around the
  benchmarking loops and report undue very fast performances, eg on the GeoJSON case.
- some execution environment (eg Java) may take advantage of parallelism with threads,
  which may or may not be a blessing: it can reduce the apparent latency (eg the gc runs
  in another thread) but have a detrimental overall effect on throughput and costs as
  more cpu ressources are spent on the same task.

## Other Artifacts

[Sourcemeta](https://sourcemeta.com)
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark)
also provides
[benchmark artifacts](https://github.com/sourcemeta-research/jsonschema-benchmark/actions)
which includes 16 JSON Schema validation tools including our compiler with
C, JS and Python backends, using the `jsu-compile` command.

It should be noted that benchmarking conditions are quite different compared to our own:

1. There is no loop to compute an average performance, but an initial _cold_ one-shot measure,
   a warming phase loop and a _hot_ one-shot measure: This may tend to mask effects from
   occasional GC runs.
2. The benchmark focuses on schema conformance, including (buggy) schemas which
   are mostly dead code: It rejects tools which do not validate all strictly conformant
   values, even if these values would be rejected by the target application.
3. Three schemas (`krakend`, `stale` and `yamllint`) in the test suites have been
   [edited](https://github.com/sourcemeta-research/jsonschema-benchmark/commit/ad109eb210c0939bd8393da28d8212f75c1c2d92),
   especially to deal corner cases issues with `$ref` under version 7 and prior,
   thus do not conform to the initial official schemas.
4. The benchmark  _removes_ format assertions before testing the schemas.
5. The model used are strictly converted from schemas, native models are not used
   even if available and schemas are not fixed for typical errors (eg misplaced keywords).

As of May 2026, the JSU C implementation is faster than Blaze on about 55% of benchmark cases
on these artifacts.
