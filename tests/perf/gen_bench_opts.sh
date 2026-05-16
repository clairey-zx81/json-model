#! /bin/bash
#
# Try desactivating compiler optimization options
#

export JMC=dev
export jmc_bench=dev

jmc_opts="--single-line-regex --no-predef --cc=clang --precompiled"

# parallelism, loop, repeats
bench_opts="-p 16 -l 1000 -r 29 -T c"
jmc_common="--single-line-regex --no-predef --cc=clang --precompiled"

# TODO add jsu-model options?

function bench()
{
  local name=$1
  shift
  export JMC_OPTS="$jmc_opts"
  [ "$@" ] && JMC_OPTS+=" $@"
  echo "# starting benchmark $name ($JMC_OPTS)" >&2
  ./start_bench.sh $jmc_bench $name $bench_opts
}

# default
bench ref

# gnu compiler instead of clang
bench gcc --cc=cc

# regex engine and optimization
bench rxe --regex-engine=pcre2 --no-precompiled
bench rxo --no-regex-optimize
bench slr --no-single-line-regex

# all preprocessor optimizations
for opt in srx csp sim flt pev ans aco x2o non ; do
  bench $opt -nOp=$opt
done

# others
bench uni --no-unique-optimize
bench sco --no-strcmp-optimize
bench set --max-strcmp-cset=0
bench map --map-threshold=0
bench aun --array-unrolling-size=0
bench mmo -mmot=0
bench mot -mot=0
bench omp -omp=0
bench pa0 -pt=0
bench pax -pt=1024

bench iro --no-ir-optimize
