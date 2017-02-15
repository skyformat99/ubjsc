#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/int8.js"> tested.txt
diff "${HERE}/int8.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/int8.js"> tested.txt
diff "${HERE}/int8.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/int8.js"> tested.txt
diff "${HERE}/int8.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/int8.ubjson" > tested.txt
diff "${HERE}/int8.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/int8.ubjson" > tested.txt
diff "${HERE}/int8.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/int8.ubjson" > tested.txt
diff "${HERE}/int8.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/int8.ubjson" > tested.txt
diff "${HERE}/int8.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

