#! /bin/bash
#
# Generate tests about array prefixes
#

err()
{
    local status=$1
    shift
    echo "$@" >&2
    exit $status
}

[ $# -lt 3 -o $# -gt 4 ] && err 0 "usage: $0 type lang unroll [base]"

mtype=$1 lang=$2 unroll=$3 base=${4:-4242}

gen_model()
{
    local mtype=$1 unroll=$2
    echo -n "{\"@\": ["
    case $mtype in
        STRING)
            echo -n '""' ;;
        OBJECT)
            echo -n '{"": ""}' ;;
        JSON)
            echo -n '{"": "$ANY"}' ;;
        INTEGER)
            echo -n '-1' ;;
        FLOAT)
            echo -n '-1.0' ;;
        *)
            err 1 "unexpected model type: $mtype" ;;
    esac
    echo "], \">=\": $unroll}"
}

gen_one_val()
{
    local mtype=$1 n=$2 base=${3:-4242}
    case $mtype in
        STRING)
            echo -n "\"$(($n + $base))\"" ;;
        OBJECT)
            echo -n "{\"foo\": \"$0x$(($n + $base))\", \"bla\": \"$((3 * $n + $base))\" }" ;;
        JSON)
            echo -n "{\"foo\": $(( $n % 3 )), \"bla\": \"Susie$(( 17 * $n % 123 ))\", \"diff\": [0, 42, $n]}" ;;
        INTEGER)
            echo -n "$((7 * $n + $base))" ;;
        FLOAT)
            echo -n "3.14" ;;
        *)
            err 1 "unexpected model type: $mtype" ;;
    esac
}

gen_val()
{
    local mtype=$1 n=$2 base=$3
    echo -n "["
    while [[ $n -gt 0 ]] ; do
        gen_one_val $mtype $n $base
        [[ $n -gt 1 ]] && echo -n ", "
        let n--
    done
    echo "]"
}

PATH=$PATH:.
opti=ua-unroll loop=ua-loop
run= src=$lang opts=

case $lang in
    c)
        exe=out execute=.out ;;
    java)
        CLASSPATH=.:$CLASSPATH
        run=java opti=UaUnroll loop=UaLoop exe=class execute= ;;
    py)
        exe=$src execute=.$src ;;
    js|pl)
        opts="--loose" exe=$src execute=.$src ;;
    *)
        err 2 "unexpected language: $lang" ;;
esac


gen_model $mtype $unroll > ua.model.json
gen_val $mtype $(( $unroll + 2 )) > ua.val.json

jmc -o $opti.$src --array-unrolling-size=$unroll $opts ua.model.json || err 1 "compilation to C failed"
[ "$src" != "$exe" ] && jmc -o $opti.$exe --array-unrolling-size=$unroll $opts ua.model.json
jmc -o $loop.$src --array-unrolling-size=$unroll $opts ua.model.json || err 1 "compilation to C failed"
[ "$src" != "$exe" ] && jmc -o $loop.$exe --array-unrolling-size=$unroll $opts ua.model.json

time $run $opti$execute -T 100000 ua.val.json
time $run $loop$execute -T 100000 ua.val.json
