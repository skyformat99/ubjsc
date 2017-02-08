#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/true.js"

cat "${HERE}/true.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/true.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/true.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/true.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/true.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/true.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/true.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/true.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/true.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/true.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/true.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/true.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

