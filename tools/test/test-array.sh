#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/array.js"

cat "${HERE}/array.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/array.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/array.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/array.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/array.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/array.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/array.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/array.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

