#! /bin/bash

export TMPDIR=.
LOOP=$1 PREFIX=$2
shift 2

# just in case
export PATH=$PATH:.

# docker wrappers
jmc=jmc
js_cli=js-cli
jsu_model="$jmc exec jsu-model"
jsu_simpler="$jmc exec jsu-simpler"
etime="/usr/bin/time -f %e"

now=$(date -Ins -u)

function keeptime()
{
    grep -E '^[0-9]+\.[0-9]+$'
}

for dir ; do
    [ -d "$dir" ] || continue
    name=$(basename $dir)
    echo "# considering $dir ($name)"
    #
    # Output
    #
    safe=${name//-/_}         # for java class names
    prefix="$PREFIX${name}"
    sprefix="$PREFIX${safe}"
    compile_csv="${prefix}_compile.csv"
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
    echo -n "$name,blaze,$now," >> $compile_csv
    $etime $js_cli compile -m -f $dir/schema.json > ${prefix}_blaze.json 2>> $compile_csv
    blaze_ko=$?
    echo "## $dir jsu compile"
    echo -n "$name,jsu-simpler,$now," >> $compile_csv
    $etime $jsu_simpler $dir/schema.json 2>&1 > ${prefix}_schema-simpler.json |
        keeptime >> $compile_csv
    echo -n "$name,jsu-model,$now," >> $compile_csv
    $etime $jsu_model --quiet --id --loose --no-fix ${prefix}_schema-simpler.json 2>&1 > ${prefix}_model.json |
        keeptime >> $compile_csv
    echo "## $dir jmc-c compile"
    echo -n "$name,jmc-c-src,$now," >> $compile_csv
    $etime $jmc $jmc_c_opt -o ${prefix}_model.c ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_c_ko=$?
    echo -n "$name,jmc-c-out,$now," >> $compile_csv
    $etime $jmc $jmc_c_opt -o ${prefix}_model.out ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_out_ko=$?
    # rename to avoid .out
    mv ${prefix}_model.out ${prefix}_model.exe
    echo "## $dir jmc-js compile"
    echo -n "$name,jmc-js,$now," >> $compile_csv
    $etime $jmc $jmc_x_opt -o ${prefix}_model.js ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_js_ko=$?
    echo "## $dir jmc-py compile"
    echo -n "$name,jmc-py,$now," >> $compile_csv
    $etime $jmc $jmc_x_opt -o ${prefix}_model.py ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_py_ko=$?
    echo "## $dir jmc-java compile"
    echo -n "$name,jmc-java-src,$now," >> $compile_csv
    $etime $jmc $jmc_x_opt -o ${sprefix}_model.java ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_java_ko=$?
    echo -n "$name,jmc-java-class,$now," >> $compile_csv
    $etime $jmc $jmc_x_opt -o ${sprefix}_model.class ${prefix}_model.json 2>&1 |
        keeptime >> $compile_csv
    jmc_class_ko=$?
    # echo "## $dir jmc-pl compile"
    # echo -n "$dir,jmc-pl,$now," >> $compile_csv
    # $etime $jmc $jmc_x_opt -o $dir/model.pl $dir/model.json 2>&1 |
    #     keeptime >> $compile_csv
    # jmc_pl_ko=$?
    #
    # RUN
    #
    [ "$LOOP" -eq 0 ] && continue
    echo "## $dir blaze run"
    [ "$blaze_ko" -eq 0 ] &&
        $js_cli validate -m ${prefix}_blaze.json -b -l $LOOP $dir/schema.json $dir/instances.jsonl \
            > ${prefix}_blaze.out
    echo "## $dir jmc-c run"
    [ "$jmc_out_ko" -eq 0 ] &&
        $jmc exec ${prefix}_model.exe -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${prefix}_jmc-c.out
    echo "## $dir jmc-js run"
    [ "$jmc_js_ko" -eq 0 ] &&
        $jmc exec ${prefix}_model.js -T $LOOP --jsonl $dir/instances.jsonl \
	        2> ${prefix}_jmc-js.out
    echo "## $dir jmc-py run"
    [ "$jmc_py_ko" -eq 0 ] &&
        $jmc exec ${prefix}_model.py -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${prefix}_jmc-py.out
    echo "## $dir jmc-java run"
    [ "$jmc_class_ko" -eq 0 ] && {
        $jmc exec java ${sprefix}_model.java -j GSON -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${prefix}_jmc-java-gson.out
        $jmc exec java ${sprefix}_model.java -j Jackson -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${prefix}_jmc-java-jackson.out
        $jmc exec java ${sprefix}_model.java -j JSONP -T $LOOP --jsonl $dir/instances.jsonl \
            2> ${prefix}_jmc-java-jsonp.out
    }
    # echo "## $dir jmc-pl run"
    # [ "$jmc_pl_ko" -eq 0 ] &&
    #     $jmc exec $dir/model.pl -T $(( $LOOP / 10 )) --jsonl $dir/instances.jsonl \
    #         2> ${prefix}_jmc-pl.out
done
