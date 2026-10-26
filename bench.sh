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
nartifacts=0 p_jsu= p_jmc= p_sbc= p_crv=

for artifact in $(ls site/benchmarks/*.md | sort -r) ; do

  jsu=$(get_version jsu $artifact)
  jmc=$(get_version jmc $artifact)
  sbc=$(get_version jsonschema-cli $artifact)
  crv=$(get_version corvus-cli $artifact)

  # skip same version (details may differ, keep first encountered)
  [ "$jsu" = "$p_jsu" -a "$jmc" = "$p_jmc" -a "$sbc" = "$p_sbc" -a "$crv" = "$p_crv" ] && continue

  p_jsu=$jsu p_jmc=$jmc p_sbc=$sbc p_crv=$crv

  link=${artifact#site/}
  name=${link#benchmarks/}
  name=${name%.md}

  message=""
  [ "$(grep 'content:.*yes' $artifact)" ] && message+="content" || message+="no content"
  [ "$(grep 'JSU_OPT.*--no-id' $artifact)" ] && message+=", no id" || message+=", id"
  [ "$(grep 'fix:.*yes' $artifact)" ] && message+=", fix" || message+=", no fix"
  echo "- Artifact [$name]($link) using"
  echo "  [JMC $jmc]($PYPI/json-model-compiler/$jmc/), "
  echo "  [JSU $jsu]($PYPI/json-schema-utils/$jsu/), "
  [ "$sbc" ] && echo "  [SBC $sbc](https://github.com/sourcemeta/jsonschema/releases/tag/v$sbc),"
  [ "$crv" ] && echo "  [Corvus $crv](https://corvus-oss.org/Corvus.JsonSchema/),"
  echo "  $message."

  let nartifacts+=1
  [ $nartifacts -eq $MAX ] && break
done

# after artifact list
sed -ne '/BENCHES/,$p' < BENCH.md | grep -v '^BENCHES$'
