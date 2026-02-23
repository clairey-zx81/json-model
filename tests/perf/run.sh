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
# - JMC: json-model container tag
# - PATH: where to find "jmc" and "js-cli" wrappers

export PATH=$PATH:.
export TMPDIR=.

# container wrappers
js_cli=js-cli
jmc=jmc
jsu_compile="$jmc exec jsu-compile"
jsu_model="$jmc exec jsu-model"

now=$(date +%Y%m%d%H%M%S.$$)

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

[ $# -ge 4 ] || err 1 "usage: $0 loop prefix task target dirs..."

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
  # echo /usr/bin/time -f "%e" -a -o "$compile_csv" "$@" >&2
  /usr/bin/time -f "%e" -a -o "$compile_csv" "$@"
}

for dir ; do

  [ -d "$dir" ] || continue

  # Output
  name=$(basename $dir)
  safe=${name//-/_}         # for java class names
  prefix="$PREFIX${name}"
  sprefix="$PREFIX${safe}"

  # JSU compiler options:
  #  - `--quiet`: reduce compiler verbosity
  #  - `--id`: use custom models when available
  #  - `--no-strict`: just warn about some ill-defined schemas
  #  - `--fix`: fix common schema issues (missing types, misplaced keywords)
  #             improving both accuracy and performance
  #  - `--no-format`: do not check formats
  jsu_opts="--quiet --id --no-strict --fix"

  # JMC compiler options:
  #  - `--loose`: assume loose integers (42.0 is an int) and floats (42 is a float)
  #  - `--no-reporting`: do not generate invalidation location reporting code
  jmc_c_opt="--loose --no-reporting"
  jmc_x_opt=$jmc_c_opt

  # regex is not compatible with re2
  if [ $name = "ui5-manifest" ] ; then
    jmc_c_opt+=" -re pcre2"
    jmc_x_opt+=" -re re"
  fi

  # skip custom OpenAPI model as the schema does not check sub-schemas
  if [ $name = "openapi" ] ; then
    jsu_opts+=" --no-id"
  fi

  for trg in $targets ; do

    echo "# considering $dir $trg ($name)"

    #
    # COMPILE
    #
    blaze_ko=9 jmc_c_ko=9 jmc_out_ko=9
    jmc_js_ko=9 jmc_py_ko=9 jmc_pl_ko=9
    jmc_java_ko=9 jmc_class_ko=9

    # blaze compilation
    [ "$do_cmp" -a $trg = "blaze" ] && {
      echo "## $dir blaze compile"
      ctime "$name,blaze,$now," "$prefix" blaze \
        $js_cli compile -m -f $dir/schema.json > ${prefix}_blaze.json
      blaze_ko=$?
      echo "## blaze ko: $blaze_ko"
    }

    # schema to model
    [ "$do_cmp" -a "$trg" = "jsu" ] && {
      echo "## $dir jsu compile"
      ctime "$name,jsu-model,$now," "$prefix" jsu \
        $jsu_model $jsu_opts $dir/schema.json > ${prefix}_model.json
    }

    # schema to C and executable
    [ "$do_cmp" -a "$trg" = "jmc-c" ] && {
      echo "## $dir jmc-c compile"
      ctime "$name,jmc-c-src,$now," "$prefix" jmc-c \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_c_opt -o ${prefix}_model.c
      jmc_c_ko=$?
      ctime "$name,jmc-c-out,$now," "$prefix" jmc-c \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_c_opt -o ${prefix}_model.out
      jmc_out_ko=$?
      echo "## jmc out ko: $jmc_out_ko"
      # rename to avoid .out
      mv ${prefix}_model.out ${prefix}_model.exe
    }

    # schema to JS
    [ "$do_cmp" -a "$trg" = "jmc-js" ] && {
      echo "## $dir jmc-js compile"
      ctime "$name,jmc-js,$now," "$prefix" jmc-js \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opt -o ${prefix}_model.js
      jmc_js_ko=$?
    }

    # schema to Python
    [ "$do_cmp" -a "$trg" = "jmc-py" ] && {
      echo "## $dir jmc-py compile"
      ctime "$name,jmc-py,$now," "$prefix" jmc-py \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opt -o ${prefix}_model.py
      jmc_py_ko=$?
    }

    # schema to Java and class
    [ "$do_cmp" -a "$trg" = "jmc-java" ] && {
      echo "## $dir jmc-java compile"
      ctime "$name,jmc-java-src,$now," "$prefix" jmc-java \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opt -o ${sprefix}_model.java
      jmc_java_ko=$?
      ctime "$name,jmc-java-class,$now," "$prefix" jmc-java \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opt -o ${sprefix}_model.class
      jmc_class_ko=$?
    }

    # schema to Perl
    [ "$do_cmp" -a "$trg" = "jmc-pl" ] && {
      echo "## $dir jmc-pl compile"
      ctime "$dir,jmc-pl,$now," "$prefix" jmc-pl \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opt -o ${prefix}_model.pl
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
