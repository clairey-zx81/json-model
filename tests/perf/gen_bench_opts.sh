#! /bin/bash
#
# Try desactivating compiler optimization options
#

export JMC=main
export JSB_DIR=$HOME/perf/jsb_dir
export POD_PULL=0

jmc_bench=main

if [ ! -d $JSB_DIR ] ; then
  git clone https://github.com/sourcemeta-research/jsonschema-benchmark.git $JSB_DIR || exit 1
fi

# default JMC options
jmc_opts="--single-line-regex --no-predef --cc=clang --precompiled --short-version"

# parallelism, loop, repeats, tasks, unshift
# 20: around 80-85% load on calcutta (24 cores, HT off), temperature <= 64°C (2.4GHz)
bench_opts="-p 20 -l 1000 -r 47"

# start a bench run with the expected setup
# NOTE that environment JMC JSB_DIR POD_PULL also affect the run
function bench()
{
  local bench=$1 name=$2
  shift 2

  export JMC_OPTS="$jmc_opts"
  [ $# -ge 1 ] && JMC_OPTS+=" $@"

  # append a counter if the bench directory already exists
  if [ -e "$name" ] ; then
    local n=1
    while [ -e "$name.$n" ] ; do
      let n++
    done
    name="$name.$n"
  fi

  echo "# starting benchmark $name ($JMC_OPTS)" >&2
  ./start_bench.sh $jmc_bench $name $bench_opts -T $bench
}

# insist on defaults
bench c ref
bench c ref

# default gnu compiler instead of clang
bench c clg --cc=cc --mark="gcc"

# regex engine and optimization
bench c rxe --regex-engine=pcre2 --no-precompiled --mark="pcre2"
bench c rxo --no-regex-optimize
bench c rxp --no-regex-pattern
bench c slr --no-single-line-regex

# default 2
bench c ref

# all preprocessor optimizations
for opt in srx csp sim flt pev ans aco x2o non ; do
  bench c $opt -nOp=$opt
done

# default 3
bench c ref

# c-backend
bench c uni --no-unique-optimize
bench c sco --no-strcmp-optimize
bench c set --max-strcmp-cset=0

# xstatic AST generation
bench c sho --no-call-shortcut
bench c map --map-threshold=0
bench c aun --array-unrolling-size=0
bench c mmo -mmot=0
bench c mot -mot=0
bench c omp -omp=0
bench c pa0 -pt=0
bench c pax -pt=1024
bench c dis --no-disjunction
bench c abo --no-all-but-one
bench c mba --no-missing-basics
bench c xrp --no-xor-repeats
bench c xin --no-xor-is-not
bench c hol --no-homogeneous-list

# IR
bench c iro --no-ir-optimize

# for reference
bench b blz

# again
bench c ref

# show a summary
echo "# benches completed"
grep "speed B" */*.md | sort -t"|" -k3nr

# always 1.0 on single tool runs…
# grep "ratio avg" */*.md | sort -t"|" -k3nr
