# NAME

jmc - JSON Model Compiler

# SYNOPSIS

```
jmc [-h] [--version] [--debug] [--verbose] [--quiet]
    [--maps MAPS] [--auto] [--entry ENTRY] [--regex-engine {re,re2,pcre2}]
    [--loose-int] [--strict-int] [--loose-float] [--strict-float] [--loose-number] [--strict-number]
    [--check] [-[-no]-optimize] [-[-no]-reporting]
    [--format {json,yaml,py,c,js,plpgsql}] [-[-no]-sort] [--indent INDENT]
    [--gen {exec,module,code,none} | --executable | --module | --code | --no-gen]
    [--cc CC] [--cflags CFLAGS] [--cppflags CPPFLAGS] [--ldflags LDFLAGS]
    [--include [INCLUDE ...]] [--library [LIBRARY ...]] [--define [DEFINE ...]]
    [--name NAME] [-[-no]-report] [--none] [--true] [--false] [--test-vector]
    [--map-threshold MAP_THRESHOLD] [--map-share]
    [--op {P,U,J,N,E,C} | --preproc | --dump | --jdump | --nope | --export | --compile]
    [--output OUTPUT] model [values ...]
```

# DESCRIPTION

JSON Model Compiler command processes a [JSON Model](https://json-model.org/) to
generate modules or scripts in C, JS, Python, PL/pgSQL, or a more-or-less equivalent JSON Schema.

# ARGUMENTS

- `model`: model to process.
- `values...`: list of value files to check.

# OPTIONS

Here are the most useful options:

### Metadata

- `--help` or `-h`: show auto-generated synopsis.
- `--version`: show command version.

### Verbosity

- `--verbose` or `-v`: set verbose mode.
- `--quiet`: set quiet mode, only show warnings.
- `--debug`: set debug mode, which is very verbose.

### Input

- `--maps "URL PATH"` or `-m …`: map remote urls to a local path.
- `--auto` or `-a`: infer url to path mapping from declared model URL (`.$.""`).
- `--check`: whether to check the model for errors at various stages.

### Processing

- `--op {P,U,J,N,E,C}`: operation to run (preproc, dump, jdump, nope, export, compile).
- `--{loose,strict}-{int,float,number}`: whether to assume loose JSON numbers,
  i.e. accept `42.0` as an integer or `42` as a float. Default is strict, but
  JS and PL/pgSQL backends are always loose due to the language and type capabilities.
- `--re RELIB`: regular expression library to use, default is to use `re2` when available,
  else the internal library.
- `--optimize` or `-O`: whether to optimize the model
  (partial eval, constraint simplifications, flattening, dead code elimination,
  xor to or conversion…).

### Output

- `--output FILE` or `-o FILE`: output file, the suffix of which is used
  for setting the default format and generation.
- `--format FMT` or `-F FMT`: output language, to override defaults.
- `--gen GEN`: whether to generate an `exec`utable, a `module`, source `code` or `none`,
  to overide defaults.
- `--entry ENTRY`: name of the entry function to generate.
- `--map-threshold THRESHOLD`: maximum number of props to inline property checks in objects.
- `--map-share`: whether to share common maps, may result in smaller generated code.

### C Compilation

- `--cc COMPILER`: compiler to use, defaut is `cc`.
- `--{cpp,c,ld}flags ...`: set raw cpp, cc or ld flags.
- `-I DIR` `-D VAR=VAL`: cpp include path and definitions.
- `-L DIR`: ld link path.
- `--static`: generate a statically linked executable.

### Testing

When testing values:

- `--name NAME` or `-n NAME`: name of model to use, default is empty string for the root model.
- `--test-vector`: assume a test vector input format for tested values.
- `--none`, `--true` or `--false`: expected result of test values,
  return an error status if unexptected values are encountered.
- `--report`: generate a report about why a value failed. Default is just to say PASS or FAIL.

# AUTHORS

Fabien Coelho (Mines Paris - PSL) and Claire Yannou-Medrala (MESR).

# REPORTING BUGS

Report bugs to [JSON Model Issues](https://github.com/clairey-zx81/json-model/issues).

# COPYRIGHT

This software is dedicated to the public domain.

# SEE ALSO

- [JSON Model on GitHub](https://github.com/clairey-zx81/json-model)
- [ADBIS 2024 Paper](https://www.cri.minesparis.psl.eu/classement/doc/A-817.pdf)
- [DBA 2023 Paper](https://www.cri.minesparis.psl.eu/classement/doc/A-794.pdf)
- [Initial Design 2023 Technical Report](https://www.cri.minesparis.psl.eu/classement/doc/A-795.pdf)
