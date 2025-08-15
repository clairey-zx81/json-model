# JSON Model Compiler

## CLOC

- Compiler (including 6 code generators): 6900 py-locs
- Runtimes
  - Python: 430 py-locs
  - C: 1500 c-locs
  - JS: 430 js-locs
  - Perl: 690 pl-locs
  - PL/pgSQL: 230 sql-locs
  - Java: 1200 java-locs

## Files

- [model](./model.py) model representation and preprocessing
- [xstatic](./xstatic.py) model compilation
- [language](./language.py) code generator abstraction
  - [python](./python.py) Python code generator
  - [clang](./clang.py) C code generator
  - [javascript](./javascript.py) JS code generator
  - [plpgsql](./plpgsql.py) PL/pgSQL code generator
  - [perl](./perl.py) Perl code generator
  - [java](./java.py) Java code generator
- [resolver](./resolver.py)
  [url_cache](./url_cache.py) URL management
- [script](./script.py) frontend
- [convert](./convert.py) conversion to JSON Schema
- [utils](./utils.py)
  [analyze](./analyze.py)
  [mtypes](./mtypes.py)
  [objmerge](./objmerge.py)
  [optim](./optim.py)
  [recurse](./recurse.py)
  various utilities
- [data/](./data/) partial source code helpers for code generation
- [runtime/](./runtime/) C, Python, JavaScript, Perl, PL/pgSQL and Java runtimes
