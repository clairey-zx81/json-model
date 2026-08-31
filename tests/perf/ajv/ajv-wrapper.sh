#! /bin/sh
#
# AJV wrapper for benchmarking purposes
#

helper()
{
  local status=$1
  shift
  echo "usage: $0 [ shell | root | echo | help | version | execute | ... ] [ options and arguments ]"
  exit $status
}

# intersept option
get_opt()
{
  local opt=$1 next= o=
  shift
  for o in "$@" ; do
    [ "$next" ] && { echo $o ; return; }
    [ "x-$o" = "x-$opt" ] && next=1
  done
}

[ "$#" -eq 0 ] && helper 0

case "$1" in
  --help|-h)
    helper 0
    ;;
  version|--version|-v)
    cat /app/.version
    ;;
  node)
    exec "$@"
    ;; 
  # NOTE the docker shell wrapper may intercept this
  shell)
    exec /bin/sh "$@"
    ;;
  optim|compile)
    shift
    # TODO clarify ES5/EC6 CJS/EMS options (--code-es5 --code-esm)
    # TODO allow removing reporting code
    # NOTE --code-source=true: standalone version
    # set useful optimizations options with "optim"
    [ "$1" = "optim" ] && ajv_opts="--messages=false --code-optimize=2 --strict=false" || ajv_opts=""
    # get output file if any
    output=$(get_opt "-o" "$@")
    # actual compilation
    ajv compile $ajv_opts "$@"
    # add benchmarkint main & prettyprint
    [ "$output" ] && {
      {
        echo
        echo 'async function main() {'
        # echo '  const jab = await import("jmc-ajv-bench")'
        echo '  const jab = require("jmc-ajv-bench")'
        echo '  jab.default(validate20)'
        echo '}'
        echo 'main()'
      } >> $output
      prettier --write "$output"
    }
    ;;
  *)
    ajv "$@"
    ;;
esac
