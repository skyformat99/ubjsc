#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/array-populated.js"

cat "${HERE}/array-populated.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/array-populated.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array-populated.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/array-populated.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array-populated.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/array-populated.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array-populated.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/array-populated.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array-populated.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/array-populated.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array-populated.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/array-populated.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

