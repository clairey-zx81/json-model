#! /bin/bash
#
# map threshold vs unroll test
#

# JMC=dev JMC_OPTS="--no-predef --cc=clang-20" nohup ./start_bench.sh dev -p 16 -l 1000 -r 7
export JMC=dev

prefix=test_mt
opts="--no-reporting --no-predef --cc=clang-20 --may-must-open-threshold=0 --may-must-open-ratio=0 --must-only-threshold=0"

NPS="1 2 4 6 8 10 12 14 16 20 24 28 32 40 48 56 64 72 80 96 128 160 192 256 384 512 700 800 900 1000"
LANGS="c out js py java class pl"

for np in $NPS ; do
  # build model with 5/6 chars property names
  {
    echo -n '{"?ABCD0": 0'
    let n=$np
    while let --n ; do
      echo -n ", \"?ABCD$n\": 0"
    done
    echo "}"
  } > ${prefix}_$np.model.json
  # look for the one in the middle (approx)
  echo "{\"ABCD$(( $np / 2 ))\": 42}" > ${prefix}_$np.value.json
done

for np in $NPS ; do
  model=${prefix}_$np.model.json
  for suffix in $LANGS ; do
    ./jmc $opts --map-threshold=0 -o ./${prefix}_${np}_MAP.$suffix $model
    ./jmc $opts --map-threshold=$np -o ./${prefix}_${np}_UNROLL.$suffix $model
  done
done
