#! /bin/bash
#
# extract result figures from run outputs
#

for file ; do
  name=$(basename $file .out | tr '_' ',')
  iter=$(echo $file | sed -e 's,^.*/\([0-9][0-9]*\)/[^/]*$,\1,')
  # echo "name=$name"
  pass=$(grep "PASS" < $file | wc -l)
  fail=$(grep "FAIL" < $file | wc -l)
  echo "$name,$iter,$pass,$fail"
done
