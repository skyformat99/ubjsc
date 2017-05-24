#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] str"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/str.js"> tested.txt
diff "${HERE}/str.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/str.js"> tested.txt
diff "${HERE}/str.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/str.js"> tested.txt
diff "${HERE}/str.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/str.ubjson" > tested.txt
diff "${HERE}/str.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/str.ubjson" > tested.txt
diff "${HERE}/str.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/str.ubjson" > tested.txt
diff "${HERE}/str.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/str.ubjson" > tested.txt
diff "${HERE}/str.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

