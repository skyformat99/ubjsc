#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/float32.js"

cat "${HERE}/float32.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/float32.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/float32.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/float32.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/float32.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/float32.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/float32.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/float32.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/float32.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/float32.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/float32.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/float32.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

