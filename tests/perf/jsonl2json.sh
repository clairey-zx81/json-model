#! /bin/bash
#
# split jsonl files into json files
#

for jsonl ; do
  prefix="$(dirname $jsonl)/$(basename $jsonl .jsonl)"
  lines=$(wc -l < $jsonl)
  echo "# splitting $jsonl ($lines)"
  n=0
  while [ $n -lt $lines ] ; do
    let n+=1
    sed -n "${n}p" $jsonl | jq > "$prefix-$n.json"
  done
done
