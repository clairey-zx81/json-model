#! /bin/bash
#
# execute jmc bench bite
#

export PATH=$PATH:.
export TMPDIR=.

# container wrappers
js_cli=js-cli
jmc=jmc
jsu_compile="$jmc exec jsu-compile"

now=$(date +%Y%m%d%H%M%S.$$)

function err()
{
  local status=$1
  shift
  echo "$@" >&2
  exit $status
}

function usage()
{
  err ${1:-0} "usage: $0 -h -c -l LOOP -t TASK prefix target dirs..."
}

function script_help()
{
  cat <<EOF

Execute JMC benchmark workbite

Synopsis:
  $0 -h -c -l LOOP -t TASK prefix target dirs...

Options:
- -l loop: number of performance loop iterations, eg 1000 or 10000
- -t task: cmp (aka compile) or all = cmp + run
- -c: check for contents

Arguments:
- prefix: directory where to write results
- target: implementation/phase to run (all, jmc, jmc-*, blaze)
- dirs: jsb schema directories to process

Environment:
- POD: container command, either "docker" or "podman"
- POD_PULL: whether to pull images before running
- JMC: json-model container tag
- JMC_ENV: names of environment variables to export
- JMC_POD_OPTS: additional pod options
- JMC_OPTS: jmc options
- JMC_JAVA_LIBS: java JSON libraries, in GSON Jackson JSONP, default is all
- JSC: jsonschema blaze cli container tag
- PATH: where to find "jmc" and "js-cli" wrappers
- WORKDIR: working directory to use
- JSB_DIR: jsonschema benchmark directory
EOF
  exit 0
}

#
# OPTIONS AND ARGS
#

# defaults
LOOP=1000 TASK="all" jsu_opts_2= jmc_opts_2= blaze_opts=

# handle options
while [[ "$1" == -* ]] ; do
  opt=$1
  shift
  case $opt in
    -h|--help)
      script_help
      ;;
    -l|--loop)
      LOOP=$1
      shift
      ;;
    --loop=*)
      LOOP=${1#*=}
      ;;
    -t|--task)
      TASK=$1
      shift
      ;;
    --task=*)
      TASK=${1#*=}
      ;;
    -c|--content)  # check contents
      blaze_opts+=" -F"
      jsu_opts_2+=" --format"
      jmc_opts_2+=" --predef"
      ;;
    -nc|--no-content)
      blaze_opts=${blaze_opts/-F/}
      jsu_opts_2+=" --no-format"
      jmc_opts_2+=" --no-predef"
      ;;
    --)  # end of options
      break
      ;;
  esac
done

[ $# -ge 2 ] || usage 1

PREFIX=$1 TARGET=$2
shift 2

case $TASK in
  all) do_cmp=1 do_run=1 ;;
  cmp) do_cmp=1 do_run= ;;
  # TODO run with pre-compiled stuff? where is it found?
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

# setup default java libs
[ "$JMC_JAVA_LIBS" ] || JMC_JAVA_LIBS="GSON Jackson JSONP"

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
  #
  # - `--quiet`: reduce compiler verbosity
  # - `--id`: use custom models when available
  # - `--no-strict`: just warn about some ill-defined schemas
  # - `--fix`: fix common schema issues (missing types, misplaced keywords)
  #            improving accuracy and possibly performance (unclear ?)
  # - `--loose`: allow loose numbers (42.0 is an int, 42 is a float)
  #
  jsu_opts="--quiet --id --no-strict --fix --no-reporting --loose"

  # skip custom OpenAPI model as the schema does not check sub-schemas, for fairer comparison
  # this means that a large chunk of the schema is not checked…
  [ $name = "openapi" ] && jsu_opts+=" --no-id"

  # JMC compiler forwarded options:
  #
  #  - `--no-format`: do not check formats
  #  - `--no-reporting`: do not generate invalidation location reporting code
  #  - `--loose`: assume loose integers (42.0 is an int) and floats (42 is a float)
  #
  jmc_c_opts=""
  jmc_x_opts=$jmc_c_opts

  # additional options may override the above defaults
  jsu_opts+=$jsu_opts_2
  jmc_c_opts+=$jmc_opts_2
  jmc_x_opts+=$jmc_opts_2

  for trg in $targets ; do

    echo "# considering $dir $trg ($name)"

    #
    # COMPILE
    #
    blaze_ko=9
    jmc_c_ko=9 jmc_out_ko=9
    jmc_js_ko=9 jmc_py_ko=9 jmc_pl_ko=9
    jmc_java_ko=9 jmc_class_ko=9

    # blaze compilation
    [ "$do_cmp" -a $trg = "blaze" ] && {
      echo "## $dir blaze compile"
      ctime "$name,blaze,$now," "$prefix" blaze \
        $js_cli compile $blaze_opts -m -f $dir/schema.json > ${prefix}.blaze.json
      blaze_ko=$?
      echo "## blaze ko: $blaze_ko"
    }

    # schema to model
    [ "$do_cmp" -a "$trg" = "jsu" ] && {
      echo "## $dir jsu compile"
      ctime "$name,jsu-model,$now," "$prefix" jsu \
        $jsu_compile $jsu_opts -o ${prefix}.model.json $dir/schema.json
    }

    # schema to C and executable
    [ "$do_cmp" -a "$trg" = "jmc-c" ] && {
      echo "## $dir jmc-c compile"
      ctime "$name,jmc-c-src,$now," "$prefix" jmc-c \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_c_opts -o ${prefix}.c
      jmc_c_ko=$?
      ctime "$name,jmc-c-out,$now," "$prefix" jmc-c \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_c_opts -o ${prefix}.out
      jmc_out_ko=$?
      echo "## jmc out ko: $jmc_out_ko"
      # rename to avoid .out
      mv ${prefix}.out ${prefix}.exe
    }

    # schema to JS
    [ "$do_cmp" -a "$trg" = "jmc-js" ] && {
      echo "## $dir jmc-js compile"
      ctime "$name,jmc-js,$now," "$prefix" jmc-js \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opts -o ${prefix}.js
      jmc_js_ko=$?
    }

    # schema to Python
    [ "$do_cmp" -a "$trg" = "jmc-py" ] && {
      echo "## $dir jmc-py compile"
      ctime "$name,jmc-py,$now," "$prefix" jmc-py \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opts -o ${prefix}.py
      jmc_py_ko=$?
    }

    # schema to Java and class
    [ "$do_cmp" -a "$trg" = "jmc-java" ] && {
      echo "## $dir jmc-java compile"
      ctime "$name,jmc-java-src,$now," "$prefix" jmc-java \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opts -o ${sprefix}.java
      jmc_java_ko=$?
      ctime "$name,jmc-java-class,$now," "$prefix" jmc-java \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opts -o ${sprefix}.class
      jmc_class_ko=$?
    }

    # schema to Perl
    [ "$do_cmp" -a "$trg" = "jmc-pl" ] && {
      echo "## $dir jmc-pl compile"
      ctime "$dir,jmc-pl,$now," "$prefix" jmc-pl \
        $jsu_compile $jsu_opts --no-format $dir/schema.json \
          -- $jmc_x_opts -o ${prefix}.pl
      jmc_pl_ko=$?
    }

    [ ! "$do_run" ] && continue
    [ "$LOOP" -eq 0 ] && continue

    #
    # RUN
    #
    [ "$trg" = "blaze" -a "$blaze_ko" -eq 0 ] && {
      echo "## $dir blaze run"
      $js_cli validate $blaze_opts -m ${prefix}.blaze.json -b -l $LOOP \
        $dir/schema.json $dir/instances.jsonl \
          > ${prefix}_blaze.out
    }

    [ "$trg" = "jmc-c" -a "$jmc_out_ko" -eq 0 ] && {
      echo "## $dir jmc-c run"
      $jmc exec ${prefix}.exe -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-c.out
    }

    [ "$trg" = "jmc-js" -a "$jmc_js_ko" -eq 0 ] && {
      echo "## $dir jmc-js run"
      $jmc exec ${prefix}.js -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-js.out
    }

    [ "$trg" = "jmc-py" -a "$jmc_py_ko" -eq 0 ] && {
      echo "## $dir jmc-py run"
      $jmc exec ${prefix}.py -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-py.out
    }

    [ "$trg" = "jmc-java" -a "$jmc_class_ko" -eq 0 ] && {
      # FIXME java .java to work around classpath subdir
      # maybe we could do better with some wrapper to fix CLASSPATH on the fly
      echo "## $dir jmc-java run"
      for lib in $JMC_JAVA_LIBS ; do
        $jmc exec java ${sprefix}.java -j $lib -T $LOOP --jsonl $dir/instances.jsonl \
          2> ${prefix}_jmc-java-$lib.out
      done
    }

    [ "$trg" = "jmc-pl" -a "$jmc_pl_ko" -eq 0 ] && {
      echo "## $dir jmc-pl run"
      $jmc exec ${prefix}.pl -T $LOOP --jsonl $dir/instances.jsonl \
        2> ${prefix}_jmc-pl.out
    }
  done
done

echo "# $0[$$]: cmp=$do_cmp run=$do_run targets=$targets dirs=$@ - $SECONDS"
