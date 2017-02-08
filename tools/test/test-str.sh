#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/str.js"

cat "${HERE}/str.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/str.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/str.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/str.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/str.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/str.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/str.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/str.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/str.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/str.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/str.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/str.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

