#!/bin/bash
set -x

HERE=$(dirname "$0")
FAIL=0

./js2ubj < "${HERE}/true.js"> tested.txt
diff "${HERE}/true.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v < "${HERE}/true.js"> tested.txt
diff "${HERE}/true.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./js2ubj -v --pretty-print-output < "${HERE}/true.js"> tested.txt
diff "${HERE}/true.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/true.ubjson" > tested.txt
diff "${HERE}/true.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/true.ubjson" > tested.txt
diff "${HERE}/true.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/true.ubjson" > tested.txt
diff "${HERE}/true.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/true.ubjson" > tested.txt
diff "${HERE}/true.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

