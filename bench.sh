#! /bin/bash
#
# generate BENCH.md page with links to available benchmarks
#

get_version()
{
  local what=$1 file=$2
  local line=$(grep "$what version:" < $file)
  line=${line#*:\*\* }
  line=${line%% *}
  echo $line
}

sed -ne '1,/BENCHES/p' < BENCH.md | grep -v '^BENCHES$'

for artifact in $(ls site/benchmarks/*.md | sort -r) ; do
  link=${artifact#site/}
  name=${link#benchmarks/}
  name=${name%.md}
  jsu=$(get_version jsu $artifact)
  jmc=$(get_version jmc $artifact)
  sbc=$(get_version jsonschema-cli $artifact)
  message=""
  [ "$(grep 'content:.*yes' $artifact)" ] && message+="content" || message+="no content"
  [ "$(grep 'JSU_OPT.*--no-id' $artifact)" ] && message+=", no id"
  [ "$(grep 'fix:.*yes' $artifact)" ] && message+=", fix" || message+=", no fix"
  echo "- artifact [$name]($link) JSU $jsu/JMC $jmc vs SBC $sbc, $message."
done

sed -ne '/BENCHES/,$p' < BENCH.md | grep -v '^BENCHES$'
