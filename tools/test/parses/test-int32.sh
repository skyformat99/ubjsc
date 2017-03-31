#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/int32.js"> tested.txt
diff "${HERE}/int32.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/int32.js"> tested.txt
diff "${HERE}/int32.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/int32.js"> tested.txt
diff "${HERE}/int32.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/int32.ubjson" > tested.txt
diff "${HERE}/int32.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/int32.ubjson" > tested.txt
diff "${HERE}/int32.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/int32.ubjson" > tested.txt
diff "${HERE}/int32.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/int32.ubjson" > tested.txt
diff "${HERE}/int32.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

