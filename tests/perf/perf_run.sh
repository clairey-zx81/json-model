#! /bin/bash

export TMPDIR=.
LOOP=$1
shift 1

export PATH=.:$PATH

# docker wrappers
jmc=jmc
js_cli=js-cli
jsu_model="$jmc exec jsu-model"
jsu_simpler="$jmc exec jsu-simpler"
etime="/usr/bin/time -f %e"

now=$(date -Is -u)

function keeptime()
{
    grep -E '^[0-9]+\.[0-9]+$'
}

for dir ; do
    [ -d "$dir" ] || continue
    name=${dir//-/_}
    echo "# considering $dir"
    #
    # Fixes
    #
    jmc_c_opt="--loose --no-reporting"
    jmc_x_opt=$jmc_c_opt
    if [ $dir = "cspell" -o $dir = "ui5-manifest" ] ; then
      jmc_c_opt+="-re pcre2"
      jmc_x_opt+="-re re"
    fi
    #
    # COMPILE
    #
    echo "## $dir blaze compile"
    echo -n "$dir,blaze,$now," >> ${dir}_compile.csv
    $etime $js_cli compile -m -f $dir/schema.json > $dir/blaze.json 2>> ${dir}_compile.csv
    blaze_ko=$?
    echo "## $dir jsu compile"
    echo -n "$dir,jsu-simpler,$now," >> ${dir}_compile.csv
    $etime $jsu_simpler $dir/schema.json 2>&1 > $dir/schema-simpler.json |
        keeptime >> ${dir}_compile.csv
    echo -n "$dir,jsu-model,$now," >> ${dir}_compile.csv
    $etime $jsu_model --quiet --id --loose --no-fix $dir/schema-simpler.json 2>&1 > $dir/model.json |
        keeptime >> ${dir}_compile.csv
    echo "## $dir jmc-c compile"
    echo -n "$dir,jmc-c-src,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_c_opt -o $dir/model.c $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_c_ko=$?
    echo -n "$dir,jmc-c-out,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_c_opt -o $dir/model.out $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_out_ko=$?
    echo "## $dir jmc-js compile"
    echo -n "$dir,jmc-js,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.js $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_js_ko=$?
    echo "## $dir jmc-py compile"
    echo -n "$dir,jmc-py,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.py $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_py_ko=$?
    echo "## $dir jmc-java compile"
    echo -n "$dir,jmc-java-src,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.java $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_java_ko=$?
    echo -n "$dir,jmc-java-class,$now," >> ${dir}_compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.class $dir/model.json 2>&1 |
        keeptime >> ${dir}_compile.csv
    jmc_class_ko=$?
    # echo "## $dir jmc-pl compile"
    # echo -n "$dir,jmc-pl,$now," >> ${dir}_compile.csv
    # $etime $jmc $jmc_x_opt -o $dir/model.pl $dir/model.json 2>&1 |
    #     keeptime >> ${dir}_compile.csv
    # jmc_pl_ko=$?
    #
    # RUN
    #
    [ "$LOOP" -eq 0 ] && continue
    echo "## $dir blaze run"
    [ "$blaze_ko" -eq 0 ] &&
        $js_cli validate -m $dir/blaze.json -b -l $LOOP $dir/schema.json $dir/instances.jsonl \
            > ${dir}_blaze.out
    echo "## $dir jmc-c run"
    [ "$jmc_out_ko" -eq 0 ] &&
        $jmc exec $dir/model.out -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${dir}_jmc-c.out
    echo "## $dir jmc-js run"
    [ "$jmc_js_ko" -eq 0 ] &&
        $jmc exec $dir/model.js -T $LOOP --jsonl $dir/instances.jsonl \
	        2> ${dir}_jmc-js.out
    echo "## $dir jmc-py run"
    [ "$jmc_py_ko" -eq 0 ] &&
        $jmc exec $dir/model.py -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${dir}_jmc-py.out
    echo "## $dir jmc-java run"
    [ "$jmc_class_ko" -eq 0 ] && {
        $jmc exec java $dir/model.java -j GSON -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${dir}_jmc-java-gson.out
        $jmc exec java $dir/model.java -j Jackson -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${dir}_jmc-java-jackson.out
        $jmc exec java $dir/model.java -j JSONP -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${dir}_jmc-java-jsonp.out
    }
    # echo "## $dir jmc-pl run"
    # [ "$jmc_pl_ko" -eq 0 ] &&
    #     $jmc exec $dir/model.pl -T $(( $LOOP / 10 )) --jsonl $dir/instances.jsonl \
    #         2> ${dir}_jmc-pl.out
done
