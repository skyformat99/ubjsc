#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/array.js"> tested.txt
diff "${HERE}/array.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/array.ubjson" > tested.txt
diff "${HERE}/array.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

