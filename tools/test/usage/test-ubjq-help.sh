#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo -n "usage: ubjq ..."
./"ubjq" -h &> tested.txt
diff "${HERE}/ubjq"-h.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

echo -n "usage: ubjq --rower ..."
./"ubjq" --rower &> tested.txt
diff "${HERE}/ubjq"-error.txt tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

