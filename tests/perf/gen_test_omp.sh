#! /bin/bash
#
# or must property tests : is -omp strategy beneficial?
#
# - or-list length: LE + 1
# - nb props: 2 SZ + 2
#
# LE SZ  C JS PY JV PL
#
#  1  0  N  Y  y  y  =
#  1  1  N  Y  y  y  =
#  1  2  n  Y  y  y  =
#  1  3  n  Y  y  y  =
#  1  4  n  Y  y  y  =
#  1  5  n  Y  y  y  =
#  2  0  n  Y  Y  Y  y
#  2  1  n  Y  Y  Y  y
#  2  2  n  Y  Y  Y  y
#  2  3  n  Y  Y  Y  y
#  2  4  n  Y  Y  Y  y
#  2  5  n  Y  Y  Y  ~
#  3  0  n  Y  Y  Y  Y
#  3  1  ~  Y  Y  Y  Y
#  3  2  y  Y  Y  Y  Y
#  3  3  y  Y  Y  Y  Y
#  3  4  Y  Y  Y  Y  Y
#  3  5  Y  Y  Y  Y  Y
#  4  0  ~
#  4  1  y
#  4  2  y
#  4  3  Y
#  4  4  Y
#  4  5  Y
#  6  0  y
#  6  1  Y
#  6  2  Y
#  6  3  Y
#  6  4  Y
#  6  5  Y
#  8  0  y
#  8  1  Y
#  8  2  Y
#  8  3  Y
#  8  4  Y
#  8  5  Y
# 12  0  y
# 12  1  Y
# 12  2  Y
# 12  3  Y
# 12  4  Y
# 12  5  Y

export JMC=dev

prefix=test_omp
opts="--no-reporting --no-predef --cc=clang-20 --loose"

# or-list length
LENS="1 2 3 4 5 6 7 8 12"
# number of properties (actual is 2*size + 2)
SIZES="0 1 2 3 4 5"
# targets
LANGS="c out js py java class pl"

for len in $LENS ; do
  for size in $SIZES ; do
    name="${prefix}_${len}_${size}"
    {
      echo "[ {\"|\":"
      echo -n " [ {\"_d\": 0, \"?may\": 0}"
      let l=$len
      while let l-- ; do
        echo -n ", {\"_foo\": 0"
        # mandatory properties
        let n=$size
        while let n-- ; do
          echo -n ", \"_${n}must\": 0"
        done
        # discriminant property
        echo -n ", \"_d$l\": 0"
        # optional properties
        let n=$size
        while let n-- ; do
          echo -n ", \"?${n}may\": 0"
        done
        echo -n "}"
      done
      echo " ]"
      echo " } ]"
    }  > $name.model.json
    sed -n "2s/[?_]//g;2s/, .[0-9]*[02348]may.: 0//g;2p" < $name.model.json > $name.value.json
  done
done

for len in $LENS ; do
  for size in $SIZES ; do
    name="${prefix}_${len}_${size}"
    for lang in $LANGS ; do
      jmc $opts -omp -o ./${name}_OMP.$lang $name
      jmc $opts -nomp -o ./${name}_NOMP.$lang $name
    done
  done
done
