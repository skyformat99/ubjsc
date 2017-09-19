#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo -n "usage: ubj2js ..."
./"ubj2js" -h &> tested.txt
diff "${HERE}/ubj2js"-h.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "usage: ubj2js --rower ..."
./"ubj2js" --rower &> tested.txt
diff "${HERE}/ubj2js"-error.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

