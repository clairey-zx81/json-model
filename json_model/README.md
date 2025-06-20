# JSON Model Compiler

## CLOC

- Compiler: 5400 py-locs, including 850 for the 3 code generators (C, Python and JavaScript)
- C runtime: 1250 c-locs
- Python runtime: 375 py-locs
- JS runtime: 350 js-locs

## Files

- [model](./model.py) model representation and preprocessing
- [xstatic](./xstatic.py) model compilation
- [language](./language.py) code generator abstraction
  - [python](./python.py) Python code generator
  - [clang](./clang.py) C code generator
  - [javascript](./javascript.py) JS code generator
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
- [runtime/](./runtime/) C and Python runtimes
- [../js_runtime/](../js_runtime/) JS runtime as a npm module

