#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] object"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/object.js"> tested.txt
diff "${HERE}/object.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/object.ubjson" > tested.txt
diff "${HERE}/object.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

