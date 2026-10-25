#!/usr/bin/env bash
set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
cd "$HERE/golden" || { echo "Falta test/golden/"; exit 1; }

THARSIS="$HERE/../tharsis_gen"
if [ ! -x "$THARSIS" ]; then
    echo "Falta $THARSIS. Compílalo primero."
    exit 1
fi

PASS=0
FAIL=0

for t in *.t; do
    [ -e "$t" ] || continue
    base="${t%.t}"
    esperado="${base}.c.esperado"
    generado="${base}.c"

    if ! "$THARSIS" "$t" --solo-c >/dev/null 2>&1; then
        echo "FAIL (transpilación): $t"
        FAIL=$((FAIL + 1))
        continue
    fi

    if [ ! -f "$esperado" ]; then
        echo "SKIP (sin esperado): $t"
        continue
    fi

    if diff -q "$generado" "$esperado" >/dev/null; then
        echo "PASS: $t"
        PASS=$((PASS + 1))
    else
        echo "FAIL (diff): $t"
        diff "$generado" "$esperado" | head -30
        FAIL=$((FAIL + 1))
    fi
done

echo "----"
echo "PASS: $PASS  FAIL: $FAIL"
[ "$FAIL" -eq 0 ]
