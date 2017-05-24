#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] float32"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/float32.js"> tested.txt
diff "${HERE}/float32.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/float32.js"> tested.txt
diff "${HERE}/float32.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/float32.js"> tested.txt
diff "${HERE}/float32.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/float32.ubjson" > tested.txt
diff "${HERE}/float32.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/float32.ubjson" > tested.txt
diff "${HERE}/float32.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/float32.ubjson" > tested.txt
diff "${HERE}/float32.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/float32.ubjson" > tested.txt
diff "${HERE}/float32.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

