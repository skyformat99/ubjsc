#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/object-populated.js"

cat "${HERE}/object-populated.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/object-populated.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object-populated.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/object-populated.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object-populated.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/object-populated.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object-populated.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/object-populated.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object-populated.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/object-populated.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object-populated.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/object-populated.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

