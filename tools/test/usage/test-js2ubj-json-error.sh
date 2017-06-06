#!/bin/bash
HERE=$(dirname "$0")
FAIL=0

echo -n "usage: js2ubj json error ..."
echo -n "[" | ./js2ubj &> tested.txt
diff "${HERE}/js2ubj-json-error.txt" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

