#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] int16"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/int16.js"> tested.txt
diff "${HERE}/int16.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/int16.js"> tested.txt
diff "${HERE}/int16.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/int16.js"> tested.txt
diff "${HERE}/int16.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/int16.ubjson" > tested.txt
diff "${HERE}/int16.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/int16.ubjson" > tested.txt
diff "${HERE}/int16.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/int16.ubjson" > tested.txt
diff "${HERE}/int16.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/int16.ubjson" > tested.txt
diff "${HERE}/int16.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

