#! /bin/bash
#
# extract result figures from run outputs
#

for file ; do
    name=$(basename $file .out | tr '_' ',')
    # echo "name=$name"
    pass=$(grep "PASS" < $file)
    fail=$(grep "PASS" < $file)
    echo "$name,$pass,$fail"
done
