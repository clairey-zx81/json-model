#! /bin/bash
#
# Compare several runs
#

script_dir=$(dirname $0)

function err()
{
  local status=$1
  shift
  echo "$@" >&2
  exit $status
}

[ $# -lt 1 -o "$1" == "-h" -o "$1" == "--help" ] && err 0 "usage: $0 tool [directories…]"

tool=$1
shift

com_files="cases.csv casevalues.csv"
run_files="result.csv perf.csv compile.csv cases.csv casevalues.csv"

echo "# sanity check before proceeding" >&2
[ -e ./perf.db ] && err 2 "cannot overwrite perf.db"

for file in $com_files $run_files ; do
  [ -e "./$file" ] && err 3 "cannot overwrite $file"
done

for dir in "$@" ; do
  [ -d "$dir" ] || err 4 "missing directory: $dir"
  for file in $com_files $run_files ; do
    [ -f "$dir/$file" ] || err 5 "missing csv file: $dir/$file"
  done
done

if [ ! "$@" ] ; then
  err 0 "no directory arguments: nothing to do…"
fi

echo "# extract directory contents" >&2
first=1
for dir in "$@" ; do
  echo "## considering directory: $dir" >&2
  name=${dir#*/}
  # copy common case data
  if [ "$first" ] ; then
    for file in $com_files ; do
      cp "$dir/$file" ./$file
    done
    first=
  fi
  for file in $run_files ; do
    sed -n -e "/,$tool/s/,$tool/,$name/p" < "$dir/$file" >> "./$file"
  done
done

# analysis
echo "# analyzing data…" >&2
sqlite3 ./perf.db \
  ".read $script_dir/perf_init.sql" \
  ".read $script_dir/perf_load.sql" \
  ".read $script_dir/perf_comp.sql"

echo "# result" >&2
sqlite3 ./perf.db "SELECT * FROM ToolSummaryPerf;"
