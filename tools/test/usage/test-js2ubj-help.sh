#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo -n "usage: js2ubj ..."
./"js2ubj" -h &> tested.txt
diff "${HERE}/js2ubj"-h.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "usage: js2ubj --rower ..."
./"js2ubj" --rower &> tested.txt
diff "${HERE}/js2ubj"-error.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

