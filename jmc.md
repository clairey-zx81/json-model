# NAME

jmc - JSON Model Compiler

# SYNOPSIS

```
jmc [-h] [--version] [--debug] [--verbose] [--quiet]
    [--maps MAPS] [--auto] [--name NAME] [--entry ENTRY] [--regex-engine {re,re2,pcre2}]
    [--loose-int] [--strict-int] [--loose-float] [--strict-float] [--loose-number] [--strict-number]
    [--format {json,yaml,py,c,js,plpgsql}] [-[-no]-sort] [--indent INDENT]
    [--executable] [--module] [--code] [--no-gen] [--reporting] [--no-reporting]
    [--cc CC] [--cflags CFLAGS] [--cppflags CPPFLAGS] [--ldflags LDFLAGS]
    [--include [INCLUDE ...]] [--library [LIBRARY ...]] [--define [DEFINE ...]]
    [-[-no]-report] [--none] [--true] [--false] [--test-vector]
    [--check] [--optimize] [--no-optimize] [--map-threshold MAP_THRESHOLD]
    [--map-share] [--op {P,U,J,N,E,C} | --preproc | --dump | --jdump | --nope | --export | --compile]
    [--output OUTPUT] model [values ...]
```

# DESCRIPTION

JSON Model Compiler command processes a [JSON Model](https://json-model.org/) to
generate modules or scripts in C, JS, Python, PL/pgSQL, or a more-or-less equivalent JSON Schema.

# OPTIONS

TODO

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
