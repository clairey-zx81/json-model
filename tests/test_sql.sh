#! /bin/bash
#
# test wrapper for SQL generated script
#

dir=$(dirname $0)
[ "$dir" ] && PATH="$dir:$PATH"

sql=$1 status=0 format= report=
shift

while [[ $1 == -* ]] ; do
  case $1 in
    --test|-t)
      format=t
      ;;
    --report|-r)
      report=1
      ;;
    --no-report)
      report=
      ;;
    -tr)
      format=t
      report=1
      ;;
    *)
      echo "unexpected option: $1" >&2
      exit 1
      ;;
  esac
  shift
done

out="${TMPDIR:-/dev/shm}/jm_test_$$.out"
db="jm_test_$$"

createdb $db || {
  echo "cannot create $db" >&2
  exit 2
}

# load runtime and model checking functions
psql --no-psqlrc -q -f $sql $db >&2
status=$?

function json2csv()
{
  jq -c < "$1" | sed 's/"/""/g'
}

for file ; do
  if [[ "$file" == *.values.json ]] ; then
    "$dir"/values2csv.py $file
  else
    json=$(json2csv $file)
    expect=true
    [[ "$file" == *.false.json ]] && expect=false
    echo "$expect,,\"$json\""
  fi | psql --no-psqlrc -v input="$file" -f "$dir"/test_sql_csv.sql $db > $out
    ok=$?
  [ $ok -ne 0 ] && status=$ok
  [ "$(grep ERROR $out)" ] || status=1
  cat $out
  rm -f $out
done

dropdb $db >&2
exit $status
