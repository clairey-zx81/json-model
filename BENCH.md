# JSON Model Compiler Benchmark Artifacts

These artifacts compare
[JSON Model Compiler](https://github.com/clairey-zx81/json-model) generated code in
C, JS, Java (GSON, Jackson and JSONP using Johnzon) and Python with
[Sourcemeta Blaze CLI](https://github.com/sourcemeta/jsonschema) using test cases from
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).

## Recent Artifacts

- [2025111100](benchmarks/2025111100.md) clang, no predefs, jmc 2.0b36 vs jsc 12.2.1, 3 runs, 1000 iterations.
- [2025110500](benchmarks/2025110500.md) clang, no predefs, jmc 2.0b36 vs jsc 12.2.0, 3 runs, 1000 iterations.
- [2025110100](benchmarks/2025110100.md) clang, no predefs, jmc 2.0b35 vs jsc 12.2.0, 3 runs, 1000 iterations.
- [2025103000](benchmarks/2025103000.md) clang, no predefs, jmc 2.0b35 vs jsc 12.1.0, 3 runs, 1000 iterations.
- [2025102900](benchmarks/2025102900.md) clang, no predefs, jmc 2.0b35 vs jsc 12.0.0, 3 runs, 1000 iterations.
- [2025102705](benchmarks/2025102705.md) clang, no predefs, jmc 2.0b34 vs jsc 12.0.0, 5 runs, 1000 iterations.
- [2025102700](benchmarks/2025102700.md) clang, no predefs, jmc 2.0b34 vs jsc 12.0.0, 3 runs, 1000 iterations.
- [2025102402](benchmarks/2025102402.md) clang, no predefs, jmc 2.0b33 vs jsc 11.11.1, 7 runs, 1000 iterations.
- [2025102400](benchmarks/2025102400.md) clang, no predefs, jmc 2.0b33 vs jsc 11.11.1, 5 runs, 1000 iterations.
- [202510220b](benchmarks/202510220b.md) clang, no predefs, jmc 2.0b32 vs jsc 11.11.1, 5 runs, 1000 iterations.
- [2025102201](benchmarks/2025102201.md) gcc, no predefs, jmc 2.0b31 vs jsc 11.11.1, 5 runs, 1000 iterations.
- [2025102200](benchmarks/2025102200.md) gcc, no predefs, jmc 2.0b31 vs jsc 11.11.1, 5 runs, 1000 iterations.

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

- Compilation times are the _minimum_ encountered of over the runs.
  whereas performance times are the _median_ over the runs.
- For JMC, the compilation time includes the schema to model conversion,
  which adds a uniform time to all target languages.
- The C backend also includes the runtime compilation from sources.
- To smooth out the wide range of collected performances (from 10 ns to
  over 300 µs for validating one value), a relative comparison ratio is shown.

Note that performance figures **must** be taken with a pinch of salt, please consider
the following caveats, and others:

- test cases may or may not be representative of specific use cases,
  especially wrt schema/model and value sizes.
- compilers, libraries and other updates can have dramatic effects.
- blaze does _not_ implement checking string values (eg dates, url…),
  so these checks may be disactivated (see `JMC_OPTS`) for fairness.
- the overall load on the host can impact measures.
- due to intrinsic limitations of the underlying libraries and the quality of models,
  some results may differ, mostly for good reasons: regex incompatibilities, stricter
  definitions…
