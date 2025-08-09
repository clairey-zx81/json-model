#! /bin/bash
#
# run test from java source
#

path=$1
shift

function err()
{
    echo "$2" >&2
    exit $1
}

tmpdir="${TMPDIR:-/dev/shm}/$USER/$$"
name=$(basename $path .java)
name=${name//-/_}
src="$tmpdir/$name.java"

mkdir -p "$tmpdir" || err 1 "cannot create test directory: $tmpdir"
cp "$path" "$src" || err 2 "cannot copy source $path: $src"

javac -d "$tmpdir" "$src"
status=$?
[ $status -eq 0 ] || err $status "java compilation failed for $name at $path: $status"

CLASSPATH="$tmpdir:$CLASSPATH" java $name "$@"
status=$?

cd ../..
rm -rf "$tmpdir" || err 4 "cannot cleanup test directory for $name: $tmpdir"

exit $status
