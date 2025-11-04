#! /bin/bash
#
# max strcmp cset test
#

export JMC=dev

prefix=test_cset
opts="--no-reporting --no-predef --cc=clang-20"

SIZES="1 2 3 4 6 8 10 12 16 20 24 28 32 40 48 56 64 96 128 192 256 500 750 1000 1250 1500 1750 2000 2250 2500 2750 3000"
LANGS="c out"

for size in $SIZES ; do
  # build model with 5/6 chars property names
  {
    echo -n '[ {"|": ["_foo"'
    let n=$size
    while let --n ; do
      echo -n ", \"_${n}abc\""
    done
    echo "] } ]"
  } > ${prefix}_${size}.model.json
  sed -ne 's/_//g;s/.*\(\[[^]]*\]\).*/\1/p' < ${prefix}_${size}.model.json > ${prefix}_${size}.value.json
done

for size in $SIZES ; do
  model=${prefix}_${size}.model.json
  for lang in $LANGS ; do
    jmc $opts --max-strcmp-cset=0    -o ./${prefix}_${size}_NOP.$lang $model
    for pt in 0 6 8 16 32 64 128 ; do
      jmc $opts --max-strcmp-cset=8192 --partition-threshold=$pt -o ./${prefix}_${size}_YEP_${pt}.$lang $model
    done
  done
done
