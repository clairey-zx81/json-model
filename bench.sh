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
nartifacts=0 p_jsu= p_jmc= p_sbc= p_crv= p_msg=

for artifact in $(ls site/benchmarks/*.md | sort -r) ; do

  jsu=$(get_version jsu $artifact)
  jmc=$(get_version jmc $artifact)
  sbc=$(get_version jsonschema-cli $artifact)
  crv=$(get_version corvus-cli $artifact)

  msg=""
  [ "$(grep 'content:.*yes' $artifact)" ] && msg+="content" || msg+="no content"
  [ "$(grep 'JSU_OPT.*--no-id' $artifact)" ] && msg+=", no id" || msg+=", id"
  [ "$(grep 'fix:.*yes' $artifact)" ] && msg+=", fix" || msg+=", no fix"

  # skip same version (details may differ, keep first encountered)
  [ "$jsu" = "$p_jsu" -a "$jmc" = "$p_jmc" -a \
    "$sbc" = "$p_sbc" -a "$crv" = "$p_crv" -a "$msg" = "$p_msg" ] && continue

  p_jsu=$jsu p_jmc=$jmc p_sbc=$sbc p_crv=$crv p_msg=$msg

  link=${artifact#site/}
  name=${link#benchmarks/}
  name=${name%.md}

  echo "- Artifact [$name]($link) using"
  echo "  [JMC $jmc]($PYPI/json-model-compiler/$jmc/), "
  echo "  [JSU $jsu]($PYPI/json-schema-utils/$jsu/), "
  [ "$sbc" ] && echo "  [SBC $sbc](https://github.com/sourcemeta/jsonschema/releases/tag/v$sbc),"
  [ "$crv" ] && echo "  [Corvus $crv](https://corvus-oss.org/Corvus.JsonSchema/),"
  echo "  $msg."

  let nartifacts+=1
  [ $nartifacts -eq $MAX ] && break
done

# after artifact list
sed -ne '/BENCHES/,$p' < BENCH.md | grep -v '^BENCHES$'
