#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/uint8.js"

cat "${HERE}/uint8.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/uint8.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/uint8.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/uint8.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/uint8.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/uint8.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/uint8.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/uint8.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/uint8.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/uint8.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/uint8.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/uint8.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

