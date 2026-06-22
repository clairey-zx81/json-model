# JSON Model Compiler Versions

## 2.0.51 2026-06-22

- perf: rename `show.py` as `report.py`
- front: allow to add a comment in generated source files
- perf: allow to hide useless entries when generating a x2 comparison report
- perf: add geometrical average delta to x2 comparison report
- perf: rewrite benchmark analysis with pandas instead of sqlite3
- js-runtime: check stability of `.mo` extension (issue reported, does not work… as intended)
- perf: add --load benchmark option to reduce load when java is running
- optim: avoid redundant lower bound checks on constrain integers
- perf: add ntests, change default order
- perf: add switch to enable value contents checks
- optim: check unfeasible distinct values for a minimum number of distinct values
- c-runtime: require `:` to appear in a url
- pl-backend: fix reporting code
- backends: fix handling of json str predefs in some cases
- c-backend: avoid inserting regex strings twice on re predefs
- backends: refactor re optim stuff in `regex.py`
- spec: add `$SEMVER` predef
- export: use regex when available when exporting predefs to schema
- py-backend: handle arbitrary typed tag values on string maps
- optim: do not flatten `^`!
- optim: fix wrong removal of min props constraint when not an object

## 2.0.50 2026-05-21

- c-runtime: remove some warnings on build
- front: reduce version display verbosity
- doc: add release procedure section
- doc: fix type in jmc pod file
- test: and minimal working sanity test
- dev: improve dev setup and cleanup
- ci: add minimal CI configuration on GitHub
- main: add parse time measure for Python, JS, C, Java, Perl
- java-runtime: update to latest JSON libraries
- js-runtime: bump version
- pl-runtime: bump version
- static: fix generated code order determinism (again)
- utils: ~improve model recurse with optional context~ not needed
- front: add options to control more optimization phases
- perf: improve benchmark script to help with next task (`compare.py`)
- perf: separate perf and show business
- perf: rewrite perf as a shell load script + sql
- perf: rewrite show as a python script
- perf: improve and generalize performance comparison script
- perf: update benchmark stuff to use new comparison script
- front: add `--no-precompiled` option
- front: add `--no-unique-optimize` option
- perf: compare can use χ² test
- perf: test with each optimizations disabled to mesure impact
- perf: analyze identical generated files when comparing same language
- backend: use current version instead of installed version in generated code
- js-runtime: fix string length as a number of chars
- static: allow do disable regex pattern matching
- static: allow to disable function call shortcuts
- c-runtime: accept time `24:00:00` (8601-1:2019/Amd 1:2022)
- test: do not test `24:00:00` as time validators are unlikely to agree
- container: remove `cstring` add, `cre2` master is now fixed
- perf: allow to restrict reporting to a subset of tools
- static: allow disabling more xstatic optimization
- perf: add note about random frequency governor changes because of cpu temperature
- perf: show median compilation time instead of min
- perf: possibly mount jsb as a volume when benchmarking
- c-runtime: move re header inclusion to `json-model.h`
- pl-backend: better escape some characters
- sql-backend: use string escape syntax
- static: fix int constant comparison typing under loose ints
- c-backend: fix handling of small chars when building integers
- static: fix some prop name escaping on reporting
- java-backend: large int constants need a "L" suffix
- java-backend: fix long conversion with GSON
- java-backend: fix GSON issue where null property values are considered missing
- pl-backend: load "utf8" package to better deal with utf8 constants
- perf: also add jsb sharing when using js-cli
- java-runtime: fix GSON null when used in value sets

## 2.0.49 2026-05-09

- front: cleanup obsolete versioning stuff
- front: show dynamic version when under dev
- pr: show static version when generating ABOUT page
- pr: add documentation section in ABOUT page
- front: workaround, allow to skip dynamic version recomputation
- front: use semver

## 2.0b48 2026-05-07

- static: unroll small array scans for simple type checks
- test: cover more array unrolling cases
- front: add option to control array type check unrolling
- perf: check for unroll minsize parameter depending on language
- static: improve reporting for unrolled array simple type check
- perf: improve extraction script performance (sh to python)
- front: show git hash on `--version`?
- front: switch to dynamic versioning

## 2.0b46 2026-05-03

- c-backend: test real then int when checking for a number
- static: provide type of array elements for unique
- c-backend: string unique implementation
- c-backend: object unique implementation avoids repeated prop extractions
- c-backend: unique with hash, aka faster non sorting algorithm for small array size
- c-backend: set unique with hash limits based on tests
- c-backend: check for other useful types for unique with hash - most str, some int/obj
- c-backend: specialized unique int array implementation
- c-backend: ~try memcmp instead of strcmp where appropriate~ not interesting…
- perl-backend: do not import RE2 unless required in generated script, ok test added
- optim: remove min props covered by mandatory props
- optim: check max props wrt mandatory props
- pr: cleanup backlog and create version markdown
- docker: use ubuntu 26.04  base

## 2.0b45 2026-04-25

- ~perl-backend: improve resilience to missing dependencies, eg `Algorithm::LUHN`~
- c-backend: allow to reuse pre-compiled runtime

## 2.0b44 2026-04-24

- front: allow to call script as a function

## 2.0b43 2026-04-23

- optim: override simpler regex props if stricter

## 2.0b42 2026-04-20

- \*-backend: remove `--jsonschema-benchmark` handling as it is moved to this repo
- command: add `--no-comment` option not to generate comments in source code
- \*-backend: support for embedded nul characters in strings, when possible (not SQL nor C)
- ir: use json name instead of python type names
- perf: add speed in lines per µs which seems more significant
- command: add `-mtune=native` to C compilation
- optim: simplify _&_ with same props and regs plus optional wildcards
- optim: simplify _X & Y_ to _X_ when _X_ is a submodel of _Y_
- py-backend: add predefs IP4 IP6 HOST
- \*-backend: use a common predef for RFC3339 DURATION UUID EMAIL JSONPT
- \*-backend: add approximated backup regex for predefs when not implemented by runtime
- predefs: add `$__EXTENSION_COLOR`
- predefs: refactor multiple instances in the sources into `predefs.py`
- predefs: add `$ETH` for ethernet (mac) addresses
- static: recognize and generate better code for typed _not_: _"" ^ "xxx"_
- ir: add forward substitution between assignments when used once
- py-backend: filter out zone id suffix from ip6
- predefs: add `$CARD` for 16 digits credit card numbers with Luhn's checksum
- predefs: add `$CARD` to js, perl, java and sql runtime.
- predefs: filter predef extensions with `--extend`
- ~static: if only one open prop, just look for it~ depends on language and costs
- ir: improve forward subs, move bool decl to first assignment in seq
- static: use combined assignment and test if possible on discriminator extraction
- static: fix any-by-one pattern on string predefs
- py-runtime: allow lowercase tz in datetime
- py-runtime: add workarounds for leap seconds and other intricacies
- predefs: add predef `EXTENSION_REL_JSONPT` as a regex
- predefs: distinguish simple time and time with mandatory tz for jsu `time` format
- static: avoid double type checks on or with predefs (java, sql, perl)
- ~ir: remove simple redundant checks _(X && (X && Z) || (X && Y))_ is _X && (Z || Y)_~ (see previous)
- c-backend: simple regex compiler for special character classes and repeat
- c-backend: simple regex compiler cache is okay with existing regex cache
- c-backend: add custom character classes based on benchmarks (ident, space, up/low/hexa/num/…)
- optim: `/.+/` is `/./`, `/(.+)/`, `/(.*)/`
- optim: remove unescaped `.*` at end of regex, also `.+/` is `./`
- c-backend: normalize before character class matching
- c-backend: extend simple regex with constant prefix
- c-backend: extend simple regex without end-of-text (`$`)
- optim: apply simpler re to property names
- optim: improve model intersection to simplify `&` in more cases
- optim: improve intersect on single open constraint object case
- optim: avoid reference expansion in and combine optimization
- c-backend: optimize special regex `/./` `/./s` `/^.*$/` `/^.+$/`
- static: detect or of any-but-some type to generate a not instead, beware of looseness
- static: do not create a separate function for an basic object check
- static: generate messages in newly added shortcuts
- c-backend: regex list of words to enum?
- c-backend: fast ic str comparison by switching to _lower char_ with a set test?
- c-backend: improve regex opt cset prettyprinting
- c-backend: extend simple regex to sequences of prefix/chars/repeats
- c-backend: add custom char class `[A-Za-z0-9_\\-:]` `[1-9]`
- container: separate base from specific installs to improve cache/no-cache build
- static: improve pattern matching for starts with/ends with/eq regex optim
- static: improve endswith pattern recognition with escapes, eg `/\\.js$/`
- c-backend: improve startwith code with fast str eq when string is a function call
- c-backend: improve `str_cmp` with fast str eq when string is a function call
- c-backend: check str cmp optims with utf8 strings
- static: preserve prop order by default
- c-backend: add custom character classes `[-a-z0-9_]` variants
- c-backend: use counter for multithreaded tests
- c-backend: fix multiple brace repeats in simple regex optimization
- model: add option to `s` on regex? else `.` is any but `\n` and sometimes `\r`
- optim: `/^.{1,256}$/`? only under `/s` though…

## 2.0b41 2026-03-14

- optim: do not recheck object if not necessary
- command: show runtime directory with `--runtime`
- optim: better merge `&` list when possible, including regex prefix incompatibilities
- js-backend: export model map
- pl-backend: add and export `mapper` function

## 2.0b40 2026-03-12

- c-backend: use monotonic instead of realtime clock which has a better precision
- java-backend: fix previously untested `--jsonschema-benchmark` implementation

## 2.0b39 2026-03-10

- optim: implement any type but one constrained optimization (jsu)
- ir: fix bad elimination when bool var was used
- ir: add bool var assign elimination on return with only one use
- c-backend: fix long option parsing

## 2.0b38 2026-03-08

- pr: publish python jmc package
- static: add support for `.in` with constraints
- optim: fix constraint simplification mixup
- tests: add _stats_ target
- perf: add missing warmup to C runtime for jsonschema benchmark
- perl-backend: be resilient on missing RE2 module

## 2.0b37 2026-02-27

- test: improve output determinism
- container: allow to use `podman` instead of `docker`
- perf: estimate measure overhead over 100 iterations
- perf: share overhead estimation between tests
- perf: try to prevent performance loops from being optimized out with some computation
- container: add podman-in-podman or docker-in-docker
- python-backend: add support for embedded nul characters in strings
- optim: fix inappriopriate model deduplication in or-lists
- dynamic: allow arbitrary options to dynamic interfaces
- lang: extend list of predefs with IP4, IP6, HOSTNAME, JSONPT, DURATION
- bug: fix unwise regex optimization
- python-backend: add support for `.mo`
- optim: remove bad transform _A & (T ^ B)) != A ^ B_
- python-backend: escape more strange characters in string constants
- perf: do not report broken count if nothing is broken
- python-backend: numerical workarounds for .mo extension implementation
- backend: add support for `.in` extension without other constraints
- tests: minimal tests for `.mo` and `.in`
- \*-backend:: add support for `.mo` and `.in` extensions
- optim: optimize typed and _"" & "xxx"_ involving references
- optim: arbitrary guard against infinite loops
- ir: fix stupid bug in ir opts
- tests: rerun with updated JSTS before release

## 2.0b36 2025-11-12

- tests: check how clang compares to gcc (maybe a few pc better)
- static: partition long lists of properties based on first bytes
- static: use more bytes for str hashing depending on min len
- static: generate hexa constants for partition limits tests
- static: use `continue` instead of long multi-if statements
- c-backend: partition inlined str cset
- static: or acceleration based on full or partial distinct mandatory props
- static: set default C partition threshold to _6_
- c-backend: replace `strcmp` with `memcmp` in runtime
- backend: improve if patterns in some cases
- pr: add explicit winner column to per case perf
- model: simplify `{"": "$NONE"}`
- ~model: avoid dead code in `mv-0f/dedup-002`~ (simple pair ok, multiple seldom useful)

## 2.0b35 2025-10-30

- static: order must/may props by increasing size
- command: fix bad mmo threshold initializations
- static: shorten return on open one may no must/regs/defs
- backend: optimize pattern "if (!? V) V = cst;"
- backend: optimize pattern "V = C; if (!? V) ..."
- backend: optimize pattern "V = E1; V = E2;"
- c-backend: generate direct code for search constant on small str sets
- static: add likely hints on array checks
- perf: test max strcmp cset to set default default
- pr: move out schema-to-model conversion
- pr: adjust radar display to visible datasets

## 2.0b34 2025-10-27

- static: improve likely hints depending on expectations
- backend: fix `TRUE AND` in `mv-07/json-schema-draft-tight.sql` (late)
- backend: useless computations in `mv-17/xor_01.pl`
- static: for must-only scheme controlled by option
- static: further improve likely hints
- command: rename `--unroll-may-…` options for `--may-must-open-threshold`
- command: set optimization parameters depending on target language

## 2.0b33 2025-10-24

- c-backend: try with `clang` instead of `gcc`

## 2.0b32 2025-10-22

- backend: optimize length-based non-empty string check
- backend: remove reporting expressions under no reporting
- backend: nullify reporting parameters under no reporting
- command: silent more cc warnings

## 2.0b31 2025-10-22

- pr: improve radar chart responsiveness and sorting
- backend: remove intermediate variable on return
- backend: remove unused boolean variable declaration on simple direct return
- ~backend: remove redundant scalar test in some cases~
- backend: remove reporting instructions under no reporting
- backend: add late code filtering to catch some backend-specific stuff
- c-backend: remove redundant scalar test in some cases (with late filtering)
- c-backend: remove some useless braces around one instruction (with late filtering)
- backend: simplify conditional assignment patterns with one boolean constant
- backend: merge boolean declaration and first assignment if possible
- backend: optimize pattern "if (! res) res = E; ret res;"
- backend: refactoring, cleanup and generalization
- static: add likely/unlikely hints to clang
- c-backend: optimize startwith implementation
- backend: optimize pattern "res = E1; if (! res) res = E2;"
- backend: optimize full pattern "(E && ...) || (E && ...)"
- backend: or/and flattening
- backend: optimize partial pattern "... || (E && ...) || (E && ...) || ...;"
- backend: optimize pattern "V = E1; if (V) V = E2;"
- perf: add launcher script
- c-backend: cleanup duplicated `json_is_boolean` calls
- c-backend: fix bad constant string expression syntax

## 2.0b30 2025-10-18

- pr: improve bench page
- command: set default to compile on `-F language` instead of model preprocessing
- c-backend: add _optimized_ str comparison code for eq and ne, enabled by default
- c-backend: consider big endian for strcmp runtime and code generation
- perf: allow running over a subset of tools only
- static: remove unexpected `$ANY` messages (irep dead code elimination)
- pr: add new artifact (2025101808)

## 2.0b29 2025-10-17

- pr: add a benchmarking performance artifact page
- backend: shamefully ignore bad json due to strange prop names
- static: fix disjunct analysis issue
- optim: fix infinite loop between xor-to-or and partial eval

## 2.0b28 2025-10-11

- static: skip map target functions for objects
- static: skip map target functions for references
- optim: add more if simplifications in IR
- optim: improve xor-to-or over references and sub-ors
- python: remove useless (debugging) assertion in generated code
- perf: also show docker id of tested image
- optim: more xor/not/or simplifications
- optim: xor-to-or model difference based on not exclusion, possibly behind refs

## 2.0b27 2025-10-07

- perf: ensure properly aligned data in box report
- perf: allow to collect data over several runs
- optim: and-to-merge optimization for open object models
- perf: allow to collect user time instead of elapsed time
- backend: improve and extend IR optimizations (wip)
- tests: perl _uninitialized value `$tag_0` in hash element at `./mv-18/dis_01.pl:171`._
- ~tests: fix sql test errors from `Makefile`~
- ~pr: submit jsonschema-benchmark PL/pgSQL PR~
- optim: get rid of double object with C, Python and Java
- backend: ~do not generate intermediate empty functions for direct objects? (skip)~

## 2.0b26 2025-10-04

- perf: add jsb version to final summary
- command: add `--no-predef` option for testing
- command: remove inline-or option and implementation
- command: allow to pass options with environment variable `JMC_OPTS`
- docker: environment control for perf tests
- command: `jmc -C -o foo.json` generates python instead of json

## 2.0b25 2025-10-02

- models: write model for json IR
- static: fix value path in some object variants
- static: add a max threshold/ratio for may property unrolling

## 2.0b24 2025-09-27

- backend: intermediate represention json code generation
- backend: optimize some output patterns on IR
- backend: generate output source code from symbolic json code
- xstatic: skip IR if not needed
- command: add `--ir-optimize` option
- command: activate ir optimization by default
- backend: IR handling of ConstMap
- static: skip model function to call obj function directly on references
- backend: apply skip functions also for all pmap/cmap/cc through IR
- optim: direct mandatory-only attributes objects with expected count checked ahead

## 2.0b23 2025-09-21

- artifact: add test case stats
- static: detect discriminators from references
- static: detect partial discriminators
- static: detect partial discriminators with other stuff
- docker: generate image for current branch
- artifact: improve docker image tagging

## 2.0b22 2025-09-19

- static: detect discriminator on object part of or/xor
- static: accept discriminator with a list of constants
- optim: fix infinite recursion in `inline_or`
- optim: improve xor-to-or to handle more cases
- optim: add `-[-no]-inline-or` option
- artifact: fix selection of docker image between `benchmark.sh` and `run.sh`
- optim: turn off `--inline-or` by default, which can impact compile perf too much
- tests: allow options for specific tests from pytest
- tests: cleanup current status, back to 100\%
- pr: update tuto scripts to match current status

## 2.0b20 2025-09-14

- artifact: reduce task granularity
- artifact: add bench docker image base on docker-cli
- java-backend: update dependency versions

## 2.0b19 2025-09-13

- docker: add subdirs to java classpath

## 2.0b18 2025-09-11

- static: optimize function mapping by skipping intermediate functions if possible

## 2.0b16 2025-09-09

- model: filter out all comments from transformations
- c-backend: improve overhead estimation accuracy

## 2.0b15 2025-09-08

- pl-backend: work around reference issues
- command: add `--schema-version` to force schema version output
- pr: remove _wip_ cover page from web site

## 2.0b13 2025-09-06

- pr: improve tuto docker launch
- pl-backend: add function declarations, needed for some recursions

## 2.0b12 2025-09-02

- js-frontend: do several iterations to measure the loop overhead
- python: fix venv installation issue with `pl/JSON` directory

## 2.0b11 2025-08-30

- py-frontend: fix line numbering for jsonl

## 2.0b10 2025-08-30

- java-frontend: improve check interface and calls
- js-frontend: fix line numbering for jsonl

## 2.0b9 2025-08-29

- c-backend: add inlining and branch hints
- c-frontend: fix --version display
- py-frontend: fix line display for jsonl and test vectors

## 2.0b7 2025-08-28

- pl-backend: fix utf8 JSON handling `mv-21/pJSON`
- pr: docker tuto script fix pull
- command: add `--jsonl` support
- pr: java-backend maven packaging and publication
- pr: update example re in tuto
- dev: complete publish task in root makefile
- pr: review readme, what is the introductory story?
- java-backend: fix `mv-0a/base-18` unique
- qa: rerun all pytest checks
- qa: rerun all source checks
- qa: ensure that full validation runs in docker zx80/jmc
- src: restructure runtime per language
- pr: write `everything.model.json` for illustration and test
- command: add cache management options, eg cleaning, ignore…
- java-backend: jsonp tested with joy
- java-backend: jsonp with johnzon, same issues compared to joy…
- design: check `$BOOL` vs `$BOOLEAN` support
- pr: complete spec
- design: force static information on `@` constraints for optimizations
- pr: howto entry about python dyn code
- pr: add about project page which include some stats
- pr: howto entry about python projects
- pr: restructure web site, avoid some duplication
- pr: python static api
- pr: python dynamic api
- pr: js api
- pr: c api
- tests: fix generated json model schema test by switching to jschon
- pr: plpgsql api
- pr: perl api
- pr: java api
- pr: js howto

## 2.0b4 2025-08-12

- command: fix handling of stdin for a model
- pr: publish pl runtime on cpan
- java-backend: env `JSON_MODEL_JAVA_JSON_LIB` can control JSON lib selection
- java-fe: add help stuff
- java-backend: use package if set
- sql-backend: handle package as schema name if set
- java-fe: implement list option
- pr: add java to docker
- \*-backend: add `$JSON` predef for all
- pr: add java to tuto
- pr: fix java utf8 with docker

## 2.0b3 2025-08-09

- pr: howto entry about installation
- pr: bootstrap spec
- pr: bootstrap doc
- pr: bootstrap api
- pr: add cover page
- pr: add front page to `models`
- pr: fix http requests without `.model.json` suffix (cri conf)
- pr: provide a non-root docker
- command: add --static compilation option to avoid dependencies?
- pr: publish the docker image `zx80/jmc:2.0b1`
- pr: use docker for tuto
- docker: allow to execute stuff inside the docker
- pl-backend: add a Perl backend
- tests: add pl tests
- backends: generate a short version string for internal tests
- tests: fix `test_models_pl`
- command: reject models and values with duplicated props by default
- pr: add pl to docker
- pr: add pl to tuto
- pr: add pl to readme
- pl-backend: fix `--jsonl` loading and improve jsonschema-benchmark output
- pr: add jmc-pl to jsonschema-benchmark
- docker: add `help` and `run` to docker wrapper
- pr: review readme for docker
- python: refactor preproc vs compile vs codegen…
- command: write a man-page or similar?
- pl-frontend: expand `--help`
- pr: add pl to howto
- pl-backend: check perl module package generation.
- design: object comments starting with `#`, not just `#`
- design: array comments `# …` to be ignored
- frontends: add `--no-report`
- pr: howto entry about python code
- pr: update `models/...` to take advantage of multi-comments
- pr: ask for pause account
- pr: ship man page with `--doc` option
- pl-backend: move to subdir + jsb PR update
- export: simple stuff to python pydantic
- pr: tuto pydantic export example
- export: use pydantic predefs and the class syntax
- pr: readme pydantic export example
- export: possible generate the root model
- java-backend: jackson gson ~jsonp moshi~
  see [perfs](https://github.com/fabienrenaud/java-json-benchmark)
- java-backend: add code generator and runtime, with abstracted json representation
- java-backend: pass validation tests with jackson
- java-backend: pass validation tests with gson
- java-backend: fix `mv-18/dis_0[13]` `mv-19/tag01` `mv-1a/opt_07` GSON/Jackson diff
- test: enable java tests with pytest
- command: allow direct java compilation
- pr: update tuto with some Java

## 2.0b1 2025-07-20

- sql-backend: package support as an extension
- pr: register `json-model.org` domain
- doc: bootstrap jmc manpage with pandoc
- pr: setup official http/https web page
- pr: improve official web page with docsify
- optim: simplify int constraints
- optim: simplify some property regex
- model: add `pgxn` model
- pr: register as an [official pgxs extension](https://pgxn.org/dist/json_model/).
- doc: complete jmc manpage
- pr: publish as a [python package](https://pypi.org/project/json-model-compiler/)

## Previous

- refactor: move schema to model conversion to json-schema-utils.
- design: change `%` to `$` and remove `$` intra-model naming shortcut.
- design: name space decision, there is only one name space per file. trafo path are exceptions?
- design: ~readability and style: `:verbose` version of single char keywords!? (see extensions)~
- design: clarify stuff inside the root `#`? or use `%` for specific purpose?
- design: extension for preprocessed (merged and trafo).
- dynamic: python compiler
- static: python compiler
- design: variants, i.e. form in progress vs final form with more constraints?
- design: extensions could allow synonyms enabling JSON Model l10n?
- tests: declaration of the meta model?
- feature: accept js suffix as input, possibly removing comments.
- feature: add `--auto` option to automatically extract url mappings
- static: generate separate `check_model` root function and simplify code.
- tests: recheck existing tests in rwt
- static: deterministic set output
- dynamic: fix output instability
- python: pyright
- python: ruff
- python: flake8
- refactor: move basic script pre processing as functions
- tests: test schemas and values with jsu
- extend: `.schema` extension to add JSON Schema specific stuff, and `.mo` and `.in`
- tests: rename without explicit `-v2`
- python: remove global list in Symbols
- tests: move bads up
- tests: move bads data to bads directory
- feature: use `-` for standard input and output
- feature: yaml file input
- tests: working `make check`
- tests: make check for bads
- tests: add malformed bad models
- tests: with an actual url! (hello2)
- python: rename `types.py` which is a pain
- feature: yaml url input
- tests: True/False -> PASS/FAIL
- feature: ~how to remove a definition? nope, must be nullified (eg `$NONE`) because refs~
- tests: upgrade all models in `models/` and check them as well
- tests: add expected "$schema" value to schema models
- static: do not inline unused support function (`is_valid_*` and possibly others)
- schema: control keyword sorting to put type-related stuff on top (-ns)
- static: use mandatory keyword parameters where appropriate
- feature: clarify and implement options management `JSON_MODEL_…`
- feature: allow scalar value for `/`
- schema: test output json schema (strict) conformity
- jmc: use exclusive options where appropriate
- tests: check all models wrt to the meta model, once
- static: remove pyright asserts from generated code
- schema: warn when generating schema with strict options
- pr: submit with _JSU_ as JSON Schema tool (export feature) (_PR 1636_)
- static: add option to report where it fails (aka reasons)
- static: fast vs slow with path and reasons (if rep is _None_)
- static: update path
- feature: --format yaml to show yaml instead of json
- design: official (meta) model url: ~`https://models.json-model.org/...`~ vs `https://json-model.org/models/...`
- static: optimize simple regex cases (from Blaze paper)
- python: remove global list in JsonModel
- python: remove all globals in Symbols and JsonModel
- static: generate executable script with minimal main
- jmc: add option `-J` to show json IR, set default to `-P` (preprocessed)
- jmc: change default to `-ns` (unsorted json properties)
- jmc: also use prettyprint options for yaml generation
- static: add a `_` to the default prefix to separate exports
- static: rename all internal stuff with a `_` prefix
- python: refactor in optim analyze merge…
- feature: warn when mixing loose/strict int/float
- feature: implement `$UUID` predef
- backend: remove `decl_` variants
- feature: make static compiled exported defs accessible…
- frontend: select named model with `--name name`
- frontend: use `--list` to show available models
- jmc: add option `--name` to control name of generated function
- frontend: add `--version` or `-v` to show jmc version
- backend: add free
- backend: no path option generation in `Language`
- c-backend: path previous and next, and back and forth scan
- c-backend: add report collection with path
- frontend: add option `-r` to collect report.
- input: accept raw js, not just json with comments
- c-backend: main API does not need to know about internal structs.
- frontend: report init errors.
- py-backend: fix nested if in inlined code generation.
- c-backend: unique shortcut while sorting
- c-backend: json anything comparison for sorting and searching
- static: constant string and int enum
- c-backend: unique for any
- static: or implementation
- static: object disjunction on str
- static: support or constants, aka enum.
- static: object disjunction on int, bool, float, null
- jmc: allow value checking under `-X -F py`
- api: load model from file, load model from string…
- py-frontend: handle test vector files
- c-frontend: handle test vector files
- c-backend: separate headers and functions to allow compiling a support library.
- backend: move runtime in a runtime directory.
- backend: working c and py "$REGEX".
- tests: check test vector files
- py-backend: import runtime.
- static: generate separate lib
- backend: clarify runtime vs data.
- c-backend: fix `-l` implementation.
- all: remove dynamic compiler code, tests and doc.
- tests: values with name field
- static: xor code generation
- c-backend: issue with "$xxx" properties, `char*` is not `json_t*` (`ex_08 ex_09`)
- py-backend: improve url validation
- frontent: add `-T 1000` to trigger measuring performance.
- static: unique constraint
- static: cmp constraint implementation
- python: use local loose settings if appropriate (but not with inlining!)
- tests: remove SO stuff
- python: remove `static.py`
- jmc: remove `-S`
- doc: remove about S
- optim: predef normalization and or/and included type cleanups
- tests: parallelism with `pytest-xdist`
- c-backend: heterogeneous enum (`enum_05`)
- py-backend: unique for any
- backend: fix `untype00` issue (c, py)
- c-backend: simplify entry by moving parts to `json-model.c`
- tests: remove `.x.`
- tests: add `tmp_dir` fixture.
- tests: improve compilation locking for parallel pytest.
- tests: split modval directory for better parallelization (wip)
- tests: refactor all tests with `pytest` to avoid SSD file delete/create cycles (wip)
- project: switch version to beta.
- tests: drop `fuzzy` name, re-test for stricter versions
- tests: chunk tests in smaller directories to please xdist
- jmc: add test vector mode with `--test-vector`
- tests: fix `wip/obj_04` (double processing from `jmc` yielded to more substitions)
- tests: fix `wip/openapi-310-models`
- tests: optimized openapi-310-models should have fully removed schema stuff
- static: optimize 1 must or may property case with a direct comparison
- static: choose threshold for switching between few/may must/may props
- static: reuse already generated may/must maps when possible (under `--map-share`)
- static: ~use common must/may map with must/may boolean? maybe not?~
- c-backend: fast `$REGEX` implementation based on re2 syntax
- c-frontend: allow to switch between the C slow and fast `$REGEX` implementations
- c-frontend: use `getopt_long` instead of `getopt`
- static: reporting clean slate on or when one is found!
- static: add option to skip reporting generation `--no-report`
- frontend: improve performance measures with stdev and removing overheads
- jmc: allow direct compilation with cc-like options?
- static: report missing must props
- jmc: rethink option usage for compilation
- jmc: allow to pass actual compiler options?
- static: disjunct could share identical may/must tabs between objects (optional)
- c-backend: also prefix type name and extensions with `jm_`
- static: use `[.]` for root in error messages
- static: simplify unexpected prop message
- jmc: generate executable python script
- jmc: make `-O` the default, add `-nO` to disable.
- frontend: align python and C pass/fail outputs
- static: fix `untyped...` with `value_len` when type is unknown
- static: fast mode, check that it returns as early as possible (or, xor, and, obj, arr)
- backend: move python-specifics from `language.py` to `python.py`
- backend: ~report which several xor succeeded? no, implicit with rejects~
- tests: run with dynamic python
- tests: run generated schema (partial)
- schema: ~nearly always add explicit `"$schema"` property, nope, fixed in tests?~
- schema: fix `untype00` schema
- optim: detect non feasible constraints wrt values
- optim: remove unfeasible `!=`
- python: refactoring, drop `Validator` class
- python: refactoring, remove `defines.py` and `validator.py`
- design: regex recursion extension `"/^/($REGEX)/\$/X"`
- design: more use-case related predefs: `"$EMAIL"`, `"$URI"`
- c-backend: get rid of `mktime` for fast date validation
- design: add `$EXREG' for JSON Model extended regex
- c-backend: see [jansson](https://jansson.readthedocs.io/en/latest/), avoid cJSON
- c-backend: predefs for $DATE, $URL, $REGEX
- backend: report errors
- python: cleanup ultimate model reliance on local defs
- backend: switch all `Inst` functions to `Block` to simplify code concatenation
- static: prioritize c for speed, js for usability
- js-backend: fix unique for non scalars (still 0 === 0.0)
- tests: move `FOO-check.out` to `FOO.check`
- js-backend: allow to generate a module only, with `mjs`
- py-backend: allow to generate a simple module only, with `mpy`
- c-backend: allow to generate a simple object file only
- command: rethink code/executable/module generation options
- js-backend: add javascript backend and runtime and working tests
- c-backend: add `qsort_r` code for Windows and MacOS (blind)
- backend: add `path` and `rep` to str functions
- tests: fix strange issue with `make check` in `mv-03`
- docs: add a tutorial tour
- js-backend: add official [npm module](https://www.npmjs.com/package/json_model_runtime) on `npmjs`.
- design: add `"$DATETIME"` and `"$TIME"`
- command: regex engine selection
- c-backend: add `re2` support
- c-backend: default to `re2`
- js-backend: add `re2` (backend, node only) support
- command: allow `-I` and `-L` for C compilation
- static: re optimize `^...` using starts with when possible (idea from blaze paper)
- static: re optimize `...$` and `^...$`
- pr: collect cloc about compiler (parts) and runtimes
- design: allow merge to handle `$ANY` values on one side
- design: import definitions with `<` in `%`
- command: check loose option propagation
- c-frontend: add support for `jsonl`
- static: optimize open must/may prop checks by dropping loop
- static: implement varlen
- py-frontend: add support for `jsonl`
- js-frontend: add support for `jsonl`
- py-frontend: add specific `--jsonschema-benchmark` option
- js-frontend: add specific `--jsonschema-benchmark` option
- design: add more predefs such as `OBJECT` or `ANYOBJECT`, `ARRAY` or `ANYARRAY`? NO.
- sql-backend: generate PL/pgSQL functions to validate JSONB data
- sql-backend: add generic entry function
- sql-backend: add testing capability
- sql-backend: add necessary support function (nearly)
- sql-backend: implement basic regex
- tests: add sql to pytest
- tests: parallelize sql checks in makefile
- sql-backend: implement extended regex
- tests: add sql.check to pytest
- tests: parallelize sql checks in pytest
- tuto: add PL/pgSQL entry
- python: rerun type check (some ignore added, but a few fixes as well)
- python: rerun style check (ruff, drop microsoft uncooperative flake8)
- design: add import `<` with scalar
- js: ~allow to run with nvm stable?~ nope, nvm is a shell function, must use path
- sql-backend: reduce extension loading verbosity
- model: warn on url-looking definitions
- tests: improve meta model for constants, predefs and regex/X (`rwt/json-model.model.json`)
- tests: fix test vector numbering to count actual tests, not items
- schema: improve generation with some constraints
- tests: fix `mv-0a/base-021.model.json` issue with C json-model
- tuto: add further reading pointers in the conclusion
- static: keep some model comments in generated code
- schema: generate valid schema from JSON Model meta-model
- python: fix internal checker on test cases
- js-backend: warn about strict/loose
- sql-backend: warn about strict/loose
