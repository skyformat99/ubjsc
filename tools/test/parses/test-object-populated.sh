#!/bin/bash

HERE=$(dirname "$0")
FAIL=0

echo "[...] object-populated"
echo "[...][...] js2ubj"
./js2ubj < "${HERE}/object-populated.js"> tested.txt
diff "${HERE}/object-populated.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v"

./js2ubj -v < "${HERE}/object-populated.js"> tested.txt
diff "${HERE}/object-populated.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

echo "[...][...] js2ubj -v --pretty-print-output"
./js2ubj -v --pretty-print-output < "${HERE}/object-populated.js"> tested.txt
diff "${HERE}/object-populated.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js < "${HERE}/object-populated.ubjson" > tested.txt
diff "${HERE}/object-populated.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v < "${HERE}/object-populated.ubjson" > tested.txt
diff "${HERE}/object-populated.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubj2js -v --pretty-print-input < "${HERE}/object-populated.ubjson" > tested.txt
diff "${HERE}/object-populated.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

./ubjq < "${HERE}/object-populated.ubjson" > tested.txt
diff "${HERE}/object-populated.ubjq" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

