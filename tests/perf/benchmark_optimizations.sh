#! /bin/bash
#
# Try desactivating compiler optimization options
#

export JMC=dev
export jmc_bench=dev

jmc_opts="--single-line-regex --no-predef --cc=clang --precompiled"

# parallelism, loop, repeats
bench_opts="-p 16 -l 1000 -r 3 -T c"

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
bench cc --cc=cc

# regex engine
bench pcre --regex-engine=pcre2 --no-precompiled
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

# simple typed arrays
bench au --array-unrolling-size=0
bench ior --no-ir-optimize
