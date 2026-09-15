#! /bin/bash
#
# generate BENCH.md page with links to available benchmarks
#

MAX=10
PYPI="https://pypi.org/project"

# extract version from file
get_version()
{
  local what=$1 file=$2
  local line=$(grep "$what version:" < $file)
  line=${line#*:\*\* }
  line=${line%% *}
  echo $line
}

# up to artifact list
sed -ne '1,/BENCHES/p' < BENCH.md | grep -v '^BENCHES$'

# list max 10 latest artifacts
nartifacts=0

for artifact in $(ls site/benchmarks/*.md | sort -r) ; do
  let nartifacts+=1

  link=${artifact#site/}
  name=${link#benchmarks/}
  name=${name%.md}
  jsu=$(get_version jsu $artifact)
  jmc=$(get_version jmc $artifact)
  sbc=$(get_version jsonschema-cli $artifact)
  message=""
  [ "$(grep 'content:.*yes' $artifact)" ] && message+="content" || message+="no content"
  [ "$(grep 'JSU_OPT.*--no-id' $artifact)" ] && message+=", no id" || message+=", id"
  [ "$(grep 'fix:.*yes' $artifact)" ] && message+=", fix" || message+=", no fix"
  echo "- Artifact [$name]($link) using [JMC $jmc]($PYPI/json-model-compiler/$jmc/), "
  echo "  [JSU $jsu]($PYPI/json-schema-utils/$jsu/) and "
  echo "  [SBC $sbc](https://github.com/sourcemeta/jsonschema/releases/tag/v$sbc), "
  echo "  $message."

  [ $nartifacts -eq $MAX ] && break
done

# after artifact list
sed -ne '/BENCHES/,$p' < BENCH.md | grep -v '^BENCHES$'
