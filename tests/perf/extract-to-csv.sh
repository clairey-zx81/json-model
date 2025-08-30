#! /bin/bash

for file ; do
    name=$(basename $file .out | tr '_' ',')
    # echo "name=$name"
    sed -e 's/[^.0-9][^.0-9]*/,/g;s/,\.,/,/g;s/,\.,/,/g;s/,$//g;s/^,//g;' $file |
        while read line ; do
            [[ "$line" == *,* ]] && echo "$name,$line"
        done
done
