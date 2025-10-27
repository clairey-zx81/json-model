#! /bin/bash
#
# may must open vs map vs unroll
#

export JMC=dev

prefix=test_mmo
opts="--no-reporting --no-predef --cc=clang-20 --may-must-open-ratio=0"

NPS="2 4 6 8 10 12 16 20 24 32 40 48 56 64 72 80 96 112 128 144 160 192 224 256"
LANGS="c out js py java class pl"

for np in $NPS ; do
  # build model with 5/6 chars property names
  {
    echo -n '{"?ABCD0": 0'
    let n=$np
    while let --n ; do
      echo -n ", \"?ABCD$n\": 0"
    done
    echo ", \"\": \"\$ANY\"}"
  } > ${prefix}_$np.model.json
  {
    echo -n "{\"Susie\": 42"
    let n=$np
    while let n-=2 ; do
      echo -n ", \"ABCD$n\": 42"
    done
    echo ", \"Calvin\": 42, \"Hobbes\": 0}"
  } > ${prefix}_$np.value.json
done

for np in $NPS ; do
  model=${prefix}_$np.model.json
  for suffix in $LANGS ; do
    ./jmc $opts --map-threshold=0   --may-must-open-threshold=0   -o ./${prefix}_${np}_MAP.$suffix $model
    ./jmc $opts --map-threshold=$np --may-must-open-threshold=0   -o ./${prefix}_${np}_UNROLL.$suffix $model
    ./jmc $opts --map-threshold=0   --may-must-open-threshold=$np -o ./${prefix}_${np}_MMO.$suffix $model
  done
done
