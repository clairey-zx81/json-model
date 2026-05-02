#! /bin/bash
#
# Generate tests about unique arrays
#

err()
{
    local status=$1
    shift
    echo "$@" >&2
    exit $status
}

gen_model()
{
    local mtype=$1
    echo -n "{\"@\": ["
    case $mtype in
        STRING)
            echo -n '""' ;;
        OBJECT)
            echo -n '{"": ""}' ;;
        JSON|INTEGER)
            echo -n '0' ;;
        *)
            err 1 "unexpected model type: $mtype" ;;
    esac
    echo "], \"!\": true}"
}

gen_one_val()
{
    local mtype=$1 n=$2 base=${3:-4242}
    case $mtype in
        STRING)
            echo -n "\"$(($n + $base))\"" ;;
        OBJECT)
            echo -n "{\"foo\": \"$0x$(($n + $base))\", \"bla\": \"$((3 * $n + $base))\" }" ;;
        JSON|INTEGER)
            echo -n "$((7 * $n + $base))" ;;
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

mtype=$1 limit=$2 base=${3:-4242}

gen_model $mtype > uh.model.json
gen_val $mtype $limit > uh.val.json
jmc -o uh.c uh.model.json
jmc -o uh-hash.out -DUNIQUE_${mtype}_ARRAY_HASH_LIMIT=$limit uh.model.json
jmc -o uh-sort.out -DUNIQUE_${mtype}_ARRAY_HASH_LIMIT=0 uh.model.json
echo -n "hash: "
./uh-hash.out -T 1000 uh.val.json
echo -n "sort: "
./uh-sort.out -T 1000 uh.val.json
