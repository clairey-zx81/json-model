#! /bin/bash
#
# must only vs unrolled vs map
#

export JMC=dev

prefix=test_mo
opts="--no-reporting --no-predef --cc=clang-20 --may-must-open-threshold=0 --may-must-open-ratio=0"

NPS="1 2 3 4 6 8 10 12 14 16 20 24 28 32 36 40 44 48 56 64 72 80 88 96 104 128 192 256 384 512"
LANGS="c out js py java class pl"

for np in $NPS ; do
  # build model with 5/6 chars property names
  {
    echo -n '{"ABCD0": 0'
    let n=$np
    while let --n ; do
      echo -n ", \"ABCD$n\": 0"
    done
    echo "}"
  } > ${prefix}_$np.model.json
  cp ${prefix}_$np.model.json ${prefix}_$np.value.json
done

for np in $NPS ; do
  model=${prefix}_$np.model.json
  for suffix in $LANGS ; do
    ./jmc $opts --map-threshold=0 --must-only=0 -o ./${prefix}_${np}_MAP.$suffix $model
    ./jmc $opts --map-threshold=$np --must-only=0 -o ./${prefix}_${np}_UNROLL.$suffix $model
    ./jmc $opts --map-threshold=0 --must-only=$np -o ./${prefix}_${np}_MUSTONLY.$suffix $model
  done
done
