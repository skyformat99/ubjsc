#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

echo -n "SZ" | ./"ubj2js" &> tested.txt
diff "${HERE}/ubj2js-ubjson-error.txt" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

