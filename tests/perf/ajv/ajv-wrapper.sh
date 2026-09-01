#! /bin/bash
#
# AJV wrapper for benchmarking purposes
#

err()
{
  local status=$1
  shift
  echo "$0 error: $@" >&2
  exit $status
}

helper()
{
  local status=$1
  shift
  echo "usage: $0 [ shell | root | echo | help | version | execute | ... ] [ options and arguments ]"
  exit $status
}

# intercept an option
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
    # TODO clarify ES5/EC6 CJS/EMS options (--code-es5 --code-esm)
    # TODO allow removing reporting code, --messages=false does not do the trick
    # NOTE --code-source=true: standalone version
    # set useful optimizations options with "optim"
    [ "$1" = "optim" ] && ajv_opts="--messages=false --code-optimize=2 --strict=false" || ajv_opts=""
    # drop command
    shift
    # get output and input file if any
    output=$(get_opt "-o" "$@") input=$(get_opt "-s" "$@")
    # extract root version
    if [ "$input" ] ; then
      schema=$(jq -r '."$schema"' "$input")
      if [ "$schema" = "https://json-schema.org/draft/2020-12/schema" ] ; then
        ajv_opts+=" --spec=draft2020"
      elif [ "$schema" = "https://json-schema.org/draft/2019-09/schema" ] ; then
        ajv_opts+=" --spec=draft2019"
      elif [ "$schema" = "http://json-schema.org/draft-07/schema#" ] ; then
        ajv_opts+=" --spec=draft7"
      # else unknown or unexpected schema version, defaults to draft7
      fi
    fi
    # actual compilation
    ajv compile "$@" $ajv_opts
    [ $? -eq 0 ] || err $? "ajv compile failed on $input"
    # add benchmarkint main & prettyprint
    if [ "$output" ] ; then
      test -e "$output" || err $? "ajv compile no result on $input"
      test -s "$output" || err $? "ajv compile empty result on $input"
      {
        echo
        echo
        echo "// test schema \"$input\""
        echo 'async function main() {'
        # echo '  const jab = await import("jmc-ajv-bench")'
        echo '  const jab = require("jmc-ajv-bench")'
        echo '  jab.default(validate20)'
        echo '}'
        echo 'main()'
      } >> $output
      prettier --write "$output" || err $? "prettier failed"
    fi
    ;;
  *)
    ajv "$@"
    ;;
esac
