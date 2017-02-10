#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

