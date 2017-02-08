#!/bin/bash
set -x

HERE="$(dirname $0)"
FAIL=0

cat "${HERE}/object.js"

cat "${HERE}/object.js" | ./js2ubj > tested.txt
cat tested.txt
diff "${HERE}/object.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object.js" | ./js2ubj -v > tested.txt
cat tested.txt
diff "${HERE}/object.v.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object.js" | ./js2ubj -v --pretty-print-output > tested.txt
cat tested.txt
diff "${HERE}/object.vpp.ubjson" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object.ubjson" | ./ubj2js > tested.txt
cat tested.txt
diff "${HERE}/object.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object.ubjson" | ./ubj2js -v > tested.txt
cat tested.txt
diff "${HERE}/object.v.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

cat "${HERE}/object.ubjson" | ./ubj2js -v --pretty-print-input > tested.txt
cat tested.txt
diff "${HERE}/object.vpp.ubjson2js" tested.txt
test $? -eq 0 || FAIL=1
rm tested.txt

exit "${FAIL}"

