#! /bin/bash
#
# extract performance figures from run outputs
#

for file ; do
    name=$(basename $file .out | tr '_' ',')
    # echo "name=$name"
    sed -e 's/ui5/uiF/;s/cql2/cqlT/;s/draft-04/draftZF/;s/[^.0-9][^.0-9]*/,/g;s/,\.,/,/g;s/,\.,/,/g;s/,$//g;s/^,//g;' $file | 
        while read line ; do
            [[ "$line" == *,* ]] && echo "$name,$line"
        done | grep -E "^[-a-zA-Z0-9_]*,[-a-zA-Z_]*,[0-9]+,[0-9.]+,[0-9.]+,[0-9.]+$"
done
