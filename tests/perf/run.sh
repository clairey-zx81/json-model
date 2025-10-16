#! /bin/bash
#
# execute jmc bench bite
#
# arguments:
# - loop: number of performance loop iterations, eg 1000 or 10000
# - prefix: directory where to write results
# - task: cmp ou all = cmp + run
# - target: implementation/phase to run (all, jmc, jmc-*, blaze)
# - dirs: jsb schema directories to process
#
# env:
# - JMC_BENCH_DEBUG: enable debug (FIXME unused)
# - JMC_BENCH_TIME_FMT: time format performance to report (default %e)

export PATH=$PATH:.
export TMPDIR=.

# docker wrappers
jmc=jmc
js_cli=js-cli
jsu_model="$jmc exec jsu-model"
jsu_simpler="$jmc exec jsu-simpler"
time_fmt=${JMC_BENCH_TIME_FMT:-%e}

now=$(date +%Y%m%d%H%M%S.$$)
debug=$JMC_BENCH_DEBUG

function err()
{
  local status=$1
  shift
  echo "$@" >&2
  exit $status
}

#
# handle arguments
#

[ $# -ge 4 ] || err 1 "usage: $0 loop prefix task target"

LOOP=$1 PREFIX=$2 TASK=$3 TARGET=$4
shift 4

case $TASK in
  all) do_cmp=1 do_run=1 ;;
  cmp) do_cmp=1 do_run= ;;
  # TODO run with pre-compiled stuff?
  # run) do_cmp= do_run=1 ;;
  *) err 1 "unexpected task: $TASK" ;;
esac

case $TARGET in
  all) targets="blaze jsu jmc-c jmc-js jmc-java jmc-py" ;;
  jmc) targets="jsu jmc-c jmc-js jmc-java jmc-py" ;;
  jmc-c|jmc-js|jmc-java|jmc-py) targets="jsu $TARGET" ;;
  blaze) targets="blaze" ;;
  *) err 1 "unexpected target: $TARGET" ;;
esac

echo "# $0[$$]: cmp=$do_cmp run=$do_run targets=$targets dirs=$@"

#
# proceed
#

# cputime
function ctime()
{
  local case=$1 prefix=$2 tool=$3
  shift 3
  local compile_csv="${prefix}_${tool}_compile.csv"
  echo -n "$case" >> "$compile_csv"
  /usr/bin/time -f "$time_fmt" -a -o "$compile_csv" "$@"
}

for dir ; do

  [ -d "$dir" ] || continue

  # Output
  name=$(basename $dir)
  safe=${name//-/_}         # for java class names
  prefix="$PREFIX${name}"
  sprefix="$PREFIX${safe}"

  # compiler options
  jsum_opts=
  jmc_c_opt="--loose --no-reporting"
  jmc_x_opt=$jmc_c_opt
  if [ $name = "cspell" -o $name = "ui5-manifest" ] ; then
    jmc_c_opt+=" -re pcre2"
    jmc_x_opt+=" -re re"
  fi

  # skip custom OpenAPI model as it is much too strict
  if [ $name = "openapi" ] ; then
    jsum_opts+=" --no-id"
  fi

  for trg in $targets ; do
    echo "# considering $dir $trg ($name)"
    #
    # COMPILE
    #
    blaze_ko=9 jmc_c_ko=9 jmc_out_ko=9
    jmc_js_ko=9 jmc_py_ko=9 jmc_pl_ko=9
    jmc_java_ko=9 jmc_class_ko=9

    [ "$do_cmp" -a $trg = "blaze" ] && {
      echo "## $dir blaze compile"
      ctime "$name,blaze,$now," "$prefix" blaze \
        $js_cli compile -m -f $dir/schema.json > ${prefix}_blaze.json
      blaze_ko=$?
      echo "## blaze ko: $blaze_ko"
    }
    [ "$do_cmp" -a "$trg" = "jsu" ] && {
      echo "## $dir jsu compile"
      ctime "$name,jsu-simpler,$now," "$prefix" jsu \
        $jsu_simpler $dir/schema.json > ${prefix}_schema-simpler.json
      echo -n "$name,jsu-model,$now," >> $compile_csv
      ctime "$name,jsu-model,$now," "$prefix" jsu \
        $jsu_model --quiet --id --loose --no-fix $jsum_opts ${prefix}_schema-simpler.json > ${prefix}_model.json
    }
    [ "$do_cmp" -a "$trg" = "jmc-c" ] && {
      echo "## $dir jmc-c compile"
      ctime "$name,jmc-c-src,$now," "$prefix" jmc-c \
        $jmc $jmc_c_opt -o ${prefix}_model.c ${prefix}_model.json
      jmc_c_ko=$?
      ctime "$name,jmc-c-out,$now," "$prefix" jmc-c \
        $jmc $jmc_c_opt -o ${prefix}_model.out ${prefix}_model.json
      jmc_out_ko=$?
      echo "## jmc out ko: $jmc_out_ko"
      # rename to avoid .out
      mv ${prefix}_model.out ${prefix}_model.exe
    }
    [ "$do_cmp" -a "$trg" = "jmc-js" ] && {
      echo "## $dir jmc-js compile"
      # echo "### $jmc $jmc_x_opt -o ${prefix}_model.js ${prefix}_model.json"
      ctime "$name,jmc-js,$now," "$prefix" jmc-js \
        $jmc $jmc_x_opt -o ${prefix}_model.js ${prefix}_model.json
      jmc_js_ko=$?
    }
    [ "$do_cmp" -a "$trg" = "jmc-py" ] && {
      echo "## $dir jmc-py compile"
      ctime "$name,jmc-py,$now," "$prefix" jmc-py \
        $jmc $jmc_x_opt -o ${prefix}_model.py ${prefix}_model.json
      jmc_py_ko=$?
    }
    [ "$do_cmp" -a "$trg" = "jmc-java" ] && {
      echo "## $dir jmc-java compile"
      ctime "$name,jmc-java-src,$now," "$prefix" jmc-java \
        $jmc $jmc_x_opt -o ${sprefix}_model.java ${prefix}_model.json
      jmc_java_ko=$?
      ctime "$name,jmc-java-class,$now," "$prefix" jmc-java \
        $jmc $jmc_x_opt -o ${sprefix}_model.class ${prefix}_model.json
      jmc_class_ko=$?
    }
    [ "$do_cmp" -a "$trg" = "jmc-pl" ] && {
      echo "## $dir jmc-pl compile"
      ctime "$dir,jmc-pl,$now," "$prefix" jmc-pl \
        $jmc $jmc_x_opt -o ${prefix}_model.pl $dir/model.json
      jmc_pl_ko=$?
    }

    [ ! "$do_run" ] && continue
    [ "$LOOP" -eq 0 ] && continue

    #
    # RUN
    #
    [ "$trg" = "blaze" -a "$blaze_ko" -eq 0 ] && {
      echo "## $dir blaze run"
      $js_cli validate -m ${prefix}_blaze.json -b -l $LOOP $dir/schema.json $dir/instances.jsonl \
        > ${prefix}_blaze.out
    }
    [ "$trg" = "jmc-c" -a "$jmc_out_ko" -eq 0 ] && {
      echo "## $dir jmc-c run"
      $jmc exec ${prefix}_model.exe -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-c.out
    }
    [ "$trg" = "jmc-js" -a "$jmc_js_ko" -eq 0 ] && {
      echo "## $dir jmc-js run"
      $jmc exec ${prefix}_model.js -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-js.out
    }
    [ "$trg" = "jmc-py" -a "$jmc_py_ko" -eq 0 ] && {
      echo "## $dir jmc-py run"
      $jmc exec ${prefix}_model.py -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-py.out
    }
    [ "$trg" = "jmc-java" -a "$jmc_class_ko" -eq 0 ] && {
      # FIXME java .java to work around classpath subdir
      # maybe we could do better with some wrapper to fix CLASSPATH on the fly
      echo "## $dir jmc-java run"
      $jmc exec java ${sprefix}_model.java -j GSON -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-java-gson.out
      $jmc exec java ${sprefix}_model.java -j Jackson -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-java-jackson.out
      $jmc exec java ${sprefix}_model.java -j JSONP -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-java-jsonp.out
    }
    [ "$trg" = "jmc-pl" -a "$jmc_pl_ko" -eq 0 ] && {
      echo "## $dir jmc-pl run"
      $jmc exec ${prefix}_model.pl -T $(( $LOOP / 10 )) --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-pl.out
    }
  done
done

echo "# $0[$$]: cmp=$do_cmp run=$do_run targets=$targets dirs=$@ - $SECONDS"
