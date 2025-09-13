#! /bin/bash
#
# keep well-formed line from compilation performance output
#

# test,tool,ts.process,perf
cat "$@" |
  exec grep -E '^[-a-zA-Z0-9_]*,[-a-zA-Z0-9_]*,[0-9.]*,[0-9][0-9.]*$'
