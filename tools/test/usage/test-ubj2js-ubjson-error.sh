#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo -n "usage: ubj2js ubjson error ..."
echo -n "SZ" | ./"ubj2js" &> tested.txt
diff "${HERE}/ubj2js-ubjson-error.txt" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

