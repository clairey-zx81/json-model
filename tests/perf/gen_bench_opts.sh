#! /bin/bash
#
# Try desactivating compiler optimization options
#

export JMC=dev
export JSB_DIR=$PWD/jsb_dir
export POD_PULL=

jmc_bench=dev

if [ ! -d ./jsb_dir ] ; then
  git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git ./jsb_dir || exit 1
fi

# default JMC options
jmc_opts="--single-line-regex --no-predef --cc=clang --precompiled --short-version"

# parallelism, loop, repeats, tasks
bench_opts="-p 20 -l 1000 -r 47 -T c"

# start a bench run with the expected setup
# NOTE that environment JMC JSB_DIR POD_PULL also affect the run
function bench()
{
  local name=$1
  shift
  export JMC_OPTS="$jmc_opts"
  [ $# -ge 1 ] && JMC_OPTS+=" $@"
  echo "# starting benchmark $name ($JMC_OPTS)" >&2
  ./start_bench.sh $jmc_bench $name $bench_opts
}

# insist on defaults
bench rf0
bench rf1
bench rf2
bench rf3

# default gnu compiler instead of clang
bench clg --cc=cc

# regex engine and optimization
bench rxe --regex-engine=pcre2 --no-precompiled
bench rxo --no-regex-optimize
bench rxp --no-regex-pattern
bench slr --no-single-line-regex

# all preprocessor optimizations
for opt in srx csp sim flt pev ans aco x2o non ; do
  bench $opt -nOp=$opt
done

# c-backend
bench uni --no-unique-optimize
bench sco --no-strcmp-optimize
bench set --max-strcmp-cset=0

# xstatic AST generation
bench sho --no-call-shortcut
bench map --map-threshold=0
bench aun --array-unrolling-size=0
bench mmo -mmot=0
bench mot -mot=0
bench omp -omp=0
bench pa0 -pt=0
bench pax -pt=1024
bench dis --no-disjunction
bench abo --no-all-but-one
bench mba --no-missing-basics
bench xrp --no-xor-repeats
bench xin --no-xor-is-not
bench hol --no-homogeneous-list

# IR
bench iro --no-ir-optimize
