# JSON Model Compiler Benchmark Artifacts

These artifacts compare
[JSON Model Compiler](https://github.com/clairey-zx81/json-model) generated code in
C, JS, Java (GSON, Jackson and JSONP using Johnzon) and Python with
[Sourcemeta Blaze CLI](https://github.com/sourcemeta/jsonschema) using test cases from
[JSON Schema Benchmark](https://github.com/sourcemeta-research/jsonschema-benchmark).

## Recent Artifacts

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
