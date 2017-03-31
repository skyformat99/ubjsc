#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/uint8.js"> tested.txt
diff "${HERE}/uint8.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/uint8.ubjson" > tested.txt
diff "${HERE}/uint8.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

