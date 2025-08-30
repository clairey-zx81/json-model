# /bin/bash

export TMPDIR=.
LOOP=1000

# docker wrappers
jmc=./jmc
js_cli=./js-cli
jsu_model="$jmc exec jsu-model"
etime="/usr/bin/time -f %e"

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
      jmc_x_opti+="-re re"
    fi
    #
    # Blaze
    #
    echo "## blaze"
    echo -n "$dir,blaze," >> compile.csv
    $etime $js_cli compile -f $dir/schema.json > $dir/blaze.json 2>> compile.csv
    $js_cli validate -m $dir/blaze.json -b -l $LOOP $dir/schema.json $dir/instances.jsonl > ${dir}_blaze.out
    #
    # JMC
    #
    echo "## jsu-model"
    echo -n "$dir,jsu-model," >> compile.csv
    $etime $jsu_model --quiet --id --loose --no-fix $dir/schema.json 2>&1 > $dir/model.json |
        grep -v "^WARNING:" >> compile.csv
    echo "## jmc-c"
    echo -n "$dir,jmc-c-src," >> compile.csv
    $etime $jmc $jmc_c_opt -o $dir/model.c $dir/model.json 2>> compile.csv
    echo -n "$dir,jmc-c-out," >> compile.csv
    $etime $jmc $jmc_c_opt -o $dir/model.out $dir/model.json 2>> compile.csv
    $jmc exec $dir/model.out -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-c.out
    echo "## jmc-js"
    echo -n "$dir,jmc-js," >> compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.js $dir/model.json 2>> compile.csv
    $jmc exec $dir/model.js -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-js.out
    echo "## jmc-py"
    echo -n "$dir,jmc-py," >> compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.py $dir/model.json 2>> compile.csv
    $jmc exec $dir/model.py -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-py.out
    echo "## jmc-java-gson"
    echo -n "$dir,jmc-java-src," >> compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.java $dir/model.json 2>> compile.csv
    echo -n "$dir,jmc-java-class," >> compile.csv
    $etime $jmc $jmc_x_opt -o $dir/model.class $dir/model.json 2>> compile.csv
    $jmc exec java $dir/model.java -j GSON -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-java-gson.out
    $jmc exec java $dir/model.java -j Jackson -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-java-jackson.out
    $jmc exec java $dir/model.java -j JSONP -T $LOOP --jsonl $dir/instances.jsonl 2> ${dir}_jmc-java-jsonp.out
done
