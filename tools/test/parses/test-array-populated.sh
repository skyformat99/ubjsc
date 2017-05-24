#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] array-populated"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/array-populated.js"> tested.txt
diff "${HERE}/array-populated.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
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

./ubjq < "${HERE}/array-populated.ubjson" > tested.txt
diff "${HERE}/array-populated.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

