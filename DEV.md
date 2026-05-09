# JSON Model Developer Stuff

## Contributions

Beware that the developer documentation is scarce. PR are always welcome, eg:

- new language or library support implementations
- new exporters
- possibly new models
- generated code optimizations

## Publication Accounts

See `publish.*` targets in `Makefile`.

- Sources on [GitHub](https://github.com/clairey-zx81)
- Python Package on [PyPI](https://pypi.org/user/zx80/)
- JavaScript module on [npmjs](https://www.npmjs.com/~calvin-5432)
- Perl module on [CPAN](https://metacpan.org/author/ZXHZ)
- Java Jar on [Maven Central](https://central.sonatype.com/artifact/org.json-model/json-model)
- Postgres extension on [PGXN](https://pgxn.org/user/fabien)
- Docker image on [Docker](https://hub.docker.com/u/zx80)
- Website on [CRI Web](https://www.cri.minesparis.psl.eu/)

## Hardcoded Versions

- [VERSION](./json_model/data/VERSION) (extracted by setuptools at build time)
- [pom](./json_model/runtime/java/pom.xml)
- [pm](./json_model/runtime/pl/JSON/JsonModel.pm) (twice)
- [pg](./json_model/META.json) (twice)
- [js](./json_model/runtime/js/package.json)
- docker tag is extracted from `jmc`
- git tag?

## Developer Setup

Get sources directly from GitHub in some Unix-like terminal:

```sh
git clone --recursive-submodules git@github.com:clairey-zx81/json-model.git
cd json-model
```

If you intend to develop and submit a PR, fork the repos before cloning.

To setup a local developer environment, run at the root of the project:

```sh
# for Python
make dev
source venv/bin/activate
# for JS
npm install
# for Perl
source $PWD/json_model/runtime/pl/env.bash
# for Java
# get needed dependency jars (see pom.xml), then
make -C json_model/runtime/java jar
source $PWD/json_model/runtime/java/env.bash
# for C
# install pcre2, cre2, gnu getopt, jansson
# for SQL
# have psql ready to connect to a local Postgres
```

## Code Doc

Read sources…
The magically-generated [deepwiki](https://deepwiki.com/clairey-zx81/json-model)
Section _The jmc Compiler_ is not too bad for an initial understanding.

## Release Procedure

Procedure for releasing a new python package version:

- consider releasing both JSU and JMC at the same time!
- merge `dev` changes into the `main` branch
- update `json_model/data/VERSION`, `BACKLOG.md` and `VERSION.md`
- `git commit` and `git tag` as new version
- run non-regression tests: `make -C tests check`, fix and squash if necessary
- `make clean.dev && make publish.py`
- test generated package(s) manually:

  ```bash
  cd /tmp
  python -m venv venv
  source venv/bin/activate
  pip install path-to-generated-package.tar.gz
  jmc --version  # should display the new version
  ```

- if okay:
  - push sources and tags: `git push && git push --tags`
  - publish package(s): `twine upload dist/*`
- check `jsonschema-benchmark` container build
- check `bowtie` container build

Note: do not push non released stuff on branch `main`, only use `post` and `dev`
as only these name are supported by Python `packaging.version`.
Not following this rule breaks branch installation from git sources.
