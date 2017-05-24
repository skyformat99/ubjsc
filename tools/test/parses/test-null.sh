#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] null"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/null.js"> tested.txt
diff "${HERE}/null.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/null.ubjson" > tested.txt
diff "${HERE}/null.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

