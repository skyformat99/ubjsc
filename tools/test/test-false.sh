#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/false.js"

cat "${HERE}/false.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/false.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/false.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/false.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/false.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/false.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/false.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/false.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/false.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/false.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/false.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/false.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

