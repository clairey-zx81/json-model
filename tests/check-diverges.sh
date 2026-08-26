# Report backend divergences found in generated *.auto.check files,
# findings on a model whose *.errors.json holds "auto.diverse": true are known

targets=("$@")
[ ${#targets[@]} -eq 0 ] && targets=(.)

list_checks() {
    local target
    for target in "${targets[@]}" ; do
        if [ -d "$target" ] ; then
            find -L "$target" -type f -name '*.auto.check'
        elif [ -f "$target" ] ; then
            echo "$target"
        else
            echo "no such file or directory: $target" >&2
        fi
    done | sort -u
}

vector() {
    local auto=$1 index=$2
    [ -f "$auto" ] || return 0
    python3 - "$auto" "$index" <<'PY'
import json, sys
try:
    data = json.load(open(sys.argv[1]))
except Exception:
    sys.exit(0)
wanted, seen, label = int(sys.argv[2]), 0, ""
for item in data:
    if isinstance(item, str):
        label = item
        continue
    if isinstance(item, list) and len(item) == 2:
        if seen == wanted:
            valid, value = item
            print(f"    {label or '?'}: expected {'PASS' if valid else 'FAIL'}"
                  f" on {json.dumps(value)}")
            break
        seen += 1
        label = ""
PY
}

diverse() {
    local errors=$1
    [ -f "$errors" ] || return 1
    python3 - "$errors" <<'PY'
import json, sys
try:
    data = json.load(open(sys.argv[1]))
except Exception:
    sys.exit(1)
sys.exit(0 if data.get("auto.diverse") is True else 1)
PY
}

checks=0 files=0 findings=0 kfiles=0 kfindings=0
while IFS= read -r check ; do
    checks=$((checks + 1))
    hits=$(grep -E 'DISAGREEMENT|MISMATCH' "$check")
    [ -z "$hits" ] && continue
    if diverse "${check%.auto.check}.errors.json" ; then
        known=1 ; kfiles=$((kfiles + 1))
    else
        known="" ; files=$((files + 1))
    fi
    if [ -n "$known" ] && [ -z "$VERBOSE" ] ; then
        kfindings=$((kfindings + $(echo "$hits" | wc -l)))
        continue
    fi
    echo "== $check${known:+  (auto.diverse)}"
    auto=${check%.check}.json
    while IFS= read -r line ; do
        if [ -n "$known" ] ; then
            kfindings=$((kfindings + 1))
        else
            findings=$((findings + 1))
        fi
        echo "  $line"
        index=$(expr "$line" : '\[\([0-9]*\)\]')
        [ -z "$index" ] || vector "$auto" "$index"
    done <<< "$hits"
done < <(list_checks)

if [ $checks -eq 0 ] ; then
    echo "no *.auto.check file found, run: make -k auto" >&2
    exit 2
fi

echo "$checks check files: $findings findings in $files files" \
     "($kfindings known in $kfiles files)" >&2

[ $findings -eq 0 ]
