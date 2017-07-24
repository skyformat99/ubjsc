#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo -n "usage: ubjq ubjson error ..."
echo -n "SZ" | ./"ubjq" &> tested.txt
diff "${HERE}/ubjq-ubjson-error.txt" tested.txt
if test $? -eq 0
then
    echo "[OK]"
else
    echo "[FAIL]"
    FAIL=1
fi
rm tested.txt

exit "${FAIL}"

