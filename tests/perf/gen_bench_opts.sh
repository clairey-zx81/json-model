#! /bin/bash
#
# Try desactivating compiler optimization options
#

export JMC=dev
export jmc_bench=dev

jmc_opts="--single-line-regex --no-predef --cc=clang --precompiled"

# parallelism, loop, repeats
bench_opts="-p 16 -l 1000 -r 17 -T c"

# TODO remove --predef?
jmc_common="--single-line-regex --no-predef --cc=clang --precompiled"

function bench()
{
  local name=$1
  shift
  export JMC_OPTS="$jmc_opts"
  [ "$@" ] && JMC_OPTS+=" $@"
  echo "# starting benchmark $name ($JMC_OPTS)" >&2
  ./start_bench.sh $jmc_bench $name $bench_opts
}

# nothing
bench ref

# gnu compiler
bench gcc --cc=cc

# regex engine
bench pcx --regex-engine=pcre2 --no-precompiled
bench slr --no-single-line-regex
bench rxo --no-regex-optimize

# preprocessor optimizations
for oo in srx csp sim flt pev ans aco x2o non ; do
  bench $oo -nOp=$oo
done

# others
bench sco --no-strcmp-optimize
bench set --max-strcmp-cset=0
bench map --map-threshold=0
bench aun --array-unrolling-size=0
bench mmo -mmot=0
bench mot -mot=0
bench omp -omp=0
bench pa0 -pt=0
bench pax -pt=1024

bench ior --no-ir-optimize
